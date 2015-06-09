#include "BoostedTTH/BoostedAnalyzer/interface/TopTagger.hpp"


TopTagger::TopTagger(){
  
  name = "";

  toplikelihood = false;
  tmva = false;
}


TopTagger::TopTagger(std::string name_, std::string histosPath_): name(name_) {
  
  file = new TFile((BoostedUtils::GetAnalyzerPath()+"/data/toptagger/"+histosPath_).c_str());

  mtop_top_histo=(TH1F*)file->Get("TopJet_Top_M_True");
  mtop_nottop_histo=(TH1F*)file->Get("TopJet_Top_M_False");
  
  /*
  mratio_top_histo=(TH1F*)file->Get("TopJet_MRatio_23_Top_True");
  mratio_nottop_histo=(TH1F*)file->Get("TopJet_MRatio_23_Top_False");
  atan_top_histo=(TH1F*)file->Get("TopJet_Atan_1213_True");
  atan_nottop_histo=(TH1F*)file->Get("TopJet_Atan_1213_False");
  */
  /*
  mratio_top_histo=(TH1F*)file->Get("TopJet_MRatio_W_Top_True");
  mratio_nottop_histo=(TH1F*)file->Get("TopJet_MRatio_W_Top_False");
  atan_top_histo=(TH1F*)file->Get("TopJet_Atan_BW1W2_True");
  atan_nottop_histo=(TH1F*)file->Get("TopJet_Atan_BW1W2_False");
  */
  
  mratio_top_histo=(TH1F*)file->Get("TopJet_MRatio_Wbtag_Top_True");
  mratio_nottop_histo=(TH1F*)file->Get("TopJet_MRatio_Wbtag_Top_False");
  atan_top_histo=(TH1F*)file->Get("TopJet_MRatio_Wbtag_Top_True");
  atan_nottop_histo=(TH1F*)file->Get("TopJet_MRatio_Wbtag_Top_False");
  
  
  toplikelihood = true;
  tmva = false;
}


TopTagger::TopTagger(std::string name_, std::vector<std::string> BDTVarNames_, std::string weightsPath_): name(name_) {
  
  BDTReader = new TMVA::Reader();

  BDTVars["TopJet_Top_M"]             = -999;
  BDTVars["TopJet_Wbtag_M"]           = -999;
  BDTVars["TopJet_BW1btag_M"]         = -999;
  BDTVars["TopJet_BW2btag_M"]         = -999;
  BDTVars["TopJet_PrunedMass"]        = -999;
  BDTVars["TopJet_UnfilteredMass"]    = -999;
  BDTVars["TopJet_fRec"]              = -999;
  BDTVars["TopJet_DRoptRoptCalc"]     = -999;
  BDTVars["TopJet_Tau21Filtered"]     = -999;
  BDTVars["TopJet_Tau32Filtered"]     = -999;
  BDTVars["TopJet_Bbtag_CSV"]         = -999;
  BDTVars["TopJet_W1btag_CSV"]        = -999;
  BDTVars["TopJet_W2btag_CSV"]        = -999;
  BDTVars["TopJet_MRatio_Wbtag_Top"]  = -999;
  BDTVars["TopJet_Atan_BW1W2btag"]    = -999;
  
  for(size_t iBDTVars=0;iBDTVars<BDTVarNames_.size();iBDTVars++){
    BDTReader->AddVariable(BDTVarNames_[iBDTVars].c_str(),&BDTVars[BDTVarNames_[iBDTVars]]);
  }

  BDTReader->BookMVA("BDT",(BoostedUtils::GetAnalyzerPath()+"/data/toptagger/"+weightsPath_).c_str());
  
  tmva = true;
  toplikelihood = false;
     
}


void TopTagger::ResetBDTVars(){  
  for(std::map<std::string,float>::iterator itBDTVar=BDTVars.begin();itBDTVar!=BDTVars.end();itBDTVar++)
    itBDTVar->second = -999;
}


float TopTagger::GetTopLikelihood(const boosted::HTTTopJet& topjet, bool verbose){
  
  if(!toplikelihood) return -1.1;
  if(topjet.nonW.pt()<1.0) return -1.1;
  if(topjet.W1.pt()<1.0) return -1.1;
  if(topjet.W2.pt()<1.0) return -1.1;
  
  std::vector<pat::Jet> subjets;
  subjets.push_back(topjet.nonW);
  subjets.push_back(topjet.W1);
  subjets.push_back(topjet.W2);
  std::sort(subjets.begin(),subjets.end(),BoostedUtils::FirstHasHigherCSV); 
  
  std::vector<math::XYZTLorentzVector> topvecs = BoostedUtils::GetJetVecs(subjets);
  
  float mW=-999;
  float mBW1=-999;
  float mBW2=-999;
  float mTop=-999; 
  if(topvecs.size()==3){
    mBW1=(topvecs[0]+topvecs[1]).M();
    mBW2=(topvecs[0]+topvecs[2]).M();
    mW=(topvecs[1]+topvecs[2]).M();
    mTop=(topvecs[0]+topvecs[1]+topvecs[2]).M();
  }
  else return -1.1;
  float mratio=mW/mTop;
  float atan=TMath::ATan(mBW1/mBW2);
  
  if (mTop<120||mTop>200) return -1.1;
  if (mratio<0.2||mratio>0.8) return -1.1;
  if (atan<0.15||atan>1.4) return -1.1;
  
  float ptt = mtop_top_histo->Interpolate(mTop);
  float ptf = mtop_nottop_histo->Interpolate(mTop);
  float pat = atan_top_histo->Interpolate(atan);
  float paf = atan_nottop_histo->Interpolate(atan);
  float pmt = mratio_top_histo->Interpolate(mratio);
  float pmf = mratio_nottop_histo->Interpolate(mratio);
  float lr = ptt*pat*pmt/(ptt*pat*pmt+ptf*paf*pmf);
  return 2*lr-1;
  
}


