#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

using namespace std;


std::string BoostedUtils::GetAnalyzerPath(){
  char* cpath;
  cpath = getenv("CMSSW_BASE");
  std::string path = cpath;
  
  if (path.size() == 0){
    cerr << "could not find path of exe" << endl;
    return path;
  }
  else
    return path+"/src/BoostedTTH/BoostedAnalyzer";
}


TLorentzVector BoostedUtils::GetTLorentzVector(const math::XYZTLorentzVector& vec){
  
  TLorentzVector result(vec.Px(),vec.Py(),vec.Pz(),vec.E());
  
  return result;
  
}


math::XYZTLorentzVector BoostedUtils::GetXYZTLorentzVector(const TLorentzVector& vec){
  
  math::XYZTLorentzVector result(vec.Px(),vec.Py(),vec.Pz(),vec.E());
  
  return result;
  
}


bool BoostedUtils::FirstIsLarger(float val1,float val2){
  return val1 > val2;
}


bool BoostedUtils::FirstIsHarder(math::XYZTLorentzVector vec1,math::XYZTLorentzVector vec2){
  return vec1.Pt()>vec2.Pt();
}


bool BoostedUtils::FirstJetIsHarder(pat::Jet jet1, pat::Jet jet2){
  return jet1.pt()>jet2.pt();
}


bool BoostedUtils::FirstHasHigherCSV(pat::Jet jet1,pat::Jet jet2){
  return jet1.bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags") > jet2.bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags");
}

bool BoostedUtils::FirstHasHigherCSVold(pat::Jet jet1,pat::Jet jet2){
  return jet1.bDiscriminator("combinedSecondaryVertexBJetTags") > jet2.bDiscriminator("combinedSecondaryVertexBJetTags");
}


float BoostedUtils::DeltaEta(const math::XYZTLorentzVector& vec1,const math::XYZTLorentzVector& vec2){
  if(vec1.Pt()<0.001||vec2.Pt()<0.001) return -2;
  
  float deta = fabs(vec1.Eta()-vec2.Eta());
  
  return deta;
}


float BoostedUtils::DeltaEta(const pat::Jet& jet1,const pat::Jet& jet2){
  if(jet1.pt()<0.001||jet2.pt()<0.001) return -2;
  
  math::XYZTLorentzVector vec1 = jet1.p4();
  math::XYZTLorentzVector vec2 = jet2.p4();
  
  float deta = fabs(vec1.Eta()-vec2.Eta());
  
  return deta;
}


float BoostedUtils::DeltaPhi(const math::XYZTLorentzVector& vec1,const math::XYZTLorentzVector& vec2){
  if(vec1.Pt()<0.001||vec2.Pt()<0.001) return -2;
  
  float dphi = ROOT::Math::VectorUtil::DeltaPhi(vec1,vec2);
  
  return fabs(dphi);
}


float BoostedUtils::DeltaPhi(const pat::Jet& jet1,const pat::Jet& jet2){
  if(jet1.pt()<0.001||jet2.pt()<0.001) return -2;
  
  math::XYZTLorentzVector vec1 = jet1.p4();
  math::XYZTLorentzVector vec2 = jet2.p4();
  
  float dphi = ROOT::Math::VectorUtil::DeltaPhi(vec1,vec2);
  
  return fabs(dphi);
}


float BoostedUtils::DeltaR(const math::XYZTLorentzVector& vec1,const math::XYZTLorentzVector& vec2){
  if(vec1.Pt()<0.001||vec2.Pt()<0.001) return -2;
  
  float dr = ROOT::Math::VectorUtil::DeltaR(vec1,vec2);
  
  return dr;
}


float BoostedUtils::DeltaR(const pat::Jet& jet1,const pat::Jet& jet2){
  if(jet1.pt()<0.001||jet2.pt()<0.001) return -2;
  
  math::XYZTLorentzVector vec1 = jet1.p4();
  math::XYZTLorentzVector vec2 = jet2.p4();
  
  float dr = ROOT::Math::VectorUtil::DeltaR(vec1,vec2);
  
  return dr;
}


float BoostedUtils::DeltaKt(const math::XYZTLorentzVector& vec1,const math::XYZTLorentzVector& vec2){
  if(vec1.Pt()<0.001 || vec2.Pt()<0.001) return -2;
  
  float dr = ROOT::Math::VectorUtil::DeltaR(vec1,vec2);
  float ptmin=min(vec1.Pt(),vec2.Pt());
  
  return sqrt(dr*dr*ptmin*ptmin);
}


float BoostedUtils::DeltaKt(const pat::Jet& jet1,const pat::Jet& jet2){
  if(jet1.pt()<0.001||jet2.pt()<0.001) return -2;
  
  math::XYZTLorentzVector vec1 = jet1.p4();
  math::XYZTLorentzVector vec2 = jet2.p4();
  
  float dr = ROOT::Math::VectorUtil::DeltaR(vec1,vec2);
  float ptmin=min(vec1.Pt(),vec2.Pt());
  
  return sqrt(dr*dr*ptmin*ptmin);
}


float BoostedUtils::CosThetaStar(const math::XYZTLorentzVector& vec1, const math::XYZTLorentzVector& vec2){
  if(vec1.Pt()<0.001||vec2.Pt()<0.001) return -2;
  
  TLorentzVector sumVec = BoostedUtils::GetTLorentzVector(vec1+vec2);
  TVector3 cmboost = -sumVec.BoostVector();
  
  TLorentzVector boostedvec1 = GetTLorentzVector(vec1);
  boostedvec1.Boost(cmboost);
  
  return cos( sumVec.Angle(boostedvec1.Vect()) );
}


float BoostedUtils::CosThetaCM(const math::XYZTLorentzVector& vec,const math::XYZTLorentzVector& boostVec){
  if(vec.Pt()<0.001||boostVec.Pt()<0.001) return -2;
  
  TLorentzVector vec_ = GetTLorentzVector(vec);
  TLorentzVector boostVec_ = GetTLorentzVector(boostVec);
  
  TVector3 zBoost = TVector3(0,0,-boostVec_.BoostVector().Pz());
  TLorentzVector boostedVec = vec_;
  boostedVec.Boost(zBoost);
  float theta = boostedVec.Theta();
  return TMath::Cos(theta);
}


std::vector<math::XYZTLorentzVector> BoostedUtils::GetGenParticleVecs(const std::vector<reco::GenParticle>& genParticles){
  std::vector<math::XYZTLorentzVector> genParticleVecs;
  
  for(std::vector<reco::GenParticle>::const_iterator itPart=genParticles.begin();itPart!=genParticles.end();++itPart){
    genParticleVecs.push_back(itPart->p4());
  }
  
  return genParticleVecs;
}


bool BoostedUtils::MCContainsTTbar(const std::vector<reco::GenParticle>& genParticles){
  bool foundT=false;
  bool foundTbar=false;
  for(size_t i=0; i<genParticles.size();i++){
    if(genParticles[i].pdgId()==6) foundT=true;
    if(genParticles[i].pdgId()==-6) foundTbar=true;
  }
  return foundT&&foundTbar;
}


bool BoostedUtils::MCContainsHiggs(const std::vector<reco::GenParticle>& genParticles){
  for(size_t i=0; i<genParticles.size();i++){
    if(genParticles[i].pdgId()==25) return true;
  }
  return false;
}


