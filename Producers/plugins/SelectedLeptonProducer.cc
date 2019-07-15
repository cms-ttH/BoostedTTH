
#include "BoostedTTH/Producers/interface/SelectedLeptonProducer.h"

// constructor with initializer list for all inputs which are obtained from the
// config
SelectedLeptonProducer::SelectedLeptonProducer(const edm::ParameterSet& iConfig)
    : leptonType{iConfig.getParameter<std::string>("leptonType")},
      collectionNames_{
          iConfig.getParameter<std::vector<std::string> >("collectionNames")},
      ptMins_{iConfig.getParameter<std::vector<double> >("ptMins")},
      etaMaxs_{iConfig.getParameter<std::vector<double> >("etaMaxs")},
      leptonIDs{iConfig.getParameter<std::vector<std::string> >("leptonIDs")},
      isoConeSizes{
          iConfig.getParameter<std::vector<std::string> >("isoConeSizes")},
      isoCorrTypes{
          iConfig.getParameter<std::vector<std::string> >("isoCorrTypes")},
      muonIsoTypes{
          iConfig.getParameter<std::vector<std::string> >("muonIsoTypes")},
      era{iConfig.getParameter<std::string>("era")},
      isData{iConfig.getParameter<bool>("isData")},
      useMuonRC{iConfig.getParameter<bool>("useMuonRC")},
      deterministicSeeds{iConfig.getParameter<bool>("useDeterministicSeeds")},
      rc{std::string(getenv("CMSSW_BASE")) + "/src/" +
         iConfig.getParameter<std::string>("rc_dir")},
      EA{std::string(getenv("CMSSW_BASE")) + "/src/" +
         iConfig.getParameter<std::string>("ea_dir")},

      // inputs
      EDMRhoToken{consumes<double>(iConfig.getParameter<edm::InputTag>("rho"))},
      EDMVertexToken{consumes<reco::VertexCollection>(
          iConfig.getParameter<edm::InputTag>("vertices"))},
      EDMMuonsToken{consumes<pat::MuonCollection>(
          iConfig.getParameter<edm::InputTag>("leptons"))},
      EDMElectronsToken{consumes<pat::ElectronCollection>(
          iConfig.getParameter<edm::InputTag>("leptons"))}

