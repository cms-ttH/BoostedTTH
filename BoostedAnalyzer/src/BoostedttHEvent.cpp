#include "BoostedTTH/BoostedAnalyzer/interface/BoostedttHEvent.hpp"


BoostedttHEvent::BoostedttHEvent(const InputCollections& input_):input(input_),verbose(false),btagger("combinedSecondaryVertexBJetTags"){
  ResetEvent();
}


BoostedttHEvent::~BoostedttHEvent(){

}


void BoostedttHEvent::ResetEvent(){

  // Charged Lepton
  lepVecCand = math::XYZTLorentzVector(0.,0.,0.,0.);

  // Neutrino
  nuVecCand = math::XYZTLorentzVector(0.,0.,0.,0.);
  nu1VecCand = math::XYZTLorentzVector(0.,0.,0.,0.);
  nu2VecCand = math::XYZTLorentzVector(0.,0.,0.,0.);

  // Anti-kt 5 Jets
  selectedJets.clear();
  BTagL.clear();
  BTagM.clear();
  BTagT.clear();
  nJets = 0;
  nBTagL = 0;
  nBTagM = 0;
  nBTagT = 0;
  
  HiggsCandak5Jet.clear();
  nHiggsak5Jets = 0;
  nHiggsCandBTagL = 0;
  nHiggsCandBTagM = 0;
  nHiggsCandBTagT = 0;
  
  TopHadCandak5Jet.clear();
  nTopHadak5Jets = 0;
  nTopHadCandBTagL = 0;
  nTopHadCandBTagM = 0;
  nTopHadCandBTagT = 0;
  
  TopLepCandak5Jet.clear();
  nTopLepak5Jets = 0;
  nTopLepCandBTagL = 0;
  nTopLepCandBTagM = 0;
  nTopLepCandBTagT = 0;
  
  cleanedak5Jets.clear();
  nCleanedak5Jets = 0;
  nCleanedBTagL = 0;
  nCleanedBTagM = 0;
  nCleanedBTagT = 0;

  // Higgs Candidate
  foundHiggsCand = false;
  higgsCand = boosted::SubFilterJet();
  higgsB1Cand = pat::Jet();
  higgsB2Cand = pat::Jet();
  higgsGCand = pat::Jet();

  // Hadronic Top Candidate
  foundTopHadCand = false;
  topHadCand = boosted::HEPTopJet();
  topHadBCand = pat::Jet();
  topHadW1Cand = pat::Jet();
  topHadW2Cand = pat::Jet();

  // Leptonic Top Candidate
  foundTopLepCand = false;
  topLepBCand = pat::Jet();
}


void BoostedttHEvent::LeptonRec(){
  lepVecCand = BoostedUtils::GetPrimLepVec(input.selectedElectronsLoose,input.selectedMuonsLoose);
}


void BoostedttHEvent::NeutrinoRec(){
  TVector2 metvec(input.pfMets[0].px(),input.pfMets[0].py());
  
  if(lepVecCand.Pt()<=0.001) return;
  
  BoostedUtils::GetNuVecs(lepVecCand,metvec,nu1VecCand,nu2VecCand);
}


// Anti-kt 5 Jets Methods    

void BoostedttHEvent::ak5JetsRec(){

  selectedJets.clear();
  BTagL.clear();
  BTagM.clear();
  BTagT.clear();
  nJets = 0;
  nBTagL = 0;
  nBTagM = 0;
  nBTagT = 0;
  
  cleanedak5Jets.clear();
  nCleanedak5Jets = 0;
  nCleanedBTagL = 0;
  nCleanedBTagM = 0;
  nCleanedBTagT = 0;
  
  for(std::vector<pat::Jet>::const_iterator itJet=input.selectedJets.begin();itJet!=input.selectedJets.end();++itJet){
    if(lepVecCand.Pt()>0.001 && BoostedUtils::DeltaR(lepVecCand,itJet->p4())<.5) continue;
    
    nJets++;
    selectedJets.push_back(*itJet);
    cleanedak5Jets.push_back(*itJet);
  }
  for(std::vector<pat::Jet>::const_iterator itJet=selectedJets.begin();itJet!=selectedJets.end();++itJet){
    if(BoostedUtils::PassesCSV(*itJet,'L')) nBTagL++;
    BTagL.push_back(BoostedUtils::PassesCSV(*itJet,'L'));
    if(BoostedUtils::PassesCSV(*itJet,'M')) nBTagM++;
    BTagM.push_back(BoostedUtils::PassesCSV(*itJet,'M'));
    if(BoostedUtils::PassesCSV(*itJet,'T')) nBTagT++;
    BTagT.push_back(BoostedUtils::PassesCSV(*itJet,'T'));
  }
  
  nCleanedak5Jets = nJets;
  nCleanedBTagL = nBTagL;
  nCleanedBTagM = nBTagM;
  nCleanedBTagT = nBTagT;
}