void BoostedUtils::GetttHMCParticles(const std::vector<reco::GenParticle>& genParticles, std::vector<reco::GenParticle>& tophad, std::vector<reco::GenParticle>& whad, std::vector<reco::GenParticle>& bhad, std::vector<reco::GenParticle>& q1, std::vector<reco::GenParticle>& q2, std::vector<reco::GenParticle>& toplep, std::vector<reco::GenParticle>& wlep, std::vector<reco::GenParticle>& blep, std::vector<reco::GenParticle>& lep, std::vector<reco::GenParticle>& nu, reco::GenParticle& higgs, reco::GenParticle& b1, reco::GenParticle& b2){
  std::vector<reco::GenParticle> leptonsFromWplus;
  std::vector<reco::GenParticle> leptonsFromWminus;
  std::vector<reco::GenParticle> quarksFromWplus;
  std::vector<reco::GenParticle> quarksFromWminus;
  std::vector<reco::GenParticle> quarksFromT;
  std::vector<reco::GenParticle> quarksFromTbar;
  std::vector<reco::GenParticle> bquarksFromHiggs;
  reco::GenParticle Wplus;
  reco::GenParticle Wminus;
  reco::GenParticle top;
  reco::GenParticle topbar;
  
  for(std::vector<reco::GenParticle>::const_iterator itPart = genParticles.begin();itPart != genParticles.end();itPart++) {
    if(itPart->numberOfMothers()==0) continue;
    if(itPart->mother()->pdgId()==6    && abs(itPart->pdgId())<6) quarksFromT.push_back(*itPart);
    if(itPart->mother()->pdgId()==-6   && abs(itPart->pdgId())<6) quarksFromTbar.push_back(*itPart);
    if(itPart->mother()->pdgId()==24   && abs(itPart->pdgId())<6) quarksFromWplus.push_back(*itPart);
    if(itPart->mother()->pdgId()==-24  && abs(itPart->pdgId())<6) quarksFromWminus.push_back(*itPart);
    if(itPart->mother()->pdgId()==24   && abs(itPart->pdgId())>=11&&abs(itPart->pdgId())<=16) leptonsFromWplus.push_back(*itPart);
    if(itPart->mother()->pdgId()==-24  && abs(itPart->pdgId())>=11&&abs(itPart->pdgId())<=16) leptonsFromWminus.push_back(*itPart);
    if(itPart->mother()->pdgId()==25   && abs(itPart->pdgId())==5) bquarksFromHiggs.push_back(*itPart);
    
    if(itPart->mother()->pdgId()==6    && itPart->pdgId()==24)    Wplus = *itPart;
    if(itPart->mother()->pdgId()==-6   && itPart->pdgId()==-24)   Wminus = *itPart;
    
    if(itPart->pdgId()==25 || fabs(itPart->pdgId())==6){
      bool lastHiggs = true;
      bool lastTop = true;
      bool lastTopBar = true;

      for(size_t iDaughter = 0;iDaughter<itPart->numberOfDaughters();++iDaughter){
        if(itPart->daughter(iDaughter)->pdgId()==25) lastHiggs = false;
        if(itPart->daughter(iDaughter)->pdgId()==6) lastTop = false;
        if(itPart->daughter(iDaughter)->pdgId()==-6) lastTopBar = false;
      }

      if(lastHiggs  && itPart->pdgId()==25) higgs = *itPart;
      if(lastTop    && itPart->pdgId()==6)  top = *itPart;
      if(lastTopBar && itPart->pdgId()==-6) topbar = *itPart; 
    }
  }
  
  if(leptonsFromWplus.size()==2 && quarksFromT.size()>=1){
    toplep.push_back(top);
    wlep.push_back(Wplus);
    blep.push_back(quarksFromT[0]);
    if(leptonsFromWplus[0].pdgId()%2!=0){
      lep.push_back(leptonsFromWplus[0]);
      nu.push_back(leptonsFromWplus[1]);
    }
    else{
      lep.push_back(leptonsFromWplus[1]);
      nu.push_back(leptonsFromWplus[0]);
    }
  }
  if(leptonsFromWminus.size()==2 && quarksFromTbar.size()>=1){
    toplep.push_back(topbar);
    wlep.push_back(Wminus);
    blep.push_back(quarksFromTbar[0]);
    if(leptonsFromWminus[0].pdgId()%2!=0){
      lep.push_back(leptonsFromWminus[0]);
      nu.push_back(leptonsFromWminus[1]);
    }
    else{
      lep.push_back(leptonsFromWminus[1]);
      nu.push_back(leptonsFromWminus[0]);
    }
  }
  if(quarksFromWplus.size()==2 && quarksFromT.size()>=1){
    tophad.push_back(top);
    whad.push_back(Wplus);
    bhad.push_back(quarksFromT[0]);
    q1.push_back(quarksFromWplus[0]);
    q2.push_back(quarksFromWplus[1]);
  }
  if(quarksFromWminus.size()==2 && quarksFromTbar.size()>=1){
    tophad.push_back(topbar);
    whad.push_back(Wminus);
    bhad.push_back(quarksFromTbar[0]);
    q1.push_back(quarksFromWminus[0]);
    q2.push_back(quarksFromWminus[1]);
  }
  if(bquarksFromHiggs.size()==2){
    b1 = bquarksFromHiggs[0];
    b2 = bquarksFromHiggs[1];
  }  
}


void BoostedUtils::GetttHMCVecs(const std::vector<reco::GenParticle>& genParticles, std::vector<math::XYZTLorentzVector>& tophadvecs, std::vector<math::XYZTLorentzVector>& whadvecs, std::vector<math::XYZTLorentzVector>& bhadvecs, std::vector<math::XYZTLorentzVector>& q1vecs, std::vector<math::XYZTLorentzVector>& q2vecs, std::vector<math::XYZTLorentzVector>& toplepvecs, std::vector<math::XYZTLorentzVector>& wlepvecs, std::vector<math::XYZTLorentzVector>& blepvecs, std::vector<math::XYZTLorentzVector>& lepvecs, std::vector<math::XYZTLorentzVector>& nuvecs, math::XYZTLorentzVector& higgsvec, math::XYZTLorentzVector& b1vec, math::XYZTLorentzVector& b2vec){
  
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
  reco::GenParticle b1;
  reco::GenParticle b2;
  
  GetttHMCParticles(genParticles,tophad,whad,bhad,q1,q2,toplep,wlep,blep,lep,nu,higgs,b1,b2);
  
  tophadvecs = GetGenParticleVecs(tophad);
  whadvecs = GetGenParticleVecs(whad);
  bhadvecs = GetGenParticleVecs(bhad);
  q1vecs = GetGenParticleVecs(q1);
  q2vecs = GetGenParticleVecs(q2);
  toplepvecs = GetGenParticleVecs(toplep);
  wlepvecs = GetGenParticleVecs(wlep);
  blepvecs = GetGenParticleVecs(blep);
  lepvecs = GetGenParticleVecs(lep);
  nuvecs = GetGenParticleVecs(nu);
  higgsvec = higgs.p4();
  b1vec = b1.p4();
  b2vec = b2.p4();
}


bool BoostedUtils::IsAnyTriggerBitFired(const std::vector<string> & targetTriggers, const edm::TriggerResults& triggerResults){
  
  // check to see if you passed the trigger by looping over the bits
  // looking for your bit
  // and see if it is 1
  
  for(vector<string>::const_iterator iTarget = targetTriggers.begin();iTarget != targetTriggers.end();iTarget++) {
    
    if(*iTarget == "None") return true;
    
    // if this is the right name and the bit is set to one
    int TriggerID = triggerResults.find(*iTarget);
    
    if(triggerResults.accept(TriggerID)==1) return true;
    
  }// end for each target
  
  return false;
  
}


std::vector<math::XYZTLorentzVector> BoostedUtils::GetLepVecs(const std::vector<pat::Electron>& selectedElectrons, const std::vector<pat::Muon> selectedMuons){
  
  std::vector<math::XYZTLorentzVector> leptonVecs;
  
  for(std::vector<pat::Electron>::const_iterator itEle = selectedElectrons.begin(); itEle != selectedElectrons.end(); ++itEle){
    leptonVecs.push_back(itEle->p4());
  }
  for(std::vector<pat::Muon>::const_iterator itMu = selectedMuons.begin(); itMu != selectedMuons.end(); ++itMu){
    leptonVecs.push_back(itMu->p4());
  }
  
  std::sort(leptonVecs.begin(), leptonVecs.end(),BoostedUtils::FirstIsHarder);
  
  return leptonVecs;
  
} 


