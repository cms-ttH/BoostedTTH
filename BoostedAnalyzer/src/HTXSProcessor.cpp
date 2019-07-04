#include "BoostedTTH/BoostedAnalyzer/interface/HTXSProcessor.hpp"

using namespace std;

HTXSProcessor::HTXSProcessor(){}
HTXSProcessor::~HTXSProcessor(){}


void HTXSProcessor::Init(const InputCollections& input,VariableContainer& vars){

    vars.InitVar( "HTXS_Stage_0_Category", "I" );
    vars.InitVar( "HTXS_Stage_1_Category_25GeV", "I" );
    vars.InitVar( "HTXS_Stage_1_Category_30GeV", "I" );
    vars.InitVar( "HTXS_Stage_1p1_Category", "I" );
    vars.InitVar( "HTXS_GenHiggs_Rapidity", -99. );
    vars.InitVar( "HTXS_GenHiggs_Pt", -99. );

    initialized=true;
}

void HTXSProcessor::Process(const InputCollections& input,VariableContainer& vars){
    if(!initialized) cerr << "tree processor not initialized" << endl;

    // Fill HTXS Variables
    vars.FillVar( "HTXS_Stage_0_Category", input.htxs.stage0_cat );
    vars.FillVar( "HTXS_Stage_1_Category_25GeV", input.htxs.stage1_cat_pTjet25GeV );
    vars.FillVar( "HTXS_Stage_1_Category_30GeV", input.htxs.stage1_cat_pTjet30GeV );
    vars.FillVar( "HTXS_Stage_1p1_Category", input.htxs.stage1p1_cat );
    vars.FillVar( "HTXS_GenHiggs_Rapidity", input.htxs.higgs.Rapidity() );
    vars.FillVar( "HTXS_GenHiggs_Pt", input.htxs.higgs.Pt() );

}
