#include "BoostedTTH/BoostedAnalyzer/interface/JABDTthwProcessor.hpp"
using namespace std;

JABDTthwProcessor::JABDTthwProcessor(const edm::ParameterSet& iConfig)
{
  if( iConfig.existsAs<edm::ParameterSet>("JetAssignmentOptions",true) ){
      const edm::ParameterSet jaoptions = iConfig.getParameter<edm::ParameterSet>("JetAssignmentOptions");
      //load input variables
      std::string bdt_input_vars = loadVariables(jaoptions, "thw_varlist");
      
      //load weightpath to even JA BDT
      std::string weightpath = loadWeightPath(jaoptions, "thw_even_weightpath");
      if(weightpath != ""){
        pointerToEvenHypothesisCombinatorics.reset(new thwHypothesisCombinatorics(weightpath, bdt_input_vars));
      }
      else{
        std::cerr << "ERROR: unable to load 'thw_even_weightpath'";
        pointerToEvenHypothesisCombinatorics.reset(nullptr);
      }

      weightpath = loadWeightPath(jaoptions, "thw_odd_weightpath");
      if(weightpath != ""){
        pointerToOddHypothesisCombinatorics.reset(new thwHypothesisCombinatorics(weightpath, bdt_input_vars));
      }
      else{
        std::cerr << "ERROR: unable to load 'thw_odd_weightpath'";
        pointerToOddHypothesisCombinatorics.reset(nullptr);
      }
      
      // std::cout << "TYPE: " << typeid(pointerToHypothesisCombinatorics).name << std::endl;
      if( iConfig.existsAs<std::string>("thw_prefix",true) ) hypothesis = iConfig.getParameter<std::string>("thw_prefix");
      else hypothesis = "thw";
  }
  else{
    std::cerr << "ERROR: Could not find JetAssignmentOptions in global config! ";
    std::cerr << "Unable to find best permutation for tHq hypothesis!\n";
    pointerToEvenHypothesisCombinatorics.reset(nullptr);
    pointerToOddHypothesisCombinatorics.reset(nullptr);
    hypothesis = "NONE";
  }
}

JABDTthwProcessor::~JABDTthwProcessor(){

}
