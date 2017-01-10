#include "BoostedTTH/BoostedAnalyzer/interface/BJetnessProcessor.hpp"

using namespace std;

// all configurations should be done in constructor
BJetnessProcessor::BJetnessProcessor(edm::ConsumesCollector && iC){
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

    double num_loosenoipnoiso_leps=-999;
//     double numjettrksnopv=-999;
    double pvTrkOVcollTrk=-999;
    double avip3d_val=-999;
    double avip3d_sig=-999;
    double avsip3d_sig=-999;
    double avip1d_sig=-999;
    

    vars.FillVar("BJN_N_Leptons",num_loosenoipnoiso_leps);
//     vars.FillVar("BJN_N_TracksNoPV",numjettrksnopv);
    vars.FillVar("BJN_N_PVtrackOvCollTrk",pvTrkOVcollTrk);
    vars.FillVar("BJN_N_AvgIp3D",avip3d_val);
    vars.FillVar("BJN_N_AvgIp3Dsig",avip3d_sig);
    vars.FillVar("BJN_N_AvgSip3Dsig",avsip3d_sig);
    vars.FillVar("BJN_N_AvgIp1Dsig",avip1d_sig);
}
