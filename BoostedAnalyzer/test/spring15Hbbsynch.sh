cmsenv

cmsRun sync_tth_spring15Hbb_cfg.py

cmsRun sync_ttbar_spring15Hbb_cfg.py

mkdir KIT_syncHBB
mkdir KIT_syncHBB/onlySL
mkdir KIT_syncHBB/onlyDL

cp sync_tth_spring15Hbb_raw.csv KIT_syncHBB/tth_raw.csv
cp sync_tth_spring15Hbb_JESdown.csv KIT_syncHBB/tth_JESDown.csv
cp sync_tth_spring15Hbb_JESup.csv KIT_syncHBB/tth_JESUp.csv
cp sync_tth_spring15Hbb.csv KIT_syncHBB/tth.csv

cp sync_ttbar_spring15Hbb_raw.csv KIT_syncHBB/ttjets_raw.csv
cp sync_ttbar_spring15Hbb_JESdown.csv KIT_syncHBB/ttjets_JESDown.csv
cp sync_ttbar_spring15Hbb_JESup.csv KIT_syncHBB/ttjets_JESUp.csv
cp sync_ttbar_spring15Hbb.csv KIT_syncHBB/ttjets.csv

for i in KIT_syncHBB/*.csv; do echo "$i"; python splitSLDL.py "$i"; done
