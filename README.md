BoostedTTH
=======
CMSSW tools for analyzing Monotop events with boosted objects

## Installation
Follow These Steps:

To have the basic CMS functionalities, do

	source /cvmfs/cms.cern.ch/cmsset_default.sh

If it is your first time setting up a CMSSW release CMSSW will create a hidden .cmsgit-cache directory in your home directory that can grow quite large. Therefore it is a good idea to specify the path of this directory to be on the dust (or other high volume storage)
Do for example:

	export CMSSW_GIT_REFERENCE=/nfs/dust/cms/user/$USER/.cmsgit-cache

----
Next, you have to choose an architecture depending on the data anylsis period and the operating system.

#### Setup environment for 2016 and 2017 data analysis with CentOS 7
	export SCRAM_ARCH="slc7_amd64_gcc630"
	export CMSSW_VERSION="CMSSW_9_4_15"

#### Setup environment for 2016 and 2017 data analysis with SLC 6
	export SCRAM_ARCH="slc6_amd64_gcc630"
	export CMSSW_VERSION="CMSSW_9_4_15"

#### Setup environment for 2018 data analysis with SLC 6
	export SCRAM_ARCH="slc6_amd64_gcc700"
	export CMSSW_VERSION="CMSSW_10_2_18"

#### Setup environment for 2018 data analysis with CentOS 7
	export SCRAM_ARCH="slc7_amd64_gcc700"
	export CMSSW_VERSION="CMSSW_10_2_18"
---
The next steps can be followed as they are.

#### Create new CMSSW environment
	scram project $CMSSW_VERSION
	cd $CMSSW_VERSION/src
	export CMSSWSRCDIR="$( pwd )"
	cmsenv 

#### Producer to apply JER to jets
	if [[ $CMSSW_VERSION == "CMSSW_10_2_"* ]]; then    
	  git cms-merge-topic michaelwassmer:CMSSW_10_2_X_changed_SmearedJetProducer
	elif [[ $CMSSW_VERSION == "CMSSW_9_4_"* ]]; then
	  git cms-merge-topic michaelwassmer:CMSSW_9_4_X_changed_SmearedJetProducer
	else
	  echo "WRONG CMSSW VERSION"
	  return 1
	fi      

#### Adds function to easily recalculate electron/photon IDs and energy corrections
	git cms-merge-topic cms-egamma:EgammaPostRecoTools #just adds in an extra file to have a setup function to make things easier

#### Mitigation of EE noise to MET in 2017 data
	if [[ $CMSSW_VERSION == "CMSSW_10_2_"* ]]; then
	  git cms-merge-topic cms-met:METFixEE2017_949_v2_backport_to_102X
	elif [[ $CMSSW_VERSION == "CMSSW_9_4_"* ]]; then
	  git cms-merge-topic cms-met:METFixEE2017_949_v2 # EE noise mitigation for 2017 data
	else
	  echo "WRONG CMSSW VERSION"
	  return 1
	fi

#### Needed to run ecalBadCalibReducedMINIAODFilter
	git cms-addpkg RecoMET/METFilters

#### Needed to rerun DeepJet
	git cms-addpkg RecoBTag/TensorFlow
	git cherry-pick 94ceae257f846998c357fcad408986cc8a039152

