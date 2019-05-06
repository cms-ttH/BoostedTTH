#include "BoostedTTH/BoostedAnalyzer/interface/JABDTtthProcessor.hpp"
using namespace std;

JABDTtthProcessor::JABDTtthProcessor(const edm::ParameterSet& iConfig)
{
  if( iConfig.existsAs<edm::ParameterSet>("JetAssignmentOptions",true) ){
      const edm::ParameterSet jaoptions = iConfig.getParameter<edm::ParameterSet>("JetAssignmentOptions");
      std::string weightpath = "";
      try{
        weightpath = jaoptions.getParameter<std::string>("tth_weightpath");
      }
      catch(const std::exception& e){
          std::cerr << "ERROR: variable 'tth_weightpath' does not exist in ParameterSet 'JetAssignentOptions'\n";
          std::cerr << e.what() << std::endl;
          return;
      }

      std::string optional_varstring = "";
      if (jaoptions.existsAs<std::string>("tth_varlist", true)) optional_varstring = jaoptions.getParameter<std::string>("tth_varlist");
      
      pointerToHypothesisCombinatorics.reset(new tthHypothesisCombinatorics(weightpath, optional_varstring));
      if( iConfig.existsAs<std::string>("tth_prefix",true) ) hypothesis = iConfig.getParameter<std::string>("tth_prefix");
      else hypothesis = "tth";
  }
  else{
    std::cerr << "ERROR: Could not find JetAssignmentOptions in global config! ";
    std::cerr << "Unable to find best permutation for tHq hypothesis!\n";
    pointerToHypothesisCombinatorics.reset(nullptr);
    hypothesis = "NONE";
  }
}

JABDTtthProcessor::~JABDTtthProcessor(){

}