math::XYZTLorentzVector BoostedUtils::GetPrimLepVec(const std::vector<pat::Electron>& selectedElectrons,const std::vector<pat::Muon> selectedMuons){
  
  std::vector<math::XYZTLorentzVector> leptonVecs = GetLepVecs(selectedElectrons,selectedMuons);
  
  if(leptonVecs.size()==0){
    std::cerr<< "No PrimLep Found!" << std::endl;
    return math::XYZTLorentzVector();
  }
  
  return leptonVecs[0];
}


void BoostedUtils::GetNuVecs(const math::XYZTLorentzVector& lepvec, const TVector2& metvec, math::XYZTLorentzVector& nu1, math::XYZTLorentzVector& nu2){
  
  double mu = (80.4*80.4)/2 + metvec.Px()*lepvec.Px() + metvec.Py()*lepvec.Py();
  double a = (mu*lepvec.Pz())/(lepvec.E()*lepvec.E() - lepvec.Pz()*lepvec.Pz());
  double a2 = TMath::Power(a, 2);
  double b = (TMath::Power(lepvec.E(), 2.)*metvec.Mod() - TMath::Power(mu, 2.)) / (TMath::Power(lepvec.E(), 2)- TMath::Power(lepvec.Pz(), 2));
  float pz1,pz2;
  
  if (a2-b < 0) { 
    pz1 = a;
    pz2 = a;
  } else {
    double root = sqrt(a2-b);
    pz1 = a + root;
    pz2 = a - root;
  }
  
  nu1.SetPxPyPzE(metvec.Px(),metvec.Py(),pz1,sqrt(metvec.Mod2()+pz1*pz1));
  nu2.SetPxPyPzE(metvec.Px(),metvec.Py(),pz2,sqrt(metvec.Mod2()+pz2*pz2));
}


vector<math::XYZTLorentzVector> BoostedUtils::GetJetVecs(const std::vector<pat::Jet>& jets){
  std::vector<math::XYZTLorentzVector> jetVecs;
  
  for(std::vector<pat::Jet>::const_iterator itJet=jets.begin();itJet!=jets.end();++itJet){
    jetVecs.push_back(itJet->p4());
  }
  
  return jetVecs;
}


boosted::SubFilterJetCollection BoostedUtils::GetSortedByPt(boosted::SubFilterJetCollection const &subfilterjets){
  boosted::SubFilterJetCollection result = subfilterjets;
  std::sort(result.begin(), result.end(),BoostedUtils::FirstFatJetIsHarder<boosted::SubFilterJet>);
  return result;
}


boosted::HEPTopJetCollection BoostedUtils::GetSortedByPt(boosted::HEPTopJetCollection const &heptopjets){
  boosted::HEPTopJetCollection result = heptopjets;
  std::sort(result.begin(), result.end(),BoostedUtils::FirstFatJetIsHarder<boosted::HEPTopJet>);
  return result;
}


bool BoostedUtils::PassesCSV(const pat::Jet& jet, const char workingPoint){
  
  float CSVLv2wp = 0.423;
  float CSVMv2wp = 0.814;
  float CSVTv2wp = 0.941;
  
  float csvValue = jet.bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags");
  
  switch(workingPoint){
    case 'L': if(csvValue > CSVLv2wp){ return true; } break;
    case 'M': if(csvValue > CSVMv2wp){ return true; } break;
    case 'T': if(csvValue > CSVTv2wp){ return true; } break;
    case '-': return true; break;
  }
  
  return false;
}


float BoostedUtils::GetClosestJetIDs(int& idJet1, int& idJet2, const std::vector<pat::Jet>& jets){
  
  float minDr = 9.;
  for(std::vector<pat::Jet>::const_iterator itJet1 = jets.begin();itJet1 != jets.end();++itJet1){
    for(std::vector<pat::Jet>::const_iterator itJet2 = itJet1+1;itJet2 != jets.end();++itJet2){
      math::XYZTLorentzVector jetVec1 = itJet1->p4();
      math::XYZTLorentzVector jetVec2 = itJet2->p4();
      
      if(BoostedUtils::DeltaR(jetVec1,jetVec2)<minDr){
	      idJet1 = itJet1 - jets.begin();
	      idJet2 = itJet2 - jets.begin();
	      minDr = BoostedUtils::DeltaR(jetVec1,jetVec2);
      }
    }
  }
  
  return minDr;
}


float BoostedUtils::GetClosestLepJetID(int& idJet, const math::XYZTLorentzVector& lepVec, const std::vector<pat::Jet>& jets){
  
  float minDr = 9.;
  for(std::vector<pat::Jet>::const_iterator itJet = jets.begin(); itJet != jets.end(); ++itJet){
    math::XYZTLorentzVector jetVec = itJet->p4();
    if(DeltaR(lepVec,jetVec)<minDr){
	    idJet = itJet - jets.begin();
	    minDr = DeltaR(lepVec,jetVec);
    }
  }

  return minDr;
}


float BoostedUtils::GetJetAverageJetEtaMax(const std::vector<pat::Jet>& jets1, const std::vector<pat::Jet>& jets2){
  int count=0;
  float avgval=0.;
  for(std::vector<pat::Jet>::const_iterator itJet1 = jets1.begin(); itJet1 != jets1.end(); ++itJet1){
    for(std::vector<pat::Jet>::const_iterator itJet2 = itJet1+1; itJet2 != jets1.end(); ++itJet2){
      avgval += itJet1->eta()-itJet2->eta();
      count++;
    }
  }
  avgval /= count;
  
  float imax = 0.;
  float etamax=0.;
  for(std::vector<pat::Jet>::const_iterator itJet = jets2.begin(); itJet != jets2.end(); ++itJet){
    imax = abs(itJet->eta()-avgval);
    if(imax>etamax) {
      etamax = imax;
    }
  }
  return etamax;
}


void BoostedUtils::GetFoxWolframMoments(std::vector<math::XYZTLorentzVector> jetVecs, float &h0, float &h1, float &h2, float &h3, float &h4) {
  //
  // Aplanarity and sphericity
  //
  
  float eVis = 0.0;
  for(std::vector<math::XYZTLorentzVector>::iterator itJetVec = jetVecs.begin();itJetVec != jetVecs.end();++itJetVec){
    eVis += itJetVec->energy();
  }
  h0 = 0.0;
  h1 = 0.0;
  h2 = 0.0;
  h3 = 0.0;
  h4 = 0.0;
  for(std::vector<math::XYZTLorentzVector>::iterator itJetVec1 = jetVecs.begin();itJetVec1 != jetVecs.end();++itJetVec1){
    for(std::vector<math::XYZTLorentzVector>::iterator itJetVec2 = itJetVec1+1;itJetVec2 != jetVecs.end();++itJetVec2){
      float costh = ROOT::Math::VectorUtil::CosTheta(*itJetVec1,*itJetVec2);
      float p0 = 1.0;
      float p1 = costh;
      float p2 = 0.5*(3.0*costh*costh - 1.0);
      float p3 = 0.5*(5.0*costh*costh - 3.0*costh);
      float p4 = 0.125*(35.0*costh*costh*costh*costh - 30.0*costh*costh + 3.0);
      float pipj = itJetVec1->P()*itJetVec2->P();
      h0 += (pipj/(eVis*eVis))*p0;
      h1 += (pipj/(eVis*eVis))*p1;
      h2 += (pipj/(eVis*eVis))*p2;
      h3 += (pipj/(eVis*eVis))*p3;
      h4 += (pipj/(eVis*eVis))*p4;
    }
  }
  return;
}


