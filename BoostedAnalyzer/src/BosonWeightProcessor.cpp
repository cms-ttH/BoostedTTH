#include "BoostedTTH/BoostedAnalyzer/interface/BosonWeightProcessor.hpp"

using namespace std;

BosonWeightProcessor::BosonWeightProcessor() {}
BosonWeightProcessor::~BosonWeightProcessor() {}


void BosonWeightProcessor::Init(const InputCollections& input, VariableContainer& vars) {

  vars.InitVar( "BosonWeight_nominal" );

  vars.InitVar( "BosonWeight_QCD1Up" );
  vars.InitVar( "BosonWeight_QCD1Down" );
  vars.InitVar( "BosonWeight_QCD2Up" );
  vars.InitVar( "BosonWeight_QCD2Down" );
  vars.InitVar( "BosonWeight_QCD3Up" );
  vars.InitVar( "BosonWeight_QCD3Down" );

  vars.InitVar( "BosonWeight_EW1Up" );
  vars.InitVar( "BosonWeight_EW1Down" );
  vars.InitVar( "BosonWeight_EW2Up" );
  vars.InitVar( "BosonWeight_EW2Down" );
  vars.InitVar( "BosonWeight_EW3Up" );
  vars.InitVar( "BosonWeight_EW3Down" );

  vars.InitVar( "BosonWeight_MixedUp" );
  vars.InitVar( "BosonWeight_MixedDown" );
  vars.InitVar( "BosonWeight_AlphaUp" );
  vars.InitVar( "BosonWeight_AlphaDown" );

  vars.InitVar( "BosonWeight_muRUp" );
  vars.InitVar( "BosonWeight_muRDown" );
  vars.InitVar( "BosonWeight_muFUp" );
  vars.InitVar( "BosonWeight_muFDown" );

  fWeightsW = new TFile("../data/TheoryXS_evj.root");
  hWbosonWeight_nominal =   (TH1D*)fWeightsW->Get("evj_NNLO_NLO_nnn_nnn_n");
  hWbosonWeight_QCD1Up =    (TH1D*)fWeightsW->Get("evj_NNLO_NLO_unn_nnn_n");
  hWbosonWeight_QCD1Down =  (TH1D*)fWeightsW->Get("evj_NNLO_NLO_dnn_nnn_n");
  hWbosonWeight_QCD2Up =    (TH1D*)fWeightsW->Get("evj_NNLO_NLO_nun_nnn_n");
  hWbosonWeight_QCD2Down =  (TH1D*)fWeightsW->Get("evj_NNLO_NLO_ndn_nnn_n");
  hWbosonWeight_QCD3Up =    (TH1D*)fWeightsW->Get("evj_NNLO_NLO_nnu_nnn_n");
  hWbosonWeight_QCD3Down =  (TH1D*)fWeightsW->Get("evj_NNLO_NLO_nnd_nnn_n");
  hWbosonWeight_EW1Up =     (TH1D*)fWeightsW->Get("evj_NNLO_NLO_nnn_unn_n");
  hWbosonWeight_EW1Down =   (TH1D*)fWeightsW->Get("evj_NNLO_NLO_nnn_dnn_n");
  hWbosonWeight_EW2Up =     (TH1D*)fWeightsW->Get("evj_NNLO_NLO_nnn_nun_n");
  hWbosonWeight_EW2Down =   (TH1D*)fWeightsW->Get("evj_NNLO_NLO_nnn_ndn_n");
  hWbosonWeight_EW3Up =     (TH1D*)fWeightsW->Get("evj_NNLO_NLO_nnn_nnu_n");
  hWbosonWeight_EW3Down =   (TH1D*)fWeightsW->Get("evj_NNLO_NLO_nnn_nnd_n");
  hWbosonWeight_MixedUp =   (TH1D*)fWeightsW->Get("evj_NNLO_NLO_nnn_nnn_u");
  hWbosonWeight_MixedDown = (TH1D*)fWeightsW->Get("evj_NNLO_NLO_nnn_nnn_d");
  hWbosonWeight_AlphaUp =   (TH1D*)fWeightsW->Get("evj_NNLO_NLO_nnn_nnn_n_alpha_up");
  hWbosonWeight_AlphaDown = (TH1D*)fWeightsW->Get("evj_NNLO_NLO_nnn_nnn_n_alpha_down");
  hWbosonWeight_muRUp =     (TH1D*)fWeightsW->Get("evj_NNLO_NLO_nnn_nnn_n_Weight_scale_variation_muR_2p0_muF_1p0");
  hWbosonWeight_muRDown =   (TH1D*)fWeightsW->Get("evj_NNLO_NLO_nnn_nnn_n_Weight_scale_variation_muR_0p5_muF_1p0");
  hWbosonWeight_muFUp =     (TH1D*)fWeightsW->Get("evj_NNLO_NLO_nnn_nnn_n_Weight_scale_variation_muR_1p0_muF_2p0");
  hWbosonWeight_muFDown =   (TH1D*)fWeightsW->Get("evj_NNLO_NLO_nnn_nnn_n_Weight_scale_variation_muR_1p0_muF_0p5");

  fWeightsZvv = new TFile("../data/TheoryXS_vvj.root");
  hZvvbosonWeight_nominal =   (TH1D*)fWeightsZll->Get("vvj_NNLO_NLO_nnn_nnn_n");
  hZvvbosonWeight_QCD1Up =    (TH1D*)fWeightsZll->Get("vvj_NNLO_NLO_unn_nnn_n");
  hZvvbosonWeight_QCD1Down =  (TH1D*)fWeightsZll->Get("vvj_NNLO_NLO_dnn_nnn_n");
  hZvvbosonWeight_QCD2Up =    (TH1D*)fWeightsZll->Get("vvj_NNLO_NLO_nun_nnn_n");
  hZvvbosonWeight_QCD2Down =  (TH1D*)fWeightsZll->Get("vvj_NNLO_NLO_ndn_nnn_n");
  hZvvbosonWeight_QCD3Up =    (TH1D*)fWeightsZll->Get("vvj_NNLO_NLO_nnu_nnn_n");
  hZvvbosonWeight_QCD3Down =  (TH1D*)fWeightsZll->Get("vvj_NNLO_NLO_nnd_nnn_n");
  hZvvbosonWeight_EW1Up =     (TH1D*)fWeightsZll->Get("vvj_NNLO_NLO_nnn_unn_n");
  hZvvbosonWeight_EW1Down =   (TH1D*)fWeightsZll->Get("vvj_NNLO_NLO_nnn_dnn_n");
  hZvvbosonWeight_EW2Up =     (TH1D*)fWeightsZll->Get("vvj_NNLO_NLO_nnn_nun_n");
  hZvvbosonWeight_EW2Down =   (TH1D*)fWeightsZll->Get("vvj_NNLO_NLO_nnn_ndn_n");
  hZvvbosonWeight_EW3Up =     (TH1D*)fWeightsZll->Get("vvj_NNLO_NLO_nnn_nnu_n");
  hZvvbosonWeight_EW3Down =   (TH1D*)fWeightsZll->Get("vvj_NNLO_NLO_nnn_nnd_n");
  hZvvbosonWeight_MixedUp =   (TH1D*)fWeightsZll->Get("vvj_NNLO_NLO_nnn_nnn_u");
  hZvvbosonWeight_MixedDown = (TH1D*)fWeightsZll->Get("vvj_NNLO_NLO_nnn_nnn_d");
  hZvvbosonWeight_AlphaUp =   (TH1D*)fWeightsZll->Get("vvj_NNLO_NLO_nnn_nnn_n_alpha_up");
  hZvvbosonWeight_AlphaDown = (TH1D*)fWeightsZll->Get("vvj_NNLO_NLO_nnn_nnn_n_alpha_down");
  hZvvbosonWeight_muRUp =     (TH1D*)fWeightsZll->Get("vvj_NNLO_NLO_nnn_nnn_n_Weight_scale_variation_muR_2p0_muF_1p0");
  hZvvbosonWeight_muRDown =   (TH1D*)fWeightsZll->Get("vvj_NNLO_NLO_nnn_nnn_n_Weight_scale_variation_muR_0p5_muF_1p0");
  hZvvbosonWeight_muFUp =     (TH1D*)fWeightsZll->Get("vvj_NNLO_NLO_nnn_nnn_n_Weight_scale_variation_muR_1p0_muF_2p0");
  hZvvbosonWeight_muFDown =   (TH1D*)fWeightsZll->Get("vvj_NNLO_NLO_nnn_nnn_n_Weight_scale_variation_muR_1p0_muF_0p5");

  fWeightsZll = new TFile("../data/TheoryXS_eej.root");
  hZllbosonWeight_nominal =   (TH1D*)fWeightsZll->Get("eej_NNLO_NLO_nnn_nnn_n");
  hZllbosonWeight_QCD1Up =    (TH1D*)fWeightsZll->Get("eej_NNLO_NLO_unn_nnn_n");
  hZllbosonWeight_QCD1Down =  (TH1D*)fWeightsZll->Get("eej_NNLO_NLO_dnn_nnn_n");
  hZllbosonWeight_QCD2Up =    (TH1D*)fWeightsZll->Get("eej_NNLO_NLO_nun_nnn_n");
  hZllbosonWeight_QCD2Down =  (TH1D*)fWeightsZll->Get("eej_NNLO_NLO_ndn_nnn_n");
  hZllbosonWeight_QCD3Up =    (TH1D*)fWeightsZll->Get("eej_NNLO_NLO_nnu_nnn_n");
  hZllbosonWeight_QCD3Down =  (TH1D*)fWeightsZll->Get("eej_NNLO_NLO_nnd_nnn_n");
  hZllbosonWeight_EW1Up =     (TH1D*)fWeightsZll->Get("eej_NNLO_NLO_nnn_unn_n");
  hZllbosonWeight_EW1Down =   (TH1D*)fWeightsZll->Get("eej_NNLO_NLO_nnn_dnn_n");
  hZllbosonWeight_EW2Up =     (TH1D*)fWeightsZll->Get("eej_NNLO_NLO_nnn_nun_n");
  hZllbosonWeight_EW2Down =   (TH1D*)fWeightsZll->Get("eej_NNLO_NLO_nnn_ndn_n");
  hZllbosonWeight_EW3Up =     (TH1D*)fWeightsZll->Get("eej_NNLO_NLO_nnn_nnu_n");
  hZllbosonWeight_EW3Down =   (TH1D*)fWeightsZll->Get("eej_NNLO_NLO_nnn_nnd_n");
  hZllbosonWeight_MixedUp =   (TH1D*)fWeightsZll->Get("eej_NNLO_NLO_nnn_nnn_u");
  hZllbosonWeight_MixedDown = (TH1D*)fWeightsZll->Get("eej_NNLO_NLO_nnn_nnn_d");
  hZllbosonWeight_AlphaUp =   (TH1D*)fWeightsZll->Get("eej_NNLO_NLO_nnn_nnn_n_alpha_up");
  hZllbosonWeight_AlphaDown = (TH1D*)fWeightsZll->Get("eej_NNLO_NLO_nnn_nnn_n_alpha_down");
  hZllbosonWeight_muRUp =     (TH1D*)fWeightsZll->Get("eej_NNLO_NLO_nnn_nnn_n_Weight_scale_variation_muR_2p0_muF_1p0");
  hZllbosonWeight_muRDown =   (TH1D*)fWeightsZll->Get("eej_NNLO_NLO_nnn_nnn_n_Weight_scale_variation_muR_0p5_muF_1p0");
  hZllbosonWeight_muFUp =     (TH1D*)fWeightsZll->Get("eej_NNLO_NLO_nnn_nnn_n_Weight_scale_variation_muR_1p0_muF_2p0");
  hZllbosonWeight_muFDown =   (TH1D*)fWeightsZll->Get("eej_NNLO_NLO_nnn_nnn_n_Weight_scale_variation_muR_1p0_muF_0p5");

  initialized = true;
}

