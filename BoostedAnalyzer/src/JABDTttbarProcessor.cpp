#include "BoostedTTH/BoostedAnalyzer/interface/JABDTttbarProcessor.hpp"
using namespace std;

JABDTttbarProcessor::JABDTttbarProcessor(const edm::ParameterSet& iConfig)
{
  if( iConfig.existsAs<edm::ParameterSet>("JetAssignmentOptions",true) ){
      const edm::ParameterSet jaoptions = iConfig.getParameter<edm::ParameterSet>("JetAssignmentOptions");
      std::string weightpath = "";
      try{
        weightpath = std::string(getenv("CMSSW_BASE")) + "/src/" +jaoptions.getParameter<std::string>("ttbar_weightpath");
      }
      catch(const std::exception& e){
          std::cerr << "ERROR: variable 'ttbar_weightpath' does not exist in ParameterSet 'JetAssignentOptions'\n";
          std::cerr << e.what() << std::endl;
          return;
      }
      std::cout << "INIT OF JABDTttbarProcessor\n";
      std::cout << "FOUND THIS WEIGHTFILE: " << weightpath << std::endl;
      std::string optional_varstring = "";
      if (jaoptions.existsAs<std::string>("ttbar_varlist", true)) optional_varstring = jaoptions.getParameter<std::string>("ttbar_varlist");
      std::cout << "INTIIALIZING 'ttbarHypothesisCombinatorics\n";
      pointerToHypothesisCombinatorics.reset(new ttbarHypothesisCombinatorics(weightpath, optional_varstring));
      // std::cout << "TYPE: " << typeid(pointerToHypothesisCombinatorics).name << std::endl;
      if( iConfig.existsAs<std::string>("ttbar_prefix",true) ) hypothesis = iConfig.getParameter<std::string>("ttbar_prefix");
      else hypothesis = "ttbar";
  }
  else{
    std::cerr << "ERROR: Could not find JetAssignmentOptions in global config! ";
    std::cerr << "Unable to find best permutation for tHq hypothesis!\n";
    pointerToHypothesisCombinatorics.reset(nullptr);
    hypothesis = "NONE";
  }
}

JABDTttbarProcessor::~JABDTttbarProcessor(){

}
