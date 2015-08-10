#include "BoostedTTH/BoostedAnalyzer/interface/ReconstructionVarProcessor.hpp"

using namespace std;

// all configurations should be done in constructor
ReconstructionVarProcessor::ReconstructionVarProcessor(){
    tags.push_back("TTWHChi2");
    tags.push_back("TTWBBChi2");
    tags.push_back("TTWChi2");
    tags.push_back("TTWHLikelihood");
    tags.push_back("TTWBBLikelihood");
    tags.push_back("TTWLikelihood");
    tags.push_back("TTWHLikelihood_comb");
    tags.push_back("TTWBBLikelihood_comb");
    tags.push_back("TTWLikelihood_comb");
    tags.push_back("TTWHishLikelihood");
    tags.push_back("TTWishLikelihood");
}
ReconstructionVarProcessor::~ReconstructionVarProcessor(){}


void ReconstructionVarProcessor::Init(const InputCollections& input,VariableContainer& vars){
    for(auto tagname=tags.begin();tagname!=tags.end();tagname++){
	vars.InitVar("Reco_Highest_"+(*tagname));
	vars.InitVar("Reco_Deta_Fn_"+(*tagname));
	vars.InitVar("Reco_Deta_TopLep_BB_"+(*tagname));
	vars.InitVar("Reco_Deta_TopHad_BB_"+(*tagname));
	vars.InitVar("Reco_Dr_BB_"+(*tagname));
	vars.InitVar("Reco_Higgs_M_"+(*tagname));
	vars.InitVar("Reco_TTWHLikelihood_"+(*tagname));
	vars.InitVar("Reco_TTHBBME _"+(*tagname));
	vars.InitVar("Reco_TTWHLikelihoodTimesME_"+(*tagname));
	vars.InitVar("Reco_TTWBBLikelihood_"+(*tagname));
	vars.InitVar("Reco_TTBBME_"+(*tagname));
	vars.InitVar("Reco_TTWBBLikelihoodTimesME_"+(*tagname));
	vars.InitVar("Reco_TTBBME_off_"+(*tagname));
	vars.InitVar("Reco_TTWBBLikelihoodTimesME_off_"+(*tagname));
	vars.InitVar("Reco_LikelihoodRatio_"+(*tagname));
	vars.InitVar("Reco_MERatio_"+(*tagname));
	vars.InitVar("Reco_MERatio_off_"+(*tagname));
	vars.InitVar("Reco_LikelihoodTimesMERatio_"+(*tagname));
	vars.InitVar("Reco_LikelihoodTimesMERatio_off_"+(*tagname));
    }
    vars.InitVar("Reco_Sum_TTWHLikelihood");
    vars.InitVar("Reco_Sum_TTWBBLikelihood");
    vars.InitVar("Reco_Sum_TTWHLikelihoodTimesME");
    vars.InitVar("Reco_Sum_TTWBBLikelihoodTimesME");
    vars.InitVar("Reco_Sum_TTHBBME");
    vars.InitVar("Reco_Sum_TTBBME");
     
    initialized=true;
}

