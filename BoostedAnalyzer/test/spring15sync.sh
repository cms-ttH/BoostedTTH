cmsenv

cmsRun sync_mu_spring15_cfg.py

mv sync_mu_spring15_Dump1_2.txt mu_cut1_kit.txt
mv sync_mu_spring15_Dump1_3.txt mu_cut2_kit.txt
mv sync_mu_spring15_Dump1_5.txt mu_cut3_kit.txt
mv sync_mu_spring15_Dump1_6.txt mu_cut4_kit.txt
mv sync_mu_spring15_Dump1_7.txt mu_cut5_kit.txt
mv sync_mu_spring15_Dump1_8.txt mu_cut6_kit.txt
mv sync_mu_spring15_Dump1_9.txt mu_cut7_kit.txt
cat sync_mu_spring15_Cutflow.txt

cmsRun sync_el_spring15_cfg.py

mv sync_el_spring15_Dump1_2.txt ele_cut1_kit.txt
mv sync_el_spring15_Dump1_3.txt ele_cut2_kit.txt
mv sync_el_spring15_Dump1_5.txt ele_cut3_kit.txt
mv sync_el_spring15_Dump1_6.txt ele_cut4_kit.txt
mv sync_el_spring15_Dump1_7.txt ele_cut5_kit.txt
mv sync_el_spring15_Dump1_8.txt ele_cut6_kit.txt
mv sync_el_spring15_Dump1_9.txt ele_cut7_kit.txt
cat sync_el_spring15_Cutflow.txt

cat sync_mu_spring15_Cutflow.txt