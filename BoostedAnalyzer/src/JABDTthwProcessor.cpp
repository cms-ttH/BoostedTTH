#include "BoostedTTH/BoostedAnalyzer/interface/JABDTthwProcessor.hpp"
using namespace std;

JABDTthwProcessor::JABDTthwProcessor(const edm::ParameterSet& iConfig)
{
  if( iConfig.existsAs<edm::ParameterSet>("JetAssignmentOptions",true) ){
      const edm::ParameterSet jaoptions = iConfig.getParameter<edm::ParameterSet>("JetAssignmentOptions");
      std::string weightpath = "";
      try{
        weightpath = jaoptions.getParameter<std::string>("thw_weightpath");
      }
      catch(const std::exception& e){
          std::cerr << "ERROR: variable 'thw_weightpath' does not exist in ParameterSet 'JetAssignentOptions'\n";
          std::cerr << e.what() << std::endl;
          return;
      }

      std::string optional_varstring = "";
      if (jaoptions.existsAs<std::string>("thw_varlist", true)) optional_varstring = jaoptions.getParameter<std::string>("thw_varlist");
      
      pointerToHypothesisCombinatorics.reset(new thwHypothesisCombinatorics(weightpath, optional_varstring));
      if( iConfig.existsAs<std::string>("thw_prefix",true) ) hypothesis = iConfig.getParameter<std::string>("thw_prefix");
      else hypothesis = "thw";
  }
  else{
    std::cerr << "ERROR: Could not find JetAssignmentOptions in global config! ";
    std::cerr << "Unable to find best permutation for tHq hypothesis!\n";
    pointerToHypothesisCombinatorics.reset(nullptr);
    hypothesis = "NONE";
  }
}

JABDTthwProcessor::~JABDTthwProcessor(){

}
