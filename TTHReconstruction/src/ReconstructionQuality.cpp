#include "BoostedTTH/TTHReconstruction/interface/ReconstructionQuality.hpp"

using namespace std;

ReconstructionQuality::ReconstructionQuality(string filename){
    if(filename==""){
	std::string cmsswbase = getenv("CMSSW_BASE");
	filename=cmsswbase+"/src/BoostedTTH/TTHReconstruction/data/likelihoodhistos.root";
    }
    
    file=TFile::Open(filename.c_str());
    h_CSV_b=(TH1F*)file->Get("CSV_b");
    h_CSV_l_w_c=(TH1F*)file->Get("CSV_l_w_c");
    h_M_Higgs_reco=(TH1F*)file->Get("M_Higgs_reco");
    h_M_BB_reco=(TH1F*)file->Get("M_BB_reco");
    h_M_TopHad_reco=(TH1F*)file->Get("M_TopHad_reco");
    h_M_TopHad_pca_reco=(TH1F*)file->Get("M_TopHad_pca_reco");
    h_M_TopLep_reco=(TH1F*)file->Get("M_TopLep_reco");
    h_M_WHad_reco=(TH1F*)file->Get("M_WHad_reco");
    h_M_WHad_pca_reco=(TH1F*)file->Get("M_WHad_pca_reco");
    h_M_Higgs_best=(TH1F*)file->Get("M_Higgs_best");
    h_M_TopHad_best=(TH1F*)file->Get("M_TopHad_best");
    h_M_TopLep_best=(TH1F*)file->Get("M_TopLep_best");
    h_M_WHad_best=(TH1F*)file->Get("M_WHad_best");
    h_M_Higgs_all=(TH1F*)file->Get("M_Higgs_all");
    h_M_BB_all=(TH1F*)file->Get("M_BB_all");
    h_M_TopHad_all=(TH1F*)file->Get("M_TopHad_all");
    h_M_TopHad_pca_all=(TH1F*)file->Get("M_TopHad_pca_all");
    h_M_TopLep_all=(TH1F*)file->Get("M_TopLep_all");
    h_M_WHad_all=(TH1F*)file->Get("M_WHad_all");
    h_M_WHad_pca_all=(TH1F*)file->Get("M_WHad_pca_all");
    
    higgs_mean=111;
    tophad_mean=165;
    toplep_mean=168;
    whad_mean=80;
    higgs_sigma=17;
    tophad_sigma=17;
    toplep_sigma=26;
    whad_sigma=10;
    tiny_likelihood=1e-6;
    bb_slope=0.0128;
}

float ReconstructionQuality::GetTag(std::string tag, Interpretation& i){
    
    if(tag=="TTHChi2") return TTHChi2(i);
    else if(tag=="TTBBChi2") return TTBBChi2(i);
    else if(tag=="TTChi2") return TTChi2(i);
    
    else if(tag=="TTHLikelihood") return TTHLikelihood(i);
    else if(tag=="TTBBLikelihood") return TTBBLikelihood(i);
    else if(tag=="TTLikelihood") return TTLikelihood(i);

    else if(tag=="TTHLikelihoodTimesME") return TTHLikelihoodTimesME(i);
    else if(tag=="TTBBLikelihoodTimesME") return TTBBLikelihoodTimesME(i);
    
    else if(tag=="TTHLikelihood_comb") return TTHLikelihood_comb(i);
    else if(tag=="TTBBLikelihood_comb") return TTBBLikelihood_comb(i);
    else if(tag=="TTLikelihood_comb") return TTLikelihood_comb(i);
    
    else if(tag=="TTH_ME") return TTH_ME(i);
    else if(tag=="TTHBB_ME") return TTHBB_ME(i);
    else if(tag=="TTBB_ON_ME") return TTBB_ON_ME(i);
    else if(tag=="TTBB_OFF_ME") return TTBB_OFF_ME(i);
    else{
	cout << "tag " << tag << " unknown!" << endl;
	return -1e20;
    }
}


float ReconstructionQuality::TTHChi2(float mthad, float mtlep, float mwhad, float mhiggs){
    float chi2=0;
    chi2+=(mthad-tophad_mean)*(mthad-tophad_mean)/(tophad_sigma*tophad_sigma);
    chi2+=(mtlep-toplep_mean)*(mtlep-toplep_mean)/(toplep_sigma*toplep_sigma);
    chi2+=(mhiggs-higgs_mean)*(mhiggs-higgs_mean)/(higgs_sigma*higgs_sigma);
    chi2+=(mwhad-whad_mean)*(mwhad-whad_mean)/(whad_sigma*whad_sigma);
    return -chi2;
}

