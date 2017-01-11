#include "BoostedTTH/BoostedAnalyzer/interface/BJetnessProcessor.hpp"

using namespace std;

// all configurations should be done in constructor
BJetnessProcessor::BJetnessProcessor(edm::ConsumesCollector && iC){
    bjetness_     = iC.consumes< vector < float > >(edm::InputTag("BJetness", "BJetnessValue"));
}
BJetnessProcessor::~BJetnessProcessor(){}


void BJetnessProcessor::Init(const InputCollections& input,VariableContainer& vars){
    
    vars.InitVar("BJN_Jet0_Pt",-99.);
    vars.InitVar("BJN_N_Leptons",-99.);
    vars.InitVar("BJN_N_PVtrackOvCollTrk",-99.);
    vars.InitVar("BJN_N_AvgIp3D",-99.);
    vars.InitVar("BJN_N_AvgIp3Dsig",-99.);
    vars.InitVar("BJN_N_AvgSip3Dsig",-99.);
    vars.InitVar("BJN_N_AvgIp1Dsig",-99.);
    initialized=true;
}

void BJetnessProcessor::Process(const InputCollections& input,VariableContainer& vars){
    if(!initialized) cerr << "tree processor not initialized" << endl; // complain if not initialized but keep running

    edm::Handle< vector < float > > bjetness;
    input.iEvent.getByToken(bjetness_, bjetness);
        
    /*
      (*bjetness)[0]; is the pt of the leading jet after correction. This value is saved as a reference value in the comparison of events.
      (*bjetness)[1]; is the number of lepton of the bjetness jet.
      (*bjetness)[2]; is the ratio between non primary vertex and primary vertex tracks.
      (*bjetness)[3]; is the average value of the 3D IP
      (*bjetness)[4]; is the average significance of the 3D IP
      (*bjetness)[5]; is the average signed significance of the 3D IP
      (*bjetness)[6]; is the average significance of the 1D IP 
    */
    
    vars.FillVar("BJN_Jet0_Pt",(*bjetness)[0]);
    vars.FillVar("BJN_N_Leptons",(*bjetness)[1]);
    vars.FillVar("BJN_N_PVtrackOvCollTrk",(*bjetness)[2]);
    vars.FillVar("BJN_N_AvgIp3D",(*bjetness)[3]);
    vars.FillVar("BJN_N_AvgIp3Dsig",(*bjetness)[4]);
    vars.FillVar("BJN_N_AvgSip3Dsig",(*bjetness)[5]);
    vars.FillVar("BJN_N_AvgIp1Dsig",(*bjetness)[6]);
}
