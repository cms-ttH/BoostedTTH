#ifndef PU_WEIGHTS_HPP
#define PU_WEIGHTS_HPP

#include <vector>
#include <string>

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "BoostedTTH/BoostedAnalyzer/interface/EventInfo.hpp"
#include "MiniAOD/MiniAODHelper/interface/PUWeightProducer.h"

class PUWeights {
 public:
  class Weight {
    friend class PUWeights;

   public:
    Weight() : name_(""), value_(1.) {}

    void compute(const unsigned int npu) { value_ = producer_(npu); }

    std::string name() const { return name_; }
    double value() const { return value_; }

   private:
    std::string name_;
    double value_;
    PUWeightProducer producer_;
  };

  PUWeights();

  void init(const edm::ParameterSet& iConfig);

  void initNominalWeight(const std::string& fileNameMCNPU,
                         const std::string& histNameMCNPU,
                         const std::string& fileNameDataNPUEstimated,
                         const std::string& histNameDataNPUEstimated);

  void initAdditionalWeight(const std::string& name,
                            const std::string& fileNameMCNPU,
                            const std::string& histNameMCNPU,
                            const std::string& fileNameDataNPUEstimated,
                            const std::string& histNameDataNPUEstimated);

  void compute(const unsigned int npu);
  void compute(const EventInfo& evtInfo) {
    compute(static_cast<unsigned int>(evtInfo.numTruePV));
  }

  double nominalWeight() const { return nominalWeight_.value(); }
  std::vector<PUWeights::Weight>::const_iterator additionalWeightsBegin()
      const {
    return additionalWeights_.begin();
  }
  std::vector<PUWeights::Weight>::const_iterator additionalWeightsEnd() const {
    return additionalWeights_.end();
  }

 private:
  bool nominalWeightIsInit_;  // if false, will return 1
  PUWeights::Weight nominalWeight_;
  std::vector<PUWeights::Weight> additionalWeights_;
};
#endif