{
  // setup of producer
  if (leptonType == "electron")
    leptonType_ = LeptonType::Electron;
  else if (leptonType == "muon")
    leptonType_ = LeptonType::Muon;
  else {
    std::cerr << "\n\nERROR: Unknown lepton type " << leptonType << std::endl;
    std::cerr << "Please select 'electron' or 'muon'\n" << std::endl;
    throw std::exception();
  }

  if (era.find("2016") == std::string::npos and
      era.find("2017") == std::string::npos and
      era.find("2018") == std::string::npos) {
    std::cerr << "\n\nERROR: Unknown era" << era << "in SelectedLeptonProducer "
              << std::endl;
    std::cerr << "Please select '2016' or '2017' or '2018'\n" << std::endl;
    throw std::exception();
  }

  // fill lepton selection criteria with default values
  electronIDs_ = std::vector<ElectronID>(leptonIDs.size(), ElectronID::Loose);
  muonIDs_ = std::vector<MuonID>(leptonIDs.size(), MuonID::Loose);
  IsoConeSizes_ = std::vector<IsoConeSize>(leptonIDs.size(), IsoConeSize::R03);
  IsoCorrTypes_ =
      std::vector<IsoCorrType>(leptonIDs.size(), IsoCorrType::rhoEA);
  muonIsos_ =
      std::vector<MuonIsolation>(leptonIDs.size(), MuonIsolation::Loose);

  // some safety guards
  assert(ptMins_.size() == etaMaxs_.size());
  assert(leptonIDs.size() == etaMaxs_.size());
  assert(collectionNames_.size() == etaMaxs_.size());
  assert(isoConeSizes.size() == etaMaxs_.size());
  assert(isoCorrTypes.size() == etaMaxs_.size());
  if (leptonType_ == LeptonType::Muon)
    assert(muonIsoTypes.size() == etaMaxs_.size());

  // translate strings from config to nice C++ objects
  for (size_t i = 0; i < ptMins_.size(); i++) {
    if (leptonType_ == LeptonType::Electron) {
      if (leptonIDs.at(i) == "loose")
        electronIDs_.at(i) = ElectronID::Loose;
      else if (leptonIDs.at(i) == "medium")
        electronIDs_.at(i) = ElectronID::Medium;
      else if (leptonIDs.at(i) == "tight")
        electronIDs_.at(i) = ElectronID::Tight;
      else if (leptonIDs.at(i) == "veto")
        electronIDs_.at(i) = ElectronID::Veto;
      else if (leptonIDs.at(i) == "none")
        electronIDs_.at(i) = ElectronID::None;
      else {
        std::cerr << "\n\nERROR: No matching electron ID type found for: "
                  << leptonIDs.at(i) << std::endl;
        throw std::exception();
      }
    }
    if (leptonType_ == LeptonType::Muon) {
      if (leptonIDs.at(i) == "loose")
        muonIDs_.at(i) = MuonID::Loose;
      else if (leptonIDs.at(i) == "medium")
        muonIDs_.at(i) = MuonID::Medium;
      else if (leptonIDs.at(i) == "tight")
        muonIDs_.at(i) = MuonID::Tight;
      else if (leptonIDs.at(i) == "none")
        muonIDs_.at(i) = MuonID::None;
      else {
        std::cerr << "\n\nERROR: No matching muon ID type found for: "
                  << leptonIDs.at(i) << std::endl;
        throw std::exception();
      }

      if (muonIsoTypes.at(i) == "loose")
        muonIsos_.at(i) = MuonIsolation::Loose;
      else if (muonIsoTypes.at(i) == "medium")
        muonIsos_.at(i) = MuonIsolation::Medium;
      else if (muonIsoTypes.at(i) == "tight")
        muonIsos_.at(i) = MuonIsolation::Tight;
      else if (muonIsoTypes.at(i) == "none")
        muonIsos_.at(i) = MuonIsolation::None;
      else {
        std::cerr << "\n\nERROR: No matching muon isolation type found for: "
                  << muonIsoTypes.at(i) << std::endl;
        throw std::exception();
      }
    }

    if (isoConeSizes.at(i) == "R03")
      IsoConeSizes_.at(i) = IsoConeSize::R03;
    else if (isoConeSizes.at(i) == "R04")
      IsoConeSizes_.at(i) = IsoConeSize::R04;
    else {
      std::cerr << "\n\nERROR: No matching isolation cone size found for: "
                << isoConeSizes.at(i) << std::endl;
      throw std::exception();
    }

    if (isoCorrTypes.at(i) == "deltaBeta")
      IsoCorrTypes_.at(i) = IsoCorrType::deltaBeta;
    else if (isoCorrTypes.at(i) == "rhoEA")
      IsoCorrTypes_.at(i) = IsoCorrType::rhoEA;
    else {
      std::cerr
          << "\n\nERROR: No matching isolation correction type found for: "
          << isoCorrTypes.at(i) << std::endl;
      throw std::exception();
    }

    if (leptonType_ == LeptonType::Electron)
      produces<pat::ElectronCollection>(collectionNames_.at(i));
    else if (leptonType_ == LeptonType::Muon)
      produces<pat::MuonCollection>(collectionNames_.at(i));
    else {
      std::cerr << "\n\nERROR: Unknown lepton type " << leptonType << std::endl;
      std::cerr << "Please select 'electron' or 'muon'\n" << std::endl;
      throw std::exception();
    }
  }

  // load electron scale factor histograms from given files
  if (leptonType_ == LeptonType::Electron) {
    EleID_SF_Loose =
        (TH2F*)TFile::Open(
            TString(std::string(getenv("CMSSW_BASE")) + "/src/" +
                    iConfig.getParameter<std::string>("file_EleLooseIDSF")))
            ->Get("EGamma_SF2D");
    EleID_SF_Loose->SetDirectory(0);
    EleID_SF_Medium =
        (TH2F*)TFile::Open(
            TString(std::string(getenv("CMSSW_BASE")) + "/src/" +
                    iConfig.getParameter<std::string>("file_EleMediumIDSF")))
            ->Get("EGamma_SF2D");
    EleID_SF_Medium->SetDirectory(0);
    EleID_SF_Tight =
        (TH2F*)TFile::Open(
            TString(std::string(getenv("CMSSW_BASE")) + "/src/" +
                    iConfig.getParameter<std::string>("file_EleTightIDSF")))
            ->Get("EGamma_SF2D");
    EleID_SF_Tight->SetDirectory(0);
    EleReco_SF_highPt =
        (TH2F*)TFile::Open(
            TString(std::string(getenv("CMSSW_BASE")) + "/src/" +
                    iConfig.getParameter<std::string>("file_EleRecoSF_highPt")))
            ->Get("EGamma_SF2D");
    EleReco_SF_highPt->SetDirectory(0);
    EleReco_SF_lowPt =
        (TH2F*)TFile::Open(
            TString(std::string(getenv("CMSSW_BASE")) + "/src/" +
                    iConfig.getParameter<std::string>("file_EleRecoSF_lowPt")))
            ->Get("EGamma_SF2D");
    EleReco_SF_lowPt->SetDirectory(0);
  }
  // load muon scale factor histograms from given files
  else if (leptonType_ == LeptonType::Muon) {
    // put muon stuff here
    TString filename;
    TString histoname;
    filename = std::string(getenv("CMSSW_BASE")) + "/src/" +
               iConfig.getParameter<std::string>("file_MuonIDSF");
    histoname = iConfig.getParameter<std::string>("histname_MuonLooseIDSF");
    MuonID_SF_Loose =
        (TH2F*)TFile::Open(filename.Data())->Get(histoname.Data());
    MuonID_SF_Loose->SetDirectory(0);

    histoname = iConfig.getParameter<std::string>("histname_MuonMediumIDSF");
    MuonID_SF_Medium =
        (TH2F*)TFile::Open(filename.Data())->Get(histoname.Data());
    MuonID_SF_Medium->SetDirectory(0);

    histoname = iConfig.getParameter<std::string>("histname_MuonTightIDSF");
    MuonID_SF_Tight =
        (TH2F*)TFile::Open(filename.Data())->Get(histoname.Data());
    MuonID_SF_Tight->SetDirectory(0);

    filename = std::string(getenv("CMSSW_BASE")) + "/src/" +
               iConfig.getParameter<std::string>("file_MuonIsoSF");
    histoname =
        iConfig.getParameter<std::string>("histname_MuonLooseISO_LooseIDSF");
    MuonISO_SF_LooseRelIso_LooseID =
        (TH2F*)TFile::Open(filename.Data())->Get(histoname.Data());
    MuonISO_SF_LooseRelIso_LooseID->SetDirectory(0);

    histoname =
        iConfig.getParameter<std::string>("histname_MuonLooseISO_MediumIDSF");
    MuonISO_SF_LooseRelIso_MediumID =
        (TH2F*)TFile::Open(filename.Data())->Get(histoname.Data());
    MuonISO_SF_LooseRelIso_MediumID->SetDirectory(0);

    histoname =
        iConfig.getParameter<std::string>("histname_MuonLooseISO_TightIDSF");
    MuonISO_SF_LooseRelIso_TightID =
        (TH2F*)TFile::Open(filename.Data())->Get(histoname.Data());
    MuonISO_SF_LooseRelIso_TightID->SetDirectory(0);

    histoname =
        iConfig.getParameter<std::string>("histname_MuonTightISO_MediumIDSF");
    MuonISO_SF_TightRelIso_MediumID =
        (TH2F*)TFile::Open(filename.Data())->Get(histoname.Data());
    MuonISO_SF_TightRelIso_MediumID->SetDirectory(0);

    histoname =
        iConfig.getParameter<std::string>("histname_MuonTightISO_TightIDSF");
    MuonISO_SF_TightRelIso_TightID =
        (TH2F*)TFile::Open(filename.Data())->Get(histoname.Data());
    MuonISO_SF_TightRelIso_TightID->SetDirectory(0);
  }
}

