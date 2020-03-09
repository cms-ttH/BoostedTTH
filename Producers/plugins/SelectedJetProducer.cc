#include "BoostedTTH/Producers/interface/SelectedJetProducer.h"

SelectedJetProducer::SelectedJetProducer(const edm::ParameterSet &iConfig) :
    jetType{iConfig.getParameter< std::string >("JetType")},
    isData{iConfig.getParameter< bool >("isData")},
    ptMins{iConfig.getParameter< std::vector< double > >("ptMins")},
    etaMaxs{iConfig.getParameter< std::vector< double > >("etaMaxs")},
    leptonJetDr{iConfig.getParameter< double >("leptonJetDr")},
    applyCorrection{iConfig.getParameter< bool >("applyCorrection")},
    doDeltaRCleaning{iConfig.getParameter< bool >("doDeltaRCleaning")},
    isSubjetCollection{iConfig.getParameter< bool >("isSubjetCollection")},
    collectionNames{iConfig.getParameter< std::vector< std::string > >("collectionNames")},
    PUJetIDMins{iConfig.getParameter< std::vector< std::string > >("PUJetIDMins")},
    JetID_{iConfig.getParameter< std::vector< std::string > >("JetID")},
    systematics_config{iConfig.getParameter< std::vector< std::string > >("systematics")},
    jecFileAK4_2016{iConfig.getParameter< std::string >("jecFileAK4_2016")},
    jecFileAK8_2016{iConfig.getParameter< std::string >("jecFileAK8_2016")},
    jecFileAK15_2016{iConfig.getParameter< std::string >("jecFileAK15_2016")},
    jecFileAK4_2017{iConfig.getParameter< std::string >("jecFileAK4_2017")},
    jecFileAK8_2017{iConfig.getParameter< std::string >("jecFileAK8_2017")},
    jecFileAK15_2017{iConfig.getParameter< std::string >("jecFileAK15_2017")},
    jecFileAK4_2018{iConfig.getParameter< std::string >("jecFileAK4_2018")},
    jecFileAK8_2018{iConfig.getParameter< std::string >("jecFileAK8_2018")},
    jecFileAK15_2018{iConfig.getParameter< std::string >("jecFileAK15_2018")},
    era{iConfig.getParameter< std::string >("era")},
    // inputs
    jetsToken{consumes< pat::JetCollection >(iConfig.getParameter< edm::InputTag >("jets"))},
    muonsToken{consumes< pat::MuonCollection >(iConfig.getParameter< edm::InputTag >("muons"))},
    electronsToken{consumes< pat::ElectronCollection >(iConfig.getParameter< edm::InputTag >("electrons"))},
    photonsToken{consumes< pat::PhotonCollection >(iConfig.getParameter< edm::InputTag >("photons"))},
    rhoToken{consumes< double >(iConfig.getParameter< edm::InputTag >("rho"))}
{
    // make sure everything is consistent
    assert(ptMins.size() == etaMaxs.size());
    assert(ptMins.size() == collectionNames.size());
    assert(ptMins.size() == PUJetIDMins.size());
    assert(ptMins.size() == JetID_.size());

    // load systematics
    for (size_t i = 0; i < systematics_config.size(); i++) {
        try {
            systematics.push_back(SystematicsHelper::get(systematics_config.at(i)));
        }
        catch (cms::Exception &e) {
            throw cms::Exception("InvalidUncertaintyName")
                << "SelectedJetProducer: systematic name " << systematics_config.at(i) << " not recognized" << std::endl;
        }
    }

    // determine JetType
    JetType_ = TranslateJetTypeStringToEnum(jetType);

    // determine jes uncertainty label for given jet type
    jetTypeLabelForJECUncertainty = TranslateJetTypeToUncertaintyLabel(JetType_);

    // determine correct file for jes uncertainty
    jecUncertaintyTxtFileName = FindJESUncertaintyFile(JetType_);

    // do this for getJetCorrector call with JetType as argument, because it needs
    // ak4... or ak8 ... instead of AK4... or AK8...
    correctorlabel = TranslateJetTypeToCorrectorLabel(JetType_);

    // determine jet IDs and pu jet IDs
    PUJetID_WP = std::vector< PUJetIDWP >(PUJetIDMins.size(), PUJetIDWP::None);
    Jet_ID     = std::vector< JetID >(JetID_.size(), JetID::None);
    // translate Jet_PUID
    for (size_t i = 0; i < PUJetIDMins.size(); i++) {
        // translate Jet_ID
        Jet_ID.at(i) = TranslateJetIDStringToEnum(JetID_.at(i));
        // translate PU Jet_ID
        PUJetID_WP.at(i) = TranslatePUJetIDStringToEnum(PUJetIDMins.at(i));
    }

    // produce Jet collections
    produces< pat::JetCollection >("rawJets");
    for (size_t i = 0; i < collectionNames.size(); i++) {
        for (size_t j = 0; j < systematics.size(); j++) { produces< pat::JetCollection >(systName(collectionNames.at(i), systematics.at(j))); }
    }
}

