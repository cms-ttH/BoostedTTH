#include "BoostedTTH/TTHReconstruction/interface/ReconstructionQuality.hpp"

using namespace std;

ReconstructionQuality::ReconstructionQuality(string filename){
  file=TFile::Open(filename.c_str());
  h_CSV_b=(TH1F*)file->Get("CSV_b");
  h_CSV_l_w_c=(TH1F*)file->Get("CSV_l_w_c");
  h_M_Higgs_reco=(TH1F*)file->Get("M_Higgs_reco");
  h_M_BB_reco=(TH1F*)file->Get("M_BB_reco");
  h_M_TopHad_reco=(TH1F*)file->Get("M_TopHad_reco");
  h_M_TopLep_reco=(TH1F*)file->Get("M_TopLep_reco");
  h_M_WHad_reco=(TH1F*)file->Get("M_WHad_reco");
  h_M_Higgs_best=(TH1F*)file->Get("M_Higgs_best");
  h_M_TopHad_best=(TH1F*)file->Get("M_TopHad_best");
  h_M_TopLep_best=(TH1F*)file->Get("M_TopLep_best");
  h_M_WHad_best=(TH1F*)file->Get("M_WHad_best");
  h_M_Higgs_all=(TH1F*)file->Get("M_Higgs_all");
  h_M_BB_all=(TH1F*)file->Get("M_BB_all");
  h_M_TopHad_all=(TH1F*)file->Get("M_TopHad_all");
  h_M_TopLep_all=(TH1F*)file->Get("M_TopLep_all");
  h_M_WHad_all=(TH1F*)file->Get("M_WHad_all");

  higgs_mean=111;
  tophad_mean=165;
  toplep_mean=168;
  whad_mean=80;
  higgs_sigma=17;
  tophad_sigma=17;
  toplep_sigma=26;
  whad_sigma=10;
  tiny_likelihood=1e-4;
  bb_slope=0.0128;
}

float ReconstructionQuality::GetTag(std::string tag, Interpretation& i){
   
  if(tag=="TTWHChi2") return TTWHChi2(i);
  else if(tag=="TTWBBChi2") return TTWBBChi2(i);
  else if(tag=="TTWChi2") return TTWChi2(i);

  else if(tag=="TTWHLikelihood") return TTWHLikelihood(i);
  else if(tag=="TTWBBLikelihood") return TTWBBLikelihood(i);
  else if(tag=="TTWLikelihood") return TTWLikelihood(i);

  else if(tag=="TTWHLikelihood_comb") return TTWHLikelihood_comb(i);
  else if(tag=="TTWBBLikelihood_comb") return TTWBBLikelihood_comb(i);
  else if(tag=="TTWLikelihood_comb") return TTWLikelihood_comb(i);

  else if(tag=="TTWHishLikelihood") return TTWHishLikelihood(i);
  else if(tag=="TTWishLikelihood") return TTWishLikelihood(i);

  else if(tag=="TTH_ME") return TTH_ME(i);
  else if(tag=="TTHBB_ME") return TTHBB_ME(i);
  else if(tag=="TTBB_ON_ME") return TTBB_ON_ME(i);
  else if(tag=="TTBB_OFF_ME") return TTBB_OFF_ME(i);
  else{
    cout << "tag " << tag << " unknown!" << endl;
    return -1e20;
  }
}


float ReconstructionQuality::TTWHChi2(float mthad, float mtlep, float mwhad, float mhiggs){
  float chi2=0;
  chi2+=(mthad-tophad_mean)*(mthad-tophad_mean)/(tophad_sigma*tophad_sigma);
  chi2+=(mtlep-toplep_mean)*(mtlep-toplep_mean)/(toplep_sigma*toplep_sigma);
  chi2+=(mhiggs-higgs_mean)*(mhiggs-higgs_mean)/(higgs_sigma*higgs_sigma);
  chi2+=(mwhad-whad_mean)*(mwhad-whad_mean)/(whad_sigma*whad_sigma);
  return -chi2;
}

float ReconstructionQuality::TTWBBChi2(float mthad, float mtlep, float mwhad, float mhiggs){
  float chi2=0;
  chi2+=(mthad-tophad_mean)*(mthad-tophad_mean)/(tophad_sigma*tophad_sigma);
  chi2+=(mtlep-toplep_mean)*(mtlep-toplep_mean)/(toplep_sigma*toplep_sigma);
  chi2+=2*bb_slope*mhiggs;
  chi2+=(mwhad-whad_mean)*(mwhad-whad_mean)/(whad_sigma*whad_sigma);
  return -chi2;
}
float ReconstructionQuality::TTWChi2(float mthad, float mtlep, float mwhad){
  float chi2=0;
  chi2+=(mthad-tophad_mean)*(mthad-tophad_mean)/(tophad_sigma*tophad_sigma);
  chi2+=(mtlep-toplep_mean)*(mtlep-toplep_mean)/(toplep_sigma*toplep_sigma);
  chi2+=(mwhad-whad_mean)*(mwhad-whad_mean)/(whad_sigma*whad_sigma);
  return -chi2;
}

