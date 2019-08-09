#include "BoostedTTH/BoostedAnalyzer/interface/essentialBasicVarProcessor.hpp"

using namespace std;

essentialBasicVarProcessor::essentialBasicVarProcessor(){}
essentialBasicVarProcessor::~essentialBasicVarProcessor(){}


void essentialBasicVarProcessor::Init(const InputCollections& input,VariableContainer& vars){
    
    // load dataEra 
    era = input.era;
    
    vars.InitVar("Evt_ID","L");
    vars.InitVar("Evt_Odd","I");
    vars.InitVar("Evt_Run","I");
    vars.InitVar("Evt_Lumi","I");

    
    
    vars.InitVar( "N_Jets","I" );
    vars.InitVar( "N_LooseJets","I" );
    vars.InitVar( "N_TightLeptons","I" );
    vars.InitVar( "N_LooseLeptons" ,"I");
    vars.InitVar( "N_TightElectrons" ,"I");
    vars.InitVar( "N_LooseElectrons","I" );
    vars.InitVar( "N_TightMuons" ,"I");
    vars.InitVar( "N_LooseMuons" ,"I");
    vars.InitVar( "N_BTagsL" ,"I");
    vars.InitVar( "N_BTagsM" ,"I");
    vars.InitVar( "N_BTagsT","I" );
    vars.InitVar( "N_PrimaryVertices","I" );
    vars.InitVar( "N_GenPVs", "I");

    vars.InitVar(  "N_GenJets","I" );
    vars.InitVars( "GenJet_E","N_GenJets" );
    vars.InitVars( "GenJet_Pt","N_GenJets" );
    vars.InitVars( "GenJet_Phi","N_GenJets" );
    vars.InitVars( "GenJet_Eta","N_GenJets" );


    
    //vars.InitVars( "LooseJet_E","N_LooseJets" );
    //vars.InitVars( "LooseJet_M","N_LooseJets" );
    //vars.InitVars( "LooseJet_Pt","N_LooseJets" );
    //vars.InitVars( "LooseJet_Phi","N_LooseJets" );
    //vars.InitVars( "LooseJet_Eta","N_LooseJets" );
    //vars.InitVars( "LooseJet_CSV","N_LooseJets" );
    //vars.InitVars( "LooseJet_Flav","N_LooseJets" );
    //vars.InitVars( "LooseJet_PartonFlav","N_LooseJets" );
    //vars.InitVars( "LooseJet_Charge","N_LooseJets" );
    //vars.InitVars( "LooseJet_PileUpID","N_LooseJets" );
    //vars.InitVars( "LooseJet_PileUpMVA","N_LooseJets" );

    //vars.InitVars( "LooseJet_GenJet_Pt","N_LooseJets" );
    //vars.InitVars( "LooseJet_GenJet_Eta","N_LooseJets" );
    //
    //vars.InitVars( "LooseJet_DeepCSV_b","N_LooseJets");
    //vars.InitVars( "LooseJet_DeepCSV_bb","N_LooseJets");
    //vars.InitVars( "LooseJet_DeepCSV_c","N_LooseJets");
    //vars.InitVars( "LooseJet_DeepCSV_udsg","N_LooseJets");

    //vars.InitVars( "LooseJet_DeepJetCSV","N_LooseJets");
    //vars.InitVars( "LooseJet_DeepJet_b","N_LooseJets");
    //vars.InitVars( "LooseJet_DeepJet_bb","N_LooseJets");
    //vars.InitVars( "LooseJet_DeepJet_lepb","N_LooseJets");
    //vars.InitVars( "LooseJet_DeepJet_c","N_LooseJets");
    //vars.InitVars( "LooseJet_DeepJet_uds","N_LooseJets");
    //vars.InitVars( "LooseJet_DeepJet_g","N_LooseJets");
    
    vars.InitVars( "Jet_E","N_Jets" );
    vars.InitVars( "Jet_M","N_Jets" );
    vars.InitVars( "Jet_Pt","N_Jets" );
    vars.InitVars( "Jet_Phi","N_Jets" );
    vars.InitVars( "Jet_Eta","N_Jets" );
    vars.InitVars( "Jet_CSV","N_Jets" );
    vars.InitVars( "Jet_Flav","N_Jets" );
    vars.InitVars( "Jet_PartonFlav","N_Jets" );
    vars.InitVars( "Jet_Charge","N_Jets" );
    vars.InitVars( "Jet_PileUpID","N_Jets" );
    vars.InitVars( "Jet_PileUpMVA","N_Jets" );

    vars.InitVars( "Jet_GenJet_Pt","N_Jets" );
    vars.InitVars( "Jet_GenJet_Eta","N_Jets" );
    
    //vars.InitVars( "Jet_DeepCSV_b","N_Jets");
    //vars.InitVars( "Jet_DeepCSV_bb","N_Jets");
    //vars.InitVars( "Jet_DeepCSV_c","N_Jets");
    //vars.InitVars( "Jet_DeepCSV_udsg","N_Jets");

    vars.InitVars( "Jet_DeepJetCSV","N_Jets");    
    vars.InitVars( "Jet_DeepJet_b","N_Jets");
    vars.InitVars( "Jet_DeepJet_bb","N_Jets");
    vars.InitVars( "Jet_DeepJet_lepb","N_Jets");
    vars.InitVars( "Jet_DeepJet_c","N_Jets");
    vars.InitVars( "Jet_DeepJet_uds","N_Jets");
    vars.InitVars( "Jet_DeepJet_g","N_Jets");

    //vars.InitVars( "TaggedJet_E","N_BTagsM" );
    //vars.InitVars( "TaggedJet_M","N_BTagsM" );
    //vars.InitVars( "TaggedJet_Pt","N_BTagsM" );
    //vars.InitVars( "TaggedJet_Phi","N_BTagsM" );
    //vars.InitVars( "TaggedJet_Eta","N_BTagsM" );
    //vars.InitVars( "TaggedJet_CSV","N_BTagsM" );
    //vars.InitVars( "TaggedJet_DeepJetCSV","N_BTagsM" );
    //vars.InitVars( "TaggedJet_DeepJet_b","N_BTagsM" );
    //vars.InitVars( "TaggedJet_DeepJet_bb","N_BTagsM" );
    //vars.InitVars( "TaggedJet_DeepJet_lepb","N_BTagsM" );
    //vars.InitVars( "TaggedJet_DeepJet_c","N_BTagsM" );
    //vars.InitVars( "TaggedJet_DeepJet_uds","N_BTagsM" );
    //vars.InitVars( "TaggedJet_DeepJet_g","N_BTagsM" );

    //vars.InitVars( "TightLepton_E","N_TightLeptons" );    
    //vars.InitVars( "TightLepton_M","N_TightLeptons" );    
    //vars.InitVars( "TightLepton_Pt","N_TightLeptons" );    
    //vars.InitVars( "TightLepton_Eta","N_TightLeptons" );    
    //vars.InitVars( "TightLepton_Phi","N_TightLeptons" );    

    vars.InitVars( "LooseLepton_E","N_LooseLeptons" );
    vars.InitVars( "LooseLepton_M","N_LooseLeptons" );
    vars.InitVars( "LooseLepton_Pt","N_LooseLeptons" );
    vars.InitVars( "LooseLepton_Eta","N_LooseLeptons" );
    vars.InitVars( "LooseLepton_Phi","N_LooseLeptons" );
    
    //vars.InitVars( "LooseMuon_E","N_LooseMuons" );
    //vars.InitVars( "LooseMuon_M","N_LooseMuons" );
    //vars.InitVars( "LooseMuon_Pt","N_LooseMuons" );
    //vars.InitVars( "LooseMuon_Eta","N_LooseMuons" );
    //vars.InitVars( "LooseMuon_Phi","N_LooseMuons" );
    //vars.InitVars( "LooseMuon_RelIso","N_LooseMuons" );
    //vars.InitVars( "LooseMuon_Charge","N_LooseMuons" );
    //vars.InitVars( "LooseMuon_Pt_BeForeRC","N_LooseMuons" );
    //vars.InitVars( "LooseMuon_roccorSF", "N_LooseMuons");
    //vars.InitVars( "LooseMuon_roccorSFUp", "N_LooseMuons");
    //vars.InitVars( "LooseMuon_roccorSFDown", "N_LooseMuons");
    //vars.InitVars( "LooseMuon_IdentificationSF","N_LooseMuons");
    //vars.InitVars( "LooseMuon_IdentificationSFUp","N_LooseMuons");
    //vars.InitVars( "LooseMuon_IdentificationSFDown","N_LooseMuons");
    //vars.InitVars( "LooseMuon_IsolationSF","N_LooseMuons");
    //vars.InitVars( "LooseMuon_IsolationSFUp","N_LooseMuons");
    //vars.InitVars( "LooseMuon_IsolationSFDown","N_LooseMuons");

    vars.InitVars( "Muon_E","N_TightMuons" );
    vars.InitVars( "Muon_M","N_TightMuons" );
    vars.InitVars( "Muon_Pt","N_TightMuons" );
    vars.InitVars( "Muon_Eta","N_TightMuons" );
    vars.InitVars( "Muon_Phi","N_TightMuons" );
    vars.InitVars( "Muon_RelIso","N_TightMuons" );
    vars.InitVars( "Muon_Charge","N_TightMuons" );
    vars.InitVars( "Muon_Pt_BeForeRC","N_TightMuons" );
    vars.InitVars( "Muon_roccorSF", "N_TightMuons");
    vars.InitVars( "Muon_roccorSFUp", "N_TightMuons");
    vars.InitVars( "Muon_roccorSFDown", "N_TightMuons");
    vars.InitVars( "Muon_IdentificationSF","N_TightMuons");
    vars.InitVars( "Muon_IdentificationSFUp","N_TightMuons");
    vars.InitVars( "Muon_IdentificationSFDown","N_TightMuons");
    vars.InitVars( "Muon_IsolationSF","N_TightMuons");
    vars.InitVars( "Muon_IsolationSFUp","N_TightMuons");
    vars.InitVars( "Muon_IsolationSFDown","N_TightMuons");


    
    //vars.InitVars( "LooseElectron_E","N_LooseElectrons" );
    //vars.InitVars( "LooseElectron_M","N_LooseElectrons" );
    //vars.InitVars( "LooseElectron_Pt","N_LooseElectrons" );
    //vars.InitVars( "LooseElectron_Eta","N_LooseElectrons" );
    //vars.InitVars( "LooseElectron_Phi","N_LooseElectrons" );
    //vars.InitVars( "LooseElectron_RelIso","N_LooseElectrons" );
    //vars.InitVars( "LooseElectron_Charge","N_LooseElectrons" );
    //vars.InitVars( "LooseElectron_Pt_BeforeRun2Calibration","N_LooseElectrons" );
    //vars.InitVars( "LooseElectron_Eta_Supercluster","N_LooseElectrons" );
    //// electron energy scale combined up/down
    //vars.InitVars( "LooseElectron_CorrFactor_ScaleUp","N_LooseElectrons");
    //vars.InitVars( "LooseElectron_CorrFactor_ScaleDown","N_LooseElectrons");
    //// electron energy smearing combined up/down
    //vars.InitVars( "LooseElectron_CorrFactor_SigmaUp","N_LooseElectrons");
    //vars.InitVars( "LooseElectron_CorrFactor_SigmaDown","N_LooseElectrons");
    //vars.InitVars( "LooseElectron_IdentificationSF","N_LooseElectrons");
    //vars.InitVars( "LooseElectron_IdentificationSFUp","N_LooseElectrons");
    //vars.InitVars( "LooseElectron_IdentificationSFDown","N_LooseElectrons");
    //vars.InitVars( "LooseElectron_ReconstructionSF","N_LooseElectrons");
    //vars.InitVars( "LooseElectron_ReconstructionSFUp","N_LooseElectrons");
    //vars.InitVars( "LooseElectron_ReconstructionSFDown","N_LooseElectrons");
    
    vars.InitVars( "Electron_E","N_TightElectrons" );
    vars.InitVars( "Electron_M","N_TightElectrons" );
    vars.InitVars( "Electron_Pt","N_TightElectrons" );
    vars.InitVars( "Electron_Eta","N_TightElectrons" );
    vars.InitVars( "Electron_Phi","N_TightElectrons" );
    vars.InitVars( "Electron_RelIso","N_TightElectrons" );
    vars.InitVars( "Electron_Charge","N_TightElectrons" );
    vars.InitVars( "Electron_Pt_BeforeRun2Calibration","N_TightElectrons" );
    vars.InitVars( "Electron_Eta_Supercluster","N_TightElectrons" );
    // electron energy scale combined up/down
    vars.InitVars( "Electron_CorrFactor_ScaleUp","N_TightElectrons");
    vars.InitVars( "Electron_CorrFactor_ScaleDown","N_TightElectrons");
    // electron energy smearing combined up/down
    vars.InitVars( "Electron_CorrFactor_SigmaUp","N_TightElectrons");
    vars.InitVars( "Electron_CorrFactor_SigmaDown","N_TightElectrons");
    vars.InitVars( "Electron_IdentificationSF","N_TightElectrons");
    vars.InitVars( "Electron_IdentificationSFUp","N_TightElectrons");
    vars.InitVars( "Electron_IdentificationSFDown","N_TightElectrons");
    vars.InitVars( "Electron_ReconstructionSF","N_TightElectrons");
    vars.InitVars( "Electron_ReconstructionSFUp","N_TightElectrons");
    vars.InitVars( "Electron_ReconstructionSFDown","N_TightElectrons");
    
    
    
    vars.InitVar( "Evt_MET_Pt" );
    vars.InitVar( "Evt_MET_Phi" );
    vars.InitVar( "Gen_MET_Pt" );
    vars.InitVar( "Gen_MET_Phi" );
    
    
    vars.InitVars( "CSV","N_Jets" );
    initialized=true;
}

void essentialBasicVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
    if(!initialized) cerr << "tree processor not initialized" << endl;

    //also write the event ID for splitting purposes
    long evt_id = input.eventInfo.evt;
    long run_id = input.eventInfo.run;
    long lumi_section = input.eventInfo.lumiBlock;

    vars.FillIntVar("Evt_ID",evt_id);
    vars.FillIntVar("Evt_Odd",evt_id%2);
    vars.FillIntVar("Evt_Run",run_id);
    vars.FillIntVar("Evt_Lumi",lumi_section);


    
    const char* btagger="DeepJet";
    std::vector<pat::Jet> selectedTaggedJets;
    std::vector<pat::Jet> selectedTaggedJetsT;
    std::vector<pat::Jet> selectedTaggedJetsL;
    std::vector<pat::Jet> selectedUntaggedJets;
    for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin(); itJet != input.selectedJets.end(); ++itJet)
    {
        if(CSVHelper::PassesCSV(*itJet, btagger, CSVHelper::CSVwp::Medium, era))
            selectedTaggedJets.push_back(*itJet);
        else
            selectedUntaggedJets.push_back(*itJet);
        

        if(CSVHelper::PassesCSV(*itJet, btagger, CSVHelper::CSVwp::Loose, era))
            selectedTaggedJetsL.push_back(*itJet);
        if(CSVHelper::PassesCSV(*itJet, btagger, CSVHelper::CSVwp::Tight, era))
            selectedTaggedJetsT.push_back(*itJet);
    }
    
    // Fill Multiplicity Variables
    vars.FillVar( "N_GenPVs",input.eventInfo.numTruePV);
    vars.FillVar( "N_PrimaryVertices",input.selectedPVs.size());    
    vars.FillVar( "N_Jets",input.selectedJets.size());
    vars.FillVar( "N_LooseJets",input.selectedJetsLoose.size());
    vars.FillVar( "N_TightLeptons",input.selectedElectrons.size()+ input.selectedMuons.size());    
    vars.FillVar( "N_LooseLeptons",input.selectedElectronsLoose.size()+ input.selectedMuonsLoose.size());    
    vars.FillVar( "N_TightElectrons",input.selectedElectrons.size());    
    vars.FillVar( "N_LooseElectrons",input.selectedElectronsLoose.size());    
    vars.FillVar( "N_TightMuons",input.selectedMuons.size());    
    vars.FillVar( "N_LooseMuons",input.selectedMuonsLoose.size());    
    

    // jet variables
    vars.FillVar( "N_GenJets", input.genJets.size() );
    size_t iGenJet = 0;
    for( auto& genJet: input.genJets ) {
        vars.FillVars( "GenJet_E",iGenJet,genJet.energy() );
        vars.FillVars( "GenJet_Pt",iGenJet,genJet.pt() );
        vars.FillVars( "GenJet_Eta",iGenJet,genJet.eta() );
        vars.FillVars( "GenJet_Phi",iGenJet,genJet.phi() );
        ++iGenJet;
    }


    // Fill Jet Variables
    // All Jets
    for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin() ; itJet != input.selectedJets.end(); ++itJet)
    {
        int iJet = itJet - input.selectedJets.begin();
        vars.FillVars( "Jet_E",iJet,itJet->energy() );
        vars.FillVars( "Jet_M",iJet,itJet->mass() );
        vars.FillVars( "Jet_Pt",iJet,itJet->pt() );
        vars.FillVars( "Jet_Eta",iJet,itJet->eta() );
        vars.FillVars( "Jet_Phi",iJet,itJet->phi() );
        vars.FillVars( "Jet_CSV",iJet,CSVHelper::GetJetCSV(*itJet,btagger) );
        vars.FillVars( "Jet_Flav",iJet,itJet->hadronFlavour() );
        vars.FillVars( "Jet_PartonFlav",iJet,itJet->partonFlavour() );
        vars.FillVars( "Jet_Charge",iJet,itJet->jetCharge() );
        if(itJet->hasUserInt("pileupJetIdUpdated:fullId")) 
            vars.FillVars( "Jet_PileUpID",iJet,itJet->userInt("pileupJetIdUpdated:fullId"));
        if(itJet->hasUserFloat("pileupJetIdUpdated:fullDiscriminant")) 
            vars.FillVars( "Jet_PileUpMVA",iJet,itJet->userFloat("pileupJetIdUpdated:fullDiscriminant"));

        if(itJet->genJet()!=NULL)
        {
            vars.FillVars( "Jet_GenJet_Pt",iJet,itJet->genJet()->pt());
            vars.FillVars( "Jet_GenJet_Eta",iJet,itJet->genJet()->eta());
        }
        else 
        {
            vars.FillVars( "Jet_GenJet_Pt",iJet,-9.0);
            vars.FillVars( "Jet_GenJet_Eta",iJet,-9.0);
        }

        //vars.FillVars( "Jet_DeepCSV_b",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepCSVJetTags:probb"));
        //vars.FillVars( "Jet_DeepCSV_bb",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepCSVJetTags:probbb"));
        //vars.FillVars( "Jet_DeepCSV_c",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepCSVJetTags:probc"));
        //vars.FillVars( "Jet_DeepCSV_udsg",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepCSVJetTags:probudsg"));
        
        vars.FillVars( "Jet_DeepJetCSV",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"DeepJet"));
        vars.FillVars( "Jet_DeepJet_b",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepFlavourJetTags:probb"));
        vars.FillVars( "Jet_DeepJet_bb",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepFlavourJetTags:probbb"));
        vars.FillVars( "Jet_DeepJet_lepb",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepFlavourJetTags:problepb"));
        vars.FillVars( "Jet_DeepJet_c",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepFlavourJetTags:probc"));
        vars.FillVars( "Jet_DeepJet_uds",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepFlavourJetTags:probuds"));
        vars.FillVars( "Jet_DeepJet_g",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepFlavourJetTags:probg"));
    }
    
    //for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJetsLoose.begin() ; itJet != input.selectedJetsLoose.end(); ++itJet)
    //{
    //    int iJet = itJet - input.selectedJetsLoose.begin();
    //    vars.FillVars( "LooseJet_E",iJet,itJet->energy() );
    //    vars.FillVars( "LooseJet_M",iJet,itJet->mass() );
    //    vars.FillVars( "LooseJet_Pt",iJet,itJet->pt() );
    //    vars.FillVars( "LooseJet_Eta",iJet,itJet->eta() );
    //    vars.FillVars( "LooseJet_Phi",iJet,itJet->phi() );
    //    vars.FillVars( "LooseJet_CSV",iJet,CSVHelper::GetJetCSV(*itJet,btagger) );
    //    //vars.FillVars( "LooseJet_CSV_DNN",iJet,CSVHelper::GetJetCSV_DNN(*itJet,btagger) );
    //    vars.FillVars( "LooseJet_Flav",iJet,itJet->hadronFlavour() );
    //    vars.FillVars( "LooseJet_PartonFlav",iJet,itJet->partonFlavour() );
    //    vars.FillVars( "LooseJet_Charge",iJet,itJet->jetCharge() );
    //    if(itJet->hasUserInt("pileupJetIdUpdated:fullId")) 
    //        vars.FillVars( "LooseJet_PileUpID",iJet,itJet->userInt("pileupJetIdUpdated:fullId"));
    //    if(itJet->hasUserFloat("pileupJetIdUpdated:fullDiscriminant")) 
    //            vars.FillVars( "LooseJet_PileUpMVA",iJet,itJet->userFloat("pileupJetIdUpdated:fullDiscriminant"));

    //    if(itJet->genJet()!=NULL)
    //    {
    //        vars.FillVars( "LooseJet_GenJet_Pt",iJet,itJet->genJet()->pt());
    //        vars.FillVars( "LooseJet_GenJet_Eta",iJet,itJet->genJet()->eta());
    //    }
    //    else 
    //    {
    //        vars.FillVars( "LooseJet_GenJet_Pt",iJet,-9.0);
    //        vars.FillVars( "LooseJet_GenJet_Eta",iJet,-9.0);
    //    }

    //    vars.FillVars( "LooseJet_DeepCSV_b",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepCSVJetTags:probb"));
    //    vars.FillVars( "LooseJet_DeepCSV_bb",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepCSVJetTags:probbb"));
    //    vars.FillVars( "LooseJet_DeepCSV_c",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepCSVJetTags:probc"));
    //    vars.FillVars( "LooseJet_DeepCSV_udsg",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepCSVJetTags:probudsg"));
    //    
    //    vars.FillVars( "LooseJet_DeepJetCSV",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"DeepJet"));
    //    vars.FillVars( "LooseJet_DeepJet_b",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepFlavourJetTags:probb"));
    //    vars.FillVars( "LooseJet_DeepJet_bb",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepFlavourJetTags:probbb"));
    //    vars.FillVars( "LooseJet_DeepJet_lepb",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepFlavourJetTags:problepb"));
    //    vars.FillVars( "LooseJet_DeepJet_c",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepFlavourJetTags:probc"));
    //    vars.FillVars( "LooseJet_DeepJet_uds",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepFlavourJetTags:probuds"));
    //    vars.FillVars( "LooseJet_DeepJet_g",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepFlavourJetTags:probg"));
    //}

    

    
    // Tagged Jets
    //for(std::vector<pat::Jet>::iterator itTaggedJet = selectedTaggedJets.begin() ; itTaggedJet != selectedTaggedJets.end(); ++itTaggedJet)
    //{
    //    int iTaggedJet = itTaggedJet - selectedTaggedJets.begin();
    //    vars.FillVars( "TaggedJet_E",iTaggedJet,            itTaggedJet->energy() );
    //    vars.FillVars( "TaggedJet_M",iTaggedJet,            itTaggedJet->mass() );
    //    vars.FillVars( "TaggedJet_Pt",iTaggedJet,           itTaggedJet->pt() );
    //    vars.FillVars( "TaggedJet_Eta",iTaggedJet,          itTaggedJet->eta() );
    //    vars.FillVars( "TaggedJet_Phi",iTaggedJet,          itTaggedJet->phi() );
    //    vars.FillVars( "TaggedJet_CSV",iTaggedJet,          CSVHelper::GetJetCSV(*itTaggedJet,btagger));
    //    vars.FillVars( "TaggedJet_DeepJetCSV",iTaggedJet,   CSVHelper::GetJetCSV_DNN(*itTaggedJet,"DeepJet"));
    //    vars.FillVars( "TaggedJet_DeepJet_b",iTaggedJet,    CSVHelper::GetJetCSV_DNN(*itTaggedJet,"pfDeepFlavourJetTags:probb"));
    //    vars.FillVars( "TaggedJet_DeepJet_bb",iTaggedJet,   CSVHelper::GetJetCSV_DNN(*itTaggedJet,"pfDeepFlavourJetTags:probbb"));
    //    vars.FillVars( "TaggedJet_DeepJet_lepb",iTaggedJet, CSVHelper::GetJetCSV_DNN(*itTaggedJet,"pfDeepFlavourJetTags:problepb"));
    //    vars.FillVars( "TaggedJet_DeepJet_c",iTaggedJet,    CSVHelper::GetJetCSV_DNN(*itTaggedJet,"pfDeepFlavourJetTags:probc"));
    //    vars.FillVars( "TaggedJet_DeepJet_uds",iTaggedJet,  CSVHelper::GetJetCSV_DNN(*itTaggedJet,"pfDeepFlavourJetTags:probuds"));
    //    vars.FillVars( "TaggedJet_DeepJet_g",iTaggedJet,    CSVHelper::GetJetCSV_DNN(*itTaggedJet,"pfDeepFlavourJetTags:probg"));
    //}

    // Fill Lepton Variables
    std::vector<math::XYZTLorentzVector> tightLeptonVecs = BoostedUtils::GetLepVecs(input.selectedElectrons,input.selectedMuons);
    //for(auto itLep = tightLeptonVecs.begin(); itLep != tightLeptonVecs.end(); ++itLep)
    //{
    //    int iLep = itLep - tightLeptonVecs.begin();
    //    vars.FillVars( "TightLepton_E",iLep,itLep->E() );
    //    vars.FillVars( "TightLepton_M",iLep,itLep->M() );
    //    vars.FillVars( "TightLepton_Pt",iLep,itLep->Pt() );
    //    vars.FillVars( "TightLepton_Eta",iLep,itLep->Eta());
    //    vars.FillVars( "TightLepton_Phi",iLep,itLep->Phi() );
    //}
    std::vector<math::XYZTLorentzVector> looseLeptonVecs = BoostedUtils::GetLepVecs(input.selectedElectronsLoose,input.selectedMuonsLoose);
    for(std::vector<math::XYZTLorentzVector>::iterator itLep = looseLeptonVecs.begin() ; itLep != looseLeptonVecs.end(); ++itLep)
    {
        int iLep = itLep - looseLeptonVecs.begin();
        vars.FillVars( "LooseLepton_E",iLep,itLep->E() );
        vars.FillVars( "LooseLepton_M",iLep,itLep->M() );
        vars.FillVars( "LooseLepton_Pt",iLep,itLep->Pt() );
        vars.FillVars( "LooseLepton_Eta",iLep,itLep->Eta());
        vars.FillVars( "LooseLepton_Phi",iLep,itLep->Phi() );
    }
     
    //for(std::vector<pat::Electron>::const_iterator itEle = input.selectedElectronsLoose.begin(); itEle != input.selectedElectronsLoose.end(); ++itEle)
    //{
    //    int iEle = itEle - input.selectedElectronsLoose.begin();
    //    vars.FillVars( "LooseElectron_E",iEle,itEle->energy() );
    //    vars.FillVars( "LooseElectron_M",iEle,itEle->mass() );
    //    vars.FillVars( "LooseElectron_Pt",iEle,itEle->pt() );
    //    vars.FillVars( "LooseElectron_Eta",iEle,itEle->eta() );
    //    vars.FillVars( "LooseElectron_Phi",iEle,itEle->phi() ); 
    //    if(itEle->hasUserFloat("relIso"))
    //        vars.FillVars( "LooseElectron_RelIso",iEle,itEle->userFloat("relIso") );

    //    vars.FillVars( "LooseElectron_Charge",iEle,itEle->charge() ); 
    //    if(itEle->hasUserFloat("ptBeforeRun2Calibration"))
    //        vars.FillVars("LooseElectron_Pt_BeforeRun2Calibration",iEle,itEle->userFloat("ptBeforeRun2Calibration"));

    //    vars.FillVars("LooseElectron_Eta_Supercluster",iEle,itEle->superCluster()->eta());
    //    if(itEle->hasUserFloat("CorrFactor_ScaleUp"))
    //    {
    //        // electron energy scale combined up/down
    //        vars.FillVars( "LooseElectron_CorrFactor_ScaleUp",iEle,itEle->userFloat("CorrFactor_ScaleUp"));
    //        vars.FillVars( "LooseElectron_CorrFactor_ScaleDown",iEle,itEle->userFloat("CorrFactor_ScaleDown"));
    //        // electron energy smearing combined up/down
    //        vars.FillVars( "LooseElectron_CorrFactor_SigmaUp",iEle,itEle->userFloat("CorrFactor_SigmaUp"));
    //        vars.FillVars( "LooseElectron_CorrFactor_SigmaDown",iEle,itEle->userFloat("CorrFactor_SigmaDown"));
    //    }
    //    if(itEle->hasUserFloat("IdentificationSF")) 
    //    {
    //        vars.FillVars( "LooseElectron_IdentificationSF",iEle,itEle->userFloat("IdentificationSF"));
    //        vars.FillVars( "LooseElectron_IdentificationSFUp",iEle,itEle->userFloat("IdentificationSFUp"));
    //        vars.FillVars( "LooseElectron_IdentificationSFDown",iEle,itEle->userFloat("IdentificationSFDown"));
    //        vars.FillVars( "LooseElectron_ReconstructionSF",iEle,itEle->userFloat("ReconstructionSF"));
    //        vars.FillVars( "LooseElectron_ReconstructionSFUp",iEle,itEle->userFloat("ReconstructionSFUp"));
    //        vars.FillVars( "LooseElectron_ReconstructionSFDown",iEle,itEle->userFloat("ReconstructionSFDown"));
    //    }
    //}
    for(std::vector<pat::Electron>::const_iterator itEle = input.selectedElectrons.begin(); itEle != input.selectedElectrons.end(); ++itEle)
    {
        int iEle = itEle - input.selectedElectrons.begin();
        vars.FillVars( "Electron_E",iEle,itEle->energy() );
        vars.FillVars( "Electron_M",iEle,itEle->mass() );
        vars.FillVars( "Electron_Pt",iEle,itEle->pt() );
        vars.FillVars( "Electron_Eta",iEle,itEle->eta() );
        vars.FillVars( "Electron_Phi",iEle,itEle->phi() ); 
        if(itEle->hasUserFloat("relIso"))
            vars.FillVars( "Electron_RelIso",iEle,itEle->userFloat("relIso") );

        vars.FillVars( "Electron_Charge",iEle,itEle->charge() ); 
        if(itEle->hasUserFloat("ptBeforeRun2Calibration"))
            vars.FillVars("Electron_Pt_BeforeRun2Calibration",iEle,itEle->userFloat("ptBeforeRun2Calibration"));
        
        vars.FillVars("Electron_Eta_Supercluster",iEle,itEle->superCluster()->eta());
        if(itEle->hasUserFloat("CorrFactor_ScaleUp"))
        {
            // electron energy scale combined up/down
            vars.FillVars( "Electron_CorrFactor_ScaleUp",iEle,itEle->userFloat("CorrFactor_ScaleUp"));
            vars.FillVars( "Electron_CorrFactor_ScaleDown",iEle,itEle->userFloat("CorrFactor_ScaleDown"));
            // electron energy smearing combined up/down
            vars.FillVars( "Electron_CorrFactor_SigmaUp",iEle,itEle->userFloat("CorrFactor_SigmaUp"));
            vars.FillVars( "Electron_CorrFactor_SigmaDown",iEle,itEle->userFloat("CorrFactor_SigmaDown"));
        }
        if(itEle->hasUserFloat("IdentificationSF"))
        {
            vars.FillVars( "Electron_IdentificationSF",iEle,itEle->userFloat("IdentificationSF"));
            vars.FillVars( "Electron_IdentificationSFUp",iEle,itEle->userFloat("IdentificationSFUp"));
            vars.FillVars( "Electron_IdentificationSFDown",iEle,itEle->userFloat("IdentificationSFDown"));
            vars.FillVars( "Electron_ReconstructionSF",iEle,itEle->userFloat("ReconstructionSF"));
            vars.FillVars( "Electron_ReconstructionSFUp",iEle,itEle->userFloat("ReconstructionSFUp"));
            vars.FillVars( "Electron_ReconstructionSFDown",iEle,itEle->userFloat("ReconstructionSFDown"));
        }
    }
    
    //for(std::vector<pat::Muon>::const_iterator itMu = input.selectedMuonsLoose.begin(); itMu != input.selectedMuonsLoose.end(); ++itMu)
    //{
    //    int iMu = itMu - input.selectedMuonsLoose.begin();
    //    vars.FillVars( "LooseMuon_E",iMu,itMu->energy() );
    //    vars.FillVars( "LooseMuon_M",iMu,itMu->mass() );
    //    vars.FillVars( "LooseMuon_Pt",iMu,itMu->pt() );
    //    vars.FillVars( "LooseMuon_Eta",iMu,itMu->eta() );
    //    vars.FillVars( "LooseMuon_Phi",iMu,itMu->phi() );
    //    if(itMu->hasUserFloat("relIso"))
    //        vars.FillVars( "LooseMuon_RelIso",iMu,itMu->userFloat("relIso") );

    //    vars.FillVars( "LooseMuon_Charge",iMu,itMu->charge() );
    //    if(itMu->hasUserFloat("PtbeforeRC"))
    //        vars.FillVars( "LooseMuon_Pt_BeForeRC",iMu,itMu->userFloat("PtbeforeRC") );

    //    if(itMu->hasUserFloat("roccorSF"))
    //        vars.FillVars( "LooseMuon_roccorSF",iMu,itMu->userFloat("roccorSF") );

    //    if(itMu->hasUserFloat("roccorSFUp"))
    //        vars.FillVars( "LooseMuon_roccorSFUp",iMu,itMu->userFloat("roccorSFUp") );

    //    if(itMu->hasUserFloat("roccorSFDown"))
    //        vars.FillVars( "LooseMuon_roccorSFDown",iMu,itMu->userFloat("roccorSFDown") );

    //    if(itMu->hasUserFloat("IdentificationSF"))
    //    {
    //        vars.FillVars( "LooseMuon_IdentificationSF",iMu,itMu->userFloat("IdentificationSF"));
    //        vars.FillVars( "LooseMuon_IdentificationSFUp",iMu,itMu->userFloat("IdentificationSFUp"));
    //        vars.FillVars( "LooseMuon_IdentificationSFDown",iMu,itMu->userFloat("IdentificationSFDown"));
    //    }
    //    if(itMu->hasUserFloat("IsolationSF"))
    //    {
    //        vars.FillVars( "LooseMuon_IsolationSF",iMu,itMu->userFloat("IsolationSF"));
    //        vars.FillVars( "LooseMuon_IsolationSFUp",iMu,itMu->userFloat("IsolationSFUp"));
    //        vars.FillVars( "LooseMuon_IsolationSFDown",iMu,itMu->userFloat("IsolationSFDown"));
    //    }
    //}
    for(std::vector<pat::Muon>::const_iterator itMu = input.selectedMuons.begin(); itMu != input.selectedMuons.end(); ++itMu)
    {
        int iMu = itMu - input.selectedMuons.begin();
        vars.FillVars( "Muon_E",iMu,itMu->energy() );
        vars.FillVars( "Muon_M",iMu,itMu->mass() );
        vars.FillVars( "Muon_Pt",iMu,itMu->pt() );
        vars.FillVars( "Muon_Eta",iMu,itMu->eta() );
        vars.FillVars( "Muon_Phi",iMu,itMu->phi() );
        if(itMu->hasUserFloat("relIso"))
            vars.FillVars( "Muon_RelIso",iMu,itMu->userFloat("relIso") );

        vars.FillVars( "Muon_Charge",iMu,itMu->charge() );
        if(itMu->hasUserFloat("PtbeforeRC"))
            vars.FillVars( "Muon_Pt_BeForeRC",iMu,itMu->userFloat("PtbeforeRC") );

        if(itMu->hasUserFloat("roccorSF"))
            vars.FillVars( "Muon_roccorSF",iMu,itMu->userFloat("roccorSF") );

        if(itMu->hasUserFloat("roccorSFUp"))
            vars.FillVars( "Muon_roccorSFUp",iMu,itMu->userFloat("roccorSFUp") );

        if(itMu->hasUserFloat("roccorSFDown"))
            vars.FillVars( "Muon_roccorSFDown",iMu,itMu->userFloat("roccorSFDown") );


        if(itMu->hasUserFloat("IdentificationSF"))
        {
            vars.FillVars( "Muon_IdentificationSF",iMu,itMu->userFloat("IdentificationSF"));
            vars.FillVars( "Muon_IdentificationSFUp",iMu,itMu->userFloat("IdentificationSFUp"));
            vars.FillVars( "Muon_IdentificationSFDown",iMu,itMu->userFloat("IdentificationSFDown"));
        }
        if(itMu->hasUserFloat("IsolationSF"))
        {
            vars.FillVars( "Muon_IsolationSF",iMu,itMu->userFloat("IsolationSF"));
            vars.FillVars( "Muon_IsolationSFUp",iMu,itMu->userFloat("IsolationSFUp"));
            vars.FillVars( "Muon_IsolationSFDown",iMu,itMu->userFloat("IsolationSFDown"));
        }
    }
    
    vars.FillVar( "Evt_MET_Pt",input.correctedMET.corPt(pat::MET::Type1XY) );
    vars.FillVar( "Evt_MET_Phi",input.correctedMET.corPhi(pat::MET::Type1XY) );
    if(input.correctedMET.genMET()!=0)
    {
        vars.FillVar( "Gen_MET_Pt",input.correctedMET.genMET()->pt() );
        vars.FillVar( "Gen_MET_Phi",input.correctedMET.genMET()->phi() );
    }
    
    //std::vector<math::XYZTLorentzVector> jetvecs = BoostedUtils::GetJetVecs(input.selectedJets);
    //math::XYZTLorentzVector metvec = input.correctedMET.corP4(pat::MET::Type1XY);
    
    // Fill Number of b Tags
    vars.FillVar( "N_BTagsM",selectedTaggedJets.size() );    
    vars.FillVar( "N_BTagsL",selectedTaggedJetsL.size() );    
    vars.FillVar( "N_BTagsT",selectedTaggedJetsT.size() );
    
    // Fill CSV Variables
    std::vector<double> csvJets;
    for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin() ; itJet != input.selectedJets.end(); ++itJet)
        csvJets.push_back(CSVHelper::GetJetCSV(*itJet,btagger));


    std::vector<double> csvJetsSorted=csvJets;
    std::sort(csvJetsSorted.begin(),csvJetsSorted.end(),std::greater<double>());
    
    for(std::vector<double>::iterator itCSV = csvJetsSorted.begin() ; itCSV != csvJetsSorted.end(); ++itCSV)
    {
        int iCSV = itCSV - csvJetsSorted.begin();
        vars.FillVars("CSV" ,iCSV,*itCSV);
    }

}
