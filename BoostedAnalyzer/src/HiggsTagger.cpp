#include "BoostedTTH/BoostedAnalyzer/interface/HiggsTagger.hpp"


HiggsTagger::HiggsTagger(){
  
  name = "";

  secondcsv = false;
  tmva = false;
}


HiggsTagger::HiggsTagger(std::string name_): name(name_) {
  secondcsv = true;
  tmva = false;
}


HiggsTagger::HiggsTagger(std::string name_, std::vector<std::string> BDTVarNames_, std::string weightsPath_): name(name_) {
  
  BDTReader = new TMVA::Reader();

  BDTVars["Pt_HiggsJet"]                      = -999;
  BDTVars["M2_HiggsJet"]                      = -999;
  BDTVars["M3_HiggsJet"]                      = -999;
  BDTVars["CSV1_HiggsJet"]                    = -999;
  BDTVars["CSV2_HiggsJet"]                    = -999;
  BDTVars["NSubjettiness_12_Ratio_HiggsJet"]  = -999;
  BDTVars["NSubjettiness_23_Ratio_HiggsJet"]  = -999;
  BDTVars["NSubjettiness_13_Ratio_HiggsJet"]  = -999;
  

  for(size_t iBDTVars=0;iBDTVars<BDTVarNames_.size();iBDTVars++){
    BDTReader->AddVariable(BDTVarNames_[iBDTVars].c_str(),&BDTVars[BDTVarNames_[iBDTVars]]);
  }

  BDTReader->BookMVA("BDT",BoostedUtils::GetAnalyzerPath()+"/data/"+weightsPath_.c_str());
  
  tmva = true;
  secondcsv = false;
}


void HiggsTagger::ResetBDTVars(){  
  for(std::map<std::string,float>::iterator itBDTVar=BDTVars.begin();itBDTVar!=BDTVars.end();itBDTVar++)
    itBDTVar->second = -999;
}


float HiggsTagger::GetSecondCSV(const boosted::SubFilterJet& higgsJet, bool verbose){
  
  if(!secondcsv) return -1.1;
  if(higgsJet.subjets.size()<2) return -1.1;
  
  std::vector<pat::Jet> subjets = higgsJet.subjets;
  std::sort(subjets.begin(),subjets.end(),BoostedUtils::FirstHasHigherCSV); 
  
  return subjets[1].bDiscriminator("combinedSecondaryVertexBJetTags");
  
}


float HiggsTagger::GetBDTOutput(const boosted::SubFilterJet& higgsJet, bool verbose){
  
  if(!tmva) return -1.1;
  if(higgsJet.filterjets.size()<2) return -1.1;
  
  std::vector<pat::Jet> filterjets = BoostedUtils::GetHiggsFilterJets(higgsJet);
  std::vector<math::XYZTLorentzVector> filterjetvecs = BoostedUtils::GetJetVecs(filterjets);
  
  double M2 = (filterjetvecs[0]+filterjetvecs[1]).M();
  double M3 = -1.1;
  if(higgsJet.filterjets.size()>=3)
    M3 = (filterjetvecs[0]+filterjetvecs[1]+filterjetvecs[2]).M();
    
  ResetBDTVars();
  
  BDTVars["Pt_HiggsJet"]                      = higgsJet.fatjet.pt();
  BDTVars["M2_HiggsJet"]                      = M2;
  BDTVars["M3_HiggsJet"]                      = M3;
  BDTVars["CSV1_HiggsJet"]                    = filterjets[0].bDiscriminator("combinedSecondaryVertexBJetTags");
  BDTVars["CSV2_HiggsJet"]                    = filterjets[1].bDiscriminator("combinedSecondaryVertexBJetTags");
  BDTVars["NSubjettiness_12_Ratio_HiggsJet"]  = higgsJet.subjettiness2/higgsJet.subjettiness1;
  BDTVars["NSubjettiness_23_Ratio_HiggsJet"]  = higgsJet.subjettiness3/higgsJet.subjettiness2;
  BDTVars["NSubjettiness_13_Ratio_HiggsJet"]  = higgsJet.subjettiness3/higgsJet.subjettiness1;
  
  if(verbose){
    std::cout << "Higgs Tagger Variables:" << std::endl;
    for(std::map<std::string,float>::iterator it=BDTVars.begin();it!=BDTVars.end();++it){
      std::cout << it->first << ": " << it->second << std::endl;
    }
  }
  
  float BDToutput = BDTReader->EvaluateMVA("BDT");
  
  if(verbose) std::cout << "BDTOutput: " << BDToutput << std::endl;
  
  return BDToutput;
}


float HiggsTagger::GetHiggsTag(const boosted::SubFilterJet& higgsJet, bool verbose){

  if(secondcsv && !tmva) return GetSecondCSV(higgsJet,verbose);
  if(tmva && !secondcsv) return GetBDTOutput(higgsJet,verbose);
  
  return -1.1;
  
}


boosted::SubFilterJetCollection HiggsTagger::GetSortedByHiggsTaggerOutput(const boosted::SubFilterJetCollection& higgsJets, bool verbose){
  
  boosted::SubFilterJetCollection result = higgsJets;
  
  HiggsTaggerOutputComparison higgsTagComp(this);
  std::sort(result.begin(), result.end(),higgsTagComp);
  
  return result;
}


float HiggsTagger::GetHiggsCand(boosted::SubFilterJetCollection& higgsJets, boosted::SubFilterJet& higgsCand, bool verbose){
  
  float maxHiggsTag=-9999;
  
  for(boosted::SubFilterJetCollection::iterator itHiggsJet = higgsJets.begin() ; itHiggsJet != higgsJets.end(); ++itHiggsJet){
    
    float higgsTag = GetHiggsTag(*itHiggsJet,verbose);
    
    if(higgsTag > maxHiggsTag) {
      maxHiggsTag = higgsTag;
      higgsCand = *itHiggsJet;
    }
  } 
  
  return maxHiggsTag;
}
