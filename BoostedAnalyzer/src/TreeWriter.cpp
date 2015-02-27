#include "BoostedTTH/BoostedAnalyzer/interface/TreeWriter.hpp"

using namespace std;

TreeWriter::TreeWriter(){
  initialized=false;
}


TreeWriter::~TreeWriter(){
  outFile->cd();
  tree->Write(); 
  outFile->Write();
  outFile->Close();
  cout << "Tree Written to " << outFile->GetPath() << endl;
}


void TreeWriter::Init( std::string fileName){
  
  outFile = new TFile( (fileName+"_Tree.root").c_str(), "RECREATE" );
  outFile->cd();
  
  tree = new TTree("MVATree","MVATree");
  vars = VariableContainer();
}


void TreeWriter::AddTreeProcessor(TreeProcessor* processor){
  processors.push_back(processor);
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
    processors[i]->Process(input,vars);
  }

  FillTree();
  return true;
}


void TreeWriter::FillTree(){
  tree->Fill();
}