// destructor
SelectedLeptonProducer::~SelectedLeptonProducer() {}

//
// member functions
//

// ------------ method called to produce the data  ------------
void SelectedLeptonProducer::produce(edm::Event& iEvent,
                                     const edm::EventSetup& iSetup) {
  // get the vertices and the rho (average pile-up energy density per unit area
  // in the phi-eta plane)
  edm::Handle<reco::VertexCollection> hVtxs;
  iEvent.getByToken(EDMVertexToken, hVtxs);
  if (not hVtxs.isValid()) {
    std::cerr << "\n\nERROR: retrieved vertex collection is not valid"
              << std::endl;
    throw std::exception();
  } else if (hVtxs->empty()) {
    std::cerr << "\n\nERROR: retrieved vertex collection is empty" << std::endl;
    throw std::exception();
  }
  // primary vertex
  vertex = hVtxs->at(0);

  edm::Handle<double> hRho;
  iEvent.getByToken(EDMRhoToken, hRho);
  if (not hRho.isValid()) {
    std::cerr << "\n\nERROR: retrieved pile-up energy density is not valid"
              << std::endl;
    throw std::exception();
  }
  // pile-up density
  rho = *hRho;

  if (leptonType_ == LeptonType::Electron) {
    // get input electron collection
    edm::Handle<pat::ElectronCollection> inputElectrons;
    iEvent.getByToken(EDMElectronsToken, inputElectrons);
    if (not inputElectrons.isValid()) {
      std::cerr << "\n\nERROR: retrieved electron collection is not valid"
                << std::endl;
      throw std::exception();
    }

    for (size_t i = 0; i < ptMins_.size(); i++) {
      std::vector<pat::Electron> updatedElectrons = *inputElectrons;

      // add the electron relative isolation as a userfloat, mainly for sync by
      // now
      AddElectronRelIsolation(updatedElectrons, IsoCorrTypes_.at(i),
                              IsoConeSizes_.at(i));

      // apply energy corrections (scale & smearing)
      for (auto& ele : updatedElectrons) {
        ele.addUserFloat("ptBeforeRun2Calibration", ele.pt());
        if (ele.hasUserFloat("ecalTrkEnergyPostCorr")) {
          ele.setP4(ele.p4() * ele.userFloat("ecalTrkEnergyPostCorr") /
                    ele.energy());
          // only use combined systematics for scaling and smearing since we
          // should not be very sensitive to electron energy scale as
          // recommended by e/gamma pog only for MC
          if (not isData) {
            ele.addUserFloat("CorrFactor_ScaleUp",
                             ele.userFloat("energyScaleUp") /
                                 ele.userFloat("ecalTrkEnergyPostCorr"));
            ele.addUserFloat("CorrFactor_ScaleDown",
                             ele.userFloat("energyScaleDown") /
                                 ele.userFloat("ecalTrkEnergyPostCorr"));
            ele.addUserFloat("CorrFactor_SigmaUp",
                             ele.userFloat("energySigmaUp") /
                                 ele.userFloat("ecalTrkEnergyPostCorr"));
            ele.addUserFloat("CorrFactor_SigmaDown",
                             ele.userFloat("energySigmaDown") /
                                 ele.userFloat("ecalTrkEnergyPostCorr"));
          }
        }
      }

      std::vector<pat::Electron> selectedElectrons = GetSortedByPt(
          GetSelectedElectrons(updatedElectrons, ptMins_.at(i),
                               electronIDs_.at(i), etaMaxs_.at(i)));

      if (not isData) AddElectronSFs(selectedElectrons, electronIDs_.at(i));

      // produce the different electron collections and create a unique ptr to
      // it
      std::unique_ptr<pat::ElectronCollection> selectedLeptons =
          std::make_unique<pat::ElectronCollection>(selectedElectrons);

      // put the collection into the event with help of the unique ptr
      iEvent.put(std::move(selectedLeptons), collectionNames_.at(i));
    }

  }

  else if (leptonType_ == LeptonType::Muon) {
    // get input muon collection
    edm::Handle<pat::MuonCollection> inputMuons;
    iEvent.getByToken(EDMMuonsToken, inputMuons);
    if (not inputMuons.isValid()) {
      std::cerr << "\n\nERROR: retrieved muon collection is not valid"
                << std::endl;
      throw std::exception();
    }
    std::vector<pat::Muon> correctedMuons = *inputMuons;
    // if the flag is set, apply the muon momentum correction (rochester
    // correction)
    if (useMuonRC) {
      ApplyMuonMomentumCorrection(correctedMuons);
    }

    // produce the different muon collections
    for (size_t i = 0; i < ptMins_.size(); i++) {
      std::vector<pat::Muon> updatedMuons = correctedMuons;
      // add the muon relative isolation as a userfloat, mainly for sync by now
      AddMuonRelIsolation(updatedMuons, IsoCorrTypes_.at(i),
                          IsoConeSizes_.at(i));

      // add muon scale factors

      std::vector<pat::Muon> selectedMuons = GetSortedByPt(GetSelectedMuons(
          updatedMuons, ptMins_.at(i), muonIDs_.at(i), IsoConeSizes_.at(i),
          IsoCorrTypes_.at(i), etaMaxs_.at(i), muonIsos_.at(i)));
      if (not isData)
        AddMuonSFs(selectedMuons, muonIDs_.at(i), muonIsos_.at(i));
      // produce the different muon collections and create a unique ptr to it
      std::unique_ptr<pat::MuonCollection> selectedLeptons =
          std::make_unique<pat::MuonCollection>(selectedMuons);
      // put the collection into the event with help of the unique ptr
      iEvent.put(std::move(selectedLeptons), collectionNames_.at(i));
    }
  } else {
    std::cerr << "\n\nERROR: Unknown lepton type " << leptonType << std::endl;
    std::cerr << "Please select 'electron' or 'muon'\n" << std::endl;
    throw std::exception();
  }
}
// template function to sort a collection by pt and return the sorted
// collection, should work with pat::Muon and pat::Electron collections and
// probably more
template <typename T>
T SelectedLeptonProducer::GetSortedByPt(const T& collection) {
  T result = collection;
  std::sort(result.begin(), result.end(),
            [](typename T::value_type a, typename T::value_type b) {
              return a.pt() > b.pt();
            });
  return result;
}
// function to select electrons with several properties and return a collection
std::vector<pat::Electron> SelectedLeptonProducer::GetSelectedElectrons(
    const std::vector<pat::Electron>& inputElectrons, const double iMinPt,
    const ElectronID iElectronID, const double iMaxEta) const {
  std::vector<pat::Electron> selectedElectrons;

  for (const auto& ele : inputElectrons) {
    if (isGoodElectron(ele, iMinPt, iMaxEta, iElectronID)) {
      selectedElectrons.push_back(ele);
    }
  }

  return selectedElectrons;
}
// function to check whether an electron fulfills several requirements
bool SelectedLeptonProducer::isGoodElectron(
    const pat::Electron& iElectron, const double iMinPt, const double iMaxEta,
    const ElectronID iElectronID) const {
  bool passesKinematics =
      (iMinPt <= iElectron.pt()) and (iMaxEta >= fabs(iElectron.eta()));
  bool inCrack = false;
  bool passesIPcuts = false;
  bool passesID = false;

  double absSCeta = 999;
  if (iElectron.superCluster().isAvailable()) {
    absSCeta = fabs(iElectron.superCluster()->position().eta());
    inCrack = (absSCeta > 1.4442 and absSCeta < 1.5660);
  }
  double IP_d0 = 999;
  double IP_dZ = 999;

  bool isEB = absSCeta < 1.479;  // check if electron is in barrel region
  if (iElectron.gsfTrack().isAvailable()) {
    IP_d0 = fabs(iElectron.gsfTrack()->dxy(vertex.position()));
    IP_dZ = fabs(iElectron.gsfTrack()->dz(vertex.position()));
  }

  // if impact parameter cuts are not met, set passesIPcuts = false
  if (isEB)
    passesIPcuts = (IP_d0 < 0.05 and IP_dZ < 0.1);
  else
    passesIPcuts = (IP_d0 < 0.1 and IP_dZ < 0.2);

  switch (iElectronID) {
    case ElectronID::None:
      passesID = true;
      break;
    case ElectronID::Veto:
      passesID = iElectron.electronID("cutBasedElectronID-Fall17-94X-V2-veto");
      break;
    case ElectronID::Loose:
      passesID = iElectron.electronID("cutBasedElectronID-Fall17-94X-V2-loose");
      break;
    case ElectronID::Medium:
      passesID =
          iElectron.electronID("cutBasedElectronID-Fall17-94X-V2-medium");
      break;
    case ElectronID::Tight:
      passesID = iElectron.electronID("cutBasedElectronID-Fall17-94X-V2-tight");
      break;
    default:
      std::cerr << "\n\nERROR: InvalidElectronID" << std::endl;
      throw std::exception();
  }

  return passesKinematics and (not inCrack) and passesIPcuts and passesID;
}
// function to calculate electron relative isolation by hand. Mainly needed for
// sync purposes since isolations are part of other provided electron properties
// like ID
double SelectedLeptonProducer::GetEletronRelIsolation(
    const pat::Electron& inputElectron, const IsoCorrType icorrType,
    const IsoConeSize iconeSize) const {
  double isoChargedHadrons =
      inputElectron.pfIsolationVariables().sumChargedHadronPt;
  double isoNeutralHadrons =
      inputElectron.pfIsolationVariables().sumNeutralHadronEt;
  double isoPhotons = inputElectron.pfIsolationVariables().sumPhotonEt;
  double pileup = 0;
  if (iconeSize == IsoConeSize::R03) {
    if (icorrType == IsoCorrType::deltaBeta)
      pileup = 0.5 * inputElectron.pfIsolationVariables().sumPUPt;
    else if (icorrType == IsoCorrType::rhoEA) {
      double eta = 0.;
      if (inputElectron.superCluster().isAvailable()) {
        eta = fabs(inputElectron.superCluster()->position().eta());
      } else {
        eta = fabs(inputElectron.eta());
      }
      pileup = rho * EA.getEffectiveArea(eta);
    } else {
      std::cerr << "\n\nERROR: invalid electron isolation correction type"
                << std::endl;
      throw std::exception();
    }
  } else {
    std::cerr << "\n\nERROR: electron isolation is not implemeted for "
                 "conesizes other than 0.3"
              << std::endl;
    throw std::exception();
  }
  return (isoChargedHadrons +
          std::max(0., isoNeutralHadrons + isoPhotons - pileup)) /
         inputElectron.pt();
}
// function to add the calculate electron relative isolation to the electron as
// a userfloat
void SelectedLeptonProducer::AddElectronRelIsolation(
    std::vector<pat::Electron>& inputElectrons, const IsoCorrType icorrType,
    const IsoConeSize iconeSize) {
  for (auto& ele : inputElectrons) {
    ele.addUserFloat("relIso",
                     GetEletronRelIsolation(ele, icorrType, iconeSize));
  }
}

