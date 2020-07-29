// -*- C++ -*-
//
// Package:    BoostedTTH/SelectedJetProducer
// Class:      SelectedJetProducer
//
/**\class SelectedJetProducer SelectedJetProducer.cc
 BoostedTTH/SelectedJetProducer/plugins/SelectedJetProducer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Hannes Mildner
//         Created:  Tue, 05 Apr 2016 09:53:41 GMT
//
//

#ifndef SelectedJetProducer_h
#define SelectedJetProducer_h

// system include files
#include <memory>
#include <vector>
#include <utility>
#include <fstream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"
#include "FWCore/Utilities/interface/Exception.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Photon.h"

#include "../interface/SystematicsHelper.h"

// JES correction stuff
#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

// To use when the object is either a reference or a pointer
template< typename T >
T *ptr(T &obj)
{
    return &obj;
}  // turn reference into pointer!
template< typename T >
T *ptr(T *obj)
{
    return obj;
}  // obj is already pointer, return it!

//
// class declaration
//

class SelectedJetProducer : public edm::stream::EDProducer<> {
   public:
    explicit SelectedJetProducer(const edm::ParameterSet &);
    ~SelectedJetProducer();

    static void fillDescriptions(edm::ConfigurationDescriptions &descriptions);

    // some enums to make things nicer
    enum class JetID { None, Loose, Tight, TightLepVeto, Matteo };
    enum class PUJetIDWP { None, Loose, Medium, Tight };
    enum class JetType { AK4PFCHS, AK4PFPUPPI, AK8PFCHS, AK8PFPUPPI, AK15PFPUPPI };

   private:
    // member functions
    virtual void beginStream(edm::StreamID) override;
    virtual void produce(edm::Event &, const edm::EventSetup &) override;
    virtual void endStream() override;

    // convert systematics type into string
    std::string systName(std::string name, SystematicsHelper::Type) const;

    // check if file exsits
    bool fileExists(const std::string &fileName) const;

    // functions to create jet correction uncertainty objects
    void                      UpdateJetCorrectorUncertainties(const edm::EventSetup &iSetup);
    JetCorrectionUncertainty *CreateJetCorrectorUncertainty(const edm::EventSetup &iSetup, const std::string &jetTypeLabel,
                                                            const std::string &uncertaintyLabel) const;
    void                      AddJetCorrectorUncertainty(const edm::EventSetup &iSetup, const std::string &uncertaintyLabel);

    // functions to select and correct jet collections
    std::vector< pat::Jet > GetSelectedJets(const std::vector< pat::Jet > &, const float iMinPt, const float iMaxAbsEta, const JetID,
                                            const PUJetIDWP = PUJetIDWP::None) const;
    bool                    isGoodJet(const pat::Jet &iJet, const float iMinPt, const float iMaxAbsEta, const JetID, const PUJetIDWP wp) const;
    std::vector< pat::Jet > GetUncorrectedJets(const std::vector< pat::Jet > &inputJets) const;
    std::vector< pat::Jet > GetDeltaRCleanedJets(const std::vector< pat::Jet > &inputJets, const std::vector< pat::Muon > &inputMuons,
                                                 const std::vector< pat::Electron > &inputElectrons, const std::vector< pat::Photon > &inputPhotons,
                                                 const double deltaRCut) const;
    std::vector< pat::Jet > GetCorrectedJets(const std::vector< pat::Jet > &, const edm::Event &, const edm::EventSetup &,
                                             const SystematicsHelper::Type iSysType = SystematicsHelper::NA, const bool &doJES = true,
                                             const float &corrFactor = 1, const float &uncFactor = 1);

    pat::Jet GetCorrectedJet(const pat::Jet &, const edm::Event &, const edm::EventSetup &, const SystematicsHelper::Type iSysType = SystematicsHelper::NA,
                             const bool doJES = true, const float corrFactor = 1, const float uncFactor = 1);

    void ApplyJetEnergyCorrection(pat::Jet &jet, double &totalCorrFactor, const edm::Event &event, const edm::EventSetup &setup,
                                  const SystematicsHelper::Type iSysType, const bool doJES, const bool addUserFloats, const float corrFactor,
                                  const float uncFactor);

    double GetJECUncertainty(const pat::Jet &jet, const edm::EventSetup &iSetup, const SystematicsHelper::Type iSysType);

    // functions to translate enums to strings or vice versa
    JetType     TranslateJetTypeStringToEnum(const std::string) const;
    std::string TranslateJetTypeToCorrectorLabel(const JetType) const;
    std::string TranslateJetTypeToUncertaintyLabel(const JetType) const;
    std::string FindJESUncertaintyFile(const JetType) const;
    JetID       TranslateJetIDStringToEnum(const std::string) const;
    PUJetIDWP   TranslatePUJetIDStringToEnum(const std::string) const;

    // function to translate pujetid wp to integer
    int TranslateJetPUIDtoInt(PUJetIDWP wp) const;

    // function to sort objects by pt
    template< typename T >
    T GetSortedByPt(const T &) const;

    // ----------member data ---------------------------

    const std::string jetType;

    const bool isData;
    /** min pt of jet collections **/
    const std::vector< double > ptMins;
    /** max eta of jet collections **/
    const std::vector< double > etaMaxs;
    /** min dir to lepton for jets **/
    const double leptonJetDr;

    /** apply jet energy correciton? **/
    const bool applyCorrection;
    const bool doDeltaRCleaning;
    const bool isSubjetCollection;

    /** names of output jet collections **/
    const std::vector< std::string > collectionNames;
    /** pileupjetid for collections **/
    const std::vector< std::string > PUJetIDMins;
    /** jetid **/
    const std::vector< std::string > JetID_;
    /** Systematics used **/
    const std::vector< std::string >       systematics_config;
    std::vector< SystematicsHelper::Type > systematics;

    // JEC files
    const std::string jecFileAK4_2016;
    const std::string jecFileAK8_2016;
    const std::string jecFileAK15_2016;
    const std::string jecFileAK4_2017;
    const std::string jecFileAK8_2017;
    const std::string jecFileAK15_2017;
    const std::string jecFileAK4_2018;
    const std::string jecFileAK8_2018;
    const std::string jecFileAK15_2018;

    const std::string era;

    /** input jets data access token **/
    edm::EDGetTokenT< pat::JetCollection > jetsToken;
    /** muons data access token (for jet cleaning)**/
    edm::EDGetTokenT< pat::MuonCollection > muonsToken;
    /** electrons data access token (for jet cleaning)**/
    edm::EDGetTokenT< pat::ElectronCollection > electronsToken;
    /** photons data access token (for jet cleaning)**/
    edm::EDGetTokenT< pat::PhotonCollection > photonsToken;
    /** rho data access token (for jet cleaning)**/
    edm::EDGetTokenT< double > rhoToken;

    // selection criterias
    JetType                  JetType_;
    std::vector< JetID >     Jet_ID;
    std::vector< PUJetIDWP > PUJetID_WP;

    // some variables neccessary for systematics
    std::string                                                          jetTypeLabelForJECUncertainty;
    std::string                                                          jecUncertaintyTxtFileName;
    std::map< std::string, std::unique_ptr< JetCorrectionUncertainty > > jecUncertainties_;
    const JetCorrector *                                                 corrector;
    std::string                                                          correctorlabel = "";

    const bool doJES = true;
};

#endif
