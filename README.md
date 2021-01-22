BoostedTTH
=======
CMSSW tools for analyzing TTH events with boosted objects

[![Build Status](https://mharrend.web.cern.ch/buildStatus/icon?job=cms-ttH/BoostedTTH/CMSSW_8_0_26_patch1)](https://mharrend.web.cern.ch/job/cms-ttH/job/BoostedTTH/job/CMSSW_8_0_26_patch1/)

## Installation
Follow These Steps:
If it is your first time setting up a CMSSW release CMSSW will create a hidden .cmsgit-cache directory in your home directory that can grow quite large. Therefore it is a good idea to specify the path of this directory to be on the dust (or other high volume storage)
Do for example:
#export CMSSW_GIT_REFERENCE=/nfs/dust/cms/user/$USER/.cmsgit-cache

    # setup environment
    # SL6
    #export SCRAM_ARCH="slc6_amd64_gcc700"
    # CC7
    export SCRAM_ARCH="slc7_amd64_gcc700"

    export CMSSW_VERSION="CMSSW_10_2_18"

    # create new CMSSW environment
    scram project $CMSSW_VERSION
    cd $CMSSW_VERSION/src
    export CMSSWSRCDIR="$( pwd )"
    eval `scramv1 runtime -sh` 

    # producer of deterministic seeds for physics objects to be able to do synchronization

    # producer to apply JER to jets
    git cms-merge-topic sebwieland:CMSSW_10_2_X_SmearedJetProducer
    # producer of deterministic seeds for physics objects to be able to do synchronization
    git cms-merge-topic yrath:deterministicSeeds_102X

    # adds function to easily recalculate electron/photon IDs and energy corrections
    git cms-merge-topic cms-egamma:EgammaPostRecoTools #just adds in an extra file to have a setup function to make things easier

    # mitigation of EE noise to MET in 2017 data
    git cms-merge-topic cms-met:METFixEE2017_949_v2_backport_to_102X

    # needed to run ecalBadCalibReducedMINIAODFilter
    git cms-addpkg RecoMET/METFilters

    # needed to rerun DeepJet
    git cms-addpkg RecoBTag/TensorFlow
    git cherry-pick 94ceae257f846998c357fcad408986cc8a039152

    # install common classifier (currently work in progress)
    mkdir TTH
    cd TTH
    git clone https://gitlab.cern.ch/ttH/CommonClassifier.git CommonClassifier -b 10_2X_MVAvars
    git clone https://gitlab.cern.ch/algomez/MEIntegratorStandalone.git MEIntegratorStandalone -b 10_2_X

    mkdir -p $CMSSW_BASE/lib/$SCRAM_ARCH/
    cp -R MEIntegratorStandalone/libs/* $CMSSW_BASE/lib/$SCRAM_ARCH/
    scram setup lhapdf
    scram setup MEIntegratorStandalone/deps/gsl.xml
    # use recent version of LHAPDF header
    sed -i '6i#include "LHAPDF/LHAPDF.h"' MEIntegratorStandalone/interface/Integrand.h
    sed -i '32i /*' MEIntegratorStandalone/interface/Integrand.h
    sed -i '44i */' MEIntegratorStandalone/interface/Integrand.h
    # install reco likelihood variables (deprecated?)
    source CommonClassifier/setup/install_recoLikelihood.sh

    # install miniaod and boostedtth
    cd $CMSSWSRCDIR
    git clone -b Legacy_2016_2017_2018_Devel https://github.com/cms-ttH/MiniAOD.git
    git clone -b Legacy_2016_2017_2018_Devel https://github.com/cms-ttH/BoostedTTH.git

    # Download the JER correction files
    cd $CMSSWSRCDIR/BoostedTTH/BoostedAnalyzer/data
    mkdir jerfiles
    cd jerfiles
    # 2017
    wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Fall17_V3_MC/Fall17_V3_MC_PtResolution_AK4PFchs.txt"
    wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Fall17_V3_MC/Fall17_V3_MC_SF_AK4PFchs.txt"
    wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Fall17_V3_MC/Fall17_V3_MC_PtResolution_AK8PFchs.txt"
    wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Fall17_V3_MC/Fall17_V3_MC_SF_AK8PFchs.txt"
    # 2016
    wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Summer16_25nsV1_MC/Summer16_25nsV1_MC_PtResolution_AK4PFchs.txt"
    wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Summer16_25nsV1_MC/Summer16_25nsV1_MC_SF_AK4PFchs.txt"
    wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Summer16_25nsV1_MC/Summer16_25nsV1_MC_PtResolution_AK8PFchs.txt"
    wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Summer16_25nsV1_MC/Summer16_25nsV1_MC_SF_AK8PFchs.txt"
    # 2018
    wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Autumn18_V1_MC/Autumn18_V7_MC_SF_AK4PFchs.txt"
    wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Autumn18_V1_MC/Autumn18_V7_MC_PtResolution_AK4PFchs.txt"
    wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Autumn18_V1_MC/Autumn18_V7_MC_SF_AK8PFchs.txt"
    wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Autumn18_V1_MC/Autumn18_V7_MC_PtResolution_AK8PFchs.txt"

    cd $CMSSWSRCDIR

    #compile
    scram b -j 12

    ### only for crab use ###
    cp /cvmfs/cms.cern.ch/$SCRAM_ARCH/external/gsl/2.2.1/lib/* $CMSSWSRCDIR/../lib/$SCRAM_ARCH
    scram b -j 12
    
## Overview
BoostedObjects contains the classes needed for subjet-analysis. They associate fat jets with the corresponding filtered objects.

BoostedProduces contains the tools used to run the HEPTopTagger and SubjetFilterJet algorithm on MiniAOD and add the output as the above collections.

BoostedAnalyzer can be used to analyze MiniAOD files. The plugin itself takes care of objectselections and stores the objects in InputCollections. Different event selection can be used in this step, too. The inputcollections can be analyzed with a TreeWriter that can load different Processors. Every processor writes a certain class of output variables in a flat TTree.
