#ifndef BOOSTEDTTH_BOOSTEDANALYZER_GENWEIGTS_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_GENWEIGTS_HPP

#include <map>
#include <iostream>

#include "LHAPDF/LHAPDF.h"
#include "LHAPDF/LHAGlue.h"

#include "FWCore/Framework/interface/Event.h"

#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"

namespace Generator {
enum Generator { POWHEG, aMC, MadGraph, pythia8, notSpecified };
}

class GenWeights {
 public:
  GenWeights();
  void GetGenWeights(std::map<std::string, float>& weights,
                     const LHEEventProduct& LHEEvent) const;
  bool GetLHAPDFWeight(std::map<std::string, float>& weights,
                       const GenEventInfoProduct& genInfos);
  bool initLHAPDF(std::string name);
  bool initLHAPDF(std::vector<std::string> name);

  void GetNamesFromLHE(const LHERunInfoProduct& myLHERunInfoProduct);
  void Clear();

 private:
  std::vector<LHAPDF::PDFSet> initializedPDFSets;
  std::vector<std::vector<LHAPDF::PDF*> > initializedPDFs;
  std::vector<std::string> initializedPDFNames;
  std::map<std::string, std::string> lhe_weights;
  bool LHAPDFinitialized;
  bool initialized;
  std::map<int, std::string> psweightsNameMap;
};

#endif