void BoostedUtils::GetAplanaritySphericity(math::XYZTLorentzVector leptonVec, math::XYZTLorentzVector metVec, std::vector<math::XYZTLorentzVector> jetVecs, float &aplanarity, float &sphericity){
  //
  // Aplanarity and sphericity
  //
  float mxx = leptonVec.Px()*leptonVec.Px() + metVec.Px()*metVec.Px();
  float myy = leptonVec.Py()*leptonVec.Py() + metVec.Py()*metVec.Py();
  float mzz = leptonVec.Pz()*leptonVec.Pz() + metVec.Pz()*metVec.Pz();
  float mxy = leptonVec.Px()*leptonVec.Py() + metVec.Px()*metVec.Py();
  float mxz = leptonVec.Px()*leptonVec.Pz() + metVec.Px()*metVec.Pz();
  float myz = leptonVec.Py()*leptonVec.Pz() + metVec.Px()*metVec.Pz();
  
  for(std::vector<math::XYZTLorentzVector>::iterator itJetVec=jetVecs.begin();itJetVec!=jetVecs.end();++itJetVec){
    mxx += itJetVec->Px()*itJetVec->Px();
    myy += itJetVec->Py()*itJetVec->Py();
    mzz += itJetVec->Pz()*itJetVec->Pz();
    mxy += itJetVec->Px()*itJetVec->Py();
    mxz += itJetVec->Px()*itJetVec->Pz();
    myz += itJetVec->Py()*itJetVec->Pz();
  }
  float sum = mxx + myy + mzz;
  mxx /= sum;
  myy /= sum;
  mzz /= sum;
  mxy /= sum;
  mxz /= sum;
  myz /= sum;
  
  TMatrix tensor(3,3);
  tensor(0,0) = mxx;
  tensor(1,1) = myy;
  tensor(2,2) = mzz;
  tensor(0,1) = mxy;
  tensor(1,0) = mxy;
  tensor(0,2) = mxz;
  tensor(2,0) = mxz;
  tensor(1,2) = myz;
  tensor(2,1) = myz;
  TVector eigenval(3);
  tensor.EigenVectors(eigenval);
  
  sphericity = 3.0*(eigenval(1)+eigenval(2))/2.0;
  aplanarity = 3.0*eigenval(2)/2.0;
  
  return;
}


bool BoostedUtils::GetTopTag(const boosted::HEPTopJet& topJet,const double& fW, const double& mTopMin, const bool& altConf){
  std::vector<pat::Jet> subjets;
  subjets.push_back(topJet.nonW);
  subjets.push_back(topJet.W1);
  subjets.push_back(topJet.W2);
  
  if(subjets.size()!=3) return false;
  
  if(!altConf)  std::sort(subjets.begin(), subjets.end(),FirstJetIsHarder);
  else          TopSubjetCSVDef(subjets);
  
  std::vector<math::XYZTLorentzVector> subjetVecs = GetJetVecs(subjets);
    
  float m12=-999;
  float m23=-999;
  float m13=-999;
  float m123=-999;
  
  m12=(subjetVecs[0]+subjetVecs[1]).M();
  m13=(subjetVecs[0]+subjetVecs[2]).M();
  m23=(subjetVecs[1]+subjetVecs[2]).M();
  m123=(subjetVecs[0]+subjetVecs[1]+subjetVecs[2]).M();

  if(m123<mTopMin) return false;
  
  float mT = 172.3;
  float mW = 80.4;
  
  float Rmin = (1-fW)*mW/mT;
  float Rmax = (1+fW)*mW/mT;
  
  if(!altConf){
    float y1 = 1+pow(m13/m12,2);
    float y2 = 1+pow(m12/m13,2);
    float x = 1-pow(m23/m123,2);  
  
    if(((0.2<atan(m23/m123)) && (atan(m23/m123)<1.3)) && ((Rmin<m23/m123) && (m23/m123<Rmax))) return true;
    if(((x>pow(Rmin,2)*y1) && (x<pow(Rmax,2)*y1)) && (m23/m123>0.35)) return true;
    if(((x>pow(Rmin,2)*y2) && (x<pow(Rmax,2)*y2)) && (m23/m123>0.35)) return true;
  }
  else{
    if(Rmin<m23/m123 && m23/m123<Rmax && 0.2<m12/m13 && 0.2<m13/m12 ) return true;
  }
  
  return false;
}

void BoostedUtils::TopSubjetCSVDef(std::vector<pat::Jet> &subjets){
  std::sort(subjets.begin(), subjets.end(),BoostedUtils::FirstHasHigherCSV);
  
  pat::Jet Bsubjet = subjets[0];
  pat::Jet W1subjet, W2subjet;
  
  if(subjets[1].pt()>subjets[2].pt()){
    W1subjet = subjets[1];
    W2subjet = subjets[2];
  }
  else{
    W1subjet = subjets[2];
    W2subjet = subjets[1];
  }
  
  subjets.clear();
  subjets.push_back(Bsubjet);
  subjets.push_back(W1subjet);
  subjets.push_back(W2subjet);
}


std::vector<pat::Jet> BoostedUtils::GetHiggsFilterJets(const boosted::SubFilterJet& higgsJet, const int& nCSVJets){

  std::vector<pat::Jet> subJets = higgsJet.filterjets;
  
  return GetHiggsFilterJets(subJets,nCSVJets);
}


std::vector<pat::Jet> BoostedUtils::GetHiggsFilterJets(const std::vector<pat::Jet>& higgsDecayJets, const int& nCSVJets){

  std::vector<pat::Jet> subJets = higgsDecayJets;
  
  std::sort(subJets.begin(), subJets.end(),BoostedUtils::FirstHasHigherCSV);
  
  std::vector<pat::Jet> HighCSVSubJets;
  
  for(std::vector<pat::Jet>::iterator itSubJet = subJets.begin(); itSubJet != subJets.end(); ){
    
    bool csvDistance = true;
    for(std::vector<pat::Jet>::iterator itCSVJet = HighCSVSubJets.begin(); itCSVJet != HighCSVSubJets.end(); ++itCSVJet){
      if(BoostedUtils::DeltaR(*itCSVJet,*itSubJet)<.4){
        csvDistance = false;
        break;
      }
    }
    
    if(csvDistance){
      HighCSVSubJets.push_back(*itSubJet);
      subJets.erase(itSubJet);
    }
    else{
      ++itSubJet;
    }
    
    if((int) HighCSVSubJets.size()>=nCSVJets) break;
  }
  
  
  if(subJets.size()==0) return HighCSVSubJets;
  else{
    std::sort(subJets.begin(), subJets.end(),BoostedUtils::FirstJetIsHarder);

    subJets.insert(subJets.begin(),HighCSVSubJets.begin(),HighCSVSubJets.end());
  }
  
  return subJets;
}


float BoostedUtils::GetHiggsMass(const boosted::SubFilterJet& higgsJet, const int& nFilterJets, const int& nBTags, const float& csvWP){
  
  if(nFilterJets<2 || nBTags>nFilterJets) return -1.;
  if(((int)higgsJet.filterjets.size())<nFilterJets || ((int)higgsJet.filterjets.size())<nBTags) return -1.;
  
  std::vector<pat::Jet> filterJets = GetHiggsFilterJets(higgsJet,nBTags);
  
  if(nBTags>0){
    if(filterJets[nBTags-1].bDiscriminator("combinedSecondaryVertexBJetTags")<csvWP) return -1.;
  }
  
  std::vector<math::XYZTLorentzVector> filterJetVecs = GetJetVecs(filterJets);
  math::XYZTLorentzVector sumVec = filterJetVecs[0];
  
  for(std::vector<math::XYZTLorentzVector>::const_iterator itFiltJet = filterJetVecs.begin()+1; itFiltJet-filterJetVecs.begin() < nFilterJets; ++itFiltJet){
    sumVec += *itFiltJet;
  }
  
  return sumVec.M();
}


