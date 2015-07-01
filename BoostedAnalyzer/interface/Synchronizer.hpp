#ifndef SYNCHRONIZER_HPP
#define SYNCHRONIZER_HPP

#include <vector>
#include <map>
#include <stdio.h>
#include <boost/format.hpp>

#include "BoostedTTH/BoostedAnalyzer/interface/InputCollections.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/Cutflow.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/LeptonSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/JetTagSelection.hpp"
#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"

class Synchronizer{

public:
  Synchronizer();
  ~Synchronizer ();
  void DumpSyncExe1(int nfile,const InputCollections& input);
  void DumpSyncExe1(const InputCollections& input, std::ostream &out);
  void DumpSyncExe2(int nfile,const InputCollections& input, const MiniAODHelper helper, sysType::sysType);
  void DumpSyncExe2(const InputCollections& input, const MiniAODHelper helper, std::ostream &out);
  void InitDumpSyncFile1(std::string filename);
  void InitDumpSyncFile2(std::string filename);
  void DumpSyncExe2Header(std::ostream &out);

private:
  vector<std::ofstream*> dumpFiles1;
  vector<std::ofstream*> dumpFiles2;
  vector<std::ofstream*> dumpFiles2_jesup;
  vector<std::ofstream*> dumpFiles2_jesdown;
  LeptonSelection* leptonSelection;
  JetTagSelection* jtSelectionDL;
  JetTagSelection* jtSelectionSL;

};


#endif
