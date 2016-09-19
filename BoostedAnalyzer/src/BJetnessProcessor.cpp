#include "BoostedTTH/BoostedAnalyzer/interface/BJetnessProcessor.hpp"

using namespace std;

// all configurations should be done in constructor
BJetnessProcessor::BJetnessProcessor(edm::ConsumesCollector && iC){
    EDMMuonsToken           = iC.consumes< edm::View<pat::Muon> >(edm::InputTag("slimmedMuons","",""));
    EDMElectronsToken       = iC.consumes< edm::View<pat::Electron> >(edm::InputTag("slimmedElectrons","",""));

}
BJetnessProcessor::~BJetnessProcessor(){}


void BJetnessProcessor::Init(const InputCollections& input,VariableContainer& vars){
    
    vars.InitVar("BJN_N_Leptons");
//     vars.InitVar("BJN_N_TracksNoPV");
    vars.InitVar("BJN_N_PVtrackOvCollTrk");
    vars.InitVar("BJN_N_AvgIp3D");
    vars.InitVar("BJN_N_AvgIp3Dsig");
    vars.InitVar("BJN_N_AvgSip3Dsig");
    vars.InitVar("BJN_N_AvgIp1Dsig");
    initialized=true;
}

void BJetnessProcessor::Process(const InputCollections& input,VariableContainer& vars){
    if(!initialized) cerr << "tree processor not initialized" << endl; // complain if not initialized but keep running
    edm::ESHandle<TransientTrackBuilder> ttrkbuilder;
    input.iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",ttrkbuilder);
    edm::Handle< edm::View<pat::Electron> > h_electrons;
    input.iEvent.getByToken( EDMElectronsToken,h_electrons );
    edm::Handle< edm::View<pat::Muon> > h_muons;
    input.iEvent.getByToken( EDMMuonsToken,h_muons );


    double num_loosenoipnoiso_leps=-999;
//     double numjettrksnopv=-999;
    double pvTrkOVcollTrk=-999;
    double avip3d_val=-999;
    double avip3d_sig=-999;
    double avsip3d_sig=-999;
    double avip1d_sig=-999;
    
    std::cout<<input.selectedJets.size()<<std::endl;
    vector<pat::Jet> jets_by_csv=GetSortedByCSV(input.selectedJets);
    vector<pat::Jet> bjetness_jets;
    const uint maxjets=6;
    uint realMaxJets=maxjets;
    if (jets_by_csv.size()<maxjets){realMaxJets=jets_by_csv.size();}
    for(uint i=1; i<realMaxJets;  i++){
	bjetness_jets.push_back(jets_by_csv[i]);
    }
    bjetness.get_bjetness_vars(bjetness_jets,input.selectedPVs[0],*ttrkbuilder,h_electrons,h_muons,
			       num_loosenoipnoiso_leps, 
			       pvTrkOVcollTrk, avip3d_val, avip3d_sig, 
			       avsip3d_sig, avip1d_sig);

    vars.FillVar("BJN_N_Leptons",num_loosenoipnoiso_leps);
//     vars.FillVar("BJN_N_TracksNoPV",numjettrksnopv);
    vars.FillVar("BJN_N_PVtrackOvCollTrk",pvTrkOVcollTrk);
    vars.FillVar("BJN_N_AvgIp3D",avip3d_val);
    vars.FillVar("BJN_N_AvgIp3Dsig",avip3d_sig);
    vars.FillVar("BJN_N_AvgSip3Dsig",avsip3d_sig);
    vars.FillVar("BJN_N_AvgIp1Dsig",avip1d_sig);
}
