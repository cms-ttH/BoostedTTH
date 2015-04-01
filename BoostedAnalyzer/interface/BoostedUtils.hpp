#ifndef BOOSTEDTTH_BOOSTEDANALYZER_BOOSTEDUTILS_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_BOOSTEDUTILS_HPP

#include <vector>

#include "TMath.h"
#include "TVector.h"
#include "TLorentzVector.h"

#include "Math/VectorUtil.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"

#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "BoostedTTH/BoostedObjects/interface/SubFilterJet.h"
#include "BoostedTTH/BoostedObjects/interface/HEPTopJet.h"

class BoostedUtils{
  
  public:
    
    static std::string GetAnalyzerPath();
    
    static TLorentzVector GetTLorentzVector(const math::XYZTLorentzVector& vec);
    static math::XYZTLorentzVector GetXYZTLorentzVector(const TLorentzVector& vec);
    
    static bool FirstIsLarger(float val1,float val2);
    static bool FirstIsHarder(math::XYZTLorentzVector vec1,math::XYZTLorentzVector vec2);
    static bool FirstHasHigherCSV(pat::Jet jet1,pat::Jet jet2);
    static bool FirstHasHigherCSVold(pat::Jet jet1,pat::Jet jet2);
    static bool FirstJetIsHarder(pat::Jet jet1, pat::Jet jet2);
    template<typename boostedJetType>
    static bool FirstFatJetIsHarder(boostedJetType jet1, boostedJetType jet2){
      return BoostedUtils::FirstJetIsHarder(jet1.fatjet,jet2.fatjet);
    }
    
    static float DeltaEta(const math::XYZTLorentzVector& vec1,const math::XYZTLorentzVector& vec2);
    static float DeltaEta(const pat::Jet& jet1,const pat::Jet& jet2);
    static float DeltaPhi(const math::XYZTLorentzVector& vec1,const math::XYZTLorentzVector& vec2);
    static float DeltaPhi(const pat::Jet& jet1,const pat::Jet& jet2);
    static float DeltaR(const math::XYZTLorentzVector& vec1,const math::XYZTLorentzVector& vec2);
    static float DeltaR(const pat::Jet& jet1,const pat::Jet& jet2);
    static float DeltaKt(const math::XYZTLorentzVector& vec1,const math::XYZTLorentzVector& vec2);
    static float DeltaKt(const pat::Jet& jet1,const pat::Jet& jet2);
    
    static float CosThetaStar(const math::XYZTLorentzVector& vec1, const math::XYZTLorentzVector& vec2);
    static float CosThetaCM(const math::XYZTLorentzVector& vec,const math::XYZTLorentzVector& boostVec);
    
    static std::vector<math::XYZTLorentzVector> GetGenParticleVecs(const std::vector<reco::GenParticle>& genParticles);
    static bool MCContainsTTbar(const std::vector<reco::GenParticle>& genParticles);
    static bool MCContainsHiggs(const std::vector<reco::GenParticle>& genParticles);
    static void GetttHMCParticles(const std::vector<reco::GenParticle>& genParticles, std::vector<reco::GenParticle>& tophad, std::vector<reco::GenParticle>& whad, std::vector<reco::GenParticle>& bhad, std::vector<reco::GenParticle>& q1, std::vector<reco::GenParticle>& q2, std::vector<reco::GenParticle>& toplep, std::vector<reco::GenParticle>& wlep, std::vector<reco::GenParticle>& blep, std::vector<reco::GenParticle>& lep, std::vector<reco::GenParticle>& nu, reco::GenParticle& higgs, reco::GenParticle& b1, reco::GenParticle& b2);
    static void GetttHMCVecs(const std::vector<reco::GenParticle>& genParticles, std::vector<math::XYZTLorentzVector>& tophadvecs, std::vector<math::XYZTLorentzVector>& whadvecs, std::vector<math::XYZTLorentzVector>& bhadvecs, std::vector<math::XYZTLorentzVector>& q1vecs, std::vector<math::XYZTLorentzVector>& q2vecs, std::vector<math::XYZTLorentzVector>& toplepvecs, std::vector<math::XYZTLorentzVector>& wlepvecs, std::vector<math::XYZTLorentzVector>& blepvecs, std::vector<math::XYZTLorentzVector>& lepvecs, std::vector<math::XYZTLorentzVector>& nuvecs, math::XYZTLorentzVector& higgsvec, math::XYZTLorentzVector& b1vec, math::XYZTLorentzVector& b2vec);
    
