#include "BoostedTTH/BoostedAnalyzer/interface/ZPrimeToTPrimeAllHadProcessor.hpp"
#include <string> 
#include "MiniAOD/MiniAODHelper/interface/TTM_SDM.h"
#include "BoostedTTH/BoostedAnalyzer/interface/ResourceMonitor.hpp"



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
            
            
std::vector<float> smearfactor_JetMass(float phi, float eta){
    std::vector<float> res;

    
    UInt_t seed = int((phi + 10.0)*10000);
    int warmup = int((eta + 10.0)*10);
    
   
    TRandom3 myrandom=TRandom3(seed);
    
    for (int i=0; i<warmup; i++){
        myrandom.Gaus(0.0,7.99);
    }
    
    float randomnumber=myrandom.Gaus(0.0,7.99/82.0);
    res.push_back(1+sqrt(1.23*1.23 -1.0)*randomnumber);
    res.push_back(1+sqrt((1.23+0.18)*(1.23+0.18) -1.0)*randomnumber);
    res.push_back(1+sqrt((1.23-0.18)*(1.23-0.18) -1.0)*randomnumber);

    
    
    return res;

}   
            
ZPrimeToTPrimeAllHadProcessor::~ZPrimeToTPrimeAllHadProcessor(){
    delete histo_ABCD_QCD_MSD_top_nobtag;
    
}