void BoostedttHEvent::ak5JetsIdentifyHiggsCand(const float jetMatchingThreshold){
  
  HiggsCandak5Jet.clear();
  nHiggsak5Jets = 0;
  nHiggsCandBTagL = 0;
  nHiggsCandBTagM = 0;
  nHiggsCandBTagT = 0;
  
  for(std::vector<pat::Jet>::const_iterator itJet=selectedJets.begin();itJet!=selectedJets.end();++itJet){
    if((higgsB1Cand.pt()>.001 && BoostedUtils::DeltaR(higgsB1Cand,*itJet) < jetMatchingThreshold)
    || (higgsB2Cand.pt()>.001 && BoostedUtils::DeltaR(higgsB2Cand,*itJet) < jetMatchingThreshold)){
      
      HiggsCandak5Jet.push_back(true);
      nHiggsak5Jets++;
      int iJet = itJet-selectedJets.begin();
      if(BTagL[iJet]) nHiggsCandBTagL++;
      if(BTagM[iJet]) nHiggsCandBTagM++;
      if(BTagT[iJet]) nHiggsCandBTagT++;
    }
    else
      HiggsCandak5Jet.push_back(false);
  }
}


void BoostedttHEvent::ak5JetsIdentifyTopHadCand(const float jetMatchingThreshold){
  
  TopHadCandak5Jet.clear();
  nTopHadak5Jets = 0;
  nTopHadCandBTagL = 0;
  nTopHadCandBTagM = 0;
  nTopHadCandBTagT = 0;
  
  for(std::vector<pat::Jet>::const_iterator itJet=selectedJets.begin();itJet!=selectedJets.end();++itJet){
    if((topHadBCand.pt()>.001 && BoostedUtils::DeltaR(topHadBCand,*itJet) < jetMatchingThreshold)
    || (topHadW1Cand.pt()>.001 && BoostedUtils::DeltaR(topHadW1Cand,*itJet) < jetMatchingThreshold)
    || (topHadW2Cand.pt()>.001 && BoostedUtils::DeltaR(topHadW2Cand,*itJet) < jetMatchingThreshold)){
      TopHadCandak5Jet.push_back(true);
      nTopHadak5Jets++;
      int iJet = itJet-selectedJets.begin();
      if(BTagL[iJet]) nTopHadCandBTagL++;
      if(BTagM[iJet]) nTopHadCandBTagM++;
      if(BTagT[iJet]) nTopHadCandBTagT++;
    }
    else
      TopHadCandak5Jet.push_back(false);
  }
}


void BoostedttHEvent::ak5JetsIdentifyTopLepCand(const float jetMatchingThreshold){
  
  TopLepCandak5Jet.clear();
  nTopLepak5Jets = 0;
  nTopLepCandBTagL = 0;
  nTopLepCandBTagM = 0;
  nTopLepCandBTagT = 0;
  
  for(std::vector<pat::Jet>::const_iterator itJet=selectedJets.begin();itJet!=selectedJets.end();++itJet){
    if(topLepBCand.pt()>0.001 && BoostedUtils::DeltaR(topLepBCand,*itJet) < jetMatchingThreshold){
      TopLepCandak5Jet.push_back(true);
      nTopLepak5Jets++;
      int iJet = itJet-selectedJets.begin();
      if(BTagL[iJet]) nTopLepCandBTagL++;
      if(BTagM[iJet]) nTopLepCandBTagM++;
      if(BTagT[iJet]) nTopLepCandBTagT++;
    }
    else
      TopLepCandak5Jet.push_back(false);
  }
}


