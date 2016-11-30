#include "BoostedTTH/BoostedAnalyzer/interface/ZPrimeToTPrimeAllHadProcessor.hpp"
#include <string> 


// all configurations should be done in constructor
ZPrimeToTPrimeAllHadProcessor::ZPrimeToTPrimeAllHadProcessor(){}
ZPrimeToTPrimeAllHadProcessor::~ZPrimeToTPrimeAllHadProcessor(){}


void ZPrimeToTPrimeAllHadProcessor::Init(const InputCollections& input,VariableContainer& vars){
    
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

    


    vars.InitVars("Gen_Top_Pt","N_Gen_Tops");
    vars.InitVars("Gen_Topbar_Pt","N_Gen_Topbars");
    vars.InitVars("Gen_TopandTopbar_Pt","N_Gen_TopsandTopbars");

    vars.InitVars("Gen_ZPrime_M","N_Gen_ZPrimes");
    vars.InitVars("Gen_TPrimeandTPrimebar_M","N_Gen_TPrimesandTPrimebars");   
    vars.InitVars("Gen_ZPrime_Pt","N_Gen_ZPrimes");   


    vars.InitVars("Gen_TPrime_Pt","N_Gen_TPrimes");
    vars.InitVars("Gen_TPrimebar_Pt","N_Gen_TPrimebars");
    vars.InitVars("Gen_TPrimeandTPrimebar_Pt","N_Gen_TPrimesandTPrimebars");

    vars.InitVars("Gen_WplusfromTop_Pt","N_Gen_WplusfromTops");
    vars.InitVars("Gen_WminusfromTopbar_Pt","N_Gen_WminusfromTopbars");
    vars.InitVars("Gen_WfromTopandTopbar_Pt","N_Gen_WfromTopsandTopbars");

    vars.InitVars("Gen_WplusfromTPrime_Pt","N_Gen_WplusfromTPrimes");
    vars.InitVars("Gen_WminusfromTPrimebar_Pt","N_Gen_WminusfromTPrimebars");
    vars.InitVars("Gen_WfromTPrimeandTPrimebar_Pt","N_Gen_WfromTPrimesandTPrimebars");

    vars.InitVars("Gen_BottomfromTop_Pt","N_Gen_BottomfromTops");
    vars.InitVars("Gen_BottombarfromTopbar_Pt","N_Gen_BottombarfromTopbars");
    vars.InitVars("Gen_BottomfromTopandTopbar_Pt","N_Gen_BottomfromTopsandTopbars");

    vars.InitVars("Gen_BottomfromTPrime_Pt","N_Gen_BottomfromTPrimes");
    vars.InitVars("Gen_BottombarfromTPrimebar_Pt","N_Gen_BottombarfromTPrimebars");
    vars.InitVars("Gen_BottomfromTPrimeandTPrimebar_Pt","N_Gen_BottomfromTPrimesandTPrimebars");

    
    
    vars.InitVars("Gen_Top_Eta","N_Gen_Tops");
    vars.InitVars("Gen_Topbar_Eta","N_Gen_Topbars");
    vars.InitVars("Gen_TopandTopbar_Eta","N_Gen_TopsandTopbars");

    vars.InitVars("Gen_ZPrime_Eta","N_Gen_ZPrimes");    
    vars.InitVars("Gen_TPrime_Eta","N_Gen_TPrimes");
    vars.InitVars("Gen_TPrimebar_Eta","N_Gen_TPrimebars");
    vars.InitVars("Gen_TPrimeandTPrimebar_Eta","N_Gen_TPrimesandTPrimebars");

    vars.InitVars("Gen_WplusfromTop_Eta","N_Gen_WplusfromTops");
    vars.InitVars("Gen_WminusfromTopbar_Eta","N_Gen_WminusfromTopbars");
    vars.InitVars("Gen_WfromTopandTopbar_Eta","N_Gen_WfromTopsandTopbars");

    vars.InitVars("Gen_WplusfromTPrime_Eta","N_Gen_WplusfromTPrimes");
    vars.InitVars("Gen_WminusfromTPrimebar_Eta","N_Gen_WminusfromTPrimebars");
    vars.InitVars("Gen_WfromTPrimeandTPrimebar_Eta","N_Gen_WfromTPrimesandTPrimebars");
    
    vars.InitVars("Gen_BottomfromTop_Eta","N_Gen_BottomfromTops");
    vars.InitVars("Gen_BottombarfromTopbar_Eta","N_Gen_BottombarfromTopbars");
    vars.InitVars("Gen_BottomfromTopandTopbar_Eta","N_Gen_BottomfromTopsandTopbars");

    vars.InitVars("Gen_BottomfromTPrime_Eta","N_Gen_BottomfromTPrimes");
    vars.InitVars("Gen_BottombarfromTPrimebar_Eta","N_Gen_BottombarfromTPrimebars");
    vars.InitVars("Gen_BottomfromTPrimeandTPrimebar_Eta","N_Gen_BottomfromTPrimesandTPrimebars");

    
    vars.InitVar("Gen_Top_TPrime_DeltaR");//,"input.zprimetotprimeallhad.GetTops_fromZprimes().size()*input.zprimetotprimeallhad.GetTPrimebars().size()");
    vars.InitVar("Gen_Top_WfromTPrime_DeltaR");//,"input.zprimetotprimeallhad.GetTops_fromZprimes().size()*input.zprimetotprimeallhad.GetWminus_fromTPrimes().size()");
    vars.InitVar("Gen_Top_BottomfromTPrime_DeltaR");//,"input.zprimetotprimeallhad.GetTop_fromZprimess().size()*input.zprimetotprimeallhad.GetTPrimeDecayQuarks().size()");
    vars.InitVar("Gen_WfromTPrime_BottomfromTPrime_DeltaR");//,"input.zprimetotprimeallhad.GetWplus_fromTPrimes().size()*input.zprimetotprimeallhad.GetTPrimeDecayQuarks().size()");
    vars.InitVar("Gen_WfromTop_BottomfromTop_DeltaR");//,"input.zprimetotprimeallhad.GetWplus_fromTops().size()*input.zprimetotprimeallhad.GetTopDecayQuarks().size()");
    
    vars.InitVar("Gen_Top_WfromTPrime_DeltaEta");
    vars.InitVar("Gen_Top_BottomfromTPrime_DeltaEta");
    vars.InitVar("Gen_WfromTPrime_BottomfromTPrime_DeltaEta");
    
    vars.InitVar("Gen_Top_WfromTPrime_DeltaPhi");
    vars.InitVar("Gen_Top_BottomfromTPrime_DeltaPhi");
    vars.InitVar("Gen_WfromTPrime_BottomfromTPrime_DeltaPhi");
    
    
    vars.InitVar("N_packedPatJetsAK8PFCHSSoftDrop","I");
    vars.InitVars("packedPatJetsAK8PFCHSSoftDrop_Pt",-9,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("packedPatJetsAK8PFCHSSoftDrop_Eta",-9,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("packedPatJetsAK8PFCHSSoftDrop_Phi",-9,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("packedPatJetsAK8PFCHSSoftDrop_E",-9,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("packedPatJetsAK8PFCHSSoftDrop_M",-9,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("NjettinessAK8CHS_tau1",-9,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("NjettinessAK8CHS_tau2",-9,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("NjettinessAK8CHS_tau3",-9,"N_packedPatJetsAK8PFCHSSoftDrop");
    
    vars.InitVars("softDropMassAK8CHS",-9,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("cmsTopTagPFJetsCHSMassAK8",-9,"N_packedPatJetsAK8PFCHSSoftDrop");
    vars.InitVars("packedPatJetsAK8PFCHSSoftDrop_subjetCSVv2",-9,"N_packedPatJetsAK8PFCHSSoftDrop");


    
//    vars.InitVar("N_selectedPatJetsAK8PFCHSSoftDropPacked","I");
//    vars.InitVar("N_packedPatJetsAK8PFCHSSoftDrop","I");
/*
    vars.InitVars("selectedPatJetsAK8PFCHSSoftDropPacked_E",-9,"N_selectedPatJetsAK8PFCHSSoftDropPacked");
    vars.InitVars("selectedPatJetsAK8PFCHSSoftDropPacked_M",-9,"N_selectedPatJetsAK8PFCHSSoftDropPacked");
    vars.InitVars("selectedPatJetsAK8PFCHSSoftDropPacked_Pt",-9,"N_selectedPatJetsAK8PFCHSSoftDropPacked");
    vars.InitVars("selectedPatJetsAK8PFCHSSoftDropPacked_Phi",-9,"N_selectedPatJetsAK8PFCHSSoftDropPacked");
    vars.InitVars("selectedPatJetsAK8PFCHSSoftDropPacked_Eta",-9,"N_selectedPatJetsAK8PFCHSSoftDropPacked");
    vars.InitVars("NsubjettinessAK8PFCHSSoftDropPacked_tau1",-9,"N_selectedPatJetsAK8PFCHSSoftDropPacked");
    vars.InitVars("NsubjettinessAK8PFCHSSoftDropPacked_tau2",-9,"N_selectedPatJetsAK8PFCHSSoftDropPacked");
    vars.InitVars("NsubjettinessAK8PFCHSSoftDropPacked_tau3",-9,"N_selectedPatJetsAK8PFCHSSoftDropPacked");
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

    
///Variables after reconstruction
    
   vars.InitVars("Jet_Dr_bfromTPrime",-9.,"N_Jets");
   vars.InitVars("Jet_Dr_bfromBG",-9.,"N_Jets");    
  
   vars.InitVar("Zprime_M","I");
   vars.InitVar("Zprime_withtop_btag_M","I");
   vars.InitVar("Zprime_bottom_anti_M","I");
   vars.InitVar("Zprime_bottom_anti_withtop_btag_M","I");

   vars.InitVar("Tprime_M","I");
   vars.InitVar("Tprime_bottom_anti_M","I");   
   vars.InitVar("Tprime_pt","I");
   vars.InitVar("Tprime_bottom_anti_pt","I");
   
   vars.InitVar("Top_candidates_pt","I");
   vars.InitVar("Top_candidates_withbtag_pt","I");  
   vars.InitVar("W_candidates_pt","I");
   vars.InitVar("Bottom_candidates_pt","I");
   vars.InitVar("Bottom_anti_candidates_pt","I");
  
///Variables for misstag rates
   vars.InitVar("N_misstagged_top","I");
   vars.InitVars("misstagged_top_pt","N_misstagged_top");
   vars.InitVars("misstagged_top_eta","N_misstagged_top");
   vars.InitVar("N_misstagged_top_withbtag","I");
   vars.InitVars("misstagged_top_withbtag_pt","N_misstagged_top_withbtag");
   vars.InitVars("misstagged_top_withbtag_eta","N_misstagged_top_withbtag");
   vars.InitVar("N_misstagged_W","I");
   vars.InitVars("misstagged_W_pt","N_misstagged_W");
   vars.InitVars("misstagged_W_eta","N_misstagged_W");
   vars.InitVar("N_misstagged_bottom","I");
   vars.InitVars("misstagged_bottom_pt","N_misstagged_bottom");
   vars.InitVars("misstagged_bottom_eta","N_misstagged_bottom");
   
   vars.InitVar("N_AK8_top_misstag_candidates","I");
   vars.InitVars("AK8_top_misstagged_candidates_pt","N_AK8_top_misstag_candidates");
   vars.InitVars("AK8_top_misstagged_candidates_eta","N_AK8_top_misstag_candidates");
   vars.InitVar("N_AK8_W_misstag_candidates","I");
   vars.InitVars("AK8_W_misstagged_candidates_pt","N_AK8_W_misstag_candidates");
   vars.InitVars("AK8_W_misstagged_candidates_eta","N_AK8_W_misstag_candidates");
   vars.InitVar("N_AK4_bottom_misstag_candidates","I");
   vars.InitVars("AK4_bottom_misstagged_candidates_pt","N_AK4_bottom_misstag_candidates");
   vars.InitVars("AK4_bottom_misstagged_candidates_eta","N_AK4_bottom_misstag_candidates");
   
///Variables for tagging efficiencies
   
   
///Variables for datadriven Background estimation
   vars.InitVar("BG_Zprime_M","I");
   vars.InitVar("BG_Zprime_withtop_btag_M","I");

   vars.InitVar("BG_Tprime_M","I");
   vars.InitVar("BG_Tprime_pt","I");

   vars.InitVar("BG_Top_candidates_pt","I");
   vars.InitVar("BG_Top_candidates_withbtag_pt","I");  
   vars.InitVar("BG_W_candidates_pt","I");
   vars.InitVar("BG_Bottom_candidates_pt","I");
   vars.InitVar("BG_Bottom_anti_candidates_pt","I");
   
  initialized=true;
}

void ZPrimeToTPrimeAllHadProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << std::endl; // complain if not initialized but keep running

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

    vars.FillVar("N_packedPatJetsAK8PFCHSSoftDrop", input.packedPatJetsAK8PFCHSSoftDrop.size());
    
//    vars.FillVar("N_selectedPatJetsAK8PFCHSSoftDropPacked", input.selectedPatJetsAK8PFCHSSoftDropPacked.size());
//    vars.FillVar("N_packedPatJetsAK8PFCHSSoftDrop", input.packedPatJetsAK8PFCHSSoftDrop.size());

  
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
    
    

//AK8->Jets
    if(input.packedPatJetsAK8PFCHSSoftDrop.size()>0){
            
///General AK8-Jet        
        for(std::vector<pat::Jet>::const_iterator itJet=input.packedPatJetsAK8PFCHSSoftDrop.begin(); itJet != input.packedPatJetsAK8PFCHSSoftDrop.end(); ++itJet){
            int iJet = itJet - input.packedPatJetsAK8PFCHSSoftDrop.begin();
            if (itJet->pt()>200 && abs(itJet->eta())<2.4){
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



///////EVENT RECONSTRUCTION Wtb-channel///////
    float ht =0.;
    for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin() ; itJet != input.selectedJets.end(); ++itJet){
        ht += itJet->pt();
    }
    if( ht<850){
        

    
    double top_pt_max=0.0;
    double top_anti_pt_max=0.0;
    double top_withbtag_pt_max=0.0;
    double top_withbtag_anti_pt_max=0.0;
    double W_pt_max=0.0;
    double W_anti_pt_max=0.0;
    double bottom_pt_max=0.0;
    double bottom_anti_pt_max=0.0;
    
    //math::XYZTTLorentzVector top;
    pat::Jet top;
    pat::Jet top_withbtag;
    pat::Jet W;
    pat::Jet bottom;
    pat::Jet top_anti;
    pat::Jet top_withbtag_anti;
    pat::Jet W_anti;
    pat::Jet bottom_anti;   
    
    math::XYZTLorentzVector Tprime;
    math::XYZTLorentzVector Tprime_bottom_anti;
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
    math::XYZTLorentzVector Zprime_withtopbtag_bottom_anti;
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
    bool Tprime_candidatefound=false;
    bool Tprime_bottom_anti_candidatefound=false;
    bool Tprime_W_anti_candidatefound=false;
    bool Tprime_W_anti_bottom_anti_candidatefound=false;

    
    std::vector<pat::Jet> misstagged_top;
    std::vector<pat::Jet> misstagged_top_withbtag;
    std::vector<pat::Jet> misstagged_W;
    std::vector<pat::Jet> misstagged_bottom;
    std::vector<pat::Jet> AK8_top_candidates;
    std::vector<pat::Jet> AK8_W_candidates;
    std::vector<pat::Jet> AK4_bottom_candidates;
    

    //uint N_AK8_top_misstag_candidates=0;
    //uint N_AK8_W_misstag_candidates=0;
    //uint N_AK4_bottom_misstag_candidates=0;
    //uint N_misstagged_top=0;
    //uint N_misstagged_top_withbtag=0;
    //uint N_misstagged_W=0;    
    //uint N_misstagged_bottom=0;    
    
//AK8->Jets
    if(input.packedPatJetsAK8PFCHSSoftDrop.size()>0){
       
///General AK8-Jet        
        for(std::vector<pat::Jet>::const_iterator itJet=input.packedPatJetsAK8PFCHSSoftDrop.begin(); itJet != input.packedPatJetsAK8PFCHSSoftDrop.end(); ++itJet){
            int iJet = itJet - input.packedPatJetsAK8PFCHSSoftDrop.begin();

            double max_subjet_csv_v2=-10;
            auto const & names = itJet->subjets("SoftDrop");
            for( auto const & itsubJet : names ){

                if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>max_subjet_csv_v2){
                    max_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
                    vars.FillVars("packedPatJetsAK8PFCHSSoftDrop_subjetCSVv2",iJet,max_subjet_csv_v2);
                }
            }
            
///top- and W-candidates
            if (itJet->pt()>200 && abs(itJet->eta())<2.4){
                //N_AK8_W_misstag_candidates+=1;
                if (itJet->pt()>400){
                    //N_AK8_top_misstag_candidates+=1;
                }
                
//top candidates
                if (itJet->userFloat("NjettinessAK8CHS:tau3")>0 && itJet->userFloat("NjettinessAK8CHS:tau2")>0 && itJet->userFloat("NjettinessAK8CHS:tau1")>0 && (itJet->userFloat("NjettinessAK8CHS:tau3")/itJet->userFloat("NjettinessAK8CHS:tau2"))<0.86 && 110<itJet->userFloat("ak8PFJetsCHSSoftDropMass") && itJet->userFloat("ak8PFJetsCHSSoftDropMass")<210 && itJet->pt()>400){
                    if (itJet->pt()>top_pt_max){
                        top=*itJet;
                        top_pt_max=itJet->pt();
                        top_candidatefound=true;
                        vars.FillVar("Top_candidates_pt",top_pt_max);
                    }
                    double max_subjet_csv_v2=-10;
                    auto const & names = itJet->subjets("SoftDrop");
                    for( auto const & itsubJet : names ){
                        if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>max_subjet_csv_v2){
                        max_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
                        }
                    }   
                    if (max_subjet_csv_v2>0.8 && itJet->pt()>top_withbtag_pt_max){
                        top_withbtag=*itJet;
                        top_withbtag_candidatefound=true;
                        top_withbtag_pt_max= itJet->pt();
                        vars.FillVar("Top_candidates_withbtag_pt",top_withbtag_pt_max);
                    }
                    
                }
                else if (itJet->pt()>400){
                    if (itJet->pt()>top_anti_pt_max){
                        top_anti=*itJet;
                        top_anti_pt_max=itJet->pt();
                        top_anti_candidatefound=true;
                    }
                    double max_subjet_csv_v2=-10;
                    auto const & names = itJet->subjets("SoftDrop");
                    for( auto const & itsubJet : names ){
                        if (itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>max_subjet_csv_v2){
                        max_subjet_csv_v2=itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
                        }
                    }
                    if (max_subjet_csv_v2<0.8 && itJet->pt()>top_withbtag_anti_pt_max){
                        top_withbtag_anti=*itJet;
                        top_withbtag_anti_candidatefound=true;
                        top_withbtag_anti_pt_max= itJet->pt();
                        vars.FillVar("Top_candidates_withbtag_anti_pt",top_withbtag_anti_pt_max);
                    }
                }
                    
//W candidates
                if (itJet->userFloat("NjettinessAK8CHS:tau3")>0 && itJet->userFloat("NjettinessAK8CHS:tau2")>0 && itJet->userFloat("NjettinessAK8CHS:tau1")>0 && itJet->userFloat("NjettinessAK8CHS:tau3")/itJet->userFloat("NjettinessAK8CHS:tau2")<0.6 && 70<itJet->userFloat("ak8PFJetsCHSSoftDropMass") && itJet->userFloat("ak8PFJetsCHSSoftDropMass")<100 && itJet->pt()>W_pt_max){
                    W=*itJet;
                    W_candidatefound=true;
                    W_pt_max=itJet->pt();
                    vars.FillVar("W_candidates_pt",W_pt_max);
                }
                else if (itJet->pt()>W_anti_pt_max){
                    W_anti=*itJet;
                    W_anti_candidatefound=true;
                    W_anti_pt_max=itJet->pt();
                    vars.FillVar("W_anti_candidates_pt",W_anti_pt_max);
                }
            }  
        }
    }

    
//AK4-Jets
  for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin() ; itJet != input.selectedJets.end(); ++itJet){
    int iJet = itJet - input.selectedJets.begin();
    if(input.zprimetotprimeallhad.IsFilled()){
        if (itJet->pt()>100 && abs(itJet->eta())<2.4){
            //N_AK4_bottom_misstag_candidates+=1;
            vars.FillVars("AK4_bottom_misstagged_candidates_pt",iJet,itJet->pt());
            vars.FillVars("AK4_bottom_misstagged_candidates_eta",iJet,itJet->eta());
            
            if (MiniAODHelper::GetJetCSV(*itJet,"pfCombinedInclusiveSecondaryVertexV2BJetTags")>0.800 && itJet->pt()>bottom_pt_max){
                bottom=*itJet;
                bottom_candidatefound=true;
                bottom_pt_max=itJet->pt();
                vars.FillVar("Bottom_candidates_pt",bottom.pt());
            }
            if (MiniAODHelper::GetJetCSV(*itJet,"pfCombinedInclusiveSecondaryVertexV2BJetTags")<0.800 && itJet->pt()>bottom_anti_pt_max){
                bottom_anti=*itJet;
                bottom_anti_candidatefound=true;
                bottom_anti_pt_max=itJet->pt();
                vars.FillVar("Bottom_anti_candidates_pt",bottom_anti_pt_max);
            }
        }
    }
  }

///TPrime reconstruction
  if ((top_candidatefound || top_withbtag_candidatefound) && (W_candidatefound || W_anti_candidatefound) && (bottom_candidatefound ||bottom_anti_candidatefound)){
      if (W_candidatefound && bottom_candidatefound){  /// && BoostedUtils::DeltaR(bottom.p4(),W.p4())>0.8 && BoostedUtils::DeltaR(bottom.p4(), top.p4())){
        Tprime=bottom.p4()+W.p4();
        if (Tprime.mass()>500){
            Tprime_candidatefound=true;
            vars.FillVar("Tprime_M",Tprime.mass());
            vars.FillVar("Tprime_pt",Tprime.pt());
        }      
      }      
      if (W_candidatefound && bottom_anti_candidatefound){// && BoostedUtils::DeltaR(bottom_anti.p4(),W.p4())>0.8 && BoostedUtils::DeltaR(bottom_anti.p4(), top.p4())){
        Tprime_bottom_anti=bottom_anti.p4()+W.p4();
        if (Tprime_bottom_anti.mass()>500){
            Tprime_bottom_anti_candidatefound=true;
            vars.FillVar("Tprime_bottom_anti_M",Tprime_bottom_anti.mass());
            vars.FillVar("Tprime_bottom_anti_pt",Tprime_bottom_anti.pt());
        }      
      }
      if (W_anti_candidatefound && bottom_candidatefound){// && BoostedUtils::DeltaR(bottom_anti.p4(),W.p4())>0.8 && BoostedUtils::DeltaR(bottom_anti.p4(), top.p4())){
        Tprime_W_anti=bottom.p4()+W_anti.p4();
        if (Tprime_W_anti.mass()>500){
            Tprime_W_anti_candidatefound=true;
            vars.FillVar("Tprime_W_anti_M",Tprime_W_anti.mass());
            vars.FillVar("Tprime_W_anti_pt",Tprime_W_anti.pt());
        }      
      }
      if (W_anti_candidatefound && bottom_anti_candidatefound){// && BoostedUtils::DeltaR(bottom_anti.p4(),W.p4())>0.8 && BoostedUtils::DeltaR(bottom_anti.p4(), top.p4())){
        Tprime_W_anti_bottom_anti=bottom_anti.p4()+W_anti.p4();
        if (Tprime_W_anti_bottom_anti.mass()>500){
            Tprime_W_anti_bottom_anti_candidatefound=true;
            vars.FillVar("Tprime_W_anti_bottom_anti_M",Tprime_W_anti_bottom_anti.mass());
            vars.FillVar("Tprime_W_anti_bottom_anti_pt",Tprime_W_anti_bottom_anti.pt());
        }      
      } 
  }

  
///ZPrime reconstructions
  if (top_candidatefound && Tprime_candidatefound && BoostedUtils::DeltaR(bottom.p4(),W.p4())>0.8 && BoostedUtils::DeltaR(bottom.p4(), top.p4())){
      Zprime=Tprime+top.p4();
      vars.FillVar("Zprime_M",Zprime.mass());
  }
  if (top_withbtag_candidatefound && Tprime_candidatefound && BoostedUtils::DeltaR(bottom.p4(),W.p4())>0.8 && BoostedUtils::DeltaR(bottom.p4(), top_withbtag.p4())){
      Zprime_withtopbtag=Tprime+top_withbtag.p4();
      vars.FillVar("Zprime_withtopbtag_M",Zprime_withtopbtag.mass());
  }  
  if (top_anti_candidatefound && Tprime_candidatefound && BoostedUtils::DeltaR(bottom.p4(),W.p4())>0.8 && BoostedUtils::DeltaR(bottom.p4(), top_anti.p4())){
      Zprime_top_anti=Tprime+top_anti.p4();
      vars.FillVar("Zprime_top_anti_M",Zprime_top_anti.mass());
  }
  if (top_anti_candidatefound && Tprime_bottom_anti_candidatefound && BoostedUtils::DeltaR(bottom.p4(),W_anti.p4())>0.8 && BoostedUtils::DeltaR(bottom.p4(), top_anti.p4())){
      Zprime_top_anti_W_anti=Tprime_W_anti+top_anti.p4();
      vars.FillVar("Zprime_top_anti_W_anti_M",Zprime_top_anti_W_anti.mass());
  } 
  if (top_anti_candidatefound && Tprime_bottom_anti_candidatefound && BoostedUtils::DeltaR(bottom_anti.p4(),W.p4())>0.8 && BoostedUtils::DeltaR(bottom_anti.p4(), top_anti.p4())){
      Zprime_top_anti_bottom_anti=Tprime_bottom_anti+top_anti.p4();
      vars.FillVar("Zprime_top_anti_bottom_anti_M",Zprime_top_anti_bottom_anti.mass());
  }
  if (top_anti_candidatefound && Tprime_W_anti_bottom_anti_candidatefound && BoostedUtils::DeltaR(bottom_anti.p4(),W_anti.p4())>0.8 && BoostedUtils::DeltaR(bottom_anti.p4(), top_anti.p4())){
      Zprime_top_anti_W_anti_bottom_anti=Tprime_W_anti_bottom_anti+top_anti.p4();
      vars.FillVar("Zprime_withtop_btag_M",Zprime_top_anti_W_anti_bottom_anti.mass());
  }  
  if (top_withbtag_anti_candidatefound && Tprime_candidatefound && BoostedUtils::DeltaR(bottom.p4(),W.p4())>0.8 && BoostedUtils::DeltaR(bottom.p4(), top_withbtag_anti.p4())){
      Zprime_top_withbtag_anti=Tprime+top_withbtag_anti.p4();
      vars.FillVar("Zprime_top_withbtag_anti_M",Zprime_top_withbtag_anti.mass());
  }
  if (top_withbtag_anti_candidatefound && Tprime_W_anti_candidatefound && BoostedUtils::DeltaR(bottom.p4(),W_anti.p4())>0.8 && BoostedUtils::DeltaR(bottom.p4(), top_withbtag_anti.p4())){
      Zprime_top_withbtag_anti_W_anti=Tprime_W_anti+top_withbtag_anti.p4();
      vars.FillVar("Zprime_top_withbtag_anti_W_anti_M",Zprime_top_withbtag_anti_W_anti.mass());
  } 
  if (top_withbtag_anti_candidatefound && Tprime_bottom_anti_candidatefound && BoostedUtils::DeltaR(bottom_anti.p4(),W.p4())>0.8 && BoostedUtils::DeltaR(bottom_anti.p4(), top_withbtag_anti.p4())){
      Zprime_top_withbtag_anti_bottom_anti=Tprime_bottom_anti+top_withbtag_anti.p4();
      vars.FillVar("Zprime_top_withbtag_anti_bottom_anti_M",Zprime_top_withbtag_anti_bottom_anti.mass());
  }
  if (top_withbtag_anti_candidatefound && Tprime_W_anti_bottom_anti_candidatefound && BoostedUtils::DeltaR(bottom_anti.p4(),W.p4())>0.8 && BoostedUtils::DeltaR(bottom_anti.p4(), top_withbtag_anti.p4())){
      Zprime_top_withbtag_anti_W_anti_bottom_anti=Tprime_W_anti_bottom_anti+top_withbtag_anti.p4();
      vars.FillVar("Zprime_top_withbtag_anti_W_anti_bottom_anti_M",Zprime_top_withbtag_anti_W_anti_bottom_anti.mass());
  }  
  if (top_candidatefound && Tprime_W_anti_candidatefound && BoostedUtils::DeltaR(bottom.p4(),W_anti.p4())>0.8 && BoostedUtils::DeltaR(bottom.p4(), top.p4())){
      Zprime_W_anti=Tprime_bottom_anti+top.p4();
      vars.FillVar("Zprime_W_anti_M",Zprime_W_anti.mass());
  }
  if (top_withbtag_candidatefound && Tprime_bottom_anti_candidatefound && BoostedUtils::DeltaR(bottom.p4(),W_anti.p4())>0.8 && BoostedUtils::DeltaR(bottom.p4(), top_withbtag.p4())){
      Zprime_withtopbtag_W_anti=Tprime_W_anti+top_withbtag.p4();
      vars.FillVar("Zprime_withtopbtag_W_anti_M",Zprime_withtopbtag_W_anti.mass());
  } 
  if (top_candidatefound && Tprime_bottom_anti_candidatefound && BoostedUtils::DeltaR(bottom_anti.p4(),W.p4())>0.8 && BoostedUtils::DeltaR(bottom_anti.p4(), top.p4())){
      Zprime_bottom_anti=Tprime_bottom_anti+top.p4();
      vars.FillVar("Zprime_bottom_anti_M",Zprime_bottom_anti.mass());
  }
  if (top_withbtag_candidatefound && Tprime_bottom_anti_candidatefound && BoostedUtils::DeltaR(bottom_anti.p4(),W.p4())>0.8 && BoostedUtils::DeltaR(bottom_anti.p4(), top_withbtag.p4())){
      Zprime_withtopbtag_bottom_anti=Tprime_bottom_anti+top_withbtag.p4();
      vars.FillVar("Zprime_withtopbtag_bottom_anti_M",Zprime_withtopbtag_bottom_anti.mass());
  }  
  if (top_candidatefound && Tprime_W_anti_bottom_anti_candidatefound && BoostedUtils::DeltaR(bottom_anti.p4(),W_anti.p4())>0.8 && BoostedUtils::DeltaR(bottom_anti.p4(), top.p4())){
      Zprime_W_anti_bottom_anti=Tprime_W_anti_bottom_anti+top.p4();
      vars.FillVar("Zprime_W_anti_bottom_anti_M",Zprime_W_anti_bottom_anti.mass());
  }
  if (top_withbtag_candidatefound && Tprime_W_anti_bottom_anti_candidatefound && BoostedUtils::DeltaR(bottom_anti.p4(),W_anti.p4())>0.8 && BoostedUtils::DeltaR(bottom_anti.p4(), top_withbtag.p4())){
      Zprime_withtopbtag_W_anti_bottom_anti=Tprime_W_anti_bottom_anti+top_withbtag.p4();
      vars.FillVar("Zprime_withtopbtag_W_anti_bottom_anti_M",Zprime_withtopbtag_W_anti_bottom_anti.mass());
  } 
///Background estimation



///Misstag rate & tag efficiency

  
  if (input.zprimetotprimeallhad.IsFilled() && input.packedPatJetsAK8PFCHSSoftDrop.size()>0){
    for(std::vector<pat::Jet>::const_iterator itJet=input.packedPatJetsAK8PFCHSSoftDrop.begin(); itJet != input.packedPatJetsAK8PFCHSSoftDrop.end(); ++itJet){
        int iJet = itJet - input.selectedJets.begin();

        
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
                if(Dr_TopZprime_temp<abs(minDr_TopZprime)){
                    minDr_TopZprime = Dr_TopZprime_temp;
                }
        }
        for(size_t j=0;j<bfromTPrime.size();j++){   
            float Dr_B_temp = BoostedUtils::DeltaR(bfromTPrime[j].p4(),itJet->p4());
                if(Dr_B_temp<abs(minDr_bfromTPrime)){
                    minDr_bfromTPrime = Dr_B_temp;
                }
        }        
        for(size_t j=0;j<WfromTPrime.size();j++){
            float Dr_W_temp = BoostedUtils::DeltaR(WfromTPrime[j].p4(),itJet->p4());
                if(Dr_W_temp<abs(minDr_WfromTPrime)){
                    minDr_WfromTPrime = Dr_W_temp;
                }            
        }
        for(size_t j=0;j<TopBG.size();j++){
            float Dr_TopBG_temp = BoostedUtils::DeltaR(TopBG[j].p4(),itJet->p4());
                if(Dr_TopBG_temp<abs(minDr_TopBG)){
                    minDr_TopBG = Dr_TopBG_temp;
                }
        }         
        for(size_t j=0;j<BottomBG.size();j++){
            float Dr_BottomBG_temp = BoostedUtils::DeltaR(BottomBG[j].p4(),itJet->p4());
                if(Dr_BottomBG_temp<abs(minDr_BottomBG)){
                    minDr_BottomBG = Dr_BottomBG_temp;
                }
        }
        for(size_t j=0;j<WBG.size();j++){
            float Dr_WBG_temp = BoostedUtils::DeltaR(WBG[j].p4(),itJet->p4());
                if(Dr_WBG_temp<abs(minDr_WBG)){
                    minDr_WBG = Dr_WBG_temp;
                }
        }
        
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
                
                if(itJet->userFloat("NjettinessAK8CHS:tau3")>0 && itJet->userFloat("NjettinessAK8CHS:tau2")>0 && itJet->userFloat("NjettinessAK8CHS:tau1")>0 && itJet->userFloat("NjettinessAK8CHS:tau3")/itJet->userFloat("NjettinessAK8CHS:tau2")<0.6 && 70<itJet->userFloat("ak8PFJetsCHSSoftDropMass") && itJet->userFloat("ak8PFJetsCHSSoftDropMass")<100 && minDr_WBG>0.4 && minDr_WfromTPrime>0.4){
                    misstagged_W.push_back(*itJet);
                    //vars.FillVars("misstagged_W_pt",iJet,itJet->pt());
                    //vars.FillVars("misstagged_W_eta",iJet,itJet->eta());
                }
                
                if (itJet->pt()>400){
                    AK8_top_candidates.push_back(*itJet);
                    //vars.FillVars("AK8_top_misstagged_candidates_pt",iJet,itJet->pt());
                    //vars.FillVars("AK8_top_misstagged_candidates_eta",iJet,itJet->eta());
                    if (minDr_TopBG>0.4 && itJet->userFloat("NjettinessAK8CHS:tau3")>0 && itJet->userFloat("NjettinessAK8CHS:tau2")>0 && itJet->userFloat("NjettinessAK8CHS:tau1")>0 && itJet->userFloat("NjettinessAK8CHS:tau3")/itJet->userFloat("NjettinessAK8CHS:tau2")<0.86 && 110<itJet->userFloat("ak8PFJetsCHSSoftDropMass") && itJet->userFloat("ak8PFJetsCHSSoftDropMass")<210 && minDr_TopBG>0.4 && minDr_TopZprime>0.4){
                        misstagged_top.push_back(*itJet);
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
                            //vars.FillVars("misstagged_top_withbtag_pt",iJet,itJet->pt());
                            //vars.FillVars("misstagged_top_withbtag_eta",iJet,itJet->eta());
                        }
                    }
                }   
        }
    }
  }

  for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin() ; itJet != input.selectedJets.end(); ++itJet){
    int iJet = itJet - input.selectedJets.begin();
    if(input.zprimetotprimeallhad.IsFilled()){
        float minDr_bfromTPrime = 999;    
        float minDr_bfromBG = 999;
        if (itJet->pt()>100 && abs(itJet->eta())<2.4){
            //N_AK4_bottom_misstag_candidates+=1;
            AK4_bottom_candidates.push_back(*itJet);
            //vars.FillVars("AK4_bottom_misstagged_candidates_pt",iJet,itJet->pt());
            //vars.FillVars("AK4_bottom_misstagged_candidates_eta",iJet,itJet->eta());
            
            for(size_t j=0;j<bfromTPrime.size();j++){   
                float Dr_B_temp = BoostedUtils::DeltaR(bfromTPrime[j].p4(),itJet->p4());
                if(Dr_B_temp<minDr_bfromTPrime){
                    minDr_bfromTPrime = Dr_B_temp;
                }
            }        
            for(size_t j=0;j<BottomBG.size();j++){   
                float Dr_B_temp = BoostedUtils::DeltaR(BottomBG[j].p4(),itJet->p4());
                if(Dr_B_temp<minDr_bfromBG){
                    minDr_bfromBG = Dr_B_temp;
                }
            }
            if(minDr_bfromTPrime<999) vars.FillVars("Jet_Dr_bfromTPrime",iJet,minDr_bfromTPrime);
            if(minDr_bfromBG<999) vars.FillVars("Jet_Dr_bfromBG",iJet,minDr_bfromBG);
            
            if (minDr_bfromBG>0.2 && minDr_bfromTPrime>0.2 && itJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>0.8){
                misstagged_bottom.push_back(*itJet);
                //vars.FillVars("misstagged_bottom_pt",iJet,itJet->pt());
                //vars.FillVars("misstagged_bottom_eta",iJet,itJet->eta());
            }
        }
    }
  }
  
  vars.FillVar("N_AK8_top_misstag_candidates",AK8_top_candidates.size());
  vars.FillVar("N_AK8_W_misstag_candidates",AK8_W_candidates.size());
  vars.FillVar("N_AK4_bottom_misstag_candidates",AK4_bottom_candidates.size()); 
  vars.FillVar("N_misstagged_top",misstagged_top.size());
  vars.FillVar("N_misstagged_top_withbtag",misstagged_top_withbtag.size());
  vars.FillVar("N_misstagged_W",misstagged_W.size()); 
  vars.FillVar("N_misstagged_bottom",misstagged_bottom.size());

  for(std::vector<pat::Jet>::const_iterator itJet = AK8_top_candidates.begin() ; itJet != AK8_top_candidates.end(); ++itJet){
    int iJet = itJet - AK8_top_candidates.begin();
    vars.FillVars("AK8_top_misstagged_candidates_pt",iJet,itJet->pt());
    vars.FillVars("AK8_top_misstagged_candidates_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = AK8_W_candidates.begin() ; itJet != AK8_W_candidates.end(); ++itJet){
    int iJet = itJet - AK8_W_candidates.begin();
    vars.FillVars("AK8_W_misstagged_candidates_pt",iJet,itJet->pt());
    vars.FillVars("AK8_W_misstagged_candidates_eta",iJet,itJet->eta());
  }
  for(std::vector<pat::Jet>::const_iterator itJet = AK4_bottom_candidates.begin() ; itJet != AK4_bottom_candidates.end(); ++itJet){
    int iJet = itJet - AK4_bottom_candidates.begin();
    vars.FillVars("AK4_bottom_misstagged_candidates_pt",iJet,itJet->pt());
    vars.FillVars("AK4_bottom_misstagged_candidates_eta",iJet,itJet->eta());
  }  
  
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

  ///Background estimation
  
  
 }// end of HT if
  
}