    static bool IsAnyTriggerBitFired(const std::vector<std::string>& targetTriggers, const edm::TriggerResults& triggerResults);
    
    static std::vector<math::XYZTLorentzVector> GetLepVecs(const std::vector<pat::Electron>& selectedElectrons, const std::vector<pat::Muon> selectedMuons);
    static math::XYZTLorentzVector GetPrimLepVec(const std::vector<pat::Electron>& selectedElectrons, const std::vector<pat::Muon> selectedMuons);
    
    static void GetNuVecs(const math::XYZTLorentzVector& lepvec, const TVector2& metvec, math::XYZTLorentzVector& nu1, math::XYZTLorentzVector& nu2);
    
    static std::vector<math::XYZTLorentzVector> GetJetVecs(const std::vector<pat::Jet>& jets);
    
    static boosted::SubFilterJetCollection GetSortedByPt(boosted::SubFilterJetCollection const &subfilterjets);
    static boosted::HEPTopJetCollection GetSortedByPt(boosted::HEPTopJetCollection const &heptopjets);
    
    static bool PassesCSV(const pat::Jet& jet, const char workingPoint);
    
    static float GetClosestJetIDs(int& idJet1, int& idJet2, const std::vector<pat::Jet>& jets);
    static float GetClosestLepJetID(int& idJet, const math::XYZTLorentzVector& lepVec, const std::vector<pat::Jet>& jets);
    
    static float GetJetAverageJetEtaMax(const std::vector<pat::Jet>& jets1, const std::vector<pat::Jet>& jets2);
    
    static void GetFoxWolframMoments(std::vector<math::XYZTLorentzVector> jetVecs, float &h0, float &h1, float &h2, float &h3, float &h4);
    static void GetAplanaritySphericity(math::XYZTLorentzVector leptonVec, math::XYZTLorentzVector metVec, std::vector<math::XYZTLorentzVector> jetVecs, float &aplanarity, float &sphericity);
    
    static bool GetTopTag(const boosted::HEPTopJet& topJet,const double& fW = 0.15, const double& mTopMin = 120, const bool& altConf = false);
    static void TopSubjetCSVDef(std::vector<pat::Jet> &subjets);
    
    static std::vector<pat::Jet> GetHiggsFilterJets(const boosted::SubFilterJet& higgsJet, const int& nCSVJets = 2);
    static std::vector<pat::Jet> GetHiggsFilterJets(const std::vector<pat::Jet>& higgsDecayJets, const int& nCSVJets = 2);
    static float GetHiggsMass(const boosted::SubFilterJet& higgsJet, const int& nFilterJets = 2, const int& nBTags = 2, const float& csvWP = 0.679);
    
