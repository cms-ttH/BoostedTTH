#include "BoostedTTH/BoostedAnalyzer/interface/TreeWriter.hpp"

using namespace std;

TreeWriter::TreeWriter(){
  tree=0;
  outFile=0;
  initialized=false;
}


TreeWriter::~TreeWriter(){
  for(uint i=0; i<stopwatches.size(); i++){
    cout << "time spent in " << processorNames[i] << " -- real time: " << stopwatches[i].RealTime() << ", cpu time: " << stopwatches[i].CpuTime() << endl;
  }
  if(outFile!=0){
    outFile->cd();
  }
  if(tree!=0){
    tree->Write(); 
  }  
  if(outFile!=0){
    outFile->Write();
    outFile->Close();
  }
  if(tree!=0){
    cout << "Tree Written to " << outFile->GetPath() << endl;
  }

}

void TreeWriter::Init( std::string fileName){
    cout << "initializing tree writer with" << fileName <<endl;
  outFile = new TFile( (fileName+"_Tree.root").c_str(), "RECREATE" );
  outFile->cd();

  tree = new TTree("MVATree","MVATree");
}


void TreeWriter::AddTreeProcessor(TreeProcessor* processor,string name){
  processors.push_back(processor);
  processorNames.push_back(name);
  stopwatches.push_back(TStopwatch());
}

std::vector<TreeProcessor*> TreeWriter::GetTreeProcessors() const{
  return processors;
}

std::vector<std::string> TreeWriter::GetTreeProcessorNames() const{
  return processorNames;
}

bool TreeWriter::Process(const InputCollections& input) {  

  if(!initialized){
    for(uint i=0; i<processors.size(); i++){
      processors[i]->Init(input,vars);
    }
    
    vars.ConnectTree(tree);
    
    initialized=true;
  }
  vars.SetDefaultValues();
  
  for(uint i=0; i<processors.size(); i++){
    stopwatches[i].Start(false);
    processors[i]->Process(input,vars);
    stopwatches[i].Stop();
  }

  FillTree();
  return true;
}


void TreeWriter::FillTree(){
  tree->Fill();
}

