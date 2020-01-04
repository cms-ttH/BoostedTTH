
// -*- C++ -*-

//
// Package:    BoostedTTH/BoostedAnalyzer
// Class:      BoostedAnalyzer
//
/**\class BoostedAnalyzer BoostedAnalyzer.cc
 BoostedTTH/BoostedAnalyzer/plugins/BoostedAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shawn Williamson, Hannes Mildner
//
//
//

// system include files
#include <memory>
#include <vector>
#include <map>
#include <fstream>

#include "TStopwatch.h"

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/MakerMacros.h"

//#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"
#include "DataFormats/METReco/interface/HcalNoiseSummary.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/Common/interface/View.h"
//#include "JetMETCorrections/Objects/interface/JetCorrector.h"

#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"
#include "MiniAOD/MiniAODHelper/interface/CSVHelper.h"
//#include "MiniAOD/MiniAODHelper/interface/LeptonSFHelper.h"

#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/InputCollections.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/Cutflow.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TreeWriter.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenWeights.hpp"

#include "BoostedTTH/BoostedAnalyzer/interface/HistoReweighter.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/PUWeights.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/FilterInfo.hpp"

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/LeptonSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/LeptonSelection_QCDControlregion.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/LooseLeptonSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonMassSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/METSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/JetTagSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/VertexSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/FilterSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/EvenOddSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/HbbSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/METSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopDLSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopSLSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopFHSelection.hpp"

#include "BoostedTTH/BoostedAnalyzer/interface/WeightProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/MCMatchVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedMCMatchVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/AdditionalJetProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BasicVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/essentialBasicVarProcessor.hpp"
//#include "BoostedTTH/BoostedAnalyzer/interface/MVAVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/StdTopVarProcessor.hpp"
//#include "BoostedTTH/BoostedAnalyzer/interface/BDTVarProcessor.hpp"
//#include "BoostedTTH/BoostedAnalyzer/interface/DNNVarProcessor.hpp"
//#include "BoostedTTH/BoostedAnalyzer/interface/essentialMVAVarProcessor.hpp"
//#include "BoostedTTH/BoostedAnalyzer/interface/essentialRecoVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/essentialMCMatchVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedJetVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedAk4VarProcessor.hpp"
//#include "BoostedTTH/BoostedAnalyzer/interface/ttHVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DiJetVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/EventInfo.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenDarkMatterEvent.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DarkMatterProcessor.hpp"
//#include "BoostedTTH/BoostedAnalyzer/interface/Synchronizer.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonJetTagSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonMETSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TriggerVarProcessor.hpp"
//#include "BoostedTTH/BoostedAnalyzer/interface/ReconstructionMEvarProcessor.hpp"
//#include "BoostedTTH/BoostedAnalyzer/interface/TTbarReconstructionVarProcessor.hpp"
//#include "BoostedTTH/BoostedAnalyzer/interface/SpinCorrelationProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenJetOrderedJetCollectionProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/Ak4Cluster.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/SlimmedNtuples.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/ResourceMonitor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TTBBStudienProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/AK8JetProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/SelectionTagProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/MonoTopSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/PhotonVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/JetVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/LeptonVarProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BosonWeightProcessor.hpp"

//
// class declaration
//

class BoostedAnalyzer : public edm::EDAnalyzer {
   public:
    explicit BoostedAnalyzer(const edm::ParameterSet&);
    ~BoostedAnalyzer();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
    virtual void beginJob() override;
    virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;
    virtual void beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup) override;
    virtual void endRun(edm::Run const& iRun, edm::EventSetup const& iSetup) override;
    virtual void beginLuminosityBlock(edm::LuminosityBlock const& iBlock, edm::EventSetup const& iSetup) override;

    float GetTopPtWeight(const float& toppt1, const float& toppt2);

    std::map< string, float > GetWeights(const GenEventInfoProduct& genEventInfo, const LHEEventProduct& lheInfo, const EventInfo& eventInfo,
                                         const reco::VertexCollection& selectedPVs, const std::vector< pat::Electron >& selectedElectrons,
                                         const std::vector< pat::Muon >& selectedMuons, const GenTopEvent& genTopEvt);

    std::map< string, float > GetCSVWeights(const std::vector< pat::Jet >& selectedJets, const Systematics::Type& systype = Systematics::NA);

    static std::string outfileName(const std::string& basename, const Systematics::Type& sysType);
    static std::string systName(const Systematics::Type& sysType);

    // -------------------------------------------------------------------
    // --------------------------- member data ---------------------------
    // -------------------------------------------------------------------

    // --------------- HELPERS/PRODUCERS ---------------
    /** the miniAODhelper is used for selections and reweighting */
    MiniAODHelper helper;
    /** the csv reweighter calculates the event weight from b-tag reweightung */
    CSVHelper csvReweighter;
    // calculate the scalefactor for leptons
    // LeptonSFHelper leptonSFhelper;
    // reweight the number of primary vertices distribution
    PUWeights puWeights;
    /** Class that tests objects and event selections */
    // Synchronizer synchronizer;
    /** class to extract generator weights */
    GenWeights genweights;
    /** produces MC truth information for ttbar and ttH samples (genTopEvent)*/
    GenTopEventProducer genTopEvtProd;
    /** produces trigger information */
    TriggerInfoProducer triggerInfoProd;
    /** produces filter information */
    FilterInfoProducer filterInfoProd;

    // resource monitor
    std::unique_ptr< ResourceMonitor > ResMon = nullptr;

    // --------------- FLAGS ---------------
    /** is analyzed sample data? */
    bool isData;
    // Whats the dataEra
    std::string era;
    /** use fat jets? this is only possible if the miniAOD contains them */
    bool useFatJets;
    /** dump some event content for newer synchronization */
    bool dumpSyncExe;
    bool dumpExtended;
    /** Calculated MEM for "boosted" events? Takes several seconds per event */
    bool doBoostedMEM;
    /** produce ntuples for mem calculation?*/
    bool ProduceMemNtuples;
    /** use GenBmatching info? this is only possible if the miniAOD contains
     * them
     */
    bool useGenHadronMatch;
    /** use tagging for selections **/
    bool taggingSelection;
    bool dogenweights;

    // --------------- MISCELLANEOUS ---------------
    /** event weight:  xs*lumi/(nPosEvents-nNegEvents) */
    double             eventWeight;
    std::vector< int > dumpAlwaysEvents;
    /** which generator was used on ME level for this sample? */
    std::string usedGenerator;
    /** base name for outfiles (incl path)**/
    std::string outfileNameBase;
    /** generator systematics weigths (pdf, ME scale, etc) */
    /** triggers that are checked (independtend of the ones used for selected)*/
    std::vector< std::string > relevantTriggers;
    /** processors run */
    std::vector< std::string > processorNames;
    /** selections applied */
    std::vector< std::string > selectionNames;
    /** writes flat trees  */
    std::vector< std::unique_ptr< TreeWriter > > treewriters;
    /** stores cutflows*/
    std::vector< Cutflow > cutflows;
    /** selections that are applied before writing the tree*/
    std::vector< std::unique_ptr< Selection > > selections;
    /** outfile base names*/
    std::vector< std::string > outfileNames;
    /** stops the time spent in every processor*/
    /** systematics */
    std::vector< Systematics::Type > jetSystematics;

    // --------------- TOKENS ---------------
    /** pu summary data access token **/
    edm::EDGetTokenT< std::vector< PileupSummaryInfo > > puInfoToken;
    /** pileup density data access token **/
    edm::EDGetTokenT< double > rhoToken;
    /** hcal noise data access token **/
    edm::EDGetTokenT< HcalNoiseSummary > hcalNoiseToken;
    /** beam spot data access token **/
    edm::EDGetTokenT< reco::BeamSpot > beamSpotToken;
    /** Conversions data access token **/
    edm::EDGetTokenT< reco::ConversionCollection > conversionCollectionToken;
    /** vertex data access token **/
    edm::EDGetTokenT< reco::VertexCollection > primaryVerticesToken;
    /** tight muons data access token **/
    edm::EDGetTokenT< std::vector< pat::Muon > > selectedMuonsToken;
    /** medium muons data access token **/
    edm::EDGetTokenT< std::vector< pat::Muon > > selectedMuonsDLToken;
    /** loose muons data access token **/
    edm::EDGetTokenT< std::vector< pat::Muon > > selectedMuonsLooseToken;
    /** tight electrons data access token **/
    edm::EDGetTokenT< pat::ElectronCollection > selectedElectronsToken;
    /** medium electrons data access token **/
    edm::EDGetTokenT< pat::ElectronCollection > selectedElectronsDLToken;
    /** loose electrons data access token **/
    edm::EDGetTokenT< pat::ElectronCollection > selectedElectronsLooseToken;
    /** photon collection **/
    edm::EDGetTokenT< pat::PhotonCollection > selectedPhotonsToken;
    /** loose photon collection **/
    edm::EDGetTokenT< pat::PhotonCollection > selectedPhotonsLooseToken;
    /** loose jets data access token **/
    std::vector< edm::EDGetTokenT< std::vector< pat::Jet > > > selectedJetsTokens;
    /** tight jets data access token **/
    std::vector< edm::EDGetTokenT< std::vector< pat::Jet > > > selectedJetsLooseTokens;
    /** AK8Jet jets data access token **/
    std::vector< edm::EDGetTokenT< std::vector< pat::Jet > > > selectedJetsAK8_Tokens;
    /** AK15Jet jets data access token **/
    std::vector< edm::EDGetTokenT< std::vector< pat::Jet > > > selectedJetsAK15_Tokens;
    /** mets data access token **/
    std::vector< edm::EDGetTokenT< std::vector< pat::MET > > > correctedMETsTokens;
    /** puppi mets data access token **/
    std::vector< edm::EDGetTokenT< std::vector< pat::MET > > > correctedMETsPuppiTokens;
    /** gen info data access token **/
    edm::EDGetTokenT< GenEventInfoProduct > genInfoToken;
    /** LHE data access token **/
    edm::EDGetTokenT< LHEEventProduct > lheInfoToken;
    /** LHE data access token **/
    edm::EDGetTokenT< LHEEventProduct > lheInfoToken_source;
    /** gen particles data access token **/
    edm::EDGetTokenT< std::vector< reco::GenParticle > > genParticlesToken;
    /** gen jets data access token **/
    edm::EDGetTokenT< std::vector< reco::GenJet > > genJetsToken;
    // LHERunInfo data access token
    edm::EDGetTokenT< LHERunInfoProduct > LHERunInfoToken;
    edm::EDGetTokenT< LHERunInfoProduct > LHERunInfoToken_source;

    /** time counter */
    TStopwatch watch;
    /** Event counter */
    int eventcount;
    /** variable to holt the position of JetTagSelection in selections vector,
     * for later use */
    uint jet_tag_pos;
    /** map for selectiontags**/
    std::map< std::string, int > selectionTags;
};

