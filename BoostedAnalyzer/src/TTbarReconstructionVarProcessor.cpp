#include "BoostedTTH/BoostedAnalyzer/interface/TTbarReconstructionVarProcessor.hpp"

using namespace std;

// all configurations should be done in constructor
TTbarReconstructionVarProcessor::TTbarReconstructionVarProcessor():generator(InterpretationGenerator(IntType::tt, 0, 8)){
}
TTbarReconstructionVarProcessor::~TTbarReconstructionVarProcessor(){}


void TTbarReconstructionVarProcessor::Init(const InputCollections& input,VariableContainer& vars){
    vars.InitVar("TTbarReco_TopHad_M");
    vars.InitVar("TTbarReco_TopHad_Pt");
    vars.InitVar("TTbarReco_TopHad_Eta");
    vars.InitVar("TTbarReco_TopHad_Phi");
    vars.InitVar("TTbarReco_TopHad_CSV");
    vars.InitVar("TTbarReco_TopHad_DrGen");

    vars.InitVar("TTbarReco_TopLep_M");
    vars.InitVar("TTbarReco_TopLep_Pt");
    vars.InitVar("TTbarReco_TopLep_Eta");
    vars.InitVar("TTbarReco_TopLep_Phi");
    vars.InitVar("TTbarReco_TopLep_CSV");
    vars.InitVar("TTbarReco_TopLep_DrGen");

    vars.InitVar("TTbarReco_WHad_M");
    vars.InitVar("TTbarReco_WHad_Pt");
    vars.InitVar("TTbarReco_WHad_Eta");
    vars.InitVar("TTbarReco_WHad_Phi");
    vars.InitVar("TTbarReco_WHad_CSV");
    vars.InitVar("TTbarReco_WHad_DrGen");

    vars.InitVar("TTbarReco_WLep_M");
    vars.InitVar("TTbarReco_WLep_Pt");
    vars.InitVar("TTbarReco_WLep_Eta");
    vars.InitVar("TTbarReco_WLep_Phi");
    vars.InitVar("TTbarReco_WLep_CSV");
    vars.InitVar("TTbarReco_WLep_DrGen");

    vars.InitVar("TTbarReco_BLep_M");
    vars.InitVar("TTbarReco_BLep_Pt");
    vars.InitVar("TTbarReco_BLep_Eta");
    vars.InitVar("TTbarReco_BLep_Phi");
    vars.InitVar("TTbarReco_BLep_CSV");
    vars.InitVar("TTbarReco_BLep_DrGen");

    vars.InitVar("TTbarReco_BHad_M");
    vars.InitVar("TTbarReco_BHad_Pt");
    vars.InitVar("TTbarReco_BHad_Eta");
    vars.InitVar("TTbarReco_BHad_Phi");
    vars.InitVar("TTbarReco_BHad_CSV");
    vars.InitVar("TTbarReco_BHad_DrGen");

    vars.InitVar("TTbarReco_Q1_M");
    vars.InitVar("TTbarReco_Q1_Pt");
    vars.InitVar("TTbarReco_Q1_Eta");
    vars.InitVar("TTbarReco_Q1_Phi");
    vars.InitVar("TTbarReco_Q1_CSV");
    vars.InitVar("TTbarReco_Q1_DrGen");

    vars.InitVar("TTbarReco_Q2_M");
    vars.InitVar("TTbarReco_Q2_Pt");
    vars.InitVar("TTbarReco_Q2_Eta");
    vars.InitVar("TTbarReco_Q2_Phi");
    vars.InitVar("TTbarReco_Q2_CSV");
    vars.InitVar("TTbarReco_Q2_DrGen");
         
    initialized=true;
}

void TTbarReconstructionVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
    if(!initialized) cerr << "tree processor not initialized" << endl;

    if(input.selectedJets.size()<4) return;
    // get vectors
    vector<TLorentzVector> jetvecs = BoostedUtils::GetTLorentzVectors(BoostedUtils::GetJetVecs(input.selectedJets));
    vector<float> jetcsvs;
    int ntags=0;
    for(auto j=input.selectedJets.begin(); j!=input.selectedJets.end(); j++){
	jetcsvs.push_back(MiniAODHelper::GetJetCSV(*j));
	if(BoostedUtils::PassesCSV(*j)) ntags++;
    }
    if(input.selectedElectrons.size()+input.selectedMuons.size()<1) return;
    TLorentzVector lepvec = BoostedUtils::GetTLorentzVector(BoostedUtils::GetPrimLepVec(input.selectedElectrons,input.selectedMuons));
    TVector2 metvec(input.correctedMET.px(),input.correctedMET.py());

    // setup mc matching
    if(input.genTopEvt.IsFilled()&&input.genTopEvt.IsSemiLepton()){
      vector<TLorentzVector> bs_true= BoostedUtils::GetTLorentzVectors(input.genTopEvt.GetHiggsDecayProductVecs());
      vector<TLorentzVector> qs_true= BoostedUtils::GetTLorentzVectors(input.genTopEvt.GetWQuarksVecs());
      if(bs_true.size()==2){
	TLorentzVector bhad_true = BoostedUtils::GetTLorentzVector(input.genTopEvt.GetTopHadDecayQuarkVec());
	TLorentzVector blep_true = BoostedUtils::GetTLorentzVector(input.genTopEvt.GetTopLepDecayQuarkVec());
	TLorentzVector lep_true = BoostedUtils::GetTLorentzVector(input.genTopEvt.GetLeptonVec());
	TLorentzVector nu_true = BoostedUtils::GetTLorentzVector(input.genTopEvt.GetNeutrinoVec());
	mcmatcher.Setup(bhad_true,qs_true[0],qs_true[1],blep_true,lep_true,nu_true,bs_true[0],bs_true[1]);
      }
    }

    //generate interpretations
    Interpretation** ints = generator.GenerateTTHInterpretations(jetvecs,jetcsvs,lepvec,metvec);
    uint nints = generator.GetNints();
    // find best interpretation
    //    Interpretation* best_int_chi2=0;
    Interpretation* best_int_lr=0;
    float best_lr=-99999;
    //    float best_chi2=-99999;
    for(uint i=0; i<nints; i++){
	// likelihood ratio good ttbar reco / combinatorial background
	float lr=quality.TTLikelihood_comb(*(ints[i]));
	// simple chi2 reconstruction using hadronic W and both to masses
	/*	float chi2=quality.TTChi2(*(ints[i]));
	if(chi2>best_chi2){
	    best_chi2=chi2;
	    best_int_chi2=ints[i];
	    }*/
	if(lr>best_lr){
	    best_lr=lr;
	    best_int_lr=ints[i];
	}
    }
    if(best_int_lr!=0){
	vars.FillVar("TTbarReco_TopHad_M",best_int_lr->TopHad().M());
	vars.FillVar("TTbarReco_TopHad_Pt",best_int_lr->TopHad().Pt());
	vars.FillVar("TTbarReco_TopHad_Eta",best_int_lr->TopHad().Eta());
	vars.FillVar("TTbarReco_TopHad_Phi",best_int_lr->TopHad().Phi());
	vars.FillVar("TTbarReco_TopHad_DrGen",mcmatcher.DrTopHad(*best_int_lr));
	
	vars.FillVar("TTbarReco_TopLep_M",best_int_lr->TopLep().M());
	vars.FillVar("TTbarReco_TopLep_Pt",best_int_lr->TopLep().Pt());
	vars.FillVar("TTbarReco_TopLep_Eta",best_int_lr->TopLep().Eta());
	vars.FillVar("TTbarReco_TopLep_DrGen",mcmatcher.DrTopLep(*best_int_lr));
	
	vars.FillVar("TTbarReco_WHad_M",best_int_lr->WHad().M());
	vars.FillVar("TTbarReco_WHad_Pt",best_int_lr->WHad().Pt());
	vars.FillVar("TTbarReco_WHad_Eta",best_int_lr->WHad().Eta());
	vars.FillVar("TTbarReco_WHad_DrGen",mcmatcher.DrWHad(*best_int_lr));
	
	vars.FillVar("TTbarReco_WLep_M",best_int_lr->WLep().M());
	vars.FillVar("TTbarReco_WLep_Pt",best_int_lr->WLep().Pt());
	vars.FillVar("TTbarReco_WLep_Eta",best_int_lr->WLep().Eta());
	vars.FillVar("TTbarReco_WLep_DrGen",mcmatcher.DrWLep(*best_int_lr));
	
	vars.FillVar("TTbarReco_BLep_M",best_int_lr->BLep().M());
	vars.FillVar("TTbarReco_BLep_Pt",best_int_lr->BLep().Pt());
	vars.FillVar("TTbarReco_BLep_Eta",best_int_lr->BLep().Eta());
	vars.FillVar("TTbarReco_BLep_Phi",best_int_lr->BLep().Phi());
	vars.FillVar("TTbarReco_BLep_CSV",best_int_lr->BLep_CSV());
	vars.FillVar("TTbarReco_BLep_DrGen",mcmatcher.DrBLep(*best_int_lr));
	
	vars.FillVar("TTbarReco_BHad_M",best_int_lr->BHad().M());
	vars.FillVar("TTbarReco_BHad_Pt",best_int_lr->BHad().Pt());
	vars.FillVar("TTbarReco_BHad_Eta",best_int_lr->BHad().Eta());
	vars.FillVar("TTbarReco_BHad_Phi",best_int_lr->BHad().Phi());
	vars.FillVar("TTbarReco_BHad_CSV",best_int_lr->BHad_CSV());
	vars.FillVar("TTbarReco_BHad_DrGen",mcmatcher.DrBHad(*best_int_lr));
	
	vars.FillVar("TTbarReco_Q1_M",best_int_lr->Q1().M());
	vars.FillVar("TTbarReco_Q1_Pt",best_int_lr->Q1().Pt());
	vars.FillVar("TTbarReco_Q1_Eta",best_int_lr->Q1().Eta());
	vars.FillVar("TTbarReco_Q1_Phi",best_int_lr->Q1().Phi());
	vars.FillVar("TTbarReco_Q1_CSV",best_int_lr->Q1_CSV());
	vars.FillVar("TTbarReco_Q1_DrGen",mcmatcher.DrQ1(*best_int_lr));

	vars.FillVar("TTbarReco_Q2_M",best_int_lr->Q2().M());
	vars.FillVar("TTbarReco_Q2_Pt",best_int_lr->Q2().Pt());
	vars.FillVar("TTbarReco_Q2_Eta",best_int_lr->Q2().Eta());
	vars.FillVar("TTbarReco_Q2_Phi",best_int_lr->Q2().Phi());
	vars.FillVar("TTbarReco_Q2_CSV",best_int_lr->Q2_CSV());
	vars.FillVar("TTbarReco_Q2_DrGen",mcmatcher.DrQ2(*best_int_lr));
    }
}
