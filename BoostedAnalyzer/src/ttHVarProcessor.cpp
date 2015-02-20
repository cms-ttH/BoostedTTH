#include "BoostedTTH/BoostedAnalyzer/interface/ttHVarProcessor.hpp"

using namespace std;

ttHVarProcessor::ttHVarProcessor(BoostedRecoType recotype_, std::string taggername_, std::string higgstaggername_, std::string suffix_){
  recotype = recotype_;
  suffix = suffix_;

  InitTopTagger(taggername_);
  InitHiggsTagger(higgstaggername_);

}
ttHVarProcessor::~ttHVarProcessor(){}


void ttHVarProcessor::Init(const InputCollections& input,VariableContainer& vars){
  InitHiggsCandidateVars(vars);
  InitTopHadCandidateVars(vars);
  InitTopLepCandidateVars(vars);
  InitAk5JetsVars(vars);
  InitCombinationVars(vars);
  InitMCVars(vars);
  initialized = true;
}


void ttHVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;

  BoostedttHEvent ttHEvent = BoostedttHEvent(input);  
  
  if(recotype == BoostedRecoType::BoostedTopHiggs)
    ttHEvent.BoostedTopHiggsEventRec(toptagger, higgstagger);
  else if(recotype == BoostedRecoType::BoostedHiggs)
    ttHEvent.BoostedHiggsEventRec(higgstagger);
  else  if(recotype == BoostedRecoType::BoostedTop)
    ttHEvent.BoostedTopEventRec(toptagger);
  else
    cerr << "ttH reconstruction: no event reconstruction found" << endl;
  
  FillHiggsCandidateVars(vars,ttHEvent);
  FillTopHadCandidateVars(vars,ttHEvent);
  FillTopLepCandidateVars(vars,ttHEvent);
  FillAk5JetsVars(vars,ttHEvent);
  FillCombinationVars(vars,ttHEvent);
  FillMCVars(vars,ttHEvent);
}


void ttHVarProcessor::InitTopTagger(string taggername){
 
  if(taggername!=""){
    if(taggername.find("TopLikelihood")!=std::string::npos) toptagger = TopTagger(taggername);
    else if(taggername.find("TMVATopTagger")!=std::string::npos){

      vector<string> BDTVars;
      string weights;

      if(taggername == "TMVATopTaggerOutput_MWDef_CombDef_ttbar"){
        BDTVars.push_back("M_Top_TopJet");
        BDTVars.push_back("Dr_Lep_TopJet");
        BDTVars.push_back("Pt_W2_TopJet");
        BDTVars.push_back("Pt_B_TopJet");
        BDTVars.push_back("NSubjettiness_12_Ratio_TopJet");
        BDTVars.push_back("Pt_W1_TopJet");
        BDTVars.push_back("M_W_TopJet");
        BDTVars.push_back("CSV_B_TopJet");

        weights = "/nfs/dust/cms/user/tpfotzer/ttbarX/BEANs/mva/TMVA/TMVATopTagger/weights/TMVATopTagger_BDTG_MWDef_CombDef.weights.xml";
      }

      toptagger = TopTagger(taggername,BDTVars,weights); 
    }
  } 
}


void ttHVarProcessor::InitHiggsTagger(string higgstaggerName){
  
  if(higgstaggerName.find("HiggsLikelihood")!=std::string::npos || higgstaggerName.find("HiggsBDT")!=std::string::npos){
    std::vector<std::string> HBDTVars;
    HBDTVars.push_back("Pt_HiggsJet");
    HBDTVars.push_back("Dr_Lep_HiggsJet");
    HBDTVars.push_back("M2_HiggsJet");
    HBDTVars.push_back("M3_HiggsJet");
    HBDTVars.push_back("Dr_TopJet1_HiggsJet");
    HBDTVars.push_back("Dr_TopJet2_HiggsJet");
    HBDTVars.push_back("CSV1_HiggsJet");
    HBDTVars.push_back("CSV2_HiggsJet");
    HBDTVars.push_back("NSubjettiness_13_Ratio_HiggsJet");
    HBDTVars.push_back("M3_SingleTag_HiggsJet");
    HBDTVars.push_back("IdxAk5_Filterjet2_HiggsJet");
    HBDTVars.push_back("CSV_Filterjet2_HiggsJet");

    string Hweightfile = "";
  
    if(higgstaggerName.find("HiggsLikelihood")!=std::string::npos) Hweightfile = (BoostedUtils::GetAnalyzerPath()+"/data/HiggsTagger/Likelihood.weights.xml").c_str();
    else if(higgstaggerName.find("HiggsBDT")!=std::string::npos) Hweightfile = (BoostedUtils::GetAnalyzerPath()+"/data/HiggsTagger/BDTG.weights.xml").c_str();
    else cerr << "Cant find specified HiggsTagger" << endl;
    
    higgstagger = new HiggsTagger(higgstaggerName, HBDTVars, Hweightfile);
  }  
  else if(higgstaggerName.find("HiggsCSV")!=std::string::npos){
    higgstagger = new HiggsTagger(higgstaggerName);
  }
  else cerr << "Cant find specified HiggsTagger" << endl;
}

void ttHVarProcessor::InitHiggsCandidateVars(VariableContainer& vars){
  
  vars.InitVar("HiggsTag_HiggsCandidate_"+suffix,-9.9);
  vars.InitVar("E_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Pt_HiggsCandidate"+suffix,-9.);
  vars.InitVar("M_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Eta_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Phi_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Pt_Filterjet2_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Pt_Filterjet1_HiggsCandidate"+suffix,-9.);
  
  vars.InitVar("E_B1_HiggsCandidate"+suffix,-9.);
  vars.InitVar("E_B2_HiggsCandidate"+suffix,-9.);
  vars.InitVar("E_G_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Pt_B1_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Pt_B2_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Pt_G_HiggsCandidate"+suffix,-9.);
  vars.InitVar("M_B1_HiggsCandidate"+suffix,-9.);
  vars.InitVar("M_B2_HiggsCandidate"+suffix,-9.);
  vars.InitVar("M_G_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Eta_B1_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Eta_B2_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Eta_G_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Phi_B1_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Phi_B2_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Phi_G_HiggsCandidate"+suffix,-9.);
  vars.InitVar("CSV_B1_HiggsCandidate"+suffix,-.1);
  vars.InitVar("CSV_B2_HiggsCandidate"+suffix,-.1);
  vars.InitVar("CSV_G_HiggsCandidate"+suffix,-.1);
  
  vars.InitVar("E2_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Pt2_HiggsCandidate"+suffix,-9.);
  vars.InitVar("M2_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Eta2_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Phi2_HiggsCandidate"+suffix,-9.);
  vars.InitVar("E3_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Pt3_HiggsCandidate"+suffix,-9.);
  vars.InitVar("M3_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Eta3_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Phi3_HiggsCandidate"+suffix,-9.);
  
  vars.InitVar("CosThetaStar_Filterjet12_HiggsCandidate"+suffix,-9.);
  vars.InitVar("CosThetaStar_Filterjet13_HiggsCandidate"+suffix,-9.);
  vars.InitVar("CosThetaStar_Filterjet23_HiggsCandidate"+suffix,-9.);
  
  vars.InitVar("Subjetiness1_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Subjetiness2_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Subjetiness3_HiggsCandidate"+suffix,-9.);
  
  vars.InitVar("Dr_Lepton_HiggsCandidate"+suffix,-9.);
  
  vars.InitVar("M_Lepton_B_HiggsCandidate"+suffix,-9.);
  vars.InitVar("M_TopLep_HiggsCandidate"+suffix,-9.);
}


