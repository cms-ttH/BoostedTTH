#ifndef Helper_H
#define Helper_H

#include <map>
#include <string>
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

class Helper {
public:
  // some enums to make things nicer
  enum class JetID { Loose, Tight, none, jetMETcorrection, jetLooseAOD,    jetMinimal,    jetPU  };
  enum class PUJetIDWP  {    none,    Loose,    Medium,    Tight  };

    enum class LeptonType    {Electron, Muon};
    enum class ElectronID    {None, Veto, Loose, Medium, Tight};
    enum class MuonID        {None, Loose, Medium, Tight};
    enum class IsoConeSize      {R03, R04};
    enum class IsoCorrType      {rhoEA, deltaBeta};
    enum class MuonIsolation {None, Loose, Medium, Tight};

  static bool isGoodJet(const pat::Jet &iJet, const float iMinPt, const float iMaxAbsEta, const JetID, const PUJetIDWP wp, std::string dataEra="2017");
  static int TranslateJetPUIDtoInt(PUJetIDWP wp);
  static bool isGoodMuon(const pat::Muon& iMuon, const double iMinPt, const double iMaxEta, const MuonID iMuonID, const IsoConeSize iconeSize, const IsoCorrType icorrType, const MuonIsolation imuonIso, reco::Vertex vert);
  static bool isGoodElectron(const pat::Electron& iElectron, reco::Vertex vert, const double iMinPt = 10., const double iMaxEta = 2.4, const ElectronID iElectronID = ElectronID::Loose);

private:
};


// function to check if Jet FullFills IDs
bool Helper::isGoodJet(const pat::Jet &iJet, const float iMinPt, const float iMaxAbsEta,
                                    const JetID iJetID, const PUJetIDWP wp, std::string dataEra)
{
  //   CheckVertexSetUp(); // What is this?

  // Transverse momentum requirement
  if (iJet.pt() < iMinPt)
    return false;

  // Absolute eta requirement
  if (fabs(iJet.eta()) > iMaxAbsEta)
    return false;

  // Jet ID
  bool loose = false;
  bool tight = false;
  bool goodForMETCorrection = false;

  if (iJetID != JetID::none && iJet.isPFJet())
  {
    // these are the loose requirements for Run 2016 80X
    loose = (iJet.neutralHadronEnergyFraction() < 0.99 &&
             iJet.neutralEmEnergyFraction() < 0.99 &&
             iJet.numberOfDaughters() > 1);
    // these are the tight requirements for Run 2017 90X. Since the tight JetID efficiency is > 99% everywhere for this era,
    // loose is not recommended anymore.
    tight = (iJet.neutralHadronEnergyFraction() < 0.90 &&
             iJet.neutralEmEnergyFraction() < 0.90 &&
             iJet.numberOfDaughters() > 1);

    if (fabs(iJet.eta()) < 2.4)
    {
      loose = (loose &&
               iJet.chargedHadronEnergyFraction() > 0.0 &&
               iJet.chargedMultiplicity() > 0 &&
               iJet.chargedEmEnergyFraction() < 0.99);
      tight = (tight &&
               iJet.chargedHadronEnergyFraction() > 0.0 &&
               iJet.chargedMultiplicity() > 0
               //iJet.chargedEmEnergyFraction() < 0.99
      );
      if (TString(dataEra).Contains("2016")){
        tight = (tight && iJet.chargedEmEnergyFraction() < 0.99);
      }
    }

    if (iJetID == JetID::jetMETcorrection)
    { //only check this if asked, otherwise there could be problems
      goodForMETCorrection = (iJet.correctedJet(0).pt() > 10.0 &&
                              ((!iJet.isPFJet() && iJet.emEnergyFraction() < 0.9) ||
                               (iJet.isPFJet() && (iJet.neutralEmEnergyFraction() + iJet.chargedEmEnergyFraction()) < 0.9)));
    }
  }

  switch (iJetID)
  {
  case JetID::jetMETcorrection:
    if (!goodForMETCorrection)
      return false;
    break;
  case JetID::jetPU:
  case JetID::jetMinimal:
  case JetID::jetLooseAOD:
  case JetID::Loose:
    if (!loose)
      return false;
    break;
  case JetID::Tight:
    if (!tight)
      return false;
    break;
  case JetID::none:
  default:
    break;
  }
  // PileUP Jet ID
  if (iJet.hasUserInt("pileupJetId:fullId"))
  {
    if (iJet.userInt("pileupJetId:fullId") < TranslateJetPUIDtoInt(wp))
      return false;
  }

  return true;
}