void BoostedttHEvent::ak5JetsClean(bool cleanHiggsCand, bool cleanTopHadCand, bool cleanTopLepCand){
  
  cleanedak5Jets.clear();
  nCleanedak5Jets = 0;
  nCleanedBTagL = 0;
  nCleanedBTagM = 0;
  nCleanedBTagT = 0;

  for(std::vector<pat::Jet>::const_iterator itJet=selectedJets.begin();itJet!=selectedJets.end();++itJet){
    int iJet = itJet-selectedJets.begin();
    if(cleanHiggsCand && HiggsCandak5Jet[iJet]) continue;
    if(cleanTopHadCand && TopHadCandak5Jet[iJet]) continue;
    if(cleanTopLepCand && TopLepCandak5Jet[iJet]) continue;
    
    nCleanedak5Jets++;
    if(BTagL[iJet]) nCleanedBTagL++;
    if(BTagM[iJet]) nCleanedBTagM++;
    if(BTagT[iJet]) nCleanedBTagT++;
    
    cleanedak5Jets.push_back(*itJet);
  }
}


void BoostedttHEvent::HiggsCandBoostedRec(HiggsTagger* higgstagger, const float higgsjetptcut, const float higgsjetetacut, const bool cleanTopHadCand, const bool cleanTopLepCand,  const float fatjetCleaningThreshold, const float subjetCleaningThreshold){
  
  higgsCand = boosted::SubFilterJet();
  higgsB1Cand = pat::Jet();
  higgsB2Cand = pat::Jet();
  higgsGCand = pat::Jet();
  
  float maxHiggsTag=-1.1;
  if(verbose) std::cout << input.selectedSubFilterJets.size() << " CA 1.2 jets"  << std::endl;
  for(std::vector<boosted::SubFilterJet>::const_iterator itJet=input.selectedSubFilterJets.begin();itJet!=input.selectedSubFilterJets.end();++itJet){
    
    if(itJet->fatjet.pt()<higgsjetptcut || fabs(itJet->fatjet.eta())>higgsjetetacut) continue;
    if(verbose) std::cout << " CA 1.2 jet passes eta/pt cuts"  << std::endl;

    std::vector<pat::Jet> cleanedFilterjets = itJet->filterjets;
    
    if((cleanTopHadCand && foundTopHadCand) || (cleanTopLepCand && foundTopLepCand)){
      
      if(cleanTopHadCand && foundTopHadCand){
        if(BoostedUtils::DeltaR(topHadCand.fatjet,itJet->fatjet)<fatjetCleaningThreshold) continue;
      }
      
      cleanedFilterjets.clear();
      
      for(std::vector<pat::Jet>::const_iterator itFilt=itJet->filterjets.begin();itFilt!=itJet->filterjets.end();++itFilt){
      
        if(cleanTopHadCand && foundTopHadCand){
          if(topHadCand.W1.pt()>0.001 && BoostedUtils::DeltaR(topHadCand.W1,*itFilt)<subjetCleaningThreshold) continue;
          if(topHadCand.W2.pt()>0.001 && BoostedUtils::DeltaR(topHadCand.W2,*itFilt)<subjetCleaningThreshold) continue;
          if(topHadCand.nonW.pt()>0.001 && BoostedUtils::DeltaR(topHadCand.nonW,*itFilt)<subjetCleaningThreshold) continue;
        }
        if(cleanTopLepCand && foundTopLepCand){
         if(topLepBCand.pt()>0.001 && BoostedUtils::DeltaR(topLepBCand,*itFilt)<subjetCleaningThreshold) continue;
        }
        
        cleanedFilterjets.push_back(*itFilt);
      }
    }
    if(verbose) std::cout << "found " << cleanedFilterjets.size() << " cleaned filterjets"  << std::endl;
    float tag = higgstagger->GetHiggsTag(*itJet);
    if(verbose) std::cout << "higgs tag of fat jet is " << tag  << std::endl;    
    if(tag>maxHiggsTag){
      
      std::vector<pat::Jet> sortedFilterjets = BoostedUtils::GetHiggsFilterJets(cleanedFilterjets);
      
      maxHiggsTag = tag;
      higgsCand = *itJet;
      if(sortedFilterjets.size()>0) higgsB1Cand = sortedFilterjets[0];
      if(sortedFilterjets.size()>1) higgsB2Cand = sortedFilterjets[1];
      if(sortedFilterjets.size()>2) higgsGCand = sortedFilterjets[2];
      
      HiggsTag_HiggsCand = tag;
      foundHiggsCand = true;
    }
  }
  if(verbose){
    if(foundHiggsCand) std::cout << "found higgs candidate, max tag " << maxHiggsTag << std::endl;
    else std::cout << "did not find higgs candidate, max tag " << maxHiggsTag << std::endl;
  }
}


