#include "BoostedTTH/BoostedAnalyzer/interface/RegressionValidationVarProcessor.hpp"

using namespace std;

RegressionValidationVarProcessor::RegressionValidationVarProcessor(edm::ConsumesCollector && iC, std::vector<edm::InputTag> regJetCollections){

    //TODO: This only works if the collections are the systematic shifted Collections --> Think about something
    //when using multiple collections
    for(auto &tag : regJetCollections){
        regressedJetsTokens.push_back(iC.consumes< std::vector<pat::Jet> >(tag));
    }
}
RegressionValidationVarProcessor::~RegressionValidationVarProcessor(){}


void RegressionValidationVarProcessor::Init(const InputCollections& input,VariableContainer& vars){

    //pT balace variables
    vars.InitVar("Evt_PtBal_noreg", "F");
    vars.InitVar("Evt_JetpT_noreg","F");

    vars.InitVar("Evt_PtBal_reg","F");
    vars.InitVar("Evt_JetpT_reg","F");

    vars.InitVar("Evt_llMass","F");
    vars.InitVar("Evt_llpT","F");

    vars.InitVar("Evt_PtBal_genJet","F");
    vars.InitVar("Evt_PtBal_genJetwNu","F");
}


void RegressionValidationVarProcessor::Process(const InputCollections& input, VariableContainer& vars) {

    //Get Regressed Jets for current systematics
    edm::Handle < std::vector< pat::Jet > > h_regressedJets;
    input.iEvent.getByToken( regressedJetsTokens[input.isys], h_regressedJets );
    std::vector<pat::Jet> const &regressedJets = *h_regressedJets;



    //Compute validation variables
    bool allwgenjet = true;
    bool allwgenjetwNu = true;
    TLorentzVector vec_noregsum;
    TLorentzVector vec_regsum;
    TLorentzVector vec_genjetsum;
    TLorentzVector vec_genjetwNusum;


    for( size_t i = 0; i < regressedJets.size(); i++){

        TLorentzVector vec_noreg;
        TLorentzVector vec_reg;
        TLorentzVector vec_genjet;
        TLorentzVector vec_genjetwNu;

        vec_noreg.SetPtEtaPhiM( input.selectedJetsLoose[i].pt(),  input.selectedJetsLoose[i].eta(),
                                input.selectedJetsLoose[i].phi(), input.selectedJetsLoose[i].mass());
        vec_reg.SetPtEtaPhiM( regressedJets[i].pt(),  regressedJets[i].eta(),
                              regressedJets[i].phi(), regressedJets[i].mass() ) ;

        vec_noregsum = vec_noregsum + vec_noreg;
        vec_regsum = vec_regsum + vec_reg;


        if(regressedJets[i].genJet()!=NULL){
            vec_genjet.SetPtEtaPhiM( regressedJets[i].genJet()->pt(),  regressedJets[i].genJet()->eta(),
                                     regressedJets[i].genJet()->phi(), regressedJets[i].genJet()->mass() );
            vec_genjetsum = vec_genjetsum + vec_genjet;
        }
        else {
            allwgenjet = false;
        }
        if( regressedJets[i].hasUserFloat("matchedGenJetwNuPt") ){
            vec_genjetwNu.SetPtEtaPhiM( regressedJets[i].userFloat("matchedGenJetwNuPt"),  regressedJets[i].userFloat("matchedGenJetwNuEta"),
                                        regressedJets[i].userFloat("matchedGenJetwNuPhi"), regressedJets[i].userFloat("matchedGenJetwNuM") );
            vec_genjetwNusum = vec_genjetwNusum + vec_genjetwNu;
        }
        else {
            allwgenjetwNu = false;
        }

    }

    vars.FillVar( "Evt_JetpT_noreg",vec_noregsum.Pt() );
    vars.FillVar( "Evt_JetpT_reg",vec_regsum.Pt() );

    double llmass = 0;
    double llpt = 0;

    if(input.selectedMuonsDL.size()>=2){

      math::XYZTLorentzVector DiMuonVec=input.selectedMuonsDL[0].p4()+input.selectedMuonsDL[1].p4();

      vars.FillVar( "Evt_llMass",DiMuonVec.M() );
      vars.FillVar( "Evt_llpT",DiMuonVec.Pt() );

      llmass = DiMuonVec.M();
      llpt = DiMuonVec.Pt();
    }

    if(input.selectedElectronsDL.size()>=2){

      math::XYZTLorentzVector DiElectronVec=input.selectedElectronsDL[0].p4()+input.selectedElectronsDL[1].p4();

      vars.FillVar( "Evt_llMass",DiElectronVec.M() );
      vars.FillVar( "Evt_llpT",DiElectronVec.Pt() );

      llmass = DiElectronVec.M();
      llpt = DiElectronVec.Pt();

    }

    if(input.selectedElectronsDL.size()>=1&&input.selectedMuonsDL.size()>=1){

      math::XYZTLorentzVector ElMuVec=input.selectedElectronsDL[0].p4()+input.selectedMuonsDL[0].p4();

      vars.FillVar( "Evt_llMass",ElMuVec.M() );
      vars.FillVar( "Evt_llpT",ElMuVec.Pt() );
      llmass = ElMuVec.M();
      llpt = ElMuVec.Pt();

    }

    if( llmass != 0 ){
        vars.FillVar( "Evt_PtBal_noreg", vec_noregsum.Pt() / llpt );
        vars.FillVar( "Evt_PtBal_reg", vec_regsum.Pt() / llpt );
        if ( allwgenjet && vec_genjetsum.Pt() > 0 ){
            vars.FillVar( "Evt_PtBal_genJet",vec_genjetsum.Pt()/llpt );
        }
        else {
            vars.FillVar( "Evt_PtBal_genJet",-0.2 );
        }
        if ( allwgenjetwNu ){
            vars.FillVar( "Evt_PtBal_genJetwNu",vec_genjetwNusum.Pt()/llpt );
        }
        else {
            vars.FillVar( "Evt_PtBal_genJetwNu",-0.2 );
        }
    }
    else{
        vars.FillVar( "Evt_PtBal_noreg",-0.2 );
        vars.FillVar( "Evt_PtBal_reg",-0.2 );
        vars.FillVar( "Evt_PtBal_genJet",-0.2 );
        vars.FillVar( "Evt_PtBal_genJetwNu",-0.2 );
    }

}
