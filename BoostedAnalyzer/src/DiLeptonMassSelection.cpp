#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonMassSelection.hpp"

using namespace std;

DiLeptonMassSelection::DiLeptonMassSelection(float minMass_,float maxMass_,bool invertCut_,bool cutForDifferentFlavors_):minMass(minMass_),maxMass(maxMass_),invertCut(invertCut_),cutForDifferentFlavors(cutForDifferentFlavors_)
{}

DiLeptonMassSelection::~DiLeptonMassSelection (){}

void DiLeptonMassSelection::InitCutflow(Cutflow& cutflow){
    if(cutForDifferentFlavors)selectionName="Any Flavor ";
    else selectionName="Same Flavor ";
    selectionName+="Dilepton mass ";
    if(invertCut) selectionName+="not ";
    selectionName+="between ";
    selectionName+=std::to_string(minMass);
    selectionName+=" and ";
    selectionName+=std::to_string(maxMass);
    cutflow.AddStep(selectionName);
    initialized=true;
}

bool DiLeptonMassSelection::IsSelected(const InputCollections& input,Cutflow& cutflow){
    if(!initialized) cerr << "DiLeptonMassSelection not initialized" << endl;
    
    /*
    if((input.selectedMuonsDL.size()+input.selectedElectronsDL.size())<2) {
      return false;
    }
    */
    
    float mumu_mass=-1;
    float elel_mass=-1;
    float elmu_mass=-1;
    
    bool leadingele = false;
    std::vector<math::XYZTLorentzVector> elevecs;
    
    if(input.selectedElectronsDL.size()>0){
      elevecs.push_back(input.selectedElectronsDL[0].p4());
      leadingele = true;
    }
    
    for(auto e=input.selectedElectronsLoose.begin();e!=input.selectedElectronsLoose.end();e++){

      if(leadingele){
        if(BoostedUtils::DeltaR(elevecs[0],e->p4())<0.001){
          continue;
        }
      }
      
      elevecs.push_back(e->p4());
    }
    
    bool leadingmu = false;
    std::vector<math::XYZTLorentzVector> muvecs;
    
    if(input.selectedMuonsDL.size()>0){
      muvecs.push_back(input.selectedMuonsDL[0].p4());
      leadingmu = true;
    }
    
    for(auto mu=input.selectedMuonsLoose.begin();mu!=input.selectedMuonsLoose.end();mu++){

      if(leadingmu){
        if(BoostedUtils::DeltaR(muvecs[0],mu->p4())<0.001){
          continue;
        }
      }
      
      muvecs.push_back(mu->p4());
    }
    
    if((elevecs.size()+muvecs.size())<2) {
      return false;
    }
    
    if(leadingele && elevecs.size()>=2){
      elel_mass=(elevecs[0]+elevecs[1]).M();
    }
    if(leadingmu && muvecs.size()>=2){
      mumu_mass=(muvecs[0]+muvecs[1]).M();
    }
    if((leadingele || leadingmu) && elevecs.size()>=1 && muvecs.size()>=1) {
      elmu_mass=(elevecs[0]+muvecs[0]).M();
      
      /*
      if(cutForDifferentFlavors){ 
        elmu_mass=(elevecs[0]+muvecs[0]).M();
      }
      else{
        cutflow.EventSurvivedStep(selectionName,input.weights.at("Weight"));
        return true;
      }
      */
    }
    
    //cout << "elel_mass: " << elel_mass << "   mumu_mass: " << mumu_mass  << "   elmu_mass: " << elmu_mass << endl;
    
    if(!invertCut){
      // both/all dilepton masses are outside of the window
      if( (elel_mass<minMass||elel_mass>maxMass) && (mumu_mass<minMass||mumu_mass>maxMass) && (cutForDifferentFlavors && (elmu_mass<minMass||elmu_mass>maxMass))){
        return false;
      }
    }
    if(invertCut){
      // one dilepton mass is inside of the window
      if( (elel_mass>minMass&&elel_mass<maxMass) || (mumu_mass>minMass&&mumu_mass<maxMass) || (cutForDifferentFlavors && elmu_mass>minMass&&elmu_mass<maxMass) ){
      	return false;
      }
    }

    cutflow.EventSurvivedStep(selectionName,input.weights.at("Weight"));
    
    return true;
}
