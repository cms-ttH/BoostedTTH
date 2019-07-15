#include "FWCore/Utilities/interface/Exception.h"

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

void Selection::checkIfIsInit(const std::string& name) const {
  if (!initialized) {
    throw cms::Exception("BadSelection") << "'" << name << "' not initialized!";
  }
}
