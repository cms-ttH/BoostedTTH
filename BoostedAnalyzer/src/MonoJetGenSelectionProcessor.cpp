#include "BoostedTTH/BoostedAnalyzer/interface/MonoJetGenSelectionProcessor.hpp"

using namespace std;

MonoJetGenSelectionProcessor::MonoJetGenSelectionProcessor(){}
MonoJetGenSelectionProcessor::~MonoJetGenSelectionProcessor(){}


void MonoJetGenSelectionProcessor::Init(const InputCollections& input,VariableContainer& vars){
  
  vars.InitVar("GenVertexSelection",0,"I");
  vars.InitVar("GenMETSelection",0,"I");
  vars.InitVar("GenMonoJetSelection",0,"I");
  vars.InitVar("GenLeptonVetoSelection",0,"I");
  vars.InitVar("GenBTagVetoSelection",0,"I");
  initialized=true;
}

void MonoJetGenSelectionProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;
  
  vars.FillVar("GenMETSelection",GenMETSelection(input));
  vars.FillVar("GenMonoJetSelection",GenMonoJetSelection(input));
  vars.FillVar("GenLeptonVetoSelection",GenLeptonVetoSelection(input));
  vars.FillVar("GenBTagVetoSelection",GenBTagVetoSelection(input));
}

int MonoJetGenSelectionProcessor::GenVertexSelection(const InputCollections& input){

    return 0;
}

int MonoJetGenSelectionProcessor::GenMETSelection(const InputCollections& input){

    if(input.correctedMET.genMET()!=0){
        double met=input.correctedMET.genMET()->pt();
        if(met>minMET&&met<maxMET){
            return 1;
        }
    }
    return 0;
}

int MonoJetGenSelectionProcessor::GenMonoJetSelection(const InputCollections& input){

  if(input.customGenJets.size()<1) return 0;
  
  bool dPhi_jet_met_criterium = true;
  
  // customGenJets are already ordered with respect to pt
  bool leading_jet_criterium = input.customGenJets.at(0).pt()>pt_min && abs(input.customGenJets.at(0).eta())<eta_max && charged_hadron_fraction_min<input.customGenJets.at(0).emEnergy()/input.customGenJets.at(0).energy() && neutral_hadron_fraction_max>input.customGenJets.at(0).hadEnergy()/input.customGenJets.at(0).energy();
  
  if(!leading_jet_criterium) return 0;
  
  for(size_t i=0;i<input.customGenJets.size()&&i<4;i++) {
      dPhi_jet_met_criterium = abs(input.customGenJets.at(i).phi()-input.correctedMET.genMET()->phi())>0.5;
      if(!dPhi_jet_met_criterium) return 0;
  }
  
  return 1;
}

int MonoJetGenSelectionProcessor::GenLeptonVetoSelection(const InputCollections& input){

    if(input.customGenElectrons.size()>0 || input.customGenMuons.size()>0 || input.customGenTaus.size()>0) {
        return 0;
    }
    else{
        return 1;    
    }
}

int MonoJetGenSelectionProcessor::GenBTagVetoSelection(const InputCollections& input){

    for(auto& jet : input.customGenJetsLoose){
        if(BoostedUtils::PassesCSV(jet, 'M')) return 0;
    }

    return 1;    
}
