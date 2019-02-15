#include "BoostedTTH/BoostedAnalyzer/interface/ttEventRecoTrainVariablesProcessor.hpp"

using namespace std;

ttEventRecoTrainVariablesProcessor::ttEventRecoTrainVariablesProcessor() {}
ttEventRecoTrainVariablesProcessor::~ttEventRecoTrainVariablesProcessor() {}

void ttEventRecoTrainVariablesProcessor::Init(const InputCollections &input, VariableContainer &vars) {

    // INPUTS
    vars.InitVar("N_ttMatchInputJets","I");
    // Jet features
    vars.InitVars("ttMatchInputJet_E",                  "N_ttMatchInputJets");
    vars.InitVars("ttMatchInputJet_M",                  "N_ttMatchInputJets");
    vars.InitVars("ttMatchInputJet_Pt",                 "N_ttMatchInputJets");
    vars.InitVars("ttMatchInputJet_Phi",                "N_ttMatchInputJets");
    vars.InitVars("ttMatchInputJet_Eta",                "N_ttMatchInputJets");
    vars.InitVars("ttMatchInputJet_Px",                 "N_ttMatchInputJets");
    vars.InitVars("ttMatchInputJet_Py",                 "N_ttMatchInputJets");
    vars.InitVars("ttMatchInputJet_Pz",                 "N_ttMatchInputJets");
    vars.InitVars("ttMatchInputJet_CSV",                "N_ttMatchInputJets");
    vars.InitVars("ttMatchInputJet_CSV_DNN",            "N_ttMatchInputJets");
    vars.InitVars("ttMatchInputJet_DeepFlavor_b",       "N_ttMatchInputJets");
    vars.InitVars("ttMatchInputJet_DeepFlavor_bb",      "N_ttMatchInputJets");
    vars.InitVars("ttMatchInputJet_DeepFlavor_c",       "N_ttMatchInputJets");
    vars.InitVars("ttMatchInputJet_DeepFlavor_uds",     "N_ttMatchInputJets");
    vars.InitVars("ttMatchInputJet_DeepFlavor_g",       "N_ttMatchInputJets");
    vars.InitVars("ttMatchInputJet_DeepFlavor_lepb",    "N_ttMatchInputJets");
    vars.InitVars("ttMatchInputJet_DeepCSV_b",          "N_ttMatchInputJets");
    vars.InitVars("ttMatchInputJet_DeepCSV_bb",         "N_ttMatchInputJets");
    vars.InitVars("ttMatchInputJet_DeepCSV_c",          "N_ttMatchInputJets");
    vars.InitVars("ttMatchInputJet_DeepCSV_udsg",       "N_ttMatchInputJets");
    vars.InitVars("ttMatchInputJet_Constituents",       "N_ttMatchInputJets");
    vars.InitVars("ttMatchInputJet_hadEnergyFrac",      "N_ttMatchInputJets");

    vars.InitVar("N_ttMatchInputLeptons","I");
    // Lepton features
    vars.InitVars("ttMatchInputLepton_E",                  "N_ttMatchInputLeptons");
    vars.InitVars("ttMatchInputLepton_M",                  "N_ttMatchInputLeptons");
    vars.InitVars("ttMatchInputLepton_Pt",                 "N_ttMatchInputLeptons");
    vars.InitVars("ttMatchInputLepton_Phi",                "N_ttMatchInputLeptons");
    vars.InitVars("ttMatchInputLepton_Eta",                "N_ttMatchInputLeptons");
    vars.InitVars("ttMatchInputLepton_Px",                 "N_ttMatchInputLeptons");
    vars.InitVars("ttMatchInputLepton_Py",                 "N_ttMatchInputLeptons");
    vars.InitVars("ttMatchInputLepton_Pz",                 "N_ttMatchInputLeptons");
    vars.InitVars("ttMatchInputLepton_CSV",                "N_ttMatchInputLeptons");
    vars.InitVars("ttMatchInputLepton_CSV_DNN",            "N_ttMatchInputLeptons");
    vars.InitVars("ttMatchInputLepton_DeepFlavor_b",       "N_ttMatchInputLeptons");
    vars.InitVars("ttMatchInputLepton_DeepFlavor_bb",      "N_ttMatchInputLeptons");
    vars.InitVars("ttMatchInputLepton_DeepFlavor_c",       "N_ttMatchInputLeptons");
    vars.InitVars("ttMatchInputLepton_DeepFlavor_uds",     "N_ttMatchInputLeptons");
    vars.InitVars("ttMatchInputLepton_DeepFlavor_g",       "N_ttMatchInputLeptons");
    vars.InitVars("ttMatchInputLepton_DeepFlavor_lepb",    "N_ttMatchInputLeptons");
    vars.InitVars("ttMatchInputLepton_DeepCSV_b",          "N_ttMatchInputLeptons");
    vars.InitVars("ttMatchInputLepton_DeepCSV_bb",         "N_ttMatchInputLeptons");
    vars.InitVars("ttMatchInputLepton_DeepCSV_c",          "N_ttMatchInputLeptons");
    vars.InitVars("ttMatchInputLepton_DeepCSV_udsg",       "N_ttMatchInputLeptons");
    vars.InitVars("ttMatchInputLepton_Constituents",       "N_ttMatchInputLeptons");
    vars.InitVars("ttMatchInputLepton_hadEnergyFrac",      "N_ttMatchInputLeptons");


    // MET features        
    vars.InitVar("ttMatchInputMET_E");                  
    vars.InitVar("ttMatchInputMET_M");                 
    vars.InitVar("ttMatchInputMET_Pt");                
    vars.InitVar("ttMatchInputMET_Phi");               
    vars.InitVar("ttMatchInputMET_Eta");               
    vars.InitVar("ttMatchInputMET_Px");                
    vars.InitVar("ttMatchInputMET_Py");                
    vars.InitVar("ttMatchInputMET_Pz");               
    vars.InitVar("ttMatchInputMET_CSV");             
    vars.InitVar("ttMatchInputMET_CSV_DNN");        
    vars.InitVar("ttMatchInputMET_DeepFlavor_b");   
    vars.InitVar("ttMatchInputMET_DeepFlavor_bb");  
    vars.InitVar("ttMatchInputMET_DeepFlavor_c");   
    vars.InitVar("ttMatchInputMET_DeepFlavor_uds");
    vars.InitVar("ttMatchInputMET_DeepFlavor_g"); 
    vars.InitVar("ttMatchInputMET_DeepFlavor_lepb"); 
    vars.InitVar("ttMatchInputMET_DeepCSV_b");   
    vars.InitVar("ttMatchInputMET_DeepCSV_bb"); 
    vars.InitVar("ttMatchInputMET_DeepCSV_c"); 
    vars.InitVar("ttMatchInputMET_DeepCSV_udsg");
    vars.InitVar("ttMatchInputMET_Constituents");
    vars.InitVar("ttMatchInputMET_hadEnergyFrac");
    

    // TARGETS

    // hadronic top features        
    vars.InitVar("ttMatchTargetHadTop_E");                  
    vars.InitVar("ttMatchTargetHadTop_M");                 
    vars.InitVar("ttMatchTargetHadTop_Pt");                
    vars.InitVar("ttMatchTargetHadTop_Phi");               
    vars.InitVar("ttMatchTargetHadTop_Eta");               
    vars.InitVar("ttMatchTargetHadTop_Px");                
    vars.InitVar("ttMatchTargetHadTop_Py");                
    vars.InitVar("ttMatchTargetHadTop_Pz");               

    // leptonic top features        
    vars.InitVar("ttMatchTargetLepTop_E");                  
    vars.InitVar("ttMatchTargetLepTop_M");                 
    vars.InitVar("ttMatchTargetLepTop_Pt");                
    vars.InitVar("ttMatchTargetLepTop_Phi");               
    vars.InitVar("ttMatchTargetLepTop_Eta");               
    vars.InitVar("ttMatchTargetLepTop_Px");                
    vars.InitVar("ttMatchTargetLepTop_Py");                
    vars.InitVar("ttMatchTargetLepTop_Pz");               

    // hadronic b features        
    vars.InitVar("ttMatchTargetHadB_E");                  
    vars.InitVar("ttMatchTargetHadB_M");                 
    vars.InitVar("ttMatchTargetHadB_Pt");                
    vars.InitVar("ttMatchTargetHadB_Phi");               
    vars.InitVar("ttMatchTargetHadB_Eta");               
    vars.InitVar("ttMatchTargetHadB_Px");                
    vars.InitVar("ttMatchTargetHadB_Py");                
    vars.InitVar("ttMatchTargetHadB_Pz");               

    // leptonic b features
    vars.InitVar("ttMatchTargetLepB_E");                  
    vars.InitVar("ttMatchTargetLepB_M");                 
    vars.InitVar("ttMatchTargetLepB_Pt");                
    vars.InitVar("ttMatchTargetLepB_Phi");               
    vars.InitVar("ttMatchTargetLepB_Eta");               
    vars.InitVar("ttMatchTargetLepB_Px");                
    vars.InitVar("ttMatchTargetLepB_Py");                
    vars.InitVar("ttMatchTargetLepB_Pz");               

    // hadronic W features
    vars.InitVar("ttMatchTargetHadW_E");                  
    vars.InitVar("ttMatchTargetHadW_M");                 
    vars.InitVar("ttMatchTargetHadW_Pt");                
    vars.InitVar("ttMatchTargetHadW_Phi");               
    vars.InitVar("ttMatchTargetHadW_Eta");               
    vars.InitVar("ttMatchTargetHadW_Px");                
    vars.InitVar("ttMatchTargetHadW_Py");                
    vars.InitVar("ttMatchTargetHadW_Pz");               

    // leptonic W features
    vars.InitVar("ttMatchTargetLepW_E");                  
    vars.InitVar("ttMatchTargetLepW_M");                 
    vars.InitVar("ttMatchTargetLepW_Pt");                
    vars.InitVar("ttMatchTargetLepW_Phi");               
    vars.InitVar("ttMatchTargetLepW_Eta");               
    vars.InitVar("ttMatchTargetLepW_Px");                
    vars.InitVar("ttMatchTargetLepW_Py");                
    vars.InitVar("ttMatchTargetLepW_Pz");               

    // Lepton features
    vars.InitVar("ttMatchTargetLepton_E");                  
    vars.InitVar("ttMatchTargetLepton_M");                 
    vars.InitVar("ttMatchTargetLepton_Pt");                
    vars.InitVar("ttMatchTargetLepton_Phi");               
    vars.InitVar("ttMatchTargetLepton_Eta");               
    vars.InitVar("ttMatchTargetLepton_Px");                
    vars.InitVar("ttMatchTargetLepton_Py");                
    vars.InitVar("ttMatchTargetLepton_Pz");               

    // hadronic W decay quarks features
    vars.InitVar("ttMatchTargetQ1_E");                  
    vars.InitVar("ttMatchTargetQ1_M");                 
    vars.InitVar("ttMatchTargetQ1_Pt");                
    vars.InitVar("ttMatchTargetQ1_Phi");               
    vars.InitVar("ttMatchTargetQ1_Eta");               
    vars.InitVar("ttMatchTargetQ1_Px");                
    vars.InitVar("ttMatchTargetQ1_Py");                
    vars.InitVar("ttMatchTargetQ1_Pz");               

    vars.InitVar("ttMatchTargetQ2_E");                  
    vars.InitVar("ttMatchTargetQ2_M");                 
    vars.InitVar("ttMatchTargetQ2_Pt");                
    vars.InitVar("ttMatchTargetQ2_Phi");               
    vars.InitVar("ttMatchTargetQ2_Eta");               
    vars.InitVar("ttMatchTargetQ2_Px");                
    vars.InitVar("ttMatchTargetQ2_Py");                
    vars.InitVar("ttMatchTargetQ2_Pz");               

    initialized = true;
    } // close Init



