#ifndef DNNVARPROCESSOR_HPP
#define DNNVARPROCESSOR_HPP
#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"
#include "TTH/CommonClassifier/interface/DNNClassifier.h"
#include "MiniAOD/MiniAODHelper/interface/CSVHelper.h"

class DNNVarProcessor: public TreeProcessor{
public:
  DNNVarProcessor();
  DNNVarProcessor(DNNClassifier* sldnnclassifier_);
  ~DNNVarProcessor();
  void Init(const InputCollections& input, VariableContainer& var);
  void Process(const InputCollections& input,VariableContainer& var);

private:
  DNNClassifier* sldnnclassifier;
  DNNOutput dnn_output;
  bool classifier_created_inside;
};

#endif
