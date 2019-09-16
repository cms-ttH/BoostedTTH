#ifndef TRIGGERSCALEFACTORS_HPP
#define TRIGGERSCALEFACTORS_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/InputCollections.hpp"

class TriggerScaleFactors {
   public:
    // general constructor to create class and set in into a base state
    // this should be done also with all derived classes
    TriggerScaleFactors(std::string name);
    // virtual because destructor cleanup probably depends on respective trigger, e.g. close opened files and so on ...
    virtual ~TriggerScaleFactors();
    // load all necessary files and so on, depends on respective triggers, therefore virtual and should be overwritten
    // by derived class
    virtual void Init();
    // return the trigger sfs
    // same function for base and derived classes
    std::vector< float > GetTriggerSFs(const InputCollections& input);
    // calculation of the trigger sfs depends on the triggers, therefore should be implemented in derived class -> virtual function
    virtual std::vector< float > CalculateTriggerSFs(const InputCollections& input);

   protected:
    bool        initialized;
    std::string name;
};
#endif
