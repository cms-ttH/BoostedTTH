/** Processor for ttbb studies
 *
 * @author Marco A. Harrendorf
 */

#ifndef BOOSTEDTTH_BOOSTEDANALYZER_TTBBSTUDIENPROCESSOR_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_TTBBSTUDIENPROCESSOR_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/TreeProcessor.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"

class TTBBStudienProcessor: public TreeProcessor{

public:

  // all configurations should be done in constructor
  TTBBStudienProcessor();
  ~TTBBStudienProcessor();

  // you have to implement this to functions, you can add additionional (private) functions
  void Init(const InputCollections& input,VariableContainer& vars);
  void Process(const InputCollections& input,VariableContainer& vars);

  // Sub functions for specific quantities
  /**
   * @brief Init function for constructing DR between top quantities
   * @param input
   * @param var
   * Inspired by StdTopVarProcessor
   */
  void initTopDR(const InputCollections& input, VariableContainer& vars);
  /**
   * @brief Process function for constructing DR between top quantities
   * @param input
   * @param var
   */
  void processTopDR(const InputCollections& input,VariableContainer& vars);


  /**
   * @brief Init function for determining event type
   * @param input
   * @param var
   * Inspired by MCMatchVarProcessor
   */
  void initEventType(const InputCollections& input, VariableContainer& vars);
  /**
   * @brief Process function for determining event type
   * @param input
   * @param var
   */
  void processEventType(const InputCollections& input,VariableContainer& vars);


  /**
   * @brief Init function for determining amount of good and bad tags
   * @param input
   * @param var
   * Inspired by MCMatchVarProcessor
   */
  void initAmountTags(const InputCollections& input, VariableContainer& vars);
  /**
   * @brief Process function for determining amount of good and bad tags
   * @param input
   * @param var
   */
  void processAmountTags(const InputCollections& input,VariableContainer& vars);

private:
  // add all members needed, initialize in constructor

};

#endif
