#include "BoostedTTH/BoostedAnalyzer/interface/ttHVarProcessor.hpp"

using namespace std;

ttHVarProcessor::ttHVarProcessor(BoostedRecoType recotype_, std::string taggername_, std::string higgstaggername_, std::string prefix_):btagger("combinedInclusiveSecondaryVertexV2BJetTags"){
  recotype = recotype_;
  prefix = prefix_;

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
  FillMCVars(vars,ttHEvent,input);
}


void ttHVarProcessor::InitTopTagger(string taggername){
 
  if(taggername!=""){
    if(taggername.find("TopLikelihood")!=std::string::npos) toptagger = TopTagger(taggername);
    else if(taggername.find("BDTTopTagger")!=std::string::npos){

      vector<string> BDTVars;
      string weights;

      if(taggername == "BDTTopTagger_PSO"){
        BDTVars.push_back("TopJet_Wbtag_M");
        BDTVars.push_back("TopJet_BW1btag_M");
        BDTVars.push_back("TopJet_BW2btag_M");
        BDTVars.push_back("TopJet_PrunedMass");
        BDTVars.push_back("TopJet_UnfilteredMass");
        BDTVars.push_back("TopJet_DRoptRoptCalc");
        BDTVars.push_back("TopJet_Tau21Filtered");
        BDTVars.push_back("TopJet_Tau32Filtered");
        BDTVars.push_back("TopJet_Bbtag_CSV");
        BDTVars.push_back("TopJet_W1btag_CSV");
        BDTVars.push_back("TopJet_MRatio_Wbtag_Top");
        BDTVars.push_back("TopJet_W2btag_CSV");
        BDTVars.push_back("TopJet_Top_M");
        BDTVars.push_back("TopJet_fRec");
        
        weights = "BDTTopTagger_PSO.weights.xml";
      }

      toptagger = TopTagger(taggername,BDTVars,weights); 
    }
  } 
}