void BosonWeightProcessor::Process(const InputCollections& input, VariableContainer& vars) {
  if (!initialized) cerr << "tree processor not initialized" << endl;

  if (input.genDarkMatterEvt.WBosonIsFilled()) {
    const GenDarkMatterEvent& DM_Evt = input.genDarkMatterEvt;
    double W_Pt = DM_Evt.ReturnWBoson().Pt();
    if (W_Pt > 30) {
      BosonWeight_nominal   = hWbosonWeight_nominal->GetBinContent(hWbosonWeight_nominal->FindBin(W_Pt));
      BosonWeight_QCD1Up    = hWbosonWeight_QCD1Up->GetBinContent(hWbosonWeight_QCD1Up->FindBin(W_Pt));
      BosonWeight_QCD1Down  = hWbosonWeight_QCD1Down->GetBinContent(hWbosonWeight_QCD1Down->FindBin(W_Pt));
      BosonWeight_QCD2Up    = hWbosonWeight_QCD2Up->GetBinContent(hWbosonWeight_QCD2Up->FindBin(W_Pt));
      BosonWeight_QCD2Down  = hWbosonWeight_QCD2Down->GetBinContent(hWbosonWeight_QCD2Down->FindBin(W_Pt));
      BosonWeight_QCD3Up    = hWbosonWeight_QCD3Up->GetBinContent(hWbosonWeight_QCD3Up->FindBin(W_Pt));
      BosonWeight_QCD3Down  = hWbosonWeight_QCD3Down->GetBinContent(hWbosonWeight_QCD3Down->FindBin(W_Pt));
      BosonWeight_EW1Up     = hWbosonWeight_EW1Up->GetBinContent(hWbosonWeight_EW1Up->FindBin(W_Pt));
      BosonWeight_EW1Down   = hWbosonWeight_EW1Down->GetBinContent(hWbosonWeight_EW1Down->FindBin(W_Pt));
      BosonWeight_EW2Up     = hWbosonWeight_EW2Up->GetBinContent(hWbosonWeight_EW2Up->FindBin(W_Pt));
      BosonWeight_EW2Down   = hWbosonWeight_EW2Down->GetBinContent(hWbosonWeight_EW2Down->FindBin(W_Pt));
      BosonWeight_EW3Up     = hWbosonWeight_EW3Up->GetBinContent(hWbosonWeight_EW3Up->FindBin(W_Pt));
      BosonWeight_EW3Down   = hWbosonWeight_EW3Down->GetBinContent(hWbosonWeight_EW3Down->FindBin(W_Pt));
      BosonWeight_MixedUp   = hWbosonWeight_MixedUp->GetBinContent(hWbosonWeight_MixedUp->FindBin(W_Pt));
      BosonWeight_MixedDown = hWbosonWeight_MixedDown->GetBinContent(hWbosonWeight_MixedDown->FindBin(W_Pt));
      BosonWeight_AlphaUp   = hWbosonWeight_AlphaUp->GetBinContent(hWbosonWeight_AlphaUp->FindBin(W_Pt));
      BosonWeight_AlphaDown = hWbosonWeight_AlphaDown->GetBinContent(hWbosonWeight_AlphaDown->FindBin(W_Pt));
      BosonWeight_muRUp     = hWbosonWeight_muRUp->GetBinContent(hWbosonWeight_muRUp->FindBin(W_Pt));
      BosonWeight_muRDown   = hWbosonWeight_muRDown->GetBinContent(hWbosonWeight_muRDown->FindBin(W_Pt));
      BosonWeight_muFUp     = hWbosonWeight_muFUp->GetBinContent(hWbosonWeight_muFUp->FindBin(W_Pt));
      BosonWeight_muFDown   = hWbosonWeight_muFDown->GetBinContent(hWbosonWeight_muFDown->FindBin(W_Pt));
    }
    else {
      BosonWeight_nominal = 1;
      BosonWeight_QCD1Up = 1;
      BosonWeight_QCD1Down = 1;
      BosonWeight_QCD2Up = 1;
      BosonWeight_QCD2Down = 1;
      BosonWeight_QCD3Up = 1;
      BosonWeight_QCD3Down = 1;
      BosonWeight_EW1Up = 1;
      BosonWeight_EW1Down = 1;
      BosonWeight_EW2Up = 1;
      BosonWeight_EW2Down = 1;
      BosonWeight_EW3Up = 1;
      BosonWeight_EW3Down = 1;
      BosonWeight_MixedUp = 1;
      BosonWeight_MixedDown = 1;
      BosonWeight_AlphaUp = 1;
      BosonWeight_AlphaDown = 1;
      BosonWeight_muRUp = 1;
      BosonWeight_muRDown = 1;
      BosonWeight_muFUp = 1;
      BosonWeight_muFDown = 1;
    }
  }

  if (input.genDarkMatterEvt.ZBosonIsFilled()) {
    const GenDarkMatterEvent& DM_Evt = input.genDarkMatterEvt;
    double Z_Pt = DM_Evt.ReturnZBoson().Pt();
    if (Z_Pt > 30) {
      if (DM_Evt.IsZnunu()){
        BosonWeight_nominal   = hZvvbosonWeight_nominal->GetBinContent(hZvvbosonWeight_nominal->FindBin(Z_Pt));
        BosonWeight_QCD1Up    = hZvvbosonWeight_QCD1Up->GetBinContent(hZvvbosonWeight_QCD1Up->FindBin(Z_Pt));
        BosonWeight_QCD1Down  = hZvvbosonWeight_QCD1Down->GetBinContent(hZvvbosonWeight_QCD1Down->FindBin(Z_Pt));
        BosonWeight_QCD2Up    = hZvvbosonWeight_QCD2Up->GetBinContent(hZvvbosonWeight_QCD2Up->FindBin(Z_Pt));
        BosonWeight_QCD2Down  = hZvvbosonWeight_QCD2Down->GetBinContent(hZvvbosonWeight_QCD2Down->FindBin(Z_Pt));
        BosonWeight_QCD3Up    = hZvvbosonWeight_QCD3Up->GetBinContent(hZvvbosonWeight_QCD3Up->FindBin(Z_Pt));
        BosonWeight_QCD3Down  = hZvvbosonWeight_QCD3Down->GetBinContent(hZvvbosonWeight_QCD3Down->FindBin(Z_Pt));
        BosonWeight_EW1Up     = hZvvbosonWeight_EW1Up->GetBinContent(hZvvbosonWeight_EW1Up->FindBin(Z_Pt));
        BosonWeight_EW1Down   = hZvvbosonWeight_EW1Down->GetBinContent(hZvvbosonWeight_EW1Down->FindBin(Z_Pt));
        BosonWeight_EW2Up     = hZvvbosonWeight_EW2Up->GetBinContent(hZvvbosonWeight_EW2Up->FindBin(Z_Pt));
        BosonWeight_EW2Down   = hZvvbosonWeight_EW2Down->GetBinContent(hZvvbosonWeight_EW2Down->FindBin(Z_Pt));
        BosonWeight_EW3Up     = hZvvbosonWeight_EW3Up->GetBinContent(hZvvbosonWeight_EW3Up->FindBin(Z_Pt));
        BosonWeight_EW3Down   = hZvvbosonWeight_EW3Down->GetBinContent(hZvvbosonWeight_EW3Down->FindBin(Z_Pt));
        BosonWeight_MixedUp   = hZvvbosonWeight_MixedUp->GetBinContent(hZvvbosonWeight_MixedUp->FindBin(Z_Pt));
        BosonWeight_MixedDown = hZvvbosonWeight_MixedDown->GetBinContent(hZvvbosonWeight_MixedDown->FindBin(Z_Pt));
        BosonWeight_AlphaUp   = hZvvbosonWeight_AlphaUp->GetBinContent(hZvvbosonWeight_AlphaUp->FindBin(Z_Pt));
        BosonWeight_AlphaDown = hZvvbosonWeight_AlphaDown->GetBinContent(hZvvbosonWeight_AlphaDown->FindBin(Z_Pt));
        BosonWeight_muRUp     = hZvvbosonWeight_muRUp->GetBinContent(hZvvbosonWeight_muRUp->FindBin(Z_Pt));
        BosonWeight_muRDown   = hZvvbosonWeight_muRDown->GetBinContent(hZvvbosonWeight_muRDown->FindBin(Z_Pt));
        BosonWeight_muFUp     = hZvvbosonWeight_muFUp->GetBinContent(hZvvbosonWeight_muFUp->FindBin(Z_Pt));
        BosonWeight_muFDown   = hZvvbosonWeight_muFDown->GetBinContent(hZvvbosonWeight_muFDown->FindBin(Z_Pt));
      }
      else{
        BosonWeight_nominal   = hZllbosonWeight_nominal->GetBinContent(hZllbosonWeight_nominal->FindBin(Z_Pt));
        BosonWeight_QCD1Up    = hZllbosonWeight_QCD1Up->GetBinContent(hZllbosonWeight_QCD1Up->FindBin(Z_Pt));
        BosonWeight_QCD1Down  = hZllbosonWeight_QCD1Down->GetBinContent(hZllbosonWeight_QCD1Down->FindBin(Z_Pt));
        BosonWeight_QCD2Up    = hZllbosonWeight_QCD2Up->GetBinContent(hZllbosonWeight_QCD2Up->FindBin(Z_Pt));
        BosonWeight_QCD2Down  = hZllbosonWeight_QCD2Down->GetBinContent(hZllbosonWeight_QCD2Down->FindBin(Z_Pt));
        BosonWeight_QCD3Up    = hZllbosonWeight_QCD3Up->GetBinContent(hZllbosonWeight_QCD3Up->FindBin(Z_Pt));
        BosonWeight_QCD3Down  = hZllbosonWeight_QCD3Down->GetBinContent(hZllbosonWeight_QCD3Down->FindBin(Z_Pt));
        BosonWeight_EW1Up     = hZllbosonWeight_EW1Up->GetBinContent(hZllbosonWeight_EW1Up->FindBin(Z_Pt));
        BosonWeight_EW1Down   = hZllbosonWeight_EW1Down->GetBinContent(hZllbosonWeight_EW1Down->FindBin(Z_Pt));
        BosonWeight_EW2Up     = hZllbosonWeight_EW2Up->GetBinContent(hZllbosonWeight_EW2Up->FindBin(Z_Pt));
        BosonWeight_EW2Down   = hZllbosonWeight_EW2Down->GetBinContent(hZllbosonWeight_EW2Down->FindBin(Z_Pt));
        BosonWeight_EW3Up     = hZllbosonWeight_EW3Up->GetBinContent(hZllbosonWeight_EW3Up->FindBin(Z_Pt));
        BosonWeight_EW3Down   = hZllbosonWeight_EW3Down->GetBinContent(hZllbosonWeight_EW3Down->FindBin(Z_Pt));
        BosonWeight_MixedUp   = hZllbosonWeight_MixedUp->GetBinContent(hZllbosonWeight_MixedUp->FindBin(Z_Pt));
        BosonWeight_MixedDown = hZllbosonWeight_MixedDown->GetBinContent(hZllbosonWeight_MixedDown->FindBin(Z_Pt));
        BosonWeight_AlphaUp   = hZllbosonWeight_AlphaUp->GetBinContent(hZllbosonWeight_AlphaUp->FindBin(Z_Pt));
        BosonWeight_AlphaDown = hZllbosonWeight_AlphaDown->GetBinContent(hZllbosonWeight_AlphaDown->FindBin(Z_Pt));
        BosonWeight_muRUp     = hZllbosonWeight_muRUp->GetBinContent(hZllbosonWeight_muRUp->FindBin(Z_Pt));
        BosonWeight_muRDown   = hZllbosonWeight_muRDown->GetBinContent(hZllbosonWeight_muRDown->FindBin(Z_Pt));
        BosonWeight_muFUp     = hZllbosonWeight_muFUp->GetBinContent(hZllbosonWeight_muFUp->FindBin(Z_Pt));
        BosonWeight_muFDown   = hZllbosonWeight_muFDown->GetBinContent(hZllbosonWeight_muFDown->FindBin(Z_Pt));        
      }
    }
    else {
      BosonWeight_nominal = 1;
      BosonWeight_QCD1Up = 1;
      BosonWeight_QCD1Down = 1;
      BosonWeight_QCD2Up = 1;
      BosonWeight_QCD2Down = 1;
      BosonWeight_QCD3Up = 1;
      BosonWeight_QCD3Down = 1;
      BosonWeight_EW1Up = 1;
      BosonWeight_EW1Down = 1;
      BosonWeight_EW2Up = 1;
      BosonWeight_EW2Down = 1;
      BosonWeight_EW3Up = 1;
      BosonWeight_EW3Down = 1;
      BosonWeight_MixedUp = 1;
      BosonWeight_MixedDown = 1;
      BosonWeight_AlphaUp = 1;
      BosonWeight_AlphaDown = 1;
      BosonWeight_muRUp = 1;
      BosonWeight_muRDown = 1;
      BosonWeight_muFUp = 1;
      BosonWeight_muFDown = 1;
    }
  }
  vars.FillVar( "BosonWeight_nominal", BosonWeight_nominal );

  vars.FillVar( "BosonWeight_QCD1Up", BosonWeight_QCD1Up );
  vars.FillVar( "BosonWeight_QCD1Down", BosonWeight_QCD1Down );
  vars.FillVar( "BosonWeight_QCD2Up", BosonWeight_QCD2Up );
  vars.FillVar( "BosonWeight_QCD2Down", BosonWeight_QCD2Down );
  vars.FillVar( "BosonWeight_QCD3Up", BosonWeight_QCD3Up );
  vars.FillVar( "BosonWeight_QCD3Down", BosonWeight_QCD3Down );

  vars.FillVar( "BosonWeight_EW1Up", BosonWeight_EW1Up );
  vars.FillVar( "BosonWeight_EW1Down", BosonWeight_EW1Down );
  vars.FillVar( "BosonWeight_EW2Up", BosonWeight_EW2Up );
  vars.FillVar( "BosonWeight_EW2Down", BosonWeight_EW2Down );
  vars.FillVar( "BosonWeight_EW3Up", BosonWeight_EW3Up );
  vars.FillVar( "BosonWeight_EW3Down", BosonWeight_EW3Down );

  vars.FillVar( "BosonWeight_MixedUp", BosonWeight_MixedUp );
  vars.FillVar( "BosonWeight_MixedDown", BosonWeight_MixedDown );
  vars.FillVar( "BosonWeight_AlphaUp", BosonWeight_AlphaUp );
  vars.FillVar( "BosonWeight_AlphaDown", BosonWeight_AlphaDown );

  vars.FillVar( "BosonWeight_muRUp", BosonWeight_muRUp );
  vars.FillVar( "BosonWeight_muRDown", BosonWeight_muRDown );
  vars.FillVar( "BosonWeight_muFUp", BosonWeight_muFUp );
  vars.FillVar( "BosonWeight_muFDown", BosonWeight_muFDown );

}
