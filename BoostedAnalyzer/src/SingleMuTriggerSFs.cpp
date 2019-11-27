#include "BoostedTTH/BoostedAnalyzer/interface/SingleMuTriggerSFs.hpp"

// constructors
SingleMuTriggerSFs::SingleMuTriggerSFs() : TriggerScaleFactors() {}
SingleMuTriggerSFs::SingleMuTriggerSFs(std::string name) : TriggerScaleFactors(name) {}

// destructor
SingleMuTriggerSFs::~SingleMuTriggerSFs()
{
    if (root_file != nullptr) root_file->Close();
}

// Init function
void SingleMuTriggerSFs::Init(const InputCollections& input)
{
    if (input.era.find("2016") != std::string::npos) {
        file = TString(std::string(getenv("CMSSW_BASE"))) + "/src/MiniAOD/MiniAODHelper/data/Run2Legacy/SingleMuTriggerEfficienciesAndSF_2016_RunBtoH.root";
        hist_name = "IsoMu24_OR_IsoTkMu24_PtEtaBins/pt_abseta_ratio";
    }
    else if (input.era.find("2017") != std::string::npos) {
        file = TString(std::string(getenv("CMSSW_BASE"))) +
               "/src/MiniAOD/MiniAODHelper/data/Run2Legacy/SingleMuTriggerEfficienciesAndSF_RunBtoF_Nov17Nov2017.root";
        hist_name = "IsoMu27_PtEtaBins/pt_abseta_ratio";
    }
    else if (input.era.find("2018") != std::string::npos) {
        file = TString(std::string(getenv("CMSSW_BASE"))) + "/src/MiniAOD/MiniAODHelper/data/Run2Legacy/SingleMuTriggerEfficienciesAndSF_2018_RunAtoD.root";
        hist_name = "IsoMu24_PtEtaBins/pt_abseta_ratio";
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

    hist = (TH2F*) root_file->Get(hist_name);
    if (hist == nullptr) {
        initialized = false;
        return;
    }

    // determine the ranges of the given TH2F
    xmin = hist->GetXaxis()->GetXmin();
    xmax = hist->GetXaxis()->GetXmax();
    ymin = hist->GetYaxis()->GetXmin();
    ymax = hist->GetYaxis()->GetXmax();
    
    //std::cout << "xmin: " << xmin << " xmax: " << xmax << std::endl;
    //std::cout << "ymin: " << ymin << " ymax: " << ymax << std::endl;

    initialized = true;
}

// function to calculate trigger scale factors
std::vector< float > SingleMuTriggerSFs::CalculateTriggerSFs(const InputCollections& input)
{
    std::vector< float > sfs{-999., -999., -999.};
    if (input.selectedMuonsLoose.size() == 0) return sfs;
    
    pt  = -999.;
    eta = -999.;

    // make sure to stay within the range ot the histograms
    pt  = std::max(xmin + 0.1, input.selectedMuonsLoose.at(0).pt());
    pt  = std::min(float(xmax - 0.1), float(pt));
    eta = std::max(ymin + 0.1, fabs(input.selectedMuonsLoose.at(0).eta()));
    eta = std::min(float(ymax - 0.1), float(eta));
    //std::cout << "Pt: " << pt << std::endl;
    //std::cout << "Eta: " << eta << std::endl;
    // calculate SFs here
    sfs.at(0) = hist->GetBinContent(hist->FindBin(pt, eta));
    sfs.at(1) = (hist->GetBinContent(hist->FindBin(pt, eta))) + (hist->GetBinError(hist->FindBin(pt, eta)));
    sfs.at(2) = (hist->GetBinContent(hist->FindBin(pt, eta))) - (hist->GetBinError(hist->FindBin(pt, eta)));
    
    return sfs;
}
