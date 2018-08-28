#include "BoostedTTH/BoostedAnalyzer/interface/MonoJetGenSelectionProcessor.hpp"

// processor to write info to ntuple whether the event does fulfill all selection on GEN level


using namespace std;

MonoJetGenSelectionProcessor::MonoJetGenSelectionProcessor(){}
MonoJetGenSelectionProcessor::~MonoJetGenSelectionProcessor(){}



void MonoJetGenSelectionProcessor::Init(const InputCollections& input,VariableContainer& vars){
  
  vars.InitVar("GenVertexSelection",0,"I");
  vars.InitVar("GenMETSelection",0,"I");
  vars.InitVar("GenMonoJetSelection",0,"I");
  vars.InitVar("GenLeptonVetoSelection",0,"I");
  vars.InitVar("GenBTagVetoSelection",0,"I");
  vars.InitVar("GenPhotonVetoSelection",0,"I");
  vars.InitVar("GenmonoVselection",0,"I");
  initialized=true;
}

void MonoJetGenSelectionProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;
  
  vars.FillVar("GenMETSelection",GenMETSelection(input));
  vars.FillVar("GenMonoJetSelection",GenMonoJetSelection(input));
  vars.FillVar("GenLeptonVetoSelection",GenLeptonVetoSelection(input));
  vars.FillVar("GenBTagVetoSelection",GenBTagVetoSelection(input));
  vars.FillVar("GenPhotonVetoSelection",GenPhotonVetoSelection(input));
  vars.FillVar("GenmonoVselection",GenmonoVselection(input));
}

// needs to done correctly, is there a GenVertex Collection??
int MonoJetGenSelectionProcessor::GenVertexSelection(const InputCollections& input){

    return 1;
}

// check if the MET Selection is fulfilled on GEN level
int MonoJetGenSelectionProcessor::GenMETSelection(const InputCollections& input){
  if(input.correctedMET.genMET()->pt()<1){ // fix for broken GenMET in MadGraphMonoJetSamples
    if(input.genDarkMatterEvt.IsFilled()){
      const GenDarkMatterEvent& DM_Evt = input.genDarkMatterEvt;
      TLorentzVector NaiveMET_p4 = DM_Evt.ReturnNaiveMET4Vector();
      double met = NaiveMET_p4.Pt();
      if(met>minMET&&met<maxMET){
        return 1;
      }
    }
  }
  else{
    if(input.correctedMET.genMET()!=0){
      double met=input.correctedMET.genMET()->pt();
      if(met>minMET&&met<maxMET){
        return 1;
      }
    }
  }
  return 0;
}


// check if the MonoJetSelection is fullfilled on GEN level
int MonoJetGenSelectionProcessor::GenMonoJetSelection(const InputCollections& input){

  if(input.customGenJets.size()<1) return 0;
  
  bool dPhi_jet_met_criterium = true;
  
  // customGenJets are already ordered with respect to pt
  bool leading_jet_criterium = input.customGenJets.at(0).pt()>pt_min && abs(input.customGenJets.at(0).eta())<eta_max;// && charged_hadron_fraction_min<input.customGenJets.at(0).emEnergy()/input.customGenJets.at(0).energy() && neutral_hadron_fraction_max>input.customGenJets.at(0).hadEnergy()/input.customGenJets.at(0).energy();

  
  if(!leading_jet_criterium) return 0;
  
  return 1;
}

// check if the LeptonVetoSelection is fulfilled on GEN level
int MonoJetGenSelectionProcessor::GenLeptonVetoSelection(const InputCollections& input){

    if(input.customGenElectrons.size()>0 || input.customGenMuons.size()>0 || input.customGenTaus.size()>0) {
        return 0;
    }
    else{
        return 1;    
    }
}

// check if the BTagVetoSelection is fulfilled on GEN level
int MonoJetGenSelectionProcessor::GenBTagVetoSelection(const InputCollections& input){

    for(auto& jet : input.customGenJetsLoose){
        if(BoostedUtils::PassesCSV(jet, 'M')) return 0;
    }

    return 1;    
}

int MonoJetGenSelectionProcessor::GenPhotonVetoSelection(const InputCollections& input){
    
    if(input.customGenPhotons.size()>0) {
        return 0;
    }
    else{
        return 1;    
    }
}

int MonoJetGenSelectionProcessor::GenmonoVselection(const InputCollections& input){

  if (input.customGenJetsAK8.size() >= 1) {
    auto leadingJet = input.customGenJetsAK8.at(0);

    float leadingJet_eta = leadingJet.eta();
    float leadingJet_Pt = leadingJet.pt();
    float leadingJet_mass = leadingJet.mass();

    monoVtagged = false;
    if (leadingJet_Pt > minpt && abs(leadingJet_eta) < maxeta && leadingJet_mass > minMass && leadingJet_mass < maxMass) {
      monoVtagged = true;
    }

    if (monoVtagged ) {
      return false;
    }
    else {
      return true;
    }
  }
  else {
    return true;
  }

}


    


