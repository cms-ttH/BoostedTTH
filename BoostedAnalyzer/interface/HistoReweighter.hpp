#ifndef BOOSTEDTTH_BOOSTEDANALYZER_HISTOREWEIGHTER_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_HISTOREWEIGHTER_HPP

#include "TH1.h"
#include "TFile.h"
#include <assert.h>
#include <iostream>
class HistoReweighter{
  
public:
  
  HistoReweighter(TH1* nom_histo, TH1* denom_histo, bool normalize=true);
  HistoReweighter(TFile* file, char* nom_histo_name, char* denom_histo_name, bool normalize=true);
  HistoReweighter(TFile* nom_file, char* nom_histo_name, TFile* denom_file, char* denom_histo_name, bool normalize=true);
  float GetWeight(float value, bool interpolate=false);

private:
  void CreateWeightHisto(TH1* nom_histo, TH1* denom_histo, bool normalize=true);
  TH1* nomHisto;
  TH1* denomHisto;
  float min;
  float max;
  int nbins;
};

#endif
