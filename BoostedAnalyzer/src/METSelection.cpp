#include "BoostedTTH/BoostedAnalyzer/interface/METSelection.hpp"

using namespace std;

METSelection::METSelection (const edm::ParameterSet& iConfig):minMET(iConfig.getParameter<double>("minMET")),maxMET(iConfig.getParameter<double>("maxMET"))
{}
METSelection::~METSelection (){}

void METSelection::InitCutflow(Cutflow& cutflow){
    selectionName="MET > ";
    selectionName=std::to_string(minMET);
    selectionName=" and MET < ";
    selectionName=std::to_string(maxMET);   
    cutflow.AddStep(selectionName);

    initialized=true;
}

bool METSelection::IsSelected(const InputCollections& input,Cutflow& cutflow){
    if(!initialized) cerr << "METSelection not initialized" << endl;
    double met=input.pfMET.pt();
    if(met>minMET&&met<maxMET){
	cutflow.EventSurvivedStep(selectionName ,input.weights.at("Weight"));
	return true;
    }
    
    return false;   

} 
