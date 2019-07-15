#include "BoostedTTH/BoostedAnalyzer/interface/ProcessorTemplate.hpp"

using namespace std;

// all configurations should be done in constructor
ProcessorTemplate::ProcessorTemplate() {}
ProcessorTemplate::~ProcessorTemplate() {}

void ProcessorTemplate::Init(const InputCollections& input,
                             VariableContainer& vars) {
  vars.InitVar("HTjet");        // initialize a float variable
  vars.InitVar("N_Jets", "I");  // initialize an integer variable
  vars.InitVars("Jet_Pt",
                "N_Jets");  // initialize a float-array variable of length
                            // N_Jets (notice the *s* in InitVars)

  initialized = true;
}

void ProcessorTemplate::Process(const InputCollections& input,
                                VariableContainer& vars) {
  if (!initialized)
    cerr << "tree processor not initialized"
         << endl;  // complain if not initialized but keep running

  vars.FillVar(
      "N_Jets",
      input.selectedJets
          .size());  // fill variable N_Jets, type is found automatically
  float htjet = 0.;
  for (uint i = 0; i < input.selectedJets.size(); i++) {
    vars.FillVars("Jet_Pt", i,
                  input.selectedJets[i].pt());  // fill array entry i of Jet_Pt
                                                // (notice the *s* in FillVars)
    htjet += input.selectedJets[i].pt();
  }
  vars.FillVar("HTjet", htjet);  // fill htjets
}
