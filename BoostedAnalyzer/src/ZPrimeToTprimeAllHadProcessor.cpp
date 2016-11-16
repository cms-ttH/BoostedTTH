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
    
    
    vars.InitVar("N_selectedPatJetsAK8PFCHS","I");
    vars.InitVars("selectedPatJetsAK8PFCHS_Pt",-9,"N_selectedPatJetsAK8PFCHS");
    vars.InitVars("selectedPatJetsAK8PFCHS_Eta",-9,"N_selectedPatJetsAK8PFCHS");
    vars.InitVars("selectedPatJetsAK8PFCHS_Phi",-9,"N_selectedPatJetsAK8PFCHS");
    vars.InitVars("selectedPatJetsAK8PFCHS_E",-9,"N_selectedPatJetsAK8PFCHS");
    vars.InitVars("selectedPatJetsAK8PFCHS_M",-9,"N_selectedPatJetsAK8PFCHS");
    vars.InitVars("NjettinessAK8CHS_tau1",-9,"N_selectedPatJetsAK8PFCHS");
    vars.InitVars("NjettinessAK8CHS_tau2",-9,"N_selectedPatJetsAK8PFCHS");
    vars.InitVars("NjettinessAK8CHS_tau3",-9,"N_selectedPatJetsAK8PFCHS");
    
    vars.InitVars("softDropMassAK8CHS",-9,"N_selectedPatJetsAK8PFCHS");
    vars.InitVars("cmsTopTagPFJetsCHSMassAK8",-9,"N_selectedPatJetsAK8PFCHS");
    
    //vars.InitVars("subjetCSVv2",-9,"N_selectedPatJetsAK8PFCHS");


    
    vars.InitVar("N_selectedPatJetsAK8PFCHSSoftDropPacked","I");
    vars.InitVar("N_packedPatJetsAK8PFCHSSoftDrop","I");
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
    
    vars.InitVars("selectedPatJetsAK8PFCHS_Dr_Top",-9.,"N_selectedPatJetsAK8PFCHS");
    vars.InitVars("selectedPatJetsAK8PFCHS_Dr_GenB_Top",-9.,"N_selectedPatJetsAK8PFCHS");
    vars.InitVars("selectedPatJetsAK8PFCHS_Dr_GenW_Top",-9.,"N_selectedPatJetsAK8PFCHS");
    vars.InitVars("selectedPatJetsAK8PFCHS_Dr_bfromTPrime",-9.,"N_selectedPatJetsAK8PFCHS");
    vars.InitVars("selectedPatJetsAK8PFCHS_Dr_GenTop_bfromTPrime",-9.,"N_selectedPatJetsAK8PFCHS");
    vars.InitVars("selectedPatJetsAK8PFCHS_Dr_GenWfromTPrime_bfromTPrime",-9.,"N_selectedPatJetsAK8PFCHS");
    vars.InitVars("selectedPatJetsAK8PFCHS_Dr_WfromTPrime",-9.,"N_selectedPatJetsAK8PFCHS");
    vars.InitVars("selectedPatJetsAK8PFCHS_Dr_GenTop_WfromTPrime",-9.,"N_selectedPatJetsAK8PFCHS");
    vars.InitVars("selectedPatJetsAK8PFCHS_Dr_GenbfromTPrime_WfromTPrime",-9.,"N_selectedPatJetsAK8PFCHS");
    
    vars.InitVars("selectedPatJetsAK8PFCHS_Dr_TopBG",-9.,"N_selectedPatJetsAK8PFCHS");
    vars.InitVars("selectedPatJetsAK8PFCHS_Dr_WBG",-9.,"N_selectedPatJetsAK8PFCHS");
    vars.InitVars("selectedPatJetsAK8PFCHS_Dr_BottomBG",-9.,"N_selectedPatJetsAK8PFCHS");

    
    
    
  vars.InitVars("Jet_Dr_bfromTPrime",-9.,"N_Jets");
  vars.InitVars("Jet_Dr_bfromBG",-9.,"N_Jets");    
    
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

    vars.FillVar("N_selectedPatJetsAK8PFCHS", input.selectedPatJetsAK8PFCHS.size());
    
    vars.FillVar("N_selectedPatJetsAK8PFCHSSoftDropPacked", input.selectedPatJetsAK8PFCHSSoftDropPacked.size());
    vars.FillVar("N_packedPatJetsAK8PFCHSSoftDrop", input.packedPatJetsAK8PFCHSSoftDrop.size());

  
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
    if(input.selectedPatJetsAK8PFCHS.size()>0){
        
        
        for(std::vector<pat::Jet>::const_iterator itJet=input.selectedPatJetsAK8PFCHS.begin(); itJet != input.selectedPatJetsAK8PFCHS.end(); ++itJet){
            int iJet = itJet - input.selectedPatJetsAK8PFCHS.begin();

            vars.FillVars("selectedPatJetsAK8PFCHS_E",iJet,itJet->energy());
            vars.FillVars("selectedPatJetsAK8PFCHS_M",iJet,itJet->mass());
            vars.FillVars("selectedPatJetsAK8PFCHS_Pt",iJet,itJet->pt());
            vars.FillVars("selectedPatJetsAK8PFCHS_Phi",iJet,itJet->phi());
            vars.FillVars("selectedPatJetsAK8PFCHS_Eta",iJet,itJet->eta());

            //vars.FillVars("cmsTopTagPFJetsCHSMassAK8",iJet, itJet->userFloat("cmsTopTagPFJetsCHSMassAK8"));           
            vars.FillVars("softDropMassAK8CHS",iJet, itJet->userFloat("ak8PFJetsCHSSoftDropMass"));
            //std::cout<<"softDropMassAK8CHS of Jet"<<iJet<<": "<<itJet->userFloat("ak8PFJetsCHSSoftDropMass")<<endl;
            //std::cout<<"test "<<iJet<<": "<<itJet->userFloat("")<<endl;
            //std::cout<<"Njettiness_tau1 of Jet"<<iJet<<": "<<itJet->userFloat("NjettinessAK8CHS:tau1")<<endl;
            vars.FillVars("NjettinessAK8CHS_tau1",iJet,itJet->userFloat("NjettinessAK8CHS:tau1"));
            vars.FillVars("NjettinessAK8CHS_tau2",iJet,itJet->userFloat("NjettinessAK8CHS:tau2"));
            vars.FillVars("NjettinessAK8CHS_tau3",iJet,itJet->userFloat("NjettinessAK8CHS:tau3"));
            //std::cout<<"Jet "<<iJet<<":"<<itJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTagsAK8PFCHS")<<endl;

                            //std::cout<<"# of SubjetCollectionNames: "<<itJet->numberOfDaughters()<<endl;

            auto const & names = itJet->subjetCollectionNames();
            for( auto const & iti : names ){
                std::cout<<"SubjetNames: "<<iti<<endl;

            }
            //for ( std::vector< std::string>::const_iterator iti = itJet->subjetCollectionNames().begin(); iti != itJet->subjetCollectionNames().end(); ++iti){
                
            //    std::cout<<"SubjetNames: "<<std::to_string(iti)<<endl;
            //}
            //TLorentzVector CHS_softdrop, CHS_softdrop_subjet;
            //std::cout<<"adsasdasd"<<itJet->subjets("SoftDrop").size()<<endl;
            //auto const & sdSubjetsCHS = itJet->subjets("SoftDrop");
            //for ( auto const & it : sdSubjetsCHS ) {
            //    CHS_softdrop_subjet.SetPtEtaPhiM(it->pt(),it->eta(),it->phi(),it->mass());
            //    CHS_softdrop+=CHS_softdrop_subjet;
            //}
            
        }
        
    
  //std::cout<<input.selectedPatJetsAK8PFCHSSoftDropPacked.size()<<endl;
    std::cout<<"selectedPatJetsAK8PFCHSSoftDropPacked: "<<input.selectedPatJetsAK8PFCHSSoftDropPacked.size()<<endl;
    for( std::vector<pat::Jet>::const_iterator itsubJet=input.selectedPatJetsAK8PFCHSSoftDropPacked.begin(); itsubJet!= input.selectedPatJetsAK8PFCHSSoftDropPacked.end(); ++itsubJet){
        int isubJet = itsubJet - input.selectedPatJetsAK8PFCHSSoftDropPacked.begin();
        std::cout<<"selectedPatJetsAK8PFCHSSoftDropPacked "<<isubJet<<":"<<itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTagsAK8PFCHSSoftDropSubjets")<<endl;
        std::cout<<"selectedPatJetsAK8PFCHSSoftDropPacked "<<isubJet<<" # of subjets:"<<itsubJet->nSubjetCollections()<<endl;

                            std::cout<<"# of daughters: "<<itsubJet->numberOfDaughters()<<endl;
            auto const & names = itsubJet->subjetCollectionNames();
            for( auto const & iti : names ){
                std::cout<<"SubjetNames: "<<iti<<endl;
            }
            
    }
    /*
    std::cout<<"selectedPatJetsAK8PFCHSSoftDropSubjets: "<<input.selectedPatJetsAK8PFCHSSoftDropSubjets.size()<<endl;
    
    std::cout<<"packedPatJetsAK8PFCHSSoftDrop: "<<input.packedPatJetsAK8PFCHSSoftDrop.size()<<endl;
    for( std::vector<pat::Jet>::const_iterator itsubJet=input.packedPatJetsAK8PFCHSSoftDrop.begin(); itsubJet!= input.packedPatJetsAK8PFCHSSoftDrop.end(); ++itsubJet){
        int isubJet = itsubJet - input.packedPatJetsAK8PFCHSSoftDrop.begin();
        std::cout<<"packedPatJetsAK8PFCHSSoftDrop CSV V2"<<isubJet<<":"<<itsubJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTagsAK8PFCHSSoftDropSubjets")<<endl;
        std::cout<<"packedPatJetsAK8PFCHSSoftDrop "<<isubJet<<" # of subjets:"<<itsubJet->nSubjetCollections()<<endl;

            std::cout<<"# of daughters: "<<itsubJet->numberOfDaughters()<<endl;
            auto const & names = itsubJet->subjetCollectionNames();
            for( auto const & iti : names ){
                std::cout<<"SubjetNames: "<<iti<<endl;
            }
            
    }
    
    std::cout<<"selectedPatJetsAK8PFCHSSoftDropSubjets: "<<input.selectedPatJetsAK8PFCHSSoftDropSubjets.size()<<endl;
    */

    
    for(size_t i=0; i< input.selectedPatJetsAK8PFCHS.size(); i++){
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

        //if(input.selectedPatJetsAK8PFCHS[i].Pt()>100){
        //cout<<"Topsize:  "<<Top.size()<<endl;
        for(size_t j=0;j<TopZprime.size();j++){
            float Dr_TopZprime_temp = BoostedUtils::DeltaR(TopZprime[j].p4(),input.selectedPatJetsAK8PFCHS[i].p4());
                if(Dr_TopZprime_temp<abs(minDr_TopZprime)){
                    minDr_TopZprime = Dr_TopZprime_temp;
                    //cout<<"minDr_Top:  "<<minDr_Top<<endl;
//                    minDr_GenB_Top = BoostedUtils::DeltaR(bfromTPrime[j].p4(),input.selectedPatJetsAK8PFCHS[i].p4());
//                    minDr_GenW_Top = BoostedUtils::DeltaR(WfromTPrime[j].p4(),input.selectedPatJetsAK8PFCHS[i].p4());
//                    cout<<"minDr_GenW_Top:  "<<minDr_GenW_Top<<endl;
                }
        }
        for(size_t j=0;j<bfromTPrime.size();j++){   
            float Dr_B_temp = BoostedUtils::DeltaR(bfromTPrime[j].p4(),input.selectedPatJetsAK8PFCHS[i].p4());
                if(Dr_B_temp<abs(minDr_bfromTPrime)){
                    minDr_bfromTPrime = Dr_B_temp;
                    //cout<<"minDr_bfromTPrime:  "<<minDr_bfromTPrime<<endl;
//                    minDr_GenTop_bfromTPrime = BoostedUtils::DeltaR(Top[j].p4(),input.selectedPatJetsAK8PFCHS[i].p4());
//                    minDr_GenWfromTPrime_bfromTPrime = BoostedUtils::DeltaR(WfromTPrime[j].p4(),input.selectedPatJetsAK8PFCHS[i].p4());
                }
        }        
        for(size_t j=0;j<WfromTPrime.size();j++){
            float Dr_W_temp = BoostedUtils::DeltaR(WfromTPrime[j].p4(),input.selectedPatJetsAK8PFCHS[i].p4());
                if(Dr_W_temp<abs(minDr_WfromTPrime)){
                    minDr_WfromTPrime = Dr_W_temp;
                    //cout<<"minDr_WfromTPrime:  "<<minDr_WfromTPrime<<endl;
//                    minDr_GenbfromTPrime_WfromTPrime = BoostedUtils::DeltaR(bfromTPrime[j].p4(),input.selectedPatJetsAK8PFCHS[i].p4());
//                    minDr_GenTop_WfromTPrime = BoostedUtils::DeltaR(Top[j].p4(),input.selectedPatJetsAK8PFCHS[i].p4());
                }            
        
        }
        for(size_t j=0;j<TopBG.size();j++){
            float Dr_TopBG_temp = BoostedUtils::DeltaR(TopBG[j].p4(),input.selectedPatJetsAK8PFCHS[i].p4());
                if(Dr_TopBG_temp<abs(minDr_TopBG)){
                    minDr_TopBG = Dr_TopBG_temp;
                }
        }         
        for(size_t j=0;j<BottomBG.size();j++){
            float Dr_BottomBG_temp = BoostedUtils::DeltaR(BottomBG[j].p4(),input.selectedPatJetsAK8PFCHS[i].p4());
                if(Dr_BottomBG_temp<abs(minDr_BottomBG)){
                    minDr_BottomBG = Dr_BottomBG_temp;
                }
        }
        for(size_t j=0;j<WBG.size();j++){
            float Dr_WBG_temp = BoostedUtils::DeltaR(WBG[j].p4(),input.selectedPatJetsAK8PFCHS[i].p4());
                if(Dr_WBG_temp<abs(minDr_WBG)){
                    minDr_WBG = Dr_WBG_temp;
                }
        }
        
        if(abs(minDr_TopZprime)<999) vars.FillVars("selectedPatJetsAK8PFCHS_Dr_Top",i,minDr_TopZprime);
        if(abs(minDr_GenB_Top)<999) vars.FillVars("selectedPatJetsAK8PFCHS_Dr_GenB_Top",i,minDr_GenB_Top);
        if(abs(minDr_GenW_Top)<999) vars.FillVars("selectedPatJetsAK8PFCHS_Dr_GenW_Top",i,minDr_GenW_Top);
        if(abs(minDr_bfromTPrime)<999) vars.FillVars("selectedPatJetsAK8PFCHS_Dr_bfromTPrime",i,minDr_bfromTPrime);
        if(abs(minDr_GenTop_bfromTPrime)<999) vars.FillVars("selectedPatJetsAK8PFCHS_Dr_GenTop_bfromTPrime",i,minDr_GenTop_bfromTPrime);
        if(abs(minDr_GenWfromTPrime_bfromTPrime)<999) vars.FillVars("selectedPatJetsAK8PFCHS_Dr_GenWfromTPrime_bfromTPrime",i,minDr_GenWfromTPrime_bfromTPrime);
        if(abs(minDr_WfromTPrime)<999) vars.FillVars("selectedPatJetsAK8PFCHS_Dr_WfromTPrime",i,minDr_WfromTPrime);
        if(abs(minDr_GenTop_WfromTPrime)<999) vars.FillVars("selectedPatJetsAK8PFCHS_Dr_GenTop_WfromTPrime",i,minDr_GenTop_WfromTPrime);
        if(abs(minDr_GenbfromTPrime_WfromTPrime)<999) vars.FillVars("selectedPatJetsAK8PFCHS_Dr_GenbfromTPrime_WfromTPrime",i,minDr_GenbfromTPrime_WfromTPrime);        
        if(abs(minDr_TopBG)<999) vars.FillVars("selectedPatJetsAK8PFCHS_Dr_TopBG",i,minDr_TopBG);
        if(abs(minDr_BottomBG)<999) vars.FillVars("selectedPatJetsAK8PFCHS_Dr_BottomBG",i,minDr_BottomBG);
        if(abs(minDr_WBG)<999) vars.FillVars("selectedPatJetsAK8PFCHS_Dr_WBG",i,minDr_WBG);

        //}


    }

    }
  vector<math::XYZTLorentzVector> jetvecs = BoostedUtils::GetJetVecs(input.selectedJets);
  for(size_t i=0; i<jetvecs.size(); i++){
    if(input.zprimetotprimeallhad.IsFilled()){
//        float minDr_GenB_ZTop = 999;
//        float minDr_GenW_ZTop = 999;
        float minDr_bfromTPrime = 999;
//        float minDr_GenZTop_bfromTPrime=999;
//        float minDr_GenWfromTPrime_bfromTPrime=999;
//        float minDr_WfromTPrime = 999;
//        float minDr_GenZTop_WfromTPrime=999;
//        float minDr_GenbfromTPrime_WfromTPrime=999;        
        float minDr_bfromBG = 999;

        
        for(size_t j=0;j<bfromTPrime.size();j++){   
            float Dr_B_temp = BoostedUtils::DeltaR(bfromTPrime[j].p4(),jetvecs[i]);
                if(Dr_B_temp<minDr_bfromTPrime){
                    minDr_bfromTPrime = Dr_B_temp;
                    cout<<"minDr_bfromTPrime:  "<<minDr_bfromTPrime<<endl;
                }
        }        
        for(size_t j=0;j<bfromTPrime.size();j++){   
            float Dr_B_temp = BoostedUtils::DeltaR(bfromTPrime[j].p4(),jetvecs[i]);
                if(Dr_B_temp<minDr_bfromBG){
                    minDr_bfromBG = Dr_B_temp;
                    cout<<"minDr_bfromBG:  "<<minDr_bfromBG<<endl;
                }
        } 
           
//        if(minDr_ZTop<999) vars.FillVars("BoostedJet_Dr_ZTop",i,minDr_ZTop);
//        if(minDr_GenB_ZTop<999) vars.FillVars("BoostedJet_Dr_GenB_ZTop",i,minDr_GenB_ZTop);
//        if(minDr_GenW_ZTop<999) vars.FillVars("BoostedJet_Dr_GenW_ZTop",i,minDr_GenW_ZTop);
        if(minDr_bfromTPrime<999) vars.FillVars("Jet_Dr_bfromTPrime",i,minDr_bfromTPrime);
        if(minDr_bfromBG<999) vars.FillVars("Jet_Dr_bfromBG",i,minDr_bfromBG);

//        if(minDr_GenZTop_bfromTPrime<999) vars.FillVars("BoostedJet_Dr_GenZTop_bfromTPrime",i,minDr_GenZTop_bfromTPrime);
//        if(minDr_GenWfromTPrime_bfromTPrime<999) vars.FillVars("BoostedJet_Dr_GenWfromTPrime_bfromTPrime",i,minDr_GenWfromTPrime_bfromTPrime);
//        if(minDr_WfromTPrime<999) vars.FillVars("BoostedJet_Dr_WfromTPrime",i,minDr_WfromTPrime);
//        if(minDr_GenZTop_WfromTPrime<999) vars.FillVars("BoostedJet_Dr_GenZTop_WfromTPrime",i,minDr_GenZTop_WfromTPrime);
//        if(minDr_GenbfromTPrime_WfromTPrime<999) vars.FillVars("BoostedJet_Dr_GenbfromTPrime_WfromTPrime",i,minDr_GenbfromTPrime_WfromTPrime);        


    }
  }

}
