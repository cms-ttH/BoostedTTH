#include "BoostedTTH/BoostedAnalyzer/interface/HistoReweighter.hpp"


using namespace std;
HistoReweighter::HistoReweighter(TH1* nom_histo, TH1* denom_histo, bool normalize){
  CreateWeightHisto(nom_histo, denom_histo, normalize);
}
HistoReweighter::HistoReweighter(TFile* file, char* nom_histo_name, char* denom_histo_name, bool normalize){
  TH1* nom_histo=file->Get(nom_histo_name);
  TH1* denom_histo=file->Get(denom_histo_name);
  CreateWeightHisto(nom_histo, denom_histo, normalize);
  
}
HistoReweighter::HistoReweighter(TFile* nom_file, char* nom_histo_name, TFile* denom_file, char* denom_histo_name, bool normalize){
  TH1* nom_histo=nom_file->Get(nom_histo_name);
  TH1* denom_histo=denom_file->Get(denom_histo_name);
  CreateWeightHisto(nom_histo, denom_histo, normalize);
  
}

HistoReweighter::GetWeightHisto(TH1* nom_histo, TH1* denom_histo, bool normalize){
  TH1* nom_clone=nom_histo->Clone();
  TH1* denom_clone=denom_histo->Clone();
  assert(denom_clone->GetNbinsX()==nom_clone->GetNbinsX());
  nbins=denom_clone->GetNbinsX();
  for(int i=1; i<=denom_clone->GetNbinsX(); i++){
    if(denom_clone->GetBinContent(i)==0&&nom_clone->GetBinContent(i)==0){
      cerr << "bin in denominator histo empty but not in nominator, erasing bin" << endl;
      nom_clone->SetBinContent(i,0);
    }
  }
  if(normalize){
    nom_clone->Scale(1./nom_clone->Integral(0,nbins+1));
    denom_clone->Scale(1./denom_clone->Integral(0,nbins+1));
  }

  nomHisto=nom_clone;
  denomHisto=nom_clone;
  max=histo->GetXaxis()->GetXmax();
  min=histo->GetXaxis()->GetXmin();
 

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

