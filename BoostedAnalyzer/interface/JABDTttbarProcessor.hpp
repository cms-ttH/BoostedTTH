#ifndef JABDTTTBARPROCESSOR_HPP
#define JABDTTTBARPROCESSOR_HPP
#include "BoostedTTH/BoostedAnalyzer/interface/JABDTBaseProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "TTH/CommonClassifier/interface/ttbarHypothesisCombinatorics.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class JABDTttbarProcessor: public JABDTBaseProcessor{
	public:
	  JABDTttbarProcessor(const edm::ParameterSet& iConfig);
	  ~JABDTttbarProcessor();
	private:
};

#endif
