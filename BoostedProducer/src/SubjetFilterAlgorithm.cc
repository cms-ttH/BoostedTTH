////////////////////////////////////////////////////////////////////////////////
//
// SubjetFilterAlgorithm
// ---------------------
//
// This algorithm implements the Subjet/Filter jet reconstruction
// which was first proposed here: http://arXiv.org/abs/0802.2470
//
// The implementation is largely based on fastjet_boosted_higgs.cc provided
// with the fastjet package.
//
// see: https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideSubjetFilterJetProducer
//
//                       David Lopes-Pegna           <david.lopes-pegna@cern.ch>
//            25/11/2009 Philipp Schieferdecker <philipp.schieferdecker@cern.ch>
////////////////////////////////////////////////////////////////////////////////


#include "BoostedTTH/BoostedProducer/interface/SubjetFilterAlgorithm.h"

#include <fastjet/ClusterSequenceArea.hh>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>


using namespace std;


////////////////////////////////////////////////////////////////////////////////
// construction / destruction
////////////////////////////////////////////////////////////////////////////////

//______________________________________________________________________________
SubjetFilterAlgorithm::SubjetFilterAlgorithm(const std::string& moduleLabel,
					     bool verbose,
					     bool doAreaFastjet,
					     double rParam,
					     unsigned nFatMax,
					     double jetPtMin,
					     double centralEtaCut,
					     double massDropCut,
					     double rFilt,
					     double asymmCut,
					     bool asymmCutLater,
					     double filterJetPtMin)
  : moduleLabel_(moduleLabel),
    verbose_(verbose),
	doAreaFastjet_(doAreaFastjet),
    rParam_(rParam),
	nFatMax_(nFatMax),
	jetPtMin_(jetPtMin),
	centralEtaCut_(centralEtaCut),
	massDropCut_(massDropCut),
	rFilt_(rFilt),
	asymmCut2_(asymmCut*asymmCut),
	asymmCutLater_(asymmCutLater),
	filterJetPtMin_(filterJetPtMin),
	nevents_(0),
	ntotal_(0),
	nfound_(0)
{

}


