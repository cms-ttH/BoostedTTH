#ifndef BOOSTEDTTH_BOOSTEDANALYZER_TTXRECONSTRUCTIONANDGENVARPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_TTXRECONSTRUCTIONANDGENVARPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"

#include "TTH/RecoLikelihoodReconstruction/interface/ReconstructionQuality.hpp"
#include "TTH/RecoLikelihoodReconstruction/interface/InterpretationGenerator.hpp"
#include "TTH/RecoLikelihoodReconstruction/interface/Interpretation.hpp"
#include "TLorentzVector.h"

#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"

class ttXReconstructionAndGenVarProcessor: public TreeProcessor {

public: 
    ttXReconstructionAndGenVarProcessor();
    ~ttXReconstructionAndGenVarProcessor();
    
    void Init(const InputCollections &input, VariableContainer &vars);
    void Process(const InputCollections &input, VariableContainer &vars);
    
    void InitSimpleKinematicVariables(const std::string &name, VariableContainer &vars);
    void FillSimpleKinematicVariables(const std::string &name, const reco::GenParticle &genParticle, const TLorentzVector &recoParticle, VariableContainer &vars);

    void InitAngularDifferences(const std::string &name1, const std::string &name2, VariableContainer &vars);
    void FillAngularDifferences(const std::string &name1, const std::string &name2, const reco::GenParticle &gen1, const reco::GenParticle &gen2, const TLorentzVector &reco1, const TLorentzVector &reco2, VariableContainer &vars);
    

    Interpretation *GetTTXInterpretation(const InputCollections &input);

private:
    std::string recoPrefix;
    std::string genPrefix;

    ReconstructionQuality quality;
    InterpretationGenerator generator;
};

#endif
