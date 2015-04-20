#ifndef BOOSTEDTTH_BOOSTEDPRODUCERS_SFJETPRODUCER_H
#define BOOSTEDTTH_BOOSTEDPRODUCERS_SFJETPRODUCER_H 1


/*
  The plugin produces the output of the Subjet/Filter jet reconstruction
  algorithm which was first proposed here: http://arXiv.org/abs/0802.2470
  
  The real work is done in RecoJets/JetAlgorithms/src/SubjetFilterjetAlgorithm.cc
  
  CMSSW implementation by David Lopes-Pegna           <david.lopes-pegna@cern.ch>
                      and Philipp Schieferdecker <philipp.schieferdecker@cern.ch>

  see: https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideSubjetFilterJetProducer

*/

#include "FWCore/Framework/interface/EventSetup.h"
#include "RecoJets/JetAlgorithms/interface/CompoundPseudoJet.h"

#include "RecoJets/JetProducers/plugins/VirtualJetProducer.h"
#include "BoostedTTH/BoostedProducer/interface/SubjetFilterjetAlgorithm.h"
#include "BoostedTTH/BoostedProducer/interface/Nsubjettiness.h"

class SFJetProducer : public VirtualJetProducer
{
	//
	// construction / destruction
	//
	public:
		SFJetProducer(const edm::ParameterSet& ps);
		~SFJetProducer();

	//
	// member functions
	//
	public:
		void produce(edm::Event& iEvent, const edm::EventSetup& iSetup);
		void endJob();
		void runAlgorithm(edm::Event& iEvent, const edm::EventSetup& iSetup);
		void inputTowers();
		void output(edm::Event& iEvent,const edm::EventSetup& iSetup);
		template<class T>
		void writeCompoundJets(edm::Event& iEvent,const edm::EventSetup& iSetup);

	//
	// member data
	//
	private:
		SubjetFilterjetAlgorithm				alg_;
		fastjet::Nsubjettiness nSubJetAlgo1_;
		fastjet::Nsubjettiness nSubJetAlgo2_;
		fastjet::Nsubjettiness nSubJetAlgo3_;
		fastjet::Nsubjettiness nSubJetAlgo4_;
		std::vector<double> nSjn1_;
		std::vector<double> nSjn2_;
		std::vector<double> nSjn3_;
		std::vector<double> nSjn4_;
		std::vector<CompoundPseudoJet>	fjCompoundJets_;
};


#endif
