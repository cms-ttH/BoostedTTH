#ifndef BOOSTEDTTH_BOOSTEDPRODUCERS_HEPTOPJETPRODUCER_H
#define BOOSTEDTTH_BOOSTEDPRODUCERS_HEPTOPJETPRODUCER_H 1

#include "FWCore/Framework/interface/EventSetup.h"
#include "RecoJets/JetAlgorithms/interface/CompoundPseudoJet.h"

#include "BoostedTTH/BoostedProducer/plugins/VirtualJetProducer.h"
#include "BoostedTTH/BoostedProducer/interface/HEPTopTaggerAlgorithm.h"
#include "BoostedTTH/BoostedProducer/interface/Nsubjettiness.h"


class HEPTopJetProducer : public VirtualJetProducer
{
	//
  	// construction / destruction
  	//
	public:
		HEPTopJetProducer(const edm::ParameterSet& ps);
		virtual ~HEPTopJetProducer();
		
		
	//
	// member functions
	//
	public:	
		void produce( edm::Event& iEvent, const edm::EventSetup& iSetup );
		void endJob();
		void runAlgorithm( edm::Event& iEvent, const edm::EventSetup& iSetup );
		void inputTowers();
		void output(edm::Event& iEvent,const edm::EventSetup& iSetup);
		template<class T>
		void writeCompoundJets(edm::Event& iEvent,const edm::EventSetup& iSetup);
		
	//
	// member data
	//
	private:
		HEPTopTaggerAlgorithm alg_;         		/// The algorithm to do the work
		fastjet::Nsubjettiness nSubJetAlgo1_;
		fastjet::Nsubjettiness nSubJetAlgo2_;
		fastjet::Nsubjettiness nSubJetAlgo3_;
		fastjet::Nsubjettiness nSubJetAlgo4_;
		std::vector<double> nSjn1_;
		std::vector<double> nSjn2_;
		std::vector<double> nSjn3_;
		std::vector<double> nSjn4_;

		std::vector<CompoundPseudoJet> fjCompoundJets_;
		std::vector<bool> topTags_;
};


#endif
