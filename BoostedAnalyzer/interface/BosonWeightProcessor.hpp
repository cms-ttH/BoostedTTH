#ifndef BOOSTEDTTH_BOOSTEDANALYZER_BosonWeightProcessor_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_BosonWeightProcessor_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

class BosonWeightProcessor : public TreeProcessor {
   public:
    BosonWeightProcessor();
    BosonWeightProcessor(std::string era);
    ~BosonWeightProcessor();

    void Init(const InputCollections& input, VariableContainer& var);
    void Process(const InputCollections& input, VariableContainer& var);

   private:
    TFile* fWeightsW   = nullptr;
    TFile* fWeightsZvv = nullptr;
    TFile* fWeightsZll = nullptr;

    TH1D* hWbosonWeight_nominal   = nullptr;
    TH1D* hWbosonWeight_QCD1Up    = nullptr;
    TH1D* hWbosonWeight_QCD1Down  = nullptr;
    TH1D* hWbosonWeight_QCD2Up    = nullptr;
    TH1D* hWbosonWeight_QCD2Down  = nullptr;
    TH1D* hWbosonWeight_QCD3Up    = nullptr;
    TH1D* hWbosonWeight_QCD3Down  = nullptr;
    TH1D* hWbosonWeight_EW1Up     = nullptr;
    TH1D* hWbosonWeight_EW1Down   = nullptr;
    TH1D* hWbosonWeight_EW2Up     = nullptr;
    TH1D* hWbosonWeight_EW2Down   = nullptr;
    TH1D* hWbosonWeight_EW3Up     = nullptr;
    TH1D* hWbosonWeight_EW3Down   = nullptr;
    TH1D* hWbosonWeight_MixedUp   = nullptr;
    TH1D* hWbosonWeight_MixedDown = nullptr;
    TH1D* hWbosonWeight_AlphaUp   = nullptr;
    TH1D* hWbosonWeight_AlphaDown = nullptr;
    TH1D* hWbosonWeight_muRUp     = nullptr;
    TH1D* hWbosonWeight_muRDown   = nullptr;
    TH1D* hWbosonWeight_muFUp     = nullptr;
    TH1D* hWbosonWeight_muFDown   = nullptr;

    TH1D* hZvvbosonWeight_nominal   = nullptr;
    TH1D* hZvvbosonWeight_QCD1Up    = nullptr;
    TH1D* hZvvbosonWeight_QCD1Down  = nullptr;
    TH1D* hZvvbosonWeight_QCD2Up    = nullptr;
    TH1D* hZvvbosonWeight_QCD2Down  = nullptr;
    TH1D* hZvvbosonWeight_QCD3Up    = nullptr;
    TH1D* hZvvbosonWeight_QCD3Down  = nullptr;
    TH1D* hZvvbosonWeight_EW1Up     = nullptr;
    TH1D* hZvvbosonWeight_EW1Down   = nullptr;
    TH1D* hZvvbosonWeight_EW2Up     = nullptr;
    TH1D* hZvvbosonWeight_EW2Down   = nullptr;
    TH1D* hZvvbosonWeight_EW3Up     = nullptr;
    TH1D* hZvvbosonWeight_EW3Down   = nullptr;
    TH1D* hZvvbosonWeight_MixedUp   = nullptr;
    TH1D* hZvvbosonWeight_MixedDown = nullptr;
    TH1D* hZvvbosonWeight_AlphaUp   = nullptr;
    TH1D* hZvvbosonWeight_AlphaDown = nullptr;
    TH1D* hZvvbosonWeight_muRUp     = nullptr;
    TH1D* hZvvbosonWeight_muRDown   = nullptr;
    TH1D* hZvvbosonWeight_muFUp     = nullptr;
    TH1D* hZvvbosonWeight_muFDown   = nullptr;

    TH1D* hZllbosonWeight_nominal   = nullptr;
    TH1D* hZllbosonWeight_QCD1Up    = nullptr;
    TH1D* hZllbosonWeight_QCD1Down  = nullptr;
    TH1D* hZllbosonWeight_QCD2Up    = nullptr;
    TH1D* hZllbosonWeight_QCD2Down  = nullptr;
    TH1D* hZllbosonWeight_QCD3Up    = nullptr;
    TH1D* hZllbosonWeight_QCD3Down  = nullptr;
    TH1D* hZllbosonWeight_EW1Up     = nullptr;
    TH1D* hZllbosonWeight_EW1Down   = nullptr;
    TH1D* hZllbosonWeight_EW2Up     = nullptr;
    TH1D* hZllbosonWeight_EW2Down   = nullptr;
    TH1D* hZllbosonWeight_EW3Up     = nullptr;
    TH1D* hZllbosonWeight_EW3Down   = nullptr;
    TH1D* hZllbosonWeight_MixedUp   = nullptr;
    TH1D* hZllbosonWeight_MixedDown = nullptr;
    TH1D* hZllbosonWeight_AlphaUp   = nullptr;
    TH1D* hZllbosonWeight_AlphaDown = nullptr;
    TH1D* hZllbosonWeight_muRUp     = nullptr;
    TH1D* hZllbosonWeight_muRDown   = nullptr;
    TH1D* hZllbosonWeight_muFUp     = nullptr;
    TH1D* hZllbosonWeight_muFDown   = nullptr;

    double BosonWeight_nominal   = 1;
    double BosonWeight_QCD1Up    = 1;
    double BosonWeight_QCD1Down  = 1;
    double BosonWeight_QCD2Up    = 1;
    double BosonWeight_QCD2Down  = 1;
    double BosonWeight_QCD3Up    = 1;
    double BosonWeight_QCD3Down  = 1;
    double BosonWeight_EW1Up     = 1;
    double BosonWeight_EW1Down   = 1;
    double BosonWeight_EW2Up     = 1;
    double BosonWeight_EW2Down   = 1;
    double BosonWeight_EW3Up     = 1;
    double BosonWeight_EW3Down   = 1;
    double BosonWeight_MixedUp   = 1;
    double BosonWeight_MixedDown = 1;
    double BosonWeight_AlphaUp   = 1;
    double BosonWeight_AlphaDown = 1;
    double BosonWeight_muRUp     = 1;
    double BosonWeight_muRDown   = 1;
    double BosonWeight_muFUp     = 1;
    double BosonWeight_muFDown   = 1;
};

#endif
