#include "BoostedTTH/BoostedAnalyzer/interface/METTriggerSFs.hpp"

// constructors
METTriggerSFs::METTriggerSFs() : TriggerScaleFactors() {}
METTriggerSFs::METTriggerSFs(std::string name) : TriggerScaleFactors(name) {}

// destructor
METTriggerSFs::~METTriggerSFs()
{
    if (root_file != nullptr) root_file->Close();
}

// Init function
void METTriggerSFs::Init(const InputCollections& input)
{
    if (input.era.find("2016") != std::string::npos) {
        file      = TString(std::string(getenv("CMSSW_BASE"))) + "/src/MiniAOD/MiniAODHelper/data/Run2Legacy/metTriggerEfficiency_recoil_monojet_TH1F.root";
        hist_name = "hden_monojet_recoil_clone_passed";
    }
    else if (input.era.find("2017") != std::string::npos) {
        file      = TString(std::string(getenv("CMSSW_BASE"))) + "/src/MiniAOD/MiniAODHelper/data/Run2Legacy/met_trigger_sf.root";
        hist_name = "120pfht_hltmu_1m_2017";
    }
    else if (input.era.find("2018") != std::string::npos) {
        file      = TString(std::string(getenv("CMSSW_BASE"))) + "/src/MiniAOD/MiniAODHelper/data/Run2Legacy/met_trigger_sf.root";
        hist_name = "120pfht_hltmu_1m_2018";
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

    hist = (TH1D*) root_file->Get(hist_name);
    if (hist == nullptr) {
        initialized = false;
        return;
    }

    // determine the ranges of the given TH2F
    xmin = hist->GetXaxis()->GetXmin();
    xmax = hist->GetXaxis()->GetXmax();

    // std::cout << "xmin: " << xmin << " xmax: " << xmax << std::endl;
    // std::cout << "ymin: " << ymin << " ymax: " << ymax << std::endl;

    initialized = true;
}

// function to calculate trigger scale factors
std::vector< float > METTriggerSFs::CalculateTriggerSFs(const InputCollections& input)
{
    std::vector< float > sfs{-999., -999., -999.};

    auto recoil_p4 = input.correctedMET.corP4(pat::MET::Type1);
    for (const auto& el : input.selectedElectronsLoose) { recoil_p4 += el.p4(); }
    for (const auto& mu : input.selectedMuonsLoose) { recoil_p4 += mu.p4(); }
    for (const auto& ph : input.selectedPhotons) { recoil_p4 += ph.p4(); }
    // make sure to stay within the range ot the histograms
    recoil = recoil_p4.pt();
    recoil = std::max(float(xmin + 0.1), recoil);
    recoil = std::min(float(xmax - 0.1), recoil);

    // std::cout << "Pt: " << pt << std::endl;
    // std::cout << "Eta: " << eta << std::endl;
    // calculate SFs here
    sfs.at(0) = hist->GetBinContent(hist->FindBin(recoil));
    sfs.at(1) = (hist->GetBinContent(hist->FindBin(recoil))) * (1 + (0.01 * input.selectedMuonsLoose.size()));
    sfs.at(2) = (hist->GetBinContent(hist->FindBin(recoil))) * (1 - (0.01 * input.selectedMuonsLoose.size()));

    return sfs;
}
