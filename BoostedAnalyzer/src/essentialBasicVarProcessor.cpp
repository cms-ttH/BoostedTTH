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
    vars.InitVar( "N_BTagsM_DeepCSV","I" );    
    vars.InitVar( "N_BTagsT","I" );
    vars.InitVar( "N_PrimaryVertices","I" );
    vars.InitVar( "N_GenPVs", "I");
    
    vars.InitVars( "Jet_E","N_Jets" );
    vars.InitVars( "Jet_M","N_Jets" );
    vars.InitVars( "Jet_Pt","N_Jets" );
    vars.InitVars( "Jet_Phi","N_Jets" );
    vars.InitVars( "Jet_Eta","N_Jets" );
    vars.InitVars( "Jet_btagValue","N_Jets" );
    vars.InitVars( "Jet_Flav","N_Jets" );
    vars.InitVars( "Jet_PartonFlav","N_Jets" );
    vars.InitVars( "Jet_Charge","N_Jets" );
    vars.InitVars( "Jet_PileUpID","N_Jets" );
    vars.InitVars( "Jet_PileUpMVA","N_Jets" );

    vars.InitVars( "Jet_GenJet_Pt","N_Jets" );
    vars.InitVars( "Jet_GenJet_Eta","N_Jets" );
    
    vars.InitVars( "Jet_DeepCSV","N_Jets");
    vars.InitVars( "Jet_DeepCSV_b","N_Jets");
    vars.InitVars( "Jet_DeepCSV_bb","N_Jets");
    vars.InitVars( "Jet_DeepCSV_c","N_Jets");
    vars.InitVars( "Jet_DeepCSV_udsg","N_Jets");

    vars.InitVars( "Jet_DeepJetValue","N_Jets");    
    vars.InitVars( "Jet_DeepJet_b","N_Jets");
    vars.InitVars( "Jet_DeepJet_bb","N_Jets");
    vars.InitVars( "Jet_DeepJet_lepb","N_Jets");
    vars.InitVars( "Jet_DeepJet_c","N_Jets");
    vars.InitVars( "Jet_DeepJet_uds","N_Jets");
    vars.InitVars( "Jet_DeepJet_g","N_Jets");

    vars.InitVars( "TightLepton_E","N_TightLeptons" );    
    vars.InitVars( "TightLepton_M","N_TightLeptons" );    
    vars.InitVars( "TightLepton_Pt","N_TightLeptons" );    
    vars.InitVars( "TightLepton_Eta","N_TightLeptons" );    
    vars.InitVars( "TightLepton_Phi","N_TightLeptons" );    

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
    
    vars.InitVars( "btagValue","N_Jets" );
    vars.InitVars( "DeepCSV","N_Jets");
    vars.InitVar("N_HEM_Jets", "I");
    vars.InitVar("N_HEM_LooseElectrons", "I");
    vars.InitVar("N_HEM_LooseMuons", "I");
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
    std::vector<pat::Jet> selectedTaggedJetsDeepCSV;
    std::vector<pat::Jet> selectedTaggedJetsT;
    std::vector<pat::Jet> selectedTaggedJetsL;
    std::vector<pat::Jet> selectedUntaggedJets;
    for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin(); itJet != input.selectedJets.end(); ++itJet)
    {
        if(CSVHelper::PassesCSV(*itJet, "DeepCSV", CSVHelper::CSVwp::Medium, era))
            selectedTaggedJetsDeepCSV.push_back(*itJet);
    }
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
    
    // Fill Jet Variables
    int N_HEM_Jets = 0;
    // All Jets
    for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin() ; itJet != input.selectedJets.end(); ++itJet)
    {
        int iJet = itJet - input.selectedJets.begin();
        vars.FillVars( "Jet_E",iJet,itJet->energy() );
        vars.FillVars( "Jet_M",iJet,itJet->mass() );
        vars.FillVars( "Jet_Pt",iJet,itJet->pt() );
        vars.FillVars( "Jet_Eta",iJet,itJet->eta() );
        vars.FillVars( "Jet_Phi",iJet,itJet->phi() );
        vars.FillVars( "Jet_btagValue",iJet,CSVHelper::GetJetCSV(*itJet,btagger) );
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

        
        vars.FillVars( "Jet_DeepCSV",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"DeepCSV"));
        vars.FillVars( "Jet_DeepCSV_b",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepCSVJetTags:probb"));
        vars.FillVars( "Jet_DeepCSV_bb",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepCSVJetTags:probbb"));
        vars.FillVars( "Jet_DeepCSV_c",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepCSVJetTags:probc"));
        vars.FillVars( "Jet_DeepCSV_udsg",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepCSVJetTags:probudsg"));
        
        vars.FillVars( "Jet_DeepJetValue",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"DeepJet"));
        vars.FillVars( "Jet_DeepJet_b",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepFlavourJetTags:probb"));
        vars.FillVars( "Jet_DeepJet_bb",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepFlavourJetTags:probbb"));
        vars.FillVars( "Jet_DeepJet_lepb",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepFlavourJetTags:problepb"));
        vars.FillVars( "Jet_DeepJet_c",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepFlavourJetTags:probc"));
        vars.FillVars( "Jet_DeepJet_uds",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepFlavourJetTags:probuds"));
        vars.FillVars( "Jet_DeepJet_g",iJet,CSVHelper::GetJetCSV_DNN(*itJet,"pfDeepFlavourJetTags:probg"));

        if (itJet->eta() < -1.3 && itJet->eta() > -3.0 && itJet->phi() < -0.87 && itJet->phi() > -1.57) N_HEM_Jets += 1;
    }

    vars.FillVar("N_HEM_Jets", N_HEM_Jets);
    
    // Fill Lepton Variables
    int N_HEM_LooseElectrons = 0;
    int N_HEM_LooseMuons = 0;
    std::vector<math::XYZTLorentzVector> tightLeptonVecs = BoostedUtils::GetLepVecs(input.selectedElectrons,input.selectedMuons);
    for(auto itLep = tightLeptonVecs.begin(); itLep != tightLeptonVecs.end(); ++itLep)
    {
        int iLep = itLep - tightLeptonVecs.begin();
        vars.FillVars( "TightLepton_E",iLep,itLep->E() );
        vars.FillVars( "TightLepton_M",iLep,itLep->M() );
        vars.FillVars( "TightLepton_Pt",iLep,itLep->Pt() );
        vars.FillVars( "TightLepton_Eta",iLep,itLep->Eta());
        vars.FillVars( "TightLepton_Phi",iLep,itLep->Phi() );
    }
    std::vector<math::XYZTLorentzVector> looseLeptonVecs = BoostedUtils::GetLepVecs(input.selectedElectronsLoose,input.selectedMuonsLoose);

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
    vars.FillVar( "N_BTagsM_DeepCSV",selectedTaggedJetsDeepCSV.size() );    
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
        vars.FillVars("btagValue" ,iCSV,*itCSV);
    }

    // Fill deepCSV Variables
    std::vector<double> deepcsvJets;
    for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin() ; itJet != input.selectedJets.end(); ++itJet)
        deepcsvJets.push_back(CSVHelper::GetJetCSV(*itJet,"DeepCSV"));


    std::vector<double> deepcsvJetsSorted=deepcsvJets;
    std::sort(deepcsvJetsSorted.begin(),deepcsvJetsSorted.end(),std::greater<double>());
    
    for(std::vector<double>::iterator itCSV = deepcsvJetsSorted.begin() ; itCSV != deepcsvJetsSorted.end(); ++itCSV)
    {
        int iCSV = itCSV - deepcsvJetsSorted.begin();
        vars.FillVars("DeepCSV" ,iCSV,*itCSV);
    }

}
