BoostedTTH
=======

CMSSW tools for analyzing TTH events with boosted objects
!!! Danger !!!
The repository cms-btv-pog:bTagHIPMitigation-PR_from-CMSSW_8_0_17 apparently no longer exists. This means that some variables used in the config do not exist in CMSSW_8_0_19, which leads to failing jobs. If you checkout CMSSW_8_0_20 (which has these variables included) and skip the step with the HIPMitigation the jobs seem to work.

## Installation
Follow These Steps:

    export SCRAM_ARCH=slc6_amd64_gcc530
    scram project CMSSW_8_0_19
    cd CMSSW_8_0_19/src
    cmsenv   
    git cms-merge-topic -u cms-btv-pog:bTagHIPMitigation-PR_from-CMSSW_8_0_17    
    git cms-merge-topic gkasieczka:htt-v2-76X
    git clone https://github.com/cms-ttH/MiniAOD.git -b CMSSW_8_0_8_expICHEPLeptons
    git clone https://github.com/cms-ttH/BoostedTTH.git -b CMSSW_8_0_8_expICHEPLeptons
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
    scram b -j 10

Known issue: Running scram b for the first time results in error.
Fix: Run scram b multiple times.

## Overview
BoostedObjects contains the classes needed for subjet-analysis. They associate fat jets with the corresponding filtered objects.

BoostedProduces contains the tools used to run the HEPTopTagger and SubjetFilterJet algorithm on MiniAOD and add the output as the above collections.

BoostedAnalyzer can be used to analyze MiniAOD files. The plugin itself takes care of objectselections and stores the objects in InputCollections. Different event selection can be used in this step, too. The inputcollections can be analyzed with a TreeWriter that can load different Processors. Every processor writes a certain class of output variables in a flat TTree.
