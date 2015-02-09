#ifndef TREEWRITER_HPP
#define TREEWRITER_HPP

#include <vector>

#include "TFile.h"
#include "TTree.h"

#include "BoostedTTH/BoostedAnalyzer/interface/VariableContainer.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/InputCollections.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"

/*
  The TreeWriter is used to write all the variables that are used in the MVA analysis in flat TTrees. Different Processors can be loaded that write a certain class of variables. Calculating BDT outputs and histograms from these variables will be supported soon.
 */
class TreeWriter{
  public:
    
    /**
       Creates a TreeWriter and the associated TTree/ 
    */
    TreeWriter();
    ~TreeWriter();
    
    /**
       Process a single event.
       @param outfileName filename of the created TTree
       @param input input collections (cannot be changed, this is left to the BEANRunner)
       @param sampleType type of the sample, decides wheter data or mc is analyzed, which mc-matching is possible and which ttbar subsample the event belongs to
       @param weights the nominal and systematics weights of the event
    */
    void Init(std::string fileName);
    bool Process(const InputCollections& input);
    void AddTreeProcessor(TreeProcessor* processor);


  private:
  
    void Init();
    void FillTree();
    bool initialized;
    TTree* tree;
    TFile* outFile;
    VariableContainer vars;
    std::vector<TreeProcessor*> processors;
};
#endif
