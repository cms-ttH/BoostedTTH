#include "BoostedTTH/BoostedAnalyzer/interface/BoostedttHEvent.hpp"


BoostedttHEvent::BoostedttHEvent():input(0),verbose(false),btagger("pfCombinedInclusiveSecondaryVertexV2BJetTags"){
  ResetEvent();
}


BoostedttHEvent::~BoostedttHEvent(){

}

void BoostedttHEvent::SetInput(const InputCollections* input_){
    input = input_;
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
  higgsCandIndex = -1;
  higgsCandTag = -1.1;
  higgsCand = boosted::BoostedJet();
  higgsCandFromAk4C = boosted::Ak4Cluster();
  higgsB1Cand = pat::Jet();
  higgsB2Cand = pat::Jet();
  higgsGCand = pat::Jet();
  useAk4Cluster = false;

  // Hadronic Top Candidate
  foundTopHadCand = false;
  topHadCandIndex = -1;
  topHadCandTag = -1.1;
  topHadCand = boosted::BoostedJet();
  topHadBCand = pat::Jet();
  topHadW1Cand = pat::Jet();
  topHadW2Cand = pat::Jet();

  // Leptonic Top Candidate
  foundTopLepCand = false;
  topLepBCand = pat::Jet();
}


void BoostedttHEvent::LeptonRec(){
  lepVecCand = BoostedUtils::GetPrimLepVec(input->selectedElectronsLoose,input->selectedMuonsLoose);
}


