#include "BoostedTTH/TTHReconstruction/interface/InterpretationGenerator.hpp"
using namespace std;

InterpretationGenerator::InterpretationGenerator(IntType::IntType type_, int allowedMistags_, int maxJets_, float minMWHad_,float maxMWHad_,float btagCut_):type(type_), allowedMistags(allowedMistags_), maxJets(maxJets_), minMWHad(minMWHad_), maxMWHad(maxMWHad_), btagCut(btagCut_)
{}

Interpretation** InterpretationGenerator::GenerateTTHInterpretations(std::vector<TLorentzVector> jetvecs_in, std::vector<float> jetcsvs_in, TLorentzVector lepvec, TVector2 metvec){
    // interpreatations
    for(uint i=0; i<interpretations.size(); i++){
	delete interpretations[i];
    }
    interpretations.clear();
    
    // Neutrino reconstruction
    TLorentzVector nuvec1;
    TLorentzVector nuvec2;
    GetNuVecs(lepvec,metvec,nuvec1,nuvec2);
    uint nNu=2;
    // if the two neutrino solutions are very close let's use just one
    if(fabs(nuvec1.Pz()-nuvec2.Pz()<1)) nNu=1;
    
    // make some basic cuts on jets
    std::vector<TLorentzVector> jetvecs;
    std::vector<float> jetcsvs;
    // number of jets and tags actually used
    int njets=0;
    int ntags=0;
    // use all tagged jets
    for(uint i=0; i<jetvecs_in.size(); i++){
	if(jetcsvs_in[i]>btagCut){
	    ntags++;
	    njets++;
	    jetvecs.push_back(jetvecs_in[i]);
	    jetcsvs.push_back(jetcsvs_in[i]);
	}
    }
    // fill up until njets = maxjets with untagged jets
    for(uint i=0; njets<maxJets&&i<jetvecs_in.size(); i++){
	if(jetcsvs_in[i]<=btagCut){
	    njets++;
	    jetvecs.push_back(jetvecs_in[i]);
	    jetcsvs.push_back(jetcsvs_in[i]);
	}
    }
    // vector of jet indices
    vector<int> idxs(njets);
    for(int i=0;i<njets;i++){
	idxs[i]=i;
    }
    // set number of jets that are used in permutations 
    int k=6;
    // number of tags that are expected for interpreation (4 for tth)
    int expected_tags=4;
    if(type==IntType::tt||type==IntType::tt_plus){
	k=4;
	expected_tags=2;
    }
    else if(type==IntType::tth5||type==IntType::tth5_plus){
	k=5;
    }
    // if njets<k no interpretation is possible, njets<4 is not supported, too
    if(njets<4||njets<k) return 0;
    if(njets<6&&(type==IntType::tth||type==IntType::tth_plus)) return 0;
    if(njets<5&&(type==IntType::tth5||type==IntType::tth5_plus)) return 0;
    
    // loop over neutrino solutions
    for(uint iNu=1; iNu<=nNu;iNu++){  
	// for all permutations of subsets with k jets  
	do{
	    // skip uninteresting interpretations
	    if(idxs[0]>idxs[1]) continue; // skip switched whad
	    if(njets>5 && idxs[4]>idxs[5]) continue; // skip switched higgs
	    int iQ1=idxs[0];
	    int iQ2=idxs[1];
	    int iBHad=idxs[2];
	    int iBLep=idxs[3];
	    int iB1=-1;
	    int iB2=-1;
	    if(njets>5){
		iB1=idxs[4];
		iB2=idxs[5];
	    }
	    int tags_used=0;
	    if(iB1>-1&&jetcsvs[iB1]>btagCut) tags_used++;
	    if(iB2>-1&&jetcsvs[iB2]>btagCut) tags_used++;
	    if(jetcsvs[iBHad]>btagCut) tags_used++;
	    if(jetcsvs[iBLep]>btagCut) tags_used++;
	    if(tags_used + allowedMistags < min(expected_tags,ntags) ){
		continue; // skip events with too few b-tagged b-quarks
	    }
	    // skip permutations not in whad window
	    if( (jetvecs[iQ1]+jetvecs[iQ2]).M()>maxMWHad || (jetvecs[iQ1]+jetvecs[iQ2]).M() < minMWHad) continue;
	    
	    // generate new interpretation
	    if(type==IntType::tth_plus){
		std::vector<TLorentzVector> additional_jets;
		std::vector<float> additional_jetcsvs;
		for(int i=0; i<int(jetvecs.size()); i++){
		    if(i!=iB1&&i!=iB2&&i!=iBLep&&i!=iBHad&&i!=iQ1&&i!=iQ2){
			additional_jets.push_back(jetvecs[i]);
			additional_jetcsvs.push_back(jetcsvs[i]);
		    }
		}
		interpretations.push_back(new Interpretation(jetvecs[iBHad],jetcsvs[iBHad],
							     jetvecs[iQ1],jetcsvs[iQ1],
							     jetvecs[iQ2],jetcsvs[iQ2],
							     jetvecs[iBLep],jetcsvs[iBLep],
							     lepvec,iNu==1?nuvec1:nuvec2,
							     jetvecs[iB1],jetcsvs[iB1],
							     jetvecs[iB2],jetcsvs[iB2],
							     additional_jets,additional_jetcsvs));
	    }
	    else if(type==IntType::tth){
		interpretations.push_back(new Interpretation(jetvecs[iBHad],jetcsvs[iBHad],
							     jetvecs[iQ1],jetcsvs[iQ1],
							     jetvecs[iQ2],jetcsvs[iQ2],
							     jetvecs[iBLep],jetcsvs[iBLep],
							     lepvec,iNu==1?nuvec1:nuvec2,
							     jetvecs[iB1],jetcsvs[iB1],
							     jetvecs[iB2],jetcsvs[iB2]));
	    }
	    else if(type==IntType::tt_plus){
		std::vector<TLorentzVector> additional_jets;
		std::vector<float> additional_jetcsvs;
		for(int i=0; i<int(jetvecs.size()); i++){
		    if(i!=iB1&&i!=iB2&&i!=iBLep&&i!=iBHad&&i!=iQ1&&i!=iQ2){
			additional_jets.push_back(jetvecs[i]);
			additional_jetcsvs.push_back(jetcsvs[i]);
		    }
		}
		interpretations.push_back(new Interpretation(jetvecs[iBHad],jetcsvs[iBHad],
							     jetvecs[iQ1],jetcsvs[iQ1],
							     jetvecs[iQ2],jetcsvs[iQ2],
							     jetvecs[iBLep],jetcsvs[iBLep],
							     lepvec,iNu==1?nuvec1:nuvec2,
							     additional_jets,additional_jetcsvs));
	    }
	    else if(type==IntType::tt){
		interpretations.push_back(new Interpretation(jetvecs[iBHad],jetcsvs[iBHad],
							     jetvecs[iQ1],jetcsvs[iQ1],
							     jetvecs[iQ2],jetcsvs[iQ2],
							     jetvecs[iBLep],jetcsvs[iBLep],
							     lepvec,iNu==1?nuvec1:nuvec2));
	    }
	    
	}while(NextSubsetPermutation(idxs,k));
    }
    return interpretations.size()==0 ? 0 : &(interpretations[0]);
}