//
// constructors and destructor
//
BoostedAnalyzer::BoostedAnalyzer(const edm::ParameterSet& iConfig) :
    // initialize some helpers with consumes collector (allows to access data
    // from file within this class)
    // leptonSFhelper{iConfig},
    // synchronizer{iConfig, consumesCollector()},
    genTopEvtProd{consumesCollector()},
    triggerInfoProd{iConfig, consumesCollector()},
    filterInfoProd{iConfig, consumesCollector()},

    // get all configurations from the python config
    // meaning of the parameters is explained in python/BoostedAnalyzer_cfi.py

    isData{iConfig.getParameter< bool >("isData")},
    era{iConfig.getParameter< std::string >("dataEra")},
    useFatJets{iConfig.getParameter< bool >("useFatJets")},
    dumpSyncExe{iConfig.getParameter< bool >("dumpSyncExe")},
    dumpExtended{iConfig.getParameter< bool >("dumpExtended")},
    doBoostedMEM{iConfig.getParameter< bool >("doBoostedMEM")},
    ProduceMemNtuples{iConfig.getParameter< bool >("memNtuples")},
    useGenHadronMatch{iConfig.getParameter< bool >("useGenHadronMatch")},
    taggingSelection{iConfig.getParameter< bool >("taggingSelection")},

    eventWeight{iConfig.getParameter< double >("eventWeight")},
    dumpAlwaysEvents{iConfig.getParameter< std::vector< int > >("dumpAlwaysEvents")},
    usedGenerator{iConfig.getParameter< std::string >("generatorName")},
    outfileNameBase{iConfig.getParameter< std::string >("outfileName")},
    relevantTriggers{iConfig.getParameter< std::vector< std::string > >("relevantTriggers")},
    processorNames{iConfig.getParameter< std::vector< std::string > >("processorNames")},
    selectionNames{iConfig.getParameter< std::vector< std::string > >("selectionNames")},

    puInfoToken{consumes< std::vector< PileupSummaryInfo > >(iConfig.getParameter< edm::InputTag >("puInfo"))},
    rhoToken{consumes< double >(iConfig.getParameter< edm::InputTag >("rho"))},
    hcalNoiseToken{consumes< HcalNoiseSummary >(iConfig.getParameter< edm::InputTag >("hcalNoise"))},
    beamSpotToken{consumes< reco::BeamSpot >(iConfig.getParameter< edm::InputTag >("beamSpot"))},
    conversionCollectionToken{consumes< reco::ConversionCollection >(iConfig.getParameter< edm::InputTag >("conversionCollection"))},
    primaryVerticesToken{consumes< reco::VertexCollection >(iConfig.getParameter< edm::InputTag >("primaryVertices"))},
    selectedMuonsToken{consumes< std::vector< pat::Muon > >(iConfig.getParameter< edm::InputTag >("selectedMuons"))},
    selectedMuonsDLToken{consumes< std::vector< pat::Muon > >(iConfig.getParameter< edm::InputTag >("selectedMuonsDL"))},
    selectedMuonsLooseToken{consumes< std::vector< pat::Muon > >(iConfig.getParameter< edm::InputTag >("selectedMuonsLoose"))},
    selectedElectronsToken{consumes< pat::ElectronCollection >(iConfig.getParameter< edm::InputTag >("selectedElectrons"))},
    selectedElectronsDLToken{consumes< pat::ElectronCollection >(iConfig.getParameter< edm::InputTag >("selectedElectronsDL"))},
    selectedElectronsLooseToken{consumes< pat::ElectronCollection >(iConfig.getParameter< edm::InputTag >("selectedElectronsLoose"))},
    selectedPhotonsToken{consumes< pat::PhotonCollection >(iConfig.getParameter< edm::InputTag >("selectedPhotons"))},
    selectedPhotonsLooseToken{consumes< pat::PhotonCollection >(iConfig.getParameter< edm::InputTag >("selectedPhotonsLoose"))},

    genInfoToken{consumes< GenEventInfoProduct >(iConfig.getParameter< edm::InputTag >("genInfo"))},
    lheInfoToken{consumes< LHEEventProduct >(iConfig.getParameter< edm::InputTag >("lheInfo"))},
    lheInfoToken_source{consumes< LHEEventProduct >(iConfig.getParameter< edm::InputTag >("lheInfo_source"))},
    genParticlesToken{consumes< std::vector< reco::GenParticle > >(iConfig.getParameter< edm::InputTag >("genParticles"))},
    genJetsToken{consumes< std::vector< reco::GenJet > >(iConfig.getParameter< edm::InputTag >("genJets"))},
    LHERunInfoToken{consumes< LHERunInfoProduct, edm::InRun >(edm::InputTag("externalLHEProducer"))},
    LHERunInfoToken_source{consumes< LHERunInfoProduct, edm::InRun >(edm::InputTag("source"))}

