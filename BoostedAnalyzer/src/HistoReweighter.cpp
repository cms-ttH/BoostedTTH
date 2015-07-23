#include "BoostedTTH/BoostedAnalyzer/interface/HistoReweighter.hpp"


using namespace std;
HistoReweighter::HistoReweighter(TH1* nom_histo, TH1* denom_histo, bool normalize){
  CreateWeightHisto(nom_histo, denom_histo, normalize);
}
HistoReweighter::HistoReweighter(TFile* file, char* nom_histo_name, char* denom_histo_name, bool normalize){
  TH1* nom_histo=(TH1*)file->Get(nom_histo_name);
  TH1* denom_histo=(TH1*)file->Get(denom_histo_name);
  CreateWeightHisto(nom_histo, denom_histo, normalize);
  
}
HistoReweighter::HistoReweighter(TFile* nom_file, char* nom_histo_name, TFile* denom_file, char* denom_histo_name, bool normalize){
  TH1* nom_histo=(TH1*)nom_file->Get(nom_histo_name);
  TH1* denom_histo=(TH1*)denom_file->Get(denom_histo_name);
  CreateWeightHisto(nom_histo, denom_histo, normalize);
  
}

void HistoReweighter::CreateWeightHisto(TH1* nom_histo, TH1* denom_histo, bool normalize){
  nomHisto=(TH1*)nom_histo->Clone();
  denomHisto=(TH1*)denom_histo->Clone();
  assert(denomHisto->GetNbinsX()==nomHisto->GetNbinsX());
  nbins=denomHisto->GetNbinsX();
  for(int i=1; i<=denomHisto->GetNbinsX(); i++){
    if(denomHisto->GetBinContent(i)==0&&nomHisto->GetBinContent(i)==0){
      cerr << "bin in denominator histo empty but not in nominator, erasing bin" << endl;
      nomHisto->SetBinContent(i,0);
    }
  }
  if(normalize){
    nomHisto->Scale(1./nomHisto->Integral(0,nbins+1));
    denomHisto->Scale(1./denomHisto->Integral(0,nbins+1));
  }

  nomHisto=nomHisto;
  denomHisto=nomHisto;
  max=nomHisto->GetXaxis()->GetXmax();
  min=nomHisto->GetXaxis()->GetXmin();
  

}

float HistoReweighter::GetWeight(float value, bool interpolate){  
  float n;
  float d;
  if(value>max) {
    n=nomHisto->GetBinContent(nbins+1);
    d=denomHisto->GetBinContent(nbins+1);  
  }
  else if(value<min) {
    n=nomHisto->GetBinContent(0);
    d=denomHisto->GetBinContent(0);
  }
  else if(interpolate){
    n=nomHisto->Interpolate(value);
    d=denomHisto->Interpolate(value);
  }
  else{
    n=nomHisto->GetBinContent(nomHisto->FindBin(value));
    d=denomHisto->GetBinContent(denomHisto->FindBin(value));
  }
  
  if(d>0) {
    return n/d;
  }
  else{
    return 0;
  }
}

