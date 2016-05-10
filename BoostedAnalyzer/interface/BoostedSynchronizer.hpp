#ifndef BOOSTEDSYNCHRONIZER_HPP
#define BOOSTEDSYNCHRONIZER_HPP

#include <iomanip>
#include <vector>
#include <map>
#include <stdio.h>
#include <boost/format.hpp>

#include "BoostedTTH/BoostedAnalyzer/interface/InputCollections.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/Cutflow.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/VertexSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/LeptonSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/JetTagSelection.hpp"
#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"
#include "MiniAOD/MiniAODHelper/interface/TopTagger.h"
#include "MiniAOD/MiniAODHelper/interface/HiggsTagger.h"

class BoostedSynchronizer{

public:
    BoostedSynchronizer();
    ~BoostedSynchronizer ();
    void InitDumpSyncFile(std::string filename);
    void DumpSyncExeHeader(std::ostream &out);
    void DumpSyncExe(int nfile,const InputCollections& input, const InputCollections& input_jesup, const InputCollections& input_jesdown, MiniAODHelper& helper);
    void DumpSyncExe(const InputCollections& input, MiniAODHelper& helper, std::ostream &out, Cutflow& cutflowSL);

private:
    ofstream* cutflowFile=0;
    vector<ofstream*> dumpFiles;
    vector<ofstream*> dumpFiles_jesup;
    vector<ofstream*> dumpFiles_jesdown;
    vector<Selection*> selections;
        
    Cutflow cutflow_nominal;
    Cutflow cutflow_jesup;
    Cutflow cutflow_jesdown;

    bool initializedCutflowsWithSelections;
};


#endif
