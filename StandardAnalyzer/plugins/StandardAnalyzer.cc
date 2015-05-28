// -*- C++ -*-
//
// Package:    BoostedTTH/StandardAnalyzer
// Class:      StandardAnalyzer
// 
/**\class StandardAnalyzer StandardAnalyzer.cc BoostedTTH/StandardAnalyzer/plugins/StandardAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Tobias Pfotzer
//         Created:  Thu, 28 May 2015 08:06:53 GMT
//
//


// system include files
#include <memory>

// user include files

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "DataFormats/METReco/interface/HcalNoiseSummary.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"

#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/InputCollections.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/Cutflow.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TreeWriter.hpp"

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/LeptonSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/JetTagSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/VertexSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/HbbSelection.hpp"

#include "BoostedTTH/BoostedAnalyzer/interface/WeightProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/MCMatchVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/MVAVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BDTVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedJetVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/ttHVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/EventInfo.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"

//
// class declaration
//

class StandardAnalyzer : public edm::EDAnalyzer {
   public:
      explicit StandardAnalyzer(const edm::ParameterSet&);
      ~StandardAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------

      /** the miniAODhelper is used for selections and reweighting */
      MiniAODHelper helper;
      
      /** writes flat trees for MVA analysis */
      TreeWriter treewriter;
      
      /** stores cutflow*/
      Cutflow cutflow;
      
      /** selections that are applied */
      vector<Selection*> selections;
      
      /** triggers that are checked */
      vector<std::string> relevantTriggers;
      
      /** files to dump eventnumber into */
      vector<std::ofstream*> dumpFiles;
      
      /** sample ID */
      int sampleID;
      
      /** stops the time needed */
      TStopwatch watch;
      
      /** events to be analyzed */
      int maxEvents;
      
      /** data luminosity */
      float luminosity;
      
      /** sample cross section*/
      float xs;
      
      /** total number of events in input file(s) */
      int totalMCevents;
     
      /** Event counter */
      int eventcount;
      
       /** is analyzed sample data? */
      bool isData;
      
       /** use GenBmatching info? this is only possible if the miniAOD contains them */
      bool useGenHadronMatch;
      
      /** jet systematic that is applied (the outher systematics are done at a different place with reweighting)*/
      sysType::sysType jsystype;
      
      // TOKENS =========================
      
      /** pu summary data access token **/
      edm::EDGetTokenT< std::vector<PileupSummaryInfo> > EDMPUInfoToken;
      
      /** hcal noise data access token **/
      edm::EDGetTokenT< HcalNoiseSummary > EDMHcalNoiseToken;
      
      /** selected trigger data access token **/
      edm::EDGetTokenT< pat::TriggerObjectStandAloneCollection > EDMSelectedTriggerToken;
      
      /** trigger results data access token **/
      edm::EDGetTokenT< edm::TriggerResults > EDMTriggerResultToken;
      HLTConfigProvider hlt_config;
      
      /** beam spot data access token **/
      edm::EDGetTokenT< reco::BeamSpot > EDMBeamSpotToken;
      
      /** vertex data access token **/
      edm::EDGetTokenT< reco::VertexCollection > EDMVertexToken;
      
      /** muons data access token **/
      edm::EDGetTokenT< std::vector<pat::Muon> > EDMMuonsToken;
      
      /** electrons data access token **/
      edm::EDGetTokenT< std::vector<pat::Electron> > EDMElectronsToken;
      
      /** jets data access token **/
      edm::EDGetTokenT< std::vector<pat::Jet> > EDMJetsToken;
      
      /** mets data access token **/
      edm::EDGetTokenT< std::vector<pat::MET> > EDMMETsToken;
      
      /** gen info data access token **/
      edm::EDGetTokenT< GenEventInfoProduct > EDMGenInfoToken;
      
      /** gen particles data access token **/
      edm::EDGetTokenT< std::vector<reco::GenParticle> > EDMGenParticlesToken;
      
      /** gen jets data access token **/
      edm::EDGetTokenT< std::vector<reco::GenJet> > EDMGenJetsToken;
      
      /** custom genjets for tt+X categorization **/
      edm::EDGetTokenT< std::vector<reco::GenJet> > EDMCustomGenJetsToken;
      
      /** tt+X categorization tokens **/
      edm::EDGetTokenT<std::vector<int> > genBHadJetIndexToken;
      edm::EDGetTokenT<std::vector<int> > genBHadFlavourToken;
      edm::EDGetTokenT<std::vector<int> > genBHadFromTopWeakDecayToken;
      edm::EDGetTokenT<std::vector<reco::GenParticle> > genBHadPlusMothersToken;
      edm::EDGetTokenT<std::vector<std::vector<int> > > genBHadPlusMothersIndicesToken;
      edm::EDGetTokenT<std::vector<int> > genBHadIndexToken;
      edm::EDGetTokenT<std::vector<int> > genBHadLeptonHadronIndexToken;
      edm::EDGetTokenT<std::vector<int> > genBHadLeptonViaTauToken;
      edm::EDGetTokenT<std::vector<int> > genCHadJetIndexToken;
      edm::EDGetTokenT<std::vector<int> > genCHadFlavourToken;
      edm::EDGetTokenT<std::vector<int> > genCHadFromTopWeakDecayToken;
      edm::EDGetTokenT<std::vector<int> > genCHadBHadronIdToken;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
StandardAnalyzer::StandardAnalyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

}


StandardAnalyzer::~StandardAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
StandardAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;



#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
StandardAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
StandardAnalyzer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
/*
void 
StandardAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
StandardAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
StandardAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
StandardAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
StandardAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(StandardAnalyzer);