//______________________________________________________________________________
SubjetFilterAlgorithm::~SubjetFilterAlgorithm()
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
void SubjetFilterAlgorithm::run(const std::vector<fastjet::PseudoJet>& fjInputs, 
				std::vector<CompoundPseudoJet>& fjJets,
				boost::shared_ptr<fastjet::ClusterSequence> & cs)
{
	nevents_++;
	if (verbose_) cout<<endl<<nevents_<<". EVENT"<<endl;
	
	vector<fastjet::PseudoJet> fjFatJets = fastjet::sorted_by_pt(cs->inclusive_jets(jetPtMin_));
	
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
		
		fastjet::PseudoJet fjFatJet = *fjCentralFatJetsIt;
		fastjet::PseudoJet fjCurrentJet(fjFatJet);
		fastjet::PseudoJet fjSubJet1,fjSubJet2;
		bool hadSubJets;

		vector<CompoundPseudoSubJet> subJets;

		// FIND SUBJETS PASSING MASSDROP [AND ASYMMETRY] CUT(S)
		while ((hadSubJets = cs->has_parents(fjCurrentJet,fjSubJet1,fjSubJet2))) {

			if (fjSubJet1.m() < fjSubJet2.m()) swap(fjSubJet1,fjSubJet2);

			if (verbose_) cout << "SUBJET CANDIDATES: " << fjSubJet1 << endl << "                   " << fjSubJet2 << endl;
			if (verbose_) cout << "md=" << fjSubJet1.m()/fjCurrentJet.m() << " y=" << fjSubJet1.kt_distance(fjSubJet2)/fjCurrentJet.m2() << endl;

			if (fjSubJet1.m()<massDropCut_*fjCurrentJet.m() && (asymmCutLater_|| fjSubJet1.kt_distance(fjSubJet2)>asymmCut2_*fjCurrentJet.m2())){
				break;
			}
			else {
				fjCurrentJet = fjSubJet1;
			}
		}

		if(!hadSubJets){
			if (verbose_) cout<<"FAILED TO SELECT SUBJETS"<<endl;
		}
		// FOUND TWO GOOD SUBJETS PASSING MASSDROP CUT
		else {
			if (verbose_) cout<<"SUBJETS selected"<<endl;

			if (asymmCutLater_&& fjSubJet1.kt_distance(fjSubJet2)<=asymmCut2_*fjCurrentJet.m2()){
				if (verbose_) cout<<"FAILED y-cut"<<endl;
			}
			// PASSED ASYMMETRY (Y) CUT
			else {
				if (verbose_) cout<<"PASSED y cut"<<endl;

				vector<fastjet::PseudoJet> fjFilterJets;
				vector<fastjet::PseudoJet> fjFilterJets_nocut;
				double       Rbb   = std::sqrt(fjSubJet1.squared_distance(fjSubJet2));
				double       Rfilt = std::min(0.5*Rbb,rFilt_);
				double       dcut  = Rfilt*Rfilt/rParam_/rParam_;
				
				fjFilterJets_nocut=fastjet::sorted_by_pt(cs->exclusive_subjets(fjCurrentJet,dcut));
				for(size_t iFilter=0;iFilter<fjFilterJets_nocut.size();iFilter++){
				  if(fjFilterJets_nocut[iFilter].pt()>filterJetPtMin_) fjFilterJets.push_back(fjFilterJets_nocut[iFilter]);
				  else break;
				}
				
				if (verbose_) {
					cout<<"Rbb="<<Rbb<<", Rfilt="<<Rfilt<<endl;
					cout<<"FILTER JETS: "<<flush;
					for (size_t i=0;i<fjFilterJets.size();i++) {
						if (i>0) cout<<"             "<<flush; cout<<fjFilterJets[i]<<endl;
					}
				}

				vector<fastjet::PseudoJet> fjSubJets;
				fjSubJets.push_back(fjSubJet1);
				fjSubJets.push_back(fjSubJet2);
				
				size_t nFilter = fjFilterJets.size();
				
				for (size_t iFilter=0;iFilter<nFilter;iFilter++) fjSubJets.push_back(fjFilterJets[iFilter]);

				for (size_t iSub=0;iSub<fjSubJets.size();iSub++) {
					vector<fastjet::PseudoJet> fjConstituents = cs->constituents(fjSubJets[iSub]);
					vector<int> constituents;
					for (size_t iConst=0;iConst<fjConstituents.size();iConst++) {
						int userIndex = fjConstituents[iConst].user_index();
						if (userIndex>=0)  constituents.push_back(userIndex);
					}

					double subJetArea=(doAreaFastjet_) ? ((fastjet::ClusterSequenceArea*)(cs.get()))->area(fjSubJets[iSub]) : 0.0;

					if (iSub<2||constituents.size()>0) subJets.push_back(CompoundPseudoSubJet(fjSubJets[iSub],subJetArea,constituents));
				}
				
				//delete cs_Filterjet;

			} // PASSED Y CUT

		} // PASSED MASSDROP CUT

		if (verbose_) cout<< "write fatjet with " << subJets.size() <<" sub+filter jets" << endl;

		double fatJetArea = (doAreaFastjet_) ? ((fastjet::ClusterSequenceArea*)(cs.get()))->area(fjFatJet) : 0.0;

		fjJets.push_back(CompoundPseudoJet(fjFatJet,fatJetArea,subJets));

		if (subJets.size()>3) nfound_++;

	} // LOOP OVER FATJETS

	if (verbose_) cout<<endl<<fjJets.size()<<" FATJETS written\n"<<endl;
	
	//delete cs;

	return;
}


//______________________________________________________________________________
string SubjetFilterAlgorithm::summary() const
{
  double eff = (ntotal_>0) ? nfound_/(double)ntotal_ : 0;
  std::stringstream ss;
  ss<<"************************************************************\n"
    <<"* "<<moduleLabel_<<" (SubjetFilterAlgorithm) SUMMARY:\n"
    <<"************************************************************\n"
    <<"nevents = "<<nevents_<<endl
    <<"ntotal  = "<<ntotal_<<endl
    <<"nfound  = "<<nfound_<<endl
    <<"eff     = "<<eff<<endl
    <<"************************************************************\n";
  return ss.str();
}
