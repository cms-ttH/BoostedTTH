#include "BoostedTTH/Producers/interface/SelectedJetProducer.h"

SelectedJetProducer::SelectedJetProducer(const edm::ParameterSet &iConfig) : jetType{iConfig.getParameter<std::string>("JetType")},
                                                                             isData{iConfig.getParameter<bool>("isData")},
                                                                             ptMins{iConfig.getParameter<std::vector<double>>("ptMins")},
                                                                             etaMaxs{iConfig.getParameter<std::vector<double>>("etaMaxs")},
                                                                             leptonJetDr{iConfig.getParameter<double>("leptonJetDr")},
                                                                             applyCorrection{iConfig.getParameter<bool>("applyCorrection")},
                                                                             doJER{iConfig.getParameter<bool>("doJER")},
                                                                             collectionNames{iConfig.getParameter<std::vector<std::string>>("collectionNames")},
                                                                             PUJetIDMins{iConfig.getParameter<std::vector<std::string>>("PUJetIDMins")},
                                                                             JetID_{iConfig.getParameter<std::vector<std::string>>("JetID")},
                                                                             systematics_config{iConfig.getParameter<std::vector<std::string>>("systematics")},
                                                                             // inputs
                                                                             jetsToken{consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("jets"))},
                                                                             genjetsToken{consumes<reco::GenJetCollection>(iConfig.getParameter<edm::InputTag>("miniAODGenJets"))},
                                                                             muonsToken{consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muons"))},
                                                                             electronsToken{consumes<pat::ElectronCollection>(iConfig.getParameter<edm::InputTag>("electrons"))},
                                                                             rhoToken{consumes<double>(iConfig.getParameter<edm::InputTag>("rho"))},
                                                                             jecFileAK4_2016{iConfig.getParameter<std::string>("jecFileAK4_2016")},
                                                                             jecFileAK8_2016{iConfig.getParameter<std::string>("jecFileAK8_2016")},
                                                                             jecFileAK4_2017{iConfig.getParameter<std::string>("jecFileAK4_2017")},
                                                                             jecFileAK8_2017{iConfig.getParameter<std::string>("jecFileAK8_2017")},
                                                                             jecFileAK4_2018{iConfig.getParameter<std::string>("jecFileAK4_2018")},
                                                                             jecFileAK8_2018{iConfig.getParameter<std::string>("jecFileAK8_2018")},
                                                                             era{iConfig.getParameter<std::string>("era")}
{
  // do this for getJetCorrector call with JetType as argument, because it needs ak4... or ak8 ... instead of AK4... or AK8...
  if(jetType=="AK4PFCHS") JetType_ = JetType::AK4PFCHS;
  else if(jetType=="AK8PFCHS") JetType_ = JetType::AK8PFCHS;
  else {
      std::cerr << "\n\nERROR: Unknown Jet type " << jetType << std::endl;
      std::cerr << "Please select 'AK4PFCHS' or 'AK8PFCHS'\n" << std::endl;
      throw std::exception();
  }

  // make sure everything is consistent
  assert(ptMins.size() == etaMaxs.size());
  assert(ptMins.size() == collectionNames.size());
  assert(ptMins.size() == PUJetIDMins.size());
  assert(ptMins.size() == JetID_.size());

  // load systematics
  for (size_t i = 0; i < systematics_config.size(); i++)
  {
    try
    {
      systematics.push_back(SystematicsHelper::get(systematics_config.at(i)));
    }
    catch (cms::Exception &e)
    {
      throw cms::Exception("InvalidUncertaintyName") << "SelectedJetProducer: systematic name " << systematics_config.at(i) << " not recognized" << std::endl;
    }
  }

  // produce Jet collections
  produces<pat::JetCollection>("rawJets");
  for (size_t i = 0; i < collectionNames.size(); i++)
  {
    for (size_t j = 0; j < systematics.size(); j++)
    {
      produces<pat::JetCollection>(systName(collectionNames.at(i), systematics.at(j)));
    }
  }

  // set JEC File
  if (JetType_==JetType::AK4PFCHS)
  {
    jetTypeLabelForJECUncertainty = "AK4PFchs";
    // change File for 2016
    if (era.find("2016")!=std::string::npos){ 
      jecUncertaintyTxtFileName = std::string(getenv("CMSSW_BASE")) + "/src/BoostedTTH/Producers/data/jec/" + jecFileAK4_2016;
    }
    else if(era.find("2017")!=std::string::npos){ 
      jecUncertaintyTxtFileName = std::string(getenv("CMSSW_BASE")) + "/src/BoostedTTH/Producers/data/jec/" + jecFileAK4_2017;
    }
    else if(era.find("2018")!=std::string::npos){ 
      jecUncertaintyTxtFileName = std::string(getenv("CMSSW_BASE")) + "/src/BoostedTTH/Producers/data/jec/" + jecFileAK4_2018;
    }
  }
  else if (JetType_==JetType::AK8PFCHS)
  {
    jetTypeLabelForJECUncertainty = "AK8PFchs";
    // change File for 2016
    if (era.find("2016")!=std::string::npos){ 
      jecUncertaintyTxtFileName = std::string(getenv("CMSSW_BASE")) + "/src/BoostedTTH/Producers/data/jec/" + jecFileAK8_2016;
    }
    else if(era.find("2017")!=std::string::npos){ 
      jecUncertaintyTxtFileName = std::string(getenv("CMSSW_BASE")) + "/src/BoostedTTH/Producers/data/jec/" + jecFileAK8_2017;
    }
    else if(era.find("2018")!=std::string::npos){ 
      jecUncertaintyTxtFileName = std::string(getenv("CMSSW_BASE")) + "/src/BoostedTTH/Producers/data/jec/" + jecFileAK8_2018;
    }
  }

  if (jecUncertaintyTxtFileName != "")
  {
    if (!fileExists(jecUncertaintyTxtFileName))
    { // check if JEC uncertainty file exists
      throw cms::Exception("InvalidJECUncertaintyFile") << "No JEC uncertainty file '" << jecUncertaintyTxtFileName << "' found";
    }
  }
  else
  {
    throw cms::Exception("NoJECUncertaintyFile") << "No JEC uncertainty file specified";
  }
  
  PUJetID_WP = std::vector<PUJetIDWP>(PUJetIDMins.size(),PUJetIDWP::None);
  Jet_ID = std::vector<JetID>(JetID_.size(),JetID::None);
  //translate Jet_PUID
  for (size_t i = 0; i < PUJetIDMins.size(); i++)
  {
    //translate Jet_ID
    if (JetID_.at(i) == "none")
        Jet_ID.at(i) = JetID::None;
    else if (JetID_.at(i) == "loose")
        Jet_ID.at(i) = JetID::Loose;
    else if (JetID_.at(i) == "tight")
        Jet_ID.at(i) = JetID::Tight;
    else if (JetID_.at(i) == "tightlepveto")
        Jet_ID.at(i) = JetID::TightLepVeto;
    else
    {
        std::cerr << "\n\nERROR: No matching JetID found for: " << JetID_.at(i) << std::endl;
        throw std::exception();
    }  
      
    if (PUJetIDMins.at(i) == "none")
      PUJetID_WP.at(i)=PUJetIDWP::None;
    else if (PUJetIDMins.at(i) == "loose")
      PUJetID_WP.at(i)=PUJetIDWP::Loose;
    else if (PUJetIDMins.at(i) == "medium")
      PUJetID_WP.at(i)=PUJetIDWP::Medium;
    else if (PUJetIDMins.at(i) == "tight")
      PUJetID_WP.at(i)=PUJetIDWP::Tight;
    else
    {
      std::cerr << "\n\nERROR: No matching PUJetID_WP found for: " << PUJetIDMins.at(i) << std::endl;
      throw std::exception();
    }
  }
  
  if(JetType_ == JetType::AK4PFCHS) correctorlabel = "ak4PFchs";
  else if(JetType_ == JetType::AK8PFCHS) correctorlabel = "ak8PFchs";
  else {
        std::cerr << "\n\nERROR: Jet Type not recognized" << std::endl;
        throw std::exception();
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
template <typename T>
T SelectedJetProducer::GetSortedByPt(const T &collection) const
{
  T result = collection;
  std::sort(result.begin(), result.end(), [](typename T::value_type a, typename T::value_type b) { return ptr(a)->pt() > ptr(b)->pt(); });
  return result;
}

void SelectedJetProducer::UpdateJetCorrectorUncertainties(const edm::EventSetup &iSetup)
{
  for (auto &jecUncIt : jecUncertainties_)
  {
    jecUncIt.second.reset(CreateJetCorrectorUncertainty(iSetup, jetTypeLabelForJECUncertainty, jecUncIt.first));
  }
}

void SelectedJetProducer::AddJetCorrectorUncertainty(const edm::EventSetup &iSetup, const std::string &uncertaintyLabel)
{
  jecUncertainties_[uncertaintyLabel] = std::unique_ptr<JetCorrectionUncertainty>(CreateJetCorrectorUncertainty(iSetup, jetTypeLabelForJECUncertainty, uncertaintyLabel));
}

// function to generate JetCorrectionUncertainty
JetCorrectionUncertainty* SelectedJetProducer::CreateJetCorrectorUncertainty(const edm::EventSetup &iSetup,
                                                                             const std::string &jetTypeLabel,
                                                                             const std::string &uncertaintyLabel) const
{
  try
  {
    JetCorrectorParameters jetCorPar;
    if (jecUncertaintyTxtFileName != "")
    {
      if (uncertaintyLabel == "Uncertainty")
      { // this is the key in the database but not in txt...
        jetCorPar = JetCorrectorParameters(jecUncertaintyTxtFileName, "Total");
      }
      else
      {
        jetCorPar = JetCorrectorParameters(jecUncertaintyTxtFileName, uncertaintyLabel);
      }
    }
    else
    {
      edm::ESHandle<JetCorrectorParametersCollection> JetCorParColl;
      iSetup.get<JetCorrectionsRecord>().get(jetTypeLabel, JetCorParColl);
      //JetCorrectorParameters const & JetCorPar = (*JetCorParColl)[uncertaintyLabel];
      jetCorPar = (*JetCorParColl)[uncertaintyLabel];
    }
    return new JetCorrectionUncertainty(jetCorPar);
  }
  catch (cms::Exception &e)
  {
    throw cms::Exception("InvalidJECUncertaintyLabel") << "No JEC uncertainty with label '" << uncertaintyLabel << "' found in event setup";
  }
  return 0;
}

// function to return Jets, which fullfill all IDs
std::vector<pat::Jet> SelectedJetProducer::GetSelectedJets(const std::vector<pat::Jet> &inputJets,
                                                           const float iMinPt, const float iMaxAbsEta,
                                                           const JetID iJetID, const PUJetIDWP wp) const
{
  // iterate through inputjets and find good Jets
  std::vector<pat::Jet> selectedJets;
  for (const auto& jet: inputJets )
  {
    if (isGoodJet(jet, iMinPt, iMaxAbsEta, iJetID, wp))
    {
      selectedJets.push_back(jet);
    }
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
bool SelectedJetProducer::isGoodJet(const pat::Jet &iJet, const float iMinPt, const float iMaxAbsEta,
                                    const JetID iJetID, const PUJetIDWP wp) const
{

  // Transverse momentum requirement
  if (iJet.pt() < iMinPt) return false;

  // Absolute eta requirement
  if (fabs(iJet.eta()) > iMaxAbsEta) return false;

  // Jet ID
  bool passesID = iJet.isPFJet();
  
  if (not passesID) return false;

  switch (iJetID)
  {
  case JetID::Loose:
    passesID = iJet.neutralHadronEnergyFraction() < 0.99 && iJet.neutralEmEnergyFraction() < 0.99 && iJet.numberOfDaughters() > 1;
    if (fabs(iJet.eta()) < 2.4) passesID = passesID && (iJet.chargedHadronEnergyFraction() > 0.0 && iJet.chargedMultiplicity() > 0 && iJet.chargedEmEnergyFraction() < 0.99);
    break;
  case JetID::Tight:
    // works for 2016 tight ID (CHS and Puppi), 2017 tight ID (CHS and Puppi), and 2018 tight ID (CHS and Puppi). Only take this for jets with |eta|<=2.4, otherwise recheck!
    // passesID = iJet.neutralHadronEnergyFraction() < 0.90 && iJet.neutralEmEnergyFraction() < 0.90 && iJet.numberOfDaughters() > 1;
    // if (fabs(iJet.eta()) < 2.4) passesID = passesID && (iJet.chargedHadronEnergyFraction() > 0.0 && iJet.chargedMultiplicity() > 0);
    // if (era.find("2016") != std::string::npos) passesID = passesID && iJet.chargedEmEnergyFraction() < 0.99;
    if (era.find("2016") != std::string::npos)
    {
      if (fabs(iJet.eta()) <= 2.7){
        passesID = iJet.neutralHadronEnergyFraction() < 0.90 
                && iJet.neutralEmEnergyFraction() < 0.90 
                && iJet.numberOfDaughters() > 1;
        if (fabs(iJet.eta()) <= 2.4){
          passesID = passesID && iJet.chargedHadronEnergyFraction() > 0.0
                && iJet.chargedMultiplicity() > 0
                && iJet.neutralEmEnergyFraction() < 0.99;
        }
      }
      else if (2.7 < fabs(iJet.eta()) && fabs(iJet.eta()) <= 3.0){
        passesID = iJet.neutralEmEnergyFraction() > 0.01 
                && iJet.neutralHadronEnergyFraction() < 0.98 
                && iJet.neutralMultiplicity() > 2;
      }
      else if (fabs(iJet.eta()) > 3.0){
        passesID = iJet.neutralEmEnergyFraction() < 0.90 
                && iJet.neutralMultiplicity() > 10;
      }
    }

    if (era.find("2017") != std::string::npos)
    {
      if (fabs(iJet.eta()) <= 2.7){
        passesID = iJet.neutralHadronEnergyFraction() < 0.90 
                && iJet.neutralEmEnergyFraction() < 0.90 
                && iJet.numberOfDaughters() > 1;
        if (fabs(iJet.eta()) <= 2.4){
          passesID = passesID && iJet.chargedHadronEnergyFraction() > 0.0
                && iJet.chargedMultiplicity() > 0
                && iJet.neutralEmEnergyFraction() < 0.80;
        }
      }
      else if (2.7 < fabs(iJet.eta()) && fabs(iJet.eta()) <= 3.0){
        passesID = iJet.neutralEmEnergyFraction() > 0.02 
                && iJet.neutralEmEnergyFraction() < 0.99 
                && iJet.neutralMultiplicity() > 2;
      }
      else if (fabs(iJet.eta()) > 3.0){
        passesID = iJet.neutralEmEnergyFraction() < 0.90 
                && iJet.neutralHadronEnergyFraction() > 0.02
                && iJet.neutralMultiplicity() > 10;
      }
    }

    if (era.find("2018") != std::string::npos)
    {
      if (fabs(iJet.eta()) <= 2.6){
        passesID = iJet.neutralHadronEnergyFraction() < 0.90 
                && iJet.neutralEmEnergyFraction() < 0.90 
                && iJet.numberOfDaughters() > 1
                && iJet.chargedHadronEnergyFraction() > 0.0
                && iJet.chargedMultiplicity() > 0;

      }
      else if (2.6 < fabs(iJet.eta()) && fabs(iJet.eta()) <= 2.7){
        passesID = iJet.neutralHadronEnergyFraction() < 0.90 
                && iJet.neutralEmEnergyFraction() < 0.99 
                && iJet.chargedMultiplicity() > 0;
      }
      else if (2.7 < fabs(iJet.eta()) && fabs(iJet.eta()) <= 3.0){
        passesID = iJet.neutralEmEnergyFraction() > 0.02 
                && iJet.neutralEmEnergyFraction() < 0.99 
                && iJet.neutralMultiplicity() > 2;
      }
      else if (3.0 < fabs(iJet.eta()) && fabs(iJet.eta()) <= 5.0){
        passesID = iJet.neutralHadronEnergyFraction() > 0.2 
                && iJet.neutralEmEnergyFraction() < 0.9 
                && iJet.neutralMultiplicity() > 10 ;
      }
    }
    break;
  case JetID::TightLepVeto:
    // works for 2016 tight ID (CHS and Puppi), 2017 tight ID (CHS and Puppi), and 2018 tight ID (CHS and Puppi). Only take this for jets with |eta|<=2.4, otherwise recheck!
    // passesID = iJet.neutralHadronEnergyFraction() < 0.90 && iJet.neutralEmEnergyFraction() < 0.90 && iJet.muonEnergyFraction()<0.80 && iJet.numberOfDaughters() > 1;
    // if (fabs(iJet.eta()) < 2.4) passesID = passesID && (iJet.chargedHadronEnergyFraction() > 0.0 && iJet.chargedMultiplicity() > 0);
    // if (era.find("2016") != std::string::npos) passesID = passesID && iJet.chargedEmEnergyFraction() < 0.90;
    // else passesID = passesID && iJet.chargedEmEnergyFraction() < 0.80;
    if (era.find("2016") != std::string::npos)
    {
      if (fabs(iJet.eta()) <= 2.7){
        passesID = iJet.neutralHadronEnergyFraction() < 0.90 
                && iJet.neutralEmEnergyFraction() < 0.90 
                && iJet.numberOfDaughters() > 1
                && iJet.muonEnergyFraction() < 0.8;
        if (fabs(iJet.eta()) <= 2.4){
          passesID = passesID && iJet.chargedHadronEnergyFraction() > 0.0
                && iJet.chargedMultiplicity() > 0
                && iJet.neutralEmEnergyFraction() < 0.90;
        }
      }
      else if (2.7 < fabs(iJet.eta()) && fabs(iJet.eta()) <= 3.0){
        passesID = iJet.neutralEmEnergyFraction() > 0.01 
                && iJet.neutralHadronEnergyFraction() < 0.98 
                && iJet.neutralMultiplicity() > 2;
      }
      else if (fabs(iJet.eta()) > 3.0){
        passesID = iJet.neutralEmEnergyFraction() < 0.90 
                && iJet.neutralMultiplicity() > 10;
      }
    }


    if (era.find("2017") != std::string::npos)
    {
      if (fabs(iJet.eta()) <= 2.7){
        passesID = iJet.neutralHadronEnergyFraction() < 0.90 
                && iJet.neutralEmEnergyFraction() < 0.90 
                && iJet.numberOfDaughters() > 1
                && iJet.muonEnergyFraction() < 0.8;
        if (fabs(iJet.eta()) <= 2.4){
          passesID = passesID && iJet.chargedHadronEnergyFraction() > 0.0
                && iJet.chargedMultiplicity() > 0
                && iJet.neutralEmEnergyFraction() < 0.80
                && iJet.chargedEmEnergyFraction() < 0.8;
        }
      }
      else if (2.7 < fabs(iJet.eta()) && fabs(iJet.eta()) <= 3.0){
        passesID = iJet.neutralEmEnergyFraction() > 0.02 
                && iJet.neutralEmEnergyFraction() < 0.99 
                && iJet.neutralMultiplicity() > 2;
      }
      else if (fabs(iJet.eta()) > 3.0){
        passesID = iJet.neutralEmEnergyFraction() < 0.90 
                && iJet.neutralHadronEnergyFraction() > 0.02
                && iJet.neutralMultiplicity() > 10;
      }
    }

    if (era.find("2018") != std::string::npos)
    {
      if (fabs(iJet.eta()) <= 2.6){
        passesID = iJet.neutralHadronEnergyFraction() < 0.90 
                && iJet.neutralEmEnergyFraction() < 0.90 
                && iJet.numberOfDaughters() > 1
                && iJet.muonEnergyFraction() < 0.8
                && iJet.chargedHadronEnergyFraction() > 0.0
                && iJet.chargedMultiplicity() > 0
                && iJet.chargedEmEnergyFraction() < 0.8;

      }
      else if (2.6 < fabs(iJet.eta()) && fabs(iJet.eta()) <= 2.7){
        passesID = iJet.neutralHadronEnergyFraction() < 0.90 
                && iJet.neutralEmEnergyFraction() < 0.99 
                && iJet.muonEnergyFraction() < 0.8
                && iJet.chargedMultiplicity() > 0
                && iJet.chargedEmEnergyFraction() < 0.8;
      }
      else if (2.7 < fabs(iJet.eta()) && fabs(iJet.eta()) <= 3.0){
        passesID = iJet.neutralEmEnergyFraction() > 0.02 
                && iJet.neutralEmEnergyFraction() < 0.99 
                && iJet.neutralMultiplicity() > 2;
      }
      else if (3.0 < fabs(iJet.eta()) && fabs(iJet.eta()) <= 5.0){
        passesID = iJet.neutralHadronEnergyFraction() > 0.2 
                && iJet.neutralEmEnergyFraction() < 0.9 
                && iJet.neutralMultiplicity() > 10 ;
      }
    }
    break;
  case JetID::None:
    passesID = true;
    break;
  default:
    std::cerr << "\n\nERROR: Unknown Jet ID " << jetType << std::endl;
    std::cerr << "Please select 'loose' or 'tight'\n" << std::endl;
    throw std::exception();
    break;
  }
  
  if (not passesID) return false;
  
  // PileUP Jet ID
  if (iJet.hasUserInt("pileupJetId:fullId"))
  {
    if (iJet.userInt("pileupJetId:fullId") < TranslateJetPUIDtoInt(wp))
      return false;
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
std::vector<pat::Jet> SelectedJetProducer::GetUncorrectedJets(const std::vector<pat::Jet> &inputJets) const
{
  std::vector<pat::Jet> outputJets;
  outputJets.reserve(inputJets.size());
  // loop over inputJets and save a uncorrected version
  for (const auto& iJet: inputJets)
  {
    pat::Jet jet = iJet;
    jet.setP4(iJet.correctedJet(0).p4());
    outputJets.push_back(jet);
  }
  return outputJets;
}

// function to return Jets with no lepton inside a particular DeltaR
std::vector<pat::Jet> SelectedJetProducer::GetDeltaRCleanedJets(const std::vector<pat::Jet> &inputJets, const std::vector<pat::Muon> &inputMuons,
                                                                const std::vector<pat::Electron> &inputElectrons, const double deltaRCut) const
{
  std::vector<pat::Jet> outputJets; //resulting jets
  // loop over inputJets
  for (const auto &iJet: inputJets)
  {
    bool isOverlap = false;
    // get Jet 4-momentum
    TLorentzVector jet_p4;
    jet_p4.SetPxPyPzE(iJet.px(), iJet.py(), iJet.pz(), iJet.energy());
    // loop over all electrons
    for (const auto &iEle: inputElectrons)
    {
      // get electron 4-momentum
      TLorentzVector ele_p4;
      ele_p4.SetPxPyPzE(iEle.px(), iEle.py(), iEle.pz(), iEle.energy());
      //calculate DeltaR between Jet and electron
      double delta_tmp = jet_p4.DeltaR(ele_p4);
      if (delta_tmp < deltaRCut)
      { // check for overlap
        isOverlap = true;
        break;
      }
    }

    if (isOverlap)
      continue;

    // loop over all muons
    for (const auto &iMuon: inputMuons)
    {
      // get muon 4-momentum
      TLorentzVector muon_p4;
      muon_p4.SetPxPyPzE(iMuon.px(), iMuon.py(), iMuon.pz(), iMuon.energy());
      // calculate DeltaR between jet and electron
      double delta_tmp = jet_p4.DeltaR(muon_p4);
      if (delta_tmp < deltaRCut)
      { // check for overlap
        isOverlap = true;
        break;
      }
    }

    if (isOverlap)
      continue;

    // save Jet if no overlap is found
    outputJets.push_back(iJet);
  }
  return outputJets;
}

// function to return a vector of corrected Jets
std::vector<pat::Jet> SelectedJetProducer::GetCorrectedJets(const std::vector<pat::Jet> &inputJets, const edm::Event &event,
                                                            const edm::EventSetup &setup, const edm::Handle<reco::GenJetCollection> &genjets,
                                                            const SystematicsHelper::Type iSysType, const bool &doJES, const bool &doJER,
                                                            const float &corrFactor, const float &uncFactor)
{
  // do nothing if neither JES or JER is demanded
  if (!doJES && !doJER)
    return inputJets;

  //resulting corrected Jets
  std::vector<pat::Jet> outputJets;

  //loop over input jets and correct each one
  // for (std::vector<pat::Jet>::const_iterator it = inputJets.begin(), ed = inputJets.end(); it != ed; ++it)
  for (const auto& jet: inputJets)
  {
    outputJets.push_back(GetCorrectedJet(jet, event, setup, genjets, iSysType, doJES, doJER, corrFactor, uncFactor));
  }
  return outputJets;
}

// function to return one corrected Jet
pat::Jet SelectedJetProducer::GetCorrectedJet(const pat::Jet &inputJet, const edm::Event &event,
                                              const edm::EventSetup &setup, const edm::Handle<reco::GenJetCollection> &genjets,
                                              const SystematicsHelper::Type iSysType, const bool doJES, const bool doJER,
                                              const float corrFactor, const float uncFactor)
{
  double factor = 1.;
  pat::Jet outputJet = inputJet;
  bool addUserFloats = true;
  ApplyJetEnergyCorrection(outputJet, factor, event, setup, genjets, iSysType, doJES, doJER, addUserFloats, corrFactor, uncFactor);

  return outputJet;
}

// function to apply JES, JER needs to be implemente (is currently done via SmearedJetProducer)
void SelectedJetProducer::ApplyJetEnergyCorrection(pat::Jet &jet, double &totalCorrFactor, const edm::Event &event, const edm::EventSetup &setup,
                                                   const edm::Handle<reco::GenJetCollection> &genjets, const SystematicsHelper::Type iSysType,
                                                   const bool doJES, const bool doJER,
                                                   const bool addUserFloats,
                                                   const float corrFactor, const float uncFactor)
{
  totalCorrFactor = 1.;
  if (doJES || doJER)
  { // check again if JES or JER is demanded
    /// JES
    if (doJES)
    {
      double scale = 1.;
      if (corrector)
      {
        scale = corrector->correction(jet, event, setup);
      }
      else
      {
        edm::LogError("SelectedJetProducer") << "Trying to use GetCorrectedJets() without setting jet corrector!";
      }

      const double jec = scale * corrFactor;
      jet.scaleEnergy(jec);
      totalCorrFactor *= jec;

      if (addUserFloats)
      {
        jet.addUserFloat("HelperJES", scale);
        const double uncUp = GetJECUncertainty(jet, setup, SystematicsHelper::JESup);
        const double uncDown = GetJECUncertainty(jet, setup, SystematicsHelper::JESdown);
        const double jecvarUp = 1. + (uncUp);
        const double jecvarDown = 1. + (uncDown);
        jet.addUserFloat("HelperJESup", jecvarUp);
        jet.addUserFloat("HelperJESdown", jecvarDown);
      }

      if (SystematicsHelper::isJECUncertainty(iSysType))
      {
        const double unc = GetJECUncertainty(jet, setup, iSysType);
        const double jecvar = 1. + (unc * uncFactor);
        if (addUserFloats)
        {
          jet.addUserFloat("Helper" + SystematicsHelper::toString(iSysType), jecvar);
        }
        jet.scaleEnergy(jecvar);
        totalCorrFactor *= jecvar;
      }
      // implement on demand
      // if (doJER){
      //}
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
  auto jecUncIt = jecUncertainties_.find(uncertaintyLabel);
  if (jecUncIt == jecUncertainties_.end())
  { // Lazy initialization
    AddJetCorrectorUncertainty(iSetup, uncertaintyLabel);
    jecUncIt = jecUncertainties_.find(uncertaintyLabel);
  }
  JetCorrectionUncertainty *unc = jecUncIt->second.get();

  unc->setJetEta(jet.eta());
  unc->setJetPt(jet.pt()); // here you must use the CORRECTED jet pt
  if (SystematicsHelper::isJECUncertaintyUp(iSysType))
    return +1. * unc->getUncertainty(true);
  else
    return -1. * unc->getUncertainty(false);
}

// ------------ method called to produce the data  ------------
void SelectedJetProducer::produce(edm::Event &iEvent, const edm::EventSetup &iSetup)
{
  using namespace edm;
  UpdateJetCorrectorUncertainties(iSetup);

  edm::Handle<double> hRho;
  iEvent.getByToken(rhoToken, hRho);
  if (not hRho.isValid())
  {
    std::cerr << "\n\nERROR: retrieved pile-up energy density is not valid" << std::endl;
    throw std::exception();
  }

  edm::Handle<pat::JetCollection> inputJets;
  iEvent.getByToken(jetsToken, inputJets);
  if (not inputJets.isValid())
  {
    std::cerr << "\n\nERROR: retrieved jet collection is not valid" << std::endl;
    throw std::exception();
  }

  edm::Handle<reco::GenJetCollection> genJets;
  if (!isData)
  {
    iEvent.getByToken(genjetsToken, genJets);
    if (not genJets.isValid())
    {
      std::cerr << "\n\nERROR: retrieved genjet collection is not valid" << std::endl;
      throw std::exception();
    }
  }

  edm::Handle<pat::ElectronCollection> inputElectrons;
  iEvent.getByToken(electronsToken, inputElectrons);
  if (not inputElectrons.isValid())
  {
    std::cerr << "\n\nERROR: retrieved electron collection is not valid" << std::endl;
    throw std::exception();
  }

  edm::Handle<pat::MuonCollection> inputMuons;
  iEvent.getByToken(muonsToken, inputMuons);
  if (not inputMuons.isValid())
  {
    std::cerr << "\n\nERROR: retrieved muon collection is not valid" << std::endl;
    throw std::exception();
  }
  
  // initialize jetcorrector
  corrector = JetCorrector::getJetCorrector(correctorlabel + "L1L2L3", iSetup);
  

  // Get raw jets
  std::vector<pat::Jet> rawJets_general = GetSortedByPt(GetUncorrectedJets(*inputJets));
  std::unique_ptr<pat::JetCollection> rawJets_general_ = std::make_unique<pat::JetCollection>(rawJets_general);
  iEvent.put(std::move(rawJets_general_), "rawJets");

  for (size_t i = 0; i < ptMins.size(); i++)
  {
      // selected jets with jet ID cuts ( do this before jet energy correction !!! )
      const std::vector<pat::Jet> idJets = GetSelectedJets(*inputJets, 0., 9999., Jet_ID.at(i));
      
      for (size_t j = 0; j < systematics.size(); j++)
      {

        std::vector<pat::Jet> unsortedJets;
        if (applyCorrection)
        {
            
            std::vector<pat::Jet> rawJets = GetSortedByPt(GetUncorrectedJets(idJets));
            
            // Clean muons and electrons from jets
            std::vector<pat::Jet> cleanJets = GetDeltaRCleanedJets(rawJets, *inputMuons, *inputElectrons, leptonJetDr);
            // Apply jet corrections
            // Get genjets for new JER recommendation (JER is done in extra producer SmearedJetProducer, the manual JER application is therefore disabled doJER=false)
            
            unsortedJets = GetCorrectedJets(cleanJets, iEvent, iSetup, genJets, systematics.at(j), doJES, doJER);
            
        }
        // if no correction is to be applied, still remove jets close to a lepton
        else
        {
        
            unsortedJets = GetDeltaRCleanedJets(idJets, *inputMuons, *inputElectrons, leptonJetDr);
            
        }

        // loop over all jetcollections and each systematic and apply pt,eta as well as pujetid cut on them
        
            
        //Get jet Collection which passes selections
        std::vector<pat::Jet> selectedJets_unsorted = GetSelectedJets(unsortedJets, ptMins.at(i), etaMaxs.at(i), JetID::None, PUJetID_WP.at(i));
        // sort the selected jets with respect to pt
        std::unique_ptr<pat::JetCollection> selectedJets = std::make_unique<pat::JetCollection>(GetSortedByPt(selectedJets_unsorted));
        iEvent.put(std::move(selectedJets), systName(collectionNames.at(i), systematics.at(j)));
    }
  }
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
    SelectedJetProducer::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void SelectedJetProducer::endStream()
{
}

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

// ------------ method called when starting to processes a luminosity block  ------------
/*
void
SelectedJetProducer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
SelectedJetProducer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void SelectedJetProducer::fillDescriptions(edm::ConfigurationDescriptions &descriptions)
{
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(SelectedJetProducer);
