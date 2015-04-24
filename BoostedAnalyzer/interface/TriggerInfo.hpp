#ifndef BOOSTEDTTH_BOOSTEDANALYZER_TRIGGERINFO_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_TRIGGERINFO_HPP

#include <vector>


class TriggerInfo {
  
public:
  
  TriggerInfo(?);
private:
  const pat::TriggerObjectStandAloneCollection& selectedTrigger_;
  const edm::TriggerResults&                    triggerResults_;
  const HLTConfigProvider&                      hlt_config_;

};

#endif
