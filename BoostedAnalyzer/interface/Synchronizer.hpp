#ifndef SYNCHRONIZER_HPP
#define SYNCHRONIZER_HPP

#include <vector>
#include <assert.h>
#include <map>
#include <stdio.h>
#include <boost/format.hpp>

#include "BoostedTTH/BoostedAnalyzer/interface/InputCollections.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/Cutflow.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/FilterSelection.hpp"
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

//namespace dataSet{ enum dataSet{ el, mu, elel, elmu, mumu}; }

class Synchronizer{

public:
    Synchronizer();
    ~Synchronizer ();
    void DumpSyncExe(const std::vector<InputCollections>& inputs);
    void Init(std::string filename, const std::vector<std::string>& jetSystematics,const edm::ParameterSet& iConfig,MiniAODHelper* helper_);
    void DumpSyncExeHeader(std::ostream &out);


private:
    void DumpSyncExe(const InputCollections& input,std::ostream &out,Cutflow& cutflowSL,Cutflow& cutflowDL);
    vector<ofstream*> cutflowFilesDL;
    vector<ofstream*> cutflowFilesSL;
    vector<ofstream*> dumpFiles;
    vector<Selection*> selectionsSL;
    vector<Selection*> selectionsDL;
    std::vector<Cutflow> cutflowsDL;
    std::vector<Cutflow> cutflowsSL;
    std::vector<std::string> systematics;

    MiniAODHelper* helper;

    bool initializedCutflowsWithSelections;
    std::string datasetFlag;
};


#endif
