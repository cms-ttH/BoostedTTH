BoostedTTH
=======

CMSSW tools for analyzing TTH events with boosted objects

## Installation
Follow These Steps:
 
    export SCRAM_ARCH=slc6_amd64_gcc491
    scram project CMSSW_7_4_6_patch6
    cd CMSSW_7_4_6_patch6/src
    cmsenv   
    git cms-addpkg PhysicsTools/JetMCAlgos/
    cd PhysicsTools/JetMCAlgos/plugins/
    rm GenHFHadronMatcher.cc
    wget https://twiki.cern.ch/twiki/pub/CMSPublic/GenHFHadronMatcher/GenHFHadronMatcher.cc
    cd -
    git clone -b run2mc https://github.com/cms-ttH/MiniAOD.git
    cd MiniAOD
    git rebase -s ours origin/master
    cd ..
    git cms-merge-topic gkasieczka:htt-v2-74X
    git clone https://github.com/cms-ttH/BoostedTTH.git
    ln -s $CMSSW_RELEASE_BASE/src/RecoJets/JetProducers/plugins/VirtualJetProducer.h BoostedTTH/BoostedProducer/plugins/VirtualJetProducer.h
    ln -s $CMSSW_RELEASE_BASE/src/RecoJets/JetProducers/plugins/VirtualJetProducer.cc BoostedTTH/BoostedProducer/plugins/VirtualJetProducer.cc
    scram b -j10

## Overview
BoostedObjects contains the classes needed for subjet-analysis. They associate fat jets with the corresponding filtered objects.

BoostedProduces contains the tools used to run the HEPTopTagger and SubjetFilterJet algorithm on MiniAOD and add the output as the above collections.

BoostedAnalyzer can be used to analyze MiniAOD files. The plugin itself takes care of objectselections and stores the objects in InputCollections. Different event selection can be used in this step, too. The inputcollections can be analyzed with a TreeWriter that can load different Processors. Every processor writes a certain class of output variables in a flat TTree.

This Branch was created to analze the new MCRun2 samples.