void BoostedttHEvent::NeutrinoRec(){
  TVector2 metvec(input->correctedMET.px(),input->correctedMET.py());

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

  selectedJets = input->selectedJets;
  cleanedak5Jets = input->selectedJets;
  nJets = selectedJets.size();

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
    else{
      HiggsCandak5Jet.push_back(false);
    }
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
    else{
      TopHadCandak5Jet.push_back(false);
    }
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
    else{
      TopLepCandak5Jet.push_back(false);
    }
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


void BoostedttHEvent::ak4ClusterHiggsCandBoostedRec(const bool cleanTopHadCand, const bool cleanTopLepCand, const float subjetCleaningThreshold){
  higgsCand = boosted::BoostedJet();
  higgsB1Cand = pat::Jet();
  higgsB2Cand = pat::Jet();
  higgsGCand = pat::Jet();
  useAk4Cluster = true;

  // loop over ak4 cluster
  for(std::vector<boosted::Ak4Cluster>::const_iterator itAk4Clu=input->selectedAk4Cluster.begin();itAk4Clu!=input->selectedAk4Cluster.end();++itAk4Clu){
    int iAk4Clu = itAk4Clu - input->selectedAk4Cluster.begin();
    if(cleanTopHadCand && foundTopHadCand && iAk4Clu==topHadCandIndex) continue;

    std::vector<pat::Jet> cleanedAk4jets = (*itAk4Clu).ak4jets;

    if((*itAk4Clu).ak4jets.size()<2) continue;
    if(verbose) std::cout << "found " << (*itAk4Clu).ak4jets.size() << " cleaned Ak4 jets"  << std::endl;

    // Higgs tagger (SecondCSV)
    std::vector<pat::Jet> sortedAk4jets = BoostedUtils::GetHiggsFilterJets((*itAk4Clu).ak4jets);
    float tag = MiniAODHelper::GetJetCSV(sortedAk4jets[1],"pfCombinedInclusiveSecondaryVertexV2BJetTags");
    if(verbose) std::cout << "Ak4 higgs tag of fat jet is " << tag  << std::endl;

    if(tag>higgsCandTag){
      higgsCandTag = tag;
      foundHiggsCand = true;
      higgsCandIndex = iAk4Clu;

      higgsCandFromAk4C = *itAk4Clu;
      if(sortedAk4jets.size()>0) higgsB1Cand = sortedAk4jets[0];
      if(sortedAk4jets.size()>1) higgsB2Cand = sortedAk4jets[1];
      if(sortedAk4jets.size()>2) higgsGCand = sortedAk4jets[2];
    }
  }
  if(verbose){
    if(foundHiggsCand) std::cout << "Ak4: found higgs candidate, max tag " << higgsCandTag << std::endl;
    else std::cout << "Ak4: did not find higgs candidate" << std::endl;
  }
}

void BoostedttHEvent::ak4JetsHiggsCandBoostedRec(const bool cleanTopHadCand, const bool cleanTopLepCand, const float subjetCleaningThreshold){
  higgsCand = boosted::BoostedJet();
  higgsB1Cand = pat::Jet();
  higgsB2Cand = pat::Jet();
  higgsGCand = pat::Jet();
  float fatjetRadius = 1.5;
  useAk4Cluster = false;

  // loop over fatjets
  for(std::vector<boosted::BoostedJet>::const_iterator itBooJet=input->selectedBoostedJets.begin();itBooJet!=input->selectedBoostedJets.end();++itBooJet){
    int iBooJet = itBooJet - input->selectedBoostedJets.begin();
    if(cleanTopHadCand && foundTopHadCand && iBooJet==topHadCandIndex) continue;

    pat::Jet fatjet = itBooJet->fatjet;
    std::vector<pat::Jet> cleanedAk4jets;

    // loop over ak4jets
    for(std::vector<pat::Jet>::const_iterator itAk4Jet=selectedJets.begin();itAk4Jet!=selectedJets.end();++itAk4Jet){
      // Delta R matching between ak4Jets and fatjets C/A 1.5
      if (BoostedUtils::DeltaR(*itAk4Jet, fatjet) < fatjetRadius){
        if(cleanTopLepCand && foundTopLepCand){
          if(topLepBCand.pt()>0. && BoostedUtils::DeltaR(topLepBCand,*itAk4Jet)<subjetCleaningThreshold) continue;
        }
        cleanedAk4jets.push_back(*itAk4Jet);
      }
    }

    if(cleanedAk4jets.size()<2) continue;
    if(verbose) std::cout << "found " << cleanedAk4jets.size() << " cleaned Ak4 jets"  << std::endl;

    // Higgs tagger (SecondCSV)
    std::vector<pat::Jet> sortedAk4jets = BoostedUtils::GetHiggsFilterJets(cleanedAk4jets);
    float tag = MiniAODHelper::GetJetCSV(sortedAk4jets[1],"pfCombinedInclusiveSecondaryVertexV2BJetTags");
    if(verbose) std::cout << "Ak4 higgs tag of fat jet is " << tag  << std::endl;


    if(tag>higgsCandTag){
      higgsCandTag = tag;
      foundHiggsCand = true;
      higgsCandIndex = iBooJet;

      higgsCand = *itBooJet;
      if(sortedAk4jets.size()>0) higgsB1Cand = sortedAk4jets[0];
      if(sortedAk4jets.size()>1) higgsB2Cand = sortedAk4jets[1];
      if(sortedAk4jets.size()>2) higgsGCand = sortedAk4jets[2];
    }
  }
  if(verbose){
    if(foundHiggsCand) std::cout << "Ak4: found higgs candidate, max tag " << higgsCandTag << std::endl;
    else std::cout << "Ak4: did not find higgs candidate" << std::endl;
  }
}


void BoostedttHEvent::HiggsCandBoostedRec(const boosted::SubjetType subjettype, HiggsTagger higgstagger, const bool cleanTopHadCand, const bool cleanTopLepCand, const float subjetCleaningThreshold){

  higgsCand = boosted::BoostedJet();
  higgsB1Cand = pat::Jet();
  higgsB2Cand = pat::Jet();
  higgsGCand = pat::Jet();

  if(verbose) std::cout << input->selectedBoostedJets.size() << " CA 1.2 jets"  << std::endl;
  for(std::vector<boosted::BoostedJet>::const_iterator itJet=input->selectedBoostedJets.begin();itJet!=input->selectedBoostedJets.end();++itJet){

    int iJet = itJet-input->selectedBoostedJets.begin();

    boosted::JetType jetType = BoostedUtils::GetBoostedJetType(*itJet,BoostedJetDisc::None);
    if(jetType != boosted::Higgs && jetType != boosted::NA) continue;

    std::vector<pat::Jet> cleanedSubjets;
    switch(subjettype){
      case boosted::SubjetType::SF_Sub:
      {
        cleanedSubjets = itJet->subjets;
        break;
      }
      case boosted::SubjetType::SF_Filter:
      {
        cleanedSubjets = itJet->filterjets;
        break;
      }
      case boosted::SubjetType::Pruned:
      {
        cleanedSubjets = itJet->prunedsubjets;
        break;
      }
      case boosted::SubjetType::SD:
      {
        cleanedSubjets = itJet->sdsubjets;
        break;
      }
      default:
        cleanedSubjets = itJet->filterjets;
    }

    if(cleanTopHadCand && foundTopHadCand && iJet==topHadCandIndex) continue;

    if(cleanTopLepCand && foundTopLepCand){
      cleanedSubjets.clear();

      for(std::vector<pat::Jet>::const_iterator itFilt=itJet->filterjets.begin();itFilt!=itJet->filterjets.end();++itFilt){
        if(topLepBCand.pt()>0. && BoostedUtils::DeltaR(topLepBCand,*itFilt)<subjetCleaningThreshold) continue;
        cleanedSubjets.push_back(*itFilt);
      }
    }

    if(cleanedSubjets.size()<2) continue;

    boosted::BoostedJet cleanedBoostedJet = *itJet;
    cleanedBoostedJet.filterjets = cleanedSubjets;

    if(verbose) std::cout << "found " << cleanedSubjets.size() << " cleaned filterjets"  << std::endl;
    float tag = higgstagger.GetHiggsTaggerOutput(cleanedBoostedJet);
    if(verbose) std::cout << "higgs tag of fat jet is " << tag  << std::endl;

    if(tag>higgsCandTag){
      higgsCandTag = tag;
      foundHiggsCand = true;
      higgsCandIndex = iJet;

      higgsCand = *itJet;
      std::vector<pat::Jet> sortedFilterjets = BoostedUtils::GetHiggsFilterJets(cleanedSubjets);
      if(sortedFilterjets.size()>0) higgsB1Cand = sortedFilterjets[0];
      if(sortedFilterjets.size()>1) higgsB2Cand = sortedFilterjets[1];
      if(sortedFilterjets.size()>2) higgsGCand = sortedFilterjets[2];
    }
  }
  if(verbose){
    if(foundHiggsCand) std::cout << "found higgs candidate, max tag " << higgsCandTag << std::endl;
    else std::cout << "did not find higgs candidate" << std::endl;
  }
}


void BoostedttHEvent::HiggsCandRec(){                                                                    // Non Boosted Higgs Reconstruction by Delta R and Loose Btags

  higgsCand = boosted::BoostedJet();
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


void BoostedttHEvent::TopHadCandBoostedRec(TopTagger toptagger, const bool cleanTopLepCand, const bool cleanHiggsCand, const float subjetCleaningThreshold){
  topHadCand = boosted::BoostedJet();
  topHadBCand = pat::Jet();
  topHadW1Cand = pat::Jet();
  topHadW2Cand = pat::Jet();

  for(std::vector<boosted::BoostedJet>::const_iterator itJet=input->selectedBoostedJets.begin();itJet!=input->selectedBoostedJets.end();++itJet){

    int iJet = itJet-input->selectedBoostedJets.begin();

    boosted::JetType jetType = BoostedUtils::GetBoostedJetType(*itJet,BoostedJetDisc::None);
    if(jetType != boosted::Top && jetType != boosted::NA) continue;

    if(cleanHiggsCand && foundHiggsCand && iJet==higgsCandIndex) continue;

    if(cleanTopLepCand && foundTopLepCand){
      if(topLepBCand.pt()>0. && BoostedUtils::DeltaR(topLepBCand,itJet->nonW)<subjetCleaningThreshold) continue;
      if(topLepBCand.pt()>0. && BoostedUtils::DeltaR(topLepBCand,itJet->W1)<subjetCleaningThreshold) continue;
      if(topLepBCand.pt()>0. && BoostedUtils::DeltaR(topLepBCand,itJet->W2)<subjetCleaningThreshold) continue;
    }

    float tag = toptagger.GetTopTaggerOutput(*itJet);

    if(tag>topHadCandTag) {
      topHadCandTag = tag;
      foundTopHadCand = true;
      topHadCandIndex = iJet;

      topHadCand = *itJet;
      if(toptagger.GetSubjetAssignment() == TopTag::CSV){
        std::vector<pat::Jet> subjets;
        subjets.push_back(itJet->nonW);
        subjets.push_back(itJet->W1);
        subjets.push_back(itJet->W2);

        BoostedUtils::TopSubjetCSVDef(subjets);

        topHadBCand = subjets.at(0);
        topHadW1Cand = subjets.at(1);
        topHadW2Cand = subjets.at(2);
      }
      else{
        topHadBCand = itJet->nonW;
        topHadW1Cand = itJet->W1;
        topHadW2Cand = itJet->W2;
      }
    }
  }

  if(verbose){
    if(foundTopHadCand) std:: cout << "found top had, max top tag: " <<topHadCandTag << std::endl;
    else std::cout << "did not find top had" << std::endl;
  }
}


void BoostedttHEvent::TopHadCandRec(){

  topHadCand = boosted::BoostedJet();
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

  topHadCand = boosted::BoostedJet();
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


void BoostedttHEvent::BoostedTopHiggsEventRec(TopTagger toptagger, const boosted::SubjetType subjettype, HiggsTagger higgstagger){

  ResetEvent();

  LeptonRec();
  NeutrinoRec();
  ak5JetsRec();

  TopHadCandBoostedRec(toptagger,false,false,.2);
  ak5JetsIdentifyTopHadCand(.3);

  HiggsCandBoostedRec(subjettype,higgstagger,true,false,.2);
  ak5JetsIdentifyHiggsCand(.3);

  ak5JetsClean(true,true,false);

  TopLepCandRec();
  ak5JetsIdentifyTopLepCand(.3);
}


void BoostedttHEvent::BoostedHiggsEventRec(const boosted::SubjetType subjettype, HiggsTagger higgstagger){

  ResetEvent();

  LeptonRec();
  NeutrinoRec();
  ak5JetsRec();

  HiggsCandBoostedRec(subjettype,higgstagger,false,false);
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

  TopHadCandBoostedRec(toptagger,false,false);
  ak5JetsIdentifyTopHadCand(.3);

  ak5JetsClean(false,true,false);

  TopLepCandRec();
  ak5JetsIdentifyTopLepCand(.3);

  //ak5JetsClean(false,true,true);

  HiggsCandRec();
  ak5JetsIdentifyHiggsCand(.3);
}


void BoostedttHEvent::BoostedTopAk4HiggsEventRec(TopTagger toptagger, const boosted::SubjetType subjettype, HiggsTagger higgstagger){

  ResetEvent();

  LeptonRec();
  NeutrinoRec();
  ak5JetsRec();

  TopHadCandBoostedRec(toptagger,false,false,.2);
  ak5JetsIdentifyTopHadCand(.3);

  ak4JetsHiggsCandBoostedRec(true,false,.2);
  ak5JetsIdentifyHiggsCand(.3);

  ak5JetsClean(true,true,false);

  TopLepCandRec();
  ak5JetsIdentifyTopLepCand(.3);
}


void BoostedttHEvent::BoostedTopAk4HiggsFromAk4CEventRec(TopTagger toptagger, const boosted::SubjetType subjettype, HiggsTagger higgstagger){

  ResetEvent();

  LeptonRec();
  NeutrinoRec();
  ak5JetsRec();

  TopHadCandBoostedRec(toptagger,false,false,.2);
  ak5JetsIdentifyTopHadCand(.3);

  ak4ClusterHiggsCandBoostedRec(true,false,.2);
  ak5JetsIdentifyHiggsCand(.3);

  ak5JetsClean(true,true,false);

  TopLepCandRec();
  ak5JetsIdentifyTopLepCand(.3);
}


const InputCollections& BoostedttHEvent::GetInput(){
  return *input;
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
    avgCSV += fmax(MiniAODHelper::GetJetCSV(*itJet,btagger),0.);

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
    avgCSV += fmax(MiniAODHelper::GetJetCSV(selectedJets[iJet],btagger),0.);
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
    avgCSV += fmax(MiniAODHelper::GetJetCSV(selectedJets[iJet],btagger),0.);
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
    avgCSV += fmax(MiniAODHelper::GetJetCSV(selectedJets[iJet],btagger),0.);
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
    avgCSV += fmax(MiniAODHelper::GetJetCSV(cleanedak5Jets[iJet],btagger),0.);

  return avgCSV/nCleanedak5Jets;
}


bool BoostedttHEvent::GetFoundHiggsCand(){
  return foundHiggsCand;
}


int BoostedttHEvent::GetHiggsCandIndex(){
  return higgsCandIndex;
}


float BoostedttHEvent::GetHiggsCandTag(){
  if(foundHiggsCand) return higgsCandTag;
  else return -1.1;
}


boosted::BoostedJet BoostedttHEvent::GetHiggsCandBoosted(){
  if(!foundHiggsCand) return boosted::BoostedJet();

  return higgsCand;
}


boosted::Ak4Cluster BoostedttHEvent::GetHiggsCandFromAk4C(){
  if(!foundHiggsCand) return boosted::Ak4Cluster();

  return higgsCandFromAk4C;
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


bool  BoostedttHEvent::GetUseAk4Cluster(){
  return useAk4Cluster;
}


bool BoostedttHEvent::GetFoundTopHadCand(){
  return foundTopHadCand;
}


int BoostedttHEvent::GetTopHadCandIndex(){
  return topHadCandIndex;
}


float BoostedttHEvent::GetTopHadCandTag(){
  if(foundTopHadCand) return topHadCandTag;
  else return -1.1;
}


boosted::BoostedJet BoostedttHEvent::GetTopHadCandBoosted(){
  if(!foundTopHadCand) return boosted::BoostedJet();

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


bool BoostedttHEvent::GetFoundTopLepCand(){
  return foundTopLepCand;
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


float BoostedttHEvent::GetTTHBB_ME(){
    if(!(foundHiggsCand&&foundTopLepCand&&foundTopHadCand)) return -1;
    TLorentzVector top=BoostedUtils::GetTLorentzVector(topHadBCand.p4()+topHadW1Cand.p4()+topHadW2Cand.p4());
    TLorentzVector topbar=BoostedUtils::GetTLorentzVector(lepVecCand+nuVecCand+topLepBCand.p4());
    TLorentzVector b=BoostedUtils::GetTLorentzVector(higgsB1Cand.p4());
    TLorentzVector bbar=BoostedUtils::GetTLorentzVector(higgsB2Cand.p4());
    return  recoME.GetTTHBBMEsq(top,topbar,b,bbar);

}
float BoostedttHEvent::GetTTBB_ME(){
    if(!(foundHiggsCand&&foundTopLepCand&&foundTopHadCand)) return -1;
    TLorentzVector top=BoostedUtils::GetTLorentzVector(topHadBCand.p4()+topHadW1Cand.p4()+topHadW2Cand.p4());
    TLorentzVector topbar=BoostedUtils::GetTLorentzVector(lepVecCand+nuVecCand+topLepBCand.p4());
    TLorentzVector b=BoostedUtils::GetTLorentzVector(higgsB1Cand.p4());
    TLorentzVector bbar=BoostedUtils::GetTLorentzVector(higgsB2Cand.p4());
    return  recoME.GetTTBBMEsq_onshell(top,topbar,b,bbar);


}
float BoostedttHEvent::Get_MEratio(){
    if(!(foundHiggsCand&&foundTopLepCand&&foundTopHadCand)) return -1;
    TLorentzVector top=BoostedUtils::GetTLorentzVector(topHadBCand.p4()+topHadW1Cand.p4()+topHadW2Cand.p4());
    TLorentzVector topbar=BoostedUtils::GetTLorentzVector(lepVecCand+nuVecCand+topLepBCand.p4());
    TLorentzVector b=BoostedUtils::GetTLorentzVector(higgsB1Cand.p4());
    TLorentzVector bbar=BoostedUtils::GetTLorentzVector(higgsB2Cand.p4());
    float tth_me = recoME.GetTTHBBMEsq(top,topbar,b,bbar);
    float ttbb_me = recoME.GetTTBBMEsq_onshell(top,topbar,b,bbar);
    ttbb_me*=3e3; // make both mes same order
    return  tth_me/(tth_me+ttbb_me);

}
