#include "BoostedTTH/BoostedAnalyzer/interface/ttEventRecoTrainVariablesProcessor.hpp"

using namespace std;

ttEventRecoTrainVariablesProcessor::ttEventRecoTrainVariablesProcessor() {
    inputPrefix  = "ttMatchInput";
    targetPrefix = "ttMatchTarget";
    }

ttEventRecoTrainVariablesProcessor::~ttEventRecoTrainVariablesProcessor() {}


void ttEventRecoTrainVariablesProcessor::Init(const InputCollections &input, VariableContainer &vars) {

    // INPUTS
    vars.InitVar("N_"+inputPrefix+"Jets","I");
    // Jet features
    vars.InitVars(inputPrefix+"Jet_E",                  "N_"+inputPrefix+"Jets");
    vars.InitVars(inputPrefix+"Jet_M",                  "N_"+inputPrefix+"Jets");
    vars.InitVars(inputPrefix+"Jet_Pt",                 "N_"+inputPrefix+"Jets");
    vars.InitVars(inputPrefix+"Jet_Phi",                "N_"+inputPrefix+"Jets");
    vars.InitVars(inputPrefix+"Jet_Eta",                "N_"+inputPrefix+"Jets");
    vars.InitVars(inputPrefix+"Jet_Px",                 "N_"+inputPrefix+"Jets");
    vars.InitVars(inputPrefix+"Jet_Py",                 "N_"+inputPrefix+"Jets");
    vars.InitVars(inputPrefix+"Jet_Pz",                 "N_"+inputPrefix+"Jets");
    vars.InitVars(inputPrefix+"Jet_CSV",                "N_"+inputPrefix+"Jets");
    vars.InitVars(inputPrefix+"Jet_CSV_DNN",            "N_"+inputPrefix+"Jets");
    vars.InitVars(inputPrefix+"Jet_DeepFlavor_b",       "N_"+inputPrefix+"Jets");
    vars.InitVars(inputPrefix+"Jet_DeepFlavor_bb",      "N_"+inputPrefix+"Jets");
    vars.InitVars(inputPrefix+"Jet_DeepFlavor_c",       "N_"+inputPrefix+"Jets");
    vars.InitVars(inputPrefix+"Jet_DeepFlavor_uds",     "N_"+inputPrefix+"Jets");
    vars.InitVars(inputPrefix+"Jet_DeepFlavor_g",       "N_"+inputPrefix+"Jets");
    vars.InitVars(inputPrefix+"Jet_DeepFlavor_lepb",    "N_"+inputPrefix+"Jets");
    vars.InitVars(inputPrefix+"Jet_DeepCSV_b",          "N_"+inputPrefix+"Jets");
    vars.InitVars(inputPrefix+"Jet_DeepCSV_bb",         "N_"+inputPrefix+"Jets");
    vars.InitVars(inputPrefix+"Jet_DeepCSV_c",          "N_"+inputPrefix+"Jets");
    vars.InitVars(inputPrefix+"Jet_DeepCSV_udsg",       "N_"+inputPrefix+"Jets");
    vars.InitVars(inputPrefix+"Jet_Constituents",       "N_"+inputPrefix+"Jets");
    //vars.InitVars(inputPrefix+"Jet_hadEnergyFrac",      "N_"+inputPrefix+"Jets");

    vars.InitVar("N_"+inputPrefix+"Leptons","I");
    // Lepton features
    vars.InitVars(inputPrefix+"Lepton_E",                  "N_"+inputPrefix+"Leptons");
    vars.InitVars(inputPrefix+"Lepton_M",                  "N_"+inputPrefix+"Leptons");
    vars.InitVars(inputPrefix+"Lepton_Pt",                 "N_"+inputPrefix+"Leptons");
    vars.InitVars(inputPrefix+"Lepton_Phi",                "N_"+inputPrefix+"Leptons");
    vars.InitVars(inputPrefix+"Lepton_Eta",                "N_"+inputPrefix+"Leptons");
    vars.InitVars(inputPrefix+"Lepton_Px",                 "N_"+inputPrefix+"Leptons");
    vars.InitVars(inputPrefix+"Lepton_Py",                 "N_"+inputPrefix+"Leptons");
    vars.InitVars(inputPrefix+"Lepton_Pz",                 "N_"+inputPrefix+"Leptons");
    vars.InitVars(inputPrefix+"Lepton_CSV",                "N_"+inputPrefix+"Leptons");
    vars.InitVars(inputPrefix+"Lepton_CSV_DNN",            "N_"+inputPrefix+"Leptons");
    vars.InitVars(inputPrefix+"Lepton_DeepFlavor_b",       "N_"+inputPrefix+"Leptons");
    vars.InitVars(inputPrefix+"Lepton_DeepFlavor_bb",      "N_"+inputPrefix+"Leptons");
    vars.InitVars(inputPrefix+"Lepton_DeepFlavor_c",       "N_"+inputPrefix+"Leptons");
    vars.InitVars(inputPrefix+"Lepton_DeepFlavor_uds",     "N_"+inputPrefix+"Leptons");
    vars.InitVars(inputPrefix+"Lepton_DeepFlavor_g",       "N_"+inputPrefix+"Leptons");
    vars.InitVars(inputPrefix+"Lepton_DeepFlavor_lepb",    "N_"+inputPrefix+"Leptons");
    vars.InitVars(inputPrefix+"Lepton_DeepCSV_b",          "N_"+inputPrefix+"Leptons");
    vars.InitVars(inputPrefix+"Lepton_DeepCSV_bb",         "N_"+inputPrefix+"Leptons");
    vars.InitVars(inputPrefix+"Lepton_DeepCSV_c",          "N_"+inputPrefix+"Leptons");
    vars.InitVars(inputPrefix+"Lepton_DeepCSV_udsg",       "N_"+inputPrefix+"Leptons");
    vars.InitVars(inputPrefix+"Lepton_Constituents",       "N_"+inputPrefix+"Leptons");
    //vars.InitVars(inputPrefix+"Lepton_hadEnergyFrac",      "N_"+inputPrefix+"Leptons");


    // MET features        
    vars.InitVar(inputPrefix+"MET_E",                   "F");                  
    vars.InitVar(inputPrefix+"MET_M",                   "F");                 
    vars.InitVar(inputPrefix+"MET_Pt",                  "F");                
    vars.InitVar(inputPrefix+"MET_Phi",                 "F");               
    vars.InitVar(inputPrefix+"MET_Eta",                 "F");               
    vars.InitVar(inputPrefix+"MET_Px",                  "F");                
    vars.InitVar(inputPrefix+"MET_Py",                  "F");                
    vars.InitVar(inputPrefix+"MET_Pz",                  "F");               
    vars.InitVar(inputPrefix+"MET_CSV",                 "F");             
    vars.InitVar(inputPrefix+"MET_CSV_DNN",             "F");        
    vars.InitVar(inputPrefix+"MET_DeepFlavor_b",        "F");   
    vars.InitVar(inputPrefix+"MET_DeepFlavor_bb",       "F");  
    vars.InitVar(inputPrefix+"MET_DeepFlavor_c",        "F");   
    vars.InitVar(inputPrefix+"MET_DeepFlavor_uds",      "F");
    vars.InitVar(inputPrefix+"MET_DeepFlavor_g",        "F"); 
    vars.InitVar(inputPrefix+"MET_DeepFlavor_lepb",     "F"); 
    vars.InitVar(inputPrefix+"MET_DeepCSV_b",           "F");   
    vars.InitVar(inputPrefix+"MET_DeepCSV_bb",          "F"); 
    vars.InitVar(inputPrefix+"MET_DeepCSV_c",           "F"); 
    vars.InitVar(inputPrefix+"MET_DeepCSV_udsg",        "F");
    vars.InitVar(inputPrefix+"MET_Constituents",        "I");
    //vars.InitVar(inputPrefix+"MET_hadEnergyFrac",       "F");
    

    // TARGETS

    // hadronic top features        
    vars.InitVar(targetPrefix+"HadTop_E",   "F");                  
    vars.InitVar(targetPrefix+"HadTop_M",   "F");                 
    vars.InitVar(targetPrefix+"HadTop_Pt",  "F");                
    vars.InitVar(targetPrefix+"HadTop_Phi", "F");               
    vars.InitVar(targetPrefix+"HadTop_Eta", "F");               
    vars.InitVar(targetPrefix+"HadTop_Px",  "F");                
    vars.InitVar(targetPrefix+"HadTop_Py",  "F");                
    vars.InitVar(targetPrefix+"HadTop_Pz",  "F");               

    // leptonic top features        
    vars.InitVar(targetPrefix+"LepTop_E",   "F");                  
    vars.InitVar(targetPrefix+"LepTop_M",   "F");                 
    vars.InitVar(targetPrefix+"LepTop_Pt",  "F");                
    vars.InitVar(targetPrefix+"LepTop_Phi", "F");               
    vars.InitVar(targetPrefix+"LepTop_Eta", "F");               
    vars.InitVar(targetPrefix+"LepTop_Px",  "F");                
    vars.InitVar(targetPrefix+"LepTop_Py",  "F");
    vars.InitVar(targetPrefix+"LepTop_Pz",  "F");

    // hadronic b features        
    vars.InitVar(targetPrefix+"HadB_E",     "F");                  
    vars.InitVar(targetPrefix+"HadB_M",     "F");                 
    vars.InitVar(targetPrefix+"HadB_Pt",    "F");                
    vars.InitVar(targetPrefix+"HadB_Phi",   "F");               
    vars.InitVar(targetPrefix+"HadB_Eta",   "F");               
    vars.InitVar(targetPrefix+"HadB_Px",    "F");                
    vars.InitVar(targetPrefix+"HadB_Py",    "F");                
    vars.InitVar(targetPrefix+"HadB_Pz",    "F");               

    // leptonic b features
    vars.InitVar(targetPrefix+"LepB_E",     "F");                  
    vars.InitVar(targetPrefix+"LepB_M",     "F");                 
    vars.InitVar(targetPrefix+"LepB_Pt",    "F");                
    vars.InitVar(targetPrefix+"LepB_Phi",   "F");               
    vars.InitVar(targetPrefix+"LepB_Eta",   "F");               
    vars.InitVar(targetPrefix+"LepB_Px",    "F");                
    vars.InitVar(targetPrefix+"LepB_Py",    "F");                
    vars.InitVar(targetPrefix+"LepB_Pz",    "F");               

    // hadronic W features
    vars.InitVar(targetPrefix+"HadW_E",     "F");                  
    vars.InitVar(targetPrefix+"HadW_M",     "F");                 
    vars.InitVar(targetPrefix+"HadW_Pt",    "F");                
    vars.InitVar(targetPrefix+"HadW_Phi",   "F");               
    vars.InitVar(targetPrefix+"HadW_Eta",   "F");               
    vars.InitVar(targetPrefix+"HadW_Px",    "F");                
    vars.InitVar(targetPrefix+"HadW_Py",    "F");                
    vars.InitVar(targetPrefix+"HadW_Pz",    "F");               

    // leptonic W features
    vars.InitVar(targetPrefix+"LepW_E",     "F");                  
    vars.InitVar(targetPrefix+"LepW_M",     "F");                 
    vars.InitVar(targetPrefix+"LepW_Pt",    "F");                
    vars.InitVar(targetPrefix+"LepW_Phi",   "F");               
    vars.InitVar(targetPrefix+"LepW_Eta",   "F");               
    vars.InitVar(targetPrefix+"LepW_Px",    "F");                
    vars.InitVar(targetPrefix+"LepW_Py",    "F");                
    vars.InitVar(targetPrefix+"LepW_Pz",    "F");               

    // Lepton features
    vars.InitVar(targetPrefix+"Lepton_E",   "F");                  
    vars.InitVar(targetPrefix+"Lepton_M",   "F");                 
    vars.InitVar(targetPrefix+"Lepton_Pt",  "F");                
    vars.InitVar(targetPrefix+"Lepton_Phi", "F");               
    vars.InitVar(targetPrefix+"Lepton_Eta", "F");               
    vars.InitVar(targetPrefix+"Lepton_Px",  "F");                
    vars.InitVar(targetPrefix+"Lepton_Py",  "F");                
    vars.InitVar(targetPrefix+"Lepton_Pz",  "F");               

    // hadronic W decay quarks features
    vars.InitVar(targetPrefix+"Q1_E",       "F");                  
    vars.InitVar(targetPrefix+"Q1_M",       "F");                 
    vars.InitVar(targetPrefix+"Q1_Pt",      "F");                
    vars.InitVar(targetPrefix+"Q1_Phi",     "F");               
    vars.InitVar(targetPrefix+"Q1_Eta",     "F");               
    vars.InitVar(targetPrefix+"Q1_Px",      "F");                
    vars.InitVar(targetPrefix+"Q1_Py",      "F");                
    vars.InitVar(targetPrefix+"Q1_Pz",      "F");               

    vars.InitVar(targetPrefix+"Q2_E",       "F");                  
    vars.InitVar(targetPrefix+"Q2_M",       "F");                 
    vars.InitVar(targetPrefix+"Q2_Pt",      "F");                
    vars.InitVar(targetPrefix+"Q2_Phi",     "F");               
    vars.InitVar(targetPrefix+"Q2_Eta",     "F");               
    vars.InitVar(targetPrefix+"Q2_Px",      "F");                
    vars.InitVar(targetPrefix+"Q2_Py",      "F");                
    vars.InitVar(targetPrefix+"Q2_Pz",      "F");               

    initialized = true;
    } // close Init