SelectedJetProducer::~SelectedJetProducer()
{
    // do anything here that needs to be done at destruction time
    // (e.g. close files, deallocate resources etc.)
}

//
// member functions
//

// check if a given file exists
bool SelectedJetProducer::fileExists(const std::string &fileName) const
{
    std::ifstream infile(fileName.c_str());
    return infile.good();
}

// === Returned sorted input collection, by descending pT === //
template< typename T >
T SelectedJetProducer::GetSortedByPt(const T &collection) const
{
    T result = collection;
    std::sort(result.begin(), result.end(), [](typename T::value_type a, typename T::value_type b) { return ptr(a)->pt() > ptr(b)->pt(); });
    return result;
}

void SelectedJetProducer::UpdateJetCorrectorUncertainties(const edm::EventSetup &iSetup)
{
    for (auto &jecUncIt : jecUncertainties_) { jecUncIt.second.reset(CreateJetCorrectorUncertainty(iSetup, jetTypeLabelForJECUncertainty, jecUncIt.first)); }
}

void SelectedJetProducer::AddJetCorrectorUncertainty(const edm::EventSetup &iSetup, const std::string &uncertaintyLabel)
{
    jecUncertainties_[uncertaintyLabel] =
        std::unique_ptr< JetCorrectionUncertainty >(CreateJetCorrectorUncertainty(iSetup, jetTypeLabelForJECUncertainty, uncertaintyLabel));
}

// function to generate JetCorrectionUncertainty
JetCorrectionUncertainty *SelectedJetProducer::CreateJetCorrectorUncertainty(const edm::EventSetup &iSetup, const std::string &jetTypeLabel,
                                                                             const std::string &uncertaintyLabel) const
{
    try {
        JetCorrectorParameters jetCorPar;
        if (jecUncertaintyTxtFileName != "") {
            if (uncertaintyLabel == "Uncertainty") {  // this is the key in the database but not in txt...
                jetCorPar = JetCorrectorParameters(jecUncertaintyTxtFileName, "Total");
            }
            else {
                jetCorPar = JetCorrectorParameters(jecUncertaintyTxtFileName, uncertaintyLabel);
            }
        }
        else {
            edm::ESHandle< JetCorrectorParametersCollection > JetCorParColl;
            iSetup.get< JetCorrectionsRecord >().get(jetTypeLabel, JetCorParColl);
            // JetCorrectorParameters const & JetCorPar =
            // (*JetCorParColl)[uncertaintyLabel];
            jetCorPar = (*JetCorParColl)[uncertaintyLabel];
        }
        return new JetCorrectionUncertainty(jetCorPar);
    }
    catch (cms::Exception &e) {
        throw cms::Exception("InvalidJECUncertaintyLabel") << "No JEC uncertainty with label '" << uncertaintyLabel << "' found in event setup";
    }
    return 0;
}

// function to return Jets, which fullfill all IDs
std::vector< pat::Jet > SelectedJetProducer::GetSelectedJets(const std::vector< pat::Jet > &inputJets, const float iMinPt, const float iMaxAbsEta,
                                                             const JetID iJetID, const PUJetIDWP wp) const
{
    // iterate through inputjets and find good Jets
    std::vector< pat::Jet > selectedJets;
    for (const auto &jet : inputJets) {
        if (isGoodJet(jet, iMinPt, iMaxAbsEta, iJetID, wp)) { selectedJets.push_back(jet); }
    }
    return selectedJets;
}

// return Systematic name
std::string SelectedJetProducer::systName(std::string name, SystematicsHelper::Type sysType) const
{
    if (sysType == SystematicsHelper::NA)
        return name;
    else
        return name + SystematicsHelper::toString(sysType);
}

