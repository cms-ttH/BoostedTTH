BoostedTTH - Regression for CMSSW 80X
=======

CMSSW tools for analyzing TTH events with boosted objects

## Installation
Follow These Steps:

    export SCRAM_ARCH=slc6_amd64_gcc530
    scram project CMSSW_8_0_12
    cd CMSSW_8_0_12/src
    cmsenv   
    git cms-merge-topic gkasieczka:htt-v2-76X
    git clone git@github.com:kschweiger/MiniAOD.git -b CMSSW_8_0_8
    git clone https://github.com/cms-ttH/BoostedTTH.git -b CMSSW_8_0_X_regression
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
    scram b -j 10
    
## Overview
BoostedObjects contains the classes needed for subjet-analysis. They associate fat jets with the corresponding filtered objects.

BoostedProduces contains the tools used to run the HEPTopTagger and SubjetFilterJet algorithm on MiniAOD and add the output as the above collections.

BoostedAnalyzer can be used to analyze MiniAOD files. The plugin itself takes care of objectselections and stores the objects in InputCollections. Different event selection can be used in this step, too. The inputcollections can be analyzed with a TreeWriter that can load different Processors. Every processor writes a certain class of output variables in a flat TTree.
