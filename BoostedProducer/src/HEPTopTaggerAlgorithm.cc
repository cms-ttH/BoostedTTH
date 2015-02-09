// Copyright (c) 2011 Christopher Vermilion
//
//----------------------------------------------------------------------
//  This file is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 3 of the License, or
//  (at your option) any later version.
//
//  This file is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  The GNU General Public License is available at
//  http://www.gnu.org/licenses/gpl.html or you can write to the Free Software
//  Foundation, Inc.:
//      59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//----------------------------------------------------------------------

#include "BoostedTTH/BoostedProducer/interface/HEPTopTaggerAlgorithm.h"

#include <fastjet/Error.hh>
#include <fastjet/ClusterSequenceArea.hh>
#include <fastjet/JetDefinition.hh>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>

using namespace std;


////////////////////////////////////////////////////////////////////////////////
// construction / destruction
////////////////////////////////////////////////////////////////////////////////

//______________________________________________________________________________
HEPTopTaggerAlgorithm::HEPTopTaggerAlgorithm(const std::string& moduleLabel,
											bool verbose,
											bool doAreaFastjet,
											unsigned nFatMax,
											double jetPtMin,
											double centralEtaCut,
											double massDropCut,
											double subjetMassCut,
											bool requireTopTag)
  : moduleLabel_(moduleLabel),
  	verbose_(verbose),
	doAreaFastjet_(doAreaFastjet),
	nFatMax_(nFatMax),
	jetPtMin_(jetPtMin),
	centralEtaCut_(centralEtaCut),
  	massDropCut_(massDropCut),
	subjetMassCut_(subjetMassCut),
	requireTopTag_(requireTopTag),
	nevents_(0),
	ntotal_(0),
	nfound_(0)
{

}


//______________________________________________________________________________
HEPTopTaggerAlgorithm::~HEPTopTaggerAlgorithm()
{

}
  

////////////////////////////////////////////////////////////////////////////////
// implementation of member functions
////////////////////////////////////////////////////////////////////////////////


namespace{
	/// does the actual work for printing out a jet
	ostream & operator<<(ostream & ostr, fastjet::PseudoJet & jet) {
	  ostr << "pt="  <<setw(10)<<jet.perp() 
    	   << " eta="<<setw(6) <<jet.eta()  
    	   << " m="  <<setw(10)<<jet.m();
	  return ostr;
	}
}


