#include "BoostedTTH/BoostedAnalyzer/interface/AK8JetProcessor.hpp"

using namespace std;

AK8JetProcessor::AK8JetProcessor(MiniAODHelper* helper_): btagger("pfCombinedInclusiveSecondaryVertexV2BJetTags") {}
AK8JetProcessor::~AK8JetProcessor() {}


void AK8JetProcessor::Init(const InputCollections& input, VariableContainer& vars) {

  vars.InitVar( "N_AK8Jets", "I" );

  vars.InitVars( "AK8Jet_E", "N_AK8Jets" );
  vars.InitVars( "AK8Jet_M", "N_AK8Jets" );
  vars.InitVars( "AK8Jet_Pt", "N_AK8Jets" );
  vars.InitVars( "AK8Jet_Phi", "N_AK8Jets" );
  vars.InitVars( "AK8Jet_Eta", "N_AK8Jets" );
  vars.InitVars( "AK8Jet_CSV", "N_AK8Jets" );
  vars.InitVars( "AK8Jet_CSV_DNN", "N_AK8Jets" );
  vars.InitVars( "AK8Jet_Flav", "N_AK8Jets" );
  vars.InitVars( "AK8Jet_PartonFlav", "N_AK8Jets" );
  vars.InitVars( "AK8Jet_Charge", "N_AK8Jets" );
  vars.InitVars( "AK8Jet_GenJet_Pt", "N_AK8Jets" );
  vars.InitVars( "AK8Jet_GenJet_Eta", "N_AK8Jets" );
  vars.InitVars( "AK8Jet_Pruned_Mass", "N_AK8Jets" );
  vars.InitVars( "AK8Jet_Puppi_Softdrop_Mass", "N_AK8Jets" );
  vars.InitVars( "AK8Jet_Tau1", "N_AK8Jets" );
  vars.InitVars( "AK8Jet_Tau2", "N_AK8Jets" );
  vars.InitVars( "AK8Jet_Tau3", "N_AK8Jets" );

  vars.InitVars( "AK8Subjet1_E", "N_AK8Jets" );
  vars.InitVars( "AK8Subjet1_Pt", "N_AK8Jets" );
  vars.InitVars( "AK8Subjet1_Phi", "N_AK8Jets" );
  vars.InitVars( "AK8Subjet1_Eta", "N_AK8Jets" );
  vars.InitVars( "AK8Subjet1_CSV_DNN", "N_AK8Jets" );

  vars.InitVars( "AK8Subjet2_E", "N_AK8Jets" );
  vars.InitVars( "AK8Subjet2_Pt", "N_AK8Jets" );
  vars.InitVars( "AK8Subjet2_Phi", "N_AK8Jets" );
  vars.InitVars( "AK8Subjet2_Eta", "N_AK8Jets" );
  vars.InitVars( "AK8Subjet2_CSV_DNN", "N_AK8Jets" );


  vars.InitVars( "AK8Jet_Dr_GenTopHad", -9., "N_AK8Jets" );
  vars.InitVars( "AK8Jet_Dr_GenTopLep", -9., "N_AK8Jets" );
  vars.InitVars( "AK8Jet_Dr_GenHiggs", -9., "N_AK8Jets" );

  vars.InitVars( "AK8Jet_Dr_GenW", -9., "N_AK8Jets" );
  vars.InitVars( "AK8Jet_Dr_GenB", -9., "N_AK8Jets" );
  vars.InitVars( "AK8Jet_Dr_GenQ1", -9., "N_AK8Jets" );
  vars.InitVars( "AK8Jet_Dr_GenQ2", -9., "N_AK8Jets" );
  vars.InitVars( "AK8Jet_Dr_GenB1", -9., "N_AK8Jets" );
  vars.InitVars( "AK8Jet_Dr_GenB2", -9., "N_AK8Jets" );

  initialized = true;
}