void ReconstructionVarProcessor::Process(const InputCollections& input,VariableContainer& vars){
    if(!initialized) cerr << "tree processor not initialized" << endl;
    // get vectors
    vector<TLorentzVector> jetvecs = BoostedUtils::GetTLorentzVectors(BoostedUtils::GetJetVecs(input.selectedJets));
    vector<float> jetcsvs;
    for(auto j=input.selectedJets.begin(); j!=input.selectedJets.end(); j++){
	jetcsvs.push_back(BoostedUtils::GetJetCSV(*j));
    }
    TLorentzVector lepvec = BoostedUtils::GetTLorentzVector(BoostedUtils::GetPrimLepVec(input.selectedElectrons,input.selectedMuons));
    TVector2 metvec(input.pfMET.px(),input.pfMET.py());

    // generate interpretations
    vector<Interpretation*> ints = generator.GenerateTTHInterpretations(jetvecs,jetcsvs,lepvec,metvec);
    
    // calculate best tags and interpretations
    map<string,Interpretation*> best_int;
    map<string,float> best_tag;
    for(uint i=0;i<ints.size();i++){
	for(auto tagname=tags.begin();tagname!=tags.end();tagname++){
	    float tag=quality.GetTag(*tagname,*ints[i]);
	    if(tag>best_tag[*tagname]){
		best_int[*tagname]=ints[i];
		best_tag[*tagname]=tag;
	    }
	}
    }

    // add best tags to vars
    for(auto t=best_tag.begin(); t!=best_tag.end(); t++){
	vars.FillVar("Reco_Highest_"+t->first,t->second);
    }

    // calculate variables for best interpretations
    for(auto tagname=tags.begin();tagname!=tags.end();tagname++){
	Interpretation* bi=best_int[*tagname];
	float dEta_fn=sqrt(abs((bi->Higgs().Eta() - bi->TopLep().Eta())*(bi->Higgs().Eta() - bi->TopHad().Eta())));
	vars.FillVar("Reco_Deta_Fn_"+(*tagname),dEta_fn);
	vars.FillVar("Reco_Deta_TopLep_BB_"+(*tagname),abs(bi->Higgs().Eta() - bi->TopLep().Eta()));
	vars.FillVar("Reco_Deta_TopHad_BB_"+(*tagname),abs(bi->Higgs().Eta() - bi->TopHad().Eta()));
	vars.FillVar("Reco_Dr_BB_"+(*tagname),bi->B1().DeltaR(bi->B2()));
	vars.FillVar("Reco_Higgs_M_"+(*tagname),best_int[*tagname]->Higgs_M());
	double tthlike= quality.TTWHLikelihood(*bi);
	double tthme = quality.TTHBB_ME(*bi);
	double tthlikeme = tthlike*tthme;
	double ttbblike= quality.TTWBBLikelihood(*bi);
	double ttbbme = quality.TTBB_ON_ME(*bi);
	double ttbblikeme = ttbblike*ttbbme;
	double ttbbme_off = quality.TTBB_OFF_ME(*bi);
	double ttbblikeme_off = ttbblike*ttbbme_off;
	double like_ratio = tthlike/(tthlike+ttbblike);
	double tthme_ratio = tthme/(tthme+ttbbme);
	double tthme_ratio_off = tthme/(tthme+ttbbme_off);
	double tthlikeme_ratio = tthlikeme/(tthlikeme+ttbblikeme);
	double tthlikeme_ratio_off = tthlikeme/(tthlikeme+ttbblikeme_off);
	vars.FillVar("Reco_TTWHLikelihood_"+(*tagname),tthlike);
	vars.FillVar("Reco_TTHBBME _"+(*tagname),tthme );
	vars.FillVar("Reco_TTWHLikelihoodTimesME_"+(*tagname),tthlikeme);
	vars.FillVar("Reco_TTWBBLikelihood_"+(*tagname),ttbblike);
	vars.FillVar("Reco_TTBBME_"+(*tagname),ttbbme);
	vars.FillVar("Reco_TTWBBLikelihoodTimesME_"+(*tagname),ttbblikeme);
	vars.FillVar("Reco_TTBBME_off_"+(*tagname),ttbbme_off);
	vars.FillVar("Reco_TTWBBLikelihoodTimesME_off_"+(*tagname),ttbblikeme_off);
	vars.FillVar("Reco_LikelihoodRatio_"+(*tagname),like_ratio);
	vars.FillVar("Reco_MERatio_"+(*tagname),tthme_ratio);
	vars.FillVar("Reco_MERatio_off_"+(*tagname),tthme_ratio_off);
	vars.FillVar("Reco_LikelihoodTimesMERatio_"+(*tagname),tthlikeme_ratio);
	vars.FillVar("Reco_LikelihoodTimesMERatio_off_"+(*tagname),tthlikeme_ratio_off);
	
    }


    // sum up likelihoods
    double sum_tth_likelihood=0;
    double sum_ttbb_likelihood=0; 
    double sum_tth_me_likelihood=0;
    double sum_ttbb_me_likelihood=0;
    double sum_tth_me=0;
    double sum_ttbb_me=0;   
    for(uint i=0;i<ints.size();i++){
	// calculating MEs for many interpretations can take a lot of time
	double tthlike= quality.TTWHLikelihood(*ints[i]);
	double tthme = quality.TTHBB_ME(*ints[i]);
	double tthlikeme = tthlike*tthme;
	double ttbblike= quality.TTWBBLikelihood(*ints[i]);
	double ttbbme = quality.TTBB_ON_ME(*ints[i]);
	double ttbblikeme = ttbblike*ttbbme;
	sum_tth_likelihood+=tthlike;
	sum_tth_me+=tthme;
	sum_tth_me_likelihood+=tthlikeme;
	sum_ttbb_likelihood+=ttbblike;
	sum_ttbb_me+=ttbbme;
	sum_ttbb_me_likelihood+=ttbblikeme;
    }
    vars.FillVar("Reco_Sum_TTWHLikelihood",sum_tth_likelihood);
    vars.FillVar("Reco_Sum_TTWBBLikelihood",sum_ttbb_likelihood);
    vars.FillVar("Reco_Sum_TTWHLikelihoodTimesME",sum_tth_me_likelihood);
    vars.FillVar("Reco_Sum_TTWBBLikelihoodTimesME",sum_ttbb_me_likelihood);
    vars.FillVar("Reco_Sum_TTHBBME",sum_tth_me);
    vars.FillVar("Reco_Sum_TTBBME",sum_ttbb_me);

  
}
