#include "BoostedTTH/BoostedAnalyzer/interface/METSelection.hpp"

using namespace std;

METSelection::METSelection (const edm::ParameterSet& iConfig):METSelection(iConfig.getParameter<double>("minMET"),iConfig.getParameter<double>("maxMET"))
{}
METSelection::METSelection (float minMET_, float maxMET_):minMET(minMET_),maxMET(maxMET_)
{}
METSelection::~METSelection (){}

void METSelection::InitCutflow(Cutflow& cutflow){
    selectionName="MET > ";
    selectionName+=std::to_string(minMET);
    selectionName+=" and MET < ";
    selectionName+=std::to_string(maxMET);   
    cutflow.AddStep(selectionName);

    initialized=true;
}

bool METSelection::IsSelected(const InputCollections& input,Cutflow& cutflow){
    if(!initialized) cerr << "METSelection not initialized" << endl;
    double met=input.correctedMET.pt();
    if(met>minMET&&met<maxMET){
	cutflow.EventSurvivedStep(selectionName ,input.weights.at("Weight"));
	return true;
    }
    
    return false;   

} 
