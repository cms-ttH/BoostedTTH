#include "BoostedTTH/BoostedAnalyzer/interface/ReconstructionMEvarProcessor.hpp"

using namespace std;

// all configurations should be done in constructor
ReconstructionMEvarProcessor::ReconstructionMEvarProcessor()
{
  tags_tth.push_back("TTHLikelihood");
  tags_ttbb.push_back("TTBBLikelihood");
  tags_tt.push_back("TTLikelihood");
  tags_tt.push_back("TTLikelihood_comb");
  tags_tth.push_back("TTHLikelihoodTimesME");
  tags_ttbb.push_back("TTBBLikelihoodTimesME");
  alltags.insert(alltags.end(), tags_tth.begin(), tags_tth.end());
  alltags.insert(alltags.end(), tags_tt.begin(), tags_tt.end());
  alltags.insert(alltags.end(), tags_ttbb.begin(), tags_ttbb.end());
  ratiotags_tth.push_back("TTHLikelihood");
  ratiotags_tth.push_back("TTHLikelihoodTimesME");
  ratiotags_ttbb.push_back("TTBBLikelihood");
  ratiotags_ttbb.push_back("TTBBLikelihoodTimesME");
  ratiotags_name.push_back("Likelihood");
  ratiotags_name.push_back("LikelihoodTimesME");
}
ReconstructionMEvarProcessor::~ReconstructionMEvarProcessor()
{
}

void
ReconstructionMEvarProcessor::Init(const InputCollections& input,
                                   VariableContainer& vars)
{
  vars.InitVar("Gen_highest_TopAndWHadLikelihood");

  for (auto tagname = alltags.begin(); tagname != alltags.end(); tagname++) {
    vars.InitVar("Gen_highest_" + (*tagname), "I");
    vars.InitVar("Gen_foundAll_with_" + (*tagname), "I");
    vars.InitVar("Gen_foundW_with_" + (*tagname), "I");
    vars.InitVar("Gen_foundH_with_" + (*tagname), "I");
    vars.InitVar("Gen_foundN_with_" + (*tagname), "I");
  }
  vars.InitVar("Gen_existingAll", "I");
  vars.InitVar("Gen_existingW", "I");
  vars.InitVar("Gen_existingH", "I");
  vars.InitVar("Gen_existingN", "I");

  for (auto tagname = tags_tt.begin(); tagname != tags_tt.end(); tagname++) {
    vars.InitVar("Reco_Dr_BB_best_" + (*tagname));
    vars.InitVar("Reco_Higgs_M_best_" + (*tagname));
    vars.InitVar("Reco_TTHLikelihood_best_" + (*tagname));
    vars.InitVar("Reco_TTHBBME_best_" + (*tagname));
    vars.InitVar("Reco_TTHLikelihoodTimesME_best_" + (*tagname));
    vars.InitVar("Reco_TTBBLikelihood_best_" + (*tagname));
    vars.InitVar("Reco_TTBBME_best_" + (*tagname));
    vars.InitVar("Reco_TTBBME_off_best_" + (*tagname));
    vars.InitVar("Reco_TTHBBLikelihoodTimesME_best_" + (*tagname));
    vars.InitVar("Reco_TTBBLikelihoodTimesME_best_" + (*tagname));
    vars.InitVar("Reco_TTBBLikelihoodTimesME_off_best_" + (*tagname));
    vars.InitVar("Reco_LikelihoodRatio_best_" + (*tagname));
    vars.InitVar("Reco_MERatio_best_" + (*tagname));
    vars.InitVar("Reco_MERatio_off_best_" + (*tagname));
    vars.InitVar("Reco_LikelihoodTimesMERatio_best_" + (*tagname));
    vars.InitVar("Reco_LikelihoodTimesMERatio_off_best_" + (*tagname));
  }
  for (auto tagname = tags_tth.begin(); tagname != tags_tth.end(); tagname++) {
    vars.InitVar("Reco_TTHLikelihood_best_" + (*tagname));
    vars.InitVar("Reco_TTHBBME_best_" + (*tagname));
    vars.InitVar("Reco_TTHLikelihoodTimesME_best_" + (*tagname));
  }
  for (auto tagname = tags_ttbb.begin(); tagname != tags_ttbb.end();
       tagname++) {
    vars.InitVar("Reco_TTBBLikelihood_best_" + (*tagname));
    vars.InitVar("Reco_TTBBME_best_" + (*tagname));
    vars.InitVar("Reco_TTBBLikelihoodTimesME_best_" + (*tagname));
    vars.InitVar("Reco_TTBBME_off_best_" + (*tagname));
    vars.InitVar("Reco_TTBBLikelihoodTimesME_off_best_" + (*tagname));
    vars.InitVar("Reco_Deta_Fn_best_" + (*tagname));
    vars.InitVar("Reco_Deta_TopLep_BB_best_" + (*tagname));
    vars.InitVar("Reco_Deta_TopHad_BB_best_" + (*tagname));
  }
  for (auto tagname = ratiotags_name.begin(); tagname != ratiotags_name.end();
       tagname++) {
    vars.InitVar("Reco_LikelihoodRatio_best_" + (*tagname));
    vars.InitVar("Reco_MERatio_best_" + (*tagname));
    vars.InitVar("Reco_MERatio_off_best_" + (*tagname));
    vars.InitVar("Reco_LikelihoodTimesMERatio_best_" + (*tagname));
    vars.InitVar("Reco_LikelihoodTimesMERatio_off_best_" + (*tagname));
  }

  vars.InitVar("Reco_Sum_TTHLikelihood");
  vars.InitVar("Reco_Sum_TTBBLikelihood");
  vars.InitVar("Reco_Sum_TTHLikelihoodTimesME");
  vars.InitVar("Reco_Sum_TTBBLikelihoodTimesME");
  vars.InitVar("Reco_Sum_TTHBBME");
  vars.InitVar("Reco_Sum_TTBBME");

  vars.InitVar("Reco_Sum_LikelihoodRatio");
  vars.InitVar("Reco_Sum_LikelihoodTimesMERatio");
  vars.InitVar("Reco_Sum_MERatio");

  initialized = true;
}