void BoostedttHEvent::HiggsCandRec(){                                                                    // Non Boosted Higgs Reconstruction by Delta R and Loose Btags
  
  higgsCand = boosted::SubFilterJet();
  higgsB1Cand = pat::Jet();
  higgsB2Cand = pat::Jet();
  higgsGCand = pat::Jet();
                                                                                                    // Optimization of BTag-DeltaR Relation is required
  if(nCleanedak5Jets<2) return;
  
  std::vector<pat::Jet> candJets = BoostedUtils::GetHiggsFilterJets(cleanedak5Jets);
  
  if(candJets.size()>0) higgsB1Cand = candJets[0];
  if(candJets.size()>1) higgsB2Cand = candJets[1];
  if(candJets.size()>2) higgsGCand = candJets[2];
}


void BoostedttHEvent::TopHadCandBoostedRec(TopTagger toptagger,const float topjetptcut, const float topjetetacut){
  topHadCand = boosted::HEPTopJet();
  topHadBCand = pat::Jet();
  topHadW1Cand = pat::Jet();
  topHadW2Cand = pat::Jet();
  
  float maxTopTag=-1.1;

  for(std::vector<boosted::HEPTopJet>::const_iterator itJet=input.selectedHEPTopJets.begin();itJet!=input.selectedHEPTopJets.end();++itJet){
  
    if(itJet->fatjet.pt()<topjetptcut || fabs(itJet->fatjet.eta())>topjetetacut) continue;
    
    float tag = toptagger.GetTopTag(*itJet);
    
    if(tag>maxTopTag) {
      maxTopTag = tag;
      topHadCand = *itJet;
      
      foundTopHadCand = true;
    }
  }

 
  if(foundTopHadCand){
    if(topHadCand.nonW.bDiscriminator(btagger)>topHadCand.W1.bDiscriminator(btagger) && topHadCand.nonW.bDiscriminator(btagger)>topHadCand.W2.bDiscriminator(btagger)){
      topHadW1Cand = topHadCand.W1;
      topHadW2Cand = topHadCand.W2;
      topHadBCand = topHadCand.nonW;  
    }
    else if(topHadCand.W1.bDiscriminator(btagger)>topHadCand.W2.bDiscriminator(btagger) && topHadCand.W1.bDiscriminator(btagger)>topHadCand.nonW.bDiscriminator(btagger)){
      topHadBCand = topHadCand.W1;
      if(topHadCand.nonW.pt()>topHadCand.W2.pt()){
        topHadW1Cand = topHadCand.nonW;
        topHadW2Cand = topHadCand.W2;
      }
      else{
        topHadW1Cand = topHadCand.W2;
        topHadW2Cand = topHadCand.nonW;
      }
    }
    else if(topHadCand.W2.bDiscriminator(btagger)>topHadCand.W1.bDiscriminator(btagger) && topHadCand.W2.bDiscriminator(btagger)>topHadCand.nonW.bDiscriminator(btagger)){
      topHadBCand = topHadCand.W2;
      if(topHadCand.nonW.pt()>topHadCand.W1.pt()){
        topHadW1Cand = topHadCand.nonW;
        topHadW2Cand = topHadCand.W1;
      }
      else{
        topHadW1Cand = topHadCand.W1;
        topHadW2Cand = topHadCand.nonW;
      }
    }
  }
  if(verbose){
    if(foundTopHadCand) std:: cout << "found top had, max top tag: " <<maxTopTag << std::endl;
    else std::cout << "did not find top had" << std::endl;
  }
}