// function to add electron object scale factors to electron, currently
// reconstruction and identification
void SelectedLeptonProducer::AddElectronSFs(
    std::vector<pat::Electron>& inputElectrons,
    const ElectronID iElectronID) const {
  for (auto& ele : inputElectrons) {
    auto IDSFs = GetElectronIDSF(ele, iElectronID);
    auto RecoSFs = GetElectronRecoSF(ele);
    assert(IDSFs.size() == 3);
    assert(RecoSFs.size() == 3);
    ele.addUserFloat("IdentificationSF", IDSFs.at(0));
    ele.addUserFloat("IdentificationSFUp", IDSFs.at(1));
    ele.addUserFloat("IdentificationSFDown", IDSFs.at(2));
    ele.addUserFloat("ReconstructionSF", RecoSFs.at(0));
    ele.addUserFloat("ReconstructionSFUp", RecoSFs.at(1));
    ele.addUserFloat("ReconstructionSFDown", RecoSFs.at(2));
  }
}

// function to calculate electron ID scale factors and return them as a triplet
std::vector<float> SelectedLeptonProducer::GetElectronIDSF(
    const pat::Electron& iElectron, const ElectronID iElectronID) const {
  // get pt and eta of the electron
  auto pt = iElectron.hasUserFloat("ptBeforeRun2Calibration")
                ? iElectron.userFloat("ptBeforeRun2Calibration")
                : iElectron.pt();
  auto eta = iElectron.superCluster().isAvailable()
                 ? iElectron.superCluster()->position().eta()
                 : iElectron.eta();
  TH2F* SF_hist = nullptr;
  std::vector<float> SFs{1.0, 1.0, 1.0};
  // load the correct scale factor histogram
  switch (iElectronID) {
    case ElectronID::None:
      break;
    case ElectronID::Veto:
      break;
    case ElectronID::Loose:
      SF_hist = EleID_SF_Loose;
      break;
    case ElectronID::Medium:
      SF_hist = EleID_SF_Medium;
      break;
    case ElectronID::Tight:
      SF_hist = EleID_SF_Tight;
      break;
    default:
      std::cerr << "\n\nERROR: InvalidElectronID" << std::endl;
      throw std::exception();
  }

  if (SF_hist == nullptr) {
    std::cerr << "\n\nERROR: Electron ID Scale Factor File could not be loaded"
              << std::endl;
    throw std::exception();
  }

  // determine the ranges of the given TH2Fs
  auto xmin = SF_hist->GetXaxis()->GetXmin();
  auto xmax = SF_hist->GetXaxis()->GetXmax();
  auto ymin = SF_hist->GetYaxis()->GetXmin();
  auto ymax = SF_hist->GetYaxis()->GetXmax();

  // make sure to stay within the range ot the histograms
  eta = std::max(xmin + 0.1, eta);
  eta = std::min(xmax - 0.1, eta);
  pt = std::max(ymin + 0.1, pt);
  pt = std::min(ymax - 0.1, pt);

  // calculate the scale factors
  SFs.at(0) = SF_hist->GetBinContent(SF_hist->FindBin(eta, pt));
  SFs.at(1) = (SF_hist->GetBinContent(SF_hist->FindBin(eta, pt))) +
              (SF_hist->GetBinError(SF_hist->FindBin(eta, pt)));
  SFs.at(2) = (SF_hist->GetBinContent(SF_hist->FindBin(eta, pt))) -
              (SF_hist->GetBinError(SF_hist->FindBin(eta, pt)));

  return SFs;
}

