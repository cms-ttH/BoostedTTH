BoostedTTH
=======

CMSSW tools for analyzing TTH events with boosted objects

## Installation
Follow These Steps:

CMSSW_7_4_14:

    export SCRAM_ARCH=slc6_amd64_gcc491
    scram project CMSSW_7_4_14
    cd CMSSW_7_4_14/src
    cmsenv   
    git cms-addpkg PhysicsTools/JetMCAlgos/
    cd PhysicsTools/JetMCAlgos/plugins/
    rm GenHFHadronMatcher.cc
    wget https://twiki.cern.ch/twiki/pub/CMSPublic/GenHFHadronMatcher/GenHFHadronMatcher.cc
    wget https://twiki.cern.ch/twiki/pub/CMSPublic/GenHFHadronMatcher/GenTtbarCategorizer.cc
    cd -
    cd PhysicsTools/JetMCAlgos/python/
    wget https://twiki.cern.ch/twiki/pub/CMSPublic/GenHFHadronMatcher/GenTtbarCategorizer_cfi.py.txt
    mv GenTtbarCategorizer_cfi.py.txt GenTtbarCategorizer_cfi.py
    cd -
    git cms-merge-topic gkasieczka:htt-v2-74X
    git clone https://github.com/cms-ttH/MiniAOD.git
    cd MiniAOD
    git checkout --track origin/MergeBoostedObjects
    cd -
    git clone https://github.com/cms-ttH/BoostedTTH.git
    cd BoostedTTH
    git checkout --track origin/CMSSW_7_4_14
    cd -
    scram b -j10

CMSSW_7_4_15:

    export SCRAM_ARCH=slc6_amd64_gcc491
    scram project CMSSW_7_4_15
    cd CMSSW_7_4_15/src
    cmsenv   
    git cms-addpkg PhysicsTools/JetMCAlgos/
    cd PhysicsTools/JetMCAlgos/plugins/
    rm GenHFHadronMatcher.cc
    wget https://twiki.cern.ch/twiki/pub/CMSPublic/GenHFHadronMatcher/GenHFHadronMatcher.cc
    wget https://twiki.cern.ch/twiki/pub/CMSPublic/GenHFHadronMatcher/GenTtbarCategorizer.cc
    cd -
    cd PhysicsTools/JetMCAlgos/python/
    wget https://twiki.cern.ch/twiki/pub/CMSPublic/GenHFHadronMatcher/GenTtbarCategorizer_cfi.py.txt
    mv GenTtbarCategorizer_cfi.py.txt GenTtbarCategorizer_cfi.py
    cd -
    git cms-merge-topic gkasieczka:htt-v2-74X
    git remote add btv-cmssw https://github.com/cms-btv-pog/cmssw.git
    git fetch --tags btv-cmssw
    git cms-merge-topic cms-btv-pog:BoostedDoubleSVTaggerV2-WithWeightFiles-v1_from-CMSSW_7_4_15
    git clone https://github.com/cms-ttH/MiniAOD.git
    cd MiniAOD
    git checkout --track origin/MergeBoostedObjects
    cd -
    git clone https://github.com/cms-ttH/BoostedTTH.git
    cd BoostedTTH
    git checkout --track origin/CMSSW_7_4_14
    cd -
    scram b -j10

## Overview
BoostedObjects contains the classes needed for subjet-analysis. They associate fat jets with the corresponding filtered objects.

BoostedProduces contains the tools used to run the HEPTopTagger and SubjetFilterJet algorithm on MiniAOD and add the output as the above collections.

BoostedAnalyzer can be used to analyze MiniAOD files. The plugin itself takes care of objectselections and stores the objects in InputCollections. Different event selection can be used in this step, too. The inputcollections can be analyzed with a TreeWriter that can load different Processors. Every processor writes a certain class of output variables in a flat TTree.
