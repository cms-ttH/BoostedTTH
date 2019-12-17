#ifndef JABDTTHWPROCESSOR_HPP
#define JABDTTHWPROCESSOR_HPP
#include "BoostedTTH/BoostedAnalyzer/interface/JABDTBaseProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "TTH/CommonClassifier/interface/thwHypothesisCombinatorics.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class JABDTthwProcessor: public JABDTBaseProcessor{
	public:
	  JABDTthwProcessor(const edm::ParameterSet& iConfig);
	  ~JABDTthwProcessor();
	private:
};

#endif
