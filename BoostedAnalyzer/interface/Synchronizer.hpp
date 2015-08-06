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
#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonMassSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/METSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/JetTagSelection.hpp"
#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"
#include "MiniAOD/MiniAODHelper/interface/TopTagger.h"

class Synchronizer{

public:
    Synchronizer();
    ~Synchronizer ();
    void DumpSyncExe1(int nfile,const InputCollections& input);
    void DumpSyncExe1(const InputCollections& input, std::ostream &out);
    void DumpSyncExe2(int nfile,const InputCollections& input, const InputCollections& input_jesup, const InputCollections& input_jesdown, const InputCollections& input_raw, const MiniAODHelper helper);
    void DumpSyncExe2(const InputCollections& input, const MiniAODHelper helper, std::ostream &out);
    void InitDumpSyncFile1(std::string filename);
    void InitDumpSyncFile2(std::string filename);
    void DumpSyncExe2Header(std::ostream &out);

private:
    vector<ofstream*> dumpFiles1;
    vector<ofstream*> dumpFiles2;
    vector<ofstream*> dumpFiles2_jesup;
    vector<ofstream*> dumpFiles2_jesdown;
    vector<ofstream*> dumpFiles2_raw;
    vector<Selection*> leptonSelections;
    vector<Selection*> dileptonSelections;
    Cutflow cutflowSL;
    Cutflow cutflowDL;
    TopTagger toptagger;
};


#endif