void ZPrimeToTPrimeAllHadProcessor::Init(const InputCollections& input,VariableContainer& vars){
    
    InitLeptonVars(vars);
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

void ZPrimeToTPrimeAllHadProcessor::InitLeptonVars(VariableContainer& vars){
    vars.InitVar("N_electrons","I");
    vars.InitVar("N_muons","I");
    vars.InitVar("N_electronsLoose","I");
    vars.InitVar("N_muonsLoose","I");
    vars.InitVar("N_electronsMidloose","I");
    vars.InitVar("N_muonsMidloose","I");    
    vars.InitVars("Electrons_Pt","N_electrons");
    vars.InitVars("Muons_Pt","N_muons");
    vars.InitVars("ElectronsLoose_Pt","N_electronsLoose");
    vars.InitVars("MuonsLoose_Pt","N_muonsLoose");
    vars.InitVars("ElectronsMidloose_Pt","N_electronsMidloose");
    vars.InitVars("MuonsMidloose_Pt","N_muonsMidloose");
}


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
    
    vars.InitVar("N_packedPatJetsAK8PFCHSPruning","I");
    vars.InitVars("packedPatJetsAK8PFCHSPruning_Pt",-9.0,"N_packedPatJetsAK8PFCHSPruning");
    vars.InitVars("packedPatJetsAK8PFCHSPruning_Eta",-9.0,"N_packedPatJetsAK8PFCHSPruning");
    vars.InitVars("packedPatJetsAK8PFCHSPruning_Phi",-9.0,"N_packedPatJetsAK8PFCHSPruning");
    vars.InitVars("packedPatJetsAK8PFCHSPruning_E",-9.0,"N_packedPatJetsAK8PFCHSPruning");
    vars.InitVars("packedPatJetsAK8PFCHSPruning_M",-9.0,"N_packedPatJetsAK8PFCHSPruning");
    
    vars.InitVar("N_packedPatJetsAK8PFPUPPISoftDrop","I");
    vars.InitVars("packedPatJetsAK8PFPUPPISoftDrop_Pt",-9.0,"N_packedPatJetsAK8PFPUPPISoftDrop");
    vars.InitVars("packedPatJetsAK8PFPUPPISoftDrop_Eta",-9.0,"N_packedPatJetsAK8PFPUPPISoftDrop");
    vars.InitVars("packedPatJetsAK8PFPUPPISoftDrop_Phi",-9.0,"N_packedPatJetsAK8PFPUPPISoftDrop");
    vars.InitVars("packedPatJetsAK8PFPUPPISoftDrop_E",-9.0,"N_packedPatJetsAK8PFPUPPISoftDrop");
    vars.InitVars("packedPatJetsAK8PFPUPPISoftDrop_M",-9.0,"N_packedPatJetsAK8PFPUPPISoftDrop");
    

    vars.InitVars("NjettinessAK8CHS_tau1",-9.0,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("NjettinessAK8CHS_tau2",-9.0,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("NjettinessAK8CHS_tau3",-9.0,"N_packedPatJetsAK8PFCHSSoftDrop");
    
    vars.InitVars("AK8CHSSoftDrop_Njettinesstau1",-9.0,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("AK8CHSSoftDrop_Njettinesstau2",-9.0,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("AK8CHSSoftDrop_Njettinesstau3",-9.0,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("AK8CHSSoftDrop_M",-9.0,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("AK8CHSSoftDrop_maxsubjetCSV",-9.0,"N_packedPatJetsAK8PFCHSSoftDrop");
    
    vars.InitVars("AK8CHSPruning_Njettinesstau1",-9.0,"N_packedPatJetsAK8PFCHSPruning");
    vars.InitVars("AK8CHSPruning_Njettinesstau2",-9.0,"N_packedPatJetsAK8PFCHSPruning");
    vars.InitVars("AK8CHSPruning_Njettinesstau3",-9.0,"N_packedPatJetsAK8PFCHSPruning");
    vars.InitVars("AK8CHSPruning_M",-9.0,"N_packedPatJetsAK8PFCHSPruning");
    vars.InitVars("AK8CHSPruning_maxsubjetCSV",-9.0,"N_packedPatJetsAK8PFCHSPruning");

    
    vars.InitVars("AK8PUPPISoftDrop_Njettinesstau1",-9.0,"N_packedPatJetsAK8PFPUPPISoftDrop");
    vars.InitVars("AK8PUPPISoftDrop_Njettinesstau2",-9.0,"N_packedPatJetsAK8PFPUPPISoftDrop");
    vars.InitVars("AK8PUPPISoftDrop_Njettinesstau3",-9.0,"N_packedPatJetsAK8PFPUPPISoftDrop");
    vars.InitVars("AK8PUPPISoftDrop_M",-9.0,"N_packedPatJetsAK8PFPUPPISoftDrop");
    vars.InitVars("AK8PUPPISoftDrop_maxsubjetCSV",-9.0,"N_packedPatJetsAK8PFPUPPISoftDrop");

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
   vars.InitVar("N_Zprime_ABCDCHSSoftDrop","I");
   vars.InitVars("Zprimes_ABCDCHSSoftDrop_M",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Zprimes_ABCDCHSSoftDrop_Pt",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Tprimes_ABCDCHSSoftDrop_M",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Tprimes_ABCDCHSSoftDrop_Pt",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_Pt",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_Eta",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_Phi",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_CSV",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_WeightCSVnominal",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_WeightCSVLFup",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_WeightCSVLFdown",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_WeightCSVHFup",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_WeightCSVHFdown",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_WeightCSVHFStats1up",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_WeightCSVHFStats1down",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_WeightCSVLFStats1up",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_WeightCSVLFStats1down",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_WeightCSVHFStats2up",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_WeightCSVHFStats2down",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_WeightCSVLFStats2up",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_WeightCSVLFStats2down",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_WeightCSVCErr1up",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_WeightCSVCErr1down",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_WeightCSVCErr2up",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_WeightCSVCErr2down",-9.0,"N_Zprime_ABCDCHSSoftDrop");

   vars.InitVars("Ws_ABCDCHSSoftDrop_corrL1L2L3",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Ws_ABCDCHSSoftDrop_corrL2L3",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Ws_ABCDCHSSoftDrop_Pt",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Ws_ABCDCHSSoftDrop_real",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Ws_ABCDCHSSoftDrop_matcheddecays",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Ws_ABCDCHSSoftDrop_Eta",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Ws_ABCDCHSSoftDrop_Phi",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Ws_ABCDCHSSoftDrop_MSD",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Ws_ABCDCHSSoftDrop_t21",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Tops_ABCDCHSSoftDrop_corrL1L2L3",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Tops_ABCDCHSSoftDrop_corrL2L3",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Tops_ABCDCHSSoftDrop_Pt",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Tops_ABCDCHSSoftDrop_real",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Tops_ABCDCHSSoftDrop_matcheddecays",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Tops_ABCDCHSSoftDrop_Eta",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Tops_ABCDCHSSoftDrop_Phi",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Tops_ABCDCHSSoftDrop_MSD",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Tops_ABCDCHSSoftDrop_t32",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Tops_ABCDCHSSoftDrop_maxsubjetCSVv2",-9.0,"N_Zprime_ABCDCHSSoftDrop");

   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVnominal",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVLFup",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVLFdown",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVHFup",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVHFdown",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVHFStats1up",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVHFStats1down",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVLFStats1up",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVLFStats1down",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVHFStats2up",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVHFStats2down",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVLFStats2up",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVLFStats2down",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVCErr1up",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVCErr1down",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVCErr2up",-9.0,"N_Zprime_ABCDCHSSoftDrop");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVCErr2down",-9.0,"N_Zprime_ABCDCHSSoftDrop");   
   
   
   
   
   
   vars.InitVar("N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag","I");
   vars.InitVars("Zprimes_ABCDCHSSoftDrop_masscorrnotopbtag_M",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Zprimes_ABCDCHSSoftDrop_masscorrnotopbtag_Pt",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Tprimes_ABCDCHSSoftDrop_masscorrnotopbtag_M",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Tprimes_ABCDCHSSoftDrop_masscorrnotopbtag_Pt",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_Pt",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_Eta",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_Phi",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_CSV",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVnominal",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFup",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFdown",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFup",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFdown",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFStats1up",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFStats1down",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFStats1up",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFStats1down",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFStats2up",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFStats2down",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFStats2up",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFStats2down",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVCErr1up",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVCErr1down",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVCErr2up",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVCErr2down",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");   
   
   vars.InitVars("Ws_ABCDCHSSoftDrop_masscorrnotopbtag_Pt",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Ws_ABCDCHSSoftDrop_masscorrnotopbtag_real",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Ws_ABCDCHSSoftDrop_masscorrnotopbtag_matcheddecays",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Ws_ABCDCHSSoftDrop_masscorrnotopbtag_Eta",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Ws_ABCDCHSSoftDrop_masscorrnotopbtag_Phi",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Ws_ABCDCHSSoftDrop_masscorrnotopbtag_MSD",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Ws_ABCDCHSSoftDrop_masscorrnotopbtag_t21",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Tops_ABCDCHSSoftDrop_masscorrnotopbtag_Pt",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Tops_ABCDCHSSoftDrop_masscorrnotopbtag_real",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Tops_ABCDCHSSoftDrop_masscorrnotopbtag_matcheddecays",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Tops_ABCDCHSSoftDrop_masscorrnotopbtag_Eta",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Tops_ABCDCHSSoftDrop_masscorrnotopbtag_Phi",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Tops_ABCDCHSSoftDrop_masscorrnotopbtag_MSD",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Tops_ABCDCHSSoftDrop_masscorrnotopbtag_t32",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Tops_ABCDCHSSoftDrop_masscorrnotopbtag_maxsubjetCSVv2",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
 
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVnominal",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFup",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFdown",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFup",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFdown",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFStats1up",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFStats1down",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFStats1up",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFStats1down",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFStats2up",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFStats2down",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFStats2up",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFStats2down",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVCErr1up",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVCErr1down",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVCErr2up",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVCErr2down",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag");      
   
   
   
   vars.InitVar("N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag","I");
   vars.InitVars("Zprimes_ABCDCHSSoftDrop_masscorrwithtopbtag_M",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Zprimes_ABCDCHSSoftDrop_masscorrwithtopbtag_Pt",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Tprimes_ABCDCHSSoftDrop_masscorrwithtopbtag_M",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Tprimes_ABCDCHSSoftDrop_masscorrwithtopbtag_Pt",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_Pt",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_Eta",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_Phi",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_CSV",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVnominal",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFup",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFdown",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFup",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFdown",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFStats1up",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFStats1down",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFStats1up",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFStats1down",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFStats2up",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFStats2down",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFStats2up",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFStats2down",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVCErr1up",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVCErr1down",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVCErr2up",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVCErr2down",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");      
   
   vars.InitVars("Ws_ABCDCHSSoftDrop_masscorrwithtopbtag_Pt",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Ws_ABCDCHSSoftDrop_masscorrwithtopbtag_real",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Ws_ABCDCHSSoftDrop_masscorrwithtopbtag_matcheddecays",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Ws_ABCDCHSSoftDrop_masscorrwithtopbtag_Eta",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Ws_ABCDCHSSoftDrop_masscorrwithtopbtag_Phi",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Ws_ABCDCHSSoftDrop_masscorrwithtopbtag_MSD",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Ws_ABCDCHSSoftDrop_masscorrwithtopbtag_t21",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Tops_ABCDCHSSoftDrop_masscorrwithtopbtag_Pt",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Tops_ABCDCHSSoftDrop_masscorrwithtopbtag_real",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Tops_ABCDCHSSoftDrop_masscorrwithtopbtag_matcheddecays",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Tops_ABCDCHSSoftDrop_masscorrwithtopbtag_Eta",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Tops_ABCDCHSSoftDrop_masscorrwithtopbtag_Phi",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Tops_ABCDCHSSoftDrop_masscorrwithtopbtag_MSD",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Tops_ABCDCHSSoftDrop_masscorrwithtopbtag_t32",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Tops_ABCDCHSSoftDrop_masscorrwithtopbtag_maxsubjetCSVv2",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");   
  
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVnominal",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFup",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFdown",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFup",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFdown",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFStats1up",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFStats1down",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFStats1up",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFStats1down",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFStats2up",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFStats2down",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFStats2up",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFStats2down",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVCErr1up",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVCErr1down",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVCErr2up",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");
   vars.InitVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVCErr2down",-9.0,"N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag");      
   
   
   vars.InitVar("N_Zprime_ABCDCHSPruning","I");
   vars.InitVars("Zprimes_ABCDCHSPruning_M",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Zprimes_ABCDCHSPruning_Pt",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Tprimes_ABCDCHSPruning_M",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Tprimes_ABCDCHSPruning_Pt",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Bottoms_ABCDCHSPruning_Pt",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Bottoms_ABCDCHSPruning_Eta",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Bottoms_ABCDCHSPruning_Phi",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Bottoms_ABCDCHSPruning_CSV",-9.0,"N_Zprime_ABCDCHSPruning");
   
   vars.InitVars("Bottoms_ABCDCHSPruning_WeightCSVnominal",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Bottoms_ABCDCHSPruning_WeightCSVLFup",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Bottoms_ABCDCHSPruning_WeightCSVLFdown",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Bottoms_ABCDCHSPruning_WeightCSVHFup",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Bottoms_ABCDCHSPruning_WeightCSVHFdown",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Bottoms_ABCDCHSPruning_WeightCSVHFStats1up",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Bottoms_ABCDCHSPruning_WeightCSVHFStats1down",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Bottoms_ABCDCHSPruning_WeightCSVLFStats1up",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Bottoms_ABCDCHSPruning_WeightCSVLFStats1down",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Bottoms_ABCDCHSPruning_WeightCSVHFStats2up",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Bottoms_ABCDCHSPruning_WeightCSVHFStats2down",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Bottoms_ABCDCHSPruning_WeightCSVLFStats2up",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Bottoms_ABCDCHSPruning_WeightCSVLFStats2down",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Bottoms_ABCDCHSPruning_WeightCSVCErr1up",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Bottoms_ABCDCHSPruning_WeightCSVCErr1down",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Bottoms_ABCDCHSPruning_WeightCSVCErr2up",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Bottoms_ABCDCHSPruning_WeightCSVCErr2down",-9.0,"N_Zprime_ABCDCHSPruning");

   vars.InitVars("Ws_ABCDCHSPruning_matcheddecays",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Ws_ABCDCHSPruning_real",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Ws_ABCDCHSPruning_corrL1L2L3",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Ws_ABCDCHSPruning_corrL2L3",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Ws_ABCDCHSPruning_Pt",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Ws_ABCDCHSPruning_Eta",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Ws_ABCDCHSPruning_Phi",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Ws_ABCDCHSPruning_MSD",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Ws_ABCDCHSPruning_MSD_smeared",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Ws_ABCDCHSPruning_MSD_JetResup",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Ws_ABCDCHSPruning_MSD_JetResdown",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Ws_ABCDCHSPruning_t21",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Tops_ABCDCHSPruning_matcheddecays",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Tops_ABCDCHSPruning_real",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Tops_ABCDCHSPruning_corrL1L2L3",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Tops_ABCDCHSPruning_corrL2L3",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Tops_ABCDCHSPruning_Pt",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Tops_ABCDCHSPruning_Eta",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Tops_ABCDCHSPruning_Phi",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Tops_ABCDCHSPruning_MSD",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Tops_ABCDCHSPruning_t32",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Tops_ABCDCHSPruning_maxsubjetCSVv2",-9.0,"N_Zprime_ABCDCHSPruning");

   vars.InitVars("Topsubjets_ABCDCHSPruning_WeightCSVnominal",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Topsubjets_ABCDCHSPruning_WeightCSVLFup",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Topsubjets_ABCDCHSPruning_WeightCSVLFdown",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Topsubjets_ABCDCHSPruning_WeightCSVHFup",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Topsubjets_ABCDCHSPruning_WeightCSVHFdown",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Topsubjets_ABCDCHSPruning_WeightCSVHFStats1up",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Topsubjets_ABCDCHSPruning_WeightCSVHFStats1down",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Topsubjets_ABCDCHSPruning_WeightCSVLFStats1up",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Topsubjets_ABCDCHSPruning_WeightCSVLFStats1down",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Topsubjets_ABCDCHSPruning_WeightCSVHFStats2up",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Topsubjets_ABCDCHSPruning_WeightCSVHFStats2down",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Topsubjets_ABCDCHSPruning_WeightCSVLFStats2up",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Topsubjets_ABCDCHSPruning_WeightCSVLFStats2down",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Topsubjets_ABCDCHSPruning_WeightCSVCErr1up",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Topsubjets_ABCDCHSPruning_WeightCSVCErr1down",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Topsubjets_ABCDCHSPruning_WeightCSVCErr2up",-9.0,"N_Zprime_ABCDCHSPruning");
   vars.InitVars("Topsubjets_ABCDCHSPruning_WeightCSVCErr2down",-9.0,"N_Zprime_ABCDCHSPruning");   
   
   
   vars.InitVar("N_Zprime_ABCDPUPPISoftDrop","I");
   vars.InitVars("Zprimes_ABCDPUPPISoftDrop_M",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Zprimes_ABCDPUPPISoftDrop_Pt",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Tprimes_ABCDPUPPISoftDrop_M",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Tprimes_ABCDPUPPISoftDrop_Pt",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Bottoms_ABCDPUPPISoftDrop_Pt",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Bottoms_ABCDPUPPISoftDrop_Eta",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Bottoms_ABCDPUPPISoftDrop_Phi",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Bottoms_ABCDPUPPISoftDrop_CSV",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   
   vars.InitVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVnominal",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVLFup",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVLFdown",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVHFup",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVHFdown",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVHFStats1up",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVHFStats1down",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVLFStats1up",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVLFStats1down",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVHFStats2up",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVHFStats2down",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVLFStats2up",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVLFStats2down",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVCErr1up",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVCErr1down",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVCErr2up",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVCErr2down",-9.0,"N_Zprime_ABCDPUPPISoftDrop");

   vars.InitVars("Ws_ABCDPUPPISoftDrop_matcheddecays",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Ws_ABCDPUPPISoftDrop_real",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Ws_ABCDPUPPISoftDrop_corrL1L2L3",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Ws_ABCDPUPPISoftDrop_corrL2L3",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Ws_ABCDPUPPISoftDrop_Pt",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Ws_ABCDPUPPISoftDrop_Eta",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Ws_ABCDPUPPISoftDrop_Phi",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Ws_ABCDPUPPISoftDrop_MSD",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Ws_ABCDPUPPISoftDrop_t21",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Tops_ABCDPUPPISoftDrop_matcheddecays",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Tops_ABCDPUPPISoftDrop_real",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Tops_ABCDPUPPISoftDrop_corrL1L2L3",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Tops_ABCDPUPPISoftDrop_corrL2L3",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Tops_ABCDPUPPISoftDrop_Pt",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Tops_ABCDPUPPISoftDrop_Eta",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Tops_ABCDPUPPISoftDrop_Phi",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Tops_ABCDPUPPISoftDrop_MSD",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Tops_ABCDPUPPISoftDrop_t32",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Tops_ABCDPUPPISoftDrop_maxsubjetCSVv2",-9.0,"N_Zprime_ABCDPUPPISoftDrop");

   vars.InitVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVnominal",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVLFup",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVLFdown",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVHFup",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVHFdown",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVHFStats1up",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVHFStats1down",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVLFStats1up",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVLFStats1down",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVHFStats2up",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVHFStats2down",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVLFStats2up",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVLFStats2down",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVCErr1up",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVCErr1down",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVCErr2up",-9.0,"N_Zprime_ABCDPUPPISoftDrop");
   vars.InitVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVCErr2down",-9.0,"N_Zprime_ABCDPUPPISoftDrop");   
   
      
   
   
   
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
    
//     bool top_candidatefound=false;
//     bool top_anti_candidatefound=false;
//     bool top_withbtag_candidatefound=false;
//     bool top_withbtag_anti_candidatefound=false;
//     bool W_candidatefound=false;
//     bool W_anti_candidatefound=false;
//     bool bottom_candidatefound=false;
//     bool bottom_anti_candidatefound=false;
    
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

    
//     std::vector<pat::Jet> AK15_top_candidates;
//     std::vector<pat::Jet> AK15_W_candidates;
//     std::vector<pat::Jet> AK12_top_candidates;
//     std::vector<pat::Jet> AK12_W_candidates;
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

    
    
    std::vector<pat::Jet> CHSSoftDrop_top_candidates;
    std::vector<pat::Jet> CHSSoftDrop_W_candidates;
    std::vector<pat::Jet> CHSPruning_top_candidates;
    std::vector<pat::Jet> CHSPruning_W_candidates;
    std::vector<pat::Jet> PUPPISoftDrop_top_candidates;
    std::vector<pat::Jet> PUPPISoftDrop_W_candidates;    
    
    std::vector<pat::Jet> AK4CHS_b_candidates;
    std::vector<pat::Jet> AK4PUPPI_b_candidates;
    
    
    std::vector<math::XYZTLorentzVector> ZprimesABCDCHSSoftDrop;
    std::vector<math::XYZTLorentzVector> TprimesABCDCHSSoftDrop;
    std::vector<pat::Jet> TopsABCDCHSSoftDrop;
    std::vector<pat::Jet> BottomsABCDCHSSoftDrop;
    std::vector<pat::Jet> WsABCDCHSSoftDrop;
    
    std::vector<math::XYZTLorentzVector> ZprimesABCDCHSSoftDropmasscorrnotopbtag;
    std::vector<math::XYZTLorentzVector> TprimesABCDCHSSoftDropmasscorrnotopbtag;
    std::vector<pat::Jet> TopsABCDCHSSoftDropmasscorrnotopbtag;
    std::vector<pat::Jet> BottomsABCDCHSSoftDropmasscorrnotopbtag;
    std::vector<pat::Jet> WsABCDCHSSoftDropmasscorrnotopbtag;
    
    std::vector<math::XYZTLorentzVector> ZprimesABCDCHSSoftDropmasscorrwithtopbtag;
    std::vector<math::XYZTLorentzVector> TprimesABCDCHSSoftDropmasscorrwithtopbtag;
    std::vector<pat::Jet> TopsABCDCHSSoftDropmasscorrwithtopbtag;
    std::vector<pat::Jet> BottomsABCDCHSSoftDropmasscorrwithtopbtag;
    std::vector<pat::Jet> WsABCDCHSSoftDropmasscorrwithtopbtag;
    
    
    std::vector<math::XYZTLorentzVector> ZprimesABCDCHSPruning;
    std::vector<math::XYZTLorentzVector> TprimesABCDCHSPruning;
    std::vector<pat::Jet> TopsABCDCHSPruning;
    std::vector<pat::Jet> BottomsABCDCHSPruning;
    std::vector<pat::Jet> WsABCDCHSPruning;

    
    std::vector<math::XYZTLorentzVector> ZprimesABCDPUPPISoftDrop;
    std::vector<math::XYZTLorentzVector> TprimesABCDPUPPISoftDrop;
    std::vector<pat::Jet> TopsABCDPUPPISoftDrop;
    std::vector<pat::Jet> BottomsABCDPUPPISoftDrop;
    std::vector<pat::Jet> WsABCDPUPPISoftDrop;
  
        
    
    std::vector<reco::GenParticle> TopZprime;
    std::vector<reco::GenParticle> TPrime;
    std::vector<reco::GenParticle> WfromTPrime;
    std::vector<reco::GenParticle> bfromTPrime;
    
    std::vector<reco::GenParticle> TopBG;
    std::vector<reco::GenParticle> TopsTprimes;
    std::vector<reco::GenParticle> BottomBG;
    std::vector<reco::GenParticle> WBG;
    std::vector<reco::GenParticle> WfromTop;
    
    std::vector<reco::GenParticle> Top_Decayquarks;
    std::vector<reco::GenParticle> Topbar_Decayquarks;
    std::vector<reco::GenParticle> WplusfromTPrime_Decayproducts;
    std::vector<reco::GenParticle> WminusfromTPrime_Decayproducts;
    std::vector<reco::GenParticle> WplusfromTop_Decayproducts;
    std::vector<reco::GenParticle> WminusfromTop_Decayproducts;
    std::vector<reco::GenParticle> WplusfromBG_Decayproducts;
    std::vector<reco::GenParticle> WminusfromBG_Decayproducts;
    
    
    std::vector<reco::GenParticle> GenTops;
    std::vector<reco::GenParticle> GenWs;
    std::vector<reco::GenParticle> GenTops_decayproducts;
    std::vector<reco::GenParticle> GenWs_decayproducts;    
    
    
    
    
    
    
    
  if(!initialized) cerr << "tree processor not initialized" << std::endl; // complain if not initialized but keep running
//     std::cout<<"here"<<endl;
  
  
  if(input.zprimetotprimeallhad.IsFilled()){
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

    vars.FillVar("N_packedPatJetsAK8PFCHSSoftDrop", input.selectedJetsAK8CHSSoftDrop.size());
//     vars.FillVar("N_packedPatJetsAK8PFCHSPruning", input.selectedJetsAK8CHSPruning.size());
//     vars.FillVar("N_packedPatJetsAK8PFPUPPISoftDrop", input.selectedJetsAK8PUPPISoftDrop.size());
//     vars.FillVar("N_packedPatJetsAK8PFPUPPIPruning", input.selectedJetsAK8PUPPIPruning.size());
    
//    vars.FillVar("N_selectedPatJetsAK8PFCHSSoftDropPacked", input.selectedPatJetsAK8PFCHSSoftDropPacked.size());
//    vars.FillVar("N_packedPatJetsAK8PFCHSSoftDrop", input.selectedJetsAK8CHSSoftDrop.size());

   //std::cout<<"there8"<<endl;
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
  }
    

    
    if(input.zprimetotprimeallhad.IsFilled()){
        TPrime=input.zprimetotprimeallhad.GetTPrimesandTPrimebars();
        bfromTPrime=input.zprimetotprimeallhad.GetBottom_fromTPrimesandTPrimebars();
        BottomBG=input.zprimetotprimeallhad.GetBottomsandBottombars_fromBG();
        
        TopZprime=input.zprimetotprimeallhad.GetTopsandTopbars_fromZprimes();
        TopsTprimes=input.zprimetotprimeallhad.GetTopsandTopbars_fromZprimes();
        TopBG=input.zprimetotprimeallhad.GetTopsandTopbars_fromBG();
        
        WfromTPrime=input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars();
        WfromTop=input.zprimetotprimeallhad.GetW_fromTopsandTopbars();
        WBG=input.zprimetotprimeallhad.GetWs_fromBG();
        
        Top_Decayquarks=input.zprimetotprimeallhad.GetTopDecayQuarks();
        Topbar_Decayquarks=input.zprimetotprimeallhad.GetTopBarDecayQuarks();
//         Top_WDecayquarks=input.zprimetotprimeallhad.GetW_decay_products_fromTop()
//         Topbar_WDecayquarks=input.zprimetotprimeallhad.GetW_decay_products_fromTopbar()
        
        WplusfromTPrime_Decayproducts=input.zprimetotprimeallhad.GetW_decay_products_fromTPrime();
        WminusfromTPrime_Decayproducts=input.zprimetotprimeallhad.GetW_decay_products_fromTPrimebar();
        WplusfromTop_Decayproducts=input.zprimetotprimeallhad.GetW_decay_products_fromTop();
        WminusfromTop_Decayproducts=input.zprimetotprimeallhad.GetW_decay_products_fromTopbar();
        WplusfromBG_Decayproducts=input.zprimetotprimeallhad.GetWplus_decay_products_fromBG();
        WminusfromBG_Decayproducts=input.zprimetotprimeallhad.GetWminus_decay_products_fromBG();
        
        
        for (uint i=0;i<TopZprime.size();i++){
            GenTops.push_back(TopZprime[i]);
        }
        for (uint i=0;i<TopsTprimes.size();i++){
            GenTops.push_back(TopsTprimes[i]);
        }  
        for (uint i=0;i<TopBG.size();i++){
            GenTops.push_back(TopBG[i]);
        }        
        
        for (uint i=0;i<WfromTPrime.size();i++){
            GenWs.push_back(WfromTPrime[i]);
        }      
        for (uint i=0;i<WfromTop.size();i++){
            GenWs.push_back(WfromTop[i]);
        }  
        for (uint i=0;i<WBG.size();i++){
            GenWs.push_back(WBG[i]);
        }  
        
        for (uint i=0;i<Top_Decayquarks.size();i++){
            GenTops_decayproducts.push_back(Top_Decayquarks[i]);
        }
        for (uint i=0;i<Topbar_Decayquarks.size();i++){
            GenTops_decayproducts.push_back(Topbar_Decayquarks[i]);
        }
        for (uint i=0;i<WplusfromTop_Decayproducts.size();i++){
            GenTops_decayproducts.push_back(WplusfromTop_Decayproducts[i]);
        }
        for (uint i=0;i<WminusfromTop_Decayproducts.size();i++){
            GenTops_decayproducts.push_back(WminusfromTop_Decayproducts[i]);
        }
        
        for (uint i=0;i<WplusfromTPrime_Decayproducts.size();i++){
            GenWs_decayproducts.push_back(WplusfromTPrime_Decayproducts[i]);
        }
        for (uint i=0;i<WminusfromTPrime_Decayproducts.size();i++){
            GenWs_decayproducts.push_back(WminusfromTPrime_Decayproducts[i]);
        }
        for (uint i=0;i<WplusfromTop_Decayproducts.size();i++){
            GenWs_decayproducts.push_back(WplusfromTop_Decayproducts[i]);
        }
        for (uint i=0;i<WminusfromTop_Decayproducts.size();i++){
            GenWs_decayproducts.push_back(WminusfromTop_Decayproducts[i]);
        } 
        for (uint i=0;i<WplusfromBG_Decayproducts.size();i++){
            GenWs_decayproducts.push_back(WplusfromBG_Decayproducts[i]);
        }
        for (uint i=0;i<WminusfromBG_Decayproducts.size();i++){
            GenWs_decayproducts.push_back(WminusfromBG_Decayproducts[i]);
        } /*               
 ResourceMonitor* ResMon;
 ResMon= new ResourceMonitor();


 
        std::cout<<"asda1"<<std::endl;
        if (input.zprimetotprimeallhad.GetTopsandTopbars_fromZprimes().size() > 0){
        std::cout<<"asda1.1"<<std::endl;
            for (std::vector<reco::GenParticle>::const_iterator particle=input.zprimetotprimeallhad.GetTopsandTopbars_fromZprimes().begin(); particle != input.zprimetotprimeallhad.GetTopsandTopbars_fromZprimes().end(); ++particle){
        std::cout<<"asda1.2"<<std::endl;
                std::cout<<input.zprimetotprimeallhad.GetTopsandTopbars_fromZprimes().size()<<std::endl;
//                 GenTops.push_back(*particle);
        std::cout<<"asda1.3"<<std::endl;
            };
            for (uint i=0;i<input.zprimetotprimeallhad.GetTopsandTopbars_fromZprimes().size(); i++){
                std::cout<<input.zprimetotprimeallhad.GetTopsandTopbars_fromZprimes().size()<<std::endl;
//                 l=
                GenTops.push_back(input.zprimetotprimeallhad.GetTopsandTopbars_fromZprimes()[i]);
            };
        ResMon->PrintMemoryUsage();
        ResMon->PrintSystemMemory();
        };
        delete ResMon;
        std::cout<<"asda1.4"<<std::endl;
        if (input.zprimetotprimeallhad.GetTopsandTopbars_fromTprimes().size()>0){
            for (std::vector<reco::GenParticle>::const_iterator particle=input.zprimetotprimeallhad.GetTopsandTopbars_fromTprimes().begin(); particle != input.zprimetotprimeallhad.GetTopsandTopbars_fromTprimes().end(); ++particle){
                GenTops.push_back(*particle);
            };
        };
        if (input.zprimetotprimeallhad.GetTopsandTopbars_fromBG().size()>0){
            for (std::vector<reco::GenParticle>::const_iterator particle=input.zprimetotprimeallhad.GetTopsandTopbars_fromBG().begin(); particle != input.zprimetotprimeallhad.GetTopsandTopbars_fromBG().end(); ++particle){
                GenTops.push_back(*particle);
            };
        };
        std::cout<<"asda2"<<std::endl;
        
        for (std::vector<reco::GenParticle>::const_iterator particle=input.zprimetotprimeallhad.GetW_fromTopsandTopbars().begin(); particle != input.zprimetotprimeallhad.GetW_fromTopsandTopbars().end(); ++particle){
            GenWs.push_back(*particle);
        };
        for (std::vector<reco::GenParticle>::const_iterator particle=input.zprimetotprimeallhad.GetWs_fromBG().begin(); particle != input.zprimetotprimeallhad.GetWs_fromBG().end(); ++particle){
            GenWs.push_back(*particle);
        };
        for (std::vector<reco::GenParticle>::const_iterator particle=input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars().begin(); particle != input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars().end(); ++particle){
            GenWs.push_back(*particle);
        };
            
        std::cout<<"asda3"<<std::endl;
        for (std::vector<reco::GenParticle>::const_iterator particle=input.zprimetotprimeallhad.GetW_decay_products_fromTop().begin(); particle != input.zprimetotprimeallhad.GetW_decay_products_fromTop().end(); ++particle){
            GenTops_decayproducts.push_back(*particle);
        };     
        for (std::vector<reco::GenParticle>::const_iterator particle=input.zprimetotprimeallhad.GetW_decay_products_fromTopbar().begin(); particle != input.zprimetotprimeallhad.GetW_decay_products_fromTopbar().end(); ++particle){
            GenTops_decayproducts.push_back(*particle);
        };  
        for (std::vector<reco::GenParticle>::const_iterator particle=input.zprimetotprimeallhad.GetTopDecayQuarks().begin(); particle != input.zprimetotprimeallhad.GetTopDecayQuarks().end(); ++particle){
            GenTops_decayproducts.push_back(*particle);
        };  
        for (std::vector<reco::GenParticle>::const_iterator particle=input.zprimetotprimeallhad.GetTopBarDecayQuarks().begin(); particle != input.zprimetotprimeallhad.GetTopBarDecayQuarks().end(); ++particle){
            GenTops_decayproducts.push_back(*particle);
        };  
        std::cout<<"asda5"<<std::endl;
        for (std::vector<reco::GenParticle>::const_iterator particle=input.zprimetotprimeallhad.GetW_decay_products_fromTop().begin(); particle != input.zprimetotprimeallhad.GetW_decay_products_fromTop().end(); ++particle){
            GenWs_decayproducts.push_back(*particle);
        };     
        for (std::vector<reco::GenParticle>::const_iterator particle=input.zprimetotprimeallhad.GetW_decay_products_fromTopbar().begin(); particle != input.zprimetotprimeallhad.GetW_decay_products_fromTopbar().end(); ++particle){
            GenWs_decayproducts.push_back(*particle);
        };  
        for (std::vector<reco::GenParticle>::const_iterator particle=input.zprimetotprimeallhad.GetW_decay_products_fromTPrime().begin(); particle != input.zprimetotprimeallhad.GetW_decay_products_fromTPrime().end(); ++particle){
            GenWs_decayproducts.push_back(*particle);
        };     
        for (std::vector<reco::GenParticle>::const_iterator particle=input.zprimetotprimeallhad.GetW_decay_products_fromTPrimebar().begin(); particle != input.zprimetotprimeallhad.GetW_decay_products_fromTPrimebar().end(); ++particle){
            GenWs_decayproducts.push_back(*particle);
        };          
        for (std::vector<reco::GenParticle>::const_iterator particle=input.zprimetotprimeallhad.GetWplus_decay_products_fromBG().begin(); particle != input.zprimetotprimeallhad.GetWplus_decay_products_fromBG().end(); ++particle){
            GenWs_decayproducts.push_back(*particle);
        };     
        for (std::vector<reco::GenParticle>::const_iterator particle=input.zprimetotprimeallhad.GetWminus_decay_products_fromBG().begin(); particle != input.zprimetotprimeallhad.GetWminus_decay_products_fromBG().end(); ++particle){
            GenWs_decayproducts.push_back(*particle);
        };*/

    }
    
    
    vars.FillVar("N_Gen_BottomfromBG",BottomBG.size());

       //std::cout<<"after gen "<<GenWs.size()<<endl;
    
//AK8->Jets
    if(input.selectedJetsAK8CHSSoftDrop.size()>0){
            
///General AK8-Jet        
        for(std::vector<pat::Jet>::const_iterator itJet=input.selectedJetsAK8CHSSoftDrop.begin(); itJet != input.selectedJetsAK8CHSSoftDrop.end(); ++itJet){
            int iJet = itJet - input.selectedJetsAK8CHSSoftDrop.begin();
            if (itJet->pt()<150 || abs(itJet->eta())>2.4){
                continue;
            }
            vars.FillVars("packedPatJetsAK8PFCHSSoftDrop_E",iJet,itJet->energy());
            vars.FillVars("packedPatJetsAK8PFCHSSoftDrop_M",iJet,itJet->mass());
            vars.FillVars("packedPatJetsAK8PFCHSSoftDrop_Pt",iJet,itJet->pt());
            vars.FillVars("packedPatJetsAK8PFCHSSoftDrop_Phi",iJet,itJet->phi());
            vars.FillVars("packedPatJetsAK8PFCHSSoftDrop_Eta",iJet,itJet->eta());

            vars.FillVars("AK8CHSSoftDrop_Njettinesstau1",iJet,itJet->userFloat("NjettinessAK8CHS:tau1"));
            vars.FillVars("AK8CHSSoftDrop_Njettinesstau2",iJet,itJet->userFloat("NjettinessAK8CHS:tau2"));
            vars.FillVars("AK8CHSSoftDrop_Njettinesstau3",iJet,itJet->userFloat("NjettinessAK8CHS:tau3"));
            vars.FillVars("AK8CHSSoftDrop_M",iJet, itJet->userFloat("ak8PFJetsCHSSoftDropMass"));


            double max_subjet_csv_v2=-10;
            auto const & names = itJet->subjets("SoftDrop");
            for( auto const & itsubJet : names ){

                if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>max_subjet_csv_v2){
                    max_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
                    vars.FillVars("AK8CHSSoftDrop_maxsubjetCSV",iJet,max_subjet_csv_v2);
                }
            }
        }
    }
   if(input.selectedJetsAK8CHSPruning.size()>0){
            
///General AK8-Jet        
        for(std::vector<pat::Jet>::const_iterator itJet=input.selectedJetsAK8CHSPruning.begin(); itJet != input.selectedJetsAK8CHSPruning.end(); ++itJet){
            int iJet = itJet - input.selectedJetsAK8CHSPruning.begin();
            if (itJet->pt()<150 || abs(itJet->eta())>2.4){
                continue;
            }
            vars.FillVars("packedPatJetsAK8PFCHSPruning_E",iJet,itJet->energy());
            vars.FillVars("packedPatJetsAK8PFCHSPruning_M",iJet,itJet->mass());
            vars.FillVars("packedPatJetsAK8PFCHSPruning_Pt",iJet,itJet->pt());
            vars.FillVars("packedPatJetsAK8PFCHSPruning_Phi",iJet,itJet->phi());
            vars.FillVars("packedPatJetsAK8PFCHSPruning_Eta",iJet,itJet->eta());


            vars.FillVars("AK8CHSPruning_Njettinesstau1",iJet,itJet->userFloat("NjettinessAK8CHS:tau1"));
            vars.FillVars("AK8CHSPruning_Njettinesstau2",iJet,itJet->userFloat("NjettinessAK8CHS:tau2"));
            vars.FillVars("AK8CHSPruning_Njettinesstau3",iJet,itJet->userFloat("NjettinessAK8CHS:tau3"));
            vars.FillVars("AK8CHSPruning_M",iJet, itJet->userFloat("ak8PFJetsCHSPrunedMass"));


            double max_subjet_csv_v2=-10;
            auto const & names = itJet->subjets("Pruned");
            for( auto const & itsubJet : names ){

                if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>max_subjet_csv_v2){
                    max_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
                    vars.FillVars("AK8CHSPruning_maxsubjetCSV",iJet,max_subjet_csv_v2);
                }
            }
        }
    }
   if(input.selectedJetsAK8PUPPISoftDrop.size()>0){
            
///General AK8-Jet        
        for(std::vector<pat::Jet>::const_iterator itJet=input.selectedJetsAK8PUPPISoftDrop.begin(); itJet != input.selectedJetsAK8PUPPISoftDrop.end(); ++itJet){
            int iJet = itJet - input.selectedJetsAK8PUPPISoftDrop.begin();
            if (itJet->pt()<150 || abs(itJet->eta())>2.4){
                continue;
            }
            vars.FillVars("packedPatJetsAK8PFPUPPISoftDrop_E",iJet,itJet->energy());
            vars.FillVars("packedPatJetsAK8PFPUPPISoftDrop_M",iJet,itJet->mass());
            vars.FillVars("packedPatJetsAK8PFPUPPISoftDrop_Pt",iJet,itJet->pt());
            vars.FillVars("packedPatJetsAK8PFPUPPISoftDrop_Phi",iJet,itJet->phi());
            vars.FillVars("packedPatJetsAK8PFPUPPISoftDrop_Eta",iJet,itJet->eta());

            vars.FillVars("AK8PUPPISoftDrop_Njettinesstau1",iJet,itJet->userFloat("NjettinessAK8Puppi:tau1"));
            vars.FillVars("AK8PUPPISoftDrop_Njettinesstau2",iJet,itJet->userFloat("NjettinessAK8Puppi:tau2"));
            vars.FillVars("AK8PUPPISoftDrop_Njettinesstau3",iJet,itJet->userFloat("NjettinessAK8Puppi:tau3"));
            vars.FillVars("AK8PUPPISoftDrop_M",iJet, itJet->userFloat("ak8PFJetsPuppiSoftDropMass"));


            double max_subjet_csv_v2=-10;
            auto const & names = itJet->subjets("SoftDrop");
            for( auto const & itsubJet : names ){

                if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>max_subjet_csv_v2){
                    max_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
                    vars.FillVars("AK8PUPPISoftDrop_maxsubjetCSV",iJet,max_subjet_csv_v2);
                }
            }
        }
    }
    //std::cout<<"there10"<<endl;

///////Object Identification///////
    float ht =0.;
    for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin() ; itJet != input.selectedJets.end(); ++itJet){
        ht += itJet->pt();
    }
    if( ht>650){
   
    

//AK8->Jets
    if(input.selectedJetsAK8CHSSoftDrop.size()>0){
       
///General AK8-Jet        
        for(std::vector<pat::Jet>::const_iterator itJet=input.selectedJetsAK8CHSSoftDrop.begin(); itJet != input.selectedJetsAK8CHSSoftDrop.end(); ++itJet){
            //int iJet = itJet - input.selectedJetsAK8CHSSoftDrop.begin();

            /*double max_subjet_csv_v2=-10;
            auto const & names = itJet->subjets("SoftDrop");
            for( auto const & itsubJet : names ){

                if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>max_subjet_csv_v2){
                    max_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
                    vars.FillVars("selectedJetsAK8CHSSoftDrop_subjetCSVv2",iJet,max_subjet_csv_v2);
                }
            }*/
            
///top- and W-candidates
            if (itJet->pt()>200 && abs(itJet->eta())<2.4){
               
//top candidates
                if (itJet->pt()>400){
                    if(!(ZPrimeToTPrimeAllHadProcessor::Top_subbtag(*itJet,"M"))){
                        if(ZPrimeToTPrimeAllHadProcessor::Toptag(*itJet,"M")){
                            tops.push_back(*itJet);
//                             /*top_candidatefound*/=true;
//                             std::cout<<"top with no subbtag found"<<endl;
                        }else{
                            tops_anti.push_back(*itJet);
//                             top_anti_candidatefound=true;
//                             std::cout<<"top anti with no subbtag found"<<endl;
                        }

                    }else{
                        if(ZPrimeToTPrimeAllHadProcessor::Toptag(*itJet,"M")){
                            tops_withbtag.push_back(*itJet);
//                             top_withbtag_candidatefound=true;
//                             std::cout<<"top withsubbtag found"<<endl;
                        }else{
                            tops_withbtag_anti.push_back(*itJet);
//                             top_withbtag_anti_candidatefound=true;
//                             std::cout<<"top anti withsubbtag found"<<endl;
                        }
                    }
                }

                    
//W candidates
                if (ZPrimeToTPrimeAllHadProcessor::Wtag(*itJet, "M")){
                    Ws.push_back(*itJet);
//                     W_candidatefound=true;
                }
                else {
                    Ws_anti.push_back(*itJet);
//                     W_anti_candidatefound=true;
                }
                
//Z candidates
                if(itJet->userFloat("NjettinessAK8CHS:tau3")>0 && itJet->userFloat("NjettinessAK8CHS:tau2")>0 && itJet->userFloat("NjettinessAK8CHS:tau1")>0 && itJet->userFloat("NjettinessAK8CHS:tau2")/itJet->userFloat("NjettinessAK8CHS:tau1")<0.6 && 80<itJet->userFloat("ak8PFJetsCHSSoftDropMass") && itJet->userFloat("ak8PFJetsCHSSoftDropMass")<110){
                    Zs.push_back(*itJet);
//                     Z_candidatefound=true;
                } else {
                    Zs_anti.push_back(*itJet);
//                     Z_anti_candidatefound=true;
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
//                         Higgs_with1btag_candidatefound=true;
                    } else {
                        Higgs_with1btag_anti.push_back(*itJet);
//                         Higgs_with1btag_anti_candidatefound=true;
                    }
                    if (min_subjet_csv_v2>0.8){
                        Higgs_with2btag.push_back(*itJet);
//                         Higgs_with2btag_candidatefound=true;
                    } else {
                        Higgs_with2btag_anti.push_back(*itJet);
//                         Higgs_with2btag_anti_candidatefound=true;    
                        
                    }
                    
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
//                 bottom_candidatefound=true; 
                //separated_bottom_candidatefound=true;
            }
            else{
                bottoms_anti.push_back(*itJet);
//                 bottom_anti_candidatefound=true;
                //separated_bottom_anti_candidatefound=true;
            }
        
        }
        
        
    }
  }
  
       //std::cout<<"check GenWs1 "<<GenWs.size()<<endl;
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
  //std::cout<<"here6"<<endl;
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
    //std::cout<<"here7"<<endl;
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
  
       //std::cout<<"check GenWs2 "<<GenWs.size()<<endl;
    //std::cout<<"here8"<<endl;
    
  if(Z_candidatefound && Z_anti_candidatefound && Higgs_candidatefound && Higgs_with1btag_candidatefound && Higgs_with2btag_candidatefound && Higgs_anti_candidatefound && Higgs_with1btag_anti_candidatefound && Higgs_with2btag_anti_candidatefound){std::cout<<"this event makes no sense"<<endl;}
//     std::cout<<"heredetail1"<<endl;
    
    /*
  
  if ((top_candidatefound || top_withbtag_candidatefound || top_anti_candidatefound || top_withbtag_anti_candidatefound) && (W_candidatefound || W_anti_candidatefound) && (bottom_candidatefound ||bottom_anti_candidatefound)){
      if(W_candidatefound){
         if(top_candidatefound){
            ZPrimeReconstructionWtbComplete(vars,tops,Ws,bottoms, bottoms_anti,top_candidatefound, false, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), false, (W_anti_candidatefound  && !W_candidatefound),"Topfirst");
            ZPrimeReconstructionWtbComplete(vars,tops,Ws,bottoms,bottoms_anti,top_candidatefound, false, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), false, (W_anti_candidatefound  && !W_candidatefound),"Wfirst");             
         }
         if(top_withbtag_candidatefound){
            ZPrimeReconstructionWtbComplete(vars,tops_withbtag,Ws,bottoms, bottoms_anti,top_candidatefound, top_withbtag_candidatefound, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), (top_withbtag_anti_candidatefound && !top_withbtag_candidatefound), (W_anti_candidatefound  && !W_candidatefound),"Topfirst");
            ZPrimeReconstructionWtbComplete(vars,tops_withbtag,Ws,bottoms,bottoms_anti,top_candidatefound, top_withbtag_candidatefound, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), (top_withbtag_anti_candidatefound && !top_withbtag_candidatefound), (W_anti_candidatefound  && !W_candidatefound),"Wfirst");   
         }
         if(top_anti_candidatefound && !top_candidatefound){
            ZPrimeReconstructionWtbComplete(vars,tops_anti,Ws,bottoms, bottoms_anti,top_candidatefound, false, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), false, (W_anti_candidatefound  && !W_candidatefound),"Topfirst");
            ZPrimeReconstructionWtbComplete(vars,tops_anti,Ws,bottoms,bottoms_anti,top_candidatefound, false, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), false, (W_anti_candidatefound  && !W_candidatefound),"Wfirst");
         }
         if(top_withbtag_anti_candidatefound && !top_withbtag_candidatefound){
            ZPrimeReconstructionWtbComplete(vars,tops_withbtag_anti,Ws,bottoms, bottoms_anti,top_candidatefound, top_withbtag_candidatefound, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), (top_withbtag_anti_candidatefound && !top_withbtag_candidatefound), (W_anti_candidatefound  && !W_candidatefound),"Topfirst");
            ZPrimeReconstructionWtbComplete(vars,tops_withbtag_anti,Ws,bottoms,bottoms_anti,top_candidatefound, top_withbtag_candidatefound, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), (top_withbtag_anti_candidatefound && !top_withbtag_candidatefound), (W_anti_candidatefound  && !W_candidatefound),"Wfirst");                 
         }
      }

      if(W_anti_candidatefound  && !W_candidatefound){
         if(top_candidatefound){
            ZPrimeReconstructionWtbComplete(vars,tops,Ws_anti,bottoms, bottoms_anti,top_candidatefound, false, W_candidatefound, (top_anti_candidatefound && !top_candidatefound),false, (W_anti_candidatefound  && !W_candidatefound),"Topfirst");
            ZPrimeReconstructionWtbComplete(vars,tops,Ws_anti,bottoms,bottoms_anti,top_candidatefound, false, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), false, (W_anti_candidatefound  && !W_candidatefound),"Wfirst"); 
         }
         if(top_withbtag_candidatefound){
            ZPrimeReconstructionWtbComplete(vars,tops_withbtag,Ws_anti,bottoms, bottoms_anti,top_candidatefound, top_withbtag_candidatefound, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), (top_withbtag_anti_candidatefound && !top_withbtag_candidatefound), (W_anti_candidatefound  && !W_candidatefound),"Topfirst");
            ZPrimeReconstructionWtbComplete(vars,tops_withbtag,Ws_anti,bottoms,bottoms_anti,top_candidatefound, top_withbtag_candidatefound, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), (top_withbtag_anti_candidatefound && !top_withbtag_candidatefound), (W_anti_candidatefound  && !W_candidatefound),"Wfirst");        
         }
         if(top_anti_candidatefound && !top_candidatefound){
            ZPrimeReconstructionWtbComplete(vars,tops_anti,Ws_anti,bottoms, bottoms_anti,top_candidatefound, false, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), false, (W_anti_candidatefound  && !W_candidatefound),"Topfirst");
            ZPrimeReconstructionWtbComplete(vars,tops_anti,Ws_anti,bottoms,bottoms_anti,top_candidatefound, false, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), false, (W_anti_candidatefound  && !W_candidatefound),"Wfirst"); 
         }
         if(top_withbtag_anti_candidatefound && !top_withbtag_candidatefound){
            ZPrimeReconstructionWtbComplete(vars,tops_withbtag_anti,Ws_anti,bottoms, bottoms_anti,top_candidatefound, top_withbtag_candidatefound, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), (top_withbtag_anti_candidatefound && !top_withbtag_candidatefound), (W_anti_candidatefound  && !W_candidatefound),"Topfirst");
            ZPrimeReconstructionWtbComplete(vars,tops_withbtag_anti,Ws_anti,bottoms,bottoms_anti,top_candidatefound, top_withbtag_candidatefound, W_candidatefound, (top_anti_candidatefound && !top_candidatefound), (top_withbtag_anti_candidatefound && !top_withbtag_candidatefound), (W_anti_candidatefound  && !W_candidatefound),"Wfirst"); 
         }          
     }
  }
 */



       //std::cout<<"check GenWs3 "<<GenWs.size()<<endl;

///Misstag rate & tag efficiency
  
  if (input.zprimetotprimeallhad.IsFilled() && input.selectedJetsAK8CHSSoftDrop.size()>0){
    for(std::vector<pat::Jet>::const_iterator itJet=input.selectedJetsAK8CHSSoftDrop.begin(); itJet != input.selectedJetsAK8CHSSoftDrop.end(); ++itJet){
        int iJet = itJet - input.selectedJetsAK8CHSSoftDrop.begin();

        
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
       //std::cout<<"check GenWs4 "<<GenWs.size()<<endl;
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
       //std::cout<<"check GenWs5 "<<GenWs.size()<<endl;
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
  
       //std::cout<<"check GenWs6 "<<GenWs.size()<<endl;
  
//std::cout<<"bugsearch1"<<std::endl;
   
    
/// CHSSoftDrop          
    if(input.selectedJetsAK8CHSSoftDrop.size()>0){
        for(std::vector<pat::Jet>::const_iterator itJet=input.selectedJetsAK8CHSSoftDrop.begin(); itJet != input.selectedJetsAK8CHSSoftDrop.end(); ++itJet){
            if (itJet->pt()>150 || abs(itJet->eta())<2.4){
                CHSSoftDrop_W_candidates.push_back(*itJet);
                if (itJet->pt()>150){
                    CHSSoftDrop_top_candidates.push_back(*itJet);
                }                
            }
        }
    }        
  
    
/// CHSPruning         
    if(input.selectedJetsAK8CHSPruning.size()>0){
        for(std::vector<pat::Jet>::const_iterator itJet=input.selectedJetsAK8CHSPruning.begin(); itJet != input.selectedJetsAK8CHSPruning.end(); ++itJet){
            if (itJet->pt()>150 || abs(itJet->eta())<2.4){
                CHSPruning_W_candidates.push_back(*itJet);
                if (itJet->pt()>150){
                    CHSPruning_top_candidates.push_back(*itJet);
                }                
            }
        }
    }        
  
    
/// PUPPISoftDrop          
    if(input.selectedJetsAK8PUPPISoftDrop.size()>0){
        for(std::vector<pat::Jet>::const_iterator itJet=input.selectedJetsAK8PUPPISoftDrop.begin(); itJet != input.selectedJetsAK8PUPPISoftDrop.end(); ++itJet){
            if (itJet->pt()>150 || abs(itJet->eta())<2.4){
                PUPPISoftDrop_W_candidates.push_back(*itJet);
                if (itJet->pt()>150){
                    PUPPISoftDrop_top_candidates.push_back(*itJet);
                }                
            }
            
        }
    }     
    
    
/// AK4 bottoms          
    if(input.selectedJets.size()>0){
        for(std::vector<pat::Jet>::const_iterator itJet=input.selectedJets.begin(); itJet != input.selectedJets.end(); ++itJet){
            if (itJet->pt()>75 || abs(itJet->eta())<2.4){
                AK4CHS_b_candidates.push_back(*itJet);             
            }
        }
    } 
/// AK4 bottoms          
    if(input.selectedJetsAK4PUPPI.size()>0){
        for(std::vector<pat::Jet>::const_iterator itJet=input.selectedJetsAK4PUPPI.begin(); itJet != input.selectedJetsAK4PUPPI.end(); ++itJet){
            if (itJet->pt()>75 || abs(itJet->eta())<2.4){
                AK4PUPPI_b_candidates.push_back(*itJet);             
            }
        }
    }           
    
// std::cout<<"bugsearch2"<<std::endl;

/////ALL COMBINATIONS FOR ABCDCHSSoftDrop-METHODE
  if(CHSSoftDrop_top_candidates.size()>0 && CHSSoftDrop_W_candidates.size()>1 && AK4CHS_b_candidates.size()>0){
    for(std::vector<pat::Jet>::iterator ittopJet = CHSSoftDrop_top_candidates.begin() ; ittopJet != CHSSoftDrop_top_candidates.end(); ++ittopJet){
        for(std::vector<pat::Jet>::iterator itWJet = CHSSoftDrop_W_candidates.begin() ; itWJet != CHSSoftDrop_W_candidates.end(); ++itWJet){
            if(BoostedUtils::DeltaR(itWJet->p4(),ittopJet->p4())<0.8){
//                 std::cout<<"ah ah ah, W- and top-jets are the same"<<endl;
            }else{
                if(itWJet->userFloat("NjettinessAK8CHS:tau1")>0 && itWJet->userFloat("NjettinessAK8CHS:tau2")>0 && itWJet->userFloat("NjettinessAK8CHS:tau3")>0 && ittopJet->userFloat("NjettinessAK8CHS:tau1")>0 && ittopJet->userFloat("NjettinessAK8CHS:tau2")>0 && ittopJet->userFloat("NjettinessAK8CHS:tau3")>0){
                    for(std::vector<pat::Jet>::const_iterator itBJet = AK4CHS_b_candidates.begin() ; itBJet != AK4CHS_b_candidates.end(); ++itBJet){
                        if(BoostedUtils::DeltaR(itWJet->p4(),itBJet->p4())>1.2 && BoostedUtils::DeltaR(itBJet->p4(),ittopJet->p4())>1.2 && MiniAODHelper::GetJetCSV(*itBJet,"pfCombinedInclusiveSecondaryVertexV2BJetTags")>=0){
                                ZprimesABCDCHSSoftDrop.push_back(itBJet->p4()+ittopJet->p4()+itWJet->p4());
                                TprimesABCDCHSSoftDrop.push_back(itBJet->p4()+itWJet->p4());
                                TopsABCDCHSSoftDrop.push_back(*ittopJet);
                                BottomsABCDCHSSoftDrop.push_back(*itBJet);
                                WsABCDCHSSoftDrop.push_back(*itWJet);
                                
                            if(ittopJet->userFloat("ak8PFJetsCHSSoftDropMass")>105.0  && ittopJet->userFloat("ak8PFJetsCHSSoftDropMass")<220.0){
                                ittopJet->setMass(foo.GetRndmSDM(histo_ABCD_QCD_MSD_top_nobtag));
                            }
                            if(itWJet->userFloat("ak8PFJetsCHSSoftDropMass")>70.0  && itWJet->userFloat("ak8PFJetsCHSSoftDropMass")>100.0){
                                itWJet->setMass(foo.GetRndmSDM(histo_ABCD_QCD_MSD_W_nobtag));
                            }
                                ZprimesABCDCHSSoftDropmasscorrnotopbtag.push_back(itBJet->p4()+ittopJet->p4()+itWJet->p4());
                                TprimesABCDCHSSoftDropmasscorrnotopbtag.push_back(itBJet->p4()+itWJet->p4());
                                TopsABCDCHSSoftDropmasscorrnotopbtag.push_back(*ittopJet);
                                BottomsABCDCHSSoftDropmasscorrnotopbtag.push_back(*itBJet);
                                WsABCDCHSSoftDropmasscorrnotopbtag.push_back(*itWJet);
                            
                            if(ittopJet->userFloat("ak8PFJetsCHSSoftDropMass")>105.0  && ittopJet->userFloat("ak8PFJetsCHSSoftDropMass")<220.0){
                                ittopJet->setMass(foo.GetRndmSDM(histo_ABCD_QCD_MSD_top_withbtag));
                            }
                            if(itWJet->userFloat("ak8PFJetsCHSSoftDropMass")>70.0  && itWJet->userFloat("ak8PFJetsCHSSoftDropMass")>100.0){
                                itWJet->setMass(foo.GetRndmSDM(histo_ABCD_QCD_MSD_W_withbtag));
                            }
                                ZprimesABCDCHSSoftDropmasscorrwithtopbtag.push_back(itBJet->p4()+ittopJet->p4()+itWJet->p4());
                                TprimesABCDCHSSoftDropmasscorrwithtopbtag.push_back(itBJet->p4()+itWJet->p4());
                                TopsABCDCHSSoftDropmasscorrwithtopbtag.push_back(*ittopJet);
                                BottomsABCDCHSSoftDropmasscorrwithtopbtag.push_back(*itBJet);
                                WsABCDCHSSoftDropmasscorrwithtopbtag.push_back(*itWJet);                            
                        }
                    }                    
                }
            }
        }
    }
  }

// std::cout<<"bugsearch3"<<std::endl;

/////ALL COMBINATIONS FOR ABCDCHSPruning-METHODE
  if(CHSSoftDrop_top_candidates.size()>0 && CHSPruning_W_candidates.size()>1 && AK4CHS_b_candidates.size()>0){
    for(std::vector<pat::Jet>::iterator ittopJet = CHSSoftDrop_top_candidates.begin() ; ittopJet != CHSSoftDrop_top_candidates.end(); ++ittopJet){
        for(std::vector<pat::Jet>::iterator itWJet = CHSPruning_W_candidates.begin() ; itWJet != CHSPruning_W_candidates.end(); ++itWJet){
            if(BoostedUtils::DeltaR(itWJet->p4(),ittopJet->p4())<0.8){
//                 std::cout<<"ah ah ah, W- and top-jets are the same"<<endl;
            }else{
                if(itWJet->userFloat("NjettinessAK8CHS:tau1")>0 && itWJet->userFloat("NjettinessAK8CHS:tau2")>0 && itWJet->userFloat("NjettinessAK8CHS:tau3")>0 && ittopJet->userFloat("NjettinessAK8CHS:tau1")>0 && ittopJet->userFloat("NjettinessAK8CHS:tau2")>0 && ittopJet->userFloat("NjettinessAK8CHS:tau3")>0){
                    for(std::vector<pat::Jet>::const_iterator itBJet = AK4CHS_b_candidates.begin() ; itBJet != AK4CHS_b_candidates.end(); ++itBJet){
                        if(BoostedUtils::DeltaR(itWJet->p4(),itBJet->p4())>1.2 && BoostedUtils::DeltaR(itBJet->p4(),ittopJet->p4())>1.2 && MiniAODHelper::GetJetCSV(*itBJet,"pfCombinedInclusiveSecondaryVertexV2BJetTags")>=0){
                                ZprimesABCDCHSPruning.push_back(itBJet->p4()+ittopJet->p4()+itWJet->p4());
                                TprimesABCDCHSPruning.push_back(itBJet->p4()+itWJet->p4());
                                TopsABCDCHSPruning.push_back(*ittopJet);
                                BottomsABCDCHSPruning.push_back(*itBJet);
                                WsABCDCHSPruning.push_back(*itWJet);
                                                          
                        }
                    }                    
                }
            }
        }
    }
  }

// std::cout<<"bugsearch3.5"<<std::endl;
/////ALL COMBINATIONS FOR ABCDPUPPISoftDrop-METHODE
  if(PUPPISoftDrop_top_candidates.size()>0 && PUPPISoftDrop_W_candidates.size()>1 && AK4PUPPI_b_candidates.size()>0){
    for(std::vector<pat::Jet>::iterator ittopJet = PUPPISoftDrop_top_candidates.begin() ; ittopJet != PUPPISoftDrop_top_candidates.end(); ++ittopJet){
        for(std::vector<pat::Jet>::iterator itWJet = PUPPISoftDrop_W_candidates.begin() ; itWJet != PUPPISoftDrop_W_candidates.end(); ++itWJet){
            if(BoostedUtils::DeltaR(itWJet->p4(),ittopJet->p4())<0.8){
//                 std::cout<<"ah ah ah, W- and top-jets are the same"<<endl;
            }else{
                if(itWJet->userFloat("NjettinessAK8Puppi:tau1")>0 && itWJet->userFloat("NjettinessAK8Puppi:tau2")>0 && itWJet->userFloat("NjettinessAK8Puppi:tau3")>0 && ittopJet->userFloat("NjettinessAK8Puppi:tau1")>0 && ittopJet->userFloat("NjettinessAK8Puppi:tau2")>0 && ittopJet->userFloat("NjettinessAK8Puppi:tau3")>0){
                    for(std::vector<pat::Jet>::const_iterator itBJet = AK4PUPPI_b_candidates.begin() ; itBJet != AK4PUPPI_b_candidates.end(); ++itBJet){
                        if(BoostedUtils::DeltaR(itWJet->p4(),itBJet->p4())>1.2 && BoostedUtils::DeltaR(itBJet->p4(),ittopJet->p4())>1.2 && MiniAODHelper::GetJetCSV(*itBJet,"pfCombinedInclusiveSecondaryVertexV2BJetTags")>=0){
                                ZprimesABCDPUPPISoftDrop.push_back(itBJet->p4()+ittopJet->p4()+itWJet->p4());
                                TprimesABCDPUPPISoftDrop.push_back(itBJet->p4()+itWJet->p4());
                                TopsABCDPUPPISoftDrop.push_back(*ittopJet);
                                BottomsABCDPUPPISoftDrop.push_back(*itBJet);
                                WsABCDPUPPISoftDrop.push_back(*itWJet);
                                                          
                        }
                    }                    
                }
            }
        }
    }
  }
// std::cout<<"bugsearch4"<<std::endl;
        //std::cout<<"check GenWs7 "<<GenWs.size()<<endl;
  const CSVHelper *csvReweighter=input.csvReweighter;
  
  ////FILL ABCDCHSSoftDrop VARIABLES
  vars.FillVar("N_Zprime_ABCDCHSSoftDrop",ZprimesABCDCHSSoftDrop.size());

  
//Define Correctors
  const JetCorrector* corrector_AK8CHS_L1L2L3 = JetCorrector::getJetCorrector("ak8PFchsL1L2L3", input.iSetup );
  const JetCorrector* corrector_AK8CHS_L2L3 = JetCorrector::getJetCorrector("ak8PFchsL2L3", input.iSetup );
  const JetCorrector* corrector_AK8Puppi_L1L2L3 = JetCorrector::getJetCorrector("ak8PFPuppiL1L2L3", input.iSetup );
  const JetCorrector* corrector_AK8Puppi_L2L3 = JetCorrector::getJetCorrector("ak8PFPuppiL2L3", input.iSetup );
  
  
  for (uint i=0; i<ZprimesABCDCHSSoftDrop.size(); i++){
  //for(math::XYZTLorentzVector::const_iterator ittopJet = AK8_top_candidates.begin() ; ittopJet != AK8_top_candidates.end(); ++ittopJet){
     //int i = 
     vars.FillVars("Zprimes_ABCDCHSSoftDrop_M",i,ZprimesABCDCHSSoftDrop[i].mass());
     vars.FillVars("Zprimes_ABCDCHSSoftDrop_Pt",i,ZprimesABCDCHSSoftDrop[i].pt());
     
     vars.FillVars("Tprimes_ABCDCHSSoftDrop_M",i,TprimesABCDCHSSoftDrop[i].mass());
     vars.FillVars("Tprimes_ABCDCHSSoftDrop_Pt",i,TprimesABCDCHSSoftDrop[i].pt());
     
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_Pt",i,BottomsABCDCHSSoftDrop[i].pt());
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_Eta",i,BottomsABCDCHSSoftDrop[i].eta());
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_Phi",i,BottomsABCDCHSSoftDrop[i].phi());
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_CSV",i,MiniAODHelper::GetJetCSV(BottomsABCDCHSSoftDrop[i],"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
     
//      CSVHelper csvReweighter;
     std::vector<double> ABCDCHSSoftDrop_jetPts;
     std::vector<double> ABCDCHSSoftDrop_jetEtas;
     std::vector<double> ABCDCHSSoftDrop_jetCSVs;
     std::vector<int> ABCDCHSSoftDrop_jetFlavors;
     double ABCDCHSSoftDrop_csvWgtHF, ABCDCHSSoftDrop_csvWgtLF, ABCDCHSSoftDrop_csvWgtCF;
     float ABCDCHSSoftDrop_csvweight = 1.;
     
     

     if(!input.isData){
        ABCDCHSSoftDrop_jetPts.push_back(BottomsABCDCHSSoftDrop[i].pt());
        ABCDCHSSoftDrop_jetEtas.push_back(BottomsABCDCHSSoftDrop[i].eta());
        ABCDCHSSoftDrop_jetCSVs.push_back(MiniAODHelper::GetJetCSV(BottomsABCDCHSSoftDrop[i],"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
        ABCDCHSSoftDrop_jetFlavors.push_back(BottomsABCDCHSSoftDrop[i].hadronFlavour());
        ABCDCHSSoftDrop_csvweight= csvReweighter->getCSVWeight(ABCDCHSSoftDrop_jetPts,ABCDCHSSoftDrop_jetEtas,ABCDCHSSoftDrop_jetCSVs,ABCDCHSSoftDrop_jetFlavors,input.systematic, ABCDCHSSoftDrop_csvWgtHF, ABCDCHSSoftDrop_csvWgtLF, ABCDCHSSoftDrop_csvWgtCF);
     }
     
    bool doSystematics=true;
//     if(doSystematics && input.input.systematic != sysType::JESup && input.input.systematic != sysType::JESdown && input.input.systematic != sysType::JERup && input.input.systematic != sysType::JERdown) {
    
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_WeightCSVnominal",i,ABCDCHSSoftDrop_csvweight);    
    
     if(doSystematics && input.systematic == Systematics::NA) { // only do these for the nominal samples
//      std::cout<<"debug1   "<<ABCDCHSSoftDrop_jetPts.size()<<endl;
     
     
         
     float Bottoms_ABCDCHSSoftDrop_WeightCSVLFup=1.0;    
     float Bottoms_ABCDCHSSoftDrop_WeightCSVLFdown=1.0;    
     float Bottoms_ABCDCHSSoftDrop_WeightCSVHFup=1.0;    
     float Bottoms_ABCDCHSSoftDrop_WeightCSVHFdown=1.0;    
     float Bottoms_ABCDCHSSoftDrop_WeightCSVHFStats1up=1.0;    
     float Bottoms_ABCDCHSSoftDrop_WeightCSVHFStats1down=1.0;    
     float Bottoms_ABCDCHSSoftDrop_WeightCSVLFStats1up=1.0;    
     float Bottoms_ABCDCHSSoftDrop_WeightCSVLFStats1down=1.0;    
     float Bottoms_ABCDCHSSoftDrop_WeightCSVHFStats2up=1.0;    
     float Bottoms_ABCDCHSSoftDrop_WeightCSVHFStats2down=1.0;    
     float Bottoms_ABCDCHSSoftDrop_WeightCSVLFStats2up=1.0;    
     float Bottoms_ABCDCHSSoftDrop_WeightCSVLFStats2down=1.0;    
     float Bottoms_ABCDCHSSoftDrop_WeightCSVCErr1up=1.0;    
     float Bottoms_ABCDCHSSoftDrop_WeightCSVCErr1down=1.0;    
     float Bottoms_ABCDCHSSoftDrop_WeightCSVCErr2up=1.0;    
     float Bottoms_ABCDCHSSoftDrop_WeightCSVCErr2down=1.0;    
        
     if(!input.isData){
         Bottoms_ABCDCHSSoftDrop_WeightCSVLFup=csvReweighter->getCSVWeight(ABCDCHSSoftDrop_jetPts,ABCDCHSSoftDrop_jetEtas,ABCDCHSSoftDrop_jetCSVs,ABCDCHSSoftDrop_jetFlavors,Systematics::CSVLFup, ABCDCHSSoftDrop_csvWgtHF, ABCDCHSSoftDrop_csvWgtLF, ABCDCHSSoftDrop_csvWgtCF)/ABCDCHSSoftDrop_csvweight;
         Bottoms_ABCDCHSSoftDrop_WeightCSVLFdown=csvReweighter->getCSVWeight(ABCDCHSSoftDrop_jetPts,ABCDCHSSoftDrop_jetEtas,ABCDCHSSoftDrop_jetCSVs,ABCDCHSSoftDrop_jetFlavors,Systematics::CSVLFdown, ABCDCHSSoftDrop_csvWgtHF, ABCDCHSSoftDrop_csvWgtLF, ABCDCHSSoftDrop_csvWgtCF)/ABCDCHSSoftDrop_csvweight;
         Bottoms_ABCDCHSSoftDrop_WeightCSVHFup=csvReweighter->getCSVWeight(ABCDCHSSoftDrop_jetPts,ABCDCHSSoftDrop_jetEtas,ABCDCHSSoftDrop_jetCSVs,ABCDCHSSoftDrop_jetFlavors,Systematics::CSVHFup, ABCDCHSSoftDrop_csvWgtHF, ABCDCHSSoftDrop_csvWgtLF, ABCDCHSSoftDrop_csvWgtCF)/ABCDCHSSoftDrop_csvweight;
         Bottoms_ABCDCHSSoftDrop_WeightCSVHFdown=csvReweighter->getCSVWeight(ABCDCHSSoftDrop_jetPts,ABCDCHSSoftDrop_jetEtas,ABCDCHSSoftDrop_jetCSVs,ABCDCHSSoftDrop_jetFlavors,Systematics::CSVHFdown, ABCDCHSSoftDrop_csvWgtHF, ABCDCHSSoftDrop_csvWgtLF, ABCDCHSSoftDrop_csvWgtCF)/ABCDCHSSoftDrop_csvweight;
         Bottoms_ABCDCHSSoftDrop_WeightCSVHFStats1up=csvReweighter->getCSVWeight(ABCDCHSSoftDrop_jetPts,ABCDCHSSoftDrop_jetEtas,ABCDCHSSoftDrop_jetCSVs,ABCDCHSSoftDrop_jetFlavors,Systematics::CSVHFStats1up, ABCDCHSSoftDrop_csvWgtHF, ABCDCHSSoftDrop_csvWgtLF, ABCDCHSSoftDrop_csvWgtCF)/ABCDCHSSoftDrop_csvweight;
         Bottoms_ABCDCHSSoftDrop_WeightCSVHFStats1down=csvReweighter->getCSVWeight(ABCDCHSSoftDrop_jetPts,ABCDCHSSoftDrop_jetEtas,ABCDCHSSoftDrop_jetCSVs,ABCDCHSSoftDrop_jetFlavors,Systematics::CSVHFStats1down, ABCDCHSSoftDrop_csvWgtHF, ABCDCHSSoftDrop_csvWgtLF, ABCDCHSSoftDrop_csvWgtCF)/ABCDCHSSoftDrop_csvweight;
         Bottoms_ABCDCHSSoftDrop_WeightCSVLFStats1up=csvReweighter->getCSVWeight(ABCDCHSSoftDrop_jetPts,ABCDCHSSoftDrop_jetEtas,ABCDCHSSoftDrop_jetCSVs,ABCDCHSSoftDrop_jetFlavors,Systematics::CSVLFStats1up, ABCDCHSSoftDrop_csvWgtHF, ABCDCHSSoftDrop_csvWgtLF, ABCDCHSSoftDrop_csvWgtCF)/ABCDCHSSoftDrop_csvweight;
         Bottoms_ABCDCHSSoftDrop_WeightCSVLFStats1down=csvReweighter->getCSVWeight(ABCDCHSSoftDrop_jetPts,ABCDCHSSoftDrop_jetEtas,ABCDCHSSoftDrop_jetCSVs,ABCDCHSSoftDrop_jetFlavors,Systematics::CSVLFStats1down, ABCDCHSSoftDrop_csvWgtHF, ABCDCHSSoftDrop_csvWgtLF, ABCDCHSSoftDrop_csvWgtCF)/ABCDCHSSoftDrop_csvweight;
         Bottoms_ABCDCHSSoftDrop_WeightCSVHFStats2up=csvReweighter->getCSVWeight(ABCDCHSSoftDrop_jetPts,ABCDCHSSoftDrop_jetEtas,ABCDCHSSoftDrop_jetCSVs,ABCDCHSSoftDrop_jetFlavors,Systematics::CSVHFStats2up, ABCDCHSSoftDrop_csvWgtHF, ABCDCHSSoftDrop_csvWgtLF, ABCDCHSSoftDrop_csvWgtCF)/ABCDCHSSoftDrop_csvweight;
         Bottoms_ABCDCHSSoftDrop_WeightCSVHFStats2down=csvReweighter->getCSVWeight(ABCDCHSSoftDrop_jetPts,ABCDCHSSoftDrop_jetEtas,ABCDCHSSoftDrop_jetCSVs,ABCDCHSSoftDrop_jetFlavors,Systematics::CSVHFStats2down, ABCDCHSSoftDrop_csvWgtHF, ABCDCHSSoftDrop_csvWgtLF, ABCDCHSSoftDrop_csvWgtCF)/ABCDCHSSoftDrop_csvweight;
         Bottoms_ABCDCHSSoftDrop_WeightCSVLFStats2up=csvReweighter->getCSVWeight(ABCDCHSSoftDrop_jetPts,ABCDCHSSoftDrop_jetEtas,ABCDCHSSoftDrop_jetCSVs,ABCDCHSSoftDrop_jetFlavors,Systematics::CSVLFStats2up, ABCDCHSSoftDrop_csvWgtHF, ABCDCHSSoftDrop_csvWgtLF, ABCDCHSSoftDrop_csvWgtCF)/ABCDCHSSoftDrop_csvweight;
         Bottoms_ABCDCHSSoftDrop_WeightCSVLFStats2down=csvReweighter->getCSVWeight(ABCDCHSSoftDrop_jetPts,ABCDCHSSoftDrop_jetEtas,ABCDCHSSoftDrop_jetCSVs,ABCDCHSSoftDrop_jetFlavors,Systematics::CSVLFStats2down, ABCDCHSSoftDrop_csvWgtHF, ABCDCHSSoftDrop_csvWgtLF, ABCDCHSSoftDrop_csvWgtCF)/ABCDCHSSoftDrop_csvweight;
         Bottoms_ABCDCHSSoftDrop_WeightCSVCErr1up=csvReweighter->getCSVWeight(ABCDCHSSoftDrop_jetPts,ABCDCHSSoftDrop_jetEtas,ABCDCHSSoftDrop_jetCSVs,ABCDCHSSoftDrop_jetFlavors,Systematics::CSVCErr1up, ABCDCHSSoftDrop_csvWgtHF, ABCDCHSSoftDrop_csvWgtLF, ABCDCHSSoftDrop_csvWgtCF)/ABCDCHSSoftDrop_csvweight;
         Bottoms_ABCDCHSSoftDrop_WeightCSVCErr1down=csvReweighter->getCSVWeight(ABCDCHSSoftDrop_jetPts,ABCDCHSSoftDrop_jetEtas,ABCDCHSSoftDrop_jetCSVs,ABCDCHSSoftDrop_jetFlavors,Systematics::CSVCErr1down, ABCDCHSSoftDrop_csvWgtHF, ABCDCHSSoftDrop_csvWgtLF, ABCDCHSSoftDrop_csvWgtCF)/ABCDCHSSoftDrop_csvweight;
         Bottoms_ABCDCHSSoftDrop_WeightCSVCErr2up=csvReweighter->getCSVWeight(ABCDCHSSoftDrop_jetPts,ABCDCHSSoftDrop_jetEtas,ABCDCHSSoftDrop_jetCSVs,ABCDCHSSoftDrop_jetFlavors,Systematics::CSVCErr2up, ABCDCHSSoftDrop_csvWgtHF, ABCDCHSSoftDrop_csvWgtLF, ABCDCHSSoftDrop_csvWgtCF)/ABCDCHSSoftDrop_csvweight;
         Bottoms_ABCDCHSSoftDrop_WeightCSVCErr2down=csvReweighter->getCSVWeight(ABCDCHSSoftDrop_jetPts,ABCDCHSSoftDrop_jetEtas,ABCDCHSSoftDrop_jetCSVs,ABCDCHSSoftDrop_jetFlavors,Systematics::CSVCErr2down, ABCDCHSSoftDrop_csvWgtHF, ABCDCHSSoftDrop_csvWgtLF, ABCDCHSSoftDrop_csvWgtCF)/ABCDCHSSoftDrop_csvweight;
     }
         
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_WeightCSVLFup",i,Bottoms_ABCDCHSSoftDrop_WeightCSVLFup);
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_WeightCSVLFdown",i,Bottoms_ABCDCHSSoftDrop_WeightCSVLFdown);
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_WeightCSVHFup",i, Bottoms_ABCDCHSSoftDrop_WeightCSVHFup);
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_WeightCSVHFdown",i, Bottoms_ABCDCHSSoftDrop_WeightCSVHFdown);
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_WeightCSVHFStats1up",i, Bottoms_ABCDCHSSoftDrop_WeightCSVHFStats1up);
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_WeightCSVHFStats1down",i, Bottoms_ABCDCHSSoftDrop_WeightCSVHFStats1down);
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_WeightCSVLFStats1up",i, Bottoms_ABCDCHSSoftDrop_WeightCSVLFStats1up);
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_WeightCSVLFStats1down",i, Bottoms_ABCDCHSSoftDrop_WeightCSVLFStats1down);
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_WeightCSVHFStats2up",i, Bottoms_ABCDCHSSoftDrop_WeightCSVHFStats2up);
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_WeightCSVHFStats2down",i, Bottoms_ABCDCHSSoftDrop_WeightCSVHFStats2down);
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_WeightCSVLFStats2up",i, Bottoms_ABCDCHSSoftDrop_WeightCSVLFStats2up);
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_WeightCSVLFStats2down",i, Bottoms_ABCDCHSSoftDrop_WeightCSVLFStats2down);
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_WeightCSVCErr1up",i, Bottoms_ABCDCHSSoftDrop_WeightCSVCErr1up);
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_WeightCSVCErr1down",i, Bottoms_ABCDCHSSoftDrop_WeightCSVCErr1down);
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_WeightCSVCErr2up",i, Bottoms_ABCDCHSSoftDrop_WeightCSVCErr2up);
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_WeightCSVCErr2down",i, Bottoms_ABCDCHSSoftDrop_WeightCSVCErr2down);
     
    }
//      std::cout<<"debug2   "<<jetPts.size()<<endl;
     

     float corr_AK8CHS_L1L2L3=1.0;
     float corr_AK8CHS_L2L3=1.0;
     pat::Jet WsABCDCHSSoftDrop_temp_AK8CHSSoftDropL1L2L3 = WsABCDCHSSoftDrop[i];
     pat::Jet WsABCDCHSSoftDrop_temp_AK8CHSSoftDropL2L3 = WsABCDCHSSoftDrop[i];
     corr_AK8CHS_L1L2L3=corrector_AK8CHS_L1L2L3->correction(WsABCDCHSSoftDrop_temp_AK8CHSSoftDropL1L2L3, input.iEvent, input.iSetup);
     corr_AK8CHS_L2L3=corrector_AK8CHS_L2L3->correction(WsABCDCHSSoftDrop_temp_AK8CHSSoftDropL2L3, input.iEvent, input.iSetup);
     vars.FillVars("Ws_ABCDCHSSoftDrop_corrL1L2L3",i,corr_AK8CHS_L1L2L3);
     vars.FillVars("Ws_ABCDCHSSoftDrop_corrL2L3",i,corr_AK8CHS_L2L3);

     vars.FillVars("Ws_ABCDCHSSoftDrop_Pt",i,WsABCDCHSSoftDrop[i].pt());
     vars.FillVars("Ws_ABCDCHSSoftDrop_Eta",i,WsABCDCHSSoftDrop[i].eta());
     vars.FillVars("Ws_ABCDCHSSoftDrop_Phi",i,WsABCDCHSSoftDrop[i].phi());
     vars.FillVars("Ws_ABCDCHSSoftDrop_MSD",i,WsABCDCHSSoftDrop[i].userFloat("ak8PFJetsCHSSoftDropMass"));
     vars.FillVars("Ws_ABCDCHSSoftDrop_t21",i,WsABCDCHSSoftDrop[i].userFloat("NjettinessAK8CHS:tau2")/WsABCDCHSSoftDrop[i].userFloat("NjettinessAK8CHS:tau1"));

     pat::Jet TopsABCDCHSSoftDrop_temp_AK8CHSSoftDropL1L2L3 = TopsABCDCHSSoftDrop[i];
     pat::Jet TopsABCDCHSSoftDrop_temp_AK8CHSSoftDropL2L3 = TopsABCDCHSSoftDrop[i];
     corr_AK8CHS_L1L2L3=corrector_AK8CHS_L1L2L3->correction(TopsABCDCHSSoftDrop_temp_AK8CHSSoftDropL1L2L3, input.iEvent, input.iSetup);
     corr_AK8CHS_L2L3=corrector_AK8CHS_L2L3->correction(TopsABCDCHSSoftDrop_temp_AK8CHSSoftDropL2L3, input.iEvent, input.iSetup);
     vars.FillVars("Tops_ABCDCHSSoftDrop_corrL1L2L3",i,corr_AK8CHS_L1L2L3);
     vars.FillVars("Tops_ABCDCHSSoftDrop_corrL2L3",i,corr_AK8CHS_L2L3);
     
     vars.FillVars("Tops_ABCDCHSSoftDrop_Pt",i,TopsABCDCHSSoftDrop[i].pt());
     vars.FillVars("Tops_ABCDCHSSoftDrop_Eta",i,TopsABCDCHSSoftDrop[i].eta());
     vars.FillVars("Tops_ABCDCHSSoftDrop_Phi",i,TopsABCDCHSSoftDrop[i].phi());
     vars.FillVars("Tops_ABCDCHSSoftDrop_MSD",i,TopsABCDCHSSoftDrop[i].userFloat("ak8PFJetsCHSSoftDropMass"));
     vars.FillVars("Tops_ABCDCHSSoftDrop_t32",i,TopsABCDCHSSoftDrop[i].userFloat("NjettinessAK8CHS:tau3")/TopsABCDCHSSoftDrop[i].userFloat("NjettinessAK8CHS:tau2"));
        //std::cout<<"check GenWs8 "<<GenWs.size()<<endl;
     
//std::cout<<"bugsearch6"<<std::endl;
     
     int realW=0;
     int nmatchedaughters_WCHSSoftDrop=0;
//std::cout<<"bugsearch6.0  "<<((input.zprimetotprimeallhad.IsFilled()) && (!input.isData))<<std::endl;
        //std::cout<<"check GenWs9 "<<GenWs.size()<<endl;
//         if (GenWs != NULL){ std::cout<<"check GenWs10 "<<GenWs.size()<<endl;}
        
     if((input.zprimetotprimeallhad.IsFilled()) && (!input.isData) && (GenWs.size() > 0)){
//std::cout<<"bugsearch6.1  "<<GenWs.size()<<std::endl;
        for(uint j=0; j<GenWs.size();j++){
//std::cout<<"bugsearch6.2"<<std::endl;
            if (BoostedUtils::DeltaR(WsABCDCHSSoftDrop[i].p4(),GenWs[j].p4())<0.8){
//std::cout<<"bugsearch6.3"<<std::endl;
                realW=1;
            for(uint k=0;k<GenWs_decayproducts.size();k++){
//std::cout<<"bugsearch6.4"<<std::endl;
                if (BoostedUtils::DeltaR(WsABCDCHSSoftDrop[i].p4(),GenWs_decayproducts[k].p4())<0.8){
                    nmatchedaughters_WCHSSoftDrop++;
//std::cout<<"bugsearch6.5"<<std::endl;
                }
            }
            }
        }
     }
//std::cout<<"bugsearch6.6"<<std::endl;
          
     int realtop=0;
     int nmatchedaughters_topCHSSoftDrop=0;
//std::cout<<"bugsearch6.6.0"<<std::endl;
     if((input.zprimetotprimeallhad.IsFilled()) && (!input.isData) && (GenTops.size() > 0)){
//std::cout<<"bugsearch6.6.1"<<std::endl;
        for(uint j=0; j<GenTops.size();j++){
            if (BoostedUtils::DeltaR(TopsABCDCHSSoftDrop[i].p4(),GenTops[j].p4())<0.8){
//std::cout<<"bugsearch6.6.2"<<std::endl;
                realtop=1;
//std::cout<<"bugsearch6.6.2.1"<<std::endl;
            for(uint k=0;k<GenTops_decayproducts.size();k++){

                if (BoostedUtils::DeltaR(TopsABCDCHSSoftDrop[i].p4(),GenTops_decayproducts[k].p4())<0.8){
//std::cout<<"bugsearch6.6.3"<<std::endl;
                    nmatchedaughters_topCHSSoftDrop++;
                }
            } 
            }
        }
     }
//std::cout<<"bugsearch6.6.4"<<std::endl;
     vars.FillVars("Ws_ABCDCHSSoftDrop_real",i,realW);
     vars.FillVars("Ws_ABCDCHSSoftDrop_matcheddecays",i,nmatchedaughters_WCHSSoftDrop);
     vars.FillVars("Tops_ABCDCHSSoftDrop_real",i,realtop);
     vars.FillVars("Tops_ABCDCHSSoftDrop_matcheddecays",i,nmatchedaughters_topCHSSoftDrop);
//std::cout<<"bugsearch6.7"<<std::endl;
//      std::cout<<"debucg1"<<endl;
     std::vector<double> ABCDCHSSoftDrop_subjetPts;
     std::vector<double> ABCDCHSSoftDrop_subjetEtas;
     std::vector<double> ABCDCHSSoftDrop_subjetCSVs;
     std::vector<int> ABCDCHSSoftDrop_subjetFlavors;
     double subjet_ABCDCHSSoftDrop_csvWgtHF, subjet_ABCDCHSSoftDrop_csvWgtLF, subjet_ABCDCHSSoftDrop_csvWgtCF;
     float subjet_ABCDCHSSoftDrop_csvweight = 1.;
     

     
     double max_subjet_csv_v2=-10;
     auto const & names = TopsABCDCHSSoftDrop[i].subjets("SoftDrop");
     for( auto const & itsubJet : names ){
        if (itsubJet->pt()<20.0 || abs(itsubJet->eta())>2.4) continue;
        if(!input.isData){
            ABCDCHSSoftDrop_subjetPts.push_back(itsubJet->pt());
            ABCDCHSSoftDrop_subjetEtas.push_back(itsubJet->eta());
            ABCDCHSSoftDrop_subjetCSVs.push_back(MiniAODHelper::GetJetCSV(*itsubJet,"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
            ABCDCHSSoftDrop_subjetFlavors.push_back(itsubJet->hadronFlavour());
        }      
        if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>max_subjet_csv_v2){
            max_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
        };
     };
//std::cout<<"bugsearch6.8"<<std::endl;
//      std::cout<<"debug2.2"<<endl;
     vars.FillVars("Tops_ABCDCHSSoftDrop_maxsubjetCSVv2",i,max_subjet_csv_v2);
//      std::cout<<"max_subjet_csv_v2  "<<max_subjet_csv_v2<<endl;
     if(!input.isData){
         subjet_ABCDCHSSoftDrop_csvweight= csvReweighter->getCSVWeight(ABCDCHSSoftDrop_subjetPts,ABCDCHSSoftDrop_subjetEtas,ABCDCHSSoftDrop_subjetCSVs,ABCDCHSSoftDrop_subjetFlavors,input.systematic, subjet_ABCDCHSSoftDrop_csvWgtHF, subjet_ABCDCHSSoftDrop_csvWgtLF, subjet_ABCDCHSSoftDrop_csvWgtCF);
     }
 //     if(doSystematics && input.input.systematic != sysType::JESup && input.input.systematic != sysType::JESdown && input.input.systematic != sysType::JERup && input.input.systematic != sysType::JERdown) {

     vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVnominal",i,subjet_ABCDCHSSoftDrop_csvweight);
     
     if(doSystematics && input.systematic == Systematics::NA) { // only do these for the nominal samples
//      std::cout<<"debug3   "<<ABCDCHSSoftDrop_subjetPts.size()<<endl;
         
            if (input.isData){
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVLFup",i,1.0);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVLFdown",i,1.0);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVHFup",i, 1.0);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVHFdown",i, 1.0);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVHFStats1up",i, 1.0);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVHFStats1down",i, 1.0);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVLFStats1up",i, 1.0);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVLFStats1down",i, 1.0);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVHFStats2up",i, 1.0);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVHFStats2down",i, 1.0);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVLFStats2up",i, 1.0);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVLFStats2down",i, 1.0);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVCErr1up",i, 1.0);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVCErr1down",i, 1.0);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVCErr2up",i, 1.0);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVCErr2down",i, 1.0);  
                
            }else{
          
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVLFup",i,csvReweighter->getCSVWeight(ABCDCHSSoftDrop_subjetPts,ABCDCHSSoftDrop_subjetEtas,ABCDCHSSoftDrop_subjetCSVs,ABCDCHSSoftDrop_subjetFlavors,Systematics::CSVLFup, subjet_ABCDCHSSoftDrop_csvWgtHF, subjet_ABCDCHSSoftDrop_csvWgtLF, subjet_ABCDCHSSoftDrop_csvWgtCF)/subjet_ABCDCHSSoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVLFdown",i,csvReweighter->getCSVWeight(ABCDCHSSoftDrop_subjetPts,ABCDCHSSoftDrop_subjetEtas,ABCDCHSSoftDrop_subjetCSVs,ABCDCHSSoftDrop_subjetFlavors,Systematics::CSVLFdown, subjet_ABCDCHSSoftDrop_csvWgtHF, subjet_ABCDCHSSoftDrop_csvWgtLF, subjet_ABCDCHSSoftDrop_csvWgtCF)/subjet_ABCDCHSSoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVHFup",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_subjetPts,ABCDCHSSoftDrop_subjetEtas,ABCDCHSSoftDrop_subjetCSVs,ABCDCHSSoftDrop_subjetFlavors,Systematics::CSVHFup, subjet_ABCDCHSSoftDrop_csvWgtHF, subjet_ABCDCHSSoftDrop_csvWgtLF, subjet_ABCDCHSSoftDrop_csvWgtCF)/subjet_ABCDCHSSoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVHFdown",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_subjetPts,ABCDCHSSoftDrop_subjetEtas,ABCDCHSSoftDrop_subjetCSVs,ABCDCHSSoftDrop_subjetFlavors,Systematics::CSVHFdown, subjet_ABCDCHSSoftDrop_csvWgtHF, subjet_ABCDCHSSoftDrop_csvWgtLF, subjet_ABCDCHSSoftDrop_csvWgtCF)/subjet_ABCDCHSSoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVHFStats1up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_subjetPts,ABCDCHSSoftDrop_subjetEtas,ABCDCHSSoftDrop_subjetCSVs,ABCDCHSSoftDrop_subjetFlavors,Systematics::CSVHFStats1up, subjet_ABCDCHSSoftDrop_csvWgtHF, subjet_ABCDCHSSoftDrop_csvWgtLF, subjet_ABCDCHSSoftDrop_csvWgtCF)/subjet_ABCDCHSSoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVHFStats1down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_subjetPts,ABCDCHSSoftDrop_subjetEtas,ABCDCHSSoftDrop_subjetCSVs,ABCDCHSSoftDrop_subjetFlavors,Systematics::CSVHFStats1down, subjet_ABCDCHSSoftDrop_csvWgtHF, subjet_ABCDCHSSoftDrop_csvWgtLF, subjet_ABCDCHSSoftDrop_csvWgtCF)/subjet_ABCDCHSSoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVLFStats1up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_subjetPts,ABCDCHSSoftDrop_subjetEtas,ABCDCHSSoftDrop_subjetCSVs,ABCDCHSSoftDrop_subjetFlavors,Systematics::CSVLFStats1up, subjet_ABCDCHSSoftDrop_csvWgtHF, subjet_ABCDCHSSoftDrop_csvWgtLF, subjet_ABCDCHSSoftDrop_csvWgtCF)/subjet_ABCDCHSSoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVLFStats1down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_subjetPts,ABCDCHSSoftDrop_subjetEtas,ABCDCHSSoftDrop_subjetCSVs,ABCDCHSSoftDrop_subjetFlavors,Systematics::CSVLFStats1down, subjet_ABCDCHSSoftDrop_csvWgtHF, subjet_ABCDCHSSoftDrop_csvWgtLF, subjet_ABCDCHSSoftDrop_csvWgtCF)/subjet_ABCDCHSSoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVHFStats2up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_subjetPts,ABCDCHSSoftDrop_subjetEtas,ABCDCHSSoftDrop_subjetCSVs,ABCDCHSSoftDrop_subjetFlavors,Systematics::CSVHFStats2up, subjet_ABCDCHSSoftDrop_csvWgtHF, subjet_ABCDCHSSoftDrop_csvWgtLF, subjet_ABCDCHSSoftDrop_csvWgtCF)/subjet_ABCDCHSSoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVHFStats2down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_subjetPts,ABCDCHSSoftDrop_subjetEtas,ABCDCHSSoftDrop_subjetCSVs,ABCDCHSSoftDrop_subjetFlavors,Systematics::CSVHFStats2down, subjet_ABCDCHSSoftDrop_csvWgtHF, subjet_ABCDCHSSoftDrop_csvWgtLF, subjet_ABCDCHSSoftDrop_csvWgtCF)/subjet_ABCDCHSSoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVLFStats2up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_subjetPts,ABCDCHSSoftDrop_subjetEtas,ABCDCHSSoftDrop_subjetCSVs,ABCDCHSSoftDrop_subjetFlavors,Systematics::CSVLFStats2up, subjet_ABCDCHSSoftDrop_csvWgtHF, subjet_ABCDCHSSoftDrop_csvWgtLF, subjet_ABCDCHSSoftDrop_csvWgtCF)/subjet_ABCDCHSSoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVLFStats2down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_subjetPts,ABCDCHSSoftDrop_subjetEtas,ABCDCHSSoftDrop_subjetCSVs,ABCDCHSSoftDrop_subjetFlavors,Systematics::CSVLFStats2down, subjet_ABCDCHSSoftDrop_csvWgtHF, subjet_ABCDCHSSoftDrop_csvWgtLF, subjet_ABCDCHSSoftDrop_csvWgtCF)/subjet_ABCDCHSSoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVCErr1up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_subjetPts,ABCDCHSSoftDrop_subjetEtas,ABCDCHSSoftDrop_subjetCSVs,ABCDCHSSoftDrop_subjetFlavors,Systematics::CSVCErr1up, subjet_ABCDCHSSoftDrop_csvWgtHF, subjet_ABCDCHSSoftDrop_csvWgtLF, subjet_ABCDCHSSoftDrop_csvWgtCF)/subjet_ABCDCHSSoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVCErr1down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_subjetPts,ABCDCHSSoftDrop_subjetEtas,ABCDCHSSoftDrop_subjetCSVs,ABCDCHSSoftDrop_subjetFlavors,Systematics::CSVCErr1down, subjet_ABCDCHSSoftDrop_csvWgtHF, subjet_ABCDCHSSoftDrop_csvWgtLF, subjet_ABCDCHSSoftDrop_csvWgtCF)/subjet_ABCDCHSSoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVCErr2up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_subjetPts,ABCDCHSSoftDrop_subjetEtas,ABCDCHSSoftDrop_subjetCSVs,ABCDCHSSoftDrop_subjetFlavors,Systematics::CSVCErr2up, subjet_ABCDCHSSoftDrop_csvWgtHF, subjet_ABCDCHSSoftDrop_csvWgtLF, subjet_ABCDCHSSoftDrop_csvWgtCF)/subjet_ABCDCHSSoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSSoftDrop_WeightCSVCErr2down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_subjetPts,ABCDCHSSoftDrop_subjetEtas,ABCDCHSSoftDrop_subjetCSVs,ABCDCHSSoftDrop_subjetFlavors,Systematics::CSVCErr2down, subjet_ABCDCHSSoftDrop_csvWgtHF, subjet_ABCDCHSSoftDrop_csvWgtLF, subjet_ABCDCHSSoftDrop_csvWgtCF)/subjet_ABCDCHSSoftDrop_csvweight);  
//      std::cout<<"debug4"<<endl;
            }
    }     
     
  }