// function to check if Jet FullFills IDs
bool SelectedJetProducer::isGoodJet(const pat::Jet &iJet, const float iMinPt, const float iMaxAbsEta, const JetID iJetID, const PUJetIDWP wp) const
{
    // Transverse momentum requirement
    if (iJet.pt() < iMinPt) return false;

    // Absolute eta requirement
    if (fabs(iJet.eta()) > iMaxAbsEta) return false;

    if (isSubjetCollection) return true;
    // Jet ID
    bool passesID = iJet.isPFJet();

    if (not passesID) return false;

    float multiplicity = iJet.hasUserFloat("patPuppiJetSpecificProducer:puppiMultiplicity") ? iJet.userFloat("patPuppiJetSpecificProducer:puppiMultiplicity")
                                                                                            : iJet.numberOfDaughters();
    float neutral_multiplicity = iJet.hasUserFloat("patPuppiJetSpecificProducer:neutralPuppiMultiplicity")
                                     ? iJet.userFloat("patPuppiJetSpecificProducer:neutralPuppiMultiplicity")
                                     : iJet.neutralMultiplicity();
    float charged_multiplicity =
        (iJet.hasUserFloat("patPuppiJetSpecificProducer:puppiMultiplicity") && iJet.hasUserFloat("patPuppiJetSpecificProducer:neutralPuppiMultiplicity"))
            ? (multiplicity - neutral_multiplicity)
            : iJet.chargedMultiplicity();

    // std::cout << "puppi charged multiplicity " << charged_multiplicity << std::endl;
    // std::cout << "puppi neutral multiplicity " << neutral_multiplicity << std::endl;
    // std::cout << "charged multiplicity " << iJet.chargedMultiplicity() << std::endl;
    // std::cout << "neutral multiplicity " << iJet.neutralMultiplicity() << std::endl;
    // std::cout << " num const 1 " << multiplicity << std::endl;
    // std::cout << " num const 2 " << iJet.numberOfDaughters() << std::endl;

    switch (iJetID) {
        case JetID::Loose:
            passesID = (iJet.neutralHadronEnergyFraction() < 0.99) && (iJet.neutralEmEnergyFraction() < 0.99) && (multiplicity > 1);
            if (fabs(iJet.eta()) < 2.4) {
                passesID = passesID && (iJet.chargedHadronEnergyFraction() > 0.0) && (iJet.chargedEmEnergyFraction() < 0.99) && (charged_multiplicity > 0);
            }
            break;
        case JetID::Tight:
            // works for 2016 tight ID (CHS and Puppi), 2017 tight ID (CHS and Puppi), and 2018 tight ID (CHS and Puppi). Only take this for jets with
            // |eta|<=2.4, otherwise recheck!
            passesID = (iJet.neutralHadronEnergyFraction() < 0.90) && (iJet.neutralEmEnergyFraction() < 0.90) && (multiplicity > 1);
            if (fabs(iJet.eta()) < 2.4) { passesID = passesID && (iJet.chargedHadronEnergyFraction() > 0.0) && (charged_multiplicity > 0); }
            if (era.find("2016") != std::string::npos) passesID = passesID && (iJet.chargedEmEnergyFraction() < 0.99);
            break;
        case JetID::TightLepVeto:
            // works for 2016 tight ID (CHS and Puppi), 2017 tight ID (CHS and Puppi), and 2018 tight ID (CHS and Puppi). Only take this for jets with
            // |eta|<=2.4, otherwise recheck!
            passesID = (iJet.neutralHadronEnergyFraction() < 0.90) && (iJet.neutralEmEnergyFraction() < 0.90) && (iJet.muonEnergyFraction() < 0.80) &&
                       (multiplicity > 1);
            if (fabs(iJet.eta()) < 2.4) { passesID = passesID && (iJet.chargedHadronEnergyFraction() > 0.0) && (charged_multiplicity > 0); }
            if (era.find("2016") != std::string::npos)
                passesID = passesID && (iJet.chargedEmEnergyFraction() < 0.90);
            else
                passesID = passesID && (iJet.chargedEmEnergyFraction() < 0.80);
            break;
        case JetID::None: passesID = true; break;
        default:
            std::cerr << "\n\nERROR: Unknown Jet ID " << jetType << std::endl;
            std::cerr << "Please select 'loose' or 'tight'\n" << std::endl;
            throw std::exception();
            break;
    }

    if (not passesID) return false;

    // PileUP Jet ID
    if (iJet.hasUserInt("pileupJetId:fullId") && iJet.pt() < 50) {
        if (iJet.userInt("pileupJetId:fullId") < TranslateJetPUIDtoInt(wp)) return false;
    }

    return true;
}