double BoostedUtils::GetBestHiggsMassOhio(math::XYZTLorentzVector lepton, math::XYZTLorentzVector met, std::vector<math::XYZTLorentzVector> jets, std::vector<double> btag, double &minChi, double &dRbb, math::XYZTLorentzVector &bjet1, math::XYZTLorentzVector &bjet2, std::vector<math::XYZTLorentzVector> loose_jets, std::vector<double> loose_btag){
  if(jets.size()<6 && loose_jets.size()>0){
    jets.push_back( loose_jets[0] );
    btag.push_back( loose_btag[0] );
  }
  int nJets = int(jets.size());
  double chi_top_lep=10000;
  double chi_top_had=10000;
  //double chi_W_lep=10000; //isn't really used
  double chi_W_had=10000;
  minChi = 1000000;
  dRbb = 1000000;
  double btagCut = 0.814;
  double W_mass = 80.0;
  double top_mass = 172.5;
  //double H_mass=120.0;
  // updated 8/22/2012 from J. Timcheck
  //sigma's from >=6j >=4t, muon, no imaginary neutrino pz ttH
  double sigma_hadW = 12.77;
  double sigma_hadTop = 18.9;
  double sigma_lepTop = 32.91;
  // //sigma's from >=6j >=4t, muon, no imaginary neutrino pz ttH
  // double sigma_hadW = 12.59;
  // double sigma_hadTop = 19.9;
  // double sigma_lepTop = 39.05;
  //sigma's from >=6j >=4t, muon, no imaginary neutrino pz ttJets
  //double sigma_hadW = 12.72,
  //sigma_hadTop = 18.12,
  //sigma_lepTop = 38.72;
  
  double metPz[2];
  double chi=999999;
  //stuff to find:
  double higgs_mass_high_energy=0;
  int nBtags = 0;
  for(int i=0;i<nJets;i++){
    if(btag[i]>btagCut) nBtags++;
  }
  int nUntags = nJets-nBtags;
  double lowest_btag = 99.;
  double second_lowest_btag = 999.;
  int ind_lowest_btag = 999;
  int ind_second_lowest_btag = 999;
  if( nJets>=6 && nBtags>=4 ){
    if( nUntags<2 ){
      for(int i=0;i<nJets;i++){
	      if( btag[i]<lowest_btag ){
	        second_lowest_btag = lowest_btag;
	        ind_second_lowest_btag = ind_lowest_btag;
	        lowest_btag = btag[i];
	        ind_lowest_btag = i;
	      }
	      else if( btag[i]<second_lowest_btag ){
	        second_lowest_btag = btag[i];
	        ind_second_lowest_btag = i;
	      }
      }
    }
  }
  //Handle 6j3t.
  int ind_promoted_btag = 999;
  if( nJets>=6 && nBtags==3 ){
    for(int i=0;i<nJets;i++){
      int rank = 0;
      for(int j=0;j<nJets;j++){
	      if( btag[j] > btag[i] ){
	        rank++;
	      }
      }
      if( rank == 3 ) ind_promoted_btag = i;
    }
  }
  // First get the neutrino z
  double energyLep = lepton.E();
  double a = (W_mass*W_mass/(2.0*energyLep)) + (lepton.Px()*met.Px() + lepton.Py()*met.Py())/energyLep;
  double radical = (2.0*lepton.Pz()*a/energyLep)*(2.0*lepton.Pz()*a/energyLep);
  radical = radical - 4.0*(1.0 - (lepton.Pz()/energyLep)*(lepton.Pz()/energyLep))*(met.Px()*met.Px() + met.Py()*met.Py()- a*a);
  if (radical < 0.0) radical = 0.0;
  metPz[0] = (lepton.Pz()*a/energyLep) + 0.5*sqrt(radical);
  metPz[0] = metPz[0] / (1.0 - (lepton.Pz()/energyLep)*(lepton.Pz()/energyLep));
  metPz[1] = (lepton.Pz()*a/energyLep) - 0.5*sqrt(radical);
  metPz[1] = metPz[1] / (1.0 - (lepton.Pz()/energyLep)*(lepton.Pz()/energyLep));
  // Loop over all jets, both Pz, calcaulte chi-square
  math::XYZTLorentzVector metNew;
  for( int ipznu=0; ipznu<2; ipznu++ ){
    metNew.SetXYZT(met.Px(),met.Py(),metPz[ipznu],0.0); //neutrino has mass 0
    
    //with b-tag info
    if( (nJets>=6 && nBtags>=4) || (nJets>=6 && nBtags==3) ){
      std::vector<math::XYZTLorentzVector> not_b_tagged,b_tagged;
      
      //fill not_b_tagged and b_tagged
      for( int i=0;i<nJets;i++ ){
	      if((btag[i]>btagCut && i!=ind_second_lowest_btag && i!=ind_lowest_btag) || (i==ind_promoted_btag)) b_tagged.push_back(jets[i]);
	      else not_b_tagged.push_back(jets[i]);
      }
      
      //first make possible t_lep's with b-tagged jets (includes making W_lep)
      for( int i=0; i<int(b_tagged.size()); i++ ){
	      //math::XYZTLorentzVector W_lep = metNew+lepton; //used for histogram drawing only
	      math::XYZTLorentzVector top_lep = metNew+lepton+b_tagged.at(i);
	      chi_top_lep = pow((top_lep.M()-top_mass)/sigma_lepTop,2);
        
	      //next make possible W_had's with not b-tagged jets
	      for( int j=0; j<int(not_b_tagged.size()); j++ ){
	        for( int k=0; k<int(not_b_tagged.size()); k++ ){
	          if( j!=k ){
	            math::XYZTLorentzVector W_had=not_b_tagged.at(j)+not_b_tagged.at(k);
	            chi_W_had=pow((W_had.M()-W_mass)/sigma_hadW,2);
              
	            //now make possible top_had's (using the W_had + some b-tagged jet)
	            for( int l=0; l<int(b_tagged.size()); l++ ){
		            if( l!=i ){
		              math::XYZTLorentzVector top_had = W_had+b_tagged.at(l);
		              chi_top_had = pow((top_had.M()-top_mass)/sigma_hadTop,2);
		              chi = chi_top_lep+chi_W_had+chi_top_had;

		              //accept the lowest chi
		              if( chi<minChi ){
		                minChi = chi;

		                //pick the other two b's that have the highest et (energy in transverse plane) as higgs mass constituents
		                math::XYZTLorentzVector H2;
		                int numH2Constituents=0;
		                math::XYZTLorentzVector bBest[2];
		                for( int m=0; m<int(b_tagged.size()); m++ ){
		                  if( m!=i && m!=l && numH2Constituents<2 ){
			                  bBest[numH2Constituents] = b_tagged.at(m);
			                  numH2Constituents++;
			                  H2 += b_tagged.at(m);
		                  }
		                }
		                dRbb = DeltaR(bBest[0],bBest[1]);
		                higgs_mass_high_energy = H2.M();
		                bjet1 = bBest[0];
		                bjet2 = bBest[1];
		              }
		            }
	            }
	          }
	        }
	      }
      }
    }
  }
  return higgs_mass_high_energy;
}


