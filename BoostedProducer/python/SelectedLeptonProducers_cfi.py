# Default lepton selection of the "loose electrons/muons" defined at
# https://twiki.cern.ch/twiki/bin/view/CMS/TTbarHbbRun2ReferenceAnalysis#Object_selection_SPRING15

import FWCore.ParameterSet.Config as cms

SelectedElectronProducer = cms.EDProducer(
    "SelectedLeptonProducer",
    leptonType = cms.string("electron"),

    era          = cms.string("2015_74x"),
    analysisType = cms.string("LJ"),
    isData       = cms.bool(False),

    leptons = cms.InputTag("slimmedElectrons"),
    vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    ptMin   = cms.double(10),
    etaMax  = cms.double(2.4),
    leptonID = cms.string("looseSpring15"),

    # The following two parameters are dummies in case of electrons
    # they are not used for the electron selection, which is defined
    # via the 'leptonID' value
    isoConeSize = cms.string("R03"), 
    isoCorrType = cms.string("rhoEA")
    )


SelectedMuonProducer = cms.EDProducer(
    "SelectedLeptonProducer",
    leptonType = cms.string("muon"),

    era          = cms.string("2015_74x"),
    analysisType = cms.string("LJ"),
    isData       = cms.bool(False),

    leptons = cms.InputTag("slimmedMuons"),
    vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    ptMin   = cms.double(10),
    etaMax  = cms.double(2.4),
    leptonID = cms.string("loose"),
    isoConeSize = cms.string("R04"),
    isoCorrType = cms.string("deltaBeta")    
    )

SelectedLeptonProducerPath = cms.Path(SelectedElectronProducer*SelectedMuonProducer)