// function to Translate PUJetIDWP into its corresponding int
int Helper::TranslateJetPUIDtoInt(PUJetIDWP wp)
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

// function to check whether a muon fulfills several requirements with overloaded vertex
bool
Helper::isGoodMuon(const pat::Muon& iMuon, const double iMinPt, const double iMaxEta, const MuonID iMuonID, const IsoConeSize iconeSize, const IsoCorrType icorrType, const MuonIsolation imuonIso, reco::Vertex vert){
    bool passesKinematics = (iMinPt<=iMuon.pt()) and (iMaxEta>=fabs(iMuon.eta()));
    bool passesID = false;
    bool passesIso = false;
    switch(iMuonID){
        case MuonID::None:
            passesID         = true;
            break;
        case MuonID::Loose:
            passesID         = muon::isLooseMuon(iMuon);
            break;
        case MuonID::Medium:
            passesID         = muon::isMediumMuon(iMuon);
            break;
        case MuonID::Tight:
            passesID         = muon::isTightMuon(iMuon, vert);
            break;
        default:
            std::cerr << "\n\nERROR: InvalidMuonID" <<  std::endl;
            throw std::exception();

    }
    switch(imuonIso){
        case MuonIsolation::None:
            passesIso         = true;
            break;
        case MuonIsolation::Loose:
            passesIso         = iMuon.passed(pat::Muon::PFIsoLoose);
            break;
        case MuonIsolation::Medium:
            passesIso         = iMuon.passed(pat::Muon::PFIsoMedium);
            break;
        case MuonIsolation::Tight:
            passesIso         = iMuon.passed(pat::Muon::PFIsoTight);
            break;
        default:
            std::cerr << "\n\nERROR: InvalidMuonIso" <<  std::endl;
            throw std::exception();

    }
    return passesKinematics and passesID and passesIso;
}

// function to check whether an electron fulfills several requirements, overloaded to take vertex
bool
Helper::isGoodElectron(const pat::Electron& iElectron, reco::Vertex vert, const double iMinPt, const double iMaxEta,const ElectronID iElectronID){
    bool passesKinematics = (iMinPt<=iElectron.pt()) and (iMaxEta>=fabs(iElectron.eta()));
    bool inCrack = false;
    bool passesIPcuts = false;
    bool passesID = false;
    
    double absSCeta = 999; 
    if( iElectron.superCluster().isAvailable() ){
        absSCeta = fabs(iElectron.superCluster()->position().eta());
        inCrack = (absSCeta>1.4442 and absSCeta<1.5660 );
    }
    double IP_d0 = 999;
    double IP_dZ = 999;

    bool isEB = absSCeta < 1.479; //check if electron is in barrel region
    if( iElectron.gsfTrack().isAvailable() ){
        IP_d0 = fabs(iElectron.gsfTrack()->dxy(vert.position()));
        IP_dZ = fabs(iElectron.gsfTrack()->dz(vert.position()));
    }
    
    //if impact parameter cuts are not met, set passesIPcuts = false
    if( isEB ) passesIPcuts = (IP_d0 < 0.05 and IP_dZ < 0.1);
    else passesIPcuts = (IP_d0 < 0.1 and IP_dZ < 0.2);
    
    switch(iElectronID){
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
            passesID = iElectron.electronID("cutBasedElectronID-Fall17-94X-V2-medium");
            break;
        case ElectronID::Tight:
            passesID = iElectron.electronID("cutBasedElectronID-Fall17-94X-V2-tight");
            break;
        default:
            std::cerr << "\n\nERROR: InvalidElectronID" <<  std::endl;
            throw std::exception();
    }
    
    return passesKinematics and (not inCrack) and passesIPcuts and passesID;
}


#endif
