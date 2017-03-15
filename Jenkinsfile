pipeline {
  agent {
    node {
      label 'naf'
    }
    
  }
  stages {
    stage('Preparation') {
      steps {
        echo 'Start with preparations'
        mattermostSend(message: 'Start with preparations', channel: 'harrendorf-devel', endpoint: 'https://mattermost.ekp.kit.edu/hooks/73p15p59tjfdida9o3h9fxnfwe', icon: 'https://wiki.jenkins-ci.org/download/attachments/2916393/headshot.png?version=1&modificationDate=1302753947000')
      }
    }
    stage('Start script') {
      steps {
        echo 'Start script'
        node(label: 'naf') {
          sh '''#!/bin/zsh -l
# Use login shell

set -o xtrace
export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch 
source $VO_CMS_SW_DIR/cmsset_default.sh

# setup environment
export SCRAM_ARCH="slc6_amd64_gcc530"
export CMSSW_VERSION="CMSSW_8_0_26_patch1"

# Variables
export JENKINSUSERDIR=$USERNAME
export JENKINSINSTALLDIR="/nfs/dust/cms/user/"$JENKINSUSERDIR"/jenkins/Spring17-NTuple-Prod"
echo $JENKINSINSTALLDIR
export JENKINSCMSSWFOLDER=$CMSSW_VERSION
echo $JENKINSCMSSWFOLDER
export JENKINSCMSSWINSTALLDIR=$JENKINSINSTALLDIR"/"$JENKINSCMSSWFOLDER
echo $JENKINSCMSSWINSTALLDIR
export JENKINSCMSSWSRCDIR=$JENKINSCMSSWINSTALLDIR"/src"
echo $JENKINSCMSSWSRCDIR

# clean old environment before creating new one
mkdir -p $JENKINSINSTALLDIR
cd $JENKINSINSTALLDIR
rm -rf $JENKINSCMSSWINSTALLDIR
sleep 5

# create new CMSSW environment
scram project $JENKINSCMSSWFOLDER
cd $JENKINSCMSSWSRCDIR
eval `scramv1 runtime -sh` 

# updated MET tools
# this topic is branched from the official cms-met:METRecipe_8020 but fixes the badGlobalMuonTagger
# so that it works like any other MET filter module
git cms-merge-topic riga:badGlobalMuonTagger_fix

# EGMSmearer and data
git cms-merge-topic shervin86:Moriond2017_JEC_energyScales
cd EgammaAnalysis/ElectronTools/data
git clone --depth 1 https://github.com/ECALELFS/ScalesSmearings.git
cd $JENKINSCMSSWSRCDIR

# ttHFGenFilter
# (only required when you use the ttHF filtered ttJets dataset)
#git cms-merge-topic riga:ttHFGenFilter_tagging

# bjetness code
git clone --depth 1 https://github.com/IHEP-CMS/BJetnessTTHbb.git
cd BJetnessTTHbb/BJetness
mkdir data
cp -r /afs/cern.ch/work/f/fromeo/public/BJetnessTTHbb/JEC/ data/
cp -r /afs/cern.ch/work/f/fromeo/public/BJetnessTTHbb/JER/ data/
cd $JENKINSCMSSWSRCDIR

# install common classifier
mkdir TTH
cd TTH
git clone --depth 1 https://gitlab.cern.ch/ttH/CommonClassifier.git
source CommonClassifier/setup/install_mem.sh
# use recent version of LHAPDF header
sed -i '6i#include "LHAPDF/LHAPDF.h"' MEIntegratorStandalone/interface/Integrand.h
sed -i '32i /*' MEIntegratorStandalone/interface/Integrand.h
sed -i '44i */' MEIntegratorStandalone/interface/Integrand.h

# install miniaod and boostedtth
cd $JENKINSCMSSWSRCDIR
git clone  -b 'Spring17_v2' --single-branch --depth 1 https://github.com/cms-ttH/MiniAOD.git
git clone --depth 1 -b CMSSW_8_0_26_patch1 https://github.com/cms-ttH/BoostedTTH.git

# Download the JER correction files
cd $JENKINSCMSSWSRCDIR/BoostedTTH/BoostedAnalyzer/data
mkdir jerfiles
cd jerfiles
wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Spring16_25nsV10_MC/Spring16_25nsV10_MC_PtResolution_AK4PFchs.txt"
wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Spring16_25nsV10_MC/Spring16_25nsV10_MC_SF_AK4PFchs.txt"
cd $JENKINSCMSSWSRCDIR

# hack to deactivate random JER smearing
sed -i '248,259d' PhysicsTools/PatUtils/interface/SmearedJetProducerT.h

#compile
scram b -j10'''
        }
        
      }
    }
    stage('Deploy') {
      steps {
        echo 'Finishing...'
      }
    }
  }
}