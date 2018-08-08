#include "BoostedTTH/BoostedAnalyzer/interface/SelectionTagProcessor.hpp"

using namespace std;

SelectionTagProcessor::SelectionTagProcessor(const edm::ParameterSet& iConfig) {
	MonoJetGenSelectionProcessor* GenSelector = new MonoJetGenSelectionProcessor(iConfig);

}
SelectionTagProcessor::~SelectionTagProcessor() {}


void SelectionTagProcessor::Init(const InputCollections& input, VariableContainer& vars) {

	for (auto& map : input.selectionTags) {
		vars.InitVar(map.first, "I");
	}
	vars.InitVar("recoSelected", "I");
		
	// vars.InitVar("Miss", "I");
	// vars.InitVar("Fake", "I");
	// vars.InitVar("genSelected", "I");
	initialized = true;

}


void SelectionTagProcessor::Process(const InputCollections& input, VariableContainer& vars) {
	if (!initialized) cerr << "tree processor not initialized" << endl;
	recoSelected = true;
	// genSelected = true;

	for (auto& map : input.selectionTags) {
		vars.FillVar( map.first, int(map.second));
		if (!map.second) recoSelected = false;
	}

	// if(!GenSelector->GenMonoJetSelection(input)) genSelected = false;
	// else if(!GenSelector->GenLeptonVetoSelection(input)) genSelected = false;
	// else if(!GenSelector->GenBTagVetoSelection(input)) genSelected = false;
	// else if(!GenSelector->GenPhotonVetoSelection(input)) genSelected = false;
	// else if(!GenSelector->GenMETSelection(input)) genSelected = false;
	// else if(!GenSelector->GenVertexSelection(input)) genSelected = false;
	// else if(!GenSelector->GenmonoVselection(input)) genSelected = false;

	// miss = genSelected && !recoSelected;
	// fake = !genSelected && recoSelected;
	// vars.FillVar("Miss", miss);
	// vars.FillVar("Fake", fake);
	vars.FillVar("recoSelected", recoSelected);
	// vars.FillVar("genSelected", genSelected);
}