float ReconstructionQuality::TTWHLikelihood(float mthad, float mtlep, float mwhad, float mhiggs){
  float llh=1;
  llh*=TopHadLikelihood(mthad);
  llh*=TopLepLikelihood(mtlep);
  llh*=WHadLikelihood(mwhad);
  llh*=HiggsLikelihood(mhiggs);
  return llh;
}
float ReconstructionQuality::TTWBBLikelihood(float mthad, float mtlep, float mwhad, float mhiggs){
  float llh=1;
  llh*=TopHadLikelihood(mthad);
  llh*=TopLepLikelihood(mtlep);
  llh*=WHadLikelihood(mwhad);
  llh*=BBLikelihood(mhiggs);
  return 2*llh;
}
float ReconstructionQuality::TTWLikelihood(float mthad, float mtlep, float mwhad){
  float llh=1;
  llh*=TopHadLikelihood(mthad);
  llh*=TopLepLikelihood(mtlep);
  llh*=WHadLikelihood(mwhad);
  return llh;
}
float ReconstructionQuality::TTWHLikelihood(Interpretation& i){
  if(i.HasTag("TTWHLikelihood")) return i.GetTag("TTWHLikelihood");
  float tag=TTWHLikelihood(i.TopHad_M(),i.TopLep_M(),i.WHad_M(),i.Higgs_M());
  i.SetTag("TTWHLikelihood",tag);
  return tag;
}
float ReconstructionQuality::TTWBBLikelihood(Interpretation& i){
  if(i.HasTag("TTWBBLikelihood")) return i.GetTag("TTWBBLikelihood");
  float tag=TTWBBLikelihood(i.TopHad_M(),i.TopLep_M(),i.WHad_M(),i.Higgs_M());
  i.SetTag("TTWBBLikelihood",tag);
  return tag;
}

float ReconstructionQuality::TTWLikelihood(Interpretation& i){
  if(i.HasTag("TTWLikelihood")) return i.GetTag("TTWLikelihood");
  float tag=TTWLikelihood(i.TopHad_M(),i.TopLep_M(),i.WHad_M());
  i.SetTag("TTWLikelihood",tag);
  return tag;
}


float ReconstructionQuality::TTWHLikelihood_comb(float mthad, float mtlep, float mwhad, float mhiggs){
  float llh=1;
  llh*=TopHadLikelihood_comb(mthad);
  llh*=TopLepLikelihood_comb(mtlep);
  llh*=WHadLikelihood_comb(mwhad);
  llh*=HiggsLikelihood_comb(mhiggs);
  return llh;
}
float ReconstructionQuality::TTWBBLikelihood_comb(float mthad, float mtlep, float mwhad, float mhiggs){
  float llh=1;
  llh*=TopHadLikelihood_comb(mthad);
  llh*=TopLepLikelihood_comb(mtlep);
  llh*=WHadLikelihood_comb(mwhad);
  llh*=BBLikelihood_comb(mhiggs);
  return llh;
}
float ReconstructionQuality::TTWLikelihood_comb(float mthad, float mtlep, float mwhad){
  float llh=1;
  llh*=TopHadLikelihood_comb(mthad);
  llh*=TopLepLikelihood_comb(mtlep);
  llh*=WHadLikelihood_comb(mwhad);
  return llh;
}
float ReconstructionQuality::TTWHLikelihood_comb(Interpretation& i){
  if(i.HasTag("TTWHLikelihood_comb")) return i.GetTag("TTWHLikelihood_comb");
  float tag=TTWHLikelihood_comb(i.TopHad_M(),i.TopLep_M(),i.WHad_M(),i.Higgs_M());
  i.SetTag("TTWHLikelihood_comb",tag);
  return tag;
}
float ReconstructionQuality::TTWBBLikelihood_comb(Interpretation& i){
  if(i.HasTag("TTWBBLikelihood_comb")) return i.GetTag("TTWBBLikelihood_comb");
  float tag=TTWBBLikelihood_comb(i.TopHad_M(),i.TopLep_M(),i.WHad_M(),i.Higgs_M());
  i.SetTag("TTWBBLikelihood_comb",tag);
  return tag;
}

float ReconstructionQuality::TTWLikelihood_comb(Interpretation& i){
  if(i.HasTag("TTWLikelihood_comb")) return i.GetTag("TTWLikelihood_comb");
  float tag=TTWLikelihood_comb(i.TopHad_M(),i.TopLep_M(),i.WHad_M());
  i.SetTag("TTWLikelihood_comb",tag);
  return tag;
}


float ReconstructionQuality::TTWHishLikelihood(float mthad, float mtlep, float mwhad, float mhiggs){
  float llh=1;
  llh*=TopHadishLikelihood(mthad);
  llh*=TopLepishLikelihood(mtlep);
  llh*=WHadishLikelihood(mwhad);
  llh*=HiggsishLikelihood(mhiggs);
  return llh;
}

