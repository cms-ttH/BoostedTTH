BoostedTTH
=======

CMSSW tools for analyzing TTH events with boosted objects

## Installation
Follow These Steps:

    # setup environment
    export SCRAM_ARCH="slc6_amd64_gcc530"
    export CMSSW_VERSION="CMSSW_8_0_25"
    scram project $CMSSW_VERSION
    cd $CMSSW_VERSION/src
    export CMSSW_SRC="$( pwd )"
    cmsenv
    
    # updated MET tools
    # this topic is branched from the official cms-met:METRecipe_8020 but fixes the badGlobalMuonTagger
    # so that it works like any other MET filter module
    git cms-merge-topic riga:badGlobalMuonTagger_fix

    # EGMSmearer and data
    git cms-merge-topic shervin86:Moriond2017_JEC_energyScales
    cd EgammaAnalysis/ElectronTools/data
    git clone https://github.com/ECALELFS/ScalesSmearings.git
    cd ../../..

    # ttHFGenFilter
    # (only required when you use the ttHF filtered ttJets dataset)
    #git cms-merge-topic riga:ttHFGenFilter_tagging
 
    # bjetness code
    git clone https://github.com/IHEP-CMS/BJetnessTTHbb.git
    cd BJetnessTTHbb/BJetness
    mkdir data
    cp -r /afs/cern.ch/work/f/fromeo/public/BJetnessTTHbb/JEC/ data/
    cp -r /afs/cern.ch/work/f/fromeo/public/BJetnessTTHbb/JER/ data/
    cd -
    
    # install common classifier
    mkdir TTH
    cd TTH
    git clone https://gitlab.cern.ch/ttH/CommonClassifier.git
    # use v0.2 of ME integration -- v0.3 does not compile with CMSSW
    sed -i 's|git clone https://github.com/jpata/Code.git MEIntegratorStandalone --branch v0.3|git clone https://github.com/bianchini/Code.git MEIntegratorStandalone --branch v0.2|g' CommonClassifier/setup/install_mem.sh
    source CommonClassifier/setup/install_mem.sh
    # use recent version of LHAPDF header
    sed -i '6i#include "LHAPDF/LHAPDF.h"' MEIntegratorStandalone/interface/Integrand.h
    sed -i '32i /*' MEIntegratorStandalone/interface/Integrand.h
    sed -i '44i */' MEIntegratorStandalone/interface/Integrand.h
    
    # install miniaod and boostedtth
    cd $CMSSW_BASE/src
    git clone https://github.com/cms-ttH/MiniAOD.git -b CMSSW_8_0_24_v1_sync
    git clone https://github.com/cms-ttH/BoostedTTH.git -b CMSSW_8_0_26_patch1
    
    # Download the JER correction files
    cd $CMSSW_BASE/src/BoostedTTH/BoostedAnalyzer/data
    mkdir jerfiles
    cd jerfiles
    wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Spring16_25nsV10_MC/Spring16_25nsV10_MC_PtResolution_AK4PFchs.txt"
    wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Spring16_25nsV10_MC/Spring16_25nsV10_MC_SF_AK4PFchs.txt"
    cd $CMSSW_BASE/src
    
    # hack to deactivate random JER smearing
    sed -i '248,259d' PhysicsTools/PatUtils/interface/SmearedJetProducerT.h
    
    #compile
    scram b -j10
    
## Overview
BoostedObjects contains the classes needed for subjet-analysis. They associate fat jets with the corresponding filtered objects.

BoostedProduces contains the tools used to run the HEPTopTagger and SubjetFilterJet algorithm on MiniAOD and add the output as the above collections.

BoostedAnalyzer can be used to analyze MiniAOD files. The plugin itself takes care of objectselections and stores the objects in InputCollections. Different event selection can be used in this step, too. The inputcollections can be analyzed with a TreeWriter that can load different Processors. Every processor writes a certain class of output variables in a flat TTree.
