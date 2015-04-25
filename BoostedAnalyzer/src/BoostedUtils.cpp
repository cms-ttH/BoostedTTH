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
  if(vec1.Pt()<0.001||vec2.Pt()<0.001){
    //throw std::invalid_argument( "BoostedUtils::DeltaR: vector with zero pt" );
    std::cerr << "BoostedUtils::DeltaR: vector with zero pt" << std::endl;
    return -2;
  }
  
  float dr = ROOT::Math::VectorUtil::DeltaR(vec1,vec2);
  
  return dr;
}


float BoostedUtils::DeltaR(const pat::Jet& jet1,const pat::Jet& jet2){
  
  math::XYZTLorentzVector vec1 = jet1.p4();
  math::XYZTLorentzVector vec2 = jet2.p4();
  
  float dr = BoostedUtils::DeltaR(vec1,vec2);
  
  return dr;
}


float BoostedUtils::DeltaKt(const math::XYZTLorentzVector& vec1,const math::XYZTLorentzVector& vec2){
  
  float dr = BoostedUtils::DeltaR(vec1,vec2);
  float ptmin=min(vec1.Pt(),vec2.Pt());
  
  return sqrt(dr*dr*ptmin*ptmin);
}


float BoostedUtils::DeltaKt(const pat::Jet& jet1,const pat::Jet& jet2){
  if(jet1.pt()<0.001||jet2.pt()<0.001) return -2;
  
  math::XYZTLorentzVector vec1 = jet1.p4();
  math::XYZTLorentzVector vec2 = jet2.p4();
  
  return BoostedUtils::DeltaKt(vec1,vec2);
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


