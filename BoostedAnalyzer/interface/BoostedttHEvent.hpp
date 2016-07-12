#ifndef BOOSTEDTTH_BOOSTEDANALYZER_BOOSTEDTTHEVENT_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_BOOSTEDTTHEVENT_HPP

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "MiniAOD/BoostedObjects/interface/BoostedJet.h"
#include "MiniAOD/MiniAODHelper/interface/TopTagger.h"
#include "MiniAOD/MiniAODHelper/interface/HiggsTagger.h"
#include "BoostedTTH/TTHReconstruction/interface/MECalculator.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/InputCollections.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"



class BoostedttHEvent{
  
  public:
    
    // Constructor & Destructor
    BoostedttHEvent();
    ~BoostedttHEvent();

    void SetInput(const InputCollections* input);
    
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
    void HiggsCandBoostedRec(HiggsTagger higgstagger, bool cleanTopHadCand = false, bool cleanTopLepCand = false, const float subjetCleaningThreshold = .4);
    void HiggsCandRec();
    
    // Hadronic Top Candidate Reconstruction
    void TopHadCandBoostedRec(TopTagger toptagger, bool cleanTopLepCand = false, bool cleanHiggsCand = false, const float subjetCleaningThreshold = .4);
    void TopHadCandRec();
    
    // Leptonic Top Candidate Reconstruction
    void TopLepCandRec();
    
    // Top Pair Candidate Reconstruction
    void TopPairCandRec();
    
    // Event Reconstruction
    void BoostedTopHiggsEventRec(TopTagger toptagger, HiggsTagger higgstagger);
    void BoostedHiggsEventRec(HiggsTagger higgstagger);
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
    bool                    GetFoundHiggsCand();
    int                     GetHiggsCandIndex();
    float                   GetHiggsCandTag();
    boosted::BoostedJet     GetHiggsCandBoosted();
    pat::Jet                GetHiggsB1Cand();
    pat::Jet                GetHiggsB2Cand();
    pat::Jet                GetHiggsGCand();
    math::XYZTLorentzVector GetHiggsCandVec3();
    math::XYZTLorentzVector GetHiggsCandVec2();   
    
    // Hadronic Top Candidate
    bool                    GetFoundTopHadCand();
    int                     GetTopHadCandIndex();
    float                   GetTopHadCandTag();
    boosted::BoostedJet     GetTopHadCandBoosted();
    pat::Jet                GetTopHadBCand();
    pat::Jet                GetTopHadW1Cand();
    pat::Jet                GetTopHadW2Cand();
    math::XYZTLorentzVector GetTopHadCandVec();
    math::XYZTLorentzVector GetWHadCandVec();
    
    // Leptonic Top Candidate
    bool                    GetFoundTopLepCand();
    pat::Jet                GetTopLepBCand();
    math::XYZTLorentzVector GetTopLepCandVec();
    math::XYZTLorentzVector GetWLepCandVec();

    // Matrix Element
    float                   GetTTHBB_ME();
    float                   GetTTBB_ME();
    float                   Get_MEratio();
    
  private:
    
    // Inhput Collection
    const InputCollections* input;
    
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
    bool                foundHiggsCand;
    int                 higgsCandIndex;
    float               higgsCandTag;
    boosted::BoostedJet higgsCand;
    pat::Jet            higgsB1Cand;
    pat::Jet            higgsB2Cand;
    pat::Jet            higgsGCand;
    
    // Hadronic Top Candidate
    bool                foundTopHadCand;
    int                 topHadCandIndex;
    float               topHadCandTag;
    boosted::BoostedJet topHadCand;
    pat::Jet            topHadBCand;
    pat::Jet            topHadW1Cand;
    pat::Jet            topHadW2Cand;
        
    // Leptonic Top Candidate
    bool foundTopLepCand;
    pat::Jet topLepBCand;      

    bool verbose;
    const char* btagger;
    MECalculator recoME;
                   
};

#endif
