#ifndef RECOJETS_JETALGORITHMS_HEPTOPTAGGERALGORITHM_H
#define RECOJETS_JETALGORITHMS_HEPTOPTAGGERALGORITHM_H 1

// Copyright (c) 2011 Christopher Vermilion
//
//----------------------------------------------------------------------
//  This file is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 3 of the License, or
//  (at your option) any later version.
//
//  This file is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  The GNU General Public License is available at
//  http://www.gnu.org/licenses/gpl.html or you can write to the Free Software
//  Foundation, Inc.:
//      59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//----------------------------------------------------------------------

#include <vector>

#include "FWCore/Framework/interface/Event.h"

#include "RecoJets/JetAlgorithms/interface/CompoundPseudoJet.h"

#include <fastjet/JetDefinition.hh>
#include <fastjet/AreaDefinition.hh>
#include <fastjet/PseudoJet.hh>

#include "BoostedTTH/BoostedProducer/interface/HEPTopTagger.h"
#include <boost/shared_ptr.hpp>

class HEPTopTaggerAlgorithm
{
	//
	// construction / destruction
	//
	public:
		HEPTopTaggerAlgorithm(const std::string& moduleLabel = '\0',
							bool verbose = false,
							bool doAreaFastjet = false,
							unsigned nFatMax = 0,
							double jetPtMin = 10.,
							double centralEtaCut = 2.5,
							double massDropCut = 0.8,
							double subjetMassCut = 30.,
							bool requireTopTag = false);

		virtual ~HEPTopTaggerAlgorithm();


	//
	// member functions
	//
	public:
		void run(const std::vector<fastjet::PseudoJet> & fjInputs, 
		std::vector<CompoundPseudoJet> & fjJets,
		std::vector<bool> & topTags,
		boost::shared_ptr<fastjet::ClusterSequence> & fjClusterSeq);

		std::string summary() const;


	//
	// member data
	//
	private:
		std::string           		moduleLabel_;
		bool						verbose_;
		bool						doAreaFastjet_;
		unsigned					nFatMax_;
		double 						jetPtMin_;
		double 						centralEtaCut_;
		double 						massDropCut_;
		double 						subjetMassCut_;
		bool  						requireTopTag_;
		
		unsigned                  	nevents_;
		unsigned                  	ntotal_;
		unsigned                  	nfound_;
};


#endif
