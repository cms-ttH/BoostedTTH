#include "BoostedTTH/BoostedAnalyzer/interface/HistoReweighter.hpp"

using namespace std;
HistoReweighter::HistoReweighter(TH1* nom_histo,
                                 TH1* denom_histo,
                                 bool normalize)
{
  CreateWeightHisto(nom_histo, denom_histo, normalize);
}
HistoReweighter::HistoReweighter(const char* filename,
                                 const char* nom_histo_name,
                                 const char* denom_histo_name,
                                 bool normalize)
{
  TFile* file = new TFile(filename);
  TH1* nom_histo = (TH1*)file->Get(nom_histo_name);
  TH1* denom_histo = (TH1*)file->Get(denom_histo_name);
  CreateWeightHisto(nom_histo, denom_histo, normalize);
  file->Close();
}
HistoReweighter::HistoReweighter(const char* nom_filename,
                                 const char* nom_histo_name,
                                 const char* denom_filename,
                                 const char* denom_histo_name,
                                 bool normalize)
{
  TFile* nom_file = new TFile(nom_filename);
  TFile* denom_file = new TFile(denom_filename);
  TH1* nom_histo = (TH1*)nom_file->Get(nom_histo_name);
  TH1* denom_histo = (TH1*)denom_file->Get(denom_histo_name);
  CreateWeightHisto(nom_histo, denom_histo, normalize);
  nom_file->Close();
  denom_file->Close();
}

void
HistoReweighter::CreateWeightHisto(TH1* nom_histo,
                                   TH1* denom_histo,
                                   bool normalize)
{
  nomHisto = (TH1*)nom_histo->Clone("nomHisto");
  denomHisto = (TH1*)denom_histo->Clone("denomHisto");
  assert(denomHisto->GetNbinsX() == nomHisto->GetNbinsX());
  nbins = denomHisto->GetNbinsX();
  for (int i = 1; i <= denomHisto->GetNbinsX(); i++) {
    if (denomHisto->GetBinContent(i) == 0 && nomHisto->GetBinContent(i) == 0) {
      cerr << "HistoReweighter: bin in denominator histo empty but not in "
              "nominator, erasing bin"
           << endl;
      nomHisto->SetBinContent(i, 0);
    }
  }
  if (normalize) {
    nomHisto->Scale(1. / nomHisto->Integral(0, nbins + 1));
    denomHisto->Scale(1. / denomHisto->Integral(0, nbins + 1));
  }

  nomHisto = nomHisto;
  denomHisto = denomHisto;
  max = nomHisto->GetXaxis()->GetXmax();
  min = nomHisto->GetXaxis()->GetXmin();
}

float
HistoReweighter::GetWeight(float value, bool interpolate)
{
  float n;
  float d;
  if (value > max) {
    n = nomHisto->GetBinContent(nbins + 1);
    d = denomHisto->GetBinContent(nbins + 1);
  } else if (value < min) {
    n = nomHisto->GetBinContent(0);
    d = denomHisto->GetBinContent(0);
  } else if (interpolate) {
    n = nomHisto->Interpolate(value);
    d = denomHisto->Interpolate(value);
  } else {
    n = nomHisto->GetBinContent(nomHisto->FindBin(value));
    d = denomHisto->GetBinContent(denomHisto->FindBin(value));
  }
  if (d > 0) {
    return n / d;
  } else {
    return 0;
  }
}
