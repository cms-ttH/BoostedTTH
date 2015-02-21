#include "BoostedTTH/BoostedAnalyzer/interface/BDTVarProcessor.hpp"
using namespace std;

BDTVarProcessor::BDTVarProcessor(){}
BDTVarProcessor::~BDTVarProcessor(){}


void BDTVarProcessor::Init(const InputCollections& input,VariableContainer& vars){
  vars.InitVar("Evt_FinalBDT",-3);
  vars.InitVar("Evt_ttbbBDT",-3);

  map<TString,float*> pointto;
  
  pointto["abs(dEta_hadtop_bb)"]=vars.GetFloatVarPointer("Evt_Deta_TopHad_BB_Ohio");
  pointto["abs(dEta_leptop_bb)"]=vars.GetFloatVarPointer("Evt_Deta_TopLep_BB_Ohio");
  pointto["all_sum_pt_with_met"]=vars.GetFloatVarPointer("Evt_HT");
  pointto["aplanarity"]=vars.GetFloatVarPointer("Evt_Aplanarity");
  pointto["avg_btag_disc_btags"]=vars.GetFloatVarPointer("Evt_CSV_Average");
  pointto["avg_dr_tagged_jets"]=vars.GetFloatVarPointer("Evt_Dr_TaggedJetsAverage");
  pointto["best_higgs_mass"]=vars.GetFloatVarPointer("Evt_Best_Higgs_Mass_Ohio");
  pointto["closest_tagged_dijet_mass"]=vars.GetFloatVarPointer("Evt_M_MinDeltaRTaggedJets");
  pointto["dEta_fn"]=vars.GetFloatVarPointer("Evt_Deta_Fn_Ohio");
  pointto["dev_from_avg_disc_btags"]=vars.GetFloatVarPointer("Evt_CSV_Dev");
  pointto["dr_between_lep_and_closest_jet"]=vars.GetFloatVarPointer("Evt_M_MinDeltaRLeptonJet");
  pointto["dRbb"]=vars.GetFloatVarPointer("Evt_Dr_BB_Ohio");
  pointto["first_jet_pt"]=vars.GetArrayVarPointer("Jet_Pt",0);
  pointto["fourth_highest_btag"]=vars.GetArrayVarPointer("CSV",3);
  pointto["fourth_jet_pt"]=vars.GetArrayVarPointer("Jet_Pt",3);
  pointto["h0"]=vars.GetFloatVarPointer("Evt_H0");
  pointto["h1"]=vars.GetFloatVarPointer("Evt_H1");
  pointto["h2"]=vars.GetFloatVarPointer("Evt_H2");
  pointto["h3"]=vars.GetFloatVarPointer("Evt_H3");
  pointto["HT"]=vars.GetFloatVarPointer("Evt_HT_Jets");
  pointto["invariant_mass_of_everything"]=vars.GetFloatVarPointer("Evt_M_Total");
  pointto["lowest_btag"]=vars.GetFloatVarPointer("Evt_CSV_Min");
  pointto["M3"]=vars.GetFloatVarPointer("Evt_M3");
  pointto["maxeta_jet_jet"]=vars.GetFloatVarPointer("Evt_MaxDeta_Jets_Jet");
  pointto["maxeta_jet_tag"]=vars.GetFloatVarPointer("Evt_MaxDeta_Jets_TaggedJet");
  pointto["maxeta_tag_tag"]=vars.GetFloatVarPointer("Evt_MaxDeta_TaggedJets_TaggedJet");
  pointto["median_bb_mass"]=vars.GetFloatVarPointer("Evt_M_MedianTaggedJets");
  pointto["MET"]=vars.GetFloatVarPointer("Evt_Pt_MET");
  pointto["MHT"]=vars.GetFloatVarPointer("Evt_MHT");
  pointto["min_dr_tagged_jets"]=vars.GetFloatVarPointer("Evt_Dr_MinDeltaRJets");
  pointto["Mlb"]=vars.GetFloatVarPointer("Evt_M_MinDeltaRLeptonTaggedJet");
  pointto["pt_all_jets_over_E_all_jets"]=vars.GetFloatVarPointer("Evt_JetPtOverJetE");
  pointto["second_highest_btag"]=vars.GetArrayVarPointer("CSV",1);
  pointto["second_jet_pt"]=vars.GetArrayVarPointer("Jet_Pt",1);
  pointto["sphericity"]=vars.GetFloatVarPointer("Evt_Sphericity");
  pointto["tagged_dijet_mass_closest_to_125"]=vars.GetFloatVarPointer("Evt_M_TaggedJetsClosestTo125");
  pointto["third_highest_btag"]=vars.GetArrayVarPointer("CSV",2);
  pointto["third_jet_pt"]=vars.GetArrayVarPointer("Jet_Pt",2);

  pointto["ttbb_tth_MVA_output_5j4t"]=vars.GetFloatVarPointer("Evt_ttbbBDT");
  pointto["ttbb_tth_MVA_output_6j3t"]=vars.GetFloatVarPointer("Evt_ttbbBDT");
  pointto["ttbb_tth_ANN_output"]=vars.GetFloatVarPointer("Evt_ttbbBDT");

  TString weightPath=  BoostedUtils::GetAnalyzerPath()+"/data/bdtweights/ohio_weights/";

  readerMap["ttbb54"]=new TMVA::Reader();
  readerMap["ttbb54"]->AddVariable("avg_dr_tagged_jets",pointto["avg_dr_tagged_jets"]);
  readerMap["ttbb54"]->AddVariable("maxeta_tag_tag",pointto["maxeta_tag_tag"]);
  readerMap["ttbb54"]->AddVariable("h1",pointto["h1"]);
  readerMap["ttbb54"]->AddVariable("h3",pointto["h3"]);
  readerMap["ttbb54"]->AddVariable("all_sum_pt_with_met",pointto["all_sum_pt_with_met"]);
  readerMap["ttbb54"]->AddVariable("tagged_dijet_mass_closest_to_125",pointto["tagged_dijet_mass_closest_to_125"]);
  readerMap["ttbb54"]->AddVariable("MET",pointto["MET"]);
  readerMap["ttbb54"]->AddVariable("aplanarity",pointto["aplanarity"]);
  readerMap["ttbb54"]->AddVariable("pt_all_jets_over_E_all_jets",pointto["pt_all_jets_over_E_all_jets"]);
  readerMap["ttbb54"]->AddVariable("fourth_highest_btag",pointto["fourth_highest_btag"]);
  readerMap["ttbb54"]->BookMVA("BDT",weightPath+"540000/TMVAClassification_BDT.weights.xml");

  readerMap["ttbb63"]=new TMVA::Reader();
  readerMap["ttbb63"]->AddVariable("sphericity",pointto["sphericity"]);
  readerMap["ttbb63"]->AddVariable("h3",pointto["h3"]);
  readerMap["ttbb63"]->AddVariable("maxeta_jet_jet",pointto["maxeta_jet_jet"]);
  readerMap["ttbb63"]->AddVariable("maxeta_jet_tag",pointto["maxeta_jet_tag"]);
  readerMap["ttbb63"]->AddVariable("maxeta_tag_tag",pointto["maxeta_tag_tag"]);
  readerMap["ttbb63"]->AddVariable("abs(dEta_leptop_bb)",pointto["abs(dEta_leptop_bb)"]);
  readerMap["ttbb63"]->AddVariable("abs(dEta_hadtop_bb)",pointto["abs(dEta_hadtop_bb)"]);
  readerMap["ttbb63"]->AddVariable("dEta_fn",pointto["dEta_fn"]);
  readerMap["ttbb63"]->AddVariable("M3",pointto["M3"]);
  readerMap["ttbb63"]->AddVariable("min_dr_tagged_jets",pointto["min_dr_tagged_jets"]);
  readerMap["ttbb63"]->AddVariable("pt_all_jets_over_E_all_jets",pointto["pt_all_jets_over_E_all_jets"]);
  readerMap["ttbb63"]->AddVariable("aplanarity",pointto["aplanarity"]);
  readerMap["ttbb63"]->AddVariable("h1",pointto["h1"]);
  readerMap["ttbb63"]->AddVariable("tagged_dijet_mass_closest_to_125",pointto["tagged_dijet_mass_closest_to_125"]);
  readerMap["ttbb63"]->AddVariable("third_jet_pt",pointto["third_jet_pt"]);
  readerMap["ttbb63"]->BookMVA("BDT",weightPath+"630000/TMVAClassification_BDT.weights.xml");

  readerMap["ttbb64"]=new TMVA::Reader();
  readerMap["ttbb64"]->AddVariable("avg_dr_tagged_jets",pointto["avg_dr_tagged_jets"]);
  readerMap["ttbb64"]->AddVariable("sphericity",pointto["sphericity"]);
  readerMap["ttbb64"]->AddVariable("avg_btag_disc_btags",pointto["avg_btag_disc_btags"]);
  readerMap["ttbb64"]->AddVariable("closest_tagged_dijet_mass",pointto["closest_tagged_dijet_mass"]);
  readerMap["ttbb64"]->AddVariable("h3",pointto["h3"]);
  readerMap["ttbb64"]->AddVariable("invariant_mass_of_everything",pointto["invariant_mass_of_everything"]);
  readerMap["ttbb64"]->AddVariable("best_higgs_mass",pointto["best_higgs_mass"]);
  readerMap["ttbb64"]->AddVariable("dRbb",pointto["dRbb"]);
  readerMap["ttbb64"]->AddVariable("maxeta_jet_tag",pointto["maxeta_jet_tag"]);
  readerMap["ttbb64"]->AddVariable("maxeta_tag_tag",pointto["maxeta_tag_tag"]);
  readerMap["ttbb64"]->AddVariable("abs(dEta_leptop_bb)",pointto["abs(dEta_leptop_bb)"]);
  readerMap["ttbb64"]->AddVariable("abs(dEta_hadtop_bb)",pointto["abs(dEta_hadtop_bb)"]);
  readerMap["ttbb64"]->AddVariable("dEta_fn",pointto["dEta_fn"]);
  readerMap["ttbb64"]->AddVariable("median_bb_mass",pointto["median_bb_mass"]);
  readerMap["ttbb64"]->AddVariable("pt_all_jets_over_E_all_jets",pointto["pt_all_jets_over_E_all_jets"]);
  readerMap["ttbb64"]->BookMVA("BDT",weightPath+"640203/TMVAClassification_BDT.weights.xml");

  readerMap["final43"]=new TMVA::Reader();
  readerMap["final43"]->AddVariable("MET",pointto["MET"]);
  readerMap["final43"]->AddVariable("first_jet_pt",pointto["first_jet_pt"]);
  readerMap["final43"]->AddVariable("second_jet_pt",pointto["second_jet_pt"]);
  readerMap["final43"]->AddVariable("third_jet_pt",pointto["third_jet_pt"]);
  readerMap["final43"]->AddVariable("fourth_jet_pt",pointto["fourth_jet_pt"]);
  readerMap["final43"]->AddVariable("all_sum_pt_with_met",pointto["all_sum_pt_with_met"]);
  readerMap["final43"]->AddVariable("HT",pointto["HT"]);
  readerMap["final43"]->AddVariable("MHT",pointto["MHT"]);
  readerMap["final43"]->AddVariable("third_highest_btag",pointto["third_highest_btag"]);
  readerMap["final43"]->AddVariable("M3",pointto["M3"]);
  readerMap["final43"]->BookMVA("BDT",weightPath+"433/TMVAClassification_BDT.weights.xml");

  readerMap["final44"]=new TMVA::Reader();
  readerMap["final44"]->AddVariable("first_jet_pt",pointto["first_jet_pt"]);
  readerMap["final44"]->AddVariable("second_jet_pt",pointto["second_jet_pt"]);
  readerMap["final44"]->AddVariable("fourth_jet_pt",pointto["fourth_jet_pt"]);
  readerMap["final44"]->AddVariable("all_sum_pt_with_met",pointto["all_sum_pt_with_met"]);
  readerMap["final44"]->AddVariable("HT",pointto["HT"]);
  readerMap["final44"]->AddVariable("avg_btag_disc_btags",pointto["avg_btag_disc_btags"]);
  readerMap["final44"]->AddVariable("second_highest_btag",pointto["second_highest_btag"]);
  readerMap["final44"]->AddVariable("third_highest_btag",pointto["third_highest_btag"]);
  readerMap["final44"]->AddVariable("fourth_highest_btag",pointto["fourth_highest_btag"]);
  readerMap["final44"]->AddVariable("M3",pointto["M3"]);
  readerMap["final44"]->BookMVA("BDT",weightPath+"443/TMVAClassification_BDT.weights.xml");

  readerMap["final53"]=new TMVA::Reader();
  readerMap["final53"]->AddVariable("first_jet_pt",pointto["first_jet_pt"]);
  readerMap["final53"]->AddVariable("second_jet_pt",pointto["second_jet_pt"]);
  readerMap["final53"]->AddVariable("third_jet_pt",pointto["third_jet_pt"]);
  readerMap["final53"]->AddVariable("fourth_jet_pt",pointto["fourth_jet_pt"]);
  readerMap["final53"]->AddVariable("all_sum_pt_with_met",pointto["all_sum_pt_with_met"]);
  readerMap["final53"]->AddVariable("HT",pointto["HT"]);
  readerMap["final53"]->AddVariable("avg_btag_disc_btags",pointto["avg_btag_disc_btags"]);
  readerMap["final53"]->AddVariable("third_highest_btag",pointto["third_highest_btag"]);
  readerMap["final53"]->AddVariable("fourth_highest_btag",pointto["fourth_highest_btag"]);
  readerMap["final53"]->AddVariable("pt_all_jets_over_E_all_jets",pointto["pt_all_jets_over_E_all_jets"]);
  readerMap["final53"]->BookMVA("BDT",weightPath+"533/TMVAClassification_BDT.weights.xml");

  readerMap["final54"]=new TMVA::Reader();
  readerMap["final54"]->AddVariable("all_sum_pt_with_met",pointto["all_sum_pt_with_met"]);
  readerMap["final54"]->AddVariable("avg_dr_tagged_jets",pointto["avg_dr_tagged_jets"]);
  readerMap["final54"]->AddVariable("avg_btag_disc_btags",pointto["avg_btag_disc_btags"]);
  readerMap["final54"]->AddVariable("dev_from_avg_disc_btags",pointto["dev_from_avg_disc_btags"]);
  readerMap["final54"]->AddVariable("lowest_btag",pointto["lowest_btag"]);
  readerMap["final54"]->AddVariable("second_highest_btag",pointto["second_highest_btag"]);
  readerMap["final54"]->AddVariable("third_highest_btag",pointto["third_highest_btag"]);
  readerMap["final54"]->AddVariable("maxeta_jet_tag",pointto["maxeta_jet_tag"]);
  readerMap["final54"]->AddVariable("pt_all_jets_over_E_all_jets",pointto["pt_all_jets_over_E_all_jets"]);
  readerMap["final54"]->AddVariable("ttbb_tth_MVA_output_5j4t",pointto["ttbb_tth_MVA_output_5j4t"]);
  readerMap["final54"]->BookMVA("BDT",weightPath+"543/TMVAClassification_BDT.weights.xml");

  readerMap["final62"]=new TMVA::Reader();
  readerMap["final62"]->AddVariable("all_sum_pt_with_met",pointto["all_sum_pt_with_met"]);
  readerMap["final62"]->AddVariable("HT",pointto["HT"]);
  readerMap["final62"]->AddVariable("sphericity",pointto["sphericity"]);
  readerMap["final62"]->AddVariable("dr_between_lep_and_closest_jet",pointto["dr_between_lep_and_closest_jet"]);
  readerMap["final62"]->AddVariable("h2",pointto["h2"]);
  readerMap["final62"]->AddVariable("third_highest_btag",pointto["third_highest_btag"]);
  readerMap["final62"]->AddVariable("fourth_highest_btag",pointto["fourth_highest_btag"]);
  readerMap["final62"]->AddVariable("maxeta_jet_jet",pointto["maxeta_jet_jet"]);
  readerMap["final62"]->AddVariable("Mlb",pointto["Mlb"]);
  readerMap["final62"]->AddVariable("pt_all_jets_over_E_all_jets",pointto["pt_all_jets_over_E_all_jets"]);
  readerMap["final62"]->BookMVA("BDT",weightPath+"623/TMVAClassification_BDT.weights.xml");

  readerMap["final63"]=new TMVA::Reader();
  readerMap["final63"]->AddVariable("h0",pointto["h0"]);
  readerMap["final63"]->AddVariable("all_sum_pt_with_met",pointto["all_sum_pt_with_met"]);
  readerMap["final63"]->AddVariable("sphericity",pointto["sphericity"]);
  readerMap["final63"]->AddVariable("avg_btag_disc_btags",pointto["avg_btag_disc_btags"]);
  readerMap["final63"]->AddVariable("second_highest_btag",pointto["second_highest_btag"]);
  readerMap["final63"]->AddVariable("third_highest_btag",pointto["third_highest_btag"]);
  readerMap["final63"]->AddVariable("fourth_highest_btag",pointto["fourth_highest_btag"]);
  readerMap["final63"]->AddVariable("maxeta_jet_jet",pointto["maxeta_jet_jet"]);
  readerMap["final63"]->AddVariable("pt_all_jets_over_E_all_jets",pointto["pt_all_jets_over_E_all_jets"]);
  readerMap["final63"]->AddVariable("ttbb_tth_MVA_output_6j3t",pointto["ttbb_tth_MVA_output_6j3t"]);
  readerMap["final63"]->BookMVA("BDT",weightPath+"633/TMVAClassification_BDT.weights.xml");

  readerMap["final64"]=new TMVA::Reader();
  readerMap["final64"]->AddVariable("avg_dr_tagged_jets",pointto["avg_dr_tagged_jets"]);
  readerMap["final64"]->AddVariable("avg_btag_disc_btags",pointto["avg_btag_disc_btags"]);
  readerMap["final64"]->AddVariable("closest_tagged_dijet_mass",pointto["closest_tagged_dijet_mass"]);
  readerMap["final64"]->AddVariable("third_highest_btag",pointto["third_highest_btag"]);
  readerMap["final64"]->AddVariable("fourth_highest_btag",pointto["fourth_highest_btag"]);
  readerMap["final64"]->AddVariable("maxeta_tag_tag",pointto["maxeta_tag_tag"]);
  readerMap["final64"]->AddVariable("pt_all_jets_over_E_all_jets",pointto["pt_all_jets_over_E_all_jets"]);
  readerMap["final64"]->AddVariable("ttbb_tth_ANN_output",pointto["ttbb_tth_ANN_output"]);
  readerMap["final64"]->AddVariable("best_higgs_mass",pointto["best_higgs_mass"]);
  readerMap["final64"]->AddVariable("dEta_fn",pointto["dEta_fn"]);
  readerMap["final64"]->BookMVA("BDT",weightPath+"643/TMVAClassification_BDT.weights.xml");

  initialized=true;
}

void BDTVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
  if(!initialized) cerr << "tree processor not initialized" << endl;

  int njets=vars.GetIntVar("N_Jets");
  int ntags=vars.GetIntVar("N_BTagsM");
  float ttbbbdt=-2;
  float finalbdt=-2;

  if(njets==5&&ntags>=4) ttbbbdt=readerMap["ttbb54"]->EvaluateMVA("BDT");
  if(njets>=6&&ntags==3) ttbbbdt=readerMap["ttbb63"]->EvaluateMVA("BDT");
  if(njets>=6&&ntags>=4) ttbbbdt=readerMap["ttbb64"]->EvaluateMVA("BDT");

  //order is important! first ttbb, then final BDT
  vars.FillVar("Evt_ttbbBDT",ttbbbdt);
  if(njets==4&&ntags==3) finalbdt=readerMap["final43"]->EvaluateMVA("BDT");
  if(njets==4&&ntags>=4) finalbdt=readerMap["final44"]->EvaluateMVA("BDT");
  if(njets==5&&ntags==3) finalbdt=readerMap["final53"]->EvaluateMVA("BDT");
  if(njets==5&&ntags>=4) finalbdt=readerMap["final54"]->EvaluateMVA("BDT");
  if(njets>=6&&ntags==2) finalbdt=readerMap["final62"]->EvaluateMVA("BDT");
  if(njets>=6&&ntags==3) finalbdt=readerMap["final63"]->EvaluateMVA("BDT");
  if(njets>=6&&ntags>=4) finalbdt=readerMap["final64"]->EvaluateMVA("BDT");
  vars.FillVar("Evt_FinalBDT",finalbdt);


}
