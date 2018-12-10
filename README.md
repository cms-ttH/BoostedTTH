BoostedTTH
=======
CMSSW tools for analyzing TTH events with boosted objects

[![Build Status](https://mharrend.web.cern.ch/buildStatus/icon?job=cms-ttH/BoostedTTH/CMSSW_8_0_26_patch1)](https://mharrend.web.cern.ch/job/cms-ttH/job/BoostedTTH/job/CMSSW_8_0_26_patch1/)

## Installation
Follow These Steps:
If it is your first time setting up a CMSSW release CMSSW will create a hidden .cmsgit-cache directory in your home directory that can grow quite large. Therefore it is a good idea to specify the path of this directory to be on the dust (or other high volume storage)
Do for example:
export CMSSW_GIT_REFERENCE=/nfs/dust/cms/user/$USER/.cmsgit-cache

    # setup environment
    export SCRAM_ARCH="slc6_amd64_gcc630"
    export CMSSW_VERSION="CMSSW_9_4_9"
    
  
    # create new CMSSW environment
    scram project $CMSSW_VERSION
    cd $CMSSW_VERSION/src
    export CMSSWSRCDIR="$( pwd )"
    eval `scramv1 runtime -sh` 
    
    git cms-merge-topic yrath:deterministicSeeds
        
    git cms-merge-topic michaelwassmer:CMSSW_9_4_6_patch1_changed_SmearedJetProducer

    git cms-merge-topic cms-egamma:EgammaPostRecoTools_940 #just adds in an extra file to have a setup function to make things easier
    #git cms-merge-topic cms-egamma:Egamma80XMiniAODV2_946 #adds the c++ changes necessary to enable 2016 scale & smearing corrections (is loaded per default)
    git cms-merge-topic cms-met:METFixEE2017_949_v2 # EE noise mitigation for 2017 data
    
    # install common classifier
    mkdir TTH
    cd TTH
    git clone https://gitlab.cern.ch/ttH/CommonClassifier.git -b master
    source CommonClassifier/setup/install_mem.sh
    # use recent version of LHAPDF header
    sed -i '6i#include "LHAPDF/LHAPDF.h"' MEIntegratorStandalone/interface/Integrand.h
    sed -i '32i /*' MEIntegratorStandalone/interface/Integrand.h
    sed -i '44i */' MEIntegratorStandalone/interface/Integrand.h
    # install reco likelihood variables
    source CommonClassifier/setup/install_recoLikelihood.sh
    
    # install miniaod and boostedtth
    cd $CMSSWSRCDIR
    git clone -b CMSSW_9_4_5 https://github.com/cms-ttH/MiniAOD.git
    git clone -b CMSSW_9_4_3 https://github.com/cms-ttH/BoostedTTH.git
    
    # Download the JER correction files
    cd $CMSSWSRCDIR/BoostedTTH/BoostedAnalyzer/data
    mkdir jerfiles
    cd jerfiles
    wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Summer16_25nsV1_MC/Summer16_25nsV1_MC_PtResolution_AK4PFchs.txt"
    wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Summer16_25nsV1_MC/Summer16_25nsV1_MC_SF_AK4PFchs.txt"
    wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Summer16_25nsV1_MC/Summer16_25nsV1_MC_PtResolution_AK8PFchs.txt"
    wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Summer16_25nsV1_MC/Summer16_25nsV1_MC_SF_AK8PFchs.txt"
    cd $CMSSWSRCDIR
   
    #compile
    scram b -j 12
    
    ### only for crab use ###
    cp /cvmfs/cms.cern.ch/slc6_amd64_gcc630/external/gsl/2.2.1/lib/* $CMSSWSRCDIR/../lib/slc6_amd64_gcc630
    scram b -j 12
    
## Overview
BoostedObjects contains the classes needed for subjet-analysis. They associate fat jets with the corresponding filtered objects.

BoostedProduces contains the tools used to run the HEPTopTagger and SubjetFilterJet algorithm on MiniAOD and add the output as the above collections.

BoostedAnalyzer can be used to analyze MiniAOD files. The plugin itself takes care of objectselections and stores the objects in InputCollections. Different event selection can be used in this step, too. The inputcollections can be analyzed with a TreeWriter that can load different Processors. Every processor writes a certain class of output variables in a flat TTree.
