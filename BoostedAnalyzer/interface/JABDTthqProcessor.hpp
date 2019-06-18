#ifndef JABDTTHQPROCESSOR_HPP
#define JABDTTHQPROCESSOR_HPP
#include "BoostedTTH/BoostedAnalyzer/interface/JABDTBaseProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "TTH/CommonClassifier/interface/thqHypothesisCombinatorics.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class JABDTthqProcessor: public JABDTBaseProcessor{
	public:
	  JABDTthqProcessor(const edm::ParameterSet& iConfig);
	  ~JABDTthqProcessor();
	private:
};

#endif