// function to calculate electron reconstruction scale factor
std::vector<float> SelectedLeptonProducer::GetElectronRecoSF(
    const pat::Electron& iElectron) const {
  // get pt and eta of the electron
  auto pt = iElectron.hasUserFloat("ptBeforeRun2Calibration")
                ? iElectron.userFloat("ptBeforeRun2Calibration")
                : iElectron.pt();
  auto eta = iElectron.superCluster().isAvailable()
                 ? iElectron.superCluster()->position().eta()
                 : iElectron.eta();
  TH2F* SF_hist = nullptr;
  std::vector<float> SFs{1.0, 1.0, 1.0};

  // load the correct scale factor histogram
  if (era.find("2016") != std::string::npos or
      era.find("2017") != std::string::npos) {
    if (pt >= 20.)
      SF_hist = EleReco_SF_highPt;
    else
      SF_hist = EleReco_SF_lowPt;
  } else if (era.find("2018") != std::string::npos) {
    SF_hist = EleReco_SF_highPt;
  }

  if (SF_hist == nullptr) {
    std::cerr
        << "\n\nERROR: Electron Reco Scale Factor File could not be loaded"
        << std::endl;
    throw std::exception();
  }

  // determine the ranges of the given TH2Fs
  auto xmin = SF_hist->GetXaxis()->GetXmin();
  auto xmax = SF_hist->GetXaxis()->GetXmax();
  auto ymin = SF_hist->GetYaxis()->GetXmin();
  auto ymax = SF_hist->GetYaxis()->GetXmax();

  // make sure to stay within the range ot the histograms
  eta = std::max(xmin + 0.1, eta);
  eta = std::min(xmax - 0.1, eta);
  pt = std::max(ymin + 0.1, pt);
  pt = std::min(ymax - 0.1, pt);

  // calculate the scale factors
  SFs.at(0) = SF_hist->GetBinContent(SF_hist->FindBin(eta, pt));
  SFs.at(1) = (SF_hist->GetBinContent(SF_hist->FindBin(eta, pt))) +
              (SF_hist->GetBinError(SF_hist->FindBin(eta, pt)));
  SFs.at(2) = (SF_hist->GetBinContent(SF_hist->FindBin(eta, pt))) -
              (SF_hist->GetBinError(SF_hist->FindBin(eta, pt)));

  return SFs;
}

