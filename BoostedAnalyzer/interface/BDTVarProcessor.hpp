#ifndef BDTVARPROCESSOR_HPP
#define BDTVARPROCESSOR_HPP
#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "TTH/CommonClassifier/interface/BDTClassifier.h"
#include "TTH/CommonClassifier/interface/RecoLikelihoodVariables.h"
#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"
#include "TMVA/Reader.h"

class BDTVarProcessor : public TreeProcessor {
 public:
  BDTVarProcessor();
  BDTVarProcessor(BDTClassifier* bdt_);
  ~BDTVarProcessor();
  void Init(const InputCollections& input, VariableContainer& var);
  void Process(const InputCollections& input, VariableContainer& var);

 private:
  //   BDTOhio_v2 bdtohio2;
  //   BDT_v3 bdt3;
  BDTClassifier* commonBDT5;
  bool needToDeleteBDTClassifier;
  //
  RecoLikelihoodVariables* recoLikelihoodVariables;
};

#endif