void ttHVarProcessor::InitHiggsTagger(string higgstaggerName){
  
  if(higgstaggerName.find("HiggsLikelihood")!=std::string::npos || higgstaggerName.find("HiggsBDT")!=std::string::npos){
    std::vector<std::string> HBDTVars;
    HBDTVars.push_back("HiggsJet_Pt");
    HBDTVars.push_back("HiggsJet_Dr_Lep");
    HBDTVars.push_back("HiggsJet_M2");
    HBDTVars.push_back("HiggsJet_M3");
    HBDTVars.push_back("HiggsJet_Dr_TopJet1");
    HBDTVars.push_back("HiggsJet_Dr_TopJet2");
    HBDTVars.push_back("HiggsJet_CSV1");
    HBDTVars.push_back("HiggsJet_CSV2");
    HBDTVars.push_back("HiggsJet_NSubjettiness_13_Ratio");
    HBDTVars.push_back("HiggsJet_M3_SingleTag");
    HBDTVars.push_back("HiggsJet_Filterjet2_IdxAk5");
    HBDTVars.push_back("HiggsJet_Filterjet2_CSV");

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
  
  vars.InitVar(prefix+"HiggsCandidate_HiggsTag",-9.);
  vars.InitVar(prefix+"HiggsCandidate_E",-9.);
  vars.InitVar(prefix+"HiggsCandidate_Pt",-9.);
  vars.InitVar(prefix+"HiggsCandidate_M",-9.);
  vars.InitVar(prefix+"HiggsCandidate_Eta",-9.);
  vars.InitVar(prefix+"HiggsCandidate_Phi",-9.);
  vars.InitVar(prefix+"HiggsCandidate_Filterjet2_Pt",-9.);
  vars.InitVar(prefix+"HiggsCandidate_Filterjet1_Pt",-9.);
  
  vars.InitVar(prefix+"HiggsCandidate_B1_E",-9.);
  vars.InitVar(prefix+"HiggsCandidate_B2_E",-9.);
  vars.InitVar(prefix+"HiggsCandidate_G_E",-9.);
  vars.InitVar(prefix+"HiggsCandidate_B1_Pt",-9.);
  vars.InitVar(prefix+"HiggsCandidate_B2_Pt",-9.);
  vars.InitVar(prefix+"HiggsCandidate_G_Pt",-9.);
  vars.InitVar(prefix+"HiggsCandidate_B1_M",-9.);
  vars.InitVar(prefix+"HiggsCandidate_B2_M",-9.);
  vars.InitVar(prefix+"HiggsCandidate_G_M",-9.);
  vars.InitVar(prefix+"HiggsCandidate_B1_Eta",-9.);
  vars.InitVar(prefix+"HiggsCandidate_B2_Eta",-9.);
  vars.InitVar(prefix+"HiggsCandidate_G_Eta",-9.);
  vars.InitVar(prefix+"HiggsCandidate_B1_Phi",-9.);
  vars.InitVar(prefix+"HiggsCandidate_B2_Phi",-9.);
  vars.InitVar(prefix+"HiggsCandidate_G_Phi",-9.);
  vars.InitVar(prefix+"HiggsCandidate_B1_CSV",-.1);
  vars.InitVar(prefix+"HiggsCandidate_B2_CSV",-.1);
  vars.InitVar(prefix+"HiggsCandidate_G_CSV",-.1);
  
  vars.InitVar(prefix+"HiggsCandidate_E2",-9.);
  vars.InitVar(prefix+"HiggsCandidate_Pt2",-9.);
  vars.InitVar(prefix+"HiggsCandidate_M2",-9.);
  vars.InitVar(prefix+"HiggsCandidate_Eta2",-9.);
  vars.InitVar(prefix+"HiggsCandidate_Phi2",-9.);
  vars.InitVar(prefix+"HiggsCandidate_E3",-9.);
  vars.InitVar(prefix+"HiggsCandidate_Pt3",-9.);
  vars.InitVar(prefix+"HiggsCandidate_M3",-9.);
  vars.InitVar(prefix+"HiggsCandidate_Eta3",-9.);
  vars.InitVar(prefix+"HiggsCandidate_Phi3",-9.);
  
  vars.InitVar(prefix+"HiggsCandidate_CosThetaStar_Filterjet12",-9.);
  vars.InitVar(prefix+"HiggsCandidate_CosThetaStar_Filterjet13",-9.);
  vars.InitVar(prefix+"HiggsCandidate_CosThetaStar_Filterjet23",-9.);
  
  vars.InitVar(prefix+"HiggsCandidate_Subjetiness1",-9.);
  vars.InitVar(prefix+"HiggsCandidate_Subjetiness2",-9.);
  vars.InitVar(prefix+"HiggsCandidate_Subjetiness3",-9.);
  
  vars.InitVar(prefix+"HiggsCandidate_Dr_Lepton",-9.);
  
  vars.InitVar(prefix+"HiggsCandidate_M_Lepton_B",-9.);
  vars.InitVar(prefix+"HiggsCandidate_M_TopLep",-9.);
}


void ttHVarProcessor::InitTopHadCandidateVars(VariableContainer& vars){

  vars.InitVar(prefix+"TopHadCandidate_Tagged",-9.);
  vars.InitVar(prefix+"TopHadCandidate_TaggedB",-9.);
  vars.InitVar(prefix+"TopHadCandidate_TopMVAOutput",-9.);
  vars.InitVar(prefix+"Chi2_TopHadCandidate_BoostedHiggs",-9.);
  
  vars.InitVar(prefix+"TopHadCandidate_E",-9.);
  vars.InitVar(prefix+"TopHadCandidate_Pt",-9.);
  vars.InitVar(prefix+"TopHadCandidate_M",-9.);
  vars.InitVar(prefix+"TopHadCandidate_Eta",-9.);
  vars.InitVar(prefix+"TopHadCandidate_Phi",-9.);
  
  vars.InitVar(prefix+"TopHadCandidate_B_E",-9.);
  vars.InitVar(prefix+"TopHadCandidate_B_Pt",-9.);
  vars.InitVar(prefix+"TopHadCandidate_B_M",-9.);
  vars.InitVar(prefix+"TopHadCandidate_B_Eta",-9.);
  vars.InitVar(prefix+"TopHadCandidate_B_Phi",-9.);
  vars.InitVar(prefix+"TopHadCandidate_B_CSV",-.1);

  vars.InitVar(prefix+"TopHadCandidate_W1_E",-9.);
  vars.InitVar(prefix+"TopHadCandidate_W1_Pt",-9.);
  vars.InitVar(prefix+"TopHadCandidate_W1_M",-9.);
  vars.InitVar(prefix+"TopHadCandidate_W1_Eta",-9.);
  vars.InitVar(prefix+"TopHadCandidate_W1_Phi",-9.);
  vars.InitVar(prefix+"TopHadCandidate_W1_CSV",-1.);

  vars.InitVar(prefix+"TopHadCandidate_W2_E",-9.);
  vars.InitVar(prefix+"TopHadCandidate_W2_Pt",-9.);
  vars.InitVar(prefix+"TopHadCandidate_W2_M",-9.);
  vars.InitVar(prefix+"TopHadCandidate_W2_Eta",-9.);
  vars.InitVar(prefix+"TopHadCandidate_W2_Phi",-9.);
  vars.InitVar(prefix+"TopHadCandidate_W2_CSV",-1.);

  vars.InitVar(prefix+"TopHadCandidate_W_E",-9.);
  vars.InitVar(prefix+"TopHadCandidate_W_Pt",-9.);
  vars.InitVar(prefix+"TopHadCandidate_W_M",-9.);
  vars.InitVar(prefix+"TopHadCandidate_W_Eta",-9.);
  vars.InitVar(prefix+"TopHadCandidate_W_Phi",-9.);
  
  vars.InitVar(prefix+"TopHadCandidate_BW1_E",-9.);
  vars.InitVar(prefix+"TopHadCandidate_BW1_Pt",-9.);
  vars.InitVar(prefix+"TopHadCandidate_BW1_M",-9.);
  vars.InitVar(prefix+"TopHadCandidate_BW1_Eta",-9.);
  vars.InitVar(prefix+"TopHadCandidate_BW1_Phi",-9.);
  
  vars.InitVar(prefix+"TopHadCandidate_BW2_E",-9.);
  vars.InitVar(prefix+"TopHadCandidate_BW2_Pt",-9.);
  vars.InitVar(prefix+"TopHadCandidate_BW2_M",-9.);
  vars.InitVar(prefix+"TopHadCandidate_BW2_Eta",-9.);
  vars.InitVar(prefix+"TopHadCandidate_BW2_Phi",-9.);
  
  vars.InitVar(prefix+"TopHadCandidate_Top_E",-9.);
  vars.InitVar(prefix+"TopHadCandidate_Top_Pt",-9.);
  vars.InitVar(prefix+"TopHadCandidate_Top_M",-9.);
  vars.InitVar(prefix+"TopHadCandidate_Top_Eta",-9.);
  vars.InitVar(prefix+"TopHadCandidate_Top_Phi",-9.);
  
  vars.InitVar(prefix+"TopHadCandidate_FatJet_Mass",-9.);
  vars.InitVar(prefix+"TopHadCandidate_FatJet_Pt",-9.);
  vars.InitVar(prefix+"TopHadCandidate_FatJet_Eta",-9.);
  vars.InitVar(prefix+"TopHadCandidate_FatJet_Phi",-9.);

  vars.InitVar(prefix+"TopHadCandidate_TopMass",-9.);
  vars.InitVar(prefix+"TopHadCandidate_UnfilteredMass",-9.);
  vars.InitVar(prefix+"TopHadCandidate_PrunedMass",-9.);
  vars.InitVar(prefix+"TopHadCandidate_fRec",-9.);
  vars.InitVar(prefix+"TopHadCandidate_MassRatioPassed",-9.);

  vars.InitVar(prefix+"TopHadCandidate_Ropt",-9.);
  vars.InitVar(prefix+"TopHadCandidate_RoptCalc",-9.);
  vars.InitVar(prefix+"TopHadCandidate_PtForRoptCalc",-9.);

  vars.InitVar(prefix+"TopHadCandidate_Tau1Unfiltered",-9.);
  vars.InitVar(prefix+"TopHadCandidate_Tau2Unfiltered",-9.);
  vars.InitVar(prefix+"TopHadCandidate_Tau3Unfiltered",-9.);
  vars.InitVar(prefix+"TopHadCandidate_Tau1Filtered",-9.);
  vars.InitVar(prefix+"TopHadCandidate_Tau2Filtered",-9.);
  vars.InitVar(prefix+"TopHadCandidate_Tau3Filtered",-9.);

  vars.InitVar(prefix+"TopHadCandidate_QWeight",-9.);
  vars.InitVar(prefix+"TopHadCandidate_QEpsilon",-9.);
  vars.InitVar(prefix+"TopHadCandidate_QSigmaM",-9.);
  
  vars.InitVar(prefix+"TopHadCandidate_Dr_Lepton",-9.);
  vars.InitVar(prefix+"TopHadCandidate_M_Lepton_B",-9.);
  vars.InitVar(prefix+"TopHadCandidate_M_TopLep",-9.);
  vars.InitVar(prefix+"TopHadCandidate_M_HiggsAk5",-9.);
  vars.InitVar(prefix+"TopHadCandidate_M_TopHadAk5",-9.);
  vars.InitVar(prefix+"TopHadCandidate_M_HiggsAk5Loose",-9.);
  vars.InitVar(prefix+"TopHadCandidate_M_TopHadAk5Loose",-9.);
}


void ttHVarProcessor::InitTopLepCandidateVars(VariableContainer& vars){
  
  vars.InitVar(prefix+"TopLepCandidate_Top_E",-9.);
  vars.InitVar(prefix+"TopLepCandidate_Top_Pt",-9.);
  vars.InitVar(prefix+"TopLepCandidate_Top_M",-9.);
  vars.InitVar(prefix+"TopLepCandidate_Top_Eta",-9.);
  vars.InitVar(prefix+"TopLepCandidate_Top_Phi",-9.);
  
  vars.InitVar(prefix+"TopLepCandidate_W_E",-9.);
  vars.InitVar(prefix+"TopLepCandidate_W_Pt",-9.);
  vars.InitVar(prefix+"TopLepCandidate_W_M",-9.);
  vars.InitVar(prefix+"TopLepCandidate_W_Eta",-9.);
  vars.InitVar(prefix+"TopLepCandidate_W_Phi",-9.);
  
  vars.InitVar(prefix+"TopLepCandidate_B_E",-9.);
  vars.InitVar(prefix+"TopLepCandidate_B_Pt",-9.);
  vars.InitVar(prefix+"TopLepCandidate_B_M",-9.);
  vars.InitVar(prefix+"TopLepCandidate_B_Eta",-9.);
  vars.InitVar(prefix+"TopLepCandidate_B_Phi",-9.);
  vars.InitVar(prefix+"TopLepCandidate_B_CSV",-.1);
  
  vars.InitVar(prefix+"TopLepCandidate_Lep_E",-9.);
  vars.InitVar(prefix+"TopLepCandidate_Lep_Pt",-9.);
  vars.InitVar(prefix+"TopLepCandidate_Lep_M",-9.);
  vars.InitVar(prefix+"TopLepCandidate_Lep_Eta",-9.);
  vars.InitVar(prefix+"TopLepCandidate_Lep_Phi",-9.);
  
  vars.InitVar(prefix+"TopLepCandidate_Nu_E",-9.);
  vars.InitVar(prefix+"TopLepCandidate_Nu_Pt",-9.);
  vars.InitVar(prefix+"TopLepCandidate_Nu_M",-9.);
  vars.InitVar(prefix+"TopLepCandidate_Nu_Eta",-9.);
  vars.InitVar(prefix+"TopLepCandidate_Nu_Phi",-9.);
}


void ttHVarProcessor::InitAk5JetsVars(VariableContainer& vars){
  
  vars.InitVar(prefix+"N_Jets_ak5Jets",-9.,"I");
  vars.InitVar(prefix+"N_BTagsL_ak5Jets",-9.,"I");
  vars.InitVar(prefix+"N_BTagsM_ak5Jets",-9.,"I");
  vars.InitVar(prefix+"N_BTagsT_ak5Jets",-9.,"I");
  vars.InitVar(prefix+"AvgCSV_ak5Jets",-.1);
  
  vars.InitVar(prefix+"N_Jets_Higgs_ak5Jets",-9.,"I");
  vars.InitVar(prefix+"N_BTagsL_Higgs_ak5Jets",-9.,"I");
  vars.InitVar(prefix+"N_BTagsM_Higgs_ak5Jets",-9.,"I");
  vars.InitVar(prefix+"N_BTagsT_Higgs_ak5Jets",-9.,"I");
  vars.InitVar(prefix+"AvgCSV_Higgs_ak5Jets",-.1);
  
  vars.InitVar(prefix+"N_Jets_TopHad_ak5Jets",-9.,"I");
  vars.InitVar(prefix+"N_BTagsL_TopHad_ak5Jets",-9.,"I");
  vars.InitVar(prefix+"N_BTagsM_TopHad_ak5Jets",-9.,"I");
  vars.InitVar(prefix+"N_BTagsT_TopHad_ak5Jets",-9.,"I");
  vars.InitVar(prefix+"AvgCSV_TopHad_ak5Jets",-.1);
  
  vars.InitVar(prefix+"N_Jets_TopLep_ak5Jets",-9.,"I");
  vars.InitVar(prefix+"N_BTagsL_TopLep_ak5Jets",-9.,"I");
  vars.InitVar(prefix+"N_BTagsM_TopLep_ak5Jets",-9.,"I");
  vars.InitVar(prefix+"N_BTagsT_TopLep_ak5Jets",-9.,"I");
  vars.InitVar(prefix+"AvgCSV_TopLep_ak5Jets",-.1);
  
  vars.InitVar(prefix+"N_Jets_Clean_ak5Jets",-9.,"I");
  vars.InitVar(prefix+"N_BTagsL_Clean_ak5Jets",-9.,"I");
  vars.InitVar(prefix+"N_BTagsM_Clean_ak5Jets",-9.,"I");
  vars.InitVar(prefix+"N_BTagsT_Clean_ak5Jets",-9.,"I");
  vars.InitVar(prefix+"AvgCSV_Clean_ak5Jets",-.1);
}


void ttHVarProcessor::InitCombinationVars(VariableContainer& vars){
  
  vars.InitVar(prefix+"HiggsCandidate_Dr_TopHadCandidate",-9.);
  vars.InitVar(prefix+"HiggsCandidate_Dr_TopLepCandidate",-9.);
  vars.InitVar(prefix+"TopHadCandidate_Dr_TopLepCandidate",-9.);
  vars.InitVar(prefix+"HiggsCandidate_Dphi_TopHadCandidate",-9.);
  vars.InitVar(prefix+"HiggsCandidate_Dphi_TopLepCandidate",-9.);
  vars.InitVar(prefix+"TopHadCandidate_Dphi_TopLepCandidate",-9.);
  vars.InitVar(prefix+"HiggsCandidate_Deta_TopHadCandidate",-9.);
  vars.InitVar(prefix+"HiggsCandidate_Deta_TopLepCandidate",-9.);
  vars.InitVar(prefix+"TopHadCandidate_Deta_TopLepCandidate",-9.);
}


void ttHVarProcessor::InitMCVars(VariableContainer& vars){
  
  vars.InitVar(prefix+"HiggsCandidate_Dr_TopHad",-9.);
  vars.InitVar(prefix+"HiggsCandidate_Dr_TopLep",-9.);
  vars.InitVar(prefix+"HiggsCandidate_Dr_Higgs",-9.);
  vars.InitVar(prefix+"TopHadCandidate_Dr_TopLep",-9.);
  vars.InitVar(prefix+"TopHadCandidate_Dr_TopHad",-9.);
  vars.InitVar(prefix+"TopHadCandidate_Dr_Higgs",-9.);
  vars.InitVar(prefix+"TopLepCandidate_Dr_TopLep",-9.);
  vars.InitVar(prefix+"TopLepCandidate_Dr_TopHad",-9.);
  vars.InitVar(prefix+"TopLepCandidate_Dr_Higgs",-9.);
  vars.InitVar(prefix+"HiggsCandidate_Dr_B_TopHad",-9.);
  vars.InitVar(prefix+"HiggsCandidate_Dr_B_TopLep",-9.);
  vars.InitVar(prefix+"Dr_W1",-9.);
  vars.InitVar(prefix+"Dr_W2",-9.);
  vars.InitVar(prefix+"Dr_Bhad",-9.);
  vars.InitVar(prefix+"Dr_B1",-9.);
  vars.InitVar(prefix+"Dr_B2",-9.);
  vars.InitVar(prefix+"Dr_Blep",-9.);
  vars.InitVar(prefix+"Dr_Nu",-9.);
  vars.InitVar(prefix+"Dr_Lep",-9.);
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
    vars.FillVar(prefix+"HiggsCandidate_E",higgsCand.fatjet.energy());
    vars.FillVar(prefix+"HiggsCandidate_Pt",higgsCand.fatjet.pt());
    vars.FillVar(prefix+"HiggsCandidate_M",higgsCand.fatjet.mass());
    vars.FillVar(prefix+"HiggsCandidate_Eta",higgsCand.fatjet.eta());
    vars.FillVar(prefix+"HiggsCandidate_Phi",higgsCand.fatjet.phi());
    vars.FillVar(prefix+"HiggsCandidate_Filterjet1_Pt",higgsCand.filterjets[0].pt());
    vars.FillVar(prefix+"HiggsCandidate_Filterjet2_Pt",higgsCand.filterjets[1].pt());
  }
  
  if(higgsB1Cand.pt()>0){
    vars.FillVar(prefix+"HiggsCandidate_B1_E",higgsB1Cand.energy());
    vars.FillVar(prefix+"HiggsCandidate_B1_Pt",higgsB1Cand.pt());
    vars.FillVar(prefix+"HiggsCandidate_B1_M",higgsB1Cand.mass());
    vars.FillVar(prefix+"HiggsCandidate_B1_Eta",higgsB1Cand.eta());
    vars.FillVar(prefix+"HiggsCandidate_B1_Phi",higgsB1Cand.phi());
    vars.FillVar(prefix+"HiggsCandidate_B1_CSV",fmax(higgsB1Cand.bDiscriminator(btagger),-.1));
  }
  
  if(higgsB2Cand.pt()>0){
    vars.FillVar(prefix+"HiggsCandidate_B2_E",higgsB2Cand.energy());
    vars.FillVar(prefix+"HiggsCandidate_B2_Pt",higgsB2Cand.pt());
    vars.FillVar(prefix+"HiggsCandidate_B2_M",higgsB2Cand.mass());
    vars.FillVar(prefix+"HiggsCandidate_B2_Eta",higgsB2Cand.eta());
    vars.FillVar(prefix+"HiggsCandidate_B2_Phi",higgsB2Cand.phi());
    vars.FillVar(prefix+"HiggsCandidate_B2_CSV",fmax(higgsB2Cand.bDiscriminator(btagger),-.1));
  }
  
  if(higgsGCand.pt()>0){
    vars.FillVar(prefix+"HiggsCandidate_G_E",higgsGCand.energy());
    vars.FillVar(prefix+"HiggsCandidate_G_Pt",higgsGCand.pt());
    vars.FillVar(prefix+"HiggsCandidate_G_M",higgsGCand.mass());
    vars.FillVar(prefix+"HiggsCandidate_G_Eta",higgsGCand.eta());
    vars.FillVar(prefix+"HiggsCandidate_G_Phi",higgsGCand.phi());
    vars.FillVar(prefix+"HiggsCandidate_G_CSV",fmax(higgsGCand.bDiscriminator(btagger),-.1));
  }
  
  if(higgsCandVec2.Pt()>0){
    vars.FillVar(prefix+"HiggsCandidate_E2",higgsCandVec2.E());
    vars.FillVar(prefix+"HiggsCandidate_Pt2",higgsCandVec2.Pt());
    vars.FillVar(prefix+"HiggsCandidate_M2",higgsCandVec2.M());
    vars.FillVar(prefix+"HiggsCandidate_Eta2",higgsCandVec2.Eta());
    vars.FillVar(prefix+"HiggsCandidate_Phi2",higgsCandVec2.Phi());
  }
  
  if(higgsCandVec3.Pt()>0){
    vars.FillVar(prefix+"HiggsCandidate_E3",higgsCandVec3.E());
    vars.FillVar(prefix+"HiggsCandidate_Pt3",higgsCandVec3.Pt());
    vars.FillVar(prefix+"HiggsCandidate_M3",higgsCandVec3.M());
    vars.FillVar(prefix+"HiggsCandidate_Eta3",higgsCandVec3.Eta());
    vars.FillVar(prefix+"HiggsCandidate_Phi3",higgsCandVec3.Phi());
  }
  
  vars.FillVar(prefix+"HiggsCandidate_CosThetaStar_Filterjet12",BoostedUtils::CosThetaStar(higgsB1Cand.p4(),higgsB2Cand.p4()));
  vars.FillVar(prefix+"HiggsCandidate_CosThetaStar_Filterjet13",BoostedUtils::CosThetaStar(higgsB1Cand.p4(),higgsGCand.p4()));
  vars.FillVar(prefix+"HiggsCandidate_CosThetaStar_Filterjet23",BoostedUtils::CosThetaStar(higgsB2Cand.p4(),higgsGCand.p4()));
  
  if(higgsCand.fatjet.pt()>0){
    vars.FillVar(prefix+"HiggsCandidate_Subjetiness1",higgsCand.subjettiness1);
    vars.FillVar(prefix+"HiggsCandidate_Subjetiness2",higgsCand.subjettiness2);
    vars.FillVar(prefix+"HiggsCandidate_Subjetiness3",higgsCand.subjettiness3);
  }
  
  if(higgsCand.fatjet.pt()>0&&lepCandVec.Pt()>0)
    vars.FillVar(prefix+"HiggsCandidate_Dr_Lepton",BoostedUtils::DeltaR(lepCandVec,higgsCand.fatjet.p4()));
  
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
  
  vars.FillVar(prefix+"HiggsCandidate_M_Lepton_B", mblep);
  if(fabs(mtoplep_higgs1-173)<fabs(mtoplep_higgs2-173)&&fabs(mtoplep_higgs1-173)<fabs(mtoplep_higgs3-173)&&fabs(mtoplep_higgs1-173)<fabs(mtoplep_higgs4-173))   
    vars.FillVar(prefix+"HiggsCandidate_M_TopLep",mtoplep_higgs1);
  else if(fabs(mtoplep_higgs2-173)<fabs(mtoplep_higgs1-173)&&fabs(mtoplep_higgs2-173)<fabs(mtoplep_higgs3-173)&&fabs(mtoplep_higgs2-173)<fabs(mtoplep_higgs4-173))
    vars.FillVar(prefix+"HiggsCandidate_M_TopLep",mtoplep_higgs2);
  else if(fabs(mtoplep_higgs3-173)<fabs(mtoplep_higgs1-173)&&fabs(mtoplep_higgs3-173)<fabs(mtoplep_higgs2-173)&&fabs(mtoplep_higgs3-173)<fabs(mtoplep_higgs4-173))
    vars.FillVar(prefix+"HiggsCandidate_M_TopLep",mtoplep_higgs3);
  else if(fabs(mtoplep_higgs4-173)<fabs(mtoplep_higgs1-173)&&fabs(mtoplep_higgs4-173)<fabs(mtoplep_higgs2-173)&&fabs(mtoplep_higgs4-173)<fabs(mtoplep_higgs3-173))
    vars.FillVar(prefix+"HiggsCandidate_M_TopLep",mtoplep_higgs4);
  
  vars.FillVar(prefix+"HiggsCandidate_HiggsTag",higgsCandTag);
}


