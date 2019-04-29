#include "BoostedTTH/BoostedAnalyzer/interface/JABDTthqProcessor.hpp"
using namespace std;

JABDTthqProcessor::JABDTthqProcessor(const edm::ParameterSet& iConfig)
{
  if( iConfig.existsAs<edm::ParameterSet>("JetAssignmentOptions",true) ){
      const edm::ParameterSet jaoptions = iConfig.getParameter<edm::ParameterSet>("JetAssignmentOptions");
      std::string weightpath = "";
      try{
        weightpath = jaoptions.getParameter<std::string>("thq_weightpath");
      }
      catch(const std::exception& e){
          std::cerr << "ERROR: variable 'thq_weightpath' does not exist in ParameterSet 'JetAssignentOptions'\n";
          std::cerr << e.what() << std::endl;
          return;
      }

      std::string optional_varstring = "";
      if (jaoptions.existsAs<std::string>("thq_varlist", true)) optional_varstring = jaoptions.getParameter<std::string>("thq_varlist");
      
      pointerToHypothesisCombinatorics.reset(new thqHypothesisCombinatorics(weightpath, optional_varstring));
      if( iConfig.existsAs<std::string>("thq_prefix",true) ) hypothesis = iConfig.getParameter<std::string>("thq_prefix");
      else hypothesis = "thq";
  }
  else{
    std::cerr << "ERROR: Could not find JetAssignmentOptions in global config! ";
    std::cerr << "Unable to find best permutation for tHq hypothesis!\n";
    pointerToHypothesisCombinatorics.reset(nullptr);
    hypothesis = "NONE";
  }
}

JABDTthqProcessor::~JABDTthqProcessor(){

}