float BoostedUtils::GetBestHiggsMassOhio2(math::XYZTLorentzVector lepton, math::XYZTLorentzVector &met, std::vector<math::XYZTLorentzVector> jets, std::vector<double> btag, double &minChi, double &dRbb, math::XYZTLorentzVector &bjet1, math::XYZTLorentzVector &bjet2, double &chi2lepW, double &chi2leptop, double &chi2hadW, double &chi2hadtop, double &mass_lepW, double &mass_leptop, double &mass_hadW, double &mass_hadtop, math::XYZTLorentzVector &toplep, math::XYZTLorentzVector &tophad){
  int nJets = int(jets.size());
  double pfmet_px=met.Px(), pfmet_py=met.Py();
  double chi_top_lep=10000;
  double chi_top_had=10000;
  //double chi_W_lep=10000; //isn't really used
  double chi_W_had=10000;
  minChi = 1000000;
  dRbb = 1000000;
  double btagCut = 0.814;
  double W_mass = 80.0;
  double top_mass = 172.5;
  //double H_mass=120.0;
  // updated 8/22/2012 from J. Timcheck
  //sigma's from >=6j >=4t, muon, no imaginary neutrino pz ttH
  double sigma_hadW = 12.77;
  double sigma_hadTop = 18.9;
  //double sigma_lepTop = 32.91;
  double sigma_lepTop = 18.9;
  // //sigma's from >=6j >=4t, muon, no imaginary neutrino pz ttH
  // double sigma_hadW = 12.59;
  // double sigma_hadTop = 19.9;
  // double sigma_lepTop = 39.05;
  //sigma's from >=6j >=4t, muon, no imaginary neutrino pz ttJets
  //double sigma_hadW = 12.72,
  //sigma_hadTop = 18.12,
  //sigma_lepTop = 38.72;
  
  /// more initializitions
  bjet1.SetPxPyPzE(1.,1.,1.,2.);
  bjet2.SetPxPyPzE(1.,1.,1.,2.);
  // chi2lepW = 0.;
  // chi2leptop = 0.;
  // chi2hadtop = 0.;
  mass_lepW = 0.;
  mass_leptop = 0.;
  mass_hadW = 0.;
  mass_hadtop = 0.;
  toplep.SetPxPyPzE(1.,1.,1.,2.);
  tophad.SetPxPyPzE(1.,1.,1.,2.);
  double metPz[2];
  double chi=999999;
  //stuff to find:
  double higgs_mass_high_energy=0;
  int nBtags = 0;
  for(int i=0;i<nJets;i++){
    if(btag[i]>btagCut) nBtags++;
  }
  int nUntags = nJets-nBtags;
  double lowest_btag = 99.;
  double second_lowest_btag = 999.;
  int ind_lowest_btag = 999;
  int ind_second_lowest_btag = 999;
  std::vector<double> btag_sorted = btag;
  if( nJets>=6 && nBtags>=4 ){
    if( nUntags<2 ){
      for(int i=0;i<nJets;i++){
	      if( btag[i]<lowest_btag ){
	        second_lowest_btag = lowest_btag;
	        ind_second_lowest_btag = ind_lowest_btag;
	        lowest_btag = btag[i];
	        ind_lowest_btag = i;
	      }
	      else if( btag[i]<second_lowest_btag ){
	        second_lowest_btag = btag[i];
	        ind_second_lowest_btag = i;
	      }
      }
    }
      // if( nBtags==3 )
//       {
//       sort(btag_sorted.begin(),btag_sorted.end());
//       double fourth_highest_csv = btag_sorted[nJets-4];
//       for (int f=0; f<nJets; f++)
//       {
//       if (btag[f]==fourth_highest_csv) ind_fourth_highest = f;
//       }
//       }
  }
  //Handle 6j3t.
  int ind_promoted_btag = 999;
  if( nJets>=6 && nBtags==3 ){
    for(int i=0;i<nJets;i++){
      int rank = 0;
      for(int j=0;j<nJets;j++){
	      if( btag[j] > btag[i] ){
	        rank++;
	      }
      }
      if( rank == 3 ) ind_promoted_btag = i;
    }
  }
  // First get the neutrino z
  double energyLep = lepton.E();
  double a = (W_mass*W_mass/(2.0*energyLep)) + (lepton.Px()*met.Px() + lepton.Py()*met.Py())/energyLep;
  double radical = (2.0*lepton.Pz()*a/energyLep)*(2.0*lepton.Pz()*a/energyLep);
  radical = radical - 4.0*(1.0 - (lepton.Pz()/energyLep)*(lepton.Pz()/energyLep))*(met.Px()*met.Px() + met.Py()*met.Py()- a*a);
  bool imaginary = false;
  if(radical < 0.0) imaginary = true;
  if(imaginary){
    radical = -1.0;
    double value = .001;
    while(true){
	    met.SetPxPyPzE(pfmet_px,pfmet_py,0.0,sqrt(pow(pfmet_px,2)+pow(pfmet_py,2))); //neutrino mass 0, pt = sqrt(px^2+py^2)
	    //	energyLep = lepton.E();
	    a = (W_mass*W_mass/(2.0*energyLep)) + (lepton.Px()*met.Px() + lepton.Py()*met.Py())/energyLep;
	    radical = (2.0*lepton.Pz()*a/energyLep)*(2.0*lepton.Pz()*a/energyLep);
	    radical = radical - 4.0*(1.0 - (lepton.Pz()/energyLep)*(lepton.Pz()/energyLep))*(met.Px()*met.Px() + met.Py()*met.Py()- a*a);
	    if(radical>=0) break;
	    pfmet_px -= pfmet_px*value;
	    pfmet_py -= pfmet_py*value;
	  }
  }
  metPz[0] = (lepton.Pz()*a/energyLep) + 0.5*sqrt(radical);
  metPz[0] = metPz[0] / (1.0 - (lepton.Pz()/energyLep)*(lepton.Pz()/energyLep));
  metPz[1] = (lepton.Pz()*a/energyLep) - 0.5*sqrt(radical);
  metPz[1] = metPz[1] / (1.0 - (lepton.Pz()/energyLep)*(lepton.Pz()/energyLep));
  
  // Loop over all jets, both Pz, calcaulte chi-square
  math::XYZTLorentzVector metNew;
  for( int ipznu=0; ipznu<2; ipznu++ ){
    metNew.SetPxPyPzE(met.Px(),met.Py(),metPz[ipznu],0.0); //neutrino has mass 0
    metNew.SetE(metNew.P());
    
    //with b-tag info
    if(( nJets>=6 && nBtags>=4 )||( nJets>=6 && nBtags==3 )){
      std::vector<math::XYZTLorentzVector> not_b_tagged,b_tagged;
      
      //fill not_b_tagged and b_tagged
      for( int i=0;i<nJets;i++ ){
	      //if (nBtags>=4)
	      //{
	      if( (btag[i]>btagCut && i!=ind_second_lowest_btag && i!=ind_lowest_btag) || (i==ind_promoted_btag) ) b_tagged.push_back(jets[i]);
	      else not_b_tagged.push_back(jets[i]);
	      //}

        // 	  if (nBtags==3)
        // 	  {
        // 	  if( btag[i]>btagCut || i==ind_fourth_highest) b_tagged.push_back(jets[i]);
        // 	  else not_b_tagged.push_back(jets[i]);
	      //}
      }
      
      //first make possible t_lep's with b-tagged jets (includes making W_lep)
      for( int i=0; i<int(b_tagged.size()); i++ ){
	      math::XYZTLorentzVector top_lep = metNew+lepton+b_tagged.at(i);
	      chi_top_lep = pow((top_lep.M()-top_mass)/sigma_lepTop,2);
	      
        //next make possible W_had's with not b-tagged jets
	      for( int j=0; j<int(not_b_tagged.size()); j++ ){
	        for( int k=0; k<int(not_b_tagged.size()); k++ ){
	          if( j!=k ){
	            math::XYZTLorentzVector W_had = not_b_tagged.at(j)+not_b_tagged.at(k);
	            chi_W_had = pow((W_had.M()-W_mass)/sigma_hadW,2);
	            
              //now make possible top_had's (using the W_had + some b-tagged jet)
	            for( int l=0; l<int(b_tagged.size()); l++ ){
		            if( l!=i ){
		              math::XYZTLorentzVector top_had=W_had+b_tagged.at(l);
		              chi_top_had = pow((top_had.M()-top_mass)/sigma_hadTop,2);
		              chi = chi_top_lep+chi_W_had+chi_top_had;
		              
                  //accept the lowest chi
		              if( chi<minChi ){
		                minChi = chi;
		                //pick the other two b's that have the highest et (energy in transverse plane) as higgs mass constituents
		                math::XYZTLorentzVector H2;
		                int numH2Constituents=0;
		                math::XYZTLorentzVector bBest[2];
		                for( int m=0; m<int(b_tagged.size()); m++ ){
		                  if( m!=i && m!=l && numH2Constituents<2 ){
			                  bBest[numH2Constituents] = b_tagged.at(m);
			                  numH2Constituents++;
			                  H2 += b_tagged.at(m);
		                  }
		                }
		                dRbb = ROOT::Math::VectorUtil::DeltaR(bBest[0],bBest[1]);
		                higgs_mass_high_energy = H2.M();
		                bjet1 = bBest[0];
		                bjet2 = bBest[1];
		                mass_lepW = W_mass;
		                mass_leptop = top_lep.M();
		                mass_hadW = W_had.M();
		                mass_hadtop = top_had.M();
		                toplep = top_lep;
		                tophad = top_had;
		              }
		            }
	            }
	          }
	        }
	      }
      }
    }
  }
  chi2lepW = 0.;
  chi2leptop = chi_top_lep;
  chi2hadtop = chi_top_had;
  chi2hadW = chi_W_had;
  return higgs_mass_high_energy;
  
}


