#include "BoostedTTH/BoostedAnalyzer/interface/VariableContainer.hpp"

using namespace std;

VariableContainer::VariableContainer(){

}


VariableContainer::~VariableContainer(){

}


void VariableContainer::InitVar( TString name,float defaultValue, std::string type ) {
  if(intMap.count(name)>0||floatMap.count(name)>0||arrayMap.count(name)>0){
    cerr << name << " already initialized!" << endl;
  }
  if(type=="F"){
    floatMap[name] = 0;
    floatMapDefaults[name] = defaultValue;
    floatMapFilled[name] = false;
  }
  else if(type=="I"){
    intMap[name] = 0;
    intMapDefaults[name] = defaultValue;
    intMapFilled[name] = false;
  }
  else
    cout << "unknown type " << type << endl;
}


void VariableContainer::InitVar( TString name, std::string type ) {
  if(intMap.count(name)>0||floatMap.count(name)>0||arrayMap.count(name)>0){
    cerr << name << " already initialized!" << endl;
  }

  InitVar(name,-1.,type);
}


void VariableContainer::FillVar( TString name, float value ) {
  if(intMap.count(name)==0&&floatMap.count(name)==0){
    cerr << name << " does not exist!" << endl;
  }
  if(floatMap.count(name)!=0){
    if(floatMapFilled[name]){
      cerr << name << " already filled!" << endl;
    }
    floatMap[name] = value;
    floatMapFilled[name] = true;
  }
  if(intMap.count(name)!=0){
    if(intMapFilled[name]){
      cerr << name << " already filled!" << endl;
    }
    intMap[name] = value;
    intMapFilled[name] = true;
  }
//     std::cout << "filling variable " << name << " with " << value << std::endl;
}


void VariableContainer::InitVars( TString name, float defaultValue, TString nEntryVariable, int maxentries ){
  if(intMap.count(name)>0 || floatMap.count(name)>0 || arrayMap.count(name)>0){
    cerr << name << " already initialized!" << endl;
  }

  arrayMap[name] = new float[maxentries];
  arrayMapDefaults[name] = defaultValue;
  arrayMapFilled[name] = false;
  maxEntriesArrays[name] = maxentries;
  entryVariableOf[name] = nEntryVariable;
}


void VariableContainer::InitVars( TString name, TString nEntryVariable, int maxentries ){
  InitVars(name,-1.,nEntryVariable,maxentries);
}


void VariableContainer::FillVars( TString name, int index, float value ) {
  if(arrayMap.count(name)==0){
    cerr << name << " does not exist!" << endl;
  }
  else if(maxEntriesArrays[name]<index){
    cerr << "array " << name << " is shorter than " << index << endl;
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
    tree->Branch(itI->first, &(itI->second), itI->first+"/I" );
    itI++;
  }
  auto itA= arrayMap.begin();
  while (itA != arrayMap.end()) {
    tree->Branch(itA->first,itA->second , itA->first+"["+entryVariableOf[itA->first]+"]/F" );
    itA++;
  }
}

void VariableContainer::PrintArrayValue(TString name){
  
  float* printArray = arrayMap[name];
  int nEntries = intMap[entryVariableOf[name]];
  
  
  for(int i=0;i<nEntries;++i){
    cout << name+"[" << i << "] : " << printArray[i] << std::endl;
  }
}


void VariableContainer::Dump(){
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


float* VariableContainer::GetFloatVarPointer(TString name){
  if(floatMap.count(name)==0){
    cerr << name << " does not exist!" << endl;
    return 0;
  }
  return &(floatMap[name]);
}

float* VariableContainer::GetArrayVarPointer(TString name, int entry){
  if(arrayMap.count(name)==0){
    cerr << name << " does not exist!" << endl;
    return 0;
  }
  return &(arrayMap[name][entry]);
}


int* VariableContainer::GetIntVarPointer(TString name){
  if(intMap.count(name)==0&&floatMap.count(name)==0&&arrayMap.count(name)==0){
    cerr << name << " does not exist!" << endl;
    return 0;
  }
  return &(intMap[name]);
}


float VariableContainer::GetFloatVar(TString name){
  float* x=GetFloatVarPointer(name);
  if(x!=0)
    return *x;
  else 
    return -999;
}


float VariableContainer::GetArrayVar(TString name, int entry){
  float* x=GetArrayVarPointer(name,entry);
  if(x!=0)
    return *x;
  else 
    return -999;
}


int VariableContainer::GetIntVar(TString name){
  int* x=GetIntVarPointer(name);
  if(x!=0)
    return *x;
  else 
    return -999;
}
