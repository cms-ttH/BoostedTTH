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


vector<TLorentzVector> BoostedUtils::GetTLorentzVectors(const std::vector<math::XYZTLorentzVector>& vecs){
  vector<TLorentzVector> results;
  for(auto vec=vecs.begin();vec!=vecs.end();vec++){
    TLorentzVector result(vec->Px(),vec->Py(),vec->Pz(),vec->E());
    results.push_back(result);
  }
  return results;

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


bool BoostedUtils::FirstBoostedJetIsHarder(boosted::BoostedJet jet1, boosted::BoostedJet jet2){
  return BoostedUtils::FirstJetIsHarder(jet1.fatjet,jet2.fatjet);
}


bool BoostedUtils::FirstHasHigherCSV(pat::Jet jet1,pat::Jet jet2){
  return MiniAODHelper::GetJetCSV(jet1,"DeepCSV") > MiniAODHelper::GetJetCSV(jet2,"DeepCSV");
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
    //std::cerr << "BoostedUtils::DeltaR: vector with zero pt" << std::endl;
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

float BoostedUtils::DeltaR(const reco::GenJet& jet1,const reco::GenJet& jet2){

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
    //std::cerr<< "No PrimLep Found!" << std::endl;
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
vector<math::XYZTLorentzVector> BoostedUtils::GetJetVecs(const std::vector<reco::GenJet>& genjets){
  std::vector<math::XYZTLorentzVector> genjetVecs;

  for(std::vector<reco::GenJet>::const_iterator itJet=genjets.begin();itJet!=genjets.end();++itJet){
    genjetVecs.push_back(itJet->p4());
  }

  return genjetVecs;
}


boosted::BoostedJetCollection BoostedUtils::GetSortedByPt(boosted::BoostedJetCollection const &boostedJets){
  boosted::BoostedJetCollection result = boostedJets;
  std::sort(result.begin(), result.end(),static_cast<bool (*)(boosted::BoostedJet,boosted::BoostedJet)>(&BoostedUtils::FirstBoostedJetIsHarder));
  return result;
}


bool BoostedUtils::PassesCSV(const pat::Jet& jet, const char workingPoint){

//   float CSVLwp = 0.5426;
//   float CSVMwp = 0.8484;
//   float CSVTwp = 0.9535;
  float CSVLwp = 0.1522;
  float CSVMwp = 0.4941;
  float CSVTwp = 0.8001;


  float csvValue = MiniAODHelper::GetJetCSV(jet,"DeepCSV");

  switch(workingPoint){
    case 'L': if(csvValue > CSVLwp){ return true; } break;
    case 'M': if(csvValue > CSVMwp){ return true; } break;
    case 'T': if(csvValue > CSVTwp){ return true; } break;
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

float BoostedUtils::GetClosestJetIDs(int& idJet1, int& idJet2, const std::vector<reco::GenJet>& genjets){

  float minDr = 9.;
  for(std::vector<reco::GenJet>::const_iterator itJet1 = genjets.begin();itJet1 != genjets.end();++itJet1){
    for(std::vector<reco::GenJet>::const_iterator itJet2 = itJet1+1;itJet2 != genjets.end();++itJet2){
      math::XYZTLorentzVector jetVec1 = itJet1->p4();
      math::XYZTLorentzVector jetVec2 = itJet2->p4();

      if(BoostedUtils::DeltaR(jetVec1,jetVec2)<minDr){
	      idJet1 = itJet1 - genjets.begin();
	      idJet2 = itJet2 - genjets.begin();
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

boosted::JetType BoostedUtils::GetBoostedJetType(const boosted::BoostedJet boostedJet, const BoostedJetDisc::Mode mode){

  switch(mode){
    case BoostedJetDisc::None:
    {
      return boosted::NA;
      break;
    }
    default:
      return boosted::NA;
  }
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


std::vector<pat::Jet> BoostedUtils::GetHiggsFilterJets(const boosted::BoostedJet& boostedJet, const int& nCSVJets, const int& nPtJets){

  std::vector<pat::Jet> subJets = boostedJet.filterjets;

  return GetHiggsFilterJets(subJets,nCSVJets,nPtJets);
}


std::vector<pat::Jet> BoostedUtils::GetHiggsFilterJets(const std::vector<pat::Jet>& higgsDecayJets, const int& nCSVJets, const int& nPtJets){

  std::vector<pat::Jet> subJets = higgsDecayJets;

  if(nPtJets>0 && nPtJets<int(subJets.size())){
    std::sort(subJets.begin(), subJets.end(),BoostedUtils::FirstJetIsHarder);
    std::vector<pat::Jet> tempvec(subJets.begin(),subJets.begin()+nPtJets);
    subJets = tempvec;
  }

  std::sort(subJets.begin(), subJets.end(),BoostedUtils::FirstHasHigherCSV);

  if((int)subJets.size() > (nCSVJets+1)){
    std::sort(subJets.begin()+nCSVJets, subJets.end(),BoostedUtils::FirstJetIsHarder);
  }

  return subJets;
}


float BoostedUtils::GetHiggsMass(const boosted::BoostedJet& boostedJet, const int& nJets, const int& nCSVJets, const int& nPtJets){

  std::vector<pat::Jet> filterJets = GetHiggsFilterJets(boostedJet,nCSVJets,nPtJets);

  if(filterJets.size()<2 || nCSVJets>nJets) return -1.;

  std::vector<math::XYZTLorentzVector> filterJetVecs = GetJetVecs(filterJets);
  math::XYZTLorentzVector sumVec = filterJetVecs[0];

  for(std::vector<math::XYZTLorentzVector>::const_iterator itFiltJet = filterJetVecs.begin()+1; itFiltJet!=filterJetVecs.end() && itFiltJet-filterJetVecs.begin()<nJets; ++itFiltJet){
    sumVec += *itFiltJet;
  }

  return sumVec.M();
}


std::vector<pat::Jet> BoostedUtils::GetSingleTopJets(const std::vector<pat::Jet>& centralJets, const std::vector<pat::Jet>& forwardJets, float etacut){
    std::vector<pat::Jet> singleTopJets;
    for(auto cj=centralJets.begin(); cj!=centralJets.end();cj++){
	if(fabs(cj->eta())<etacut){
	    singleTopJets.push_back(*cj);
	}
    }
    for(auto fj=forwardJets.begin(); fj!=forwardJets.end();fj++){
	if(fabs(fj->eta())>etacut){
	    singleTopJets.push_back(*fj);
	}
    }
    return singleTopJets;
}


float BoostedUtils::GetMuonRelIso(const pat::Muon& iMuon){
  float result = 9999;

  double pfIsoCharged = iMuon.pfIsolationR04().sumChargedHadronPt;
  double pfIsoNeutral = iMuon.pfIsolationR04().sumNeutralHadronEt + iMuon.pfIsolationR04().sumPhotonEt;

  double pfIsoPUSubtracted = std::max( 0.0, pfIsoNeutral - 0.5*iMuon.pfIsolationR04().sumPUPt );

  result = (pfIsoCharged + pfIsoPUSubtracted)/iMuon.pt();

  return result;
}


std::vector<pat::MET> BoostedUtils::GetCorrectedMET(const std::vector<pat::Jet>& cleanIdJetsForMET, const std::vector<pat::Jet>& correctedJets, const std::vector<pat::MET>& correctedMETs){
  std::vector<pat::MET> outputMets;

  int i=0;
  for(std::vector<pat::MET>::const_iterator oldMET=correctedMETs.begin();oldMET!=correctedMETs.end();++oldMET){
  pat::MET outMET=*oldMET;

  if(i==0){
  //get old MET p4
  TLorentzVector oldMETVec;
  oldMETVec.SetPxPyPzE(oldMET->p4().Px(),oldMET->p4().Py(),oldMET->p4().Pz(),oldMET->p4().E());
//  std::cout<<"uncorrected MET px py pz pT "<<oldMET->p4().Px()<<" "<<oldMET->p4().Py()<<" "<<oldMET->p4().Pz()<<" "<<oldMET->p4().Pt()<<" "<<std::endl;

  // add the pT vector of cleaned jets with the initial correction to the MET vector
  for(std::vector<pat::Jet>::const_iterator itJet=cleanIdJetsForMET.begin();itJet!=cleanIdJetsForMET.end();++itJet){
    TLorentzVector cleanJETVec;
    cleanJETVec.SetPtEtaPhiE(itJet->pt(),itJet->eta(),itJet->phi(),itJet->energy());
    TLorentzVector PTcleanJETVec;
    PTcleanJETVec.SetPxPyPzE(cleanJETVec.Px(),cleanJETVec.Py(),0.0,cleanJETVec.Et());
    oldMETVec+=PTcleanJETVec;
  }
  // now subtract the pT vectors of the clean recorrected jets
  for(std::vector<pat::Jet>::const_iterator itJet=correctedJets.begin();itJet!=correctedJets.end();++itJet){
    TLorentzVector correctedJETVec;
    correctedJETVec.SetPtEtaPhiE(itJet->pt(),itJet->eta(),itJet->phi(),itJet->energy());
    TLorentzVector PTcorrectedJETVec;
    PTcorrectedJETVec.SetPxPyPzE(correctedJETVec.Px(),correctedJETVec.Py(),0.0,correctedJETVec.Et());
    oldMETVec-=PTcorrectedJETVec;
  }
  outMET.setP4(reco::Candidate::LorentzVector(oldMETVec.Px(),oldMETVec.Py(),oldMETVec.Pz(),oldMETVec.E()));
//  std::cout<<"recorrected MET px py pz pT"<<outMET.p4().Px()<<" "<<outMET.p4().Py()<<" "<<outMET.p4().Pz()<<" "<<outMET.p4().Pt()<<" "<<std::endl;
  }

  i++;
  outputMets.push_back(outMET);
  }

  return outputMets;

}
