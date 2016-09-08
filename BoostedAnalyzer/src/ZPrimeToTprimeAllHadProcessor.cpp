#include "BoostedTTH/BoostedAnalyzer/interface/ZPrimeToTPrimeAllHadProcessor.hpp"



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

    
    vars.InitVar("Gen_Top_TPrime_DeltaR");//,"input.zprimetotprimeallhad.GetTops().size()*input.zprimetotprimeallhad.GetTPrimebars().size()");
    vars.InitVar("Gen_Top_WfromTPrime_DeltaR");//,"input.zprimetotprimeallhad.GetTops().size()*input.zprimetotprimeallhad.GetWminus_fromTPrimes().size()");
    vars.InitVar("Gen_Top_BottomfromTPrime_DeltaR");//,"input.zprimetotprimeallhad.GetTops().size()*input.zprimetotprimeallhad.GetTPrimeDecayQuarks().size()");
    vars.InitVar("Gen_WfromTPrime_BottomfromTPrime_DeltaR");//,"input.zprimetotprimeallhad.GetWplus_fromTPrimes().size()*input.zprimetotprimeallhad.GetTPrimeDecayQuarks().size()");
    vars.InitVar("Gen_WfromTop_BottomfromTop_DeltaR");//,"input.zprimetotprimeallhad.GetWplus_fromTops().size()*input.zprimetotprimeallhad.GetTopDecayQuarks().size()");
    
    vars.InitVar("Gen_Top_WfromTPrime_DeltaEta");
    vars.InitVar("Gen_Top_BottomfromTPrime_DeltaEta");
    vars.InitVar("Gen_WfromTPrime_BottomfromTPrime_DeltaEta");
    
    vars.InitVar("Gen_Top_WfromTPrime_DeltaPhi");
    vars.InitVar("Gen_Top_BottomfromTPrime_DeltaPhi");
    vars.InitVar("Gen_WfromTPrime_BottomfromTPrime_DeltaPhi");

  initialized=true;
}

void ZPrimeToTPrimeAllHadProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << std::endl; // complain if not initialized but keep running

    vars.FillVar("N_Gen_ZPrimes", input.zprimetotprimeallhad.GetZPrimes().size());
    vars.FillVar("N_Gen_Tops", input.zprimetotprimeallhad.GetTops().size());
    vars.FillVar("N_Gen_Topbars", input.zprimetotprimeallhad.GetTopbars().size());
    vars.FillVar("N_Gen_TopsandTopbars", input.zprimetotprimeallhad.GetTopsandTopbars().size());

    vars.FillVar("N_Gen_TPrimes", input.zprimetotprimeallhad.GetTPrimes().size());
    vars.FillVar("N_Gen_TPrimebars", input.zprimetotprimeallhad.GetTPrimebars().size());
    vars.FillVar("N_Gen_TPrimesandTPrimebars", input.zprimetotprimeallhad.GetTPrimesandTPrimebars().size());

    vars.FillVar("N_Gen_WplusfromTops", input.zprimetotprimeallhad.GetWplus_fromTops().size());
    vars.FillVar("N_Gen_WminusfromTopbars", input.zprimetotprimeallhad.GetWminus_fromTops().size());
    vars.FillVar("N_Gen_WfromTopsandTopbars", input.zprimetotprimeallhad.GetW_fromTopsandTopbars().size());
    
    vars.FillVar("N_Gen_WplusfromTPrimes", input.zprimetotprimeallhad.GetWplus_fromTPrimes().size());
    vars.FillVar("N_Gen_WminusfromTPrimebars", input.zprimetotprimeallhad.GetWminus_fromTPrimes().size());
    vars.FillVar("N_Gen_WfromTPrimesandTPrimebars", input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars().size());

    vars.FillVar("N_Gen_BottomfromTops", input.zprimetotprimeallhad.GetTopDecayQuarks().size());
    vars.FillVar("N_Gen_BottombarfromTopbars", input.zprimetotprimeallhad.GetTopBarDecayQuarks().size());
    vars.FillVar("N_Gen_BottomfromTopsandTopbars", input.zprimetotprimeallhad.GetBottom_fromTopsandTopbars().size());

    vars.FillVar("N_Gen_BottomfromTPrimes", input.zprimetotprimeallhad.GetTPrimeDecayQuarks().size());
    vars.FillVar("N_Gen_BottombarfromTPrimebars", input.zprimetotprimeallhad.GetTPrimebarDecayQuarks().size());
    vars.FillVar("N_Gen_BottomfromTPrimesandTPrimebars", input.zprimetotprimeallhad.GetBottom_fromTPrimesandTPrimebars().size());

  

  
    if(input.zprimetotprimeallhad.GetTops().size()>0){
        for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetTops().begin() ; itParticle != input.zprimetotprimeallhad.GetTops().end(); ++itParticle){
        int iParticle = itParticle - input.zprimetotprimeallhad.GetTops().begin();
            vars.FillVars( "Gen_Top_Pt",iParticle,itParticle->pt() );
            vars.FillVars( "Gen_Top_Eta",iParticle,itParticle->eta() );
        }
    }
    if(input.zprimetotprimeallhad.GetTopbars().size()>0){
        for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetTopbars().begin() ; itParticle != input.zprimetotprimeallhad.GetTopbars().end(); ++itParticle){
        int iParticle = itParticle - input.zprimetotprimeallhad.GetTopbars().begin();
            vars.FillVars( "Gen_Topbar_Pt",iParticle,itParticle->pt() );
            vars.FillVars( "Gen_Topbar_Eta",iParticle,itParticle->eta() );
        }
    }
    if(input.zprimetotprimeallhad.GetTopsandTopbars().size()>0){
        for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetTopsandTopbars().begin() ; itParticle != input.zprimetotprimeallhad.GetTopsandTopbars().end(); ++itParticle){
        int iParticle = itParticle - input.zprimetotprimeallhad.GetTopsandTopbars().begin();
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
        }
    }
    if(input.zprimetotprimeallhad.GetZPrimes().size()>0){
        for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetZPrimes().begin() ; itParticle != input.zprimetotprimeallhad.GetZPrimes().end(); ++itParticle){
        int iParticle = itParticle - input.zprimetotprimeallhad.GetZPrimes().begin();
            vars.FillVars( "Gen_ZPrime_Pt",iParticle,itParticle->pt() );
            vars.FillVars( "Gen_ZPrime_Eta",iParticle,itParticle->eta() );
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
    
   
    if((input.zprimetotprimeallhad.GetTopsandTopbars().size()==1 && input.zprimetotprimeallhad.GetTPrimesandTPrimebars().size()==1)){
        float DeltaR= BoostedUtils::DeltaR(input.zprimetotprimeallhad.GetTopsandTopbars()[0].p4(),input.zprimetotprimeallhad.GetTPrimesandTPrimebars()[0].p4());
        vars.FillVar( "Gen_Top_TPrime_DeltaR", DeltaR );
    }
    if((input.zprimetotprimeallhad.GetTopsandTopbars().size()==1 && input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars().size()==1)){
        float DeltaR=BoostedUtils::DeltaR(input.zprimetotprimeallhad.GetTopsandTopbars()[0].p4(),input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars()[0].p4());
        vars.FillVar( "Gen_Top_WfromTPrime_DeltaR", DeltaR );
    }
    if((input.zprimetotprimeallhad.GetTopsandTopbars().size()==1 && input.zprimetotprimeallhad.GetTPrimeandTPrimebarDecayBottoms().size()==1)){
        float DeltaR=BoostedUtils::DeltaR(input.zprimetotprimeallhad.GetTopsandTopbars()[0].p4(),input.zprimetotprimeallhad.GetTPrimeandTPrimebarDecayBottoms()[0].p4());
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

    
    if((input.zprimetotprimeallhad.GetTopsandTopbars().size()==1 && input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars().size()==1)){
        float DeltaEta=BoostedUtils::DeltaEta(input.zprimetotprimeallhad.GetTopsandTopbars()[0].p4(),input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars()[0].p4());
        vars.FillVar( "Gen_Top_WfromTPrime_DeltaEta", DeltaEta );
    }
    if((input.zprimetotprimeallhad.GetTopsandTopbars().size()==1 && input.zprimetotprimeallhad.GetTPrimeandTPrimebarDecayBottoms().size()==1)){
        float DeltaEta=BoostedUtils::DeltaEta(input.zprimetotprimeallhad.GetTopsandTopbars()[0].p4(),input.zprimetotprimeallhad.GetTPrimeandTPrimebarDecayBottoms()[0].p4());
        vars.FillVar( "Gen_Top_BottomfromTPrime_DeltaEta", DeltaEta );
    }
    if((input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars().size()==1 && input.zprimetotprimeallhad.GetTPrimeandTPrimebarDecayBottoms().size()==1)){
        float DeltaEta=BoostedUtils::DeltaEta(input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars()[0].p4(),input.zprimetotprimeallhad.GetTPrimeandTPrimebarDecayBottoms()[0].p4());
        vars.FillVar( "Gen_WfromTPrime_BottomfromTPrime_DeltaEta", DeltaEta );
    }

    if((input.zprimetotprimeallhad.GetTopsandTopbars().size()==1 && input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars().size()==1)){
        float DeltaPhi=BoostedUtils::DeltaPhi(input.zprimetotprimeallhad.GetTopsandTopbars()[0].p4(),input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars()[0].p4());
        vars.FillVar( "Gen_Top_Wfr"omTPrime_DeltaPhi", DeltaPhi );
    }
    if((input.zprimetotprimeallhad.GetTopsandTopbars().size()==1 && input.zprimetotprimeallhad.GetTPrimeandTPrimebarDecayBottoms().size()==1)){
        float DeltaPhi=BoostedUtils::DeltaPhi(input.zprimetotprimeallhad.GetTopsandTopbars()[0].p4(),input.zprimetotprimeallhad.GetTPrimeandTPrimebarDecayBottoms()[0].p4());
        vars.FillVar( "Gen_Top_BottomfromTPrime_DeltaPhi", DeltaPhi );
    }
    if((input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars().size()==1 && input.zprimetotprimeallhad.GetTPrimeandTPrimebarDecayBottoms().size()==1)){
        float DeltaPhi=BoostedUtils::DeltaPhi(input.zprimetotprimeallhad.GetW_fromTPrimesandTPrimebars()[0].p4(),input.zprimetotprimeallhad.GetTPrimeandTPrimebarDecayBottoms()[0].p4());
        vars.FillVar( "Gen_WfromTPrime_BottomfromTPrime_DeltaPhi", DeltaPhi );
    }

    

}
