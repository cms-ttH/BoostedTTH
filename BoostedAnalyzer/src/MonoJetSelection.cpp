#include "BoostedTTH/BoostedAnalyzer/interface/MonoJetSelection.hpp"

using namespace std;

MonoJetSelection::MonoJetSelection (const edm::ParameterSet& iConfig):MonoJetSelection(iConfig.getParameter<double>("MonoJet_Pt"),iConfig.getParameter<double>("MonoJet_Eta"),iConfig.getParameter<double>("MonoJet_Chf"),iConfig.getParameter<double>("MonoJet_Nhf")){}
MonoJetSelection::MonoJetSelection (double pt_min_,double eta_max_,double chf_min_,double nhf_max_):pt_min(pt_min_),eta_max(eta_max_),charged_hadron_fraction_min(chf_min_),neutral_hadron_fraction_max(nhf_max_){}
MonoJetSelection::~MonoJetSelection (){}

double MonoJetSelection::DeltaPhi(const double& phi1, const double& phi2){
    
    double dPhi = fabs(phi1-phi2);
    if(dPhi>ROOT::Math::Pi()) dPhi = 2*ROOT::Math::Pi()-dPhi;
    return dPhi;
    
}

void MonoJetSelection::InitCutflow(Cutflow& cutflow){

  pt_str = std::to_string(pt_min); 
  eta_str = std::to_string(eta_max); 
  cutflow.AddStep("At least one jet with pt greater than "+pt_str+"and eta smaller than "+eta_str);

  initialized=true;
}

bool MonoJetSelection::IsSelected(const InputCollections& input,Cutflow& cutflow){
    if(!initialized) cerr << "MonoJetSelection not initialized" << endl;

    if(input.selectedJets.size()<1) return false;

    bool dPhi_jet_met_criterium = true;

    bool leading_jet_criterium = input.selectedJets.at(0).pt()>pt_min && fabs(input.selectedJets.at(0).eta())<eta_max && charged_hadron_fraction_min<input.selectedJets.at(0).userFloat("chargedHadronEnergyFraction") && neutral_hadron_fraction_max>input.selectedJets.at(0).userFloat("neutralHadronEnergyFraction");

    if(!leading_jet_criterium) return false;

    /*bool jet_cleaning_criterium = true;

    for(size_t i=0;i<input.selectedJets.size();i++) {
    jet_cleaning_criterium = charged_hadron_fraction_min<input.selectedJets.at(i).userFloat("chargedHadronEnergyFraction") && neutral_hadron_fraction_max>input.selectedJets.at(i).userFloat("neutralHadronEnergyFraction");
    if(!jet_cleaning_criterium) return false;
    }*/
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
    hadr_recoil_p4 = met_p4;
    for(const auto& el : input.selectedElectrons){
        hadr_recoil_p4 += el.p4();
    }
    for(const auto& mu : input.selectedMuons){
        hadr_recoil_p4 += mu.p4();
    }
    for(const auto& ph : input.selectedPhotonsLoose){
        hadr_recoil_p4 += ph.p4();
    }

    for(size_t i=0;i<input.selectedJets.size()&&i<4;i++) {
        dPhi_jet_met_criterium = DeltaPhi(input.selectedJets.at(i).phi(),met_p4.phi())>0.5;
        if(!dPhi_jet_met_criterium) return false;
    }

    cutflow.EventSurvivedStep("At least one jet with pt greater than "+pt_str+"and eta smaller than "+eta_str,input.weights.at("Weight"));
    return true;

}
