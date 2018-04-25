#include "BoostedTTH/BoostedAnalyzer/interface/SelectionTagProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/MonoJetGenSelectionProcessor.hpp"

using namespace std;

SelectionTagProcessor::SelectionTagProcessor() {}
SelectionTagProcessor::~SelectionTagProcessor() {}


void SelectionTagProcessor::Init(const InputCollections& input, VariableContainer& vars) {

	for (auto& map : input.selectionTags) {
		vars.InitVar(map.first, "I");
	}
	initialized = true;

}


void SelectionTagProcessor::Process(const InputCollections& input, VariableContainer& vars) {
	if (!initialized) cerr << "tree processor not initialized" << endl;
	for (auto& map : input.selectionTags) {
		vars.FillVar( map.first, int(map.second));
	}
}