void ttHVarProcessor::FillTopHadCandidateVars(VariableContainer& vars, BoostedttHEvent& ttHEvent){
  
  // Get Objects
  boosted::HTTTopJet topHadCand = ttHEvent.GetTopHadCandBoosted();
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
  vars.FillVar(prefix+"TopHadCandidate_Tagged",BoostedUtils::GetTopTag(topHadCand));
  vars.FillVar(prefix+"TopHadCandidate_TaggedB",BoostedUtils::GetTopTag(topHadCand,0.15,120.,true));
  vars.FillVar(prefix+"TopHadCandidate_TopMVAOutput", toptagger.GetTopTag(topHadCand));
  
  if(topHadCand.fatjet.pt()>0){
    vars.FillVar(prefix+"TopHadCandidate_E",topHadCand.fatjet.energy());
    vars.FillVar(prefix+"TopHadCandidate_Pt",topHadCand.fatjet.pt());
    vars.FillVar(prefix+"TopHadCandidate_M",topHadCand.fatjet.mass());
    vars.FillVar(prefix+"TopHadCandidate_Eta",topHadCand.fatjet.eta());
    vars.FillVar(prefix+"TopHadCandidate_Phi",topHadCand.fatjet.phi());
  }
  
  if(topHadBCand.pt()>0){
    vars.FillVar(prefix+"TopHadCandidate_B_E",topHadBCand.energy());
    vars.FillVar(prefix+"TopHadCandidate_B_Pt",topHadBCand.pt());
    vars.FillVar(prefix+"TopHadCandidate_B_M",topHadBCand.mass());
    vars.FillVar(prefix+"TopHadCandidate_B_Eta",topHadBCand.eta());
    vars.FillVar(prefix+"TopHadCandidate_B_Phi",topHadBCand.phi());
    vars.FillVar(prefix+"TopHadCandidate_B_CSV",fmax(topHadBCand.bDiscriminator(btagger),-.1));
  }
  
  if(topHadW1Cand.pt()>0){
    vars.FillVar(prefix+"TopHadCandidate_W1_E",topHadW1Cand.energy());
    vars.FillVar(prefix+"TopHadCandidate_W1_Pt",topHadW1Cand.pt());
    vars.FillVar(prefix+"TopHadCandidate_W1_M",topHadW1Cand.mass());
    vars.FillVar(prefix+"TopHadCandidate_W1_Eta",topHadW1Cand.eta());
    vars.FillVar(prefix+"TopHadCandidate_W1_Phi",topHadW1Cand.phi());
    vars.FillVar(prefix+"TopHadCandidate_W1_CSV",fmax(topHadW1Cand.bDiscriminator(btagger),-.1));
  }
  
  if(topHadW2Cand.pt()>0){
    vars.FillVar(prefix+"TopHadCandidate_W2_E",topHadW2Cand.energy());
    vars.FillVar(prefix+"TopHadCandidate_W2_Pt",topHadW2Cand.pt());
    vars.FillVar(prefix+"TopHadCandidate_W2_M",topHadW2Cand.mass());
    vars.FillVar(prefix+"TopHadCandidate_W2_Eta",topHadW2Cand.eta());
    vars.FillVar(prefix+"TopHadCandidate_W2_Phi",topHadW2Cand.phi());
    vars.FillVar(prefix+"TopHadCandidate_W2_CSV",fmax(topHadW2Cand.bDiscriminator(btagger),-.1));
  }
  
  if(wHadCandVec.Pt()>0.001){
    vars.FillVar(prefix+"TopHadCandidate_W_E",wHadCandVec.E());
    vars.FillVar(prefix+"TopHadCandidate_W_Pt",wHadCandVec.Pt());
    vars.FillVar(prefix+"TopHadCandidate_W_M",wHadCandVec.M());
    vars.FillVar(prefix+"TopHadCandidate_W_Eta",wHadCandVec.Eta());
    vars.FillVar(prefix+"TopHadCandidate_W_Phi",wHadCandVec.Phi());
  }
  
  if(bW1CandVec.Pt()>0.001){
    vars.FillVar(prefix+"TopHadCandidate_BW1_E",bW1CandVec.E());
    vars.FillVar(prefix+"TopHadCandidate_BW1_Pt",bW1CandVec.Pt());
    vars.FillVar(prefix+"TopHadCandidate_BW1_M",bW1CandVec.M());
    vars.FillVar(prefix+"TopHadCandidate_BW1_Eta",bW1CandVec.Eta());
    vars.FillVar(prefix+"TopHadCandidate_BW1_Phi",bW1CandVec.Phi());
  }

  if(bW2CandVec.Pt()>0.001){
    vars.FillVar(prefix+"TopHadCandidate_BW2_E",bW2CandVec.E());
    vars.FillVar(prefix+"TopHadCandidate_BW2_Pt",bW2CandVec.Pt());
    vars.FillVar(prefix+"TopHadCandidate_BW2_M",bW2CandVec.M());
    vars.FillVar(prefix+"TopHadCandidate_BW2_Eta",bW2CandVec.Eta());
    vars.FillVar(prefix+"TopHadCandidate_BW2_Phi",bW2CandVec.Phi());
  }
  
  if(topHadCandVec.Pt()>0.001){
    vars.FillVar(prefix+"TopHadCandidate_Top_E",topHadCandVec.E());
    vars.FillVar(prefix+"TopHadCandidate_Top_M",topHadCandVec.M());
    vars.FillVar(prefix+"TopHadCandidate_Top_Pt", topHadCandVec.Pt());
    vars.FillVar(prefix+"TopHadCandidate_Top_Eta",topHadCandVec.Eta());
    vars.FillVar(prefix+"TopHadCandidate_Top_Phi", topHadCandVec.Phi());
  }

  vars.FillVar(prefix+"TopHadCandidate_FatJet_Mass",topHadCand.fatjetMass);
  vars.FillVar(prefix+"TopHadCandidate_FatJet_Pt",topHadCand.fatjetPt);
  vars.FillVar(prefix+"TopHadCandidate_FatJet_Eta",topHadCand.fatjetEta);
  vars.FillVar(prefix+"TopHadCandidate_FatJet_Phi",topHadCand.fatjetPhi);

  vars.FillVar(prefix+"TopHadCandidate_TopMass",topHadCand.topMass);
  vars.FillVar(prefix+"TopHadCandidate_UnfilteredMass",topHadCand.unfilteredMass);
  vars.FillVar(prefix+"TopHadCandidate_PrunedMass",topHadCand.prunedMass);
  vars.FillVar(prefix+"TopHadCandidate_fRec",topHadCand.fRec);
  vars.FillVar(prefix+"TopHadCandidate_MassRatioPassed",topHadCand.massRatioPassed);

  vars.FillVar(prefix+"TopHadCandidate_Ropt",topHadCand.Ropt);
  vars.FillVar(prefix+"TopHadCandidate_RoptCalc",topHadCand.RoptCalc);
  vars.FillVar(prefix+"TopHadCandidate_PtForRoptCalc",topHadCand.ptForRoptCalc);

  vars.FillVar(prefix+"TopHadCandidate_Tau1Unfiltered",topHadCand.tau1Unfiltered);
  vars.FillVar(prefix+"TopHadCandidate_Tau2Unfiltered",topHadCand.tau2Unfiltered);
  vars.FillVar(prefix+"TopHadCandidate_Tau3Unfiltered",topHadCand.tau3Unfiltered);
  vars.FillVar(prefix+"TopHadCandidate_Tau1Filtered",topHadCand.tau1Filtered);
  vars.FillVar(prefix+"TopHadCandidate_Tau2Filtered",topHadCand.tau2Filtered);
  vars.FillVar(prefix+"TopHadCandidate_Tau3Filtered",topHadCand.tau3Filtered);

  vars.FillVar(prefix+"TopHadCandidate_QWeight",topHadCand.qWeight);
  vars.FillVar(prefix+"TopHadCandidate_QEpsilon",topHadCand.qEpsilon);
  vars.FillVar(prefix+"TopHadCandidate_QSigmaM",topHadCand.qSigmaM);
  
  if(topHadCandVec.Pt()>0 && lepCandVec.Pt()>0){
    vars.FillVar(prefix+"TopHadCandidate_Dr_Lepton",BoostedUtils::DeltaR(lepCandVec,topHadCandVec));
  }
  
  float mtoplep_tophad1=(nu1CandVec+lepCandVec+topHadBCand.p4()).M();
  float mtoplep_tophad2=(nu2CandVec+lepCandVec+topHadBCand.p4()).M();
  if(topHadBCand.pt()>0.001){
    vars.FillVar(prefix+"TopHadCandidate_M_Lepton_B", (lepCandVec+topHadBCand.p4()).M());
    vars.FillVar(prefix+"TopHadCandidate_M_TopLep",fabs(mtoplep_tophad1-173)<fabs(mtoplep_tophad2-173) ? mtoplep_tophad1 : mtoplep_tophad2);
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
    vars.FillVar(prefix+"TopLepCandidate_Top_E",topLepCandVec.E());
    vars.FillVar(prefix+"TopLepCandidate_Top_Pt",topLepCandVec.Pt());
    vars.FillVar(prefix+"TopLepCandidate_Top_M",topLepCandVec.M());
    vars.FillVar(prefix+"TopLepCandidate_Top_Eta",topLepCandVec.Eta());
    vars.FillVar(prefix+"TopLepCandidate_Top_Phi",topLepCandVec.Phi());
  }
  
  if(wLepCandVec.Pt()>0.001){
    vars.FillVar(prefix+"TopLepCandidate_W_E",wLepCandVec.E());
    vars.FillVar(prefix+"TopLepCandidate_W_Pt",wLepCandVec.Pt());
    vars.FillVar(prefix+"TopLepCandidate_W_M",wLepCandVec.M());
    vars.FillVar(prefix+"TopLepCandidate_W_Eta",wLepCandVec.Eta());
    vars.FillVar(prefix+"TopLepCandidate_W_Phi",wLepCandVec.Phi());
  }
  
  if(topLepBCand.pt()>0.001){
    vars.FillVar(prefix+"TopLepCandidate_B_E",topLepBCand.energy());
    vars.FillVar(prefix+"TopLepCandidate_B_Pt",topLepBCand.pt());
    vars.FillVar(prefix+"TopLepCandidate_B_M",topLepBCand.mass());
    vars.FillVar(prefix+"TopLepCandidate_B_Eta",topLepBCand.eta());
    vars.FillVar(prefix+"TopLepCandidate_B_Phi",topLepBCand.phi());
    vars.FillVar(prefix+"TopLepCandidate_B_CSV",fmax(topLepBCand.bDiscriminator(btagger),-.1));
  }
  
  if(lepCandVec.Pt()>0.001){
    vars.FillVar(prefix+"TopLepCandidate_Lep_E",lepCandVec.E());
    vars.FillVar(prefix+"TopLepCandidate_Lep_Pt",lepCandVec.Pt());
    vars.FillVar(prefix+"TopLepCandidate_Lep_M",lepCandVec.M());
    vars.FillVar(prefix+"TopLepCandidate_Lep_Eta",lepCandVec.Eta());
    vars.FillVar(prefix+"TopLepCandidate_Lep_Phi",lepCandVec.Phi()); 
  }
  
  if(nuCandVec.Pt()>0.001){
    vars.FillVar(prefix+"TopLepCandidate_Nu_E",nuCandVec.E());
    vars.FillVar(prefix+"TopLepCandidate_Nu_Pt",nuCandVec.Pt());
    vars.FillVar(prefix+"TopLepCandidate_Nu_M",nuCandVec.M());
    vars.FillVar(prefix+"TopLepCandidate_Nu_Eta",nuCandVec.Eta());
    vars.FillVar(prefix+"TopLepCandidate_Nu_Phi",nuCandVec.Phi()); 
  }
}


