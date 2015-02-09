#ifndef CUTFLOW_HPP
#define CUTFLOW_HPP

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

// ------ Cutflow Object
class Cutflow{
public:

  Cutflow();
  ~Cutflow();
  void AddStep(std::string name);
  void Print();
  void EventSurvivedStep(std::string name);
  void Init(const char* filename);
private:
  bool initialized;
  std::vector<int> eventsAfterSelectionSteps;
  std::vector<std::string> selectionStepNames;
  std::ofstream cutflowfile;

};

#endif
