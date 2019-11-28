#include "BoostedTTH/BoostedAnalyzer/interface/TriggerVarProcessor.hpp"

using namespace std;

TriggerVarProcessor::TriggerVarProcessor(const std::vector< std::string > relevantTriggers_) : relevantTriggers(relevantTriggers_)
{
    availableTriggerScaleFactors.emplace_back(new SingleMuTriggerSFs("SingleMuon"));
    availableTriggerScaleFactors.emplace_back(new SingleElTriggerSFs("SingleElectron"));
}
TriggerVarProcessor::~TriggerVarProcessor() {}

void TriggerVarProcessor::Init(const InputCollections& input, VariableContainer& vars)
{
    for (auto it = relevantTriggers.begin(); it != relevantTriggers.end(); ++it) {
        vars.InitVar("Triggered_" + replaceAsterix(*it), "I");
        vars.InitVar("Prescale_" + replaceAsterix(*it), "F");
    }
    if (not input.iEvent.isRealData()) {
        for (auto& triggerSF : availableTriggerScaleFactors) {
            triggerSF->Init(input);
            vars.InitVar("TriggerSF_" + triggerSF->GetName());
            vars.InitVar("TriggerSF_" + triggerSF->GetName() + "_Up");
            vars.InitVar("TriggerSF_" + triggerSF->GetName() + "_Down");
        }
    }
    for (auto& prefire : input.triggerInfo.GetL1PrefireWeights()) { vars.InitVar(prefire.first); }
    initialized = true;
}

void TriggerVarProcessor::Process(const InputCollections& input, VariableContainer& vars)
{
    if (!initialized) cerr << "tree processor not initialized" << endl;
    for (auto it = relevantTriggers.begin(); it != relevantTriggers.end(); ++it) {
        vars.FillVar("Triggered_" + replaceAsterix(*it), int(input.triggerInfo.IsTriggered(*it)));
        vars.FillVar("Prescale_" + replaceAsterix(*it), float(input.triggerInfo.GetPrescale(*it)));
    }
    if (not input.iEvent.isRealData()) {
        for (auto& triggerSF : availableTriggerScaleFactors) {
            auto sfs = triggerSF->GetTriggerSFs(input);
            vars.FillVar("TriggerSF_" + triggerSF->GetName(), sfs.at(0));
            vars.FillVar("TriggerSF_" + triggerSF->GetName() + "_Up", sfs.at(1));
            vars.FillVar("TriggerSF_" + triggerSF->GetName() + "_Down", sfs.at(2));
        }
    }
    for (auto& prefire : input.triggerInfo.GetL1PrefireWeights()) { vars.FillVar(prefire.first, prefire.second); }
}

std::string TriggerVarProcessor::replaceAsterix(std::string triggername)
{
    int asterix = triggername.find("*");
    if (triggername.find("*") == std::string::npos) { return triggername; }
    else {
        return triggername.replace(asterix, 1, "X");
    }
}