// function to Translate PUJetIDWP into its corresponding int
int SelectedJetProducer::TranslateJetPUIDtoInt(PUJetIDWP wp) const
{
    if (wp == PUJetIDWP::Loose)
        return 4;
    else if (wp == PUJetIDWP::Medium)
        return 6;
    else if (wp == PUJetIDWP::Tight)
        return 7;
    else
        return 0;
}

// function to return Jets without any correction
std::vector< pat::Jet > SelectedJetProducer::GetUncorrectedJets(const std::vector< pat::Jet > &inputJets) const
{
    std::vector< pat::Jet > outputJets;
    outputJets.reserve(inputJets.size());
    // loop over inputJets and save a uncorrected version
    for (const auto &iJet : inputJets) {
        pat::Jet jet = iJet;
        jet.setP4(iJet.correctedJet(0).p4());
        outputJets.push_back(jet);
    }
    return outputJets;
}

// function to return Jets with no lepton inside a particular DeltaR
std::vector< pat::Jet > SelectedJetProducer::GetDeltaRCleanedJets(const std::vector< pat::Jet > &inputJets, const std::vector< pat::Muon > &inputMuons,
                                                                  const std::vector< pat::Electron > &inputElectrons,
                                                                  const std::vector< pat::Photon > &inputPhotons, const double deltaRCut) const
{
    std::vector< pat::Jet > outputJets;  // resulting jets
    // loop over inputJets
    for (const auto &iJet : inputJets) {
        bool isOverlap = false;
        // loop over all electrons
        for (const auto &iEle : inputElectrons) {
            // calculate DeltaR between Jet and electron
            if (reco::deltaR(iJet.p4(), iEle.p4()) < deltaRCut) {  // check for overlap
                isOverlap = true;
                break;
            }
        }

        if (isOverlap) continue;

        // loop over all muons
        for (const auto &iMuon : inputMuons) {
            // calculate DeltaR between jet and electron
            if (reco::deltaR(iJet.p4(), iMuon.p4()) < deltaRCut) {  // check for overlap
                isOverlap = true;
                break;
            }
        }

        if (isOverlap) continue;

        for (const auto &iPho : inputPhotons) {
            // calculate DeltaR between Jet and electron
            if (reco::deltaR(iJet.p4(), iPho.p4()) < deltaRCut) {  // check for overlap
                isOverlap = true;
                break;
            }
        }

        if (isOverlap) continue;

        // save Jet if no overlap is found
        outputJets.push_back(iJet);
    }
    return outputJets;
}

// function to return a vector of corrected Jets
std::vector< pat::Jet > SelectedJetProducer::GetCorrectedJets(const std::vector< pat::Jet > &inputJets, const edm::Event &event, const edm::EventSetup &setup,
                                                              const SystematicsHelper::Type iSysType, const bool &doJES, const float &corrFactor,
                                                              const float &uncFactor)
{
    // do nothing if JES is not demanded
    if (!doJES) return inputJets;

    // resulting corrected Jets
    std::vector< pat::Jet > outputJets;

    // loop over input jets and correct each one
    // for (std::vector<pat::Jet>::const_iterator it = inputJets.begin(), ed =
    // inputJets.end(); it != ed; ++it)
    for (const auto &jet : inputJets) { outputJets.push_back(GetCorrectedJet(jet, event, setup, iSysType, doJES, corrFactor, uncFactor)); }
    return outputJets;
}

// function to return one corrected Jet
pat::Jet SelectedJetProducer::GetCorrectedJet(const pat::Jet &inputJet, const edm::Event &event, const edm::EventSetup &setup,
                                              const SystematicsHelper::Type iSysType, const bool doJES, const float corrFactor, const float uncFactor)
{
    double   factor        = 1.;
    pat::Jet outputJet     = inputJet;
    bool     addUserFloats = true;
    ApplyJetEnergyCorrection(outputJet, factor, event, setup, iSysType, doJES, addUserFloats, corrFactor, uncFactor);

    return outputJet;
}

