BoostedTTH
=======

CMSSW tools for analyzing TTH events with boosted objects

## Installation
Follow These Steps:

    export SCRAM_ARCH=slc6_amd64_gcc530
    scram project CMSSW_8_0_12
    cd CMSSW_8_0_12/src
    cmsenv   
    git cms-merge-topic gkasieczka:htt-v2-76X
    git clone https://github.com/cms-ttH/MiniAOD.git -b CMSSW_8_0_8
    git clone https://github.com/cms-ttH/BoostedTTH.git -b CMSSW_8_0_8_VLQ
    mkdir Other
    cd Other
    git clone https://github.com/kit-cn-cms/bjetness-code.git .
    cd -
    mkdir TTH
    cd TTH
    git clone https://github.com/cms-ttH/CommonClassifier.git -b subjet-restricted-perms-kit-80X
    source CommonClassifier/setup/install_mem.sh
    cd $CMSSW_BASE/src
    sed -i 's/int member=0/int member/g' TTH/MEIntegratorStandalone/interface/Integrand.h
    sed -i 's/cfg.pdfset/cfg.pdfset, 0/g' TTH/MEIntegratorStandalone/src/Integrand.cpp
    cp BoostedTTH/BoostedProducer/plugins/ModifiedProducer/SubjetFilterJetProducer.cc RecoJets/JetProducers/plugins/
    cp BoostedTTH/BoostedProducer/plugins/ModifiedProducer/FastjetJetProducer.cc RecoJets/JetProducers/plugins/ 
    git clone git@github.com:cms-jet/JetToolbox.git JMEAnalysis/JetToolbox -b jetToolbox_80X_V2
    scram b -j 10
    scram b -j 10
    
    
Known issue: Running scram b for the first time results in error.
Fix: Run scram b multiple times.

## Overview
BoostedObjects contains the classes needed for subjet-analysis. They associate fat jets with the corresponding filtered objects.

BoostedProduces contains the tools used to run the HEPTopTagger and SubjetFilterJet algorithm on MiniAOD and add the output as the above collections.

BoostedAnalyzer can be used to analyze MiniAOD files. The plugin itself takes care of objectselections and stores the objects in InputCollections. Different event selection can be used in this step, too. The inputcollections can be analyzed with a TreeWriter that can load different Processors. Every processor writes a certain class of output variables in a flat TTree.
