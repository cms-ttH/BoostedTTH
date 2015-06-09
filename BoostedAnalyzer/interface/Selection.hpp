#ifndef SELECTION_HPP
#define SELECTION_HPP

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "BoostedTTH/BoostedAnalyzer/interface/InputCollections.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/Cutflow.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

class Selection{

public:
  virtual void InitCutflow(Cutflow& cutflow)=0;
  virtual bool IsSelected(const InputCollections& input,Cutflow& cutflow)=0;

protected:
  bool initialized;


};


#endif