//std::cout<<"bugsearch7"<<std::endl;

  
  ////FILL ABCDCHSSoftDrop VARIABLES
  vars.FillVar("N_Zprimes_ABCDCHSSoftDropmasscorrnotopbtag",ZprimesABCDCHSSoftDropmasscorrnotopbtag.size());

  for (uint i=0; i<ZprimesABCDCHSSoftDropmasscorrnotopbtag.size(); i++){
  //for(math::XYZTLorentzVector::const_iterator ittopJet = AK8_top_candidates.begin() ; ittopJet != AK8_top_candidates.end(); ++ittopJet){
     //int i = 
     vars.FillVars("Zprimes_ABCDCHSSoftDrop_masscorrnotopbtag_M",i,ZprimesABCDCHSSoftDropmasscorrnotopbtag[i].mass());
     vars.FillVars("Zprimes_ABCDCHSSoftDrop_masscorrnotopbtag_Pt",i,ZprimesABCDCHSSoftDropmasscorrnotopbtag[i].pt());
     
     vars.FillVars("Tprimes_ABCDCHSSoftDrop_masscorrnotopbtag_M",i,TprimesABCDCHSSoftDropmasscorrnotopbtag[i].mass());
     vars.FillVars("Tprimes_ABCDCHSSoftDrop_masscorrnotopbtag_Pt",i,TprimesABCDCHSSoftDropmasscorrnotopbtag[i].pt());
     
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_Pt",i,BottomsABCDCHSSoftDropmasscorrnotopbtag[i].pt());
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_Eta",i,BottomsABCDCHSSoftDropmasscorrnotopbtag[i].eta());
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_Phi",i,BottomsABCDCHSSoftDropmasscorrnotopbtag[i].phi());
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_CSV",i,MiniAODHelper::GetJetCSV(BottomsABCDCHSSoftDropmasscorrnotopbtag[i],"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
     
//      CSVHelper csvReweighter=input.csvReweighter;
     std::vector<double> ABCDCHSSoftDrop_masscorrnotopbtag_jetPts;
     std::vector<double> ABCDCHSSoftDrop_masscorrnotopbtag_jetEtas;
     std::vector<double> ABCDCHSSoftDrop_masscorrnotopbtag_jetCSVs;
     std::vector<int> ABCDCHSSoftDrop_masscorrnotopbtag_jetFlavors;
     double ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF;
     float ABCDCHSSoftDrop_csvweight = 1.;
     
     if(!input.isData){
        ABCDCHSSoftDrop_masscorrnotopbtag_jetPts.push_back(BottomsABCDCHSSoftDropmasscorrnotopbtag[i].pt());
        ABCDCHSSoftDrop_masscorrnotopbtag_jetEtas.push_back(BottomsABCDCHSSoftDropmasscorrnotopbtag[i].eta());
        ABCDCHSSoftDrop_masscorrnotopbtag_jetCSVs.push_back(MiniAODHelper::GetJetCSV(BottomsABCDCHSSoftDropmasscorrnotopbtag[i],"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
        ABCDCHSSoftDrop_masscorrnotopbtag_jetFlavors.push_back(BottomsABCDCHSSoftDropmasscorrnotopbtag[i].hadronFlavour());
     
        ABCDCHSSoftDrop_csvweight= csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_jetPts,ABCDCHSSoftDrop_masscorrnotopbtag_jetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_jetFlavors,input.systematic, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF,   ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF);
     }
    bool doSystematics=true;
//     if(doSystematics && input.input.systematic != sysType::JESup && input.input.systematic != sysType::JESdown && input.input.systematic != sysType::JERup && input.input.systematic != sysType::JERdown) {
    vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVnominal",i,ABCDCHSSoftDrop_csvweight);
     
    
    if(doSystematics && input.systematic == Systematics::NA) { // only do these for the nominal samples

        if(input.isData){         
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFup",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFdown",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFup",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFdown",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFStats1up",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFStats1down",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFStats1up",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFStats1down",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFStats2up",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFStats2down",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFStats2up",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFStats2down",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVCErr1up",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVCErr1down",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVCErr2up",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVCErr2down",i, 1.0);  
        }else{
            
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFup",i,csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_jetPts,ABCDCHSSoftDrop_masscorrnotopbtag_jetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_jetFlavors,Systematics::CSVLFup, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/ABCDCHSSoftDrop_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFdown",i,csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_jetPts,ABCDCHSSoftDrop_masscorrnotopbtag_jetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_jetFlavors,Systematics::CSVLFdown, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/ABCDCHSSoftDrop_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFup",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_jetPts,ABCDCHSSoftDrop_masscorrnotopbtag_jetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_jetFlavors,Systematics::CSVHFup, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/ABCDCHSSoftDrop_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFdown",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_jetPts,ABCDCHSSoftDrop_masscorrnotopbtag_jetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_jetFlavors,Systematics::CSVHFdown, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/ABCDCHSSoftDrop_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFStats1up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_jetPts,ABCDCHSSoftDrop_masscorrnotopbtag_jetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_jetFlavors,Systematics::CSVHFStats1up, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/ABCDCHSSoftDrop_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFStats1down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_jetPts,ABCDCHSSoftDrop_masscorrnotopbtag_jetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_jetFlavors,Systematics::CSVHFStats1down, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/ABCDCHSSoftDrop_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFStats1up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_jetPts,ABCDCHSSoftDrop_masscorrnotopbtag_jetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_jetFlavors,Systematics::CSVLFStats1up, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/ABCDCHSSoftDrop_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFStats1down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_jetPts,ABCDCHSSoftDrop_masscorrnotopbtag_jetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_jetFlavors,Systematics::CSVLFStats1down, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/ABCDCHSSoftDrop_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFStats2up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_jetPts,ABCDCHSSoftDrop_masscorrnotopbtag_jetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_jetFlavors,Systematics::CSVHFStats2up, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/ABCDCHSSoftDrop_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFStats2down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_jetPts,ABCDCHSSoftDrop_masscorrnotopbtag_jetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_jetFlavors,Systematics::CSVHFStats2down, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/ABCDCHSSoftDrop_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFStats2up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_jetPts,ABCDCHSSoftDrop_masscorrnotopbtag_jetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_jetFlavors,Systematics::CSVLFStats2up, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/ABCDCHSSoftDrop_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFStats2down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_jetPts,ABCDCHSSoftDrop_masscorrnotopbtag_jetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_jetFlavors,Systematics::CSVLFStats2down, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/ABCDCHSSoftDrop_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVCErr1up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_jetPts,ABCDCHSSoftDrop_masscorrnotopbtag_jetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_jetFlavors,Systematics::CSVCErr1up, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/ABCDCHSSoftDrop_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVCErr1down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_jetPts,ABCDCHSSoftDrop_masscorrnotopbtag_jetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_jetFlavors,Systematics::CSVCErr1down, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/ABCDCHSSoftDrop_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVCErr2up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_jetPts,ABCDCHSSoftDrop_masscorrnotopbtag_jetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_jetFlavors,Systematics::CSVCErr2up, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/ABCDCHSSoftDrop_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVCErr2down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_jetPts,ABCDCHSSoftDrop_masscorrnotopbtag_jetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_jetFlavors,Systematics::CSVCErr2down, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/ABCDCHSSoftDrop_csvweight);  
            
        }
    }
     
     vars.FillVars("Ws_ABCDCHSSoftDrop_masscorrnotopbtag_Pt",i,WsABCDCHSSoftDropmasscorrnotopbtag[i].pt());
     vars.FillVars("Ws_ABCDCHSSoftDrop_masscorrnotopbtag_Eta",i,WsABCDCHSSoftDropmasscorrnotopbtag[i].eta());
     vars.FillVars("Ws_ABCDCHSSoftDrop_masscorrnotopbtag_Phi",i,WsABCDCHSSoftDropmasscorrnotopbtag[i].phi());
     vars.FillVars("Ws_ABCDCHSSoftDrop_masscorrnotopbtag_MSD",i,WsABCDCHSSoftDropmasscorrnotopbtag[i].userFloat("ak8PFJetsCHSSoftDropMass"));
     vars.FillVars("Ws_ABCDCHSSoftDrop_masscorrnotopbtag_t21",i,WsABCDCHSSoftDropmasscorrnotopbtag[i].userFloat("NjettinessAK8CHS:tau2")/WsABCDCHSSoftDropmasscorrnotopbtag[i].userFloat("NjettinessAK8CHS:tau1"));
     
     vars.FillVars("Tops_ABCDCHSSoftDrop_masscorrnotopbtag_Pt",i,TopsABCDCHSSoftDropmasscorrnotopbtag[i].pt());
     vars.FillVars("Tops_ABCDCHSSoftDrop_masscorrnotopbtag_Eta",i,TopsABCDCHSSoftDropmasscorrnotopbtag[i].eta());
     vars.FillVars("Tops_ABCDCHSSoftDrop_masscorrnotopbtag_Phi",i,TopsABCDCHSSoftDropmasscorrnotopbtag[i].phi());
     vars.FillVars("Tops_ABCDCHSSoftDrop_masscorrnotopbtag_MSD",i,TopsABCDCHSSoftDropmasscorrnotopbtag[i].userFloat("ak8PFJetsCHSSoftDropMass"));
     vars.FillVars("Tops_ABCDCHSSoftDrop_masscorrnotopbtag_t32",i,TopsABCDCHSSoftDropmasscorrnotopbtag[i].userFloat("NjettinessAK8CHS:tau3")/TopsABCDCHSSoftDropmasscorrnotopbtag[i].userFloat("NjettinessAK8CHS:tau2"));

     
     int realW_CHSSoftDropmasscorrnotopbtag=0;
     int nmatchedaughters_WCHSSoftDropmasscorrnotopbtag=0;
     if(input.zprimetotprimeallhad.IsFilled() && !input.isData && GenWs.size()>0){
        for(uint j=0; j<GenWs.size();j++){
            if (BoostedUtils::DeltaR(WsABCDCHSSoftDropmasscorrnotopbtag[i].p4(),GenWs[j].p4())<0.8){
                realW_CHSSoftDropmasscorrnotopbtag=1;
            for(uint k=0;k<GenWs_decayproducts.size();k++){
                if (BoostedUtils::DeltaR(WsABCDCHSSoftDropmasscorrnotopbtag[i].p4(),GenWs_decayproducts[k].p4())<0.8){
                    nmatchedaughters_WCHSSoftDropmasscorrnotopbtag++;
                }
            } 
            }
        }
     }

          
     int realtop_CHSSoftDropmasscorrnotopbtag=0;
     int nmatchedaughters_topCHSSoftDropmasscorrnotopbtag=0;
     if(input.zprimetotprimeallhad.IsFilled() && !input.isData && GenTops.size()>0){
        for(uint j=0; j<GenTops.size();j++){
            if (BoostedUtils::DeltaR(TopsABCDCHSSoftDropmasscorrnotopbtag[i].p4(),GenTops[j].p4())<0.8){
                realtop_CHSSoftDropmasscorrnotopbtag=1;
            for(uint k=0;k<GenTops[j].numberOfDaughters();k++){
                if (BoostedUtils::DeltaR(TopsABCDCHSSoftDropmasscorrnotopbtag[i].p4(),GenTops_decayproducts[k].p4())<0.8){
                    nmatchedaughters_topCHSSoftDropmasscorrnotopbtag++;
                }
            } 
            }
        }
     }
     vars.FillVars("Ws_ABCDCHSSoftDrop_masscorrnotopbtag_real",i,realW_CHSSoftDropmasscorrnotopbtag);
     vars.FillVars("Ws_ABCDCHSSoftDrop_masscorrnotopbtag_matcheddecays",i,nmatchedaughters_WCHSSoftDropmasscorrnotopbtag);
     vars.FillVars("Tops_ABCDCHSSoftDrop_masscorrnotopbtag_real",i,realtop_CHSSoftDropmasscorrnotopbtag);     
     vars.FillVars("Tops_ABCDCHSSoftDrop_masscorrnotopbtag_matcheddecays",i,nmatchedaughters_topCHSSoftDropmasscorrnotopbtag);
     

     
     std::vector<double> ABCDCHSSoftDrop_masscorrnotopbtag_subjetPts;
     std::vector<double> ABCDCHSSoftDrop_masscorrnotopbtag_subjetEtas;
     std::vector<double> ABCDCHSSoftDrop_masscorrnotopbtag_subjetCSVs;
     std::vector<int> ABCDCHSSoftDrop_masscorrnotopbtag_subjetFlavors;
     double subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF;
     float subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvweight = 1.;
     

     
     double max_subjet_csv_v2=-10;
     auto const & names = TopsABCDCHSSoftDropmasscorrnotopbtag[i].subjets("SoftDrop");
     for( auto const & itsubJet : names ){
        if (itsubJet->pt()<20.0 || abs(itsubJet->eta())>2.4) continue;
        if(!input.isData){
            ABCDCHSSoftDrop_masscorrnotopbtag_subjetPts.push_back(itsubJet->pt());
            ABCDCHSSoftDrop_masscorrnotopbtag_subjetEtas.push_back(itsubJet->eta());
            ABCDCHSSoftDrop_masscorrnotopbtag_subjetCSVs.push_back(MiniAODHelper::GetJetCSV(*itsubJet,"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
            ABCDCHSSoftDrop_masscorrnotopbtag_subjetFlavors.push_back(itsubJet->hadronFlavour());
        }
        if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>max_subjet_csv_v2){
            max_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
        };
     };
     
     
     vars.FillVars("Tops_ABCDCHSSoftDrop_masscorrnotopbtag_maxsubjetCSVv2",i,max_subjet_csv_v2);
//      std::cout<<"max_subjet_csv_v2  "<<max_subjet_csv_v2<<endl;
     if(!input.isData){
        subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvweight= csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_subjetPts,ABCDCHSSoftDrop_masscorrnotopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_subjetFlavors,input.systematic, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF);
     }
