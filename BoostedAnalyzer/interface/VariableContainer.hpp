#ifndef VARIABLECONTAINER_HPP
#define VARIABLECONTAINER_HPP

#include <iostream>
#include <map>
#include <string>

#include "TString.h"
#include "TTree.h"

/*
The VariableContainer is basically a set of std::maps that stores variables as
integers, floats or as arrays of floats. It also has some helper functions that
make sure maps are filled with default values for every event and that maps are
only filled once per event. The variable container is connected to a tree in
which all the variables are written for every event.
 */
class VariableContainer
{
public:
  VariableContainer();
  ~VariableContainer();

  bool DoesVarExist(const TString& name) const;
  bool IsVarFilled(const TString& name) const;
  void InitVar(const TString& name, const std::string& type = "F");
  void InitVar(const TString& name,
               float defaultValue,
               const std::string& type = "F");
  void FillVar(const TString& name, double value);
  void FillFloatVar(const TString& name,
                    float value,
                    bool checkIfExists = true);
  void FillIntVar(const TString& name, long value, bool checkIfExists = true);
  void InitVars(const TString& name,
                float defaultValue,
                const TString& nEntryVariable,
                int maxentries = 100);
  void InitVars(const TString& name,
                const TString& nEntryVariable,
                int maxentries = 100);
  void FillVars(const TString& name, int index, float value);
  float* GetFloatVarPointer(const TString& name);
  float* GetArrayVarPointer(const TString& name, int entry);
  long* GetIntVarPointer(const TString& name);
  long GetIntVar(const TString& name);
  float GetFloatVar(const TString& name);
  float GetArrayVar(const TString& name, int index);
  void ConnectTree(TTree* tree);

  void SetDefaultValues();
  void PrintArrayValue(const TString& name);
  void Dump() const;

private:
  void checkIfVariableAlreadyInit(const TString& name) const;

  std::map<TString, Float_t> floatMap;
  std::map<TString, bool> floatMapFilled;
  std::map<TString, Float_t> floatMapDefaults;
  std::map<TString, long> intMap;
  std::map<TString, long> intMapDefaults;
  std::map<TString, bool> intMapFilled;
  std::map<TString, Float_t*> arrayMap;
  std::map<TString, Float_t> arrayMapDefaults;
  std::map<TString, bool> arrayMapFilled;
  std::map<TString, int> maxEntriesArrays;
  std::map<TString, TString> entryVariableOf;
};

#endif
