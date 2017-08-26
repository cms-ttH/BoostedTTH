#include "FWCore/Utilities/interface/Exception.h"

#include "BoostedTTH/BoostedAnalyzer/interface/VariableContainer.hpp"

using namespace std;

VariableContainer::VariableContainer(){

}


VariableContainer::~VariableContainer(){
    for(std::map<TString,Float_t*>::iterator it=arrayMap.begin();it!=arrayMap.end();it++) {
        delete[] it->second;
    }
}
bool VariableContainer::DoesVarExist( const TString& name ) const {
  return (intMap.count(name)>0||floatMap.count(name)>0||arrayMap.count(name)>0);
}

bool VariableContainer::IsVarFilled( const TString& name ) const {
  return floatMapFilled.find(name) != floatMapFilled.end() || intMapFilled.find(name) != intMapFilled.end() || arrayMapFilled.find(name) != arrayMapFilled.end();
}


void VariableContainer::InitVar( const TString& name,float defaultValue, const std::string& type ) {
  checkIfVariableAlreadyInit(name);
  if(type=="F"){
    floatMap[name] = 0;
    floatMapDefaults[name] = defaultValue;
    floatMapFilled[name] = false;
  }
  else if(type=="I" or type=="L"){
    intMap[name] = 0;
    intMapDefaults[name] = defaultValue;
    intMapFilled[name] = false;
  }
  else
    cout << "unknown type " << type << endl;
}


void VariableContainer::InitVar( const TString& name, const std::string& type ) {
  checkIfVariableAlreadyInit(name);
  InitVar(name,-9.,type);
}


void VariableContainer::FillVar( const TString& name, double value ) {
  bool isInt=intMap.count(name)!=0;
  bool isFloat=floatMap.count(name)!=0;
  if(isFloat){
    FillFloatVar( name, value, false);
  }
  else if(isInt){
    FillIntVar( name, long(value+0.1), false);
  }
  else{
    cerr << name << " does not exist!" << endl;
  }
}

void VariableContainer::FillIntVar( const TString& name, long value, bool checkIfExists) {
    if(checkIfExists&&intMap.count(name)==0){
        cerr << name << " does not exist!" << endl;
        return;
    }
    if(intMapFilled[name]){
        cerr << name << " already filled, replacing value!" << endl;
    }
    intMap[name] = value;
    intMapFilled[name] = true;
}

void VariableContainer::FillFloatVar( const TString& name, float value, bool checkIfExists) {
    if(checkIfExists&&floatMap.count(name)==0){
        cerr << name << " does not exist!" << endl;
        return;
    }
    if(floatMapFilled[name]){
        cerr << name << " already filled, replacing value!" << endl;
    }
    floatMap[name] = value;
    floatMapFilled[name] = true;
}



void VariableContainer::InitVars( const TString& name, float defaultValue, const TString& nEntryVariable, int maxentries ){
  checkIfVariableAlreadyInit(name);
  if(!DoesVarExist(nEntryVariable)){
    cerr << nEntryVariable << " not filled, needed for " << name << ", will not initialize" << endl;
    return;
  }

  arrayMap[name] = new float[maxentries];
  arrayMapDefaults[name] = defaultValue;
  arrayMapFilled[name] = false;
  maxEntriesArrays[name] = maxentries;
  entryVariableOf[name] = nEntryVariable;
}


void VariableContainer::InitVars( const TString& name, const TString& nEntryVariable, int maxentries ){
  InitVars(name,-9.,nEntryVariable,maxentries);
}


void VariableContainer::FillVars( const TString& name, int index, float value ) {
  if(arrayMap.count(name)==0){
    cerr << name << " does not exist!" << endl;
  }
  else if(maxEntriesArrays[name]<index){
    cerr << "array " << name << " is shorter than " << index << endl;
  }
  else if(index<0){
    cerr << "array " << name << " index is negative! " << index << endl;
  }
  else
    arrayMap[name][index]=value;
}