//     bool doSystematics=true;
//     if(doSystematics && input.input.systematic != sysType::JESup && input.input.systematic != sysType::JESdown && input.input.systematic != sysType::JERup && input.input.systematic != sysType::JERdown) {
     vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVnominal",i,subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvweight);

     if(doSystematics && input.systematic == Systematics::NA) { // only do these for the nominal samples
     
     if(!input.isData){
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFup",i,csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_subjetPts,ABCDCHSSoftDrop_masscorrnotopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_subjetFlavors,Systematics::CSVLFup, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvweight);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFdown",i,csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_subjetPts,ABCDCHSSoftDrop_masscorrnotopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_subjetFlavors,Systematics::CSVLFdown, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvweight);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFup",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_subjetPts,ABCDCHSSoftDrop_masscorrnotopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_subjetFlavors,Systematics::CSVHFup, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvweight);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFdown",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_subjetPts,ABCDCHSSoftDrop_masscorrnotopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_subjetFlavors,Systematics::CSVHFdown, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvweight);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFStats1up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_subjetPts,ABCDCHSSoftDrop_masscorrnotopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_subjetFlavors,Systematics::CSVHFStats1up, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvweight);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFStats1down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_subjetPts,ABCDCHSSoftDrop_masscorrnotopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_subjetFlavors,Systematics::CSVHFStats1down, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvweight);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFStats1up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_subjetPts,ABCDCHSSoftDrop_masscorrnotopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_subjetFlavors,Systematics::CSVLFStats1up, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvweight);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFStats1down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_subjetPts,ABCDCHSSoftDrop_masscorrnotopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_subjetFlavors,Systematics::CSVLFStats1down, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvweight);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFStats2up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_subjetPts,ABCDCHSSoftDrop_masscorrnotopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_subjetFlavors,Systematics::CSVHFStats2up, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvweight);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFStats2down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_subjetPts,ABCDCHSSoftDrop_masscorrnotopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_subjetFlavors,Systematics::CSVHFStats2down, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvweight);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFStats2up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_subjetPts,ABCDCHSSoftDrop_masscorrnotopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_subjetFlavors,Systematics::CSVLFStats2up, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvweight);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFStats2down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_subjetPts,ABCDCHSSoftDrop_masscorrnotopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_subjetFlavors,Systematics::CSVLFStats2down, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvweight);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVCErr1up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_subjetPts,ABCDCHSSoftDrop_masscorrnotopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_subjetFlavors,Systematics::CSVCErr1up, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvweight);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVCErr1down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_subjetPts,ABCDCHSSoftDrop_masscorrnotopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_subjetFlavors,Systematics::CSVCErr1down, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvweight);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVCErr2up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_subjetPts,ABCDCHSSoftDrop_masscorrnotopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_subjetFlavors,Systematics::CSVCErr2up, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvweight);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVCErr2down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrnotopbtag_subjetPts,ABCDCHSSoftDrop_masscorrnotopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrnotopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrnotopbtag_subjetFlavors,Systematics::CSVCErr2down, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrnotopbtag_csvweight);  
     }else{
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFup",i, 1.0);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFdown",i, 1.0);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFup",i, 1.0);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFdown",i, 1.0);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFStats1up",i, 1.0);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFStats1down",i, 1.0);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFStats1up",i, 1.0);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFStats1down",i, 1.0);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFStats2up",i, 1.0);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVHFStats2down",i, 1.0);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFStats2up",i, 1.0);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVLFStats2down",i, 1.0);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVCErr1up",i, 1.0);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVCErr1down",i, 1.0);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVCErr2up",i, 1.0);
        vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrnotopbtag_WeightCSVCErr2down",i, 1.0); 
     }     
     }     
  }

  
  vars.FillVar("N_Zprimes_ABCDCHSSoftDropmasscorrwithtopbtag",ZprimesABCDCHSSoftDropmasscorrwithtopbtag.size());

  for (uint i=0; i<ZprimesABCDCHSSoftDropmasscorrwithtopbtag.size(); i++){
  //for(math::XYZTLorentzVector::const_iterator ittopJet = AK8_top_candidates.begin() ; ittopJet != AK8_top_candidates.end(); ++ittopJet){
     //int i = 
     vars.FillVars("Zprimes_ABCDCHSSoftDrop_masscorrwithtopbtag_M",i,ZprimesABCDCHSSoftDropmasscorrwithtopbtag[i].mass());
     vars.FillVars("Zprimes_ABCDCHSSoftDrop_masscorrwithtopbtag_Pt",i,ZprimesABCDCHSSoftDropmasscorrwithtopbtag[i].pt());
     
     vars.FillVars("Tprimes_ABCDCHSSoftDrop_masscorrwithtopbtag_M",i,TprimesABCDCHSSoftDropmasscorrwithtopbtag[i].mass());
     vars.FillVars("Tprimes_ABCDCHSSoftDrop_masscorrwithtopbtag_Pt",i,TprimesABCDCHSSoftDropmasscorrwithtopbtag[i].pt());
     
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_Pt",i,BottomsABCDCHSSoftDropmasscorrwithtopbtag[i].pt());
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_Eta",i,BottomsABCDCHSSoftDropmasscorrwithtopbtag[i].eta());
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_Phi",i,BottomsABCDCHSSoftDropmasscorrwithtopbtag[i].phi());
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_CSV",i,MiniAODHelper::GetJetCSV(BottomsABCDCHSSoftDropmasscorrwithtopbtag[i],"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
     
//      CSVHelper csvReweighter;
     std::vector<double> ABCDCHSSoftDrop_masscorrwithtopbtag_jetPts;
     std::vector<double> ABCDCHSSoftDrop_masscorrwithtopbtag_jetEtas;
     std::vector<double> ABCDCHSSoftDrop_masscorrwithtopbtag_jetCSVs;
     std::vector<int> ABCDCHSSoftDrop_masscorrwithtopbtag_jetFlavors;
     double ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF;
     float ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight = 1.;
     
     if(!input.isData){
        ABCDCHSSoftDrop_masscorrwithtopbtag_jetPts.push_back(BottomsABCDCHSSoftDropmasscorrwithtopbtag[i].pt());
        ABCDCHSSoftDrop_masscorrwithtopbtag_jetEtas.push_back(BottomsABCDCHSSoftDropmasscorrwithtopbtag[i].eta());
        ABCDCHSSoftDrop_masscorrwithtopbtag_jetCSVs.push_back(MiniAODHelper::GetJetCSV(BottomsABCDCHSSoftDropmasscorrwithtopbtag[i],"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
        ABCDCHSSoftDrop_masscorrwithtopbtag_jetFlavors.push_back(BottomsABCDCHSSoftDropmasscorrwithtopbtag[i].hadronFlavour());
        ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight= csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_jetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_jetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_jetFlavors,input.systematic, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF);
     }
     

    bool doSystematics=true;
//     if(doSystematics && input.input.systematic != sysType::JESup && input.input.systematic != sysType::JESdown && input.input.systematic != sysType::JERup && input.input.systematic != sysType::JERdown) {
     vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVnominal",i,ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
     
     if(doSystematics && input.systematic == Systematics::NA) { // only do these for the nominal samples

        if(input.isData){
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFup",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFdown",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFup",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFdown",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFStats1up",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFStats1down",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFStats1up",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFStats1down",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFStats2up",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFStats2down",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFStats2up",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFStats2down",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVCErr1up",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVCErr1down",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVCErr2up",i, 1.0);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVCErr2down",i, 1.0);
            
        }else{
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFup",i,csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_jetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_jetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_jetFlavors,Systematics::CSVLFup, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFdown",i,csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_jetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_jetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_jetFlavors,Systematics::CSVLFdown, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFup",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_jetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_jetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_jetFlavors,Systematics::CSVHFup, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFdown",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_jetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_jetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_jetFlavors,Systematics::CSVHFdown, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFStats1up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_jetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_jetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_jetFlavors,Systematics::CSVHFStats1up, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFStats1down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_jetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_jetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_jetFlavors,Systematics::CSVHFStats1down, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFStats1up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_jetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_jetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_jetFlavors,Systematics::CSVLFStats1up, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFStats1down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_jetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_jetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_jetFlavors,Systematics::CSVLFStats1down, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFStats2up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_jetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_jetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_jetFlavors,Systematics::CSVHFStats2up, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFStats2down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_jetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_jetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_jetFlavors,Systematics::CSVHFStats2down, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFStats2up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_jetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_jetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_jetFlavors,Systematics::CSVLFStats2up, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFStats2down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_jetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_jetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_jetFlavors,Systematics::CSVLFStats2down, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVCErr1up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_jetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_jetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_jetFlavors,Systematics::CSVCErr1up, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVCErr1down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_jetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_jetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_jetFlavors,Systematics::CSVCErr1down, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVCErr2up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_jetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_jetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_jetFlavors,Systematics::CSVCErr2up, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Bottoms_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVCErr2down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_jetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_jetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_jetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_jetFlavors,Systematics::CSVCErr2down, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);  
        }
    }

     
     
     vars.FillVars("Ws_ABCDCHSSoftDrop_masscorrwithtopbtag_Pt",i,WsABCDCHSSoftDropmasscorrwithtopbtag[i].pt());
     vars.FillVars("Ws_ABCDCHSSoftDrop_masscorrwithtopbtag_Eta",i,WsABCDCHSSoftDropmasscorrwithtopbtag[i].eta());
     vars.FillVars("Ws_ABCDCHSSoftDrop_masscorrwithtopbtag_Phi",i,WsABCDCHSSoftDropmasscorrwithtopbtag[i].phi());
     vars.FillVars("Ws_ABCDCHSSoftDrop_masscorrwithtopbtag_MSD",i,WsABCDCHSSoftDropmasscorrwithtopbtag[i].userFloat("ak8PFJetsCHSSoftDropMass"));     
     vars.FillVars("Tops_ABCDCHSSoftDrop_masscorrwithtopbtag_Pt",i,TopsABCDCHSSoftDropmasscorrwithtopbtag[i].pt());
     vars.FillVars("Tops_ABCDCHSSoftDrop_masscorrwithtopbtag_Eta",i,TopsABCDCHSSoftDropmasscorrwithtopbtag[i].eta());
     vars.FillVars("Tops_ABCDCHSSoftDrop_masscorrwithtopbtag_Phi",i,TopsABCDCHSSoftDropmasscorrwithtopbtag[i].phi());
     vars.FillVars("Tops_ABCDCHSSoftDrop_masscorrwithtopbtag_MSD",i,TopsABCDCHSSoftDropmasscorrwithtopbtag[i].userFloat("ak8PFJetsCHSSoftDropMass"));
     vars.FillVars("Tops_ABCDCHSSoftDrop_masscorrwithtopbtag_t32",i,TopsABCDCHSSoftDropmasscorrwithtopbtag[i].userFloat("NjettinessAK8CHS:tau3")/TopsABCDCHSSoftDropmasscorrwithtopbtag[i].userFloat("NjettinessAK8CHS:tau2"));

    
     int realW_CHSSoftDropmasscorrwithtopbtag=0;
     int nmatchedaughters_WCHSSoftDropmasscorrwithtopbtag=0;
     if(input.zprimetotprimeallhad.IsFilled() && !input.isData && GenWs.size()>0){
        for(uint j=0; j<GenWs.size();j++){
            if (BoostedUtils::DeltaR(WsABCDCHSSoftDropmasscorrwithtopbtag[i].p4(),GenWs[j].p4())<0.8){
                realW_CHSSoftDropmasscorrwithtopbtag=1;
            for(uint k=0;k<GenWs_decayproducts.size();k++){
                if (BoostedUtils::DeltaR(WsABCDCHSSoftDrop[i].p4(),GenWs_decayproducts[k].p4())<0.8){
                    nmatchedaughters_WCHSSoftDropmasscorrwithtopbtag++;
                }
            } 
            }
        }
     }

          
     int realtop_CHSSoftDropmasscorrwithtopbtag=0;
     int nmatchedaughters_topCHSSoftDropmasscorrwithtopbtag=0;
     if(input.zprimetotprimeallhad.IsFilled() && !input.isData && GenTops.size()>0){
        for(uint j=0; j<GenTops.size();j++){
            if (BoostedUtils::DeltaR(TopsABCDCHSSoftDropmasscorrwithtopbtag[i].p4(),GenTops[j].p4())<0.8){
                realtop_CHSSoftDropmasscorrwithtopbtag=1;
           
            for(uint k=0;k<GenTops_decayproducts.size();k++){
                if (BoostedUtils::DeltaR(TopsABCDCHSSoftDropmasscorrwithtopbtag[i].p4(),GenTops_decayproducts[k].p4())<0.8){
                    nmatchedaughters_topCHSSoftDropmasscorrwithtopbtag++;
                }
            } 
            }
        }
     }
     vars.FillVars("Ws_ABCDCHSSoftDrop_masscorrwithtopbtag_real",i,realW_CHSSoftDropmasscorrwithtopbtag);
     vars.FillVars("Ws_ABCDCHSSoftDrop_masscorrwithtopbtag_matcheddecays",i,nmatchedaughters_WCHSSoftDropmasscorrwithtopbtag);
     vars.FillVars("Tops_ABCDCHSSoftDrop_masscorrwithtopbtag_real",i,realtop_CHSSoftDropmasscorrwithtopbtag); 
     vars.FillVars("Tops_ABCDCHSSoftDrop_masscorrwithtopbtag_matcheddecays",i,nmatchedaughters_topCHSSoftDropmasscorrwithtopbtag);
     
     
     
     
     std::vector<double> ABCDCHSSoftDrop_masscorrwithtopbtag_subjetPts;
     std::vector<double> ABCDCHSSoftDrop_masscorrwithtopbtag_subjetEtas;
     std::vector<double> ABCDCHSSoftDrop_masscorrwithtopbtag_subjetCSVs;
     std::vector<int> ABCDCHSSoftDrop_masscorrwithtopbtag_subjetFlavors;
     double subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF;
     float subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight = 1.;
     

     
     double max_subjet_csv_v2=-10;
     auto const & names = TopsABCDCHSSoftDropmasscorrwithtopbtag[i].subjets("SoftDrop");
     for( auto const & itsubJet : names ){
        if (itsubJet->pt()<20.0 || abs(itsubJet->eta())>2.4) continue;
        if(!input.isData){
            ABCDCHSSoftDrop_masscorrwithtopbtag_subjetPts.push_back(itsubJet->pt());
            ABCDCHSSoftDrop_masscorrwithtopbtag_subjetEtas.push_back(itsubJet->eta());
            ABCDCHSSoftDrop_masscorrwithtopbtag_subjetCSVs.push_back(MiniAODHelper::GetJetCSV(*itsubJet,"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
            ABCDCHSSoftDrop_masscorrwithtopbtag_subjetFlavors.push_back(itsubJet->hadronFlavour());
        }      
        if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>max_subjet_csv_v2){
            max_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
        };
     };
     
     vars.FillVars("Tops_ABCDCHSSoftDrop_masscorrwithtopbtag_maxsubjetCSVv2",i,max_subjet_csv_v2);
//      std::cout<<"max_subjet_csv_v2  "<<max_subjet_csv_v2<<endl;
     if(!input.isData){
        subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight= csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_subjetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetFlavors,input.systematic, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF);
     }
