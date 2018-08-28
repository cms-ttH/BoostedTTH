#ifndef BOOSTEDTTH_BOOSTEDANALYZER_BosonWeightProcessor_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_BosonWeightProcessor_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"


class BosonWeightProcessor: public TreeProcessor {

public:

	BosonWeightProcessor();
	~BosonWeightProcessor();

	void Init(const InputCollections& input, VariableContainer& var);
	void Process(const InputCollections& input, VariableContainer& var);
private:
	TFile* fWeightsW = 0;
	TFile* fWeightsZvv = 0;
	TFile* fWeightsZll = 0;

	TH1D* hWbosonWeight_nominal = 0;
	TH1D* hWbosonWeight_QCD1Up = 0;
	TH1D* hWbosonWeight_QCD1Down = 0;
	TH1D* hWbosonWeight_QCD2Up = 0;
	TH1D* hWbosonWeight_QCD2Down = 0;
	TH1D* hWbosonWeight_QCD3Up = 0;
	TH1D* hWbosonWeight_QCD3Down = 0;
	TH1D* hWbosonWeight_EW1Up = 0;
	TH1D* hWbosonWeight_EW1Down = 0;
	TH1D* hWbosonWeight_EW2Up = 0;
	TH1D* hWbosonWeight_EW2Down = 0;
	TH1D* hWbosonWeight_EW3Up = 0;
	TH1D* hWbosonWeight_EW3Down = 0;
	TH1D* hWbosonWeight_MixedUp = 0;
	TH1D* hWbosonWeight_MixedDown = 0;
	TH1D* hWbosonWeight_AlphaUp = 0;
	TH1D* hWbosonWeight_AlphaDown = 0;
	TH1D* hWbosonWeight_muRUp = 0;
	TH1D* hWbosonWeight_muRDown = 0;
	TH1D* hWbosonWeight_muFUp = 0;
	TH1D* hWbosonWeight_muFDown = 0;


	TH1D* hZvvbosonWeight_nominal = 0;
	TH1D* hZvvbosonWeight_QCD1Up = 0;
	TH1D* hZvvbosonWeight_QCD1Down = 0;
	TH1D* hZvvbosonWeight_QCD2Up = 0;
	TH1D* hZvvbosonWeight_QCD2Down = 0;
	TH1D* hZvvbosonWeight_QCD3Up = 0;
	TH1D* hZvvbosonWeight_QCD3Down = 0;
	TH1D* hZvvbosonWeight_EW1Up = 0;
	TH1D* hZvvbosonWeight_EW1Down = 0;
	TH1D* hZvvbosonWeight_EW2Up = 0;
	TH1D* hZvvbosonWeight_EW2Down = 0;
	TH1D* hZvvbosonWeight_EW3Up = 0;
	TH1D* hZvvbosonWeight_EW3Down = 0;
	TH1D* hZvvbosonWeight_MixedUp = 0;
	TH1D* hZvvbosonWeight_MixedDown = 0;
	TH1D* hZvvbosonWeight_AlphaUp = 0;
	TH1D* hZvvbosonWeight_AlphaDown = 0;
	TH1D* hZvvbosonWeight_muRUp = 0;
	TH1D* hZvvbosonWeight_muRDown = 0;
	TH1D* hZvvbosonWeight_muFUp = 0;
	TH1D* hZvvbosonWeight_muFDown = 0;

	TH1D* hZllbosonWeight_nominal = 0;
	TH1D* hZllbosonWeight_QCD1Up = 0;
	TH1D* hZllbosonWeight_QCD1Down = 0;
	TH1D* hZllbosonWeight_QCD2Up = 0;
	TH1D* hZllbosonWeight_QCD2Down = 0;
	TH1D* hZllbosonWeight_QCD3Up = 0;
	TH1D* hZllbosonWeight_QCD3Down = 0;
	TH1D* hZllbosonWeight_EW1Up = 0;
	TH1D* hZllbosonWeight_EW1Down = 0;
	TH1D* hZllbosonWeight_EW2Up = 0;
	TH1D* hZllbosonWeight_EW2Down = 0;
	TH1D* hZllbosonWeight_EW3Up = 0;
	TH1D* hZllbosonWeight_EW3Down = 0;
	TH1D* hZllbosonWeight_MixedUp = 0;
	TH1D* hZllbosonWeight_MixedDown = 0;
	TH1D* hZllbosonWeight_AlphaUp = 0;
	TH1D* hZllbosonWeight_AlphaDown = 0;
	TH1D* hZllbosonWeight_muRUp = 0;
	TH1D* hZllbosonWeight_muRDown = 0;
	TH1D* hZllbosonWeight_muFUp = 0;
	TH1D* hZllbosonWeight_muFDown = 0;

	double BosonWeight_nominal = 1;
	double BosonWeight_QCD1Up = 1;
	double BosonWeight_QCD1Down = 1;
	double BosonWeight_QCD2Up = 1;
	double BosonWeight_QCD2Down = 1;
	double BosonWeight_QCD3Up = 1;
	double BosonWeight_QCD3Down = 1;
	double BosonWeight_EW1Up = 1;
	double BosonWeight_EW1Down = 1;
	double BosonWeight_EW2Up = 1;
	double BosonWeight_EW2Down = 1;
	double BosonWeight_EW3Up = 1;
	double BosonWeight_EW3Down = 1;
	double BosonWeight_MixedUp = 1;
	double BosonWeight_MixedDown = 1;
	double BosonWeight_AlphaUp = 1;
	double BosonWeight_AlphaDown = 1;
	double BosonWeight_muRUp = 1;
	double BosonWeight_muRDown = 1;
	double BosonWeight_muFUp = 1;
	double BosonWeight_muFDown = 1;


};

#endif