void ttEventRecoTrainVariablesProcessor::Process(const InputCollections &input, VariableContainer &vars) {
    if( !initialized ) cerr << "ttEventRecoTrainVariablesProcessor was not initialized" << endl;
    const char* btagger="DeepCSV";

    // fill counting variables
    vars.FillVar("N_ttMatchInputJets",      input.selectedJets.size());
    vars.FillVar("N_ttMatchInputLeptons",   input.selectedElectronsLoose.size()+input.selectedMuonsLoose.size());

    // fill jet variables
    for( std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin(); itJet != input.selectedJets.end(); ++itJet ) {
        int iJet = itJet - input.selectedJets.begin();

        vars.FillVars("ttMatchInputJet_E",              iJet,   itJet->energy() );
        vars.FillVars("ttMatchInputJet_M",              iJet,   itJet->mass()   );
        vars.FillVars("ttMatchInputJet_Pt",             iJet,   itJet->pt()     );
        vars.FillVars("ttMatchInputJet_Phi",            iJet,   itJet->phi()    );
        vars.FillVars("ttMatchInputJet_Eta",            iJet,   itJet->eta()    );
        vars.FillVars("ttMatchInputJet_Px",             iJet,   itJet->px()     );
        vars.FillVars("ttMatchInputJet_Py",             iJet,   itJet->py()     );
        vars.FillVars("ttMatchInputJet_Pz",             iJet,   itJet->pz()     );

        vars.FillVars("ttMatchInputJet_CSV",            iJet,   MiniAODHelper::GetJetCSV(*itJet, btagger)    );
        vars.FillVars("ttMatchInputJet_CSV_DNN",        iJet,   MiniAODHelper::GetJetCSV_DNN(*itJet, btagger));

        vars.FillVars("ttMatchInputJet_DeepFlavor_b",   iJet,   MiniAODHelper::GetJetCSV_DNN(*itJet, "pfDeepFlavourJetTags:probb")    );
        vars.FillVars("ttMatchInputJet_DeepFlavor_bb",  iJet,   MiniAODHelper::GetJetCSV_DNN(*itJet, "pfDeepFlavourJetTags:probbb")   );
        vars.FillVars("ttMatchInputJet_DeepFlavor_c",   iJet,   MiniAODHelper::GetJetCSV_DNN(*itJet, "pfDeepFlavourJetTags:probc")    );
        vars.FillVars("ttMatchInputJet_DeepFlavor_uds", iJet,   MiniAODHelper::GetJetCSV_DNN(*itJet, "pfDeepFlavourJetTags:probuds")  );
        vars.FillVars("ttMatchInputJet_DeepFlavor_g",   iJet,   MiniAODHelper::GetJetCSV_DNN(*itJet, "pfDeepFlavourJetTags:probg")    );
        vars.FillVars("ttMatchInputJet_DeepFlavor_lepb",iJet,   MiniAODHelper::GetJetCSV_DNN(*itJet, "pfDeepFlavourJetTags:problepb") );

        vars.FillVars("ttMatchInputJet_DeepCSV_b",      iJet,   MiniAODHelper::GetJetCSV_DNN(*itJet, "pfDeepCSVJetTags:probb")       );
        vars.FillVars("ttMatchInputJet_DeepCSV_bb",     iJet,   MiniAODHelper::GetJetCSV_DNN(*itJet, "pfDeepCSVJetTags:probbb")      );
        vars.FillVars("ttMatchInputJet_DeepCSV_c",      iJet,   MiniAODHelper::GetJetCSV_DNN(*itJet, "pfDeepCSVJetTags:probbc")      );
        vars.FillVars("ttMatchInputJet_DeepCSV_udsg",   iJet,   MiniAODHelper::GetJetCSV_DNN(*itJet, "pfDeepCSVJetTags:probudsg")    );

        vars.FillVars("ttMatchInputJet_Constituents",   iJet,   itJet->nConstituents()          );
        vars.FillVars("ttMatchInputJet_hadEnergyFrac",  iJet,   itJet->energyFractionHadronic() );


        } // close jet loop

    // fill Lepton variables
    std::vector<math::XYZTLorentzVector> looseLeptonVecs = BoostedUtils::GetLepVecs(input.selectedElectronsLoose,input.selectedMuonsLoose);
    for( std::vector<math::XYZTLorentzVector>::iterator itLep = looseLeptonVecs.begin(); itLep != looseLeptonVecs.end(); ++itLep ) {
        int iLep = itLep - looseLeptonVecs.begin();

        vars.FillVars("ttMatchInputLepton_E",              iLep,   itLep->E()   );
        vars.FillVars("ttMatchInputLepton_M",              iLep,   itLep->M()   );
        vars.FillVars("ttMatchInputLepton_Pt",             iLep,   itLep->Pt()  );
        vars.FillVars("ttMatchInputLepton_Phi",            iLep,   itLep->Phi() );
        vars.FillVars("ttMatchInputLepton_Eta",            iLep,   itLep->Eta() );
        vars.FillVars("ttMatchInputLepton_Px",             iLep,   itLep->Px()  );
        vars.FillVars("ttMatchInputLepton_Py",             iLep,   itLep->Py()  );
        vars.FillVars("ttMatchInputLepton_Pz",             iLep,   itLep->Pz()  );

        vars.FillVars("ttMatchInputLepton_CSV",            iLep,   0.);
        vars.FillVars("ttMatchInputLepton_CSV_DNN",        iLep,   0.);

        vars.FillVars("ttMatchInputLepton_DeepFlavor_b",   iLep,   0.);
        vars.FillVars("ttMatchInputLepton_DeepFlavor_bb",  iLep,   0.);
        vars.FillVars("ttMatchInputLepton_DeepFlavor_c",   iLep,   0.);
        vars.FillVars("ttMatchInputLepton_DeepFlavor_uds", iLep,   0.);
        vars.FillVars("ttMatchInputLepton_DeepFlavor_g",   iLep,   0.);
        vars.FillVars("ttMatchInputLepton_DeepFlavor_lepb",iLep,   0.);

        vars.FillVars("ttMatchInputLepton_DeepCSV_b",      iLep,   0.);
        vars.FillVars("ttMatchInputLepton_DeepCSV_bb",     iLep,   0.);
        vars.FillVars("ttMatchInputLepton_DeepCSV_c",      iLep,   0.);
        vars.FillVars("ttMatchInputLepton_DeepCSV_udsg",   iLep,   0.);

        vars.FillVars("ttMatchInputLepton_Constituents",   iLep,   1.);
        vars.FillVars("ttMatchInputLepton_hadEnergyFrac",  iLep,   0.);

        } // close lepton loop

    // fill MET variables
    math::XYZTLorentzVector metVec = input.correctedMET.corP4(pat::MET::Type1XY);

    vars.FillVar("ttMatchInputMET_E",               metVec.E()     );
    vars.FillVar("ttMatchInputMET_M",               metVec.M()     );
    vars.FillVar("ttMatchInputMET_Pt",              metVec.Pt()    );
    vars.FillVar("ttMatchInputMET_Phi",             metVec.Phi()   );
    vars.FillVar("ttMatchInputMET_Eta",             metVec.Eta()   );
    vars.FillVar("ttMatchInputMET_Px",              metVec.Px()    );
    vars.FillVar("ttMatchInputMET_Py",              metVec.Py()    );
    vars.FillVar("ttMatchInputMET_Pz",              metVec.Pz()    );
    vars.FillVar("ttMatchInputMET_CSV",             0.  );
    vars.FillVar("ttMatchInputMET_CSV_DNN",         0.  );
    vars.FillVar("ttMatchInputMET_DeepFlavor_b",    0.  );
    vars.FillVar("ttMatchInputMET_DeepFlavor_bb",   0.  );
    vars.FillVar("ttMatchInputMET_DeepFlavor_c",    0.  );
    vars.FillVar("ttMatchInputMET_DeepFlavor_uds",  0.  );
    vars.FillVar("ttMatchInputMET_DeepFlavor_g",    0.  );
    vars.FillVar("ttMatchInputMET_DeepFlavor_lepb", 0.  );
    vars.FillVar("ttMatchInputMET_DeepCSV_b",       0.  );
    vars.FillVar("ttMatchInputMET_DeepCSV_bb",      0.  );
    vars.FillVar("ttMatchInputMET_DeepCSV_c",       0.  );
    vars.FillVar("ttMatchInputMET_DeepCSV_udsg",    0.  );
    vars.FillVar("ttMatchInputMET_Constituents",    0.  );
    vars.FillVar("ttMatchInputMET_hadEnergyFrac",   0.  );






    } // close Process
