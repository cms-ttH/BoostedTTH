#include "DataFormats/Common/interface/Wrapper.h"

//Add includes for your classes here
#include "BoostedTTH/BoostedObjects/interface/HEPTopJet.h"
#include "BoostedTTH/BoostedObjects/interface/HTTTopJet.h"
#include "BoostedTTH/BoostedObjects/interface/SubFilterJet.h"

#include <vector>

namespace {

  struct BEAN_Collections {

    //add 'dummy' Wrapper variable for each class type you put into the Event
   
    boosted::HEPTopJet heptopjetdummy0;
    edm::Wrapper<boosted::HEPTopJet> heptopjetdummy1;
    std::vector<boosted::HEPTopJet> heptopjetdummy2;
    edm::Wrapper<std::vector<boosted::HEPTopJet> > heptopjetdummy3;
    
    boosted::HTTTopJet htttopjetdummy0;
    edm::Wrapper<boosted::HTTTopJet> htttopjetdummy1;
    std::vector<boosted::HTTTopJet> htttopjetdummy2;
    edm::Wrapper<std::vector<boosted::HTTTopJet> > htttopjetdummy3;
    
    boosted::SubFilterJet subfilterjetdummy0;
    edm::Wrapper<boosted::SubFilterJet> subfilterjetdummy1;
    std::vector<boosted::SubFilterJet> subfilterjetdummy2;
    edm::Wrapper<std::vector<boosted::SubFilterJet> > subfilterjetdummy3;
  };
}
