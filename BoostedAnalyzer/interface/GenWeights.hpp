#ifndef BOOSTEDTTH_BOOSTEDANALYZER_GENWEIGTS_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_GENWEIGTS_HPP

#include <map>
#include <iostream>

#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"


namespace Generator{ enum Generator{POWHEG, aMC, MadGraph, pythia8,  notSpecified}; }


class GenWeights {

public:
  GenWeights();
  void GetGenWeights(std::map<std::string, float>& weights, 
		     const LHEEventProduct& LHEEvent,
		     bool& dogenweights) const;
  bool SetGenerator(const Generator::Generator);
private:
  std::map<int, std::string> GetWeightNames(const Generator::Generator) const;
  std::map<int, std::string> weightnames;
  int errweightvalue;
  bool GeneratorSet;
  int GeneratorWeights;
};

#endif