void AK8JetProcessor::Process(const InputCollections& input, VariableContainer& vars) {
  if (!initialized) cerr << "tree processor not initialized" << endl;

  // Fill Multiplicity Variables
  vars.FillVar( "N_AK8Jets", input.AK8Jets.size());

  const char* btagger="DeepCSV";

  // Fill Jet Variables
  // All Jets
  for (std::vector<pat::Jet>::const_iterator itJet = input.AK8Jets.begin() ; itJet != input.AK8Jets.end(); ++itJet) {
    int iJet = itJet - input.AK8Jets.begin();
    vars.FillVars( "AK8Jet_E", iJet, itJet->energy() );
    vars.FillVars( "AK8Jet_M", iJet, itJet->mass() );
    vars.FillVars( "AK8Jet_Pt", iJet, itJet->pt() );
    vars.FillVars( "AK8Jet_Eta", iJet, itJet->eta() );
    vars.FillVars( "AK8Jet_Phi", iJet, itJet->phi() );
    vars.FillVars( "AK8Jet_CSV", iJet, MiniAODHelper::GetJetCSV(*itJet, btagger) );
    vars.FillVars( "AK8Jet_CSV_DNN", iJet, MiniAODHelper::GetJetCSV_DNN(*itJet, btagger) );
    vars.FillVars( "AK8Jet_Flav", iJet, itJet->hadronFlavour() );
    vars.FillVars( "AK8Jet_PartonFlav", iJet, itJet->partonFlavour() );
    vars.FillVars( "AK8Jet_Charge", iJet, itJet->jetCharge() );
    if (itJet->genJet() != NULL) {
      vars.FillVars( "AK8Jet_GenJet_Pt", iJet, itJet->genJet()->pt());
      vars.FillVars( "AK8Jet_GenJet_Eta", iJet, itJet->genJet()->eta());
    }
    else {
      vars.FillVars( "AK8Jet_GenJet_Pt", iJet, -9.0);
      vars.FillVars( "AK8Jet_GenJet_Eta", iJet, -9.0);
    }
    if ( itJet->hasUserFloat("NjettinessAK8Puppi:tau1") ) {
      tau1 = itJet->userFloat("NjettinessAK8Puppi:tau1");
      vars.FillVars( "AK8Jet_Tau1", iJet, tau1 );
    }
    if ( itJet->hasUserFloat("NjettinessAK8Puppi:tau2") ) {
      tau2 = itJet->userFloat("NjettinessAK8Puppi:tau2");
      vars.FillVars( "AK8Jet_Tau2", iJet, tau2 );
    }
    if ( itJet->hasUserFloat("NjettinessAK8Puppi:tau3") ) {
      tau3 = itJet->userFloat("NjettinessAK8Puppi:tau3");
      vars.FillVars( "AK8Jet_Tau3", iJet, tau3 );
    }

    /*
    std::vector< edm::Ptr<reco::Candidate>> allconstituents;
    for (auto const & constituent : itJet->daughterPtrVector()) {
        allconstituents.push_back(constituent);
    }
    */
    int i = 0;
    auto const & sdSubjetsPuppi = itJet->subjets("SoftDropPuppi");
    //make sure subjets exist
    if (sdSubjetsPuppi.size() > 0) {
      vars.FillVars( "AK8Jet_Puppi_Softdrop_Mass", iJet, itJet->userFloat("ak8PFJetsPuppiSoftDropMass"));
      vars.FillVars( "AK8Jet_Pruned_Mass", iJet, itJet->userFloat("ak8PFJetsCHSValueMap:ak8PFJetsCHSPrunedMass"));
      for ( auto& it : sdSubjetsPuppi ) {
        i++;
        if (i == 1) {
          vars.FillVars( "AK8Subjet1_E", iJet, it->correctedP4(0).e());
          vars.FillVars( "AK8Subjet1_Pt", iJet, it->correctedP4(0).pt());
          vars.FillVars( "AK8Subjet1_Phi", iJet, it->correctedP4(0).phi());
          vars.FillVars( "AK8Subjet1_Eta", iJet, it->correctedP4(0).eta());
          vars.FillVars( "AK8Subjet1_CSV_DNN", iJet, MiniAODHelper::GetJetCSV(*it, btagger));
        }
        if (i == 2) {
          vars.FillVars( "AK8Subjet2_E", iJet, it->correctedP4(0).e());
          vars.FillVars( "AK8Subjet2_Pt", iJet, it->correctedP4(0).pt());
          vars.FillVars( "AK8Subjet2_Phi", iJet, it->correctedP4(0).phi());
          vars.FillVars( "AK8Subjet2_Eta", iJet, it->correctedP4(0).eta());
          vars.FillVars( "AK8Subjet2_CSV_DNN", iJet, MiniAODHelper::GetJetCSV(*it, btagger));
        }
      }
    }
  }

  std::vector<reco::GenParticle> tophad;
  std::vector<reco::GenParticle> whad;
  std::vector<reco::GenParticle> bhad;
  std::vector<reco::GenParticle> q1;
  std::vector<reco::GenParticle> q2;
  std::vector<reco::GenParticle> toplep;
  std::vector<reco::GenParticle> wlep;
  std::vector<reco::GenParticle> blep;
  std::vector<reco::GenParticle> lep;
  std::vector<reco::GenParticle> nu;
  reco::GenParticle higgs;
  std::vector<reco::GenParticle> higgs_bs;
  if (input.genTopEvt.IsFilled()) {
    tophad = input.genTopEvt.GetAllTopHads();
    whad = input.genTopEvt.GetAllWhads();
    bhad = input.genTopEvt.GetAllTopHadDecayQuarks();
    q1 = input.genTopEvt.GetAllWQuarks();
    q2 = input.genTopEvt.GetAllWAntiQuarks();
    toplep = input.genTopEvt.GetAllTopLeps();
    wlep = input.genTopEvt.GetAllWleps();
    blep = input.genTopEvt.GetAllTopLepDecayQuarks();
    lep = input.genTopEvt.GetAllLeptons();
    nu = input.genTopEvt.GetAllNeutrinos();
    higgs = input.genTopEvt.GetHiggs();
    higgs_bs = input.genTopEvt.GetHiggsDecayProducts();
  }

  reco::GenParticle b1;
  reco::GenParticle b2;

  for (auto p = higgs_bs.begin(); p != higgs_bs.end(); p++) {
    if (p->pdgId() == 5) b1 = *p;
    if (p->pdgId() == -5) b2 = *p;
  }
  if (input.genTopEvt.IsFilled() && input.genTopEvt.TTxIsFilled()) {
    std::vector<reco::GenParticle> additional_bs = input.genTopEvt.GetAdditionalBHadrons();
    if (additional_bs.size() > 0)
      b1 = additional_bs[0];
    if (additional_bs.size() > 1)
      b2 = additional_bs[1];

  }

  // Match TopLep jets
  for (size_t i = 0; i < input.AK8Jets.size(); i++) {

    float minDr_TopLep = 999;

    for (size_t j = 0; j < toplep.size(); j++) {
      float Dr_temp = BoostedUtils::DeltaR(toplep[j].p4(), input.AK8Jets[i].p4());
      if (Dr_temp < minDr_TopLep) minDr_TopLep = Dr_temp;
    }

    if (minDr_TopLep < 999) {
      vars.FillVars("AK8Jet_Dr_GenTopLep", i, minDr_TopLep);
    }
  }

  // Match TopHad jets
  for (size_t i = 0; i < input.AK8Jets.size(); i++) {

    float minDr_TopHad = 999;
    float minDr_WHad = 999;
    float minDr_TopB = 999;
    float minDr_TopQ1 = 999;
    float minDr_TopQ2 = 999;

    for (size_t j = 0; j < tophad.size(); j++) {
      float Dr_temp = BoostedUtils::DeltaR(tophad[j].p4(), input.AK8Jets[i].p4());
      if (Dr_temp < minDr_TopHad) {
        minDr_TopHad = Dr_temp;
        minDr_WHad = BoostedUtils::DeltaR(whad[j].p4(), input.AK8Jets[i].p4());
        minDr_TopB = BoostedUtils::DeltaR(bhad[j].p4(), input.AK8Jets[i].p4());
        minDr_TopQ1 = BoostedUtils::DeltaR(q1[j].p4(), input.AK8Jets[i].p4());
        minDr_TopQ2 = BoostedUtils::DeltaR(q2[j].p4(), input.AK8Jets[i].p4());
      }
    }

    if (minDr_TopHad < 999) vars.FillVars("AK8Jet_Dr_GenTopHad", i, minDr_TopHad);
    if (minDr_WHad < 999) vars.FillVars("AK8Jet_Dr_GenW", i, minDr_WHad);
    if (minDr_TopB < 999) vars.FillVars("AK8Jet_Dr_GenB", i, minDr_TopB);
    if (minDr_TopQ1 < 999) vars.FillVars("AK8Jet_Dr_GenQ1", i, minDr_TopQ1);
    if (minDr_TopQ2 < 999) vars.FillVars("AK8Jet_Dr_GenQ2", i, minDr_TopQ2);
  }

  for (size_t i = 0; i < input.AK8Jets.size(); i++) {
    if (higgs.pt() > 0.) {
      vars.FillVars("AK8Jet_Dr_GenHiggs", i, BoostedUtils::DeltaR(higgs.p4(), input.AK8Jets[i].p4()));
    }
    if (b1.pt() > 0.) vars.FillVars("AK8Jet_Dr_GenB1", i, BoostedUtils::DeltaR(b1.p4(), input.AK8Jets[i].p4()));
    if (b2.pt() > 0.) vars.FillVars("AK8Jet_Dr_GenB2", i, BoostedUtils::DeltaR(b2.p4(), input.AK8Jets[i].p4()));
  }
}