{
    // set up resource monitor
    ResMon.reset(new ResourceMonitor());

    if (isData) useGenHadronMatch = false;

    std::vector< std::string > systematicsNames = iConfig.getParameter< std::vector< std::string > >("systematics");

    for (auto const& s : systematicsNames) { jetSystematics.push_back(Systematics::get(s)); }

    for (auto const& s : jetSystematics) { outfileNames.push_back(outfileName(outfileNameBase, s)); }

    // REGISTER DATA ACCESS
    // This needs to be done in the constructor of this class or via the
    // consumes collector in the constructor of helper classes

    for (const auto& tag : iConfig.getParameter< std::vector< edm::InputTag > >("selectedJets")) {
        selectedJetsTokens.push_back(consumes< std::vector< pat::Jet > >(tag));
    }
    for (const auto& tag : iConfig.getParameter< std::vector< edm::InputTag > >("selectedJetsLoose")) {
        selectedJetsLooseTokens.push_back(consumes< std::vector< pat::Jet > >(tag));
    }
    for (const auto& tag : iConfig.getParameter< std::vector< edm::InputTag > >("selectedJetsAK8")) {
        selectedJetsAK8_Tokens.push_back(consumes< std::vector< pat::Jet > >(tag));
    }
    for (const auto& tag : iConfig.getParameter< std::vector< edm::InputTag > >("selectedJetsAK15")) {
        selectedJetsAK15_Tokens.push_back(consumes< std::vector< pat::Jet > >(tag));
    }
    for (const auto& tag : iConfig.getParameter< std::vector< edm::InputTag > >("correctedMETs")) {
        correctedMETsTokens.push_back(consumes< std::vector< pat::MET > >(tag));
    }
    for (const auto& tag : iConfig.getParameter< std::vector< edm::InputTag > >("correctedMETsPuppi")) {
        correctedMETsPuppiTokens.push_back(consumes< std::vector< pat::MET > >(tag));
    }

    // initialize helper classes
    helper.SetUp("2015_74x", isData ? -1 : 1, analysisType::LJ, isData);

    // initialize CSV reweighter
    if (iConfig.existsAs< edm::ParameterSet >("bTagSFs", true)) {
        const edm::ParameterSet bTagSFsPS = iConfig.getParameter< edm::ParameterSet >("bTagSFs");
        csvReweighter.init(bTagSFsPS.getParameter< std::string >("fileNameHF"), bTagSFsPS.getParameter< std::string >("fileNameLF"),
                           bTagSFsPS.getParameter< int >("nHFPtBins"), bTagSFsPS.getParameter< int >("nLFPtBins"), bTagSFsPS.getParameter< int >("nLFEtaBins"),
                           jetSystematics);
        if (bTagSFsPS.existsAs< bool >("AllowJetsOutOfBinning", true)) {
            csvReweighter.allowJetsOutOfBinning(bTagSFsPS.getParameter< bool >("AllowJetsOutOfBinning"));
        }
    }

    // INITIALIZE PU WEIGHTS
    puWeights.init(iConfig);

    // initialize cutflows
    for (size_t i = 0; i < jetSystematics.size(); i++) {
        cutflows.emplace_back();
        cutflows.back().Init();
    }

    // initialize selections
    // add requested selections
    for (const auto& itSel : selectionNames) {
        cout << "Initializing " << itSel << endl;
        std::unique_ptr< Selection > selection = nullptr;
        if (itSel == "VertexSelection")
            selection.reset(new VertexSelection());
        else if (itSel == "FilterSelection")
            selection.reset(new FilterSelection(iConfig));
        else if (itSel == "METSelection")
            selection.reset(new METSelection(iConfig));
        else if (itSel == "MonoTopSelection")
            selection.reset(new MonoTopSelection(iConfig));
        else if (itSel == "LeptonSelection")
            selection.reset(new LeptonSelection(iConfig));
        else if (itSel == "JetTagSelection")
            selection.reset(new JetTagSelection(iConfig));
        else if (itSel == "EvenSelection")
            selection.reset(new EvenOddSelection(true));
        else if (itSel == "OddSelection")
            selection.reset(new EvenOddSelection(false));
        else if (itSel == "GenTopFHSelection")
            selection.reset(new GenTopFHSelection());
        else if (itSel == "GenTopSLSelection")
            selection.reset(new GenTopSLSelection());
        else if (itSel == "GenTopDLSelection")
            selection.reset(new GenTopDLSelection());
        else if (itSel == "LeptonSelection_QCDControlregion")
            selection.reset(new LeptonSelection_QCDControlregion(iConfig));
        else if (itSel == "LooseLeptonSelection")
            selection.reset(new LooseLeptonSelection(iConfig));
        else if (itSel == "DiLeptonJetTagSelection")
            selection.reset(new DiLeptonJetTagSelection(iConfig));
        else if (itSel == "DiLeptonSelection")
            selection.reset(new DiLeptonSelection(iConfig));
        else if (itSel == "MinDiLeptonMassSelection")
            selection.reset(new DiLeptonMassSelection(20., 9999.));
        else if (itSel == "ZVetoSelection")
            selection.reset(new DiLeptonMassSelection(76., 106, true, false));
        else if (itSel == "ZWindowSelection")
            selection.reset(new DiLeptonMassSelection(76., 106, false));
        else if (itSel == "DiLeptonMETSelection")
            selection.reset(new DiLeptonMETSelection(iConfig));
        else if (itSel == "HbbSelection")
            selection.reset(new HbbSelection());
        else if (itSel == "4JetSelection")
            selection.reset(new JetTagSelection(4, -1));
        else if (itSel == "2TagSelection")
            selection.reset(new JetTagSelection(-1, 2));
        else {
            cout << "No matching selection found for: " << itSel << endl;
            continue;
        }
        selections.push_back(std::move(selection));
        // connect added selection to cutflow
        for (auto& c : cutflows) { selections.back()->InitCutflow(c); }
        // dump some event info after selection step
    }
    // find the position of the JetTagSelection to check later if the failed
    // selection is the JetTagSelection or not
    jet_tag_pos = find(selectionNames.begin(), selectionNames.end(), "JetTagSelection") - selectionNames.begin();

    // initialize synchronizer
    // if (dumpSyncExe) { synchronizer.Init(outfileNameBase, systematicsNames, iConfig, &helper, &leptonSFhelper, dumpExtended); }

    // INITIALIZE TREEWRITERs
    if (!ProduceMemNtuples) {
        for (size_t i = 0; i < jetSystematics.size(); i++) {
            cout << "creating tree writer " << outfileNames[i] << endl;
            std::unique_ptr< TreeWriter > treewriter(new TreeWriter());
            treewriters.push_back(std::move(treewriter));
            treewriters.back()->Init(outfileNames[i]);
        }
    }
    else {
        cout << "creating tree writer "
             << "slimmed_ntuples" << endl;
        std::unique_ptr< TreeWriter > treewriter(new TreeWriter());
        treewriters.push_back(std::move(treewriter));
        treewriters.back()->Init(outfileNameBase + "_slimmed_ntuples");
    }
    // add processors to first tree writer
    cout << "using processors:" << endl;
    for (const auto& itPro : processorNames) { cout << itPro << endl; }
    // add processors that have been requested in the config
    for (auto& treewriter : treewriters) {
        if (std::find(processorNames.begin(), processorNames.end(), "WeightProcessor") != processorNames.end()) {
            treewriter->AddTreeProcessor(new WeightProcessor(), "WeightProcessor");
        }
        if (std::find(processorNames.begin(), processorNames.end(), "BasicVarProcessor") != processorNames.end()) {
            treewriter->AddTreeProcessor(new BasicVarProcessor(), "BasicVarProcessor");
        }
        if (std::find(processorNames.begin(), processorNames.end(), "essentialBasicVarProcessor") != processorNames.end()) {
            treewriter->AddTreeProcessor(new essentialBasicVarProcessor(), "essentialBasicVarProcessor");
        }
        //if (std::find(processorNames.begin(), processorNames.end(), "essentialRecoVarProcessor") != processorNames.end()) {
            //treewriter->AddTreeProcessor(new essentialRecoVarProcessor(), "essentialRecoVarProcessor");
        //}
        if (std::find(processorNames.begin(), processorNames.end(), "PhotonVarProcessor") != processorNames.end()) {
            treewriter->AddTreeProcessor(new PhotonVarProcessor(), "PhotonVarProcessor");
        }
        if (std::find(processorNames.begin(), processorNames.end(), "JetVarProcessor") != processorNames.end()) {
            treewriter->AddTreeProcessor(new JetVarProcessor(), "JetVarProcessor");
        }
        if (std::find(processorNames.begin(), processorNames.end(), "LeptonVarProcessor") != processorNames.end()) {
            treewriter->AddTreeProcessor(new LeptonVarProcessor(), "LeptonVarProcessor");
        }
        if (std::find(processorNames.begin(), processorNames.end(), "DarkMatterProcessor") != processorNames.end()) {
            treewriter->AddTreeProcessor(new DarkMatterProcessor(), "DarkMatterProcessor");
        }
        if (std::find(processorNames.begin(), processorNames.end(), "BosonWeightProcessor") != processorNames.end()) {
            treewriter->AddTreeProcessor(new BosonWeightProcessor(era), "BosonWeightProcessor");
        }
        //if (std::find(processorNames.begin(), processorNames.end(), "essentialMVAVarProcessor") != processorNames.end()) {
            //if (std::find(processorNames.begin(), processorNames.end(), "essentialBasicVarProcessor") == processorNames.end()) {
                //cout << "adding essentialBasicVarProcessor, needed for "
                //        "essentialMVAVarProcessor"
                //     << endl;
                //treewriter->AddTreeProcessor(new essentialBasicVarProcessor(), "essentialBasicVarProcessor");
            //}
            //treewriter->AddTreeProcessor(new essentialMVAVarProcessor(), "essentialMVAVarProcessor");
        //}
        if (std::find(processorNames.begin(), processorNames.end(), "StdTopVarProcessor") != processorNames.end()) {
            treewriter->AddTreeProcessor(new StdTopVarProcessor(), "StdTopVarProcessor");
        }
        if (std::find(processorNames.begin(), processorNames.end(), "MCMatchVarProcessor") != processorNames.end()) {
            treewriter->AddTreeProcessor(new MCMatchVarProcessor(), "MCMatchVarProcessor");
        }
        if (std::find(processorNames.begin(), processorNames.end(), "essentialMCMatchVarProcessor") != processorNames.end()) {
            treewriter->AddTreeProcessor(new essentialMCMatchVarProcessor(), "essentialMCMatchVarProcessor");
        }
        if (std::find(processorNames.begin(), processorNames.end(), "AdditionalJetProcessor") != processorNames.end()) {
            treewriter->AddTreeProcessor(new AdditionalJetProcessor(), "AdditionalJetProcessor");
        }
        if (std::find(processorNames.begin(), processorNames.end(), "DiLeptonVarProcessor") != processorNames.end()) {
            treewriter->AddTreeProcessor(new DiLeptonVarProcessor(), "DiLeptonVarProcessor");
        }
        if (std::find(processorNames.begin(), processorNames.end(), "TriggerVarProcessor") != processorNames.end()) {
            treewriter->AddTreeProcessor(new TriggerVarProcessor(relevantTriggers), "TriggerVarProcessor");
        }
        //if (std::find(processorNames.begin(), processorNames.end(), "TTbarReconstructionVarProcessor") != processorNames.end()) {
            //treewriter->AddTreeProcessor(new TTbarReconstructionVarProcessor(), "TTbarReconstructionVarProcessor");
        //}
        //if (std::find(processorNames.begin(), processorNames.end(), "ReconstructionMEvarProcessor") != processorNames.end()) {
            //treewriter->AddTreeProcessor(new ReconstructionMEvarProcessor(), "ReconstructionMEvarProcessor");
        //}
        //if (std::find(processorNames.begin(), processorNames.end(), "SpinCorrelationProcessor") != processorNames.end()) {
            //treewriter->AddTreeProcessor(new SpinCorrelationProcessor(), "SpinCorrelationProcessor");
        //}
        if (std::find(processorNames.begin(), processorNames.end(), "GenJetOrderedJetCollectionProcessor") != processorNames.end()) {
            treewriter->AddTreeProcessor(new GenJetOrderedJetCollectionProcessor, "GenJetOrderedJetCollectionProcessor");
        }
        if (std::find(processorNames.begin(), processorNames.end(), "TTBBStudienProcessor") != processorNames.end()) {
            treewriter->AddTreeProcessor(new TTBBStudienProcessor, "TTBBStudienProcessor");
        }
        if (std::find(processorNames.begin(), processorNames.end(), "SlimmedNtuples") != processorNames.end()) {
            treewriter->AddTreeProcessor(new SlimmedNtuples(), "SlimmedNtuples");
        }
        if (std::find(processorNames.begin(), processorNames.end(), "AK8JetProcessor") != processorNames.end()) {
            treewriter->AddTreeProcessor(new AK8JetProcessor(&helper), "AK8JetProcessor");
        }
        if (std::find(processorNames.begin(), processorNames.end(), "SelectionTagProcessor") != processorNames.end()) {
            treewriter->AddTreeProcessor(new SelectionTagProcessor(), "SelectionTagProcessor");
        }
    }

    std::vector< std::string > pdfs = {"NNPDF31_nnlo_hessian_pdfas"};
    genweights.initLHAPDF(pdfs);

    assert(selectedJetsTokens.size() == selectedJetsLooseTokens.size());
    assert(selectedJetsTokens.size() == jetSystematics.size());
    assert(selectedJetsTokens.size() == selectedJetsAK8_Tokens.size());
    assert(selectedJetsTokens.size() == selectedJetsAK15_Tokens.size());
    assert(selectedJetsTokens.size() == correctedMETsTokens.size());
    assert(selectedJetsTokens.size() == correctedMETsPuppiTokens.size());
    assert(selectedJetsTokens.size() == cutflows.size());
}

