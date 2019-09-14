#ifndef TRIGGERSCALEFACTORS_HPP
#define TRIGGERSCALEFACTORS_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/InputCollections.hpp"

class TriggerScaleFactors {
   public:
    // general constructor to create class and set in into a base state
    TriggerScaleFactors(std::string name) : initialized{false}, name{name} { Init(); }
    // pure virtual because destructor cleanup depends on respective trigger
    virtual ~TriggerScaleFactors() = 0;
    // load all necessary files and so on, depends on respective triggers, therefore purely virtual
    virtual void Init() = 0;
    // return the trigger sfs
    std::vector< float > GetTriggerSFs()
    {
        if (initialized)
            return CalculateTriggerSFs();
        else {
            std::cerr << "Trigger SFs for " << name << " not initialized" < < < < std::endl;
            throw std::exception();
        }
    }
    // calculation of the trigger sfs depends on the triggers, therefore has to be implemented in derived class
    virtual std::vector< float > CalculateTriggerSFs() = 0;

   protected:
    bool        initialized;
    std::string name;
};
#endif