// function to select muons with several properties and return a collection
std::vector<pat::Muon> SelectedLeptonProducer::GetSelectedMuons(
    const std::vector<pat::Muon>& inputMuons, const double iMinPt,
    const MuonID iMuonID, const IsoConeSize iconeSize,
    const IsoCorrType icorrType, const double iMaxEta,
    const MuonIsolation imuonIso) const {
  std::vector<pat::Muon> selectedMuons;

  for (const auto& mu : inputMuons) {
    if (isGoodMuon(mu, iMinPt, iMaxEta, iMuonID, iconeSize, icorrType,
                   imuonIso)) {
      selectedMuons.push_back(mu);
    }
  }

  return selectedMuons;
}
// function to check whether a muon fulfills several requirements
bool SelectedLeptonProducer::isGoodMuon(
    const pat::Muon& iMuon, const double iMinPt, const double iMaxEta,
    const MuonID iMuonID, const IsoConeSize iconeSize,
    const IsoCorrType icorrType, const MuonIsolation imuonIso) const {
  bool passesKinematics =
      (iMinPt <= iMuon.pt()) and (iMaxEta >= fabs(iMuon.eta()));
  bool passesID = false;
  bool passesIso = false;
  switch (iMuonID) {
    case MuonID::None:
      passesID = true;
      break;
    case MuonID::Loose:
      passesID = muon::isLooseMuon(iMuon);
      break;
    case MuonID::Medium:
      passesID = muon::isMediumMuon(iMuon);
      break;
    case MuonID::Tight:
      passesID = muon::isTightMuon(iMuon, vertex);
      break;
    default:
      std::cerr << "\n\nERROR: InvalidMuonID" << std::endl;
      throw std::exception();
  }
  switch (imuonIso) {
    case MuonIsolation::None:
      passesIso = true;
      break;
    case MuonIsolation::Loose:
      passesIso = iMuon.passed(pat::Muon::PFIsoLoose);
      break;
    case MuonIsolation::Medium:
      passesIso = iMuon.passed(pat::Muon::PFIsoMedium);
      break;
    case MuonIsolation::Tight:
      passesIso = iMuon.passed(pat::Muon::PFIsoTight);
      break;
    default:
      std::cerr << "\n\nERROR: InvalidMuonIso" << std::endl;
      throw std::exception();
  }
  return passesKinematics and passesID and passesIso;
}
// function to apply muon momentum correction (rochester correction)
void SelectedLeptonProducer::ApplyMuonMomentumCorrection(
    std::vector<pat::Muon>& inputMuons) {
  double momentum_sf;
  double momentum_sfDelta;
  TRandom3 rnd;
  for (size_t i = 0; i < inputMuons.size(); i++) {
    momentum_sf = 1.;
    if (deterministicSeeds) {
      int32_t seed = inputMuons.at(i).userInt("deterministicSeed");
      rnd.SetSeed((uint32_t)seed);
    }
    double r1 = rnd.Rndm();
    int trackerLayersWithMeasurement = 0;
    if (!inputMuons.at(i).innerTrack().isNull()) {
      trackerLayersWithMeasurement = inputMuons.at(i)
                                         .innerTrack()
                                         ->hitPattern()
                                         .trackerLayersWithMeasurement();
    }
    if (isData) {
      momentum_sf =
          rc.kScaleDT(inputMuons.at(i).charge(), inputMuons.at(i).pt(),
                      inputMuons.at(i).eta(), inputMuons.at(i).phi(), 0, 0);
      momentum_sfDelta =
          rc.kScaleDTerror(inputMuons.at(i).charge(), inputMuons.at(i).pt(),
                           inputMuons.at(i).eta(), inputMuons.at(i).phi());
    } else {
      if (inputMuons.at(i).genLepton()) {
        momentum_sf =
            rc.kSpreadMC(inputMuons.at(i).charge(), inputMuons.at(i).pt(),
                         inputMuons.at(i).eta(), inputMuons.at(i).phi(),
                         inputMuons.at(i).genLepton()->pt(), 0, 0);
        momentum_sfDelta =
            rc.kSpreadMCerror(inputMuons.at(i).charge(), inputMuons.at(i).pt(),
                              inputMuons.at(i).eta(), inputMuons.at(i).phi(),
                              inputMuons.at(i).genLepton()->pt());
      } else {
        momentum_sf =
            rc.kSmearMC(inputMuons.at(i).charge(), inputMuons.at(i).pt(),
                        inputMuons.at(i).eta(), inputMuons.at(i).phi(),
                        trackerLayersWithMeasurement, r1, 0, 0);
        momentum_sfDelta =
            rc.kSmearMCerror(inputMuons.at(i).charge(), inputMuons.at(i).pt(),
                             inputMuons.at(i).eta(), inputMuons.at(i).phi(),
                             trackerLayersWithMeasurement, r1);
      }
    }
    auto tmp_vector = inputMuons.at(i).p4();
    inputMuons.at(i).addUserFloat("PtbeforeRC", tmp_vector.Pt());
    inputMuons.at(i).addUserFloat("roccorSF", momentum_sf);
    inputMuons.at(i).addUserFloat("roccorSFUp", momentum_sf + momentum_sfDelta);
    inputMuons.at(i).addUserFloat("roccorSFDown",
                                  momentum_sf - momentum_sfDelta);
    // tmp_vector.SetPxPyPzE(momentum_sf*tmp_vector.Px(),momentum_sf*tmp_vector.Py(),momentum_sf*tmp_vector.Pz(),TMath::Sqrt((1+(tmp_vector.P2()/(tmp_vector.E()*tmp_vector.E())*(momentum_sf*momentum_sf-1))))*tmp_vector.E());
    tmp_vector *= momentum_sf;
    inputMuons.at(i).setP4(tmp_vector);
  }
}
// function to calculate muon relative isolation by hand. Mainly needed for sync
// purposes since isolation-checks are provided centrally
double SelectedLeptonProducer::GetMuonRelIsolation(
    const pat::Muon& inputMuon, const IsoCorrType icorrType,
    const IsoConeSize iconeSize) const {
  double isoChargedHadrons = inputMuon.pfIsolationR04().sumChargedHadronPt;
  double isoNeutralHadrons = inputMuon.pfIsolationR04().sumNeutralHadronEt;
  double isoPhotons = inputMuon.pfIsolationR04().sumPhotonEt;
  double pileup = 0;
  if (iconeSize == IsoConeSize::R04) {
    if (icorrType == IsoCorrType::deltaBeta)
      pileup = 0.5 * inputMuon.pfIsolationR04().sumPUPt;
    else {
      std::cerr << "\n\nERROR: muon isolation is not implemeted for pileup "
                   "corrections other than deltaBeta"
                << std::endl;
      throw std::exception();
    }
  } else {
    std::cerr << "\n\nERROR: muon isolation is not implemeted for conesizes "
                 "other than 0.4"
              << std::endl;
    throw std::exception();
  }
  return (isoChargedHadrons +
          std::max(0., isoNeutralHadrons + isoPhotons - pileup)) /
         inputMuon.pt();
}
// function to add the calculate muon relative isolation to the muon as a
// userfloat
void SelectedLeptonProducer::AddMuonRelIsolation(
    std::vector<pat::Muon>& inputMuons, const IsoCorrType icorrType,
    const IsoConeSize iconeSize) {
  for (auto& mu : inputMuons) {
    mu.addUserFloat("relIso", GetMuonRelIsolation(mu, icorrType, iconeSize));
  }
}

