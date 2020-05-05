#include "BoostedTTH/BoostedAnalyzer/interface/SinglePhTriggerSFs.hpp"

// constructors
SinglePhTriggerSFs::SinglePhTriggerSFs() : TriggerScaleFactors() {}
SinglePhTriggerSFs::SinglePhTriggerSFs(std::string name) : TriggerScaleFactors(name) {}

float SinglePhTriggerSFs::Sigmoid(float x, float a, float b, float c, float d) { return c + ((d - c) / (1 + TMath::Exp(-a * (x - b)))); }

// destructor
SinglePhTriggerSFs::~SinglePhTriggerSFs()
{
    if (root_file != nullptr) root_file->Close();
}

// Init function
void SinglePhTriggerSFs::Init(const InputCollections& input)
{
    if (input.era.find("2016") != std::string::npos) {
        file      = TString(std::string(getenv("CMSSW_BASE"))) + "/src/MiniAOD/MiniAODHelper/data/Run2Legacy/photonTriggerEfficiency_photon_TH1F.root";
        hist_name = "hden_photonpt_clone_passed";

        root_file = new TFile(file, "READ");

        if (root_file == nullptr) {
            initialized = false;
            return;
        }

        hist = (TH1F*) root_file->Get(hist_name);
        if (hist == nullptr) {
            initialized = false;
            return;
        }

        // determine the ranges of the given TH2F
        xmin = hist->GetXaxis()->GetXmin();
        xmax = hist->GetXaxis()->GetXmax();
    }

    // std::cout << "xmin: " << xmin << " xmax: " << xmax << std::endl;
    // std::cout << "ymin: " << ymin << " ymax: " << ymax << std::endl;

    initialized = true;
}

// function to calculate trigger scale factors
std::vector< float > SinglePhTriggerSFs::CalculateTriggerSFs(const InputCollections& input)
{
    std::vector< float > sfs{-999., -999., -999.};
    pt = -999.;
    if (input.selectedPhotons.size() == 0) return sfs;

    pt = input.selectedPhotons.at(0).pt();
    // eta = -999.;

    if (input.era.find("2017") != std::string::npos) {
        sfs.at(0) = Sigmoid(pt, 0.335, 217.91, 0.065, 0.996) / Sigmoid(pt, 0.244, 212.34, 0.050, 1.000);
        sfs.at(1) = sfs.at(0) * 1.01;
        sfs.at(2) = sfs.at(1) * 0.99;
    }
    else if (input.era.find("2018") != std::string::npos) {
        sfs.at(0) = Sigmoid(pt, 1.022, 218.39, 0.086, 0.999) / Sigmoid(pt, 0.301, 212.83, 0.062, 1.000);
        sfs.at(1) = sfs.at(0) * 1.01;
        sfs.at(2) = sfs.at(1) * 0.99;
    }
    else if (input.era.find("2016") != std::string::npos) {
        pt        = std::max(float(xmin + 0.1), float(pt));
        pt        = std::min(float(xmax - 0.1), float(pt));
        sfs.at(0) = hist->GetBinContent(hist->FindBin(pt));
        sfs.at(1) = sfs.at(0) * 1.01;
        sfs.at(2) = sfs.at(1) * 0.99;
    }
    if (std::isnan(sfs.at(0)) or std::isinf(sfs.at(0))) {
        sfs.at(0) = 1.;
        sfs.at(1) = 1.;
        sfs.at(2) = 1.;
    }
    return sfs;
}
