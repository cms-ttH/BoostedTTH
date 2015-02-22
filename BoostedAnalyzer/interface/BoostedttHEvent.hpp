#ifndef BOOSTEDTTH_BOOSTEDANALYZER_BOOSTEDTTHEVENT_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_BOOSTEDTTHEVENT_HPP

#include "BoostedTTH/BoostedObjects/interface/Event.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "BoostedTTH/BoostedObjects/interface/SubFilterJet.h"
#include "BoostedTTH/BoostedObjects/interface/HEPTopJet.h"

#include "BoostedTTH/BoostedAnalyzer/interface/InputCollections.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TopTagger.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/HiggsTagger.hpp"

class BoostedttHEvent{
  
  public:
    
    // Constructor & Destructor
    BoostedttHEvent(const InputCollections& input);
    ~BoostedttHEvent();
    
    // Manage Event
    void ResetEvent();
    
    // Reconstruction Functions
    
    // Charged Lepton Reconstruction
    void LeptonRec();
    
    // Neutrino Reconstruction
    void NeutrinoRec();
    
    // Anti-kt 5 Jets Reconstruction
    void ak5JetsRec();
    void ak5JetsIdentifyHiggsCand(const float jetMatchingThreshold = .3);
    void ak5JetsIdentifyTopHadCand(const float jetMatchingThreshold = .3);
    void ak5JetsIdentifyTopLepCand(const float jetMatchingThreshold = .3);
    void ak5JetsClean(bool cleanHiggsCand = false, bool cleanTopHadCand = false, bool cleanTopLepCand = false);    
    
    // Higgs Candidate Reconstruction
    void HiggsCandBoostedRec(HiggsTagger* higgstagger, const float higgsjetptcut = 200., const float higgsjetetacut = 2., bool cleanTopHadCand = false, bool cleanTopLepCand = false,  const float fatjetCleaningThreshold = 1.5, const float subjetCleaningThreshold = .4);
    void HiggsCandRec();
    
    // Hadronic Top Candidate Reconstruction
    void TopHadCandBoostedRec(TopTagger toptagger, const float topjetptcut = 200., const float topjetetacut = 2.);
    void TopHadCandRec();
    
    // Leptonic Top Candidate Reconstruction
    void TopLepCandRec();
    
    // Top Pair Candidate Reconstruction
    void TopPairCandRec();
    
    // Event Reconstruction
    void BoostedTopHiggsEventRec(TopTagger toptagger, HiggsTagger* higgstagger);
    void BoostedHiggsEventRec(HiggsTagger* higgstagger);
    void BoostedTopEventRec(TopTagger toptagger);
    
    // Get Functions
    // Input Collection
    const InputCollections& GetInput();
    
    // Charged Lepton Reconstruction
    math::XYZTLorentzVector  GetLeptonVec();
    
    // Neutrino Reconstruction
    math::XYZTLorentzVector  GetNeutrinoVec();
    math::XYZTLorentzVector  GetNeutrino1Vec();
    math::XYZTLorentzVector  GetNeutrino2Vec();
    
    // Anti-kt 5 Jets
    pat::JetCollection Getak5JetsAll();
    int             GetNJets();
    int             GetNBTagL();
    int             GetNBTagM();
    int             GetNBTagT();
    float           GetAverageCSV();
    
    int             GetNHiggsak5Jets();
    int             GetNHiggsCandBTagL();
    int             GetNHiggsCandBTagM();
    int             GetNHiggsCandBTagT();
    float           GetAverageCSVHiggsCand();
    
    int             GetNTopHadak5Jets();
    int             GetNTopHadCandBTagL();
    int             GetNTopHadCandBTagM();
    int             GetNTopHadCandBTagT();
    float           GetAverageCSVTopHadCand();
    
    int             GetNTopLepak5Jets();
    int             GetNTopLepCandBTagL();
    int             GetNTopLepCandBTagM();
    int             GetNTopLepCandBTagT();
    float           GetAverageCSVTopLepCand();
    
    pat::JetCollection Getak5JetsCleaned();
    int             GetNCleanedak5Jets();
    int             GetNCleanedBTagL();
    int             GetNCleanedBTagM();
    int             GetNCleanedBTagT();
    float           GetAverageCSVClean();
    
    // Higgs Candidate
    boosted::SubFilterJet  GetHiggsCandBoosted();
    pat::Jet           GetHiggsB1Cand();
    pat::Jet           GetHiggsB2Cand();
    pat::Jet           GetHiggsGCand();
    math::XYZTLorentzVector  GetHiggsCandVec3();
    math::XYZTLorentzVector  GetHiggsCandVec2();   
    
    // Hadronic Top Candidate
    boosted::HEPTopJet     GetTopHadCandBoosted();
    pat::Jet           GetTopHadBCand();
    pat::Jet           GetTopHadW1Cand();
    pat::Jet           GetTopHadW2Cand();
    math::XYZTLorentzVector  GetTopHadCandVec();
    math::XYZTLorentzVector  GetWHadCandVec();
    
    // Leptonic Top Candidate
    pat::Jet           GetTopLepBCand();
    math::XYZTLorentzVector  GetTopLepCandVec();
    math::XYZTLorentzVector  GetWLepCandVec();
    
    bool            GetFoundTopHad();
    float           GetHiggsTag();
    
  private:
    
    // Inhput Collection
    const InputCollections& input;
    
    // Analysis Settings
    
    // Charged Lepton
    math::XYZTLorentzVector lepVecCand;
    
    // Neutrino
    math::XYZTLorentzVector nuVecCand;
    math::XYZTLorentzVector nu1VecCand;
    math::XYZTLorentzVector nu2VecCand;
    
    // Anti-kt 5 Jets
    pat::JetCollection selectedJets;
    std::vector<bool> BTagL;
    std::vector<bool> BTagM;
    std::vector<bool> BTagT;
    int nJets;
    int nBTagL;
    int nBTagM;
    int nBTagT;
    
    std::vector<bool> HiggsCandak5Jet;
    int nHiggsak5Jets;
    int nHiggsCandBTagL;
    int nHiggsCandBTagM;
    int nHiggsCandBTagT;
    
    std::vector<bool> TopHadCandak5Jet;
    int nTopHadak5Jets;
    int nTopHadCandBTagL;
    int nTopHadCandBTagM;
    int nTopHadCandBTagT;
    
    std::vector<bool> TopLepCandak5Jet;
    int nTopLepak5Jets;
    int nTopLepCandBTagL;
    int nTopLepCandBTagM;
    int nTopLepCandBTagT;
    
    pat::JetCollection cleanedak5Jets;
    int nCleanedak5Jets;
    int nCleanedBTagL;
    int nCleanedBTagM;
    int nCleanedBTagT;
    
    // Higgs Candidate
    bool                  foundHiggsCand;
    float                 HiggsTag_HiggsCand;
    boosted::SubFilterJet higgsCand;
    pat::Jet              higgsB1Cand;
    pat::Jet              higgsB2Cand;
    pat::Jet              higgsGCand;
    
    // Hadronic Top Candidate
    bool                foundTopHadCand;
    boosted::HEPTopJet  topHadCand;
    pat::Jet            topHadBCand;
    pat::Jet            topHadW1Cand;
    pat::Jet            topHadW2Cand;
        
    // Leptonic Top Candidate
    bool foundTopLepCand;
    pat::Jet topLepBCand;      

    bool verbose;
    const char* btagger;
};

#endif
