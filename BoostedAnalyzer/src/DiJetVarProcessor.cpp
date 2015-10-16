#include <vector>

#include "DataFormats/BTauReco/interface/SecondaryVertexTagInfo.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "FWCore/Utilities/interface/Exception.h"

#include "BoostedTTH/BoostedAnalyzer/interface/DiJetVarProcessor.hpp"


void DiJetVarProcessor::Init(const InputCollections& input, VariableContainer& vars) {
 
  vars.InitVar("Evt_ID","I"); // Possible conflict because of same-name variables in BasicVarProcessor

  vars.InitVar( "N_PrimaryVertices","I" );

  vars.InitVar( "N_Jets","I" );
  vars.InitVars( "Jet_E","N_Jets" );
  vars.InitVars( "Jet_M","N_Jets" );
  vars.InitVars( "Jet_Pt","N_Jets" );
  vars.InitVars( "Jet_Phi","N_Jets" );
  vars.InitVars( "Jet_Eta","N_Jets" );
  vars.InitVars( "Jet_CSV","N_Jets" );
  vars.InitVars( "Jet_PartonFlav","N_Jets" );
  vars.InitVars( "Jet_HadronFlav","N_Jets" );
  vars.InitVars( "Jet_Charge","N_Jets" );
  vars.InitVars( "Jet_PileUpID","N_Jets" );
  vars.InitVars( "Jet_NSV","N_Jets" );
  vars.InitVars( "Jet_SumSVMass","N_Jets" );
  vars.InitVars( "Jet_GenJet_Pt","N_Jets" );
  vars.InitVars( "Jet_GenJet_Eta","N_Jets" );
  vars.InitVars( "Jet_GenJet_Phi","N_Jets" );
  vars.InitVars( "Jet_GenParton_PdgId","N_Jets" );

  // Dijet specific variables
  vars.InitVar( "DeltaPhi","F" );
  vars.InitVar( "PtAve","F" );

  bTagger_ = "pfCombinedInclusiveSecondaryVertexV2BJetTags";
  puJetIDDiscr_ = "pileupJetId:fullDiscriminant";
  jetTagInfoSV_ = "pfSecondaryVertex";

  minSVFlightDistSig_ = 1.;

  initialized=true;
}


void DiJetVarProcessor::Process(const InputCollections& input, VariableContainer& vars) {
  if( !initialized ) throw cms::Exception("BadProcessor") << "DiJetVarProcessor not initialized";

  // event variables
  vars.FillIntVar( "Evt_ID", input.eventInfo.evt );
  vars.FillVar( "N_PrimaryVertices",input.selectedPVs.size());  

  // jet variables
  // use "selectedJetsLoose" --> pt>20 GeV  
  const std::vector<pat::Jet>& jets = input.idJets;
  vars.FillVar( "N_Jets", jets.size());
  for( std::vector<pat::Jet>::const_iterator itJet = jets.begin(); itJet != jets.end(); ++itJet) {
    const size_t iJet = itJet - jets.begin();
    vars.FillVars( "Jet_E",iJet,itJet->energy() );
    vars.FillVars( "Jet_M",iJet,itJet->mass() );
    vars.FillVars( "Jet_Pt",iJet,itJet->pt() );
    vars.FillVars( "Jet_Eta",iJet,itJet->eta() );
    vars.FillVars( "Jet_Phi",iJet,itJet->phi() );
    vars.FillVars( "Jet_CSV",iJet,BoostedUtils::GetJetCSV(*itJet,bTagger_) );
    vars.FillVars( "Jet_Charge",iJet,itJet->jetCharge() );
    vars.FillVars( "Jet_PileUpID",iJet,itJet->userFloat(puJetIDDiscr_));
    fillSecondaryVertexInfo(vars,*itJet,iJet);
    if( itJet->genJet() != 0 ) {
      // Info on jet flavour: https://indico.cern.ch/event/448366/session/0/contribution/5/attachments/1159737/1669162/BTVSWNews_24_9_2015.pdf
      vars.FillVars( "Jet_PartonFlav",iJet,itJet->partonFlavour() );
      vars.FillVars( "Jet_HadronFlav",iJet,itJet->hadronFlavour() );
      vars.FillVars( "Jet_GenJet_Pt",iJet,itJet->genJet()->pt());
      vars.FillVars( "Jet_GenJet_Eta",iJet,itJet->genJet()->eta());
      vars.FillVars( "Jet_GenJet_Phi",iJet,itJet->genJet()->phi());
    } else {
      vars.FillVars( "Jet_PartonFlav",iJet, -99999 );
      vars.FillVars( "Jet_HadronFlav",iJet, -99999 );
      vars.FillVars( "Jet_GenJet_Pt",iJet, -9.0);
      vars.FillVars( "Jet_GenJet_Eta",iJet, -9.0);
      vars.FillVars( "Jet_GenJet_Phi",iJet, -9.0);
    }
    if( itJet->genParton() != 0 ) {
      vars.FillVars( "Jet_GenParton_PdgId",iJet, itJet->genParton()->pdgId() ); 
    } else {
      vars.FillVars( "Jet_GenParton_PdgId",iJet, -99999 );
    }
  }
  // compute dijet specific variables from first two jets
  double ptAve    = -99999.;
  double deltaPhi = -99999.;
  if( jets.size() > 1 ) {
    ptAve    = 0.5 * ( jets.at(0).pt() + jets.at(1).pt() );
    deltaPhi = std::abs( reco::deltaPhi( jets.at(0).phi(), jets.at(1).phi() ) );
  }
  vars.FillVar( "PtAve",    ptAve    );
  vars.FillVar( "DeltaPhi", deltaPhi );
}


void DiJetVarProcessor::fillSecondaryVertexInfo(VariableContainer& vars, const pat::Jet& jet, const size_t iJet) const {
  int nSV = 0;		// number of secondary vertices
  float sumSVM = 0.;	// sum of secondary vertex masses

  // std::cout << "\n\nTagInfoLabels" << std::endl;
  // for(std::vector<std::string>::const_iterator it = jet.tagInfoLabels().begin(); it != jet.tagInfoLabels().end(); ++it) {
  //   std::cout << *it << std::endl;
  // }

  if( jet.hasTagInfo(jetTagInfoSV_) ) {
    std::cout << "Jet has SVInfo" << std::endl;
    const reco::SecondaryVertexTagInfo* svti = jet.tagInfoSecondaryVertex(jetTagInfoSV_);
    if( svti != 0 ) {
      std::cout << "  Jet has SVInfo objec" << std::endl;
      // Vertices in a jet are not ordered in flight distance significance!!!
      for(size_t isv = 0; isv < svti->nVertices(); ++isv) {
	// Consider only SV with a minimum significance
	if( svti->flightDistance(isv).significance() > minSVFlightDistSig_ ) {
	  const reco::Vertex& sv = svti->secondaryVertex(isv);
	  sumSVM += sv.p4().mass();
	  ++nSV;
	}
      }	// end of loop over SV
    } // end SV tag info exists
  }

  vars.FillVars( "Jet_NSV",       iJet, nSV    );
  vars.FillVars( "Jet_SumSVMass", iJet, sumSVM );
}
        