// function to apply JES
void SelectedJetProducer::ApplyJetEnergyCorrection(pat::Jet &jet, double &totalCorrFactor, const edm::Event &event, const edm::EventSetup &setup,
                                                   const SystematicsHelper::Type iSysType, const bool doJES, const bool addUserFloats, const float corrFactor,
                                                   const float uncFactor)
{
    totalCorrFactor = 1.;
    if (doJES) {  // check again if JES is demanded
        /// JES
        if (doJES) {
            double scale = 1.;
            if (corrector) { scale = corrector->correction(jet, event, setup); }
            else {
                edm::LogError("SelectedJetProducer") << "Trying to use GetCorrectedJets() without setting jet "
                                                        "corrector!";
            }

            const double jec = scale * corrFactor;
            jet.scaleEnergy(jec);
            totalCorrFactor *= jec;

            if (addUserFloats) {
                jet.addUserFloat("HelperJES", scale);
                const double uncUp      = GetJECUncertainty(jet, setup, SystematicsHelper::JESup);
                const double uncDown    = GetJECUncertainty(jet, setup, SystematicsHelper::JESdown);
                const double jecvarUp   = 1. + (uncUp);
                const double jecvarDown = 1. + (uncDown);
                jet.addUserFloat("HelperJESup", jecvarUp);
                jet.addUserFloat("HelperJESdown", jecvarDown);
            }

            if (SystematicsHelper::isJECUncertainty(iSysType)) {
                const double unc    = GetJECUncertainty(jet, setup, iSysType);
                const double jecvar = 1. + (unc * uncFactor);
                if (addUserFloats) { jet.addUserFloat("Helper" + SystematicsHelper::toString(iSysType), jecvar); }
                jet.scaleEnergy(jecvar);
                totalCorrFactor *= jecvar;
            }
        }
    }
}

// Return the JEC uncertainty value
// Scale JES by (1+value) to apply uncertainty
// Note: for JEC down, value will internally be multiplied by -1
// --> *always* scale JES by (1+value).
double SelectedJetProducer::GetJECUncertainty(const pat::Jet &jet, const edm::EventSetup &iSetup, const SystematicsHelper::Type iSysType)
{
    const std::string uncertaintyLabel = SystematicsHelper::GetJECUncertaintyLabel(iSysType);
    auto              jecUncIt         = jecUncertainties_.find(uncertaintyLabel);
    if (jecUncIt == jecUncertainties_.end()) {  // Lazy initialization
        AddJetCorrectorUncertainty(iSetup, uncertaintyLabel);
        jecUncIt = jecUncertainties_.find(uncertaintyLabel);
    }
    JetCorrectionUncertainty *unc = jecUncIt->second.get();

    unc->setJetEta(jet.eta());
    unc->setJetPt(jet.pt());  // here you must use the CORRECTED jet pt
    if (SystematicsHelper::isJECUncertaintyUp(iSysType))
        return +1. * unc->getUncertainty(true);
    else
        return -1. * unc->getUncertainty(false);
}

