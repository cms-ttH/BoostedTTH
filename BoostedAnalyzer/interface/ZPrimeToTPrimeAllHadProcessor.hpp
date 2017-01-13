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
  math::XYZTLorentzVector TPrimeReconstructionWtb( std::vector<pat::Jet>& Ws,  std::vector<pat::Jet>& bottoms);
  math::XYZTLorentzVector ZPrimeReconstructionWtb( std::vector<pat::Jet>& tops, math::XYZTLorentzVector& TPrime);
  std::vector<pat::Jet> SelectfromTopSeparatedWs( std::vector<pat::Jet>& tops, std::vector<pat::Jet>& Ws);
  std::vector<pat::Jet> SelectfromWSeparatedTops( std::vector<pat::Jet>& tops, std::vector<pat::Jet>& Ws);
  void ZPrimeReconstructionWtbComplete(VariableContainer& vars,  std::vector<pat::Jet>& tops, std::vector<pat::Jet>& Ws,  std::vector<pat::Jet>& bottoms, std::vector<pat::Jet>& bottoms_anti, bool toptag, bool toptag_withbtag,  bool Wtag, bool toptag_anti, bool toptag_withbtag_anti,  bool Wtag_anti, std::string str_AK8_selected_first);
  void FillSignalSidebandVars(VariableContainer& vars, std::vector<pat::Jet>& tops, std::vector<pat::Jet>& Ws,  std::vector<pat::Jet>& bottoms,  math::XYZTLorentzVector TPrime,  math::XYZTLorentzVector ZPrime,  bool toptag, bool toptag_withbtag,  bool Wtag, bool bottomtag, bool toptag_anti, bool toptag_withbtag_anti,  bool Wtag_anti, std::string str_AK8_selected_first="");
  void FillZprimeVars(VariableContainer& vars, std::vector<pat::Jet>& tops, std::vector<pat::Jet>& Ws,  std::vector<pat::Jet>& bottoms,  math::XYZTLorentzVector Tprime,  math::XYZTLorentzVector Zprime,std::string string);
  
private:

  
};

#endif
