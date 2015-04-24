#ifndef SYNCHSELECTION_HPP
#define SYNCHSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include <stdio.h>
#include <string.h>
#include "JetMETCorrections/Objects/interface/JetCorrector.h"



class SynchSelection: public Selection{
  
public:
    
  SynchSelection();
  ~SynchSelection();
  void Init(const edm::ParameterSet& iConfig, Cutflow& cutflow);
  bool IsSelected(const InputCollections& input,Cutflow& cutflow);

private:
  
  std::vector<std::string> muonTriggers;
  std::vector<std::string> electronTriggers;
  edm::ParameterSet Config;
  std::string doMode;
  /** pu summary data access token **/
  edm::EDGetTokenT< std::vector<PileupSummaryInfo> > EDMPUInfoToken;
  
  /** hcal noise data access token **/
  edm::EDGetTokenT< HcalNoiseSummary > EDMHcalNoiseToken;
  
  /** selected trigger data access token **/
  edm::EDGetTokenT< pat::TriggerObjectStandAloneCollection > EDMSelectedTriggerToken;
  
  /** trigger results data access token **/
  edm::EDGetTokenT< edm::TriggerResults > EDMTriggerResultToken;
  HLTConfigProvider hlt_config_;
  
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
  
  /** hep top jets data access token **/
  edm::EDGetTokenT< boosted::HEPTopJetCollection > EDMHEPTopJetsToken;
  
  /** subjet filterjets data access token **/
  edm::EDGetTokenT< boosted::SubFilterJetCollection > EDMSubFilterJetsToken;
  
  /** gen info data access token **/
  edm::EDGetTokenT< GenEventInfoProduct > EDMGenInfoToken;
  
  /** gen particles data access token **/
  edm::EDGetTokenT< std::vector<reco::GenParticle> > EDMGenParticlesToken;
  
  /** gen jets data access token **/
  edm::EDGetTokenT< std::vector<reco::GenJet> > EDMGenJetsToken;
};

#endif
