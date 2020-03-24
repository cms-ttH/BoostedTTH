#include "BoostedTTH/BoostedAnalyzer/interface/SingleElTriggerSFs.hpp"

// constructors
SingleElTriggerSFs::SingleElTriggerSFs() : TriggerScaleFactors() {}
SingleElTriggerSFs::SingleElTriggerSFs(std::string name) : TriggerScaleFactors(name) {}

// destructor
SingleElTriggerSFs::~SingleElTriggerSFs()
{
    if (root_file != nullptr) root_file->Close();
}

// Init function
void SingleElTriggerSFs::Init(const InputCollections& input)
{
    if (input.era.find("2016") != std::string::npos) {
        file = TString(std::string(getenv("CMSSW_BASE"))) + "/src/MiniAOD/MiniAODHelper/data/Run2Legacy/SingleEG_JetHT_Trigger_Scale_Factors_ttHbb2016_v4.root";
        hist_name = "ele27_ele_pt_ele_sceta";
    }
    else if (input.era.find("2017") != std::string::npos) {
        file      = TString(std::string(getenv("CMSSW_BASE"))) + "/src/MiniAOD/MiniAODHelper/data/Run2Legacy/electron_trigger_sf_2017.root";
        hist_name = "EGamma_SF2D";
    }
    else if (input.era.find("2018") != std::string::npos) {
        file      = TString(std::string(getenv("CMSSW_BASE"))) + "/src/MiniAOD/MiniAODHelper/data/Run2Legacy/electron_trigger_sf_2018.root";
        hist_name = "EGamma_SF2D";
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

    // std::cout << "xmin: " << xmin << " xmax: " << xmax << std::endl;
    // std::cout << "ymin: " << ymin << " ymax: " << ymax << std::endl;

    initialized = true;
}

// function to calculate trigger scale factors
std::vector< float > SingleElTriggerSFs::CalculateTriggerSFs(const InputCollections& input)
{
    std::vector< float > sfs{-999., -999., -999.};
    if (input.selectedElectronsLoose.size() == 0) return sfs;

    pt  = -999.;
    eta = -999.;

    if (input.era.find("2017") != std::string::npos || input.era.find("2018") != std::string::npos) {
        // make sure to stay within the range ot the histograms
        pt  = std::max(ymin + 0.1, input.selectedElectronsLoose.at(0).pt());
        pt  = std::min(float(ymax - 0.1), float(pt));
        eta = std::max(xmin + 0.1, input.selectedElectronsLoose.at(0).superCluster().isAvailable()
                                       ? input.selectedElectronsLoose.at(0).superCluster()->position().eta()
                                       : input.selectedElectronsLoose.at(0).eta());
        eta = std::min(float(xmax - 0.1), float(eta));
        // std::cout << "Pt: " << pt << std::endl;
        // std::cout << "Eta: " << eta << std::endl;
        // calculate SFs here
        sfs.at(0) = hist->GetBinContent(hist->FindBin(eta, pt));
        sfs.at(1) = (hist->GetBinContent(hist->FindBin(eta, pt))) + (hist->GetBinError(hist->FindBin(eta, pt)));
        sfs.at(2) = (hist->GetBinContent(hist->FindBin(eta, pt))) - (hist->GetBinError(hist->FindBin(eta, pt)));
    }
    else if (input.era.find("2016") != std::string::npos) {
        // make sure to stay within the range ot the histograms
        pt  = std::max(xmin + 0.1, input.selectedElectronsLoose.at(0).pt());
        pt  = std::min(float(xmax - 0.1), float(pt));
        eta = std::max(ymin + 0.1, input.selectedElectronsLoose.at(0).superCluster().isAvailable()
                                       ? input.selectedElectronsLoose.at(0).superCluster()->position().eta()
                                       : input.selectedElectronsLoose.at(0).eta());
        eta = std::min(float(ymax - 0.1), float(eta));
        // std::cout << "Pt: " << pt << std::endl;
        // std::cout << "Eta: " << eta << std::endl;
        // calculate SFs here
        sfs.at(0) = hist->GetBinContent(hist->FindBin(pt, eta));
        sfs.at(1) = (hist->GetBinContent(hist->FindBin(pt, eta))) + (hist->GetBinError(hist->FindBin(pt, eta)));
        sfs.at(2) = (hist->GetBinContent(hist->FindBin(pt, eta))) - (hist->GetBinError(hist->FindBin(pt, eta)));
    }
    return sfs;
}
