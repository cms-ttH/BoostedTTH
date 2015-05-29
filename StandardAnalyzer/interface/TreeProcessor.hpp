#ifndef TREEPROCESSOR_HPP
#define TREEPROCESSOR_HPP

#include "BoostedTTH/StandardAnalyzer/interface/InputCollections.hpp"
#include "BoostedTTH/StandardAnalyzer/interface/VariableContainer.hpp"

class TreeProcessor{
  public:
  
    virtual void Init(const InputCollections& input,VariableContainer& var)=0;
    virtual void Process(const InputCollections& input,VariableContainer& var) =0;


  protected:
  
    bool initialized;
};

#endif