uint InterpretationGenerator::GetNints(){
    return interpretations.size();
}

bool InterpretationGenerator::NextSubsetPermutation(vector<int>& idxs, int k){
    if(next_permutation(idxs.begin(), idxs.begin()+k)) return true;
    else if(next_combination(idxs.begin(), idxs.begin()+k, idxs.end())) return true;
    else return false;
}

void InterpretationGenerator::GetNuVecs(const TLorentzVector & lepvec, const TVector2 & metvec, TLorentzVector & nu1, TLorentzVector & nu2){
    double metvec2 = metvec.Px()*metvec.Px() + metvec.Py()*metvec.Py();
    double mu = (80.4*80.4)/2 + metvec.Px()*lepvec.Px() + metvec.Py()*lepvec.Py();
    double a = (mu*lepvec.Pz())/(lepvec.E()*lepvec.E() - lepvec.Pz()*lepvec.Pz());
    double a2 = TMath::Power(a, 2);
    double b = (TMath::Power(lepvec.E(), 2.)*metvec2 - TMath::Power(mu, 2.)) / (TMath::Power(lepvec.E(), 2)- TMath::Power(lepvec.Pz(), 2));
    float pz1,pz2;
    if (a2-b < 0) { 
	pz1 = a;
	pz2 = a;
    } else {
	double root = sqrt(a2-b);
	pz1 = a + root;
	pz2 = a - root;
    }
    nu1.SetPxPyPzE(metvec.Px(),metvec.Py(),pz1,sqrt(metvec.Mod2()+pz1*pz1));
    nu2.SetPxPyPzE(metvec.Px(),metvec.Py(),pz2,sqrt(metvec.Mod2()+pz2*pz2));
}
