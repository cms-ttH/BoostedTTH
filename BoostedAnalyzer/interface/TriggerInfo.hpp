#ifndef BOOSTEDTTH_BOOSTEDANALYZER_TRIGGERINFO_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_TRIGGERINFO_HPP

#include <map>
#include <vector>
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

class TriggerInfo {
  
public:
  TriggerInfo(std::map<std::string,bool> triggers_);
  bool IsTriggered(std::string triggername) const ; 
  bool IsAnyTriggered(std::vector< std::string > triggers) const ;
private:
  const std::map<std::string, bool> triggers;
};

#endif
