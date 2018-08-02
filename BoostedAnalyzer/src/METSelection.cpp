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
    math::XYZTLorentzVector met_p4(0.,0.,0.,0.);
    math::XYZTLorentzVector hadr_recoil_p4(0.,0.,0.,0.);
    if(input.systematic==Systematics::JESup) {
        met_p4 = input.correctedMET.shiftedP4(pat::MET::JetEnUp,pat::MET::Type1XY);
    }
    else if(input.systematic==Systematics::JESdown) {
        met_p4 = input.correctedMET.shiftedP4(pat::MET::JetEnDown,pat::MET::Type1XY);
    }
    else if(input.systematic==Systematics::JERup) {
        met_p4 = input.correctedMET.shiftedP4(pat::MET::JetResUp,pat::MET::Type1XY);
    }
    else if(input.systematic==Systematics::JERdown) {
        met_p4 = input.correctedMET.shiftedP4(pat::MET::JetResDown,pat::MET::Type1XY);
    }
    else {
        met_p4 = input.correctedMET.corP4(pat::MET::Type1XY);
    }
    double met = met_p4.pt();
    hadr_recoil_p4 = met_p4;
    for(const auto& el : input.selectedElectronsLoose){
        hadr_recoil_p4 += el.p4();
    }
    for(const auto& mu : input.selectedMuonsLoose){
        hadr_recoil_p4 += mu.p4();
    }
    for(const auto& ph : input.selectedPhotonsLoose){
        hadr_recoil_p4 += ph.p4();
    }
    double hadr_recoil = hadr_recoil_p4.pt();
    //double uncormet = input.correctedMET.uncorPt();
    double calomet = input.correctedMET.caloMETPt();
    if((hadr_recoil>minMET&&hadr_recoil<maxMET)&&(fabs(calomet-met)/calomet<0.5)){
	cutflow.EventSurvivedStep(selectionName ,input.weights.at("Weight"));
	return true;
    }
    
    return false;   

} 
