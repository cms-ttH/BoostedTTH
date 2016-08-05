#ifndef BOOSTEDTTH_BOOSTEDANALYZER_GENWEIGTS_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_GENWEIGTS_HPP

#include <map>
#include <iostream>

#include "LHAPDF/LHAPDF.h"
#include "LHAPDF/LHAGlue.h"

#include "FWCore/Framework/interface/Event.h"

#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"


namespace Generator{ enum Generator{POWHEG, aMC, MadGraph, pythia8,  notSpecified}; }


class GenWeights {

public:
  GenWeights();
  void GetGenWeights(std::map<std::string, float>& weights, 
		       const LHEEventProduct& LHEEvent,
		       bool& dogenweights) const;
  bool GetLHAPDFWeight( std::map<std::string, float>& weights, 
			  const GenEventInfoProduct& genInfos,
		       std::string PDFSetName);
  bool SetGenerator(const Generator::Generator);
  bool initLHAPDF(std::string name);
  bool initLHAPDF(std::vector<std::string> name);


private:
  std::map<int, std::string> GetWeightNames(const Generator::Generator) const;
  std::map<int, std::string> weightnames;
  int errweightvalue;
  bool GeneratorSet;
  int GeneratorWeights;

  std::vector< LHAPDF::PDFSet > initializedPDFSets;
  std::vector< std::vector< LHAPDF::PDF* > > initializedPDFs; 
  std::vector< std::string > initializedPDFNames;
  bool LHAPDFinitialized ;

  
};

#endif
