#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonMETSelection.hpp"

using namespace std;

DiLeptonMETSelection::DiLeptonMETSelection (const edm::ParameterSet& iConfig):DiLeptonMETSelection(iConfig.getParameter<double>("minMET"),iConfig.getParameter<double>("maxMET"))
{}
DiLeptonMETSelection::DiLeptonMETSelection (float minMET_, float maxMET_):minMET(minMET_),maxMET(maxMET_)
{}
DiLeptonMETSelection::~DiLeptonMETSelection (){}

void DiLeptonMETSelection::InitCutflow(Cutflow& cutflow){
    selectionName="MET > ";
    selectionName+=std::to_string(minMET);
    selectionName+=" and MET < ";
    selectionName+=std::to_string(maxMET);   
    cutflow.AddStep(selectionName);

    initialized=true;
}

bool DiLeptonMETSelection::IsSelected(const InputCollections& input,Cutflow& cutflow){
    if(!initialized) cerr << "METSelection not initialized" << endl;

    if(input.selectedMuonsDL.size()>=1 && input.selectedElectronsDL.size()>=1){
	cutflow.EventSurvivedStep(selectionName ,input.weights.at("Weight"));
	return true;
    }
    double met=input.pfMET.pt();
    if(met>minMET&&met<maxMET){
	cutflow.EventSurvivedStep(selectionName ,input.weights.at("Weight"));
	return true;
    }
    
    return false;   

} 