BoostedAnalyzer::~BoostedAnalyzer()
{
    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)
    // DNNClassifierBase::pyFinalize();
}

//
// member functions
//

// ------------ method called for each event  ------------
void BoostedAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    if (eventcount < 20 || eventcount % 1000 == 0) {
        cout << "Analyzing event " << eventcount << endl;
        watch.Print();
        watch.Continue();
        ResMon->PrintMemoryUsage();
        ResMon->PrintSystemMemory();
    }

    eventcount++;

    // EVENTINFO
    edm::Handle< std::vector< PileupSummaryInfo > > h_puInfo;
    iEvent.getByToken(puInfoToken, h_puInfo);
    edm::Handle< double > h_rho;
    iEvent.getByToken(rhoToken, h_rho);
    edm::Handle< HcalNoiseSummary > h_hcalNoiseSummary;
    iEvent.getByToken(hcalNoiseToken, h_hcalNoiseSummary);
    edm::Handle< reco::BeamSpot > h_beamSpot;
    iEvent.getByToken(beamSpotToken, h_beamSpot);
    edm::Handle< reco::ConversionCollection > h_conversionCollection;
    iEvent.getByToken(conversionCollectionToken, h_conversionCollection);
    edm::Handle< reco::VertexCollection > h_primaryVertices;
    iEvent.getByToken(primaryVerticesToken, h_primaryVertices);

    // MUONS
    edm::Handle< pat::MuonCollection > h_selectedMuons;
    edm::Handle< pat::MuonCollection > h_selectedMuonsDL;
    edm::Handle< pat::MuonCollection > h_selectedMuonsLoose;
    iEvent.getByToken(selectedMuonsToken, h_selectedMuons);
    iEvent.getByToken(selectedMuonsDLToken, h_selectedMuonsDL);
    iEvent.getByToken(selectedMuonsLooseToken, h_selectedMuonsLoose);

    // ELECTRONS
    edm::Handle< pat::ElectronCollection > h_selectedElectrons;
    edm::Handle< pat::ElectronCollection > h_selectedElectronsDL;
    edm::Handle< pat::ElectronCollection > h_selectedElectronsLoose;
    iEvent.getByToken(selectedElectronsToken, h_selectedElectrons);
    iEvent.getByToken(selectedElectronsDLToken, h_selectedElectronsDL);
    iEvent.getByToken(selectedElectronsLooseToken, h_selectedElectronsLoose);

    // PHOTONS
    edm::Handle< pat::PhotonCollection > h_selectedPhotons;
    iEvent.getByToken(selectedPhotonsToken, h_selectedPhotons);
    edm::Handle< pat::PhotonCollection > h_selectedPhotonsLoose;
    iEvent.getByToken(selectedPhotonsLooseToken, h_selectedPhotonsLoose);

    // JETs
    std::vector< edm::Handle< pat::JetCollection > > hs_selectedJets;
    std::vector< edm::Handle< pat::JetCollection > > hs_selectedJetsLoose;
    std::vector< edm::Handle< pat::JetCollection > > hs_selectedJetsAK8;
    std::vector< edm::Handle< pat::JetCollection > > hs_selectedJetsAK15;
    std::vector< edm::Handle< pat::METCollection > > hs_correctedMETs;
    std::vector< edm::Handle< pat::METCollection > > hs_correctedMETsPuppi;

    for (size_t i = 0; i < selectedJetsTokens.size(); i++) {
        edm::Handle< pat::JetCollection > h_selectedJets;
        edm::Handle< pat::JetCollection > h_selectedJetsLoose;
        edm::Handle< pat::JetCollection > h_selectedJetsAK8;
        edm::Handle< pat::JetCollection > h_selectedJetsAK15;
        edm::Handle< pat::METCollection > h_correctedMETs;
        edm::Handle< pat::METCollection > h_correctedMETsPuppi;
        iEvent.getByToken(selectedJetsTokens.at(i), h_selectedJets);
        iEvent.getByToken(selectedJetsLooseTokens.at(i), h_selectedJetsLoose);
        iEvent.getByToken(selectedJetsAK8_Tokens.at(i), h_selectedJetsAK8);
        iEvent.getByToken(selectedJetsAK15_Tokens.at(i), h_selectedJetsAK15);
        iEvent.getByToken(correctedMETsTokens.at(i), h_correctedMETs);
        iEvent.getByToken(correctedMETsPuppiTokens.at(i), h_correctedMETsPuppi);
        hs_selectedJets.push_back(h_selectedJets);
        hs_selectedJetsLoose.push_back(h_selectedJetsLoose);
        hs_selectedJetsAK8.push_back(h_selectedJetsAK8);
        hs_selectedJetsAK15.push_back(h_selectedJetsAK15);
        hs_correctedMETs.push_back(h_correctedMETs);
        hs_correctedMETsPuppi.push_back(h_correctedMETsPuppi);
    }

    // MC only (generator weights for example)
    edm::Handle< GenEventInfoProduct >              h_genInfo;
    edm::Handle< LHEEventProduct >                  h_lheInfo;
    edm::Handle< LHEEventProduct >                  h_dummie1;
    edm::Handle< LHEEventProduct >                  h_dummie2;
    edm::Handle< std::vector< reco::GenParticle > > h_genParticles;
    edm::Handle< std::vector< reco::GenJet > >      h_genJets;
    if (!isData) {
        iEvent.getByToken(genInfoToken, h_genInfo);
        iEvent.getByToken(lheInfoToken, h_dummie1);
        iEvent.getByToken(lheInfoToken_source, h_dummie2);
        if (h_dummie1.isValid()) {
            iEvent.getByToken(lheInfoToken, h_lheInfo);
            dogenweights = true;
        }
        else if (h_dummie2.isValid()) {
            iEvent.getByToken(lheInfoToken_source, h_lheInfo);
            dogenweights = true;
        }
        else {
            dogenweights = false;
        }
        iEvent.getByToken(genParticlesToken, h_genParticles);
        iEvent.getByToken(genJetsToken, h_genJets);
    }

    // selected vertices and set vertex for MiniAODhelper
    // TODO: vertex selection in external producer
    reco::VertexCollection const& vtxs = *h_primaryVertices;
    reco::VertexCollection        selectedPVs;
    bool                          firstVertexIsGood = false;
    bool                          isFirst           = true;
    if (h_primaryVertices.isValid()) {
        for (const auto& itvtx : vtxs) {
            bool isGood = (!(itvtx.isFake()) && (itvtx.ndof() > 4.0) && (abs(itvtx.z()) < 24.0) && (abs(itvtx.position().Rho()) < 2.0));
            if (isGood) selectedPVs.push_back(itvtx);
            if (isFirst) firstVertexIsGood = isGood;
            isFirst = false;
        }
    }
    if (vtxs.size() > 0) helper.SetVertex(vtxs[0]);

    // set rho in MiniAODhelper
    // TODO: setup MiniAODhelper more transparently
    helper.SetRho(*h_rho);

    // Fill Event Info Object
    EventInfo   eventInfo(iEvent, h_beamSpot, h_hcalNoiseSummary, h_puInfo, firstVertexIsGood, *h_rho);
    TriggerInfo triggerInfo = triggerInfoProd.Produce(iEvent);
    FilterInfo  filterInfo  = filterInfoProd.Produce(iEvent);

    // FIGURE OUT SAMPLE
    bool                   foundT     = false;
    bool                   foundTbar  = false;
    bool                   foundHiggs = false;
    HiggsDecay::HiggsDecay higgsdecay = HiggsDecay::NA;
    if (!isData) {
        std::vector< reco::GenParticle > const& genParticles = *h_genParticles;
        for (size_t i = 0; i < genParticles.size(); i++) {
            if (genParticles[i].pdgId() == 6)
                foundT = true;
            else if (genParticles[i].pdgId() == -6)
                foundTbar = true;
            else if (genParticles[i].pdgId() == 25) {
                foundHiggs = true;
                if (higgsdecay == HiggsDecay::NA) higgsdecay = HiggsDecay::nonbb;
                for (size_t j = 0; j < genParticles[i].numberOfDaughters(); j++) {
                    if (abs(genParticles[i].daughter(j)->pdgId()) == 5) { higgsdecay = HiggsDecay::bb; }
                }
            }
        }
    }
    GenTopEvent genTopEvt = genTopEvtProd.Produce(iEvent, useGenHadronMatch, !(!isData && (foundT || foundTbar)));
    int         ttid      = genTopEvt.IsFilled() ? genTopEvt.GetTTxIdFromProducer() : -1;

    SampleType sampleType = SampleType::nonttbkg;
    if (isData)
        sampleType = SampleType::data;
    else if (foundT && foundTbar && foundHiggs)
        sampleType = SampleType::tth;
    else if (foundT && foundTbar) {
        sampleType = SampleType::ttl;
        if (ttid == 51)
            sampleType = SampleType::ttb;
        else if (ttid == 52)
            sampleType = SampleType::tt2b;
        else if (ttid == 53 || ttid == 54 || ttid == 55)
            sampleType = SampleType::ttbb;
        else if (ttid == 41 || ttid == 42)
            sampleType = SampleType::ttcc;
        else if (ttid == 43 || ttid == 44 || ttid == 45)
            sampleType = SampleType::ttcc;
    }
    else if (((foundT && !foundTbar) || (!foundT && foundTbar)) && foundHiggs)
        sampleType = SampleType::thq;

    // create empty packedGenParticle dummy since this collection is not yet
    // needed, but maybe later
    std::vector< pat::PackedGenParticle > packedGenParticles_dummy;
    // create GenDarkMatterEvent object
    GenDarkMatterEvent genDarkMatterEvent(*h_genParticles, packedGenParticles_dummy);
    // initialze the GenDarkMatterEvent object with the collections of
    // genparticles
    if (!isData) {
        genDarkMatterEvent.Initialize();
        // fill the event
        genDarkMatterEvent.Fill();
        if (genDarkMatterEvent.HasVectorBoson()) genDarkMatterEvent.FillBoson();
    }

    // selectiontags
    map< string, int > selectionTags;

    // inputs
    std::vector< InputCollections > inputs;
    const auto eventweights = GetWeights(*h_genInfo, *h_lheInfo, eventInfo, selectedPVs, *h_selectedElectronsLoose, *h_selectedMuonsLoose, genTopEvt);
    for (size_t isys = 0; isys < jetSystematics.size(); isys++) {
        auto weights    = eventweights;
        auto csvweights = GetCSVWeights(*(hs_selectedJets.at(isys)), jetSystematics.at(isys));
        weights.insert(csvweights.begin(), csvweights.end());
        inputs.emplace_back(eventInfo, triggerInfo, filterInfo, selectedPVs, *h_selectedMuons, *h_selectedMuonsDL, *h_selectedMuonsLoose, *h_selectedElectrons,
                            *h_selectedElectronsDL, *h_selectedElectronsLoose, *h_selectedPhotons, *h_selectedPhotonsLoose, *(hs_selectedJets.at(isys)),
                            *(hs_selectedJetsLoose.at(isys)), *(hs_selectedJetsAK8.at(isys)), *(hs_selectedJetsAK15.at(isys)),
                            (*(hs_correctedMETs.at(isys))).at(0), (*(hs_correctedMETsPuppi.at(isys))).at(0),
                            // selectedBoostedJets[isys],
                            // selectedAk4Cluster,
                            genTopEvt, genDarkMatterEvent, *h_genJets, sampleType, higgsdecay, weights, iEvent, iSetup, jetSystematics.at(isys), selectionTags,
                            era);
    }
    // TODO: adapt to new synch exe

    // if (dumpSyncExe) { synchronizer.DumpSyncExe(inputs, dumpExtended, dumpAlwaysEvents); }

    assert(inputs.size() == cutflows.size());
    assert(inputs.size() == jetSystematics.size());
    // flag to identifiy if the event is selected for at least one of the
    // possible jet collections corresponding to the jec sources
    bool at_least_one_selected = false;
    // flag to identify if the event does not fulfill selection criteria
    // independent of the jet collections (vertex,filter,lepton) so it can be
    // skipped no matter which jet collection is looked at
    bool next_event = false;
    // DO SELECTION
    // loop over jet systematics
    for (size_t i_sys = 0; i_sys < jetSystematics.size(); i_sys++) {
        // all events survive step 0
        cutflows[i_sys].EventSurvivedStep("all", inputs[i_sys].weights.at("Weight"));
        // start with selection=true and change this if one selection fails
        bool selected = true;
        // for every systematic: loop over selections
        for (size_t i_sel = 0; i_sel < selections.size() && selected; i_sel++) {
            // see if event is selected
            if (!taggingSelection) {
                // std::cout << "not running in tagging mode" << std::endl;
                if (!selections.at(i_sel)->IsSelected(inputs[i_sys], cutflows[i_sys])) {
                    selected = false;
                    // if the vertex,filter or lepton selection is not
                    // fulfilled, set the flag to skip the other jec variations
                    if (!selected && i_sel != jet_tag_pos && jet_tag_pos != selections.size()) next_event = true;
                }
            }
            else {
                selected                                = true;
                next_event                              = false;
                selectionTags[selectionNames.at(i_sel)] = selections.at(i_sel)->IsSelected(inputs[i_sys], cutflows[i_sys]);
            }
        }
        // if the vertex,filter or lepton selection is not fulfilled, skip the
        // other jec variations
        if (next_event) break;
        // if one of the jet collections fulfills the selection and mem ntuples
        // are supposed to be written, skip the checks for the other jet
        // collections and go directly to writing
        at_least_one_selected = at_least_one_selected || selected;
        if (ProduceMemNtuples && at_least_one_selected) break;
        // if normal ntuples are supposed to be written and the selections are
        // fulfilled for the jet collection, then write
        if (!ProduceMemNtuples && selected) treewriters[i_sys]->Process(inputs[i_sys],
                                                                        false);  // second parameter: verbose
    }
    // write the mem ntuples if the mem ntuples flag is set and at least one jet
    // collection fulfills the selection criteria
    if (ProduceMemNtuples && at_least_one_selected) treewriters.back()->Process(inputs, false);
}