    static double GetBestHiggsMassOhio(math::XYZTLorentzVector lepton, math::XYZTLorentzVector met, std::vector<math::XYZTLorentzVector> jets, std::vector<double> btag, double &minChi, double &dRbb, math::XYZTLorentzVector &bjet1, math::XYZTLorentzVector &bjet2, std::vector<math::XYZTLorentzVector> loose_jets, std::vector<double> loose_btag);
    static float GetBestHiggsMassOhio2(math::XYZTLorentzVector lepton, math::XYZTLorentzVector &met, std::vector<math::XYZTLorentzVector> jets, std::vector<double> btag, double &minChi, double &dRbb, math::XYZTLorentzVector &bjet1, math::XYZTLorentzVector &bjet2, double &chi2lepW, double &chi2leptop, double &chi2hadW, double &chi2hadtop, double &mass_lepW, double &mass_leptop, double &mass_hadW, double &mass_hadtop, math::XYZTLorentzVector &toplep, math::XYZTLorentzVector &tophad);
    static double StudyTopsBBSystOhio(math::XYZTLorentzVector &metv, std::vector<double> lep, std::vector< std::vector<double> > jets, std::vector<double> csv, double &minChi, double &chi2lepW, double &chi2leptop, double &chi2hadW, double &chi2hadtop, double &mass_lepW, double &mass_leptop, double &mass_hadW, double &mass_hadtop, double &dRbb, double &testquant1, double &testquant2, double &testquant3, double &testquant4, double &testquant5, double &testquant6, double &testquant7, math::XYZTLorentzVector &b1, math::XYZTLorentzVector &b2);
    static void TTHRecoVarsOhio(const std::vector<pat::Jet>& selectedJets,const std::vector<pat::Jet>& selectedJetsLoose, const pat::MET& pfMET, const math::XYZTLorentzVector& lepton, float& higgsMass_, float& dRbb_,float& dEtaHadTopbb_,float& dEtaLeptopbb_, float& dEtaFN_);
  
  
  template <typename T, typename S> static std::vector<T> RemoveOverlaps( const std::vector<S>&, const std::vector<T>& );
  template <typename T, typename S> static T RemoveOverlap( const std::vector<S>&, const T& );
  
  private:
  
};


template <typename PATObj1, typename PATObj2> 
PATObj1 BoostedUtils::RemoveOverlap( const std::vector<PATObj2>& other, const PATObj1& unclean ){

  unsigned int nSources1 = unclean.numberOfSourceCandidatePtrs();
  bool hasOverlaps = false;

  std::vector<reco::CandidatePtr> overlaps;

  for( typename std::vector<PATObj2>::const_iterator iobj2 = other.begin(); iobj2!=other.end(); ++iobj2 ){

    unsigned int nSources2 = iobj2->numberOfSourceCandidatePtrs();

    for( unsigned int i1=0; i1<nSources1; i1++ ){
      reco::CandidatePtr source1 = unclean.sourceCandidatePtr(i1);

      if( !(source1.isNonnull() && source1.isAvailable()) ) continue;

      for( unsigned int i2=0; i2<nSources2; i2++ ){
	reco::CandidatePtr source2 = iobj2->sourceCandidatePtr(i2);

	if( !(source2.isNonnull() && source2.isAvailable()) ) continue;

	if( source1==source2 ){
	  hasOverlaps = true;
	  overlaps.push_back(source2);
	}
      }

    }
  }// end loop over iobj22


  PATObj1 cleaned = unclean;
  if( hasOverlaps ){
    math::XYZTLorentzVector original = cleaned.p4();

    for( int iOverlap=0; iOverlap<int(overlaps.size()); iOverlap++ ){

      const reco::Candidate & cOverlap = *(overlaps[iOverlap]);
      math::XYZTLorentzVector overlaper = cOverlap.p4();

      original -= overlaper;
    }

    cleaned.setP4( original );
  }

  return cleaned;
}


template <typename PATObj1, typename PATObj2> 
std::vector<PATObj1> BoostedUtils::RemoveOverlaps( const std::vector<PATObj2>& other, const std::vector<PATObj1>& unclean ){

  std::vector<PATObj1> cleaned;
  
  for( typename std::vector<PATObj1>::const_iterator iobj1 = unclean.begin(); iobj1!=unclean.end(); ++iobj1 ){

    PATObj1 myobj = (*iobj1);
    PATObj1 clean = RemoveOverlap(other, myobj);

    cleaned.push_back(clean);
  }

  return cleaned;
}
    