// function to add electron object scale factors to electron, currently
// reconstruction and identification
void SelectedLeptonProducer::AddMuonSFs(std::vector<pat::Muon>& inputMuons,
                                        const MuonID& iMuonID,
                                        const MuonIsolation& iMuonIso) const {
  for (auto& muon : inputMuons) {
    auto IDSFs = GetMuonIDSF(muon, iMuonID);
    auto IsoSFs = GetMuonISOSF(muon, iMuonID, iMuonIso);
    assert(IDSFs.size() == 3);
    assert(IsoSFs.size() == 3);
    muon.addUserFloat("IdentificationSF", IDSFs.at(0));
    muon.addUserFloat("IdentificationSFUp", IDSFs.at(1));
    muon.addUserFloat("IdentificationSFDown", IDSFs.at(2));
    muon.addUserFloat("IsolationSF", IsoSFs.at(0));
    muon.addUserFloat("IsolationSFUp", IsoSFs.at(1));
    muon.addUserFloat("IsolationSFDown", IsoSFs.at(2));
  }
}

std::vector<float> SelectedLeptonProducer::GetMuonIDSF(
    const pat::Muon& iMuon, const MuonID& iMuonID) const {
  // get pt and eta of the electron
  auto pt = iMuon.pt();
  auto eta = abs(iMuon.eta());
  TH2F* SF_hist = nullptr;
  std::vector<float> SFs{1.0, 1.0, 1.0};
  // load the correct scale factor histogram
  switch (iMuonID) {
    case MuonID::None:
      break;
    case MuonID::Loose:
      SF_hist = MuonID_SF_Loose;
      break;
    case MuonID::Medium:
      SF_hist = MuonID_SF_Medium;
      break;
    case MuonID::Tight:
      SF_hist = MuonID_SF_Tight;
      break;
    default:
      std::cerr << "\n\nERROR: InvalidMuonID" << std::endl;
      throw std::exception();
  }

  if (SF_hist == nullptr) {
    std::cerr << "\n\nERROR: Muon ID Scale Factor File could not be loaded"
              << std::endl;
    throw std::exception();
  }

  // determine the ranges of the given TH2Fs
  auto xmin = SF_hist->GetXaxis()->GetXmin();
  auto xmax = SF_hist->GetXaxis()->GetXmax();
  auto ymin = SF_hist->GetYaxis()->GetXmin();
  auto ymax = SF_hist->GetYaxis()->GetXmax();

  // make sure to stay within the range of the histograms
  pt = std::max(xmin + 0.1, pt);
  pt = std::min(xmax - 0.1, pt);
  eta = std::max(ymin + 0.1, eta);
  eta = std::min(ymax - 0.1, eta);

  // find bin in the scale factor histogram
  auto bin = SF_hist->FindBin(pt, eta);

  // calculate the scale factors
  SFs.at(0) = SF_hist->GetBinContent(bin);
  SFs.at(1) = (SF_hist->GetBinContent(bin)) + (SF_hist->GetBinError(bin));
  SFs.at(2) = (SF_hist->GetBinContent(bin)) - (SF_hist->GetBinError(bin));

  return SFs;
}

