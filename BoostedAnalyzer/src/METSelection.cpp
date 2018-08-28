#include "BoostedTTH/BoostedAnalyzer/interface/METSelection.hpp"

using namespace std;

METSelection::METSelection (const edm::ParameterSet& iConfig):METSelection(iConfig.getParameter<double>("minMET"),iConfig.getParameter<double>("maxMET"))
{}
METSelection::METSelection (float minMET_, float maxMET_):minMET(minMET_),maxMET(maxMET_)
{}
METSelection::~METSelection (){}

void METSelection::InitCutflow(Cutflow& cutflow){
    
    // create string for cutflow
    selectionName="MET > ";
    selectionName+=std::to_string(minMET);
    selectionName+=" and MET < ";
    selectionName+=std::to_string(maxMET);   
    cutflow.AddStep(selectionName);

    initialized=true;
}

bool METSelection::IsSelected(const InputCollections& input,Cutflow& cutflow){
    if(!initialized) cerr << "METSelection not initialized" << endl;
    
    // 4-vector for MET and hadronic recoil
    math::XYZTLorentzVector met_p4(0.,0.,0.,0.);
    math::XYZTLorentzVector hadr_recoil_p4(0.,0.,0.,0.);
    
    // check if are jet systematic is being used and if so use the correct method to extract the 4-vector from the pat::MET object
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
    else if(input.systematic==Systematics::METUnclENup) {
        met_p4 = input.correctedMET.shiftedP4(pat::MET::UnclusteredEnUp,pat::MET::Type1XY);
    }
    else if(input.systematic==Systematics::METUnclENdown) {
        met_p4 = input.correctedMET.shiftedP4(pat::MET::UnclusteredEnDown,pat::MET::Type1XY);
    }
    else {
        met_p4 = input.correctedMET.corP4(pat::MET::Type1XY);
    }
    
    // after the correct pat::MET method has been used, get the pt of the MET 4-vector
    double met = met_p4.pt();
    
    // set the 4-vector of the hadronic recoil equals to the MET 4-vector and correct it in the following for leptons and photons
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
    
    // after correcting the MET to obtain the correct hadronic recoil, get the pt
    double hadr_recoil = hadr_recoil_p4.pt();
    //double uncormet = input.correctedMET.uncorPt();
    
    // get the pt of the calorimeter MET
    double calomet = input.correctedMET.caloMETPt();
    
    // check if MET/hadronic recoil is greater than a lower threshold and smaller than a maximum threshold
    // check in addition if a quality criteria for MET is fulfilled to reduce fake MET events
    // if the events satisfies the conditions, return true
    if((hadr_recoil>minMET&&hadr_recoil<maxMET)&&(fabs(calomet-met)/calomet<0.5)){
    	cutflow.EventSurvivedStep(selectionName ,input.weights.at("Weight"));
	   return true;
    }
    
    return false;   

} 
