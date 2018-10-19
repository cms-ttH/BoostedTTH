#include "BoostedTTH/BoostedAnalyzer/interface/SlimmedNtuples.hpp"

using namespace std;

SlimmedNtuples::SlimmedNtuples(){}
SlimmedNtuples::~SlimmedNtuples(){}

void SlimmedNtuples::Init(const InputCollections& input,VariableContainer& vars){cout << "this method should not be called -> something is wrong" << endl;}
void SlimmedNtuples::Process(const InputCollections& input,VariableContainer& vars){cout << "this method should not be called -> something is wrong" << endl;}

template <typename T> T SlimmedNtuples::GetSortedBySeed(const T& collection){
  T result = collection;
  std::sort(result.begin(), result.end(), [] (typename T::value_type a, typename T::value_type b) { return ptr(a)->userInt("deterministicSeed") > ptr(b)->userInt("deterministicSeed");});
  return result;
}

void SlimmedNtuples::Init(const std::vector<InputCollections>& input,VariableContainer& vars){
    
    vars.InitVar( "event" , "I" );
    vars.InitVar( "run" , "I" );
    vars.InitVar( "lumi" , "I" );
    vars.InitVar( "systematic" , "I" );
    
    vars.InitVar( "nleps" , "I" );
    
    vars.InitVars( "lep_mass" , "nleps" );
    vars.InitVars( "lep_pt" , "nleps" );
    vars.InitVars( "lep_eta" , "nleps" );
    vars.InitVars( "lep_phi" , "nleps" );
    vars.InitVars( "lep_charge" , "nleps" );
    
    vars.InitVar( "met_pt" );
    vars.InitVar( "met_phi" );
    
    vars.InitVar( "njets" , "I" );
    
    for(uint i_sys=1;i_sys<uint(input.size());i_sys++) {
        TString syst_str = Systematics::toString(input.at(i_sys).systematic);
        syst_str.ReplaceAll("JES","");
        //vars.InitVar("njets"+syst_str,"I");
        vars.InitVars( "jet_"+syst_str , "njets" );
    }
    
    vars.InitVars( "jet_mass" , "njets" );
    vars.InitVars( "jet_pt" , "njets" );
    vars.InitVars( "jet_eta" , "njets" );
    vars.InitVars( "jet_phi" , "njets" );
    vars.InitVars( "jet_corr" , "njets" );
    vars.InitVars( "jet_corr_JER" , "njets" );
    vars.InitVars( "jet_corr_JES" , "njets" );
    vars.InitVars( "jet_csv" , "njets" );
    vars.InitVars( "jet_deepcsv" , "njets" );
    vars.InitVars( "jet_cmva" , "njets" );
    
    initialized=true;
}

