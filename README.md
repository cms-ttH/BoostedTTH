BoostedTTH
=======
CMSSW tools for analyzing TTH events with boosted objects

[![Build Status](https://mharrend.web.cern.ch/buildStatus/icon?job=cms-ttH/BoostedTTH/CMSSW_8_0_26_patch1)](https://mharrend.web.cern.ch/job/cms-ttH/job/BoostedTTH/job/CMSSW_8_0_26_patch1/)

## Installation
Follow These Steps:

    # setup environment
    export SCRAM_ARCH="slc6_amd64_gcc530"
    export CMSSW_VERSION="CMSSW_8_0_26_patch2"
    
  
    # create new CMSSW environment
    scram project $CMSSW_VERSION
    cd $CMSSW_VERSION/src
    export JENKINSCMSSWSRCDIR="$( pwd )"
    eval `scramv1 runtime -sh` 
    
    git cms-merge-topic riga:deterministicSeeds
    
    # provide cut-based photon IDs
    git cms-merge-topic ikrav:egm_id_80X_v3_photons
    
    # updated MET tools
    # this topic is branched from the official cms-met:METRecipe_8020 but fixes the badGlobalMuonTagger
    # so that it works like any other MET filter module
    git cms-merge-topic riga:badGlobalMuonTagger_fix
    git cms-merge-topic cms-met:METRecipe_80X_part2
    git clone https://github.com/cms-met/MetTools.git
    
    # update PUJetId values
    git remote add ahinzmann https://github.com/ahinzmann/cmssw.git
    git fetch ahinzmann PUidMiniAODfix80
    git cherry-pick ca33756e1747aec27d13971bcfd0874b16724e7f

    # EGMSmearer and data
    git cms-merge-topic riga:deterministicEGMSmearer_v2
    cd EgammaAnalysis/ElectronTools/data
    git clone https://github.com/ECALELFS/ScalesSmearings.git -b Moriond17_gainSwitch_unc
    cd $JENKINSCMSSWSRCDIR
    
    git cms-merge-topic michaelwassmer:CMSSW_8_0_26_patch2_changed_SmearedJetProducer -s recursive -X theirs

    # ttHFGenFilter
    # (only required when you use the ttHF filtered ttJets dataset)
    #git cms-merge-topic riga:ttHFGenFilter_tagging
 
    # bjetness code
    #git clone --depth 1 https://github.com/IHEP-CMS/BJetnessTTHbb.git
    #cd BJetnessTTHbb/BJetness
    #mkdir data
    #cp -r /afs/cern.ch/work/f/fromeo/public/BJetnessTTHbb/JEC/ data/
    #cp -r /afs/cern.ch/work/f/fromeo/public/BJetnessTTHbb/JER/ data/
    #cd $JENKINSCMSSWSRCDIR
    
    # install common classifier
    mkdir TTH
    cd TTH
    git clone --depth 1 https://gitlab.cern.ch/ttH/CommonClassifier.git
    source CommonClassifier/setup/install_mem.sh
    # use recent version of LHAPDF header
    sed -i '6i#include "LHAPDF/LHAPDF.h"' MEIntegratorStandalone/interface/Integrand.h
    sed -i '32i /*' MEIntegratorStandalone/interface/Integrand.h
    sed -i '44i */' MEIntegratorStandalone/interface/Integrand.h
    # install reco likelihood variables
    source CommonClassifier/setup/install_recoLikelihood.sh
    
    # install miniaod and boostedtth
    cd $JENKINSCMSSWSRCDIR
    git clone --depth 1 -b CMSSW_8_0_26_patch2_DarkMatter https://github.com/cms-ttH/MiniAOD.git
    git clone --depth 1 -b CMSSW_8_0_26_patch2_DarkMatter https://github.com/cms-ttH/BoostedTTH.git
    
    # Download the JER correction files
    cd $JENKINSCMSSWSRCDIR/BoostedTTH/BoostedAnalyzer/data
    mkdir jerfiles
    cd jerfiles
    wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Spring16_25nsV10_MC/Spring16_25nsV10_MC_PtResolution_AK4PFchs.txt"
    wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Spring16_25nsV10_MC/Spring16_25nsV10_MC_SF_AK4PFchs.txt"
    cd $JENKINSCMSSWSRCDIR
   
    #compile
    scram b -j 12
    
    ### only for crab use ###
    cp /cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/gsl/2.2.1/lib/* $JENKINSCMSSWSRCDIR/../lib/slc6_amd64_gcc530
    scram b -j 12
    
## Overview
BoostedObjects contains the classes needed for subjet-analysis. They associate fat jets with the corresponding filtered objects.

BoostedProduces contains the tools used to run the HEPTopTagger and SubjetFilterJet algorithm on MiniAOD and add the output as the above collections.

BoostedAnalyzer can be used to analyze MiniAOD files. The plugin itself takes care of objectselections and stores the objects in InputCollections. Different event selection can be used in this step, too. The inputcollections can be analyzed with a TreeWriter that can load different Processors. Every processor writes a certain class of output variables in a flat TTree.
