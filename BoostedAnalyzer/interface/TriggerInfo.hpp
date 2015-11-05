#ifndef BOOSTEDTTH_BOOSTEDANALYZER_TRIGGERINFO_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_TRIGGERINFO_HPP

#include <map>
#include <vector>
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "FWCore/Framework/interface/Event.h"

class TriggerInfo {
  
public:
    TriggerInfo(const edm::Event& iEvent,
		    const edm::EDGetTokenT<edm::TriggerResults>& triggerBitsToken,
		    const edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection>& triggerObjectsToken,
		    const edm::EDGetTokenT<pat::PackedTriggerPrescales>& triggerPrescalesToken);
    bool IsTriggered(std::string triggername) const ; 
    bool Exists(std::string triggername) const ; 
    bool GetPrescale(std::string triggername) const ; 
    bool IsAnyTriggered(std::vector< std::string > triggers) const ;
    std::map<std::string, bool> GetTriggers() const;
private:
    std::map<std::string, bool> triggers;
    std::map<std::string, int> prescales;
};

#endif