// ------------ method called to produce the data  ------------
void SelectedJetProducer::produce(edm::Event &iEvent, const edm::EventSetup &iSetup)
{
    // using namespace edm;
    UpdateJetCorrectorUncertainties(iSetup);

    // get some necessary input data from the event

    edm::Handle< double > hRho;
    iEvent.getByToken(rhoToken, hRho);
    if (not hRho.isValid()) {
        std::cerr << "\n\nERROR: retrieved pile-up energy density is not valid" << std::endl;
        throw std::exception();
    }

    edm::Handle< pat::JetCollection > inputJets;
    iEvent.getByToken(jetsToken, inputJets);
    if (not inputJets.isValid()) {
        std::cerr << "\n\nERROR: retrieved jet collection is not valid" << std::endl;
        throw std::exception();
    }

    edm::Handle< pat::ElectronCollection > inputElectrons;
    iEvent.getByToken(electronsToken, inputElectrons);
    if (not inputElectrons.isValid()) {
        std::cerr << "\n\nERROR: retrieved electron collection is not valid" << std::endl;
        throw std::exception();
    }

    edm::Handle< pat::MuonCollection > inputMuons;
    iEvent.getByToken(muonsToken, inputMuons);
    if (not inputMuons.isValid()) {
        std::cerr << "\n\nERROR: retrieved muon collection is not valid" << std::endl;
        throw std::exception();
    }

    edm::Handle< pat::PhotonCollection > inputPhotons;
    iEvent.getByToken(photonsToken, inputPhotons);
    if (not inputPhotons.isValid()) {
        std::cerr << "\n\nERROR: retrieved photon collection is not valid" << std::endl;
        throw std::exception();
    }

    // initialize jetcorrector which returns the nominal jes corrections
    corrector = JetCorrector::getJetCorrector(correctorlabel + "L1L2L3", iSetup);

    // get raw jets and put them into the event
    std::vector< pat::Jet >               rawJets_general  = GetSortedByPt(GetUncorrectedJets(*inputJets));
    std::unique_ptr< pat::JetCollection > rawJets_general_ = std::make_unique< pat::JetCollection >(rawJets_general);
    iEvent.put(std::move(rawJets_general_), "rawJets");

    // loop over the requested output jet collections
    for (size_t i = 0; i < ptMins.size(); i++) {
        // select jets with jet ID cuts (do this before jet energy correction !!!)
        std::vector< pat::Jet > idJets = GetSelectedJets(*inputJets, 0., 9999., Jet_ID.at(i));

        // clean muons and electrons and photons from jets
        std::vector< pat::Jet > cleanJets = doDeltaRCleaning ? GetDeltaRCleanedJets(idJets, *inputMuons, *inputElectrons, *inputPhotons, leptonJetDr) : idJets;

        // these numbers are added as userfloats because they change after the jet energy corrections
        // but the values only make sense before the jet energy corrections
        for (auto &jet : cleanJets) {
            if (!jet.hasUserFloat("neutralHadronEnergyFraction") && !jet.hasUserFloat("chargedHadronEnergyFraction") && !isSubjetCollection) {
                jet.addUserFloat("neutralHadronEnergyFraction", jet.neutralHadronEnergyFraction());
                jet.addUserFloat("chargedHadronEnergyFraction", jet.chargedHadronEnergyFraction());
                jet.addUserFloat("neutralElectromagneticEnergyFraction", jet.neutralEmEnergyFraction());
                jet.addUserFloat("muonEnergyFraction", jet.muonEnergyFraction());
                jet.addUserFloat("chargedElectromagneticEnergyFraction", jet.chargedEmEnergyFraction());
            }
        }

        // loop over the requested JES systematics
        for (size_t j = 0; j < systematics.size(); j++) {
            std::vector< pat::Jet > unsortedJets;

            // apply jet energy corrections or not
            if (applyCorrection) {
                // uncorrect the previous jet energy corrections before applying new ones
                std::vector< pat::Jet > rawJets = GetUncorrectedJets(cleanJets);

                // apply jet corrections
                unsortedJets = GetCorrectedJets(rawJets, iEvent, iSetup, systematics.at(j), doJES);
            }
            else {
                unsortedJets = cleanJets;
            }

            // apply pt,eta cuts as well as pujetid cut but no jetid cut because it was already done
            std::vector< pat::Jet > selectedJets_unsorted = GetSelectedJets(unsortedJets, ptMins.at(i), etaMaxs.at(i), JetID::None, PUJetID_WP.at(i));

            // sort the selected jets with respect to pt
            std::unique_ptr< pat::JetCollection > selectedJets = std::make_unique< pat::JetCollection >(GetSortedByPt(selectedJets_unsorted));

            // put the selected jets into the event
            iEvent.put(std::move(selectedJets), systName(collectionNames.at(i), systematics.at(j)));
        }
    }
}

SelectedJetProducer::JetType SelectedJetProducer::TranslateJetTypeStringToEnum(const std::string jet_type_str) const
{
    JetType jet_type_enum;
    if (jet_type_str == "AK4PFCHS")
        jet_type_enum = JetType::AK4PFCHS;
    else if (jet_type_str == "AK4PFPUPPI")
        jet_type_enum = JetType::AK4PFPUPPI;
    else if (jet_type_str == "AK8PFCHS")
        jet_type_enum = JetType::AK8PFCHS;
    else if (jet_type_str == "AK8PFPUPPI")
        jet_type_enum = JetType::AK8PFPUPPI;
    else if (jet_type_str == "AK15PFPUPPI")
        jet_type_enum = JetType::AK15PFPUPPI;
    else {
        std::cerr << "\n\nERROR: Unknown Jet type " << jet_type_str << std::endl;
        std::cerr << "Please select 'AK4PFCHS/PUPPI' or 'AK8PFCHS/PUPPI' or 'AK15PFPUPPI'\n" << std::endl;
        throw std::exception();
    }
    return jet_type_enum;
}