void BoostedttHEvent::TopHadCandRec(){
  
  topHadCand = boosted::HEPTopJet();
  topHadBCand = pat::Jet();
  topHadW1Cand = pat::Jet();
  topHadW2Cand = pat::Jet();
  
  float chi2 = 999;
  
  double mWhad = 82.4;
  double sigmamWhad = 11.9;
  double mtophad = 173.2;
  double sigmamtophad = 24.2;
  
  if(nCleanedak5Jets < 3) return;
  
  for(size_t iTopHadQ2=0;iTopHadQ2<cleanedak5Jets.size();iTopHadQ2++){
    for(size_t iTopHadQ1=0;iTopHadQ1<iTopHadQ2;iTopHadQ1++){
      for(size_t iTopHadB=0;iTopHadB<cleanedak5Jets.size();iTopHadB++){
        
        if(iTopHadB == iTopHadQ1 || iTopHadB == iTopHadQ2) continue;

        if(nCleanedBTagM>0 && !BoostedUtils::PassesCSV(cleanedak5Jets[iTopHadB],'M')) continue;
        
        math::XYZTLorentzVector topHadW1VecHyp = cleanedak5Jets[iTopHadQ1].p4();
        math::XYZTLorentzVector topHadW2VecHyp = cleanedak5Jets[iTopHadQ2].p4();
        math::XYZTLorentzVector topHadBVecHyp = cleanedak5Jets[iTopHadB].p4();
        
        float mWHadHyp = (topHadW1VecHyp + topHadW2VecHyp).M();
        float mTopHadHyp = (topHadBVecHyp + topHadW1VecHyp + topHadW2VecHyp).M();
        
        float chi2Hyp = pow(mWHadHyp-mWhad,2)/pow(sigmamWhad,2);
        chi2Hyp += pow(mTopHadHyp-mtophad,2)/pow(sigmamtophad,2);
        
        if(chi2Hyp<chi2){
          topHadW1Cand = cleanedak5Jets[iTopHadQ1];
          topHadW2Cand = cleanedak5Jets[iTopHadQ2];
          topHadBCand = cleanedak5Jets[iTopHadB];
          chi2 = chi2Hyp;

          foundTopHadCand = true;
        }
      }
    }
  }
}


void BoostedttHEvent::TopLepCandRec(){
  
  topLepBCand = pat::Jet();
  
  float chi2 = 999;
  
  double mtoplep = 169.7;
  double sigmamtoplep = 23.6;
  
  if(nCleanedak5Jets < 1) return;
  
  for(size_t iTopLepB=0;iTopLepB<cleanedak5Jets.size();iTopLepB++){

    if(nCleanedBTagM>0 && !BoostedUtils::PassesCSV(cleanedak5Jets[iTopLepB],'M')) continue;
    
    math::XYZTLorentzVector topLepBVecHyp = cleanedak5Jets[iTopLepB].p4();
    math::XYZTLorentzVector topLepNuVecHyp;
    math::XYZTLorentzVector topLepVecCandHyp;

    float mTopLep1Hyp = (topLepBVecHyp + lepVecCand + nu1VecCand).M();
    float mTopLep2Hyp = (topLepBVecHyp + lepVecCand + nu2VecCand).M();
    float mTopLepHyp = -1;
    
    if(fabs(mTopLep1Hyp-mtoplep)<fabs(mTopLep2Hyp-mtoplep)){
      mTopLepHyp = mTopLep1Hyp;
      topLepNuVecHyp = nu1VecCand;
      topLepVecCandHyp = topLepBVecHyp + lepVecCand + nu1VecCand;
    }
    else{
      mTopLepHyp = mTopLep2Hyp;
      topLepNuVecHyp = nu2VecCand;
      topLepVecCandHyp = topLepBVecHyp + lepVecCand + nu2VecCand;
    }

    float chi2Hyp = pow(mTopLepHyp-mtoplep,2)/pow(sigmamtoplep,2);

    if(chi2Hyp<chi2){
      topLepBCand = cleanedak5Jets[iTopLepB];
      nuVecCand = topLepNuVecHyp;
      chi2 = chi2Hyp;

      foundTopLepCand = true;
    }
  }
}


