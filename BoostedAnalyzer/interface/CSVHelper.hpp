#ifndef BOOSTEDTTH_BOOSTEDANALYZER_CSVHelper_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_CSVHelper_HPP

#include <vector>
#include <map>
#include <stdio.h>
#include <boost/format.hpp>

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "MiniAOD/BoostedObjects/interface/SubFilterJet.h"
#include "MiniAOD/BoostedObjects/interface/HTTTopJet.h"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/EventInfo.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TriggerInfo.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

#include "TH1D.h"
#include "TFile.h"

class CSVHelper{
  public:
    CSVHelper();
    ~ CSVHelper();

    double get_csv_wgt( const std::vector<pat::Jet>& Jets, int iSys, double &csvWgtHF, double &csvWgtLF, double &csvWgtCF );

  private:
    void fillCSVhistos(TFile *fileHF, TFile *fileLF);
     
    TH1D* h_csv_wgt_hf[9][6];
    TH1D* c_csv_wgt_hf[9][6];
    TH1D* h_csv_wgt_lf[9][4][3];

    const char* btagger;


};


#endif
