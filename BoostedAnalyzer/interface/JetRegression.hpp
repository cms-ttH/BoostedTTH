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
#include "BoostedTTH/BoostedAnalyzer/interface/GenJetMatcher.hpp"

class JetRegression {

public:
  JetRegression( );

  //JetRegression( std::map < std::string, std::vector < bool >  > WeightsandInputs, std::vector < std::string > names);
  bool init(  std::string weightname  );  

  bool init(  std::string weightname, std::string extention  );

  bool init(  std::vector< std::string > WeightFiles, std::vector<std::vector < bool > >  WeightInputs, std::vector < std::string > names  );

  void evaluateRegression(const  edm::Event& iEvent,
			  const  edm::EDGetTokenT< edm::View<pat::Electron> >& electronToken,
			  const  edm::EDGetTokenT< std::vector<pat::Muon> >& muonToken,
			  const  edm::EDGetTokenT< reco::VertexCollection>& vertexToken,
			  const  edm::EDGetTokenT< std::vector<pat::Jet> >& jetToken,
			  std::vector<pat::Jet>& Jets);   //evaluate regression

  void evaluateRegression(const  edm::Event& iEvent,
			  const  edm::EDGetTokenT< edm::View<pat::Electron> >& electronToken,
			  const  edm::EDGetTokenT< std::vector<pat::Muon> >& muonToken,
			  const  edm::EDGetTokenT< reco::VertexCollection>& vertexToken,
			  const  edm::EDGetTokenT< std::vector<pat::Jet> >& jetToken,
			  std::vector<pat::Jet>& Jets,
			  const std::string prefix,
			  const bool isadditionaltraining = true);   //evaluate regression



  std::vector<pat::Jet> GetRegressedJets(const vector<pat::Jet>& Jets);
  
  void setTightLeptons(const std::vector< pat::Muon >& muons,
		       const std::vector< pat::Electron >& electrons);

  void getSoftLeptons( std::vector< pat:: Muon >& muons,
		       std::vector< pat:: Electron>& electrons);

  bool isRegressionDone();

  bool isRegressionInitialized();
  
  bool isRegressionEvaluated();

  void activateDebugMode();

  void matchGenJetstoJets( std::vector< pat::Jet >& Jets,
			   std::vector< reco::GenJet >& GenJets);

private:
  bool setInclusiveLeptons(const std::vector<pat::Electron>& electrons, 
			   const std::vector<pat::Muon>& muons,
			   const reco::VertexCollection& Vertices);

  bool matchLeptonswithJets(const std::vector<pat::Electron>& raw_electrons, 
			    const std::vector<pat::Muon>& raw_muons, 
			    const std::vector<pat::Jet>& jets,
			    const reco::VertexCollection& Vertices); //Match Leptons with Jets for small dR differences
  
  float leadingTrackpT(const pat::Jet& jet);
  

  std::vector<pat::Electron> inclusiveElectrons;
  std::vector<pat::Muon> inclusiveMuons;

  std::vector<pat::Electron> returnElectrons;
  std::vector<pat::Muon> returnMuons;
  
  std::map<pat::Electron*, const pat::Jet*> ElectronJetPairs;
  std::map<pat::Muon*, const pat::Jet*> MuonJetPairs;

  std::vector< pat::Electron > tightElectrons;
  std::vector< pat::Muon > tightMuons;

  std::vector < std::string > regressionnames;  

  std::map < std::string, TMVA::Reader* > readermap;
  
  std::vector<float> treevars;
  std::vector<float> treespec;

  // Electron Cuts
  float epTCut;
  float eetaCut;
  float edxyCut;
  float edzCut;
  float elostHits;

  //Muon Cuts
  float mupTCut;
  float muetaCut;
  float mudxyCut;
  float mudzCut;
  
  //Other Cuts
  float deltaR2Max;
  
  //State variables
  bool isDone;
  bool isInitialized;
  bool isEvaluated;

  bool excludetightLeptons;
  bool tightLeptonssSet;
  bool returnsoftLeptons;
  
  bool debugmode;
};


#endif
