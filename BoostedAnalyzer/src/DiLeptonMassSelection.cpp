#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonMassSelection.hpp"

using namespace std;

DiLeptonMassSelection::DiLeptonMassSelection(float minMass_,float maxMass_,bool invertCut_):minMass(minMass_),maxMass(maxMass_),invertCut(invertCut_)
{}

DiLeptonMassSelection::~DiLeptonMassSelection (){}

void DiLeptonMassSelection::InitCutflow(Cutflow& cutflow){
    selectionName="Dilepton mass ";
    if(invertCut) selectionName+="not ";
    selectionName+="between ";
    selectionName+=std::to_string(minMass);
    selectionName+=" and ";
    selectionName+=std::to_string(maxMass);
    cutflow.AddStep(selectionName);
    initialized=true;
}

bool DiLeptonMassSelection::IsSelected(const InputCollections& input,Cutflow& cutflow){
    if(!initialized) cerr << "DiLeptonMassSelection not initialized" << endl;
    if(input.selectedElectronsDL.size()+input.selectedMuonsDL.size()<2) return false;
    vector<math::XYZTLorentzVector> lvs=BoostedUtils::GetLepVecs(input.selectedElectronsDL,input.selectedMuonsDL);
    float mass=(lvs[0]+lvs[1]).M();

    if( (!invertCut&&(mass<minMass||mass>maxMass)) 
	|| (invertCut&&(mass>minMass&&mass<maxMass)) ) return false;
    else cutflow.EventSurvivedStep(selectionName,input.weights.at("Weight"));
    
    return true;
}