void ttHVarProcessor::InitTopHadCandidateVars(VariableContainer& vars){

  vars.InitVar("Tagged_TopHadCandidate"+suffix,-9.);
  vars.InitVar("TaggedB_TopHadCandidate"+suffix,-9.);
  vars.InitVar("TopMVAOutput_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Chi2_TopHadCandidate_BoostedHiggs"+suffix,-9.);
  
  vars.InitVar("E_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Pt_TopHadCandidate"+suffix,-9.);
  vars.InitVar("M_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Eta_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Phi_TopHadCandidate"+suffix,-9.);
  
  vars.InitVar("E_B_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Pt_B_TopHadCandidate"+suffix,-9.);
  vars.InitVar("M_B_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Eta_B_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Phi_B_TopHadCandidate"+suffix,-9.);
  vars.InitVar("CSV_B_TopHadCandidate"+suffix,-.1);

  vars.InitVar("E_W1_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Pt_W1_TopHadCandidate"+suffix,-9.);
  vars.InitVar("M_W1_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Eta_W1_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Phi_W1_TopHadCandidate"+suffix,-9.);
  vars.InitVar("CSV_W1_TopHadCandidate"+suffix,-1.);

  vars.InitVar("E_W2_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Pt_W2_TopHadCandidate"+suffix,-9.);
  vars.InitVar("M_W2_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Eta_W2_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Phi_W2_TopHadCandidate"+suffix,-9.);
  vars.InitVar("CSV_W2_TopHadCandidate"+suffix,-1.);

  vars.InitVar("E_W_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Pt_W_TopHadCandidate"+suffix,-9.);
  vars.InitVar("M_W_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Eta_W_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Phi_W_TopHadCandidate"+suffix,-9.);
  
  vars.InitVar("E_BW1_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Pt_BW1_TopHadCandidate"+suffix,-9.);
  vars.InitVar("M_BW1_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Eta_BW1_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Phi_BW1_TopHadCandidate"+suffix,-9.);
  
  vars.InitVar("E_BW2_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Pt_BW2_TopHadCandidate"+suffix,-9.);
  vars.InitVar("M_BW2_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Eta_BW2_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Phi_BW2_TopHadCandidate"+suffix,-9.);
  
  vars.InitVar("E_Top_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Pt_Top_TopHadCandidate"+suffix,-9.);
  vars.InitVar("M_Top_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Eta_Top_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Phi_Top_TopHadCandidate"+suffix,-9.);
  
  vars.InitVar("Subjettiness1_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Subjettiness2_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Subjettiness3_TopHadCandidate"+suffix,-9.);
 
  vars.InitVar("Dr_Lepton_TopHadCandidate"+suffix,-9.);
  vars.InitVar("M_Lepton_B_TopHadCandidate"+suffix,-9.);
  vars.InitVar("M_TopLep_TopHadCandidate"+suffix,-9.);
  vars.InitVar("M_HiggsAk5_TopHadCandidate"+suffix,-9.);
  vars.InitVar("M_TopHadAk5_TopHadCandidate"+suffix,-9.);
  vars.InitVar("M_HiggsAk5Loose_TopHadCandidate"+suffix,-9.);
  vars.InitVar("M_TopHadAk5Loose_TopHadCandidate"+suffix,-9.);
}


void ttHVarProcessor::InitTopLepCandidateVars(VariableContainer& vars){
  
  vars.InitVar("E_Top_TopLepCandidate"+suffix,-9.);
  vars.InitVar("Pt_Top_TopLepCandidate"+suffix,-9.);
  vars.InitVar("M_Top_TopLepCandidate"+suffix,-9.);
  vars.InitVar("Eta_Top_TopLepCandidate"+suffix,-9.);
  vars.InitVar("Phi_Top_TopLepCandidate"+suffix,-9.);
  
  vars.InitVar("E_W_TopLepCandidate"+suffix,-9.);
  vars.InitVar("Pt_W_TopLepCandidate"+suffix,-9.);
  vars.InitVar("M_W_TopLepCandidate"+suffix,-9.);
  vars.InitVar("Eta_W_TopLepCandidate"+suffix,-9.);
  vars.InitVar("Phi_W_TopLepCandidate"+suffix,-9.);
  
  vars.InitVar("E_B_TopLepCandidate"+suffix,-9.);
  vars.InitVar("Pt_B_TopLepCandidate"+suffix,-9.);
  vars.InitVar("M_B_TopLepCandidate"+suffix,-9.);
  vars.InitVar("Eta_B_TopLepCandidate"+suffix,-9.);
  vars.InitVar("Phi_B_TopLepCandidate"+suffix,-9.);
  vars.InitVar("CSV_B_TopLepCandidate"+suffix,-.1);
  
  vars.InitVar("E_Lep_TopLepCandidate"+suffix,-9.);
  vars.InitVar("Pt_Lep_TopLepCandidate"+suffix,-9.);
  vars.InitVar("M_Lep_TopLepCandidate"+suffix,-9.);
  vars.InitVar("Eta_Lep_TopLepCandidate"+suffix,-9.);
  vars.InitVar("Phi_Lep_TopLepCandidate"+suffix,-9.);
  
  vars.InitVar("E_Nu_TopLepCandidate"+suffix,-9.);
  vars.InitVar("Pt_Nu_TopLepCandidate"+suffix,-9.);
  vars.InitVar("M_Nu_TopLepCandidate"+suffix,-9.);
  vars.InitVar("Eta_Nu_TopLepCandidate"+suffix,-9.);
  vars.InitVar("Phi_Nu_TopLepCandidate"+suffix,-9.);
}