double BoostedUtils::StudyTopsBBSystOhio(math::XYZTLorentzVector &metv, std::vector<double> lep, std::vector< std::vector<double> > jets, std::vector<double> csv, double &minChi, double &chi2lepW, double &chi2leptop, double &chi2hadW, double &chi2hadtop, double &mass_lepW, double &mass_leptop, double &mass_hadW, double &mass_hadtop, double &dRbb, double &testquant1, double &testquant2, double &testquant3, double &testquant4, double &testquant5, double &testquant6, double &testquant7, math::XYZTLorentzVector &b1, math::XYZTLorentzVector &b2){
  double pi = TMath::Pi();
  math::XYZTLorentzVector lepton(lep[0],lep[1],lep[2],lep[3]);
  std::vector<math::XYZTLorentzVector> jet_TLVs;
  math::XYZTLorentzVector jet;
  int nJets = jets.size();
  for(int i=0;i<nJets;i++){
    jet.SetPxPyPzE(jets[i][0],jets[i][1],jets[i][2],jets[i][3]);
    jet_TLVs.push_back(jet);
  } 
  //double minChi;
  //double dRbb;
  math::XYZTLorentzVector bjet1;
  math::XYZTLorentzVector bjet2;
  math::XYZTLorentzVector leptop;
  math::XYZTLorentzVector hadtop;
  double bhm = GetBestHiggsMassOhio2(lepton, metv, jet_TLVs, csv, minChi, dRbb, bjet1, bjet2, chi2lepW, chi2leptop, chi2hadW, chi2hadtop, mass_lepW, mass_leptop, mass_hadW, mass_hadtop, leptop, hadtop); // Jon T. version 2
  b1 = bjet1;
  b2 = bjet2;
  math::XYZTLorentzVector bsyst = bjet1+bjet2;
  math::XYZTLorentzVector topsyst = leptop+hadtop;
  //testquant1 = bsyst.Angle(leptop.Vect());
  //testquant2 = bsyst.Angle(hadtop.Vect());
  //testquant1 = bsyst.DeltaPhi(leptop);
  //testquant2 = bsyst.DeltaPhi(hadtop);
  //testquant1 = bsyst.Eta() - leptop.Eta();
  //testquant2 = bsyst.Eta() - hadtop.Eta();
  //testquant1 = bsyst.Eta() - hadtop.Eta();
  //testquant2 = bsyst.DeltaPhi(hadtop);
  //testquant2 = bsyst.Eta();
  //testquant1 = topsyst.Phi();
  //testquant2 = bsyst.Phi();
  //testquant2 = bsyst.Angle(hadtop.Vect());
  //dphi, deta stuff
  testquant1 = bsyst.Eta() - leptop.Eta();
  testquant2 = bsyst.Eta() - hadtop.Eta();
  double dphihad = ROOT::Math::VectorUtil::DeltaPhi(bsyst,hadtop);
  double dphilep = ROOT::Math::VectorUtil::DeltaPhi(bsyst,leptop);
  testquant3 = fabs((dphilep - pi)*(dphilep + pi)) + pow(dphihad,2);
  testquant3 = sqrt(testquant3 / (2.0*pow(pi,2)));
  testquant4 = bsyst.Eta();
  testquant5 = (hadtop.Eta() + leptop.Eta())/2;
  testquant6 = sqrt(abs((bsyst.Eta() - leptop.Eta())*(bsyst.Eta() - hadtop.Eta())));
  testquant7 = ROOT::Math::VectorUtil::Angle(bsyst,topsyst.Vect());
  return bhm;
}


