#include "BoostedTTH/BoostedAnalyzer/interface/SynchSelection.hpp"

using namespace std;

SynchSelection::SynchSelection (){}
SynchSelection::~SynchSelection (){}

void SynchSelection::Init(const edm::ParameterSet& iConfig, Cutflow& cutflow){
  vector<std::string> muonTriggers;
  muonTriggers.push_back("HLT_IsoMu24_eta2p1_IterTrk02_v1");
  vector<std::string> electronTriggers;
  electronTriggers.push_back("HLT_Ele27_eta2p1_WP85_Gsf_v1");

   std::cout<<electronTriggers.size()<<" "<<muonTriggers.size()<<" "<<std::endl;

  cutflow.AddStep("vertex selection");
  cutflow.AddStep("single lepton trigger");
  cutflow.AddStep("== 1 lepton");
  cutflow.AddStep("== 0 leptons different flavor");
  cutflow.AddStep(">= 4 jets");
  cutflow.AddStep(">= 2 b-tags");
  cutflow.AddStep(">= 1 top tagged jet");
  cutflow.AddStep(">= 1 Higgs jet");
  
  
  Config=iConfig;  

  initialized=true;
}

bool SynchSelection::IsSelected(const InputCollections& input,Cutflow& cutflow){
  if(!initialized) cerr << "SynchSelection not initialized" << endl;
  
  bool doElectrons=false;
  
  // For this selection, do object selections first
  // This is an exception, usually object selections should be done in BoostedAnalyzer.cc with the help of the miniAODhelper
  //do only first vertex
  bool hasGoodVertex = false; 
  if(input.selectedPVs.size()>0){
    reco::Vertex vtx= input.selectedPVs[0];
    hasGoodVertex = !vtx.isFake() 
      && vtx.ndof() >= 4.0 
      && abs(vtx.z()) <= 24.0 
      && abs(vtx.position().Rho()) <= 2.0;
  }

std::cout<<"doing electrons"<<std::endl;
//-------------------------------------------------------------------------
//do electrons
   std::vector<pat::Electron> selectedElectrons;
  for( std::vector<pat::Electron>::const_iterator it = input.selectedElectrons.begin(), ed = input.selectedElectrons.end(); it != ed; ++it ){
    pat::Electron iElectron = *it;
    bool passesKinematics=false;
    bool inCrack=true;
    bool passesConversion=false;
    bool passesISO=false;
    bool passessID=false;
    
    //check if barrel or endcap supercluster
  double SCeta = (iElectron.superCluster().isAvailable()) ? iElectron.superCluster()->position().eta() : 99;
  double absSCeta = fabs(SCeta);
  bool isEB = ( absSCeta <= 1.479 );
  bool isEE = ( absSCeta > 1.479 && absSCeta < 2.5 );
    
    //isolation
  double pfIsoCharged = iElectron.pfIsolationVariables().sumChargedHadronPt;
  double pfIsoNeutralHadron = iElectron.pfIsolationVariables().sumNeutralHadronEt;
  double pfIsoNeutralPhoton = iElectron.pfIsolationVariables().sumPhotonEt;
  double pfIsoSumPUPt = iElectron.pfIsolationVariables().sumPUPt;

  double relIso = (pfIsoCharged + std::max( pfIsoNeutralHadron + pfIsoNeutralPhoton - 0.5*pfIsoSumPUPt, 0.0 ))/iElectron.pt();


    //other stuff
  double full5x5_sigmaIetaIeta = iElectron.full5x5_sigmaIetaIeta();
  double dEtaIn = fabs( iElectron.deltaEtaSuperClusterTrackAtVtx() );
  double dPhiIn = fabs( iElectron.deltaPhiSuperClusterTrackAtVtx() );
  double hOverE = iElectron.hcalOverEcal();

  double ooEmooP = 999;
  if( iElectron.ecalEnergy() == 0 ) ooEmooP = 1e30;
  else if( !std::isfinite(iElectron.ecalEnergy()) ) ooEmooP = 1e30;
  else ooEmooP = fabs(1.0/iElectron.ecalEnergy() - iElectron.eSuperClusterOverP()/iElectron.ecalEnergy() );

  double d0 = 999;
  double dZ = 999;
  double expectedMissingInnerHits = 999;
  if( iElectron.gsfTrack().isAvailable() ){
    d0 = fabs(iElectron.gsfTrack()->dxy(input.selectedPVs[0].position()));
    dZ = fabs(iElectron.gsfTrack()->dz(input.selectedPVs[0].position()));
    expectedMissingInnerHits = iElectron.gsfTrack()->hitPattern().numberOfHits(reco::HitPattern::MISSING_INNER_HITS);
  }

  //do the checks
  passesConversion = ( iElectron.passConversionVeto() );
  passesKinematics = (iElectron.pt()>20 && fabs(iElectron.eta())<2.4);
  inCrack = (fabs(iElectron.superCluster()->position().eta())>1.4442 && fabs(iElectron.superCluster()->position().eta())<1.5660);
  
  //dZ and d0 cuts are different than in the posted recipe 
  if(isEB){
      passessID = (full5x5_sigmaIetaIeta<0.010399 && dEtaIn<0.007641 && dPhiIn<0.032643 &&hOverE<0.060662 && d0<0.05 && dZ<0.5 && expectedMissingInnerHits<=1 && ooEmooP<0.153897);
      passesISO = (relIso<0.097213);
      }
  else if(isEE){
      passessID = (full5x5_sigmaIetaIeta<0.029524 && dEtaIn<0.009285 && dPhiIn<0.042447 &&hOverE<0.104263 && d0<0.05 && dZ<0.5 && expectedMissingInnerHits<=1 && ooEmooP<0.137468);
      passesISO = (relIso<0.116708);
      }
  else{
       passessID=false;
       passesISO=false;
       }
  
  if(passesKinematics && passesConversion && passesISO && passessID && !inCrack){
    selectedElectrons.push_back(*it);
    }
    
  }
  
std::cout<<"doing muons"<<std::endl;
//-------------------------------------------------------------------------
//do muons
  std::vector<pat::Muon> selectedMuons;
  for( std::vector<pat::Muon>::const_iterator it = input.selectedMuons.begin(), ed = input.selectedMuons.end(); it != ed; ++it ){
    pat::Muon iMuon = *it;
    bool passesKinematics=false;
    bool isPFandGlobal=false;
    bool passesISO=false;
    bool passesGlobalTrackID=false;
    bool passesBestTrackID=false;
    bool passesinnerTrackID=false;
    bool passesTrackID=false;
    bool passesID=false;
    
    if(iMuon.globalTrack().isAvailable()){
    double chi2ndof = iMuon.globalTrack()->normalizedChi2();
    int nValidHits = iMuon.globalTrack()->hitPattern().numberOfValidMuonHits();
    passesGlobalTrackID=(chi2ndof<10.0 && nValidHits>0);
    } 

    if(iMuon.muonBestTrack().isAvailable()){
    double d0 = fabs(iMuon.muonBestTrack()->dxy(input.selectedPVs[0].position()));
    double dZ = fabs(iMuon.muonBestTrack()->dz(input.selectedPVs[0].position()));
    passesBestTrackID=(d0<0.2 && dZ<0.5);
    }

    int nMatchedStations = iMuon.numberOfMatchedStations();
        
    if(iMuon.track().isAvailable()){
    int nTrackerLayers = iMuon.track()->hitPattern().trackerLayersWithMeasurement();
    passesTrackID=(nTrackerLayers>5);
    }

    
    if(iMuon.innerTrack().isAvailable()){
    int nValidPiyles = iMuon.innerTrack()->hitPattern().numberOfValidPixelHits();
    passesinnerTrackID=(nValidPiyles>0);
    }
    double relIso = (iMuon.pfIsolationR04().sumChargedHadronPt + std::max( iMuon.pfIsolationR04().sumNeutralHadronEt + iMuon.pfIsolationR04().sumPhotonEt - 0.5 * iMuon.pfIsolationR04().sumPUPt,0.0)) / iMuon.pt();
    
    isPFandGlobal = (iMuon.isPFMuon() && iMuon.isGlobalMuon());
    passesKinematics = (iMuon.pt()>20 && fabs(iMuon.eta())<2.4);
    passesISO = (relIso<0.12);
    passesID = (passesinnerTrackID && passesGlobalTrackID && passesBestTrackID && passesTrackID && nMatchedStations>1);
    
    if(passesKinematics && passesISO && passesID && isPFandGlobal){
    selectedMuons.push_back(*it);
    }
    
  }


    
std::cout<<"doing trigger"<<std::endl;

//-------------------------------------------------------------------------
//do trigger
bool hasTriggered=false;
//  std::cout<<electronTriggers.size()<<" "<<muonTriggers.size()<<" "<<std::endl;

vector<string> targetTriggers;
  if(doElectrons){
    targetTriggers.push_back("HLT_Ele27_eta2p1_WP85_Gsf_v1");
  }
  else{
      targetTriggers.push_back("HLT_IsoMu24_eta2p1_IterTrk02_v1");
    }
  
 if(input.triggerResults.size()>0){ 
//   std::cout<<"ok im here"<<std::endl;
  
  for(vector<string>::const_iterator iTarget = targetTriggers.begin();iTarget != targetTriggers.end();iTarget++) {
    
    unsigned int TriggerID =  input.hlt_config.triggerIndex(*iTarget);
    std::cout<<TriggerID<<" "<<input.triggerResults.size()<<std::endl;
    if( TriggerID >= input.triggerResults.size() ) continue;
      std::cout<<input.triggerResults.accept(TriggerID)<<std::endl;

    if(input.triggerResults.accept(TriggerID)) hasTriggered=true;

  }
}
else hasTriggered=false;



//----------------------------------------------------------------------------------
//do jets
std::vector<pat::Jet> cleanEleJets;
std::vector<pat::Jet> cleanMuonJets;
std::vector<pat::Jet> correctedJets;
std::vector<pat::Jet> sortedJets;
std::vector<pat::Jet> selectedJets;
std::vector<pat::Jet> taggedJets;

//first uncorrect the jets
std::vector<pat::Jet> bufferJets;
for( std::vector<pat::Jet>::const_iterator it = input.selectedJets.begin(), ed = input.selectedJets.end(); it != ed; ++it ){
  pat::Jet iJet = *it;
  double originalPt = iJet.pt();
  std::cout<<iJet.currentJECLevel()<<" "<<iJet.currentJECSet()<<std::endl;
  math::XYZTLorentzVector uncorrectedP4 = iJet.correctedP4("Uncorrected");
  math::XYZTLorentzVector ALTuncorrectedP4 = iJet.correctedJet(0).p4();
  iJet.setP4(uncorrectedP4);
  double uncorrectedPt = iJet.pt();
  std::cout<<originalPt<<" "<<uncorrectedPt<<std::endl;
  iJet.setP4(ALTuncorrectedP4);
  uncorrectedPt = iJet.pt();
//   std::cout<<iJet.currentJECLevel()<<" "<<iJet.currentJECSet()<<std::endl;

//   std::cout<<originalPt<<" "<<uncorrectedPt<<std::endl;
  bufferJets.push_back(iJet);
}
  
//clean from electrons 
for(std::vector<pat::Electron>::const_iterator iEle = selectedElectrons.begin(), ed = selectedElectrons.end(); iEle != ed; ++iEle ){
  pat::Electron Ele = *iEle;
  double maxDeltaR=0.4;
  double minDeltaR=maxDeltaR;
  double dR=999.0;
  int matchindex=-1;
  int counter=0;
  
  //find jet closes to electron
  for( std::vector<pat::Jet>::const_iterator it = bufferJets.begin(), ed = bufferJets.end(); it != ed; ++it ){
      pat::Jet iJet = *it;
      dR = reco::deltaR(Ele.eta(), Ele.phi(), iJet.eta(), iJet.phi());
      if(dR<minDeltaR){
        minDeltaR = dR;
        matchindex=counter;
        }
      counter++;
    }
    
  // now clean the closest jet from the electron and put it back with the rest
  counter=0;
  for( std::vector<pat::Jet>::const_iterator it = bufferJets.begin(), ed = bufferJets.end(); it != ed; ++it ){
      pat::Jet iJet = *it;
      if(matchindex==counter){
        math::XYZTLorentzVector original = iJet.p4();
        original -= Ele.p4();
        iJet.setP4(original);
       }
      if(iJet.pt()>0.0 && iJet.energy()>0.0){
        cleanEleJets.push_back(iJet);
       } 
      counter++;
   }
   bufferJets.clear();
   for( std::vector<pat::Jet>::const_iterator it = cleanEleJets.begin(), ed = cleanEleJets.end(); it != ed; ++it ){
      bufferJets.push_back(*it);
   }
   cleanEleJets.clear();
}
for( std::vector<pat::Jet>::const_iterator it = bufferJets.begin(), ed = bufferJets.end(); it != ed; ++it ){
  cleanEleJets.push_back(*it);
}
//now we should have the jets cleaned from the electrons
//clean from electrons 

bufferJets.clear();
for( std::vector<pat::Jet>::const_iterator it = cleanEleJets.begin(), ed = cleanEleJets.end(); it != ed; ++it ){
  bufferJets.push_back(*it);
}

for(std::vector<pat::Muon>::const_iterator iMuon = selectedMuons.begin(), ed = selectedMuons.end(); iMuon != ed; ++iMuon ){
  pat::Muon Muon = *iMuon;
  double maxDeltaR=0.4;
  double minDeltaR=maxDeltaR;
  double dR=999.0;
  int matchindex=-1;
  int counter=0;
  
  //find jet closes to muon
  for( std::vector<pat::Jet>::const_iterator it = bufferJets.begin(), ed = bufferJets.end(); it != ed; ++it ){
      pat::Jet iJet = *it;
      dR = reco::deltaR(Muon.eta(), Muon.phi(), iJet.eta(), iJet.phi());
      if(dR<minDeltaR){
        minDeltaR = dR;
        matchindex=counter;
        }
      counter++;
    }
    
  // now clean the closest jet from the muon and put it back with the rest
  counter=0;
  for( std::vector<pat::Jet>::const_iterator it = bufferJets.begin(), ed = bufferJets.end(); it != ed; ++it ){
      pat::Jet iJet = *it;
      if(matchindex==counter){
        math::XYZTLorentzVector original = iJet.p4();
        original -= Muon.p4();
        iJet.setP4(original);
       }
      if(iJet.pt()>0.0 && iJet.energy()>0.0){
        cleanMuonJets.push_back(iJet);
       } 
      counter++;
   }
   bufferJets.clear();
   for( std::vector<pat::Jet>::const_iterator it = cleanMuonJets.begin(), ed = cleanMuonJets.end(); it != ed; ++it ){
      bufferJets.push_back(*it);
   }
   cleanMuonJets.clear();
}
for( std::vector<pat::Jet>::const_iterator it = bufferJets.begin(), ed = bufferJets.end(); it != ed; ++it ){
  cleanMuonJets.push_back(*it);
  std::cout<<it->pt()<<std::endl;
}

//now correct the jets again
//using the PHYS14_25_V2 corrections i hope :)
/*  "ak4PFchsL1L2L3"*/

const JetCorrector* jetCorrector = JetCorrector::getJetCorrector("ak4PFchsL1L2L3",input.setup);
correctedJets.clear();
  
std::cout<<"setup the corrector"<<std::endl;
for( std::vector<pat::Jet>::const_iterator it = cleanMuonJets.begin(), ed = cleanMuonJets.end(); it != ed; ++it ){
  pat::Jet iJet = *it;
  double jec = jetCorrector->correction(iJet, input.edmevent, input.setup );
  std::cout<<"uncorrected "<<jec<<" "<<iJet.pt()<<std::endl;
  iJet.scaleEnergy(jec);
  std::cout<<"corrected "<<iJet.pt()<<std::endl;
  std::cout<<iJet.currentJECLevel()<<" "<<iJet.currentJECSet()<<" "<<std::endl;

  correctedJets.push_back(iJet);

//   double uncorrectedPt = iJet.pt();
//   math::XYZTLorentzVector correctedP4 = iJet.correctedP4("L1FastJetL2RelativeL3Absolute","","PHYS14_25_V2");
//   iJet.setP4(correctedP4);
//   pat::Jet newJet = iJet.correctedJet("L3Absolute","none","patJetCorrFactors");
//   double correctedPt = newJet.pt();
//   std::cout<<uncorrectedPt<<" "<<correctedPt<<std::endl;
//   bufferJets.push_back(iJet);
  
//   for(unsigned int i=0; i<iJet.availableJECSets().size(); i++){
//     std::cout<<iJet.availableJECSets()[i]<<std::endl;
//   }
//   for(unsigned int i=0; i<iJet.availableJECLevels().size(); i++){
//     std::cout<<iJet.availableJECLevels("patJetCorrFactors")[i]<<std::endl;
//   }
}

// std::cout<<"The Parameter Set"<<std::endl;

// std::cout<<Config.dump()<<std::endl;;

//now sort the jets by pt
std::sort(correctedJets.begin(), correctedJets.end(), BoostedUtils::FirstJetIsHarder);
std::cout<<correctedJets.at(0).pt()<<" "<<correctedJets.at(1).pt()<<" "<<correctedJets.at(2).pt()<<std::endl;

//now select only the good jets  
selectedJets.clear();
for( std::vector<pat::Jet>::const_iterator it = correctedJets.begin(), ed = correctedJets.end(); it != ed; ++it ){
  pat::Jet iJet = *it;

  bool isselected=false;
  isselected=(iJet.pt()>25 && abs(iJet.eta())<2.4 && iJet.neutralHadronEnergyFraction()<0.99 && iJet.chargedHadronEnergyFraction()>0.0 && iJet.chargedMultiplicity()>0.0 && iJet.chargedEmEnergyFraction()<0.99 && iJet.neutralEmEnergyFraction()<0.99 && iJet.numberOfDaughters()>1 );
  if(isselected){
    selectedJets.push_back(iJet);
    }
}

//get the btagged jets
taggedJets.clear();
for( std::vector<pat::Jet>::const_iterator it = selectedJets.begin(), ed = selectedJets.end(); it != ed; ++it ){
  pat::Jet iJet = *it;

  bool istagged=false;
  double workingPoint=0.814;
  istagged=(iJet.bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags") > workingPoint);
  if(istagged){
    taggedJets.push_back(iJet);
    }
}



//----------------------------------------------------------------------------------
//do the topjets
std::vector<boosted::HEPTopJet> selectedTopJets;
for( std::vector<boosted::HEPTopJet>::const_iterator it = input.selectedHEPTopJets.begin(), ed = input.selectedHEPTopJets.end(); it != ed; ++it ){
  boosted::HEPTopJet iJet = *it;
  bool passesCuts=false;
  bool passesSubCuts=false;
  bool hasTopTag=false;
  
  passesCuts=(iJet.fatjet.pt()>250 && abs(iJet.fatjet.eta())<1.8 );
  passesSubCuts = (iJet.nonW.pt()>20 && abs(iJet.nonW.eta())<2.5 && iJet.W1.pt()>20 && abs(iJet.W1.eta())<2.5 && iJet.W2.pt()>20 && abs(iJet.W2.eta())<2.5 );

  std::vector<pat::Jet> subjets;
  subjets.push_back(iJet.nonW);
  subjets.push_back(iJet.W1);
  subjets.push_back(iJet.W2);
  
  std::sort(subjets.begin(), subjets.end(), BoostedUtils::FirstJetIsHarder);
  vector<math::XYZTLorentzVector> topvecs;
  topvecs.push_back(subjets.at(0).p4());
  topvecs.push_back(subjets.at(1).p4());
  topvecs.push_back(subjets.at(2).p4());

  float m12=-99;
  float m23=-99;
  float m13=-99;
  float m123=-99;
  if(topvecs.size()==3){
    m12=(topvecs[0]+topvecs[1]).M();
    m13=(topvecs[0]+topvecs[2]).M();
    m23=(topvecs[1]+topvecs[2]).M();
    m123=(topvecs.at(0)+topvecs.at(1)+topvecs.at(2)).M();
  }
  
  bool tagOne=false;
  bool tagTwo=false;
  bool tagThree=false;
  double fW = 0.15;
  double mT = 172.3;
  double mW = 80.4;
  double Rmin = (1.0-fW)*mW/mT;
  double Rmax = (1.0+fW)*mW/mT;

  double y1 = 1.0+pow(m13/m12 ,2);
    double y2 = 1.0+pow(m12/m13 ,2);
  double x = 1.0-pow(m23/m123 ,2);

  tagOne = ( atan(m23/m123)>0.2 && atan(m23/m123)<1.3 && Rmin < m23/m123 && m23/m123 < Rmax);
  
  tagTwo = ( pow(Rmin,2)*y1 < x && pow(Rmax,2)*y1 > x && m23/m123 > 0.35 );
  
  tagThree = ( pow(Rmin,2)*y2 < x && pow(Rmax,2)*y2 > x && m23/m123 > 0.35 );

  hasTopTag = (tagOne || tagTwo || tagThree );
  if(hasTopTag && passesCuts && passesSubCuts ){
    selectedTopJets.push_back(iJet);
    }
}


//----------------------------------------------------------------------------------
//do the higgsjets

std::vector<boosted::SubFilterJet> selectedHiggsJets;
for( std::vector<boosted::SubFilterJet>::const_iterator it = input.selectedSubFilterJets.begin(), ed =        input.selectedSubFilterJets.end(); it != ed; ++it ){
  boosted::SubFilterJet iJet = *it;

  
  bool passesCuts=false;
  bool hasTwoTaggedSubjets=false;
  
  passesCuts = ( iJet.fatjet.pt()>250 && abs(iJet.fatjet.eta())<1.8 );
  
  double workingPoint=0.814;

  std::vector<pat::Jet> taggedsubjets;
  for(size_t i=0; i< iJet.filterjets.size(); i++){
    if( iJet.filterjets.at(i).pt()>20 && abs(iJet.filterjets.at(i).eta())<2.5 && iJet.filterjets.at(i).bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags") > workingPoint ){
      taggedsubjets.push_back(iJet.filterjets.at(i));
    }
  }
  
  hasTwoTaggedSubjets = (taggedsubjets.size()>=2);
  if(passesCuts && hasTwoTaggedSubjets){
    selectedHiggsJets.push_back(iJet);
    }
  
}
    
//----------------------------------------------------------------------------------
  // now write the numbers that should be dumped
 
  int run=-99;
  int lumi=-99;
  int event=-99;
  float lep1_pt=-99;
  float lep1_eta=-99;
  float lep1_phi=-99;
  float jet1_pt=-99;
  float jet2_pt=-99;
  float jet3_pt=-99; 
  float jet4_pt=-99;
  float jet1_CSVv2=-99;
  float jet2_CSVv2=-99;
  float jet3_CSVv2=-99;
  float jet4_CSVv2=-99;
  int n_jets=-99;
  int n_btags=-99;
  int n_toptags=-99; 
  int n_higgstags=-99;
  
  run = int(input.event.run);
  lumi = int(input.event.lumiBlock);
  event = int(input.event.evt);
  
  // not clear what lep1 is
  // do we need to sort ele+mu by pt?
  if(doElectrons && selectedElectrons.size()>0){
    lep1_pt=selectedElectrons.at(0).pt();
    lep1_eta=selectedElectrons.at(0).eta();
    lep1_phi=selectedElectrons.at(0).phi();
  }
  else if(selectedMuons.size()>0){
   lep1_pt=selectedMuons.at(0).pt();
   lep1_eta=selectedMuons.at(0).eta();
   lep1_phi=selectedMuons.at(0).phi();
  }
  
  if(selectedJets.size()>0){
  jet1_pt=selectedJets.at(0).pt();
  jet1_CSVv2=selectedJets.at(0).bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags");
  }
  
  if(selectedJets.size()>1){
  jet2_pt=selectedJets.at(1).pt();
  jet2_CSVv2=selectedJets.at(1).bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags");
  }
  
  if(selectedJets.size()>2){
  jet3_pt=selectedJets.at(2).pt();
  jet3_CSVv2=selectedJets.at(2).bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags");
  }
  
  if(selectedJets.size()>3){
  jet4_pt=selectedJets.at(3).pt();
  jet4_CSVv2=selectedJets.at(3).bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags");
  }
  
  n_jets=int(selectedJets.size());
  n_btags=int(taggedJets.size());
  
  
  n_toptags = int(selectedTopJets.size());
  n_higgstags = int(selectedHiggsJets.size());
  // dump
  printf("%6d %8d %10d   %6.2f %+4.2f %+4.2f   %6.2f %6.2f %6.2f %6.2f   %+7.3f %+7.3f %+7.3f %+7.3f   %2d  %2d   %2d  %2d\n",
	 run, lumi, event,
	 lep1_pt, lep1_eta, lep1_phi,
	 jet1_pt, jet2_pt, jet3_pt, jet4_pt,
	 jet1_CSVv2, jet2_CSVv2, jet3_CSVv2, jet4_CSVv2,
	 n_jets, n_btags,
	 n_toptags, n_higgstags);


  // make event selection
  string outfile;
  
  if(!hasGoodVertex) return false;
  else cutflow.EventSurvivedStep("vertex selection");
  
  if(!hasTriggered) return false;
  else{ cutflow.EventSurvivedStep("single lepton trigger");
    if(doElectrons) outfile="KIT_sync_ele_1.txt";
    else outfile="KIT_sync_mu_1.txt";
    FILE* pFile;
    pFile=fopen(outfile.c_str(),"a");
    if(pFile!=NULL)
      {
      fprintf(pFile, "%6d %8d %10d   %6.2f %+4.2f %+4.2f   %6.2f %6.2f %6.2f %6.2f   %+7.3f %+7.3f %+7.3f %+7.3f   %2d  %2d   %2d  %2d\n",
      run, lumi, event,
      lep1_pt, lep1_eta, lep1_phi,
      jet1_pt, jet2_pt, jet3_pt, jet4_pt,
      jet1_CSVv2, jet2_CSVv2, jet3_CSVv2, jet4_CSVv2,
      n_jets, n_btags,
      n_toptags, n_higgstags);
      fclose (pFile);
      } 
    }
      
  bool singleLepton=false;
  if(doElectrons){if(selectedElectrons.size()==1)singleLepton=true;}
  else{if(selectedMuons.size()==1)singleLepton=true;}
  
  if(!singleLepton) return false;
  else{ cutflow.EventSurvivedStep("== 1 lepton");
    if(doElectrons) outfile="KIT_sync_ele_2.txt";
    else outfile="KIT_sync_mu_2.txt";
    FILE* pFile;
    pFile=fopen(outfile.c_str(),"a");
    if(pFile!=NULL)
      {
      fprintf(pFile, "%6d %8d %10d   %6.2f %+4.2f %+4.2f   %6.2f %6.2f %6.2f %6.2f   %+7.3f %+7.3f %+7.3f %+7.3f   %2d  %2d   %2d  %2d\n",
      run, lumi, event,
      lep1_pt, lep1_eta, lep1_phi,
      jet1_pt, jet2_pt, jet3_pt, jet4_pt,
      jet1_CSVv2, jet2_CSVv2, jet3_CSVv2, jet4_CSVv2,
      n_jets, n_btags,
      n_toptags, n_higgstags);
      fclose (pFile);
      } 
    }
    
  bool noOtherLepton=false;
  if(doElectrons){if(selectedMuons.size()==0)noOtherLepton=true;}
  else{if(selectedElectrons.size()==0)noOtherLepton=true;}
  if(!noOtherLepton) return false;
  else{ cutflow.EventSurvivedStep("== 0 leptons different flavor");
    if(doElectrons) outfile="KIT_sync_ele_3.txt";
    else outfile="KIT_sync_mu_3.txt";
    FILE* pFile;
    pFile=fopen(outfile.c_str(),"a");
    if(pFile!=NULL)
      {
      fprintf(pFile, "%6d %8d %10d   %6.2f %+4.2f %+4.2f   %6.2f %6.2f %6.2f %6.2f   %+7.3f %+7.3f %+7.3f %+7.3f   %2d  %2d   %2d  %2d\n",
      run, lumi, event,
      lep1_pt, lep1_eta, lep1_phi,
      jet1_pt, jet2_pt, jet3_pt, jet4_pt,
      jet1_CSVv2, jet2_CSVv2, jet3_CSVv2, jet4_CSVv2,
      n_jets, n_btags,
      n_toptags, n_higgstags);
      fclose (pFile);
      } 
    }
    
  if(selectedJets.size()<4) return false;
  else{ cutflow.EventSurvivedStep(">= 4 jets");
  if(doElectrons) outfile="KIT_sync_ele_4.txt";
    else outfile="KIT_sync_mu_4.txt";
    FILE* pFile;
    pFile=fopen(outfile.c_str(),"a");
    if(pFile!=NULL)
      {
      fprintf(pFile, "%6d %8d %10d   %6.2f %+4.2f %+4.2f   %6.2f %6.2f %6.2f %6.2f   %+7.3f %+7.3f %+7.3f %+7.3f   %2d  %2d   %2d  %2d\n",
      run, lumi, event,
      lep1_pt, lep1_eta, lep1_phi,
      jet1_pt, jet2_pt, jet3_pt, jet4_pt,
      jet1_CSVv2, jet2_CSVv2, jet3_CSVv2, jet4_CSVv2,
      n_jets, n_btags,
      n_toptags, n_higgstags);
      fclose (pFile);
      } 
    }
    
    
  if(taggedJets.size()<2) return false;
  else{ cutflow.EventSurvivedStep(">= 2 b-tags");
  if(doElectrons) outfile="KIT_sync_ele_5.txt";
    else outfile="KIT_sync_mu_5.txt";
    FILE* pFile;
    pFile=fopen(outfile.c_str(),"a");
    if(pFile!=NULL)
      {
      fprintf(pFile, "%6d %8d %10d   %6.2f %+4.2f %+4.2f   %6.2f %6.2f %6.2f %6.2f   %+7.3f %+7.3f %+7.3f %+7.3f   %2d  %2d   %2d  %2d\n",
      run, lumi, event,
      lep1_pt, lep1_eta, lep1_phi,
      jet1_pt, jet2_pt, jet3_pt, jet4_pt,
      jet1_CSVv2, jet2_CSVv2, jet3_CSVv2, jet4_CSVv2,
      n_jets, n_btags,
      n_toptags, n_higgstags);
      fclose (pFile);
      } 
    }
    
  if(selectedTopJets.size()<1) return false;
  else{ cutflow.EventSurvivedStep(">= 1 top tagged jet");
  if(doElectrons) outfile="KIT_sync_ele_6.txt";
    else outfile="KIT_sync_mu_6.txt";
    FILE* pFile;
    pFile=fopen(outfile.c_str(),"a");
    if(pFile!=NULL)
      {
      fprintf(pFile, "%6d %8d %10d   %6.2f %+4.2f %+4.2f   %6.2f %6.2f %6.2f %6.2f   %+7.3f %+7.3f %+7.3f %+7.3f   %2d  %2d   %2d  %2d\n",
      run, lumi, event,
      lep1_pt, lep1_eta, lep1_phi,
      jet1_pt, jet2_pt, jet3_pt, jet4_pt,
      jet1_CSVv2, jet2_CSVv2, jet3_CSVv2, jet4_CSVv2,
      n_jets, n_btags,
      n_toptags, n_higgstags);
      fclose (pFile);
      } 
    }
    
  if(selectedHiggsJets.size()<1) return false;
  else{ cutflow.EventSurvivedStep(">= 1 Higgs jet");
  if(doElectrons) outfile="KIT_sync_ele_7.txt";
    else outfile="KIT_sync_mu_7.txt";
    FILE* pFile;
    pFile=fopen(outfile.c_str(),"a");
    if(pFile!=NULL)
      {
      fprintf(pFile, "%6d %8d %10d   %6.2f %+4.2f %+4.2f   %6.2f %6.2f %6.2f %6.2f   %+7.3f %+7.3f %+7.3f %+7.3f   %2d  %2d   %2d  %2d\n",
      run, lumi, event,
      lep1_pt, lep1_eta, lep1_phi,
      jet1_pt, jet2_pt, jet3_pt, jet4_pt,
      jet1_CSVv2, jet2_CSVv2, jet3_CSVv2, jet4_CSVv2,
      n_jets, n_btags,
      n_toptags, n_higgstags);
      fclose (pFile);
      } 
    }
    
  return true;
  
}


