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

  fWeightsZ = new TFile("../data/TheoryXS_vvj.root");
  hZbosonWeight_nominal =   (TH1D*)fWeightsZ->Get("vvj_NNLO_NLO_nnn_nnn_n");
  hZbosonWeight_QCD1Up =    (TH1D*)fWeightsZ->Get("vvj_NNLO_NLO_unn_nnn_n");
  hZbosonWeight_QCD1Down =  (TH1D*)fWeightsZ->Get("vvj_NNLO_NLO_dnn_nnn_n");
  hZbosonWeight_QCD2Up =    (TH1D*)fWeightsZ->Get("vvj_NNLO_NLO_nun_nnn_n");
  hZbosonWeight_QCD2Down =  (TH1D*)fWeightsZ->Get("vvj_NNLO_NLO_ndn_nnn_n");
  hZbosonWeight_QCD3Up =    (TH1D*)fWeightsZ->Get("vvj_NNLO_NLO_nnu_nnn_n");
  hZbosonWeight_QCD3Down =  (TH1D*)fWeightsZ->Get("vvj_NNLO_NLO_nnd_nnn_n");
  hZbosonWeight_EW1Up =     (TH1D*)fWeightsZ->Get("vvj_NNLO_NLO_nnn_unn_n");
  hZbosonWeight_EW1Down =   (TH1D*)fWeightsZ->Get("vvj_NNLO_NLO_nnn_dnn_n");
  hZbosonWeight_EW2Up =     (TH1D*)fWeightsZ->Get("vvj_NNLO_NLO_nnn_nun_n");
  hZbosonWeight_EW2Down =   (TH1D*)fWeightsZ->Get("vvj_NNLO_NLO_nnn_ndn_n");
  hZbosonWeight_EW3Up =     (TH1D*)fWeightsZ->Get("vvj_NNLO_NLO_nnn_nnu_n");
  hZbosonWeight_EW3Down =   (TH1D*)fWeightsZ->Get("vvj_NNLO_NLO_nnn_nnd_n");
  hZbosonWeight_MixedUp =   (TH1D*)fWeightsZ->Get("vvj_NNLO_NLO_nnn_nnn_u");
  hZbosonWeight_MixedDown = (TH1D*)fWeightsZ->Get("vvj_NNLO_NLO_nnn_nnn_d");
  hZbosonWeight_AlphaUp =   (TH1D*)fWeightsZ->Get("vvj_NNLO_NLO_nnn_nnn_n_alpha_up");
  hZbosonWeight_AlphaDown = (TH1D*)fWeightsZ->Get("vvj_NNLO_NLO_nnn_nnn_n_alpha_down");
  hZbosonWeight_muRUp =     (TH1D*)fWeightsZ->Get("vvj_NNLO_NLO_nnn_nnn_n_Weight_scale_variation_muR_2p0_muF_1p0");
  hZbosonWeight_muRDown =   (TH1D*)fWeightsZ->Get("vvj_NNLO_NLO_nnn_nnn_n_Weight_scale_variation_muR_0p5_muF_1p0");
  hZbosonWeight_muFUp =     (TH1D*)fWeightsZ->Get("vvj_NNLO_NLO_nnn_nnn_n_Weight_scale_variation_muR_1p0_muF_2p0");
  hZbosonWeight_muFDown =   (TH1D*)fWeightsZ->Get("vvj_NNLO_NLO_nnn_nnn_n_Weight_scale_variation_muR_1p0_muF_0p5");


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
      BosonWeight_nominal   = hZbosonWeight_nominal->GetBinContent(hZbosonWeight_nominal->FindBin(Z_Pt));
      BosonWeight_QCD1Up    = hZbosonWeight_QCD1Up->GetBinContent(hZbosonWeight_QCD1Up->FindBin(Z_Pt));
      BosonWeight_QCD1Down  = hZbosonWeight_QCD1Down->GetBinContent(hZbosonWeight_QCD1Down->FindBin(Z_Pt));
      BosonWeight_QCD2Up    = hZbosonWeight_QCD2Up->GetBinContent(hZbosonWeight_QCD2Up->FindBin(Z_Pt));
      BosonWeight_QCD2Down  = hZbosonWeight_QCD2Down->GetBinContent(hZbosonWeight_QCD2Down->FindBin(Z_Pt));
      BosonWeight_QCD3Up    = hZbosonWeight_QCD3Up->GetBinContent(hZbosonWeight_QCD3Up->FindBin(Z_Pt));
      BosonWeight_QCD3Down  = hZbosonWeight_QCD3Down->GetBinContent(hZbosonWeight_QCD3Down->FindBin(Z_Pt));
      BosonWeight_EW1Up     = hZbosonWeight_EW1Up->GetBinContent(hZbosonWeight_EW1Up->FindBin(Z_Pt));
      BosonWeight_EW1Down   = hZbosonWeight_EW1Down->GetBinContent(hZbosonWeight_EW1Down->FindBin(Z_Pt));
      BosonWeight_EW2Up     = hZbosonWeight_EW2Up->GetBinContent(hZbosonWeight_EW2Up->FindBin(Z_Pt));
      BosonWeight_EW2Down   = hZbosonWeight_EW2Down->GetBinContent(hZbosonWeight_EW2Down->FindBin(Z_Pt));
      BosonWeight_EW3Up     = hZbosonWeight_EW3Up->GetBinContent(hZbosonWeight_EW3Up->FindBin(Z_Pt));
      BosonWeight_EW3Down   = hZbosonWeight_EW3Down->GetBinContent(hZbosonWeight_EW3Down->FindBin(Z_Pt));
      BosonWeight_MixedUp   = hZbosonWeight_MixedUp->GetBinContent(hZbosonWeight_MixedUp->FindBin(Z_Pt));
      BosonWeight_MixedDown = hZbosonWeight_MixedDown->GetBinContent(hZbosonWeight_MixedDown->FindBin(Z_Pt));
      BosonWeight_AlphaUp   = hZbosonWeight_AlphaUp->GetBinContent(hZbosonWeight_AlphaUp->FindBin(Z_Pt));
      BosonWeight_AlphaDown = hZbosonWeight_AlphaDown->GetBinContent(hZbosonWeight_AlphaDown->FindBin(Z_Pt));
      BosonWeight_muRUp     = hZbosonWeight_muRUp->GetBinContent(hZbosonWeight_muRUp->FindBin(Z_Pt));
      BosonWeight_muRDown   = hZbosonWeight_muRDown->GetBinContent(hZbosonWeight_muRDown->FindBin(Z_Pt));
      BosonWeight_muFUp     = hZbosonWeight_muFUp->GetBinContent(hZbosonWeight_muFUp->FindBin(Z_Pt));
      BosonWeight_muFDown   = hZbosonWeight_muFDown->GetBinContent(hZbosonWeight_muFDown->FindBin(Z_Pt));
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
