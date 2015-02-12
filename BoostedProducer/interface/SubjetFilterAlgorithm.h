#ifndef RECOJETS_JETALGORITHMS_SUBJETFILTERALGORITHM_H
#define RECOJETS_JETALGORITHMS_SUBJETFILTERALGORITHM_H 1


/*
  Implementation of the subjet/filter jet reconstruction algorithm
  which is described in: http://arXiv.org/abs/0802.2470
  
  CMSSW implementation by David Lopes-Pegna           <david.lopes-pegna@cern.ch>
                      and Philipp Schieferdecker <philipp.schieferdecker@cern.ch>

  see: https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideSubjetFilterJetProducer

*/


#include <vector>

#include "RecoJets/JetAlgorithms/interface/CompoundPseudoJet.h"
#include "FWCore/Framework/interface/Event.h"

#include <fastjet/JetDefinition.hh>
#include <fastjet/AreaDefinition.hh>
#include <fastjet/PseudoJet.hh>

#include <boost/shared_ptr.hpp>
class SubjetFilterAlgorithm
{
	//
	// construction / destruction
	//
	public:
		SubjetFilterAlgorithm(const std::string& moduleLabel = '\0',
				      bool verbose = false,
				      bool doAreaFastjet = false,
				      double rParam = 1.2,
				      unsigned nFatMax = 0,
				      double jetPtMin = 10.,
				      double centralEtaCut = 2.5,
				      double massDropCut = 0.67,
				      double rFilt = 0.3,
				      double asymmCut = 0.3,
				      bool asymmCutLater = true,
				      double filterJetPtMin = 10.);
							
		virtual ~SubjetFilterAlgorithm();


	//
	// member functions
	//
	public:
		void run(const std::vector<fastjet::PseudoJet> & inputs, 
		std::vector<CompoundPseudoJet> & fatJets,
		boost::shared_ptr<fastjet::ClusterSequence> & fjClusterSeq);
		
		std::string summary() const;


	//
	// member data
	//
	private:
		std::string              	moduleLabel_;
		bool                     	verbose_;
		bool                     	doAreaFastjet_;		
		double                   	rParam_;
		unsigned                 	nFatMax_;
		double                   	jetPtMin_;
		double 						centralEtaCut_;
		double                   	massDropCut_;
		double						rFilt_;
		double                   	asymmCut2_;
		bool                     	asymmCutLater_;
		double                   	filterJetPtMin_;

		unsigned                 	nevents_;
		unsigned                 	ntotal_;
		unsigned                 	nfound_;
};


#endif
