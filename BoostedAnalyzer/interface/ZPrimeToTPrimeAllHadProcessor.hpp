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
private:
};

#endif
