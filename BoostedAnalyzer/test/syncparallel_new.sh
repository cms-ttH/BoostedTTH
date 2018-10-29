CFG=/nfs/dust/cms/user/mwassmer/ttH_2018/dev/CMSSW_9_4_9/src/BoostedTTH/BoostedAnalyzer/test/boostedAnalysis_ntuples-ICHEP18_cg.py
OUTFOLDER=/nfs/dust/cms/user/mwassmer/ttH_2018/sync/syncfiles
SCRIPTFOLDER=/nfs/dust/cms/user/mwassmer/ttH_2018/sync/syncscripts
SETUP="#!/bin/bash \nexport VO_CMS_SW_DIR=/cvmfs/cms.cern.ch; source \$VO_CMS_SW_DIR/cmsset_default.sh; cd /nfs/dust/cms/user/mwassmer/ttH_2018/dev/CMSSW_9_4_9/src; eval \`scram runtime -sh\`;"

printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='root://xrootd-cms.infn.it///store/mc/RunIIFall17MiniAODv2/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/60000/AC628CE7-0169-E811-9C5E-00010100096B.root' isData=False outName=${OUTFOLDER}/syncTTH globalTag=94X_mc2017_realistic_v14 systematicVariations=nominal" > ${SCRIPTFOLDER}/syncTTH.sh

printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='root://xrootd-cms.infn.it///store/mc/RunIIFall17MiniAODv2/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/00000/64301B32-E742-E811-823F-0025905A60D0.root' isData=False outName=${OUTFOLDER}/syncTTbar globalTag=94X_mc2017_realistic_v14 systematicVariations=nominal" > ${SCRIPTFOLDER}/syncTTbar.sh
# 
# #######
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016B/SingleElectron/MINIAOD/03Feb2017_ver2-v2/110000/003B2C1F-50EB-E611-A8F1-002590E2D9FE.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016B/SingleElectron/MINIAOD/03Feb2017_ver2-v2/110000/0043D133-4DEB-E611-BFE4-003048F5ADEC.root' outName=${OUTFOLDER}/syncElrunB isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=el dataEra=2016B systematicVariations=nominal" > ${SCRIPTFOLDER}/syncElrunB.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016C/SingleElectron/MINIAOD/03Feb2017-v1/100000/02169BE7-81EB-E611-BB99-02163E0137CD.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016C/SingleElectron/MINIAOD/03Feb2017-v1/100000/0244B3B4-78EB-E611-9D42-0CC47A009E24.root' outName=${OUTFOLDER}/syncElrunC isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=el dataEra=2016C systematicVariations=nominal" > ${SCRIPTFOLDER}/syncElrunC.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016D/SingleElectron/MINIAOD/03Feb2017-v1/110000/001A5DEC-77EB-E611-95CD-0CC47A4C8EE8.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016D/SingleElectron/MINIAOD/03Feb2017-v1/110000/001F5992-6DEA-E611-AF62-A4BF01013DD5.root' outName=${OUTFOLDER}/syncElrunD isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=el dataEra=2016D systematicVariations=nominal" > ${SCRIPTFOLDER}/syncElrunD.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016E/SingleElectron/MINIAOD/03Feb2017-v1/110000/00022327-8BEA-E611-86CB-0025905B8566.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016E/SingleElectron/MINIAOD/03Feb2017-v1/110000/002070E4-1BEB-E611-BA80-0025905A608E.root' outName=${OUTFOLDER}/syncElrunE isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=el dataEra=2016E systematicVariations=nominal" > ${SCRIPTFOLDER}/syncElrunE.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016F/SingleElectron/MINIAOD/03Feb2017-v1/100000/00B336D6-6AEC-E611-8581-E0071B7AC7B0.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016F/SingleElectron/MINIAOD/03Feb2017-v1/100000/0229A4E9-5DEC-E611-B931-A0000420FE80.root' outName=${OUTFOLDER}/syncElrunF isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=el dataEra=2016F systematicVariations=nominal" > ${SCRIPTFOLDER}/syncElrunF.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016G/SingleElectron/MINIAOD/03Feb2017-v1/50000/004A75AB-B2EA-E611-B000-24BE05CEFDF1.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016G/SingleElectron/MINIAOD/03Feb2017-v1/50000/00539EDD-F8EA-E611-AC1D-0025900B5648.root' outName=${OUTFOLDER}/syncElrunG isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=el dataEra=2016G systematicVariations=nominal" > ${SCRIPTFOLDER}/syncElrunG.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/SingleElectron/MINIAOD/03Feb2017_ver2-v1/100000/00553E5F-29EC-E611-ADB0-00259074AE8C.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/SingleElectron/MINIAOD/03Feb2017_ver2-v1/100000/006EC85C-29EC-E611-B2E1-20CF3019DF17.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/SingleElectron/MINIAOD/03Feb2017_ver3-v1/110000/02973E99-69EC-E611-9913-5065F381A2F1.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/SingleElectron/MINIAOD/03Feb2017_ver3-v1/110000/04C8C9AF-62EC-E611-AB90-A0000420FE80.root' outName=${OUTFOLDER}/syncElrunH isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=el dataEra=2016H systematicVariations=nominal" > ${SCRIPTFOLDER}/syncElrunH.sh
# 
# ########
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016B/SingleMuon/MINIAOD/03Feb2017_ver2-v2/100000/000C6E52-8BEC-E611-B3FF-0025905C42FE.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016B/SingleMuon/MINIAOD/03Feb2017_ver2-v2/100000/001E3E7D-57EB-E611-8469-0CC47A7C35D2.root' outName=${OUTFOLDER}/syncMurunB isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=mu dataEra=2016B systematicVariations=nominal" > ${SCRIPTFOLDER}/syncMurunB.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016C/SingleMuon/MINIAOD/03Feb2017-v1/50000/001CF316-1AEB-E611-BBBD-0CC47A4C8EE2.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016C/SingleMuon/MINIAOD/03Feb2017-v1/50000/0022D65B-05EB-E611-84E9-0025905A6104.root' outName=${OUTFOLDER}/syncMurunC isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=mu dataEra=2016C systematicVariations=nominal" > ${SCRIPTFOLDER}/syncMurunC.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016D/SingleMuon/MINIAOD/03Feb2017-v1/100000/00622F98-20EB-E611-A0A4-28924A33AFF6.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016D/SingleMuon/MINIAOD/03Feb2017-v1/100000/023071E7-97EA-E611-A89A-0025904C67B6.root' outName=${OUTFOLDER}/syncMurunD isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=mu dataEra=2016D systematicVariations=nominal" > ${SCRIPTFOLDER}/syncMurunD.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016E/SingleMuon/MINIAOD/03Feb2017-v1/110000/001D567A-0CEB-E611-A438-D8D385AE8848.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016E/SingleMuon/MINIAOD/03Feb2017-v1/110000/004309C7-E6EA-E611-92B5-0025905A60DA.root' outName=${OUTFOLDER}/syncMurunE isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=mu dataEra=2016E systematicVariations=nominal" > ${SCRIPTFOLDER}/syncMurunE.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016F/SingleMuon/MINIAOD/03Feb2017-v1/100000/00E6AB6D-BCEC-E611-8F6E-0025905C3D98.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016F/SingleMuon/MINIAOD/03Feb2017-v1/100000/040B13AE-C3EC-E611-8082-0025904C6564.root' outName=${OUTFOLDER}/syncMurunF isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=mu dataEra=2016F systematicVariations=nominal" > ${SCRIPTFOLDER}/syncMurunF.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016G/SingleMuon/MINIAOD/03Feb2017-v1/100000/00E6DF50-70EA-E611-ACC4-0CC47A1E089C.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016G/SingleMuon/MINIAOD/03Feb2017-v1/100000/02382B19-D1EA-E611-B2F9-0CC47ABAC11C.root' outName=${OUTFOLDER}/syncMurunG isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=mu dataEra=2016G systematicVariations=nominal" > ${SCRIPTFOLDER}/syncMurunG.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/SingleMuon/MINIAOD/03Feb2017_ver2-v1/110000/00633FF0-85EA-E611-811C-001E674FB25C.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/SingleMuon/MINIAOD/03Feb2017_ver2-v1/110000/006517CB-8AEA-E611-8CF6-0CC47AC08BD4.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/SingleMuon/MINIAOD/03Feb2017_ver3-v1/80000/0040ECBB-76EA-E611-8FE7-A0000420FE80.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/SingleMuon/MINIAOD/03Feb2017_ver3-v1/80000/16F28614-84EA-E611-8083-A0369F310374.root' outName=${OUTFOLDER}/syncMurunH isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=mu dataEra=2016H systematicVariations=nominal" > ${SCRIPTFOLDER}/syncMurunH.sh
# 
# ########
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016B/DoubleEG/MINIAOD/03Feb2017_ver2-v2/50000/00054938-CEEA-E611-889E-0CC47A4D7650.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016B/DoubleEG/MINIAOD/03Feb2017_ver2-v2/50000/001BC16F-90EA-E611-87E2-F04DA27540BB.root' outName=${OUTFOLDER}/syncElElrunB isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=elel dataEra=2016B systematicVariations=nominal" > ${SCRIPTFOLDER}/syncElElrunB.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016C/DoubleEG/MINIAOD/03Feb2017-v1/80000/00371362-6AEC-E611-9845-842B2B758BAA.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016C/DoubleEG/MINIAOD/03Feb2017-v1/80000/006E86B9-77EC-E611-BA8F-02163E019CE7.root' outName=${OUTFOLDER}/syncElElrunC isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=elel dataEra=2016C systematicVariations=nominal" > ${SCRIPTFOLDER}/syncElElrunC.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016D/DoubleEG/MINIAOD/03Feb2017-v1/100000/002CE21C-0BEB-E611-8597-001E67E6F8E6.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016D/DoubleEG/MINIAOD/03Feb2017-v1/100000/006BB826-05EB-E611-97F4-0025904A8ED2.root' outName=${OUTFOLDER}/syncElElrunD isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=elel dataEra=2016D systematicVariations=nominal" > ${SCRIPTFOLDER}/syncElElrunD.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016E/DoubleEG/MINIAOD/03Feb2017-v1/110000/003AF399-ABEA-E611-92CF-002590E2DA08.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016E/DoubleEG/MINIAOD/03Feb2017-v1/110000/048E7FCD-98EA-E611-AB8A-002590D9D966.root' outName=${OUTFOLDER}/syncElElrunE isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=elel dataEra=2016E systematicVariations=nominal" > ${SCRIPTFOLDER}/syncElElrunE.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016F/DoubleEG/MINIAOD/03Feb2017-v1/80000/0006AFD8-F8EA-E611-9F9D-0CC47A13D09C.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016F/DoubleEG/MINIAOD/03Feb2017-v1/80000/00A7E4D9-F8EA-E611-A62B-002590E3A004.root' outName=${OUTFOLDER}/syncElElrunF isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=elel dataEra=2016F systematicVariations=nominal" > ${SCRIPTFOLDER}/syncElElrunF.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016G/DoubleEG/MINIAOD/03Feb2017-v1/100000/002F14FF-D0EA-E611-952E-008CFA197AF4.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016G/DoubleEG/MINIAOD/03Feb2017-v1/100000/02642443-F0EA-E611-9D24-008CFA197D74.root' outName=${OUTFOLDER}/syncElElrunG isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=elel dataEra=2016G systematicVariations=nominal" > ${SCRIPTFOLDER}/syncElElrunG.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/DoubleEG/MINIAOD/03Feb2017_ver2-v1/100000/023E858B-F7EC-E611-889C-047D7BD6DDF2.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/DoubleEG/MINIAOD/03Feb2017_ver2-v1/100000/02AD337A-95ED-E611-B1AE-047D7B881D90.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/DoubleEG/MINIAOD/03Feb2017_ver3-v1/1030000/D41C6358-4DF0-E611-BBAC-002590DB927A.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/DoubleEG/MINIAOD/03Feb2017_ver3-v1/110000/78C7FC4D-7CED-E611-870F-0CC47A7FC858.root' outName=${OUTFOLDER}/syncElElrunH isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=elel dataEra=2016H systematicVariations=nominal" > ${SCRIPTFOLDER}/syncElElrunH.sh
# 
# #######
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016B/MuonEG/MINIAOD/03Feb2017_ver2-v2/100000/0017ADAB-F6EC-E611-8C01-0090FAA57EA4.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016B/MuonEG/MINIAOD/03Feb2017_ver2-v2/100000/00680B67-A0EC-E611-ABC5-00259073E4E2.root' outName=${OUTFOLDER}/syncElMurunB isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=elmu dataEra=2016B systematicVariations=nominal" > ${SCRIPTFOLDER}/syncElMurunB.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016C/MuonEG/MINIAOD/03Feb2017-v1/110000/0649FFBD-50EC-E611-9875-24BE05CEEDE1.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016C/MuonEG/MINIAOD/03Feb2017-v1/110000/0AEA5448-35EC-E611-B1AF-A0369F310374.root' outName=${OUTFOLDER}/syncElMurunC isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=elmu dataEra=2016C systematicVariations=nominal" > ${SCRIPTFOLDER}/syncElMurunC.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016D/MuonEG/MINIAOD/03Feb2017-v1/80000/02264DFC-6EEB-E611-95AF-0090FAA572B0.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016D/MuonEG/MINIAOD/03Feb2017-v1/80000/0261593F-D6EA-E611-8577-0090FAA57630.root' outName=${OUTFOLDER}/syncElMurunD isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=elmu dataEra=2016D systematicVariations=nominal" > ${SCRIPTFOLDER}/syncElMurunD.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016E/MuonEG/MINIAOD/03Feb2017-v1/110000/00003F8D-05EB-E611-92D9-02163E019DC6.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016E/MuonEG/MINIAOD/03Feb2017-v1/110000/005F2FB7-7CEB-E611-9454-0CC47A745298.root' outName=${OUTFOLDER}/syncElMurunE isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=elmu dataEra=2016E systematicVariations=nominal" > ${SCRIPTFOLDER}/syncElMurunE.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016F/MuonEG/MINIAOD/03Feb2017-v1/50000/0496325A-05EB-E611-953B-0025905A60DE.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016F/MuonEG/MINIAOD/03Feb2017-v1/50000/0C20A32A-A6EA-E611-ADFB-0025905A60F8.root' outName=${OUTFOLDER}/syncElMurunF isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=elmu dataEra=2016F systematicVariations=nominal" > ${SCRIPTFOLDER}/syncElMurunF.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016G/MuonEG/MINIAOD/03Feb2017-v1/100000/08127890-99EC-E611-82BE-0CC47A7E6A6C.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016G/MuonEG/MINIAOD/03Feb2017-v1/100000/0ABB558F-99EC-E611-8484-002590DE6E6E.root' outName=${OUTFOLDER}/syncElMurunG isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=elmu dataEra=2016G systematicVariations=nominal" > ${SCRIPTFOLDER}/syncElMurunG.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/MuonEG/MINIAOD/03Feb2017_ver2-v1/100000/044366C7-4AEE-E611-8CF7-0025905B856E.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/MuonEG/MINIAOD/03Feb2017_ver2-v1/100000/04BB134D-3BEE-E611-B80E-0025905A48D6.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/MuonEG/MINIAOD/03Feb2017_ver3-v1/110000/10D7E08C-96EA-E611-9119-0025905B858E.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/MuonEG/MINIAOD/03Feb2017_ver3-v1/110000/1468B227-F4EA-E611-BF5A-0025905A60B6.root' outName=${OUTFOLDER}/syncElMurunH isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=elmu dataEra=2016H systematicVariations=nominal" > ${SCRIPTFOLDER}/syncElMurunH.sh
# 
# #######
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016B/DoubleMuon/MINIAOD/03Feb2017_ver2-v2/100000/0005AD9F-64ED-E611-A952-0CC47A78A42C.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016B/DoubleMuon/MINIAOD/03Feb2017_ver2-v2/100000/00415FAC-B5EC-E611-A1C9-00266CF3E130.root' outName=${OUTFOLDER}/syncMuMurunB isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=mumu dataEra=2016B systematicVariations=nominal" > ${SCRIPTFOLDER}/syncMuMurunB.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016C/DoubleMuon/MINIAOD/03Feb2017-v1/110000/02292378-59ED-E611-BA0B-0CC47A4D768E.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016C/DoubleMuon/MINIAOD/03Feb2017-v1/110000/022E014E-5FED-E611-BDCC-0025905B858E.root' outName=${OUTFOLDER}/syncMuMurunC isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=mumu dataEra=2016C systematicVariations=nominal" > ${SCRIPTFOLDER}/syncMuMurunC.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016D/DoubleMuon/MINIAOD/03Feb2017-v1/100000/00E0F123-F7ED-E611-9F34-0CC47A7FC736.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016D/DoubleMuon/MINIAOD/03Feb2017-v1/100000/025BE3ED-EBED-E611-95E9-047D7BD6DDA4.root' outName=${OUTFOLDER}/syncMuMurunD isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=mumu dataEra=2016D systematicVariations=nominal" > ${SCRIPTFOLDER}/syncMuMurunD.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016E/DoubleMuon/MINIAOD/03Feb2017-v1/100000/022FEC03-9AED-E611-9AE9-0025905A60B2.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016E/DoubleMuon/MINIAOD/03Feb2017-v1/100000/04328A2E-13ED-E611-BC83-0CC47A4D76D2.root' outName=${OUTFOLDER}/syncMuMurunE isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=mumu dataEra=2016E systematicVariations=nominal" > ${SCRIPTFOLDER}/syncMuMurunE.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016F/DoubleMuon/MINIAOD/03Feb2017-v1/100000/0055F5B5-76EB-E611-B313-002590D9D9FC.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016F/DoubleMuon/MINIAOD/03Feb2017-v1/100000/04B25C93-58EB-E611-86E4-002590FD5694.root' outName=${OUTFOLDER}/syncMuMurunF isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=mumu dataEra=2016F systematicVariations=nominal" > ${SCRIPTFOLDER}/syncMuMurunF.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016G/DoubleMuon/MINIAOD/03Feb2017-v1/100000/00182C13-EEEA-E611-8897-001E675A6C2A.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016G/DoubleMuon/MINIAOD/03Feb2017-v1/100000/007796A5-78EB-E611-8EFA-A4BF01011FD0.root' outName=${OUTFOLDER}/syncMuMurunG isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=mumu dataEra=2016G systematicVariations=nominal" > ${SCRIPTFOLDER}/syncMuMurunG.sh
# 
# printf "$SETUP cmsRun $CFG dumpSyncExe=True maxEvents=99999999 inputFiles='file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/DoubleMuon/MINIAOD/03Feb2017_ver2-v1/110000/08ADA6AA-D3EC-E611-AF17-B083FED42488.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/DoubleMuon/MINIAOD/03Feb2017_ver2-v1/110000/0A1CCEC7-78EC-E611-863C-141877411FED.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/DoubleMuon/MINIAOD/03Feb2017_ver3-v1/50000/36C4C2FB-4AEB-E611-ADD7-008CFA580778.root,file:/pnfs/desy.de/cms/tier2/store/data/Run2016H/DoubleMuon/MINIAOD/03Feb2017_ver3-v1/50000/44C1C1FB-4AEB-E611-9597-008CFA1113F4.root' outName=${OUTFOLDER}/syncMuMurunH isData=True globalTag=94X_dataRun2_ReReco_EOY17_v6 useJson=True dataset=mumu dataEra=2016H systematicVariations=nominal" > ${SCRIPTFOLDER}/syncMuMurunH.sh


# systematicVariations=nominal,JESPileUpDataMC,JESRelativeFSR
