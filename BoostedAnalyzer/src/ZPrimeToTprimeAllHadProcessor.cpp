#include "BoostedTTH/BoostedAnalyzer/interface/ZPrimeToTPrimeAllHadProcessor.hpp"



// all configurations should be done in constructor
ZPrimeToTPrimeAllHadProcessor::ZPrimeToTPrimeAllHadProcessor(){}
ZPrimeToTPrimeAllHadProcessor::~ZPrimeToTPrimeAllHadProcessor(){}


void ZPrimeToTPrimeAllHadProcessor::Init(const InputCollections& input,VariableContainer& vars){
    
    vars.InitVar("N_Gen_ZPrimes","I");
    vars.InitVar("N_Gen_Tops","I");
    vars.InitVar("N_Gen_Topbars","I");
    vars.InitVar("N_Gen_TPrimes","I");
    vars.InitVar("N_Gen_TPrimebars","I");
    vars.InitVar("N_Gen_WplusfromTops","I");
    vars.InitVar("N_Gen_WminusfromTopbars","I");
    vars.InitVar("N_Gen_WplusfromTPrimes","I");
    vars.InitVar("N_Gen_WminusfromTPrimebars","I");
    vars.InitVar("N_Gen_BottomfromTops","I");
    vars.InitVar("N_Gen_BottombarfromTopbars","I");
    vars.InitVar("N_Gen_BottomfromTPrimes","I");
    vars.InitVar("N_Gen_BottombarfromTPrimebars","I");
    
    


    vars.InitVars("Gen_Top_Pt","N_Gen_Tops");
    vars.InitVars("Gen_Topbar_Pt","N_Gen_Topbars");
    vars.InitVars("Gen_ZPrime_Pt","N_Gen_ZPrimes");    
    vars.InitVars("Gen_TPrime_Pt","N_Gen_TPrimes");
    vars.InitVars("Gen_TPrimebar_Pt","N_Gen_TPrimebars");
    vars.InitVars("Gen_WplusfromTop_Pt","N_Gen_WplusfromTops");
    vars.InitVars("Gen_WminusfromTopbar_Pt","N_Gen_WminusfromTopbars");
    vars.InitVars("Gen_WplusfromTPrime_Pt","N_Gen_WplusfromTPrimes");
    vars.InitVars("Gen_WminusfromTPrimebar_Pt","N_Gen_WminusfromTPrimebars");    
    vars.InitVars("Gen_BottomfromTop_Pt","N_Gen_BottomfromTops");
    vars.InitVars("Gen_BottombarfromTopbar_Pt","N_Gen_BottombarfromTopbars");
    vars.InitVars("Gen_BottomfromTPrime_Pt","N_Gen_BottomfromTPrimes");
    vars.InitVars("Gen_BottombarfromTPrimebar_Pt","N_Gen_BottombarfromTPrimebars");
    
    vars.InitVars("Gen_Top_Eta","N_Gen_Tops");
    vars.InitVars("Gen_Topbar_Eta","N_Gen_Topbars");
    vars.InitVars("Gen_ZPrime_Eta","N_Gen_ZPrimes");    
    vars.InitVars("Gen_TPrime_Eta","N_Gen_TPrimes");
    vars.InitVars("Gen_TPrimebar_Eta","N_Gen_TPrimebars");
    vars.InitVars("Gen_WplusfromTop_Eta","N_Gen_WplusfromTops");
    vars.InitVars("Gen_WminusfromTopbar_Eta","N_Gen_WminusfromTopbars");
    vars.InitVars("Gen_WplusfromTPrime_Eta","N_Gen_WplusfromTPrimes");
    vars.InitVars("Gen_WminusfromTPrimebar_Eta","N_Gen_WminusfromTPrimebars");    
    vars.InitVars("Gen_BottomfromTop_Eta","N_Gen_BottomfromTops");
    vars.InitVars("Gen_BottombarfromTopbar_Eta","N_Gen_BottombarfromTopbars");
    vars.InitVars("Gen_BottomfromTPrime_Eta","N_Gen_BottomfromTPrimes");
    vars.InitVars("Gen_BottombarfromTPrimebar_Eta","N_Gen_BottombarfromTPrimebars");

    
    vars.InitVar("Gen_Top_TPrimebar_DeltaR");//,"input.zprimetotprimeallhad.GetTops().size()*input.zprimetotprimeallhad.GetTPrimebars().size()");
    vars.InitVar("Gen_Topbar_TPrime_DeltaR");//,"input.zprimetotprimeallhad.GetTopbars().size()*input.zprimetotprimeallhad.GetTPrimes().size()");
    vars.InitVar("Gen_Top_WfromTPrimebar_DeltaR");//,"input.zprimetotprimeallhad.GetTops().size()*input.zprimetotprimeallhad.GetWminus_fromTPrimes().size()");
    vars.InitVar("Gen_Topbar_WfromTPrime_DeltaR");//,"input.zprimetotprimeallhad.GetTopbars().size()*input.zprimetotprimeallhad.GetWplus_fromTPrimes().size()");
    vars.InitVar("Gen_Top_BottomfromTPrimebar_DeltaR");//,"input.zprimetotprimeallhad.GetTops().size()*input.zprimetotprimeallhad.GetTPrimeDecayQuarks().size()");
    vars.InitVar("Gen_Topbar_BottomfromTPrime_DeltaR");//,"input.zprimetotprimeallhad.GetTopbars().size()*input.zprimetotprimeallhad.GetTPrimebarDecayQuarks().size()");

    vars.InitVar("Gen_WfromTPrime_BottomfromTPrime_DeltaR");//,"input.zprimetotprimeallhad.GetWplus_fromTPrimes().size()*input.zprimetotprimeallhad.GetTPrimeDecayQuarks().size()");
    vars.InitVar("Gen_WfromTPrimebar_BottomfromTPrimebar_DeltaR");//,"input.zprimetotprimeallhad.GetWminus_fromTPrimes().size()*input.zprimetotprimeallhad.GetTPrimebarDecayQuarks().size()");
    vars.InitVar("Gen_WfromTop_BottomfromTop_DeltaR");//,"input.zprimetotprimeallhad.GetWplus_fromTops().size()*input.zprimetotprimeallhad.GetTopDecayQuarks().size()");
    vars.InitVar("Gen_WfromTopbar_BottomfromTopbar_DeltaR");//,"input.zprimetotprimeallhad.GetWminus_fromTops().size()*input.zprimetotprimeallhad.GetTopBarDecayQuarks().size()");


  initialized=true;
}

void ZPrimeToTPrimeAllHadProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << std::endl; // complain if not initialized but keep running

    vars.FillVar("N_Gen_ZPrimes", input.zprimetotprimeallhad.GetZPrimes().size());
    vars.FillVar("N_Gen_Tops", input.zprimetotprimeallhad.GetTops().size());
    vars.FillVar("N_Gen_Topbars", input.zprimetotprimeallhad.GetTopbars().size());
    vars.FillVar("N_Gen_TPrimes", input.zprimetotprimeallhad.GetTPrimes().size());
    vars.FillVar("N_Gen_TPrimebars", input.zprimetotprimeallhad.GetTPrimebars().size());
    vars.FillVar("N_Gen_WplusfromTops", input.zprimetotprimeallhad.GetWplus_fromTops().size());
    vars.FillVar("N_Gen_WminusfromTopbars", input.zprimetotprimeallhad.GetWminus_fromTops().size());
    vars.FillVar("N_Gen_WplusfromTPrimes", input.zprimetotprimeallhad.GetWplus_fromTPrimes().size());
    vars.FillVar("N_Gen_WminusfromTPrimebars", input.zprimetotprimeallhad.GetWminus_fromTPrimes().size());
    vars.FillVar("N_Gen_BottomfromTops", input.zprimetotprimeallhad.GetTopDecayQuarks().size());
    vars.FillVar("N_Gen_BottombarfromTopbars", input.zprimetotprimeallhad.GetTopBarDecayQuarks().size());
    vars.FillVar("N_Gen_BottomfromTPrimes", input.zprimetotprimeallhad.GetTPrimeDecayQuarks().size());
    vars.FillVar("N_Gen_BottombarfromTPrimebars", input.zprimetotprimeallhad.GetTPrimebarDecayQuarks().size());

  

  
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
    if(input.zprimetotprimeallhad.GetTopDecayQuarks().size()>0){
        for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetTopDecayQuarks().begin() ; itParticle != input.zprimetotprimeallhad.GetTopDecayQuarks().end(); ++itParticle){
            int iParticle = itParticle - input.zprimetotprimeallhad.GetTopDecayQuarks().begin();
            if(abs(itParticle->pdgId())==5){
                vars.FillVars( "Gen_BottomfromTop_Pt",iParticle,itParticle->pt() );
                vars.FillVars( "Gen_BottomfromTop_Eta",iParticle,itParticle->eta() );
            }
        }
    }
    if(input.zprimetotprimeallhad.GetTopBarDecayQuarks().size()>0){
        for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetTopBarDecayQuarks().begin() ; itParticle != input.zprimetotprimeallhad.GetTopBarDecayQuarks().end(); ++itParticle){
            int iParticle = itParticle - input.zprimetotprimeallhad.GetTopBarDecayQuarks().begin();
            if(abs(itParticle->pdgId())==5){
                vars.FillVars( "Gen_BottombarfromTopbar_Pt",iParticle,itParticle->pt() );
                vars.FillVars( "Gen_BottombarfromTopbar_Eta",iParticle,itParticle->eta() );
            }
        }
    }
    if(input.zprimetotprimeallhad.GetTPrimeDecayQuarks().size()>0){
        for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetTPrimeDecayQuarks().begin() ; itParticle != input.zprimetotprimeallhad.GetTPrimeDecayQuarks().end(); ++itParticle){
            int iParticle = itParticle - input.zprimetotprimeallhad.GetTPrimeDecayQuarks().begin();
            if(abs(itParticle->pdgId())==5){
                vars.FillVars( "Gen_BottomfromTPrime_Pt",iParticle,itParticle->pt() );
                vars.FillVars( "Gen_BottomfromTPrime_Eta",iParticle,itParticle->eta() );
            }
        }
    }
    if(input.zprimetotprimeallhad.GetTPrimebarDecayQuarks().size()>0){
        for(std::vector<reco::GenParticle>::const_iterator itParticle = input.zprimetotprimeallhad.GetTPrimebarDecayQuarks().begin() ; itParticle != input.zprimetotprimeallhad.GetTPrimebarDecayQuarks().end(); ++itParticle){
            int iParticle = itParticle - input.zprimetotprimeallhad.GetTPrimebarDecayQuarks().begin();
            if(abs(itParticle->pdgId())==5){
                vars.FillVars( "Gen_BottombarfromTPrimebar_Pt",iParticle,itParticle->pt() );
                vars.FillVars( "Gen_BottombarfromTPrimebar_Eta",iParticle,itParticle->eta() );
            }
        }
    }
    
   
    if((input.zprimetotprimeallhad.GetTops().size()==1 && input.zprimetotprimeallhad.GetTPrimebars().size()==1)){
        float DeltaR= BoostedUtils::DeltaR(input.zprimetotprimeallhad.GetTops()[0].p4(),input.zprimetotprimeallhad.GetTPrimebars()[0].p4());
        vars.FillVar( "Gen_Top_TPrimebar_DeltaR", DeltaR );
    }
    if((input.zprimetotprimeallhad.GetTopbars().size()==1 && input.zprimetotprimeallhad.GetTPrimes().size()==1)){
        float DeltaR=BoostedUtils::DeltaR(input.zprimetotprimeallhad.GetTopbars()[0].p4(),input.zprimetotprimeallhad.GetTPrimes()[0].p4());
        vars.FillVar( "Gen_Topbar_TPrime_DeltaR", DeltaR );
    }
    if((input.zprimetotprimeallhad.GetTops().size()==1 && input.zprimetotprimeallhad.GetWplus_fromTPrimes().size()==1)){
        float DeltaR=BoostedUtils::DeltaR(input.zprimetotprimeallhad.GetTops()[0].p4(),input.zprimetotprimeallhad.GetWplus_fromTPrimes()[0].p4());
        vars.FillVar( "Gen_Top_WfromTPrimebar_DeltaR", DeltaR );
    }
    if((input.zprimetotprimeallhad.GetTopbars().size()==1 && input.zprimetotprimeallhad.GetWminus_fromTPrimes().size()==1)){
        float DeltaR=BoostedUtils::DeltaR(input.zprimetotprimeallhad.GetTopbars()[0].p4(),input.zprimetotprimeallhad.GetWminus_fromTPrimes()[0].p4());
        vars.FillVar( "Gen_Topbar_WfromTPrime_DeltaR", DeltaR );
    }
    if((input.zprimetotprimeallhad.GetTops().size()==1 && input.zprimetotprimeallhad.GetTPrimebarDecayQuarks().size()==1)){
        float DeltaR=BoostedUtils::DeltaR(input.zprimetotprimeallhad.GetTops()[0].p4(),input.zprimetotprimeallhad.GetTPrimebarDecayQuarks()[0].p4());
        vars.FillVar( "Gen_Top_BottomfromTPrimebar_DeltaR", DeltaR );
    }
    if((input.zprimetotprimeallhad.GetTopbars().size()==1 && input.zprimetotprimeallhad.GetTPrimeDecayQuarks().size()==1)){
        float DeltaR=BoostedUtils::DeltaR(input.zprimetotprimeallhad.GetTopbars()[0].p4(),input.zprimetotprimeallhad.GetTPrimes()[0].p4());
        vars.FillVar( "Gen_Topbar_BottomfromTPrime_DeltaR", DeltaR );
    }
    if((input.zprimetotprimeallhad.GetWplus_fromTPrimes().size()==1 && input.zprimetotprimeallhad.GetTPrimeDecayQuarks().size()==1)){
        float DeltaR=BoostedUtils::DeltaR(input.zprimetotprimeallhad.GetWplus_fromTPrimes()[0].p4(),input.zprimetotprimeallhad.GetTPrimeDecayQuarks()[0].p4());
        vars.FillVar( "Gen_WfromTPrime_BottomfromTPrime_DeltaR", DeltaR );
    }
    if((input.zprimetotprimeallhad.GetWminus_fromTPrimes().size()==1 && input.zprimetotprimeallhad.GetTPrimebarDecayQuarks().size()==1)){
        float DeltaR=BoostedUtils::DeltaR(input.zprimetotprimeallhad.GetWminus_fromTPrimes()[0].p4(),input.zprimetotprimeallhad.GetTPrimebarDecayQuarks()[0].p4());
        vars.FillVar( "Gen_WfromTPrimebar_BottomfromTPrimebar_DeltaR", DeltaR );
    }
    if((input.zprimetotprimeallhad.GetWplus_fromTops().size()==1 && input.zprimetotprimeallhad.GetTopDecayQuarks().size()==1)){
        float DeltaR=BoostedUtils::DeltaR(input.zprimetotprimeallhad.GetWplus_fromTops()[0].p4(),input.zprimetotprimeallhad.GetTopDecayQuarks()[0].p4());
        vars.FillVar( "Gen_WfromTop_BottomfromTop_DeltaR", DeltaR );
    }
    if((input.zprimetotprimeallhad.GetWminus_fromTops().size()==1 && input.zprimetotprimeallhad.GetTopBarDecayQuarks().size()==1)){
        float DeltaR=BoostedUtils::DeltaR(input.zprimetotprimeallhad.GetWminus_fromTops()[0].p4(),input.zprimetotprimeallhad.GetTopBarDecayQuarks()[0].p4());
        vars.FillVar( "Gen_WfromTopbar_BottomfromTopbar_DeltaR", DeltaR );
    }

}
