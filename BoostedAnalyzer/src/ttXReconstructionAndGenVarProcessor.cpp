#include "BoostedTTH/BoostedAnalyzer/interface/ttXReconstructionAndGenVarProcessor.hpp"

using namespace std;

ttXReconstructionAndGenVarProcessor::ttXReconstructionAndGenVarProcessor() {
    recoPrefix = "recoTTX";
    genPrefix  = "genTTX";
    }

ttXReconstructionAndGenVarProcessor::~ttXReconstructionAndGenVarProcessor() {}


void ttXReconstructionAndGenVarProcessor::Init(const InputCollections &input, VariableContainer &vars) {

    // SIMPLE KINEMATIC VARIABLES
    InitSimpleKinematicVariables("TopHad",  vars);
    InitSimpleKinematicVariables("TopLep",  vars);
    InitSimpleKinematicVariables("BHad",    vars);
    InitSimpleKinematicVariables("BLep",    vars);
    InitSimpleKinematicVariables("WHad",    vars);
    InitSimpleKinematicVariables("WLep",    vars);
    InitSimpleKinematicVariables("Lepton",  vars);

    InitSimpleKinematicVariables("Boson",   vars);

    // ANGULAR DIFFERENCES
    InitAngularDifferences("TopHad", "TopLep", vars);
    InitAngularDifferences("BHad",   "BLep",   vars);
    InitAngularDifferences("BHad",   "Lepton", vars);

    InitAngularDifferences("Boson",  "TopHad", vars);
    InitAngularDifferences("Boson",  "TopLep", vars);
    InitAngularDifferences("Boson",  "Lepton", vars);

    // FLAGS
    vars.InitVar("genTopIsFilled", 0, "I");
    vars.InitVar("genTTXIsFilled", 0, "I");
    vars.InitVar("genTopIsSL", 0, "I");

    // QUALITY CONTROL VALUES
    vars.InitVar("TTXmatcher_chi2", "F");

    initialized = true;
    } // close init




void ttXReconstructionAndGenVarProcessor::Process(const InputCollections &input, VariableContainer &vars) {
    if( !initialized ) cerr << "tree processor not initialized" << endl;
    if(input.selectedJets.size() < 4) return;

    if( input.genTopEvt.IsFilled())     vars.FillVar("genTopIsFilled", 1);
    if( input.genTopEvt.IsSemiLepton()) vars.FillVar("genTopIsSL", 1);

    if( input.genTopEvt.IsFilled() && input.genTopEvt.IsSemiLepton() ) {
        // Generator Level

        // LOAD PARTICLES
        // hadronic top
        reco::GenParticle topHad = input.genTopEvt.GetTopHad();
        // leptonic top 
        reco::GenParticle topLep = input.genTopEvt.GetTopLep();
        // hadronic b
        reco::GenParticle bHad   = input.genTopEvt.GetTopHadDecayQuark();
        // leptonic b
        reco::GenParticle bLep   = input.genTopEvt.GetTopLepDecayQuark();
        // hadronic W
        reco::GenParticle WHad   = input.genTopEvt.GetWhad();
        // leptonic W
        reco::GenParticle WLep   = input.genTopEvt.GetWlep();
        // lepton
        reco::GenParticle lepton = input.genTopEvt.GetLepton();
        // lf quarks
        std::vector<reco::GenParticle> hadQs = input.genTopEvt.GetWQuarks();
        if( !(hadQs.size() == 2) ){ std::cout << "UNEQUAL TWO QUARKS FROM HADRONIC W" << std::endl; }

        // higgs boson
        reco::GenParticle higgs  = input.genTopEvt.GetHiggs();
        // higgs decay quarks
        std::vector<reco::GenParticle> higgsBs = input.genTopEvt.GetHiggsDecayProducts();
        if( !(higgsBs.size() == 2) ){ std::cout << "UNEQUAL TWO BS FROM HIGGS" << std::endl; }


        // Reconstruction Level
        // dont fill stuff if not at least one lepton
        if( input.selectedElectrons.size() + input.selectedMuons.size() < 1 ) return;
        
        // generate best interpretation
        Interpretation *recoTTX = 0;
        if( input.selectedJets.size() < 6) {
            recoTTX = GetTTXInterpretation(input, vars ); }
        else {
            recoTTX = GetTTXInterpretation(input, vars ); }
        //if( recoTTX == 0 ) return;

        // SIMPLE KINEMATIC VARIABLES
        FillSimpleKinematicVariables("TopHad",  topHad, recoTTX->TopHad(),  vars);
        FillSimpleKinematicVariables("TopLep",  topLep, recoTTX->TopLep(),  vars);
        FillSimpleKinematicVariables("BHad",    bHad,   recoTTX->BHad(),    vars);
        FillSimpleKinematicVariables("BLep",    bLep,   recoTTX->BLep(),    vars);
        FillSimpleKinematicVariables("WHad",    WHad,   recoTTX->WHad(),    vars);
        FillSimpleKinematicVariables("WLep",    WLep,   recoTTX->WLep(),    vars);
        FillSimpleKinematicVariables("Lepton",  lepton, recoTTX->Lep(),     vars);
    
        // ANGULAR DIFFERENCES
        FillAngularDifferences("TopHad", "TopLep", topHad, topLep, recoTTX->TopHad(), recoTTX->TopLep(), vars);
        FillAngularDifferences("BHad",   "BLep",   bHad,   bLep,   recoTTX->BHad(),   recoTTX->BLep(),   vars);
        FillAngularDifferences("BHad",   "Lepton", bHad,   lepton, recoTTX->BHad(),   recoTTX->Lep(),    vars);

        if( input.selectedJets.size() >= 6 ) {
            FillSimpleKinematicVariables("Boson", higgs, recoTTX->Higgs(), vars);

            FillAngularDifferences("Boson", "TopHad", higgs, topHad, recoTTX->Higgs(), recoTTX->TopHad(), vars);
            FillAngularDifferences("Boson", "TopLep", higgs, topLep, recoTTX->Higgs(), recoTTX->TopLep(), vars);
            FillAngularDifferences("Boson", "Lepton", higgs, lepton, recoTTX->Higgs(), recoTTX->Lep(), vars);
            }        


        } // end of if filled
    } // close process





