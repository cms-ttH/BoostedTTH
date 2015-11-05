#ifndef TREEWRITER_HPP
#define TREEWRITER_HPP

#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TStopwatch.h"

#include "BoostedTTH/BoostedAnalyzer/interface/VariableContainer.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/InputCollections.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"

/*
  The TreeWriter opens the output TFile and a TTree and has a variable container. At the begin of the analysis different TreeProcessors are added to the TreeWriter. For every event the TreeWriter is given an InputCollection. With the help of the processors the output variables are calculated and written in the VariableContainer. The content VariableContainer is then written into the TTree. 
*/
class TreeWriter{
  public:
    
    TreeWriter();
    ~TreeWriter();
    
    /**
       Initialize the tree
       @param fileName  filename of the created TTree
    */
    void Init(std::string fileName);

    /**
       Analyze a single event
       @param input the event information that is used to calculate the variables
    */
    bool Process(const InputCollections& input);

    /**
       Before the event loop different processors can be added to the TreeWriter. These will write into the trees whenever Process is called
       @param processor the TreeProcessor to add
    */
    void AddTreeProcessor(TreeProcessor* processor, std::string name);

    /**
       Returns references to all used Processors (in case you want to use them in a different TreeWriter)
    */
    std::vector<TreeProcessor*> GetTreeProcessors() const;

    /**
       Returns names of all used Processors (in case you want to use them in a different TreeWriter)
    */
    std::vector<std::string> GetTreeProcessorNames() const;

  private:
  
    void FillTree();
    TTree* tree;
    TFile* outFile;
    bool initialized;
    VariableContainer vars;
    std::vector<TreeProcessor*> processors;
    std::vector<TStopwatch> stopwatches;
    std::vector<std::string> processorNames;

};
#endif
