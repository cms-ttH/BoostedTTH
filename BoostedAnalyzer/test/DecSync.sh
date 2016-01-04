eval `scramv1 runtime -sh`

cmsRun sync_mu_skim_decSyncHbb_cfg.py
cmsRun sync_el_skim_decSyncHbb_cfg.py
cmsRun sync_muel_skim_decSyncHbb_cfg.py

mkdir KIT_syncHBB_data
mkdir KIT_syncHBB_data/onlySL
mkdir KIT_syncHBB_data/onlyDL

cp sync_mu_skim_decSyncHbb_raw.csv KIT_syncHBB_data/singleMuon_raw.csv
cp sync_mu_skim_decSyncHbb_JESdown.csv KIT_syncHBB_data/singleMuon_JESDown.csv
cp sync_mu_skim_decSyncHbb_JESup.csv KIT_syncHBB_data/singleMuon_JESUp.csv
cp sync_mu_skim_decSyncHbb.csv KIT_syncHBB_data/singleMuon.csv

cp sync_el_skim_decSyncHbb_raw.csv KIT_syncHBB_data/singleElectron_raw.csv
cp sync_el_skim_decSyncHbb_JESdown.csv KIT_syncHBB_data/singleElectron_JESDown.csv
cp sync_el_skim_decSyncHbb_JESup.csv KIT_syncHBB_data/singleElectron_JESUp.csv
cp sync_el_skim_decSyncHbb.csv KIT_syncHBB_data/singleElectron.csv

cp sync_muel_skim_decSyncHbb_raw.csv KIT_syncHBB_data/muEG_raw.csv
cp sync_muel_skim_decSyncHbb_JESdown.csv KIT_syncHBB_data/muEG_JESDown.csv
cp sync_muel_skim_decSyncHbb_JESup.csv KIT_syncHBB_data/muEG_JESUp.csv
cp sync_muel_skim_decSyncHbb.csv KIT_syncHBB_data/muEG.csv


for i in KIT_syncHBB_data/*.csv; do echo "$i"; python /nfs/dust/cms/user/mharrend/ttHanalysis/CMSSW_7_4_14/src/BoostedTTH/BoostedAnalyzer/test/splitSLDL_data.py "$i"; done
