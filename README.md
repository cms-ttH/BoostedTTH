BoostedTTH
=======

CMSSW tools for analyzing TTH events with boosted objects

## Installation
Follow These Steps:

    cmsrel CMSSW_7_2_3
    cd CMSSW_7_2_3/src
    cmsenv
    git cms-addpkg PhysicsTools/JetMCAlgos/
    cd PhysicsTools/JetMCAlgos/plugins/
    rm GenHFHadronMatcher.cc
    wget https://twiki.cern.ch/twiki/pub/CMSPublic/GenHFHadronMatcher/GenHFHadronMatcher.cc
    cd -
    git clone https://github.com/cms-ttH/MiniAOD.git
    git clone https://github.com/cms-ttH/BoostedTTH.git -b phys14
    
    scram b -j 32

## Overview
BoostedObjects contains the classes needed for subjet-analysis. They associate fat jets with the corresponding filtered objects.

BoostedProduces contains the tools used to run the HEPTopTagger and SubjetFilterJet algorithm on MiniAOD and add the output as the above collections.

BoostedAnalyzer can be used to analyze MiniAOD files. The plugin itself takes care of objectselections and stores the objects in InputCollections. Different event selection can be used in this step, too. The inputcollections can be analyzed with a TreeWriter that can load different Processors. Every processor writes a certain class of output variables in a flat TTree.
