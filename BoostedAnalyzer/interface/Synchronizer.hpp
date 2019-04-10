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
#include "BoostedTTH/BoostedAnalyzer/interface/METSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonJetTagSelection.hpp"
#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"
#include "MiniAOD/MiniAODHelper/interface/TopTagger.h"
#include "MiniAOD/MiniAODHelper/interface/LeptonSFHelper.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "TTH/CommonClassifier/interface/MVAvars.h"


class Synchronizer{

public:
    Synchronizer(const edm::ParameterSet& iConfig,edm::ConsumesCollector && iC);
    ~Synchronizer ();
    void DumpSyncExe(const std::vector<InputCollections>& inputs, bool dumpExtended, std::vector<int> dumpAlwaysEvents);
    void Init(std::string filename, const std::vector<std::string>& jetSystematics,const edm::ParameterSet& iConfig,MiniAODHelper* helper_,LeptonSFHelper* leptonsfhelper_,bool dumpExtended);
    void DumpSyncExeHeader(std::ostream &out, bool dumpExtended=false);


private:
    void DumpSyncExe(const InputCollections& input,std::ostream &out,Cutflow& cutflowSL,Cutflow& cutflowDL, bool dumpExtended,  std::vector<int> dumpAlwaysEvents);
    vector<ofstream*> cutflowFilesDL;
    vector<ofstream*> cutflowFilesSL;
    vector<ofstream*> dumpFiles;
    vector<Selection*> selectionsSL;
    vector<Selection*> selectionsDL;
    std::vector<Cutflow> cutflowsDL;
    std::vector<Cutflow> cutflowsSL;
    std::vector<std::string> systematics;

    MiniAODHelper* helper;
    LeptonSFHelper* leptonsfhelper;

    //MVAvars from CommonClassifier classifier for sl channel
    MVAvars *mvavars;
    std::map<std::string, float> varMap;
    std::unique_ptr<MVAvars> pointerToMVAvars = nullptr;

    bool initializedCutflowsWithSelections;
    std::string dataset;

    edm::EDGetTokenT< std::vector<pat::Electron> > rawElToken;
    edm::EDGetTokenT< std::vector<pat::Muon> > rawMuToken;

    bool isData;

};


#endif
