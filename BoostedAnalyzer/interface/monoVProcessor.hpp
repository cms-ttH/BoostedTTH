#ifndef BOOSTEDTTH_BOOSTEDANALYZER_monoVProcessor_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_monoVProcessor_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

class monoVProcessor: public TreeProcessor {

public:

	monoVProcessor();
	~monoVProcessor();

	void Init(const InputCollections& input, VariableContainer& var);
	void Process(const InputCollections& input, VariableContainer& var);
private:
	float tau1, tau2, tau3 ;
	bool monoVtagged_ChsPrun;
	bool monoVtagged_PuppiSoftDrop;
};

#endif