/*
#include "BEAN/Collections/interface/BNjet.h"
#include "BEAN/Collections/interface/BNelectron.h"
#include "BEAN/Collections/interface/BNevent.h"
#include "BEAN/Collections/interface/BNmcparticle.h"
#include "BEAN/Collections/interface/BNmet.h"
#include "BEAN/Collections/interface/BNmuon.h"
#include "BEAN/Collections/interface/BNphoton.h"
#include "BEAN/Collections/interface/BNsupercluster.h"
#include "BEAN/Collections/interface/BNtrack.h"
#include "BEAN/Collections/interface/BNtrigger.h"
#include "BEAN/Collections/interface/BNskimbits.h"
#include "BEAN/Collections/interface/BNtrigobj.h"
#include "BEAN/Collections/interface/BNprimaryvertex.h"
#include "BEAN/Collections/interface/BNsubfilterjet.h"
#include "BEAN/Collections/interface/BNtoptagjet.h"
#include "BEAN/Collections/interface/BNleptonCollection.h"

#include "BEAN/BEANmaker/interface/BEANhelper.h"
#include "BEAN/BEANmaker/interface/AnglesUtil.h"

#include "boost/lexical_cast.hpp"
#include "TFile.h"
#include "TTree.h"
#include "TStopwatch.h"
#include <map>

typedef std::vector<std::vector<double> > vvdouble;
typedef std::vector<std::vector<std::string> > vvstring;
typedef std::vector<double> vdouble;
typedef std::vector<string> vstring;
typedef std::vector<bool> vbool;
typedef std::vector<int> vint;
typedef std::vector< TLorentzVector > vecTLorentzVector;

using namespace std;

enum SampleType{data,tth,ttl,ttbb,ttb,ttcc,nonttbkg};

class BEANUtils{
public:
  static bool IsAnyTriggerBitFired ( const std::vector<string> & targetTriggers, const BNtriggerCollection &  triggerBits);
  static bool PassesCSV(const BNjet& jet, const char workingPoint);
  static void GetSp(TLorentzVector lepton, TLorentzVector met, vecTLorentzVector jets, float &aplanarity, float &sphericity);
  static void GetFox(vecTLorentzVector jets, float &h0, float &h1, float &h2, float &h3, float &h4);
  static bool FirstFatJetIsHarder( BNsubfilterjet jet1, BNsubfilterjet jet2);
  static bool FirstTopJetIsHarder( BNtoptagjet jet1, BNtoptagjet jet2);
  static void TopSubjetCSVDef(vector<BNjet> &subjets);
  static bool GetTopTag(const BNtoptagjet& top_jet);
  static bool GetTopTagB(const BNtoptagjet& top_jet);
  static bool FirstHasHigherCSV(BNjet j1,BNjet j2);
  static float GetClosestJetIndices(int&i,int&j,BNjetCollection jets);
  static std::vector<BNjet> GetJetsByDr(TLorentzVector vec,const std::vector<BNjet>& jets);
  static TLorentzVector GetPrimLepVec(BNelectronCollection selectedElectrons, BNmuonCollection selectedMuons);
  static std::vector<TLorentzVector> GetJetVecs(BNjetCollection selectedJets);
  static TLorentzVector GetJetVec(BNjet jet);
  static TLorentzVector GetMCVec(BNmcparticle p);
  static float CosThetaStar(const TLorentzVector & v1, const TLorentzVector & v2); 
  static float DeltaEta(const TLorentzVector & v1, const TLorentzVector & v2); 
  static float DeltaPhi(const TLorentzVector & v1, const TLorentzVector & v2); 
  static float DeltaR(const TLorentzVector & v1, const TLorentzVector & v2); 
  static float CosThetaCM(const TLorentzVector& v,const TLorentzVector& b);
  static float DeltaR(const BNjet& j1,const BNjet& j2);
  static float DeltaKt(const TLorentzVector & v1, const TLorentzVector & v2); 
  static void GetHiggsJetDistanceVars(const BNsubfilterjet& jet,const std::vector<BNtoptagjet>& topjets,float& deltaR1_,float& deltaR2_,float& deltaR3_,float& deltaR4_);
  static void GetFilterJetVars(const BNsubfilterjet& jet,TLorentzVector& vec1_,TLorentzVector& vec2_,TLorentzVector& vec3_,TLorentzVector& vec4_,float& csvfj1_,float& csvfj2_,float& csvfj3_,float& csvfj4_);
  static void GetHiggsJetCSVVars(const BNsubfilterjet& jet,float& csv1_,float& csv2_,float& csv3_,float& csv4_);
  static void GetHiggsJetCSVVarsDr(const BNsubfilterjet& jet,BNjet& csv1_fjet_,BNjet& csv2_fjet_);
  static void GetHiggsJetCSVVarsDr(const BNjetCollection& filterjets,BNjet& b1_fjet_,BNjet& b2_fjet_,BNjet& g_fjet_);
  static float GetHiggsMass(const BNsubfilterjet& higgs_jet, const int n_filterjets=2, const bool hardest_jets=false, const int n_btags=0, const float csv_wp=0.679);
  static void GetNuVecs(const TLorentzVector & lepvec, const TVector2 & metvec, TLorentzVector & nu1, TLorentzVector & nu2);
  static BNjet GetTopLepBjet(const BNsubfilterjet& sfjet,const BNtoptagjet& topjet, const std::vector<BNjet>& ak5jets);
  static TLorentzVector GetTopLepVec(const TLorentzVector & lepvec, const TLorentzVector & nu1, const TLorentzVector & nu2, const BNjet & bjet);
  static void GetSemiLeptMCVecs(const BNmcparticleCollection& mcparticlesStatus3,TLorentzVector& bhad_mc,TLorentzVector& q1_mc,TLorentzVector& q2_mc,TLorentzVector& blep_mc,TLorentzVector& lep_mc,TLorentzVector& nu_mc,TLorentzVector& b1_mc,TLorentzVector& b2_mc);

  static bool GetSelected_HiggsJets(const BNsubfilterjetCollection& subfilterjets, BNsubfilterjetCollection& selected_higgsjets, BNtoptagjet& topHadCand, BNsubfilterjet& higgsCand, bool check_subjet_overlap);
  static void GetttHMCVecs(const BNmcparticleCollection& mcparticlesStatus3,vector<TLorentzVector>& bhadvec,vector<TLorentzVector>& q1vec,vector<TLorentzVector>& q2vec,vector<TLorentzVector>& blepvec,vector<TLorentzVector>& lepvec,vector<TLorentzVector>& nuvec,TLorentzVector& b1vec,TLorentzVector& b2vec);
  static float GetJetAverageJetEtaMax(const BNjetCollection& selectedJets,const BNjetCollection& subset);
  static double GetBestHiggsMassOhio(TLorentzVector lepton, TLorentzVector met, vecTLorentzVector jets, vdouble btag, double &minChi, double &dRbb, TLorentzVector &bjet1, TLorentzVector &bjet2, vecTLorentzVector loose_jets, vdouble loose_btag);
  static double StudyTopsBBSystOhio(double MET, double METphi, TLorentzVector &metv, vdouble lep, vvdouble jets, vdouble csv, double &minChi, double &chi2lepW, double &chi2leptop, double &chi2hadW, double &chi2hadtop, double &mass_lepW, double &mass_leptop, double &mass_hadW, double &mass_hadtop, double &dRbb, double &testquant1, double &testquant2, double &testquant3, double &testquant4, double &testquant5, double &testquant6, double &testquant7, TLorentzVector &b1, TLorentzVector &b2);
  static void TTHRecoVarsOhio(const BNjetCollection& selectedJets,const BNjetCollection& selectedJets_loose, const BNmet& correctedMET, const TLorentzVector& lepton, float& best_higgs_mass_, float& dRbb_,float& abs_dEta_hadtop_bb_,float& abs_dEta_leptop_bb_, float& dEta_fn_);
  static float GetBestHiggsMassOhio2(TLorentzVector lepton, TLorentzVector &met, vecTLorentzVector jets, vdouble btag, double &minChi, double &dRbb, TLorentzVector &bjet1, TLorentzVector &bjet2, double &chi2lepW, double &chi2leptop, double &chi2hadW, double &chi2hadtop, double &mass_lepW, double &mass_leptop, double &mass_hadW, double &mass_hadtop, TLorentzVector &toplep, TLorentzVector &tophad);
  static std::string GetDataPath();
  static std::vector<string> ParseFileNames(string fnames);

private:
};

struct closerToVec {
  TLorentzVector vec;
  bool operator() (BNjet j1,BNjet j2) { return (vec.DeltaR(BEANUtils::GetJetVec(j1))<vec.DeltaR(BEANUtils::GetJetVec(j2)));}
} ;
*/

#endif
