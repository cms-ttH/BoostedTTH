#include "BoostedTTH/BoostedAnalyzer/interface/TriggerInfo.hpp"
using namespace std;
TriggerInfo::TriggerInfo(std::map<std::string, bool> triggers_,
                         std::map<std::string, int> prescales_)
{
  triggers = triggers_;
  prescales = prescales_;
}

bool
TriggerInfo::Exists(std::string triggername) const
{
  if (triggers.count(triggername) == 0) {
    return false;
  }
  return true;
}

bool
TriggerInfo::GetPrescale(std::string triggername) const
{
  if (!Exists(triggername))
    return -1;
  else
    return prescales.at(triggername);
}

bool
TriggerInfo::IsTriggered(std::string triggername) const
{
  if (triggername == "any" || triggername == "Any" || triggername == "none" ||
      triggername == "None")
    return true;
  int asterix = triggername.find("*");
  if (asterix == int(std::string::npos)) {
    return Exists(triggername) && triggers.at(triggername);
  } else {
    if (asterix == int(triggername.length() - 1)) {
      triggername.pop_back();
      auto it = triggers.lower_bound(triggername);
      while (it != triggers.end() && it->first.find(triggername) == 0) {
        if (it->second)
          return true;
        it++;
      }
      return false;
    } else {
      cerr << "* wildcard only allowed at the end" << endl;
      return false;
    }
  }
  return false;
}

bool
TriggerInfo::IsAnyTriggered(std::vector<std::string> triggernames) const
{
  for (auto name = triggernames.begin(); name != triggernames.end(); name++) {
    if (IsTriggered(*name))
      return true;
  }
  return false;
}
std::map<std::string, bool>
TriggerInfo::GetTriggers() const
{
  return triggers;
}

TriggerInfoProducer::TriggerInfoProducer(const edm::ParameterSet& iConfig,
                                         edm::ConsumesCollector&& iC)
{
  triggerBitsToken = iC.consumes<edm::TriggerResults>(
    iConfig.getParameter<edm::InputTag>("triggerBits"));
  triggerPrescalesToken = iC.consumes<pat::PackedTriggerPrescales>(
    iConfig.getParameter<edm::InputTag>("triggerPrescales"));
}

void
TriggerInfo::Print() const
{
  std::cout << "Triggers:" << endl;
  for (auto f : triggers) {
    std::cout << f.first << " " << f.second << "\n";
  }
}

TriggerInfo
TriggerInfoProducer::Produce(const edm::Event& iEvent) const
{
  std::map<std::string, bool> triggers;
  std::map<std::string, int> prescales;
  edm::Handle<edm::TriggerResults> h_triggerBits;
  edm::Handle<pat::PackedTriggerPrescales> h_triggerPrescales;
  iEvent.getByToken(triggerBitsToken, h_triggerBits);
  iEvent.getByToken(triggerPrescalesToken, h_triggerPrescales);
  if (h_triggerBits.isValid()) {
    const edm::TriggerNames& names = iEvent.triggerNames(*h_triggerBits);
    for (unsigned int i = 0; i < h_triggerBits->size(); ++i) {
      string name = names.triggerName(i);
      triggers[name] = h_triggerBits->accept(i);
      prescales[name] = h_triggerPrescales->getPrescaleForIndex(i);
    }
  } else {
    std::cout << "trigger handle is not valid!" << std::endl;
  }

  return TriggerInfo(triggers, prescales);
}
