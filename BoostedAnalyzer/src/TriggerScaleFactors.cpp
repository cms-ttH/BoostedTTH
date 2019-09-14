#include "BoostedTTH/BoostedAnalyzer/interface/TriggerScaleFactors.hpp"

TriggerScaleFactors::TriggerScaleFactors(std::string name) : initialized{false}, name{name} { Init(); }

TriggerScaleFactors::~TriggerScaleFactors() {}

void TriggerScaleFactors::Init() { initialized = true; }

std::vector< float > TriggerScaleFactors::CalculateTriggerSFs(const InputCollections& input)
{
    std::vector< float > ones{1.0, 1.0, 1.0};
    return ones;
}

std::vector< float > TriggerScaleFactors::GetTriggerSFs(const InputCollections& input)
{
    if (initialized)
        return CalculateTriggerSFs(input);
    else {
        std::cerr << "Trigger SFs for " << name << " not initialized" << std::endl;
        throw std::exception();
    }
}