std::string SelectedJetProducer::TranslateJetTypeToCorrectorLabel(const JetType jet_type_enum) const
{
    std::string corrector_label = "";
    if (jet_type_enum == JetType::AK4PFCHS)
        corrector_label = "ak4PFchs";
    else if (jet_type_enum == JetType::AK4PFPUPPI)
        corrector_label = "ak4PFPuppi";
    else if (jet_type_enum == JetType::AK8PFCHS)
        corrector_label = "ak8PFchs";
    else if (jet_type_enum == JetType::AK8PFPUPPI)
        corrector_label = "ak8PFPuppi";
    else if (jet_type_enum == JetType::AK15PFPUPPI)
        corrector_label = "ak8PFPuppi";
    else {
        std::cerr << "\n\nERROR: Jet Type not recognized" << std::endl;
        throw std::exception();
    }
    return corrector_label;
}

std::string SelectedJetProducer::TranslateJetTypeToUncertaintyLabel(const JetType jet_type_enum) const
{
    std::string uncertainty_label = "";
    if (jet_type_enum == JetType::AK4PFCHS) { uncertainty_label = "AK4PFchs"; }
    else if (jet_type_enum == JetType::AK4PFPUPPI) {
        uncertainty_label = "AK4PFPuppi";
    }
    else if (jet_type_enum == JetType::AK8PFCHS) {
        uncertainty_label = "AK8PFchs";
    }
    else if (jet_type_enum == JetType::AK8PFPUPPI) {
        uncertainty_label = "AK8PFPuppi";
    }
    else if (jet_type_enum == JetType::AK15PFPUPPI) {
        uncertainty_label = "AK8PFPuppi";
    }
    else {
        std::cerr << "\n\nERROR: Jet Type not recognized" << std::endl;
        throw std::exception();
    }
    return uncertainty_label;
}

std::string SelectedJetProducer::FindJESUncertaintyFile(const JetType jettype) const
{
    // set JEC File
    std::string jes_uncertainty_file = "";
    if (jettype == JetType::AK4PFCHS) {
        // change File for 2016
        if (era.find("2016") != std::string::npos) {
            jes_uncertainty_file = std::string(getenv("CMSSW_BASE")) + "/src/BoostedTTH/Producers/data/jec/" + jecFileAK4_2016;
        }
        else if (era.find("2017") != std::string::npos) {
            jes_uncertainty_file = std::string(getenv("CMSSW_BASE")) + "/src/BoostedTTH/Producers/data/jec/" + jecFileAK4_2017;
        }
        else if (era.find("2018") != std::string::npos) {
            jes_uncertainty_file = std::string(getenv("CMSSW_BASE")) + "/src/BoostedTTH/Producers/data/jec/" + jecFileAK4_2018;
        }
    }
    else if (jettype == JetType::AK4PFPUPPI) {
        // change File for 2016
        if (era.find("2016") != std::string::npos) {
            jes_uncertainty_file = std::string(getenv("CMSSW_BASE")) + "/src/BoostedTTH/Producers/data/jec/" + jecFileAK4_2016;
        }
        else if (era.find("2017") != std::string::npos) {
            jes_uncertainty_file = std::string(getenv("CMSSW_BASE")) + "/src/BoostedTTH/Producers/data/jec/" + jecFileAK4_2017;
        }
        else if (era.find("2018") != std::string::npos) {
            jes_uncertainty_file = std::string(getenv("CMSSW_BASE")) + "/src/BoostedTTH/Producers/data/jec/" + jecFileAK4_2018;
        }
    }
    else if (jettype == JetType::AK8PFCHS) {
        // change File for 2016
        if (era.find("2016") != std::string::npos) {
            jes_uncertainty_file = std::string(getenv("CMSSW_BASE")) + "/src/BoostedTTH/Producers/data/jec/" + jecFileAK8_2016;
        }
        else if (era.find("2017") != std::string::npos) {
            jes_uncertainty_file = std::string(getenv("CMSSW_BASE")) + "/src/BoostedTTH/Producers/data/jec/" + jecFileAK8_2017;
        }
        else if (era.find("2018") != std::string::npos) {
            jes_uncertainty_file = std::string(getenv("CMSSW_BASE")) + "/src/BoostedTTH/Producers/data/jec/" + jecFileAK8_2018;
        }
    }
    else if (jettype == JetType::AK8PFPUPPI) {
        // change File for 2016
        if (era.find("2016") != std::string::npos) {
            jes_uncertainty_file = std::string(getenv("CMSSW_BASE")) + "/src/BoostedTTH/Producers/data/jec/" + jecFileAK8_2016;
        }
        else if (era.find("2017") != std::string::npos) {
            jes_uncertainty_file = std::string(getenv("CMSSW_BASE")) + "/src/BoostedTTH/Producers/data/jec/" + jecFileAK8_2017;
        }
        else if (era.find("2018") != std::string::npos) {
            jes_uncertainty_file = std::string(getenv("CMSSW_BASE")) + "/src/BoostedTTH/Producers/data/jec/" + jecFileAK8_2018;
        }
    }
    else if (jettype == JetType::AK15PFPUPPI) {
        // change File for 2016
        if (era.find("2016") != std::string::npos) {
            jes_uncertainty_file = std::string(getenv("CMSSW_BASE")) + "/src/BoostedTTH/Producers/data/jec/" + jecFileAK15_2016;
        }
        else if (era.find("2017") != std::string::npos) {
            jes_uncertainty_file = std::string(getenv("CMSSW_BASE")) + "/src/BoostedTTH/Producers/data/jec/" + jecFileAK15_2017;
        }
        else if (era.find("2018") != std::string::npos) {
            jes_uncertainty_file = std::string(getenv("CMSSW_BASE")) + "/src/BoostedTTH/Producers/data/jec/" + jecFileAK15_2018;
        }
    }

    if (jes_uncertainty_file != "") {
        if (!fileExists(jes_uncertainty_file)) {  // check if JEC uncertainty
                                                  // file exists
            throw cms::Exception("InvalidJECUncertaintyFile") << "No JEC uncertainty file '" << jes_uncertainty_file << "' found";
        }
    }
    else {
        throw cms::Exception("NoJECUncertaintyFile") << "No JEC uncertainty file specified";
    }
    return jes_uncertainty_file;
}

