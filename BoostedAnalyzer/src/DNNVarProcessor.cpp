#include "BoostedTTH/BoostedAnalyzer/interface/DNNVarProcessor.hpp"
using namespace std;

DNNVarProcessor::DNNVarProcessor(){
    DNNClassifierBase::pyInitialize();
    sldnnclassifier=new DNNClassifier_SL("v4");
    classifier_created_inside=true;
}


DNNVarProcessor::DNNVarProcessor(DNNClassifier_SL* sldnnclassifier_):sldnnclassifier(sldnnclassifier_){
    classifier_created_inside=false;
}

DNNVarProcessor::~DNNVarProcessor(){
    if(classifier_created_inside) {
        delete sldnnclassifier;
        DNNClassifierBase::pyFinalize();
    }
}

void DNNVarProcessor::Init(const InputCollections& input,VariableContainer& vars){

    vars.InitVar("DNN_RWTH_ttH");       //0
    vars.InitVar("DNN_RWTH_ttbb");      //1
    vars.InitVar("DNN_RWTH_ttb");       //2
    vars.InitVar("DNN_RWTH_tt2b");      //3
    vars.InitVar("DNN_RWTH_ttcc");      //4
    vars.InitVar("DNN_RWTH_ttlf");      //5
    vars.InitVar("DNN_RWTH_other");     //6
    vars.InitVar("DNN_RWTH_class","I");
    initialized=true;
}


void DNNVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
    if(!initialized) cerr << "tree processor not initialized" << endl;
    if(input.selectedMuons.size()+input.selectedElectrons.size()!=1) return;
    
    dnn_output.reset();
    
    std::vector<TLorentzVector> lepvecs=BoostedUtils::GetTLorentzVectors(BoostedUtils::GetLepVecs(input.selectedElectrons,input.selectedMuons));
    std::vector<TLorentzVector> jetvecs=BoostedUtils::GetTLorentzVectors(BoostedUtils::GetJetVecs(input.selectedJets));
    TLorentzVector metP4=BoostedUtils::GetTLorentzVector(input.correctedMET.corP4(pat::MET::Type1XY));
    std::vector<double> jetcsvs;
    for(auto j=input.selectedJets.begin(); j!=input.selectedJets.end(); j++){
        jetcsvs.push_back(MiniAODHelper::GetJetCSV(*j));
    }
    dnn_output = sldnnclassifier->evaluate(jetvecs,jetcsvs,lepvecs[0],metP4);
    
    vars.FillVar("DNN_RWTH_ttH",dnn_output.ttH());
    vars.FillVar("DNN_RWTH_ttbb",dnn_output.ttbb());
    vars.FillVar("DNN_RWTH_ttb",dnn_output.ttb());
    vars.FillVar("DNN_RWTH_tt2b",dnn_output.tt2b());
    vars.FillVar("DNN_RWTH_ttcc",dnn_output.ttcc());
    vars.FillVar("DNN_RWTH_ttlf",dnn_output.ttlf());
    vars.FillVar("DNN_RWTH_other",dnn_output.other());
    vars.FillIntVar("DNN_RWTH_class",int(dnn_output.mostProbableClass()));
}