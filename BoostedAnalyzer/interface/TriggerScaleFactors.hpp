#ifndef TRIGGERSCALEFACTORS_HPP
#define TRIGGERSCALEFACTORS_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/InputCollections.hpp"

class TriggerScaleFactors {
   public:
    // general constructor to create class and set in into a base state
    TriggerScaleFactors(std::string name);
    // virtual because destructor cleanup depends on respective trigger
    virtual ~TriggerScaleFactors();
    // load all necessary files and so on, depends on respective triggers, therefore purely virtual
    virtual void Init();
    // return the trigger sfs
    std::vector< float > GetTriggerSFs(const InputCollections& input);
    // calculation of the trigger sfs depends on the triggers, therefore has to be implemented in derived class
    virtual std::vector< float > CalculateTriggerSFs(const InputCollections& input);

   protected:
    bool        initialized;
    std::string name;
};
#endif