float ReconstructionQuality::TTWishLikelihood(float mthad, float mtlep, float mwhad){
  float llh=1;
  llh*=TopHadishLikelihood(mthad);
  llh*=TopLepishLikelihood(mtlep);
  llh*=WHadishLikelihood(mwhad);
  return llh;
}

float ReconstructionQuality::TTWHChi2(Interpretation& i){
  if(i.HasTag("TTWHChi2")) return i.GetTag("TTWHChi2");
  float tag=TTWHChi2(i.TopHad_M(),i.TopLep_M(),i.WHad_M(),i.Higgs_M());
  i.SetTag("TTWHChi2",tag);
  return tag;
}
float ReconstructionQuality::TTWBBChi2(Interpretation& i){
  if(i.HasTag("TTWBBChi2")) return i.GetTag("TTWBBChi2");
  float tag=TTWBBChi2(i.TopHad_M(),i.TopLep_M(),i.WHad_M(),i.Higgs_M());
  i.SetTag("TTWBBChi2",tag);
  return tag;
}

float ReconstructionQuality::TTWChi2(Interpretation& i){
  if(i.HasTag("TTWChi2")) return i.GetTag("TTWChi2");
  float tag=TTWChi2(i.TopHad_M(),i.TopLep_M(),i.WHad_M());
  i.SetTag("TTWChi2",tag);
  return tag;
}


float ReconstructionQuality::TTWHishLikelihood(Interpretation& i){
  if(i.HasTag("TTWHishLikelihood")) return i.GetTag("TTWHishLikelihood");
  float tag=TTWHishLikelihood(i.TopHad_M(),i.TopLep_M(),i.WHad_M(),i.Higgs_M());
  i.SetTag("TTWHishLikelihood",tag);
  return tag;
}
float ReconstructionQuality::TTWishLikelihood(Interpretation& i){
  if(i.HasTag("TTWishLikelihood")) return i.GetTag("TTWishLikelihood");
  float tag=TTWishLikelihood(i.TopHad_M(),i.TopLep_M(),i.WHad_M());
  i.SetTag("TTWishLikelihood",tag);
  return tag;
}

float ReconstructionQuality::TTH_ME(Interpretation& i){
  if(i.HasTag("TTH_ME")) return i.GetTag("TTH_ME");
  float tag=1e4*me.GetTTHMEsq(i.TopHad(),i.TopLep(),i.Higgs());
  i.SetTag("TTH_ME",tag);
  return tag;
}

float ReconstructionQuality::TTBB_ON_ME(Interpretation& i){
  if(i.HasTag("TTBB_ON_ME")) return i.GetTag("TTBB_ON_ME");
  float tag=1e4*me.GetTTBBMEsq_onshell(i.TopHad(),i.TopLep(),i.B1(),i.B2());
  i.SetTag("TTBB_ON_ME",tag);
  return tag;
}
float ReconstructionQuality::TTBB_OFF_ME(Interpretation& i){
  if(i.HasTag("TTBB_OFF_ME")) return i.GetTag("TTBB_OFF_ME");
  float tag=1e4*me.GetTTBBMEsq_offshell(i.TopHad(),i.TopLep(),i.B1(),i.B2());
  i.SetTag("TTBB_OFF_ME",tag);
  return tag;
}


float ReconstructionQuality::TTHBB_ME(Interpretation& i){
  if(i.HasTag("TTHBB_ME")) return i.GetTag("TTHBB_ME");
  float tag=me.GetTTHBBMEsq(i.TopHad(),i.TopLep(),i.B1(),i.B2());
  i.SetTag("TTHBB_ME",tag);
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
float ReconstructionQuality::TopHadishLikelihood(float m){
  float llh=Interpolate(h_M_TopHad_best, m);
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

float ReconstructionQuality::TopLepishLikelihood(float m){
  float llh=Interpolate(h_M_TopLep_best, m);
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

float ReconstructionQuality::WHadishLikelihood(float m){
  float llh= Interpolate(h_M_WHad_best,m);
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

float ReconstructionQuality::HiggsishLikelihood(float m){
  float llh= Interpolate(h_M_Higgs_best,m);
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

float ReconstructionQuality::NBLikelihood(uint ntagged, uint njets, float* csvs){
  if(njets<ntagged) return 0;
  double llh=0.; // total likelihood
  uint binary=pow(2,ntagged)-1; //e.g.2^4-1=15=00001111, only last 4 tagged
  uint lastcomb=binary*pow(2,(njets-ntagged)); //e.g. 11110000, only first 4 tagged
  while(binary<=lastcomb){
    double l=1; //likelihood of current combination
    uint b=binary; //used to copute nth digit in binary
    for(uint ijet=0; ijet<njets;ijet++){
      if(b%2==1){
	l*=BLikelihood(csvs[ijet]);
      }
      else{
	l*=LLikelihood(csvs[ijet]);
      }
      b=b/2;
    }
    llh+=l;
    // get next permutation: 00001111 -> 00010111
    uint t = (binary | (binary - 1)) + 1;  
      binary = t | ((((t & -t) / (binary & -binary)) >> 1) - 1);  
      
  }   
  return llh;
}
