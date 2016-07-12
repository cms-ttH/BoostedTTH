#include "BoostedTTH/BoostedAnalyzer/interface/MEMProcessor.hpp"
using namespace std;


MEMProcessor::MEMProcessor(int minJets_,int maxJets_,int minTags_):
    minJets(minJets_),
    maxJets(maxJets_),
    minTags(minTags_)
{}

MEMProcessor::MEMProcessor(const edm::ParameterSet& iConfig):MEMProcessor(iConfig.getParameter< int >("minJetsForMEM"),
									  iConfig.getParameter< int >("maxJetsForMEM"),
									  iConfig.getParameter< int >("minTagsForMEM"))
									  {}

MEMProcessor::~MEMProcessor(){}

void MEMProcessor::Init(const InputCollections& input,VariableContainer& vars){
    vars.InitVar("MEM_p");
    vars.InitVar("MEM_p_sig");
    vars.InitVar("MEM_p_bkg");
    vars.InitVar("MEM_p_err_sig");
    vars.InitVar("MEM_p_err_bkg");
    vars.InitVar("MEM_n_perm_sig","I");
    vars.InitVar("MEM_n_perm_bkg","I");

    initialized=true;
}

void MEMProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;


  // leptons
  vector<TLorentzVector> lepvecs;
  vector<double> lepcharges;
  for(auto& el: input.selectedElectrons){
      lepcharges.push_back(el.charge());
      lepvecs.push_back(BoostedUtils::GetTLorentzVector(el.p4()));
  }
  for(auto& mu: input.selectedMuons){
      lepcharges.push_back(mu.charge());
      lepvecs.push_back(BoostedUtils::GetTLorentzVector(mu.p4()));
  }
  if(lepvecs.size()!=1) return;
  
  // MET
  TLorentzVector metP4=BoostedUtils::GetTLorentzVector(input.pfMET.p4());
  
  // jets
  vector<TLorentzVector> jetvecs;
  vector<double> jetcsvs;
  std::vector<MEMClassifier::JetType> jettype;
  
  int ntags=0;
  
  for(uint i=0; i<input.selectedJets.size(); i++){
      if(int(i)==maxJets) break;
      
      jetvecs.push_back(BoostedUtils::GetTLorentzVector(input.selectedJets[i].p4()));
      jetcsvs.push_back(MiniAODHelper::GetJetCSV(input.selectedJets[i]));
      jettype.push_back(MEMClassifier::JetType::RESOLVED);
      
      if(jetcsvs.back()>btagMcut) ntags++;
  }
  if(int(jetvecs.size())<minJets) return;
  if(ntags<minTags) return;

  //calculate MEM
  MEMResult result=mem.GetOutput(MEMClassifier::Hypothesis::SL_0W2H2T, lepvecs, lepcharges, jetvecs, jetcsvs, jettype, jetvecs, jetcsvs,metP4);
  
  vars.FillVar("MEM_p",result.p);
  vars.FillVar("MEM_p_sig",result.p_sig);
  vars.FillVar("MEM_p_bkg",result.p_bkg);
  vars.FillVar("MEM_p_err_sig",result.p_err_sig);
  vars.FillVar("MEM_p_err_bkg",result.p_err_bkg);
  vars.FillVar("MEM_n_perm_sig",result.n_perm_sig);
  vars.FillVar("MEM_n_perm_bkg",result.n_perm_bkg);
  
}
