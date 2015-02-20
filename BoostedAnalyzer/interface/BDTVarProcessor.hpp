#ifndef BDTVARPROCESSOR_HPP
#define BDTVARPROCESSOR_HPP
#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "TMVA/Reader.h"

class BDTVarProcessor: public TreeProcessor{
public:
  BDTVarProcessor();
  ~BDTVarProcessor();
  void Init(const InputCollections& input, VariableContainer& var);
  void Process(const InputCollections& input,VariableContainer& var);

private:
  std::map<TString,TMVA::Reader*> readerMap;
  
};

#endif