Interpretation *ttXReconstructionAndGenVarProcessor::GetTTXInterpretation( const InputCollections &input, VariableContainer &vars ) {
    // get jet vectors
    vector<TLorentzVector> jetVecs = BoostedUtils::GetTLorentzVectors( BoostedUtils::GetJetVecs(input.selectedJets) );

    // fill CSV values
    vector<float> jetCSVs;
    int nTags = 0;
    for( auto j = input.selectedJets.begin(); j!=input.selectedJets.end(); j++ ) {
        jetCSVs.push_back( MiniAODHelper::GetJetCSV(*j, "DeepCSV") );
        if( BoostedUtils::PassesCSV(*j) ) nTags++;
        }

    // get lepton vector
    TLorentzVector lepVec = BoostedUtils::GetTLorentzVector( BoostedUtils::GetPrimLepVec( input.selectedElectrons, input.selectedMuons ) );
    
    // get MET vector
    TVector2 metVec(input.correctedMET.corP4(pat::MET::Type1XY).px(), input.correctedMET.corP4(pat::MET::Type1XY).py());

    // Generate Interpretations
    // Interpretation **ints = generator.GenerateTTHInterpretations( jetVecs, jetCSVs, lepVec, metVec );
    Interpretation **ints = generator.GenerateNJetDependentInterpretations( jetVecs, jetCSVs, lepVec, metVec );
    uint nInts = generator.GetNints();

    // find best interpretation
    Interpretation *bestInterpretation = 0;

    float best_chi2 = -99999;

    // loop over all interpretations and calculate chi2 values
    for( uint i = 0; i < nInts; i++ ) {
        float chi2 = -99999;
        if( jetVecs.size() < 6 ) {
            chi2 = quality.TTChi2( *(ints[i]) );
            }
        else {
            chi2 = quality.TTHChi2( *(ints[i]) );
            }

        if( chi2 > best_chi2 ) {
            best_chi2 = chi2;
            bestInterpretation = ints[i];
            } 
        }

    // fill chi2
    vars.FillVar("TTXmatcher_chi2", best_chi2);

    return bestInterpretation;


    } // close GetTTInterpretation

    