//______________________________________________________________________________
void HEPTopTaggerAlgorithm::run(const std::vector<fastjet::PseudoJet>& fjInputs, 
								std::vector<CompoundPseudoJet>& fjJets,
								std::vector<bool>& topTags,
								boost::shared_ptr<fastjet::ClusterSequence> & fjClusterSeq)
{
	nevents_++;
	
	if (verbose_) cout<<endl<<nevents_<<". EVENT"<<endl;
	
	vector<fastjet::PseudoJet> fjFatJets = fastjet::sorted_by_pt(fjClusterSeq->inclusive_jets(jetPtMin_));
	
	vector<fastjet::PseudoJet> fjCentralFatJets;
	
	vector<fastjet::PseudoJet>::iterator fjFatJetIt = fjFatJets.begin(), fjFatJetEnd = fjFatJets.end();
	
	for (;fjFatJetIt!=fjFatJetEnd; fjFatJetIt++) {
		if (fjFatJetIt->perp() > jetPtMin_ && fabs(fjFatJetIt->pseudorapidity()) < centralEtaCut_) fjCentralFatJets.push_back(*fjFatJetIt);
	}
	
	if(verbose_) cout<<endl<<"NUMBER OF FAT JETS BEFORE SELECTION : "<<fjFatJets.size()<<"\tAFTER SELECTION : "<<fjCentralFatJets.size()<<endl;
	
	size_t nFat = (nFatMax_==0) ? fjCentralFatJets.size() : std::min(fjCentralFatJets.size(),(size_t)nFatMax_);
	
	vector<fastjet::PseudoJet>::iterator fjCentralFatJetsIt = fjCentralFatJets.begin(), fjCentralFatJetsEnd = fjCentralFatJets.end();
	
	for (;fjCentralFatJetsIt!=fjCentralFatJetsEnd;++fjCentralFatJetsIt){
		
		size_t iFat = fjCentralFatJetsIt - fjCentralFatJets.begin();
		
		if(iFat >= nFat) break;
		
		if (verbose_) cout<<endl<<iFat<<". FATJET: "<<*fjCentralFatJetsIt<<endl;
		
		ntotal_++;
		
		// make sure that there is a "regular" cluster sequence associated
		// with the jet. Note that we also check it is valid (to avoid a
		// more criptic error later on)
		if (!fjCentralFatJetsIt->has_valid_cluster_sequence()){
			throw fastjet::Error("HEPTopTagger can only be applied on jets having an associated (and valid) ClusterSequence");
		}

		HEPTopTagger tagger(*fjCentralFatJetsIt->associated_cluster_sequence(), *fjCentralFatJetsIt); // !!! ---------------------------------------------------- To be modified
		tagger.set_top_range(0.0, 10000.0); // don't do top mass cut; this can be applied later
		tagger.set_mass_drop_threshold(massDropCut_);
		tagger.set_max_subjet_mass(subjetMassCut_);

		tagger.run_tagger();

		// if a top tag is required for keeping the jet (use_subjet_mass_cuts_ = true):
		// check that we passed the tagger; if not continue to next fat jet
		if (requireTopTag_ && !tagger.is_masscut_passed()) continue; // encompasses is_maybe_top() plus subjet mass cuts	
		
		CompoundPseudoJet CompoundResult;
		vector<CompoundPseudoSubJet> TopJetConstituents_CPSJ;
		
		// check if subjets were found by the HEP top tagger; if not store fat jet without subjets
		// if the jet is top tagged this requirement is automatically true;
		if (tagger.is_maybe_top()){

			// create the result and its structure
			const fastjet::JetDefinition::Recombiner *rec = fjCentralFatJetsIt->associated_cluster_sequence()->jet_def().recombiner();

			const vector<fastjet::PseudoJet>& subjets = tagger.top_subjets();
			assert(subjets.size() == 3);

			fastjet::PseudoJet non_W = subjets[0];
			fastjet::PseudoJet W1 = subjets[1];
			fastjet::PseudoJet W2 = subjets[2];
			fastjet::PseudoJet W = join(subjets[1], subjets[2], *rec);

			fastjet::PseudoJet result = fastjet::join( W1, W2, non_W, *rec);
			
			vector<fastjet::PseudoJet> TopJetConstituents;

			TopJetConstituents.push_back(result);
			TopJetConstituents.push_back(non_W);
			TopJetConstituents.push_back(W);
			TopJetConstituents.push_back(W1);
			TopJetConstituents.push_back(W2);

			for (size_t iSub=0;iSub<TopJetConstituents.size();iSub++) {
				vector<int> constituents;
				vector<fastjet::PseudoJet> fjConstituents = TopJetConstituents[iSub].constituents();

				for (size_t iConst=0;iConst<fjConstituents.size();iConst++) {
					int userIndex = fjConstituents[iConst].user_index();
					if (userIndex>=0)  constituents.push_back(userIndex);
				}

				double subJetArea=(doAreaFastjet_) ? ((fastjet::ClusterSequenceArea*)fjClusterSeq.get())->area(TopJetConstituents[iSub]) : 0.0;

				if (constituents.size()>0) TopJetConstituents_CPSJ.push_back(CompoundPseudoSubJet(TopJetConstituents[iSub],subJetArea,constituents));
			}
		}

		double fatJetArea=(doAreaFastjet_) ? ((fastjet::ClusterSequenceArea*)fjClusterSeq.get())->area(*fjCentralFatJetsIt) : 0.0;

		CompoundResult = CompoundPseudoJet(*fjCentralFatJetsIt,fatJetArea,TopJetConstituents_CPSJ);

		if(tagger.is_masscut_passed()){
			topTags.push_back(true);
			nfound_++;
		}
		else topTags.push_back(false);
		
		fjJets.push_back(CompoundResult);	
	}
	
	if(fjJets.size()!=topTags.size()) throw fastjet::Error("HEPTopTagger found a difference in the number of fat jets and the number of top tag bools");
	
	if(verbose_) cout<<endl<<fjJets.size()<<" FATJETS written\n"<<endl;
	
	return;
}


//______________________________________________________________________________
string HEPTopTaggerAlgorithm::summary() const
{
  double eff = (ntotal_>0) ? nfound_/(double)ntotal_ : 0;
  std::stringstream ss;
  ss<<"************************************************************\n"
    <<"* "<<moduleLabel_<<" (HEPTopTaggerAlgorithm) SUMMARY:\n"
    <<"************************************************************\n"
    <<"nevents = "<<nevents_<<endl
    <<"ntotal  = "<<ntotal_<<endl
    <<"nfound  = "<<nfound_<<endl
    <<"eff     = "<<eff<<endl
    <<"************************************************************\n";
  return ss.str();
}