//     bool doSystematics=true;
//     if(doSystematics && input.input.systematic != sysType::JESup && input.input.systematic != sysType::JESdown && input.input.systematic != sysType::JERup && input.input.systematic != sysType::JERdown) {
     vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVnominal",i,subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
     
     if(doSystematics && input.systematic == Systematics::NA) { // only do these for the nominal samples
     
         if(input.isData){
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFup",i, 1.0);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFdown",i,1.0);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFup",i, 1.0);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFdown",i, 1.0);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFStats1up",i, 1.0);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFStats1down",i, 1.0);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFStats1up",i, 1.0);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFStats1down",i, 1.0);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFStats2up",i, 1.0);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFStats2down",i, 1.0);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFStats2up",i, 1.0);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFStats2down",i, 1.0);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVCErr1up",i, 1.0);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVCErr1down",i, 1.0);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVCErr2up",i, 1.0);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVCErr2down",i, 1.0);  
             
        }else{
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFup",i,csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_subjetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetFlavors,Systematics::CSVLFup, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFdown",i,csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_subjetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetFlavors,Systematics::CSVLFdown, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFup",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_subjetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetFlavors,Systematics::CSVHFup, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFdown",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_subjetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetFlavors,Systematics::CSVHFdown, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFStats1up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_subjetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetFlavors,Systematics::CSVHFStats1up, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFStats1down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_subjetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetFlavors,Systematics::CSVHFStats1down, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFStats1up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_subjetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetFlavors,Systematics::CSVLFStats1up, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFStats1down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_subjetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetFlavors,Systematics::CSVLFStats1down, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFStats2up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_subjetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetFlavors,Systematics::CSVHFStats2up, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVHFStats2down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_subjetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetFlavors,Systematics::CSVHFStats2down, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFStats2up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_subjetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetFlavors,Systematics::CSVLFStats2up, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVLFStats2down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_subjetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetFlavors,Systematics::CSVLFStats2down, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVCErr1up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_subjetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetFlavors,Systematics::CSVCErr1up, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVCErr1down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_subjetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetFlavors,Systematics::CSVCErr1down, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVCErr2up",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_subjetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetFlavors,Systematics::CSVCErr2up, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);
            vars.FillVars("Topsubjets_ABCDCHSSoftDrop_masscorrwithtopbtag_WeightCSVCErr2down",i, csvReweighter->getCSVWeight(ABCDCHSSoftDrop_masscorrwithtopbtag_subjetPts,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetEtas,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetCSVs,ABCDCHSSoftDrop_masscorrwithtopbtag_subjetFlavors,Systematics::CSVCErr2down, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtHF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtLF, subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvWgtCF)/subjet_ABCDCHSSoftDrop_masscorrwithtopbtag_csvweight);  
            
        }
 
     }
  }
  
  
  
  
  //std::cout<<"furtherdebugging1"<<std::endl;
 
  ////FILL ABCDCHSPruning VARIABLES
  vars.FillVar("N_Zprime_ABCDCHSPruning",ZprimesABCDCHSPruning.size());

  for (uint i=0; i<ZprimesABCDCHSPruning.size(); i++){
  //for(math::XYZTLorentzVector::const_iterator ittopJet = AK8_top_candidates.begin() ; ittopJet != AK8_top_candidates.end(); ++ittopJet){
     //int i = 
     vars.FillVars("Zprimes_ABCDCHSPruning_M",i,ZprimesABCDCHSPruning[i].mass());
     vars.FillVars("Zprimes_ABCDCHSPruning_Pt",i,ZprimesABCDCHSPruning[i].pt());
     
     vars.FillVars("Tprimes_ABCDCHSPruning_M",i,TprimesABCDCHSPruning[i].mass());
     vars.FillVars("Tprimes_ABCDCHSPruning_Pt",i,TprimesABCDCHSPruning[i].pt());
     
     vars.FillVars("Bottoms_ABCDCHSPruning_Pt",i,BottomsABCDCHSPruning[i].pt());
     vars.FillVars("Bottoms_ABCDCHSPruning_Eta",i,BottomsABCDCHSPruning[i].eta());
     vars.FillVars("Bottoms_ABCDCHSPruning_Phi",i,BottomsABCDCHSPruning[i].phi());
     vars.FillVars("Bottoms_ABCDCHSPruning_CSV",i,MiniAODHelper::GetJetCSV(BottomsABCDCHSPruning[i],"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
     
//      CSVHelper csvReweighter;
     std::vector<double> ABCDCHSPruning_jetPts;
     std::vector<double> ABCDCHSPruning_jetEtas;
     std::vector<double> ABCDCHSPruning_jetCSVs;
     std::vector<int> ABCDCHSPruning_jetFlavors;
     double ABCDCHSPruning_csvWgtHF, ABCDCHSPruning_csvWgtLF, ABCDCHSPruning_csvWgtCF;
     float ABCDCHSPruning_csvweight = 1.;
     
     

     if(!input.isData){
        ABCDCHSPruning_jetPts.push_back(BottomsABCDCHSPruning[i].pt());
        ABCDCHSPruning_jetEtas.push_back(BottomsABCDCHSPruning[i].eta());
        ABCDCHSPruning_jetCSVs.push_back(MiniAODHelper::GetJetCSV(BottomsABCDCHSPruning[i],"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
        ABCDCHSPruning_jetFlavors.push_back(BottomsABCDCHSPruning[i].hadronFlavour());
        ABCDCHSPruning_csvweight= csvReweighter->getCSVWeight(ABCDCHSPruning_jetPts,ABCDCHSPruning_jetEtas,ABCDCHSPruning_jetCSVs,ABCDCHSPruning_jetFlavors,input.systematic, ABCDCHSPruning_csvWgtHF, ABCDCHSPruning_csvWgtLF, ABCDCHSPruning_csvWgtCF);
     }
     
    bool doSystematics=true;
//     if(doSystematics && input.input.systematic != sysType::JESup && input.input.systematic != sysType::JESdown && input.input.systematic != sysType::JERup && input.input.systematic != sysType::JERdown) {
    
     vars.FillVars("Bottoms_ABCDCHSPruning_WeightCSVnominal",i,ABCDCHSPruning_csvweight);    
    
     if(doSystematics && input.systematic == Systematics::NA) { // only do these for the nominal samples
//      std::cout<<"debug1   "<<ABCDCHSPruning_jetPts.size()<<endl;
     
     
         
     float Bottoms_ABCDCHSPruning_WeightCSVLFup=1.0;    
     float Bottoms_ABCDCHSPruning_WeightCSVLFdown=1.0;    
     float Bottoms_ABCDCHSPruning_WeightCSVHFup=1.0;    
     float Bottoms_ABCDCHSPruning_WeightCSVHFdown=1.0;    
     float Bottoms_ABCDCHSPruning_WeightCSVHFStats1up=1.0;    
     float Bottoms_ABCDCHSPruning_WeightCSVHFStats1down=1.0;    
     float Bottoms_ABCDCHSPruning_WeightCSVLFStats1up=1.0;    
     float Bottoms_ABCDCHSPruning_WeightCSVLFStats1down=1.0;    
     float Bottoms_ABCDCHSPruning_WeightCSVHFStats2up=1.0;    
     float Bottoms_ABCDCHSPruning_WeightCSVHFStats2down=1.0;    
     float Bottoms_ABCDCHSPruning_WeightCSVLFStats2up=1.0;    
     float Bottoms_ABCDCHSPruning_WeightCSVLFStats2down=1.0;    
     float Bottoms_ABCDCHSPruning_WeightCSVCErr1up=1.0;    
     float Bottoms_ABCDCHSPruning_WeightCSVCErr1down=1.0;    
     float Bottoms_ABCDCHSPruning_WeightCSVCErr2up=1.0;    
     float Bottoms_ABCDCHSPruning_WeightCSVCErr2down=1.0;    
        
     if(!input.isData){
         Bottoms_ABCDCHSPruning_WeightCSVLFup=csvReweighter->getCSVWeight(ABCDCHSPruning_jetPts,ABCDCHSPruning_jetEtas,ABCDCHSPruning_jetCSVs,ABCDCHSPruning_jetFlavors,Systematics::CSVLFup, ABCDCHSPruning_csvWgtHF, ABCDCHSPruning_csvWgtLF, ABCDCHSPruning_csvWgtCF)/ABCDCHSPruning_csvweight;
         Bottoms_ABCDCHSPruning_WeightCSVLFdown=csvReweighter->getCSVWeight(ABCDCHSPruning_jetPts,ABCDCHSPruning_jetEtas,ABCDCHSPruning_jetCSVs,ABCDCHSPruning_jetFlavors,Systematics::CSVLFdown, ABCDCHSPruning_csvWgtHF, ABCDCHSPruning_csvWgtLF, ABCDCHSPruning_csvWgtCF)/ABCDCHSPruning_csvweight;
         Bottoms_ABCDCHSPruning_WeightCSVHFup=csvReweighter->getCSVWeight(ABCDCHSPruning_jetPts,ABCDCHSPruning_jetEtas,ABCDCHSPruning_jetCSVs,ABCDCHSPruning_jetFlavors,Systematics::CSVHFup, ABCDCHSPruning_csvWgtHF, ABCDCHSPruning_csvWgtLF, ABCDCHSPruning_csvWgtCF)/ABCDCHSPruning_csvweight;
         Bottoms_ABCDCHSPruning_WeightCSVHFdown=csvReweighter->getCSVWeight(ABCDCHSPruning_jetPts,ABCDCHSPruning_jetEtas,ABCDCHSPruning_jetCSVs,ABCDCHSPruning_jetFlavors,Systematics::CSVHFdown, ABCDCHSPruning_csvWgtHF, ABCDCHSPruning_csvWgtLF, ABCDCHSPruning_csvWgtCF)/ABCDCHSPruning_csvweight;
         Bottoms_ABCDCHSPruning_WeightCSVHFStats1up=csvReweighter->getCSVWeight(ABCDCHSPruning_jetPts,ABCDCHSPruning_jetEtas,ABCDCHSPruning_jetCSVs,ABCDCHSPruning_jetFlavors,Systematics::CSVHFStats1up, ABCDCHSPruning_csvWgtHF, ABCDCHSPruning_csvWgtLF, ABCDCHSPruning_csvWgtCF)/ABCDCHSPruning_csvweight;
         Bottoms_ABCDCHSPruning_WeightCSVHFStats1down=csvReweighter->getCSVWeight(ABCDCHSPruning_jetPts,ABCDCHSPruning_jetEtas,ABCDCHSPruning_jetCSVs,ABCDCHSPruning_jetFlavors,Systematics::CSVHFStats1down, ABCDCHSPruning_csvWgtHF, ABCDCHSPruning_csvWgtLF, ABCDCHSPruning_csvWgtCF)/ABCDCHSPruning_csvweight;
         Bottoms_ABCDCHSPruning_WeightCSVLFStats1up=csvReweighter->getCSVWeight(ABCDCHSPruning_jetPts,ABCDCHSPruning_jetEtas,ABCDCHSPruning_jetCSVs,ABCDCHSPruning_jetFlavors,Systematics::CSVLFStats1up, ABCDCHSPruning_csvWgtHF, ABCDCHSPruning_csvWgtLF, ABCDCHSPruning_csvWgtCF)/ABCDCHSPruning_csvweight;
         Bottoms_ABCDCHSPruning_WeightCSVLFStats1down=csvReweighter->getCSVWeight(ABCDCHSPruning_jetPts,ABCDCHSPruning_jetEtas,ABCDCHSPruning_jetCSVs,ABCDCHSPruning_jetFlavors,Systematics::CSVLFStats1down, ABCDCHSPruning_csvWgtHF, ABCDCHSPruning_csvWgtLF, ABCDCHSPruning_csvWgtCF)/ABCDCHSPruning_csvweight;
         Bottoms_ABCDCHSPruning_WeightCSVHFStats2up=csvReweighter->getCSVWeight(ABCDCHSPruning_jetPts,ABCDCHSPruning_jetEtas,ABCDCHSPruning_jetCSVs,ABCDCHSPruning_jetFlavors,Systematics::CSVHFStats2up, ABCDCHSPruning_csvWgtHF, ABCDCHSPruning_csvWgtLF, ABCDCHSPruning_csvWgtCF)/ABCDCHSPruning_csvweight;
         Bottoms_ABCDCHSPruning_WeightCSVHFStats2down=csvReweighter->getCSVWeight(ABCDCHSPruning_jetPts,ABCDCHSPruning_jetEtas,ABCDCHSPruning_jetCSVs,ABCDCHSPruning_jetFlavors,Systematics::CSVHFStats2down, ABCDCHSPruning_csvWgtHF, ABCDCHSPruning_csvWgtLF, ABCDCHSPruning_csvWgtCF)/ABCDCHSPruning_csvweight;
         Bottoms_ABCDCHSPruning_WeightCSVLFStats2up=csvReweighter->getCSVWeight(ABCDCHSPruning_jetPts,ABCDCHSPruning_jetEtas,ABCDCHSPruning_jetCSVs,ABCDCHSPruning_jetFlavors,Systematics::CSVLFStats2up, ABCDCHSPruning_csvWgtHF, ABCDCHSPruning_csvWgtLF, ABCDCHSPruning_csvWgtCF)/ABCDCHSPruning_csvweight;
         Bottoms_ABCDCHSPruning_WeightCSVLFStats2down=csvReweighter->getCSVWeight(ABCDCHSPruning_jetPts,ABCDCHSPruning_jetEtas,ABCDCHSPruning_jetCSVs,ABCDCHSPruning_jetFlavors,Systematics::CSVLFStats2down, ABCDCHSPruning_csvWgtHF, ABCDCHSPruning_csvWgtLF, ABCDCHSPruning_csvWgtCF)/ABCDCHSPruning_csvweight;
         Bottoms_ABCDCHSPruning_WeightCSVCErr1up=csvReweighter->getCSVWeight(ABCDCHSPruning_jetPts,ABCDCHSPruning_jetEtas,ABCDCHSPruning_jetCSVs,ABCDCHSPruning_jetFlavors,Systematics::CSVCErr1up, ABCDCHSPruning_csvWgtHF, ABCDCHSPruning_csvWgtLF, ABCDCHSPruning_csvWgtCF)/ABCDCHSPruning_csvweight;
         Bottoms_ABCDCHSPruning_WeightCSVCErr1down=csvReweighter->getCSVWeight(ABCDCHSPruning_jetPts,ABCDCHSPruning_jetEtas,ABCDCHSPruning_jetCSVs,ABCDCHSPruning_jetFlavors,Systematics::CSVCErr1down, ABCDCHSPruning_csvWgtHF, ABCDCHSPruning_csvWgtLF, ABCDCHSPruning_csvWgtCF)/ABCDCHSPruning_csvweight;
         Bottoms_ABCDCHSPruning_WeightCSVCErr2up=csvReweighter->getCSVWeight(ABCDCHSPruning_jetPts,ABCDCHSPruning_jetEtas,ABCDCHSPruning_jetCSVs,ABCDCHSPruning_jetFlavors,Systematics::CSVCErr2up, ABCDCHSPruning_csvWgtHF, ABCDCHSPruning_csvWgtLF, ABCDCHSPruning_csvWgtCF)/ABCDCHSPruning_csvweight;
         Bottoms_ABCDCHSPruning_WeightCSVCErr2down=csvReweighter->getCSVWeight(ABCDCHSPruning_jetPts,ABCDCHSPruning_jetEtas,ABCDCHSPruning_jetCSVs,ABCDCHSPruning_jetFlavors,Systematics::CSVCErr2down, ABCDCHSPruning_csvWgtHF, ABCDCHSPruning_csvWgtLF, ABCDCHSPruning_csvWgtCF)/ABCDCHSPruning_csvweight;
     }
         
     vars.FillVars("Bottoms_ABCDCHSPruning_WeightCSVLFup",i,Bottoms_ABCDCHSPruning_WeightCSVLFup);
     vars.FillVars("Bottoms_ABCDCHSPruning_WeightCSVLFdown",i,Bottoms_ABCDCHSPruning_WeightCSVLFdown);
     vars.FillVars("Bottoms_ABCDCHSPruning_WeightCSVHFup",i, Bottoms_ABCDCHSPruning_WeightCSVHFup);
     vars.FillVars("Bottoms_ABCDCHSPruning_WeightCSVHFdown",i, Bottoms_ABCDCHSPruning_WeightCSVHFdown);
     vars.FillVars("Bottoms_ABCDCHSPruning_WeightCSVHFStats1up",i, Bottoms_ABCDCHSPruning_WeightCSVHFStats1up);
     vars.FillVars("Bottoms_ABCDCHSPruning_WeightCSVHFStats1down",i, Bottoms_ABCDCHSPruning_WeightCSVHFStats1down);
     vars.FillVars("Bottoms_ABCDCHSPruning_WeightCSVLFStats1up",i, Bottoms_ABCDCHSPruning_WeightCSVLFStats1up);
     vars.FillVars("Bottoms_ABCDCHSPruning_WeightCSVLFStats1down",i, Bottoms_ABCDCHSPruning_WeightCSVLFStats1down);
     vars.FillVars("Bottoms_ABCDCHSPruning_WeightCSVHFStats2up",i, Bottoms_ABCDCHSPruning_WeightCSVHFStats2up);
     vars.FillVars("Bottoms_ABCDCHSPruning_WeightCSVHFStats2down",i, Bottoms_ABCDCHSPruning_WeightCSVHFStats2down);
     vars.FillVars("Bottoms_ABCDCHSPruning_WeightCSVLFStats2up",i, Bottoms_ABCDCHSPruning_WeightCSVLFStats2up);
     vars.FillVars("Bottoms_ABCDCHSPruning_WeightCSVLFStats2down",i, Bottoms_ABCDCHSPruning_WeightCSVLFStats2down);
     vars.FillVars("Bottoms_ABCDCHSPruning_WeightCSVCErr1up",i, Bottoms_ABCDCHSPruning_WeightCSVCErr1up);
     vars.FillVars("Bottoms_ABCDCHSPruning_WeightCSVCErr1down",i, Bottoms_ABCDCHSPruning_WeightCSVCErr1down);
     vars.FillVars("Bottoms_ABCDCHSPruning_WeightCSVCErr2up",i, Bottoms_ABCDCHSPruning_WeightCSVCErr2up);
     vars.FillVars("Bottoms_ABCDCHSPruning_WeightCSVCErr2down",i, Bottoms_ABCDCHSPruning_WeightCSVCErr2down);
     
    }
//      std::cout<<"debug2   "<<jetPts.size()<<endl;
     

     float corr_AK8CHS_L1L2L3=1.0;
     float corr_AK8CHS_L2L3=1.0;
     pat::Jet WsABCDCHSPruning_temp_AK8CHSPruningL1L2L3 = WsABCDCHSPruning[i];
     pat::Jet WsABCDCHSPruning_temp_AK8CHSPruningL2L3 = WsABCDCHSPruning[i];
     corr_AK8CHS_L1L2L3=corrector_AK8CHS_L1L2L3->correction(WsABCDCHSPruning_temp_AK8CHSPruningL1L2L3, input.iEvent, input.iSetup);
     corr_AK8CHS_L2L3=corrector_AK8CHS_L2L3->correction(WsABCDCHSPruning_temp_AK8CHSPruningL2L3, input.iEvent, input.iSetup);
     
     vars.FillVars("Ws_ABCDCHSPruning_Pt",i,WsABCDCHSPruning[i].pt());
     vars.FillVars("Ws_ABCDCHSPruning_Eta",i,WsABCDCHSPruning[i].eta());
     vars.FillVars("Ws_ABCDCHSPruning_Phi",i,WsABCDCHSPruning[i].phi());
     vars.FillVars("Ws_ABCDCHSPruning_MSD",i,WsABCDCHSPruning[i].userFloat("ak8PFJetsCHSPrunedMass"));
     vars.FillVars("Ws_ABCDCHSPruning_MSD_smeared",i,WsABCDCHSPruning[i].userFloat("ak8PFJetsCHSPrunedMass")*(smearfactor_JetMass(WsABCDCHSPruning[i].phi(),WsABCDCHSPruning[i].eta()))[0]);
     vars.FillVars("Ws_ABCDCHSPruning_MSD_JetResup",i,WsABCDCHSPruning[i].userFloat("ak8PFJetsCHSPrunedMass")*(smearfactor_JetMass(WsABCDCHSPruning[i].phi(),WsABCDCHSPruning[i].eta()))[1]);
     vars.FillVars("Ws_ABCDCHSPruning_MSD_JetResdown",i,WsABCDCHSPruning[i].userFloat("ak8PFJetsCHSPrunedMass")*(smearfactor_JetMass(WsABCDCHSPruning[i].phi(),WsABCDCHSPruning[i].eta()))[2]);
     vars.FillVars("Ws_ABCDCHSPruning_t21",i,WsABCDCHSPruning[i].userFloat("NjettinessAK8CHS:tau2")/WsABCDCHSPruning[i].userFloat("NjettinessAK8CHS:tau1"));
     vars.FillVars("Ws_ABCDCHSPruning_corrL1L2L3",i,corr_AK8CHS_L1L2L3);
     vars.FillVars("Ws_ABCDCHSPruning_corrL2L3",i,corr_AK8CHS_L2L3);

     pat::Jet TopsABCDCHSPruning_temp_AK8CHSPruningL1L2L3 = TopsABCDCHSPruning[i];
     pat::Jet TopsABCDCHSPruning_temp_AK8CHSPruningL2L3 = TopsABCDCHSPruning[i];
     corr_AK8CHS_L1L2L3=corrector_AK8CHS_L1L2L3->correction(TopsABCDCHSPruning_temp_AK8CHSPruningL1L2L3, input.iEvent, input.iSetup);
     corr_AK8CHS_L2L3=corrector_AK8CHS_L2L3->correction(TopsABCDCHSPruning_temp_AK8CHSPruningL2L3, input.iEvent, input.iSetup);
     
     vars.FillVars("Tops_ABCDCHSPruning_Pt",i,TopsABCDCHSPruning[i].pt());
     vars.FillVars("Tops_ABCDCHSPruning_Eta",i,TopsABCDCHSPruning[i].eta());
     vars.FillVars("Tops_ABCDCHSPruning_Phi",i,TopsABCDCHSPruning[i].phi());
     vars.FillVars("Tops_ABCDCHSPruning_MSD",i,TopsABCDCHSPruning[i].userFloat("ak8PFJetsCHSSoftDropMass"));
     vars.FillVars("Tops_ABCDCHSPruning_t32",i,TopsABCDCHSPruning[i].userFloat("NjettinessAK8CHS:tau3")/TopsABCDCHSPruning[i].userFloat("NjettinessAK8CHS:tau2"));
     vars.FillVars("Tops_ABCDCHSPruning_corrL1L2L3",i,corr_AK8CHS_L1L2L3);
     vars.FillVars("Tops_ABCDCHSPruning_corrL2L3",i,corr_AK8CHS_L2L3);
     
     int realW_CHSPruning=0;
     int nmatchedaughters_topCHSPruning=0;
     if(input.zprimetotprimeallhad.IsFilled() && !input.isData && GenWs.size()>0){
        for(uint j=0; j<GenWs.size();j++){
            if (BoostedUtils::DeltaR(WsABCDCHSPruning[i].p4(),GenWs[j].p4())<0.8){
                realW_CHSPruning=1;
            for(uint k=0;k<GenWs_decayproducts.size();k++){
                if (BoostedUtils::DeltaR(WsABCDCHSPruning[i].p4(),GenWs_decayproducts[k].p4())<0.8){
                    nmatchedaughters_topCHSPruning++;
                }
            } 
            }
        }
     }

          
     int realtop_CHSPruning=0;
     int nmatchedaughters_WCHSPruning=0;
     if(input.zprimetotprimeallhad.IsFilled() && !input.isData && GenTops.size()>0){
        for(uint j=0; j<GenTops.size();j++){
            if (BoostedUtils::DeltaR(TopsABCDCHSPruning[i].p4(),GenTops[j].p4())<0.8){
                realtop_CHSPruning=1;
            for(uint k=0;k<GenTops_decayproducts.size();k++){
                if (BoostedUtils::DeltaR(TopsABCDCHSPruning[i].p4(),GenTops_decayproducts[k].p4())<0.8){
                    nmatchedaughters_WCHSPruning++;
                }
            }  
            }
        }
     }
     vars.FillVars("Ws_ABCDCHSPruning_real",i,realW_CHSPruning);
     vars.FillVars("Ws_ABCDCHSPruning_matcheddecays",i,nmatchedaughters_topCHSPruning);
     vars.FillVars("Tops_ABCDCHSPruning_real",i,realtop_CHSPruning);       
     vars.FillVars("Tops_ABCDCHSPruning_matcheddecays",i,nmatchedaughters_WCHSPruning);
  

     
  //std::cout<<"furtherdebugging1"<<std::endl;
     
//      std::cout<<"debucg1"<<endl;
     std::vector<double> ABCDCHSPruning_subjetPts;
     std::vector<double> ABCDCHSPruning_subjetEtas;
     std::vector<double> ABCDCHSPruning_subjetCSVs;
     std::vector<int> ABCDCHSPruning_subjetFlavors;
     double subjet_ABCDCHSPruning_csvWgtHF, subjet_ABCDCHSPruning_csvWgtLF, subjet_ABCDCHSPruning_csvWgtCF;
     float subjet_ABCDCHSPruning_csvweight = 1.;
     

     
     double max_subjet_csv_v2=-10;
     auto const & names = TopsABCDCHSPruning[i].subjets("SoftDrop");
     for( auto const & itsubJet : names ){
        if (itsubJet->pt()<20.0 || abs(itsubJet->eta())>2.4) continue;
        if(!input.isData){
            ABCDCHSPruning_subjetPts.push_back(itsubJet->pt());
            ABCDCHSPruning_subjetEtas.push_back(itsubJet->eta());
            ABCDCHSPruning_subjetCSVs.push_back(MiniAODHelper::GetJetCSV(*itsubJet,"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
            ABCDCHSPruning_subjetFlavors.push_back(itsubJet->hadronFlavour());
        }      
        if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>max_subjet_csv_v2){
            max_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
        };
     };
     
//      std::cout<<"debug2.2"<<endl;
     vars.FillVars("Tops_ABCDCHSPruning_maxsubjetCSVv2",i,max_subjet_csv_v2);
//      std::cout<<"max_subjet_csv_v2  "<<max_subjet_csv_v2<<endl;
     if(!input.isData){
         subjet_ABCDCHSPruning_csvweight= csvReweighter->getCSVWeight(ABCDCHSPruning_subjetPts,ABCDCHSPruning_subjetEtas,ABCDCHSPruning_subjetCSVs,ABCDCHSPruning_subjetFlavors,input.systematic, subjet_ABCDCHSPruning_csvWgtHF, subjet_ABCDCHSPruning_csvWgtLF, subjet_ABCDCHSPruning_csvWgtCF);
     }
 //     if(doSystematics && input.input.systematic != sysType::JESup && input.input.systematic != sysType::JESdown && input.input.systematic != sysType::JERup && input.input.systematic != sysType::JERdown) {

     vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVnominal",i,subjet_ABCDCHSPruning_csvweight);
     
     if(doSystematics && input.systematic == Systematics::NA) { // only do these for the nominal samples
//      std::cout<<"debug3   "<<ABCDCHSPruning_subjetPts.size()<<endl;
         
            if (input.isData){
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVLFup",i,1.0);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVLFdown",i,1.0);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVHFup",i, 1.0);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVHFdown",i, 1.0);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVHFStats1up",i, 1.0);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVHFStats1down",i, 1.0);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVLFStats1up",i, 1.0);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVLFStats1down",i, 1.0);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVHFStats2up",i, 1.0);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVHFStats2down",i, 1.0);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVLFStats2up",i, 1.0);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVLFStats2down",i, 1.0);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVCErr1up",i, 1.0);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVCErr1down",i, 1.0);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVCErr2up",i, 1.0);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVCErr2down",i, 1.0);  
                
            }else{
          
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVLFup",i,csvReweighter->getCSVWeight(ABCDCHSPruning_subjetPts,ABCDCHSPruning_subjetEtas,ABCDCHSPruning_subjetCSVs,ABCDCHSPruning_subjetFlavors,Systematics::CSVLFup, subjet_ABCDCHSPruning_csvWgtHF, subjet_ABCDCHSPruning_csvWgtLF, subjet_ABCDCHSPruning_csvWgtCF)/subjet_ABCDCHSPruning_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVLFdown",i,csvReweighter->getCSVWeight(ABCDCHSPruning_subjetPts,ABCDCHSPruning_subjetEtas,ABCDCHSPruning_subjetCSVs,ABCDCHSPruning_subjetFlavors,Systematics::CSVLFdown, subjet_ABCDCHSPruning_csvWgtHF, subjet_ABCDCHSPruning_csvWgtLF, subjet_ABCDCHSPruning_csvWgtCF)/subjet_ABCDCHSPruning_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVHFup",i, csvReweighter->getCSVWeight(ABCDCHSPruning_subjetPts,ABCDCHSPruning_subjetEtas,ABCDCHSPruning_subjetCSVs,ABCDCHSPruning_subjetFlavors,Systematics::CSVHFup, subjet_ABCDCHSPruning_csvWgtHF, subjet_ABCDCHSPruning_csvWgtLF, subjet_ABCDCHSPruning_csvWgtCF)/subjet_ABCDCHSPruning_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVHFdown",i, csvReweighter->getCSVWeight(ABCDCHSPruning_subjetPts,ABCDCHSPruning_subjetEtas,ABCDCHSPruning_subjetCSVs,ABCDCHSPruning_subjetFlavors,Systematics::CSVHFdown, subjet_ABCDCHSPruning_csvWgtHF, subjet_ABCDCHSPruning_csvWgtLF, subjet_ABCDCHSPruning_csvWgtCF)/subjet_ABCDCHSPruning_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVHFStats1up",i, csvReweighter->getCSVWeight(ABCDCHSPruning_subjetPts,ABCDCHSPruning_subjetEtas,ABCDCHSPruning_subjetCSVs,ABCDCHSPruning_subjetFlavors,Systematics::CSVHFStats1up, subjet_ABCDCHSPruning_csvWgtHF, subjet_ABCDCHSPruning_csvWgtLF, subjet_ABCDCHSPruning_csvWgtCF)/subjet_ABCDCHSPruning_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVHFStats1down",i, csvReweighter->getCSVWeight(ABCDCHSPruning_subjetPts,ABCDCHSPruning_subjetEtas,ABCDCHSPruning_subjetCSVs,ABCDCHSPruning_subjetFlavors,Systematics::CSVHFStats1down, subjet_ABCDCHSPruning_csvWgtHF, subjet_ABCDCHSPruning_csvWgtLF, subjet_ABCDCHSPruning_csvWgtCF)/subjet_ABCDCHSPruning_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVLFStats1up",i, csvReweighter->getCSVWeight(ABCDCHSPruning_subjetPts,ABCDCHSPruning_subjetEtas,ABCDCHSPruning_subjetCSVs,ABCDCHSPruning_subjetFlavors,Systematics::CSVLFStats1up, subjet_ABCDCHSPruning_csvWgtHF, subjet_ABCDCHSPruning_csvWgtLF, subjet_ABCDCHSPruning_csvWgtCF)/subjet_ABCDCHSPruning_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVLFStats1down",i, csvReweighter->getCSVWeight(ABCDCHSPruning_subjetPts,ABCDCHSPruning_subjetEtas,ABCDCHSPruning_subjetCSVs,ABCDCHSPruning_subjetFlavors,Systematics::CSVLFStats1down, subjet_ABCDCHSPruning_csvWgtHF, subjet_ABCDCHSPruning_csvWgtLF, subjet_ABCDCHSPruning_csvWgtCF)/subjet_ABCDCHSPruning_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVHFStats2up",i, csvReweighter->getCSVWeight(ABCDCHSPruning_subjetPts,ABCDCHSPruning_subjetEtas,ABCDCHSPruning_subjetCSVs,ABCDCHSPruning_subjetFlavors,Systematics::CSVHFStats2up, subjet_ABCDCHSPruning_csvWgtHF, subjet_ABCDCHSPruning_csvWgtLF, subjet_ABCDCHSPruning_csvWgtCF)/subjet_ABCDCHSPruning_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVHFStats2down",i, csvReweighter->getCSVWeight(ABCDCHSPruning_subjetPts,ABCDCHSPruning_subjetEtas,ABCDCHSPruning_subjetCSVs,ABCDCHSPruning_subjetFlavors,Systematics::CSVHFStats2down, subjet_ABCDCHSPruning_csvWgtHF, subjet_ABCDCHSPruning_csvWgtLF, subjet_ABCDCHSPruning_csvWgtCF)/subjet_ABCDCHSPruning_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVLFStats2up",i, csvReweighter->getCSVWeight(ABCDCHSPruning_subjetPts,ABCDCHSPruning_subjetEtas,ABCDCHSPruning_subjetCSVs,ABCDCHSPruning_subjetFlavors,Systematics::CSVLFStats2up, subjet_ABCDCHSPruning_csvWgtHF, subjet_ABCDCHSPruning_csvWgtLF, subjet_ABCDCHSPruning_csvWgtCF)/subjet_ABCDCHSPruning_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVLFStats2down",i, csvReweighter->getCSVWeight(ABCDCHSPruning_subjetPts,ABCDCHSPruning_subjetEtas,ABCDCHSPruning_subjetCSVs,ABCDCHSPruning_subjetFlavors,Systematics::CSVLFStats2down, subjet_ABCDCHSPruning_csvWgtHF, subjet_ABCDCHSPruning_csvWgtLF, subjet_ABCDCHSPruning_csvWgtCF)/subjet_ABCDCHSPruning_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVCErr1up",i, csvReweighter->getCSVWeight(ABCDCHSPruning_subjetPts,ABCDCHSPruning_subjetEtas,ABCDCHSPruning_subjetCSVs,ABCDCHSPruning_subjetFlavors,Systematics::CSVCErr1up, subjet_ABCDCHSPruning_csvWgtHF, subjet_ABCDCHSPruning_csvWgtLF, subjet_ABCDCHSPruning_csvWgtCF)/subjet_ABCDCHSPruning_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVCErr1down",i, csvReweighter->getCSVWeight(ABCDCHSPruning_subjetPts,ABCDCHSPruning_subjetEtas,ABCDCHSPruning_subjetCSVs,ABCDCHSPruning_subjetFlavors,Systematics::CSVCErr1down, subjet_ABCDCHSPruning_csvWgtHF, subjet_ABCDCHSPruning_csvWgtLF, subjet_ABCDCHSPruning_csvWgtCF)/subjet_ABCDCHSPruning_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVCErr2up",i, csvReweighter->getCSVWeight(ABCDCHSPruning_subjetPts,ABCDCHSPruning_subjetEtas,ABCDCHSPruning_subjetCSVs,ABCDCHSPruning_subjetFlavors,Systematics::CSVCErr2up, subjet_ABCDCHSPruning_csvWgtHF, subjet_ABCDCHSPruning_csvWgtLF, subjet_ABCDCHSPruning_csvWgtCF)/subjet_ABCDCHSPruning_csvweight);
                vars.FillVars("Topsubjets_ABCDCHSPruning_WeightCSVCErr2down",i, csvReweighter->getCSVWeight(ABCDCHSPruning_subjetPts,ABCDCHSPruning_subjetEtas,ABCDCHSPruning_subjetCSVs,ABCDCHSPruning_subjetFlavors,Systematics::CSVCErr2down, subjet_ABCDCHSPruning_csvWgtHF, subjet_ABCDCHSPruning_csvWgtLF, subjet_ABCDCHSPruning_csvWgtCF)/subjet_ABCDCHSPruning_csvweight);  
      //std::cout<<"debug4"<<endl;
            }
    }     
     
  }
  
  
 
  ////FILL ABCDPUPPISoftDrop VARIABLES
  vars.FillVar("N_Zprime_ABCDPUPPISoftDrop",ZprimesABCDPUPPISoftDrop.size());

  for (uint i=0; i<ZprimesABCDPUPPISoftDrop.size(); i++){
  //for(math::XYZTLorentzVector::const_iterator ittopJet = AK8_top_candidates.begin() ; ittopJet != AK8_top_candidates.end(); ++ittopJet){
     //int i = 
     vars.FillVars("Zprimes_ABCDPUPPISoftDrop_M",i,ZprimesABCDPUPPISoftDrop[i].mass());
     vars.FillVars("Zprimes_ABCDPUPPISoftDrop_Pt",i,ZprimesABCDPUPPISoftDrop[i].pt());
     
     vars.FillVars("Tprimes_ABCDPUPPISoftDrop_M",i,TprimesABCDPUPPISoftDrop[i].mass());
     vars.FillVars("Tprimes_ABCDPUPPISoftDrop_Pt",i,TprimesABCDPUPPISoftDrop[i].pt());
     
     vars.FillVars("Bottoms_ABCDPUPPISoftDrop_Pt",i,BottomsABCDPUPPISoftDrop[i].pt());
     vars.FillVars("Bottoms_ABCDPUPPISoftDrop_Eta",i,BottomsABCDPUPPISoftDrop[i].eta());
     vars.FillVars("Bottoms_ABCDPUPPISoftDrop_Phi",i,BottomsABCDPUPPISoftDrop[i].phi());
     vars.FillVars("Bottoms_ABCDPUPPISoftDrop_CSV",i,MiniAODHelper::GetJetCSV(BottomsABCDPUPPISoftDrop[i],"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
     
//      CSVHelper csvReweighter;
     std::vector<double> ABCDPUPPISoftDrop_jetPts;
     std::vector<double> ABCDPUPPISoftDrop_jetEtas;
     std::vector<double> ABCDPUPPISoftDrop_jetCSVs;
     std::vector<int> ABCDPUPPISoftDrop_jetFlavors;
     double ABCDPUPPISoftDrop_csvWgtHF, ABCDPUPPISoftDrop_csvWgtLF, ABCDPUPPISoftDrop_csvWgtCF;
     float ABCDPUPPISoftDrop_csvweight = 1.;
     
     

     if(!input.isData){
        ABCDPUPPISoftDrop_jetPts.push_back(BottomsABCDPUPPISoftDrop[i].pt());
        ABCDPUPPISoftDrop_jetEtas.push_back(BottomsABCDPUPPISoftDrop[i].eta());
        ABCDPUPPISoftDrop_jetCSVs.push_back(MiniAODHelper::GetJetCSV(BottomsABCDPUPPISoftDrop[i],"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
        ABCDPUPPISoftDrop_jetFlavors.push_back(BottomsABCDPUPPISoftDrop[i].hadronFlavour());
        ABCDPUPPISoftDrop_csvweight= csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_jetPts,ABCDPUPPISoftDrop_jetEtas,ABCDPUPPISoftDrop_jetCSVs,ABCDPUPPISoftDrop_jetFlavors,input.systematic, ABCDPUPPISoftDrop_csvWgtHF, ABCDPUPPISoftDrop_csvWgtLF, ABCDPUPPISoftDrop_csvWgtCF);
     }
     
    bool doSystematics=true;
//     if(doSystematics && input.input.systematic != sysType::JESup && input.input.systematic != sysType::JESdown && input.input.systematic != sysType::JERup && input.input.systematic != sysType::JERdown) {
    
     vars.FillVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVnominal",i,ABCDPUPPISoftDrop_csvweight);    
    
     if(doSystematics && input.systematic == Systematics::NA) { // only do these for the nominal samples
      //std::cout<<"debug1   "<<ABCDPUPPISoftDrop_jetPts.size()<<endl;
     
     
         
     float Bottoms_ABCDPUPPISoftDrop_WeightCSVLFup=1.0;    
     float Bottoms_ABCDPUPPISoftDrop_WeightCSVLFdown=1.0;    
     float Bottoms_ABCDPUPPISoftDrop_WeightCSVHFup=1.0;    
     float Bottoms_ABCDPUPPISoftDrop_WeightCSVHFdown=1.0;    
     float Bottoms_ABCDPUPPISoftDrop_WeightCSVHFStats1up=1.0;    
     float Bottoms_ABCDPUPPISoftDrop_WeightCSVHFStats1down=1.0;    
     float Bottoms_ABCDPUPPISoftDrop_WeightCSVLFStats1up=1.0;    
     float Bottoms_ABCDPUPPISoftDrop_WeightCSVLFStats1down=1.0;    
     float Bottoms_ABCDPUPPISoftDrop_WeightCSVHFStats2up=1.0;    
     float Bottoms_ABCDPUPPISoftDrop_WeightCSVHFStats2down=1.0;    
     float Bottoms_ABCDPUPPISoftDrop_WeightCSVLFStats2up=1.0;    
     float Bottoms_ABCDPUPPISoftDrop_WeightCSVLFStats2down=1.0;    
     float Bottoms_ABCDPUPPISoftDrop_WeightCSVCErr1up=1.0;    
     float Bottoms_ABCDPUPPISoftDrop_WeightCSVCErr1down=1.0;    
     float Bottoms_ABCDPUPPISoftDrop_WeightCSVCErr2up=1.0;    
     float Bottoms_ABCDPUPPISoftDrop_WeightCSVCErr2down=1.0;    
        
     if(!input.isData){
         Bottoms_ABCDPUPPISoftDrop_WeightCSVLFup=csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_jetPts,ABCDPUPPISoftDrop_jetEtas,ABCDPUPPISoftDrop_jetCSVs,ABCDPUPPISoftDrop_jetFlavors,Systematics::CSVLFup, ABCDPUPPISoftDrop_csvWgtHF, ABCDPUPPISoftDrop_csvWgtLF, ABCDPUPPISoftDrop_csvWgtCF)/ABCDPUPPISoftDrop_csvweight;
         Bottoms_ABCDPUPPISoftDrop_WeightCSVLFdown=csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_jetPts,ABCDPUPPISoftDrop_jetEtas,ABCDPUPPISoftDrop_jetCSVs,ABCDPUPPISoftDrop_jetFlavors,Systematics::CSVLFdown, ABCDPUPPISoftDrop_csvWgtHF, ABCDPUPPISoftDrop_csvWgtLF, ABCDPUPPISoftDrop_csvWgtCF)/ABCDPUPPISoftDrop_csvweight;
         Bottoms_ABCDPUPPISoftDrop_WeightCSVHFup=csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_jetPts,ABCDPUPPISoftDrop_jetEtas,ABCDPUPPISoftDrop_jetCSVs,ABCDPUPPISoftDrop_jetFlavors,Systematics::CSVHFup, ABCDPUPPISoftDrop_csvWgtHF, ABCDPUPPISoftDrop_csvWgtLF, ABCDPUPPISoftDrop_csvWgtCF)/ABCDPUPPISoftDrop_csvweight;
         Bottoms_ABCDPUPPISoftDrop_WeightCSVHFdown=csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_jetPts,ABCDPUPPISoftDrop_jetEtas,ABCDPUPPISoftDrop_jetCSVs,ABCDPUPPISoftDrop_jetFlavors,Systematics::CSVHFdown, ABCDPUPPISoftDrop_csvWgtHF, ABCDPUPPISoftDrop_csvWgtLF, ABCDPUPPISoftDrop_csvWgtCF)/ABCDPUPPISoftDrop_csvweight;
         Bottoms_ABCDPUPPISoftDrop_WeightCSVHFStats1up=csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_jetPts,ABCDPUPPISoftDrop_jetEtas,ABCDPUPPISoftDrop_jetCSVs,ABCDPUPPISoftDrop_jetFlavors,Systematics::CSVHFStats1up, ABCDPUPPISoftDrop_csvWgtHF, ABCDPUPPISoftDrop_csvWgtLF, ABCDPUPPISoftDrop_csvWgtCF)/ABCDPUPPISoftDrop_csvweight;
         Bottoms_ABCDPUPPISoftDrop_WeightCSVHFStats1down=csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_jetPts,ABCDPUPPISoftDrop_jetEtas,ABCDPUPPISoftDrop_jetCSVs,ABCDPUPPISoftDrop_jetFlavors,Systematics::CSVHFStats1down, ABCDPUPPISoftDrop_csvWgtHF, ABCDPUPPISoftDrop_csvWgtLF, ABCDPUPPISoftDrop_csvWgtCF)/ABCDPUPPISoftDrop_csvweight;
         Bottoms_ABCDPUPPISoftDrop_WeightCSVLFStats1up=csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_jetPts,ABCDPUPPISoftDrop_jetEtas,ABCDPUPPISoftDrop_jetCSVs,ABCDPUPPISoftDrop_jetFlavors,Systematics::CSVLFStats1up, ABCDPUPPISoftDrop_csvWgtHF, ABCDPUPPISoftDrop_csvWgtLF, ABCDPUPPISoftDrop_csvWgtCF)/ABCDPUPPISoftDrop_csvweight;
         Bottoms_ABCDPUPPISoftDrop_WeightCSVLFStats1down=csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_jetPts,ABCDPUPPISoftDrop_jetEtas,ABCDPUPPISoftDrop_jetCSVs,ABCDPUPPISoftDrop_jetFlavors,Systematics::CSVLFStats1down, ABCDPUPPISoftDrop_csvWgtHF, ABCDPUPPISoftDrop_csvWgtLF, ABCDPUPPISoftDrop_csvWgtCF)/ABCDPUPPISoftDrop_csvweight;
         Bottoms_ABCDPUPPISoftDrop_WeightCSVHFStats2up=csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_jetPts,ABCDPUPPISoftDrop_jetEtas,ABCDPUPPISoftDrop_jetCSVs,ABCDPUPPISoftDrop_jetFlavors,Systematics::CSVHFStats2up, ABCDPUPPISoftDrop_csvWgtHF, ABCDPUPPISoftDrop_csvWgtLF, ABCDPUPPISoftDrop_csvWgtCF)/ABCDPUPPISoftDrop_csvweight;
         Bottoms_ABCDPUPPISoftDrop_WeightCSVHFStats2down=csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_jetPts,ABCDPUPPISoftDrop_jetEtas,ABCDPUPPISoftDrop_jetCSVs,ABCDPUPPISoftDrop_jetFlavors,Systematics::CSVHFStats2down, ABCDPUPPISoftDrop_csvWgtHF, ABCDPUPPISoftDrop_csvWgtLF, ABCDPUPPISoftDrop_csvWgtCF)/ABCDPUPPISoftDrop_csvweight;
         Bottoms_ABCDPUPPISoftDrop_WeightCSVLFStats2up=csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_jetPts,ABCDPUPPISoftDrop_jetEtas,ABCDPUPPISoftDrop_jetCSVs,ABCDPUPPISoftDrop_jetFlavors,Systematics::CSVLFStats2up, ABCDPUPPISoftDrop_csvWgtHF, ABCDPUPPISoftDrop_csvWgtLF, ABCDPUPPISoftDrop_csvWgtCF)/ABCDPUPPISoftDrop_csvweight;
         Bottoms_ABCDPUPPISoftDrop_WeightCSVLFStats2down=csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_jetPts,ABCDPUPPISoftDrop_jetEtas,ABCDPUPPISoftDrop_jetCSVs,ABCDPUPPISoftDrop_jetFlavors,Systematics::CSVLFStats2down, ABCDPUPPISoftDrop_csvWgtHF, ABCDPUPPISoftDrop_csvWgtLF, ABCDPUPPISoftDrop_csvWgtCF)/ABCDPUPPISoftDrop_csvweight;
         Bottoms_ABCDPUPPISoftDrop_WeightCSVCErr1up=csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_jetPts,ABCDPUPPISoftDrop_jetEtas,ABCDPUPPISoftDrop_jetCSVs,ABCDPUPPISoftDrop_jetFlavors,Systematics::CSVCErr1up, ABCDPUPPISoftDrop_csvWgtHF, ABCDPUPPISoftDrop_csvWgtLF, ABCDPUPPISoftDrop_csvWgtCF)/ABCDPUPPISoftDrop_csvweight;
         Bottoms_ABCDPUPPISoftDrop_WeightCSVCErr1down=csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_jetPts,ABCDPUPPISoftDrop_jetEtas,ABCDPUPPISoftDrop_jetCSVs,ABCDPUPPISoftDrop_jetFlavors,Systematics::CSVCErr1down, ABCDPUPPISoftDrop_csvWgtHF, ABCDPUPPISoftDrop_csvWgtLF, ABCDPUPPISoftDrop_csvWgtCF)/ABCDPUPPISoftDrop_csvweight;
         Bottoms_ABCDPUPPISoftDrop_WeightCSVCErr2up=csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_jetPts,ABCDPUPPISoftDrop_jetEtas,ABCDPUPPISoftDrop_jetCSVs,ABCDPUPPISoftDrop_jetFlavors,Systematics::CSVCErr2up, ABCDPUPPISoftDrop_csvWgtHF, ABCDPUPPISoftDrop_csvWgtLF, ABCDPUPPISoftDrop_csvWgtCF)/ABCDPUPPISoftDrop_csvweight;
         Bottoms_ABCDPUPPISoftDrop_WeightCSVCErr2down=csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_jetPts,ABCDPUPPISoftDrop_jetEtas,ABCDPUPPISoftDrop_jetCSVs,ABCDPUPPISoftDrop_jetFlavors,Systematics::CSVCErr2down, ABCDPUPPISoftDrop_csvWgtHF, ABCDPUPPISoftDrop_csvWgtLF, ABCDPUPPISoftDrop_csvWgtCF)/ABCDPUPPISoftDrop_csvweight;
     }
         
     vars.FillVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVLFup",i,Bottoms_ABCDPUPPISoftDrop_WeightCSVLFup);
     vars.FillVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVLFdown",i,Bottoms_ABCDPUPPISoftDrop_WeightCSVLFdown);
     vars.FillVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVHFup",i, Bottoms_ABCDPUPPISoftDrop_WeightCSVHFup);
     vars.FillVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVHFdown",i, Bottoms_ABCDPUPPISoftDrop_WeightCSVHFdown);
     vars.FillVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVHFStats1up",i, Bottoms_ABCDPUPPISoftDrop_WeightCSVHFStats1up);
     vars.FillVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVHFStats1down",i, Bottoms_ABCDPUPPISoftDrop_WeightCSVHFStats1down);
     vars.FillVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVLFStats1up",i, Bottoms_ABCDPUPPISoftDrop_WeightCSVLFStats1up);
     vars.FillVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVLFStats1down",i, Bottoms_ABCDPUPPISoftDrop_WeightCSVLFStats1down);
     vars.FillVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVHFStats2up",i, Bottoms_ABCDPUPPISoftDrop_WeightCSVHFStats2up);
     vars.FillVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVHFStats2down",i, Bottoms_ABCDPUPPISoftDrop_WeightCSVHFStats2down);
     vars.FillVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVLFStats2up",i, Bottoms_ABCDPUPPISoftDrop_WeightCSVLFStats2up);
     vars.FillVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVLFStats2down",i, Bottoms_ABCDPUPPISoftDrop_WeightCSVLFStats2down);
     vars.FillVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVCErr1up",i, Bottoms_ABCDPUPPISoftDrop_WeightCSVCErr1up);
     vars.FillVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVCErr1down",i, Bottoms_ABCDPUPPISoftDrop_WeightCSVCErr1down);
     vars.FillVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVCErr2up",i, Bottoms_ABCDPUPPISoftDrop_WeightCSVCErr2up);
     vars.FillVars("Bottoms_ABCDPUPPISoftDrop_WeightCSVCErr2down",i, Bottoms_ABCDPUPPISoftDrop_WeightCSVCErr2down);
     
    }
