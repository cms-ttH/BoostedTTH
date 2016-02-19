BoostedTTH
=======

CMSSW tools for analyzing TTH events with boosted objects

## Installation
Follow These Steps:

    export SCRAM_ARCH=slc6_amd64_gcc493
    scram project CMSSW_7_6_3
    cd CMSSW_7_6_3/src
    cmsenv   
    git cms-merge-topic gkasieczka:htt-v2-76X
    git clone https://github.com/cms-ttH/MiniAOD.git
    git clone https://github.com/cms-ttH/BoostedTTH.git -b CMSSW_7_6_3
    mkdir TTH
    cd TTH
    git clone https://github.com/cms-ttH/CommonClassifier.git -b subjet-restricted-perms-kit
    source CommonClassifier/setup/install_mem.sh
    cd $CMSSW_BASE/src
    scram b -j 10
    
## Overview
BoostedObjects contains the classes needed for subjet-analysis. They associate fat jets with the corresponding filtered objects.

BoostedProduces contains the tools used to run the HEPTopTagger and SubjetFilterJet algorithm on MiniAOD and add the output as the above collections.

BoostedAnalyzer can be used to analyze MiniAOD files. The plugin itself takes care of objectselections and stores the objects in InputCollections. Different event selection can be used in this step, too. The inputcollections can be analyzed with a TreeWriter that can load different Processors. Every processor writes a certain class of output variables in a flat TTree.
