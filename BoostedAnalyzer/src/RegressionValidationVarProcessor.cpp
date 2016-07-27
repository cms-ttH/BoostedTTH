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
    double unregJetpT= 0;
    double regJetpT = 0;
    double genjetpT = 0;
    double genjetwNupT = 0;
    bool allwgenjet = true;
    bool allwgenjetwNu = true;
    for( size_t i = 0; i < regressedJets.size(); i++){

        unregJetpT = regJetpT + input.selectedJetsLoose[i].pt();
        regJetpT = regJetpT + regressedJets[i].pt();
        if(regressedJets[i].genJet()!=NULL){
            genjetpT = genjetpT + regressedJets[i].genJet()->pt();
        }
        else {
            allwgenjet = false;
        }
        if( regressedJets[i].hasUserFloat("matchedGenJetwNuPt") ){
            genjetpT = genjetpT + regressedJets[i].userFloat("matchedGenJetwNuPt");
        }
        else {
            allwgenjetwNu = false;
        }

    }


    vars.FillVar("Evt_JetpT_noreg",unregJetpT);
    vars.FillVar("Evt_JetpT_reg",regJetpT);

    double llmass = 0;
    double llpt = 0;

    if(input.selectedMuonsDL.size()>=2){

      math::XYZTLorentzVector DiMuonVec=input.selectedMuonsDL[0].p4()+input.selectedMuonsDL[1].p4();

      vars.FillVar("Evt_llMass",DiMuonVec.M() );
      vars.FillVar("Evt_llpT",DiMuonVec.Pt() );

      llmass = DiMuonVec.M();
      llpt = DiMuonVec.Pt();
    }

    if(input.selectedElectronsDL.size()>=2){

      math::XYZTLorentzVector DiElectronVec=input.selectedElectronsDL[0].p4()+input.selectedElectronsDL[1].p4();

      vars.FillVar("Evt_llMass",DiElectronVec.M() );
      vars.FillVar("Evt_llpT",DiElectronVec.Pt() );

      llmass = DiElectronVec.M();
      llpt = DiElectronVec.Pt();

    }

    if(input.selectedElectronsDL.size()>=1&&input.selectedMuonsDL.size()>=1){

      math::XYZTLorentzVector ElMuVec=input.selectedElectronsDL[0].p4()+input.selectedMuonsDL[0].p4();

      vars.FillVar("Evt_llMass",ElMuVec.M() );
      vars.FillVar("Evt_llpT",ElMuVec.Pt() );
      llmass = ElMuVec.M();
      llpt = ElMuVec.Pt();

    }

    if( llmass != 0 ){
        vars.FillVar("Evt_PtBal_noreg",unregJetpT / llpt);
        vars.FillVar("Evt_PtBal_reg",regJetpT / llpt);
        if (allwgenjet && genjetpT > 0){
            vars.FillVar("Evt_PtBal_genJet",genjetpT/llpt);
        }
        else {
            vars.FillVar("Evt_PtBal_genJet",-0.2);
        }
        if (allwgenjetwNu){
            vars.FillVar("Evt_PtBal_genJetwNu",genjetwNupT/llpt);
        }
        else {
            vars.FillVar("Evt_PtBal_genJetwNu",-0.2);
        }
    }
    else{
        vars.FillVar("Evt_PtBal_noreg",-0.2);
        vars.FillVar("Evt_PtBal_reg",-0.2);
        vars.FillVar("Evt_PtBal_genJet",-0.2);
        vars.FillVar("Evt_PtBal_genJetwNu",-0.2);
    }

}
