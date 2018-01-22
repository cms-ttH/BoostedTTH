#ifndef PHOTONVETOSELECTION_HPP
#define PHOTONVETOSELECTION_HPP

#include <vector>

#include "BoostedTTH/BoostedAnalyzer/interface/Selection.hpp"

class PhotonVetoSelection: public Selection{
  
  public:
    
    PhotonVetoSelection();
    ~PhotonVetoSelection();
    void InitCutflow(Cutflow& cutflow);
    bool IsSelected(const InputCollections& input,Cutflow& cutflow);


  private:

};

#endif