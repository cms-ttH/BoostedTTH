#ifndef BOOSTEDTTH_BOOSTEDANALYZER_SelectionTagPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_SelectionTagPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/MonoJetGenSelectionProcessor.hpp"


class SelectionTagProcessor: public TreeProcessor {

public:

	// SelectionTagProcessor(const edm::ParameterSet& iConfig);
	// explicit SelectionTagProcessor(const edm::ParameterSet&);
	SelectionTagProcessor(const edm::ParameterSet&);
	~SelectionTagProcessor();

	void Init(const InputCollections& input, VariableContainer& var);
	void Process(const InputCollections& input, VariableContainer& var);

	bool miss;
	bool fake;
	bool recoSelected;
	bool genSelected;
	MonoJetGenSelectionProcessor* GenSelector;


private:

};

#endif