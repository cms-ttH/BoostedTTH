#include "BoostedTTH/BoostedAnalyzer/interface/JABDTttbarProcessor.hpp"
using namespace std;

JABDTttbarProcessor::JABDTttbarProcessor(const edm::ParameterSet& iConfig)
{
  if( iConfig.existsAs<edm::ParameterSet>("JetAssignmentOptions",true) ){
      const edm::ParameterSet jaoptions = iConfig.getParameter<edm::ParameterSet>("JetAssignmentOptions");
      //load input variables
      std::string bdt_input_vars = loadVariables(jaoptions, "ttbar_varlist");
      
      //load weightpath to even JA BDT
      std::string weightpath = loadWeightPath(jaoptions, "ttbar_even_weightpath");
      if(weightpath != ""){
        pointerToEvenHypothesisCombinatorics.reset(new ttbarHypothesisCombinatorics(weightpath, bdt_input_vars));
      }
      else{
        std::cerr << "ERROR: unable to load 'ttbar_even_weightpath'";
        pointerToEvenHypothesisCombinatorics.reset(nullptr);
      }

      weightpath = loadWeightPath(jaoptions, "ttbar_odd_weightpath");
      if(weightpath != ""){
        pointerToOddHypothesisCombinatorics.reset(new ttbarHypothesisCombinatorics(weightpath, bdt_input_vars));
      }
      else{
        std::cerr << "ERROR: unable to load 'ttbar_odd_weightpath'";
        pointerToOddHypothesisCombinatorics.reset(nullptr);
      }
      
      // std::cout << "TYPE: " << typeid(pointerToHypothesisCombinatorics).name << std::endl;
      if( iConfig.existsAs<std::string>("ttbar_prefix",true) ) hypothesis = iConfig.getParameter<std::string>("ttbar_prefix");
      else hypothesis = "ttbar";
  }
  else{
    std::cerr << "ERROR: Could not find JetAssignmentOptions in global config! ";
    std::cerr << "Unable to find best permutation for tHq hypothesis!\n";
    pointerToEvenHypothesisCombinatorics.reset(nullptr);
    pointerToOddHypothesisCombinatorics.reset(nullptr);
    hypothesis = "NONE";
  }
}

JABDTttbarProcessor::~JABDTttbarProcessor(){

}
