#ifndef SYNCHRONIZER_HPP
#define SYNCHRONIZER_HPP

#include <vector>
#include <map>
#include <stdio.h>
#include <boost/format.hpp>

#include "BoostedTTH/BoostedAnalyzer/interface/InputCollections.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/Cutflow.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/VertexSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/LeptonSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonMassSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonMETSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/JetTagSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonJetTagSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BDT_v3.hpp"
#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"
#include "MiniAOD/MiniAODHelper/interface/TopTagger.h"

class Synchronizer{

public:
    Synchronizer();
    ~Synchronizer ();
    void DumpSyncExe1(int nfile,const InputCollections& input);
    void DumpSyncExe1(const InputCollections& input, std::ostream &out);
    void DumpSyncExe2(int nfile,const InputCollections& input, const InputCollections& input_jesup, const InputCollections& input_jesdown, const InputCollections& input_raw,const InputCollections& input_DL, const InputCollections& input_DL_jesup, const InputCollections& input_DL_jesdown, const InputCollections& input_DL_raw, MiniAODHelper& helper, int dataset_flag);
    void DumpSyncExe2(const InputCollections& input,const InputCollections& input_DL, MiniAODHelper& helper, std::ostream &out, Cutflow& cutflowSL,Cutflow& cutflowDL,int dataset_flag);
    void InitDumpSyncFile1(std::string filename);
    void InitDumpSyncFile2(std::string filename, bool BTagSystematics);
    void DumpSyncExe2Header(std::ostream &out);
    void DumpSyncExe2HeaderBTagSys(std::ostream &out);

private:
    ofstream* cutflowFile=0;
    vector<ofstream*> dumpFiles1;
    vector<ofstream*> dumpFiles2;
    vector<ofstream*> dumpFiles2_jesup;
    vector<ofstream*> dumpFiles2_jesdown;
    vector<ofstream*> dumpFiles2_raw;
    vector<Selection*> leptonSelections;
    vector<Selection*> dileptonSelections;

    vector<Selection*> dileptonSelection;
    vector<Selection*> dileptonMllSelections;
    vector<Selection*> dileptonMETSelection;

    Cutflow cutflowSL_jesup;
    Cutflow cutflowSL_jesdown;
    Cutflow cutflowSL_raw;
    Cutflow cutflowSL_nominal;
    Cutflow cutflowDL_jesup;
    Cutflow cutflowDL_jesdown;
    Cutflow cutflowDL_raw;
    Cutflow cutflowDL_nominal;

    std::vector<Cutflow> dummycutflow_DL;
    std::vector<Cutflow> dummycutflow_Mll;
    std::vector<Cutflow> dummycutflow_MET;

    TopTagger toptagger;
    BDT_v3 bdt3;
    bool initializedCutflowsWithSelections;
};


#endif