float TopTagger::GetBDTOutput(const boosted::HTTTopJet& topjet, bool verbose){
  
  if(!tmva) return -1.1;
  if(topjet.nonW.pt()==0) return -1.1;
  if(topjet.W1.pt()==0) return -1.1;
  if(topjet.W2.pt()==0) return -1.1;
  
  ResetBDTVars();
  
  const char* btagger="combinedInclusiveSecondaryVertexV2BJetTags";
  
  BDTVars["TopJet_Top_M"]             = topjet.topjet.mass();
  BDTVars["TopJet_Wbtag_M"]           = (topjet.W1.p4()+topjet.W2.p4()).M();
  BDTVars["TopJet_BW1btag_M"]         = (topjet.nonW.p4()+topjet.W1.p4()).M();
  BDTVars["TopJet_BW2btag_M"]         = (topjet.nonW.p4()+topjet.W2.p4()).M();
  BDTVars["TopJet_PrunedMass"]        = topjet.prunedMass;
  BDTVars["TopJet_UnfilteredMass"]    = topjet.unfilteredMass;
  BDTVars["TopJet_fRec"]              = topjet.fRec;
  BDTVars["TopJet_DRoptRoptCalc"]     = topjet.Ropt-topjet.RoptCalc;
  BDTVars["TopJet_Tau21Filtered"]     = topjet.tau2Filtered/topjet.tau1Filtered;
  BDTVars["TopJet_Tau32Filtered"]     = topjet.tau3Filtered/topjet.tau2Filtered;
  BDTVars["TopJet_Bbtag_CSV"]         = fmax(topjet.nonW.bDiscriminator(btagger),-.1);
  BDTVars["TopJet_W1btag_CSV"]        = fmax(topjet.W1.bDiscriminator(btagger),-.1);
  BDTVars["TopJet_W2btag_CSV"]        = fmax(topjet.W2.bDiscriminator(btagger),-.1);
  BDTVars["TopJet_MRatio_Wbtag_Top"]  = (topjet.W1.p4()+topjet.W2.p4()).M()/topjet.topjet.mass();
  BDTVars["TopJet_Atan_BW1W2btag"]    = atan((topjet.nonW.p4()+topjet.W1.p4()).M()/(topjet.nonW.p4()+topjet.W2.p4()).M());
  
  if(verbose){
    std::cout << "Top Tagger Variables:" << std::endl;
    for(std::map<std::string,float>::iterator it=BDTVars.begin();it!=BDTVars.end();++it){
      std::cout << it->first << ": " << it->second << std::endl;
    }
  }
  
  float BDToutput = BDTReader->EvaluateMVA("BDT");
  
  if(verbose) std::cout << "BDTOutput: " << BDToutput << std::endl;
  
  return BDToutput;
}


float TopTagger::GetTopTag(const boosted::HTTTopJet& topJet, bool verbose){

  if(toplikelihood && !tmva) return GetTopLikelihood(topJet,verbose);
  if(tmva && !toplikelihood) return GetBDTOutput(topJet,verbose);
  
  return -1.1;
  
}


boosted::HTTTopJetCollection TopTagger::GetSortedByTopTaggerOutput(const boosted::HTTTopJetCollection& topJets, bool verbose){
  
  boosted::HTTTopJetCollection result = topJets;
  
  TopTaggerOutputComparison topTagComp(this);
  std::sort(result.begin(), result.end(),topTagComp);
  
  return result;
}


float TopTagger::GetTopHad(boosted::HTTTopJetCollection& topJets, boosted::HTTTopJet& topHadCand, bool verbose){
  
  float maxTopTag=-9999;
  
  for(boosted::HTTTopJetCollection::iterator itTopJet = topJets.begin() ; itTopJet != topJets.end(); ++itTopJet){
    
    float topTag = GetTopTag(*itTopJet,verbose);
    
    if(topTag > maxTopTag) {
      maxTopTag = topTag;
      topHadCand = *itTopJet;
    }
  } 
  
  return maxTopTag;
}