void ttXReconstructionAndGenVarProcessor::InitSimpleKinematicVariables(const std::string &name, VariableContainer &vars) {
    // Eta 
    vars.InitVar( genPrefix+"_Eta_"+name    );
    vars.InitVar(recoPrefix+"_Eta_"+name    );

    // pT
    vars.InitVar( genPrefix+"_pT_"+name     );
    vars.InitVar(recoPrefix+"_pT_"+name     );

    // theta
    vars.InitVar( genPrefix+"_Theta_"+name  );
    vars.InitVar(recoPrefix+"_Theta_"+name  );

    // Mass
    vars.InitVar( genPrefix+"_M_"+name      );
    vars.InitVar(recoPrefix+"_M_"+name      );

    // deltaR reconstruction/gen
    vars.InitVar(recoPrefix+"_GENdR_"+name  );

    } // close InitSimpleKinematicVariables

void ttXReconstructionAndGenVarProcessor::FillSimpleKinematicVariables(const std::string &name, const reco::GenParticle &genParticle, const TLorentzVector &recoParticle, VariableContainer &vars) {
    
    // Eta 
    vars.FillVar( genPrefix+"_Eta_"+name,    genParticle.eta()  );
    vars.FillVar(recoPrefix+"_Eta_"+name,   recoParticle.Eta()  );

    // pT
    vars.FillVar( genPrefix+"_pT_"+name,     genParticle.pt()   );
    vars.FillVar(recoPrefix+"_pT_"+name,    recoParticle.Pt()   );

    // theta
    vars.FillVar( genPrefix+"_Theta_"+name,  genParticle.theta());
    vars.FillVar(recoPrefix+"_Theta_"+name, recoParticle.Theta());

    // Mass
    vars.FillVar( genPrefix+"_M_"+name,      genParticle.mass() );
    vars.FillVar(recoPrefix+"_M_"+name,     recoParticle.M()    );

    // deltaR reconstruction/gen
    float dphi = fabs( genParticle.phi() - recoParticle.Phi() );
    if( dphi > M_PI ) dphi = 2.*M_PI - dphi;
    float deta = fabs( genParticle.eta() - recoParticle.Eta() );
    float dR2 = dphi*dphi + deta*deta;
    vars.FillVar(recoPrefix+"_GENdR_"+name, sqrt(dR2));

    } // close FillSimpleKinematicVariables


void ttXReconstructionAndGenVarProcessor::InitAngularDifferences(const std::string &name1, const std::string &name2, VariableContainer &vars) {

    // deltaEta
    vars.InitVar( genPrefix+"_DeltaEta_"+name1+"_"+name2   );
    vars.InitVar(recoPrefix+"_DeltaEta_"+name1+"_"+name2   );

    // deltaPhi
    vars.InitVar( genPrefix+"_DeltaPhi_"+name1+"_"+name2   );
    vars.InitVar(recoPrefix+"_DeltaPhi_"+name1+"_"+name2   );

    // deltaTheta
    vars.InitVar( genPrefix+"_DeltaTheta_"+name1+"_"+name2 );
    vars.InitVar(recoPrefix+"_DeltaTheta_"+name1+"_"+name2 );

    } // close InitAngularDifferences


void ttXReconstructionAndGenVarProcessor::FillAngularDifferences(const std::string &name1, const std::string &name2, const reco::GenParticle &gen1, const reco::GenParticle &gen2, const TLorentzVector &reco1, const TLorentzVector &reco2, VariableContainer &vars) {

    // deltaEta
    vars.FillVar( genPrefix+"_DeltaEta_"+name1+"_"+name2,   fabs(gen1.eta()  - gen2.eta() )   );
    vars.FillVar(recoPrefix+"_DeltaEta_"+name1+"_"+name2,   fabs(reco1.Eta() - reco2.Eta())   );

    // deltaPhi TODO fix
    float dphi_gen = fabs( gen1.phi() - gen2.phi() );
    if( dphi_gen > M_PI ) dphi_gen = 2.*M_PI - dphi_gen;
    vars.FillVar( genPrefix+"_DeltaPhi_"+name1+"_"+name2,   dphi_gen   );

    float dphi_reco = fabs( reco1.Phi() - reco2.Phi() );
    if( dphi_reco > M_PI ) dphi_reco = 2.*M_PI - dphi_reco;    
    vars.FillVar(recoPrefix+"_DeltaPhi_"+name1+"_"+name2,   dphi_reco   );

    // deltaTheta
    vars.FillVar( genPrefix+"_DeltaTheta_"+name1+"_"+name2, fabs(gen1.theta()  - gen2.theta() ) );
    vars.FillVar(recoPrefix+"_DeltaTheta_"+name1+"_"+name2, fabs(reco1.Theta() - reco2.Theta()) );

    } // close FillAngularDifferences