float BoostedAnalyzer::GetTopPtWeight(const float& toppt1, const float& toppt2)
{
    float sf1 = exp(0.0615 - 0.0005 * toppt1);
    float sf2 = exp(0.0615 - 0.0005 * toppt2);
    return sqrt(sf1 * sf2);
}

std::map< string, float > BoostedAnalyzer::GetWeights(const GenEventInfoProduct& genInfo, const LHEEventProduct& lheInfo, const EventInfo& eventInfo,
                                                      const reco::VertexCollection& selectedPVs, const std::vector< pat::Electron >& selectedElectrons,
                                                      const std::vector< pat::Muon >& selectedMuons, const GenTopEvent& genTopEvt)
{
    std::map< string, float > weights;

    if (isData) {
        weights["Weight"]          = 1.0;
        weights["Weight_XS"]       = 1.0;
        weights["Weight_PU"]       = 1.0;
        weights["Weight_TopPt"]    = 1.0;
        weights["Weight_GenValue"] = 1.0;
        return weights;
    }

    float weight          = 1.;
    float weight_GenValue = 1.0;
    if (genInfo.weights().size() > 0) {
        weight          = genInfo.weights()[0] > 0 ? 1. : -1.;
        weight_GenValue = genInfo.weights()[0];
    }

    float xsweight        = eventWeight;
    float puweight        = 1.;
    float topptweight     = genTopEvt.IsTTbar() ? GetTopPtWeight(genTopEvt.GetHardTop().pt(), genTopEvt.GetHardTopBar().pt()) : 1.;
    float topptweightUp   = 1.0 + 2.0 * (topptweight - 1.0);
    float topptweightDown = 1.0;

    // compute PU weights, and set nominal weight
    puWeights.compute(eventInfo);
    puweight = puWeights.nominalWeight();

    weight *= weight_GenValue * xsweight;
    weights["Weight_GenValue"] = weight_GenValue;
    weights["Weight"]          = weight;
    weights["Weight_XS"]       = xsweight;

    weights["Weight_PU"]    = puweight;
    weights["Weight_TopPt"] = topptweight;

    weights["Weight_TopPtup"]   = topptweightUp;
    weights["Weight_TopPtdown"] = topptweightDown;

    // Add Lepton Scalefactors to weight map
    // std::map< std::string, float > selectedScaleFactors = leptonSFhelper.GetLeptonSF(selectedElectrons, selectedMuons);

    // for (auto sfit = selectedScaleFactors.begin(); sfit != selectedScaleFactors.end(); sfit++) { weights["Weight_" + sfit->first] = sfit->second; }

    // set optional additional PU weights
    for (std::vector< PUWeights::Weight >::const_iterator it = puWeights.additionalWeightsBegin(); it != puWeights.additionalWeightsEnd(); ++it) {
        weights[it->name()] = it->value();
    }
    // Add Genweights to the weight map
    genweights.GetGenWeights(weights, lheInfo);
    // DANGERZONE
    genweights.GetLHAPDFWeight(weights, genInfo);
    // DANGERZONE

    return weights;
}

