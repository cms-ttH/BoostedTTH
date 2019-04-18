#include  "BoostedTTH/BoostedAnalyzer/interface/FilterInfo.hpp"
using namespace std;
FilterInfo::FilterInfo(std::map<std::string, bool> filters_){
    filters=filters_;
}

bool FilterInfo::Exists(std::string filtername) const {
    if(filters.find(filtername)==filters.end()){ 
	return false;
    }
    return true;
}

bool FilterInfo::Pass(std::string filtername) const {
    if(filtername=="any"||filtername=="Any"||filtername=="none"||filtername=="None") return true;
    int asterix = filtername.find("*");
    if(asterix==int(std::string::npos)){
	return Exists(filtername)&&filters.at(filtername);
    }
    else{
	if(asterix==int(filtername.length()-1)){
	    filtername.pop_back();
	    auto it=filters.lower_bound(filtername);
	    while(it!=filters.end()&&it->first.find(filtername) == 0){
		if(it->second) return true;
		it++;
	    }
	    return false;
	}
	else{
	    cerr << "* wildcard only allowed at the end" << endl;
	    return false;
	}
    }
    return false;    
}

bool FilterInfo::PassAll(std::vector< std::string > filternames) const {
    for(auto name=filternames.begin(); name!=filternames.end();name++){
	if(!Pass(*name)) return false;
    }
    return true;
}

std::map<std::string, bool> FilterInfo::GetFilters() const{
    return filters;
}

FilterInfoProducer::FilterInfoProducer(const edm::ParameterSet& iConfig,
				       edm::ConsumesCollector && iC){
    filterBitsToken = iC.consumes< edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("filterBits"));
    for(auto &tag : iConfig.getParameter<std::vector<edm::InputTag> >("additionalFilters")){
	additionalFiltersNames.push_back(tag.label());
	additionalFiltersTokens.push_back(iC.consumes< bool >(tag));
    }
}

void FilterInfo::Print() const{
    std::cout << "Filters:" << endl;
    for(auto f : filters){
	std::cout << f.first << " " << f.second << "\n";
    }
}


FilterInfo FilterInfoProducer::Produce(const edm::Event& iEvent) const{
    std::map<std::string, bool> filters;
    edm::Handle<edm::TriggerResults> h_filterBits;
    iEvent.getByToken(filterBitsToken, h_filterBits);

    if (h_filterBits.isValid()){ 
	const edm::TriggerNames &names = iEvent.triggerNames(*h_filterBits);
	for (unsigned int i = 0; i < h_filterBits->size(); ++i) {   
	    string name=names.triggerName(i);
	    filters[name]=h_filterBits->accept(i);
	}
    }
    else{
	std::cout<<"filter handle is not valid!"<<std::endl;
    }


    for(uint i=0; i<additionalFiltersTokens.size(); i++){
    	edm::Handle< bool > h_additionalFilter;
    	iEvent.getByToken( additionalFiltersTokens[i],h_additionalFilter );
	filters[additionalFiltersNames[i]]=*h_additionalFilter;
    }
    return FilterInfo(filters);

}
