#ifndef BOOSTEDTTH_BOOSTEDANALYZER_ZPRIMETOTPRIMEALLHADPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_ZPRIMETOTPRIMEALLHADPROCESSOR_HPP

#include <vector>


#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
/*class TreeProcessor{
public:
    TreeProcessor();
};
*/

class ZPrimeToTPrimeAllHadProcessor: public TreeProcessor{
  
public:
  
  ZPrimeToTPrimeAllHadProcessor();
  ~ZPrimeToTPrimeAllHadProcessor();
  
  void Init(const InputCollections& input,VariableContainer& var);
  void Process(const InputCollections& input,VariableContainer& var);
  
  void InitGenVars(VariableContainer& vars);
  void InitBasicRecoVars(VariableContainer& vars);
  void InitSignalandSidbandVars(VariableContainer& vars);
  void InitTaggingVars(VariableContainer& vars);
  void InitABCDVars(VariableContainer& vars);
  
  
  std::vector<pat::Jet> SelectSeparatedBottoms(std::vector<pat::Jet>& tops, std::vector<pat::Jet>& Ws, std::vector<pat::Jet>& bottoms); 
  math::XYZTLorentzVector TPrimeReconstructionWtb(const std::vector<pat::Jet>& Ws, const std::vector<pat::Jet>& bottoms);
  math::XYZTLorentzVector ZPrimeReconstructionWtb(const std::vector<pat::Jet>& tops,const math::XYZTLorentzVector& TPrime);  
  
private:

  
};

#endif
