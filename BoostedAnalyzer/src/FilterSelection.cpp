#include "FWCore/Utilities/interface/Exception.h"

#include "BoostedTTH/BoostedAnalyzer/interface/FilterSelection.hpp"

using namespace std;


FilterSelection::FilterSelection(const edm::ParameterSet& iConfig){
    filters=iConfig.getParameter< std::vector<std::string> >("METfilters");
}

FilterSelection::~FilterSelection (){}

void FilterSelection::InitCutflow(Cutflow& cutflow){
    for(auto const filter : filters){
	cutflow.AddStep(string("Filter "+filter));
    }
    initialized=true;
}

bool FilterSelection::IsSelected(const InputCollections& input,Cutflow& cutflow){
    if(!initialized) cerr << "FilterSelection not initialized" << endl;
    for(auto const filter : filters){
	if( !input.filterInfo.Pass(filter) ) return false;
	else cutflow.EventSurvivedStep(string("Filter ")+filter,input.weights.at("Weight"));
    }
    return true;
}
