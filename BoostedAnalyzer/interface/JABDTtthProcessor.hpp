#ifndef JABDTTTHPROCESSOR_HPP
#define JABDTTTHPROCESSOR_HPP
#include "BoostedTTH/BoostedAnalyzer/interface/JABDTBaseProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "TTH/CommonClassifier/interface/tthHypothesisCombinatorics.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class JABDTtthProcessor: public JABDTBaseProcessor{
	public:
	  JABDTtthProcessor(const edm::ParameterSet& iConfig);
	  ~JABDTtthProcessor();
	private:
};

#endif
