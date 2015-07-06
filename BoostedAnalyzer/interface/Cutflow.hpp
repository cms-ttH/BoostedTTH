#ifndef CUTFLOW_HPP
#define CUTFLOW_HPP

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "BoostedTTH/BoostedAnalyzer/interface/InputCollections.hpp"

// ------ Cutflow Object
class Cutflow{
public:

  Cutflow();
  ~Cutflow();
  void AddStep(std::string name);
  void Print(std::ostream& out);
  void EventSurvivedStep(std::string name, float weight);
  void Init();
  int GetNSelected();

private:
  bool initialized;
  std::vector<int> eventsAfterSelectionSteps;
  std::vector<float> yieldsAfterSelectionSteps;
  std::vector<std::string> selectionStepNames;
  

};

#endif