void ttEventRecoTrainVariablesProcessor::Process(const InputCollections &input, VariableContainer &vars) {
    if( !initialized ) cerr << "ttEventRecoTrainVariablesProcessor was not initialized" << endl;
    const char* btagger="DeepCSV";

    // fill counting variables
    vars.FillVar("N_"+inputPrefix+"Jets",      input.selectedJets.size());
    vars.FillVar("N_"+inputPrefix+"Leptons",   input.selectedElectronsLoose.size()+input.selectedMuonsLoose.size());

    // fill jet variables
    for( std::vector<pat::Jet>::const_iterator itJet = input.selectedJets.begin(); itJet != input.selectedJets.end(); ++itJet ) {
        int iJet = itJet - input.selectedJets.begin();

        vars.FillVars(inputPrefix+"Jet_E",              iJet,   itJet->energy() );
        vars.FillVars(inputPrefix+"Jet_M",              iJet,   itJet->mass()   );
        vars.FillVars(inputPrefix+"Jet_Pt",             iJet,   itJet->pt()     );
        vars.FillVars(inputPrefix+"Jet_Phi",            iJet,   itJet->phi()    );
        vars.FillVars(inputPrefix+"Jet_Eta",            iJet,   itJet->eta()    );
        vars.FillVars(inputPrefix+"Jet_Px",             iJet,   itJet->px()     );
        vars.FillVars(inputPrefix+"Jet_Py",             iJet,   itJet->py()     );
        vars.FillVars(inputPrefix+"Jet_Pz",             iJet,   itJet->pz()     );

        vars.FillVars(inputPrefix+"Jet_CSV",            iJet,   MiniAODHelper::GetJetCSV(*itJet, btagger)    );
        vars.FillVars(inputPrefix+"Jet_CSV_DNN",        iJet,   MiniAODHelper::GetJetCSV_DNN(*itJet, btagger));

        vars.FillVars(inputPrefix+"Jet_DeepFlavor_b",   iJet,   MiniAODHelper::GetJetCSV_DNN(*itJet, "pfDeepFlavourJetTags:probb")    );
        vars.FillVars(inputPrefix+"Jet_DeepFlavor_bb",  iJet,   MiniAODHelper::GetJetCSV_DNN(*itJet, "pfDeepFlavourJetTags:probbb")   );
        vars.FillVars(inputPrefix+"Jet_DeepFlavor_c",   iJet,   MiniAODHelper::GetJetCSV_DNN(*itJet, "pfDeepFlavourJetTags:probc")    );
        vars.FillVars(inputPrefix+"Jet_DeepFlavor_uds", iJet,   MiniAODHelper::GetJetCSV_DNN(*itJet, "pfDeepFlavourJetTags:probuds")  );
        vars.FillVars(inputPrefix+"Jet_DeepFlavor_g",   iJet,   MiniAODHelper::GetJetCSV_DNN(*itJet, "pfDeepFlavourJetTags:probg")    );
        vars.FillVars(inputPrefix+"Jet_DeepFlavor_lepb",iJet,   MiniAODHelper::GetJetCSV_DNN(*itJet, "pfDeepFlavourJetTags:problepb") );

        vars.FillVars(inputPrefix+"Jet_DeepCSV_b",      iJet,   MiniAODHelper::GetJetCSV_DNN(*itJet, "pfDeepCSVJetTags:probb")       );
        vars.FillVars(inputPrefix+"Jet_DeepCSV_bb",     iJet,   MiniAODHelper::GetJetCSV_DNN(*itJet, "pfDeepCSVJetTags:probbb")      );
        vars.FillVars(inputPrefix+"Jet_DeepCSV_c",      iJet,   MiniAODHelper::GetJetCSV_DNN(*itJet, "pfDeepCSVJetTags:probbc")      );
        vars.FillVars(inputPrefix+"Jet_DeepCSV_udsg",   iJet,   MiniAODHelper::GetJetCSV_DNN(*itJet, "pfDeepCSVJetTags:probudsg")    );

        vars.FillVars(inputPrefix+"Jet_Constituents",   iJet,   itJet->nConstituents() );


        } // close jet loop

    // fill Lepton variables
    std::vector<math::XYZTLorentzVector> looseLeptonVecs = BoostedUtils::GetLepVecs(input.selectedElectronsLoose,input.selectedMuonsLoose);
    for( std::vector<math::XYZTLorentzVector>::iterator itLep = looseLeptonVecs.begin(); itLep != looseLeptonVecs.end(); ++itLep ) {
        int iLep = itLep - looseLeptonVecs.begin();

        vars.FillVars(inputPrefix+"Lepton_E",              iLep,   itLep->E()   );
        vars.FillVars(inputPrefix+"Lepton_M",              iLep,   itLep->M()   );
        vars.FillVars(inputPrefix+"Lepton_Pt",             iLep,   itLep->Pt()  );
        vars.FillVars(inputPrefix+"Lepton_Phi",            iLep,   itLep->Phi() );
        vars.FillVars(inputPrefix+"Lepton_Eta",            iLep,   itLep->Eta() );
        vars.FillVars(inputPrefix+"Lepton_Px",             iLep,   itLep->Px()  );
        vars.FillVars(inputPrefix+"Lepton_Py",             iLep,   itLep->Py()  );
        vars.FillVars(inputPrefix+"Lepton_Pz",             iLep,   itLep->Pz()  );

        vars.FillVars(inputPrefix+"Lepton_CSV",            iLep,   0.);
        vars.FillVars(inputPrefix+"Lepton_CSV_DNN",        iLep,   0.);

        vars.FillVars(inputPrefix+"Lepton_DeepFlavor_b",   iLep,   0.);
        vars.FillVars(inputPrefix+"Lepton_DeepFlavor_bb",  iLep,   0.);
        vars.FillVars(inputPrefix+"Lepton_DeepFlavor_c",   iLep,   0.);
        vars.FillVars(inputPrefix+"Lepton_DeepFlavor_uds", iLep,   0.);
        vars.FillVars(inputPrefix+"Lepton_DeepFlavor_g",   iLep,   0.);
        vars.FillVars(inputPrefix+"Lepton_DeepFlavor_lepb",iLep,   0.);

        vars.FillVars(inputPrefix+"Lepton_DeepCSV_b",      iLep,   0.);
        vars.FillVars(inputPrefix+"Lepton_DeepCSV_bb",     iLep,   0.);
        vars.FillVars(inputPrefix+"Lepton_DeepCSV_c",      iLep,   0.);
        vars.FillVars(inputPrefix+"Lepton_DeepCSV_udsg",   iLep,   0.);

        vars.FillVars(inputPrefix+"Lepton_Constituents",   iLep,   1);

        } // close lepton loop

    // fill MET variables
    math::XYZTLorentzVector metVec = input.correctedMET.corP4(pat::MET::Type1XY);

    vars.FillVar(inputPrefix+"MET_E",               metVec.E()     );
    vars.FillVar(inputPrefix+"MET_M",               metVec.M()     );
    vars.FillVar(inputPrefix+"MET_Pt",              metVec.Pt()    );
    vars.FillVar(inputPrefix+"MET_Phi",             metVec.Phi()   );
    vars.FillVar(inputPrefix+"MET_Eta",             metVec.Eta()   );
    vars.FillVar(inputPrefix+"MET_Px",              metVec.Px()    );
    vars.FillVar(inputPrefix+"MET_Py",              metVec.Py()    );
    vars.FillVar(inputPrefix+"MET_Pz",              metVec.Pz()    );
    vars.FillVar(inputPrefix+"MET_CSV",             0.  );
    vars.FillVar(inputPrefix+"MET_CSV_DNN",         0.  );
    vars.FillVar(inputPrefix+"MET_DeepFlavor_b",    0.  );
    vars.FillVar(inputPrefix+"MET_DeepFlavor_bb",   0.  );
    vars.FillVar(inputPrefix+"MET_DeepFlavor_c",    0.  );
    vars.FillVar(inputPrefix+"MET_DeepFlavor_uds",  0.  );
    vars.FillVar(inputPrefix+"MET_DeepFlavor_g",    0.  );
    vars.FillVar(inputPrefix+"MET_DeepFlavor_lepb", 0.  );
    vars.FillVar(inputPrefix+"MET_DeepCSV_b",       0.  );
    vars.FillVar(inputPrefix+"MET_DeepCSV_bb",      0.  );
    vars.FillVar(inputPrefix+"MET_DeepCSV_c",       0.  );
    vars.FillVar(inputPrefix+"MET_DeepCSV_udsg",    0.  );
    vars.FillVar(inputPrefix+"MET_Constituents",    1.  );


    // add gen level variables
    if( input.genTopEvt.IsFilled() && input.genTopEvt.IsSemiLepton() ) {

        // hadronic top
        reco::GenParticle hadtop = input.genTopEvt.GetTopHad();
        FillTargetVariables(hadtop, "HadTop",   vars);

        // leptonic top 
        reco::GenParticle leptop = input.genTopEvt.GetTopLep();
        FillTargetVariables(leptop, "LepTop",   vars);

        // hadronic b
        reco::GenParticle hadb   = input.genTopEvt.GetTopHadDecayQuark();
        FillTargetVariables(hadb,   "HadB",     vars);    

        // leptonic b
        reco::GenParticle lepb   = input.genTopEvt.GetTopLepDecayQuark();
        FillTargetVariables(lepb,   "LepB",     vars);    

        // hadronic W
        reco::GenParticle hadW   = input.genTopEvt.GetWhad();
        FillTargetVariables(hadW,   "HadW",     vars);

        // leptonic W
        reco::GenParticle lepW   = input.genTopEvt.GetWlep();
        FillTargetVariables(lepW,   "LepW",     vars);

        // lepton
        reco::GenParticle lepton = input.genTopEvt.GetLepton();
        FillTargetVariables(lepton, "Lepton",   vars);

        // lf quarks
        std::vector<reco::GenParticle> hadQs = input.genTopEvt.GetWQuarks();
        if( !(hadQs.size() == 2) ){ std::cout << "UNEQUAL TWO QUARKS FROM HADRONIC W" << std::endl; }
        FillTargetVariables(hadQs[0], "Q1",     vars);
        if( hadQs.size() >= 2){
            FillTargetVariables(hadQs[1], "Q2",     vars);
            }
    
        } // close gen level filling
    

    } // close Process


void ttEventRecoTrainVariablesProcessor::FillTargetVariables(const reco::GenParticle &particle, const std::string &name, VariableContainer &vars) {

    vars.FillVar(targetPrefix+name+"_E",    particle.energy()   );    
    vars.FillVar(targetPrefix+name+"_M",    particle.mass()     );    
    vars.FillVar(targetPrefix+name+"_Pt",   particle.pt()       );    
    vars.FillVar(targetPrefix+name+"_Phi",  particle.phi()      );    
    vars.FillVar(targetPrefix+name+"_Eta",  particle.eta()      );    
    vars.FillVar(targetPrefix+name+"_Px",   particle.px()       );    
    vars.FillVar(targetPrefix+name+"_Py",   particle.py()       );    
    vars.FillVar(targetPrefix+name+"_Pz",   particle.pz()       );    

    } // close FillTargetVariables