SelectedJetProducer::JetID SelectedJetProducer::TranslateJetIDStringToEnum(const std::string jet_id_str) const
{
    JetID jet_id_enum;
    if (jet_id_str == "none")
        jet_id_enum = JetID::None;
    else if (jet_id_str == "loose")
        jet_id_enum = JetID::Loose;
    else if (jet_id_str == "tight")
        jet_id_enum = JetID::Tight;
    else if (jet_id_str == "tightlepveto")
        jet_id_enum = JetID::TightLepVeto;
    else {
        std::cerr << "\n\nERROR: No matching JetID found for: " << jet_id_str << std::endl;
        throw std::exception();
    }
    return jet_id_enum;
}

SelectedJetProducer::PUJetIDWP SelectedJetProducer::TranslatePUJetIDStringToEnum(const std::string pu_jet_id_str) const
{
    PUJetIDWP pu_jet_id_enum;
    if (pu_jet_id_str == "none")
        pu_jet_id_enum = PUJetIDWP::None;
    else if (pu_jet_id_str == "loose")
        pu_jet_id_enum = PUJetIDWP::Loose;
    else if (pu_jet_id_str == "medium")
        pu_jet_id_enum = PUJetIDWP::Medium;
    else if (pu_jet_id_str == "tight")
        pu_jet_id_enum = PUJetIDWP::Tight;
    else {
        std::cerr << "\n\nERROR: No matching PUJetID_WP found for: " << pu_jet_id_str << std::endl;
        throw std::exception();
    }
    return pu_jet_id_enum;
}

// ------------ method called once each stream before processing any runs, lumis
// or events  ------------
void SelectedJetProducer::beginStream(edm::StreamID) {}

// ------------ method called once each stream after processing all runs, lumis
// and events  ------------
void SelectedJetProducer::endStream() {}

// ------------ method called when starting to processes a run  ------------
/*
void
SelectedJetProducer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void
SelectedJetProducer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block
// ------------
/*
void
SelectedJetProducer::beginLuminosityBlock(edm::LuminosityBlock const&,
edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block
// ------------
/*
void
SelectedJetProducer::endLuminosityBlock(edm::LuminosityBlock const&,
edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the
// module  ------------
void SelectedJetProducer::fillDescriptions(edm::ConfigurationDescriptions &descriptions)
{
    // The following says we do not know what parameters are allowed so do no
    // validation
    // Please change this to state exactly what you do use, even if it is no
    // parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
}

// define this as a plug-in
DEFINE_FWK_MODULE(SelectedJetProducer);