//      std::cout<<"debug2   "<<jetPts.size()<<endl;
     

     float corr_AK8PUPPI_L1L2L3=1.0;
     float corr_AK8PUPPI_L2L3=1.0;
     pat::Jet WsABCDPUPPISoftDrop_temp_AK8PUPPISoftDropL1L2L3 = WsABCDPUPPISoftDrop[i];
     pat::Jet WsABCDPUPPISoftDrop_temp_AK8PUPPISoftDropL2L3 = WsABCDPUPPISoftDrop[i];
     corr_AK8PUPPI_L1L2L3=corrector_AK8Puppi_L1L2L3->correction(WsABCDPUPPISoftDrop_temp_AK8PUPPISoftDropL1L2L3, input.iEvent, input.iSetup);
     corr_AK8PUPPI_L2L3=corrector_AK8Puppi_L2L3->correction(WsABCDPUPPISoftDrop_temp_AK8PUPPISoftDropL2L3, input.iEvent, input.iSetup);
     vars.FillVars("Ws_ABCDPUPPISoftDrop_corrL1L2L3",i,corr_AK8PUPPI_L1L2L3);
     vars.FillVars("Ws_ABCDPUPPISoftDrop_corrL2L3",i,corr_AK8PUPPI_L2L3);

     
     vars.FillVars("Ws_ABCDPUPPISoftDrop_Pt",i,WsABCDPUPPISoftDrop[i].pt());
     vars.FillVars("Ws_ABCDPUPPISoftDrop_Eta",i,WsABCDPUPPISoftDrop[i].eta());
     vars.FillVars("Ws_ABCDPUPPISoftDrop_Phi",i,WsABCDPUPPISoftDrop[i].phi());
     vars.FillVars("Ws_ABCDPUPPISoftDrop_MSD",i,WsABCDPUPPISoftDrop[i].userFloat("ak8PFJetsPuppiSoftDropMass"));
     vars.FillVars("Ws_ABCDPUPPISoftDrop_t21",i,WsABCDPUPPISoftDrop[i].userFloat("NjettinessAK8Puppi:tau2")/WsABCDPUPPISoftDrop[i].userFloat("NjettinessAK8Puppi:tau1"));
     
     pat::Jet TopsABCDPUPPISoftDrop_temp_AK8PUPPISoftDropL1L2L3 = TopsABCDPUPPISoftDrop[i];
     pat::Jet TopsABCDPUPPISoftDrop_temp_AK8PUPPISoftDropL2L3 = TopsABCDPUPPISoftDrop[i];
     corr_AK8PUPPI_L1L2L3=corrector_AK8Puppi_L1L2L3->correction(TopsABCDPUPPISoftDrop_temp_AK8PUPPISoftDropL1L2L3, input.iEvent, input.iSetup);
     corr_AK8PUPPI_L2L3=corrector_AK8Puppi_L2L3->correction(TopsABCDPUPPISoftDrop_temp_AK8PUPPISoftDropL2L3, input.iEvent, input.iSetup);
     vars.FillVars("Tops_ABCDPUPPISoftDrop_corrL1L2L3",i,corr_AK8PUPPI_L1L2L3);
     vars.FillVars("Tops_ABCDPUPPISoftDrop_corrL2L3",i,corr_AK8PUPPI_L2L3);
     
     vars.FillVars("Tops_ABCDPUPPISoftDrop_Pt",i,TopsABCDPUPPISoftDrop[i].pt());
     vars.FillVars("Tops_ABCDPUPPISoftDrop_Eta",i,TopsABCDPUPPISoftDrop[i].eta());
     vars.FillVars("Tops_ABCDPUPPISoftDrop_Phi",i,TopsABCDPUPPISoftDrop[i].phi());
     vars.FillVars("Tops_ABCDPUPPISoftDrop_MSD",i,TopsABCDPUPPISoftDrop[i].userFloat("ak8PFJetsPuppiSoftDropMass"));
     vars.FillVars("Tops_ABCDPUPPISoftDrop_t32",i,TopsABCDPUPPISoftDrop[i].userFloat("NjettinessAK8Puppi:tau3")/TopsABCDPUPPISoftDrop[i].userFloat("NjettinessAK8Puppi:tau2"));

     int realW_PUPPISoftDrop=0;
    int nmatchedaughters_topPUPPISoftDrop=0;
     if(input.zprimetotprimeallhad.IsFilled() && !input.isData && GenWs.size()>0){
        for(uint j=0; j<GenWs.size();j++){
            if (BoostedUtils::DeltaR(WsABCDPUPPISoftDrop[i].p4(),GenWs[j].p4())<0.8){
                realW_PUPPISoftDrop=1;
            for(uint k=0;k<GenWs_decayproducts.size();k++){
                if (BoostedUtils::DeltaR(WsABCDPUPPISoftDrop[i].p4(),GenWs_decayproducts[k].p4())<0.8){
                    nmatchedaughters_topPUPPISoftDrop++;
                }
            }
            
            }
        }
     }

          
     int realtop_PUPPISoftDrop=0;
     int nmatchedaughters_WPUPPISoftDrop=0;
     if(input.zprimetotprimeallhad.IsFilled() && !input.isData && GenTops.size()>0){
        for(uint j=0; j<GenTops.size();j++){
            if (BoostedUtils::DeltaR(TopsABCDPUPPISoftDrop[i].p4(),GenTops[j].p4())<0.8){
                realtop_PUPPISoftDrop=1;
            for(uint k=0;k<GenTops_decayproducts.size();k++){
                if (BoostedUtils::DeltaR(TopsABCDPUPPISoftDrop[i].p4(),GenTops_decayproducts[k].p4())<0.8){
                    nmatchedaughters_WPUPPISoftDrop++;
                }
            }
            }
        }
     }
     vars.FillVars("Ws_ABCDPUPPISoftDrop_real",i,realW_PUPPISoftDrop);
     vars.FillVars("Ws_ABCDPUPPISoftDrop_matcheddecays",i,nmatchedaughters_topPUPPISoftDrop);
     vars.FillVars("Tops_ABCDPUPPISoftDrop_real",i,realtop_PUPPISoftDrop); 
     vars.FillVars("Tops_ABCDPUPPISoftDrop_matcheddecays",i,nmatchedaughters_WPUPPISoftDrop);
 
     
     //      std::cout<<"debucg1"<<endl;
     std::vector<double> ABCDPUPPISoftDrop_subjetPts;
     std::vector<double> ABCDPUPPISoftDrop_subjetEtas;
     std::vector<double> ABCDPUPPISoftDrop_subjetCSVs;
     std::vector<int> ABCDPUPPISoftDrop_subjetFlavors;
     double subjet_ABCDPUPPISoftDrop_csvWgtHF, subjet_ABCDPUPPISoftDrop_csvWgtLF, subjet_ABCDPUPPISoftDrop_csvWgtCF;
     float subjet_ABCDPUPPISoftDrop_csvweight = 1.;
     

     
     double max_subjet_csv_v2=-10;
     auto const & names = TopsABCDPUPPISoftDrop[i].subjets("SoftDrop");
     for( auto const & itsubJet : names ){
        if (itsubJet->pt()<20.0 || abs(itsubJet->eta())>2.4) continue;
        if(!input.isData){
            ABCDPUPPISoftDrop_subjetPts.push_back(itsubJet->pt());
            ABCDPUPPISoftDrop_subjetEtas.push_back(itsubJet->eta());
            ABCDPUPPISoftDrop_subjetCSVs.push_back(MiniAODHelper::GetJetCSV(*itsubJet,"pfCombinedInclusiveSecondaryVertexV2BJetTags"));
            ABCDPUPPISoftDrop_subjetFlavors.push_back(itsubJet->hadronFlavour());
        }      
        if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>max_subjet_csv_v2){
            max_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
        };
     };
     