std::map< string, float > BoostedAnalyzer::GetCSVWeights(const std::vector< pat::Jet >& selectedJets, const Systematics::Type& systype)
{
    std::map< string, float > weights;

    if (isData) {
        weights["Weight_CSV"] = 1.0;
        return weights;
    }

    // dummy variables for the getCSVWeight function, might be useful for checks
    double csvWgtHF, csvWgtLF, csvWgtCF;
    float  csvweight = 1.;

    // get vectors of jet properties
    std::vector< double > jetPts;
    std::vector< double > jetEtas;
    std::vector< double > jetCSVs;
    std::vector< int >    jetFlavors;

    for (const auto& itJet : selectedJets) {
        jetPts.push_back(itJet.pt());
        jetEtas.push_back(itJet.eta());
        jetCSVs.push_back(CSVHelper::GetJetCSV(itJet, "DeepJet"));
        jetFlavors.push_back(itJet.hadronFlavour());
    }

    // calculate the csv weight for the desired systematic
    csvweight = csvReweighter.getCSVWeight(jetPts, jetEtas, jetCSVs, jetFlavors, systype, csvWgtHF, csvWgtLF, csvWgtCF);

    weights["Weight_CSV"] = csvweight;

    if (systype == Systematics::NA) {  // only do these for the nominal samples
        weights["Weight_CSVLFup"] =
            csvReweighter.getCSVWeight(jetPts, jetEtas, jetCSVs, jetFlavors, Systematics::CSVLFup, csvWgtHF, csvWgtLF, csvWgtCF) / csvweight;
        weights["Weight_CSVLFdown"] =
            csvReweighter.getCSVWeight(jetPts, jetEtas, jetCSVs, jetFlavors, Systematics::CSVLFdown, csvWgtHF, csvWgtLF, csvWgtCF) / csvweight;
        weights["Weight_CSVHFup"] =
            csvReweighter.getCSVWeight(jetPts, jetEtas, jetCSVs, jetFlavors, Systematics::CSVHFup, csvWgtHF, csvWgtLF, csvWgtCF) / csvweight;
        weights["Weight_CSVHFdown"] =
            csvReweighter.getCSVWeight(jetPts, jetEtas, jetCSVs, jetFlavors, Systematics::CSVHFdown, csvWgtHF, csvWgtLF, csvWgtCF) / csvweight;
        weights["Weight_CSVHFStats1up"] =
            csvReweighter.getCSVWeight(jetPts, jetEtas, jetCSVs, jetFlavors, Systematics::CSVHFStats1up, csvWgtHF, csvWgtLF, csvWgtCF) / csvweight;
        weights["Weight_CSVHFStats1down"] =
            csvReweighter.getCSVWeight(jetPts, jetEtas, jetCSVs, jetFlavors, Systematics::CSVHFStats1down, csvWgtHF, csvWgtLF, csvWgtCF) / csvweight;
        weights["Weight_CSVLFStats1up"] =
            csvReweighter.getCSVWeight(jetPts, jetEtas, jetCSVs, jetFlavors, Systematics::CSVLFStats1up, csvWgtHF, csvWgtLF, csvWgtCF) / csvweight;
        weights["Weight_CSVLFStats1down"] =
            csvReweighter.getCSVWeight(jetPts, jetEtas, jetCSVs, jetFlavors, Systematics::CSVLFStats1down, csvWgtHF, csvWgtLF, csvWgtCF) / csvweight;
        weights["Weight_CSVHFStats2up"] =
            csvReweighter.getCSVWeight(jetPts, jetEtas, jetCSVs, jetFlavors, Systematics::CSVHFStats2up, csvWgtHF, csvWgtLF, csvWgtCF) / csvweight;
        weights["Weight_CSVHFStats2down"] =
            csvReweighter.getCSVWeight(jetPts, jetEtas, jetCSVs, jetFlavors, Systematics::CSVHFStats2down, csvWgtHF, csvWgtLF, csvWgtCF) / csvweight;
        weights["Weight_CSVLFStats2up"] =
            csvReweighter.getCSVWeight(jetPts, jetEtas, jetCSVs, jetFlavors, Systematics::CSVLFStats2up, csvWgtHF, csvWgtLF, csvWgtCF) / csvweight;
        weights["Weight_CSVLFStats2down"] =
            csvReweighter.getCSVWeight(jetPts, jetEtas, jetCSVs, jetFlavors, Systematics::CSVLFStats2down, csvWgtHF, csvWgtLF, csvWgtCF) / csvweight;
        weights["Weight_CSVCErr1up"] =
            csvReweighter.getCSVWeight(jetPts, jetEtas, jetCSVs, jetFlavors, Systematics::CSVCErr1up, csvWgtHF, csvWgtLF, csvWgtCF) / csvweight;
        weights["Weight_CSVCErr1down"] =
            csvReweighter.getCSVWeight(jetPts, jetEtas, jetCSVs, jetFlavors, Systematics::CSVCErr1down, csvWgtHF, csvWgtLF, csvWgtCF) / csvweight;
        weights["Weight_CSVCErr2up"] =
            csvReweighter.getCSVWeight(jetPts, jetEtas, jetCSVs, jetFlavors, Systematics::CSVCErr2up, csvWgtHF, csvWgtLF, csvWgtCF) / csvweight;
        weights["Weight_CSVCErr2down"] =
            csvReweighter.getCSVWeight(jetPts, jetEtas, jetCSVs, jetFlavors, Systematics::CSVCErr2down, csvWgtHF, csvWgtLF, csvWgtCF) / csvweight;
    }

    return weights;
}

