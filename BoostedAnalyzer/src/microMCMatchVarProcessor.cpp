#include "BoostedTTH/BoostedAnalyzer/interface/microMCMatchVarProcessor.hpp"

using namespace std;

microMCMatchVarProcessor::microMCMatchVarProcessor (){}
microMCMatchVarProcessor::~microMCMatchVarProcessor (){}


void microMCMatchVarProcessor::Init(const InputCollections& input,VariableContainer& vars){

 
  vars.InitVar( "GenEvt_I_TTPlusCC",-1,"I" );
  vars.InitVar( "GenEvt_I_TTPlusBB",-1,"I" );
  vars.InitVar( "GenEvt_TTxId_FromProducer",-1,"I" );
  vars.InitVar( "N_GoodTagsM",-1,"I" );
  vars.InitVar( "N_MisTagsM",-1,"I" );
  
  initialized = true;
}


void microMCMatchVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  
  if(!initialized) cerr << "tree processor not initialized" << endl;
  
  int iBB = 0;
  int iCC = 0;
  
  if(input.sampleType == SampleType::ttbb) iBB = 3;
  if(input.sampleType == SampleType::ttb) iBB = 1;
  if(input.sampleType == SampleType::tt2b) iBB = 2;
  if(input.sampleType == SampleType::ttcc) iCC = 1;
  
  vars.FillVar( "GenEvt_I_TTPlusCC",iCC );
  vars.FillVar( "GenEvt_I_TTPlusBB",iBB );
  if(input.genTopEvt.IsFilled()){
      vars.FillVar( "GenEvt_TTxId_FromProducer",input.genTopEvt.GetTTxIdFromProducer());
  }
  int nGoodTagsM=0;
  int nMisTagsM=0;
  for(auto j=input.selectedJets.begin(); j!=input.selectedJets.end(); j++){
      if (!(CSVHelper::PassesCSV(*j, "DeepJet", CSVHelper::CSVwp::Medium,input.era))) continue;
      if(abs(j->hadronFlavour())==5) nGoodTagsM++;
      if(abs(j->hadronFlavour())!=5) nMisTagsM++;
  }  
  vars.FillVar( "N_GoodTagsM",nGoodTagsM);
  vars.FillVar( "N_MisTagsM",nMisTagsM);
}