//      std::cout<<"debug2.2"<<endl;
     vars.FillVars("Tops_ABCDPUPPISoftDrop_maxsubjetCSVv2",i,max_subjet_csv_v2);
//      std::cout<<"max_subjet_csv_v2  "<<max_subjet_csv_v2<<endl;
     if(!input.isData){
         subjet_ABCDPUPPISoftDrop_csvweight= csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_subjetPts,ABCDPUPPISoftDrop_subjetEtas,ABCDPUPPISoftDrop_subjetCSVs,ABCDPUPPISoftDrop_subjetFlavors,input.systematic, subjet_ABCDPUPPISoftDrop_csvWgtHF, subjet_ABCDPUPPISoftDrop_csvWgtLF, subjet_ABCDPUPPISoftDrop_csvWgtCF);
     }
 //     if(doSystematics && input.input.systematic != sysType::JESup && input.input.systematic != sysType::JESdown && input.input.systematic != sysType::JERup && input.input.systematic != sysType::JERdown) {

     vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVnominal",i,subjet_ABCDPUPPISoftDrop_csvweight);
     
     if(doSystematics && input.systematic == Systematics::NA) { // only do these for the nominal samples
//      std::cout<<"debug3   "<<ABCDPUPPISoftDrop_subjetPts.size()<<endl;
         
            if (input.isData){
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVLFup",i,1.0);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVLFdown",i,1.0);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVHFup",i, 1.0);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVHFdown",i, 1.0);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVHFStats1up",i, 1.0);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVHFStats1down",i, 1.0);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVLFStats1up",i, 1.0);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVLFStats1down",i, 1.0);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVHFStats2up",i, 1.0);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVHFStats2down",i, 1.0);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVLFStats2up",i, 1.0);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVLFStats2down",i, 1.0);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVCErr1up",i, 1.0);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVCErr1down",i, 1.0);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVCErr2up",i, 1.0);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVCErr2down",i, 1.0);  
                
            }else{
          
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVLFup",i,csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_subjetPts,ABCDPUPPISoftDrop_subjetEtas,ABCDPUPPISoftDrop_subjetCSVs,ABCDPUPPISoftDrop_subjetFlavors,Systematics::CSVLFup, subjet_ABCDPUPPISoftDrop_csvWgtHF, subjet_ABCDPUPPISoftDrop_csvWgtLF, subjet_ABCDPUPPISoftDrop_csvWgtCF)/subjet_ABCDPUPPISoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVLFdown",i,csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_subjetPts,ABCDPUPPISoftDrop_subjetEtas,ABCDPUPPISoftDrop_subjetCSVs,ABCDPUPPISoftDrop_subjetFlavors,Systematics::CSVLFdown, subjet_ABCDPUPPISoftDrop_csvWgtHF, subjet_ABCDPUPPISoftDrop_csvWgtLF, subjet_ABCDPUPPISoftDrop_csvWgtCF)/subjet_ABCDPUPPISoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVHFup",i, csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_subjetPts,ABCDPUPPISoftDrop_subjetEtas,ABCDPUPPISoftDrop_subjetCSVs,ABCDPUPPISoftDrop_subjetFlavors,Systematics::CSVHFup, subjet_ABCDPUPPISoftDrop_csvWgtHF, subjet_ABCDPUPPISoftDrop_csvWgtLF, subjet_ABCDPUPPISoftDrop_csvWgtCF)/subjet_ABCDPUPPISoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVHFdown",i, csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_subjetPts,ABCDPUPPISoftDrop_subjetEtas,ABCDPUPPISoftDrop_subjetCSVs,ABCDPUPPISoftDrop_subjetFlavors,Systematics::CSVHFdown, subjet_ABCDPUPPISoftDrop_csvWgtHF, subjet_ABCDPUPPISoftDrop_csvWgtLF, subjet_ABCDPUPPISoftDrop_csvWgtCF)/subjet_ABCDPUPPISoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVHFStats1up",i, csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_subjetPts,ABCDPUPPISoftDrop_subjetEtas,ABCDPUPPISoftDrop_subjetCSVs,ABCDPUPPISoftDrop_subjetFlavors,Systematics::CSVHFStats1up, subjet_ABCDPUPPISoftDrop_csvWgtHF, subjet_ABCDPUPPISoftDrop_csvWgtLF, subjet_ABCDPUPPISoftDrop_csvWgtCF)/subjet_ABCDPUPPISoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVHFStats1down",i, csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_subjetPts,ABCDPUPPISoftDrop_subjetEtas,ABCDPUPPISoftDrop_subjetCSVs,ABCDPUPPISoftDrop_subjetFlavors,Systematics::CSVHFStats1down, subjet_ABCDPUPPISoftDrop_csvWgtHF, subjet_ABCDPUPPISoftDrop_csvWgtLF, subjet_ABCDPUPPISoftDrop_csvWgtCF)/subjet_ABCDPUPPISoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVLFStats1up",i, csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_subjetPts,ABCDPUPPISoftDrop_subjetEtas,ABCDPUPPISoftDrop_subjetCSVs,ABCDPUPPISoftDrop_subjetFlavors,Systematics::CSVLFStats1up, subjet_ABCDPUPPISoftDrop_csvWgtHF, subjet_ABCDPUPPISoftDrop_csvWgtLF, subjet_ABCDPUPPISoftDrop_csvWgtCF)/subjet_ABCDPUPPISoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVLFStats1down",i, csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_subjetPts,ABCDPUPPISoftDrop_subjetEtas,ABCDPUPPISoftDrop_subjetCSVs,ABCDPUPPISoftDrop_subjetFlavors,Systematics::CSVLFStats1down, subjet_ABCDPUPPISoftDrop_csvWgtHF, subjet_ABCDPUPPISoftDrop_csvWgtLF, subjet_ABCDPUPPISoftDrop_csvWgtCF)/subjet_ABCDPUPPISoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVHFStats2up",i, csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_subjetPts,ABCDPUPPISoftDrop_subjetEtas,ABCDPUPPISoftDrop_subjetCSVs,ABCDPUPPISoftDrop_subjetFlavors,Systematics::CSVHFStats2up, subjet_ABCDPUPPISoftDrop_csvWgtHF, subjet_ABCDPUPPISoftDrop_csvWgtLF, subjet_ABCDPUPPISoftDrop_csvWgtCF)/subjet_ABCDPUPPISoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVHFStats2down",i, csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_subjetPts,ABCDPUPPISoftDrop_subjetEtas,ABCDPUPPISoftDrop_subjetCSVs,ABCDPUPPISoftDrop_subjetFlavors,Systematics::CSVHFStats2down, subjet_ABCDPUPPISoftDrop_csvWgtHF, subjet_ABCDPUPPISoftDrop_csvWgtLF, subjet_ABCDPUPPISoftDrop_csvWgtCF)/subjet_ABCDPUPPISoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVLFStats2up",i, csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_subjetPts,ABCDPUPPISoftDrop_subjetEtas,ABCDPUPPISoftDrop_subjetCSVs,ABCDPUPPISoftDrop_subjetFlavors,Systematics::CSVLFStats2up, subjet_ABCDPUPPISoftDrop_csvWgtHF, subjet_ABCDPUPPISoftDrop_csvWgtLF, subjet_ABCDPUPPISoftDrop_csvWgtCF)/subjet_ABCDPUPPISoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVLFStats2down",i, csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_subjetPts,ABCDPUPPISoftDrop_subjetEtas,ABCDPUPPISoftDrop_subjetCSVs,ABCDPUPPISoftDrop_subjetFlavors,Systematics::CSVLFStats2down, subjet_ABCDPUPPISoftDrop_csvWgtHF, subjet_ABCDPUPPISoftDrop_csvWgtLF, subjet_ABCDPUPPISoftDrop_csvWgtCF)/subjet_ABCDPUPPISoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVCErr1up",i, csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_subjetPts,ABCDPUPPISoftDrop_subjetEtas,ABCDPUPPISoftDrop_subjetCSVs,ABCDPUPPISoftDrop_subjetFlavors,Systematics::CSVCErr1up, subjet_ABCDPUPPISoftDrop_csvWgtHF, subjet_ABCDPUPPISoftDrop_csvWgtLF, subjet_ABCDPUPPISoftDrop_csvWgtCF)/subjet_ABCDPUPPISoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVCErr1down",i, csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_subjetPts,ABCDPUPPISoftDrop_subjetEtas,ABCDPUPPISoftDrop_subjetCSVs,ABCDPUPPISoftDrop_subjetFlavors,Systematics::CSVCErr1down, subjet_ABCDPUPPISoftDrop_csvWgtHF, subjet_ABCDPUPPISoftDrop_csvWgtLF, subjet_ABCDPUPPISoftDrop_csvWgtCF)/subjet_ABCDPUPPISoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVCErr2up",i, csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_subjetPts,ABCDPUPPISoftDrop_subjetEtas,ABCDPUPPISoftDrop_subjetCSVs,ABCDPUPPISoftDrop_subjetFlavors,Systematics::CSVCErr2up, subjet_ABCDPUPPISoftDrop_csvWgtHF, subjet_ABCDPUPPISoftDrop_csvWgtLF, subjet_ABCDPUPPISoftDrop_csvWgtCF)/subjet_ABCDPUPPISoftDrop_csvweight);
                vars.FillVars("Topsubjets_ABCDPUPPISoftDrop_WeightCSVCErr2down",i, csvReweighter->getCSVWeight(ABCDPUPPISoftDrop_subjetPts,ABCDPUPPISoftDrop_subjetEtas,ABCDPUPPISoftDrop_subjetCSVs,ABCDPUPPISoftDrop_subjetFlavors,Systematics::CSVCErr2down, subjet_ABCDPUPPISoftDrop_csvWgtHF, subjet_ABCDPUPPISoftDrop_csvWgtLF, subjet_ABCDPUPPISoftDrop_csvWgtCF)/subjet_ABCDPUPPISoftDrop_csvweight);  