void ttHVarProcessor::InitAk5JetsVars(VariableContainer& vars){
  
  vars.InitVar("N_Jets_ak5Jets"+suffix,-9.,"I");
  vars.InitVar("N_BTagsL_ak5Jets"+suffix,-9.,"I");
  vars.InitVar("N_BTagsM_ak5Jets"+suffix,-9.,"I");
  vars.InitVar("N_BTagsT_ak5Jets"+suffix,-9.,"I");
  vars.InitVar("AvgCSV_ak5Jets"+suffix,-.1);
  
  vars.InitVar("N_Jets_Higgs_ak5Jets"+suffix,-9.,"I");
  vars.InitVar("N_BTagsL_Higgs_ak5Jets"+suffix,-9.,"I");
  vars.InitVar("N_BTagsM_Higgs_ak5Jets"+suffix,-9.,"I");
  vars.InitVar("N_BTagsT_Higgs_ak5Jets"+suffix,-9.,"I");
  vars.InitVar("AvgCSV_Higgs_ak5Jets"+suffix,-.1);
  
  vars.InitVar("N_Jets_TopHad_ak5Jets"+suffix,-9.,"I");
  vars.InitVar("N_BTagsL_TopHad_ak5Jets"+suffix,-9.,"I");
  vars.InitVar("N_BTagsM_TopHad_ak5Jets"+suffix,-9.,"I");
  vars.InitVar("N_BTagsT_TopHad_ak5Jets"+suffix,-9.,"I");
  vars.InitVar("AvgCSV_TopHad_ak5Jets"+suffix,-.1);
  
  vars.InitVar("N_Jets_TopLep_ak5Jets"+suffix,-9.,"I");
  vars.InitVar("N_BTagsL_TopLep_ak5Jets"+suffix,-9.,"I");
  vars.InitVar("N_BTagsM_TopLep_ak5Jets"+suffix,-9.,"I");
  vars.InitVar("N_BTagsT_TopLep_ak5Jets"+suffix,-9.,"I");
  vars.InitVar("AvgCSV_TopLep_ak5Jets"+suffix,-.1);
  
  vars.InitVar("N_Jets_Clean_ak5Jets"+suffix,-9.,"I");
  vars.InitVar("N_BTagsL_Clean_ak5Jets"+suffix,-9.,"I");
  vars.InitVar("N_BTagsM_Clean_ak5Jets"+suffix,-9.,"I");
  vars.InitVar("N_BTagsT_Clean_ak5Jets"+suffix,-9.,"I");
  vars.InitVar("AvgCSV_Clean_ak5Jets"+suffix,-.1);
}


void ttHVarProcessor::InitCombinationVars(VariableContainer& vars){
  
  vars.InitVar("Dr_TopHadCandidate_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Dr_TopLepCandidate_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Dr_TopLepCandidate_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Dphi_TopHadCandidate_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Dphi_TopLepCandidate_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Dphi_TopLepCandidate_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Deta_TopHadCandidate_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Deta_TopLepCandidate_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Deta_TopLepCandidate_TopHadCandidate"+suffix,-9.);
}


void ttHVarProcessor::InitMCVars(VariableContainer& vars){
  
  vars.InitVar("Dr_TopHad_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Dr_TopLep_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Dr_Higgs_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Dr_TopLep_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Dr_TopHad_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Dr_Higgs_TopHadCandidate"+suffix,-9.);
  vars.InitVar("Dr_TopLep_TopLepCandidate"+suffix,-9.);
  vars.InitVar("Dr_TopHad_TopLepCandidate"+suffix,-9.);
  vars.InitVar("Dr_Higgs_TopLepCandidate"+suffix,-9.);
  vars.InitVar("Dr_B_TopHad_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Dr_B_TopLep_HiggsCandidate"+suffix,-9.);
  vars.InitVar("Dr_W1"+suffix,-9.);
  vars.InitVar("Dr_W2"+suffix,-9.);
  vars.InitVar("Dr_Bhad"+suffix,-9.);
  vars.InitVar("Dr_B1"+suffix,-9.);
  vars.InitVar("Dr_B2"+suffix,-9.);
  vars.InitVar("Dr_Blep"+suffix,-9.);
  vars.InitVar("Dr_Nu"+suffix,-9.);
  vars.InitVar("Dr_Lep"+suffix,-9.);
}


