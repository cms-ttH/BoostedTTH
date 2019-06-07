#include "BoostedTTH/BoostedAnalyzer/interface/JABDTthqProcessor.hpp"
using namespace std;

JABDTthqProcessor::JABDTthqProcessor(const edm::ParameterSet& iConfig)
{
  if( iConfig.existsAs<edm::ParameterSet>("JetAssignmentOptions",true) ){
      const edm::ParameterSet jaoptions = iConfig.getParameter<edm::ParameterSet>("JetAssignmentOptions");
      //load input variables
      std::string bdt_input_vars = loadVariables(jaoptions, "thq_varlist");
      
      //load weightpath to even JA BDT
      std::string weightpath = loadWeightPath(jaoptions, "thq_even_weightpath");
      if(weightpath != ""){
        pointerToEvenHypothesisCombinatorics.reset(new thqHypothesisCombinatorics(weightpath, bdt_input_vars));
      }
      else{
        std::cerr << "ERROR: unable to load 'thq_even_weightpath'";
        pointerToEvenHypothesisCombinatorics.reset(nullptr);
      }

      weightpath = loadWeightPath(jaoptions, "thq_odd_weightpath");
      if(weightpath != ""){
        pointerToOddHypothesisCombinatorics.reset(new thqHypothesisCombinatorics(weightpath, bdt_input_vars));
      }
      else{
        std::cerr << "ERROR: unable to load 'thq_odd_weightpath'";
        pointerToOddHypothesisCombinatorics.reset(nullptr);
      }
      
      // std::cout << "TYPE: " << typeid(pointerToHypothesisCombinatorics).name << std::endl;
      if( iConfig.existsAs<std::string>("thq_prefix",true) ) hypothesis = iConfig.getParameter<std::string>("thq_prefix");
      else hypothesis = "thq";
  }
  else{
    std::cerr << "ERROR: Could not find JetAssignmentOptions in global config! ";
    std::cerr << "Unable to find best permutation for tHq hypothesis!\n";
    pointerToEvenHypothesisCombinatorics.reset(nullptr);
    pointerToOddHypothesisCombinatorics.reset(nullptr);
    hypothesis = "NONE";
  }
}

JABDTthqProcessor::~JABDTthqProcessor(){

}
