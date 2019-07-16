#ifndef BOOSTEDTTH_BOOSTEDANALYZER_HISTOREWEIGHTER_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_HISTOREWEIGHTER_HPP

#include "TH1.h"
#include "TFile.h"
#include <assert.h>
#include <iostream>
class HistoReweighter {
   public:
    HistoReweighter(TH1* nom_histo, TH1* denom_histo, bool normalize = true);
    HistoReweighter(const char* filename, const char* nom_histo_name, const char* denom_histo_name, bool normalize = true);
    HistoReweighter(const char* filename, const char* nom_histo_name, const char* denom_file, const char* denom_histo_name, bool normalize = true);
    float GetWeight(float value, bool interpolate = false);

   private:
    void  CreateWeightHisto(TH1* nom_histo, TH1* denom_histo, bool normalize = true);
    TH1*  nomHisto;
    TH1*  denomHisto;
    float min;
    float max;
    int   nbins;
};

#endif