std::string BoostedAnalyzer::systName(const Systematics::Type& sysType)
{
    if (sysType == Systematics::NA)
        return "nominal";
    else
        return Systematics::toString(sysType);
}

std::string BoostedAnalyzer::outfileName(const std::string& basename, const Systematics::Type& sysType)
{
    const std::string systLabel   = Systematics::toString(sysType);
    const size_t      stringIndex = basename.find("nominal");
    if (stringIndex != std::string::npos) {
        std::string outfileName = basename;
        outfileName.replace(stringIndex, 7, systLabel);
        return outfileName;
    }
    if (sysType == Systematics::NA)
        return basename + "_nominal";
    else
        return basename + "_" + systLabel;
}

// ------------ method called once each job just before starting event loop
// ------------
void BoostedAnalyzer::beginJob()
{
    eventcount = 0;

    watch.Start();
}

// ------------ method called once each job just after ending the event loop
// ------------
void BoostedAnalyzer::endJob()
{
    for (size_t i = 0; i < outfileNames.size(); i++) {
        std::ofstream fout(outfileNames[i] + "_Cutflow.txt");
        cutflows[i].Print(fout);
        fout.close();
        // if(!ProduceMemNtuples) {
        // delete treewriters[i];
        //}
    }
    // if(ProduceMemNtuples) {
    // delete treewriters.back();
    //}
    // for(size_t i=0; i<selections.size();i++) {
    // delete selections[i];
    //}
}

