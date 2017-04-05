CFG=/nfs/dust/cms/user/mwassmer/CMSSW_8_0_26_patch2/src/BoostedTTH/BoostedAnalyzer/test/boostedAnalysis_ntuples-Spring17_sync_cfg.py
OUTFOLDER=/nfs/dust/cms/user/mwassmer/Spring17_sync/syncfiles
SCRIPTFOLDER=/nfs/dust/cms/user/mwassmer/Spring17_sync/syncscripts
SETUP="#!/bin/bash \nexport VO_CMS_SW_DIR=/cvmfs/cms.cern.ch; source \$VO_CMS_SW_DIR/cmsset_default.sh; cd /nfs/dust/cms/user/mwassmer/CMSSW_8_0_26_patch2/src; eval \`scram runtime -sh\`;"

printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2//store/mc/RunIISummer16MiniAODv2/ttHTobb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/44949CF4-96C6-E611-B9A0-0025905A6122.root' outName=${OUTFOLDER}/syncTTH globalTag=80X_mcRun2_asymptotic_2016_TrancheIV_v8" > ${SCRIPTFOLDER}/syncTTH.sh

printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/mc/RunIISummer16MiniAODv2/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/0693E0E7-97BE-E611-B32F-0CC47A78A3D8.root' outName=${OUTFOLDER}/syncTTbar globalTag=80X_mcRun2_asymptotic_2016_TrancheIV_v8" > ${SCRIPTFOLDER}/syncTTbar.sh

printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016B/SingleElectron/MINIAOD/03Feb2017_ver2-v2/110000/003B2C1F-50EB-E611-A8F1-002590E2D9FE.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016B/SingleElectron/MINIAOD/03Feb2017_ver2-v2/110000/0043D133-4DEB-E611-BFE4-003048F5ADEC.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016C/SingleElectron/MINIAOD/03Feb2017-v1/100000/02169BE7-81EB-E611-BB99-02163E0137CD.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016C/SingleElectron/MINIAOD/03Feb2017-v1/100000/0244B3B4-78EB-E611-9D42-0CC47A009E24.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016D/SingleElectron/MINIAOD/03Feb2017-v1/110000/001A5DEC-77EB-E611-95CD-0CC47A4C8EE8.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016D/SingleElectron/MINIAOD/03Feb2017-v1/110000/001F5992-6DEA-E611-AF62-A4BF01013DD5.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016E/SingleElectron/MINIAOD/03Feb2017-v1/110000/00022327-8BEA-E611-86CB-0025905B8566.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016E/SingleElectron/MINIAOD/03Feb2017-v1/110000/002070E4-1BEB-E611-BA80-0025905A608E.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016F/SingleElectron/MINIAOD/03Feb2017-v1/100000/00B336D6-6AEC-E611-8581-E0071B7AC7B0.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016F/SingleElectron/MINIAOD/03Feb2017-v1/100000/0229A4E9-5DEC-E611-B931-A0000420FE80.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016G/SingleElectron/MINIAOD/03Feb2017-v1/50000/004A75AB-B2EA-E611-B000-24BE05CEFDF1.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016G/SingleElectron/MINIAOD/03Feb2017-v1/50000/00539EDD-F8EA-E611-AC1D-0025900B5648.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/SingleElectron/MINIAOD/03Feb2017_ver2-v1/100000/00553E5F-29EC-E611-ADB0-00259074AE8C.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/SingleElectron/MINIAOD/03Feb2017_ver2-v1/100000/006EC85C-29EC-E611-B2E1-20CF3019DF17.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/SingleElectron/MINIAOD/03Feb2017_ver3-v1/110000/02973E99-69EC-E611-9913-5065F381A2F1.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/SingleElectron/MINIAOD/03Feb2017_ver3-v1/110000/04C8C9AF-62EC-E611-AB90-A0000420FE80.root' outName=${OUTFOLDER}/syncElrunBtoH isData=True globalTag=80X_dataRun2_2016SeptRepro_v7 useJson=True dataset=el" > ${SCRIPTFOLDER}/syncElrunBtoH.sh

printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016B/SingleMuon/MINIAOD/03Feb2017_ver2-v2/100000/000C6E52-8BEC-E611-B3FF-0025905C42FE.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016B/SingleMuon/MINIAOD/03Feb2017_ver2-v2/100000/001E3E7D-57EB-E611-8469-0CC47A7C35D2.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016C/SingleMuon/MINIAOD/03Feb2017-v1/50000/001CF316-1AEB-E611-BBBD-0CC47A4C8EE2.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016C/SingleMuon/MINIAOD/03Feb2017-v1/50000/0022D65B-05EB-E611-84E9-0025905A6104.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016D/SingleMuon/MINIAOD/03Feb2017-v1/100000/00622F98-20EB-E611-A0A4-28924A33AFF6.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016D/SingleMuon/MINIAOD/03Feb2017-v1/100000/023071E7-97EA-E611-A89A-0025904C67B6.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016E/SingleMuon/MINIAOD/03Feb2017-v1/110000/001D567A-0CEB-E611-A438-D8D385AE8848.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016E/SingleMuon/MINIAOD/03Feb2017-v1/110000/004309C7-E6EA-E611-92B5-0025905A60DA.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016F/SingleMuon/MINIAOD/03Feb2017-v1/100000/00E6AB6D-BCEC-E611-8F6E-0025905C3D98.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016F/SingleMuon/MINIAOD/03Feb2017-v1/100000/040B13AE-C3EC-E611-8082-0025904C6564.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016G/SingleMuon/MINIAOD/03Feb2017-v1/100000/00E6DF50-70EA-E611-ACC4-0CC47A1E089C.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016G/SingleMuon/MINIAOD/03Feb2017-v1/100000/02382B19-D1EA-E611-B2F9-0CC47ABAC11C.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/SingleMuon/MINIAOD/03Feb2017_ver2-v1/110000/00633FF0-85EA-E611-811C-001E674FB25C.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/SingleMuon/MINIAOD/03Feb2017_ver2-v1/110000/006517CB-8AEA-E611-8CF6-0CC47AC08BD4.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/SingleMuon/MINIAOD/03Feb2017_ver3-v1/80000/0040ECBB-76EA-E611-8FE7-A0000420FE80.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/SingleMuon/MINIAOD/03Feb2017_ver3-v1/80000/16F28614-84EA-E611-8083-A0369F310374.root' outName=${OUTFOLDER}/syncElrunBtoH isData=True globalTag=80X_dataRun2_2016SeptRepro_v7 useJson=True dataset=mu" > ${SCRIPTFOLDER}/syncMurunBtoH.sh