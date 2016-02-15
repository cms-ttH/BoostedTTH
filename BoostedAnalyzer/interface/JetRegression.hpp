#ifndef BOOSTEDTTH_BOOSTEDANALYZER_JETREGRESSION_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_JETREGRESSION_HPP

#include <map>
#include <vector>
#include <cmath>
#include <typeinfo>

#include "TMVA/Reader.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"


class JetRegression {

public:
  JetRegression( );   //Constructor: Read Wight file

  void evaluateRegression(const  edm::Event& iEvent,
			  const reco::VertexCollection& Vertices,
			  const  edm::EDGetTokenT< edm::View<pat::Electron> >& electronToken,
			  const  edm::EDGetTokenT< std::vector<pat::Muon> >& muonToken,
			  const  edm::EDGetTokenT <double>& rhoToken,
			  const  edm::EDGetTokenT< std::vector<pat::Jet> >& jetToken,
			  std::vector<pat::Jet>& Jets);   //evaluate regression: Input: event, add new pt als userfloat after evaluation

  std::vector<pat::Jet> GetCorrectedJetswbReg(const std::vector<pat::Jet>& Jets);

  bool IsRegressionDone();

private:
  bool setInclusiveLeptons(const std::vector<pat::Electron>& electrons, 
			   const std::vector<pat::Muon>& muons,
			   const reco::VertexCollection& Vertices);

  bool matchLeptonswithJets(const std::vector<pat::Electron>& electrons, 
			    const std::vector<pat::Muon>& muons, 
			    const std::vector<pat::Jet>& jets,
			    const reco::VertexCollection& Vertices); //Match Leptons with Jets for small dR differences

  float leadingTrackpT(const pat::Jet& jet);
  

  std::vector<pat::Electron> inclusiveElectrons;
  std::vector<pat::Muon> inclusiveMuons;

  std::map<pat::Electron*, const pat::Jet*> ElectronJetPairs;
  std::map<pat::Muon*, const pat::Jet*> MuonJetPairs;

  TMVA::Reader* reader;

  std::string name = "";
  std::string weightfile = "";
  std::vector<float> treevars;
  std::vector<float> treespec;

  float epTCut;
  float eetaCut;
  float edxyCut;
  float edzCut;
  float elostHits;


  float mupTCut;
  float muetaCut;
  float mudxyCut;
  float mudzCut;
  
  float deltaR2Max;
  
  bool isDone;
};


#endif