std::vector<float> SelectedLeptonProducer::GetMuonISOSF(
    const pat::Muon& iMuon, const MuonID& iMuonID,
    const MuonIsolation& iMuonIso) const {
  // get pt and eta of the electron
  auto pt = iMuon.pt();
  auto eta = abs(iMuon.eta());
  TH2F* SF_hist = nullptr;
  std::vector<float> SFs{1.0, 1.0, 1.0};
  // load the correct scale factor histogram
  switch (iMuonIso) {
    case MuonIsolation::None:
      break;
    case MuonIsolation::Loose:
      switch (iMuonID) {
        case MuonID::None:
          break;
        case MuonID::Loose:
          SF_hist = MuonISO_SF_LooseRelIso_LooseID;
          break;
        case MuonID::Medium:
          SF_hist = MuonISO_SF_LooseRelIso_MediumID;
          break;
        case MuonID::Tight:
          SF_hist = MuonISO_SF_LooseRelIso_TightID;
          break;
        default:
          std::cerr << "\n\nERROR: InvalidMuonID in GetMuonISOSF" << std::endl;
          throw std::exception();
      }
      break;
    case MuonIsolation::Medium:
      break;
    case MuonIsolation::Tight:
      switch (iMuonID) {
        case MuonID::None:
          break;
        case MuonID::Loose:
          break;
        case MuonID::Medium:
          SF_hist = MuonISO_SF_TightRelIso_MediumID;
          break;
        case MuonID::Tight:
          SF_hist = MuonISO_SF_TightRelIso_TightID;
          break;
        default:
          std::cerr << "\n\nERROR: InvalidMuonID in GetMuonISOSF" << std::endl;
          throw std::exception();
      }
      break;
    default:
      std::cerr << "\n\nERROR: InvalidMuonIsolation" << std::endl;
      throw std::exception();
  }

  if (SF_hist == nullptr) {
    std::cerr << "\n\nERROR: Muon Isolation Scale Factor could not be loaded"
              << std::endl;
    throw std::exception();
  }

  // determine the ranges of the given TH2Fs
  auto xmin = SF_hist->GetXaxis()->GetXmin();
  auto xmax = SF_hist->GetXaxis()->GetXmax();
  auto ymin = SF_hist->GetYaxis()->GetXmin();
  auto ymax = SF_hist->GetYaxis()->GetXmax();

  // make sure to stay within the range of the histograms
  pt = std::max(xmin + 0.1, pt);
  pt = std::min(xmax - 0.1, pt);
  eta = std::max(ymin + 0.1, eta);
  eta = std::min(ymax - 0.1, eta);

  // find bin in the scale factor histogram
  auto bin = SF_hist->FindBin(pt, eta);

  // calculate the scale factors
  SFs.at(0) = SF_hist->GetBinContent(bin);
  SFs.at(1) = (SF_hist->GetBinContent(bin)) + (SF_hist->GetBinError(bin));
  SFs.at(2) = (SF_hist->GetBinContent(bin)) - (SF_hist->GetBinError(bin));

  return SFs;
}

// ------------ method called once each job just before starting event loop
// ------------
void SelectedLeptonProducer::beginJob() {}

// ------------ method called once each job just after ending the event loop
// ------------
void SelectedLeptonProducer::endJob() {}

// ------------ method fills 'descriptions' with the allowed parameters for the
// module  ------------
void SelectedLeptonProducer::fillDescriptions(
    edm::ConfigurationDescriptions& descriptions) {
  // The following says we do not know what parameters are allowed so do no
  // validation
  // Please change this to state exactly what you do use, even if it is no
  // parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

// define this as a plug-in
DEFINE_FWK_MODULE(SelectedLeptonProducer);