//      std::cout<<"debug4"<<endl;
            }
    }     
     
  }  

  
  
   
 }// end of HT if 1190
 
 //std::cout<<"last"<<std::endl;
 vars.FillVar("N_electrons",input.selectedElectrons.size());
 vars.FillVar("N_muons",input.selectedMuons.size());
 vars.FillVar("N_electronsMidloose",input.selectedElectronsDL.size());
 vars.FillVar("N_muonsMidloose",input.selectedMuonsDL.size());
 vars.FillVar("N_electronsLoose",input.selectedElectronsLoose.size());
 vars.FillVar("N_muonsLoose",input.selectedMuonsLoose.size());
 
 for(std::vector<pat::Electron>::const_iterator itParticle = input.selectedElectrons.begin() ; itParticle != input.selectedElectrons.end(); ++itParticle){
    int iParticle = itParticle - input.selectedElectrons.begin();
    vars.FillVars("Electrons_Pt",iParticle,itParticle->pt());
 }
 for(std::vector<pat::Muon>::const_iterator itParticle = input.selectedMuons.begin() ; itParticle != input.selectedMuons.end(); ++itParticle){
    int iParticle = itParticle - input.selectedMuons.begin();    
    vars.FillVars("Muons_Pt",iParticle,itParticle->pt());
 } 
 for(std::vector<pat::Electron>::const_iterator itParticle = input.selectedElectronsDL.begin() ; itParticle != input.selectedElectronsDL.end(); ++itParticle){
    int iParticle = itParticle - input.selectedElectronsDL.begin();
    vars.FillVars("ElectronsMidloose_Pt",iParticle,itParticle->pt());
 }
 for(std::vector<pat::Muon>::const_iterator itParticle = input.selectedMuonsDL.begin() ; itParticle != input.selectedMuonsDL.end(); ++itParticle){
    int iParticle = itParticle - input.selectedMuonsDL.begin();
    vars.FillVars("MuonsMidloose_Pt",iParticle,itParticle->pt());
 } 
 
 for(std::vector<pat::Electron>::const_iterator itParticle = input.selectedElectronsLoose.begin() ; itParticle != input.selectedElectronsLoose.end(); ++itParticle){
    int iParticle = itParticle - input.selectedElectronsLoose.begin();
    vars.FillVars("ElectronsLoose_Pt",iParticle,itParticle->pt());
 }
 for(std::vector<pat::Muon>::const_iterator itParticle = input.selectedMuonsLoose.begin() ; itParticle != input.selectedMuonsLoose.end(); ++itParticle){
    int iParticle = itParticle - input.selectedMuonsLoose.begin();
    vars.FillVars("MuonsLoose_Pt",iParticle,itParticle->pt());
 }
 
}