void BoostedttHEvent::TopPairCandRec(){
  
  topHadCand = boosted::HEPTopJet();
  topHadBCand = pat::Jet();
  topHadW1Cand = pat::Jet();
  topHadW2Cand = pat::Jet();
  topLepBCand = pat::Jet();
  
  float chi2 = 999;
  
  double mWhad = 82.4;
  double sigmamWhad = 11.9;
  double mtophad = 173.2;
  double sigmamtophad = 24.2;
  double mtoplep = 169.7;
  double sigmamtoplep = 23.6;
  
  if(nCleanedak5Jets < 4) return;
  
  for(size_t iTopHadQ2=0;iTopHadQ2<cleanedak5Jets.size();iTopHadQ2++){
    for(size_t iTopHadQ1=0;iTopHadQ1<iTopHadQ2;iTopHadQ1++){
      for(size_t iTopHadB=0;iTopHadB<cleanedak5Jets.size();iTopHadB++){
        for(size_t iTopLepB=0;iTopLepB<cleanedak5Jets.size();iTopLepB++){

          if(iTopLepB == iTopHadB || iTopLepB == iTopHadQ1 || iTopLepB == iTopHadQ2 || iTopHadB == iTopHadQ1 || iTopHadB == iTopHadQ2) continue;

          if(nCleanedBTagM>1 && !(BoostedUtils::PassesCSV(cleanedak5Jets[iTopHadB],'M') && BoostedUtils::PassesCSV(cleanedak5Jets[iTopLepB],'M'))) continue;
          if(nCleanedBTagM==1 && !(BoostedUtils::PassesCSV(cleanedak5Jets[iTopHadB],'M') || BoostedUtils::PassesCSV(cleanedak5Jets[iTopLepB],'M'))) continue;

          math::XYZTLorentzVector topHadW1VecHyp = cleanedak5Jets[iTopHadQ1].p4();
          math::XYZTLorentzVector topHadW2VecHyp = cleanedak5Jets[iTopHadQ2].p4();
          math::XYZTLorentzVector topHadBVecHyp = cleanedak5Jets[iTopHadB].p4();
          math::XYZTLorentzVector topLepBVecHyp = cleanedak5Jets[iTopLepB].p4();
          math::XYZTLorentzVector topLepNuVecHyp;
          math::XYZTLorentzVector topLepVecCandHyp;

          float mWHadHyp = (topHadW1VecHyp + topHadW2VecHyp).M();
          float mTopHadHyp = (topHadBVecHyp + topHadW1VecHyp + topHadW2VecHyp).M();
          float mTopLep1Hyp = (topLepBVecHyp + lepVecCand + nu1VecCand).M();
          float mTopLep2Hyp = (topLepBVecHyp + lepVecCand + nu2VecCand).M();
          float mTopLepHyp = -1;
          
          if(fabs(mTopLep1Hyp-mtoplep)<fabs(mTopLep2Hyp-mtoplep)){
            mTopLepHyp = mTopLep1Hyp;
            topLepNuVecHyp = nu1VecCand;
            topLepVecCandHyp = topLepBVecHyp + lepVecCand + nu1VecCand;
          }
          else{
            mTopLepHyp = mTopLep2Hyp;
            topLepNuVecHyp = nu2VecCand;
            topLepVecCandHyp = topLepBVecHyp + lepVecCand + nu2VecCand;
          }

          float chi2Hyp = pow(mWHadHyp-mWhad,2)/pow(sigmamWhad,2);
          chi2Hyp += pow(mTopHadHyp-mtophad,2)/pow(sigmamtophad,2);
          chi2Hyp += pow(mTopLepHyp-mtoplep,2)/pow(sigmamtoplep,2);

          if(chi2Hyp<chi2){
            topHadW1Cand = cleanedak5Jets[iTopHadQ1];
            topHadW2Cand = cleanedak5Jets[iTopHadQ2];
            topHadBCand = cleanedak5Jets[iTopHadB];
            topLepBCand = cleanedak5Jets[iTopLepB];
            nuVecCand = topLepNuVecHyp;
            chi2 = chi2Hyp;
            
            foundTopHadCand = true;
            foundTopLepCand = true;
          }
        }
      }
    }
  }
}


void BoostedttHEvent::BoostedTopHiggsEventRec(TopTagger toptagger, HiggsTagger* higgstagger){
  
  ResetEvent();
  
  LeptonRec();
  NeutrinoRec();
  ak5JetsRec();
  
  TopHadCandBoostedRec(toptagger,200.,2.);
  ak5JetsIdentifyTopHadCand(.3);
  
  HiggsCandBoostedRec(higgstagger,200.,2.,true,false,1.5,.2);
  ak5JetsIdentifyHiggsCand(.3);
  
  ak5JetsClean(true,true,false);
  
  TopLepCandRec();
  ak5JetsIdentifyTopLepCand(.3);
}


void BoostedttHEvent::BoostedHiggsEventRec(HiggsTagger* higgstagger){
  
  ResetEvent();
  
  LeptonRec();
  NeutrinoRec();
  ak5JetsRec();
  
  HiggsCandBoostedRec(higgstagger,200.,2.,false,false);
  ak5JetsIdentifyHiggsCand(.3);
  
  ak5JetsClean(true,false,false);
  
  TopPairCandRec();
  ak5JetsIdentifyTopHadCand(.3);
  ak5JetsIdentifyTopLepCand(.3);
} 