#### Install common classifier (currently work in progress)
	mkdir TTH
	cd TTH
	git clone https://gitlab.cern.ch/ttH/CommonClassifier.git CommonClassifier -b 10_2X_MVAvars
	if [[ $CMSSW_VERSION == "CMSSW_10_2_"* ]]; then
	  git clone https://gitlab.cern.ch/algomez/MEIntegratorStandalone.git MEIntegratorStandalone -b 10_2_X
	elif [[ $CMSSW_VERSION == "CMSSW_9_4_"* ]]; then
	  git clone https://gitlab.cern.ch/algomez/MEIntegratorStandalone.git MEIntegratorStandalone
	else
	  echo "WRONG CMSSW VERSION"
	  return 1
	fi
	git clone https://gitlab.cern.ch/kit-cn-cms-public/RecoLikelihoodReconstruction.git RecoLikelihoodReconstruction
	mkdir -p $CMSSW_BASE/lib/$SCRAM_ARCH/
	cp -R MEIntegratorStandalone/libs/* $CMSSW_BASE/lib/$SCRAM_ARCH/
	scram setup lhapdf
	scram setup MEIntegratorStandalone/deps/gsl.xml
#### Use recent version of LHAPDF header
	sed -i '6i#include "LHAPDF/LHAPDF.h"' MEIntegratorStandalone/interface/Integrand.h
	sed -i '32i /*' MEIntegratorStandalone/interface/Integrand.h
	sed -i '44i */' MEIntegratorStandalone/interface/Integrand.h
#### Install reco likelihood variables (deprecated?)
	source CommonClassifier/setup/install_recoLikelihood.sh

#### Install miniaod and boostedtth
	cd $CMSSWSRCDIR
	git clone -b Legacy_2016_2017_2018_Devel https://github.com/cms-ttH/MiniAOD.git
	git clone -b Legacy_2016_2017_2018_MonoTop https://github.com/cms-ttH/BoostedTTH.git

#### Download the JER correction files (not needed at the moment)
	#cd $CMSSWSRCDIR/BoostedTTH/BoostedAnalyzer/data
	#mkdir jerfiles
	#cd jerfiles
##### 2017
	#wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Fall17_V3_MC/Fall17_V3_MC_PtResolution_AK4PFchs.txt"
	#wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Fall17_V3_MC/Fall17_V3_MC_SF_AK4PFchs.txt"
	#wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Fall17_V3_MC/Fall17_V3_MC_PtResolution_AK8PFchs.txt"
	#wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Fall17_V3_MC/Fall17_V3_MC_SF_AK8PFchs.txt"
##### 2016
	#wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Summer16_25nsV1_MC/Summer16_25nsV1_MC_PtResolution_AK4PFchs.txt"
	#wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Summer16_25nsV1_MC/Summer16_25nsV1_MC_SF_AK4PFchs.txt"
	#wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Summer16_25nsV1_MC/Summer16_25nsV1_MC_PtResolution_AK8PFchs.txt"
	#wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Summer16_25nsV1_MC/Summer16_25nsV1_MC_SF_AK8PFchs.txt"
##### 2018
	#wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Autumn18_V1_MC/Autumn18_V1_MC_SF_AK4PFchs.txt"
	#wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Autumn18_V1_MC/Autumn18_V1_MC_PtResolution_AK4PFchs.txt"
	#wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Autumn18_V1_MC/Autumn18_V1_MC_SF_AK8PFchs.txt"
	#wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Autumn18_V1_MC/Autumn18_V1_MC_PtResolution_AK8PFchs.txt"

	cd $CMSSWSRCDIR

#### Add JetToolbox
	git clone https://github.com/cms-jet/JetToolbox.git JMEAnalysis/JetToolbox -b jetToolbox_102X_v2

#### Update electron scale factors

	git cms-addpkg EgammaAnalysis/ElectronTools
	rm EgammaAnalysis/ElectronTools/data -rf
	git clone https://github.com/cms-data/EgammaAnalysis-ElectronTools.git EgammaAnalysis/ElectronTools/data

	#compile
	scram b -j 12

#### Only for crab use ###
	cp /cvmfs/cms.cern.ch/$SCRAM_ARCH/external/gsl/2.2.1/lib/* $CMSSWSRCDIR/../lib/$SCRAM_ARCH
	scram b -j 12
    
### Overview
BoostedAnalyzer can be used to analyze MiniAOD files. The plugin itself takes care of objectselections and stores the objects in InputCollections. Different event selection can be used in this step, too. The inputcollections can be analyzed with a TreeWriter that can load different Processors. Every processor writes a certain class of output variables in a flat TTree.
