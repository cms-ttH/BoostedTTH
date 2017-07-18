#include "BoostedTTH/BoostedAnalyzer/interface/ZPrimeToTPrimeAllHadProcessor.hpp"
#include <string> 
#include "MiniAOD/MiniAODHelper/interface/TTM_SDM.h"



// all configurations should be done in constructor
ZPrimeToTPrimeAllHadProcessor::ZPrimeToTPrimeAllHadProcessor(){
		std::string cmsswbase = getenv("CMSSW_BASE");
		TString filename_QCD=cmsswbase+"/src/BoostedTTH/BoostedAnalyzer/data/mistagrateweights/BKG_QCD_false_negativ.root";
		TString filename_SDM=cmsswbase+"/src/BoostedTTH/BoostedAnalyzer/data/mistagrateweights/BKG_QCD_SDM_Cut.root";
		TString filename_ABCD_QCD_MSD=cmsswbase+"/src/BoostedTTH/BoostedAnalyzer/data/ABCD_MSD/MSDs_QCD_histos.root";
                
		histo_ABCD_QCD_MSD_top_nobtag=foo.Load_DisSDM(filename_ABCD_QCD_MSD,"QCD_HT_Notopbtag_Top_MSD");
		histo_ABCD_QCD_MSD_top_withbtag=foo.Load_DisSDM(filename_ABCD_QCD_MSD,"QCD_HT_Withtopbtag_Top_MSD");
		histo_ABCD_QCD_MSD_W_nobtag=foo.Load_DisSDM(filename_ABCD_QCD_MSD,"QCD_HT_Notopbtag_W_MSD");
		histo_ABCD_QCD_MSD_W_withbtag=foo.Load_DisSDM(filename_ABCD_QCD_MSD,"QCD_HT_Withtopbtag_W_MSD");

                foo.Load_QCDMistag(filename_QCD,"BKG_QCD_false_negativ");
                histo_TTM_SDM=foo.Load_DisSDM(filename_SDM,"BKG_QCD_SDM_Cut");
                
//                 csvReweighter_ = csvReweighter;
            
                
}
            
            
            
            
ZPrimeToTPrimeAllHadProcessor::~ZPrimeToTPrimeAllHadProcessor(){
    delete histo_ABCD_QCD_MSD_top_nobtag;
    
}


void ZPrimeToTPrimeAllHadProcessor::Init(const InputCollections& input,VariableContainer& vars){
    
    InitGenVars(vars);
    InitBasicRecoVars(vars);
    InitSignalandSidbandVars(vars);
    InitTaggingVars(vars);
    InitABCDVars(vars);
    //InitmisstagBKGVars(vars);

    initialized=true;
}

//void ZPrimeToTPrimeAllHadProcessor::Process(const InputCollections& input,VariableContainer& vars){
//    FillGenVars(vars);
//    
//}



void ZPrimeToTPrimeAllHadProcessor::InitGenVars(VariableContainer& vars){
    

 
    vars.InitVar("N_Gen_ZPrimes","I");
    vars.InitVar("N_Gen_Tops","I");
    vars.InitVar("N_Gen_Topbars","I");
    vars.InitVar("N_Gen_TopsandTopbars","I");
    
    vars.InitVar("N_Gen_TPrimes","I");
    vars.InitVar("N_Gen_TPrimebars","I");
    vars.InitVar("N_Gen_TPrimesandTPrimebars","I");
    
    vars.InitVar("N_Gen_WplusfromTops","I");
    vars.InitVar("N_Gen_WminusfromTopbars","I");
    vars.InitVar("N_Gen_WfromTopsandTopbars","I");
    
    vars.InitVar("N_Gen_WplusfromTPrimes","I");
    vars.InitVar("N_Gen_WminusfromTPrimebars","I");
    vars.InitVar("N_Gen_WfromTPrimesandTPrimebars","I");
    
    vars.InitVar("N_Gen_BottomfromTops","I");
    vars.InitVar("N_Gen_BottombarfromTopbars","I");
    vars.InitVar("N_Gen_BottomfromTopsandTopbars","I");
    
    vars.InitVar("N_Gen_BottomfromTPrimes","I");
    vars.InitVar("N_Gen_BottombarfromTPrimebars","I");
    vars.InitVar("N_Gen_BottomfromTPrimesandTPrimebars","I");
    vars.InitVar("N_Gen_BottomfromBG","I");

    vars.InitVars("Gen_Top_Pt",-9.0,"N_Gen_Tops");
    vars.InitVars("Gen_Topbar_Pt",-9.0,"N_Gen_Topbars");
    vars.InitVars("Gen_TopandTopbar_Pt",-9.0,"N_Gen_TopsandTopbars");

    vars.InitVars("Gen_ZPrime_M","N_Gen_ZPrimes");
    vars.InitVars("Gen_TPrimeandTPrimebar_M",-9.0,"N_Gen_TPrimesandTPrimebars");   
    vars.InitVars("Gen_ZPrime_Pt",-9.0,"N_Gen_ZPrimes");   


    vars.InitVars("Gen_TPrime_Pt",-9.0,"N_Gen_TPrimes");
    vars.InitVars("Gen_TPrimebar_Pt",-9.0,"N_Gen_TPrimebars");
    vars.InitVars("Gen_TPrimeandTPrimebar_Pt",-9.0,"N_Gen_TPrimesandTPrimebars");

    vars.InitVars("Gen_WplusfromTop_Pt",-9.0,"N_Gen_WplusfromTops");
    vars.InitVars("Gen_WminusfromTopbar_Pt",-9.0,"N_Gen_WminusfromTopbars");
    vars.InitVars("Gen_WfromTopandTopbar_Pt",-9.0,"N_Gen_WfromTopsandTopbars");

    vars.InitVars("Gen_WplusfromTPrime_Pt",-9.0,"N_Gen_WplusfromTPrimes");
    vars.InitVars("Gen_WminusfromTPrimebar_Pt",-9.0,"N_Gen_WminusfromTPrimebars");
    vars.InitVars("Gen_WfromTPrimeandTPrimebar_Pt",-9.0,"N_Gen_WfromTPrimesandTPrimebars");

    vars.InitVars("Gen_BottomfromTop_Pt",-9.0,"N_Gen_BottomfromTops");
    vars.InitVars("Gen_BottombarfromTopbar_Pt",-9.0,"N_Gen_BottombarfromTopbars");
    vars.InitVars("Gen_BottomfromTopandTopbar_Pt",-9.0,"N_Gen_BottomfromTopsandTopbars");

    vars.InitVars("Gen_BottomfromTPrime_Pt",-9.0,"N_Gen_BottomfromTPrimes");
    vars.InitVars("Gen_BottombarfromTPrimebar_Pt",-9.0,"N_Gen_BottombarfromTPrimebars");
    vars.InitVars("Gen_BottomfromTPrimeandTPrimebar_Pt",-9.0,"N_Gen_BottomfromTPrimesandTPrimebars");
    vars.InitVars("Gen_BottomsfromBG_Pt",-9.0,"N_Gen_BottomfromBG");
    
    
    vars.InitVars("Gen_Top_Eta",-9.0,"N_Gen_Tops");
    vars.InitVars("Gen_Topbar_Eta",-9.0,"N_Gen_Topbars");
    vars.InitVars("Gen_TopandTopbar_Eta",-9.0,"N_Gen_TopsandTopbars");

    vars.InitVars("Gen_ZPrime_Eta",-9.0,"N_Gen_ZPrimes");    
    vars.InitVars("Gen_TPrime_Eta",-9.0,"N_Gen_TPrimes");
    vars.InitVars("Gen_TPrimebar_Eta",-9.0,"N_Gen_TPrimebars");
    vars.InitVars("Gen_TPrimeandTPrimebar_Eta",-9.0,"N_Gen_TPrimesandTPrimebars");

    vars.InitVars("Gen_WplusfromTop_Eta",-9.0,"N_Gen_WplusfromTops");
    vars.InitVars("Gen_WminusfromTopbar_Eta",-9.0,"N_Gen_WminusfromTopbars");
    vars.InitVars("Gen_WfromTopandTopbar_Eta",-9.0,"N_Gen_WfromTopsandTopbars");

    vars.InitVars("Gen_WplusfromTPrime_Eta",-9.0,"N_Gen_WplusfromTPrimes");
    vars.InitVars("Gen_WminusfromTPrimebar_Eta",-9.0,"N_Gen_WminusfromTPrimebars");
    vars.InitVars("Gen_WfromTPrimeandTPrimebar_Eta",-9.0,"N_Gen_WfromTPrimesandTPrimebars");
    
    vars.InitVars("Gen_BottomfromTop_Eta",-9.0,"N_Gen_BottomfromTops");
    vars.InitVars("Gen_BottombarfromTopbar_Eta",-9.0,"N_Gen_BottombarfromTopbars");
    vars.InitVars("Gen_BottomfromTopandTopbar_Eta",-9.0,"N_Gen_BottomfromTopsandTopbars");

    vars.InitVars("Gen_BottomfromTPrime_Eta",-9.0,"N_Gen_BottomfromTPrimes");
    vars.InitVars("Gen_BottombarfromTPrimebar_Eta",-9.0,"N_Gen_BottombarfromTPrimebars");
    vars.InitVars("Gen_BottomfromTPrimeandTPrimebar_Eta",-9.0,"N_Gen_BottomfromTPrimesandTPrimebars");
    vars.InitVars("Gen_BottomsfromBG_Eta",-9.0,"N_Gen_BottomfromBG");

    
    vars.InitVar("Gen_Top_TPrime_DeltaR","F");//,"input.zprimetotprimeallhad.GetTops_fromZprimes().size()*input.zprimetotprimeallhad.GetTPrimebars().size()");
    vars.InitVar("Gen_Top_WfromTPrime_DeltaR","F");//,"input.zprimetotprimeallhad.GetTops_fromZprimes().size()*input.zprimetotprimeallhad.GetWminus_fromTPrimes().size()");
    vars.InitVar("Gen_Top_BottomfromTPrime_DeltaR","F");//,"input.zprimetotprimeallhad.GetTop_fromZprimess().size()*input.zprimetotprimeallhad.GetTPrimeDecayQuarks().size()");
    vars.InitVar("Gen_WfromTPrime_BottomfromTPrime_DeltaR","F");//,"input.zprimetotprimeallhad.GetWplus_fromTPrimes().size()*input.zprimetotprimeallhad.GetTPrimeDecayQuarks().size()");
    vars.InitVar("Gen_WfromTop_BottomfromTop_DeltaR","F");//,"input.zprimetotprimeallhad.GetWplus_fromTops().size()*input.zprimetotprimeallhad.GetTopDecayQuarks().size()");
    
    vars.InitVar("Gen_Top_WfromTPrime_DeltaEta","F");
    vars.InitVar("Gen_Top_BottomfromTPrime_DeltaEta","F");
    vars.InitVar("Gen_WfromTPrime_BottomfromTPrime_DeltaEta","F");
    
    vars.InitVar("Gen_Top_WfromTPrime_DeltaPhi","F");
    vars.InitVar("Gen_Top_BottomfromTPrime_DeltaPhi","F");
    vars.InitVar("Gen_WfromTPrime_BottomfromTPrime_DeltaPhi","F");
    
}

void ZPrimeToTPrimeAllHadProcessor::InitBasicRecoVars(VariableContainer& vars){

    vars.InitVar("N_packedPatJetsAK8PFCHSSoftDrop","I");
    vars.InitVars("packedPatJetsAK8PFCHSSoftDrop_Pt",-9.0,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("packedPatJetsAK8PFCHSSoftDrop_Eta",-9.0,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("packedPatJetsAK8PFCHSSoftDrop_Phi",-9.0,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("packedPatJetsAK8PFCHSSoftDrop_E",-9.0,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("packedPatJetsAK8PFCHSSoftDrop_M",-9.0,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("NjettinessAK8CHS_tau1",-9.0,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("NjettinessAK8CHS_tau2",-9.0,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("NjettinessAK8CHS_tau3",-9.0,"N_packedPatJetsAK8PFCHSSoftDrop");
    
    vars.InitVars("softDropMassAK8CHS",-9.0,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("cmsTopTagPFJetsCHSMassAK8",-9.0,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("packedPatJetsAK8PFCHSSoftDrop_subjetCSVv2",-9.0,"N_packedPatJetsAK8PFCHSSoftDrop");

//    vars.InitVar("N_selectedPatJetsAK8PFCHSSoftDropPacked","I");
//    vars.InitVar("N_packedPatJetsAK8PFCHSSoftDrop","I");
/*
    vars.InitVars("selectedPatJetsAK8PFCHSSoftDropPacked_E",-9.0,"N_selectedPatJetsAK8PFCHSSoftDropPacked");
    vars.InitVars("selectedPatJetsAK8PFCHSSoftDropPacked_M",-9.0,"N_selectedPatJetsAK8PFCHSSoftDropPacked");
    vars.InitVars("selectedPatJetsAK8PFCHSSoftDropPacked_Pt",-9.0,"N_selectedPatJetsAK8PFCHSSoftDropPacked");
    vars.InitVars("selectedPatJetsAK8PFCHSSoftDropPacked_Phi",-9.0,"N_selectedPatJetsAK8PFCHSSoftDropPacked");
    vars.InitVars("selectedPatJetsAK8PFCHSSoftDropPacked_Eta",-9.0,"N_selectedPatJetsAK8PFCHSSoftDropPacked");
    vars.InitVars("NsubjettinessAK8PFCHSSoftDropPacked_tau1",-9.0,"N_selectedPatJetsAK8PFCHSSoftDropPacked");
    vars.InitVars("NsubjettinessAK8PFCHSSoftDropPacked_tau2",-9.0,"N_selectedPatJetsAK8PFCHSSoftDropPacked");
    vars.InitVars("NsubjettinessAK8PFCHSSoftDropPacked_tau3",-9.0,"N_selectedPatJetsAK8PFCHSSoftDropPacked");
*/
    vars.InitVars("packedPatJetsAK8PFCHSSoftDrop_Dr_Top",-9.,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("packedPatJetsAK8PFCHSSoftDrop_Dr_GenB_Top",-9.,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("packedPatJetsAK8PFCHSSoftDrop_Dr_GenW_Top",-9.,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("packedPatJetsAK8PFCHSSoftDrop_Dr_bfromTPrime",-9.,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("packedPatJetsAK8PFCHSSoftDrop_Dr_GenTop_bfromTPrime",-9.,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("packedPatJetsAK8PFCHSSoftDrop_Dr_GenWfromTPrime_bfromTPrime",-9.,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("packedPatJetsAK8PFCHSSoftDrop_Dr_WfromTPrime",-9.,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("packedPatJetsAK8PFCHSSoftDrop_Dr_GenTop_WfromTPrime",-9.,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("packedPatJetsAK8PFCHSSoftDrop_Dr_GenbfromTPrime_WfromTPrime",-9.,"N_packedPatJetsAK8PFCHSSoftDrop");
    
    vars.InitVars("packedPatJetsAK8PFCHSSoftDrop_Dr_TopBG",-9.,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("packedPatJetsAK8PFCHSSoftDrop_Dr_WBG",-9.,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("packedPatJetsAK8PFCHSSoftDrop_Dr_BottomBG",-9.,"N_packedPatJetsAK8PFCHSSoftDrop");
 
   vars.InitVars("Jet_Dr_bfromTPrime",-9.,"N_Jets");
   vars.InitVars("Jet_Dr_bfromBG",-9.,"N_Jets");    

///Variables after reconstruction/Identification
  
   vars.InitVar("N_Tops","I");
   vars.InitVar("N_Tops_withbtag","I");
   vars.InitVar("N_Tops_anti","I");
   vars.InitVar("N_Tops_withbtag_anti","I");
   vars.InitVars("Tops_pt",-9.0,"N_Tops");
   vars.InitVars("Tops_eta",-9.0,"N_Tops");
   vars.InitVars("Tops_anti_pt",-9.0,"N_Tops_anti");
   vars.InitVars("Tops_anti_eta",-9.0,"N_Tops_anti");
   vars.InitVars("Tops_withbtag_pt",-9.0,"N_Tops_withbtag");  
   vars.InitVars("Tops_withbtag_eta",-9.0,"N_Tops_withbtag");
   vars.InitVars("Tops_withbtag_anti_pt",-9.0,"N_Tops_withbtag_anti");  
   vars.InitVars("Tops_withbtag_anti_eta",-9.0,"N_Tops_withbtag_anti");  
   
   vars.InitVar("N_Ws","I");
   vars.InitVar("N_Ws_anti","I");
   vars.InitVars("Ws_pt",-9.0,"N_Ws");
   vars.InitVars("Ws_eta",-9.0,"N_Ws");
   vars.InitVars("Ws_anti_pt",-9.0,"N_Ws_anti");
   vars.InitVars("Ws_anti_eta",-9.0,"N_Ws_anti");
   vars.InitVar("N_Bottoms","I");
   vars.InitVar("N_Bottoms_anti","I");
   vars.InitVar("N_no_Bottoms","I");
   vars.InitVars("Bottoms_pt",-9.0,"N_Bottoms");
   vars.InitVars("Bottoms_eta",-9.0,"N_Bottoms");
   vars.InitVars("Bottoms_anti_pt",-9.0,"N_Bottoms_anti");
   vars.InitVars("Bottoms_anti_eta",-9.0,"N_Bottoms_anti");
   vars.InitVars("No_Bottoms_pt",-9.0,"N_no_Bottoms");
   vars.InitVars("No_Bottoms_eta",-9.0,"N_no_Bottoms");
   
   vars.InitVar("N_Zs","I");
   vars.InitVar("N_Zs_anti","I");
   vars.InitVars("Zs_pt",-9.0,"N_Zs");
   vars.InitVars("Zs_eta",-9.0,"N_Zs");
   vars.InitVars("Zs_anti_pt",-9.0,"N_Zs_anti");
   vars.InitVars("Zs_anti_eta",-9.0,"N_Zs_anti");   
   
   vars.InitVar("N_Higgs","I");
   vars.InitVar("N_Higgs_with1btag","I");
   vars.InitVar("N_Higgs_with2btag","I");
   vars.InitVar("N_Higgs_anti","I");
   vars.InitVar("N_Higgs_with1btag_anti","I");
   vars.InitVar("N_Higgs_with2btag_anti","I");
   vars.InitVars("Higgs_pt",-9.0,"N_Higgs");
   vars.InitVars("Higgs_eta",-9.0,"N_Higgs");
   vars.InitVars("Higgs_anti_pt",-9.0,"N_Higgs_anti");
   vars.InitVars("Higgs_anti_eta",-9.0,"N_Higgs_anti");
   vars.InitVars("Higgs_with1btag_pt",-9.0,"N_Higgs_with1btag");  
   vars.InitVars("Higgs_with1btag_eta",-9.0,"N_Higgs_with1btag");
   vars.InitVars("Higgs_with1btag_anti_pt",-9.0,"N_Higgs_with1btag_anti");  
   vars.InitVars("Higgs_with1btag_anti_eta",-9.0,"N_Higgs_with1btag_anti");    
   vars.InitVars("Higgs_with2btag_pt",-9.0,"N_Higgs_with2btag");  
   vars.InitVars("Higgs_with2btag_eta",-9.0,"N_Higgs_with2btag");
   vars.InitVars("Higgs_with2btag_anti_pt",-9.0,"N_Higgs_with2btag_anti");  
   vars.InitVars("Higgs_with2btag_anti_eta",-9.0,"N_Higgs_with2btag_anti"); 
}   

void ZPrimeToTPrimeAllHadProcessor::InitSignalandSidbandVars(VariableContainer& vars){

    
    for(bool top : { false, true }){
        for(bool W : { false, true }){
            for(bool bottom : { false, true }){
                for(bool topwbt : { false, true }){
//                     if(top){bool tfirst : { false, true }
                        for(bool tfirst : { false, true }){
                            std::string str_region="Sideband_";
                            std::string str_bottom="";
                            std::string str_top="";
                            std::string str_W="";
                            std::string str_first="Topfirst_";
                            std::string fullstring="";
                            
                            if(top && topwbt && W && bottom){str_region="Signal_";};
                            if(top && !topwbt && W && bottom){str_region="Signal_";};
                            if(topwbt && top){str_top="withtopbtag_";};
                            if(!topwbt && top){str_top="";};
                            if(!top && !topwbt){str_top="top_anti_";};
                            if(!top && topwbt){str_top="top_withbtag_anti_";}
                            if(!W){str_W="W_anti_";};
                            if(!bottom){str_bottom="bottom_anti_";};
                            if(!tfirst){str_first="Wfirst_";};
                            
                            fullstring=str_region+str_top+str_W+str_bottom+str_first;
//                              std::cout<<"N_"+fullstring+"Tops"+"  created"<<endl;
//                             std::cout<<"lala0"<<endl;
                            vars.InitVar("N_"+fullstring+"Tops","I");
                            vars.InitVars(fullstring+"Tops_Pt",-9.0,"N_"+fullstring+"Tops");
                            vars.InitVars(fullstring+"Tops_Eta",-9.0,"N_"+fullstring+"Tops");
                            vars.InitVars(fullstring+"Tops_MSD",-9.0,"N_"+fullstring+"Tops");
                            vars.InitVars(fullstring+"Tops_t32",-9.0,"N_"+fullstring+"Tops");
                            vars.InitVars(fullstring+"Tops_t21",-9.0,"N_"+fullstring+"Tops");
                            vars.InitVars(fullstring+"Tops_subjetCSVv2",-9.0,"N_"+fullstring+"Tops");
                            
                            vars.InitVar("N_"+fullstring+"Ws","I");
                            vars.InitVars(fullstring+"Ws_Pt",-9.0,"N_"+fullstring+"Ws");
                            vars.InitVars(fullstring+"Ws_Eta",-9.0,"N_"+fullstring+"Ws");
                            vars.InitVars(fullstring+"Ws_MSD",-9.0,"N_"+fullstring+"Ws");
                            vars.InitVars(fullstring+"Ws_t32",-9.0,"N_"+fullstring+"Ws");
                            vars.InitVars(fullstring+"Ws_t21",-9.0,"N_"+fullstring+"Ws");

                            vars.InitVar("N_"+fullstring+"Bottoms","I");
                            vars.InitVars(fullstring+"Bottoms_Pt",-9.0,"N_"+fullstring+"Bottoms");
                            vars.InitVars(fullstring+"Bottoms_Eta",-9.0,"N_"+fullstring+"Bottoms");
                            vars.InitVars(fullstring+"Bottoms_CSVv2",-9.0,"N_"+fullstring+"Bottoms");
//                             std::cout<<"lala1"<<endl;

                            vars.InitVar(fullstring+"Tprime_M",-9.0,"F");
                            vars.InitVar(fullstring+"Tprime_Pt",-9.0,"F");
                            vars.InitVar(fullstring+"Zprime_M",-9.0,"F");
                            vars.InitVar(fullstring+"Zprime_Pt",-9.0,"F");
//                             std::cout<<"lala2"<<endl;
                            
                            fullstring=str_region+str_top+"MCtopmass_"+str_W+str_bottom+str_first;
//                             std::cout<<"N_"+fullstring+"Tops"+"  created"<<endl;
//                             std::cout<<"lala0"<<endl;
                            vars.InitVar("N_"+fullstring+"Tops","I");
                            vars.InitVars(fullstring+"Tops_Pt",-9.0,"N_"+fullstring+"Tops");
                            vars.InitVars(fullstring+"Tops_Eta",-9.0,"N_"+fullstring+"Tops");
                            vars.InitVars(fullstring+"Tops_MSD",-9.0,"N_"+fullstring+"Tops");
                            vars.InitVars(fullstring+"Tops_t32",-9.0,"N_"+fullstring+"Tops");
                            vars.InitVars(fullstring+"Tops_t21",-9.0,"N_"+fullstring+"Tops");
                            vars.InitVars(fullstring+"Tops_subjetCSVv2",-9.0,"N_"+fullstring+"Tops");
                            
                            vars.InitVar("N_"+fullstring+"Ws","I");
                            vars.InitVars(fullstring+"Ws_Pt",-9.0,"N_"+fullstring+"Ws");
                            vars.InitVars(fullstring+"Ws_Eta",-9.0,"N_"+fullstring+"Ws");
                            vars.InitVars(fullstring+"Ws_MSD",-9.0,"N_"+fullstring+"Ws");
                            vars.InitVars(fullstring+"Ws_t32",-9.0,"N_"+fullstring+"Ws");
                            vars.InitVars(fullstring+"Ws_t21",-9.0,"N_"+fullstring+"Ws");

                            vars.InitVar("N_"+fullstring+"Bottoms","I");
                            vars.InitVars(fullstring+"Bottoms_Pt",-9.0,"N_"+fullstring+"Bottoms");
                            vars.InitVars(fullstring+"Bottoms_Eta",-9.0,"N_"+fullstring+"Bottoms");
                            vars.InitVars(fullstring+"Bottoms_CSVv2",-9.0,"N_"+fullstring+"Bottoms");
//                             std::cout<<"lala1"<<endl;

                            vars.InitVar(fullstring+"Tprime_M",-9.0,"F");
                            vars.InitVar(fullstring+"Tprime_Pt",-9.0,"F");
                            vars.InitVar(fullstring+"Zprime_M",-9.0,"F");
                            vars.InitVar(fullstring+"Zprime_Pt",-9.0,"F");
//                             std::cout<<"lala2"<<endl;                            
                            
                        }
                    //}
                }
            }
        }
    }
}

/*
void ZPrimeToTPrimeAllHadProcessor::InitSignalandSidbandVars(VariableContainer& vars){
 
//Signal & Sidebands
   
   vars.InitVar("N_Signal_Tops","I");
   vars.InitVars("Signal_Tops_Pt","N_Signal_Tops");
   vars.InitVars("Signal_Tops_Eta","N_Signal_Tops");
   vars.InitVar("N_Signal_Ws","I");
   vars.InitVars("Signal_Ws_Pt","N_Signal_Ws");
   vars.InitVars("Signal_Ws_Eta","N_Signal_Ws");   
   vars.InitVar("N_Signal_Bottoms","I");
   vars.InitVars("Signal_Bottoms_Pt","N_Signal_Bottoms");
   vars.InitVars("Signal_Bottoms_Eta","N_Signal_Bottoms");
   vars.InitVar("Signal_Tprime_M","I");
   vars.InitVar("Signal_Tprime_Pt","I");
   vars.InitVar("Signal_Zprime_M","I");
   vars.InitVar("Signal_Zprime_Pt","I");
      
   
   vars.InitVar("N_Sideband_bottom_anti_Tops","I");
   vars.InitVars("Sideband_bottom_anti_Tops_Pt","N_Sideband_bottom_anti_Tops");
   vars.InitVars("Sideband_bottom_anti_Tops_Eta","N_Sideband_bottom_anti_Tops");
   vars.InitVar("N_Sideband_bottom_anti_Ws","I");
   vars.InitVars("Sideband_bottom_anti_Ws_Pt","N_Sideband_bottom_anti_Ws");
   vars.InitVars("Sideband_bottom_anti_Ws_Eta","N_Sideband_bottom_anti_Ws");   
   vars.InitVar("N_Sideband_bottom_anti_Bottoms","I");
   vars.InitVars("Sideband_bottom_anti_Bottoms_Pt","N_Signal_Bottoms");
   vars.InitVars("Sideband_bottom_anti_Bottoms_Eta","N_Signal_Bottoms");
   vars.InitVar("Sideband_bottom_anti_Tprime_M","I");
   vars.InitVar("Sideband_bottom_anti_Tprime_Pt","I");
   vars.InitVar("Sideband_bottom_anti_Zprime_M","I");
   vars.InitVar("Sideband_bottom_anti_Zprime_Pt","I");
   
   vars.InitVar("N_Signal_withtoptag_Tops","I");
   vars.InitVars("Signal_withtoptag_Tops_Pt","N_Signal_withtoptag_Tops");
   vars.InitVars("Signal_withtoptag_Tops_Eta","N_Signal_withtoptag_Tops");
   vars.InitVar("N_Signal_withtoptag_Ws","I");
   vars.InitVars("Signal_withtoptag_Ws_Pt","N_Signal_withtoptag_Ws");
   vars.InitVars("Signal_withtoptag_Ws_Eta","N_Signal_withtoptag_Ws");   
   vars.InitVar("N_Signal_withtoptag_Bottoms","I");
   vars.InitVars("Signal_withtoptag_Bottoms_Pt","N_Signal_withtoptag_Bottoms");
   vars.InitVars("Signal_withtoptag_Bottoms_Eta","N_Signal_withtoptag_Bottoms");
   vars.InitVar("Signal_withtopbtag_Tprime_M","I");
   vars.InitVar("Signal_withtopbtag_Tprime_Pt","I");
   vars.InitVar("Signal_withtopbtag_Zprime_M","I");
   vars.InitVar("Signal_withtopbtag_Zprime_Pt","I");
   
   vars.InitVar("N_Sideband_withtopbtag_bottom_anti_Tops","I");
   vars.InitVars("Sideband_withtopbtag_bottom_anti_Tops_Pt","N_Sideband_withtopbtag_bottom_anti_Tops");
   vars.InitVars("Sideband_withtopbtag_bottom_anti_Tops_Eta","N_Sideband_withtopbtag_bottom_anti_Tops");
   vars.InitVar("N_Sideband_withtopbtag_bottom_anti_Ws","I");
   vars.InitVars("Sideband_withtopbtag_bottom_anti_Ws_Pt","N_Sideband_withtopbtag_bottom_anti_Ws");
   vars.InitVars("Sideband_withtopbtag_bottom_anti_Ws_Eta","N_Sideband_withtopbtag_bottom_anti_Ws");   
   vars.InitVar("N_Sideband_withtopbtag_bottom_anti_Bottoms","I");
   vars.InitVars("Sideband_withtopbtag_bottom_anti_Bottoms_Pt","N_Sideband_withtopbtag_bottom_anti_Bottoms");
   vars.InitVars("Sideband_withtopbtag_bottom_anti_Bottoms_Eta","N_Sideband_withtopbtag_bottom_anti_Bottoms");
   vars.InitVar("Sideband_withtopbtag_bottom_anti_Tprime_M","I");
   vars.InitVar("Sideband_withtopbtag_bottom_anti_Tprime_Pt","I");
   vars.InitVar("Sideband_withtopbtag_bottom_anti_Zprime_M","I");
   vars.InitVar("Sideband_withtopbtag_bottom_anti_Zprime_Pt","I");
   
   vars.InitVar("N_Sideband_top_anti_Tops","I");
   vars.InitVars("Sideband_top_anti_Tops_Pt","N_Sideband_top_anti_Tops");
   vars.InitVars("Sideband_top_anti_Tops_Eta","N_Sideband_top_anti_Tops");
   vars.InitVar("N_Sideband_top_anti_Ws","I");
   vars.InitVars("Sideband_top_anti_Ws_Pt","N_Sideband_top_anti_Ws");
   vars.InitVars("Sideband_top_anti_Ws_Eta","N_Sideband_top_anti_Ws");   
   vars.InitVar("N_Sideband_top_anti_Bottoms","I");
   vars.InitVars("Sideband_top_anti_Bottoms_Pt","N_Sideband_top_anti_Bottoms");
   vars.InitVars("Sideband_top_anti_Bottoms_Eta","N_Sideband_top_anti_Bottoms");
   vars.InitVar("Sideband_top_anti_Tprime_M","I");
   vars.InitVar("Sideband_top_anti_Tprime_Pt","I");
   vars.InitVar("Sideband_top_anti_Zprime_M","I");
   vars.InitVar("Sideband_top_anti_Zprime_Pt","I");  
   
   vars.InitVar("N_Sideband_top_anti_bottom_anti_Tops","I");
   vars.InitVars("Sideband_top_anti_bottom_anti_Tops_Pt","N_Sideband_top_anti_bottom_anti_Tops");
   vars.InitVars("Sideband_top_anti_bottom_anti_Tops_Eta","N_Sideband_top_anti_bottom_anti_Tops");
   vars.InitVar("N_Sideband_top_anti_bottom_anti_Ws","I");
   vars.InitVars("Sideband_top_anti_bottom_anti_Ws_Pt","N_Sideband_top_anti_bottom_anti_Ws");
   vars.InitVars("Sideband_top_anti_bottom_anti_Ws_Eta","N_Sideband_top_anti_bottom_anti_Ws");   
   vars.InitVar("N_Sideband_top_anti_bottom_anti_Bottoms","I");
   vars.InitVars("Sideband_top_anti_bottom_anti_Bottoms_Pt","N_Sideband_top_anti_bottom_anti_Bottoms");
   vars.InitVars("Sideband_top_anti_bottom_anti_Bottoms_Eta","N_Sideband_top_anti_bottom_anti_Bottoms");
   vars.InitVar("Sideband_top_anti_bottom_anti_Tprime_M","I");
   vars.InitVar("Sideband_top_anti_bottom_anti_Tprime_Pt","I");
   vars.InitVar("Sideband_top_anti_bottom_anti_Zprime_M","I");
   vars.InitVar("Sideband_top_anti_bottom_anti_Zprime_Pt","I");  
   
   vars.InitVar("N_Sideband_top_withbtag_anti_Tops","I");
   vars.InitVars("Sideband_top_withbtag_anti_Tops_Pt","N_Sideband_top_withbtag_anti_Tops");
   vars.InitVars("Sideband_top_withbtag_anti_Tops_Eta","N_Sideband_top_withbtag_anti_Tops");
   vars.InitVar("N_Sideband_top_withbtag_anti_Ws","I");
   vars.InitVars("Sideband_top_withbtag_anti_Ws_Pt","N_Sideband_top_withbtag_anti_Ws");
   vars.InitVars("Sideband_top_withbtag_anti_Ws_Eta","N_Sideband_top_withbtag_anti_Ws");   
   vars.InitVar("N_Sideband_top_withbtag_anti_Bottoms","I");
   vars.InitVars("Sideband_top_withbtag_anti_Bottoms_Pt","N_Sideband_top_withbtag_anti_Bottoms");
   vars.InitVars("Sideband_top_withbtag_anti_Bottoms_Eta","N_Sideband_top_withbtag_anti_Bottoms");
   vars.InitVar("Sideband_top_withbtag_anti_Tprime_M","I");
   vars.InitVar("Sideband_top_withbtag_anti_Tprime_Pt","I");
   vars.InitVar("Sideband_top_withbtag_anti_Zprime_M","I");
   vars.InitVar("Sideband_top_withbtag_anti_Zprime_Pt","I"); 

   vars.InitVar("N_Sideband_top_withbtag_anti_bottom_anti_Tops","I");
   vars.InitVars("Sideband_top_withbtag_anti_Tops_bottom_anti_Pt","N_Sideband_top_withbtag_anti_bottom_anti_Tops");
   vars.InitVars("Sideband_top_withbtag_anti_Tops_bottom_anti_Eta","N_Sideband_top_withbtag_anti_bottom_anti_Tops");
   vars.InitVar("N_Sideband_top_withbtag_anti_bottom_anti_Ws","I");
   vars.InitVars("Sideband_top_withbtag_anti_bottom_anti_Ws_Pt","N_Sideband_top_withbtag_anti_bottom_anti_Ws");
   vars.InitVars("Sideband_top_withbtag_anti_bottom_anti_Ws_Eta","N_Sideband_top_withbtag_anti_bottom_anti_Ws");   
   vars.InitVar("N_Sideband_top_withbtag_anti_bottom_anti_Bottoms","I");
   vars.InitVars("Sideband_top_withbtag_anti_bottom_anti_Bottoms_Pt","N_Sideband_top_withbtag_anti_bottom_anti_Bottoms");
   vars.InitVars("Sideband_top_withbtag_anti_bottom_anti_Bottoms_Eta","N_Sideband_top_withbtag_anti_bottom_anti_Bottoms");
   vars.InitVar("Sideband_top_withbtag_anti_bottom_anti_Tprime_M","I");
   vars.InitVar("Sideband_top_withbtag_anti_bottom_anti_Tprime_Pt","I");
   vars.InitVar("Sideband_top_withbtag_anti_bottom_anti_Zprime_M","I");
   vars.InitVar("Sideband_top_withbtag_anti_bottom_anti_Zprime_Pt","I");

   vars.InitVar("N_Sideband_W_anti_Tops","I");
   vars.InitVars("Sideband_W_anti_Tops_Pt","N_Sideband_W_anti_Tops");
   vars.InitVars("Sideband_W_anti_Tops_Eta","N_Sideband_W_anti_Tops");
   vars.InitVar("N_Sideband_W_anti_Ws","I");
   vars.InitVars("Sideband_W_anti_Ws_Pt","N_Sideband_W_anti_Ws");
   vars.InitVars("Sideband_W_anti_Ws_Eta","N_Sideband_W_anti_Ws");   
   vars.InitVar("N_Sideband_W_anti_Bottoms","I");
   vars.InitVars("Sideband_W_anti_Bottoms_Pt","N_Sideband_W_anti_Bottoms");
   vars.InitVars("Sideband_W_anti_Bottoms_Eta","N_Sideband_W_anti_Bottoms");
   vars.InitVar("Sideband_W_anti_Tprime_M","I");
   vars.InitVar("Sideband_W_anti_Tprime_Pt","I");
   vars.InitVar("Sideband_W_anti_Zprime_M","I");
   vars.InitVar("Sideband_W_anti_Zprime_Pt","I");
   
   vars.InitVar("N_Sideband_W_anti_bottom_anti_Tops","I");
   vars.InitVars("Sideband_W_anti_bottom_anti_Tops_Pt","N_Sideband_W_anti_bottom_anti_Tops");
   vars.InitVars("Sideband_W_anti_bottom_anti_Tops_Eta","N_Sideband_W_anti_bottom_anti_Tops");
   vars.InitVar("N_Sideband_W_anti_bottom_anti_Ws","I");
   vars.InitVars("Sideband_W_anti_bottom_anti_Ws_Pt","N_Sideband_W_anti_bottom_anti_Ws");
   vars.InitVars("Sideband_W_anti_bottom_anti_Ws_Eta","N_Sideband_W_anti_bottom_anti_Ws");   
   vars.InitVar("N_Sideband_W_anti_bottom_anti_Bottoms","I");
   vars.InitVars("Sideband_W_anti_bottom_anti_Bottoms_Pt","N_Sideband_W_anti_bottom_anti_Bottoms");
   vars.InitVars("Sideband_W_anti_bottom_anti_Bottoms_Eta","N_Sideband_W_anti_bottom_anti_Bottoms");
   vars.InitVar("Sideband_W_anti_bottom_anti_Tprime_M","I");
   vars.InitVar("Sideband_W_anti_bottom_anti_Tprime_Pt","I");
   vars.InitVar("Sideband_W_anti_bottom_anti_Zprime_M","I");
   vars.InitVar("Sideband_W_anti_bottom_anti_Zprime_Pt","I");    
   
   vars.InitVar("N_Sideband_withtopbtag_W_anti_Tops","I");
   vars.InitVars("Sideband_withtopbtag_W_anti_Tops_Pt","N_Sideband_withtopbtag_W_anti_Tops");
   vars.InitVars("Sideband_withtopbtag_W_anti_Tops_Eta","N_Sideband_withtopbtag_W_anti_Tops");
   vars.InitVar("N_Sideband_withtopbtag_W_anti_Ws","I");
   vars.InitVars("Sideband_withtopbtag_W_anti_Ws_Pt","N_Sideband_withtopbtag_W_anti_Ws");
   vars.InitVars("Sideband_withtopbtag_W_anti_Ws_Eta","N_Sideband_withtopbtag_W_anti_Ws");   
   vars.InitVar("N_Sideband_withtopbtag_W_anti_Bottoms","I");
   vars.InitVars("Sideband_withtopbtag_W_anti_Bottoms_Pt","N_Sideband_withtopbtag_W_anti_Bottoms");
   vars.InitVars("Sideband_withtopbtag_W_anti_Bottoms_Eta","N_Sideband_withtopbtag_W_anti_Bottoms");
   vars.InitVar("Sideband_withtopbtag_W_anti_Tprime_M","I");
   vars.InitVar("Sideband_withtopbtag_W_anti_Tprime_Pt","I");
   vars.InitVar("Sideband_withtopbtag_W_anti_Zprime_M","I");
   vars.InitVar("Sideband_withtopbtag_W_anti_Zprime_Pt","I");  
   
   vars.InitVar("N_Sideband_withtopbtag_W_anti_bottom_anti_Tops","I");
   vars.InitVars("Sideband_withtopbtag_W_anti_bottom_anti_Tops_Pt","N_Sideband_withtopbtag_W_anti_bottom_anti_Tops");
   vars.InitVars("Sideband_withtopbtag_W_anti_bottom_anti_Tops_Eta","N_Sideband_withtopbtag_W_anti_bottom_anti_Tops");
   vars.InitVar("N_Sideband_withtopbtag_W_anti_bottom_anti_Ws","I");
   vars.InitVars("Sideband_withtopbtag_W_anti_bottom_anti_Ws_Pt","N_Sideband_withtopbtag_W_anti_bottom_anti_Ws");
   vars.InitVars("Sideband_withtopbtag_W_anti_bottom_anti_Ws_Eta","N_Sideband_withtopbtag_W_anti_bottom_anti_Ws");   
   vars.InitVar("N_Sideband_withtopbtag_W_anti_bottom_anti_Bottoms","I");
   vars.InitVars("Sideband_withtopbtag_W_anti_bottom_anti_Bottoms_Pt","N_Sideband_withtopbtag_W_anti_bottom_anti_Bottoms");
   vars.InitVars("Sideband_withtopbtag_W_anti_bottom_anti_Bottoms_Eta","N_Sideband_withtopbtag_W_anti_bottom_anti_Bottoms");
   vars.InitVar("Sideband_withtopbtag_W_anti_bottom_anti_Tprime_M","I");
   vars.InitVar("Sideband_withtopbtag_W_anti_bottom_anti_Tprime_Pt","I");
   vars.InitVar("Sideband_withtopbtag_W_anti_bottom_anti_Zprime_M","I");
   vars.InitVar("Sideband_withtopbtag_W_anti_bottom_anti_Zprime_Pt","I"); 
   
   vars.InitVar("N_Sideband_top_anti_W_anti_Tops","I");
   vars.InitVars("Sideband_top_anti_W_anti_Tops_Pt","N_Sideband_top_anti_W_anti_Tops");
   vars.InitVars("Sideband_top_anti_W_anti_Tops_Eta","N_Sideband_top_anti_W_anti_Tops");
   vars.InitVar("N_Sideband_top_anti_W_anti_Ws","I");
   vars.InitVars("Sideband_top_anti_W_anti_Ws_Pt","N_Sideband_top_anti_W_anti_Ws");
   vars.InitVars("Sideband_top_anti_W_anti_Ws_Eta","N_Sideband_top_anti_W_anti_Ws");   
   vars.InitVar("N_Sideband_top_anti_W_anti_Bottoms","I");
   vars.InitVars("Sideband_top_anti_W_anti_Bottoms_Pt","N_Sideband_top_anti_W_anti_Bottoms");
   vars.InitVars("Sideband_top_anti_W_anti_Bottoms_Eta","N_Sideband_top_anti_W_anti_Bottoms");
   vars.InitVar("Sideband_top_anti_W_anti_Tprime_M","I");
   vars.InitVar("Sideband_top_anti_W_anti_Tprime_Pt","I");
   vars.InitVar("Sideband_top_anti_W_anti_Zprime_M","I");
   vars.InitVar("Sideband_top_anti_W_anti_Zprime_Pt","I");
   
   vars.InitVar("N_Sideband_top_anti_W_anti_bottom_anti_Tops","I");
   vars.InitVars("Sideband_top_anti_W_anti_bottom_anti_Tops_Pt","N_Sideband_top_anti_W_anti_bottom_anti_Tops");
   vars.InitVars("Sideband_top_anti_W_anti_bottom_anti_Tops_Eta","N_Sideband_top_anti_W_anti_bottom_anti_Tops");
   vars.InitVar("N_Sideband_top_anti_W_anti_bottom_anti_Ws","I");
   vars.InitVars("Sideband_top_anti_W_anti_bottom_anti_Ws_Pt","N_Sideband_top_anti_W_anti_bottom_anti_Ws");
   vars.InitVars("Sideband_top_anti_W_anti_bottom_anti_Ws_Eta","N_Sideband_top_anti_W_anti_bottom_anti_Ws");   
   vars.InitVar("N_Sideband_top_anti_W_anti_bottom_anti_Bottoms","I");
   vars.InitVars("Sideband_top_anti_W_anti_bottom_anti_Bottoms_Pt","N_Sideband_top_anti_W_anti_bottom_anti_Bottoms");
   vars.InitVars("Sideband_top_anti_W_anti_bottom_anti_Bottoms_Eta","N_Sideband_top_anti_W_anti_bottom_anti_Bottoms");
   vars.InitVar("Sideband_top_anti_W_anti_bottom_anti_Tprime_M","I");
   vars.InitVar("Sideband_top_anti_W_anti_bottom_anti_Tprime_Pt","I");
   vars.InitVar("Sideband_top_anti_W_anti_bottom_anti_Zprime_M","I");
   vars.InitVar("Sideband_top_anti_W_anti_bottom_anti_Zprime_Pt","I"); 

   vars.InitVar("N_Sideband_top_withbtag_anti_W_anti_Tops","I");
   vars.InitVars("Sideband_top_withbtag_anti_W_anti_Tops_Pt","N_Sideband_top_withbtag_anti_W_anti_Tops");
   vars.InitVars("Sideband_top_withbtag_anti_W_anti_Tops_Eta","N_Sideband_top_withbtag_anti_W_anti_Tops");
   vars.InitVar("N_Sideband_top_withbtag_anti_W_anti_Ws","I");
   vars.InitVars("Sideband_top_withbtag_anti_W_anti_Ws_Pt","N_Sideband_top_withbtag_anti_W_anti_Ws");
   vars.InitVars("Sideband_top_withbtag_anti_W_anti_Ws_Eta","N_Sideband_top_withbtag_anti_W_anti_Ws");   
   vars.InitVar("N_Sideband_top_withbtag_anti_W_anti_Bottoms","I");
   vars.InitVars("Sideband_top_withbtag_anti_W_anti_Bottoms_Pt","N_Sideband_top_withbtag_anti_W_anti_Bottoms");
   vars.InitVars("Sideband_top_withbtag_anti_W_anti_Bottoms_Eta","N_Sideband_top_withbtag_anti_W_anti_Bottoms");
   vars.InitVar("Sideband_top_withbtag_anti_W_anti_Tprime_M","I");
   vars.InitVar("Sideband_top_withbtag_anti_W_anti_Tprime_Pt","I");
   vars.InitVar("Sideband_top_withbtag_anti_W_anti_Zprime_M","I");
   vars.InitVar("Sideband_top_withbtag_anti_W_anti_Zprime_Pt","I");
   
   vars.InitVar("N_Sideband_top_withbtag_anti_W_anti_bottom_anti_Tops","I");
   vars.InitVars("Sideband_top_withbtag_anti_W_anti_bottom_anti_Tops_Pt","N_Sideband_top_withbtag_anti_W_anti_bottom_anti_Tops");
   vars.InitVars("Sideband_top_withbtag_anti_W_anti_bottom_anti_Tops_Eta","N_Sideband_top_withbtag_anti_W_anti_bottom_anti_Tops");
   vars.InitVar("N_Sideband_top_withbtag_anti_W_anti_bottom_anti_Ws","I");
   vars.InitVars("Sideband_top_withbtag_anti_W_anti_bottom_anti_Ws_Pt","N_Sideband_top_withbtag_anti_W_anti_bottom_anti_Ws");
   vars.InitVars("Sideband_top_withbtag_anti_W_anti_bottom_anti_Ws_Eta","N_Sideband_top_withbtag_anti_W_anti_bottom_anti_Ws");   
   vars.InitVar("N_Sideband_top_withbtag_anti_W_anti_bottom_anti_Bottoms","I");
   vars.InitVars("Sideband_top_withbtag_anti_W_anti_bottom_anti_Bottoms_Pt","N_Sideband_top_withbtag_anti_W_anti_bottom_anti_Bottoms");
   vars.InitVars("Sideband_top_withbtag_anti_W_anti_bottom_anti_Bottoms_Eta","N_Sideband_top_withbtag_anti_W_anti_bottom_anti_Bottoms");
   vars.InitVar("Sideband_top_withbtag_anti_W_anti_bottom_anti_Tprime_M","I");
   vars.InitVar("Sideband_top_withbtag_anti_W_anti_bottom_anti_Tprime_Pt","I");
   vars.InitVar("Sideband_top_withbtag_anti_W_anti_bottom_anti_Zprime_M","I");
   vars.InitVar("Sideband_top_withbtag_anti_W_anti_bottom_anti_Zprime_Pt","I");  
   
    

}
*/
			  
void ZPrimeToTPrimeAllHadProcessor::InitTaggingVars(VariableContainer& vars){

//variables for TTM Kevin

		
		vars.InitVar("TTM_Zprime_M",-9.0,"F");
		vars.InitVar("TTM_Zprime_pt",-9.0,"F");
		vars.InitVar("TTM_Zprime_eta",-9.0,"F");
		vars.InitVar("TTM_Tprime_M",-9.0,"F");
		vars.InitVar("TTM_Tprime_pt",-9.0,"F");
		vars.InitVar("TTM_Tprime_eta",-9.0,"F");
		vars.InitVar("TTM_separated_highest_bottoms_M",-9.0,"F");
		vars.InitVar("TTM_separated_highest_bottoms_pt",-9.0,"F");
		vars.InitVar("TTM_separated_highest_bottoms_eta",-9.0,"F");
		vars.InitVar("TTM_highest_Ws_M",-9.0,"F");
		vars.InitVar("TTM_highest_Ws_pt",-9.0,"F");
		vars.InitVar("TTM_highest_Ws_eta",-9.0,"F");
		vars.InitVar("TTM_AK8_top_candidates_highest_M",-9.0,"F");
		vars.InitVar("TTM_AK8_top_candidates_highest_pt",-9.0,"F");
		vars.InitVar("TTM_AK8_top_candidates_highest_eta",-9.0,"F");
		vars.InitVar("N_TTM_separated_bottoms",-9.0,"I");
		vars.InitVars("TTM_separated_bottoms_M",-9.0,"N_TTM_separated_bottoms");
		vars.InitVars("TTM_separated_bottoms_pt",-9.0,"N_TTM_separated_bottoms");
		vars.InitVars("TTM_separated_bottoms_eta",-9.0,"N_TTM_separated_bottoms");
		vars.InitVar("TTM_Mistagrate",-9.0,"F");
		vars.InitVar("TTM_RndmSDM",-9.0,"F");
		
		//second run
		
		vars.InitVar("TTM_no_top_Zprime_M",-9.0,"F");
		vars.InitVar("TTM_no_top_Zprime_pt",-9.0,"F");
		vars.InitVar("TTM_no_top_Zprime_eta",-9.0,"F");
		vars.InitVar("TTM_no_top_Tprime_M",-9.0,"F");
		vars.InitVar("TTM_no_top_Tprime_pt",-9.0,"F");
		vars.InitVar("TTM_no_top_Tprime_eta",-9.0,"F");
		vars.InitVar("TTM_no_top_separated_highest_bottoms_M",-9.0,"F");
		vars.InitVar("TTM_no_top_separated_highest_bottoms_pt",-9.0,"F");
		vars.InitVar("TTM_no_top_separated_highest_bottoms_eta",-9.0,"F");
		vars.InitVar("N_TTM_no_top_separated_bottoms",-9.0,"I");
		vars.InitVars("TTM_no_top_separated_bottoms_M",-9.0,"N_TTM_no_top_separated_bottoms");
		vars.InitVars("TTM_no_top_separated_bottoms_pt",-9.0,"N_TTM_no_top_separated_bottoms");
		vars.InitVars("TTM_no_top_separated_bottoms_eta",-9.0,"N_TTM_no_top_separated_bottoms");
		
    ///Variables for misstag rates and tagging efficiencies
   
   vars.InitVar("N_tagged_top","I");
   vars.InitVars("tagged_top_pt",-9.0,"N_tagged_top");
   vars.InitVars("tagged_top_eta",-9.0,"N_tagged_top");
   vars.InitVar("N_tagged_top_withbtag","I");
   vars.InitVars("tagged_top_withbtag_pt",-9.0,"N_tagged_top_withbtag");
   vars.InitVars("tagged_top_withbtag_eta",-9.0,"N_tagged_top_withbtag");
   vars.InitVar("N_tagged_W","I");
   vars.InitVars("tagged_W_pt",-9.0,"N_tagged_W");
   vars.InitVars("tagged_W_eta",-9.0,"N_tagged_W");
   vars.InitVar("N_tagged_bottom","I");
   vars.InitVars("tagged_bottom_pt",-9.0,"N_tagged_bottom");
   vars.InitVars("tagged_bottom_eta",-9.0,"N_tagged_bottom");

   vars.InitVar("N_misstagged_top","I");
   vars.InitVars("misstagged_top_pt",-9.0,"N_misstagged_top");
   vars.InitVars("misstagged_top_eta",-9.0,"N_misstagged_top");
   vars.InitVar("N_misstagged_top_withbtag","I");
   vars.InitVars("misstagged_top_withbtag_pt",-9.0,"N_misstagged_top_withbtag");
   vars.InitVars("misstagged_top_withbtag_eta",-9.0,"N_misstagged_top_withbtag");
   vars.InitVar("N_misstagged_W","I");
   vars.InitVars("misstagged_W_pt",-9.0,"N_misstagged_W");
   vars.InitVars("misstagged_W_eta",-9.0,"N_misstagged_W");
   vars.InitVar("N_misstagged_bottom","I");
   vars.InitVars("misstagged_bottom_pt",-9.0,"N_misstagged_bottom");
   vars.InitVars("misstagged_bottom_eta",-9.0,"N_misstagged_bottom");
   
   vars.InitVar("N_AK8_top_tag_candidates","I");
   vars.InitVars("AK8_top_tag_candidates_pt",-9.0,"N_AK8_top_tag_candidates");
   vars.InitVars("AK8_top_tag_candidates_eta",-9.0,"N_AK8_top_tag_candidates");
   vars.InitVar("N_AK8_W_tag_candidates","I");
   vars.InitVars("AK8_W_tag_candidates_pt",-9.0,"N_AK8_W_tag_candidates");
   vars.InitVars("AK8_W_tag_candidates_eta",-9.0,"N_AK8_W_tag_candidates");
   vars.InitVar("N_AK4_bottom_tag_candidates","I");
   vars.InitVars("AK4_bottom_tag_candidates_pt",-9.0,"N_AK4_bottom_tag_candidates");
   vars.InitVars("AK4_bottom_tag_candidates_eta",-9.0,"N_AK4_bottom_tag_candidates");
   
   vars.InitVar("N_AK8_top_misstag_candidates","I");
   vars.InitVars("AK8_top_misstagged_candidates_pt",-9.0,"N_AK8_top_misstag_candidates");
   vars.InitVars("AK8_top_misstagged_candidates_eta",-9.0,"N_AK8_top_misstag_candidates");
   vars.InitVar("N_AK8_W_misstag_candidates","I");
   vars.InitVars("AK8_W_misstagged_candidates_pt",-9.0,"N_AK8_W_misstag_candidates");
   vars.InitVars("AK8_W_misstagged_candidates_eta",-9.0,"N_AK8_W_misstag_candidates");
   vars.InitVar("N_AK4_bottom_misstag_candidates","I");
   vars.InitVars("AK4_bottom_misstagged_candidates_pt",-9.0,"N_AK4_bottom_misstag_candidates");
   vars.InitVars("AK4_bottom_misstagged_candidates_eta",-9.0,"N_AK4_bottom_misstag_candidates");
   
   
   
   vars.InitVar("N_tagged_top_anti","I");
   vars.InitVars("tagged_top_anti_pt",-9.0,"N_tagged_top_anti");
   vars.InitVars("tagged_top_anti_eta",-9.0,"N_tagged_top_anti");
   vars.InitVar("N_tagged_top_withbtag_anti","I");
   vars.InitVars("tagged_top_withbtag_anti_pt",-9.0,"N_tagged_top_withbtag_anti");
   vars.InitVars("tagged_top_withbtag_anti_eta",-9.0,"N_tagged_top_withbtag_anti");
   vars.InitVar("N_tagged_W_anti","I");
   vars.InitVars("tagged_W_anti_pt",-9.0,"N_tagged_W_anti");
   vars.InitVars("tagged_W_anti_eta",-9.0,"N_tagged_W_anti");
   vars.InitVar("N_tagged_anti_bottom","I");
   vars.InitVars("tagged_bottom_anti_pt",-9.0,"N_tagged_anti_bottom");
   vars.InitVars("tagged_bottom_anti_eta",-9.0,"N_tagged_anti_bottom");

   vars.InitVar("N_misstagged_top_anti","I");
   vars.InitVars("misstagged_top_anti_pt",-9.0,"N_misstagged_top_anti");
   vars.InitVars("misstagged_top_anti_eta",-9.0,"N_misstagged_top_anti");
   vars.InitVar("N_misstagged_top_withbtag_anti","I");
   vars.InitVars("misstagged_top_withbtag_anti_pt",-9.0,"N_misstagged_top_withbtag_anti");
   vars.InitVars("misstagged_top_withbtag_anti_eta",-9.0,"N_misstagged_top_withbtag_anti");
   vars.InitVar("N_misstagged_W_anti","I");
   vars.InitVars("misstagged_W_anti_pt",-9.0,"N_misstagged_W_anti");
   vars.InitVars("misstagged_W_anti_eta",-9.0,"N_misstagged_W_anti");
   vars.InitVar("N_misstagged_bottom_anti","I");
   vars.InitVars("misstagged_bottom_anti_pt",-9.0,"N_misstagged_bottom_anti");
   vars.InitVars("misstagged_bottom_anti_eta",-9.0,"N_misstagged_bottom_anti");
   
   vars.InitVar("N_AK8_top_candidates","I");
   vars.InitVars("AK8_top_candidates_pt",-9.0,"N_AK8_top_candidates");
   vars.InitVars("AK8_top_candidates_eta",-9.0,"N_AK8_top_candidates");
   vars.InitVar("N_AK8_W_candidates","I");
   vars.InitVars("AK8_W_candidates_pt",-9.0,"N_AK8_W_candidates");
   vars.InitVars("AK8_W_candidates_eta",-9.0,"N_AK8_W_candidates");
   vars.InitVar("N_AK4_bottom_candidates","I");
   vars.InitVars("AK4_bottom_candidates_pt",-9.0,"N_AK4_bottom_candidates");
   vars.InitVars("AK4_bottom_candidates_eta",-9.0,"N_AK4_bottom_candidates");   
   
}



   //AK8_top_misstag_anti_candidates same as AK8_top_tag_candidates
   //AK8_W_misstag_anti_candidates same as AK8_W_tag_candidates
   //AK4_bottom_misstag_anti_candidates same as AK4_bottom_tag_candidates
   
   
/*   
   vars.InitVar("N_AK8_top_tag_anti_candidates","I");
   vars.InitVars("AK8_top_tag_anti_candidates_pt","N_AK8_top_tag_anti_candidates");
   vars.InitVars("AK8_top_tag_anti_candidates_eta","N_AK8_top_tag_anti_candidates");
   vars.InitVar("N_AK8_W_tag_anti_candidates","I");
   vars.InitVars("AK8_W_tag_anti_candidates_pt","N_AK8_W_tag_anti_candidates");
   vars.InitVars("AK8_W_tag_anti_candidates_eta","N_AK8_W_tag_anti_candidates");
   vars.InitVar("N_AK4_bottom_tag_anti_candidates","I");
   vars.InitVars("AK4_bottom_tag_anti_candidates_pt","N_AK4_bottom_tag_anti_candidates");
   vars.InitVars("AK4_bottom_tag_anti_candidates_eta","N_AK4_bottom_tag_anti_candidates");
   
   vars.InitVar("N_AK8_top_misstag_anti_candidates","I");
   vars.InitVars("AK8_top_misstagged_anti_candidates_pt","N_AK8_top_misstag_anti_candidates");
   vars.InitVars("AK8_top_misstagged_anti_candidates_eta","N_AK8_top_misstag_anti_candidates");
   vars.InitVar("N_AK8_W_misstag_anti_candidates","I");
   vars.InitVars("AK8_W_misstagged_anti_candidates_pt","N_AK8_W_misstag_anti_candidates");
   vars.InitVars("AK8_W_misstagged_anti_candidates_eta","N_AK8_W_misstag_anti_candidates");
   vars.InitVar("N_AK4_bottom_misstag_anti_candidates","I");
   vars.InitVars("AK4_bottom_misstagged_anti_candidates_pt","N_AK4_bottom_misstag_anti_candidates");
   vars.InitVars("AK4_bottom_misstagged_anti_candidates_eta","N_AK4_bottom_misstag_anti_candidates");
*/   

   
  
   

   
void ZPrimeToTPrimeAllHadProcessor::InitABCDVars(VariableContainer& vars){

///ABCD BACKGROUND ESTIMATION
   vars.InitVar("N_Zprime_ABCD","I");
   vars.InitVars("Zprimes_ABCD_M",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Zprimes_ABCD_Pt",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Tprimes_ABCD_M",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Tprimes_ABCD_Pt",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Bottoms_ABCD_Pt",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Bottoms_ABCD_Eta",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Bottoms_ABCD_Phi",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Bottoms_ABCD_CSV",-9.0,"N_Zprime_ABCD");
   
   vars.InitVars("Bottoms_ABCD_WeightCSVnominal",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Bottoms_ABCD_WeightCSVLFup",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Bottoms_ABCD_WeightCSVLFdown",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Bottoms_ABCD_WeightCSVHFup",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Bottoms_ABCD_WeightCSVHFdown",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Bottoms_ABCD_WeightCSVHFStats1up",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Bottoms_ABCD_WeightCSVHFStats1down",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Bottoms_ABCD_WeightCSVLFStats1up",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Bottoms_ABCD_WeightCSVLFStats1down",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Bottoms_ABCD_WeightCSVHFStats2up",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Bottoms_ABCD_WeightCSVHFStats2down",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Bottoms_ABCD_WeightCSVLFStats2up",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Bottoms_ABCD_WeightCSVLFStats2down",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Bottoms_ABCD_WeightCSVCErr1up",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Bottoms_ABCD_WeightCSVCErr1down",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Bottoms_ABCD_WeightCSVCErr2up",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Bottoms_ABCD_WeightCSVCErr2down",-9.0,"N_Zprime_ABCD");

   vars.InitVars("Ws_ABCD_Pt",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Ws_ABCD_Eta",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Ws_ABCD_Phi",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Ws_ABCD_MSD",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Ws_ABCD_t21",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Tops_ABCD_Pt",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Tops_ABCD_Eta",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Tops_ABCD_Phi",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Tops_ABCD_MSD",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Tops_ABCD_t32",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Tops_ABCD_maxsubjetCSVv2",-9.0,"N_Zprime_ABCD");

   vars.InitVars("Topsubjets_ABCD_WeightCSVnominal",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Topsubjets_ABCD_WeightCSVLFup",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Topsubjets_ABCD_WeightCSVLFdown",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Topsubjets_ABCD_WeightCSVHFup",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Topsubjets_ABCD_WeightCSVHFdown",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Topsubjets_ABCD_WeightCSVHFStats1up",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Topsubjets_ABCD_WeightCSVHFStats1down",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Topsubjets_ABCD_WeightCSVLFStats1up",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Topsubjets_ABCD_WeightCSVLFStats1down",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Topsubjets_ABCD_WeightCSVHFStats2up",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Topsubjets_ABCD_WeightCSVHFStats2down",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Topsubjets_ABCD_WeightCSVLFStats2up",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Topsubjets_ABCD_WeightCSVLFStats2down",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Topsubjets_ABCD_WeightCSVCErr1up",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Topsubjets_ABCD_WeightCSVCErr1down",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Topsubjets_ABCD_WeightCSVCErr2up",-9.0,"N_Zprime_ABCD");
   vars.InitVars("Topsubjets_ABCD_WeightCSVCErr2down",-9.0,"N_Zprime_ABCD");   
   
   
   
   
   
   vars.InitVar("N_Zprimes_ABCDmasscorrnotopbtag","I");
   vars.InitVars("Zprimes_ABCD_masscorrnotopbtag_M",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Zprimes_ABCD_masscorrnotopbtag_Pt",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Tprimes_ABCD_masscorrnotopbtag_M",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Tprimes_ABCD_masscorrnotopbtag_Pt",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrnotopbtag_Pt",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrnotopbtag_Eta",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrnotopbtag_Phi",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrnotopbtag_CSV",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   
   vars.InitVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVnominal",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVLFup",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVLFdown",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVHFup",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVHFdown",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVHFStats1up",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVHFStats1down",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVLFStats1up",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVLFStats1down",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVHFStats2up",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVHFStats2down",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVLFStats2up",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVLFStats2down",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVCErr1up",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVCErr1down",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVCErr2up",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVCErr2down",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");   
   
   vars.InitVars("Ws_ABCD_masscorrnotopbtag_Pt",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Ws_ABCD_masscorrnotopbtag_Eta",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Ws_ABCD_masscorrnotopbtag_Phi",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Ws_ABCD_masscorrnotopbtag_MSD",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Ws_ABCD_masscorrnotopbtag_t21",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Tops_ABCD_masscorrnotopbtag_Pt",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Tops_ABCD_masscorrnotopbtag_Eta",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Tops_ABCD_masscorrnotopbtag_Phi",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Tops_ABCD_masscorrnotopbtag_MSD",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Tops_ABCD_masscorrnotopbtag_t32",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Tops_ABCD_masscorrnotopbtag_maxsubjetCSVv2",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
 
   vars.InitVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVnominal",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVLFup",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVLFdown",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVHFup",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVHFdown",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVHFStats1up",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVHFStats1down",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVLFStats1up",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVLFStats1down",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVHFStats2up",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVHFStats2down",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVLFStats2up",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVLFStats2down",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVCErr1up",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVCErr1down",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVCErr2up",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVCErr2down",-9.0,"N_Zprimes_ABCDmasscorrnotopbtag");      
   
   
   
   vars.InitVar("N_Zprimes_ABCDmasscorrwithtopbtag","I");
   vars.InitVars("Zprimes_ABCD_masscorrwithtopbtag_M",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Zprimes_ABCD_masscorrwithtopbtag_Pt",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Tprimes_ABCD_masscorrwithtopbtag_M",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Tprimes_ABCD_masscorrwithtopbtag_Pt",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrwithtopbtag_Pt",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrwithtopbtag_Eta",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrwithtopbtag_Phi",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrwithtopbtag_CSV",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   
   vars.InitVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVnominal",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVLFup",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVLFdown",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVHFup",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVHFdown",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVHFStats1up",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVHFStats1down",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVLFStats1up",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVLFStats1down",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVHFStats2up",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVHFStats2down",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVLFStats2up",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVLFStats2down",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVCErr1up",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVCErr1down",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVCErr2up",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVCErr2down",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");      
   
   vars.InitVars("Ws_ABCD_masscorrwithtopbtag_Pt",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Ws_ABCD_masscorrwithtopbtag_Eta",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Ws_ABCD_masscorrwithtopbtag_Phi",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Ws_ABCD_masscorrwithtopbtag_MSD",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Ws_ABCD_masscorrwithtopbtag_t21",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Tops_ABCD_masscorrwithtopbtag_Pt",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Tops_ABCD_masscorrwithtopbtag_Eta",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Tops_ABCD_masscorrwithtopbtag_Phi",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Tops_ABCD_masscorrwithtopbtag_MSD",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Tops_ABCD_masscorrwithtopbtag_t32",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Tops_ABCD_masscorrwithtopbtag_maxsubjetCSVv2",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");   
  
   vars.InitVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVnominal",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVLFup",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVLFdown",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVHFup",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVHFdown",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVHFStats1up",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVHFStats1down",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVLFStats1up",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVLFStats1down",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVHFStats2up",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVHFStats2down",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVLFStats2up",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVLFStats2down",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVCErr1up",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVCErr1down",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVCErr2up",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVCErr2down",-9.0,"N_Zprimes_ABCDmasscorrwithtopbtag");      
   
   
/*   vars.InitVar("N_Zprime_ABCD_tAK15WAK15bAK4","I");
   vars.InitVars("Zprimes_ABCD_tAK15WAK15bAK4_M",-9.0,"N_Zprime_ABCD_tAK15WAK15bAK4");
   vars.InitVars("Zprimes_ABCD_tAK15WAK15bAK4_Pt",-9.0,"N_Zprime_ABCD_tAK15WAK15bAK4");
   vars.InitVars("Tprimes_ABCD_tAK15WAK15bAK4_M",-9.0,"N_Zprime_ABCD_tAK15WAK15bAK4");
   vars.InitVars("Tprimes_ABCD_tAK15WAK15bAK4_Pt",-9.0,"N_Zprime_ABCD_tAK15WAK15bAK4");
   vars.InitVars("Bottoms_ABCD_tAK15WAK15bAK4_Pt",-9.0,"N_Zprime_ABCD_tAK15WAK15bAK4");
   vars.InitVars("Bottoms_ABCD_tAK15WAK15bAK4_Eta",-9.0,"N_Zprime_ABCD_tAK15WAK15bAK4");
   vars.InitVars("Bottoms_ABCD_tAK15WAK15bAK4_Phi",-9.0,"N_Zprime_ABCD_tAK15WAK15bAK4");
   vars.InitVars("Bottoms_ABCD_tAK15WAK15bAK4_CSV",-9.0,"N_Zprime_ABCD_tAK15WAK15bAK4");
   vars.InitVars("Ws_ABCD_tAK15WAK15bAK4_Pt",-9.0,"N_Zprime_ABCD_tAK15WAK15bAK4");
   vars.InitVars("Ws_ABCD_tAK15WAK15bAK4_Eta",-9.0,"N_Zprime_ABCD_tAK15WAK15bAK4");
   vars.InitVars("Ws_ABCD_tAK15WAK15bAK4_Phi",-9.0,"N_Zprime_ABCD_tAK15WAK15bAK4");
   vars.InitVars("Ws_ABCD_tAK15WAK15bAK4_MSD",-9.0,"N_Zprime_ABCD_tAK15WAK15bAK4");
   vars.InitVars("Ws_ABCD_tAK15WAK15bAK4_t21",-9.0,"N_Zprime_ABCD_tAK15WAK15bAK4");
   vars.InitVars("Tops_ABCD_tAK15WAK15bAK4_Pt",-9.0,"N_Zprime_ABCD_tAK15WAK15bAK4");
   vars.InitVars("Tops_ABCD_tAK15WAK15bAK4_Eta",-9.0,"N_Zprime_ABCD_tAK15WAK15bAK4");
   vars.InitVars("Tops_ABCD_tAK15WAK15bAK4_Phi",-9.0,"N_Zprime_ABCD_tAK15WAK15bAK4");
   vars.InitVars("Tops_ABCD_tAK15WAK15bAK4_MSD",-9.0,"N_Zprime_ABCD_tAK15WAK15bAK4");
   vars.InitVars("Tops_ABCD_tAK15WAK15bAK4_t32",-9.0,"N_Zprime_ABCD_tAK15WAK15bAK4");
   vars.InitVars("Tops_ABCD_tAK15WAK15bAK4_maxsubjetCSVv2",-9.0,"N_Zprime_ABCD_tAK15WAK15bAK4");   
 */  
   
   vars.InitVar("N_Zprime_ABCD_tAK15WAK8bAK4","I");
   vars.InitVars("Zprimes_ABCD_tAK15WAK8bAK4_M",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Zprimes_ABCD_tAK15WAK8bAK4_Pt",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Tprimes_ABCD_tAK15WAK8bAK4_M",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Tprimes_ABCD_tAK15WAK8bAK4_Pt",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK15WAK8bAK4_Pt",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK15WAK8bAK4_Eta",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK15WAK8bAK4_Phi",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK15WAK8bAK4_CSV",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   
   vars.InitVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVnominal",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVLFup",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVLFdown",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVHFup",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVHFdown",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVHFStats1up",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVHFStats1down",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVLFStats1up",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVLFStats1down",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVHFStats2up",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVHFStats2down",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVLFStats2up",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVLFStats2down",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVCErr1up",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVCErr1down",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVCErr2up",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVCErr2down",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");   
   
   vars.InitVars("Ws_ABCD_tAK15WAK8bAK4_Pt",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Ws_ABCD_tAK15WAK8bAK4_Eta",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Ws_ABCD_tAK15WAK8bAK4_Phi",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Ws_ABCD_tAK15WAK8bAK4_MSD",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Ws_ABCD_tAK15WAK8bAK4_t21",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Tops_ABCD_tAK15WAK8bAK4_Pt",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Tops_ABCD_tAK15WAK8bAK4_Eta",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Tops_ABCD_tAK15WAK8bAK4_Phi",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Tops_ABCD_tAK15WAK8bAK4_MSD",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Tops_ABCD_tAK15WAK8bAK4_t32",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Tops_ABCD_tAK15WAK8bAK4_maxsubjetCSVv2",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");   
   
   vars.InitVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVnominal",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVLFup",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVLFdown",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVHFup",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVHFdown",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVHFStats1up",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVHFStats1down",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVLFStats1up",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVLFStats1down",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVHFStats2up",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVHFStats2down",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVLFStats2up",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVLFStats2down",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVCErr1up",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVCErr1down",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVCErr2up",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVCErr2down",-9.0,"N_Zprime_ABCD_tAK15WAK8bAK4");   
      
  
   
//    vars.InitVar("N_Zprime_ABCD_tAK12WAK12bAK4","I");
//    vars.InitVars("Zprimes_ABCD_tAK12WAK12bAK4_M",-9.0,"N_Zprime_ABCD_tAK12WAK12bAK4");
//    vars.InitVars("Zprimes_ABCD_tAK12WAK12bAK4_Pt",-9.0,"N_Zprime_ABCD_tAK12WAK12bAK4");
//    vars.InitVars("Tprimes_ABCD_tAK12WAK12bAK4_M",-9.0,"N_Zprime_ABCD_tAK12WAK12bAK4");
//    vars.InitVars("Tprimes_ABCD_tAK12WAK12bAK4_Pt",-9.0,"N_Zprime_ABCD_tAK12WAK12bAK4");
//    vars.InitVars("Bottoms_ABCD_tAK12WAK12bAK4_Pt",-9.0,"N_Zprime_ABCD_tAK12WAK12bAK4");
//    vars.InitVars("Bottoms_ABCD_tAK12WAK12bAK4_Eta",-9.0,"N_Zprime_ABCD_tAK12WAK12bAK4");
//    vars.InitVars("Bottoms_ABCD_tAK12WAK12bAK4_Phi",-9.0,"N_Zprime_ABCD_tAK12WAK12bAK4");
//    vars.InitVars("Bottoms_ABCD_tAK12WAK12bAK4_CSV",-9.0,"N_Zprime_ABCD_tAK12WAK12bAK4");
//    vars.InitVars("Ws_ABCD_tAK12WAK12bAK4_Pt",-9.0,"N_Zprime_ABCD_tAK12WAK12bAK4");
//    vars.InitVars("Ws_ABCD_tAK12WAK12bAK4_Eta",-9.0,"N_Zprime_ABCD_tAK12WAK12bAK4");
//    vars.InitVars("Ws_ABCD_tAK12WAK12bAK4_Phi",-9.0,"N_Zprime_ABCD_tAK12WAK12bAK4");
//    vars.InitVars("Ws_ABCD_tAK12WAK12bAK4_MSD",-9.0,"N_Zprime_ABCD_tAK12WAK12bAK4");
//    vars.InitVars("Ws_ABCD_tAK12WAK12bAK4_t21",-9.0,"N_Zprime_ABCD_tAK12WAK12bAK4");
//    vars.InitVars("Tops_ABCD_tAK12WAK12bAK4_Pt",-9.0,"N_Zprime_ABCD_tAK12WAK12bAK4");
//    vars.InitVars("Tops_ABCD_tAK12WAK12bAK4_Eta",-9.0,"N_Zprime_ABCD_tAK12WAK12bAK4");
//    vars.InitVars("Tops_ABCD_tAK12WAK12bAK4_Phi",-9.0,"N_Zprime_ABCD_tAK12WAK12bAK4");
//    vars.InitVars("Tops_ABCD_tAK12WAK12bAK4_MSD",-9.0,"N_Zprime_ABCD_tAK12WAK12bAK4");
//    vars.InitVars("Tops_ABCD_tAK12WAK12bAK4_t32",-9.0,"N_Zprime_ABCD_tAK12WAK12bAK4");
//    vars.InitVars("Tops_ABCD_tAK12WAK12bAK4_maxsubjetCSVv2",-9.0,"N_Zprime_ABCD_tAK12WAK12bAK4");   
//    
   
   vars.InitVar("N_Zprime_ABCD_tAK12WAK8bAK4","I");
   vars.InitVars("Zprimes_ABCD_tAK12WAK8bAK4_M",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Zprimes_ABCD_tAK12WAK8bAK4_Pt",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Tprimes_ABCD_tAK12WAK8bAK4_M",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Tprimes_ABCD_tAK12WAK8bAK4_Pt",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK12WAK8bAK4_Pt",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK12WAK8bAK4_Eta",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK12WAK8bAK4_Phi",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK12WAK8bAK4_CSV",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   
   vars.InitVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVnominal",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVLFup",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVLFdown",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVHFup",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVHFdown",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVHFStats1up",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVHFStats1down",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVLFStats1up",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVLFStats1down",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVHFStats2up",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVHFStats2down",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVLFStats2up",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVLFStats2down",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVCErr1up",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVCErr1down",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVCErr2up",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVCErr2down",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");   

   vars.InitVars("Ws_ABCD_tAK12WAK8bAK4_Pt",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Ws_ABCD_tAK12WAK8bAK4_Eta",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Ws_ABCD_tAK12WAK8bAK4_Phi",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Ws_ABCD_tAK12WAK8bAK4_MSD",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Ws_ABCD_tAK12WAK8bAK4_t21",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Tops_ABCD_tAK12WAK8bAK4_Pt",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Tops_ABCD_tAK12WAK8bAK4_Eta",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Tops_ABCD_tAK12WAK8bAK4_Phi",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Tops_ABCD_tAK12WAK8bAK4_MSD",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Tops_ABCD_tAK12WAK8bAK4_t32",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Tops_ABCD_tAK12WAK8bAK4_maxsubjetCSVv2",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");   
   
   vars.InitVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVnominal",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVLFup",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVLFdown",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVHFup",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVHFdown",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVHFStats1up",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVHFStats1down",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVLFStats1up",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVLFStats1down",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVHFStats2up",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVHFStats2down",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVLFStats2up",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVLFStats2down",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVCErr1up",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVCErr1down",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVCErr2up",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");
   vars.InitVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVCErr2down",-9.0,"N_Zprime_ABCD_tAK12WAK8bAK4");   

   
///Datadriven Background estimation   
   vars.InitVar("BG_Zprime_M","F");
   vars.InitVar("BG_Zprime_withtop_btag_M","F");

   vars.InitVar("BG_Tprime_M","F");
   vars.InitVar("BG_Tprime_pt","F");

   vars.InitVar("BG_Top_candidates_pt","F");
   vars.InitVar("BG_Top_candidates_withbtag_pt","F");  
   vars.InitVar("BG_W_candidates_pt","F");
   vars.InitVar("BG_Bottom_candidates_pt","F");
   vars.InitVar("BG_Bottom_anti_candidates_pt","F");
   
}

bool ZPrimeToTPrimeAllHadProcessor::Toptag(pat::Jet top,std::string workingpoint){
    float M_SD_up=220;
    float M_SD_low=105;
    float tau32=0.86;
    
    if(workingpoint=="T"){
        M_SD_up=220;
        M_SD_low=105;
        tau32=0.5;
    }
    if(workingpoint=="M"){
        M_SD_up=220;
        M_SD_low=105;
        tau32=0.67;
    }
    if(workingpoint=="L"){
        M_SD_up=220;
        M_SD_low=105;
        tau32=0.81;
    }
    
    if(top.userFloat("NjettinessAK8CHS:tau3")>0.0 && top.userFloat("NjettinessAK8CHS:tau2")>0.0 && top.userFloat("NjettinessAK8CHS:tau1")>0.0 && (top.userFloat("NjettinessAK8CHS:tau3")/top.userFloat("NjettinessAK8CHS:tau2"))<tau32 && M_SD_low<top.userFloat("ak8PFJetsCHSSoftDropMass") && top.userFloat("ak8PFJetsCHSSoftDropMass")<M_SD_up){
        return true;
    }else{
        return false;
    }
}



bool ZPrimeToTPrimeAllHadProcessor::Top_subbtag(pat::Jet top,std::string subjet_workingpoint){
    float CSVv2=0.8;
    if(subjet_workingpoint=="T"){
        CSVv2=0.935;
    }
    if(subjet_workingpoint=="M"){
        CSVv2=0.8;
    }
    if(subjet_workingpoint=="L"){
        CSVv2=0.46;
    }
    
    double max_subjet_csv_v2=-10;
    auto const & names = top.subjets("SoftDrop");
    for( auto const & itsubJet : names ){
        if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>max_subjet_csv_v2){
            max_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
        }
    };   
    if (max_subjet_csv_v2>CSVv2){    
        return true;
    }else{
        return false;
    }
}
    





bool ZPrimeToTPrimeAllHadProcessor::Wtag(pat::Jet W,std::string workingpoint){
    float M_SD_up=100;
    float M_SD_low=70;
    float tau21=0.6;
    
    if(workingpoint=="T"){
        M_SD_up=100;
        M_SD_low=70;
        tau21=0.5;
    }
    if(workingpoint=="M"){
        M_SD_up=100;
        M_SD_low=70;
        tau21=0.6;
    }
    if(workingpoint=="L"){
        M_SD_up=100;
        M_SD_low=70;
        tau21=0.5;
    }
    
    if(W.userFloat("NjettinessAK8CHS:tau3")>0.0 && W.userFloat("NjettinessAK8CHS:tau2")>0.0 && W.userFloat("NjettinessAK8CHS:tau1")>0.0 && (W.userFloat("NjettinessAK8CHS:tau2")/W.userFloat("NjettinessAK8CHS:tau1"))<tau21 && M_SD_low<W.userFloat("ak8PFJetsCHSSoftDropMass") && W.userFloat("ak8PFJetsCHSSoftDropMass")<M_SD_up){
        return true;
    }
    else{
        return false;
    }
}



bool ZPrimeToTPrimeAllHadProcessor::Bottomtag(pat::Jet bottom,std::string workingpoint){
    float CSVv2=0.46;
    if(workingpoint=="T"){
        CSVv2=0.935;
    }
    if(workingpoint=="M"){
        CSVv2=0.8;
    }
    if(workingpoint=="L"){
        CSVv2=0.46;
    }
    if(MiniAODHelper::GetJetCSV(bottom,"pfCombinedInclusiveSecondaryVertexV2BJetTags")>CSVv2){
        return true;
    }
    else{
        return false;
    }
}


std::vector<pat::Jet> ZPrimeToTPrimeAllHadProcessor::SelectSeparatedBottoms(std::vector<pat::Jet>& tops, std::vector<pat::Jet>& Ws, std::vector<pat::Jet>& bottoms){
    std::vector<pat::Jet> separated_bottoms;
    for(std::vector<pat::Jet>::const_iterator itbJet = bottoms.begin() ; itbJet != bottoms.end(); ++itbJet){
        bool check_dR_top_bottom=true;
        bool check_dR_W_bottom=true;
            for(std::vector<pat::Jet>::const_iterator ittopJet = tops.begin() ; ittopJet != tops.end(); ++ittopJet){
                if (BoostedUtils::DeltaR(itbJet->p4(),ittopJet->p4())<1.2){
                    check_dR_top_bottom=false;
                }
            }
            for(std::vector<pat::Jet>::const_iterator itWJet = Ws.begin() ; itWJet != Ws.end(); ++itWJet){
                if (BoostedUtils::DeltaR(itbJet->p4(),itWJet->p4())<1.2){
                    check_dR_W_bottom=false;
                }                    
            }
        
        if (check_dR_top_bottom && check_dR_W_bottom){
            separated_bottoms.push_back(*itbJet);
        }
    }
    return separated_bottoms;
}

std::vector<pat::Jet> ZPrimeToTPrimeAllHadProcessor::SelectfromTopSeparatedWs( std::vector<pat::Jet>& tops, std::vector<pat::Jet>& Ws){
    std::vector<pat::Jet> separated_Ws;
    for(std::vector<pat::Jet>::const_iterator ittopJet = tops.begin() ; ittopJet != tops.end(); ++ittopJet){
        for(std::vector<pat::Jet>::const_iterator itWJet = Ws.begin() ; itWJet != Ws.end(); ++itWJet){
            if (BoostedUtils::DeltaR(ittopJet->p4(),itWJet->p4())>0.8){
                separated_Ws.push_back(*itWJet);
            }
        }
    }
    return separated_Ws;
}

std::vector<pat::Jet> ZPrimeToTPrimeAllHadProcessor::SelectfromWSeparatedTops(std::vector<pat::Jet>& tops,std::vector<pat::Jet>& Ws){
    std::vector<pat::Jet> separated_Tops;
    for(std::vector<pat::Jet>::const_iterator ittopJet = tops.begin() ; ittopJet != tops.end(); ++ittopJet){
        for(std::vector<pat::Jet>::const_iterator itWJet = Ws.begin() ; itWJet != Ws.end(); ++itWJet){
            if (BoostedUtils::DeltaR(ittopJet->p4(),itWJet->p4())>0.8){
                separated_Tops.push_back(*ittopJet);
            }
        }
    }
    return separated_Tops;
}

math::XYZTLorentzVector ZPrimeToTPrimeAllHadProcessor::TPrimeReconstructionWtb( std::vector<pat::Jet>& Ws,  std::vector<pat::Jet>& bottoms){
    math::XYZTLorentzVector TPrime;
    TPrime=bottoms[0].p4()+Ws[0].p4();
    return TPrime;
}

math::XYZTLorentzVector ZPrimeToTPrimeAllHadProcessor::ZPrimeReconstructionWtb( std::vector<pat::Jet>& tops,  math::XYZTLorentzVector& TPrime){
    math::XYZTLorentzVector ZPrime;
    ZPrime=TPrime+tops[0].p4();
    return ZPrime;
}

void ZPrimeToTPrimeAllHadProcessor::ZPrimeReconstructionWtbComplete(VariableContainer& vars,  std::vector<pat::Jet>& tops, std::vector<pat::Jet>& Ws,  std::vector<pat::Jet>& bottoms, std::vector<pat::Jet>& bottoms_anti, bool toptag, bool toptag_withbtag,  bool Wtag, bool toptag_anti, bool toptag_withbtag_anti,  bool Wtag_anti, std::string str_AK8_selected_first){
//     std::cout<<"ladida1"<<endl;
    math::XYZTLorentzVector Zprime;
    math::XYZTLorentzVector Tprime;
    std::vector<pat::Jet> selected_Top;
    std::vector<pat::Jet> selected_W;
    if(str_AK8_selected_first=="Topfirst"){
        //std::cout<<"ladida11"<<endl;
        selected_Top.push_back(tops[0]);
        std::vector<pat::Jet> separated_Ws;
        separated_Ws=SelectfromTopSeparatedWs(selected_Top, Ws);
        //std::cout<<"ladida12"<<separated_Ws.size()<<endl;
        if(separated_Ws.size()>0){
            selected_W.push_back(separated_Ws[0]); 
        }
        //std::cout<<"ladida13"<<endl;
    }
    if(str_AK8_selected_first=="Wfirst"){
        selected_W.push_back(Ws[0]);
        std::vector<pat::Jet> separated_Tops;
        separated_Tops=SelectfromWSeparatedTops(tops, selected_W);
        if(separated_Tops.size()>0){
            selected_Top.push_back(separated_Tops[0]);
        }
    }
    if(selected_W.size()>0 && selected_Top.size()>0){
        
        std::vector<pat::Jet> separated_bottoms;
        std::vector<pat::Jet> separated_bottoms_anti;
        separated_bottoms=SelectSeparatedBottoms(selected_Top, selected_W, bottoms);
        separated_bottoms_anti=SelectSeparatedBottoms(selected_Top, selected_W, bottoms_anti);
        if (separated_bottoms_anti.size()>0 && separated_bottoms.size()==0){
            Tprime=TPrimeReconstructionWtb(selected_W,separated_bottoms_anti);
            if(Tprime.mass()>500){
                Zprime=ZPrimeReconstructionWtb(selected_Top,Tprime);
                FillSignalSidebandVars(vars, tops,Ws,separated_bottoms_anti,Tprime,Zprime,toptag,toptag_withbtag,Wtag,false,toptag_anti,toptag_withbtag_anti,Wtag_anti,str_AK8_selected_first);
            }
        }
        //std::cout<<"ladida4"<<endl;
        if(separated_bottoms.size()>0){
            Tprime=TPrimeReconstructionWtb(selected_W,separated_bottoms);
            if(Tprime.mass()>500){
                Zprime=ZPrimeReconstructionWtb(selected_Top,Tprime);
                FillSignalSidebandVars(vars,tops,Ws,separated_bottoms,Tprime,Zprime,toptag,toptag_withbtag,Wtag,true,toptag_anti,toptag_withbtag_anti,Wtag_anti,str_AK8_selected_first);
            }
        }
    }

}


void ZPrimeToTPrimeAllHadProcessor::FillSignalSidebandVars(VariableContainer& vars, std::vector<pat::Jet>& tops, std::vector<pat::Jet>& Ws,  std::vector<pat::Jet>& bottoms,  math::XYZTLorentzVector Tprime,  math::XYZTLorentzVector Zprime,  bool toptag, bool toptag_withbtag,  bool Wtag, bool bottomtag, bool toptag_anti, bool toptag_withbtag_anti,  bool Wtag_anti, std::string str_AK8_selected_first){
    std::string str_region="Sideband_";
    std::string str_bottom="";
    std::string str_top="";
    std::string str_W="";
//     std::cout<<"top:"<<toptag<<" twbt:"<<toptag_withbtag<<" W:"<<Wtag<<" Bottom:"<<bottomtag<<"  toptaganti:"<< toptag_anti<<"  toptagantiwbt:"<<toptag_withbtag_anti<<"  Wtaganti:"<<Wtag_anti<<endl;
    
    if((toptag || toptag_withbtag)&& Wtag && bottomtag){str_region="Signal_";};
    if(Wtag_anti && !Wtag){str_W="W_anti_";};
    if(!bottomtag){str_bottom="bottom_anti_";};
    if(toptag_anti && !toptag){str_top="top_anti_";};
    if(toptag_withbtag){str_top="withtopbtag_";};
    if(toptag_withbtag_anti && !toptag_withbtag){str_top="top_withbtag_anti_";};

    
    
    FillZprimeVars(vars,tops,Ws,bottoms,Tprime,Zprime,str_region+str_top+str_W+str_bottom+str_AK8_selected_first);
    
    str_top+="MCtopmass_";
    for(std::vector<pat::Jet>::iterator itJet = tops.begin() ; itJet != tops.end(); ++itJet){
            itJet->setMass(foo.GetRndmSDM(histo_TTM_SDM));
    };

    FillZprimeVars(vars,tops,Ws,bottoms,Tprime,Zprime,str_region+str_top+str_W+str_bottom+str_AK8_selected_first);
    /*if(toptag_withbtag){
        str_top="withtopbtag_";
        FillZprimeVars(vars,tops,Ws,bottoms,Tprime,Zprime,str_region+str_top+str_W+str_bottom+str_AK8_selected_first);
    }
    if(toptag_withbtag_anti && !toptag_withbtag){
        str_top="top_withbtag_anti_";
        FillZprimeVars(vars,tops,Ws,bottoms,Tprime,Zprime,str_region+str_top+str_W+str_bottom+str_AK8_selected_first);
    }*/
}    
    
void ZPrimeToTPrimeAllHadProcessor::FillZprimeVars(VariableContainer& vars, std::vector<pat::Jet>& tops, std::vector<pat::Jet>& Ws,  std::vector<pat::Jet>& bottoms,  math::XYZTLorentzVector Tprime,  math::XYZTLorentzVector Zprime, std::string string){
    vars.FillVar("N_"+string+"_Tops",tops.size());
    for(std::vector<pat::Jet>::const_iterator itJet = tops.begin() ; itJet != tops.end(); ++itJet){
        int iJet = itJet - tops.begin();
        vars.FillVars(string+"_Tops_Pt",iJet,itJet->pt());
        vars.FillVars(string+"_Tops_Eta",iJet,itJet->eta());
        vars.FillVars(string+"_Tops_MSD",iJet,itJet->userFloat("ak8PFJetsCHSSoftDropMass"));
        vars.FillVars(string+"_Tops_t32",iJet,itJet->userFloat("NjettinessAK8CHS:tau3")/itJet->userFloat("NjettinessAK8CHS:tau2"));
        vars.FillVars(string+"_Tops_t21",iJet,itJet->userFloat("NjettinessAK8CHS:tau2")/itJet->userFloat("NjettinessAK8CHS:tau1"));
        
        double max_subjet_csv_v2=-10;
        auto const & names = itJet->subjets("SoftDrop");
        for( auto const & itsubJet : names ){
            if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>max_subjet_csv_v2){
            max_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
            }
        }
        vars.FillVars(string+"_Tops_subjetCSVv2",iJet,max_subjet_csv_v2);
        
    }
    vars.FillVar("N_"+string+"_Ws",Ws.size());
    for(std::vector<pat::Jet>::const_iterator itJet = Ws.begin() ; itJet != Ws.end(); ++itJet){
        int iJet = itJet - Ws.begin();
        vars.FillVars(string+"_Ws_Pt",iJet,itJet->pt());
        vars.FillVars(string+"_Ws_Eta",iJet,itJet->eta());
        vars.FillVars(string+"_Ws_MSD",iJet,itJet->userFloat("ak8PFJetsCHSSoftDropMass"));
        vars.FillVars(string+"_Ws_t32",iJet,itJet->userFloat("NjettinessAK8CHS:tau3")/itJet->userFloat("NjettinessAK8CHS:tau2"));
        vars.FillVars(string+"_Ws_t21",iJet,itJet->userFloat("NjettinessAK8CHS:tau2")/itJet->userFloat("NjettinessAK8CHS:tau1"));
    }
    vars.FillVar("N_"+string+"_Bottoms",bottoms.size());
    for(std::vector<pat::Jet>::const_iterator itJet = bottoms.begin() ; itJet != bottoms.end(); ++itJet){
        int iJet = itJet - bottoms.begin();
        vars.FillVars(string+"_Bottoms_Pt",iJet,itJet->pt());
        vars.FillVars(string+"_Bottoms_Eta",iJet,itJet->eta());
        vars.FillVars(string+"_Bottoms_CSVv2",iJet,MiniAODHelper::GetJetCSV(*itJet,"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
    }
    
    vars.FillVar(string+"_Tprime_M",Tprime.mass());
    vars.FillVar(string+"_Tprime_Pt",Tprime.pt());
    Zprime=ZPrimeReconstructionWtb(tops, Tprime);
    vars.FillVar(string+"_Zprime_M",Zprime.mass());
    vars.FillVar(string+"_Zprime_Pt",Zprime.pt());
    
//     std::cout<<"HALLLLOOOOOOO  "<<string<<endl;
}

void ZPrimeToTPrimeAllHadProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << std::endl; // complain if not initialized but keep running
//     std::cout<<"here"<<endl;
  
    vars.FillVar("N_Gen_ZPrimes", input.zprimetotprimeallhad.GetZPrimes().size());
    vars.FillVar("N_Gen_Tops", input.zprimetotprimeallhad.GetTops_fromZprimes().size());
    vars.FillVar("N_Gen_Topbars", input.zprimetotprimeallhad.GetTopbars_fromZprimes().size());
    vars.FillVar("N_Gen_TopsandTopbars", input.zprimetotprimeallhad.GetTopsandTopbars_fromZprimes().size());

    vars.FillVar("N_Gen_TPrimes", input.zprimetotprimeallhad.GetTPrimes().size());
    vars.FillVar("N_Gen_TPrimebars", input.zprimetotprimeallhad.GetTPrimebars().size());
    vars.FillVar("N_Gen_TPrimesandTPrimebars", input.zprimetotprimeallhad.GetTPrimesandTPrimebars().size());

    vars.FillVar("N_Gen_WplusfromTops", input.zprimetotprimeallhad.GetWplus_fromTops().size());
    vars.FillVar("N_Gen_WminusfromTopbars", input.zprimetotprimeallhad.GetWminus_fromTops().size());
    vars.FillVar("N_Gen_WfromTopsandTopbars", input.zprimetotprimeallhad.GetW_fromTopsandTopbars().size());
    
    vars.FillVar("N_Gen_WplusfromTPrimes", input.zprimetotprimeallhad.GetWplus_fromTPrimes().size());
    vars.FillVar("N_Gen_WminusfromTPrimebars", input.zprimetotprimeallhad.GetWminus_fromTPrimes().size());
    vars.FillVar("N_Gen_WfromTPrimesandTPrimebars", input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars().size());

    vars.FillVar("N_Gen_BottomfromTops", input.zprimetotprimeallhad.GetBottom_fromTops().size());
    vars.FillVar("N_Gen_BottombarfromTopbars", input.zprimetotprimeallhad.GetBottom_fromTopbars().size());
    vars.FillVar("N_Gen_BottomfromTopsandTopbars", input.zprimetotprimeallhad.GetBottom_fromTopsandTopbars().size());

    vars.FillVar("N_Gen_BottomfromTPrimes", input.zprimetotprimeallhad.GetBottom_fromTPrimes().size());
    vars.FillVar("N_Gen_BottombarfromTPrimebars", input.zprimetotprimeallhad.GetBottom_fromTPrimebars().size());
    vars.FillVar("N_Gen_BottomfromTPrimesandTPrimebars", input.zprimetotprimeallhad.GetBottom_fromTPrimesandTPrimebars().size());

    vars.FillVar("N_packedPatJetsAK8PFCHSSoftDrop", input.selectedJetsAK8.size());
    
//    vars.FillVar("N_selectedPatJetsAK8PFCHSSoftDropPacked", input.selectedPatJetsAK8PFCHSSoftDropPacked.size());
//    vars.FillVar("N_packedPatJetsAK8PFCHSSoftDrop", input.selectedJetsAK8.size());

//     std::cout<<"there8"<<endl;
    if(input.zprimetotprimeallhad.GetTops_fromZprimes().size()>0){
        for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetTops_fromZprimes().begin() ; itParticle != input.zprimetotprimeallhad.GetTops_fromZprimes().end(); ++itParticle){
        int iParticle = itParticle - input.zprimetotprimeallhad.GetTops_fromZprimes().begin();
            vars.FillVars( "Gen_Top_Pt",iParticle,itParticle->pt() );
            vars.FillVars( "Gen_Top_Eta",iParticle,itParticle->eta() );
        }
    }
    if(input.zprimetotprimeallhad.GetTopbars_fromZprimes().size()>0){
        for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetTopbars_fromZprimes().begin() ; itParticle != input.zprimetotprimeallhad.GetTopbars_fromZprimes().end(); ++itParticle){
        int iParticle = itParticle - input.zprimetotprimeallhad.GetTopbars_fromZprimes().begin();
            vars.FillVars( "Gen_Topbar_Pt",iParticle,itParticle->pt() );
            vars.FillVars( "Gen_Topbar_Eta",iParticle,itParticle->eta() );
        }
    }
    if(input.zprimetotprimeallhad.GetTopsandTopbars_fromZprimes().size()>0){
        for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetTopsandTopbars_fromZprimes().begin() ; itParticle != input.zprimetotprimeallhad.GetTopsandTopbars_fromZprimes().end(); ++itParticle){
        int iParticle = itParticle - input.zprimetotprimeallhad.GetTopsandTopbars_fromZprimes().begin();
            vars.FillVars( "Gen_TopandTopbar_Pt",iParticle,itParticle->pt() );
            vars.FillVars( "Gen_TopandTopbar_Eta",iParticle,itParticle->eta() );
        }
    }
    if(input.zprimetotprimeallhad.GetTPrimes().size()>0){
    for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetTPrimes().begin() ; itParticle != input.zprimetotprimeallhad.GetTPrimes().end(); ++itParticle){
        int iParticle = itParticle - input.zprimetotprimeallhad.GetTPrimes().begin();
            vars.FillVars( "Gen_TPrime_Pt",iParticle,itParticle->pt() );
            vars.FillVars( "Gen_TPrime_Eta",iParticle,itParticle->eta() );
        }
    }
    if(input.zprimetotprimeallhad.GetTPrimebars().size()>0){
        for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetTPrimebars().begin() ; itParticle != input.zprimetotprimeallhad.GetTPrimebars().end(); ++itParticle){
        int iParticle = itParticle - input.zprimetotprimeallhad.GetTPrimebars().begin();
            vars.FillVars( "Gen_TPrimebar_Pt",iParticle,itParticle->pt() );
            vars.FillVars( "Gen_TPrimebar_Eta",iParticle,itParticle->eta() );
        }
    }
    if(input.zprimetotprimeallhad.GetTPrimesandTPrimebars().size()>0){
        for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetTPrimesandTPrimebars().begin() ; itParticle != input.zprimetotprimeallhad.GetTPrimesandTPrimebars().end(); ++itParticle){
        int iParticle = itParticle - input.zprimetotprimeallhad.GetTPrimesandTPrimebars().begin();
            vars.FillVars( "Gen_TPrimeandTPrimebar_Pt",iParticle,itParticle->pt() );
            vars.FillVars( "Gen_TPrimeandTPrimebar_Eta",iParticle,itParticle->eta() );
            vars.FillVars( "Gen_TPrimeandTPrimebar_M",iParticle,itParticle->mass() );
        }
    }
    if(input.zprimetotprimeallhad.GetZPrimes().size()>0){
        for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetZPrimes().begin() ; itParticle != input.zprimetotprimeallhad.GetZPrimes().end(); ++itParticle){
        int iParticle = itParticle - input.zprimetotprimeallhad.GetZPrimes().begin();
            vars.FillVars( "Gen_ZPrime_Pt",iParticle,itParticle->pt() );
            vars.FillVars( "Gen_ZPrime_Eta",iParticle,itParticle->eta() );
            vars.FillVars( "Gen_ZPrime_M",iParticle,itParticle->mass() );
        }
    }
    if(input.zprimetotprimeallhad.GetWplus_fromTops().size()>0){
        for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetWplus_fromTops().begin() ; itParticle != input.zprimetotprimeallhad.GetWplus_fromTops().end(); ++itParticle){
        int iParticle = itParticle - input.zprimetotprimeallhad.GetWplus_fromTops().begin();
            vars.FillVars( "Gen_WplusfromTop_Pt",iParticle,itParticle->pt() );
            vars.FillVars( "Gen_WplusfromTop_Eta",iParticle,itParticle->eta() );
        }
    }
    if(input.zprimetotprimeallhad.GetWminus_fromTops().size()>0){
        for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetWminus_fromTops().begin() ; itParticle != input.zprimetotprimeallhad.GetWminus_fromTops().end(); ++itParticle){
        int iParticle = itParticle - input.zprimetotprimeallhad.GetWminus_fromTops().begin();
            vars.FillVars( "Gen_WminusfromTopbar_Pt",iParticle,itParticle->pt() );
            vars.FillVars( "Gen_WminusfromTopbar_Eta",iParticle,itParticle->eta() );
        }
    }
    if(input.zprimetotprimeallhad.GetW_fromTopsandTopbars().size()>0){
        for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetW_fromTopsandTopbars().begin() ; itParticle != input.zprimetotprimeallhad.GetW_fromTopsandTopbars().end(); ++itParticle){
        int iParticle = itParticle - input.zprimetotprimeallhad.GetW_fromTopsandTopbars().begin();
            vars.FillVars( "Gen_WfromTopandTopbar_Pt",iParticle,itParticle->pt() );
            vars.FillVars( "Gen_WfromTopandTopbar_Eta",iParticle,itParticle->eta() );
        }
    }
    if(input.zprimetotprimeallhad.GetWplus_fromTPrimes().size()>0){
        for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetWplus_fromTPrimes().begin() ; itParticle != input.zprimetotprimeallhad.GetWplus_fromTPrimes().end(); ++itParticle){
        int iParticle = itParticle - input.zprimetotprimeallhad.GetWplus_fromTPrimes().begin();
            vars.FillVars( "Gen_WplusfromTPrime_Pt",iParticle,itParticle->pt() );
            vars.FillVars( "Gen_WplusfromTPrime_Eta",iParticle,itParticle->eta() );
        }
    }
    if(input.zprimetotprimeallhad.GetWminus_fromTPrimes().size()>0){
        for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetWminus_fromTPrimes().begin() ; itParticle != input.zprimetotprimeallhad.GetWminus_fromTPrimes().end(); ++itParticle){
        int iParticle = itParticle - input.zprimetotprimeallhad.GetWminus_fromTPrimes().begin();
            vars.FillVars( "Gen_WminusfromTPrimebar_Pt",iParticle,itParticle->pt() );
            vars.FillVars( "Gen_WminusfromTPrimebar_Eta",iParticle,itParticle->eta() );
        }
    }
    if(input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars().size()>0){
        for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars().begin() ; itParticle != input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars().end(); ++itParticle){
        int iParticle = itParticle - input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars().begin();
            vars.FillVars( "Gen_WfromTPrimeandTPrimebar_Pt",iParticle,itParticle->pt() );
            vars.FillVars( "Gen_WfromTPrimeandTPrimebar_Eta",iParticle,itParticle->eta() );
        }
    }
    if(input.zprimetotprimeallhad.GetBottom_fromTops().size()>0){
        for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetBottom_fromTops().begin() ; itParticle != input.zprimetotprimeallhad.GetBottom_fromTops().end(); ++itParticle){
            int iParticle = itParticle - input.zprimetotprimeallhad.GetBottom_fromTops().begin();
            if(abs(itParticle->pdgId())==5){
                vars.FillVars( "Gen_BottomfromTop_Pt",iParticle,itParticle->pt() );
                vars.FillVars( "Gen_BottomfromTop_Eta",iParticle,itParticle->eta() );
            }
        }
    }
    if(input.zprimetotprimeallhad.GetBottom_fromTopbars().size()>0){
        for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetBottom_fromTopbars().begin() ; itParticle != input.zprimetotprimeallhad.GetBottom_fromTopbars().end(); ++itParticle){
            int iParticle = itParticle - input.zprimetotprimeallhad.GetBottom_fromTopbars().begin();
            if(abs(itParticle->pdgId())==5){
                vars.FillVars( "Gen_BottombarfromTopbar_Pt",iParticle,itParticle->pt() );
                vars.FillVars( "Gen_BottombarfromTopbar_Eta",iParticle,itParticle->eta() );
            }
        }
    }
    if(input.zprimetotprimeallhad.GetBottom_fromTopsandTopbars().size()>0){
        for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetBottom_fromTopsandTopbars().begin() ; itParticle != input.zprimetotprimeallhad.GetBottom_fromTopsandTopbars().end(); ++itParticle){
            int iParticle = itParticle - input.zprimetotprimeallhad.GetBottom_fromTopsandTopbars().begin();
            if(abs(itParticle->pdgId())==5){
                vars.FillVars( "Gen_BottomfromTopandTopbar_Pt",iParticle,itParticle->pt() );
                vars.FillVars( "Gen_BottomfromTopandTopbar_Eta",iParticle,itParticle->eta() );
            }
        }
    }
    if(input.zprimetotprimeallhad.GetBottom_fromTPrimes().size()>0){
        for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetBottom_fromTPrimes().begin() ; itParticle != input.zprimetotprimeallhad.GetBottom_fromTPrimes().end(); ++itParticle){
            int iParticle = itParticle - input.zprimetotprimeallhad.GetBottom_fromTPrimes().begin();
            if(abs(itParticle->pdgId())==5){
                vars.FillVars( "Gen_BottomfromTPrime_Pt",iParticle,itParticle->pt() );
                vars.FillVars( "Gen_BottomfromTPrime_Eta",iParticle,itParticle->eta() );
            }
        }
    }
    if(input.zprimetotprimeallhad.GetBottom_fromTPrimebars().size()>0){
        for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetBottom_fromTPrimebars().begin() ; itParticle != input.zprimetotprimeallhad.GetBottom_fromTPrimebars().end(); ++itParticle){
            int iParticle = itParticle - input.zprimetotprimeallhad.GetBottom_fromTPrimebars().begin();
            if(abs(itParticle->pdgId())==5){
                vars.FillVars( "Gen_BottombarfromTPrimebar_Pt",iParticle,itParticle->pt() );
                vars.FillVars( "Gen_BottombarfromTPrimebar_Eta",iParticle,itParticle->eta() );
            }
        }
    }
    if(input.zprimetotprimeallhad.GetBottom_fromTPrimesandTPrimebars().size()>0){
        for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetBottom_fromTPrimesandTPrimebars().begin() ; itParticle != input.zprimetotprimeallhad.GetBottom_fromTPrimesandTPrimebars().end(); ++itParticle){
            int iParticle = itParticle - input.zprimetotprimeallhad.GetBottom_fromTPrimesandTPrimebars().begin();
            if(abs(itParticle->pdgId())==5){
                vars.FillVars( "Gen_BottomfromTPrimeandTPrimebar_Pt",iParticle,itParticle->pt() );
                vars.FillVars( "Gen_BottomfromTPrimeandTPrimebar_Eta",iParticle,itParticle->eta() );
            }
        }
    }
    
    if((input.zprimetotprimeallhad.GetTopsandTopbars_fromZprimes().size()==1 && input.zprimetotprimeallhad.GetTPrimesandTPrimebars().size()==1)){
        float DeltaR= BoostedUtils::DeltaR(input.zprimetotprimeallhad.GetTopsandTopbars_fromZprimes()[0].p4(),input.zprimetotprimeallhad.GetTPrimesandTPrimebars()[0].p4());
        vars.FillVar( "Gen_Top_TPrime_DeltaR", DeltaR );
    }
    if((input.zprimetotprimeallhad.GetTopsandTopbars_fromZprimes().size()==1 && input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars().size()==1)){
        float DeltaR=BoostedUtils::DeltaR(input.zprimetotprimeallhad.GetTopsandTopbars_fromZprimes()[0].p4(),input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars()[0].p4());
        vars.FillVar( "Gen_Top_WfromTPrime_DeltaR", DeltaR );
    }
    if((input.zprimetotprimeallhad.GetTopsandTopbars_fromZprimes().size()==1 && input.zprimetotprimeallhad.GetTPrimeandTPrimebarDecayBottoms().size()==1)){
        float DeltaR=BoostedUtils::DeltaR(input.zprimetotprimeallhad.GetTopsandTopbars_fromZprimes()[0].p4(),input.zprimetotprimeallhad.GetTPrimeandTPrimebarDecayBottoms()[0].p4());
        vars.FillVar( "Gen_Top_BottomfromTPrime_DeltaR", DeltaR );
    }
    if((input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars().size()==1 && input.zprimetotprimeallhad.GetTPrimeandTPrimebarDecayBottoms().size()==1)){
        float DeltaR=BoostedUtils::DeltaR(input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars()[0].p4(),input.zprimetotprimeallhad.GetTPrimeandTPrimebarDecayBottoms()[0].p4());
        vars.FillVar( "Gen_WfromTPrime_BottomfromTPrime_DeltaR", DeltaR );
    }
    if((input.zprimetotprimeallhad.GetW_fromTopsandTopbars().size()==1 && input.zprimetotprimeallhad.GetTopandTopbarDecayBottoms().size()==1)){
        float DeltaR=BoostedUtils::DeltaR(input.zprimetotprimeallhad.GetW_fromTopsandTopbars()[0].p4(),input.zprimetotprimeallhad.GetTopandTopbarDecayBottoms()[0].p4());
        vars.FillVar( "Gen_WfromTop_BottomfromTop_DeltaR", DeltaR );
    }

    
    if((input.zprimetotprimeallhad.GetTopsandTopbars_fromTprimes().size()==1 && input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars().size()==1)){
        float DeltaEta=BoostedUtils::DeltaEta(input.zprimetotprimeallhad.GetTopsandTopbars_fromTprimes()[0].p4(),input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars()[0].p4());
        vars.FillVar( "Gen_Top_WfromTPrime_DeltaEta", DeltaEta );
    }
    if((input.zprimetotprimeallhad.GetTopsandTopbars_fromTprimes().size()==1 && input.zprimetotprimeallhad.GetTPrimeandTPrimebarDecayBottoms().size()==1)){
        float DeltaEta=BoostedUtils::DeltaEta(input.zprimetotprimeallhad.GetTopsandTopbars_fromTprimes()[0].p4(),input.zprimetotprimeallhad.GetTPrimeandTPrimebarDecayBottoms()[0].p4());
        vars.FillVar( "Gen_Top_BottomfromTPrime_DeltaEta", DeltaEta );
    }
    if((input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars().size()==1 && input.zprimetotprimeallhad.GetTPrimeandTPrimebarDecayBottoms().size()==1)){
        float DeltaEta=BoostedUtils::DeltaEta(input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars()[0].p4(),input.zprimetotprimeallhad.GetTPrimeandTPrimebarDecayBottoms()[0].p4());
        vars.FillVar( "Gen_WfromTPrime_BottomfromTPrime_DeltaEta", DeltaEta );
    }

    if((input.zprimetotprimeallhad.GetTopsandTopbars_fromTprimes().size()==1 && input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars().size()==1)){
        float DeltaPhi=BoostedUtils::DeltaPhi(input.zprimetotprimeallhad.GetTopsandTopbars_fromTprimes()[0].p4(),input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars()[0].p4());
        vars.FillVar( "Gen_Top_WfromTPrime_DeltaPhi", DeltaPhi );
    }
    if((input.zprimetotprimeallhad.GetTopsandTopbars_fromTprimes().size()==1 && input.zprimetotprimeallhad.GetTPrimeandTPrimebarDecayBottoms().size()==1)){
        float DeltaPhi=BoostedUtils::DeltaPhi(input.zprimetotprimeallhad.GetTopsandTopbars_fromTprimes()[0].p4(),input.zprimetotprimeallhad.GetTPrimeandTPrimebarDecayBottoms()[0].p4());
        vars.FillVar( "Gen_Top_BottomfromTPrime_DeltaPhi", DeltaPhi );
    }
    if((input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars().size()==1 && input.zprimetotprimeallhad.GetTPrimeandTPrimebarDecayBottoms().size()==1)){
        float DeltaPhi=BoostedUtils::DeltaPhi(input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars()[0].p4(),input.zprimetotprimeallhad.GetTPrimeandTPrimebarDecayBottoms()[0].p4());
        vars.FillVar( "Gen_WfromTPrime_BottomfromTPrime_DeltaPhi", DeltaPhi );
    }

    
    std::vector<reco::GenParticle> TopZprime;
    std::vector<reco::GenParticle> TPrime;
    std::vector<reco::GenParticle> WfromTPrime;
    std::vector<reco::GenParticle> bfromTPrime;
    
    std::vector<reco::GenParticle> TopBG;
    std::vector<reco::GenParticle> BottomBG;
    std::vector<reco::GenParticle> WBG;

    
    
    if(input.zprimetotprimeallhad.IsFilled()){
    TopZprime=input.zprimetotprimeallhad.GetTopsandTopbars_fromZprimes();
    TPrime=input.zprimetotprimeallhad.GetTPrimesandTPrimebars();
    WfromTPrime=input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars();
    bfromTPrime=input.zprimetotprimeallhad.GetBottom_fromTPrimesandTPrimebars();
    
    TopBG=input.zprimetotprimeallhad.GetTopsandTopbars_fromBG();
    BottomBG=input.zprimetotprimeallhad.GetBottomsandBottombars_fromBG();
    WBG=input.zprimetotprimeallhad.GetWs_fromBG();

    }    

    vars.FillVar("N_Gen_BottomfromBG",BottomBG.size());

//         std::cout<<"after gen"<<endl;
    
//AK8->Jets
    if(input.selectedJetsAK8.size()>0){
            
///General AK8-Jet        
        for(std::vector<pat::Jet>::const_iterator itJet=input.selectedJetsAK8.begin(); itJet != input.selectedJetsAK8.end(); ++itJet){
            int iJet = itJet - input.selectedJetsAK8.begin();
            if (itJet->pt()<200 || abs(itJet->eta())>2.4){
                continue;
            }
            vars.FillVars("packedPatJetsAK8PFCHSSoftDrop_E",iJet,itJet->energy());
            vars.FillVars("packedPatJetsAK8PFCHSSoftDrop_M",iJet,itJet->mass());
            vars.FillVars("packedPatJetsAK8PFCHSSoftDrop_Pt",iJet,itJet->pt());
            vars.FillVars("packedPatJetsAK8PFCHSSoftDrop_Phi",iJet,itJet->phi());
            vars.FillVars("packedPatJetsAK8PFCHSSoftDrop_Eta",iJet,itJet->eta());

            vars.FillVars("softDropMassAK8CHS",iJet, itJet->userFloat("ak8PFJetsCHSSoftDropMass"));

            vars.FillVars("NjettinessAK8CHS_tau1",iJet,itJet->userFloat("NjettinessAK8CHS:tau1"));
            vars.FillVars("NjettinessAK8CHS_tau2",iJet,itJet->userFloat("NjettinessAK8CHS:tau2"));
            vars.FillVars("NjettinessAK8CHS_tau3",iJet,itJet->userFloat("NjettinessAK8CHS:tau3"));


            double max_subjet_csv_v2=-10;
            auto const & names = itJet->subjets("SoftDrop");
            for( auto const & itsubJet : names ){

                if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>max_subjet_csv_v2){
                    max_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
                    vars.FillVars("packedPatJetsAK8PFCHSSoftDrop_subjetCSVv2",iJet,max_subjet_csv_v2);
                }
            }
        }
    }

//     std::cout<<"there10"<<endl;

///////Object Identification///////
    float ht =0.;
    for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin() ; itJet != input.selectedJets.end(); ++itJet){
        ht += itJet->pt();
    }
    if( ht>850){
    
    //math::XYZTTLorentzVector top;
    std::vector<pat::Jet> tops;
    std::vector<pat::Jet> tops_withbtag;
    std::vector<pat::Jet> Ws;
    std::vector<pat::Jet> bottoms;
    std::vector<pat::Jet> separated_bottoms;
    
    std::vector<pat::Jet> tops_anti;
    std::vector<pat::Jet> tops_withbtag_anti;
    std::vector<pat::Jet> Ws_anti;
    std::vector<pat::Jet> bottoms_anti;
    std::vector<pat::Jet> Zs;
    std::vector<pat::Jet> Higgs;
    std::vector<pat::Jet> Higgs_with1btag;
    std::vector<pat::Jet> Higgs_with2btag;
    std::vector<pat::Jet> Zs_anti;
    std::vector<pat::Jet> Higgs_anti;
    std::vector<pat::Jet> Higgs_with1btag_anti;
    std::vector<pat::Jet> Higgs_with2btag_anti;
    
    std::vector<pat::Jet> no_bottoms;
    
    math::XYZTLorentzVector Tprime;
    math::XYZTLorentzVector Tprime_bottom_anti;
    math::XYZTLorentzVector Tprime_no_bottom;
    math::XYZTLorentzVector Tprime_W_anti;
    math::XYZTLorentzVector Tprime_W_anti_bottom_anti;
    
    math::XYZTLorentzVector Zprime;
    math::XYZTLorentzVector Zprime_withtopbtag;
    math::XYZTLorentzVector Zprime_top_anti;
    math::XYZTLorentzVector Zprime_top_anti_W_anti;
    math::XYZTLorentzVector Zprime_top_anti_bottom_anti;
    math::XYZTLorentzVector Zprime_top_anti_W_anti_bottom_anti;
    math::XYZTLorentzVector Zprime_top_withbtag_anti;
    math::XYZTLorentzVector Zprime_top_withbtag_anti_W_anti;
    math::XYZTLorentzVector Zprime_top_withbtag_anti_bottom_anti;
    math::XYZTLorentzVector Zprime_top_withbtag_anti_W_anti_bottom_anti;
    math::XYZTLorentzVector Zprime_W_anti;
    math::XYZTLorentzVector Zprime_withtopbtag_W_anti;
    math::XYZTLorentzVector Zprime_bottom_anti;
    math::XYZTLorentzVector Zprime_no_bottom;
    math::XYZTLorentzVector Zprime_withtopbtag_bottom_anti;
    math::XYZTLorentzVector Zprime_withtopbtag_no_bottom;
    math::XYZTLorentzVector Zprime_W_anti_bottom_anti;
    math::XYZTLorentzVector Zprime_withtopbtag_W_anti_bottom_anti;
    
    bool top_candidatefound=false;
    bool top_anti_candidatefound=false;
    bool top_withbtag_candidatefound=false;
    bool top_withbtag_anti_candidatefound=false;
    bool W_candidatefound=false;
    bool W_anti_candidatefound=false;
    bool bottom_candidatefound=false;
    bool bottom_anti_candidatefound=false;
    
/*    
    bool no_bottom_candidatesfound=false;
    bool Tprime_candidatefound=false;
    bool Tprime_bottom_anti_candidatefound=false;
    bool Tprime_no_bottom_candidatefound=false;
    bool Tprime_W_anti_candidatefound=false;
    bool Tprime_W_anti_bottom_anti_candidatefound=false;
*/    
    bool Z_candidatefound=false;
    bool Z_anti_candidatefound=false;

    bool Higgs_candidatefound=false;
    bool Higgs_with1btag_candidatefound=false;
    bool Higgs_with2btag_candidatefound=false;
    bool Higgs_anti_candidatefound=false;
    bool Higgs_with1btag_anti_candidatefound=false;
    bool Higgs_with2btag_anti_candidatefound=false;

    
    std::vector<pat::Jet> AK15_top_candidates;
    std::vector<pat::Jet> AK15_W_candidates;
    std::vector<pat::Jet> AK12_top_candidates;
    std::vector<pat::Jet> AK12_W_candidates;
    std::vector<pat::Jet> AK8_top_candidates;
    std::vector<pat::Jet> AK8_W_candidates;
    std::vector<pat::Jet> AK4_bottom_candidates;
  
    
    

    std::vector<pat::Jet> AK8_top_tag_candidates;
    std::vector<pat::Jet> AK8_W_tag_candidates;
    std::vector<pat::Jet> AK4_bottom_tag_candidates;
    std::vector<pat::Jet> AK8_top_misstag_candidates;
    std::vector<pat::Jet> AK8_W_misstag_candidates;
    std::vector<pat::Jet> AK4_bottom_misstag_candidates;

    std::vector<pat::Jet> tagged_top;
    std::vector<pat::Jet> tagged_top_withbtag;
    std::vector<pat::Jet> tagged_W;
    std::vector<pat::Jet> tagged_bottom;
    std::vector<pat::Jet> misstagged_top;
    std::vector<pat::Jet> misstagged_top_withbtag;
    std::vector<pat::Jet> misstagged_W;
    std::vector<pat::Jet> misstagged_bottom;
        
    std::vector<pat::Jet> AK8_top_tag_anti_candidates;
    std::vector<pat::Jet> AK8_W_tag_anti_candidates;
    std::vector<pat::Jet> AK4_bottom_tag_anti_candidates;
    std::vector<pat::Jet> AK8_top_misstag_anti_candidates;
    std::vector<pat::Jet> AK8_W_misstag_anti_candidates;
    std::vector<pat::Jet> AK4_bottom_misstag_anti_candidates;
    
    std::vector<pat::Jet> tagged_top_anti;
    std::vector<pat::Jet> tagged_top_withbtag_anti;
    std::vector<pat::Jet> tagged_W_anti;
    std::vector<pat::Jet> tagged_bottom_anti;
    std::vector<pat::Jet> misstagged_top_anti;
    std::vector<pat::Jet> misstagged_top_withbtag_anti;
    std::vector<pat::Jet> misstagged_W_anti;
    std::vector<pat::Jet> misstagged_bottom_anti;

    
    std::vector<math::XYZTLorentzVector> ZprimesABCD;
    std::vector<math::XYZTLorentzVector> TprimesABCD;
    std::vector<pat::Jet> TopsABCD;
    std::vector<pat::Jet> BottomsABCD;
    std::vector<pat::Jet> WsABCD;
    
    std::vector<math::XYZTLorentzVector> ZprimesABCDmasscorrnotopbtag;
    std::vector<math::XYZTLorentzVector> TprimesABCDmasscorrnotopbtag;
    std::vector<pat::Jet> TopsABCDmasscorrnotopbtag;
    std::vector<pat::Jet> BottomsABCDmasscorrnotopbtag;
    std::vector<pat::Jet> WsABCDmasscorrnotopbtag;
    
    std::vector<math::XYZTLorentzVector> ZprimesABCDmasscorrwithtopbtag;
    std::vector<math::XYZTLorentzVector> TprimesABCDmasscorrwithtopbtag;
    std::vector<pat::Jet> TopsABCDmasscorrwithtopbtag;
    std::vector<pat::Jet> BottomsABCDmasscorrwithtopbtag;
    std::vector<pat::Jet> WsABCDmasscorrwithtopbtag;
    
    std::vector<math::XYZTLorentzVector> Zprimes_ABCD_tAK15WAK15bAK4;
    std::vector<math::XYZTLorentzVector> Tprimes_ABCD_tAK15WAK15bAK4;
    std::vector<pat::Jet> Tops_ABCD_tAK15WAK15bAK4;
    std::vector<pat::Jet> Bottoms_ABCD_tAK15WAK15bAK4;
    std::vector<pat::Jet> Ws_ABCD_tAK15WAK15bAK4;    

    std::vector<math::XYZTLorentzVector> Zprimes_ABCD_tAK15WAK8bAK4;
    std::vector<math::XYZTLorentzVector> Tprimes_ABCD_tAK15WAK8bAK4;
    std::vector<pat::Jet> Tops_ABCD_tAK15WAK8bAK4;
    std::vector<pat::Jet> Bottoms_ABCD_tAK15WAK8bAK4;
    std::vector<pat::Jet> Ws_ABCD_tAK15WAK8bAK4;      
    
    std::vector<math::XYZTLorentzVector> Zprimes_ABCD_tAK12WAK12bAK4;
    std::vector<math::XYZTLorentzVector> Tprimes_ABCD_tAK12WAK12bAK4;
    std::vector<pat::Jet> Tops_ABCD_tAK12WAK12bAK4;
    std::vector<pat::Jet> Bottoms_ABCD_tAK12WAK12bAK4;
    std::vector<pat::Jet> Ws_ABCD_tAK12WAK12bAK4; 
    
    std::vector<math::XYZTLorentzVector> Zprimes_ABCD_tAK12WAK8bAK4;
    std::vector<math::XYZTLorentzVector> Tprimes_ABCD_tAK12WAK8bAK4;
    std::vector<pat::Jet> Tops_ABCD_tAK12WAK8bAK4;
    std::vector<pat::Jet> Bottoms_ABCD_tAK12WAK8bAK4;
    std::vector<pat::Jet> Ws_ABCD_tAK12WAK8bAK4;
    
    if(input.selectedJetsAK15.size()>0){
/// AK15-Jet        
        for(std::vector<pat::Jet>::const_iterator itJet=input.selectedJetsAK15.begin(); itJet != input.selectedJetsAK15.end(); ++itJet){
            if (itJet->pt()>100 || abs(itJet->eta())<2.4){
                AK15_W_candidates.push_back(*itJet);
                if (itJet->pt()>200){
                    AK15_top_candidates.push_back(*itJet);
                }                
            }
        }
            
    }  
    
    
    
    if(input.selectedJetsAK12.size()>0){
/// AK12-Jet        
        for(std::vector<pat::Jet>::const_iterator itJet=input.selectedJetsAK12.begin(); itJet != input.selectedJetsAK12.end(); ++itJet){
            if (itJet->pt()>100 || abs(itJet->eta())<2.4){
                AK12_W_candidates.push_back(*itJet);
                if (itJet->pt()>200){
                    AK12_top_candidates.push_back(*itJet);
                }                
            }
        }
            
    }
    
    
//AK8->Jets
    if(input.selectedJetsAK8.size()>0){
       
///General AK8-Jet        
        for(std::vector<pat::Jet>::const_iterator itJet=input.selectedJetsAK8.begin(); itJet != input.selectedJetsAK8.end(); ++itJet){
            //int iJet = itJet - input.selectedJetsAK8.begin();

            /*double max_subjet_csv_v2=-10;
            auto const & names = itJet->subjets("SoftDrop");
            for( auto const & itsubJet : names ){

                if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>max_subjet_csv_v2){
                    max_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
                    vars.FillVars("selectedJetsAK8_subjetCSVv2",iJet,max_subjet_csv_v2);
                }
            }*/
            
///top- and W-candidates
            if (itJet->pt()>200 && abs(itJet->eta())<2.4){
               
//top candidates
                if (itJet->pt()>400){
                    if(!(ZPrimeToTPrimeAllHadProcessor::Top_subbtag(*itJet,"M"))){
                        if(ZPrimeToTPrimeAllHadProcessor::Toptag(*itJet,"M")){
                            tops.push_back(*itJet);
                            top_candidatefound=true;
//                             std::cout<<"top with no subbtag found"<<endl;
                        }else{
                            tops_anti.push_back(*itJet);
                            top_anti_candidatefound=true;
//                             std::cout<<"top anti with no subbtag found"<<endl;
                        }

                    }else{
                        if(ZPrimeToTPrimeAllHadProcessor::Toptag(*itJet,"M")){
                            tops_withbtag.push_back(*itJet);
                            top_withbtag_candidatefound=true;
//                             std::cout<<"top withsubbtag found"<<endl;
                        }else{
                            tops_withbtag_anti.push_back(*itJet);
                            top_withbtag_anti_candidatefound=true;
//                             std::cout<<"top anti withsubbtag found"<<endl;
                        }
                    }
                }

                    
//W candidates
                if (ZPrimeToTPrimeAllHadProcessor::Wtag(*itJet, "M")){
                    Ws.push_back(*itJet);
                    W_candidatefound=true;
                }
                else {
                    Ws_anti.push_back(*itJet);
                    W_anti_candidatefound=true;
                }
                
//Z candidates
                if(itJet->userFloat("NjettinessAK8CHS:tau3")>0 && itJet->userFloat("NjettinessAK8CHS:tau2")>0 && itJet->userFloat("NjettinessAK8CHS:tau1")>0 && itJet->userFloat("NjettinessAK8CHS:tau2")/itJet->userFloat("NjettinessAK8CHS:tau1")<0.6 && 80<itJet->userFloat("ak8PFJetsCHSSoftDropMass") && itJet->userFloat("ak8PFJetsCHSSoftDropMass")<110){
                    Zs.push_back(*itJet);
                    Z_candidatefound=true;
                } else {
                    Zs_anti.push_back(*itJet);
                    Z_anti_candidatefound=true;
                }
//H candidates
                if(itJet->userFloat("NjettinessAK8CHS:tau3")>0 && itJet->userFloat("NjettinessAK8CHS:tau2")>0 && itJet->userFloat("NjettinessAK8CHS:tau1")>0 && itJet->userFloat("NjettinessAK8CHS:tau2")/itJet->userFloat("NjettinessAK8CHS:tau1")<0.6 && 90<itJet->userFloat("ak8PFJetsCHSSoftDropMass") && itJet->userFloat("ak8PFJetsCHSSoftDropMass")<160){
                    Higgs.push_back(*itJet);
                    Higgs_candidatefound=true;
                    double max_subjet_csv_v2=-10;
                    double min_subjet_csv_v2=-10;
                    auto const & names = itJet->subjets("SoftDrop");
                    for( auto const & itsubJet : names ){
                        if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>max_subjet_csv_v2){
                            max_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
                        }
                        if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")<abs(min_subjet_csv_v2)){
                            min_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
                        }
                    }   
                    if (max_subjet_csv_v2>0.8){
                        Higgs_with1btag.push_back(*itJet);
                        Higgs_with1btag_candidatefound=true;
                    } else {
                        Higgs_with1btag_anti.push_back(*itJet);
                        Higgs_with1btag_anti_candidatefound=true;
                    }
                    if (min_subjet_csv_v2>0.8){
                        Higgs_with2btag.push_back(*itJet);
                        Higgs_with2btag_candidatefound=true;
                    } else {
                        Higgs_with2btag_anti.push_back(*itJet);
                        Higgs_with2btag_anti_candidatefound=true;                    }
                    
                } else {
                    Higgs_with1btag_anti.push_back(*itJet);
                    Higgs_with2btag_anti.push_back(*itJet);
                    Higgs_anti.push_back(*itJet);
                    Higgs_anti_candidatefound=true;
                    Higgs_with1btag_anti_candidatefound=true;
                    Higgs_with2btag_anti_candidatefound=true;
                }
            }  
        }
    }

//AK4-Jets
  for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin() ; itJet != input.selectedJets.end(); ++itJet){
    //int iJet = itJet - input.selectedJets.begin();
    if(input.zprimetotprimeallhad.IsFilled()){
        if (itJet->pt()>100 && abs(itJet->eta())<2.4){
            //N_AK4_bottom_misstag_candidates+=1;
            //vars.FillVars("AK4_bottom_misstagged_candidates_pt",iJet,itJet->pt());
            //vars.FillVars("AK4_bottom_misstagged_candidates_eta",iJet,itJet->eta());
            
            
            if (ZPrimeToTPrimeAllHadProcessor::Bottomtag(*itJet,"M")){
                bottoms.push_back(*itJet);
                bottom_candidatefound=true; 
                //separated_bottom_candidatefound=true;
            }
            else{
                bottoms_anti.push_back(*itJet);
                bottom_anti_candidatefound=true;
                //separated_bottom_anti_candidatefound=true;
            }
        
        }
        
        
    }
  }
  
  
///Fill tops
  vars.FillVar("N_Tops",tops.size());   
  vars.FillVar("N_Tops_withbtag",tops_withbtag.size());   
  vars.FillVar("N_Tops_anti",tops_anti.size());   
  vars.FillVar("N_Tops_withbtag_anti",tops_withbtag_anti.size());   
    
  for(std::vector<pat::Jet>::const_iterator itJet = tops.begin() ; itJet != tops.end(); ++itJet){
    int iJet = itJet - tops.begin();
    vars.FillVars("Tops_pt",iJet,itJet->pt());
    vars.FillVars("Tops_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = tops_withbtag.begin() ; itJet != tops_withbtag.end(); ++itJet){
    int iJet = itJet - tops_withbtag.begin();
    vars.FillVars("Tops_withbtag_pt",iJet,itJet->pt());
    vars.FillVars("Tops_withbtag_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = tops_anti.begin() ; itJet != tops_anti.end(); ++itJet){
    int iJet = itJet - tops_anti.begin();
    vars.FillVars("Tops_anti_pt",iJet,itJet->pt());
    vars.FillVars("Tops_anti_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = tops_withbtag_anti.begin() ; itJet != tops_withbtag_anti.end(); ++itJet){
    int iJet = itJet - tops_withbtag_anti.begin();
    vars.FillVars("Tops_withbtag_anti_pt",iJet,itJet->pt());
    vars.FillVars("Tops_withbtag_anti_eta",iJet,itJet->eta());
  }
///Fill Ws
  vars.FillVar("N_Ws",Ws.size());   
  vars.FillVar("N_Ws_anti",Ws_anti.size());   
    
  for(std::vector<pat::Jet>::const_iterator itJet = Ws.begin() ; itJet != Ws.end(); ++itJet){
    int iJet = itJet - Ws.begin();
    vars.FillVars("Ws_pt",iJet,itJet->pt());
    vars.FillVars("Ws_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = Ws_anti.begin() ; itJet != Ws_anti.end(); ++itJet){
    int iJet = itJet - Ws_anti.begin();
    vars.FillVars("Ws_anti_pt",iJet,itJet->pt());
    vars.FillVars("Ws_anti_eta",iJet,itJet->eta());
  }
///Fill separated_bottoms
  vars.FillVar("N_Bottoms",bottoms.size());   
  vars.FillVar("N_Bottoms_anti",bottoms_anti.size());
    
  for(std::vector<pat::Jet>::const_iterator itJet = bottoms.begin() ; itJet != bottoms.end(); ++itJet){
    int iJet = itJet - bottoms.begin();
    vars.FillVars("Bottoms_pt",iJet,itJet->pt());
    vars.FillVars("Bottoms_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = bottoms_anti.begin() ; itJet != bottoms_anti.end(); ++itJet){
    int iJet = itJet - bottoms_anti.begin();
    vars.FillVars("Bottoms_anti_pt",iJet,itJet->pt());
    vars.FillVars("Bottoms_anti_eta",iJet,itJet->eta());
  } 
/*  for(std::vector<pat::Jet>::const_iterator itJet = no_bottoms.begin() ; itJet != no_bottoms.end(); ++itJet){
    int iJet = itJet - no_bottoms.begin();
    vars.FillVars("No_Bottoms_pt",iJet,itJet->pt());
    vars.FillVars("No_Bottoms_eta",iJet,itJet->eta());
  } 
  
*/
/*
  vars.FillVar("N_SelectedBottoms",bottoms.size());   
  vars.FillVar("N_SelectedBottoms_anti",bottoms_anti.size());
  vars.FillVar("N_no_Bottoms",no_bottoms.size());
  
  for(std::vector<pat::Jet>::const_iterator itJet = bottoms.begin() ; itJet != bottoms.end(); ++itJet){
    int iJet = itJet - bottoms.begin();
    vars.FillVars("Bottoms_pt",iJet,itJet->pt());
    vars.FillVars("Bottoms_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = bottoms_anti.begin() ; itJet != bottoms_anti.end(); ++itJet){
    int iJet = itJet - bottoms_anti.begin();
    vars.FillVars("Bottoms_anti_pt",iJet,itJet->pt());
    vars.FillVars("Bottoms_anti_eta",iJet,itJet->eta());
  } 
  for(std::vector<pat::Jet>::const_iterator itJet = no_bottoms.begin() ; itJet != no_bottoms.end(); ++itJet){
    int iJet = itJet - no_bottoms.begin();
    vars.FillVars("No_Bottoms_pt",iJet,itJet->pt());
    vars.FillVars("No_Bottoms_eta",iJet,itJet->eta());
  } 
*/  
//   std::cout<<"here6"<<endl;
///Fill Zs
  vars.FillVar("N_Zs",Zs.size());   
  vars.FillVar("N_Zs_anti",Zs_anti.size());   
    
  for(std::vector<pat::Jet>::const_iterator itJet = Zs.begin() ; itJet != Zs.end(); ++itJet){
    int iJet = itJet - Zs.begin();
    vars.FillVars("Zs_pt",iJet,itJet->pt());
    vars.FillVars("Zs_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = Zs_anti.begin() ; itJet != Zs_anti.end(); ++itJet){
    int iJet = itJet - Zs_anti.begin();
    vars.FillVars("Zs_anti_pt",iJet,itJet->pt());
    vars.FillVars("Zs_anti_eta",iJet,itJet->eta());
  }
//     std::cout<<"here7"<<endl;
///Fill Higgs
  vars.FillVar("N_Higgs",Higgs.size());   
  vars.FillVar("N_Higgs_with1btag",Higgs_with1btag.size());   
  vars.FillVar("N_Higgs_with2btag",Higgs_with2btag.size());   
  vars.FillVar("N_Higgs_anti",Higgs_anti.size());   
  vars.FillVar("N_Higgs_with1btag_anti",Higgs_with1btag_anti.size());   
  vars.FillVar("N_Higgs_with2btag_anti",Higgs_with2btag_anti.size());   
    
  for(std::vector<pat::Jet>::const_iterator itJet = Higgs.begin() ; itJet != Higgs.end(); ++itJet){
    int iJet = itJet - Higgs.begin();
    vars.FillVars("Higgs_pt",iJet,itJet->pt());
    vars.FillVars("Higgs_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = Higgs_with1btag.begin() ; itJet != Higgs_with1btag.end(); ++itJet){
    int iJet = itJet - Higgs_with1btag.begin();
    vars.FillVars("Higgs_with1btag_pt",iJet,itJet->pt());
    vars.FillVars("Higgs_with1btag_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = Higgs_with2btag.begin() ; itJet != Higgs_with2btag.end(); ++itJet){
    int iJet = itJet - Higgs_with2btag.begin();
    vars.FillVars("Higgs_with2btag_pt",iJet,itJet->pt());
    vars.FillVars("Higgs_with2btag_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = Higgs_anti.begin() ; itJet != Higgs_anti.end(); ++itJet){
    int iJet = itJet - Higgs_anti.begin();
    vars.FillVars("Higgs_anti_pt",iJet,itJet->pt());
    vars.FillVars("Higgs_anti_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = Higgs_with1btag_anti.begin() ; itJet != Higgs_with1btag_anti.end(); ++itJet){
    int iJet = itJet - Higgs_with1btag_anti.begin();
    vars.FillVars("Higgs_with1btag_anti_pt",iJet,itJet->pt());
    vars.FillVars("Higgs_with1btag_anti_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = Higgs_with2btag_anti.begin() ; itJet != Higgs_with2btag_anti.end(); ++itJet){
    int iJet = itJet - Higgs_with2btag_anti.begin();
    vars.FillVars("Higgs_with2btag_anti_pt",iJet,itJet->pt());
    vars.FillVars("Higgs_with2btag_anti_eta",iJet,itJet->eta());
  }
  
  
//     std::cout<<"here8"<<endl;
    
  if(Z_candidatefound && Z_anti_candidatefound && Higgs_candidatefound && Higgs_with1btag_candidatefound && Higgs_with2btag_candidatefound && Higgs_anti_candidatefound && Higgs_with1btag_anti_candidatefound && Higgs_with2btag_anti_candidatefound){std::cout<<"this event makes no sense"<<endl;}
//     std::cout<<"heredetail1"<<endl;
    
    
    
    
///TPrime reconstruction Wtb-channel
/* 
  if ((top_candidatefound || top_withbtag_candidatefound || top_anti_candidatefound || top_withbtag_anti_candidatefound) && (W_candidatefound || W_anti_candidatefound) && (bottom_candidatefound ||bottom_anti_candidatefound)){
      if (W_candidatefound && bottom_candidatefound){  
        
        Tprime=bottoms[0].p4()+Ws[0].p4();
        if (Tprime.mass()>500){
            Tprime_candidatefound=true;
            vars.FillVar("Tprime_M",Tprime.mass());
            vars.FillVar("Tprime_pt",Tprime.pt());
        }      
      }
      
      if (W_candidatefound && bottom_anti_candidatefound){
        Tprime_bottom_anti=bottoms_anti[0].p4()+Ws[0].p4();
        if (Tprime_bottom_anti.mass()>500){
            Tprime_bottom_anti_candidatefound=true;
            vars.FillVar("Tprime_bottom_anti_M",Tprime_bottom_anti.mass());
            vars.FillVar("Tprime_bottom_anti_pt",Tprime_bottom_anti.pt());
        }      
      }
      if (W_candidatefound && no_bottom_candidatesfound){
        Tprime_no_bottom=no_bottoms[0].p4()+Ws[0].p4();
        if (Tprime_no_bottom.mass()>500){
            Tprime_no_bottom_candidatefound=true;
            vars.FillVar("Tprime_no_bottom_M",Tprime_no_bottom.mass());
            vars.FillVar("Tprime_no_bottom_pt",Tprime_no_bottom.pt());
        }      
      }      if (W_anti_candidatefound && bottom_candidatefound){
        Tprime_W_anti=bottoms[0].p4()+Ws_anti[0].p4();
        if (Tprime_W_anti.mass()>500){
            Tprime_W_anti_candidatefound=true;
            vars.FillVar("Tprime_W_anti_M",Tprime_W_anti.mass());
            vars.FillVar("Tprime_W_anti_pt",Tprime_W_anti.pt());
        }      
      }
      if (W_anti_candidatefound && bottom_anti_candidatefound){
        Tprime_W_anti_bottom_anti=bottoms_anti[0].p4()+Ws_anti[0].p4();
        if (Tprime_W_anti_bottom_anti.mass()>500){
            Tprime_W_anti_bottom_anti_candidatefound=true;
            vars.FillVar("Tprime_W_anti_bottom_anti_M",Tprime_W_anti_bottom_anti.mass());
            vars.FillVar("Tprime_W_anti_bottom_anti_pt",Tprime_W_anti_bottom_anti.pt());
        }      
      } 
  }
*/
  
  if ((top_candidatefound || top_withbtag_candidatefound || top_anti_candidatefound || top_withbtag_anti_candidatefound) && (W_candidatefound || W_anti_candidatefound) && (bottom_candidatefound ||bottom_anti_candidatefound)){
      if(W_candidatefound){
         if(top_candidatefound){
            ZPrimeReconstructionWtbComplete(vars,tops,Ws,bottoms, bottoms_anti,top_candidatefound, false, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), false, (W_anti_candidatefound  && !W_candidatefound),"Topfirst");
            ZPrimeReconstructionWtbComplete(vars,tops,Ws,bottoms,bottoms_anti,top_candidatefound, false, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), false, (W_anti_candidatefound  && !W_candidatefound),"Wfirst");             
//              std::cout<<"heredetail2"<<endl;
            /* if(bottom_candidatefound){

                 
                 
                 std::vector<pat::Jet> separated_bottoms;
                 separated_bottoms=ZPrimeToTPrimeAllHadProcessor::SelectSeparatedBottoms(tops, Ws, bottoms);
                 if(separated_bottoms.size()>0){
                     Tprime=ZPrimeToTPrimeAllHadProcessor::TPrimeReconstructionWtb(Ws,separated_bottoms);
                     if(Tprime.mass()>500){
                         
                        vars.FillVar("N_Signal_Tops",tops.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = tops.begin() ; itJet != tops.end(); ++itJet){
                            int iJet = itJet - tops.begin();
                            vars.FillVars("Signal_Tops_Pt",iJet,itJet->pt());
                            vars.FillVars("Signal_Tops_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Signal_Ws",Ws.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = Ws.begin() ; itJet != Ws.end(); ++itJet){
                            int iJet = itJet - Ws.begin();
                            vars.FillVars("Signal_Ws_Pt",iJet,itJet->pt());
                            vars.FillVars("Signal_Ws_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Signal_Bottoms",separated_bottoms.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = separated_bottoms.begin() ; itJet != separated_bottoms.end(); ++itJet){
                            int iJet = itJet - separated_bottoms.begin();
                            vars.FillVars("Signal_Bottoms_Pt",iJet,itJet->pt());
                            vars.FillVars("Signal_Bottoms_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("Signal_Tprime_M",Tprime.mass());
                        vars.FillVar("Signal_Tprime_Pt",Tprime.pt());
                        Zprime=ZPrimeToTPrimeAllHadProcessor::ZPrimeReconstructionWtb(tops, Tprime);
                        vars.FillVar("Signal_Zprime_M",Zprime.mass());
                        vars.FillVar("Signal_Zprime_Pt",Zprime.pt());
                    }
                 }
             }
             if(bottom_anti_candidatefound){
                 std::vector<pat::Jet> separated_bottoms_anti;                 
                 separated_bottoms_anti=ZPrimeToTPrimeAllHadProcessor::SelectSeparatedBottoms(tops, Ws, bottoms_anti);
                 if(separated_bottoms_anti.size()>0){
                     Tprime=ZPrimeToTPrimeAllHadProcessor::TPrimeReconstructionWtb(Ws,separated_bottoms_anti);
                     if(Tprime.mass()>500){
                         
                        vars.FillVar("N_Sideband_bottom_anti_Tops",tops.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = tops.begin() ; itJet != tops.end(); ++itJet){
                            int iJet = itJet - tops.begin();
                            vars.FillVars("Sideband_bottom_anti_Tops_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_bottom_anti_Tops_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_bottom_anti_Ws",Ws.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = Ws.begin() ; itJet != Ws.end(); ++itJet){
                            int iJet = itJet - Ws.begin();
                            vars.FillVars("Sideband_bottom_anti_Ws_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_bottom_anti_Ws_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_bottom_anti_Bottoms",separated_bottoms_anti.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = separated_bottoms_anti.begin() ; itJet != separated_bottoms_anti.end(); ++itJet){
                            int iJet = itJet - separated_bottoms_anti.begin();
                            vars.FillVars("Sideband_bottom_anti_Bottoms_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_bottom_anti_Bottoms_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("Sideband_bottom_anti_Tprime_M",Tprime.mass());
                        vars.FillVar("Sideband_bottom_anti_Tprime_Pt",Tprime.pt());
                        Zprime=ZPrimeToTPrimeAllHadProcessor::ZPrimeReconstructionWtb(tops, Tprime);
                        vars.FillVar("Sideband_bottom_anti_Zprime_M",Zprime.mass());
                        vars.FillVar("Sideband_bottom_anti_Zprime_Pt",Zprime.pt());
                    }
                 }
             }*/
         }
         if(top_withbtag_candidatefound){
            ZPrimeReconstructionWtbComplete(vars,tops_withbtag,Ws,bottoms, bottoms_anti,top_candidatefound, top_withbtag_candidatefound, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), (top_withbtag_anti_candidatefound && !top_withbtag_candidatefound), (W_anti_candidatefound  && !W_candidatefound),"Topfirst");
            ZPrimeReconstructionWtbComplete(vars,tops_withbtag,Ws,bottoms,bottoms_anti,top_candidatefound, top_withbtag_candidatefound, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), (top_withbtag_anti_candidatefound && !top_withbtag_candidatefound), (W_anti_candidatefound  && !W_candidatefound),"Wfirst");  
//             std::cout<<"heredetail3"<<endl;
             /*if(bottom_candidatefound){
                 std::vector<pat::Jet> separated_bottoms;                 
                 separated_bottoms=ZPrimeToTPrimeAllHadProcessor::SelectSeparatedBottoms(tops_withbtag, Ws, bottoms);
                 if(separated_bottoms.size()>0){
                     Tprime=ZPrimeToTPrimeAllHadProcessor::TPrimeReconstructionWtb(Ws,separated_bottoms);
                     if(Tprime.mass()>500){
                         
                        vars.FillVar("N_Signal_withtoptag_Tops",tops_withbtag.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = tops_withbtag.begin() ; itJet != tops_withbtag.end(); ++itJet){
                            int iJet = itJet - tops_withbtag.begin();
                            vars.FillVars("Signal_withtoptag_Tops_Pt",iJet,itJet->pt());
                            vars.FillVars("Signal_withtoptag_Tops_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Signal_withtoptag_Ws",Ws.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = Ws.begin() ; itJet != Ws.end(); ++itJet){
                            int iJet = itJet - Ws.begin();
                            vars.FillVars("Signal_withtoptag_Ws_Pt",iJet,itJet->pt());
                            vars.FillVars("Signal_withtoptag_Ws_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Signal_withtoptag_Bottoms",separated_bottoms.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = separated_bottoms.begin() ; itJet != separated_bottoms.end(); ++itJet){
                            int iJet = itJet - separated_bottoms.begin();
                            vars.FillVars("Signal_withtoptag_Bottoms_Pt",iJet,itJet->pt());
                            vars.FillVars("Signal_withtoptag_Bottoms_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("Signal_withtopbtag_Tprime_M",Tprime.mass());
                        vars.FillVar("Signal_withtopbtag_Tprime_Pt",Tprime.pt());
                        Zprime=ZPrimeToTPrimeAllHadProcessor::ZPrimeReconstructionWtb(tops_withbtag, Tprime);
                        vars.FillVar("Signal_withtopbtag_Zprime_M",Zprime.mass());
                        vars.FillVar("Signal_withtopbtag_Zprime_Pt",Zprime.pt());
                    }
                 }
             }
             if(bottom_anti_candidatefound){
                 std::vector<pat::Jet> separated_bottoms_anti;                 
                 separated_bottoms_anti=ZPrimeToTPrimeAllHadProcessor::SelectSeparatedBottoms(tops_withbtag, Ws, bottoms_anti);
                 if(separated_bottoms_anti.size()>0){
                     Tprime=ZPrimeToTPrimeAllHadProcessor::TPrimeReconstructionWtb(Ws,separated_bottoms_anti);
                     if(Tprime.mass()>500){
                         
                        vars.FillVar("N_Sideband_withtopbtag_bottom_anti_Tops",tops_withbtag.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = tops_withbtag.begin() ; itJet != tops_withbtag.end(); ++itJet){
                            int iJet = itJet - tops_withbtag.begin();
                            vars.FillVars("Sideband_withtopbtag_bottom_anti_Tops_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_withtopbtag_bottom_anti_Tops_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_withtopbtag_bottom_anti_Ws",Ws.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = Ws.begin() ; itJet != Ws.end(); ++itJet){
                            int iJet = itJet - Ws.begin();
                            vars.FillVars("Sideband_withtopbtag_bottom_anti_Ws_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_withtopbtag_bottom_anti_Ws_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_bottom_anti_Bottoms",separated_bottoms_anti.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = separated_bottoms_anti.begin() ; itJet != separated_bottoms_anti.end(); ++itJet){
                            int iJet = itJet - separated_bottoms_anti.begin();
                            vars.FillVars("Sideband_withtopbtag_bottom_anti_Bottoms_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_withtopbtag_bottom_anti_Bottoms_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("Sideband_withtopbtag_bottom_anti_Tprime_M",Tprime.mass());
                        vars.FillVar("Sideband_withtopbtag_bottom_anti_Tprime_Pt",Tprime.pt());
                        Zprime=ZPrimeToTPrimeAllHadProcessor::ZPrimeReconstructionWtb(tops_withbtag, Tprime);
                        vars.FillVar("Sideband_withtopbtag_bottom_anti_Zprime_M",Zprime.mass());
                        vars.FillVar("Sideband_withtopbtag_bottom_anti_Zprime_Pt",Zprime.pt());
                    }
                 }
             }*/             
         }
         if(top_anti_candidatefound && !top_candidatefound){
            ZPrimeReconstructionWtbComplete(vars,tops_anti,Ws,bottoms, bottoms_anti,top_candidatefound, false, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), false, (W_anti_candidatefound  && !W_candidatefound),"Topfirst");
            ZPrimeReconstructionWtbComplete(vars,tops_anti,Ws,bottoms,bottoms_anti,top_candidatefound, false, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), false, (W_anti_candidatefound  && !W_candidatefound),"Wfirst");
//             std::cout<<"heredetail4"<<endl;
            /*if(bottom_candidatefound){
              
                 std::vector<pat::Jet> separated_bottoms;                 
                 separated_bottoms=ZPrimeToTPrimeAllHadProcessor::SelectSeparatedBottoms(tops_anti, Ws, bottoms);
                 if(separated_bottoms.size()>0){
                     Tprime=ZPrimeToTPrimeAllHadProcessor::TPrimeReconstructionWtb(Ws,separated_bottoms);
                     if(Tprime.mass()>500){
                         
                        vars.FillVar("N_Sideband_top_anti_Tops",tops_anti.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = tops_anti.begin() ; itJet != tops_anti.end(); ++itJet){
                            int iJet = itJet - tops_anti.begin();
                            vars.FillVars("Sideband_top_anti_Tops_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_top_anti_Tops_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_top_anti_Ws",Ws.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = Ws.begin() ; itJet != Ws.end(); ++itJet){
                            int iJet = itJet - Ws.begin();
                            vars.FillVars("Sideband_top_anti_Ws_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_top_anti_Ws_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_top_anti_Bottoms",separated_bottoms.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = separated_bottoms.begin() ; itJet != separated_bottoms.end(); ++itJet){
                            int iJet = itJet - separated_bottoms.begin();
                            vars.FillVars("Sideband_top_anti_Bottoms_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_top_anti_Bottoms_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("Sideband_top_anti_Tprime_M",Tprime.mass());
                        vars.FillVar("Sideband_top_anti_Tprime_Pt",Tprime.pt());
                        Zprime=ZPrimeToTPrimeAllHadProcessor::ZPrimeReconstructionWtb(tops_anti, Tprime);
                        vars.FillVar("Sideband_top_anti_Zprime_M",Zprime.mass());
                        vars.FillVar("Sideband_top_anti_Zprime_Pt",Zprime.pt());
                    }
                 }
             }

             if(bottom_anti_candidatefound){
                 std::vector<pat::Jet> separated_bottoms_anti;                 
                 separated_bottoms_anti=ZPrimeToTPrimeAllHadProcessor::SelectSeparatedBottoms(tops_anti, Ws, bottoms_anti);
                 if(separated_bottoms_anti.size()>0){
                     Tprime=ZPrimeToTPrimeAllHadProcessor::TPrimeReconstructionWtb(Ws,separated_bottoms_anti);
                     if(Tprime.mass()>500){
                         
                        vars.FillVar("N_Sideband_top_anti_bottom_anti_Tops",tops_anti.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = tops_anti.begin() ; itJet != tops_anti.end(); ++itJet){
                            int iJet = itJet - tops_anti.begin();
                            vars.FillVars("Sideband_top_anti_bottom_anti_Tops_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_top_anti_bottom_anti_Tops_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_top_anti_bottom_anti_Ws",Ws.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = Ws.begin() ; itJet != Ws.end(); ++itJet){
                            int iJet = itJet - Ws.begin();
                            vars.FillVars("Sideband_top_anti_bottom_anti_Ws_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_top_anti_bottom_anti_Ws_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_top_anti_bottom_anti_Bottoms",separated_bottoms_anti.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = separated_bottoms_anti.begin() ; itJet != separated_bottoms_anti.end(); ++itJet){
                            int iJet = itJet - separated_bottoms_anti.begin();
                            vars.FillVars("Sideband_top_anti_bottom_anti_Bottoms_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_top_anti_bottom_anti_Bottoms_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("Sideband_top_anti_bottom_anti_Tprime_M",Tprime.mass());
                        vars.FillVar("Sideband_top_anti_bottom_anti_Tprime_Pt",Tprime.pt());
                        Zprime=ZPrimeToTPrimeAllHadProcessor::ZPrimeReconstructionWtb(tops_anti, Tprime);
                        vars.FillVar("Sideband_top_anti_bottom_anti_Zprime_M",Zprime.mass());
                        vars.FillVar("Sideband_top_anti_bottom_anti_Zprime_Pt",Zprime.pt());
                    }
                 }
             }*/
         }
         if(top_withbtag_anti_candidatefound && !top_withbtag_candidatefound){
            ZPrimeReconstructionWtbComplete(vars,tops_withbtag_anti,Ws,bottoms, bottoms_anti,top_candidatefound, top_withbtag_candidatefound, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), (top_withbtag_anti_candidatefound && !top_withbtag_candidatefound), (W_anti_candidatefound  && !W_candidatefound),"Topfirst");
            ZPrimeReconstructionWtbComplete(vars,tops_withbtag_anti,Ws,bottoms,bottoms_anti,top_candidatefound, top_withbtag_candidatefound, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), (top_withbtag_anti_candidatefound && !top_withbtag_candidatefound), (W_anti_candidatefound  && !W_candidatefound),"Wfirst");                 
//              std::cout<<"heredetail5"<<endl;
             /*if(bottom_candidatefound){
                 std::vector<pat::Jet> separated_bottoms;                 
                 separated_bottoms=ZPrimeToTPrimeAllHadProcessor::SelectSeparatedBottoms(tops_withbtag_anti, Ws, bottoms);
                 if(separated_bottoms.size()>0){
                     Tprime=ZPrimeToTPrimeAllHadProcessor::TPrimeReconstructionWtb(Ws,separated_bottoms);
                     if(Tprime.mass()>500){
                         
                        vars.FillVar("N_Sideband_top_withbtag_anti_Tops",tops_withbtag_anti.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = tops_withbtag_anti.begin() ; itJet != tops_withbtag_anti.end(); ++itJet){
                            int iJet = itJet - tops_withbtag_anti.begin();
                            vars.FillVars("Sideband_top_withbtag_anti_Tops_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_top_withbtag_anti_Tops_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_top_withbtag_anti_Ws",Ws.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = Ws.begin() ; itJet != Ws.end(); ++itJet){
                            int iJet = itJet - Ws.begin();
                            vars.FillVars("Sideband_top_withbtag_anti_Ws_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_top_withbtag_anti_Ws_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_top_withbtag_anti_Bottoms",separated_bottoms.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = separated_bottoms.begin() ; itJet != separated_bottoms.end(); ++itJet){
                            int iJet = itJet - separated_bottoms.begin();
                            vars.FillVars("Sideband_top_withbtag_anti_Bottoms_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_top_withbtag_anti_Bottoms_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("Sideband_top_withbtag_anti_Tprime_M",Tprime.mass());
                        vars.FillVar("Sideband_top_withbtag_anti_Tprime_Pt",Tprime.pt());
                        Zprime=ZPrimeToTPrimeAllHadProcessor::ZPrimeReconstructionWtb(tops_withbtag_anti, Tprime);
                        vars.FillVar("Sideband_top_withbtag_anti_Zprime_M",Zprime.mass());
                        vars.FillVar("Sideband_top_withbtag_anti_Zprime_Pt",Zprime.pt());
                    }
                 }
             }
             if(bottom_anti_candidatefound){
                 std::vector<pat::Jet> separated_bottoms_anti;                 
                 separated_bottoms_anti=ZPrimeToTPrimeAllHadProcessor::SelectSeparatedBottoms(tops_withbtag_anti, Ws, bottoms_anti);
                 if(separated_bottoms_anti.size()>0){
                     Tprime=ZPrimeToTPrimeAllHadProcessor::TPrimeReconstructionWtb(Ws,separated_bottoms_anti);
                     if(Tprime.mass()>500){
                         
                        vars.FillVar("N_Sideband_top_withbtag_anti_bottom_anti_Tops",tops_withbtag_anti.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = tops_withbtag_anti.begin() ; itJet != tops_withbtag_anti.end(); ++itJet){
                            int iJet = itJet - tops_withbtag_anti.begin();
                            vars.FillVars("Sideband_top_withbtag_anti_Tops_bottom_anti_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_top_withbtag_anti_Tops_bottom_anti_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_top_withbtag_anti_bottom_anti_Ws",Ws.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = Ws.begin() ; itJet != Ws.end(); ++itJet){
                            int iJet = itJet - Ws.begin();
                            vars.FillVars("Sideband_top_withbtag_anti_bottom_anti_Ws_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_top_withbtag_anti_bottom_anti_Ws_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_top_withbtag_anti_bottom_anti_Bottoms",separated_bottoms_anti.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = separated_bottoms_anti.begin() ; itJet != separated_bottoms_anti.end(); ++itJet){
                            int iJet = itJet - separated_bottoms_anti.begin();
                            vars.FillVars("Sideband_top_withbtag_anti_bottom_anti_Bottoms_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_top_withbtag_anti_bottom_anti_Bottoms_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("Sideband_top_withbtag_anti_bottom_anti_Tprime_M",Tprime.mass());
                        vars.FillVar("Sideband_top_withbtag_anti_bottom_anti_Tprime_Pt",Tprime.pt());
                        Zprime=ZPrimeToTPrimeAllHadProcessor::ZPrimeReconstructionWtb(tops_withbtag_anti, Tprime);
                        vars.FillVar("Sideband_top_withbtag_anti_bottom_anti_Zprime_M",Zprime.mass());
                        vars.FillVar("Sideband_top_withbtag_anti_bottom_anti_Zprime_Pt",Zprime.pt());
                    }
                 }
             }*/
         }
      }

      if(W_anti_candidatefound  && !W_candidatefound){
         if(top_candidatefound){
            ZPrimeReconstructionWtbComplete(vars,tops,Ws_anti,bottoms, bottoms_anti,top_candidatefound, false, W_candidatefound, (top_anti_candidatefound && !top_candidatefound),false, (W_anti_candidatefound  && !W_candidatefound),"Topfirst");
            ZPrimeReconstructionWtbComplete(vars,tops,Ws_anti,bottoms,bottoms_anti,top_candidatefound, false, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), false, (W_anti_candidatefound  && !W_candidatefound),"Wfirst"); 
//              std::cout<<"heredetail6"<<endl;
            /*if(bottom_candidatefound){
                 std::vector<pat::Jet> separated_bottoms_anti;                 
                 separated_bottoms=ZPrimeToTPrimeAllHadProcessor::SelectSeparatedBottoms(tops, Ws_anti, bottoms);
                 if(separated_bottoms.size()>0){
                     Tprime=ZPrimeToTPrimeAllHadProcessor::TPrimeReconstructionWtb(Ws_anti,separated_bottoms);
                     if(Tprime.mass()>500){
                         
                        vars.FillVar("N_Sideband_W_anti_Tops",tops.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = tops.begin() ; itJet != tops.end(); ++itJet){
                            int iJet = itJet - tops.begin();
                            vars.FillVars("Sideband_W_anti_Tops_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_W_anti_Tops_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_W_anti_Ws",Ws_anti.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = Ws_anti.begin() ; itJet != Ws_anti.end(); ++itJet){
                            int iJet = itJet - Ws_anti.begin();
                            vars.FillVars("Sideband_W_anti_Ws_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_W_anti_Ws_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_W_anti_Bottoms",separated_bottoms.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = separated_bottoms.begin() ; itJet != separated_bottoms.end(); ++itJet){
                            int iJet = itJet - separated_bottoms.begin();
                            vars.FillVars("Sideband_W_anti_Bottoms_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_W_anti_Bottoms_Eta",iJet,itJet->eta());
                        }
                                                 
                        vars.FillVar("Sideband_W_anti_Tprime_M",Tprime.mass());
                        vars.FillVar("Sideband_W_anti_Tprime_Pt",Tprime.pt());
                        Zprime=ZPrimeToTPrimeAllHadProcessor::ZPrimeReconstructionWtb(tops, Tprime);
                        vars.FillVar("Sideband_W_anti_Zprime_M",Zprime.mass());
                        vars.FillVar("Sideband_W_anti_Zprime_Pt",Zprime.pt());
                    }
                 }
             }
             if(bottom_anti_candidatefound){
                 std::vector<pat::Jet> separated_bottoms_anti;                 
                 separated_bottoms_anti=ZPrimeToTPrimeAllHadProcessor::SelectSeparatedBottoms(tops, Ws_anti, bottoms_anti);
                 if(separated_bottoms_anti.size()>0){
                     Tprime=ZPrimeToTPrimeAllHadProcessor::TPrimeReconstructionWtb(Ws_anti,separated_bottoms_anti);
                     if(Tprime.mass()>500){
                         
                        vars.FillVar("N_Sideband_W_anti_bottom_anti_Tops",tops.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = tops.begin() ; itJet != tops.end(); ++itJet){
                            int iJet = itJet - tops.begin();
                            vars.FillVars("Sideband_W_anti_bottom_anti_Tops_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_W_anti_bottom_anti_Tops_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_W_anti_bottom_anti_Ws",Ws_anti.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = Ws_anti.begin() ; itJet != Ws_anti.end(); ++itJet){
                            int iJet = itJet - Ws_anti.begin();
                            vars.FillVars("Sideband_W_anti_bottom_anti_Ws_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_W_anti_bottom_anti_Ws_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_W_anti_bottom_anti_Bottoms",separated_bottoms_anti.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = separated_bottoms_anti.begin() ; itJet != separated_bottoms_anti.end(); ++itJet){
                            int iJet = itJet - separated_bottoms_anti.begin();
                            vars.FillVars("Sideband_W_anti_bottom_anti_Bottoms_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_W_anti_bottom_anti_Bottoms_Eta",iJet,itJet->eta());
                        }
                                                      
                        vars.FillVar("Sideband_W_anti_bottom_anti_Tprime_M",Tprime.mass());
                        vars.FillVar("Sideband_W_anti_bottom_anti_Tprime_Pt",Tprime.pt());
                        Zprime=ZPrimeToTPrimeAllHadProcessor::ZPrimeReconstructionWtb(tops, Tprime);
                        vars.FillVar("Sideband_W_anti_bottom_anti_Zprime_M",Zprime.mass());
                        vars.FillVar("Sideband_W_anti_bottom_anti_Zprime_Pt",Zprime.pt());
                    }
                 }
             }*/
         }
         if(top_withbtag_candidatefound){
            ZPrimeReconstructionWtbComplete(vars,tops_withbtag,Ws_anti,bottoms, bottoms_anti,top_candidatefound, top_withbtag_candidatefound, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), (top_withbtag_anti_candidatefound && !top_withbtag_candidatefound), (W_anti_candidatefound  && !W_candidatefound),"Topfirst");
            ZPrimeReconstructionWtbComplete(vars,tops_withbtag,Ws_anti,bottoms,bottoms_anti,top_candidatefound, top_withbtag_candidatefound, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), (top_withbtag_anti_candidatefound && !top_withbtag_candidatefound), (W_anti_candidatefound  && !W_candidatefound),"Wfirst");
//              std::cout<<"heredetail7"<<endl;
             /*if(bottom_candidatefound){
                 std::vector<pat::Jet> separated_bottoms;
                 separated_bottoms=ZPrimeToTPrimeAllHadProcessor::SelectSeparatedBottoms(tops_withbtag, Ws_anti, bottoms);
                 if(separated_bottoms.size()>0){
                     Tprime=ZPrimeToTPrimeAllHadProcessor::TPrimeReconstructionWtb(Ws_anti,separated_bottoms);
                     if(Tprime.mass()>500){
                         
                        vars.FillVar("N_Sideband_withtopbtag_W_anti_Tops",tops_withbtag.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = tops_withbtag.begin() ; itJet != tops_withbtag.end(); ++itJet){
                            int iJet = itJet - tops_withbtag.begin();
                            vars.FillVars("Sideband_withtopbtag_W_anti_Tops_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_withtopbtag_W_anti_Tops_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_withtopbtag_W_anti_Ws",Ws_anti.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = Ws_anti.begin() ; itJet != Ws_anti.end(); ++itJet){
                            int iJet = itJet - Ws_anti.begin();
                            vars.FillVars("Sideband_withtopbtag_W_anti_Ws_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_withtopbtag_W_anti_Ws_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_withtopbtag_W_anti_Bottoms",separated_bottoms.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = separated_bottoms.begin() ; itJet != separated_bottoms.end(); ++itJet){
                            int iJet = itJet - separated_bottoms.begin();
                            vars.FillVars("Sideband_withtopbtag_W_anti_Bottoms_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_withtopbtag_W_anti_Bottoms_Eta",iJet,itJet->eta());
                        }
                                                       
                        vars.FillVar("Sideband_withtopbtag_W_anti_Tprime_M",Tprime.mass());
                        vars.FillVar("Sideband_withtopbtag_W_anti_Tprime_Pt",Tprime.pt());
                        Zprime=ZPrimeToTPrimeAllHadProcessor::ZPrimeReconstructionWtb(tops_withbtag, Tprime);
                        vars.FillVar("Sideband_withtopbtag_W_anti_Zprime_M",Zprime.mass());
                        vars.FillVar("Sideband_withtopbtag_W_anti_Zprime_Pt",Zprime.pt());
                    }
                 }
             }
             if(bottom_anti_candidatefound){
                 std::vector<pat::Jet> separated_bottoms_anti;
                 separated_bottoms_anti=ZPrimeToTPrimeAllHadProcessor::SelectSeparatedBottoms(tops_withbtag, Ws_anti, bottoms_anti);
                 if(separated_bottoms_anti.size()>0){
                     Tprime=ZPrimeToTPrimeAllHadProcessor::TPrimeReconstructionWtb(Ws_anti,separated_bottoms_anti);
                     if(Tprime.mass()>500){
                         
                        vars.FillVar("N_Sideband_withtopbtag_W_anti_bottom_anti_Tops",tops_withbtag.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = tops_withbtag.begin() ; itJet != tops_withbtag.end(); ++itJet){
                            int iJet = itJet - tops_withbtag.begin();
                            vars.FillVars("Sideband_withtopbtag_W_anti_bottom_anti_Tops_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_withtopbtag_W_anti_bottom_anti_Tops_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_withtopbtag_W_anti_bottom_anti_Ws",Ws_anti.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = Ws_anti.begin() ; itJet != Ws_anti.end(); ++itJet){
                            int iJet = itJet - Ws_anti.begin();
                            vars.FillVars("Sideband_withtopbtag_W_anti_bottom_anti_Ws_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_withtopbtag_W_anti_bottom_anti_Ws_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_withtopbtag_W_anti_bottom_anti_Bottoms",separated_bottoms_anti.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = separated_bottoms_anti.begin() ; itJet != separated_bottoms_anti.end(); ++itJet){
                            int iJet = itJet - separated_bottoms_anti.begin();
                            vars.FillVars("Sideband_withtopbtag_W_anti_bottom_anti_Bottoms_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_withtopbtag_W_anti_bottom_anti_Bottoms_Eta",iJet,itJet->eta());
                        }
                                                      
                        vars.FillVar("Sideband_withtopbtag_W_anti_bottom_anti_Tprime_M",Tprime.mass());
                        vars.FillVar("Sideband_withtopbtag_W_anti_bottom_anti_Tprime_Pt",Tprime.pt());
                        Zprime=ZPrimeToTPrimeAllHadProcessor::ZPrimeReconstructionWtb(tops_withbtag, Tprime);
                        vars.FillVar("Sideband_withtopbtag_W_anti_bottom_anti_Zprime_M",Zprime.mass());
                        vars.FillVar("Sideband_withtopbtag_W_anti_bottom_anti_Zprime_Pt",Zprime.pt());
                    }
                 }
             }*/             
         }
         if(top_anti_candidatefound && !top_candidatefound){
            ZPrimeReconstructionWtbComplete(vars,tops_anti,Ws_anti,bottoms, bottoms_anti,top_candidatefound, false, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), false, (W_anti_candidatefound  && !W_candidatefound),"Topfirst");
            ZPrimeReconstructionWtbComplete(vars,tops_anti,Ws_anti,bottoms,bottoms_anti,top_candidatefound, false, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), false, (W_anti_candidatefound  && !W_candidatefound),"Wfirst"); 
//              std::cout<<"heredetail8"<<endl;
             /*if(bottom_candidatefound){
                 std::vector<pat::Jet> separated_bottoms;
                 separated_bottoms=ZPrimeToTPrimeAllHadProcessor::SelectSeparatedBottoms(tops_anti, Ws_anti, bottoms);
                 if(separated_bottoms.size()>0){
                     Tprime=ZPrimeToTPrimeAllHadProcessor::TPrimeReconstructionWtb(Ws_anti,separated_bottoms);
                     if(Tprime.mass()>500){
                         
                        vars.FillVar("N_Sideband_top_anti_W_anti_Tops",tops_anti.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = tops_anti.begin() ; itJet != tops_anti.end(); ++itJet){
                            int iJet = itJet - tops_anti.begin();
                            vars.FillVars("Sideband_top_anti_W_anti_Tops_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_top_anti_W_anti_Tops_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_top_anti_W_anti_Ws",Ws_anti.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = Ws_anti.begin() ; itJet != Ws_anti.end(); ++itJet){
                            int iJet = itJet - Ws_anti.begin();
                            vars.FillVars("Sideband_top_anti_W_anti_Ws_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_top_anti_W_anti_Ws_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_top_anti_W_anti_Bottoms",separated_bottoms.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = separated_bottoms.begin() ; itJet != separated_bottoms.end(); ++itJet){
                            int iJet = itJet - separated_bottoms.begin();
                            vars.FillVars("Sideband_top_anti_W_anti_Bottoms_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_top_anti_W_anti_Bottoms_Eta",iJet,itJet->eta());
                        }
                                                     
                        vars.FillVar("Sideband_top_anti_W_anti_Tprime_M",Tprime.mass());
                        vars.FillVar("Sideband_top_anti_W_anti_Tprime_Pt",Tprime.pt());
                        Zprime=ZPrimeToTPrimeAllHadProcessor::ZPrimeReconstructionWtb(tops_anti, Tprime);
                        vars.FillVar("Sideband_top_anti_W_anti_Zprime_M",Zprime.mass());
                        vars.FillVar("Sideband_top_anti_W_anti_Zprime_Pt",Zprime.pt());
                    }
                 }
             }
             if(bottom_anti_candidatefound){
                 std::vector<pat::Jet> separated_bottoms_anti;
                 separated_bottoms_anti=ZPrimeToTPrimeAllHadProcessor::SelectSeparatedBottoms(tops_anti, Ws_anti, bottoms_anti);
                 if(separated_bottoms_anti.size()>0){
                     Tprime=ZPrimeToTPrimeAllHadProcessor::TPrimeReconstructionWtb(Ws_anti,separated_bottoms_anti);
                     if(Tprime.mass()>500){
                         
                        vars.FillVar("N_Sideband_top_anti_W_anti_bottom_anti_Tops",tops_anti.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = tops_anti.begin() ; itJet != tops_anti.end(); ++itJet){
                            int iJet = itJet - tops_anti.begin();
                            vars.FillVars("Sideband_top_anti_W_anti_bottom_anti_Tops_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_top_anti_W_anti_bottom_anti_Tops_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_top_anti_W_anti_bottom_anti_Ws",Ws_anti.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = Ws_anti.begin() ; itJet != Ws_anti.end(); ++itJet){
                            int iJet = itJet - Ws_anti.begin();
                            vars.FillVars("Sideband_top_anti_W_anti_bottom_anti_Ws_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_top_anti_W_anti_bottom_anti_Ws_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_top_anti_W_anti_bottom_anti_Bottoms",separated_bottoms_anti.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = separated_bottoms_anti.begin() ; itJet != separated_bottoms_anti.end(); ++itJet){
                            int iJet = itJet - separated_bottoms_anti.begin();
                            vars.FillVars("Sideband_top_anti_W_anti_bottom_anti_Bottoms_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_top_anti_W_anti_bottom_anti_Bottoms_Eta",iJet,itJet->eta());
                        }
                                                           
                        vars.FillVar("Sideband_top_anti_W_anti_bottom_anti_Tprime_M",Tprime.mass());
                        vars.FillVar("Sideband_top_anti_W_anti_bottom_anti_Tprime_Pt",Tprime.pt());
                        Zprime=ZPrimeToTPrimeAllHadProcessor::ZPrimeReconstructionWtb(tops_anti, Tprime);
                        vars.FillVar("Sideband_top_anti_W_anti_bottom_anti_Zprime_M",Zprime.mass());
                        vars.FillVar("Sideband_top_anti_W_anti_bottom_anti_Zprime_Pt",Zprime.pt());
                    }
                 }
             }*/
         }
         if(top_withbtag_anti_candidatefound && !top_withbtag_candidatefound){
            ZPrimeReconstructionWtbComplete(vars,tops_withbtag_anti,Ws_anti,bottoms, bottoms_anti,top_candidatefound, top_withbtag_candidatefound, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), (top_withbtag_anti_candidatefound && !top_withbtag_candidatefound), (W_anti_candidatefound  && !W_candidatefound),"Topfirst");
            ZPrimeReconstructionWtbComplete(vars,tops_withbtag_anti,Ws_anti,bottoms,bottoms_anti,top_candidatefound, top_withbtag_candidatefound, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), (top_withbtag_anti_candidatefound && !top_withbtag_candidatefound), (W_anti_candidatefound  && !W_candidatefound),"Wfirst"); 
//              std::cout<<"heredetail9"<<endl;
            /*if(bottom_candidatefound){
                 std::vector<pat::Jet> separated_bottoms;
                 separated_bottoms=ZPrimeToTPrimeAllHadProcessor::SelectSeparatedBottoms(tops_withbtag_anti, Ws_anti, bottoms);
                 if(separated_bottoms.size()>0){
                     Tprime=ZPrimeToTPrimeAllHadProcessor::TPrimeReconstructionWtb(Ws_anti,separated_bottoms);
                     if(Tprime.mass()>500){
                         
                        vars.FillVar("N_Sideband_top_withbtag_anti_W_anti_Tops",tops_withbtag_anti.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = tops_withbtag_anti.begin() ; itJet != tops_withbtag_anti.end(); ++itJet){
                            int iJet = itJet - tops_withbtag_anti.begin();
                            vars.FillVars("Sideband_top_withbtag_anti_W_anti_Tops_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_top_withbtag_anti_W_anti_Tops_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_top_withbtag_anti_W_anti_Ws",Ws_anti.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = Ws_anti.begin() ; itJet != Ws_anti.end(); ++itJet){
                            int iJet = itJet - Ws_anti.begin();
                            vars.FillVars("Sideband_top_withbtag_anti_W_anti_Ws_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_top_withbtag_anti_W_anti_Ws_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_top_withbtag_anti_W_anti_Bottoms",separated_bottoms.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = separated_bottoms.begin() ; itJet != separated_bottoms.end(); ++itJet){
                            int iJet = itJet - separated_bottoms.begin();
                            vars.FillVars("Sideband_top_withbtag_anti_W_anti_Bottoms_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_top_withbtag_anti_W_anti_Bottoms_Eta",iJet,itJet->eta());
                        }
                                                 
                        vars.FillVar("Sideband_top_withbtag_anti_W_anti_Tprime_M",Tprime.mass());
                        vars.FillVar("Sideband_top_withbtag_anti_W_anti_Tprime_Pt",Tprime.pt());
                        Zprime=ZPrimeToTPrimeAllHadProcessor::ZPrimeReconstructionWtb(tops_withbtag_anti, Tprime);
                        vars.FillVar("Sideband_top_withbtag_anti_W_anti_Zprime_M",Zprime.mass());
                        vars.FillVar("Sideband_top_withbtag_anti_W_anti_Zprime_Pt",Zprime.pt());
                    }
                 }
             }
             if(bottom_anti_candidatefound){
                 std::vector<pat::Jet> separated_bottoms_anti;
                 separated_bottoms_anti=ZPrimeToTPrimeAllHadProcessor::SelectSeparatedBottoms(tops_withbtag_anti, Ws_anti, bottoms_anti);
                 if(separated_bottoms_anti.size()>0){
                     Tprime=ZPrimeToTPrimeAllHadProcessor::TPrimeReconstructionWtb(Ws_anti,separated_bottoms_anti);
                     if(Tprime.mass()>500){
                         
                        vars.FillVar("N_Sideband_top_withbtag_anti_W_anti_bottom_anti_Tops",tops_withbtag_anti.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = tops_withbtag_anti.begin() ; itJet != tops_withbtag_anti.end(); ++itJet){
                            int iJet = itJet - tops_withbtag_anti.begin();
                            vars.FillVars("Sideband_top_withbtag_anti_W_anti_bottom_anti_Tops_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_top_withbtag_anti_W_anti_bottom_anti_Tops_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_top_withbtag_anti_W_anti_bottom_anti_Ws",Ws_anti.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = Ws_anti.begin() ; itJet != Ws_anti.end(); ++itJet){
                            int iJet = itJet - Ws_anti.begin();
                            vars.FillVars("Sideband_top_withbtag_anti_W_anti_bottom_anti_Ws_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_top_withbtag_anti_W_anti_bottom_anti_Ws_Eta",iJet,itJet->eta());
                        }
                        
                        vars.FillVar("N_Sideband_top_withbtag_anti_W_anti_bottom_anti_Bottoms",separated_bottoms_anti.size());
                        for(std::vector<pat::Jet>::const_iterator itJet = separated_bottoms_anti.begin() ; itJet != separated_bottoms_anti.end(); ++itJet){
                            int iJet = itJet - separated_bottoms_anti.begin();
                            vars.FillVars("Sideband_top_withbtag_anti_W_anti_bottom_anti_Bottoms_Pt",iJet,itJet->pt());
                            vars.FillVars("Sideband_top_withbtag_anti_W_anti_bottom_anti_Bottoms_Eta",iJet,itJet->eta());
                        }
                                                        
                        vars.FillVar("Sideband_top_withbtag_anti_W_anti_bottom_anti_Tprime_M",Tprime.mass());
                        vars.FillVar("Sideband_top_withbtag_anti_W_anti_bottom_anti_Tprime_Pt",Tprime.pt());
                        Zprime=ZPrimeToTPrimeAllHadProcessor::ZPrimeReconstructionWtb(tops_withbtag_anti, Tprime);
                        vars.FillVar("Sideband_top_withbtag_anti_W_anti_bottom_anti_Zprime_M",Zprime.mass());
                        vars.FillVar("Sideband_top_withbtag_anti_W_anti_bottom_anti_Zprime_Pt",Zprime.pt());
                    }
                 }
             }*/
         }          
     }
  }
  
  
/*  
///TPrime reconstruction ttZ-channel
  if ((Z_candidatefound || Z_anti_candidatefound) && (top_candidatefound || top_anti_candidatefound || top_withbtag_candidatefound || top_withbtag_anti_candidatefound){
      if(Z_candidatefound){
          if (tops.size()>1){
              Tprime_ttZ_t1Z=tops[0].p4()+Zs[0].p4();
              Tprime_ttZ_t2Z=tops[1].p4()+Zs[0].p4();
              if(Tprime_ttZ_t1Z.mass()>500){
                Tprime_ttZ_t1Z_candidatefound=true;
              }
              if(Tprime_ttZ_t2Z.mass()>500){
                Tprime_ttZ_t2Z_candidatefound=true;
              }
          }
          if (tops_anti.size()>1){
              Tprime_2tantiZ_tanti1Z=tops_anti[0].p4()+Zs[0].p4();
              Tprime_2tantiZ_tanti2Z=tops_anti[1].p4()+Zs[0].p4();
              if(Tprime_2tantiZ_tanti1Z.mass()>500){
                Tprime_2tantiZ_tanti1Z_candidatefound=true;
              }
              if(Tprime_2tantiZ_tanti2Z.mass()>500){
                Tprime_2tantiZ_tanti2Z_candidatefound=true;
              }
          }
          if (tops.size()=1 && top_anti_candidatefound){
              Tprime_tantitZ_tantiZ=tops_anti[0].p4()+Zs[0].p4();
              Tprime_tantitZ_tZ=tops[0].p4()+Zs[0].p4();
              if(Tprime_tantitZ_tantiZ.mass()>500){
                Tprime_tantitZ_tantiZ_candidatefound=true;
              }
              if(Tprime_tantitZ_tZ.mass()>500){
                Tprime_tantitZ_tZ_candidatefound=true;
              }
          }
      }
      if (Z_anti_candidatefound){
          if (tops.size()>1){
              Tprime_ttZanti_t1Zanti=tops[0].p4()+Zs[0].p4();
              Tprime_ttZanti_t2Zanti=tops[1].p4()+Zs[0].p4();
              if(Tprime_ttZanti_t1Zanti.mass()>500){
                Tprime_ttZanti_t1Zanti_candidatefound=true;
              }
              if(Tprime_ttZanti_t2Zanti.mass()>500){
                Tprime_ttZanti_t2Zanti_candidatefound=true;
              }
          }
          if (tops_anti.size()>1){
              Tprime_2tantiZanti_tanti1Zanti=tops_anti[0].p4()+Zs[0].p4();
              Tprime_2tantiZanti_tanti2Zanti=tops_anti[1].p4()+Zs[0].p4();
              if(Tprime_2tantiZanti_tanti1Zanti.mass()>500){
                Tprime_2tantiZanti_tanti1Zanti_candidatefound=true;
              }
              if(Tprime_2tantiZanti_tanti1Zanti.mass()>500){
                Tprime_2tantiZanti_tanti2Zanti_candidatefound=true;
              }    
          }
          if (tops.size()=1 && top_anti_candidatefound){
              Tprime_tantitZanti_tantiZanti=tops_anti[0].p4()+Zs[0].p4();
              Tprime_tantitZanti_tZanti=tops[0].p4()+Zs[0].p4();
              if(Tprime_tantitZanti_tantiZanti.mass()>500){
                Tprime_tantitZanti_tantiZanti_candidatefound=true;
              }
              if(Tprime_tantitZanti_tZanti.mass()>500){
                Tprime_tantitZanti_tZanti_candidatefound=true;
              }
          }
      }
  }  

///TPrime reconstruction ttH-channel
  if ((Higgs_candidatefound || Higgs_anti_candidatefound) && (top_candidatefound || top_anti_candidatefound){
      if(Higgs_candidatefound){
          if (tops.size()>1){
              Tprime_t1H=tops[0].p4()+Higgs[0].p4();
              Tprime_t2H=tops[1].p4()+Higgs[0].p4();
              Tprime_tH_candidatefound=true;
          }
          if (tops_anti.size()>1){
              Tprime_t_anti_H_candidatefound=true;
              Tprime_tanti1H=tops_anti[0].p4()+Higgs[0].p4();
              Tprime_tanti2H=tops_anti[1].p4()+Higgs[0].p4();
          }
      }
      if (Higgs_anti_candidatefound){
          
      }
  }
*/

/*
    std::cout<<"here11"<<endl;

///ZPrime reconstructions Wtb-channel
  if (top_candidatefound && Tprime_candidatefound && BoostedUtils::DeltaR(bottoms[0].p4(),Ws[0].p4())>1.2 && BoostedUtils::DeltaR(bottoms[0].p4(), tops[0].p4())>1.2){
      Zprime=Tprime+tops[0].p4();
      vars.FillVar("Zprime_M",Zprime.mass());
      vars.FillVar("Zprime_Pt",Zprime.pt());
  }
      std::cout<<"heredetail1"<<endl;

  if (top_withbtag_candidatefound && Tprime_candidatefound && BoostedUtils::DeltaR(bottoms[0].p4(),Ws[0].p4())>1.2 && BoostedUtils::DeltaR(bottoms[0].p4(), tops_withbtag[0].p4())>1.2){
      Zprime_withtopbtag=Tprime+tops_withbtag[0].p4();
      vars.FillVar("Zprime_withtopbtag_M",Zprime_withtopbtag.mass());
      vars.FillVar("Zprime_withtopbtag_Pt",Zprime_withtopbtag.pt());
  }  
        std::cout<<"heredetail2"<<endl;

  if (top_anti_candidatefound && Tprime_candidatefound && BoostedUtils::DeltaR(bottoms[0].p4(),Ws[0].p4())>1.2 && BoostedUtils::DeltaR(bottoms[0].p4(), tops_anti[0].p4())>1.2){
      Zprime_top_anti=Tprime+tops_anti[0].p4();
      vars.FillVar("Zprime_top_anti_M",Zprime_top_anti.mass());
      vars.FillVar("Zprime_top_anti_Pt",Zprime_top_anti.pt());
  }
        std::cout<<"heredetail3"<<endl;

  if (top_anti_candidatefound && Tprime_W_anti_candidatefound && BoostedUtils::DeltaR(bottoms[0].p4(),Ws_anti[0].p4())>1.2 && BoostedUtils::DeltaR(bottoms[0].p4(), tops_anti[0].p4())>1.2){
      Zprime_top_anti_W_anti=Tprime_W_anti+tops_anti[0].p4();
      vars.FillVar("Zprime_top_anti_W_anti_M",Zprime_top_anti_W_anti.mass());
      vars.FillVar("Zprime_top_anti_W_anti_Pt",Zprime_top_anti_W_anti.pt());
  } 
        std::cout<<"heredetail4"<<endl;

  if (top_anti_candidatefound && Tprime_bottom_anti_candidatefound && BoostedUtils::DeltaR(bottoms_anti[0].p4(),Ws[0].p4())>1.2 && BoostedUtils::DeltaR(bottoms_anti[0].p4(), tops_anti[0].p4())>1.2){
      Zprime_top_anti_bottom_anti=Tprime_bottom_anti+tops_anti[0].p4();
      vars.FillVar("Zprime_top_anti_bottom_anti_M",Zprime_top_anti_bottom_anti.mass());
      vars.FillVar("Zprime_top_anti_bottom_anti_Pt",Zprime_top_anti_bottom_anti.pt());
  }
        std::cout<<"heredetail5"<<endl;

  if (top_anti_candidatefound && Tprime_W_anti_bottom_anti_candidatefound && BoostedUtils::DeltaR(bottoms_anti[0].p4(),Ws_anti[0].p4())>1.2 && BoostedUtils::DeltaR(bottoms_anti[0].p4(), tops_anti[0].p4())>1.2){
      Zprime_top_anti_W_anti_bottom_anti=Tprime_W_anti_bottom_anti+tops_anti[0].p4();
      vars.FillVar("Zprime_top_anti_W_anti_bottom_anti_M",Zprime_top_anti_W_anti_bottom_anti.mass());
      vars.FillVar("Zprime_top_anti_W_anti_bottom_anti_Pt",Zprime_top_anti_W_anti_bottom_anti.pt());
  }  
        std::cout<<"heredetail6"<<endl;

  if (top_withbtag_anti_candidatefound && Tprime_candidatefound && BoostedUtils::DeltaR(bottoms[0].p4(),Ws[0].p4())>1.2 && BoostedUtils::DeltaR(bottoms[0].p4(), tops_withbtag_anti[0].p4())>1.2){
      Zprime_top_withbtag_anti=Tprime+tops_withbtag_anti[0].p4();
      vars.FillVar("Zprime_top_withbtag_anti_M",Zprime_top_withbtag_anti.mass());
      vars.FillVar("Zprime_top_withbtag_anti_Pt",Zprime_top_withbtag_anti.pt());
  }
          std::cout<<"heredetail7"<<endl;

  if (top_withbtag_anti_candidatefound && Tprime_W_anti_candidatefound && BoostedUtils::DeltaR(bottoms[0].p4(),Ws_anti[0].p4())>1.2 && BoostedUtils::DeltaR(bottoms[0].p4(), tops_withbtag_anti[0].p4())>1.2){
      Zprime_top_withbtag_anti_W_anti=Tprime_W_anti+tops_withbtag_anti[0].p4();
      vars.FillVar("Zprime_top_withbtag_anti_W_anti_M",Zprime_top_withbtag_anti_W_anti.mass());
      vars.FillVar("Zprime_top_withbtag_anti_W_anti_Pt",Zprime_top_withbtag_anti_W_anti.pt());
  } 
          std::cout<<"heredetail8"<<endl;

  if (top_withbtag_anti_candidatefound && Tprime_bottom_anti_candidatefound && BoostedUtils::DeltaR(bottoms_anti[0].p4(),Ws[0].p4())>1.2 && BoostedUtils::DeltaR(bottoms_anti[0].p4(), tops_withbtag_anti[0].p4())>1.2){
      Zprime_top_withbtag_anti_bottom_anti=Tprime_bottom_anti+tops_withbtag_anti[0].p4();
      vars.FillVar("Zprime_top_withbtag_anti_bottom_anti_M",Zprime_top_withbtag_anti_bottom_anti.mass());
      vars.FillVar("Zprime_top_withbtag_anti_bottom_anti_Pt",Zprime_top_withbtag_anti_bottom_anti.pt());
  }
          std::cout<<"heredetail9"<<endl;

  if (top_withbtag_anti_candidatefound && Tprime_W_anti_bottom_anti_candidatefound && BoostedUtils::DeltaR(bottoms_anti[0].p4(),Ws_anti[0].p4())>1.2 && BoostedUtils::DeltaR(bottoms_anti[0].p4(), tops_withbtag_anti[0].p4())>1.2){
      Zprime_top_withbtag_anti_W_anti_bottom_anti=Tprime_W_anti_bottom_anti+tops_withbtag_anti[0].p4();
      vars.FillVar("Zprime_top_withbtag_anti_W_anti_bottom_anti_M",Zprime_top_withbtag_anti_W_anti_bottom_anti.mass());
      vars.FillVar("Zprime_top_withbtag_anti_W_anti_bottom_anti_Pt",Zprime_top_withbtag_anti_W_anti_bottom_anti.pt());
  }  
          std::cout<<"heredetail10"<<endl;

  if (top_candidatefound && Tprime_W_anti_candidatefound && BoostedUtils::DeltaR(bottoms[0].p4(),Ws_anti[0].p4())>1.2 && BoostedUtils::DeltaR(bottoms[0].p4(), tops[0].p4())>1.2){
      Zprime_W_anti=Tprime_bottom_anti+tops[0].p4();
      vars.FillVar("Zprime_W_anti_M",Zprime_W_anti.mass());
      vars.FillVar("Zprime_W_anti_Pt",Zprime_W_anti.pt());
  }
          std::cout<<"heredetail11"<<endl;

  if (top_withbtag_candidatefound && Tprime_W_anti_candidatefound && BoostedUtils::DeltaR(bottoms[0].p4(),Ws_anti[0].p4())>1.2 && BoostedUtils::DeltaR(bottoms[0].p4(), tops_withbtag[0].p4())>1.2){
      Zprime_withtopbtag_W_anti=Tprime_W_anti+tops_withbtag[0].p4();
      vars.FillVar("Zprime_withtopbtag_W_anti_M",Zprime_withtopbtag_W_anti.mass());
      vars.FillVar("Zprime_withtopbtag_W_anti_Pt",Zprime_withtopbtag_W_anti.pt());
  } 
          std::cout<<"heredetail12"<<endl;

  if (top_candidatefound && Tprime_bottom_anti_candidatefound && BoostedUtils::DeltaR(bottoms_anti[0].p4(),Ws[0].p4())>1.2 && BoostedUtils::DeltaR(bottoms_anti[0].p4(), tops[0].p4())>1.2){
      Zprime_bottom_anti=Tprime_bottom_anti+tops[0].p4();
      vars.FillVar("Zprime_bottom_anti_M",Zprime_bottom_anti.mass());
      vars.FillVar("Zprime_bottom_anti_Pt",Zprime_bottom_anti.pt());
  }
          std::cout<<"heredetail613"<<endl;

  if (top_withbtag_candidatefound && Tprime_bottom_anti_candidatefound && BoostedUtils::DeltaR(bottoms_anti[0].p4(),Ws[0].p4())>1.2 && BoostedUtils::DeltaR(bottoms_anti[0].p4(), tops_withbtag[0].p4())>1.2){
      Zprime_withtopbtag_bottom_anti=Tprime_bottom_anti+tops_withbtag[0].p4();
      vars.FillVar("Zprime_withtopbtag_bottom_anti_M",Zprime_withtopbtag_bottom_anti.mass());
      vars.FillVar("Zprime_withtopbtag_bottom_anti_Pt",Zprime_withtopbtag_bottom_anti.pt());
  }  
          std::cout<<"heredetail14"<<endl;

  if (top_candidatefound && Tprime_W_anti_bottom_anti_candidatefound && BoostedUtils::DeltaR(bottoms_anti[0].p4(),Ws_anti[0].p4())>1.2 && BoostedUtils::DeltaR(bottoms_anti[0].p4(), tops[0].p4())>1.2){
      Zprime_W_anti_bottom_anti=Tprime_W_anti_bottom_anti+tops[0].p4();
      vars.FillVar("Zprime_W_anti_bottom_anti_M",Zprime_W_anti_bottom_anti.mass());
      vars.FillVar("Zprime_W_anti_bottom_anti_Pt",Zprime_W_anti_bottom_anti.pt());
  }
          std::cout<<"heredetail15"<<endl;

  if (top_withbtag_candidatefound && Tprime_W_anti_bottom_anti_candidatefound && BoostedUtils::DeltaR(bottoms_anti[0].p4(),Ws_anti[0].p4())>1.2 && BoostedUtils::DeltaR(bottoms_anti[0].p4(), tops_withbtag[0].p4())>1.2){
      Zprime_withtopbtag_W_anti_bottom_anti=Tprime_W_anti_bottom_anti+tops_withbtag[0].p4();
      vars.FillVar("Zprime_withtopbtag_W_anti_bottom_anti_M",Zprime_withtopbtag_W_anti_bottom_anti.mass());
      vars.FillVar("Zprime_withtopbtag_W_anti_bottom_anti_Pt",Zprime_withtopbtag_W_anti_bottom_anti.pt());
  } 
  
  if (top_candidatefound && Tprime_no_bottom_candidatefound && BoostedUtils::DeltaR(no_bottoms[0].p4(),Ws[0].p4())>1.2 && BoostedUtils::DeltaR(no_bottoms[0].p4(), tops[0].p4())>1.2){
      Zprime_no_bottom=Tprime_no_bottom+tops[0].p4();
      vars.FillVar("Zprime_no_bottom_M",Zprime_no_bottom.mass());
      vars.FillVar("Zprime_no_bottom_Pt",Zprime_no_bottom.pt());
  }
  if (top_withbtag_candidatefound && Tprime_no_bottom_candidatefound && BoostedUtils::DeltaR(no_bottoms[0].p4(),Ws[0].p4())>1.2 && BoostedUtils::DeltaR(no_bottoms[0].p4(), tops_withbtag[0].p4())>1.2){
      Zprime_withtopbtag_no_bottom=Tprime_no_bottom+tops_withbtag[0].p4();
      vars.FillVar("Zprime_withtopbtag_no_bottom_M",Zprime_withtopbtag_no_bottom.mass());
      vars.FillVar("Zprime_withtopbtag_no_bottom_Pt",Zprime_withtopbtag_no_bottom.pt());
  }  
    std::cout<<"here12"<<endl;
*/    
    
/*
///ZPrime reconstructions Ztt-channel
  if(Tprime_ttZ_t1Z_candidatefound){
      Zprime_ttZ_t1Z=Tprime_ttZ_t1Z+tops[1].p4();
      vars.FillVar("Zprime_ttZ_t1Z_M",Zprime_ttZ_t1Z.mass());
  }
  if(Tprime_ttZ_t2Z_candidatefound){
      Tprime_ttZ_t2Z=Tprime_ttZ_t2Z+tops[0].p4();
      vars.FillVar("Tprime_ttZ_t2Z_M",Tprime_ttZ_t2Z.mass());
  }
  if(Tprime_2tantiZ_tanti1Z_candidatefound){
      Zprime_2tantiZ_tanti1Z=Tprime_2tantiZ_tanti1Z+tops_anti[1].p4();
      vars.FillVar("Zprime_2tantiZ_tanti1Z_M",Zprime_2tantiZ_tanti1Z.mass());
  }
  if(Tprime_2tantiZ_tanti2Z_candidatefound){
      Zprime_2tantiZ_tanti2Z=Tprime_2tantiZ_tanti2Z+tops_anti[0].p4();
      vars.FillVar("Zprime_2tantiZ_tanti2Z_M",Zprime_2tantiZ_tanti2Z.mass());
  }
  if(Tprime_tantitZ_tantiZ_candidatefound){
      Zprime_tantitZ_tantiZ=Tprime_tantitZ_tantiZ+tops[0].p4();
      vars.FillVar("Zprime_tantitZ_tantiZ_M",Zprime_tantitZ_tantiZ.mass());
  }
  
  if(Tprime_tantitZanti_tZanti_candidatefound){
      Zprime_tantitZanti_tZanti=Tprime_tantitZanti_tZanti+tops_anti[0].p4();
      vars.FillVar("Zprime_tantitZanti_tZanti",Zprime_tantitZanti_tZanti.mass());
  }
  if(Tprime_ttZanti_t1Zanti_candidatefound){
      Zprime_ttZanti_t1Zanti=Tprime_ttZanti_t1Zanti+tops[1].p4();
      vars.FillVar("Zprime_ttZanti_t1Zanti_M",Zprime_ttZanti_t1Zanti.mass());
  }
  if(Tprime_ttZanti_t2Zanti_candidatefound){
      Zprime_ttZanti_t2Zanti=Tprime_ttZanti_t2Zanti+tops[0].p4();
      vars.FillVar("Zprime_ttZanti_t2Zanti_M",Zprime_ttZanti_t2Zanti.mass());
  }
  if(Tprime_2tantiZanti_tanti1Zanti_candidatefound){
      Zprime_2tantiZanti_tanti1Zanti=Tprime_2tantiZanti_tanti1Zanti+tops_anti[1].p4();
      vars.FillVar("Zprime_2tantiZanti_tanti1Zanti_M",Zprime_2tantiZanti_tanti1Zanti.mass());
  }
  if(Tprime_2tantiZanti_tanti2Zanti_candidatefound){
      Zprime_2tantiZanti_tanti2Zanti=Tprime_2tantiZanti_tanti2Zanti+tops_anti[0].p4();
      vars.FillVar("Zprime_2tantiZanti_tanti2Zanti_M",Zprime_2tantiZanti_tanti2Zanti.mass());
  }
  if(Tprime_tantitZanti_tantiZanti_candidatefound){
      Zprime_tantitZanti_tantiZanti=Tprime_tantitZanti_tantiZanti+tops[0].p4();
      vars.FillVar("Zprime_tantitZanti_tantiZanti_M",Zprime_tantitZanti_tantiZanti.mass());
  }
  if(Tprime_tantitZanti_tZanti_candidatefound){
      Zprime_tantitZanti_tZanti=Tprime_tantitZanti_tZanti+tops_anti[0].p4();
      vars.FillVar("Zprime_tantitZanti_tZanti",Zprime_tantitZanti_tZanti.mass());
  }  
  
*/








///Misstag rate & tag efficiency
  
  if (input.zprimetotprimeallhad.IsFilled() && input.selectedJetsAK8.size()>0){
    for(std::vector<pat::Jet>::const_iterator itJet=input.selectedJetsAK8.begin(); itJet != input.selectedJetsAK8.end(); ++itJet){
        int iJet = itJet - input.selectedJetsAK8.begin();

        
        float minDr_TopZprime = -999;
        float minDr_GenB_Top = -999;
        float minDr_GenW_Top = -999;
        float minDr_bfromTPrime = -999;
        float minDr_GenTop_bfromTPrime=-999;
        float minDr_GenWfromTPrime_bfromTPrime=-999;
        float minDr_WfromTPrime = -999;
        float minDr_GenTop_WfromTPrime=-999;
        float minDr_GenbfromTPrime_WfromTPrime=-999;

        float minDr_TopBG = -999;
        float minDr_BottomBG = -999;
        float minDr_WBG = -999;

        for(size_t j=0;j<TopZprime.size();j++){
            float Dr_TopZprime_temp = BoostedUtils::DeltaR(TopZprime[j].p4(),itJet->p4());
                if(Dr_TopZprime_temp>0 && Dr_TopZprime_temp<abs(minDr_TopZprime)){
                    minDr_TopZprime = Dr_TopZprime_temp;
                }
        }
        for(size_t j=0;j<bfromTPrime.size();j++){   
            float Dr_B_temp = BoostedUtils::DeltaR(bfromTPrime[j].p4(),itJet->p4());
                if(Dr_B_temp>0 && Dr_B_temp<abs(minDr_bfromTPrime)){
                    minDr_bfromTPrime = Dr_B_temp;
                }
        }        
        for(size_t j=0;j<WfromTPrime.size();j++){
            float Dr_W_temp = BoostedUtils::DeltaR(WfromTPrime[j].p4(),itJet->p4());
                if(Dr_W_temp>0 && Dr_W_temp<abs(minDr_WfromTPrime)){
                    minDr_WfromTPrime = Dr_W_temp;
                }            
        }
        for(size_t j=0;j<TopBG.size();j++){
            float Dr_TopBG_temp = BoostedUtils::DeltaR(TopBG[j].p4(),itJet->p4());
                if(Dr_TopBG_temp>0 && Dr_TopBG_temp<abs(minDr_TopBG)){
                    minDr_TopBG = Dr_TopBG_temp;
                }
        }         
        for(size_t j=0;j<BottomBG.size();j++){
            float Dr_BottomBG_temp = BoostedUtils::DeltaR(BottomBG[j].p4(),itJet->p4());
                if(Dr_BottomBG_temp>0 && Dr_BottomBG_temp<abs(minDr_BottomBG)){
                    minDr_BottomBG = Dr_BottomBG_temp;
                }
        }
        for(size_t j=0;j<WBG.size();j++){
            float Dr_WBG_temp = BoostedUtils::DeltaR(WBG[j].p4(),itJet->p4());
                if(Dr_WBG_temp>0 && Dr_WBG_temp<abs(minDr_WBG)){
                    minDr_WBG = Dr_WBG_temp;
                }
        }
//         std::cout<<"AK8_minDr_TopZprime: "<<minDr_TopZprime<<endl;
//         std::cout<<"AK8_minDr_bfromTPrime: "<<minDr_bfromTPrime<<endl;
//         std::cout<<"AK8_minDr_WfromTPrime: "<<minDr_WfromTPrime<<endl;
//         std::cout<<"AK8_minDr_TopBG: "<<minDr_TopBG<<endl;
//         std::cout<<"AK8_minDr_BottomBG: "<<minDr_BottomBG<<endl;
//         std::cout<<"AK8_minDr_WBG: "<<minDr_WBG<<endl;
                    
        if(abs(minDr_TopZprime)<999) vars.FillVars("packedPatJetsAK8PFCHSSoftDrop_Dr_Top",iJet,minDr_TopZprime);
        if(abs(minDr_GenB_Top)<999) vars.FillVars("packedPatJetsAK8PFCHSSoftDrop_Dr_GenB_Top",iJet,minDr_GenB_Top);
        if(abs(minDr_GenW_Top)<999) vars.FillVars("packedPatJetsAK8PFCHSSoftDrop_Dr_GenW_Top",iJet,minDr_GenW_Top);
        if(abs(minDr_bfromTPrime)<999) vars.FillVars("packedPatJetsAK8PFCHSSoftDrop_Dr_bfromTPrime",iJet,minDr_bfromTPrime);
        if(abs(minDr_GenTop_bfromTPrime)<999) vars.FillVars("packedPatJetsAK8PFCHSSoftDrop_Dr_GenTop_bfromTPrime",iJet,minDr_GenTop_bfromTPrime);
        if(abs(minDr_GenWfromTPrime_bfromTPrime)<999) vars.FillVars("packedPatJetsAK8PFCHSSoftDrop_Dr_GenWfromTPrime_bfromTPrime",iJet,minDr_GenWfromTPrime_bfromTPrime);
        if(abs(minDr_WfromTPrime)<999) vars.FillVars("packedPatJetsAK8PFCHSSoftDrop_Dr_WfromTPrime",iJet,minDr_WfromTPrime);
        if(abs(minDr_GenTop_WfromTPrime)<999) vars.FillVars("packedPatJetsAK8PFCHSSoftDrop_Dr_GenTop_WfromTPrime",iJet,minDr_GenTop_WfromTPrime);
        if(abs(minDr_GenbfromTPrime_WfromTPrime)<999) vars.FillVars("packedPatJetsAK8PFCHSSoftDrop_Dr_GenbfromTPrime_WfromTPrime",iJet,minDr_GenbfromTPrime_WfromTPrime);        
        if(abs(minDr_TopBG)<999) vars.FillVars("packedPatJetsAK8PFCHSSoftDrop_Dr_TopBG",iJet,minDr_TopBG);
        if(abs(minDr_BottomBG)<999) vars.FillVars("packedPatJetsAK8PFCHSSoftDrop_Dr_BottomBG",iJet,minDr_BottomBG);
        if(abs(minDr_WBG)<999) vars.FillVars("packedPatJetsAK8PFCHSSoftDrop_Dr_WBG",iJet,minDr_WBG);
        
        if(itJet->pt()>200 && abs(itJet->eta())<2.4){
                AK8_W_candidates.push_back(*itJet);
                
                //vars.FillVars("AK8_W_misstagged_candidates_eta",iJet,itJet->pt());
                //vars.FillVars("AK8_W_misstagged_candidates_eta",iJet,itJet->eta());
                
                if(abs(minDr_WBG)>0.8 && abs(minDr_WfromTPrime)>0.8){
                    AK8_W_misstag_candidates.push_back(*itJet);
//                     std::cout<<"AK8 W misstag candidate found with "<<minDr_WBG<<"  "<<minDr_WfromTPrime<<endl;
                    if(itJet->userFloat("NjettinessAK8CHS:tau3")>0 && itJet->userFloat("NjettinessAK8CHS:tau2")>0 && itJet->userFloat("NjettinessAK8CHS:tau1")>0 && itJet->userFloat("NjettinessAK8CHS:tau3")/itJet->userFloat("NjettinessAK8CHS:tau2")<0.6 && 70<itJet->userFloat("ak8PFJetsCHSSoftDropMass") && itJet->userFloat("ak8PFJetsCHSSoftDropMass")<100){
                        misstagged_W.push_back(*itJet);
//                         cout<<"found misstagged W"<<endl;
                        //vars.FillVars("misstagged_W_pt",iJet,itJet->pt());
                        //vars.FillVars("misstagged_W_eta",iJet,itJet->eta());
                    } else{
                        tagged_W_anti.push_back(*itJet);
//                         cout<<"found tagged W anti"<<endl;
                    }
                } else {
                    AK8_W_tag_candidates.push_back(*itJet);
//                     std::cout<<"AK8 W tag candidate found"<<endl;
                    if(itJet->userFloat("NjettinessAK8CHS:tau3")>0 && itJet->userFloat("NjettinessAK8CHS:tau2")>0 && itJet->userFloat("NjettinessAK8CHS:tau1")>0 && itJet->userFloat("NjettinessAK8CHS:tau3")/itJet->userFloat("NjettinessAK8CHS:tau2")<0.6 && 70<itJet->userFloat("ak8PFJetsCHSSoftDropMass") && itJet->userFloat("ak8PFJetsCHSSoftDropMass")<100){
                        tagged_W.push_back(*itJet);
//                         cout<<"found tagged W"<<endl;
                    } else {
                        misstagged_W_anti.push_back(*itJet);
//                         cout<<"found misstagged W anti"<<endl;
                    }
                }
                if (itJet->pt()>400){
                    AK8_top_candidates.push_back(*itJet);
                    //vars.FillVars("AK8_top_misstagged_candidates_pt",iJet,itJet->pt());
                    //vars.FillVars("AK8_top_misstagged_candidates_eta",iJet,itJet->eta());
                    if(abs(minDr_TopBG)>0.8 && abs(minDr_TopZprime)>0.8){
                        AK8_top_misstag_candidates.push_back(*itJet);
//                         std::cout<<"AK8 top misstag candidate found"<<endl;
                        if (itJet->userFloat("NjettinessAK8CHS:tau3")>0 && itJet->userFloat("NjettinessAK8CHS:tau2")>0 && itJet->userFloat("NjettinessAK8CHS:tau1")>0 && itJet->userFloat("NjettinessAK8CHS:tau3")/itJet->userFloat("NjettinessAK8CHS:tau2")<0.86 && 110<itJet->userFloat("ak8PFJetsCHSSoftDropMass") && itJet->userFloat("ak8PFJetsCHSSoftDropMass")<210){
                            misstagged_top.push_back(*itJet);
//                             cout<<"found misstagged t"<<endl;
                        //vars.FillVars("misstagged_top_pt",iJet,itJet->pt());
                        //vars.FillVars("misstagged_top_eta",iJet,itJet->eta());
                    
                            double max_subjet_csv_v2=-10;
                            auto const & names = itJet->subjets("SoftDrop");
                            for( auto const & itsubJet : names ){
                                if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>max_subjet_csv_v2){
                                max_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
                                }
                            }   
                            if (max_subjet_csv_v2>0.8){
                                misstagged_top_withbtag.push_back(*itJet);
//                                 cout<<"found misstagged t"<<endl;
                                //vars.FillVars("misstagged_top_withbtag_pt",iJet,itJet->pt());
                                //vars.FillVars("misstagged_top_withbtag_eta",iJet,itJet->eta());
                            } else {
                                tagged_top_withbtag_anti.push_back(*itJet);
                            }
                        } else {
                            tagged_top_anti.push_back(*itJet);
                            tagged_top_withbtag_anti.push_back(*itJet);
                        }
                    } else {
                        AK8_top_tag_candidates.push_back(*itJet);
//                         std::cout<<"AK8 top tag candidate found"<<endl;
                        if(itJet->userFloat("NjettinessAK8CHS:tau3")>0 && itJet->userFloat("NjettinessAK8CHS:tau2")>0 && itJet->userFloat("NjettinessAK8CHS:tau1")>0 && itJet->userFloat("NjettinessAK8CHS:tau3")/itJet->userFloat("NjettinessAK8CHS:tau2")<0.86 && 110<itJet->userFloat("ak8PFJetsCHSSoftDropMass") && itJet->userFloat("ak8PFJetsCHSSoftDropMass")<210){
                            tagged_top.push_back(*itJet);
                            
                            double max_subjet_csv_v2=-10;
                            auto const & names = itJet->subjets("SoftDrop");
                            for( auto const & itsubJet : names ){
                                if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>max_subjet_csv_v2){
                                max_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
                                }
                            }   
                            if (max_subjet_csv_v2>0.8){
                                tagged_top_withbtag.push_back(*itJet);
                                //vars.FillVars("misstagged_top_withbtag_pt",iJet,itJet->pt());
                                //vars.FillVars("misstagged_top_withbtag_eta",iJet,itJet->eta());
                            } else {
                                misstagged_top_withbtag_anti.push_back(*itJet);
                            }
                        } else {
                            misstagged_top_anti.push_back(*itJet);
                            misstagged_top_withbtag_anti.push_back(*itJet);
                        }
                    }
                }
        }
    }
  }

  for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin() ; itJet != input.selectedJets.end(); ++itJet){
    int iJet = itJet - input.selectedJets.begin();
    if(input.zprimetotprimeallhad.IsFilled()){
        float minDr_bfromTPrime = -999;    
        float minDr_bfromBG = -999;
        if (itJet->pt()>100 && abs(itJet->eta())<2.4){
            //N_AK4_bottom_misstag_candidates+=1;
            AK4_bottom_candidates.push_back(*itJet);
            //vars.FillVars("AK4_bottom_misstagged_candidates_pt",iJet,itJet->pt());
            //vars.FillVars("AK4_bottom_misstagged_candidates_eta",iJet,itJet->eta());
            
            for(size_t j=0;j<bfromTPrime.size();j++){   
                float Dr_B_temp = BoostedUtils::DeltaR(bfromTPrime[j].p4(),itJet->p4());
                if(Dr_B_temp>0 && Dr_B_temp<abs(minDr_bfromTPrime)){
                    minDr_bfromTPrime = Dr_B_temp;
                }
            }        
            for(size_t j=0;j<BottomBG.size();j++){   
                float Dr_B_temp = BoostedUtils::DeltaR(BottomBG[j].p4(),itJet->p4());
                if(Dr_B_temp>0 && Dr_B_temp<abs(minDr_bfromBG)){
                    minDr_bfromBG = Dr_B_temp;
                }
            }
            if(abs(minDr_bfromTPrime)<999) vars.FillVars("Jet_Dr_bfromTPrime",iJet,minDr_bfromTPrime);
            if(abs(minDr_bfromBG)<999) vars.FillVars("Jet_Dr_bfromBG",iJet,minDr_bfromBG);
            
            if (abs(minDr_bfromBG)>0.2 && abs(minDr_bfromTPrime)>0.2){
                AK4_bottom_misstag_candidates.push_back(*itJet);
//                 std::cout<<"AK4 bottom misstag candidate found"<<endl;
                if (itJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>0.8){
                    misstagged_bottom.push_back(*itJet);
//                     cout<<"found misstagged b"<<endl;
                } else {
                    tagged_bottom_anti.push_back(*itJet);
//                     cout<<"found tagged b anti"<<endl;
                }
            } else {
                AK4_bottom_tag_candidates.push_back(*itJet);
//                 std::cout<<"AK4 bottom tag candidate found"<<endl;
                if (itJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>0.8){
                    tagged_bottom.push_back(*itJet);
//                     cout<<"found tagged b"<<endl;
                } else {
                    misstagged_bottom_anti.push_back(*itJet);
//                     cout<<"found misstagged b anti"<<endl;
                }
                //vars.FillVars("misstagged_bottom_pt",iJet,itJet->pt());
                //vars.FillVars("misstagged_bottom_eta",iJet,itJet->eta());
            }
        }
//         std::cout<<"AK4_minDr_BottomTprime: "<<minDr_bfromTPrime<<endl;
//         std::cout<<"AK4_minDr_BottomBG: "<<minDr_bfromBG<<endl;    
        
    }
  }
  vars.FillVar("N_AK8_top_candidates",AK8_top_candidates.size());   
  vars.FillVar("N_AK8_W_candidates",AK8_W_candidates.size());  
  vars.FillVar("N_AK4_bottom_candidates",AK4_bottom_candidates.size()); 

  for(std::vector<pat::Jet>::const_iterator itJet = AK8_top_candidates.begin() ; itJet != AK8_top_candidates.end(); ++itJet){
    int iJet = itJet - AK8_top_candidates.begin();
    vars.FillVars("AK8_top_candidates_pt",iJet,itJet->pt());
    vars.FillVars("AK8_top_candidates_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = AK8_W_candidates.begin() ; itJet != AK8_W_candidates.end(); ++itJet){
    int iJet = itJet - AK8_W_candidates.begin();
    vars.FillVars("AK8_W_candidates_pt",iJet,itJet->pt());
    vars.FillVars("AK8_W_candidates_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = AK4_bottom_candidates.begin() ; itJet != AK4_bottom_candidates.end(); ++itJet){
    int iJet = itJet - AK4_bottom_candidates.begin();
    vars.FillVars("AK4_bottom_candidates_pt",iJet,itJet->pt());
    vars.FillVars("AK4_bottom_candidates_eta",iJet,itJet->eta());
  }   
  
    
  vars.FillVar("N_AK8_top_misstag_candidates",AK8_top_misstag_candidates.size());
  vars.FillVar("N_AK8_W_misstag_candidates",AK8_W_misstag_candidates.size());
  vars.FillVar("N_AK4_bottom_misstag_candidates",AK4_bottom_misstag_candidates.size());
  vars.FillVar("N_AK8_top_tag_candidates",AK8_top_tag_candidates.size());
  vars.FillVar("N_AK8_W_tag_candidates",AK8_W_tag_candidates.size());
  vars.FillVar("N_AK4_bottom_tag_candidates",AK4_bottom_tag_candidates.size());

  for(std::vector<pat::Jet>::const_iterator itJet = AK8_top_misstag_candidates.begin() ; itJet != AK8_top_misstag_candidates.end(); ++itJet){
    int iJet = itJet - AK8_top_misstag_candidates.begin();
    vars.FillVars("AK8_top_misstagged_candidates_pt",iJet,itJet->pt());
    vars.FillVars("AK8_top_misstagged_candidates_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = AK8_W_misstag_candidates.begin() ; itJet != AK8_W_misstag_candidates.end(); ++itJet){
    int iJet = itJet - AK8_W_misstag_candidates.begin();
    vars.FillVars("AK8_W_misstagged_candidates_pt",iJet,itJet->pt());
    vars.FillVars("AK8_W_misstagged_candidates_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = AK4_bottom_misstag_candidates.begin() ; itJet != AK4_bottom_misstag_candidates.end(); ++itJet){
    int iJet = itJet - AK4_bottom_misstag_candidates.begin();
    vars.FillVars("AK4_bottom_misstagged_candidates_pt",iJet,itJet->pt());
    vars.FillVars("AK4_bottom_misstagged_candidates_eta",iJet,itJet->eta());
  } 
  
  for(std::vector<pat::Jet>::const_iterator itJet = AK8_top_tag_candidates.begin() ; itJet != AK8_top_tag_candidates.end(); ++itJet){
    int iJet = itJet - AK8_top_tag_candidates.begin();
    vars.FillVars("AK8_top_tag_candidates_pt",iJet,itJet->pt());
    vars.FillVars("AK8_top_tag_candidates_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = AK8_W_tag_candidates.begin() ; itJet != AK8_W_tag_candidates.end(); ++itJet){
    int iJet = itJet - AK8_W_tag_candidates.begin();
    vars.FillVars("AK8_W_tag_candidates_pt",iJet,itJet->pt());
    vars.FillVars("AK8_W_tag_candidates_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = AK4_bottom_tag_candidates.begin() ; itJet != AK4_bottom_tag_candidates.end(); ++itJet){
    int iJet = itJet - AK4_bottom_tag_candidates.begin();
    vars.FillVars("AK4_bottom_tag_candidates_pt",iJet,itJet->pt());
    vars.FillVars("AK4_bottom_tag_candidates_eta",iJet,itJet->eta());
  }    

  

  vars.FillVar("N_misstagged_top",misstagged_top.size());
  vars.FillVar("N_misstagged_top_withbtag",misstagged_top_withbtag.size());
  vars.FillVar("N_misstagged_W",misstagged_W.size()); 
  vars.FillVar("N_misstagged_bottom",misstagged_bottom.size());
  vars.FillVar("N_tagged_top",tagged_top.size());
  vars.FillVar("N_tagged_top_withbtag",tagged_top_withbtag.size());
  vars.FillVar("N_tagged_W",tagged_W.size()); 
  vars.FillVar("N_tagged_bottom",tagged_bottom.size());  
  
  for(std::vector<pat::Jet>::const_iterator itJet = misstagged_top.begin() ; itJet != misstagged_top.end(); ++itJet){
    int iJet = itJet - misstagged_top.begin();
    vars.FillVars("misstagged_top_pt",iJet,itJet->pt());
    vars.FillVars("misstagged_top_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = misstagged_top_withbtag.begin() ; itJet != misstagged_top_withbtag.end(); ++itJet){
    int iJet = itJet - misstagged_top_withbtag.begin();
    vars.FillVars("misstagged_top_withbtag_pt",iJet,itJet->pt());
    vars.FillVars("misstagged_top_withbtag_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = misstagged_W.begin() ; itJet != misstagged_W.end(); ++itJet){
    int iJet = itJet - misstagged_W.begin();
    vars.FillVars("misstagged_W_pt",iJet,itJet->pt());
    vars.FillVars("misstagged_W_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = misstagged_bottom.begin() ; itJet != misstagged_bottom.end(); ++itJet){
    int iJet = itJet - misstagged_bottom.begin();
    vars.FillVars("misstagged_bottom_pt",iJet,itJet->pt());
    vars.FillVars("misstagged_bottom_eta",iJet,itJet->eta());
  }
  
  for(std::vector<pat::Jet>::const_iterator itJet = tagged_top.begin() ; itJet != tagged_top.end(); ++itJet){
    int iJet = itJet - tagged_top.begin();
    vars.FillVars("tagged_top_pt",iJet,itJet->pt());
    vars.FillVars("tagged_top_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = tagged_top_withbtag.begin() ; itJet != tagged_top_withbtag.end(); ++itJet){
    int iJet = itJet - tagged_top_withbtag.begin();
    vars.FillVars("tagged_top_withbtag_pt",iJet,itJet->pt());
    vars.FillVars("tagged_top_withbtag_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = tagged_W.begin() ; itJet != tagged_W.end(); ++itJet){
    int iJet = itJet - tagged_W.begin();
    vars.FillVars("tagged_W_pt",iJet,itJet->pt());
    vars.FillVars("tagged_W_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = tagged_bottom.begin() ; itJet != tagged_bottom.end(); ++itJet){
    int iJet = itJet - tagged_bottom.begin();
    vars.FillVars("tagged_bottom_pt",iJet,itJet->pt());
    vars.FillVars("tagged_bottom_eta",iJet,itJet->eta());
  }
  
  
  vars.FillVar("N_misstagged_top_anti",misstagged_top_anti.size());
  vars.FillVar("N_misstagged_top_withbtag_anti",misstagged_top_withbtag_anti.size());
  vars.FillVar("N_misstagged_W_anti",misstagged_W_anti.size()); 
  vars.FillVar("N_misstagged_bottom_anti",misstagged_bottom_anti.size());
  vars.FillVar("N_tagged_top_anti",tagged_top_anti.size());
  vars.FillVar("N_tagged_top_withbtag_anti",tagged_top_withbtag_anti.size());
  vars.FillVar("N_tagged_W_anti",tagged_W_anti.size()); 
  vars.FillVar("N_tagged_anti_bottom",tagged_bottom_anti.size());  
  
  for(std::vector<pat::Jet>::const_iterator itJet = misstagged_top_anti.begin() ; itJet != misstagged_top_anti.end(); ++itJet){
    int iJet = itJet - misstagged_top_anti.begin();
    vars.FillVars("misstagged_top_anti_pt",iJet,itJet->pt());
    vars.FillVars("misstagged_top_anti_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = misstagged_top_withbtag_anti.begin() ; itJet != misstagged_top_withbtag_anti.end(); ++itJet){
    int iJet = itJet - misstagged_top_withbtag_anti.begin();
    vars.FillVars("misstagged_top_withbtag_anti_pt",iJet,itJet->pt());
    vars.FillVars("misstagged_top_withbtag_anti_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = misstagged_W_anti.begin() ; itJet != misstagged_W_anti.end(); ++itJet){
    int iJet = itJet - misstagged_W_anti.begin();
    vars.FillVars("misstagged_W_anti_pt",iJet,itJet->pt());
    vars.FillVars("misstagged_W_anti_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = misstagged_bottom_anti.begin() ; itJet != misstagged_bottom_anti.end(); ++itJet){
    int iJet = itJet - misstagged_bottom_anti.begin();
    vars.FillVars("misstagged_bottom_anti_pt",iJet,itJet->pt());
    vars.FillVars("misstagged_bottom_anti_eta",iJet,itJet->eta());
  }
  
  for(std::vector<pat::Jet>::const_iterator itJet = tagged_top_anti.begin() ; itJet != tagged_top_anti.end(); ++itJet){
    int iJet = itJet - tagged_top_anti.begin();
    vars.FillVars("tagged_top_anti_pt",iJet,itJet->pt());
    vars.FillVars("tagged_top_anti_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = tagged_top_withbtag_anti.begin() ; itJet != tagged_top_withbtag_anti.end(); ++itJet){
    int iJet = itJet - tagged_top_withbtag_anti.begin();
    vars.FillVars("tagged_top_withbtag_anti_pt",iJet,itJet->pt());
    vars.FillVars("tagged_top_withbtag_anti_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = tagged_W_anti.begin() ; itJet != tagged_W_anti.end(); ++itJet){
    int iJet = itJet - tagged_W_anti.begin();
    vars.FillVars("tagged_W_anti_pt",iJet,itJet->pt());
    vars.FillVars("tagged_W_anti_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = tagged_bottom_anti.begin() ; itJet != tagged_bottom_anti.end(); ++itJet){
    int iJet = itJet - tagged_bottom_anti.begin();
    vars.FillVars("tagged_bottom_anti_pt",iJet,itJet->pt());
    vars.FillVars("tagged_bottom_anti_eta",iJet,itJet->eta());
  }

// select all jets without a top tag added by Kevin ; top tag mistag tag method -> TTM preceding character
// ht is sum of pt of all Ak4 (selected jets) jets
	
	math::XYZTLorentzVector TTM_Zprime;
  math::XYZTLorentzVector TTM_Tprime; 
  std::vector<pat::Jet> TTM_separated_bottoms;
  std::vector<pat::Jet> TTM_separated_bottoms_no_top;
  std::vector<pat::Jet> TTM_AK8_top_candidates_separated_highest_pt;
  std::vector<pat::Jet> TTM_AK8_top_candidates_separated;
  std::vector<pat::Jet> TTM_Ws_highest_pt;
  std::vector<pat::Jet> TTM_separated_bottoms_highest_pt;
  std::vector<pat::Jet> TTM_separated_bottoms_no_top_highest_pt;
  
  for(std::vector<pat::Jet>::const_iterator ittopJet = AK8_top_candidates.begin() ; ittopJet != AK8_top_candidates.end(); ++ittopJet)
  {
  	bool check_dR_ak8_W=true;
    for(std::vector<pat::Jet>::const_iterator itWJet = Ws.begin() ; itWJet != Ws.end() ; ++itWJet)
  	{
  		if(BoostedUtils::DeltaR(ittopJet->p4(),itWJet->p4())<0.8)
  		{
  			check_dR_ak8_W=false;
  		 	break;
  		 }
  		else continue;
  	}
  	if (check_dR_ak8_W==true) TTM_AK8_top_candidates_separated.push_back(*ittopJet);
  }
           
      
  			
  			
  
  if (TTM_AK8_top_candidates_separated.size()>0 && Ws.size()>0 )
  {
  	TTM_AK8_top_candidates_separated_highest_pt.push_back(TTM_AK8_top_candidates_separated.at(0));
  	TTM_Ws_highest_pt.push_back(Ws.at(0));
//   	std::cout << "Found TopCandidates and W-Bosons" << std::endl;
  	vars.FillVar("TTM_AK8_top_candidates_highest_M",TTM_AK8_top_candidates_separated_highest_pt[0].mass());
		vars.FillVar("TTM_AK8_top_candidates_highest_pt",TTM_AK8_top_candidates_separated_highest_pt[0].pt());
		vars.FillVar("TTM_AK8_top_candidates_highest_eta",TTM_AK8_top_candidates_separated_highest_pt[0].eta());
		vars.FillVar("TTM_highest_Ws_M",TTM_Ws_highest_pt[0].mass());
		vars.FillVar("TTM_highest_Ws_pt",TTM_Ws_highest_pt[0].pt());
		vars.FillVar("TTM_highest_Ws_eta",TTM_Ws_highest_pt[0].eta());
		vars.FillVar("TTM_Mistagrate",foo.GetMistagrate(TTM_AK8_top_candidates_separated_highest_pt[0].pt(),TTM_AK8_top_candidates_separated_highest_pt[0].eta()));
// 		std::cout << "Mistagrate:  " << foo.GetMistagrate(TTM_AK8_top_candidates_separated_highest_pt[0].pt(),TTM_AK8_top_candidates_separated_highest_pt[0].eta()) << std::endl;
// 		std::cout << "TTM_AK8_top_candidates_highest_pt[0].pt():    " << TTM_AK8_top_candidates_separated_highest_pt[0].pt() << std::endl;
// 		std::cout << "TTM_AK8_top_candidates_highest_pt[0].eta():   " << TTM_AK8_top_candidates_separated_highest_pt[0].eta() << std::endl;
// 		std::cout << "Mass of highest pt AK8 Jet:  " << TTM_AK8_top_candidates_separated_highest_pt[0].mass() << std::endl;
  }
  else 
  {
//   	std::cout << "Found no AK_8_top_candidate and no W-Bosons. Cant reconstruct Tprime and Zprime." << std::endl;
  }


	vars.FillVar("TTM_RndmSDM",foo.GetRndmSDM(histo_TTM_SDM));
// 	std::cout << "Random SoftdropMass:  " << foo.GetRndmSDM(histo_TTM_SDM) << std::endl;  	
  

// go through all cuts
	
			if (ht>850 && bottoms.size()>0 && Ws.size()>0 && TTM_AK8_top_candidates_separated.size()>0) 
			{
			  TTM_separated_bottoms=SelectSeparatedBottoms(TTM_AK8_top_candidates_separated_highest_pt,TTM_Ws_highest_pt,bottoms);
			  if (TTM_separated_bottoms.size()>0)
			  {
					for (std::vector<pat::Jet>::const_iterator itJet = TTM_separated_bottoms.begin() ; itJet != TTM_separated_bottoms.end(); ++itJet)
					{
						int iJet = itJet-TTM_separated_bottoms.begin();
						vars.FillVar("N_TTM_separated_bottoms",TTM_separated_bottoms.size());
						vars.FillVars("TTM_separated_bottoms_M",iJet,TTM_separated_bottoms[iJet].mass());
						vars.FillVars("TTM_separated_bottoms_pt",iJet,TTM_separated_bottoms[iJet].pt());
						vars.FillVars("TTM_separated_bottoms_eta",iJet,TTM_separated_bottoms[iJet].eta());
					}
				}
					
			  if (TTM_separated_bottoms.size()>0)
			  {
			  	TTM_separated_bottoms_highest_pt.push_back(TTM_separated_bottoms.at(0));
			  	vars.FillVar("TTM_separated_highest_bottoms_M",TTM_separated_bottoms_highest_pt[0].mass());
					vars.FillVar("TTM_separated_highest_bottoms_pt",TTM_separated_bottoms_highest_pt[0].pt());
					vars.FillVar("TTM_separated_highest_bottoms_eta",TTM_separated_bottoms_highest_pt[0].eta());
// 			  	std::cout << "Highest pt of separated bottoms:  " << TTM_separated_bottoms_highest_pt[0].pt() << std::endl;
			  	
			  	TTM_Tprime=TPrimeReconstructionWtb(TTM_Ws_highest_pt,TTM_separated_bottoms_highest_pt);
			  	if (TTM_Tprime.mass()>500)
					{
								
								
				    		TTM_AK8_top_candidates_separated_highest_pt[0].setMass(foo.GetRndmSDM(histo_TTM_SDM));
// 				    		std::cout << "New Mass of highest pt AK8 Jet:  " << TTM_AK8_top_candidates_separated_highest_pt[0].mass() << std::endl;
				    		TTM_Zprime=ZPrimeReconstructionWtb(TTM_AK8_top_candidates_separated_highest_pt,TTM_Tprime);
				    		
// 				    		std::cout << "Mass of Tprime:  " << TTM_Tprime.mass() << std::endl;
// 				    		std::cout << "Mass of Zprime:  " << TTM_Zprime.mass() << std::endl;
				    		
				    		vars.FillVar("TTM_Zprime_M",TTM_Zprime.mass());
								vars.FillVar("TTM_Zprime_pt",TTM_Zprime.pt());
								vars.FillVar("TTM_Zprime_eta",TTM_Zprime.eta());
								vars.FillVar("TTM_Tprime_M",TTM_Tprime.mass());
								vars.FillVar("TTM_Tprime_pt",TTM_Tprime.pt());
								vars.FillVar("TTM_Tprime_eta",TTM_Tprime.eta());
						
					}
				}
			}
  
			//second run with inverted top tag
			
			if (ht>850 && bottoms.size()>0 && Ws.size()>0 && TTM_AK8_top_candidates_separated.size()>0 && tops.size()==0) 
			{
			  TTM_separated_bottoms_no_top=SelectSeparatedBottoms(TTM_AK8_top_candidates_separated_highest_pt,TTM_Ws_highest_pt,bottoms);
			  if (TTM_separated_bottoms_no_top.size()>0)
			  {
					for (std::vector<pat::Jet>::const_iterator itJet = TTM_separated_bottoms_no_top.begin() ; itJet != TTM_separated_bottoms_no_top.end(); ++itJet)
					{
						int iJet = itJet-TTM_separated_bottoms_no_top.begin();
						vars.FillVar("N_TTM_no_top_separated_bottoms",TTM_separated_bottoms_no_top.size());
						vars.FillVars("TTM_no_top_separated_bottoms_M",iJet,TTM_separated_bottoms_no_top[iJet].mass());
						vars.FillVars("TTM_no_top_separated_bottoms_pt",iJet,TTM_separated_bottoms_no_top[iJet].pt());
						vars.FillVars("TTM_no_top_separated_bottoms_eta",iJet,TTM_separated_bottoms_no_top[iJet].eta());
					}
				}
					
			  if (TTM_separated_bottoms_no_top.size()>0)
			  {
			  	TTM_separated_bottoms_no_top_highest_pt.push_back(TTM_separated_bottoms_no_top.at(0));
			  	vars.FillVar("TTM_no_top_separated_highest_bottoms_M",TTM_separated_bottoms_no_top_highest_pt[0].mass());
					vars.FillVar("TTM_no_top_separated_highest_bottoms_pt",TTM_separated_bottoms_no_top_highest_pt[0].pt());
					vars.FillVar("TTM_no_top_separated_highest_bottoms_eta",TTM_separated_bottoms_no_top_highest_pt[0].eta());
// 			  	std::cout << "Highest pt of separated bottoms:  " << TTM_separated_bottoms_no_top_highest_pt[0].pt() << std::endl;
			  	
			  	TTM_Tprime=TPrimeReconstructionWtb(TTM_Ws_highest_pt,TTM_separated_bottoms_no_top_highest_pt);
			  	if (TTM_Tprime.mass()>500)
					{
								
								
				    		TTM_AK8_top_candidates_separated_highest_pt[0].setMass(foo.GetRndmSDM(histo_TTM_SDM));
// 				    		std::cout << "New Mass of highest pt AK8 Jet:  " << TTM_AK8_top_candidates_separated_highest_pt[0].mass() << std::endl;
				    		TTM_Zprime=ZPrimeReconstructionWtb(TTM_AK8_top_candidates_separated_highest_pt,TTM_Tprime);
				    		
// 				    		std::cout << "Mass of Tprime:  " << TTM_Tprime.mass() << std::endl;
// 				    		std::cout << "Mass of Zprime:  " << TTM_Zprime.mass() << std::endl;
				    		
				    		vars.FillVar("TTM_no_top_Zprime_M",TTM_Zprime.mass());
								vars.FillVar("TTM_no_top_Zprime_pt",TTM_Zprime.pt());
								vars.FillVar("TTM_no_top_Zprime_eta",TTM_Zprime.eta());
								vars.FillVar("TTM_no_top_Tprime_M",TTM_Tprime.mass());
								vars.FillVar("TTM_no_top_Tprime_pt",TTM_Tprime.pt());
								vars.FillVar("TTM_no_top_Tprime_eta",TTM_Tprime.eta());
						
					}
				}
			}
		
				
        		
 //**************************************  
  
  
  
  
/////ALL COMBINATIONS FOR ABCD-METHODE
  if(AK8_top_candidates.size()>0 && AK8_W_candidates.size()>1 && AK4_bottom_candidates.size()>0){
    for(std::vector<pat::Jet>::iterator ittopJet = AK8_top_candidates.begin() ; ittopJet != AK8_top_candidates.end(); ++ittopJet){
        for(std::vector<pat::Jet>::iterator itWJet = AK8_W_candidates.begin() ; itWJet != AK8_W_candidates.end(); ++itWJet){
            if(BoostedUtils::DeltaR(itWJet->p4(),ittopJet->p4())<0.1){
//                 std::cout<<"ah ah ah, W- and top-jets are the same"<<endl;
            }else{
                if(itWJet->userFloat("NjettinessAK8CHS:tau1")>0 && itWJet->userFloat("NjettinessAK8CHS:tau2")>0 && itWJet->userFloat("NjettinessAK8CHS:tau3")>0 && ittopJet->userFloat("NjettinessAK8CHS:tau1")>0 && ittopJet->userFloat("NjettinessAK8CHS:tau2")>0 && ittopJet->userFloat("NjettinessAK8CHS:tau3")>0){
                    for(std::vector<pat::Jet>::const_iterator itBJet = AK4_bottom_candidates.begin() ; itBJet != AK4_bottom_candidates.end(); ++itBJet){
                        if(BoostedUtils::DeltaR(itWJet->p4(),itBJet->p4())>1.2 && BoostedUtils::DeltaR(itBJet->p4(),ittopJet->p4())>1.2){
                                ZprimesABCD.push_back(itBJet->p4()+ittopJet->p4()+itWJet->p4());
                                TprimesABCD.push_back(itBJet->p4()+itWJet->p4());
                                TopsABCD.push_back(*ittopJet);
                                BottomsABCD.push_back(*itBJet);
                                WsABCD.push_back(*itWJet);
                                
                            if(ittopJet->userFloat("ak8PFJetsCHSSoftDropMass")>105.0  && ittopJet->userFloat("ak8PFJetsCHSSoftDropMass")<220.0){
                                ittopJet->setMass(foo.GetRndmSDM(histo_ABCD_QCD_MSD_top_nobtag));
                            }
                            if(itWJet->userFloat("ak8PFJetsCHSSoftDropMass")>70.0  && itWJet->userFloat("ak8PFJetsCHSSoftDropMass")>100.0){
                                itWJet->setMass(foo.GetRndmSDM(histo_ABCD_QCD_MSD_W_nobtag));
                            }
                                ZprimesABCDmasscorrnotopbtag.push_back(itBJet->p4()+ittopJet->p4()+itWJet->p4());
                                TprimesABCDmasscorrnotopbtag.push_back(itBJet->p4()+itWJet->p4());
                                TopsABCDmasscorrnotopbtag.push_back(*ittopJet);
                                BottomsABCDmasscorrnotopbtag.push_back(*itBJet);
                                WsABCDmasscorrnotopbtag.push_back(*itWJet);
                            
                            if(ittopJet->userFloat("ak8PFJetsCHSSoftDropMass")>105.0  && ittopJet->userFloat("ak8PFJetsCHSSoftDropMass")<220.0){
                                ittopJet->setMass(foo.GetRndmSDM(histo_ABCD_QCD_MSD_top_withbtag));
                            }
                            if(itWJet->userFloat("ak8PFJetsCHSSoftDropMass")>70.0  && itWJet->userFloat("ak8PFJetsCHSSoftDropMass")>100.0){
                                itWJet->setMass(foo.GetRndmSDM(histo_ABCD_QCD_MSD_W_withbtag));
                            }
                                ZprimesABCDmasscorrwithtopbtag.push_back(itBJet->p4()+ittopJet->p4()+itWJet->p4());
                                TprimesABCDmasscorrwithtopbtag.push_back(itBJet->p4()+itWJet->p4());
                                TopsABCDmasscorrwithtopbtag.push_back(*ittopJet);
                                BottomsABCDmasscorrwithtopbtag.push_back(*itBJet);
                                WsABCDmasscorrwithtopbtag.push_back(*itWJet);                            
                        }
                    }                    
                }
            }
        }
    }
  }
  
 
/////ALL COMBINATIONS FOR ABCD-METHODE with top AK15-Jets and W AK8-Jets
  if(AK15_top_candidates.size()>0 && AK8_W_candidates.size()>1 && AK4_bottom_candidates.size()>0){
    for(std::vector<pat::Jet>::iterator ittopJet = AK15_top_candidates.begin() ; ittopJet != AK15_top_candidates.end(); ++ittopJet){
        for(std::vector<pat::Jet>::iterator itWJet = AK8_W_candidates.begin() ; itWJet != AK8_W_candidates.end(); ++itWJet){
            if(BoostedUtils::DeltaR(itWJet->p4(),ittopJet->p4())<2.3){
//                 std::cout<<"ah ah ah, W- and top-jets have overlap"<<endl;
            }else{
                if(itWJet->userFloat("NjettinessAK8CHS:tau1")>0 && itWJet->userFloat("NjettinessAK8CHS:tau2")>0 && itWJet->userFloat("NjettinessAK8CHS:tau3")>0 && ittopJet->userFloat("NjettinessAK15CHS:tau1")>0 && ittopJet->userFloat("NjettinessAK15CHS:tau2")>0 && ittopJet->userFloat("NjettinessAK15CHS:tau3")>0){
                    for(std::vector<pat::Jet>::const_iterator itBJet = AK4_bottom_candidates.begin() ; itBJet != AK4_bottom_candidates.end(); ++itBJet){
                        if(BoostedUtils::DeltaR(itWJet->p4(),itBJet->p4())>1.2 && BoostedUtils::DeltaR(itBJet->p4(),ittopJet->p4())>1.9){
                                Zprimes_ABCD_tAK15WAK8bAK4.push_back(itBJet->p4()+ittopJet->p4()+itWJet->p4());
                                Tprimes_ABCD_tAK15WAK8bAK4.push_back(itBJet->p4()+itWJet->p4());
                                Tops_ABCD_tAK15WAK8bAK4.push_back(*ittopJet);
                                Bottoms_ABCD_tAK15WAK8bAK4.push_back(*itBJet);
                                Ws_ABCD_tAK15WAK8bAK4.push_back(*itWJet);
                                
/*                            if(ittopJet->userFloat("ak8PFJetsCHSSoftDropMass")>105.0  && ittopJet->userFloat("ak8PFJetsCHSSoftDropMass")<220.0){
                                ittopJet->setMass(foo.GetRndmSDM(histo_ABCD_QCD_MSD_top_nobtag));
                            }
                            if(itWJet->userFloat("ak8PFJetsCHSSoftDropMass")>70.0  && itWJet->userFloat("ak8PFJetsCHSSoftDropMass")>100.0){
                                itWJet->setMass(foo.GetRndmSDM(histo_ABCD_QCD_MSD_W_nobtag));
                            }
                                ZprimesABCDmasscorrnotopbtag.push_back(itBJet->p4()+ittopJet->p4()+itWJet->p4());
                                TprimesABCDmasscorrnotopbtag.push_back(itBJet->p4()+itWJet->p4());
                                TopsABCDmasscorrnotopbtag.push_back(*ittopJet);
                                BottomsABCDmasscorrnotopbtag.push_back(*itBJet);
                                WsABCDmasscorrnotopbtag.push_back(*itWJet);
                            
                            if(ittopJet->userFloat("ak8PFJetsCHSSoftDropMass")>105.0  && ittopJet->userFloat("ak8PFJetsCHSSoftDropMass")<220.0){
                                ittopJet->setMass(foo.GetRndmSDM(histo_ABCD_QCD_MSD_top_withbtag));
                            }
                            if(itWJet->userFloat("ak8PFJetsCHSSoftDropMass")>70.0  && itWJet->userFloat("ak8PFJetsCHSSoftDropMass")>100.0){
                                itWJet->setMass(foo.GetRndmSDM(histo_ABCD_QCD_MSD_W_withbtag));
                            }
                                ZprimesABCDmasscorrwithtopbtag.push_back(itBJet->p4()+ittopJet->p4()+itWJet->p4());
                                TprimesABCDmasscorrwithtopbtag.push_back(itBJet->p4()+itWJet->p4());
                                TopsABCDmasscorrwithtopbtag.push_back(*ittopJet);
                                BottomsABCDmasscorrwithtopbtag.push_back(*itBJet);
                                WsABCDmasscorrwithtopbtag.push_back(*itWJet);      */                      
                        }
                    }                    
                }
            }
        }
    }
  }   
 
  
/////ALL COMBINATIONS FOR ABCD-METHODE with top AK15-Jets and W AK15-Jets
  if(AK15_top_candidates.size()>0 && AK15_W_candidates.size()>1 && AK4_bottom_candidates.size()>0){
    for(std::vector<pat::Jet>::iterator ittopJet = AK15_top_candidates.begin() ; ittopJet != AK15_top_candidates.end(); ++ittopJet){
        for(std::vector<pat::Jet>::iterator itWJet = AK15_W_candidates.begin() ; itWJet != AK15_W_candidates.end(); ++itWJet){
            if(BoostedUtils::DeltaR(itWJet->p4(),ittopJet->p4())<0.1){
//                 std::cout<<"ah ah ah, W- and top-jets are the same"<<endl;
            }else{
                if(itWJet->userFloat("NjettinessAK15CHS:tau1")>0 && itWJet->userFloat("NjettinessAK15CHS:tau2")>0 && itWJet->userFloat("NjettinessAK15CHS:tau3")>0 && ittopJet->userFloat("NjettinessAK15CHS:tau1")>0 && ittopJet->userFloat("NjettinessAK15CHS:tau2")>0 && ittopJet->userFloat("NjettinessAK15CHS:tau3")>0){
                    for(std::vector<pat::Jet>::const_iterator itBJet = AK4_bottom_candidates.begin() ; itBJet != AK4_bottom_candidates.end(); ++itBJet){
                        if(BoostedUtils::DeltaR(itWJet->p4(),itBJet->p4())>1.9 && BoostedUtils::DeltaR(itBJet->p4(),ittopJet->p4())>1.9){
                                Zprimes_ABCD_tAK15WAK15bAK4.push_back(itBJet->p4()+ittopJet->p4()+itWJet->p4());
                                Tprimes_ABCD_tAK15WAK15bAK4.push_back(itBJet->p4()+itWJet->p4());
                                Tops_ABCD_tAK15WAK15bAK4.push_back(*ittopJet);
                                Bottoms_ABCD_tAK15WAK15bAK4.push_back(*itBJet);
                                Ws_ABCD_tAK15WAK15bAK4.push_back(*itWJet);
                                
/*                            if(ittopJet->userFloat("ak8PFJetsCHSSoftDropMass")>105.0  && ittopJet->userFloat("ak8PFJetsCHSSoftDropMass")<220.0){
                                ittopJet->setMass(foo.GetRndmSDM(histo_ABCD_QCD_MSD_top_nobtag));
                            }
                            if(itWJet->userFloat("ak8PFJetsCHSSoftDropMass")>70.0  && itWJet->userFloat("ak8PFJetsCHSSoftDropMass")>100.0){
                                itWJet->setMass(foo.GetRndmSDM(histo_ABCD_QCD_MSD_W_nobtag));
                            }
                                ZprimesABCDmasscorrnotopbtag.push_back(itBJet->p4()+ittopJet->p4()+itWJet->p4());
                                TprimesABCDmasscorrnotopbtag.push_back(itBJet->p4()+itWJet->p4());
                                TopsABCDmasscorrnotopbtag.push_back(*ittopJet);
                                BottomsABCDmasscorrnotopbtag.push_back(*itBJet);
                                WsABCDmasscorrnotopbtag.push_back(*itWJet);
                            
                            if(ittopJet->userFloat("ak8PFJetsCHSSoftDropMass")>105.0  && ittopJet->userFloat("ak8PFJetsCHSSoftDropMass")<220.0){
                                ittopJet->setMass(foo.GetRndmSDM(histo_ABCD_QCD_MSD_top_withbtag));
                            }
                            if(itWJet->userFloat("ak8PFJetsCHSSoftDropMass")>70.0  && itWJet->userFloat("ak8PFJetsCHSSoftDropMass")>100.0){
                                itWJet->setMass(foo.GetRndmSDM(histo_ABCD_QCD_MSD_W_withbtag));
                            }
                                ZprimesABCDmasscorrwithtopbtag.push_back(itBJet->p4()+ittopJet->p4()+itWJet->p4());
                                TprimesABCDmasscorrwithtopbtag.push_back(itBJet->p4()+itWJet->p4());
                                TopsABCDmasscorrwithtopbtag.push_back(*ittopJet);
                                BottomsABCDmasscorrwithtopbtag.push_back(*itBJet);
                                WsABCDmasscorrwithtopbtag.push_back(*itWJet);      */                      
                        }
                    }                    
                }
            }
        }
    }
  }  

  
  
 
/////ALL COMBINATIONS FOR ABCD-METHODE with top AK12-Jets and W AK8-Jets
  if(AK12_top_candidates.size()>0 && AK8_W_candidates.size()>1 && AK4_bottom_candidates.size()>0){
    for(std::vector<pat::Jet>::iterator ittopJet = AK12_top_candidates.begin() ; ittopJet != AK12_top_candidates.end(); ++ittopJet){
        for(std::vector<pat::Jet>::iterator itWJet = AK8_W_candidates.begin() ; itWJet != AK8_W_candidates.end(); ++itWJet){
            if(BoostedUtils::DeltaR(itWJet->p4(),ittopJet->p4())<2.0){
//                 std::cout<<"ah ah ah, W- and top-jets have overlap"<<endl;
            }else{
                if(itWJet->userFloat("NjettinessAK8CHS:tau1")>0 && itWJet->userFloat("NjettinessAK8CHS:tau2")>0 && itWJet->userFloat("NjettinessAK8CHS:tau3")>0 && ittopJet->userFloat("NjettinessAK12CHS:tau1")>0 && ittopJet->userFloat("NjettinessAK12CHS:tau2")>0 && ittopJet->userFloat("NjettinessAK12CHS:tau3")>0){
                    for(std::vector<pat::Jet>::const_iterator itBJet = AK4_bottom_candidates.begin() ; itBJet != AK4_bottom_candidates.end(); ++itBJet){
                        if(BoostedUtils::DeltaR(itWJet->p4(),itBJet->p4())>1.2 && BoostedUtils::DeltaR(itBJet->p4(),ittopJet->p4())>1.6){
                                Zprimes_ABCD_tAK12WAK8bAK4.push_back(itBJet->p4()+ittopJet->p4()+itWJet->p4());
                                Tprimes_ABCD_tAK12WAK8bAK4.push_back(itBJet->p4()+itWJet->p4());
                                Tops_ABCD_tAK12WAK8bAK4.push_back(*ittopJet);
                                Bottoms_ABCD_tAK12WAK8bAK4.push_back(*itBJet);
                                Ws_ABCD_tAK12WAK8bAK4.push_back(*itWJet);
                                
/*                            if(ittopJet->userFloat("ak8PFJetsCHSSoftDropMass")>105.0  && ittopJet->userFloat("ak8PFJetsCHSSoftDropMass")<220.0){
                                ittopJet->setMass(foo.GetRndmSDM(histo_ABCD_QCD_MSD_top_nobtag));
                            }
                            if(itWJet->userFloat("ak8PFJetsCHSSoftDropMass")>70.0  && itWJet->userFloat("ak8PFJetsCHSSoftDropMass")>100.0){
                                itWJet->setMass(foo.GetRndmSDM(histo_ABCD_QCD_MSD_W_nobtag));
                            }
                                ZprimesABCDmasscorrnotopbtag.push_back(itBJet->p4()+ittopJet->p4()+itWJet->p4());
                                TprimesABCDmasscorrnotopbtag.push_back(itBJet->p4()+itWJet->p4());
                                TopsABCDmasscorrnotopbtag.push_back(*ittopJet);
                                BottomsABCDmasscorrnotopbtag.push_back(*itBJet);
                                WsABCDmasscorrnotopbtag.push_back(*itWJet);
                            
                            if(ittopJet->userFloat("ak8PFJetsCHSSoftDropMass")>105.0  && ittopJet->userFloat("ak8PFJetsCHSSoftDropMass")<220.0){
                                ittopJet->setMass(foo.GetRndmSDM(histo_ABCD_QCD_MSD_top_withbtag));
                            }
                            if(itWJet->userFloat("ak8PFJetsCHSSoftDropMass")>70.0  && itWJet->userFloat("ak8PFJetsCHSSoftDropMass")>100.0){
                                itWJet->setMass(foo.GetRndmSDM(histo_ABCD_QCD_MSD_W_withbtag));
                            }
                                ZprimesABCDmasscorrwithtopbtag.push_back(itBJet->p4()+ittopJet->p4()+itWJet->p4());
                                TprimesABCDmasscorrwithtopbtag.push_back(itBJet->p4()+itWJet->p4());
                                TopsABCDmasscorrwithtopbtag.push_back(*ittopJet);
                                BottomsABCDmasscorrwithtopbtag.push_back(*itBJet);
                                WsABCDmasscorrwithtopbtag.push_back(*itWJet);      */                      
                        }
                    }                    
                }
            }
        }
    }
  }   
 
  
/////ALL COMBINATIONS FOR ABCD-METHODE with top AK12-Jets and W AK12-Jets
  if(AK12_top_candidates.size()>0 && AK12_W_candidates.size()>1 && AK4_bottom_candidates.size()>0){
    for(std::vector<pat::Jet>::iterator ittopJet = AK12_top_candidates.begin() ; ittopJet != AK12_top_candidates.end(); ++ittopJet){
        for(std::vector<pat::Jet>::iterator itWJet = AK12_W_candidates.begin() ; itWJet != AK12_W_candidates.end(); ++itWJet){
            if(BoostedUtils::DeltaR(itWJet->p4(),ittopJet->p4())<0.1){
//                 std::cout<<"ah ah ah, W- and top-jets are the same"<<endl;
            }else{
                if(itWJet->userFloat("NjettinessAK12CHS:tau1")>0 && itWJet->userFloat("NjettinessAK12CHS:tau2")>0 && itWJet->userFloat("NjettinessAK12CHS:tau3")>0 && ittopJet->userFloat("NjettinessAK12CHS:tau1")>0 && ittopJet->userFloat("NjettinessAK12CHS:tau2")>0 && ittopJet->userFloat("NjettinessAK12CHS:tau3")>0){
                    for(std::vector<pat::Jet>::const_iterator itBJet = AK4_bottom_candidates.begin() ; itBJet != AK4_bottom_candidates.end(); ++itBJet){
                        if(BoostedUtils::DeltaR(itWJet->p4(),itBJet->p4())>1.6 && BoostedUtils::DeltaR(itBJet->p4(),ittopJet->p4())>1.6){
                                Zprimes_ABCD_tAK12WAK12bAK4.push_back(itBJet->p4()+ittopJet->p4()+itWJet->p4());
                                Tprimes_ABCD_tAK12WAK12bAK4.push_back(itBJet->p4()+itWJet->p4());
                                Tops_ABCD_tAK12WAK12bAK4.push_back(*ittopJet);
                                Bottoms_ABCD_tAK12WAK12bAK4.push_back(*itBJet);
                                Ws_ABCD_tAK12WAK12bAK4.push_back(*itWJet);
                                
/*                            if(ittopJet->userFloat("ak8PFJetsCHSSoftDropMass")>105.0  && ittopJet->userFloat("ak8PFJetsCHSSoftDropMass")<220.0){
                                ittopJet->setMass(foo.GetRndmSDM(histo_ABCD_QCD_MSD_top_nobtag));
                            }
                            if(itWJet->userFloat("ak8PFJetsCHSSoftDropMass")>70.0  && itWJet->userFloat("ak8PFJetsCHSSoftDropMass")>100.0){
                                itWJet->setMass(foo.GetRndmSDM(histo_ABCD_QCD_MSD_W_nobtag));
                            }
                                ZprimesABCDmasscorrnotopbtag.push_back(itBJet->p4()+ittopJet->p4()+itWJet->p4());
                                TprimesABCDmasscorrnotopbtag.push_back(itBJet->p4()+itWJet->p4());
                                TopsABCDmasscorrnotopbtag.push_back(*ittopJet);
                                BottomsABCDmasscorrnotopbtag.push_back(*itBJet);
                                WsABCDmasscorrnotopbtag.push_back(*itWJet);
                            
                            if(ittopJet->userFloat("ak8PFJetsCHSSoftDropMass")>105.0  && ittopJet->userFloat("ak8PFJetsCHSSoftDropMass")<220.0){
                                ittopJet->setMass(foo.GetRndmSDM(histo_ABCD_QCD_MSD_top_withbtag));
                            }
                            if(itWJet->userFloat("ak8PFJetsCHSSoftDropMass")>70.0  && itWJet->userFloat("ak8PFJetsCHSSoftDropMass")>100.0){
                                itWJet->setMass(foo.GetRndmSDM(histo_ABCD_QCD_MSD_W_withbtag));
                            }
                                ZprimesABCDmasscorrwithtopbtag.push_back(itBJet->p4()+ittopJet->p4()+itWJet->p4());
                                TprimesABCDmasscorrwithtopbtag.push_back(itBJet->p4()+itWJet->p4());
                                TopsABCDmasscorrwithtopbtag.push_back(*ittopJet);
                                BottomsABCDmasscorrwithtopbtag.push_back(*itBJet);
                                WsABCDmasscorrwithtopbtag.push_back(*itWJet);      */                      
                        }
                    }                    
                }
            }
        }
    }
  }  
  
  const CSVHelper *csvReweighter=input.csvReweighter;
  
  ////FILL ABCD VARIABLES
  vars.FillVar("N_Zprime_ABCD",ZprimesABCD.size());

  for (uint i=0; i<ZprimesABCD.size(); i++){
  //for(math::XYZTLorentzVector::const_iterator ittopJet = AK8_top_candidates.begin() ; ittopJet != AK8_top_candidates.end(); ++ittopJet){
     //int i = 
     vars.FillVars("Zprimes_ABCD_M",i,ZprimesABCD[i].mass());
     vars.FillVars("Zprimes_ABCD_Pt",i,ZprimesABCD[i].pt());
     
     vars.FillVars("Tprimes_ABCD_M",i,TprimesABCD[i].mass());
     vars.FillVars("Tprimes_ABCD_Pt",i,TprimesABCD[i].pt());
     
     vars.FillVars("Bottoms_ABCD_Pt",i,BottomsABCD[i].pt());
     vars.FillVars("Bottoms_ABCD_Eta",i,BottomsABCD[i].eta());
     vars.FillVars("Bottoms_ABCD_Phi",i,BottomsABCD[i].phi());
     vars.FillVars("Bottoms_ABCD_CSV",i,MiniAODHelper::GetJetCSV(BottomsABCD[i],"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
     
//      CSVHelper csvReweighter;
     std::vector<double> ABCD_jetPts;
     std::vector<double> ABCD_jetEtas;
     std::vector<double> ABCD_jetCSVs;
     std::vector<int> ABCD_jetFlavors;
     double ABCD_csvWgtHF, ABCD_csvWgtLF, ABCD_csvWgtCF;
     float ABCD_csvweight = 1.;
     
     ABCD_jetPts.push_back(BottomsABCD[i].pt());
     ABCD_jetEtas.push_back(BottomsABCD[i].eta());
     ABCD_jetCSVs.push_back(MiniAODHelper::GetJetCSV(BottomsABCD[i],"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
     ABCD_jetFlavors.push_back(BottomsABCD[i].hadronFlavour());
     
     ABCD_csvweight= csvReweighter->getCSVWeight(ABCD_jetPts,ABCD_jetEtas,ABCD_jetCSVs,ABCD_jetFlavors,input.systematic, ABCD_csvWgtHF, ABCD_csvWgtLF, ABCD_csvWgtCF);

    bool doSystematics=true;
//     if(doSystematics && input.input.systematic != sysType::JESup && input.input.systematic != sysType::JESdown && input.input.systematic != sysType::JERup && input.input.systematic != sysType::JERdown) {
     if(doSystematics && input.systematic == Systematics::NA) { // only do these for the nominal samples
//      std::cout<<"debug1   "<<ABCD_jetPts.size()<<endl;
     vars.FillVars("Bottoms_ABCD_WeightCSVnominal",i,ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_WeightCSVLFup",i,csvReweighter->getCSVWeight(ABCD_jetPts,ABCD_jetEtas,ABCD_jetCSVs,ABCD_jetFlavors,Systematics::CSVLFup, ABCD_csvWgtHF, ABCD_csvWgtLF, ABCD_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_WeightCSVLFdown",i,csvReweighter->getCSVWeight(ABCD_jetPts,ABCD_jetEtas,ABCD_jetCSVs,ABCD_jetFlavors,Systematics::CSVLFdown, ABCD_csvWgtHF, ABCD_csvWgtLF, ABCD_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_WeightCSVHFup",i, csvReweighter->getCSVWeight(ABCD_jetPts,ABCD_jetEtas,ABCD_jetCSVs,ABCD_jetFlavors,Systematics::CSVHFup, ABCD_csvWgtHF, ABCD_csvWgtLF, ABCD_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_WeightCSVHFdown",i, csvReweighter->getCSVWeight(ABCD_jetPts,ABCD_jetEtas,ABCD_jetCSVs,ABCD_jetFlavors,Systematics::CSVHFdown, ABCD_csvWgtHF, ABCD_csvWgtLF, ABCD_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_WeightCSVHFStats1up",i, csvReweighter->getCSVWeight(ABCD_jetPts,ABCD_jetEtas,ABCD_jetCSVs,ABCD_jetFlavors,Systematics::CSVHFStats1up, ABCD_csvWgtHF, ABCD_csvWgtLF, ABCD_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_WeightCSVHFStats1down",i, csvReweighter->getCSVWeight(ABCD_jetPts,ABCD_jetEtas,ABCD_jetCSVs,ABCD_jetFlavors,Systematics::CSVHFStats1down, ABCD_csvWgtHF, ABCD_csvWgtLF, ABCD_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_WeightCSVLFStats1up",i, csvReweighter->getCSVWeight(ABCD_jetPts,ABCD_jetEtas,ABCD_jetCSVs,ABCD_jetFlavors,Systematics::CSVLFStats1up, ABCD_csvWgtHF, ABCD_csvWgtLF, ABCD_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_WeightCSVLFStats1down",i, csvReweighter->getCSVWeight(ABCD_jetPts,ABCD_jetEtas,ABCD_jetCSVs,ABCD_jetFlavors,Systematics::CSVLFStats1down, ABCD_csvWgtHF, ABCD_csvWgtLF, ABCD_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_WeightCSVHFStats2up",i, csvReweighter->getCSVWeight(ABCD_jetPts,ABCD_jetEtas,ABCD_jetCSVs,ABCD_jetFlavors,Systematics::CSVHFStats2up, ABCD_csvWgtHF, ABCD_csvWgtLF, ABCD_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_WeightCSVHFStats2down",i, csvReweighter->getCSVWeight(ABCD_jetPts,ABCD_jetEtas,ABCD_jetCSVs,ABCD_jetFlavors,Systematics::CSVHFStats2down, ABCD_csvWgtHF, ABCD_csvWgtLF, ABCD_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_WeightCSVLFStats2up",i, csvReweighter->getCSVWeight(ABCD_jetPts,ABCD_jetEtas,ABCD_jetCSVs,ABCD_jetFlavors,Systematics::CSVLFStats2up, ABCD_csvWgtHF, ABCD_csvWgtLF, ABCD_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_WeightCSVLFStats2down",i, csvReweighter->getCSVWeight(ABCD_jetPts,ABCD_jetEtas,ABCD_jetCSVs,ABCD_jetFlavors,Systematics::CSVLFStats2down, ABCD_csvWgtHF, ABCD_csvWgtLF, ABCD_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_WeightCSVCErr1up",i, csvReweighter->getCSVWeight(ABCD_jetPts,ABCD_jetEtas,ABCD_jetCSVs,ABCD_jetFlavors,Systematics::CSVCErr1up, ABCD_csvWgtHF, ABCD_csvWgtLF, ABCD_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_WeightCSVCErr1down",i, csvReweighter->getCSVWeight(ABCD_jetPts,ABCD_jetEtas,ABCD_jetCSVs,ABCD_jetFlavors,Systematics::CSVCErr1down, ABCD_csvWgtHF, ABCD_csvWgtLF, ABCD_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_WeightCSVCErr2up",i, csvReweighter->getCSVWeight(ABCD_jetPts,ABCD_jetEtas,ABCD_jetCSVs,ABCD_jetFlavors,Systematics::CSVCErr2up, ABCD_csvWgtHF, ABCD_csvWgtLF, ABCD_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_WeightCSVCErr2down",i, csvReweighter->getCSVWeight(ABCD_jetPts,ABCD_jetEtas,ABCD_jetCSVs,ABCD_jetFlavors,Systematics::CSVCErr2down, ABCD_csvWgtHF, ABCD_csvWgtLF, ABCD_csvWgtCF)/ABCD_csvweight);  
    }
//      std::cout<<"debug2   "<<jetPts.size()<<endl;
     
     
     vars.FillVars("Ws_ABCD_Pt",i,WsABCD[i].pt());
     vars.FillVars("Ws_ABCD_Eta",i,WsABCD[i].eta());
     vars.FillVars("Ws_ABCD_Phi",i,WsABCD[i].phi());
     vars.FillVars("Ws_ABCD_MSD",i,WsABCD[i].userFloat("ak8PFJetsCHSSoftDropMass"));
     vars.FillVars("Ws_ABCD_t21",i,WsABCD[i].userFloat("NjettinessAK8CHS:tau2")/WsABCD[i].userFloat("NjettinessAK8CHS:tau1"));
     
     vars.FillVars("Tops_ABCD_Pt",i,TopsABCD[i].pt());
     vars.FillVars("Tops_ABCD_Eta",i,TopsABCD[i].eta());
     vars.FillVars("Tops_ABCD_Phi",i,TopsABCD[i].phi());
     vars.FillVars("Tops_ABCD_MSD",i,TopsABCD[i].userFloat("ak8PFJetsCHSSoftDropMass"));
     vars.FillVars("Tops_ABCD_t32",i,TopsABCD[i].userFloat("NjettinessAK8CHS:tau3")/TopsABCD[i].userFloat("NjettinessAK8CHS:tau2"));

     
//      std::cout<<"debucg1"<<endl;
     std::vector<double> ABCD_subjetPts;
     std::vector<double> ABCD_subjetEtas;
     std::vector<double> ABCD_subjetCSVs;
     std::vector<int> ABCD_subjetFlavors;
     double subjet_ABCD_csvWgtHF, subjet_ABCD_csvWgtLF, subjet_ABCD_csvWgtCF;
     float subjet_ABCD_csvweight = 1.;
     

     
     double max_subjet_csv_v2=-10;
     auto const & names = TopsABCD[i].subjets("SoftDrop");
     for( auto const & itsubJet : names ){
        if (itsubJet->pt()<20.0 || abs(itsubJet->eta())>2.4) continue;
        ABCD_subjetPts.push_back(itsubJet->pt());
        ABCD_subjetEtas.push_back(itsubJet->eta());
        ABCD_subjetCSVs.push_back(MiniAODHelper::GetJetCSV(*itsubJet,"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
        ABCD_subjetFlavors.push_back(itsubJet->hadronFlavour());
              
        if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>max_subjet_csv_v2){
            max_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
        };
     };
     
//      std::cout<<"debug2.2"<<endl;
     vars.FillVars("Tops_ABCD_maxsubjetCSVv2",i,max_subjet_csv_v2);
//      std::cout<<"max_subjet_csv_v2  "<<max_subjet_csv_v2<<endl;
     
     subjet_ABCD_csvweight= csvReweighter->getCSVWeight(ABCD_subjetPts,ABCD_subjetEtas,ABCD_subjetCSVs,ABCD_subjetFlavors,input.systematic, subjet_ABCD_csvWgtHF, subjet_ABCD_csvWgtLF, subjet_ABCD_csvWgtCF);
 //     if(doSystematics && input.input.systematic != sysType::JESup && input.input.systematic != sysType::JESdown && input.input.systematic != sysType::JERup && input.input.systematic != sysType::JERdown) {
     if(doSystematics && input.systematic == Systematics::NA) { // only do these for the nominal samples
//      std::cout<<"debug3   "<<ABCD_subjetPts.size()<<endl;
     vars.FillVars("Topsubjets_ABCD_WeightCSVnominal",i,subjet_ABCD_csvweight);
     vars.FillVars("Topsubjets_ABCD_WeightCSVLFup",i,csvReweighter->getCSVWeight(ABCD_subjetPts,ABCD_subjetEtas,ABCD_subjetCSVs,ABCD_subjetFlavors,Systematics::CSVLFup, subjet_ABCD_csvWgtHF, subjet_ABCD_csvWgtLF, subjet_ABCD_csvWgtCF)/subjet_ABCD_csvweight);
     vars.FillVars("Topsubjets_ABCD_WeightCSVLFdown",i,csvReweighter->getCSVWeight(ABCD_subjetPts,ABCD_subjetEtas,ABCD_subjetCSVs,ABCD_subjetFlavors,Systematics::CSVLFdown, subjet_ABCD_csvWgtHF, subjet_ABCD_csvWgtLF, subjet_ABCD_csvWgtCF)/subjet_ABCD_csvweight);
     vars.FillVars("Topsubjets_ABCD_WeightCSVHFup",i, csvReweighter->getCSVWeight(ABCD_subjetPts,ABCD_subjetEtas,ABCD_subjetCSVs,ABCD_subjetFlavors,Systematics::CSVHFup, subjet_ABCD_csvWgtHF, subjet_ABCD_csvWgtLF, subjet_ABCD_csvWgtCF)/subjet_ABCD_csvweight);
     vars.FillVars("Topsubjets_ABCD_WeightCSVHFdown",i, csvReweighter->getCSVWeight(ABCD_subjetPts,ABCD_subjetEtas,ABCD_subjetCSVs,ABCD_subjetFlavors,Systematics::CSVHFdown, subjet_ABCD_csvWgtHF, subjet_ABCD_csvWgtLF, subjet_ABCD_csvWgtCF)/subjet_ABCD_csvweight);
     vars.FillVars("Topsubjets_ABCD_WeightCSVHFStats1up",i, csvReweighter->getCSVWeight(ABCD_subjetPts,ABCD_subjetEtas,ABCD_subjetCSVs,ABCD_subjetFlavors,Systematics::CSVHFStats1up, subjet_ABCD_csvWgtHF, subjet_ABCD_csvWgtLF, subjet_ABCD_csvWgtCF)/subjet_ABCD_csvweight);
     vars.FillVars("Topsubjets_ABCD_WeightCSVHFStats1down",i, csvReweighter->getCSVWeight(ABCD_subjetPts,ABCD_subjetEtas,ABCD_subjetCSVs,ABCD_subjetFlavors,Systematics::CSVHFStats1down, subjet_ABCD_csvWgtHF, subjet_ABCD_csvWgtLF, subjet_ABCD_csvWgtCF)/subjet_ABCD_csvweight);
     vars.FillVars("Topsubjets_ABCD_WeightCSVLFStats1up",i, csvReweighter->getCSVWeight(ABCD_subjetPts,ABCD_subjetEtas,ABCD_subjetCSVs,ABCD_subjetFlavors,Systematics::CSVLFStats1up, subjet_ABCD_csvWgtHF, subjet_ABCD_csvWgtLF, subjet_ABCD_csvWgtCF)/subjet_ABCD_csvweight);
     vars.FillVars("Topsubjets_ABCD_WeightCSVLFStats1down",i, csvReweighter->getCSVWeight(ABCD_subjetPts,ABCD_subjetEtas,ABCD_subjetCSVs,ABCD_subjetFlavors,Systematics::CSVLFStats1down, subjet_ABCD_csvWgtHF, subjet_ABCD_csvWgtLF, subjet_ABCD_csvWgtCF)/subjet_ABCD_csvweight);
     vars.FillVars("Topsubjets_ABCD_WeightCSVHFStats2up",i, csvReweighter->getCSVWeight(ABCD_subjetPts,ABCD_subjetEtas,ABCD_subjetCSVs,ABCD_subjetFlavors,Systematics::CSVHFStats2up, subjet_ABCD_csvWgtHF, subjet_ABCD_csvWgtLF, subjet_ABCD_csvWgtCF)/subjet_ABCD_csvweight);
     vars.FillVars("Topsubjets_ABCD_WeightCSVHFStats2down",i, csvReweighter->getCSVWeight(ABCD_subjetPts,ABCD_subjetEtas,ABCD_subjetCSVs,ABCD_subjetFlavors,Systematics::CSVHFStats2down, subjet_ABCD_csvWgtHF, subjet_ABCD_csvWgtLF, subjet_ABCD_csvWgtCF)/subjet_ABCD_csvweight);
     vars.FillVars("Topsubjets_ABCD_WeightCSVLFStats2up",i, csvReweighter->getCSVWeight(ABCD_subjetPts,ABCD_subjetEtas,ABCD_subjetCSVs,ABCD_subjetFlavors,Systematics::CSVLFStats2up, subjet_ABCD_csvWgtHF, subjet_ABCD_csvWgtLF, subjet_ABCD_csvWgtCF)/subjet_ABCD_csvweight);
     vars.FillVars("Topsubjets_ABCD_WeightCSVLFStats2down",i, csvReweighter->getCSVWeight(ABCD_subjetPts,ABCD_subjetEtas,ABCD_subjetCSVs,ABCD_subjetFlavors,Systematics::CSVLFStats2down, subjet_ABCD_csvWgtHF, subjet_ABCD_csvWgtLF, subjet_ABCD_csvWgtCF)/subjet_ABCD_csvweight);
     vars.FillVars("Topsubjets_ABCD_WeightCSVCErr1up",i, csvReweighter->getCSVWeight(ABCD_subjetPts,ABCD_subjetEtas,ABCD_subjetCSVs,ABCD_subjetFlavors,Systematics::CSVCErr1up, subjet_ABCD_csvWgtHF, subjet_ABCD_csvWgtLF, subjet_ABCD_csvWgtCF)/subjet_ABCD_csvweight);
     vars.FillVars("Topsubjets_ABCD_WeightCSVCErr1down",i, csvReweighter->getCSVWeight(ABCD_subjetPts,ABCD_subjetEtas,ABCD_subjetCSVs,ABCD_subjetFlavors,Systematics::CSVCErr1down, subjet_ABCD_csvWgtHF, subjet_ABCD_csvWgtLF, subjet_ABCD_csvWgtCF)/subjet_ABCD_csvweight);
     vars.FillVars("Topsubjets_ABCD_WeightCSVCErr2up",i, csvReweighter->getCSVWeight(ABCD_subjetPts,ABCD_subjetEtas,ABCD_subjetCSVs,ABCD_subjetFlavors,Systematics::CSVCErr2up, subjet_ABCD_csvWgtHF, subjet_ABCD_csvWgtLF, subjet_ABCD_csvWgtCF)/subjet_ABCD_csvweight);
     vars.FillVars("Topsubjets_ABCD_WeightCSVCErr2down",i, csvReweighter->getCSVWeight(ABCD_subjetPts,ABCD_subjetEtas,ABCD_subjetCSVs,ABCD_subjetFlavors,Systematics::CSVCErr2down, subjet_ABCD_csvWgtHF, subjet_ABCD_csvWgtLF, subjet_ABCD_csvWgtCF)/subjet_ABCD_csvweight);  
//      std::cout<<"debug4"<<endl;
         
    }     
     
  }

  
  ////FILL ABCD VARIABLES
  vars.FillVar("N_Zprimes_ABCDmasscorrnotopbtag",ZprimesABCDmasscorrnotopbtag.size());

  for (uint i=0; i<ZprimesABCDmasscorrnotopbtag.size(); i++){
  //for(math::XYZTLorentzVector::const_iterator ittopJet = AK8_top_candidates.begin() ; ittopJet != AK8_top_candidates.end(); ++ittopJet){
     //int i = 
     vars.FillVars("Zprimes_ABCD_masscorrnotopbtag_M",i,ZprimesABCDmasscorrnotopbtag[i].mass());
     vars.FillVars("Zprimes_ABCD_masscorrnotopbtag_Pt",i,ZprimesABCDmasscorrnotopbtag[i].pt());
     
     vars.FillVars("Tprimes_ABCD_masscorrnotopbtag_M",i,TprimesABCDmasscorrnotopbtag[i].mass());
     vars.FillVars("Tprimes_ABCD_masscorrnotopbtag_Pt",i,TprimesABCDmasscorrnotopbtag[i].pt());
     
     vars.FillVars("Bottoms_ABCD_masscorrnotopbtag_Pt",i,BottomsABCDmasscorrnotopbtag[i].pt());
     vars.FillVars("Bottoms_ABCD_masscorrnotopbtag_Eta",i,BottomsABCDmasscorrnotopbtag[i].eta());
     vars.FillVars("Bottoms_ABCD_masscorrnotopbtag_Phi",i,BottomsABCDmasscorrnotopbtag[i].phi());
     vars.FillVars("Bottoms_ABCD_masscorrnotopbtag_CSV",i,MiniAODHelper::GetJetCSV(BottomsABCDmasscorrnotopbtag[i],"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
     
//      CSVHelper csvReweighter=input.csvReweighter;
     std::vector<double> ABCD_masscorrnotopbtag_jetPts;
     std::vector<double> ABCD_masscorrnotopbtag_jetEtas;
     std::vector<double> ABCD_masscorrnotopbtag_jetCSVs;
     std::vector<int> ABCD_masscorrnotopbtag_jetFlavors;
     double ABCD_masscorrnotopbtag_csvWgtHF, ABCD_masscorrnotopbtag_csvWgtLF, ABCD_masscorrnotopbtag_csvWgtCF;
     float ABCD_csvweight = 1.;
     
     ABCD_masscorrnotopbtag_jetPts.push_back(BottomsABCDmasscorrnotopbtag[i].pt());
     ABCD_masscorrnotopbtag_jetEtas.push_back(BottomsABCDmasscorrnotopbtag[i].eta());
     ABCD_masscorrnotopbtag_jetCSVs.push_back(MiniAODHelper::GetJetCSV(BottomsABCDmasscorrnotopbtag[i],"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
     ABCD_masscorrnotopbtag_jetFlavors.push_back(BottomsABCDmasscorrnotopbtag[i].hadronFlavour());
     
     ABCD_csvweight= csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_jetPts,ABCD_masscorrnotopbtag_jetEtas,ABCD_masscorrnotopbtag_jetCSVs,ABCD_masscorrnotopbtag_jetFlavors,input.systematic, ABCD_masscorrnotopbtag_csvWgtHF, ABCD_masscorrnotopbtag_csvWgtLF, ABCD_masscorrnotopbtag_csvWgtCF);

    bool doSystematics=true;
//     if(doSystematics && input.input.systematic != sysType::JESup && input.input.systematic != sysType::JESdown && input.input.systematic != sysType::JERup && input.input.systematic != sysType::JERdown) {
     if(doSystematics && input.systematic == Systematics::NA) { // only do these for the nominal samples

     
     vars.FillVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVnominal",i,ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVLFup",i,csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_jetPts,ABCD_masscorrnotopbtag_jetEtas,ABCD_masscorrnotopbtag_jetCSVs,ABCD_masscorrnotopbtag_jetFlavors,Systematics::CSVLFup, ABCD_masscorrnotopbtag_csvWgtHF, ABCD_masscorrnotopbtag_csvWgtLF, ABCD_masscorrnotopbtag_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVLFdown",i,csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_jetPts,ABCD_masscorrnotopbtag_jetEtas,ABCD_masscorrnotopbtag_jetCSVs,ABCD_masscorrnotopbtag_jetFlavors,Systematics::CSVLFdown, ABCD_masscorrnotopbtag_csvWgtHF, ABCD_masscorrnotopbtag_csvWgtLF, ABCD_masscorrnotopbtag_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVHFup",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_jetPts,ABCD_masscorrnotopbtag_jetEtas,ABCD_masscorrnotopbtag_jetCSVs,ABCD_masscorrnotopbtag_jetFlavors,Systematics::CSVHFup, ABCD_masscorrnotopbtag_csvWgtHF, ABCD_masscorrnotopbtag_csvWgtLF, ABCD_masscorrnotopbtag_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVHFdown",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_jetPts,ABCD_masscorrnotopbtag_jetEtas,ABCD_masscorrnotopbtag_jetCSVs,ABCD_masscorrnotopbtag_jetFlavors,Systematics::CSVHFdown, ABCD_masscorrnotopbtag_csvWgtHF, ABCD_masscorrnotopbtag_csvWgtLF, ABCD_masscorrnotopbtag_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVHFStats1up",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_jetPts,ABCD_masscorrnotopbtag_jetEtas,ABCD_masscorrnotopbtag_jetCSVs,ABCD_masscorrnotopbtag_jetFlavors,Systematics::CSVHFStats1up, ABCD_masscorrnotopbtag_csvWgtHF, ABCD_masscorrnotopbtag_csvWgtLF, ABCD_masscorrnotopbtag_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVHFStats1down",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_jetPts,ABCD_masscorrnotopbtag_jetEtas,ABCD_masscorrnotopbtag_jetCSVs,ABCD_masscorrnotopbtag_jetFlavors,Systematics::CSVHFStats1down, ABCD_masscorrnotopbtag_csvWgtHF, ABCD_masscorrnotopbtag_csvWgtLF, ABCD_masscorrnotopbtag_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVLFStats1up",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_jetPts,ABCD_masscorrnotopbtag_jetEtas,ABCD_masscorrnotopbtag_jetCSVs,ABCD_masscorrnotopbtag_jetFlavors,Systematics::CSVLFStats1up, ABCD_masscorrnotopbtag_csvWgtHF, ABCD_masscorrnotopbtag_csvWgtLF, ABCD_masscorrnotopbtag_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVLFStats1down",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_jetPts,ABCD_masscorrnotopbtag_jetEtas,ABCD_masscorrnotopbtag_jetCSVs,ABCD_masscorrnotopbtag_jetFlavors,Systematics::CSVLFStats1down, ABCD_masscorrnotopbtag_csvWgtHF, ABCD_masscorrnotopbtag_csvWgtLF, ABCD_masscorrnotopbtag_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVHFStats2up",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_jetPts,ABCD_masscorrnotopbtag_jetEtas,ABCD_masscorrnotopbtag_jetCSVs,ABCD_masscorrnotopbtag_jetFlavors,Systematics::CSVHFStats2up, ABCD_masscorrnotopbtag_csvWgtHF, ABCD_masscorrnotopbtag_csvWgtLF, ABCD_masscorrnotopbtag_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVHFStats2down",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_jetPts,ABCD_masscorrnotopbtag_jetEtas,ABCD_masscorrnotopbtag_jetCSVs,ABCD_masscorrnotopbtag_jetFlavors,Systematics::CSVHFStats2down, ABCD_masscorrnotopbtag_csvWgtHF, ABCD_masscorrnotopbtag_csvWgtLF, ABCD_masscorrnotopbtag_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVLFStats2up",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_jetPts,ABCD_masscorrnotopbtag_jetEtas,ABCD_masscorrnotopbtag_jetCSVs,ABCD_masscorrnotopbtag_jetFlavors,Systematics::CSVLFStats2up, ABCD_masscorrnotopbtag_csvWgtHF, ABCD_masscorrnotopbtag_csvWgtLF, ABCD_masscorrnotopbtag_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVLFStats2down",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_jetPts,ABCD_masscorrnotopbtag_jetEtas,ABCD_masscorrnotopbtag_jetCSVs,ABCD_masscorrnotopbtag_jetFlavors,Systematics::CSVLFStats2down, ABCD_masscorrnotopbtag_csvWgtLF, ABCD_masscorrnotopbtag_csvWgtLF, ABCD_masscorrnotopbtag_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVCErr1up",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_jetPts,ABCD_masscorrnotopbtag_jetEtas,ABCD_masscorrnotopbtag_jetCSVs,ABCD_masscorrnotopbtag_jetFlavors,Systematics::CSVCErr1up, ABCD_masscorrnotopbtag_csvWgtLF, ABCD_masscorrnotopbtag_csvWgtLF, ABCD_masscorrnotopbtag_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVCErr1down",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_jetPts,ABCD_masscorrnotopbtag_jetEtas,ABCD_masscorrnotopbtag_jetCSVs,ABCD_masscorrnotopbtag_jetFlavors,Systematics::CSVCErr1down, ABCD_masscorrnotopbtag_csvWgtLF, ABCD_masscorrnotopbtag_csvWgtLF, ABCD_masscorrnotopbtag_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVCErr2up",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_jetPts,ABCD_masscorrnotopbtag_jetEtas,ABCD_masscorrnotopbtag_jetCSVs,ABCD_masscorrnotopbtag_jetFlavors,Systematics::CSVCErr2up, ABCD_masscorrnotopbtag_csvWgtLF, ABCD_masscorrnotopbtag_csvWgtLF, ABCD_masscorrnotopbtag_csvWgtCF)/ABCD_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrnotopbtag_WeightCSVCErr2down",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_jetPts,ABCD_masscorrnotopbtag_jetEtas,ABCD_masscorrnotopbtag_jetCSVs,ABCD_masscorrnotopbtag_jetFlavors,Systematics::CSVCErr2down, ABCD_masscorrnotopbtag_csvWgtLF, ABCD_masscorrnotopbtag_csvWgtLF, ABCD_masscorrnotopbtag_csvWgtCF)/ABCD_csvweight);  
    }
     
     vars.FillVars("Ws_ABCD_masscorrnotopbtag_Pt",i,WsABCDmasscorrnotopbtag[i].pt());
     vars.FillVars("Ws_ABCD_masscorrnotopbtag_Eta",i,WsABCDmasscorrnotopbtag[i].eta());
     vars.FillVars("Ws_ABCD_masscorrnotopbtag_Phi",i,WsABCDmasscorrnotopbtag[i].phi());
     vars.FillVars("Ws_ABCD_masscorrnotopbtag_MSD",i,WsABCDmasscorrnotopbtag[i].userFloat("ak8PFJetsCHSSoftDropMass"));
     vars.FillVars("Ws_ABCD_masscorrnotopbtag_t21",i,WsABCDmasscorrnotopbtag[i].userFloat("NjettinessAK8CHS:tau2")/WsABCDmasscorrnotopbtag[i].userFloat("NjettinessAK8CHS:tau1"));
     
     vars.FillVars("Tops_ABCD_masscorrnotopbtag_Pt",i,TopsABCDmasscorrnotopbtag[i].pt());
     vars.FillVars("Tops_ABCD_masscorrnotopbtag_Eta",i,TopsABCDmasscorrnotopbtag[i].eta());
     vars.FillVars("Tops_ABCD_masscorrnotopbtag_Phi",i,TopsABCDmasscorrnotopbtag[i].phi());
     vars.FillVars("Tops_ABCD_masscorrnotopbtag_MSD",i,TopsABCDmasscorrnotopbtag[i].userFloat("ak8PFJetsCHSSoftDropMass"));
     vars.FillVars("Tops_ABCD_masscorrnotopbtag_t32",i,TopsABCDmasscorrnotopbtag[i].userFloat("NjettinessAK8CHS:tau3")/TopsABCDmasscorrnotopbtag[i].userFloat("NjettinessAK8CHS:tau2"));


     std::vector<double> ABCD_masscorrnotopbtag_subjetPts;
     std::vector<double> ABCD_masscorrnotopbtag_subjetEtas;
     std::vector<double> ABCD_masscorrnotopbtag_subjetCSVs;
     std::vector<int> ABCD_masscorrnotopbtag_subjetFlavors;
     double subjet_ABCD_masscorrnotopbtag_csvWgtHF, subjet_ABCD_masscorrnotopbtag_csvWgtLF, subjet_ABCD_masscorrnotopbtag_csvWgtCF;
     float subjet_ABCD_masscorrnotopbtag_csvweight = 1.;
     

     
     double max_subjet_csv_v2=-10;
     auto const & names = TopsABCDmasscorrnotopbtag[i].subjets("SoftDrop");
     for( auto const & itsubJet : names ){
        if (itsubJet->pt()<20.0 || abs(itsubJet->eta())>2.4) continue;
        ABCD_masscorrnotopbtag_subjetPts.push_back(itsubJet->pt());
        ABCD_masscorrnotopbtag_subjetEtas.push_back(itsubJet->eta());
        ABCD_masscorrnotopbtag_subjetCSVs.push_back(MiniAODHelper::GetJetCSV(*itsubJet,"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
        ABCD_masscorrnotopbtag_subjetFlavors.push_back(itsubJet->hadronFlavour());
              
        if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>max_subjet_csv_v2){
            max_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
        };
     };
     
     
     vars.FillVars("Tops_ABCD_masscorrnotopbtag_maxsubjetCSVv2",i,max_subjet_csv_v2);
//      std::cout<<"max_subjet_csv_v2  "<<max_subjet_csv_v2<<endl;
     
     subjet_ABCD_masscorrnotopbtag_csvweight= csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_subjetPts,ABCD_masscorrnotopbtag_subjetEtas,ABCD_masscorrnotopbtag_subjetCSVs,ABCD_masscorrnotopbtag_subjetFlavors,input.systematic, subjet_ABCD_masscorrnotopbtag_csvWgtHF, subjet_ABCD_masscorrnotopbtag_csvWgtLF, subjet_ABCD_masscorrnotopbtag_csvWgtCF);
     
//     bool doSystematics=true;
//     if(doSystematics && input.input.systematic != sysType::JESup && input.input.systematic != sysType::JESdown && input.input.systematic != sysType::JERup && input.input.systematic != sysType::JERdown) {
     if(doSystematics && input.systematic == Systematics::NA) { // only do these for the nominal samples
     
     vars.FillVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVnominal",i,subjet_ABCD_masscorrnotopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVLFup",i,csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_subjetPts,ABCD_masscorrnotopbtag_subjetEtas,ABCD_masscorrnotopbtag_subjetCSVs,ABCD_masscorrnotopbtag_subjetFlavors,Systematics::CSVLFup, subjet_ABCD_masscorrnotopbtag_csvWgtHF, subjet_ABCD_masscorrnotopbtag_csvWgtLF, subjet_ABCD_masscorrnotopbtag_csvWgtCF)/subjet_ABCD_masscorrnotopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVLFdown",i,csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_subjetPts,ABCD_masscorrnotopbtag_subjetEtas,ABCD_masscorrnotopbtag_subjetCSVs,ABCD_masscorrnotopbtag_subjetFlavors,Systematics::CSVLFdown, subjet_ABCD_masscorrnotopbtag_csvWgtHF, subjet_ABCD_masscorrnotopbtag_csvWgtLF, subjet_ABCD_masscorrnotopbtag_csvWgtCF)/subjet_ABCD_masscorrnotopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVHFup",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_subjetPts,ABCD_masscorrnotopbtag_subjetEtas,ABCD_masscorrnotopbtag_subjetCSVs,ABCD_masscorrnotopbtag_subjetFlavors,Systematics::CSVHFup, subjet_ABCD_masscorrnotopbtag_csvWgtHF, subjet_ABCD_masscorrnotopbtag_csvWgtLF, subjet_ABCD_masscorrnotopbtag_csvWgtCF)/subjet_ABCD_masscorrnotopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVHFdown",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_subjetPts,ABCD_masscorrnotopbtag_subjetEtas,ABCD_masscorrnotopbtag_subjetCSVs,ABCD_masscorrnotopbtag_subjetFlavors,Systematics::CSVHFdown, subjet_ABCD_masscorrnotopbtag_csvWgtHF, subjet_ABCD_masscorrnotopbtag_csvWgtLF, subjet_ABCD_masscorrnotopbtag_csvWgtCF)/subjet_ABCD_masscorrnotopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVHFStats1up",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_subjetPts,ABCD_masscorrnotopbtag_subjetEtas,ABCD_masscorrnotopbtag_subjetCSVs,ABCD_masscorrnotopbtag_subjetFlavors,Systematics::CSVHFStats1up, subjet_ABCD_masscorrnotopbtag_csvWgtHF, subjet_ABCD_masscorrnotopbtag_csvWgtLF, subjet_ABCD_masscorrnotopbtag_csvWgtCF)/subjet_ABCD_masscorrnotopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVHFStats1down",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_subjetPts,ABCD_masscorrnotopbtag_subjetEtas,ABCD_masscorrnotopbtag_subjetCSVs,ABCD_masscorrnotopbtag_subjetFlavors,Systematics::CSVHFStats1down, subjet_ABCD_masscorrnotopbtag_csvWgtHF, subjet_ABCD_masscorrnotopbtag_csvWgtLF, subjet_ABCD_masscorrnotopbtag_csvWgtCF)/subjet_ABCD_masscorrnotopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVLFStats1up",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_subjetPts,ABCD_masscorrnotopbtag_subjetEtas,ABCD_masscorrnotopbtag_subjetCSVs,ABCD_masscorrnotopbtag_subjetFlavors,Systematics::CSVLFStats1up, subjet_ABCD_masscorrnotopbtag_csvWgtHF, subjet_ABCD_masscorrnotopbtag_csvWgtLF, subjet_ABCD_masscorrnotopbtag_csvWgtCF)/subjet_ABCD_masscorrnotopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVLFStats1down",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_subjetPts,ABCD_masscorrnotopbtag_subjetEtas,ABCD_masscorrnotopbtag_subjetCSVs,ABCD_masscorrnotopbtag_subjetFlavors,Systematics::CSVLFStats1down, subjet_ABCD_masscorrnotopbtag_csvWgtHF, subjet_ABCD_masscorrnotopbtag_csvWgtLF, subjet_ABCD_masscorrnotopbtag_csvWgtCF)/subjet_ABCD_masscorrnotopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVHFStats2up",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_subjetPts,ABCD_masscorrnotopbtag_subjetEtas,ABCD_masscorrnotopbtag_subjetCSVs,ABCD_masscorrnotopbtag_subjetFlavors,Systematics::CSVHFStats2up, subjet_ABCD_masscorrnotopbtag_csvWgtHF, subjet_ABCD_masscorrnotopbtag_csvWgtLF, subjet_ABCD_masscorrnotopbtag_csvWgtCF)/subjet_ABCD_masscorrnotopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVHFStats2down",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_subjetPts,ABCD_masscorrnotopbtag_subjetEtas,ABCD_masscorrnotopbtag_subjetCSVs,ABCD_masscorrnotopbtag_subjetFlavors,Systematics::CSVHFStats2down, subjet_ABCD_masscorrnotopbtag_csvWgtHF, subjet_ABCD_masscorrnotopbtag_csvWgtLF, subjet_ABCD_masscorrnotopbtag_csvWgtCF)/subjet_ABCD_masscorrnotopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVLFStats2up",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_subjetPts,ABCD_masscorrnotopbtag_subjetEtas,ABCD_masscorrnotopbtag_subjetCSVs,ABCD_masscorrnotopbtag_subjetFlavors,Systematics::CSVLFStats2up, subjet_ABCD_masscorrnotopbtag_csvWgtHF, subjet_ABCD_masscorrnotopbtag_csvWgtLF, subjet_ABCD_masscorrnotopbtag_csvWgtCF)/subjet_ABCD_masscorrnotopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVLFStats2down",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_subjetPts,ABCD_masscorrnotopbtag_subjetEtas,ABCD_masscorrnotopbtag_subjetCSVs,ABCD_masscorrnotopbtag_subjetFlavors,Systematics::CSVLFStats2down, subjet_ABCD_masscorrnotopbtag_csvWgtHF, subjet_ABCD_masscorrnotopbtag_csvWgtLF, subjet_ABCD_masscorrnotopbtag_csvWgtCF)/subjet_ABCD_masscorrnotopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVCErr1up",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_subjetPts,ABCD_masscorrnotopbtag_subjetEtas,ABCD_masscorrnotopbtag_subjetCSVs,ABCD_masscorrnotopbtag_subjetFlavors,Systematics::CSVCErr1up, subjet_ABCD_masscorrnotopbtag_csvWgtHF, subjet_ABCD_masscorrnotopbtag_csvWgtLF, subjet_ABCD_masscorrnotopbtag_csvWgtCF)/subjet_ABCD_masscorrnotopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVCErr1down",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_subjetPts,ABCD_masscorrnotopbtag_subjetEtas,ABCD_masscorrnotopbtag_subjetCSVs,ABCD_masscorrnotopbtag_subjetFlavors,Systematics::CSVCErr1down, subjet_ABCD_masscorrnotopbtag_csvWgtHF, subjet_ABCD_masscorrnotopbtag_csvWgtLF, subjet_ABCD_masscorrnotopbtag_csvWgtCF)/subjet_ABCD_masscorrnotopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVCErr2up",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_subjetPts,ABCD_masscorrnotopbtag_subjetEtas,ABCD_masscorrnotopbtag_subjetCSVs,ABCD_masscorrnotopbtag_subjetFlavors,Systematics::CSVCErr2up, subjet_ABCD_masscorrnotopbtag_csvWgtHF, subjet_ABCD_masscorrnotopbtag_csvWgtLF, subjet_ABCD_masscorrnotopbtag_csvWgtCF)/subjet_ABCD_masscorrnotopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrnotopbtag_WeightCSVCErr2down",i, csvReweighter->getCSVWeight(ABCD_masscorrnotopbtag_subjetPts,ABCD_masscorrnotopbtag_subjetEtas,ABCD_masscorrnotopbtag_subjetCSVs,ABCD_masscorrnotopbtag_subjetFlavors,Systematics::CSVCErr2down, subjet_ABCD_masscorrnotopbtag_csvWgtHF, subjet_ABCD_masscorrnotopbtag_csvWgtLF, subjet_ABCD_masscorrnotopbtag_csvWgtCF)/subjet_ABCD_masscorrnotopbtag_csvweight);  
    
         
    }     
     
  }

  vars.FillVar("N_Zprimes_ABCDmasscorrwithtopbtag",ZprimesABCDmasscorrwithtopbtag.size());

  for (uint i=0; i<ZprimesABCDmasscorrwithtopbtag.size(); i++){
  //for(math::XYZTLorentzVector::const_iterator ittopJet = AK8_top_candidates.begin() ; ittopJet != AK8_top_candidates.end(); ++ittopJet){
     //int i = 
     vars.FillVars("Zprimes_ABCD_masscorrwithtopbtag_M",i,ZprimesABCDmasscorrwithtopbtag[i].mass());
     vars.FillVars("Zprimes_ABCD_masscorrwithtopbtag_Pt",i,ZprimesABCDmasscorrwithtopbtag[i].pt());
     
     vars.FillVars("Tprimes_ABCD_masscorrwithtopbtag_M",i,TprimesABCDmasscorrwithtopbtag[i].mass());
     vars.FillVars("Tprimes_ABCD_masscorrwithtopbtag_Pt",i,TprimesABCDmasscorrwithtopbtag[i].pt());
     
     vars.FillVars("Bottoms_ABCD_masscorrwithtopbtag_Pt",i,BottomsABCDmasscorrwithtopbtag[i].pt());
     vars.FillVars("Bottoms_ABCD_masscorrwithtopbtag_Eta",i,BottomsABCDmasscorrwithtopbtag[i].eta());
     vars.FillVars("Bottoms_ABCD_masscorrwithtopbtag_Phi",i,BottomsABCDmasscorrwithtopbtag[i].phi());
     vars.FillVars("Bottoms_ABCD_masscorrwithtopbtag_CSV",i,MiniAODHelper::GetJetCSV(BottomsABCDmasscorrwithtopbtag[i],"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
     
//      CSVHelper csvReweighter;
     std::vector<double> ABCD_masscorrwithtopbtag_jetPts;
     std::vector<double> ABCD_masscorrwithtopbtag_jetEtas;
     std::vector<double> ABCD_masscorrwithtopbtag_jetCSVs;
     std::vector<int> ABCD_masscorrwithtopbtag_jetFlavors;
     double ABCD_masscorrwithtopbtag_csvWgtHF, ABCD_masscorrwithtopbtag_csvWgtLF, ABCD_masscorrwithtopbtag_csvWgtCF;
     float ABCD_masscorrwithtopbtag_csvweight = 1.;
     
     ABCD_masscorrwithtopbtag_jetPts.push_back(BottomsABCDmasscorrwithtopbtag[i].pt());
     ABCD_masscorrwithtopbtag_jetEtas.push_back(BottomsABCDmasscorrwithtopbtag[i].eta());
     ABCD_masscorrwithtopbtag_jetCSVs.push_back(MiniAODHelper::GetJetCSV(BottomsABCDmasscorrwithtopbtag[i],"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
     ABCD_masscorrwithtopbtag_jetFlavors.push_back(BottomsABCDmasscorrwithtopbtag[i].hadronFlavour());
     
     ABCD_masscorrwithtopbtag_csvweight= csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_jetPts,ABCD_masscorrwithtopbtag_jetEtas,ABCD_masscorrwithtopbtag_jetCSVs,ABCD_masscorrwithtopbtag_jetFlavors,input.systematic, ABCD_masscorrwithtopbtag_csvWgtHF, ABCD_masscorrwithtopbtag_csvWgtLF, ABCD_masscorrwithtopbtag_csvWgtCF);
     

    bool doSystematics=true;
//     if(doSystematics && input.input.systematic != sysType::JESup && input.input.systematic != sysType::JESdown && input.input.systematic != sysType::JERup && input.input.systematic != sysType::JERdown) {
     if(doSystematics && input.systematic == Systematics::NA) { // only do these for the nominal samples

     
     vars.FillVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVnominal",i,ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVLFup",i,csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_jetPts,ABCD_masscorrwithtopbtag_jetEtas,ABCD_masscorrwithtopbtag_jetCSVs,ABCD_masscorrwithtopbtag_jetFlavors,Systematics::CSVLFup, ABCD_masscorrwithtopbtag_csvWgtHF, ABCD_masscorrwithtopbtag_csvWgtLF, ABCD_masscorrwithtopbtag_csvWgtCF)/ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVLFdown",i,csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_jetPts,ABCD_masscorrwithtopbtag_jetEtas,ABCD_masscorrwithtopbtag_jetCSVs,ABCD_masscorrwithtopbtag_jetFlavors,Systematics::CSVLFdown, ABCD_masscorrwithtopbtag_csvWgtHF, ABCD_masscorrwithtopbtag_csvWgtLF, ABCD_masscorrwithtopbtag_csvWgtCF)/ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVHFup",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_jetPts,ABCD_masscorrwithtopbtag_jetEtas,ABCD_masscorrwithtopbtag_jetCSVs,ABCD_masscorrwithtopbtag_jetFlavors,Systematics::CSVHFup, ABCD_masscorrwithtopbtag_csvWgtHF, ABCD_masscorrwithtopbtag_csvWgtLF, ABCD_masscorrwithtopbtag_csvWgtCF)/ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVHFdown",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_jetPts,ABCD_masscorrwithtopbtag_jetEtas,ABCD_masscorrwithtopbtag_jetCSVs,ABCD_masscorrwithtopbtag_jetFlavors,Systematics::CSVHFdown, ABCD_masscorrwithtopbtag_csvWgtHF, ABCD_masscorrwithtopbtag_csvWgtLF, ABCD_masscorrwithtopbtag_csvWgtCF)/ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVHFStats1up",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_jetPts,ABCD_masscorrwithtopbtag_jetEtas,ABCD_masscorrwithtopbtag_jetCSVs,ABCD_masscorrwithtopbtag_jetFlavors,Systematics::CSVHFStats1up, ABCD_masscorrwithtopbtag_csvWgtHF, ABCD_masscorrwithtopbtag_csvWgtLF, ABCD_masscorrwithtopbtag_csvWgtCF)/ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVHFStats1down",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_jetPts,ABCD_masscorrwithtopbtag_jetEtas,ABCD_masscorrwithtopbtag_jetCSVs,ABCD_masscorrwithtopbtag_jetFlavors,Systematics::CSVHFStats1down, ABCD_masscorrwithtopbtag_csvWgtHF, ABCD_masscorrwithtopbtag_csvWgtLF, ABCD_masscorrwithtopbtag_csvWgtCF)/ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVLFStats1up",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_jetPts,ABCD_masscorrwithtopbtag_jetEtas,ABCD_masscorrwithtopbtag_jetCSVs,ABCD_masscorrwithtopbtag_jetFlavors,Systematics::CSVLFStats1up, ABCD_masscorrwithtopbtag_csvWgtHF, ABCD_masscorrwithtopbtag_csvWgtLF, ABCD_masscorrwithtopbtag_csvWgtCF)/ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVLFStats1down",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_jetPts,ABCD_masscorrwithtopbtag_jetEtas,ABCD_masscorrwithtopbtag_jetCSVs,ABCD_masscorrwithtopbtag_jetFlavors,Systematics::CSVLFStats1down, ABCD_masscorrwithtopbtag_csvWgtHF, ABCD_masscorrwithtopbtag_csvWgtLF, ABCD_masscorrwithtopbtag_csvWgtCF)/ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVHFStats2up",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_jetPts,ABCD_masscorrwithtopbtag_jetEtas,ABCD_masscorrwithtopbtag_jetCSVs,ABCD_masscorrwithtopbtag_jetFlavors,Systematics::CSVHFStats2up, ABCD_masscorrwithtopbtag_csvWgtHF, ABCD_masscorrwithtopbtag_csvWgtLF, ABCD_masscorrwithtopbtag_csvWgtCF)/ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVHFStats2down",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_jetPts,ABCD_masscorrwithtopbtag_jetEtas,ABCD_masscorrwithtopbtag_jetCSVs,ABCD_masscorrwithtopbtag_jetFlavors,Systematics::CSVHFStats2down, ABCD_masscorrwithtopbtag_csvWgtHF, ABCD_masscorrwithtopbtag_csvWgtLF, ABCD_masscorrwithtopbtag_csvWgtCF)/ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVLFStats2up",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_jetPts,ABCD_masscorrwithtopbtag_jetEtas,ABCD_masscorrwithtopbtag_jetCSVs,ABCD_masscorrwithtopbtag_jetFlavors,Systematics::CSVLFStats2up, ABCD_masscorrwithtopbtag_csvWgtHF, ABCD_masscorrwithtopbtag_csvWgtLF, ABCD_masscorrwithtopbtag_csvWgtCF)/ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVLFStats2down",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_jetPts,ABCD_masscorrwithtopbtag_jetEtas,ABCD_masscorrwithtopbtag_jetCSVs,ABCD_masscorrwithtopbtag_jetFlavors,Systematics::CSVLFStats2down, ABCD_masscorrwithtopbtag_csvWgtHF, ABCD_masscorrwithtopbtag_csvWgtLF, ABCD_masscorrwithtopbtag_csvWgtCF)/ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVCErr1up",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_jetPts,ABCD_masscorrwithtopbtag_jetEtas,ABCD_masscorrwithtopbtag_jetCSVs,ABCD_masscorrwithtopbtag_jetFlavors,Systematics::CSVCErr1up, ABCD_masscorrwithtopbtag_csvWgtHF, ABCD_masscorrwithtopbtag_csvWgtLF, ABCD_masscorrwithtopbtag_csvWgtCF)/ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVCErr1down",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_jetPts,ABCD_masscorrwithtopbtag_jetEtas,ABCD_masscorrwithtopbtag_jetCSVs,ABCD_masscorrwithtopbtag_jetFlavors,Systematics::CSVCErr1down, ABCD_masscorrwithtopbtag_csvWgtHF, ABCD_masscorrwithtopbtag_csvWgtLF, ABCD_masscorrwithtopbtag_csvWgtCF)/ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVCErr2up",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_jetPts,ABCD_masscorrwithtopbtag_jetEtas,ABCD_masscorrwithtopbtag_jetCSVs,ABCD_masscorrwithtopbtag_jetFlavors,Systematics::CSVCErr2up, ABCD_masscorrwithtopbtag_csvWgtHF, ABCD_masscorrwithtopbtag_csvWgtLF, ABCD_masscorrwithtopbtag_csvWgtCF)/ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Bottoms_ABCD_masscorrwithtopbtag_WeightCSVCErr2down",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_jetPts,ABCD_masscorrwithtopbtag_jetEtas,ABCD_masscorrwithtopbtag_jetCSVs,ABCD_masscorrwithtopbtag_jetFlavors,Systematics::CSVCErr2down, ABCD_masscorrwithtopbtag_csvWgtHF, ABCD_masscorrwithtopbtag_csvWgtLF, ABCD_masscorrwithtopbtag_csvWgtCF)/ABCD_masscorrwithtopbtag_csvweight);  
    }

     
     
     vars.FillVars("Ws_ABCD_masscorrwithtopbtag_Pt",i,WsABCDmasscorrwithtopbtag[i].pt());
     vars.FillVars("Ws_ABCD_masscorrwithtopbtag_Eta",i,WsABCDmasscorrwithtopbtag[i].eta());
     vars.FillVars("Ws_ABCD_masscorrwithtopbtag_Phi",i,WsABCDmasscorrwithtopbtag[i].phi());
     vars.FillVars("Ws_ABCD_masscorrwithtopbtag_MSD",i,WsABCDmasscorrwithtopbtag[i].userFloat("ak8PFJetsCHSSoftDropMass"));
     vars.FillVars("Ws_ABCD_masscorrwithtopbtag_t21",i,WsABCDmasscorrwithtopbtag[i].userFloat("NjettinessAK8CHS:tau2")/WsABCDmasscorrwithtopbtag[i].userFloat("NjettinessAK8CHS:tau1"));
     
     vars.FillVars("Tops_ABCD_masscorrwithtopbtag_Pt",i,TopsABCDmasscorrwithtopbtag[i].pt());
     vars.FillVars("Tops_ABCD_masscorrwithtopbtag_Eta",i,TopsABCDmasscorrwithtopbtag[i].eta());
     vars.FillVars("Tops_ABCD_masscorrwithtopbtag_Phi",i,TopsABCDmasscorrwithtopbtag[i].phi());
     vars.FillVars("Tops_ABCD_masscorrwithtopbtag_MSD",i,TopsABCDmasscorrwithtopbtag[i].userFloat("ak8PFJetsCHSSoftDropMass"));
     vars.FillVars("Tops_ABCD_masscorrwithtopbtag_t32",i,TopsABCDmasscorrwithtopbtag[i].userFloat("NjettinessAK8CHS:tau3")/TopsABCDmasscorrwithtopbtag[i].userFloat("NjettinessAK8CHS:tau2"));



     std::vector<double> ABCD_masscorrwithtopbtag_subjetPts;
     std::vector<double> ABCD_masscorrwithtopbtag_subjetEtas;
     std::vector<double> ABCD_masscorrwithtopbtag_subjetCSVs;
     std::vector<int> ABCD_masscorrwithtopbtag_subjetFlavors;
     double subjet_ABCD_masscorrwithtopbtag_csvWgtHF, subjet_ABCD_masscorrwithtopbtag_csvWgtLF, subjet_ABCD_masscorrwithtopbtag_csvWgtCF;
     float subjet_ABCD_masscorrwithtopbtag_csvweight = 1.;
     

     
     double max_subjet_csv_v2=-10;
     auto const & names = TopsABCDmasscorrwithtopbtag[i].subjets("SoftDrop");
     for( auto const & itsubJet : names ){
        if (itsubJet->pt()<20.0 || abs(itsubJet->eta())>2.4) continue;
        ABCD_masscorrwithtopbtag_subjetPts.push_back(itsubJet->pt());
        ABCD_masscorrwithtopbtag_subjetEtas.push_back(itsubJet->eta());
        ABCD_masscorrwithtopbtag_subjetCSVs.push_back(MiniAODHelper::GetJetCSV(*itsubJet,"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
        ABCD_masscorrwithtopbtag_subjetFlavors.push_back(itsubJet->hadronFlavour());
              
        if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>max_subjet_csv_v2){
            max_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
        };
     };
     
     
     vars.FillVars("Tops_ABCD_masscorrwithtopbtag_maxsubjetCSVv2",i,max_subjet_csv_v2);
//      std::cout<<"max_subjet_csv_v2  "<<max_subjet_csv_v2<<endl;
     
     subjet_ABCD_masscorrwithtopbtag_csvweight= csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_subjetPts,ABCD_masscorrwithtopbtag_subjetEtas,ABCD_masscorrwithtopbtag_subjetCSVs,ABCD_masscorrwithtopbtag_subjetFlavors,input.systematic, subjet_ABCD_masscorrwithtopbtag_csvWgtHF, subjet_ABCD_masscorrwithtopbtag_csvWgtLF, subjet_ABCD_masscorrwithtopbtag_csvWgtCF);
     
//     bool doSystematics=true;
//     if(doSystematics && input.input.systematic != sysType::JESup && input.input.systematic != sysType::JESdown && input.input.systematic != sysType::JERup && input.input.systematic != sysType::JERdown) {
     if(doSystematics && input.systematic == Systematics::NA) { // only do these for the nominal samples
     
     vars.FillVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVnominal",i,subjet_ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVLFup",i,csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_subjetPts,ABCD_masscorrwithtopbtag_subjetEtas,ABCD_masscorrwithtopbtag_subjetCSVs,ABCD_masscorrwithtopbtag_subjetFlavors,Systematics::CSVLFup, subjet_ABCD_masscorrwithtopbtag_csvWgtHF, subjet_ABCD_masscorrwithtopbtag_csvWgtLF, subjet_ABCD_masscorrwithtopbtag_csvWgtCF)/subjet_ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVLFdown",i,csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_subjetPts,ABCD_masscorrwithtopbtag_subjetEtas,ABCD_masscorrwithtopbtag_subjetCSVs,ABCD_masscorrwithtopbtag_subjetFlavors,Systematics::CSVLFdown, subjet_ABCD_masscorrwithtopbtag_csvWgtHF, subjet_ABCD_masscorrwithtopbtag_csvWgtLF, subjet_ABCD_masscorrwithtopbtag_csvWgtCF)/subjet_ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVHFup",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_subjetPts,ABCD_masscorrwithtopbtag_subjetEtas,ABCD_masscorrwithtopbtag_subjetCSVs,ABCD_masscorrwithtopbtag_subjetFlavors,Systematics::CSVHFup, subjet_ABCD_masscorrwithtopbtag_csvWgtHF, subjet_ABCD_masscorrwithtopbtag_csvWgtLF, subjet_ABCD_masscorrwithtopbtag_csvWgtCF)/subjet_ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVHFdown",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_subjetPts,ABCD_masscorrwithtopbtag_subjetEtas,ABCD_masscorrwithtopbtag_subjetCSVs,ABCD_masscorrwithtopbtag_subjetFlavors,Systematics::CSVHFdown, subjet_ABCD_masscorrwithtopbtag_csvWgtHF, subjet_ABCD_masscorrwithtopbtag_csvWgtLF, subjet_ABCD_masscorrwithtopbtag_csvWgtCF)/subjet_ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVHFStats1up",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_subjetPts,ABCD_masscorrwithtopbtag_subjetEtas,ABCD_masscorrwithtopbtag_subjetCSVs,ABCD_masscorrwithtopbtag_subjetFlavors,Systematics::CSVHFStats1up, subjet_ABCD_masscorrwithtopbtag_csvWgtHF, subjet_ABCD_masscorrwithtopbtag_csvWgtLF, subjet_ABCD_masscorrwithtopbtag_csvWgtCF)/subjet_ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVHFStats1down",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_subjetPts,ABCD_masscorrwithtopbtag_subjetEtas,ABCD_masscorrwithtopbtag_subjetCSVs,ABCD_masscorrwithtopbtag_subjetFlavors,Systematics::CSVHFStats1down, subjet_ABCD_masscorrwithtopbtag_csvWgtHF, subjet_ABCD_masscorrwithtopbtag_csvWgtLF, subjet_ABCD_masscorrwithtopbtag_csvWgtCF)/subjet_ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVLFStats1up",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_subjetPts,ABCD_masscorrwithtopbtag_subjetEtas,ABCD_masscorrwithtopbtag_subjetCSVs,ABCD_masscorrwithtopbtag_subjetFlavors,Systematics::CSVLFStats1up, subjet_ABCD_masscorrwithtopbtag_csvWgtHF, subjet_ABCD_masscorrwithtopbtag_csvWgtLF, subjet_ABCD_masscorrwithtopbtag_csvWgtCF)/subjet_ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVLFStats1down",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_subjetPts,ABCD_masscorrwithtopbtag_subjetEtas,ABCD_masscorrwithtopbtag_subjetCSVs,ABCD_masscorrwithtopbtag_subjetFlavors,Systematics::CSVLFStats1down, subjet_ABCD_masscorrwithtopbtag_csvWgtHF, subjet_ABCD_masscorrwithtopbtag_csvWgtLF, subjet_ABCD_masscorrwithtopbtag_csvWgtCF)/subjet_ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVHFStats2up",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_subjetPts,ABCD_masscorrwithtopbtag_subjetEtas,ABCD_masscorrwithtopbtag_subjetCSVs,ABCD_masscorrwithtopbtag_subjetFlavors,Systematics::CSVHFStats2up, subjet_ABCD_masscorrwithtopbtag_csvWgtHF, subjet_ABCD_masscorrwithtopbtag_csvWgtLF, subjet_ABCD_masscorrwithtopbtag_csvWgtCF)/subjet_ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVHFStats2down",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_subjetPts,ABCD_masscorrwithtopbtag_subjetEtas,ABCD_masscorrwithtopbtag_subjetCSVs,ABCD_masscorrwithtopbtag_subjetFlavors,Systematics::CSVHFStats2down, subjet_ABCD_masscorrwithtopbtag_csvWgtHF, subjet_ABCD_masscorrwithtopbtag_csvWgtLF, subjet_ABCD_masscorrwithtopbtag_csvWgtCF)/subjet_ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVLFStats2up",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_subjetPts,ABCD_masscorrwithtopbtag_subjetEtas,ABCD_masscorrwithtopbtag_subjetCSVs,ABCD_masscorrwithtopbtag_subjetFlavors,Systematics::CSVLFStats2up, subjet_ABCD_masscorrwithtopbtag_csvWgtHF, subjet_ABCD_masscorrwithtopbtag_csvWgtLF, subjet_ABCD_masscorrwithtopbtag_csvWgtCF)/subjet_ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVLFStats2down",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_subjetPts,ABCD_masscorrwithtopbtag_subjetEtas,ABCD_masscorrwithtopbtag_subjetCSVs,ABCD_masscorrwithtopbtag_subjetFlavors,Systematics::CSVLFStats2down, subjet_ABCD_masscorrwithtopbtag_csvWgtHF, subjet_ABCD_masscorrwithtopbtag_csvWgtLF, subjet_ABCD_masscorrwithtopbtag_csvWgtCF)/subjet_ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVCErr1up",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_subjetPts,ABCD_masscorrwithtopbtag_subjetEtas,ABCD_masscorrwithtopbtag_subjetCSVs,ABCD_masscorrwithtopbtag_subjetFlavors,Systematics::CSVCErr1up, subjet_ABCD_masscorrwithtopbtag_csvWgtHF, subjet_ABCD_masscorrwithtopbtag_csvWgtLF, subjet_ABCD_masscorrwithtopbtag_csvWgtCF)/subjet_ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVCErr1down",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_subjetPts,ABCD_masscorrwithtopbtag_subjetEtas,ABCD_masscorrwithtopbtag_subjetCSVs,ABCD_masscorrwithtopbtag_subjetFlavors,Systematics::CSVCErr1down, subjet_ABCD_masscorrwithtopbtag_csvWgtHF, subjet_ABCD_masscorrwithtopbtag_csvWgtLF, subjet_ABCD_masscorrwithtopbtag_csvWgtCF)/subjet_ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVCErr2up",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_subjetPts,ABCD_masscorrwithtopbtag_subjetEtas,ABCD_masscorrwithtopbtag_subjetCSVs,ABCD_masscorrwithtopbtag_subjetFlavors,Systematics::CSVCErr2up, subjet_ABCD_masscorrwithtopbtag_csvWgtHF, subjet_ABCD_masscorrwithtopbtag_csvWgtLF, subjet_ABCD_masscorrwithtopbtag_csvWgtCF)/subjet_ABCD_masscorrwithtopbtag_csvweight);
     vars.FillVars("Topsubjets_ABCD_masscorrwithtopbtag_WeightCSVCErr2down",i, csvReweighter->getCSVWeight(ABCD_masscorrwithtopbtag_subjetPts,ABCD_masscorrwithtopbtag_subjetEtas,ABCD_masscorrwithtopbtag_subjetCSVs,ABCD_masscorrwithtopbtag_subjetFlavors,Systematics::CSVCErr2down, subjet_ABCD_masscorrwithtopbtag_csvWgtHF, subjet_ABCD_masscorrwithtopbtag_csvWgtLF, subjet_ABCD_masscorrwithtopbtag_csvWgtCF)/subjet_ABCD_masscorrwithtopbtag_csvweight);  
     }
  }
  
/*
  ////FILL ABCD_tAK15WAK15bAK4 VARIABLES
  vars.FillVar("N_Zprime_ABCD_tAK15WAK15bAK4",Zprimes_ABCD_tAK15WAK15bAK4.size());

  for (uint i=0; i<Zprimes_ABCD_tAK15WAK15bAK4.size(); i++){
  //for(math::XYZTLorentzVector::const_iterator ittopJet = AK8_top_candidates.begin() ; ittopJet != AK8_top_candidates.end(); ++ittopJet){
     //int i = 
     vars.FillVars("Zprimes_ABCD_tAK15WAK15bAK4_M",i,Zprimes_ABCD_tAK15WAK15bAK4[i].mass());
     vars.FillVars("Zprimes_ABCD_tAK15WAK15bAK4_Pt",i,Zprimes_ABCD_tAK15WAK15bAK4[i].pt());
     
     vars.FillVars("Tprimes_ABCD_tAK15WAK15bAK4_M",i,Tprimes_ABCD_tAK15WAK15bAK4[i].mass());
     vars.FillVars("Tprimes_ABCD_tAK15WAK15bAK4_Pt",i,Tprimes_ABCD_tAK15WAK15bAK4[i].pt());
     
     vars.FillVars("Bottoms_ABCD_tAK15WAK15bAK4_Pt",i,Bottoms_ABCD_tAK15WAK15bAK4[i].pt());
     vars.FillVars("Bottoms_ABCD_tAK15WAK15bAK4_Eta",i,Bottoms_ABCD_tAK15WAK15bAK4[i].eta());
     vars.FillVars("Bottoms_ABCD_tAK15WAK15bAK4_Phi",i,Bottoms_ABCD_tAK15WAK15bAK4[i].phi());
     vars.FillVars("Bottoms_ABCD_tAK15WAK15bAK4_CSV",i,MiniAODHelper::GetJetCSV(Bottoms_ABCD_tAK15WAK15bAK4[i],"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
     
     vars.FillVars("Ws_ABCD_tAK15WAK15bAK4_Pt",i,Ws_ABCD_tAK15WAK15bAK4[i].pt());
     vars.FillVars("Ws_ABCD_tAK15WAK15bAK4_Eta",i,Ws_ABCD_tAK15WAK15bAK4[i].eta());
     vars.FillVars("Ws_ABCD_tAK15WAK15bAK4_Phi",i,Ws_ABCD_tAK15WAK15bAK4[i].phi());
     vars.FillVars("Ws_ABCD_tAK15WAK15bAK4_MSD",i,Ws_ABCD_tAK15WAK15bAK4[i].userFloat("ak15PFJetsCHSSoftDropMass"));
     vars.FillVars("Ws_ABCD_tAK15WAK15bAK4_t21",i,Ws_ABCD_tAK15WAK15bAK4[i].userFloat("NjettinessAK15CHS:tau2")/Ws_ABCD_tAK15WAK15bAK4[i].userFloat("NjettinessAK15CHS:tau1"));
     
     vars.FillVars("Tops_ABCD_tAK15WAK15bAK4_Pt",i,Tops_ABCD_tAK15WAK15bAK4[i].pt());
     vars.FillVars("Tops_ABCD_tAK15WAK15bAK4_Eta",i,Tops_ABCD_tAK15WAK15bAK4[i].eta());
     vars.FillVars("Tops_ABCD_tAK15WAK15bAK4_Phi",i,Tops_ABCD_tAK15WAK15bAK4[i].phi());
     vars.FillVars("Tops_ABCD_tAK15WAK15bAK4_MSD",i,Tops_ABCD_tAK15WAK15bAK4[i].userFloat("ak15PFJetsCHSSoftDropMass"));
     vars.FillVars("Tops_ABCD_tAK15WAK15bAK4_t32",i,Tops_ABCD_tAK15WAK15bAK4[i].userFloat("NjettinessAK15CHS:tau3")/Tops_ABCD_tAK15WAK15bAK4[i].userFloat("NjettinessAK15CHS:tau2"));

     double max_subjet_csv_v2=-10;
     auto const & names = Tops_ABCD_tAK15WAK15bAK4[i].subjets("SoftDrop");
     for( auto const & itsubJet : names ){
        if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>max_subjet_csv_v2){
            max_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
        };
     };
     vars.FillVars("Tops_ABCD_tAK15WAK15bAK4_maxsubjetCSVv2",i,max_subjet_csv_v2);
//      std::cout<<"max_subjet_csv_v2  "<<max_subjet_csv_v2<<endl;
  }
*/

  ////FILL ABCD_tAK15WAK8bAK4 VARIABLES
  vars.FillVar("N_Zprime_ABCD_tAK15WAK8bAK4",Zprimes_ABCD_tAK15WAK8bAK4.size());

  for (uint i=0; i<Zprimes_ABCD_tAK15WAK8bAK4.size(); i++){
  //for(math::XYZTLorentzVector::const_iterator ittopJet = AK8_top_candidates.begin() ; ittopJet != AK8_top_candidates.end(); ++ittopJet){
     //int i = 
     vars.FillVars("Zprimes_ABCD_tAK15WAK8bAK4_M",i,Zprimes_ABCD_tAK15WAK8bAK4[i].mass());
     vars.FillVars("Zprimes_ABCD_tAK15WAK8bAK4_Pt",i,Zprimes_ABCD_tAK15WAK8bAK4[i].pt());
     
     vars.FillVars("Tprimes_ABCD_tAK15WAK8bAK4_M",i,Tprimes_ABCD_tAK15WAK8bAK4[i].mass());
     vars.FillVars("Tprimes_ABCD_tAK15WAK8bAK4_Pt",i,Tprimes_ABCD_tAK15WAK8bAK4[i].pt());
     
     vars.FillVars("Bottoms_ABCD_tAK15WAK8bAK4_Pt",i,Bottoms_ABCD_tAK15WAK8bAK4[i].pt());
     vars.FillVars("Bottoms_ABCD_tAK15WAK8bAK4_Eta",i,Bottoms_ABCD_tAK15WAK8bAK4[i].eta());
     vars.FillVars("Bottoms_ABCD_tAK15WAK8bAK4_Phi",i,Bottoms_ABCD_tAK15WAK8bAK4[i].phi());
     vars.FillVars("Bottoms_ABCD_tAK15WAK8bAK4_CSV",i,MiniAODHelper::GetJetCSV(Bottoms_ABCD_tAK15WAK8bAK4[i],"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
     
//      CSVHelper csvReweighter;
     std::vector<double> ABCD_tAK15WAK8bAK4_jetPts;
     std::vector<double> ABCD_tAK15WAK8bAK4_jetEtas;
     std::vector<double> ABCD_tAK15WAK8bAK4_jetCSVs;
     std::vector<int> ABCD_tAK15WAK8bAK4_jetFlavors;
     double ABCD_tAK15WAK8bAK4_csvWgtHF, ABCD_tAK15WAK8bAK4_csvWgtLF, ABCD_tAK15WAK8bAK4_csvWgtCF;
     float ABCD_tAK15WAK8bAK4_csvweight = 1.;
     
     ABCD_tAK15WAK8bAK4_jetPts.push_back(Bottoms_ABCD_tAK15WAK8bAK4[i].pt());
     ABCD_tAK15WAK8bAK4_jetEtas.push_back(Bottoms_ABCD_tAK15WAK8bAK4[i].eta());
     ABCD_tAK15WAK8bAK4_jetCSVs.push_back(MiniAODHelper::GetJetCSV(Bottoms_ABCD_tAK15WAK8bAK4[i],"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
     ABCD_tAK15WAK8bAK4_jetFlavors.push_back(Bottoms_ABCD_tAK15WAK8bAK4[i].hadronFlavour());
     
     

     ABCD_tAK15WAK8bAK4_csvweight= csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_jetPts,ABCD_tAK15WAK8bAK4_jetEtas,ABCD_tAK15WAK8bAK4_jetCSVs,ABCD_tAK15WAK8bAK4_jetFlavors,input.systematic, ABCD_tAK15WAK8bAK4_csvWgtHF, ABCD_tAK15WAK8bAK4_csvWgtLF, ABCD_tAK15WAK8bAK4_csvWgtCF);


    bool doSystematics=true;
//     if(doSystematics && input.input.systematic != sysType::JESup && input.input.systematic != sysType::JESdown && input.input.systematic != sysType::JERup && input.input.systematic != sysType::JERdown) {
     if(doSystematics && input.systematic == Systematics::NA) { // only do these for the nominal samples

     
     vars.FillVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVnominal",i,ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVLFup",i,csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_jetPts,ABCD_tAK15WAK8bAK4_jetEtas,ABCD_tAK15WAK8bAK4_jetCSVs,ABCD_tAK15WAK8bAK4_jetFlavors,Systematics::CSVLFup, ABCD_tAK15WAK8bAK4_csvWgtHF, ABCD_tAK15WAK8bAK4_csvWgtLF, ABCD_tAK15WAK8bAK4_csvWgtCF)/ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVLFdown",i,csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_jetPts,ABCD_tAK15WAK8bAK4_jetEtas,ABCD_tAK15WAK8bAK4_jetCSVs,ABCD_tAK15WAK8bAK4_jetFlavors,Systematics::CSVLFdown, ABCD_tAK15WAK8bAK4_csvWgtHF, ABCD_tAK15WAK8bAK4_csvWgtLF, ABCD_tAK15WAK8bAK4_csvWgtCF)/ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVHFup",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_jetPts,ABCD_tAK15WAK8bAK4_jetEtas,ABCD_tAK15WAK8bAK4_jetCSVs,ABCD_tAK15WAK8bAK4_jetFlavors,Systematics::CSVHFup, ABCD_tAK15WAK8bAK4_csvWgtHF, ABCD_tAK15WAK8bAK4_csvWgtLF, ABCD_tAK15WAK8bAK4_csvWgtCF)/ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVHFdown",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_jetPts,ABCD_tAK15WAK8bAK4_jetEtas,ABCD_tAK15WAK8bAK4_jetCSVs,ABCD_tAK15WAK8bAK4_jetFlavors,Systematics::CSVHFdown, ABCD_tAK15WAK8bAK4_csvWgtHF, ABCD_tAK15WAK8bAK4_csvWgtLF, ABCD_tAK15WAK8bAK4_csvWgtCF)/ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVHFStats1up",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_jetPts,ABCD_tAK15WAK8bAK4_jetEtas,ABCD_tAK15WAK8bAK4_jetCSVs,ABCD_tAK15WAK8bAK4_jetFlavors,Systematics::CSVHFStats1up, ABCD_tAK15WAK8bAK4_csvWgtHF, ABCD_tAK15WAK8bAK4_csvWgtLF, ABCD_tAK15WAK8bAK4_csvWgtCF)/ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVHFStats1down",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_jetPts,ABCD_tAK15WAK8bAK4_jetEtas,ABCD_tAK15WAK8bAK4_jetCSVs,ABCD_tAK15WAK8bAK4_jetFlavors,Systematics::CSVHFStats1down, ABCD_tAK15WAK8bAK4_csvWgtHF, ABCD_tAK15WAK8bAK4_csvWgtLF, ABCD_tAK15WAK8bAK4_csvWgtCF)/ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVLFStats1up",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_jetPts,ABCD_tAK15WAK8bAK4_jetEtas,ABCD_tAK15WAK8bAK4_jetCSVs,ABCD_tAK15WAK8bAK4_jetFlavors,Systematics::CSVLFStats1up, ABCD_tAK15WAK8bAK4_csvWgtHF, ABCD_tAK15WAK8bAK4_csvWgtLF, ABCD_tAK15WAK8bAK4_csvWgtCF)/ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVLFStats1down",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_jetPts,ABCD_tAK15WAK8bAK4_jetEtas,ABCD_tAK15WAK8bAK4_jetCSVs,ABCD_tAK15WAK8bAK4_jetFlavors,Systematics::CSVLFStats1down, ABCD_tAK15WAK8bAK4_csvWgtHF, ABCD_tAK15WAK8bAK4_csvWgtLF, ABCD_tAK15WAK8bAK4_csvWgtCF)/ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVHFStats2up",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_jetPts,ABCD_tAK15WAK8bAK4_jetEtas,ABCD_tAK15WAK8bAK4_jetCSVs,ABCD_tAK15WAK8bAK4_jetFlavors,Systematics::CSVHFStats2up, ABCD_tAK15WAK8bAK4_csvWgtHF, ABCD_tAK15WAK8bAK4_csvWgtLF, ABCD_tAK15WAK8bAK4_csvWgtCF)/ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVHFStats2down",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_jetPts,ABCD_tAK15WAK8bAK4_jetEtas,ABCD_tAK15WAK8bAK4_jetCSVs,ABCD_tAK15WAK8bAK4_jetFlavors,Systematics::CSVHFStats2down, ABCD_tAK15WAK8bAK4_csvWgtHF, ABCD_tAK15WAK8bAK4_csvWgtLF, ABCD_tAK15WAK8bAK4_csvWgtCF)/ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVLFStats2up",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_jetPts,ABCD_tAK15WAK8bAK4_jetEtas,ABCD_tAK15WAK8bAK4_jetCSVs,ABCD_tAK15WAK8bAK4_jetFlavors,Systematics::CSVLFStats2up, ABCD_tAK15WAK8bAK4_csvWgtHF, ABCD_tAK15WAK8bAK4_csvWgtLF, ABCD_tAK15WAK8bAK4_csvWgtCF)/ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVLFStats2down",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_jetPts,ABCD_tAK15WAK8bAK4_jetEtas,ABCD_tAK15WAK8bAK4_jetCSVs,ABCD_tAK15WAK8bAK4_jetFlavors,Systematics::CSVLFStats2down, ABCD_tAK15WAK8bAK4_csvWgtHF, ABCD_tAK15WAK8bAK4_csvWgtLF, ABCD_tAK15WAK8bAK4_csvWgtCF)/ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVCErr1up",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_jetPts,ABCD_tAK15WAK8bAK4_jetEtas,ABCD_tAK15WAK8bAK4_jetCSVs,ABCD_tAK15WAK8bAK4_jetFlavors,Systematics::CSVCErr1up, ABCD_tAK15WAK8bAK4_csvWgtHF, ABCD_tAK15WAK8bAK4_csvWgtLF, ABCD_tAK15WAK8bAK4_csvWgtCF)/ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVCErr1down",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_jetPts,ABCD_tAK15WAK8bAK4_jetEtas,ABCD_tAK15WAK8bAK4_jetCSVs,ABCD_tAK15WAK8bAK4_jetFlavors,Systematics::CSVCErr1down, ABCD_tAK15WAK8bAK4_csvWgtHF, ABCD_tAK15WAK8bAK4_csvWgtLF, ABCD_tAK15WAK8bAK4_csvWgtCF)/ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVCErr2up",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_jetPts,ABCD_tAK15WAK8bAK4_jetEtas,ABCD_tAK15WAK8bAK4_jetCSVs,ABCD_tAK15WAK8bAK4_jetFlavors,Systematics::CSVCErr2up, ABCD_tAK15WAK8bAK4_csvWgtHF, ABCD_tAK15WAK8bAK4_csvWgtLF, ABCD_tAK15WAK8bAK4_csvWgtCF)/ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK15WAK8bAK4_WeightCSVCErr2down",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_jetPts,ABCD_tAK15WAK8bAK4_jetEtas,ABCD_tAK15WAK8bAK4_jetCSVs,ABCD_tAK15WAK8bAK4_jetFlavors,Systematics::CSVCErr2down, ABCD_tAK15WAK8bAK4_csvWgtHF, ABCD_tAK15WAK8bAK4_csvWgtLF, ABCD_tAK15WAK8bAK4_csvWgtCF)/ABCD_tAK15WAK8bAK4_csvweight);  
    }

     
     
     vars.FillVars("Ws_ABCD_tAK15WAK8bAK4_Pt",i,Ws_ABCD_tAK15WAK8bAK4[i].pt());
     vars.FillVars("Ws_ABCD_tAK15WAK8bAK4_Eta",i,Ws_ABCD_tAK15WAK8bAK4[i].eta());
     vars.FillVars("Ws_ABCD_tAK15WAK8bAK4_Phi",i,Ws_ABCD_tAK15WAK8bAK4[i].phi());
     vars.FillVars("Ws_ABCD_tAK15WAK8bAK4_MSD",i,Ws_ABCD_tAK15WAK8bAK4[i].userFloat("ak8PFJetsCHSSoftDropMass"));
     vars.FillVars("Ws_ABCD_tAK15WAK8bAK4_t21",i,Ws_ABCD_tAK15WAK8bAK4[i].userFloat("NjettinessAK8CHS:tau2")/Ws_ABCD_tAK15WAK8bAK4[i].userFloat("NjettinessAK8CHS:tau1"));
     
     vars.FillVars("Tops_ABCD_tAK15WAK8bAK4_Pt",i,Tops_ABCD_tAK15WAK8bAK4[i].pt());
     vars.FillVars("Tops_ABCD_tAK15WAK8bAK4_Eta",i,Tops_ABCD_tAK15WAK8bAK4[i].eta());
     vars.FillVars("Tops_ABCD_tAK15WAK8bAK4_Phi",i,Tops_ABCD_tAK15WAK8bAK4[i].phi());
     vars.FillVars("Tops_ABCD_tAK15WAK8bAK4_MSD",i,Tops_ABCD_tAK15WAK8bAK4[i].userFloat("ak15PFJetsCHSSoftDropMass"));
     vars.FillVars("Tops_ABCD_tAK15WAK8bAK4_t32",i,Tops_ABCD_tAK15WAK8bAK4[i].userFloat("NjettinessAK15CHS:tau3")/Tops_ABCD_tAK15WAK8bAK4[i].userFloat("NjettinessAK15CHS:tau2"));

     std::vector<double> ABCD_tAK15WAK8bAK4_subjetPts;
     std::vector<double> ABCD_tAK15WAK8bAK4_subjetEtas;
     std::vector<double> ABCD_tAK15WAK8bAK4_subjetCSVs;
     std::vector<int> ABCD_tAK15WAK8bAK4_subjetFlavors;
     double subjet_ABCD_tAK15WAK8bAK4_csvWgtHF, subjet_ABCD_tAK15WAK8bAK4_csvWgtLF, subjet_ABCD_tAK15WAK8bAK4_csvWgtCF;
     float subjet_ABCD_tAK15WAK8bAK4_csvweight = 1.;
     

     
     double max_subjet_csv_v2=-10;
     auto const & names = Tops_ABCD_tAK15WAK8bAK4[i].subjets("SoftDrop");
     for( auto const & itsubJet : names ){
        if (itsubJet->pt()<20.0 || abs(itsubJet->eta())>2.4) continue;
        ABCD_tAK15WAK8bAK4_subjetPts.push_back(itsubJet->pt());
        ABCD_tAK15WAK8bAK4_subjetEtas.push_back(itsubJet->eta());
        ABCD_tAK15WAK8bAK4_subjetCSVs.push_back(MiniAODHelper::GetJetCSV(*itsubJet,"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
        ABCD_tAK15WAK8bAK4_subjetFlavors.push_back(itsubJet->hadronFlavour());
              
        if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>max_subjet_csv_v2){
            max_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
        };
     };
     
     
     vars.FillVars("Tops_ABCD_tAK15WAK8bAK4_maxsubjetCSVv2",i,max_subjet_csv_v2);
//      std::cout<<"max_subjet_csv_v2  "<<max_subjet_csv_v2<<endl;
     
     subjet_ABCD_tAK15WAK8bAK4_csvweight= csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_subjetPts,ABCD_tAK15WAK8bAK4_subjetEtas,ABCD_tAK15WAK8bAK4_subjetCSVs,ABCD_tAK15WAK8bAK4_subjetFlavors,input.systematic, subjet_ABCD_tAK15WAK8bAK4_csvWgtHF, subjet_ABCD_tAK15WAK8bAK4_csvWgtLF, subjet_ABCD_tAK15WAK8bAK4_csvWgtCF);
     
//     bool doSystematics=true;
//     if(doSystematics && input.input.systematic != sysType::JESup && input.input.systematic != sysType::JESdown && input.input.systematic != sysType::JERup && input.input.systematic != sysType::JERdown) {
     if(doSystematics && input.systematic == Systematics::NA) { // only do these for the nominal samples
     
     vars.FillVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVnominal",i,subjet_ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVLFup",i,csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_subjetPts,ABCD_tAK15WAK8bAK4_subjetEtas,ABCD_tAK15WAK8bAK4_subjetCSVs,ABCD_tAK15WAK8bAK4_subjetFlavors,Systematics::CSVLFup, subjet_ABCD_tAK15WAK8bAK4_csvWgtHF, subjet_ABCD_tAK15WAK8bAK4_csvWgtLF, subjet_ABCD_tAK15WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVLFdown",i,csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_subjetPts,ABCD_tAK15WAK8bAK4_subjetEtas,ABCD_tAK15WAK8bAK4_subjetCSVs,ABCD_tAK15WAK8bAK4_subjetFlavors,Systematics::CSVLFdown, subjet_ABCD_tAK15WAK8bAK4_csvWgtHF, subjet_ABCD_tAK15WAK8bAK4_csvWgtLF, subjet_ABCD_tAK15WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVHFup",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_subjetPts,ABCD_tAK15WAK8bAK4_subjetEtas,ABCD_tAK15WAK8bAK4_subjetCSVs,ABCD_tAK15WAK8bAK4_subjetFlavors,Systematics::CSVHFup, subjet_ABCD_tAK15WAK8bAK4_csvWgtHF, subjet_ABCD_tAK15WAK8bAK4_csvWgtLF, subjet_ABCD_tAK15WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVHFdown",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_subjetPts,ABCD_tAK15WAK8bAK4_subjetEtas,ABCD_tAK15WAK8bAK4_subjetCSVs,ABCD_tAK15WAK8bAK4_subjetFlavors,Systematics::CSVHFdown, subjet_ABCD_tAK15WAK8bAK4_csvWgtHF, subjet_ABCD_tAK15WAK8bAK4_csvWgtLF, subjet_ABCD_tAK15WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVHFStats1up",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_subjetPts,ABCD_tAK15WAK8bAK4_subjetEtas,ABCD_tAK15WAK8bAK4_subjetCSVs,ABCD_tAK15WAK8bAK4_subjetFlavors,Systematics::CSVHFStats1up, subjet_ABCD_tAK15WAK8bAK4_csvWgtHF, subjet_ABCD_tAK15WAK8bAK4_csvWgtLF, subjet_ABCD_tAK15WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVHFStats1down",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_subjetPts,ABCD_tAK15WAK8bAK4_subjetEtas,ABCD_tAK15WAK8bAK4_subjetCSVs,ABCD_tAK15WAK8bAK4_subjetFlavors,Systematics::CSVHFStats1down, subjet_ABCD_tAK15WAK8bAK4_csvWgtHF, subjet_ABCD_tAK15WAK8bAK4_csvWgtLF, subjet_ABCD_tAK15WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVLFStats1up",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_subjetPts,ABCD_tAK15WAK8bAK4_subjetEtas,ABCD_tAK15WAK8bAK4_subjetCSVs,ABCD_tAK15WAK8bAK4_subjetFlavors,Systematics::CSVLFStats1up, subjet_ABCD_tAK15WAK8bAK4_csvWgtHF, subjet_ABCD_tAK15WAK8bAK4_csvWgtLF, subjet_ABCD_tAK15WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVLFStats1down",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_subjetPts,ABCD_tAK15WAK8bAK4_subjetEtas,ABCD_tAK15WAK8bAK4_subjetCSVs,ABCD_tAK15WAK8bAK4_subjetFlavors,Systematics::CSVLFStats1down, subjet_ABCD_tAK15WAK8bAK4_csvWgtHF, subjet_ABCD_tAK15WAK8bAK4_csvWgtLF, subjet_ABCD_tAK15WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVHFStats2up",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_subjetPts,ABCD_tAK15WAK8bAK4_subjetEtas,ABCD_tAK15WAK8bAK4_subjetCSVs,ABCD_tAK15WAK8bAK4_subjetFlavors,Systematics::CSVHFStats2up, subjet_ABCD_tAK15WAK8bAK4_csvWgtHF, subjet_ABCD_tAK15WAK8bAK4_csvWgtLF, subjet_ABCD_tAK15WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVHFStats2down",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_subjetPts,ABCD_tAK15WAK8bAK4_subjetEtas,ABCD_tAK15WAK8bAK4_subjetCSVs,ABCD_tAK15WAK8bAK4_subjetFlavors,Systematics::CSVHFStats2down, subjet_ABCD_tAK15WAK8bAK4_csvWgtHF, subjet_ABCD_tAK15WAK8bAK4_csvWgtLF, subjet_ABCD_tAK15WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVLFStats2up",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_subjetPts,ABCD_tAK15WAK8bAK4_subjetEtas,ABCD_tAK15WAK8bAK4_subjetCSVs,ABCD_tAK15WAK8bAK4_subjetFlavors,Systematics::CSVLFStats2up, subjet_ABCD_tAK15WAK8bAK4_csvWgtHF, subjet_ABCD_tAK15WAK8bAK4_csvWgtLF, subjet_ABCD_tAK15WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVLFStats2down",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_subjetPts,ABCD_tAK15WAK8bAK4_subjetEtas,ABCD_tAK15WAK8bAK4_subjetCSVs,ABCD_tAK15WAK8bAK4_subjetFlavors,Systematics::CSVLFStats2down, subjet_ABCD_tAK15WAK8bAK4_csvWgtHF, subjet_ABCD_tAK15WAK8bAK4_csvWgtLF, subjet_ABCD_tAK15WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVCErr1up",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_subjetPts,ABCD_tAK15WAK8bAK4_subjetEtas,ABCD_tAK15WAK8bAK4_subjetCSVs,ABCD_tAK15WAK8bAK4_subjetFlavors,Systematics::CSVCErr1up, subjet_ABCD_tAK15WAK8bAK4_csvWgtHF, subjet_ABCD_tAK15WAK8bAK4_csvWgtLF, subjet_ABCD_tAK15WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVCErr1down",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_subjetPts,ABCD_tAK15WAK8bAK4_subjetEtas,ABCD_tAK15WAK8bAK4_subjetCSVs,ABCD_tAK15WAK8bAK4_subjetFlavors,Systematics::CSVCErr1down, subjet_ABCD_tAK15WAK8bAK4_csvWgtHF, subjet_ABCD_tAK15WAK8bAK4_csvWgtLF, subjet_ABCD_tAK15WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVCErr2up",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_subjetPts,ABCD_tAK15WAK8bAK4_subjetEtas,ABCD_tAK15WAK8bAK4_subjetCSVs,ABCD_tAK15WAK8bAK4_subjetFlavors,Systematics::CSVCErr2up, subjet_ABCD_tAK15WAK8bAK4_csvWgtHF, subjet_ABCD_tAK15WAK8bAK4_csvWgtLF, subjet_ABCD_tAK15WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK15WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK15WAK8bAK4_WeightCSVCErr2down",i, csvReweighter->getCSVWeight(ABCD_tAK15WAK8bAK4_subjetPts,ABCD_tAK15WAK8bAK4_subjetEtas,ABCD_tAK15WAK8bAK4_subjetCSVs,ABCD_tAK15WAK8bAK4_subjetFlavors,Systematics::CSVCErr2down, subjet_ABCD_tAK15WAK8bAK4_csvWgtHF, subjet_ABCD_tAK15WAK8bAK4_csvWgtLF, subjet_ABCD_tAK15WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK15WAK8bAK4_csvweight);  
     }

  }
/*
  ////FILL ABCD_tAK12WAK12bAK4 VARIABLES
  vars.FillVar("N_Zprime_ABCD_tAK12WAK12bAK4",Zprimes_ABCD_tAK12WAK12bAK4.size());

  for (uint i=0; i<Zprimes_ABCD_tAK12WAK12bAK4.size(); i++){
  //for(math::XYZTLorentzVector::const_iterator ittopJet = AK8_top_candidates.begin() ; ittopJet != AK8_top_candidates.end(); ++ittopJet){
     //int i = 
     vars.FillVars("Zprimes_ABCD_tAK12WAK12bAK4_M",i,Zprimes_ABCD_tAK12WAK12bAK4[i].mass());
     vars.FillVars("Zprimes_ABCD_tAK12WAK12bAK4_Pt",i,Zprimes_ABCD_tAK12WAK12bAK4[i].pt());
     
     vars.FillVars("Tprimes_ABCD_tAK12WAK12bAK4_M",i,Tprimes_ABCD_tAK12WAK12bAK4[i].mass());
     vars.FillVars("Tprimes_ABCD_tAK12WAK12bAK4_Pt",i,Tprimes_ABCD_tAK12WAK12bAK4[i].pt());
     
     vars.FillVars("Bottoms_ABCD_tAK12WAK12bAK4_Pt",i,Bottoms_ABCD_tAK12WAK12bAK4[i].pt());
     vars.FillVars("Bottoms_ABCD_tAK12WAK12bAK4_Eta",i,Bottoms_ABCD_tAK12WAK12bAK4[i].eta());
     vars.FillVars("Bottoms_ABCD_tAK12WAK12bAK4_Phi",i,Bottoms_ABCD_tAK12WAK12bAK4[i].phi());
     vars.FillVars("Bottoms_ABCD_tAK12WAK12bAK4_CSV",i,MiniAODHelper::GetJetCSV(Bottoms_ABCD_tAK12WAK12bAK4[i],"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
     
     vars.FillVars("Ws_ABCD_tAK12WAK12bAK4_Pt",i,Ws_ABCD_tAK12WAK12bAK4[i].pt());
     vars.FillVars("Ws_ABCD_tAK12WAK12bAK4_Eta",i,Ws_ABCD_tAK12WAK12bAK4[i].eta());
     vars.FillVars("Ws_ABCD_tAK12WAK12bAK4_Phi",i,Ws_ABCD_tAK12WAK12bAK4[i].phi());
     vars.FillVars("Ws_ABCD_tAK12WAK12bAK4_MSD",i,Ws_ABCD_tAK12WAK12bAK4[i].userFloat("ak12PFJetsCHSSoftDropMass"));
     vars.FillVars("Ws_ABCD_tAK12WAK12bAK4_t21",i,Ws_ABCD_tAK12WAK12bAK4[i].userFloat("NjettinessAK12CHS:tau2")/Ws_ABCD_tAK12WAK12bAK4[i].userFloat("NjettinessAK12CHS:tau1"));
     
     vars.FillVars("Tops_ABCD_tAK12WAK12bAK4_Pt",i,Tops_ABCD_tAK12WAK12bAK4[i].pt());
     vars.FillVars("Tops_ABCD_tAK12WAK12bAK4_Eta",i,Tops_ABCD_tAK12WAK12bAK4[i].eta());
     vars.FillVars("Tops_ABCD_tAK12WAK12bAK4_Phi",i,Tops_ABCD_tAK12WAK12bAK4[i].phi());
     vars.FillVars("Tops_ABCD_tAK12WAK12bAK4_MSD",i,Tops_ABCD_tAK12WAK12bAK4[i].userFloat("ak12PFJetsCHSSoftDropMass"));
     vars.FillVars("Tops_ABCD_tAK12WAK12bAK4_t32",i,Tops_ABCD_tAK12WAK12bAK4[i].userFloat("NjettinessAK12CHS:tau3")/Tops_ABCD_tAK12WAK12bAK4[i].userFloat("NjettinessAK12CHS:tau2"));

     double max_subjet_csv_v2=-10;
     auto const & names = Tops_ABCD_tAK12WAK12bAK4[i].subjets("SoftDrop");
     for( auto const & itsubJet : names ){
        if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>max_subjet_csv_v2){
            max_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
        };
     };
     vars.FillVars("Tops_ABCD_tAK12WAK12bAK4_maxsubjetCSVv2",i,max_subjet_csv_v2);
//      std::cout<<"max_subjet_csv_v2  "<<max_subjet_csv_v2<<endl;
  }
*/

  ////FILL ABCD_tAK12WAK8bAK4 VARIABLES
  vars.FillVar("N_Zprime_ABCD_tAK12WAK8bAK4",Zprimes_ABCD_tAK12WAK8bAK4.size());

  for (uint i=0; i<Zprimes_ABCD_tAK12WAK8bAK4.size(); i++){
  //for(math::XYZTLorentzVector::const_iterator ittopJet = AK8_top_candidates.begin() ; ittopJet != AK8_top_candidates.end(); ++ittopJet){
     //int i = 
     vars.FillVars("Zprimes_ABCD_tAK12WAK8bAK4_M",i,Zprimes_ABCD_tAK12WAK8bAK4[i].mass());
     vars.FillVars("Zprimes_ABCD_tAK12WAK8bAK4_Pt",i,Zprimes_ABCD_tAK12WAK8bAK4[i].pt());
     
     vars.FillVars("Tprimes_ABCD_tAK12WAK8bAK4_M",i,Tprimes_ABCD_tAK12WAK8bAK4[i].mass());
     vars.FillVars("Tprimes_ABCD_tAK12WAK8bAK4_Pt",i,Tprimes_ABCD_tAK12WAK8bAK4[i].pt());
     
     vars.FillVars("Bottoms_ABCD_tAK12WAK8bAK4_Pt",i,Bottoms_ABCD_tAK12WAK8bAK4[i].pt());
     vars.FillVars("Bottoms_ABCD_tAK12WAK8bAK4_Eta",i,Bottoms_ABCD_tAK12WAK8bAK4[i].eta());
     vars.FillVars("Bottoms_ABCD_tAK12WAK8bAK4_Phi",i,Bottoms_ABCD_tAK12WAK8bAK4[i].phi());
     vars.FillVars("Bottoms_ABCD_tAK12WAK8bAK4_CSV",i,MiniAODHelper::GetJetCSV(Bottoms_ABCD_tAK12WAK8bAK4[i],"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
     
//      CSVHelper csvReweighter;
     std::vector<double> ABCD_tAK12WAK8bAK4_jetPts;
     std::vector<double> ABCD_tAK12WAK8bAK4_jetEtas;
     std::vector<double> ABCD_tAK12WAK8bAK4_jetCSVs;
     std::vector<int> ABCD_tAK12WAK8bAK4_jetFlavors;
     double ABCD_tAK12WAK8bAK4_csvWgtHF, ABCD_tAK12WAK8bAK4_csvWgtLF, ABCD_tAK12WAK8bAK4_csvWgtCF;
     float ABCD_tAK12WAK8bAK4_csvweight = 1.;
     
     ABCD_tAK12WAK8bAK4_jetPts.push_back(Bottoms_ABCD_tAK12WAK8bAK4[i].pt());
     ABCD_tAK12WAK8bAK4_jetEtas.push_back(Bottoms_ABCD_tAK12WAK8bAK4[i].eta());
     ABCD_tAK12WAK8bAK4_jetCSVs.push_back(MiniAODHelper::GetJetCSV(Bottoms_ABCD_tAK12WAK8bAK4[i],"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
     ABCD_tAK12WAK8bAK4_jetFlavors.push_back(Bottoms_ABCD_tAK12WAK8bAK4[i].hadronFlavour());
     
     ABCD_tAK12WAK8bAK4_csvweight= csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_jetPts,ABCD_tAK12WAK8bAK4_jetEtas,ABCD_tAK12WAK8bAK4_jetCSVs,ABCD_tAK12WAK8bAK4_jetFlavors,input.systematic, ABCD_tAK12WAK8bAK4_csvWgtHF, ABCD_tAK12WAK8bAK4_csvWgtLF, ABCD_tAK12WAK8bAK4_csvWgtCF);



    bool doSystematics=true;
//     if(doSystematics && input.input.systematic != sysType::JESup && input.input.systematic != sysType::JESdown && input.input.systematic != sysType::JERup && input.input.systematic != sysType::JERdown) {
     if(doSystematics && input.systematic == Systematics::NA) { // only do these for the nominal samples

     
     vars.FillVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVnominal",i,ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVLFup",i,csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_jetPts,ABCD_tAK12WAK8bAK4_jetEtas,ABCD_tAK12WAK8bAK4_jetCSVs,ABCD_tAK12WAK8bAK4_jetFlavors,Systematics::CSVLFup, ABCD_tAK12WAK8bAK4_csvWgtHF, ABCD_tAK12WAK8bAK4_csvWgtLF, ABCD_tAK12WAK8bAK4_csvWgtCF)/ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVLFdown",i,csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_jetPts,ABCD_tAK12WAK8bAK4_jetEtas,ABCD_tAK12WAK8bAK4_jetCSVs,ABCD_tAK12WAK8bAK4_jetFlavors,Systematics::CSVLFdown, ABCD_tAK12WAK8bAK4_csvWgtHF, ABCD_tAK12WAK8bAK4_csvWgtLF, ABCD_tAK12WAK8bAK4_csvWgtCF)/ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVHFup",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_jetPts,ABCD_tAK12WAK8bAK4_jetEtas,ABCD_tAK12WAK8bAK4_jetCSVs,ABCD_tAK12WAK8bAK4_jetFlavors,Systematics::CSVHFup, ABCD_tAK12WAK8bAK4_csvWgtHF, ABCD_tAK12WAK8bAK4_csvWgtLF, ABCD_tAK12WAK8bAK4_csvWgtCF)/ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVHFdown",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_jetPts,ABCD_tAK12WAK8bAK4_jetEtas,ABCD_tAK12WAK8bAK4_jetCSVs,ABCD_tAK12WAK8bAK4_jetFlavors,Systematics::CSVHFdown, ABCD_tAK12WAK8bAK4_csvWgtHF, ABCD_tAK12WAK8bAK4_csvWgtLF, ABCD_tAK12WAK8bAK4_csvWgtCF)/ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVHFStats1up",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_jetPts,ABCD_tAK12WAK8bAK4_jetEtas,ABCD_tAK12WAK8bAK4_jetCSVs,ABCD_tAK12WAK8bAK4_jetFlavors,Systematics::CSVHFStats1up, ABCD_tAK12WAK8bAK4_csvWgtHF, ABCD_tAK12WAK8bAK4_csvWgtLF, ABCD_tAK12WAK8bAK4_csvWgtCF)/ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVHFStats1down",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_jetPts,ABCD_tAK12WAK8bAK4_jetEtas,ABCD_tAK12WAK8bAK4_jetCSVs,ABCD_tAK12WAK8bAK4_jetFlavors,Systematics::CSVHFStats1down, ABCD_tAK12WAK8bAK4_csvWgtHF, ABCD_tAK12WAK8bAK4_csvWgtLF, ABCD_tAK12WAK8bAK4_csvWgtCF)/ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVLFStats1up",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_jetPts,ABCD_tAK12WAK8bAK4_jetEtas,ABCD_tAK12WAK8bAK4_jetCSVs,ABCD_tAK12WAK8bAK4_jetFlavors,Systematics::CSVLFStats1up, ABCD_tAK12WAK8bAK4_csvWgtHF, ABCD_tAK12WAK8bAK4_csvWgtLF, ABCD_tAK12WAK8bAK4_csvWgtCF)/ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVLFStats1down",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_jetPts,ABCD_tAK12WAK8bAK4_jetEtas,ABCD_tAK12WAK8bAK4_jetCSVs,ABCD_tAK12WAK8bAK4_jetFlavors,Systematics::CSVLFStats1down, ABCD_tAK12WAK8bAK4_csvWgtHF, ABCD_tAK12WAK8bAK4_csvWgtLF, ABCD_tAK12WAK8bAK4_csvWgtCF)/ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVHFStats2up",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_jetPts,ABCD_tAK12WAK8bAK4_jetEtas,ABCD_tAK12WAK8bAK4_jetCSVs,ABCD_tAK12WAK8bAK4_jetFlavors,Systematics::CSVHFStats2up, ABCD_tAK12WAK8bAK4_csvWgtHF, ABCD_tAK12WAK8bAK4_csvWgtLF, ABCD_tAK12WAK8bAK4_csvWgtCF)/ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVHFStats2down",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_jetPts,ABCD_tAK12WAK8bAK4_jetEtas,ABCD_tAK12WAK8bAK4_jetCSVs,ABCD_tAK12WAK8bAK4_jetFlavors,Systematics::CSVHFStats2down, ABCD_tAK12WAK8bAK4_csvWgtHF, ABCD_tAK12WAK8bAK4_csvWgtLF, ABCD_tAK12WAK8bAK4_csvWgtCF)/ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVLFStats2up",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_jetPts,ABCD_tAK12WAK8bAK4_jetEtas,ABCD_tAK12WAK8bAK4_jetCSVs,ABCD_tAK12WAK8bAK4_jetFlavors,Systematics::CSVLFStats2up, ABCD_tAK12WAK8bAK4_csvWgtHF, ABCD_tAK12WAK8bAK4_csvWgtLF, ABCD_tAK12WAK8bAK4_csvWgtCF)/ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVLFStats2down",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_jetPts,ABCD_tAK12WAK8bAK4_jetEtas,ABCD_tAK12WAK8bAK4_jetCSVs,ABCD_tAK12WAK8bAK4_jetFlavors,Systematics::CSVLFStats2down, ABCD_tAK12WAK8bAK4_csvWgtHF, ABCD_tAK12WAK8bAK4_csvWgtLF, ABCD_tAK12WAK8bAK4_csvWgtCF)/ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVCErr1up",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_jetPts,ABCD_tAK12WAK8bAK4_jetEtas,ABCD_tAK12WAK8bAK4_jetCSVs,ABCD_tAK12WAK8bAK4_jetFlavors,Systematics::CSVCErr1up, ABCD_tAK12WAK8bAK4_csvWgtHF, ABCD_tAK12WAK8bAK4_csvWgtLF, ABCD_tAK12WAK8bAK4_csvWgtCF)/ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVCErr1down",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_jetPts,ABCD_tAK12WAK8bAK4_jetEtas,ABCD_tAK12WAK8bAK4_jetCSVs,ABCD_tAK12WAK8bAK4_jetFlavors,Systematics::CSVCErr1down, ABCD_tAK12WAK8bAK4_csvWgtHF, ABCD_tAK12WAK8bAK4_csvWgtLF, ABCD_tAK12WAK8bAK4_csvWgtCF)/ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVCErr2up",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_jetPts,ABCD_tAK12WAK8bAK4_jetEtas,ABCD_tAK12WAK8bAK4_jetCSVs,ABCD_tAK12WAK8bAK4_jetFlavors,Systematics::CSVCErr2up, ABCD_tAK12WAK8bAK4_csvWgtHF, ABCD_tAK12WAK8bAK4_csvWgtLF, ABCD_tAK12WAK8bAK4_csvWgtCF)/ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Bottoms_ABCD_tAK12WAK8bAK4_WeightCSVCErr2down",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_jetPts,ABCD_tAK12WAK8bAK4_jetEtas,ABCD_tAK12WAK8bAK4_jetCSVs,ABCD_tAK12WAK8bAK4_jetFlavors,Systematics::CSVCErr2down, ABCD_tAK12WAK8bAK4_csvWgtHF, ABCD_tAK12WAK8bAK4_csvWgtLF, ABCD_tAK12WAK8bAK4_csvWgtCF)/ABCD_tAK12WAK8bAK4_csvweight);  
    }

     
     vars.FillVars("Ws_ABCD_tAK12WAK8bAK4_Pt",i,Ws_ABCD_tAK12WAK8bAK4[i].pt());
     vars.FillVars("Ws_ABCD_tAK12WAK8bAK4_Eta",i,Ws_ABCD_tAK12WAK8bAK4[i].eta());
     vars.FillVars("Ws_ABCD_tAK12WAK8bAK4_Phi",i,Ws_ABCD_tAK12WAK8bAK4[i].phi());
     vars.FillVars("Ws_ABCD_tAK12WAK8bAK4_MSD",i,Ws_ABCD_tAK12WAK8bAK4[i].userFloat("ak8PFJetsCHSSoftDropMass"));
     vars.FillVars("Ws_ABCD_tAK12WAK8bAK4_t21",i,Ws_ABCD_tAK12WAK8bAK4[i].userFloat("NjettinessAK8CHS:tau2")/Ws_ABCD_tAK12WAK8bAK4[i].userFloat("NjettinessAK8CHS:tau1"));
     
     vars.FillVars("Tops_ABCD_tAK12WAK8bAK4_Pt",i,Tops_ABCD_tAK12WAK8bAK4[i].pt());
     vars.FillVars("Tops_ABCD_tAK12WAK8bAK4_Eta",i,Tops_ABCD_tAK12WAK8bAK4[i].eta());
     vars.FillVars("Tops_ABCD_tAK12WAK8bAK4_Phi",i,Tops_ABCD_tAK12WAK8bAK4[i].phi());
     vars.FillVars("Tops_ABCD_tAK12WAK8bAK4_MSD",i,Tops_ABCD_tAK12WAK8bAK4[i].userFloat("ak12PFJetsCHSSoftDropMass"));
     vars.FillVars("Tops_ABCD_tAK12WAK8bAK4_t32",i,Tops_ABCD_tAK12WAK8bAK4[i].userFloat("NjettinessAK12CHS:tau3")/Tops_ABCD_tAK12WAK8bAK4[i].userFloat("NjettinessAK12CHS:tau2"));

     
     std::vector<double> ABCD_tAK12WAK8bAK4_subjetPts;
     std::vector<double> ABCD_tAK12WAK8bAK4_subjetEtas;
     std::vector<double> ABCD_tAK12WAK8bAK4_subjetCSVs;
     std::vector<int> ABCD_tAK12WAK8bAK4_subjetFlavors;
     double subjet_ABCD_tAK12WAK8bAK4_csvWgtHF, subjet_ABCD_tAK12WAK8bAK4_csvWgtLF, subjet_ABCD_tAK12WAK8bAK4_csvWgtCF;
     float subjet_ABCD_tAK12WAK8bAK4_csvweight = 1.;
     
     double max_subjet_csv_v2=-10;
     auto const & names = Tops_ABCD_tAK12WAK8bAK4[i].subjets("SoftDrop");
     for( auto const & itsubJet : names ){
        if (itsubJet->pt()<20.0 || abs(itsubJet->eta())>2.4) continue;
        ABCD_tAK12WAK8bAK4_subjetPts.push_back(itsubJet->pt());
        ABCD_tAK12WAK8bAK4_subjetEtas.push_back(itsubJet->eta());
        ABCD_tAK12WAK8bAK4_subjetCSVs.push_back(MiniAODHelper::GetJetCSV(*itsubJet,"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
        ABCD_tAK12WAK8bAK4_subjetFlavors.push_back(itsubJet->hadronFlavour());
              
        if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>max_subjet_csv_v2){
            max_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
        };
     };
     
     
     vars.FillVars("Tops_ABCD_tAK12WAK8bAK4_maxsubjetCSVv2",i,max_subjet_csv_v2);
//      std::cout<<"max_subjet_csv_v2  "<<max_subjet_csv_v2<<endl;
     
     subjet_ABCD_tAK12WAK8bAK4_csvweight= csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_subjetPts,ABCD_tAK12WAK8bAK4_subjetEtas,ABCD_tAK12WAK8bAK4_subjetCSVs,ABCD_tAK12WAK8bAK4_subjetFlavors,input.systematic, subjet_ABCD_tAK12WAK8bAK4_csvWgtHF, subjet_ABCD_tAK12WAK8bAK4_csvWgtLF, subjet_ABCD_tAK12WAK8bAK4_csvWgtCF);
     
//     bool doSystematics=true;
//     if(doSystematics && input.input.systematic != sysType::JESup && input.input.systematic != sysType::JESdown && input.input.systematic != sysType::JERup && input.input.systematic != sysType::JERdown) {
     if(doSystematics && input.systematic == Systematics::NA) { // only do these for the nominal samples
     
     vars.FillVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVnominal",i,subjet_ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVLFup",i,csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_subjetPts,ABCD_tAK12WAK8bAK4_subjetEtas,ABCD_tAK12WAK8bAK4_subjetCSVs,ABCD_tAK12WAK8bAK4_subjetFlavors,Systematics::CSVLFup, subjet_ABCD_tAK12WAK8bAK4_csvWgtHF, subjet_ABCD_tAK12WAK8bAK4_csvWgtLF, subjet_ABCD_tAK12WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVLFdown",i,csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_subjetPts,ABCD_tAK12WAK8bAK4_subjetEtas,ABCD_tAK12WAK8bAK4_subjetCSVs,ABCD_tAK12WAK8bAK4_subjetFlavors,Systematics::CSVLFdown, subjet_ABCD_tAK12WAK8bAK4_csvWgtHF, subjet_ABCD_tAK12WAK8bAK4_csvWgtLF, subjet_ABCD_tAK12WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVHFup",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_subjetPts,ABCD_tAK12WAK8bAK4_subjetEtas,ABCD_tAK12WAK8bAK4_subjetCSVs,ABCD_tAK12WAK8bAK4_subjetFlavors,Systematics::CSVHFup, subjet_ABCD_tAK12WAK8bAK4_csvWgtHF, subjet_ABCD_tAK12WAK8bAK4_csvWgtLF, subjet_ABCD_tAK12WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVHFdown",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_subjetPts,ABCD_tAK12WAK8bAK4_subjetEtas,ABCD_tAK12WAK8bAK4_subjetCSVs,ABCD_tAK12WAK8bAK4_subjetFlavors,Systematics::CSVHFdown, subjet_ABCD_tAK12WAK8bAK4_csvWgtHF, subjet_ABCD_tAK12WAK8bAK4_csvWgtLF, subjet_ABCD_tAK12WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVHFStats1up",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_subjetPts,ABCD_tAK12WAK8bAK4_subjetEtas,ABCD_tAK12WAK8bAK4_subjetCSVs,ABCD_tAK12WAK8bAK4_subjetFlavors,Systematics::CSVHFStats1up, subjet_ABCD_tAK12WAK8bAK4_csvWgtHF, subjet_ABCD_tAK12WAK8bAK4_csvWgtLF, subjet_ABCD_tAK12WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVHFStats1down",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_subjetPts,ABCD_tAK12WAK8bAK4_subjetEtas,ABCD_tAK12WAK8bAK4_subjetCSVs,ABCD_tAK12WAK8bAK4_subjetFlavors,Systematics::CSVHFStats1down, subjet_ABCD_tAK12WAK8bAK4_csvWgtHF, subjet_ABCD_tAK12WAK8bAK4_csvWgtLF, subjet_ABCD_tAK12WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVLFStats1up",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_subjetPts,ABCD_tAK12WAK8bAK4_subjetEtas,ABCD_tAK12WAK8bAK4_subjetCSVs,ABCD_tAK12WAK8bAK4_subjetFlavors,Systematics::CSVLFStats1up, subjet_ABCD_tAK12WAK8bAK4_csvWgtHF, subjet_ABCD_tAK12WAK8bAK4_csvWgtLF, subjet_ABCD_tAK12WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVLFStats1down",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_subjetPts,ABCD_tAK12WAK8bAK4_subjetEtas,ABCD_tAK12WAK8bAK4_subjetCSVs,ABCD_tAK12WAK8bAK4_subjetFlavors,Systematics::CSVLFStats1down, subjet_ABCD_tAK12WAK8bAK4_csvWgtHF, subjet_ABCD_tAK12WAK8bAK4_csvWgtLF, subjet_ABCD_tAK12WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVHFStats2up",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_subjetPts,ABCD_tAK12WAK8bAK4_subjetEtas,ABCD_tAK12WAK8bAK4_subjetCSVs,ABCD_tAK12WAK8bAK4_subjetFlavors,Systematics::CSVHFStats2up, subjet_ABCD_tAK12WAK8bAK4_csvWgtHF, subjet_ABCD_tAK12WAK8bAK4_csvWgtLF, subjet_ABCD_tAK12WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVHFStats2down",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_subjetPts,ABCD_tAK12WAK8bAK4_subjetEtas,ABCD_tAK12WAK8bAK4_subjetCSVs,ABCD_tAK12WAK8bAK4_subjetFlavors,Systematics::CSVHFStats2down, subjet_ABCD_tAK12WAK8bAK4_csvWgtHF, subjet_ABCD_tAK12WAK8bAK4_csvWgtLF, subjet_ABCD_tAK12WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVLFStats2up",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_subjetPts,ABCD_tAK12WAK8bAK4_subjetEtas,ABCD_tAK12WAK8bAK4_subjetCSVs,ABCD_tAK12WAK8bAK4_subjetFlavors,Systematics::CSVLFStats2up, subjet_ABCD_tAK12WAK8bAK4_csvWgtHF, subjet_ABCD_tAK12WAK8bAK4_csvWgtLF, subjet_ABCD_tAK12WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVLFStats2down",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_subjetPts,ABCD_tAK12WAK8bAK4_subjetEtas,ABCD_tAK12WAK8bAK4_subjetCSVs,ABCD_tAK12WAK8bAK4_subjetFlavors,Systematics::CSVLFStats2down, subjet_ABCD_tAK12WAK8bAK4_csvWgtHF, subjet_ABCD_tAK12WAK8bAK4_csvWgtLF, subjet_ABCD_tAK12WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVCErr1up",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_subjetPts,ABCD_tAK12WAK8bAK4_subjetEtas,ABCD_tAK12WAK8bAK4_subjetCSVs,ABCD_tAK12WAK8bAK4_subjetFlavors,Systematics::CSVCErr1up, subjet_ABCD_tAK12WAK8bAK4_csvWgtHF, subjet_ABCD_tAK12WAK8bAK4_csvWgtLF, subjet_ABCD_tAK12WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVCErr1down",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_subjetPts,ABCD_tAK12WAK8bAK4_subjetEtas,ABCD_tAK12WAK8bAK4_subjetCSVs,ABCD_tAK12WAK8bAK4_subjetFlavors,Systematics::CSVCErr1down, subjet_ABCD_tAK12WAK8bAK4_csvWgtHF, subjet_ABCD_tAK12WAK8bAK4_csvWgtLF, subjet_ABCD_tAK12WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVCErr2up",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_subjetPts,ABCD_tAK12WAK8bAK4_subjetEtas,ABCD_tAK12WAK8bAK4_subjetCSVs,ABCD_tAK12WAK8bAK4_subjetFlavors,Systematics::CSVCErr2up, subjet_ABCD_tAK12WAK8bAK4_csvWgtHF, subjet_ABCD_tAK12WAK8bAK4_csvWgtLF, subjet_ABCD_tAK12WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK12WAK8bAK4_csvweight);
     vars.FillVars("Topsubjets_ABCD_tAK12WAK8bAK4_WeightCSVCErr2down",i, csvReweighter->getCSVWeight(ABCD_tAK12WAK8bAK4_subjetPts,ABCD_tAK12WAK8bAK4_subjetEtas,ABCD_tAK12WAK8bAK4_subjetCSVs,ABCD_tAK12WAK8bAK4_subjetFlavors,Systematics::CSVCErr2down, subjet_ABCD_tAK12WAK8bAK4_csvWgtHF, subjet_ABCD_tAK12WAK8bAK4_csvWgtLF, subjet_ABCD_tAK12WAK8bAK4_csvWgtCF)/subjet_ABCD_tAK12WAK8bAK4_csvweight);  

     }
            
  }  
   
 }// end of HT if 1190
  
}
