#ifndef TREEPROCESSOR_HPP
#define TREEPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/InputCollections.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/VariableContainer.hpp"

class TreeProcessor{
public:
  TreeProcessor() : initialized(false) {}
  virtual ~TreeProcessor() {}
  
  virtual void Init(const InputCollections& input,VariableContainer& var)=0;
  virtual void Process(const InputCollections& input,VariableContainer& var) =0;
  
protected:
  bool initialized;
};

#endif