// ------------ method called when starting to processes a run ------------
void BoostedAnalyzer::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
    edm::Handle< LHERunInfoProduct > runhandle1;
    edm::Handle< LHERunInfoProduct > runhandle2;
    // iEvent.getRun()
    iRun.getByLabel("externalLHEProducer", runhandle1);
    iRun.getByLabel("source", runhandle2);

    LHERunInfoProduct myLHERunInfoProduct;
    if (runhandle1.isValid()) { myLHERunInfoProduct = *(runhandle1.product()); }
    else if (runhandle2.isValid()) {
        myLHERunInfoProduct = *(runhandle2.product());
    }
    else {
        cout << "Attention: no genweights will be written because the "
                "LHERunInfoProduct is not available!"
             << endl;
        return;
    }

    genweights.GetNamesFromLHE(myLHERunInfoProduct);
}

void BoostedAnalyzer::endRun(edm::Run const& iRun, edm::EventSetup const& iSetup) { genweights.Clear(); }

// ------------ method called when starting a luminosity block ------------
void BoostedAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const& iBlock, edm::EventSetup const& iSetup) {}

// ------------ method fills 'descriptions' with the allowed parameters for the
// module  ------------
void BoostedAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions)
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
DEFINE_FWK_MODULE(BoostedAnalyzer);
