#include "BoostedTTH/BoostedAnalyzer/interface/TriggerScaleFactors.hpp"

// constructors of base class
// enforces that all derived classes have to be initialized with a name, otherwise exception will be thrown
// also enforces that the initiliazed flag will be set to false during construction
TriggerScaleFactors::TriggerScaleFactors()
{
    std::cerr << "TriggerScaleFactors class has to be constructed with a name in constructor " << std::endl;
    std::cerr << "You only used the default constructor which is not allowed" << std::endl;
    throw std::exception();
}
TriggerScaleFactors::TriggerScaleFactors(std::string name) : initialized{false}, name{name} {}

// destructor
// should also be implemented in derived classes to clean up and so on ...
TriggerScaleFactors::~TriggerScaleFactors() {}

// Init function should be implemented in derived classes and overwrite this base function
void TriggerScaleFactors::Init(const InputCollections& input) { initialized = true; }

// base function to calculate trigger scale factors
// if the derived class does not overwrite this function, only three 1s will be returned
std::vector< float > TriggerScaleFactors::CalculateTriggerSFs(const InputCollections& input)
{
    std::vector< float > defaults{-999., -999., -999.};
    return defaults;
}

// function which returns the trigger scale factors if the class was initialized
// also checks if the event is from data and throws an exception
std::vector< float > TriggerScaleFactors::GetTriggerSFs(const InputCollections& input)
{
    if (initialized && not input.iEvent.isRealData())
        return CalculateTriggerSFs(input);
    else {
        std::cerr << "Trigger SFs for " << name << " not initialized" << std::endl;
        std::cerr << "OR" << std::endl;
        std::cerr << "You want to calculate Trigger SFs for data which is not necessary" << std::endl;
        throw std::exception();
    }
}

// returns the necessary name of the trigger scale factors
std::string TriggerScaleFactors::GetName() const { return name; }
