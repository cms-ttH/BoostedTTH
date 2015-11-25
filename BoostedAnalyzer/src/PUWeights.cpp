#include <iostream>

#include "FWCore/Utilities/interface/Exception.h"

#include "BoostedTTH/BoostedAnalyzer/interface/PUWeights.hpp"


PUWeights::PUWeights() {
  nominalWeight_.name_ = "NOMINAL_PU_WEIGHT";
  nominalWeight_.value_ = 1.;
  nominalWeightIsInit_ = false;	// this means, it returns the default of 1 as set above
}


void PUWeights::init(const edm::ParameterSet& iConfig) {
  if( iConfig.existsAs<edm::ParameterSet>("nominalPUWeight",true) ) {
    const edm::ParameterSet nominalPUWeightPS = iConfig.getParameter<edm::ParameterSet>("nominalPUWeight");
    initNominalWeight( nominalPUWeightPS.getParameter<std::string>("fileNameMCNPU"),
		       nominalPUWeightPS.getParameter<std::string>("histNameMCNPU"),
		       nominalPUWeightPS.getParameter<std::string>("fileNameDataNPUEstimated"),
		       nominalPUWeightPS.getParameter<std::string>("histNameDataNPUEstimated")  );
  } 

  // Optionally, add additional weights
  if( iConfig.existsAs<edm::VParameterSet>("additionalPUWeights",true) ) {
    const edm::VParameterSet additionalPUWeightsPS = iConfig.getParameter<edm::VParameterSet>("additionalPUWeights");
    for(edm::VParameterSet::const_iterator iPS = additionalPUWeightsPS.begin();
      iPS != additionalPUWeightsPS.end(); ++iPS) {
      initAdditionalWeight( iPS->getParameter<std::string>("namePUWeight"),
			    iPS->getParameter<std::string>("fileNameMCNPU"),
			    iPS->getParameter<std::string>("histNameMCNPU"),
			    iPS->getParameter<std::string>("fileNameDataNPUEstimated"),
			    iPS->getParameter<std::string>("histNameDataNPUEstimated")  );
    }
  }
}


void PUWeights::initNominalWeight(const std::string& fileNameMCNPU,
				  const std::string& histNameMCNPU,
				  const std::string& fileNameDataNPUEstimated,
				  const std::string& histNameDataNPUEstimated) {
  if( nominalWeightIsInit_ ) {
    throw cms::Exception("PU weight already initialized")
      << "Trying to set up second producer for nominal weight";
  }
  std::cout << "Initializing nominal PU weight" << std::endl;
  nominalWeight_.producer_.initWeights(fileNameMCNPU,histNameMCNPU,fileNameDataNPUEstimated,histNameDataNPUEstimated);
  nominalWeightIsInit_ = true;
}


void PUWeights::initAdditionalWeight(const std::string& name,
				     const std::string& fileNameMCNPU,
				     const std::string& histNameMCNPU,
				     const std::string& fileNameDataNPUEstimated,
				     const std::string& histNameDataNPUEstimated) {
  for( const auto weight : additionalWeights_ ) {
    if( name == weight.name() ) {
      throw cms::Exception("PU weight already initialized")
	<< "Trying to set up second producer with '" << name << "' for"
	<< fileNameDataNPUEstimated << "' and '" << fileNameMCNPU << "'";
    }
  }
  std::cout << "Initializing additional PU weight '" << name << "'" << std::endl;
  PUWeights::Weight weight;
  weight.name_ = name;
  weight.producer_.initWeights(fileNameMCNPU,histNameMCNPU,fileNameDataNPUEstimated,histNameDataNPUEstimated);
  additionalWeights_.push_back(weight);
  //  additionalWeights_.back().producer_.initWeights(fileNameMCNPU,histNameMCNPU,fileNameDataNPUEstimated,histNameDataNPUEstimated);
}


void PUWeights::compute(const unsigned int npu) {
  if( nominalWeightIsInit_ ) {
    nominalWeight_.compute(npu);
  }
  for(std::vector<PUWeights::Weight>::iterator it = additionalWeights_.begin();
      it != additionalWeights_.end(); ++it) {
    it->compute(npu);
  }
}