void ttHVarProcessor::FillAk5JetsVars(VariableContainer& vars,BoostedttHEvent& ttHEvent){
  
  // Fill Variables
  vars.FillVar(prefix+"N_Jets_ak5Jets",ttHEvent.GetNJets());
  vars.FillVar(prefix+"N_BTagsL_ak5Jets",ttHEvent.GetNBTagL());
  vars.FillVar(prefix+"N_BTagsM_ak5Jets",ttHEvent.GetNBTagM());
  vars.FillVar(prefix+"N_BTagsT_ak5Jets",ttHEvent.GetNBTagT());
  vars.FillVar(prefix+"AvgCSV_ak5Jets",ttHEvent.GetAverageCSV());
  
  vars.FillVar(prefix+"N_Jets_Higgs_ak5Jets",ttHEvent.GetNHiggsak5Jets());
  vars.FillVar(prefix+"N_BTagsL_Higgs_ak5Jets",ttHEvent.GetNHiggsCandBTagL());
  vars.FillVar(prefix+"N_BTagsM_Higgs_ak5Jets",ttHEvent.GetNHiggsCandBTagM());
  vars.FillVar(prefix+"N_BTagsT_Higgs_ak5Jets",ttHEvent.GetNHiggsCandBTagT());
  vars.FillVar(prefix+"AvgCSV_Higgs_ak5Jets",ttHEvent.GetAverageCSVHiggsCand());
  
  vars.FillVar(prefix+"N_Jets_TopHad_ak5Jets",ttHEvent.GetNTopHadak5Jets());
  vars.FillVar(prefix+"N_BTagsL_TopHad_ak5Jets",ttHEvent.GetNTopHadCandBTagL());
  vars.FillVar(prefix+"N_BTagsM_TopHad_ak5Jets",ttHEvent.GetNTopHadCandBTagM());
  vars.FillVar(prefix+"N_BTagsT_TopHad_ak5Jets",ttHEvent.GetNTopHadCandBTagT());
  vars.FillVar(prefix+"AvgCSV_TopHad_ak5Jets",ttHEvent.GetAverageCSVTopHadCand());
  
  vars.FillVar(prefix+"N_Jets_TopLep_ak5Jets",ttHEvent.GetNTopLepak5Jets());
  vars.FillVar(prefix+"N_BTagsL_TopLep_ak5Jets",ttHEvent.GetNTopLepCandBTagL());
  vars.FillVar(prefix+"N_BTagsM_TopLep_ak5Jets",ttHEvent.GetNTopLepCandBTagM());
  vars.FillVar(prefix+"N_BTagsT_TopLep_ak5Jets",ttHEvent.GetNTopLepCandBTagT());
  vars.FillVar(prefix+"AvgCSV_TopLep_ak5Jets",ttHEvent.GetAverageCSVTopLepCand());
  
  vars.FillVar(prefix+"N_Jets_Clean_ak5Jets",ttHEvent.GetNCleanedak5Jets());
  vars.FillVar(prefix+"N_BTagsL_Clean_ak5Jets",ttHEvent.GetNCleanedBTagL());
  vars.FillVar(prefix+"N_BTagsM_Clean_ak5Jets",ttHEvent.GetNCleanedBTagM());
  vars.FillVar(prefix+"N_BTagsT_Clean_ak5Jets",ttHEvent.GetNCleanedBTagT());
  vars.FillVar(prefix+"AvgCSV_Clean_ak5Jets",ttHEvent.GetAverageCSVClean());
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
  if(higgsCandVec2.Pt()>0 && topHadCandVec.Pt()>0){
    vars.FillVar(prefix+"HiggsCandidate_Dr_TopHadCandidate",BoostedUtils::DeltaR(topHadCandVec,higgsCandVec2));
    vars.FillVar(prefix+"HiggsCandidate_Dphi_TopHadCandidate",BoostedUtils::DeltaPhi(topHadCandVec,higgsCandVec2));
    vars.FillVar(prefix+"HiggsCandidate_Deta_TopHadCandidate",BoostedUtils::DeltaEta(topHadCandVec,higgsCandVec2));
  }
  
  if(higgsCandVec2.Pt()>0 && topLepCandVec.Pt()>0){
    vars.FillVar(prefix+"HiggsCandidate_Dr_TopLepCandidate",BoostedUtils::DeltaR(topLepCandVec,higgsCandVec2));
    vars.FillVar(prefix+"HiggsCandidate_Dphi_TopLepCandidate",BoostedUtils::DeltaPhi(topLepCandVec,higgsCandVec2));
    vars.FillVar(prefix+"HiggsCandidate_Deta_TopLepCandidate",BoostedUtils::DeltaEta(topLepCandVec,higgsCandVec2));
  }
  
  if(topHadCandVec.Pt()>0 && topLepCandVec.Pt()>0){
    vars.FillVar(prefix+"TopHadCandidate_Dr_TopLepCandidate",BoostedUtils::DeltaR(topLepCandVec,topHadCandVec));
    vars.FillVar(prefix+"TopHadCandidate_Dphi_TopLepCandidate",BoostedUtils::DeltaPhi(topLepCandVec,topHadCandVec));
    vars.FillVar(prefix+"TopHadCandidate_Deta_TopLepCandidate",BoostedUtils::DeltaEta(topLepCandVec,topHadCandVec));
  }
}


