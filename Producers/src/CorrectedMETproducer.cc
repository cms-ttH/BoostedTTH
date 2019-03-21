#include "BoostedTTH/Producers/interface/CorrectedMETproducer.h"


CorrectedMETproducer::CorrectedMETproducer(const edm::ParameterSet& iConfig) :  oldJetsToken{consumes< std::vector<pat::Jet> >(iConfig.getParameter<edm::InputTag>("oldJets"))},
                                                                                newJetsToken{consumes< std::vector<pat::Jet> >(iConfig.getParameter<edm::InputTag>("newJets"))},
                                                                                
                                                                                oldElectronsToken{consumes< std::vector<pat::Electron> >(iConfig.getParameter<edm::InputTag>("oldElectrons"))},
                                                                                newElectronsToken{consumes< std::vector<pat::Electron> >(iConfig.getParameter<edm::InputTag>("newElectrons"))},
                                                                                
                                                                                oldMuonsToken{consumes< std::vector<pat::Muon> >(iConfig.getParameter<edm::InputTag>("oldMuons"))},
                                                                                newMuonsToken{consumes< std::vector<pat::Muon> >(iConfig.getParameter<edm::InputTag>("newMuons"))},
                                                                                
                                                                                metsToken{consumes< std::vector<pat::MET> >(iConfig.getParameter<edm::InputTag>("mets"))},
                                                                                collectionName{iConfig.getParameter< std::string>("collectionName")}
{
    produces<pat::METCollection>(collectionName);      
}


CorrectedMETproducer::~CorrectedMETproducer()
{
 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
CorrectedMETproducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle< pat::JetCollection > h_oldJets;
   iEvent.getByToken( oldJetsToken,h_oldJets );
   edm::Handle< pat::JetCollection > h_newJets;
   iEvent.getByToken( newJetsToken,h_newJets );
   
   edm::Handle< pat::ElectronCollection > h_oldElectrons;
   iEvent.getByToken( oldElectronsToken,h_oldElectrons );
   edm::Handle< pat::ElectronCollection > h_newElectrons;
   iEvent.getByToken( newElectronsToken,h_newElectrons );
   
   edm::Handle< pat::MuonCollection > h_oldMuons;
   iEvent.getByToken( oldMuonsToken,h_oldMuons );
   edm::Handle< pat::MuonCollection > h_newMuons;
   iEvent.getByToken( newMuonsToken,h_newMuons );

   edm::Handle< pat::METCollection > h_inputMETs;
   iEvent.getByToken( metsToken,h_inputMETs );

   std::unique_ptr<pat::METCollection> correctedMETs = std::make_unique<pat::METCollection>(CorrectMET(*h_oldJets,*h_newJets,*h_oldElectrons,*h_newElectrons,*h_oldMuons,*h_newMuons,*h_inputMETs));
   iEvent.put(std::move(correctedMETs),collectionName);
   
   
}

std::vector<pat::MET> CorrectedMETproducer::CorrectMET(const std::vector<pat::Jet>& oldJetsForMET, const std::vector<pat::Jet>& newJetsForMET, const std::vector<pat::Electron>& oldElectronsForMET, const std::vector<pat::Electron>& newElectronsForMET, const std::vector<pat::Muon>& oldMuonsForMET, const std::vector<pat::Muon>& newMuonsForMET , const std::vector<pat::MET>& pfMETs) const{
  // this function takes two jet collections and replaces their contribution to the Type1 correction of the MET

  std::vector<pat::MET> outputMets;

  for(std::vector<pat::MET>::const_iterator oldMET=pfMETs.begin();oldMET!=pfMETs.end();++oldMET){
    pat::MET outMET=*oldMET;
    //cout << "before: uncor pt " << outMET.uncorPt() << " cor pt (type1) " << outMET.corPt(pat::MET::Type1) << " cor pt (type1XY) " << outMET.corPt(pat::MET::Type1XY) << endl;
    if(oldMET-pfMETs.begin() == 0){
    //get old MET p4
    reco::Candidate::LorentzVector oldMETVec(oldMET->corPx(pat::MET::Type1),oldMET->corPy(pat::MET::Type1),oldMET->pz(),oldMET->corSumEt(pat::MET::Type1));
    // add the pT vector of the old jets with the initial correction to the MET vector
    for(std::vector<pat::Jet>::const_iterator itJet=oldJetsForMET.begin();itJet!=oldJetsForMET.end();++itJet){
      reco::Candidate::LorentzVector PToldJETVec(itJet->px(),itJet->py(),0.,itJet->et());
      oldMETVec=oldMETVec+PToldJETVec;
    }   
    // add the pT vector of the old electrons with the initial correction to the MET vector
    for(std::vector<pat::Electron>::const_iterator itEle=oldElectronsForMET.begin();itEle!=oldElectronsForMET.end();++itEle){
      reco::Candidate::LorentzVector PToldEleVec(itEle->px(),itEle->py(),0.,itEle->et());
      oldMETVec=oldMETVec+PToldEleVec;
    }
    // add the pT vector of the old muonns with the initial correction to the MET vector
    for(std::vector<pat::Muon>::const_iterator itMu=oldMuonsForMET.begin();itMu!=oldMuonsForMET.end();++itMu){
      reco::Candidate::LorentzVector PToldMuVec(itMu->px(),itMu->py(),0.,itMu->et());
      oldMETVec=oldMETVec+PToldMuVec;
    }
    // now subtract the pT vectors of the clean recorrected jets
    for(std::vector<pat::Jet>::const_iterator itJet=newJetsForMET.begin();itJet!=newJetsForMET.end();++itJet){
      reco::Candidate::LorentzVector PTnewJETVec(itJet->px(),itJet->py(),0.,itJet->et());
      oldMETVec=oldMETVec-PTnewJETVec;
    }
    // now subtract the pT vectors of the recorrected electrons
    for(std::vector<pat::Electron>::const_iterator itEle=newElectronsForMET.begin();itEle!=newElectronsForMET.end();++itEle){
      reco::Candidate::LorentzVector PTnewEleVec(itEle->px(),itEle->py(),0.,itEle->et());
      oldMETVec=oldMETVec-PTnewEleVec;
    }
    // now subtract the pT vectors of the recorrected muons
    for(std::vector<pat::Muon>::const_iterator itMu=newMuonsForMET.begin();itMu!=newMuonsForMET.end();++itMu){
      reco::Candidate::LorentzVector PTnewMuVec(itMu->px(),itMu->py(),0.,itMu->et());
      oldMETVec=oldMETVec-PTnewMuVec;
    }
    outMET.setP4(oldMETVec);
    //cout << "after: uncor pt " << outMET.uncorPt() << " cor pt (type1) " << outMET.corPt(pat::MET::Type1) << " cor pt (type1XY) " << outMET.corPt(pat::MET::Type1XY) << endl;
    }

    outputMets.push_back(outMET);
  }

  return outputMets;
  
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
CorrectedMETproducer::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
CorrectedMETproducer::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
CorrectedMETproducer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
CorrectedMETproducer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
CorrectedMETproducer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
CorrectedMETproducer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
CorrectedMETproducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
//DEFINE_FWK_MODULE(CorrectedMETproducer);
