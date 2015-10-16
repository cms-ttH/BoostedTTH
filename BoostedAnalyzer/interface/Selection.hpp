#ifndef SELECTION_HPP
#define SELECTION_HPP

#include <string>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "BoostedTTH/BoostedAnalyzer/interface/InputCollections.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/Cutflow.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"


/*
 Selection is the base class for all selections. All selections have two functions, one that initializes a Cutflow with the selection steps of the selection ("e.g. >=1 loose lepton" etc) and one that deduces from a InputCollection which selection steps an event survives 
 */
class Selection{

public:
  virtual ~Selection() {}

  /**
     Initialize a Cutflow, i.e., write all the selection steps that will be performed in it
     @param cutflow the cutflow that is being initialized
  */
  virtual void InitCutflow(Cutflow& cutflow)=0;
  /**
     Figure out if an event is selected and write result into the cutflow
     @param input the input collections of the analyzed event
     @param cutflow the cutflow 
  */

  virtual bool IsSelected(const InputCollections& input,Cutflow& cutflow)=0;

protected:
  void checkIfIsInit(const std::string& name) const;

  bool initialized;
};


#endif