void ttHVarProcessor::FillMCVars(VariableContainer& vars,BoostedttHEvent& ttHEvent,const InputCollections& input){
  
  // Get Objects
  
  // MC Objects 
  std::vector<math::XYZTLorentzVector> tophad_mc;
  std::vector<math::XYZTLorentzVector> whad_mc;
  std::vector<math::XYZTLorentzVector> bhad_mc;
  std::vector<math::XYZTLorentzVector> q1_mc;
  std::vector<math::XYZTLorentzVector> q2_mc;
  std::vector<math::XYZTLorentzVector> toplep_mc;
  std::vector<math::XYZTLorentzVector> wlep_mc;
  std::vector<math::XYZTLorentzVector> blep_mc;
  std::vector<math::XYZTLorentzVector> lep_mc;
  std::vector<math::XYZTLorentzVector> nu_mc;
  math::XYZTLorentzVector higgs_mc;
  std::vector<reco::GenParticle> higgs_bs;
  if(input.genTopEvt.IsFilled()){
    tophad_mc=input.genTopEvt.GetAllTopHadVecs();
    whad_mc=input.genTopEvt.GetAllWhadVecs();
    bhad_mc=input.genTopEvt.GetAllTopHadDecayQuarkVecs();
    q1_mc=input.genTopEvt.GetAllWQuarkVecs();
    q2_mc=input.genTopEvt.GetAllWAntiQuarkVecs();
    toplep_mc=input.genTopEvt.GetAllTopLepVecs();
    wlep_mc=input.genTopEvt.GetAllWlepVecs();
    blep_mc=input.genTopEvt.GetAllTopLepDecayQuarkVecs();
    lep_mc=input.genTopEvt.GetAllLeptonVecs();
    nu_mc=input.genTopEvt.GetAllNeutrinoVecs();
    higgs_mc=input.genTopEvt.GetHiggsVec();
    higgs_bs=input.genTopEvt.GetHiggsDecayProducts();
  }

  math::XYZTLorentzVector b1_mc;
  math::XYZTLorentzVector b2_mc;

  for(auto p =higgs_bs.begin(); p!=higgs_bs.end(); p++){
    if(abs(p->pdgId())==5) b1_mc=p->p4();
    if(abs(p->pdgId())==-5) b2_mc=p->p4();
  }
  
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

  if(higgsCandVec2.Pt()>0){
    if(higgs_mc.Pt()>0)
            vars.FillVar(prefix+"HiggsCandidate_Dr_Higgs",BoostedUtils::DeltaR(higgs_mc,higgsCandVec2));
    
    if(tophad_mc.size()==1){
      vars.FillVar(prefix+"HiggsCandidate_Dr_B_TopHad",BoostedUtils::DeltaR(bhad_mc[0],higgsCandVec2));
      vars.FillVar(prefix+"HiggsCandidate_Dr_TopHad",BoostedUtils::DeltaR(tophad_mc[0],higgsCandVec2));
    }
    else if(tophad_mc.size()==2){
      vars.FillVar(prefix+"HiggsCandidate_Dr_B_TopHad",fmin(BoostedUtils::DeltaR(bhad_mc[0],higgsCandVec2),BoostedUtils::DeltaR(bhad_mc[1],higgsCandVec2)));
      vars.FillVar(prefix+"HiggsCandidate_Dr_TopHad",fmin(BoostedUtils::DeltaR(tophad_mc[0],higgsCandVec2),BoostedUtils::DeltaR(tophad_mc[1],higgsCandVec2)));
    }
   
    if(toplep_mc.size()==1){
      vars.FillVar(prefix+"HiggsCandidate_Dr_B_TopLep",BoostedUtils::DeltaR(blep_mc[0],higgsCandVec2));
      vars.FillVar(prefix+"HiggsCandidate_Dr_TopLep",BoostedUtils::DeltaR(toplep_mc[0],higgsCandVec2));
    }
    else if(toplep_mc.size()==2){
      vars.FillVar(prefix+"HiggsCandidate_Dr_B_TopLep",fmin(BoostedUtils::DeltaR(blep_mc[0],higgsCandVec2),BoostedUtils::DeltaR(blep_mc[1],higgsCandVec2)));
      vars.FillVar(prefix+"HiggsCandidate_Dr_TopLep",fmin(BoostedUtils::DeltaR(toplep_mc[0],higgsCandVec2),BoostedUtils::DeltaR(toplep_mc[1],higgsCandVec2)));
    }
  }
  
  if(topHadCandVec.Pt()>0){
    if(higgs_mc.Pt()>0)
      vars.FillVar(prefix+"TopHadCandidate_Dr_Higgs",BoostedUtils::DeltaR(higgs_mc,topHadCandVec));
   
    if(tophad_mc.size()==1)
      vars.FillVar(prefix+"TopHadCandidate_Dr_TopHad",BoostedUtils::DeltaR(tophad_mc[0],topHadCandVec));
    else if (tophad_mc.size()==2)
       vars.FillVar(prefix+"TopHadCandidate_Dr_TopHad",fmin(BoostedUtils::DeltaR(tophad_mc[0],topHadCandVec),BoostedUtils::DeltaR(tophad_mc[1],topHadCandVec)));
     
    if(toplep_mc.size()==1)
      vars.FillVar(prefix+"TopHadCandidate_Dr_TopLep",BoostedUtils::DeltaR(toplep_mc[0],topHadCandVec));
    else if (toplep_mc.size()==2)
       vars.FillVar(prefix+"TopHadCandidate_Dr_TopLep",fmin(BoostedUtils::DeltaR(toplep_mc[0],topHadCandVec),BoostedUtils::DeltaR(toplep_mc[1],topHadCandVec)));
  }
  
  if(topLepCandVec.Pt()>0){
    if(higgs_mc.Pt()>0)
            vars.FillVar(prefix+"TopLepCandidate_Dr_Higgs",BoostedUtils::DeltaR(higgs_mc,topLepCandVec));
    
    if(tophad_mc.size()==1)
      vars.FillVar(prefix+"TopLepCandidate_Dr_TopHad",BoostedUtils::DeltaR(tophad_mc[0],topLepCandVec));
    else if (tophad_mc.size()==2)
      vars.FillVar(prefix+"TopLepCandidate_Dr_TopHad",fmin(BoostedUtils::DeltaR(tophad_mc[0],topLepCandVec),BoostedUtils::DeltaR(tophad_mc[1],topLepCandVec)));
    
    if(toplep_mc.size()==1)
      vars.FillVar(prefix+"TopLepCandidate_Dr_TopLep",BoostedUtils::DeltaR(toplep_mc[0],topLepCandVec));
    else if (toplep_mc.size()==2)
      vars.FillVar(prefix+"TopLepCandidate_Dr_TopLep",fmin(BoostedUtils::DeltaR(toplep_mc[0],topLepCandVec),BoostedUtils::DeltaR(toplep_mc[1],topLepCandVec)));
  }
  
  float drw11 = 9;
  float drw22 = 9;
  float drw21 = 9;
  float drw12 = 9;
 
  int topHadMCID = -1;
  if(tophad_mc.size()>0) topHadMCID = 0;
  if(tophad_mc.size()>1 && topHadCandVec.Pt()>0){
    if(BoostedUtils::DeltaR(tophad_mc[1],topHadCandVec)<BoostedUtils::DeltaR(tophad_mc[0],topHadCandVec)) topHadMCID = 1;
  }
  
  if(tophad_mc.size()>0 && topHadW1Cand.pt()>0 && topHadW2Cand.pt()>0){
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
  
  vars.FillVar(prefix+"Dr_W1",drw1 );
  vars.FillVar(prefix+"Dr_W2",drw2 );
  
  if(topHadMCID>=0 && topHadBCand.pt()>0) vars.FillVar(prefix+"Dr_Bhad",BoostedUtils::DeltaR(bhad_mc[topHadMCID],topHadBCand.p4())); 
  
  float drb11 = 9;
  float drb22 = 9;
  float drb21 = 9;
  float drb12 = 9;
  if(b1_mc.pt()>0 && b2_mc.pt()>0 && higgsB1Cand.pt()>0 && higgsB2Cand.pt()>0){
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
  
  vars.FillVar(prefix+"Dr_B1",drb1 );
  vars.FillVar(prefix+"Dr_B2",drb2 );
  
  int topLepMCID = -1;
  if(toplep_mc.size()>0) topLepMCID = 0;
  if(toplep_mc.size()>1 && topLepCandVec.Pt()>0.001){
    if(BoostedUtils::DeltaR(toplep_mc[1],topLepCandVec)<BoostedUtils::DeltaR(toplep_mc[0],topLepCandVec)) topLepMCID = 1;
  }
 
  if(toplep_mc.size()>0){
    if(topLepBCand.pt()>0) vars.FillVar(prefix+"Dr_Blep",BoostedUtils::DeltaR(blep_mc[topLepMCID],topLepBCand.p4()));
    if(nuCandVec.Pt()>0) vars.FillVar(prefix+"Dr_Nu",BoostedUtils::DeltaR(nu_mc[topLepMCID],nuCandVec));
    if(lepCandVec.Pt()>0) vars.FillVar(prefix+"Dr_Lep",BoostedUtils::DeltaR(lep_mc[topLepMCID],lepCandVec));
  }
}