void BoostedttHEvent::BoostedTopEventRec(TopTagger toptagger){
  
  ResetEvent();
  
  LeptonRec();
  NeutrinoRec();
  ak5JetsRec();
  
  TopHadCandBoostedRec(toptagger,200.,2.);
  ak5JetsIdentifyTopHadCand(.3);
  
  ak5JetsClean(false,true,false);
  
  TopLepCandRec();
  ak5JetsIdentifyTopLepCand(.3);
  
  //ak5JetsClean(false,true,true);
  
  HiggsCandRec();
  ak5JetsIdentifyHiggsCand(.3);
}


const InputCollections& BoostedttHEvent::GetInput(){
  return input;
} 


math::XYZTLorentzVector BoostedttHEvent::GetLeptonVec(){
  return lepVecCand;
} 

    
math::XYZTLorentzVector BoostedttHEvent::GetNeutrinoVec(){
  return nuVecCand;
}


math::XYZTLorentzVector BoostedttHEvent::GetNeutrino1Vec(){
  return nu1VecCand;
}


math::XYZTLorentzVector BoostedttHEvent::GetNeutrino2Vec(){
  return nu2VecCand;
}


std::vector<pat::Jet> BoostedttHEvent::Getak5JetsAll(){
  return selectedJets;
}


int BoostedttHEvent::GetNJets(){
  return nJets;
}


int BoostedttHEvent::GetNBTagL(){
  return nBTagL;
}


int BoostedttHEvent::GetNBTagM(){
  return nBTagM;
}

int BoostedttHEvent::GetNBTagT(){
  return nBTagT;
}

float BoostedttHEvent::GetAverageCSV(){
  
  float avgCSV = 0.;
  for(std::vector<pat::Jet>::const_iterator itJet=selectedJets.begin();itJet!=selectedJets.end();++itJet)
    avgCSV += fmax(itJet->bDiscriminator(btagger),0.);
    
  return avgCSV/nJets;
}


int BoostedttHEvent::GetNHiggsak5Jets(){
  return nHiggsak5Jets;
}


int BoostedttHEvent::GetNHiggsCandBTagL(){
  return nHiggsCandBTagL;
}


int BoostedttHEvent::GetNHiggsCandBTagM(){
  return nHiggsCandBTagM;
}


int BoostedttHEvent::GetNHiggsCandBTagT(){
  return nHiggsCandBTagT;
}


float BoostedttHEvent::GetAverageCSVHiggsCand(){
  
  float avgCSV = 0.;
  
  for(size_t iJet=0;iJet<selectedJets.size();iJet++){
    if(!HiggsCandak5Jet[iJet]) continue;
    avgCSV += fmax(selectedJets[iJet].bDiscriminator(btagger),0.);
  }
    
  return avgCSV/nHiggsak5Jets;
}


int BoostedttHEvent::GetNTopHadak5Jets(){
  return nTopHadak5Jets;
}


int BoostedttHEvent::GetNTopHadCandBTagL(){
  return nTopHadCandBTagL;
}


int BoostedttHEvent::GetNTopHadCandBTagM(){
  return nTopHadCandBTagM;
}


int BoostedttHEvent::GetNTopHadCandBTagT(){
  return nTopHadCandBTagT;
}


float BoostedttHEvent::GetAverageCSVTopHadCand(){
  
  float avgCSV = 0.;
  
  for(size_t iJet=0;iJet<selectedJets.size();iJet++){
    if(!TopHadCandak5Jet[iJet]) continue;
    avgCSV += fmax(selectedJets[iJet].bDiscriminator(btagger),0.);
  }
    
  return avgCSV/nTopHadak5Jets;
}


int BoostedttHEvent::GetNTopLepak5Jets(){
  return nTopLepak5Jets;
}


int BoostedttHEvent::GetNTopLepCandBTagL(){
  return nTopLepCandBTagL;
}


int BoostedttHEvent::GetNTopLepCandBTagM(){
  return nTopLepCandBTagM;
}


int BoostedttHEvent::GetNTopLepCandBTagT(){
  return nTopLepCandBTagT;
}


float BoostedttHEvent::GetAverageCSVTopLepCand(){
  
  float avgCSV = 0.;
  
  for(size_t iJet=0;iJet<selectedJets.size();iJet++){
    if(!TopLepCandak5Jet[iJet]) continue;
    avgCSV += fmax(selectedJets[iJet].bDiscriminator(btagger),0.);
  }
    
  return avgCSV/nTopLepak5Jets;
}


std::vector<pat::Jet> BoostedttHEvent::Getak5JetsCleaned(){
  return cleanedak5Jets;
}


