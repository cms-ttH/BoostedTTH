CFG=/nfs/dust/cms/user/kelmorab/CMSSW9/CMSSW_9_4_6/src/BoostedTTH/BoostedAnalyzer/test/boostedAnalysis_ntuples-ICHEP18_sync_cfg.py
OUTFOLDER=/nfs/dust/cms/user/kelmorab/ICHEP18_sync/syncfiles
SCRIPTFOLDER=/nfs/dust/cms/user/kelmorab/ICHEP18_sync/syncscripts
SETUP="#!/bin/bash \nexport VO_CMS_SW_DIR=/cvmfs/cms.cern.ch; source \$VO_CMS_SW_DIR/cmsset_default.sh; cd /nfs/dust/cms/user/kelmorab/CMSSW9/CMSSW_9_4_6/src; eval \`scram runtime -sh\`;"

printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2//store/mc/RunIIFall17MiniAOD/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/94X_mc2017_realistic_v10-v1/00000/CC0FCC49-B50A-E811-9694-02163E0144C8.root' outName=${OUTFOLDER}/syncTTH globalTag=94X_mc2017_realistic_v13 systematicVariations=nominal" > ${SCRIPTFOLDER}/syncTTH.sh