float ReconstructionQuality::TTBBChi2(float mthad, float mtlep, float mwhad, float mhiggs){
    float chi2=0;
    chi2+=(mthad-tophad_mean)*(mthad-tophad_mean)/(tophad_sigma*tophad_sigma);
    chi2+=(mtlep-toplep_mean)*(mtlep-toplep_mean)/(toplep_sigma*toplep_sigma);
    chi2+=2*bb_slope*mhiggs;
    chi2+=(mwhad-whad_mean)*(mwhad-whad_mean)/(whad_sigma*whad_sigma);
    return -chi2;
}
float ReconstructionQuality::TTChi2(float mthad, float mtlep, float mwhad){
    float chi2=0;
    chi2+=(mthad-tophad_mean)*(mthad-tophad_mean)/(tophad_sigma*tophad_sigma);
    chi2+=(mtlep-toplep_mean)*(mtlep-toplep_mean)/(toplep_sigma*toplep_sigma);
    chi2+=(mwhad-whad_mean)*(mwhad-whad_mean)/(whad_sigma*whad_sigma);
    return -chi2;
}

float ReconstructionQuality::TTHLikelihood(float mthad, float mtlep, float mwhad, float mhiggs){
    float llh=1;
    llh*=TopAndWHadLikelihood(mthad,mwhad);
    llh*=TopLepLikelihood(mtlep);
    llh*=HiggsLikelihood(mhiggs);
    return llh;
}
float ReconstructionQuality::TTBBLikelihood(float mthad, float mtlep, float mwhad, float mhiggs){
    float llh=1;
    llh*=TopAndWHadLikelihood(mthad,mwhad);
    llh*=TopLepLikelihood(mtlep);
    llh*=BBLikelihood(mhiggs);
    return 2*llh;
}
float ReconstructionQuality::TTLikelihood(float mthad, float mtlep, float mwhad){
    float llh=1;
    llh*=TopAndWHadLikelihood(mthad,mwhad);
    llh*=TopLepLikelihood(mtlep);
    return llh;
}
float ReconstructionQuality::TTHLikelihood(Interpretation& i){
    if(i.HasTag("TTHLikelihood")) return i.GetTag("TTHLikelihood");
    float tag=TTHLikelihood(i.TopHad_M(),i.TopLep_M(),i.WHad_M(),i.Higgs_M());
    i.SetTag("TTHLikelihood",tag);
    return tag;
}
float ReconstructionQuality::TTBBLikelihood(Interpretation& i){
    if(i.HasTag("TTBBLikelihood")) return i.GetTag("TTBBLikelihood");
    float tag=TTBBLikelihood(i.TopHad_M(),i.TopLep_M(),i.WHad_M(),i.Higgs_M());
    i.SetTag("TTBBLikelihood",tag);
    return tag;
}
float ReconstructionQuality::TTLikelihood(Interpretation& i){
    if(i.HasTag("TTLikelihood")) return i.GetTag("TTLikelihood");
    float tag=TTLikelihood(i.TopHad_M(),i.TopLep_M(),i.WHad_M());
    i.SetTag("TTLikelihood",tag);
    return tag;
}

float ReconstructionQuality::TTHLikelihoodTimesME(Interpretation& i){
    if(i.HasTag("TTHLikelihoodTimesME")) return i.GetTag("TTHLikelihoodTimesME");
    float tag=TTHLikelihood(i.TopHad_M(),i.TopLep_M(),i.WHad_M(),i.Higgs_M());
    tag*=TTHBB_ME(i);
    i.SetTag("TTHLikelihoodTimesME",tag);
    return tag;
}
float ReconstructionQuality::TTBBLikelihoodTimesME(Interpretation& i){
    if(i.HasTag("TTBBLikelihoodTimesME")) return i.GetTag("TTBBLikelihoodTimesME");
    float tag=TTBBLikelihood(i.TopHad_M(),i.TopLep_M(),i.WHad_M(),i.Higgs_M());
    tag*=TTBB_ON_ME(i);
    i.SetTag("TTBBLikelihoodTimesME",tag);
    return tag;
}