void VariableContainer::SetDefaultValues(){
  
  auto itF= floatMap.begin();
  auto itFdefault = floatMapDefaults.begin();
  auto itFfilled = floatMapFilled.begin();
  while (itF != floatMap.end()) {
    itF->second = itFdefault->second;
    itFfilled->second=false;
    ++itF;
    ++itFdefault;
    ++itFfilled;
  }
  
  auto itI= intMap.begin();
  auto itIdefault = intMapDefaults.begin();
  auto itIfilled = intMapFilled.begin();
  while (itI != intMap.end()) {
    itI->second = itIdefault->second;
    itIfilled->second=false;
    ++itI;
    ++itIdefault;
    ++itIfilled;
  }
  
  auto itA = arrayMap.begin();
  auto itAdefault = arrayMapDefaults.begin();
  auto itAmaxEntriesArrays = maxEntriesArrays.begin();
  auto itAfilled = arrayMapFilled.begin();
  while (itA != arrayMap.end()) {    
    for(int i=0;i<itAmaxEntriesArrays->second;++i)
      itA->second[i] = itAdefault->second;
    
    itAfilled->second=false;
    ++itA;
    ++itAdefault;
    ++itAmaxEntriesArrays;
    ++itAfilled;
  }
  
}


void VariableContainer::ConnectTree(TTree* tree){
  auto itF= floatMap.begin();
  while (itF != floatMap.end()) {
    tree->Branch(itF->first, &(itF->second), itF->first+"/F" );
    itF++;
  }
  auto itI= intMap.begin();
  while (itI != intMap.end()) {
    tree->Branch(itI->first, &(itI->second), itI->first+"/L" );
    itI++;
  }
  auto itA= arrayMap.begin();
  while (itA != arrayMap.end()) {
    tree->Branch(itA->first,itA->second , itA->first+"["+entryVariableOf[itA->first]+"]/F" );
    itA++;
  }
}

void VariableContainer::PrintArrayValue(const TString& name) {
  float* printArray = arrayMap[name];
  int nEntries = intMap[entryVariableOf[name]];
  for(int i=0;i<nEntries;++i){
    cout << name+"[" << i << "] : " << printArray[i] << std::endl;
  }
}


void VariableContainer::Dump() const {
  auto itF= floatMap.begin();
  auto itFdefault = floatMapDefaults.begin();
  cout << "floats: " << endl;
  while (itF != floatMap.end()) {
    cout << itF->first << " : " << itF->second << " : " << itFdefault->second << endl;
    ++itF;
    ++itFdefault;
  }
  auto itI= intMap.begin();
  auto itIdefault = intMapDefaults.begin();
  cout << "ints: " << endl;
  while (itI != intMap.end()) {
    cout << itI->first << " : " << itI->second << " : " << itIdefault->second << endl;
    ++itI;
    ++itIdefault;
  }
}


float* VariableContainer::GetFloatVarPointer(const TString& name){
  if(floatMap.count(name)==0){
    cerr << name << " does not exist!" << endl;
    return 0;
  }
  return &(floatMap[name]);
}

float* VariableContainer::GetArrayVarPointer(const TString& name, int entry){
  if(arrayMap.count(name)==0){
    cerr << name << " does not exist!" << endl;
    return 0;
  }
  return &(arrayMap[name][entry]);
}


long* VariableContainer::GetIntVarPointer(const TString& name){
  if(intMap.count(name)==0&&floatMap.count(name)==0&&arrayMap.count(name)==0){
    cerr << name << " does not exist!" << endl;
    return 0;
  }
  return &(intMap[name]);
}


float VariableContainer::GetFloatVar(const TString& name) {
  float* x=GetFloatVarPointer(name);
  if(x!=0)
    return *x;
  else 
    return -999;
}


float VariableContainer::GetArrayVar(const TString& name, int entry) {
  float* x=GetArrayVarPointer(name,entry);
  if(x!=0)
    return *x;
  else 
    return -999;
}


long VariableContainer::GetIntVar(const TString& name) {
  long* x=GetIntVarPointer(name);
  if(x!=0)
    return *x;
  else 
    return -999;
}


void VariableContainer::checkIfVariableAlreadyInit(const TString& name) const {
  if( intMap.count(name)>0 || floatMap.count(name)>0 || arrayMap.count(name)>0 ) {
    throw cms::Exception("BadProcessor") << "Variable '" << name << "' already initialized!";
  }
}
