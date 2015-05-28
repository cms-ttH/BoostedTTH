#include "BoostedTTH/BoostedAnalyzer/interface/BDTOhio_v2.hpp"
using namespace std;

BDTOhio_v2::BDTOhio_v2 (TString weightPath):btagMcut(0.814),btagger("combinedInclusiveSecondaryVertexV2BJetTags"){
  // ==================================================
  //init all variables used in BDT set
  variableMap["all_sum_pt_with_met"]=-999.;
  variableMap["avg_btag_disc_btags"]=-999.;
  variableMap["avg_dr_tagged_jets"]=-999.;
  variableMap["best_higgs_mass"]=-999.;
  variableMap["closest_tagged_dijet_mass"]=-999.;
  variableMap["dEta_fn"]=-999.;
  variableMap["dev_from_avg_disc_btags"]=-999.;
  variableMap["dr_between_lep_and_closest_jet"]=-999.;
  variableMap["fifth_highest_btag"]=-999.;
  variableMap["first_jet_pt"]=-999.;
  variableMap["fourth_highest_btag"]=-999.;
  variableMap["fourth_jet_pt"]=-999.;
  variableMap["h0"]=-999.;
  variableMap["h2"]=-999.;
  variableMap["HT"]=-999.;
  variableMap["lowest_btag"]=-999.;
  variableMap["M3"]=-999.;
  variableMap["maxeta_jet_jet"]=-999.;
  variableMap["maxeta_jet_tag"]=-999.;
  variableMap["maxeta_tag_tag"]=-999.;
  variableMap["MET"]=-999.;
  variableMap["MHT"]=-999.;
  variableMap["Mlb"]=-999.;
  variableMap["pt_all_jets_over_E_all_jets"]=-999.;
  variableMap["second_highest_btag"]=-999.;
  variableMap["second_jet_pt"]=-999.;
  variableMap["sixth_highest_btag"]=-999.;
  variableMap["sphericity"]=-999.;
  variableMap["third_highest_btag"]=-999.;
  variableMap["third_jet_pt"]=-999.;
  // ==================================================
  ///init readers for all categories
  readerMap["6j4t"]=new TMVA::Reader();
  readerMap["5j4t"]=new TMVA::Reader();
  readerMap["4j4t"]=new TMVA::Reader();
  readerMap["6j3t"]=new TMVA::Reader();
  readerMap["5j3t"]=new TMVA::Reader();
  readerMap["4j3t"]=new TMVA::Reader();
  readerMap["6j2t"]=new TMVA::Reader();

  // ==================================================
  //add variables to corresponding readers

  readerMap["6j2t"]->AddVariable("first_jet_pt", &variableMap["first_jet_pt"]);
  readerMap["6j2t"]->AddVariable("second_jet_pt", &variableMap["second_jet_pt"]);
  readerMap["6j2t"]->AddVariable("third_jet_pt", &variableMap["third_jet_pt"]);
  readerMap["6j2t"]->AddVariable("fourth_jet_pt", &variableMap["fourth_jet_pt"]);
  readerMap["6j2t"]->AddVariable("h0", &variableMap["h0"]);
  readerMap["6j2t"]->AddVariable("h1", &variableMap["h1"]);
  readerMap["6j2t"]->AddVariable("all_sum_pt_with_met", &variableMap["all_sum_pt_with_met"]);
  readerMap["6j2t"]->AddVariable("HT", &variableMap["HT"]);
  readerMap["6j2t"]->AddVariable("h3", &variableMap["h3"]);
  readerMap["6j2t"]->AddVariable("third_highest_btag", &variableMap["third_highest_btag"]);
  readerMap["6j2t"]->AddVariable("fourth_highest_btag", &variableMap["fourth_highest_btag"]);
  readerMap["6j2t"]->AddVariable("fifth_highest_CSV", &variableMap["fifth_highest_CSV"]);
  readerMap["6j2t"]->AddVariable("maxeta_jet_jet", &variableMap["maxeta_jet_jet"]);
  readerMap["6j2t"]->AddVariable("pt_all_jets_over_E_all_jets", &variableMap["pt_all_jets_over_E_all_jets"]);

  readerMap["4j3t"]->AddVariable("first_jet_pt", &variableMap["first_jet_pt"]);
  readerMap["4j3t"]->AddVariable("second_jet_pt", &variableMap["second_jet_pt"]);
  readerMap["4j3t"]->AddVariable("third_jet_pt", &variableMap["third_jet_pt"]);
  readerMap["4j3t"]->AddVariable("all_sum_pt_with_met", &variableMap["all_sum_pt_with_met"]);
  readerMap["4j3t"]->AddVariable("HT", &variableMap["HT"]);
  readerMap["4j3t"]->AddVariable("avg_btag_disc_btags", &variableMap["avg_btag_disc_btags"]);
  readerMap["4j3t"]->AddVariable("dev_from_avg_disc_btags", &variableMap["dev_from_avg_disc_btags"]);
  readerMap["4j3t"]->AddVariable("second_highest_btag", &variableMap["second_highest_btag"]);
  readerMap["4j3t"]->AddVariable("third_highest_btag", &variableMap["third_highest_btag"]);
  readerMap["4j3t"]->AddVariable("invariant_mass_of_everything", &variableMap["invariant_mass_of_everything"]);
  readerMap["4j3t"]->AddVariable("fifth_highest_CSV", &variableMap["fifth_highest_CSV"]);

  readerMap["5j3t"]->AddVariable("third_jet_pt", &variableMap["third_jet_pt"]);
  readerMap["5j3t"]->AddVariable("fourth_jet_pt", &variableMap["fourth_jet_pt"]);
  readerMap["5j3t"]->AddVariable("all_sum_pt_with_met", &variableMap["all_sum_pt_with_met"]);
  readerMap["5j3t"]->AddVariable("HT", &variableMap["HT"]);
  readerMap["5j3t"]->AddVariable("avg_dr_tagged_jets", &variableMap["avg_dr_tagged_jets"]);
  readerMap["5j3t"]->AddVariable("avg_btag_disc_btags", &variableMap["avg_btag_disc_btags"]);
  readerMap["5j3t"]->AddVariable("dev_from_avg_disc_btags", &variableMap["dev_from_avg_disc_btags"]);
  readerMap["5j3t"]->AddVariable("h3", &variableMap["h3"]);
  readerMap["5j3t"]->AddVariable("second_highest_btag", &variableMap["second_highest_btag"]);
  readerMap["5j3t"]->AddVariable("third_highest_btag", &variableMap["third_highest_btag"]);
  readerMap["5j3t"]->AddVariable("maxeta_jet_jet", &variableMap["maxeta_jet_jet"]);
  readerMap["5j3t"]->AddVariable("maxeta_jet_tag", &variableMap["maxeta_jet_tag"]);
  readerMap["5j3t"]->AddVariable("maxeta_tag_tag", &variableMap["maxeta_tag_tag"]);

  readerMap["6j3t"]->AddVariable("third_jet_pt", &variableMap["third_jet_pt"]);
  readerMap["6j3t"]->AddVariable("fourth_jet_pt", &variableMap["fourth_jet_pt"]);
  readerMap["6j3t"]->AddVariable("all_sum_pt_with_met", &variableMap["all_sum_pt_with_met"]);
  readerMap["6j3t"]->AddVariable("HT", &variableMap["HT"]);
  readerMap["6j3t"]->AddVariable("avg_dr_tagged_jets", &variableMap["avg_dr_tagged_jets"]);
  readerMap["6j3t"]->AddVariable("avg_btag_disc_btags", &variableMap["avg_btag_disc_btags"]);
  readerMap["6j3t"]->AddVariable("dev_from_avg_disc_btags", &variableMap["dev_from_avg_disc_btags"]);
  readerMap["6j3t"]->AddVariable("h3", &variableMap["h3"]);
  readerMap["6j3t"]->AddVariable("second_highest_btag", &variableMap["second_highest_btag"]);
  readerMap["6j3t"]->AddVariable("third_highest_btag", &variableMap["third_highest_btag"]);
  readerMap["6j3t"]->AddVariable("fourth_highest_btag", &variableMap["fourth_highest_btag"]);
  readerMap["6j3t"]->AddVariable("maxeta_jet_tag", &variableMap["maxeta_jet_tag"]);
  readerMap["6j3t"]->AddVariable("maxeta_tag_tag", &variableMap["maxeta_tag_tag"]);
  readerMap["6j3t"]->AddVariable("min_dr_tagged_jets", &variableMap["min_dr_tagged_jets"]);
  readerMap["6j3t"]->AddVariable("pt_all_jets_over_E_all_jets", &variableMap["pt_all_jets_over_E_all_jets"]);

  readerMap["4j4t"]->AddVariable("h1", &variableMap["h1"]);
  readerMap["4j4t"]->AddVariable("avg_dr_tagged_jets", &variableMap["avg_dr_tagged_jets"]);
  readerMap["4j4t"]->AddVariable("sphericity", &variableMap["sphericity"]);
  readerMap["4j4t"]->AddVariable("avg_btag_disc_btags", &variableMap["avg_btag_disc_btags"]);
  readerMap["4j4t"]->AddVariable("dev_from_avg_disc_btags", &variableMap["dev_from_avg_disc_btags"]);
  readerMap["4j4t"]->AddVariable("h2", &variableMap["h2"]);
  readerMap["4j4t"]->AddVariable("closest_tagged_dijet_mass", &variableMap["closest_tagged_dijet_mass"]);
  readerMap["4j4t"]->AddVariable("h3", &variableMap["h3"]);
  readerMap["4j4t"]->AddVariable("second_highest_btag", &variableMap["second_highest_btag"]);
  readerMap["4j4t"]->AddVariable("third_highest_btag", &variableMap["third_highest_btag"]);
  readerMap["4j4t"]->AddVariable("fourth_highest_btag", &variableMap["fourth_highest_btag"]);
  readerMap["4j4t"]->AddVariable("maxeta_jet_jet", &variableMap["maxeta_jet_jet"]);
  readerMap["4j4t"]->AddVariable("min_dr_tagged_jets", &variableMap["min_dr_tagged_jets"]);
  readerMap["4j4t"]->AddVariable("pt_all_jets_over_E_all_jets", &variableMap["pt_all_jets_over_E_all_jets"]);

  readerMap["5j4t"]->AddVariable("aplanarity", &variableMap["aplanarity"]);
  readerMap["5j4t"]->AddVariable("fourth_jet_pt", &variableMap["fourth_jet_pt"]);
  readerMap["5j4t"]->AddVariable("h1", &variableMap["h1"]);
  readerMap["5j4t"]->AddVariable("avg_dr_tagged_jets", &variableMap["avg_dr_tagged_jets"]);
  readerMap["5j4t"]->AddVariable("sphericity", &variableMap["sphericity"]);
  readerMap["5j4t"]->AddVariable("avg_btag_disc_btags", &variableMap["avg_btag_disc_btags"]);
  readerMap["5j4t"]->AddVariable("dev_from_avg_disc_btags", &variableMap["dev_from_avg_disc_btags"]);
  readerMap["5j4t"]->AddVariable("h2", &variableMap["h2"]);
  readerMap["5j4t"]->AddVariable("lowest_btag", &variableMap["lowest_btag"]);
  readerMap["5j4t"]->AddVariable("h3", &variableMap["h3"]);
  readerMap["5j4t"]->AddVariable("second_highest_btag", &variableMap["second_highest_btag"]);
  readerMap["5j4t"]->AddVariable("third_highest_btag", &variableMap["third_highest_btag"]);
  readerMap["5j4t"]->AddVariable("maxeta_jet_jet", &variableMap["maxeta_jet_jet"]);
  readerMap["5j4t"]->AddVariable("maxeta_jet_tag", &variableMap["maxeta_jet_tag"]);
  readerMap["5j4t"]->AddVariable("maxeta_tag_tag", &variableMap["maxeta_tag_tag"]);
  readerMap["5j4t"]->AddVariable("min_dr_tagged_jets", &variableMap["min_dr_tagged_jets"]);
  readerMap["5j4t"]->AddVariable("pt_all_jets_over_E_all_jets", &variableMap["pt_all_jets_over_E_all_jets"]);

  readerMap["6j4t"]->AddVariable("avg_dr_tagged_jets", &variableMap["avg_dr_tagged_jets"]);
  readerMap["6j4t"]->AddVariable("avg_btag_disc_btags", &variableMap["avg_btag_disc_btags"]);
  readerMap["6j4t"]->AddVariable("h2", &variableMap["h2"]);
  readerMap["6j4t"]->AddVariable("h3", &variableMap["h3"]);
  readerMap["6j4t"]->AddVariable("second_highest_btag", &variableMap["second_highest_btag"]);
  readerMap["6j4t"]->AddVariable("third_highest_btag", &variableMap["third_highest_btag"]);
  readerMap["6j4t"]->AddVariable("fourth_highest_btag", &variableMap["fourth_highest_btag"]);
  readerMap["6j4t"]->AddVariable("maxeta_jet_jet", &variableMap["maxeta_jet_jet"]);
  readerMap["6j4t"]->AddVariable("maxeta_jet_tag", &variableMap["maxeta_jet_tag"]);
  readerMap["6j4t"]->AddVariable("maxeta_tag_tag", &variableMap["maxeta_tag_tag"]);
  readerMap["6j4t"]->AddVariable("pt_all_jets_over_E_all_jets", &variableMap["pt_all_jets_over_E_all_jets"]);
  readerMap["6j4t"]->AddVariable("tagged_dijet_mass_closest_to_125", &variableMap["tagged_dijet_mass_closest_to_125"]);
  readerMap["6j4t"]->AddVariable("dEta_fn", &variableMap["dEta_fn"]);

  // ==================================================
  //book MVAs from weights
  readerMap["6j4t"]->BookMVA("BDT",weightPath+"/643/TMVAClassification_BDT.weights.xml");
  readerMap["5j4t"]->BookMVA("BDT",weightPath+"/543/TMVAClassification_BDT.weights.xml");
  readerMap["4j4t"]->BookMVA("BDT",weightPath+"/443/TMVAClassification_BDT.weights.xml");
  readerMap["6j3t"]->BookMVA("BDT",weightPath+"/633/TMVAClassification_BDT.weights.xml");
  readerMap["5j3t"]->BookMVA("BDT",weightPath+"/533/TMVAClassification_BDT.weights.xml");
  readerMap["4j3t"]->BookMVA("BDT",weightPath+"/433/TMVAClassification_BDT.weights.xml");
  readerMap["6j2t"]->BookMVA("BDT",weightPath+"/623/TMVAClassification_BDT.weights.xml");

}
BDTOhio_v2::~BDTOhio_v2(){
}
std::string BDTOhio_v2::GetCategory(const std::vector<pat::Jet>& selectedJets) const{
  int njets=selectedJets.size();
  int ntagged=0;
  for(auto jet=selectedJets.begin(); jet!=selectedJets.end(); jet++){
    if(jet->bDiscriminator(btagger)>btagMcut) ntagged++;
  }
  if(ntagged>=4&&njets>=6){
    return "6j4t"; 
  }
  else if(ntagged>=4&&njets==5){
    return "5j4t"; 
  }
  else if(ntagged>=4&&njets==4){
    return "4j4t"; 
  }
  else if(ntagged==3&&njets>=6){
    return "6j3t"; 
  }
  else if(ntagged==3&&njets==5){
    return "5j3t"; 
  }
  else if(ntagged==3&&njets==4){
    return "4j3t"; 
  }
  else if(ntagged==2&&njets>=6){
    return "6j2t"; 
  }
  else{
    return "none";
  }
  
}


				   
float BDTOhio_v2::Evaluate(std::string categoryLabel, const std::vector<pat::Muon>& selectedMuons, const std::vector<pat::Electron>& selectedElectrons, const std::vector<pat::Jet>& selectedJets, const std::vector<pat::Jet>& selectedJetsLoose, const pat::MET& pfMET){

  if(selectedMuons.size()+selectedElectrons.size()!=1){
    cerr << "BDTOhio_v2: not a SL event" << endl;
  }
  // ==================================================
  // construct object vectors etc
  TLorentzVector lepton_vec;
  TLorentzVector met_vec;
  vector<TLorentzVector> jet_vecs;
  vector<double> jetCSV;
  vector< vector<double> > jets_vvdouble;
  vector<TLorentzVector> jet_loose_vecs;
  vector<TLorentzVector> tagged_jet_vecs;
  vector<double> jetCSV_loose;
  vector<double> sortedCSV;
  if(selectedMuons.size()>0) lepton_vec.SetPtEtaPhiE(selectedMuons[0].pt(),selectedMuons[0].eta(),selectedMuons[0].phi(),selectedMuons[0].energy());
  if(selectedElectrons.size()>0) lepton_vec.SetPtEtaPhiE(selectedElectrons[0].pt(),selectedElectrons[0].eta(),selectedElectrons[0].phi(),selectedElectrons[0].energy());
  met_vec.SetPtEtaPhiE(pfMET.pt(),pfMET.eta(),0,pfMET.pt());
  for(auto jet=selectedJets.begin();jet!=selectedJets.end(); jet++){
    TLorentzVector jetvec;
    jetvec.SetPtEtaPhiE(jet->pt(),jet->eta(),jet->phi(),jet->energy());
    jet_vecs.push_back(jetvec);
    if(jet->bDiscriminator(btagger)>btagMcut){
      tagged_jet_vecs.push_back(jetvec);
    }
    vector<double> pxpypzE;
    pxpypzE.push_back(jet->px());
    pxpypzE.push_back(jet->py());
    pxpypzE.push_back(jet->pz());
    pxpypzE.push_back(jet->energy());
    jets_vvdouble.push_back(pxpypzE);
    jetCSV.push_back(jet->bDiscriminator(btagger));
  }
  sortedCSV=jetCSV;
  std::sort(sortedCSV.begin(),sortedCSV.end(),std::greater<float>());
  for(auto jet=selectedJetsLoose.begin();jet!=selectedJetsLoose.end(); jet++){
    TLorentzVector jetvec;
    jetvec.SetPtEtaPhiE(jet->pt(),jet->eta(),jet->phi(),jet->energy());
    jet_loose_vecs.push_back(jetvec);
    jetCSV_loose.push_back(jet->bDiscriminator(btagger));
  }

  // TODO loose jet and csv defintion

  // ==================================================
  // calculate variables
  // aplanarity and sphericity
  float aplanarity,sphericity;
  bdtvar.getSp(lepton_vec,met_vec,jet_vecs,aplanarity,sphericity);

  // Fox Wolfram
  float h0,h1,h2,h3,h4;
  bdtvar.getFox(jet_vecs,h0,h1,h2,h3,h4);

  // best higgs mass 1
  double minChi,dRbb;
  TLorentzVector bjet1,bjet2;
  float bestHiggsMass = bdtvar.getBestHiggsMass(lepton_vec,met_vec,jet_vecs,jetCSV,minChi,dRbb,bjet1,bjet2, jet_loose_vecs,jetCSV_loose);
  
  // study top bb system
  TLorentzVector dummy_metv;
  double minChiStudy, chi2lepW, chi2leptop, chi2hadW, chi2hadtop, mass_lepW, mass_leptop, mass_hadW, mass_hadtop, dRbbStudy, testquant1, testquant2, testquant3, testquant4, testquant5, testquant6, testquant7; 
  TLorentzVector b1,b2;
  bdtvar.study_tops_bb_syst (pfMET.pt(), pfMET.phi(), dummy_metv, lepton_vec, jets_vvdouble, jetCSV, minChiStudy, chi2lepW, chi2leptop, chi2hadW, chi2hadtop, mass_lepW, mass_leptop, mass_hadW, mass_hadtop, dRbbStudy, testquant1, testquant2, testquant3, testquant4, testquant5, testquant6, testquant7, b1, b2);
  float dEta_fn=testquant6;
  // ptE ratio
  float pt_E_ratio = bdtvar.pt_E_ratio_jets(jets_vvdouble);
  
  // etamax
  float jet_jet_etamax = bdtvar.get_jet_jet_etamax (jets_vvdouble);
  float jet_tag_etamax = bdtvar.get_jet_tag_etamax (jets_vvdouble,jetCSV);
  float tag_tag_etamax = bdtvar.get_tag_tag_etamax (jets_vvdouble,jetCSV);

  // jet variables
  float sum_pt_jets=0;
  float dr_between_lep_and_closest_jet=99;
  float mht_px=0;
  float mht_py=0;
  for(auto jetvec = jet_vecs.begin() ; jetvec != jet_vecs.end(); ++jetvec){
    dr_between_lep_and_closest_jet=fmin(dr_between_lep_and_closest_jet,lepton_vec.DeltaR(*jetvec));
    sum_pt_jets += jetvec->Pt();
    mht_px += jetvec->Px();
    mht_py += jetvec->Py();
  }
  mht_px+=lepton_vec.Px();
  mht_py+=lepton_vec.Py();
  float sum_pt_wo_met=sum_pt_jets+lepton_vec.Pt();
  float sum_pt_with_met=pfMET.pt()+sum_pt_wo_met;
  float MHT=sqrt( mht_px*mht_px + mht_py*mht_py );

  float Mlb=0;   // mass of lepton and closest bt-tagged jet
  float minDr_for_Mlb=999.;
  for(auto tagged_jet=tagged_jet_vecs.begin();tagged_jet!=tagged_jet_vecs.end();tagged_jet++){
    float drLep=lepton_vec.DeltaR(*tagged_jet);
    if(drLep<minDr_for_Mlb){
      minDr_for_Mlb=drLep;
      Mlb=(lepton_vec+*tagged_jet).M();
    }
  }
  float closest_tagged_dijet_mass=-99;
  float minDrTagged=99;
  float sumDrTagged=0;
  int npairs=0;
  for(auto tagged_jet1=tagged_jet_vecs.begin();tagged_jet1!=tagged_jet_vecs.end();tagged_jet1++){
    for(auto tagged_jet2=tagged_jet1+1;tagged_jet2!=tagged_jet_vecs.end();tagged_jet2++){
      float dr=tagged_jet1->DeltaR(*tagged_jet2);
      sumDrTagged+=dr;
      npairs++;
      if(dr<minDrTagged){
	minDrTagged=dr;
	closest_tagged_dijet_mass=(*tagged_jet1+*tagged_jet2).M();
      }
    }
  }
  float avgDrTagged=-1;
  if(npairs!=0) avgDrTagged=sumDrTagged/npairs;
  // M3
  float m3 = -1.;
  float maxpt_for_m3=-1;
  for(auto itJetVec1 = jet_vecs.begin() ; itJetVec1 != jet_vecs.end(); ++itJetVec1){
    for(auto itJetVec2 = itJetVec1+1 ; itJetVec2 != jet_vecs.end(); ++itJetVec2){
      for(auto itJetVec3 = itJetVec2+1 ; itJetVec3 != jet_vecs.end(); ++itJetVec3){
    
        TLorentzVector m3vec = *itJetVec1 + *itJetVec2 + *itJetVec3;
        
	if(m3vec.Pt() > maxpt_for_m3){
	  maxpt_for_m3 = m3vec.Pt();
	  m3 = m3vec.M();
	}
      } 
    }
  }
  // btag variables
  float averageCSV = 0;
  float lowest_btag=99;
  int njets=selectedJets.size();
  int ntags=0;
  for(auto itCSV = jetCSV.begin() ; itCSV != jetCSV.end(); ++itCSV){
    if(*itCSV<btagMcut) continue;
    lowest_btag=fmin(*itCSV,lowest_btag);
    averageCSV += fmax(*itCSV,0);
    ntags++;
  }
  if(ntags>0)
    averageCSV /= ntags;
  else
    averageCSV=1;
  if(lowest_btag>90) lowest_btag=-1;

  float csvDev = 0;
  for(auto itCSV = jetCSV.begin() ; itCSV != jetCSV.end(); ++itCSV){
    if(*itCSV<btagMcut) continue;
    csvDev += pow(*itCSV - averageCSV,2);
  }
  if(ntags>0)
    csvDev /= ntags;
  else
    csvDev=-1.;


  // ==================================================
  // Fill variable map
  variableMap["all_sum_pt_with_met"]=sum_pt_with_met;
  variableMap["avg_btag_disc_btags"]=averageCSV;
  variableMap["avg_dr_tagged_jets"]=avgDrTagged;
  variableMap["best_higgs_mass"]=bestHiggsMass;
  variableMap["closest_tagged_dijet_mass"]=closest_tagged_dijet_mass;
  variableMap["dEta_fn"]=dEta_fn;
  variableMap["dev_from_avg_disc_btags"]=csvDev;
  variableMap["dr_between_lep_and_closest_jet"]=dr_between_lep_and_closest_jet;
  variableMap["fifth_highest_btag"]=njets>4?sortedCSV[4]:-1.;
  variableMap["first_jet_pt"]=jet_vecs.size()>0?jet_vecs[0].Pt():-99;
  variableMap["fourth_highest_btag"]=njets>3?sortedCSV[3]:-1.;
  variableMap["fourth_jet_pt"]=jet_vecs.size()>3?jet_vecs[3].Pt():-99;
  variableMap["h0"]=h0;
  variableMap["h2"]=h2;
  variableMap["HT"]=sum_pt_jets;
  variableMap["lowest_btag"]=lowest_btag;
  variableMap["M3"]=m3;
  variableMap["maxeta_jet_jet"]=jet_jet_etamax;
  variableMap["maxeta_jet_tag"]=jet_tag_etamax;
  variableMap["maxeta_tag_tag"]=tag_tag_etamax;
  variableMap["MET"]=pfMET.pt();
  variableMap["MHT"]=MHT;
  variableMap["Mlb"]=Mlb;
  variableMap["pt_all_jets_over_E_all_jets"]=pt_E_ratio;
  variableMap["second_highest_btag"]=njets>1?sortedCSV[1]:-1.;
  variableMap["second_jet_pt"]=jet_vecs.size()>1?jet_vecs[1].Pt():-99;
  variableMap["sixth_highest_btag"]=njets>5?sortedCSV[5]:-1.;
  variableMap["sphericity"]=sphericity;
  variableMap["third_highest_btag"]=njets>2?sortedCSV[2]:-1.;
  variableMap["third_jet_pt"]=jet_vecs.size()>2?jet_vecs[2].Pt():-99;

  // ==================================================
  // evaluate BDT of current category
  return readerMap[categoryLabel]->EvaluateMVA("BDT");
}

std::map<std::string,float> BDTOhio_v2::GetAllOutputsOfLastEvaluation() const{
  std::map<std::string,float> outputs;
  for(auto it = readerMap.begin();it != readerMap.end();it++){
    outputs[it->first]=it->second->EvaluateMVA("BDT");
  }
  return outputs;
}
float BDTOhio_v2::Evaluate(const std::vector<pat::Muon>& selectedMuons, const std::vector<pat::Electron>& selectedElectrons, const std::vector<pat::Jet>& selectedJets, const std::vector<pat::Jet>& selectedJetsLoose, const pat::MET& pfMET){
  std::string category=GetCategory(selectedJets);
  if(category=="none") {
    cerr <<  "BDTOhio_v2: no matching category found" << endl;
    return -2;
  }
  return Evaluate(category,selectedMuons,selectedElectrons,selectedJets,selectedJetsLoose,pfMET);
}

std::map<std::string,float> BDTOhio_v2::GetVariablesOfLastEvaluation() const{
  return variableMap;
}
