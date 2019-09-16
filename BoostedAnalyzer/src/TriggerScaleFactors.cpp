#include "BoostedTTH/BoostedAnalyzer/interface/TriggerScaleFactors.hpp"

// constructor sets initiliazed flag to false and calls Init() function which should do all necessary things
// before the scale factors can be calculated, e.g. open files and so on ...
TriggerScaleFactors::TriggerScaleFactors(std::string name) : initialized{false}, name{name} { Init(); }

// destructor should also be implemented in derived classes
TriggerScaleFactors::~TriggerScaleFactors() {}

// Init function should be implemented in derived classes and overwrite this base function
void TriggerScaleFactors::Init() { initialized = true; }

// base function to calculate trigger scale factors
// if the derived class does not overwrite this function, only three 1s will be returned
std::vector< float > TriggerScaleFactors::CalculateTriggerSFs(const InputCollections& input)
{
    std::vector< float > ones{1.0, 1.0, 1.0};
    return ones;
}

// function which returns the correct trigger scale factors if the class was initialized
std::vector< float > TriggerScaleFactors::GetTriggerSFs(const InputCollections& input)
{
    if (initialized)
        return CalculateTriggerSFs(input);
    else {
        std::cerr << "Trigger SFs for " << name << " not initialized" << std::endl;
        throw std::exception();
    }
}
