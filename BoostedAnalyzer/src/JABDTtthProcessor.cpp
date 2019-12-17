#include "BoostedTTH/BoostedAnalyzer/interface/JABDTtthProcessor.hpp"
using namespace std;

JABDTtthProcessor::JABDTtthProcessor(const edm::ParameterSet& iConfig)
{
  if( iConfig.existsAs<edm::ParameterSet>("JetAssignmentOptions",true) ){
      const edm::ParameterSet jaoptions = iConfig.getParameter<edm::ParameterSet>("JetAssignmentOptions");
      //load input variables
      std::string bdt_input_vars = loadVariables(jaoptions, "ttH_varlist");
      
      //load weightpath to even JA BDT
      std::string weightpath = loadWeightPath(jaoptions, "ttH_even_weightpath");
      if(weightpath != ""){
        pointerToEvenHypothesisCombinatorics.reset(new tthHypothesisCombinatorics(weightpath, bdt_input_vars));
      }
      else{
        std::cerr << "ERROR: unable to load 'ttH_even_weightpath'";
        pointerToEvenHypothesisCombinatorics.reset(nullptr);
      }

      weightpath = loadWeightPath(jaoptions, "ttH_odd_weightpath");
      if(weightpath != ""){
        pointerToOddHypothesisCombinatorics.reset(new tthHypothesisCombinatorics(weightpath, bdt_input_vars));
      }
      else{
        std::cerr << "ERROR: unable to load 'ttH_odd_weightpath'";
        pointerToOddHypothesisCombinatorics.reset(nullptr);
      }
      
      // std::cout << "TYPE: " << typeid(pointerToHypothesisCombinatorics).name << std::endl;
      if( iConfig.existsAs<std::string>("ttH_prefix",true) ) hypothesis = iConfig.getParameter<std::string>("ttH_prefix");
      else hypothesis = "ttH";
  }
  else{
    std::cerr << "ERROR: Could not find JetAssignmentOptions in global config! ";
    std::cerr << "Unable to find best permutation for tHq hypothesis!\n";
    pointerToEvenHypothesisCombinatorics.reset(nullptr);
    pointerToOddHypothesisCombinatorics.reset(nullptr);
    hypothesis = "NONE";
  }
}

JABDTtthProcessor::~JABDTtthProcessor(){

}
