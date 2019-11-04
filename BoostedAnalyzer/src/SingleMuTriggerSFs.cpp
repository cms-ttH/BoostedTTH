#include "BoostedTTH/BoostedAnalyzer/interface/SingleMuTriggerSFs.hpp"

// destructor should also be implemented in derived classes
SingleMuTriggerSFs::~SingleMuTriggerSFs() { root_file->Close(); }

// Init function should be implemented in derived classes and overwrite this base function
void SingleMuTriggerSFs::Init(const InputCollections& input)
{
    if (input.era.find("2016") != std::string::npos) {
        file = TString(std::string(getenv("CMSSW_BASE"))) + "/src/MiniAOD/MiniAODHelper/data/Run2Legacy/SingleMuTriggerEfficienciesAndSF_2016_RunBtoH.root";
    }
    else if (input.era.find("2017") != std::string::npos) {
        file = TString(std::string(getenv("CMSSW_BASE"))) + "/src/MiniAOD/MiniAODHelper/data/Run2Legacy/SingleMuTriggerEfficienciesAndSF_RunBtoF_Nov17Nov2017.root";
    }
    else if (input.era.find("2018") != std::string::npos) {
        file = TString(std::string(getenv("CMSSW_BASE"))) + "/src/MiniAOD/MiniAODHelper/data/Run2Legacy/SingleMuTriggerEfficienciesAndSF_2018_RunAtoD.root";
    }
    else {
        initialized = false;
        return;
    }
    root_file = new TFile(file, "READ");

    if (root_file == nullptr) {
        initialized = false;
        return;
    }

    hist = (TH2F*)root_file->Get("IsoMu24_PtEtaBins/pt_abseta_ratio");
    if (hist == nullptr) {
        initialized = false;
        return;
    }

    // determine the ranges of the given TH2F
    xmin = hist->GetXaxis()->GetXmin();
    xmax = hist->GetXaxis()->GetXmax();
    ymin = hist->GetYaxis()->GetXmin();
    ymax = hist->GetYaxis()->GetXmax();
    
    initialized = true;
}

// base function to calculate trigger scale factors
// if the derived class does not overwrite this function, only three 1s will be returned
std::vector< float > SingleMuTriggerSFs::CalculateTriggerSFs(const InputCollections& input)
{
    std::vector< float > sfs{1.0, 1.0, 1.0};
    if(input.selectedMuonsLoose.size()==0) return sfs;
    
    // calculate SFs here
    pt = -999.;
    eta = -999.;

    // make sure to stay within the range ot the histograms
    pt  = std::max(xmin + 0.1, input.selectedMuonsLoose.at(0).pt());
    pt  = std::min(xmax - 0.1, input.selectedMuonsLoose.at(0).pt());
    eta = std::max(ymin + 0.1, fabs(input.selectedMuonsLoose.at(0).eta()));
    eta = std::min(ymax - 0.1, fabs(input.selectedMuonsLoose.at(0).eta()));

    sfs.at(0) = hist->GetBinContent(hist->FindBin(pt, eta));
    sfs.at(1) = (hist->GetBinContent(hist->FindBin(pt, eta))) + (hist->GetBinError(hist->FindBin(pt, eta)));
    sfs.at(2) = (hist->GetBinContent(hist->FindBin(pt, eta))) - (hist->GetBinError(hist->FindBin(pt, eta)));
    
    return sfs;
    
}