void ttHVarProcessor::FillHiggsCandidateVars(VariableContainer& vars, BoostedttHEvent& ttHEvent){
  
  // Get Objects
  boosted::SubFilterJet higgsCand = ttHEvent.GetHiggsCandBoosted();
  pat::Jet higgsB1Cand = ttHEvent.GetHiggsB1Cand();
  pat::Jet higgsB2Cand = ttHEvent.GetHiggsB2Cand();
  pat::Jet higgsGCand = ttHEvent.GetHiggsGCand();
    
  math::XYZTLorentzVector higgsCandVec2 = ttHEvent.GetHiggsCandVec2();
  math::XYZTLorentzVector higgsCandVec3 = ttHEvent.GetHiggsCandVec3();
  
  math::XYZTLorentzVector lepCandVec = ttHEvent.GetLeptonVec();
  
  math::XYZTLorentzVector nu1CandVec = ttHEvent.GetNeutrino1Vec();
  math::XYZTLorentzVector nu2CandVec = ttHEvent.GetNeutrino2Vec();
  
  float higgsCandTag=-1.1;
//   higgsCandTag=higgstagger->GetHiggsTag(higgsCand, lepCandVec,ttHEvent.GetInput().selectedToptagjets,ttHEvent.GetInput().selectedJets) ;
  higgsCandTag = ttHEvent.GetHiggsTag();
  
  
  // Fill Variables
  if(higgsCand.fatjet.pt()>0){
    vars.FillVar("E_HiggsCandidate"+suffix,higgsCand.fatjet.energy());
    vars.FillVar("Pt_HiggsCandidate"+suffix,higgsCand.fatjet.pt());
    vars.FillVar("M_HiggsCandidate"+suffix,higgsCand.fatjet.mass());
    vars.FillVar("Eta_HiggsCandidate"+suffix,higgsCand.fatjet.eta());
    vars.FillVar("Phi_HiggsCandidate"+suffix,higgsCand.fatjet.phi());
    vars.FillVar("Pt_Filterjet1_HiggsCandidate"+suffix,higgsCand.filterjets[0].pt());
    vars.FillVar("Pt_Filterjet2_HiggsCandidate"+suffix,higgsCand.filterjets[1].pt());
  }
  
  if(higgsB1Cand.pt()>0){
    vars.FillVar("E_B1_HiggsCandidate"+suffix,higgsB1Cand.energy());
    vars.FillVar("Pt_B1_HiggsCandidate"+suffix,higgsB1Cand.pt());
    vars.FillVar("M_B1_HiggsCandidate"+suffix,higgsB1Cand.mass());
    vars.FillVar("Eta_B1_HiggsCandidate"+suffix,higgsB1Cand.eta());
    vars.FillVar("Phi_B1_HiggsCandidate"+suffix,higgsB1Cand.phi());
    vars.FillVar("CSV_B1_HiggsCandidate"+suffix,fmax(higgsB1Cand.bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags"),-.1));
  }
  
  if(higgsB2Cand.pt()>0){
    vars.FillVar("E_B2_HiggsCandidate"+suffix,higgsB2Cand.energy());
    vars.FillVar("Pt_B2_HiggsCandidate"+suffix,higgsB2Cand.pt());
    vars.FillVar("M_B2_HiggsCandidate"+suffix,higgsB2Cand.mass());
    vars.FillVar("Eta_B2_HiggsCandidate"+suffix,higgsB2Cand.eta());
    vars.FillVar("Phi_B2_HiggsCandidate"+suffix,higgsB2Cand.phi());
    vars.FillVar("CSV_B2_HiggsCandidate"+suffix,fmax(higgsB2Cand.bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags"),-.1));
  }
  
  if(higgsGCand.pt()>0){
    vars.FillVar("E_G_HiggsCandidate"+suffix,higgsGCand.energy());
    vars.FillVar("Pt_G_HiggsCandidate"+suffix,higgsGCand.pt());
    vars.FillVar("M_G_HiggsCandidate"+suffix,higgsGCand.mass());
    vars.FillVar("Eta_G_HiggsCandidate"+suffix,higgsGCand.eta());
    vars.FillVar("Phi_G_HiggsCandidate"+suffix,higgsGCand.phi());
    vars.FillVar("CSV_G_HiggsCandidate"+suffix,fmax(higgsGCand.bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags"),-.1));
  }
  
  if(higgsCandVec2.Pt()>0){
    vars.FillVar("E2_HiggsCandidate"+suffix,higgsCandVec2.E());
    vars.FillVar("Pt2_HiggsCandidate"+suffix,higgsCandVec2.Pt());
    vars.FillVar("M2_HiggsCandidate"+suffix,higgsCandVec2.M());
    vars.FillVar("Eta2_HiggsCandidate"+suffix,higgsCandVec2.Eta());
    vars.FillVar("Phi2_HiggsCandidate"+suffix,higgsCandVec2.Phi());
  }
  
  if(higgsCandVec3.Pt()>0){
    vars.FillVar("E3_HiggsCandidate"+suffix,higgsCandVec3.E());
    vars.FillVar("Pt3_HiggsCandidate"+suffix,higgsCandVec3.Pt());
    vars.FillVar("M3_HiggsCandidate"+suffix,higgsCandVec3.M());
    vars.FillVar("Eta3_HiggsCandidate"+suffix,higgsCandVec3.Eta());
    vars.FillVar("Phi3_HiggsCandidate"+suffix,higgsCandVec3.Phi());
  }
  
  vars.FillVar("CosThetaStar_Filterjet12_HiggsCandidate"+suffix,BoostedUtils::CosThetaStar(higgsB1Cand.p4(),higgsB2Cand.p4()));
  vars.FillVar("CosThetaStar_Filterjet13_HiggsCandidate"+suffix,BoostedUtils::CosThetaStar(higgsB1Cand.p4(),higgsGCand.p4()));
  vars.FillVar("CosThetaStar_Filterjet23_HiggsCandidate"+suffix,BoostedUtils::CosThetaStar(higgsB2Cand.p4(),higgsGCand.p4()));
  
  if(higgsCand.fatjet.pt()>0){
    vars.FillVar("Subjetiness1_HiggsCandidate"+suffix,higgsCand.subjettiness1);
    vars.FillVar("Subjetiness2_HiggsCandidate"+suffix,higgsCand.subjettiness2);
    vars.FillVar("Subjetiness3_HiggsCandidate"+suffix,higgsCand.subjettiness3);
  }
  
  if(higgsCand.fatjet.pt()>0&&lepCandVec.Pt()>0)
    vars.FillVar("Dr_Lepton_HiggsCandidate"+suffix,BoostedUtils::DeltaR(lepCandVec,higgsCand.fatjet.p4()));
  
  float mblep= -999;
  float mtoplep_higgs1=-999;
  float mtoplep_higgs2=-999;
  float mtoplep_higgs3=-999;
  float mtoplep_higgs4=-999;
  if(higgsB1Cand.pt()>0){
    mtoplep_higgs1=(nu1CandVec+lepCandVec+higgsB1Cand.p4()).M();
    mtoplep_higgs2=(nu2CandVec+lepCandVec+higgsB1Cand.p4()).M();
    mblep=(lepCandVec+higgsB1Cand.p4()).M();
  }
  if(higgsB2Cand.pt()>0){
    mtoplep_higgs3=(nu1CandVec+lepCandVec+higgsB2Cand.p4()).M();
    mtoplep_higgs4=(nu2CandVec+lepCandVec+higgsB2Cand.p4()).M();
    mblep=fmin((lepCandVec+higgsB1Cand.p4()).M(),(lepCandVec+higgsB2Cand.p4()).M());
  }
  
  vars.FillVar("M_Lepton_B_HiggsCandidate"+suffix, mblep);
  if(fabs(mtoplep_higgs1-173)<fabs(mtoplep_higgs2-173)&&fabs(mtoplep_higgs1-173)<fabs(mtoplep_higgs3-173)&&fabs(mtoplep_higgs1-173)<fabs(mtoplep_higgs4-173))   
    vars.FillVar("M_TopLep_HiggsCandidate"+suffix,mtoplep_higgs1);
  else if(fabs(mtoplep_higgs2-173)<fabs(mtoplep_higgs1-173)&&fabs(mtoplep_higgs2-173)<fabs(mtoplep_higgs3-173)&&fabs(mtoplep_higgs2-173)<fabs(mtoplep_higgs4-173))
    vars.FillVar("M_TopLep_HiggsCandidate"+suffix,mtoplep_higgs2);
  else if(fabs(mtoplep_higgs3-173)<fabs(mtoplep_higgs1-173)&&fabs(mtoplep_higgs3-173)<fabs(mtoplep_higgs2-173)&&fabs(mtoplep_higgs3-173)<fabs(mtoplep_higgs4-173))
    vars.FillVar("M_TopLep_HiggsCandidate"+suffix,mtoplep_higgs3);
  else if(fabs(mtoplep_higgs4-173)<fabs(mtoplep_higgs1-173)&&fabs(mtoplep_higgs4-173)<fabs(mtoplep_higgs2-173)&&fabs(mtoplep_higgs4-173)<fabs(mtoplep_higgs3-173))
    vars.FillVar("M_TopLep_HiggsCandidate"+suffix,mtoplep_higgs4);
  
  vars.FillVar("HiggsTag_HiggsCandidate_"+suffix,higgsCandTag);
}


void ttHVarProcessor::FillTopHadCandidateVars(VariableContainer& vars, BoostedttHEvent& ttHEvent){
  
  // Get Objects
  boosted::HEPTopJet topHadCand = ttHEvent.GetTopHadCandBoosted();
  pat::Jet topHadBCand = ttHEvent.GetTopHadBCand();
  pat::Jet topHadW1Cand = ttHEvent.GetTopHadW1Cand();
  pat::Jet topHadW2Cand = ttHEvent.GetTopHadW2Cand();
  
  math::XYZTLorentzVector topHadCandVec = ttHEvent.GetTopHadCandVec();
  math::XYZTLorentzVector wHadCandVec = ttHEvent.GetWHadCandVec();
  math::XYZTLorentzVector bW1CandVec = topHadBCand.p4()+topHadW1Cand.p4();
  math::XYZTLorentzVector bW2CandVec = topHadBCand.p4()+topHadW2Cand.p4();
  
  math::XYZTLorentzVector lepCandVec = ttHEvent.GetLeptonVec();
  
  math::XYZTLorentzVector nu1CandVec = ttHEvent.GetNeutrino1Vec();
  math::XYZTLorentzVector nu2CandVec = ttHEvent.GetNeutrino2Vec();
  
  // Fill Variables
  vars.FillVar("Tagged_TopHadCandidate"+suffix,BoostedUtils::GetTopTag(topHadCand));
  vars.FillVar("TaggedB_TopHadCandidate"+suffix,BoostedUtils::GetTopTag(topHadCand,0.15,120.,true));
  vars.FillVar("TopMVAOutput_TopHadCandidate"+suffix, toptagger.GetTopTag(topHadCand));

  vars.FillVar("E_TopHadCandidate"+suffix,topHadCand.fatjet.energy());
  vars.FillVar("Pt_TopHadCandidate"+suffix,topHadCand.fatjet.pt());
  vars.FillVar("M_TopHadCandidate"+suffix,topHadCand.fatjet.mass());
  vars.FillVar("Eta_TopHadCandidate"+suffix,topHadCand.fatjet.eta());
  vars.FillVar("Phi_TopHadCandidate"+suffix,topHadCand.fatjet.phi());
  
  vars.FillVar("E_B_TopHadCandidate"+suffix,topHadBCand.energy());
  vars.FillVar("Pt_B_TopHadCandidate"+suffix,topHadBCand.pt());
  vars.FillVar("M_B_TopHadCandidate"+suffix,topHadBCand.mass());
  vars.FillVar("Eta_B_TopHadCandidate"+suffix,topHadBCand.eta());
  vars.FillVar("Phi_B_TopHadCandidate"+suffix,topHadBCand.phi());
  vars.FillVar("CSV_B_TopHadCandidate"+suffix,fmax(topHadBCand.bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags"),-.1));

  vars.FillVar("E_W1_TopHadCandidate"+suffix,topHadW1Cand.energy());
  vars.FillVar("Pt_W1_TopHadCandidate"+suffix,topHadW1Cand.pt());
  vars.FillVar("M_W1_TopHadCandidate"+suffix,topHadW1Cand.mass());
  vars.FillVar("Eta_W1_TopHadCandidate"+suffix,topHadW1Cand.eta());
  vars.FillVar("Phi_W1_TopHadCandidate"+suffix,topHadW1Cand.phi());
  vars.FillVar("CSV_W1_TopHadCandidate"+suffix,fmax(topHadW1Cand.bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags"),-.1));

  vars.FillVar("E_W2_TopHadCandidate"+suffix,topHadW2Cand.energy());
  vars.FillVar("Pt_W2_TopHadCandidate"+suffix,topHadW2Cand.pt());
  vars.FillVar("M_W2_TopHadCandidate"+suffix,topHadW2Cand.mass());
  vars.FillVar("Eta_W2_TopHadCandidate"+suffix,topHadW2Cand.eta());
  vars.FillVar("Phi_W2_TopHadCandidate"+suffix,topHadW2Cand.phi());
  vars.FillVar("CSV_W2_TopHadCandidate"+suffix,fmax(topHadW2Cand.bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags"),-.1));
  
  if(wHadCandVec.Pt()>0.001){
    vars.FillVar("E_W_TopHadCandidate"+suffix,wHadCandVec.E());
    vars.FillVar("Pt_W_TopHadCandidate"+suffix,wHadCandVec.Pt());
    vars.FillVar("M_W_TopHadCandidate"+suffix,wHadCandVec.M());
    vars.FillVar("Eta_W_TopHadCandidate"+suffix,wHadCandVec.Eta());
    vars.FillVar("Phi_W_TopHadCandidate"+suffix,wHadCandVec.Phi());
  }
  
  if(bW1CandVec.Pt()>0.001){
    vars.FillVar("E_BW1_TopHadCandidate"+suffix,bW1CandVec.E());
    vars.FillVar("Pt_BW1_TopHadCandidate"+suffix,bW1CandVec.Pt());
    vars.FillVar("M_BW1_TopHadCandidate"+suffix,bW1CandVec.M());
    vars.FillVar("Eta_BW1_TopHadCandidate"+suffix,bW1CandVec.Eta());
    vars.FillVar("Phi_BW1_TopHadCandidate"+suffix,bW1CandVec.Phi());
  }

  if(bW2CandVec.Pt()>0.001){
    vars.FillVar("E_BW2_TopHadCandidate"+suffix,bW2CandVec.E());
    vars.FillVar("Pt_BW2_TopHadCandidate"+suffix,bW2CandVec.Pt());
    vars.FillVar("M_BW2_TopHadCandidate"+suffix,bW2CandVec.M());
    vars.FillVar("Eta_BW2_TopHadCandidate"+suffix,bW2CandVec.Eta());
    vars.FillVar("Phi_BW2_TopHadCandidate"+suffix,bW2CandVec.Phi());
  }
  
  if(topHadCandVec.Pt()>0.001){
    vars.FillVar("E_Top_TopHadCandidate"+suffix,topHadCandVec.E());
    vars.FillVar("M_Top_TopHadCandidate"+suffix,topHadCandVec.M());
    vars.FillVar("Pt_Top_TopHadCandidate"+suffix, topHadCandVec.Pt());
    vars.FillVar("Eta_Top_TopHadCandidate"+suffix,topHadCandVec.Eta());
    vars.FillVar("Phi_Top_TopHadCandidate"+suffix, topHadCandVec.Phi());
  }

  vars.FillVar("Subjettiness1_TopHadCandidate"+suffix,topHadCand.subjettiness1);
  vars.FillVar("Subjettiness2_TopHadCandidate"+suffix,topHadCand.subjettiness2);
  vars.FillVar("Subjettiness3_TopHadCandidate"+suffix,topHadCand.subjettiness3);
  
  if(topHadCandVec.Pt()>0.001 && lepCandVec.Pt()>0.001){
    vars.FillVar("Dr_Lepton_TopHadCandidate"+suffix,BoostedUtils::DeltaR(lepCandVec,topHadCandVec));
  }
  
  float mtoplep_tophad1=(nu1CandVec+lepCandVec+topHadBCand.p4()).M();
  float mtoplep_tophad2=(nu2CandVec+lepCandVec+topHadBCand.p4()).M();
  if(topHadBCand.pt()>0.001){
    vars.FillVar("M_Lepton_B_TopHadCandidate"+suffix, (lepCandVec+topHadBCand.p4()).M());
    vars.FillVar("M_TopLep_TopHadCandidate"+suffix,fabs(mtoplep_tophad1-173)<fabs(mtoplep_tophad2-173) ? mtoplep_tophad1 : mtoplep_tophad2);
  }
}


void ttHVarProcessor::FillTopLepCandidateVars(VariableContainer& vars,BoostedttHEvent& ttHEvent){
  
  // Get Objects
  pat::Jet topLepBCand = ttHEvent.GetTopLepBCand();
  
  math::XYZTLorentzVector lepCandVec = ttHEvent.GetLeptonVec();
  
  math::XYZTLorentzVector nuCandVec = ttHEvent.GetNeutrinoVec();
  
  math::XYZTLorentzVector topLepCandVec = ttHEvent.GetTopLepCandVec();
  math::XYZTLorentzVector wLepCandVec = ttHEvent.GetWLepCandVec();
  
  // Fill Variables
  if(topLepCandVec.Pt()>0.001){
    vars.FillVar("E_Top_TopLepCandidate"+suffix,topLepCandVec.E());
    vars.FillVar("Pt_Top_TopLepCandidate"+suffix,topLepCandVec.Pt());
    vars.FillVar("M_Top_TopLepCandidate"+suffix,topLepCandVec.M());
    vars.FillVar("Eta_Top_TopLepCandidate"+suffix,topLepCandVec.Eta());
    vars.FillVar("Phi_Top_TopLepCandidate"+suffix,topLepCandVec.Phi());
  }
  
  if(wLepCandVec.Pt()>0.001){
    vars.FillVar("E_W_TopLepCandidate"+suffix,wLepCandVec.E());
    vars.FillVar("Pt_W_TopLepCandidate"+suffix,wLepCandVec.Pt());
    vars.FillVar("M_W_TopLepCandidate"+suffix,wLepCandVec.M());
    vars.FillVar("Eta_W_TopLepCandidate"+suffix,wLepCandVec.Eta());
    vars.FillVar("Phi_W_TopLepCandidate"+suffix,wLepCandVec.Phi());
  }
  
  if(topLepBCand.pt()>0.001){
    vars.FillVar("E_B_TopLepCandidate"+suffix,topLepBCand.energy());
    vars.FillVar("Pt_B_TopLepCandidate"+suffix,topLepBCand.pt());
    vars.FillVar("M_B_TopLepCandidate"+suffix,topLepBCand.mass());
    vars.FillVar("Eta_B_TopLepCandidate"+suffix,topLepBCand.eta());
    vars.FillVar("Phi_B_TopLepCandidate"+suffix,topLepBCand.phi());
    vars.FillVar("CSV_B_TopLepCandidate"+suffix,fmax(topLepBCand.bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags"),-.1));
  }
  
  if(lepCandVec.Pt()>0.001){
    vars.FillVar("E_Lep_TopLepCandidate"+suffix,lepCandVec.E());
    vars.FillVar("Pt_Lep_TopLepCandidate"+suffix,lepCandVec.Pt());
    vars.FillVar("M_Lep_TopLepCandidate"+suffix,lepCandVec.M());
    vars.FillVar("Eta_Lep_TopLepCandidate"+suffix,lepCandVec.Eta());
    vars.FillVar("Phi_Lep_TopLepCandidate"+suffix,lepCandVec.Phi()); 
  }
  
  if(nuCandVec.Pt()>0.001){
    vars.FillVar("E_Nu_TopLepCandidate"+suffix,nuCandVec.E());
    vars.FillVar("Pt_Nu_TopLepCandidate"+suffix,nuCandVec.Pt());
    vars.FillVar("M_Nu_TopLepCandidate"+suffix,nuCandVec.M());
    vars.FillVar("Eta_Nu_TopLepCandidate"+suffix,nuCandVec.Eta());
    vars.FillVar("Phi_Nu_TopLepCandidate"+suffix,nuCandVec.Phi()); 
  }
}


void ttHVarProcessor::FillAk5JetsVars(VariableContainer& vars,BoostedttHEvent& ttHEvent){
  
  // Fill Variables
  vars.FillVar("N_Jets_ak5Jets"+suffix,ttHEvent.GetNJets());
  vars.FillVar("N_BTagsL_ak5Jets"+suffix,ttHEvent.GetNBTagL());
  vars.FillVar("N_BTagsM_ak5Jets"+suffix,ttHEvent.GetNBTagM());
  vars.FillVar("N_BTagsT_ak5Jets"+suffix,ttHEvent.GetNBTagT());
  vars.FillVar("AvgCSV_ak5Jets"+suffix,ttHEvent.GetAverageCSV());
  
  vars.FillVar("N_Jets_Higgs_ak5Jets"+suffix,ttHEvent.GetNHiggsak5Jets());
  vars.FillVar("N_BTagsL_Higgs_ak5Jets"+suffix,ttHEvent.GetNHiggsCandBTagL());
  vars.FillVar("N_BTagsM_Higgs_ak5Jets"+suffix,ttHEvent.GetNHiggsCandBTagM());
  vars.FillVar("N_BTagsT_Higgs_ak5Jets"+suffix,ttHEvent.GetNHiggsCandBTagT());
  vars.FillVar("AvgCSV_Higgs_ak5Jets"+suffix,ttHEvent.GetAverageCSVHiggsCand());
  
  vars.FillVar("N_Jets_TopHad_ak5Jets"+suffix,ttHEvent.GetNTopHadak5Jets());
  vars.FillVar("N_BTagsL_TopHad_ak5Jets"+suffix,ttHEvent.GetNTopHadCandBTagL());
  vars.FillVar("N_BTagsM_TopHad_ak5Jets"+suffix,ttHEvent.GetNTopHadCandBTagM());
  vars.FillVar("N_BTagsT_TopHad_ak5Jets"+suffix,ttHEvent.GetNTopHadCandBTagT());
  vars.FillVar("AvgCSV_TopHad_ak5Jets"+suffix,ttHEvent.GetAverageCSVTopHadCand());
  
  vars.FillVar("N_Jets_TopLep_ak5Jets"+suffix,ttHEvent.GetNTopLepak5Jets());
  vars.FillVar("N_BTagsL_TopLep_ak5Jets"+suffix,ttHEvent.GetNTopLepCandBTagL());
  vars.FillVar("N_BTagsM_TopLep_ak5Jets"+suffix,ttHEvent.GetNTopLepCandBTagM());
  vars.FillVar("N_BTagsT_TopLep_ak5Jets"+suffix,ttHEvent.GetNTopLepCandBTagT());
  vars.FillVar("AvgCSV_TopLep_ak5Jets"+suffix,ttHEvent.GetAverageCSVTopLepCand());
  
  vars.FillVar("N_Jets_Clean_ak5Jets"+suffix,ttHEvent.GetNCleanedak5Jets());
  vars.FillVar("N_BTagsL_Clean_ak5Jets"+suffix,ttHEvent.GetNCleanedBTagL());
  vars.FillVar("N_BTagsM_Clean_ak5Jets"+suffix,ttHEvent.GetNCleanedBTagM());
  vars.FillVar("N_BTagsT_Clean_ak5Jets"+suffix,ttHEvent.GetNCleanedBTagT());
  vars.FillVar("AvgCSV_Clean_ak5Jets"+suffix,ttHEvent.GetAverageCSVClean());
}


void ttHVarProcessor::FillCombinationVars(VariableContainer& vars,BoostedttHEvent& ttHEvent){
  
  // Get Objects
  // Higgs Candidate
  math::XYZTLorentzVector higgsCandVec2 = ttHEvent.GetHiggsCandVec2();
  
  // Hadronic Top Candidate
  math::XYZTLorentzVector topHadCandVec = ttHEvent.GetTopHadCandVec();
  
  // Leptonic Top Candidate
  math::XYZTLorentzVector topLepCandVec = ttHEvent.GetTopLepCandVec();
  
  // Fill Variables
  if(higgsCandVec2.Pt()>0.001 && topHadCandVec.Pt()>0.001){
    vars.FillVar("Dr_TopHadCandidate_HiggsCandidate"+suffix,BoostedUtils::DeltaR(topHadCandVec,higgsCandVec2));
    vars.FillVar("Dphi_TopHadCandidate_HiggsCandidate"+suffix,BoostedUtils::DeltaPhi(topHadCandVec,higgsCandVec2));
    vars.FillVar("Deta_TopHadCandidate_HiggsCandidate"+suffix,BoostedUtils::DeltaEta(topHadCandVec,higgsCandVec2));
  }
  
  if(higgsCandVec2.Pt()>0.001 && topLepCandVec.Pt()>0.001){
    vars.FillVar("Dr_TopLepCandidate_HiggsCandidate"+suffix,BoostedUtils::DeltaR(topLepCandVec,higgsCandVec2));
    vars.FillVar("Dphi_TopLepCandidate_HiggsCandidate"+suffix,BoostedUtils::DeltaPhi(topLepCandVec,higgsCandVec2));
    vars.FillVar("Deta_TopLepCandidate_HiggsCandidate"+suffix,BoostedUtils::DeltaEta(topLepCandVec,higgsCandVec2));
  }
  
  if(topHadCandVec.Pt()>0.001 && topLepCandVec.Pt()>0.001){
    vars.FillVar("Dr_TopLepCandidate_TopHadCandidate"+suffix,BoostedUtils::DeltaR(topLepCandVec,topHadCandVec));
    vars.FillVar("Dphi_TopLepCandidate_TopHadCandidate"+suffix,BoostedUtils::DeltaPhi(topLepCandVec,topHadCandVec));
    vars.FillVar("Deta_TopLepCandidate_TopHadCandidate"+suffix,BoostedUtils::DeltaEta(topLepCandVec,topHadCandVec));
  }
}


void ttHVarProcessor::FillMCVars(VariableContainer& vars,BoostedttHEvent& ttHEvent){
  
  // Get Objects
  
  // MC Objects 
  vector<math::XYZTLorentzVector> bhad_mc;
  vector<math::XYZTLorentzVector> q1_mc;
  vector<math::XYZTLorentzVector> q2_mc;
  vector<math::XYZTLorentzVector> blep_mc;
  vector<math::XYZTLorentzVector> lep_mc;
  vector<math::XYZTLorentzVector> nu_mc;
  math::XYZTLorentzVector b1_mc;
  math::XYZTLorentzVector b2_mc;
  
  BoostedUtils::GetttHMCVecs(ttHEvent.GetInput().genParticles,bhad_mc,q1_mc,q2_mc,blep_mc,lep_mc,nu_mc,b1_mc,b2_mc);
 
  // Higgs Candidate
  math::XYZTLorentzVector higgsCandVec2 = ttHEvent.GetHiggsCandVec2();
  pat::Jet higgsB1Cand = ttHEvent.GetHiggsB1Cand();
  pat::Jet higgsB2Cand = ttHEvent.GetHiggsB2Cand();
  
  // Hadronic Top Candidate
  math::XYZTLorentzVector topHadCandVec = ttHEvent.GetTopHadCandVec();
  pat::Jet topHadBCand = ttHEvent.GetTopHadBCand();
  pat::Jet topHadW1Cand = ttHEvent.GetTopHadW1Cand();
  pat::Jet topHadW2Cand = ttHEvent.GetTopHadW2Cand();
  
  // Leptonic Top Candidate
  math::XYZTLorentzVector topLepCandVec = ttHEvent.GetTopLepCandVec();
  pat::Jet topLepBCand = ttHEvent.GetTopLepBCand();
  math::XYZTLorentzVector lepCandVec = ttHEvent.GetLeptonVec();
  math::XYZTLorentzVector nuCandVec = ttHEvent.GetNeutrinoVec();
  
  vector<math::XYZTLorentzVector>  tophad_mc;
  for(size_t i=0;i<bhad_mc.size();i++) tophad_mc.push_back(bhad_mc[i]+q1_mc[i]+q2_mc[i]);
  vector<math::XYZTLorentzVector>  toplep_mc;
  for(size_t i=0;i<blep_mc.size();i++) toplep_mc.push_back(blep_mc[i]+lep_mc[i]+nu_mc[i]);
  math::XYZTLorentzVector          higgs_mc=b1_mc+b2_mc;
 
  if(higgsCandVec2.Pt()>0.001){
    if(higgs_mc.Pt()>0.001)
            vars.FillVar("Dr_Higgs_HiggsCandidate"+suffix,BoostedUtils::DeltaR(higgs_mc,higgsCandVec2));
    
    if(tophad_mc.size()==1){
      vars.FillVar("Dr_B_TopHad_HiggsCandidate"+suffix,BoostedUtils::DeltaR(bhad_mc[0],higgsCandVec2));
      vars.FillVar("Dr_TopHad_HiggsCandidate"+suffix,BoostedUtils::DeltaR(tophad_mc[0],higgsCandVec2));
    }
    else if(tophad_mc.size()==2){
      vars.FillVar("Dr_B_TopHad_HiggsCandidate"+suffix, fmin(BoostedUtils::DeltaR(bhad_mc[0],higgsCandVec2),BoostedUtils::DeltaR(bhad_mc[1],higgsCandVec2)));
      vars.FillVar("Dr_TopHad_HiggsCandidate"+suffix,fmin(BoostedUtils::DeltaR(tophad_mc[0],higgsCandVec2),BoostedUtils::DeltaR(tophad_mc[1],higgsCandVec2)));
    }
   
    if(toplep_mc.size()==1){
      vars.FillVar("Dr_B_TopLep_HiggsCandidate"+suffix,BoostedUtils::DeltaR(blep_mc[0],higgsCandVec2));
      vars.FillVar("Dr_TopLep_HiggsCandidate"+suffix,BoostedUtils::DeltaR(toplep_mc[0],higgsCandVec2));
    }
    else if(toplep_mc.size()==2){
      vars.FillVar("Dr_B_TopLep_HiggsCandidate"+suffix, fmin(BoostedUtils::DeltaR(blep_mc[0],higgsCandVec2),BoostedUtils::DeltaR(blep_mc[1],higgsCandVec2)));
      vars.FillVar("Dr_TopLep_HiggsCandidate"+suffix,fmin(BoostedUtils::DeltaR(toplep_mc[0],higgsCandVec2),BoostedUtils::DeltaR(toplep_mc[1],higgsCandVec2)));
    }
  }
   
  if(topHadCandVec.Pt()>0.001){
    if(higgs_mc.Pt()>0.001)
      vars.FillVar("Dr_Higgs_TopHadCandidate"+suffix,BoostedUtils::DeltaR(higgs_mc,topHadCandVec));
   
    if(tophad_mc.size()==1)
      vars.FillVar("Dr_TopHad_TopHadCandidate"+suffix,BoostedUtils::DeltaR(tophad_mc[0],topHadCandVec));
    else if (tophad_mc.size()==2)
       vars.FillVar("Dr_TopHad_TopHadCandidate"+suffix,fmin(BoostedUtils::DeltaR(tophad_mc[0],topHadCandVec),BoostedUtils::DeltaR(tophad_mc[1],topHadCandVec)));
     
    if(toplep_mc.size()==1)
      vars.FillVar("Dr_TopLep_TopHadCandidate"+suffix,BoostedUtils::DeltaR(toplep_mc[0],topHadCandVec));
    else if (toplep_mc.size()==2)
       vars.FillVar("Dr_TopLep_TopHadCandidate"+suffix,fmin(BoostedUtils::DeltaR(toplep_mc[0],topHadCandVec),BoostedUtils::DeltaR(toplep_mc[1],topHadCandVec)));
  }
 
  if(topLepCandVec.Pt()>0.001){
    if(higgs_mc.Pt()>0.001)
            vars.FillVar("Dr_Higgs_TopLepCandidate"+suffix,BoostedUtils::DeltaR(higgs_mc,topLepCandVec));
    
    if(tophad_mc.size()==1)
      vars.FillVar("Dr_TopHad_TopLepCandidate"+suffix,BoostedUtils::DeltaR(tophad_mc[0],topLepCandVec));
    else if (tophad_mc.size()==2)
      vars.FillVar("Dr_TopHad_TopLepCandidate"+suffix,fmin(BoostedUtils::DeltaR(tophad_mc[0],topLepCandVec),BoostedUtils::DeltaR(tophad_mc[1],topLepCandVec)));
    
    if(toplep_mc.size()==1)
      vars.FillVar("Dr_TopLep_TopLepCandidate"+suffix,BoostedUtils::DeltaR(toplep_mc[0],topLepCandVec));
    else if (toplep_mc.size()==2)
      vars.FillVar("Dr_TopLep_TopLepCandidate"+suffix,fmin(BoostedUtils::DeltaR(toplep_mc[0],topLepCandVec),BoostedUtils::DeltaR(toplep_mc[1],topLepCandVec)));
  }

  float drw11 = 9;
  float drw22 = 9;
  float drw21 = 9;
  float drw12 = 9;
 
  int topHadMCID = -1;
  if(tophad_mc.size()>0) topHadMCID = 0;
  if(tophad_mc.size()>1 && topHadCandVec.Pt()>0.001 && BoostedUtils::DeltaR(tophad_mc[1],topHadCandVec)<BoostedUtils::DeltaR(tophad_mc[0],topHadCandVec)) topHadMCID = 1;
 
  if(tophad_mc.size()>0 && topHadW1Cand.pt()>0.001 && topHadW2Cand.pt()>0.001){
    drw11 = BoostedUtils::DeltaR(q1_mc[topHadMCID],topHadW1Cand.p4());
    drw22 = BoostedUtils::DeltaR(q2_mc[topHadMCID],topHadW2Cand.p4());
    drw21 = BoostedUtils::DeltaR(q2_mc[topHadMCID],topHadW1Cand.p4());
    drw12 = BoostedUtils::DeltaR(q1_mc[topHadMCID],topHadW2Cand.p4());
  }
  
  float drw1 = 9;
  float drw2 = 9;
  
  if(drw11<drw22&&drw11<drw21&&drw11<drw12){
    drw1=drw11;
    drw2=drw22;
  }
  if(drw22<drw11&&drw22<drw21&&drw22<drw12){
    drw1=drw11;
    drw2=drw22;
  }
  if(drw21<drw22&&drw21<drw11&&drw21<drw12){
    drw1=drw21;
    drw2=drw12;
  }
  if(drw12<drw22&&drw12<drw21&&drw12<drw11){
    drw1=drw21;
    drw2=drw12;
  }
  
  vars.FillVar("Dr_W1"+suffix,drw1 );
  vars.FillVar("Dr_W2"+suffix,drw2 );
  
  if(topHadMCID>=0) vars.FillVar("Dr_Bhad"+suffix,BoostedUtils::DeltaR(bhad_mc[topHadMCID],topHadBCand.p4())); 
  
  float drb11 = 9;
  float drb22 = 9;
  float drb21 = 9;
  float drb12 = 9;
  if(higgs_mc.Pt()>0.001 && higgsB1Cand.pt()>0.001 && higgsB2Cand.pt()>0.001){
    drb11 = BoostedUtils::DeltaR(b1_mc,higgsB1Cand.p4());
    drb22 = BoostedUtils::DeltaR(b2_mc,higgsB2Cand.p4());
    drb21 = BoostedUtils::DeltaR(b2_mc,higgsB1Cand.p4());
    drb12 = BoostedUtils::DeltaR(b1_mc,higgsB2Cand.p4());
  }
  
  float drb1 = 9;
  float drb2 = 9;
  if(drb11<drb22&&drb11<drb21&&drb11<drb12){
    drb1=drb11;
    drb2=drb22;
  }
  if(drb22<drb11&&drb22<drb21&&drb22<drb12){
    drb1=drb11;
    drb2=drb22;   
  }
  if(drb21<drb22&&drb21<drb11&&drb21<drb12){
    drb1=drb21;
    drb2=drb12;
  }
  if(drb12<drb22&&drb12<drb21&&drb12<drb11){
    drb1=drb21;
    drb2=drb12;
  } 
  
  vars.FillVar("Dr_B1"+suffix,drb1 );
  vars.FillVar("Dr_B2"+suffix,drb2 );
 
  int topLepMCID = 0;
  if(toplep_mc.size()>1 && topLepCandVec.Pt()>0.001 && BoostedUtils::DeltaR(toplep_mc[1],topLepCandVec)<BoostedUtils::DeltaR(toplep_mc[0],topLepCandVec)) topLepMCID = 1;
 
  if(toplep_mc.size()>0){
    if(topLepBCand.pt()>0.001) vars.FillVar("Dr_Blep"+suffix,BoostedUtils::DeltaR(blep_mc[topLepMCID],topLepBCand.p4()));
    if(nuCandVec.Pt()>0.001) vars.FillVar("Dr_Nu"+suffix,BoostedUtils::DeltaR(nu_mc[topLepMCID],nuCandVec));
    if(lepCandVec.Pt()>0.001) vars.FillVar("Dr_Lep"+suffix,BoostedUtils::DeltaR(lep_mc[topLepMCID],lepCandVec));
  }
}
