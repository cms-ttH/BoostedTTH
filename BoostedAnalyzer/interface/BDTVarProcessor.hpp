#ifndef BDTVARPROCESSOR_HPP
#define BDTVARPROCESSOR_HPP
#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BDTOhio_v2.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BDT_v3.hpp"
#include "TTH/CommonClassifier/interface/BDTClassifier.h"
#include "MiniAOD/MiniAODHelper/interface/LJ_BDT_v4.hpp"
#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"
#include "TMVA/Reader.h"

class BDTVarProcessor: public TreeProcessor{
public:
  BDTVarProcessor();
  ~BDTVarProcessor();
  void Init(const InputCollections& input, VariableContainer& var);
  void Process(const InputCollections& input,VariableContainer& var);

private:
  BDTOhio_v2 bdtohio2;
  BDT_v3 bdt3;
  LJ_BDT_v4 bdt4;
  BDTClassifier commonBDT4;
  BDTClassifier commonBDT5;
  
  
};

#endif