float ReconstructionQuality::TTHLikelihood_comb(float mthad, float mtlep, float mwhad, float mhiggs){
    float llh=1;
    llh*=TopAndWHadLikelihood_comb(mthad,mwhad);
    llh*=TopLepLikelihood_comb(mtlep);
    llh*=HiggsLikelihood_comb(mhiggs);
    return llh;
}
float ReconstructionQuality::TTBBLikelihood_comb(float mthad, float mtlep, float mwhad, float mhiggs){
    float llh=1;
    llh*=TopAndWHadLikelihood_comb(mthad,mwhad);
    llh*=TopLepLikelihood_comb(mtlep);
    llh*=BBLikelihood_comb(mhiggs);
    return llh;
}
float ReconstructionQuality::TTLikelihood_comb(float mthad, float mtlep, float mwhad){
    float llh=1;
    llh*=TopAndWHadLikelihood_comb(mthad,mwhad);
    llh*=TopLepLikelihood_comb(mtlep);
    return llh;
}
float ReconstructionQuality::TTHLikelihood_comb(Interpretation& i){
    if(i.HasTag("TTHLikelihood_comb")) return i.GetTag("TTHLikelihood_comb");
    float tag=TTHLikelihood_comb(i.TopHad_M(),i.TopLep_M(),i.WHad_M(),i.Higgs_M());
    i.SetTag("TTHLikelihood_comb",tag);
    return tag;
}
float ReconstructionQuality::TTBBLikelihood_comb(Interpretation& i){
    if(i.HasTag("TTBBLikelihood_comb")) return i.GetTag("TTBBLikelihood_comb");
    float tag=TTBBLikelihood_comb(i.TopHad_M(),i.TopLep_M(),i.WHad_M(),i.Higgs_M());
    i.SetTag("TTBBLikelihood_comb",tag);
    return tag;
}

float ReconstructionQuality::TTLikelihood_comb(Interpretation& i){
    if(i.HasTag("TTLikelihood_comb")) return i.GetTag("TTLikelihood_comb");
    float tag=TTLikelihood_comb(i.TopHad_M(),i.TopLep_M(),i.WHad_M());
    i.SetTag("TTLikelihood_comb",tag);
    return tag;
}


float ReconstructionQuality::TTHChi2(Interpretation& i){
    if(i.HasTag("TTHChi2")) return i.GetTag("TTHChi2");
    float tag=TTHChi2(i.TopHad_M(),i.TopLep_M(),i.WHad_M(),i.Higgs_M());
    i.SetTag("TTHChi2",tag);
    return tag;
}
float ReconstructionQuality::TTBBChi2(Interpretation& i){
    if(i.HasTag("TTBBChi2")) return i.GetTag("TTBBChi2");
    float tag=TTBBChi2(i.TopHad_M(),i.TopLep_M(),i.WHad_M(),i.Higgs_M());
    i.SetTag("TTBBChi2",tag);
    return tag;
}

float ReconstructionQuality::TTChi2(Interpretation& i){
    if(i.HasTag("TTChi2")) return i.GetTag("TTChi2");
    float tag=TTChi2(i.TopHad_M(),i.TopLep_M(),i.WHad_M());
    i.SetTag("TTChi2",tag);
    return tag;
}

float ReconstructionQuality::TTH_ME(Interpretation& i){
    if(i.HasTag("TTH_ME")) return i.GetTag("TTH_ME");
    float tag=3e3*me.GetTTHMEsq(i.TopHad(),i.TopLep(),i.Higgs());
    i.SetTag("TTH_ME",tag);
    return tag;
}

float ReconstructionQuality::TTBB_ON_ME(Interpretation& i){
    if(i.HasTag("TTBB_ON_ME")) return i.GetTag("TTBB_ON_ME");
    float tag=3e3*me.GetTTBBMEsq_onshell(i.TopHad(),i.TopLep(),i.B1(),i.B2());
    i.SetTag("TTBB_ON_ME",tag);
    return tag;
}
float ReconstructionQuality::TTBB_OFF_ME(Interpretation& i){
    if(i.HasTag("TTBB_OFF_ME")) return i.GetTag("TTBB_OFF_ME");
    float tag=3e3*me.GetTTBBMEsq_offshell(i.TopHad(),i.TopLep(),i.B1(),i.B2());
    i.SetTag("TTBB_OFF_ME",tag);
    return tag;
}


float ReconstructionQuality::TTHBB_ME(Interpretation& i){
    if(i.HasTag("TTHBB_ME")) return i.GetTag("TTHBB_ME");
    float tag=me.GetTTHBBMEsq(i.TopHad(),i.TopLep(),i.B1(),i.B2());
    i.SetTag("TTHBB_ME",tag);
    return tag;
}

