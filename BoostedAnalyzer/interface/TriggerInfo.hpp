#ifndef BOOSTEDTTH_BOOSTEDANALYZER_TRIGGERINFO_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_TRIGGERINFO_HPP

#include <map>
#include <vector>
#include <iostream>
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class TriggerInfo {
   public:
    TriggerInfo(std::map< std::string, bool > triggers, std::map< std::string, int > prescales, std::map< std::string, double > L1_prefire_weights,
                bool Ele32DoubleL1ToSingleL1);
    bool                          IsTriggered(std::string triggername) const;
    bool                          Exists(std::string triggername) const;
    bool                          GetPrescale(std::string triggername) const;
    void                          Print() const;
    bool                          IsAnyTriggered(std::vector< std::string > triggers) const;
    std::map< std::string, bool > GetTriggers() const;
    // L1 prefiring issue
    std::map< std::string, double > GetL1PrefireWeights() const;
    // ele32 trigger issue for 2017 era
    bool GetEle32DoubleL1ToSingleL1() const;

   private:
    std::map< std::string, bool > triggers;
    std::map< std::string, int >  prescales;
    // L1 prefiring issue
    std::map< std::string, double > L1_prefire_weights;
    // ele32 trigger issue for 2017 era
    bool ele32DoubleL1ToSingleL1;
};

class TriggerInfoProducer {
   public:
    TriggerInfoProducer(const edm::ParameterSet& iConfig, edm::ConsumesCollector&& iC);
    TriggerInfo Produce(const edm::Event& iEvent) const;

   private:
    edm::EDGetTokenT< edm::TriggerResults >         triggerBitsToken;
    edm::EDGetTokenT< pat::PackedTriggerPrescales > triggerPrescalesToken;
    // L1 prefiring issue
    edm::EDGetTokenT< double > prefweight_token;
    edm::EDGetTokenT< double > prefweightup_token;
    edm::EDGetTokenT< double > prefweightdown_token;
    // ele32 trigger issue for 2017 era
    edm::EDGetTokenT< bool > ele32DoubleL1ToSingleL1_token;
    std::string              era;
    bool                     isData;
};

#endif