void SlimmedNtuples::Process(const std::vector<InputCollections>& input,VariableContainer& vars){
  if(!initialized) cerr << "slimmed ntuples not initialized" << endl;
  
  const InputCollections& input_nom=input.at(0);
  // Get & fill basic event quantities
  long evt_id = input_nom.eventInfo.evt;
  long run_id = input_nom.eventInfo.run;
  long lumi_section = input_nom.eventInfo.lumiBlock;

  vars.FillIntVar( "event" , evt_id );
  vars.FillIntVar( "run" , run_id);
  vars.FillIntVar( "lumi" , lumi_section);
  ///////////////////////////////////////////
  
  //not yet sure what to do with this systematic number
  long systematic=0;
  
  vars.FillIntVar( "systematic" , systematic);
  ////////////////////////////////////////////////////
  
  vars.FillIntVar( "nleps" , int(input_nom.selectedElectrons.size()+input_nom.selectedMuons.size()) );
  
  // fill lepton stuff in the tree
  for(std::vector<pat::Electron>::const_iterator itLep = input_nom.selectedElectrons.begin() ; itLep != input_nom.selectedElectrons.end(); ++itLep){
    int iLep = itLep - input_nom.selectedElectrons.begin();
    vars.FillVars( "lep_mass" , iLep,itLep->mass() );
    vars.FillVars( "lep_pt" , iLep,itLep->pt() );
    vars.FillVars( "lep_eta" , iLep,itLep->eta() );
    vars.FillVars( "lep_phi" , iLep,itLep->phi() );
    vars.FillVars( "lep_charge" , iLep,itLep->charge() );
  }
  for(std::vector<pat::Muon>::const_iterator itLep = input_nom.selectedMuons.begin() ; itLep != input_nom.selectedMuons.end(); ++itLep){
    int iLep = itLep - input_nom.selectedMuons.begin();
    vars.FillVars( "lep_mass" , iLep,itLep->mass() );
    vars.FillVars( "lep_pt" , iLep,itLep->pt() );
    vars.FillVars( "lep_eta" , iLep,itLep->eta() );
    vars.FillVars( "lep_phi" , iLep,itLep->phi() );
    vars.FillVars( "lep_charge" , iLep,itLep->charge() );
  }
  // fill nominal jet collection into the tree
  std::vector<pat::Jet> jets = GetSortedBySeed(input_nom.selectedJetsLoose);
  uint iJet=0;
  for(std::vector<pat::Jet>::const_iterator itJet = jets.begin() ; itJet != jets.end(); ++itJet){
    pat::Jet jet = *itJet;
    double jes_nom = 1.;
    double jer_nom = 1.;
    if(jet.hasUserFloat("HelperJES")) jes_nom = jet.userFloat("HelperJES");
    if(jet.hasUserFloat("HelperJER")) jer_nom = jet.userFloat("HelperJER");
    // the following steps are done to have exactly the same jets in each considered inputcollection //
    jet.scaleEnergy(1./(jes_nom*jer_nom));
    if(jet.pt()<20.) continue;
    jet.scaleEnergy(jes_nom*jer_nom);
    ////////////////
    vars.FillVars( "jet_mass" , iJet,jet.mass() );
    vars.FillVars( "jet_pt" , iJet , jet.pt() );
    vars.FillVars( "jet_eta" , iJet , jet.eta() );
    vars.FillVars( "jet_phi" , iJet , jet.phi() );
    vars.FillVars( "jet_csv" , iJet , MiniAODHelper::GetJetCSV(jet,"pfCombinedInclusiveSecondaryVertexV2BJetTags") );
    vars.FillVars( "jet_deepcsv" , iJet , MiniAODHelper::GetJetCSV(jet,"DeepCSV") );
    // save the product of the nominal jec, meaning JESnominal*JERnominal
    vars.FillVars( "jet_corr" , iJet , jes_nom*jer_nom );
    vars.FillVars( "jet_corr_JER" , iJet , jer_nom );
    vars.FillVars( "jet_corr_JES" , iJet , jes_nom );
    iJet++;
  }
  // number of jets
  vars.FillIntVar( "njets" , iJet);
  // met properties
  vars.FillVar( "met_pt" , input_nom.correctedMET.corPt(pat::MET::Type1XY) );
  vars.FillVar( "met_phi" , input_nom.correctedMET.corPhi(pat::MET::Type1XY) );
  
  
  // loop over all systematic jec sources 
  for(uint i_sys=1;i_sys<uint(input.size());i_sys++) {
        const InputCollections&  input_used = input.at(i_sys);
        std::vector<pat::Jet> jets = GetSortedBySeed(input_used.selectedJetsLoose);
        const Systematics::Type& systematic = input_used.systematic;
        TString syst_str = Systematics::toString(systematic);
        syst_str.ReplaceAll("JES","");
        //vars.FillIntVar("njets"+syst_str,jets.size());
        iJet=0;
        for(std::vector<pat::Jet>::const_iterator itJet = jets.begin() ; itJet != jets.end(); ++itJet){
            pat::Jet jet = *itJet;
            double jes_nom = 1.;
            double jer_nom = 1.;
            if(jet.hasUserFloat("HelperJES")) jes_nom = jet.userFloat("HelperJES");
            if(jet.hasUserFloat("HelperJER")) jer_nom = jet.userFloat("HelperJER");
            // the following steps are done to have exactly the same jets in each considered inputcollection //
            jet.scaleEnergy(1./(jes_nom*jer_nom*jet.userFloat("Helper"+Systematics::toString(systematic))));
            if(jet.pt()<20.) continue;
            jet.scaleEnergy(jes_nom*jer_nom*jet.userFloat("Helper"+Systematics::toString(systematic)));
            ////////////////
            // save the complete product of the jec for each variation, meaning JESnominal*JERnominal*VariationUpDown
            vars.FillVars( "jet_"+syst_str , iJet , jes_nom*jer_nom*jet.userFloat("Helper"+Systematics::toString(systematic)) );
            iJet++;
        }
    }
  

  
}
