#include "BoostedTTH/BoostedAnalyzer/interface/SingleTopVarProcessor.hpp"

using namespace std;

SingleTopVarProcessor::SingleTopVarProcessor():tHqJetSelection(new THQJetSelection()),btagger("pfCombinedInclusiveSecondaryVertexV2BJetTags"){
    tHqJetSelection->InitCutflow(cutflow);
}
SingleTopVarProcessor::~SingleTopVarProcessor(){}


void SingleTopVarProcessor::Init(const InputCollections& input,VariableContainer& vars){

    vars.InitVar( "N_SingleTopJets",-1,"I");
    vars.InitVars( "SingleTopJet_CSV",-9.,"N_SingleTopJets");
    vars.InitVars( "SingleTopJet_Pt",-9.,"N_SingleTopJets");
    vars.InitVars( "SingleTopJet_Eta",-9.,"N_SingleTopJets");
    vars.InitVars( "SingleTopJet_Phi",-9.,"N_SingleTopJets");
    vars.InitVars( "SingleTopJet_E",-9.,"N_SingleTopJets");
    vars.InitVar( "Evt_SingleTopJet_MaxEta",-9.);
    vars.InitVar( "N_SingleTopJets30",-1,"I");
    vars.InitVar( "N_TaggedSingleTopJetsM",-1,"I");
    vars.InitVar( "N_TaggedSingleTopJetsT",-1,"I");
    vars.InitVar( "N_TaggedSingleTopJetsL",-1,"I");
    vars.InitVar( "I_PassesTHQJetSelection",-1,"I");
    
    initialized=true;
}

void SingleTopVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
    if(!initialized) cerr << "tree processor not initialized" << endl;
    vars.FillVar( "N_SingleTopJets",input.selectedJetsSingleTop.size());
    int njets30=0;
    int ntagsM=0;
    int ntagsL=0;
    int ntagsT=0;
    float maxeta=0;    
    for(auto j=input.selectedJetsSingleTop.begin(); j!=input.selectedJetsSingleTop.end(); j++){
	if(j->pt()>30) njets30++;
	if(fabs(j->eta())<2.4&&BoostedUtils::PassesCSV(*j,'T')) ntagsT++;
	if(fabs(j->eta())<2.4&&BoostedUtils::PassesCSV(*j,'M')) ntagsM++;
	if(fabs(j->eta())<2.4&&BoostedUtils::PassesCSV(*j,'L')) ntagsL++;
	maxeta=fmax(fabs(j->eta()),maxeta);
	int i = j - input.selectedJetsSingleTop.begin();
	vars.FillVars( "SingleTopJet_CSV",i,BoostedUtils::GetJetCSV(*j,btagger));
	vars.FillVars( "SingleTopJet_Pt",i,j->pt());
	vars.FillVars( "SingleTopJet_Eta",i,j->eta());
	vars.FillVars( "SingleTopJet_Phi",i,j->phi());
	vars.FillVars( "SingleTopJet_E",i,j->energy());

    }
    vars.FillVar( "N_SingleTopJets30",njets30);
    vars.FillVar( "N_TaggedSingleTopJetsM",ntagsM);
    vars.FillVar( "N_TaggedSingleTopJetsT",ntagsT);
    vars.FillVar( "N_TaggedSingleTopJetsL",ntagsL);
    vars.FillVar( "Evt_SingleTopJet_MaxEta",maxeta);    
    int isTHQselected=tHqJetSelection->IsSelected(input,cutflow);
    vars.FillVar( "I_PassesTHQJetSelection",isTHQselected);    
}