void BoostedUtils::TTHRecoVarsOhio(const std::vector<pat::Jet>& selectedJets,const std::vector<pat::Jet>& selectedJetsLoose, const pat::MET& pfMET, const math::XYZTLorentzVector& lepton, float& higgsMass_, float& dRbb_,float& dEtaHadTopbb_,float& dEtaLeptopbb_, float& dEtaFN_)
{
  math::XYZTLorentzVector met = pfMET.p4();
  std::vector< std::vector<double> > fjets;
  std::vector<math::XYZTLorentzVector> jets = BoostedUtils::GetJetVecs(selectedJets);
  std::vector<double> btag;
  for(std::vector<pat::Jet>::const_iterator itJet = selectedJets.begin(); itJet != selectedJets.end(); ++itJet){
    std::vector<double> ajet;
    ajet.push_back(itJet->px());
    ajet.push_back(itJet->py());
    ajet.push_back(itJet->pz());
    ajet.push_back(itJet->energy());
    fjets.push_back(ajet);
    btag.push_back(itJet->bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags"));
  }
  std::vector<math::XYZTLorentzVector> jetsLoose = GetJetVecs(selectedJetsLoose);
  std::vector<double> btagLoose;
  for(std::vector<pat::Jet>::const_iterator itJetLoose = selectedJetsLoose.begin(); itJetLoose != selectedJetsLoose.end(); ++itJetLoose){
    btagLoose.push_back(itJetLoose->bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags"));
  }  
  std::vector<double> lep;
  lep.push_back(lepton.Px());
  lep.push_back(lepton.Py());
  lep.push_back(lepton.Pz());
  lep.push_back(lepton.E()); 

  double minChi;
  double dRbb;
  math::XYZTLorentzVector bjet1;
  math::XYZTLorentzVector bjet2;

  double higgsmass1 = GetBestHiggsMassOhio(lepton, met, jets, btag, minChi, dRbb, bjet1, bjet2, jetsLoose, btagLoose);

  double minChi2; 
  double chi2lepW;
  double chi2leptop;
  double chi2hadW;
  double chi2hadtop;
  double mass_lepW;
  double mass_leptop;
  double mass_hadW;
  double mass_hadtop;
  double dRbb2;
  double testquant1; 
  double testquant2; 
  double testquant3; 
  double testquant4; 
  double testquant5; 
  double testquant6;
  double testquant7;
  math::XYZTLorentzVector b1; 
  math::XYZTLorentzVector b2;
  
  //double higgsmass2 = BoostedUtils::StudyTopsBBSystOhio(MET, METphi, met, lep, fjets, btag, minChi2, chi2lepW, chi2leptop, chi2hadW, chi2hadtop, mass_lepW, mass_leptop, mass_hadW, mass_hadtop, dRbb2, testquant1, testquant2, testquant3,testquant4, testquant5, testquant6, testquant7, b1, b2);
  BoostedUtils::StudyTopsBBSystOhio(met, lep, fjets, btag, minChi2, chi2lepW, chi2leptop, chi2hadW, chi2hadtop, mass_lepW, mass_leptop, mass_hadW, mass_hadtop, dRbb2, testquant1, testquant2, testquant3,testquant4, testquant5, testquant6, testquant7, b1, b2);

  higgsMass_ = higgsmass1;
  dRbb_ = dRbb2;
  dEtaHadTopbb_ = abs(testquant2);
  dEtaLeptopbb_ = abs(testquant1);
  dEtaFN_ = testquant6;
  
}

    


    
/*










vector<BNjet> BEANUtils::GetJetsByDr(TLorentzVector vec,const std::vector<BNjet>& jets){
  closerToVec closer;
  closer.vec=vec;
  std::vector<BNjet> sorted_jets = jets;
  std::sort(sorted_jets.begin(),sorted_jets.end(),closer);
  return sorted_jets;
}




void BEANUtils::GetHiggsJetCSVVarsDr(const BNsubfilterjet& jet, BNjet& csvec1_fjet_,BNjet& csvec2_fjet_){
  float csvec1 = -.1;
  float csvec2 = -.1;
  
  int fjindex1 = -1;
  int fjindex2 = -1;
  
  for(size_t i=0;i<jet.filterjets.size();i++){
    if(jet.filterjets[i].pt>20&&jet.filterjets[i].btagCombinedSecVertex>csvec1){
      csvec1 = fmax(jet.filterjets[i].btagCombinedSecVertex,-.1);
      fjindex1 = i;
    }
  }
  for(size_t i=0;i<jet.filterjets.size();i++){
    if(jet.filterjets[i].pt>20&&jet.filterjets[i].btagCombinedSecVertex>csvec2&&i!=fjindex1&&DeltaR(jet.filterjets[i],jet.filterjets[fjindex1])>0.4){
      csvec2 = fmax(jet.filterjets[i].btagCombinedSecVertex,-.1);
      fjindex2 = i;
    }
  }
  
  if(fjindex1>=0) csvec1_fjet_ = jet.filterjets[fjindex1];
  if(fjindex2>=0) csvec2_fjet_ = jet.filterjets[fjindex2];
}


void BEANUtils::GetHiggsJetCSVVarsDr(const BNjetCollection& filterjets,BNjet& b1_fjet_,BNjet& b2_fjet_,BNjet& g_fjet_){
  float csvec1 = -.1;
  float csvec2 = -.1;
 
  int fjindex1 = -1;
  int fjindex2 = -1;
  int fjindex3 = -1;
 
  for(size_t i=0;i<filterjets.size();i++){
    if(filterjets[i].pt<20) continue;
    if(filterjets[i].btagCombinedSecVertex>csvec1){
      csvec1 = fmax(filterjets[i].btagCombinedSecVertex,-.1);
      fjindex1 = i;
    }
  }
  for(size_t i=0;i<filterjets.size();i++){
    if(filterjets[i].pt<20) continue;
    if(i==fjindex1) continue;
    if(DeltaR(filterjets[i],filterjets[fjindex1])<0.4) continue;
    if(filterjets[i].btagCombinedSecVertex>csvec2){
      csvec2 = fmax(filterjets[i].btagCombinedSecVertex,-.1);
      fjindex2 = i;
    }
  }
  for(size_t i=0;i<filterjets.size();i++){
    if(filterjets[i].pt<20) continue;
    if(i==fjindex1) continue;
    if(i==fjindex2) continue;
   
    fjindex3 = i;
  }
 
  if(fjindex1>=0) b1_fjet_ = filterjets[fjindex1];
  if(fjindex2>=0) b2_fjet_ = filterjets[fjindex2];
  if(fjindex3>=0) g_fjet_ = filterjets[fjindex3];
}




float BEANUtils::GetHiggsMass(const BNsubfilterjet& higgs_jet, const int n_filterjets, const bool hardest_jets, const int n_btags, const float csv_wp){
  
  TLorentzVector vec;
  
  int n_filterjets_found = 0;
  int n_btags_found = 0;
  
  for(size_t i=0;i<higgs_jet.filterjets.size() && n_filterjets_found<n_filterjets;i++){
  	if(higgs_jet.filterjets[i].btagCombinedSecVertex<csv_wp)
	  if(n_filterjets_found-n_btags_found < n_filterjets-n_btags) continue;
	else
	  n_btags_found ++;
	
    vec = vec +BEANUtils::GetJetVec(higgs_jet.filterjets[i]);
	n_filterjets_found++;
  }
  
  if(hardest_jets && n_filterjets_found!=n_filterjets) return -1;
  return vec.M();
}



BNjet BEANUtils::GetTopLepBjet(const BNsubfilterjet& sfjet,const BNtoptagjet& topjet, const std::vector<BNjet>& ak5jets){
  std::vector<BNjet> sortedJets=ak5jets;
  std::sort(sortedJets.begin(), sortedJets.end(),BEANUtils::FirstHasHigherCSV);  
  bool clean = false;
  BNjet bjet;
  for(size_t i=0; i<sortedJets.size()&&!clean;i++){    
    clean=true;
    if(DeltaR(sortedJets[i],topjet.W1)<0.2) clean=false;
    if(DeltaR(sortedJets[i],topjet.W2)<0.2) clean=false;
    if(DeltaR(sortedJets[i],topjet.nonW)<0.2) clean=false;
    for(size_t j=0; j<sfjet.filterjets.size()&&j<3;j++){    
      if(DeltaR(sortedJets[i],sfjet.filterjets[j])<0.2) clean=false;
    }
    if(clean) bjet=sortedJets[i];
  }
  return bjet;
}
  


bool BEANUtils::GetSelected_HiggsJets(const BNsubfilterjetCollection& subfilterjets, BNsubfilterjetCollection& selected_higgsjets, BNtoptagjet& topHadCand, BNsubfilterjet& higgsCand, bool check_subjet_overlap=true){
  
  bool foundHiggsJet=false;
  for(size_t i=0; i<subfilterjets.size();i++){
    BNjet csvec1_fjet;
    BNjet csvec2_fjet;
    BEANUtils::GetHiggsJetCSVVarsDr(subfilterjets[i],csvec1_fjet,csvec2_fjet);    
    if(csvec2_fjet.btagCombinedSecVertex>0.814&&subfilterjets[i].fatjet.pt>200 and BEANUtils::DeltaR(topHadCand.fatjet,subfilterjets[i].fatjet)>1.5 and fabs(subfilterjets[i].fatjet.eta)<=2.0) {
      //std::cout<<"test"<<std::endl;
           
      if(check_subjet_overlap){
        bool clean = true;
        for(size_t j=0; j<subfilterjets[i].filterjets.size();j++){
          if(BEANUtils::DeltaR(topHadCand.W1,subfilterjets[i].filterjets[j])<0.2) clean=false;
          if(BEANUtils::DeltaR(topHadCand.W2,subfilterjets[i].filterjets[j])<0.2) clean=false;
          if(BEANUtils::DeltaR(topHadCand.nonW,subfilterjets[i].filterjets[j])<0.2) clean=false;
          }
         if(!clean) continue;
        }//0.814 or 0.244
        
      selected_higgsjets.push_back(subfilterjets[i]);
      foundHiggsJet=true;
    }
  }
  
  if(foundHiggsJet){
    size_t maxHiggsTag=-1.0;
    for(size_t i=0; i<selected_higgsjets.size();i++){
      BNjet csvec1_fjet;
      BNjet csvec2_fjet;
      BEANUtils::GetHiggsJetCSVVarsDr(selected_higgsjets[i],csvec1_fjet,csvec2_fjet);
      if(csvec2_fjet.btagCombinedSecVertex>maxHiggsTag){
        maxHiggsTag=csvec2_fjet.btagCombinedSecVertex;
        higgsCand=selected_higgsjets[i];
      }
      
    }
  }
  
  return foundHiggsJet;
}

bool BEANUtils::MCContainsTTbar(const BNmcparticleCollection& mcparticlesStatus3){
  bool foundT=false;
  bool foundTbar=false;
  for(size_t i=0; i<mcparticlesStatus3.size();i++){
    if(mcparticlesStatus3[i].id==6) foundT=true;
    if(mcparticlesStatus3[i].id==-6) foundTbar=true;
  }
  return foundT&&foundTbar;
}
bool BEANUtils::MCContainsHiggs(const BNmcparticleCollection& mcparticlesStatus3){
  for(size_t i=0; i<mcparticlesStatus3.size();i++){
    if(mcparticlesStatus3[i].id==25) return true;
  }
  return false;
}





// parses input file names
vector<string> BEANUtils:: ParseFileNames(string fnames){
    std::vector<string> filenames;
    while(fnames.size() > 0 && *fnames.rbegin()==' '){
        fnames.erase(fnames.begin() + (fnames.size() - 1));
    }
    
    while(true){
        //erase spaces at the beginning:
        while(fnames.size() > 0 && fnames[0]==' ') fnames.erase(0, 1);
        if(fnames.size()==0) break;
        size_t spacepos = fnames.find(' ');
        if(spacepos==string::npos){
            //take the whole rest and go out of here:
            filenames.push_back(fnames);
            break;
        }
        else{
            //take all up to (excluding) the space:
            filenames.push_back(fnames.substr(0, spacepos));
            fnames.erase(0, spacepos);
        }
    }
    return filenames;
}
*/