float ReconstructionQuality::TopAndWHadLikelihood(Interpretation& i){
    if(i.HasTag("TopAndWHadLikelihood")) return i.GetTag("TopAndWHadLikelihood");
    float tag=TopAndWHadLikelihood(i.TopHad_M(),i.WHad_M());
    i.SetTag("TopAndWHadLikelihood",tag);
    return tag;
}


float ReconstructionQuality::BLikelihood(float csv){
    csv=fmax(csv,-0.099);
    float llh=Interpolate(h_CSV_b,csv);
    return llh;
}
float ReconstructionQuality::LLikelihood(float csv){
    csv=fmax(csv,-0.099);
    float llh=Interpolate(h_CSV_l_w_c, csv);
    return llh;
}
float ReconstructionQuality::TopHadLikelihood(float m){
    float llh=Interpolate(h_M_TopHad_reco,m);
    return llh;
}
float ReconstructionQuality::TopHadLikelihood_comb(float m){
    float llh=Interpolate(h_M_TopHad_all,m);
    return llh;
}
float ReconstructionQuality::TopAndWHadLikelihood(float mt, float mw){
    float mt_new, mw_new;
    PCA_MW_MT(mw,mt,mw_new,mt_new);
    float llh=1.;
    llh*=Interpolate(h_M_TopHad_pca_all,mt_new);
    llh*=Interpolate(h_M_WHad_pca_all,mw_new);
    return llh;
}
float ReconstructionQuality::TopAndWHadLikelihood_comb(float mt, float mw){
    float mt_new, mw_new;
    PCA_MW_MT(mw,mt,mw_new,mt_new);
    float llh=1.;
    llh*=Interpolate(h_M_TopHad_pca_reco,mt_new);
    llh*=Interpolate(h_M_WHad_pca_reco,mw_new);
    return llh;
}
float ReconstructionQuality::TopLepLikelihood(float m){
    float llh=Interpolate(h_M_TopLep_reco,m);
    return llh;
}
float ReconstructionQuality::TopLepLikelihood_comb(float m){
    float llh=Interpolate(h_M_TopLep_all,m);
    return llh;
}

float ReconstructionQuality::WHadLikelihood(float m){
    float llh= Interpolate(h_M_WHad_reco,m);
    return llh;
}
float ReconstructionQuality::WHadLikelihood_comb(float m){
    float llh= Interpolate(h_M_WHad_all,m);
    return llh;
}

float ReconstructionQuality::HiggsLikelihood(float m){
    float llh= Interpolate(h_M_Higgs_reco,m);
    return llh;
}
float ReconstructionQuality::HiggsLikelihood_comb(float m){
    float llh= Interpolate(h_M_Higgs_all,m);
    return llh;
}
float ReconstructionQuality::BBLikelihood(float m){
    float llh= Interpolate(h_M_BB_reco,m);
    return llh;
}
float ReconstructionQuality::BBLikelihood_comb(float m){
    float llh= Interpolate(h_M_BB_all,m);
    return llh;
}

float ReconstructionQuality::Interpolate(TH1F* histo, float value){
    if(value>histo->GetXaxis()->GetXmax()){
	return histo->GetBinContent(histo->GetNbinsX())*tiny_likelihood;
    }
    if(value<histo->GetXaxis()->GetXmin()){
	return histo->GetBinContent(0)*tiny_likelihood;
    }
    return fmax(histo->Interpolate(value),tiny_likelihood);
}

float ReconstructionQuality::NBLikelihood(uint ntagged, uint njets,const double* csvs){
  if(njets<ntagged) return 0;
  double llh=0.; // total likelihood
  vector<int> idxs(njets);
  for(uint i=0;i<njets;i++){
    idxs[i]=i;
  }
  do{
    double l=1; //likelihood of current combination
    for(uint i=0; i<ntagged;i++){
      l*=BLikelihood(csvs[idxs[i]]);
    }
    for(uint i=ntagged; i<njets;i++){
      l*=LLikelihood(csvs[idxs[i]]);
    }
    llh+=l;     
  }while(next_combination(idxs.begin(), idxs.begin()+ntagged, idxs.end()));
  return llh;
}

void ReconstructionQuality::PCA_MW_MT(float mw, float mt, float& mw_new , float& mt_new){
  mt_new=(mw-83.7)/21.+(mt-172.5)/33.2;
  mw_new=(mw-83.7)/21.-(mt-172.5)/33.2;
}