void
ReconstructionMEvarProcessor::Process(const InputCollections& input,
                                      VariableContainer& vars)
{
  if (!initialized)
    cerr << "tree processor not initialized" << endl;

  if (input.selectedJets.size() < 6)
    return;
  // get vectors
  vector<TLorentzVector> jetvecs = BoostedUtils::GetTLorentzVectors(
    BoostedUtils::GetJetVecs(input.selectedJets));
  vector<float> jetcsvs;
  int ntags = 0;
  for (auto j = input.selectedJets.begin(); j != input.selectedJets.end();
       j++) {
    jetcsvs.push_back(MiniAODHelper::GetJetCSV(*j));
    if (BoostedUtils::PassesCSV(*j))
      ntags++;
  }
  if (ntags < 2)
    return;
  if (input.selectedElectrons.size() + input.selectedMuons.size() < 1)
    return;
  TLorentzVector lepvec = BoostedUtils::GetTLorentzVector(
    BoostedUtils::GetPrimLepVec(input.selectedElectrons, input.selectedMuons));
  TVector2 metvec(input.correctedMET.px(), input.correctedMET.py());

  // setup mc matching
  if (input.genTopEvt.IsFilled() && input.genTopEvt.IsSemiLepton() &&
      (input.higgsDecay == HiggsDecay::bb)) {
    vector<TLorentzVector> bs_true = BoostedUtils::GetTLorentzVectors(
      input.genTopEvt.GetHiggsDecayProductVecs());
    vector<TLorentzVector> qs_true =
      BoostedUtils::GetTLorentzVectors(input.genTopEvt.GetWQuarksVecs());
    if (qs_true.size() == 2 && bs_true.size() == 2) {
      TLorentzVector bhad_true = BoostedUtils::GetTLorentzVector(
        input.genTopEvt.GetTopHadDecayQuarkVec());
      TLorentzVector blep_true = BoostedUtils::GetTLorentzVector(
        input.genTopEvt.GetTopLepDecayQuarkVec());
      TLorentzVector lep_true =
        BoostedUtils::GetTLorentzVector(input.genTopEvt.GetLeptonVec());
      TLorentzVector nu_true =
        BoostedUtils::GetTLorentzVector(input.genTopEvt.GetNeutrinoVec());
      mcmatcher.Setup(bhad_true,
                      qs_true[0],
                      qs_true[1],
                      blep_true,
                      lep_true,
                      nu_true,
                      bs_true[0],
                      bs_true[1]);
    }
  }
  if (input.genTopEvt.IsFilled() && input.genTopEvt.IsSemiLepton() &&
      input.sampleType == ttbb) {
    std::vector<reco::GenJet> additional_b_genjets =
      input.genTopEvt.GetAdditionalBGenJets();
    vector<TLorentzVector> qs_true =
      BoostedUtils::GetTLorentzVectors(input.genTopEvt.GetWQuarksVecs());
    if (qs_true.size() == 2 && additional_b_genjets.size() >= 2) {
      TLorentzVector bhad_true = BoostedUtils::GetTLorentzVector(
        input.genTopEvt.GetTopHadDecayQuarkVec());
      TLorentzVector blep_true = BoostedUtils::GetTLorentzVector(
        input.genTopEvt.GetTopLepDecayQuarkVec());
      TLorentzVector lep_true =
        BoostedUtils::GetTLorentzVector(input.genTopEvt.GetLeptonVec());
      TLorentzVector nu_true =
        BoostedUtils::GetTLorentzVector(input.genTopEvt.GetNeutrinoVec());
      mcmatcher.Setup(
        bhad_true,
        qs_true[0],
        qs_true[1],
        blep_true,
        lep_true,
        nu_true,
        BoostedUtils::GetTLorentzVector(additional_b_genjets[0].p4()),
        BoostedUtils::GetTLorentzVector(additional_b_genjets[1].p4()));
    }
  }

  // generate interpretations
  Interpretation** ints =
    generator.GenerateTTHInterpretations(jetvecs, jetcsvs, lepvec, metvec);
  uint nints = generator.GetNints();

  // calculate best tags and interpretations
  map<string, Interpretation*> best_int;
  for (auto tagname = alltags.begin(); tagname != alltags.end(); tagname++) {
    best_int[*tagname] = 0;
  }
  map<string, float> best_tag;
  for (uint i = 0; i < nints; i++) {
    for (auto tagname = alltags.begin(); tagname != alltags.end(); tagname++) {
      float tag = quality.GetTag(*tagname, *ints[i]);
      if (tag > best_tag[*tagname]) {
        best_int[*tagname] = ints[i];
        best_tag[*tagname] = tag;
      }
    }
  }

  // add best tags to vars
  for (auto t = best_tag.begin(); t != best_tag.end(); t++) {
    vars.FillVar("Gen_highest_" + t->first, t->second);
  }
  float toptag = -9999;
  for (uint i = 0; i < nints; i++) {
    float tag = quality.TopAndWHadLikelihood(*ints[i]);
    if (tag > toptag) {
      toptag = tag;
    }
  }
  vars.FillVar("Gen_highest_TopAndWHadLikelihood", toptag);

  // calculate variables for best interpretations
  for (auto tagname = alltags.begin(); tagname != alltags.end(); tagname++) {
    Interpretation* bi = best_int[*tagname];
    if (bi == 0)
      continue;
    if (mcmatcher.GetState() == 2) {
      vars.FillVar("Gen_foundAll_with_" + (*tagname), mcmatcher.MatchWHad(*bi));
      vars.FillVar("Gen_foundW_with_" + (*tagname), mcmatcher.MatchWHad(*bi));
      vars.FillVar("Gen_foundH_with_" + (*tagname), mcmatcher.MatchH(*bi));
      vars.FillVar("Gen_foundN_with_" + (*tagname), mcmatcher.MatchNTTH(*bi));
    }
  }
  bool existingAll = false;
  bool existingW = false;
  bool existingH = false;
  int existingN = 0;
  for (uint i = 0; i < nints; i++) {
    if (mcmatcher.GetState() == 2) {
      if (mcmatcher.MatchWHad(*ints[i]))
        existingW = true;
      if (mcmatcher.MatchH(*ints[i]))
        existingH = true;
      if (mcmatcher.MatchTTHallQ(*ints[i]))
        existingAll = true;
      if (mcmatcher.MatchNTTH(*ints[i]) > existingN)
        existingN = mcmatcher.MatchNTTH(*ints[i]);
    }
  }
  vars.FillVar("Gen_existingAll", existingAll);
  vars.FillVar("Gen_existingW", existingW);
  vars.FillVar("Gen_existingH", existingH);
  vars.FillVar("Gen_existingN", existingN);

  // calculate variables for best tt interpretations
  for (auto tagname = tags_tt.begin(); tagname != tags_tt.end(); tagname++) {
    Interpretation* bi = best_int[*tagname];
    if (bi == 0)
      continue;
    vars.FillVar("Reco_Dr_BB_best_" + (*tagname), bi->B1().DeltaR(bi->B2()));
    vars.FillVar("Reco_Higgs_M_best_" + (*tagname),
                 best_int[*tagname]->Higgs_M());

    double tthlike = quality.TTHLikelihood(*bi);
    double tthme = quality.TTHBB_ME(*bi);
    double tthlikeme = tthlike * tthme;
    double ttbblike = quality.TTBBLikelihood(*bi);
    double ttbbme = quality.TTBB_ON_ME(*bi);
    double ttbblikeme = ttbblike * ttbbme;
    double ttbbme_off = quality.TTBB_OFF_ME(*bi);
    double ttbblikeme_off = ttbblike * ttbbme_off;
    double like_ratio = tthlike / (tthlike + ttbblike);
    double me_ratio = tthme / (tthme + ttbbme);
    double me_ratio_off = tthme / (tthme + ttbbme_off);
    double likeme_ratio = tthlikeme / (tthlikeme + ttbblikeme);
    double likeme_ratio_off = tthlikeme / (tthlikeme + ttbblikeme_off);
    vars.FillVar("Reco_TTHLikelihood_best_" + (*tagname), tthlike);
    vars.FillVar("Reco_TTHBBME_best_" + (*tagname), tthme);
    vars.FillVar("Reco_TTBBLikelihood_best_" + (*tagname), ttbblike);
    vars.FillVar("Reco_TTBBME_best_" + (*tagname), ttbbme);
    vars.FillVar("Reco_TTBBME_off_best_" + (*tagname), ttbbme_off);
    vars.FillVar("Reco_TTHLikelihoodTimesME_best_" + (*tagname), tthlikeme);
    vars.FillVar("Reco_TTBBLikelihoodTimesME_best_" + (*tagname), ttbblikeme);
    vars.FillVar("Reco_TTBBLikelihoodTimesME_off_best_" + (*tagname),
                 ttbblikeme_off);
    vars.FillVar("Reco_LikelihoodRatio_best_" + (*tagname), like_ratio);
    vars.FillVar("Reco_MERatio_best_" + (*tagname), me_ratio);
    vars.FillVar("Reco_MERatio_off_best_" + (*tagname), me_ratio_off);
    vars.FillVar("Reco_LikelihoodTimesMERatio_best_" + (*tagname),
                 likeme_ratio);
    vars.FillVar("Reco_LikelihoodTimesMERatio_off_best_" + (*tagname),
                 likeme_ratio_off);
  }
  for (auto tagname = tags_tth.begin(); tagname != tags_tth.end(); tagname++) {
    Interpretation* bi = best_int[*tagname];
    if (bi == 0)
      continue;
    double tthlike = quality.TTHLikelihood(*bi);
    double tthme = quality.TTHBB_ME(*bi);
    double tthlikeme = tthlike * tthme;
    vars.FillVar("Reco_TTHLikelihood_best_" + (*tagname), tthlike);
    vars.FillVar("Reco_TTHBBME_best_" + (*tagname), tthme);
    vars.FillVar("Reco_TTHLikelihoodTimesME_best_" + (*tagname), tthlikeme);
  }
  for (auto tagname = tags_ttbb.begin(); tagname != tags_ttbb.end();
       tagname++) {
    Interpretation* bi = best_int[*tagname];
    if (bi == 0)
      continue;
    double ttbblike = quality.TTBBLikelihood(*bi);
    double ttbbme = quality.TTBB_ON_ME(*bi);
    double ttbblikeme = ttbblike * ttbbme;
    double ttbbme_off = quality.TTBB_OFF_ME(*bi);
    double ttbblikeme_off = ttbblike * ttbbme_off;
    vars.FillVar("Reco_TTBBLikelihood_best_" + (*tagname), ttbblike);
    vars.FillVar("Reco_TTBBME_best_" + (*tagname), ttbbme);
    vars.FillVar("Reco_TTBBLikelihoodTimesME_best_" + (*tagname), ttbblikeme);
    vars.FillVar("Reco_TTBBME_off_best_" + (*tagname), ttbbme_off);
    vars.FillVar("Reco_TTBBLikelihoodTimesME_off_best_" + (*tagname),
                 ttbblikeme_off);
    float dEta_fn = sqrt(abs((bi->Higgs().Eta() - bi->TopLep().Eta()) *
                             (bi->Higgs().Eta() - bi->TopHad().Eta())));
    vars.FillVar("Reco_Deta_Fn_best_" + (*tagname), dEta_fn);
    vars.FillVar("Reco_Deta_TopLep_BB_best_" + (*tagname),
                 abs(bi->Higgs().Eta() - bi->TopLep().Eta()));
    vars.FillVar("Reco_Deta_TopHad_BB_best_" + (*tagname),
                 abs(bi->Higgs().Eta() - bi->TopHad().Eta()));
  }
  // fill best tth / best ttbb interpretation ratios
  assert(ratiotags_tth.size() == ratiotags_ttbb.size());
  assert(ratiotags_tth.size() == ratiotags_name.size());
  for (uint i = 0; i < ratiotags_tth.size(); i++) {
    Interpretation* bi_tth = best_int[ratiotags_tth[i]];
    Interpretation* bi_ttbb = best_int[ratiotags_ttbb[i]];
    if (bi_tth == 0)
      continue;
    if (bi_ttbb == 0)
      continue;
    double tthlike = quality.TTHLikelihood(*bi_tth);
    double tthme = quality.TTHBB_ME(*bi_tth);
    double tthlikeme = tthlike * tthme;
    double ttbblike = quality.TTBBLikelihood(*bi_ttbb);
    double ttbbme = quality.TTBB_ON_ME(*bi_ttbb);
    double ttbblikeme = ttbblike * ttbbme;
    double ttbbme_off = quality.TTBB_OFF_ME(*bi_ttbb);
    double ttbblikeme_off = ttbblike * ttbbme_off;
    double like_ratio = tthlike / (tthlike + ttbblike);
    double me_ratio = tthme / (tthme + ttbbme);
    double me_ratio_off = tthme / (tthme + ttbbme_off);
    double likeme_ratio = tthlikeme / (tthlikeme + ttbblikeme);
    double likeme_ratio_off = tthlikeme / (tthlikeme + ttbblikeme_off);

    vars.FillVar("Reco_LikelihoodRatio_best_" + ratiotags_name[i], like_ratio);
    vars.FillVar("Reco_MERatio_best_" + ratiotags_name[i], me_ratio);
    vars.FillVar("Reco_MERatio_off_best_" + ratiotags_name[i], me_ratio_off);
    vars.FillVar("Reco_LikelihoodTimesMERatio_best_" + ratiotags_name[i],
                 likeme_ratio);
    vars.FillVar("Reco_LikelihoodTimesMERatio_off_best_" + ratiotags_name[i],
                 likeme_ratio_off);
  }

  // sum up likelihoods
  double sum_tth_likelihood = 0;
  double sum_ttbb_likelihood = 0;
  double sum_tth_me_likelihood = 0;
  double sum_ttbb_me_likelihood = 0;
  double sum_tth_me = 0;
  double sum_ttbb_me = 0;
  for (uint i = 0; i < nints; i++) {
    // calculating MEs for many interpretations can take a lot of time
    double tthlike = quality.TTHLikelihood(*ints[i]);
    double tthme = quality.TTHBB_ME(*ints[i]);
    double tthlikeme = tthlike * tthme;
    double ttbblike = quality.TTBBLikelihood(*ints[i]);
    double ttbbme = quality.TTBB_ON_ME(*ints[i]);
    double ttbblikeme = ttbblike * ttbbme;
    sum_tth_likelihood += tthlike;
    sum_tth_me += tthme;
    sum_tth_me_likelihood += tthlikeme;
    sum_ttbb_likelihood += ttbblike;
    sum_ttbb_me += ttbbme;
    sum_ttbb_me_likelihood += ttbblikeme;
  }
  vars.FillVar("Reco_Sum_TTHLikelihood", sum_tth_likelihood);
  vars.FillVar("Reco_Sum_TTBBLikelihood", sum_ttbb_likelihood);
  vars.FillVar("Reco_Sum_TTHLikelihoodTimesME", sum_tth_me_likelihood);
  vars.FillVar("Reco_Sum_TTBBLikelihoodTimesME", sum_ttbb_me_likelihood);
  vars.FillVar("Reco_Sum_TTHBBME", sum_tth_me);
  vars.FillVar("Reco_Sum_TTBBME", sum_ttbb_me);

  vars.FillVar("Reco_Sum_LikelihoodRatio",
               sum_tth_likelihood / (sum_tth_likelihood + sum_ttbb_likelihood));
  vars.FillVar("Reco_Sum_LikelihoodTimesMERatio",
               sum_tth_me_likelihood /
                 (sum_tth_me_likelihood + sum_ttbb_me_likelihood));
  vars.FillVar("Reco_Sum_MERatio", sum_tth_me / (sum_tth_me + sum_ttbb_me));
}
