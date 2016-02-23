eval `scramv1 runtime -sh`

cmsRun /nfs/dust/cms/user/mharrend/ttHanalysis/CMSSW_7_4_14/src/BoostedTTH/BoostedAnalyzer/test/sync_muonEG_endof15Hbb_data_cfg.py

cmsRun /nfs/dust/cms/user/mharrend/ttHanalysis/CMSSW_7_4_14/src/BoostedTTH/BoostedAnalyzer/test/sync_singleMuon_endof15Hbb_data_cfg.py

mkdir KIT_syncHBB_data
mkdir KIT_syncHBB_data/onlySL
mkdir KIT_syncHBB_data/onlyDL

cp sync_singleMuon_endof15Hbb_data_raw.csv KIT_syncHBB_data/singleMuon_raw.csv
cp sync_singleMuon_endof15Hbb_data_JESdown.csv KIT_syncHBB_data/singleMuon_JESDown.csv
cp sync_singleMuon_endof15Hbb_data_JESup.csv KIT_syncHBB_data/singleMuon_JESUp.csv
cp sync_singleMuon_endof15Hbb_data.csv KIT_syncHBB_data/singleMuon.csv

cp sync_muonEG_endof15Hbb_data_raw.csv KIT_syncHBB_data/muonEG_raw.csv
cp sync_muonEG_endof15Hbb_data_JESdown.csv KIT_syncHBB_data/muonEG_JESDown.csv
cp sync_muonEG_endof15Hbb_data_JESup.csv KIT_syncHBB_data/muonEG_JESUp.csv
cp sync_muonEG_endof15Hbb_data.csv KIT_syncHBB_data/muonEG.csv


for i in KIT_syncHBB_data/*.csv; do echo "$i"; python /nfs/dust/cms/user/mharrend/ttHanalysis/CMSSW_7_4_14/src/BoostedTTH/BoostedAnalyzer/test/splitSLDL_data.py "$i"; done
