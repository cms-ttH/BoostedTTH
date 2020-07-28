#include "BoostedTTH/BoostedAnalyzer/interface/microBasicVarProcessor.hpp"

using namespace std;

microBasicVarProcessor::microBasicVarProcessor(){}
microBasicVarProcessor::~microBasicVarProcessor(){}


void microBasicVarProcessor::Init(const InputCollections& input,VariableContainer& vars){
    
    // load dataEra 
    era = input.era;
    
    vars.InitVar("Evt_ID","L");
    vars.InitVar("Evt_Odd","I");
    vars.InitVar("Evt_Run","I");
    vars.InitVar("Evt_Lumi","I");

    
    
    vars.InitVar( "N_Jets","I" );
    vars.InitVar( "N_TightLeptons","I" );
    vars.InitVar( "N_LooseLeptons" ,"I");
    vars.InitVar( "N_TightElectrons" ,"I");
    vars.InitVar( "N_LooseElectrons","I" );
    vars.InitVar( "N_TightMuons" ,"I");
    vars.InitVar( "N_LooseMuons" ,"I");
    vars.InitVar( "N_BTagsM" ,"I");
    vars.InitVar( "N_PrimaryVertices","I" );
    vars.InitVar( "N_GenPVs", "I");

    vars.InitVar("Evt_HT");
    vars.InitVar("Evt_HT_jets");
    vars.InitVar("Evt_HT_wo_MET");
    vars.InitVar("N_HEM_Jets", "I");
    vars.InitVar("N_HEM_LooseElectrons", "I");
    vars.InitVar("N_HEM_LooseMuons", "I");
    initialized=true;
}

void microBasicVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
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
    vars.FillVar( "N_TightLeptons",input.selectedElectrons.size()+ input.selectedMuons.size());    
    vars.FillVar( "N_LooseLeptons",input.selectedElectronsLoose.size()+ input.selectedMuonsLoose.size());    
    vars.FillVar( "N_TightElectrons",input.selectedElectrons.size());    
    vars.FillVar( "N_LooseElectrons",input.selectedElectronsLoose.size());    
    vars.FillVar( "N_TightMuons",input.selectedMuons.size());    
    vars.FillVar( "N_LooseMuons",input.selectedMuonsLoose.size());    
    
    // Fill Jet Variables
    int N_HEM_Jets = 0;
    double ht = 0;
    double ht_jets = 0;
    double ht_woMET = 0;
    // All Jets
    for(std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin() ; itJet != input.selectedJets.end(); ++itJet)
    {
        int iJet = itJet - input.selectedJets.begin();
        ht+=itJet->pt();
        ht_jets+=itJet->pt();
        ht_woMET+=itJet->pt();
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
        ht+=itLep->Pt();
        ht_woMET+=itLep->Pt();
    }
     
    for(std::vector<pat::Electron>::const_iterator itEle = input.selectedElectronsLoose.begin(); itEle != input.selectedElectronsLoose.end(); ++itEle)
    {
        int iEle = itEle - input.selectedElectronsLoose.begin();
        if (itEle->eta() < -1.3 && itEle->eta() > -3.0 && itEle->phi() < -0.87 && itEle->phi() > -1.57) N_HEM_LooseElectrons += 1;

    }
    vars.FillVar("N_HEM_LooseElectrons", N_HEM_LooseElectrons);

    for(std::vector<pat::Muon>::const_iterator itMu = input.selectedMuonsLoose.begin(); itMu != input.selectedMuonsLoose.end(); ++itMu)
    {
        int iMu = itMu - input.selectedMuonsLoose.begin();
        if (itMu->eta() < -1.3 && itMu->eta() > -3.0 && itMu->phi() < -0.87 && itMu->phi() > -1.57) N_HEM_LooseMuons += 1;
    }
    vars.FillVar("N_HEM_LooseMuons", N_HEM_LooseMuons);

    
    ht+=input.correctedMET.corPt(pat::MET::Type1XY);
    vars.FillVar("Evt_HT", ht);
    vars.FillVar("Evt_HT_jets", ht_jets);
    vars.FillVar("Evt_HT_wo_MET", ht_woMET);
    
    // Fill Number of b Tags
    vars.FillVar( "N_BTagsM",selectedTaggedJets.size() );    
}