int BoostedttHEvent::GetNCleanedak5Jets(){
  return nCleanedak5Jets;
}


int BoostedttHEvent::GetNCleanedBTagL(){
  return nCleanedBTagL;
}


int BoostedttHEvent::GetNCleanedBTagM(){
  return nCleanedBTagM;
}


int BoostedttHEvent::GetNCleanedBTagT(){
  return nCleanedBTagT;
}


float BoostedttHEvent::GetAverageCSVClean(){
  
  float avgCSV = 0.;
  
  for(size_t iJet=0;iJet<cleanedak5Jets.size();iJet++)
    avgCSV += fmax(cleanedak5Jets[iJet].bDiscriminator(btagger),0.);
    
  return avgCSV/nCleanedak5Jets;
}


boosted::SubFilterJet BoostedttHEvent::GetHiggsCandBoosted(){
  if(!foundHiggsCand) return boosted::SubFilterJet();
  
  return higgsCand;
}


pat::Jet BoostedttHEvent::GetHiggsB1Cand(){
  if(!foundHiggsCand) return pat::Jet();

  return higgsB1Cand;
}


pat::Jet BoostedttHEvent::GetHiggsB2Cand(){
  if(!foundHiggsCand) return pat::Jet();

  return higgsB2Cand;
}


pat::Jet BoostedttHEvent::GetHiggsGCand(){
  if(!foundHiggsCand) return pat::Jet();

  return higgsGCand;
}


math::XYZTLorentzVector BoostedttHEvent::GetHiggsCandVec3(){
  if(!foundHiggsCand) return math::XYZTLorentzVector();

  math::XYZTLorentzVector HiggsCandVec3 = higgsB1Cand.p4()+higgsB2Cand.p4()+higgsGCand.p4();

  return HiggsCandVec3;
}


math::XYZTLorentzVector BoostedttHEvent::GetHiggsCandVec2(){
  if(!foundHiggsCand) return math::XYZTLorentzVector();

  math::XYZTLorentzVector HiggsCandVec2 = higgsB1Cand.p4()+higgsB2Cand.p4();

  return HiggsCandVec2;
}


boosted::HEPTopJet BoostedttHEvent::GetTopHadCandBoosted(){
  if(!foundTopHadCand) return boosted::HEPTopJet();
  
  return topHadCand;
}


pat::Jet BoostedttHEvent::GetTopHadBCand(){
  if(!foundTopHadCand) return pat::Jet();
  
  return topHadBCand;
}


pat::Jet BoostedttHEvent::GetTopHadW1Cand(){
  if(!foundTopHadCand) return pat::Jet();
  
  return topHadW1Cand;
}


pat::Jet BoostedttHEvent::GetTopHadW2Cand(){
  if(!foundTopHadCand) return pat::Jet();
  
  return topHadW2Cand;
}


math::XYZTLorentzVector BoostedttHEvent::GetTopHadCandVec(){
  if(!foundTopHadCand) return math::XYZTLorentzVector();
  
  math::XYZTLorentzVector TopHadCandVec = topHadBCand.p4()+topHadW1Cand.p4()+topHadW2Cand.p4();
  
  return TopHadCandVec;
}


math::XYZTLorentzVector BoostedttHEvent::GetWHadCandVec(){
  if(!foundTopHadCand) return math::XYZTLorentzVector();
  
  math::XYZTLorentzVector WHadCandVec = topHadW1Cand.p4()+topHadW2Cand.p4();
  
  return WHadCandVec;
}


pat::Jet BoostedttHEvent::GetTopLepBCand(){
  if(!foundTopLepCand) return pat::Jet();
  
  return topLepBCand;
}


math::XYZTLorentzVector BoostedttHEvent::GetTopLepCandVec(){
  if(!foundTopLepCand) return math::XYZTLorentzVector();
  
  math::XYZTLorentzVector TopLepCandVec = topLepBCand.p4()+lepVecCand+nuVecCand;
  
  return TopLepCandVec;
}


math::XYZTLorentzVector BoostedttHEvent::GetWLepCandVec(){

  math::XYZTLorentzVector WLepCandVec = lepVecCand+nuVecCand;

  return WLepCandVec;
}

bool BoostedttHEvent::GetFoundTopHad(){
  if(foundTopHadCand) return true; 
  else return false;
  
}

float BoostedttHEvent::GetHiggsTag(){
  if(foundHiggsCand) return HiggsTag_HiggsCand; 
  else return -1.1;
  
}
