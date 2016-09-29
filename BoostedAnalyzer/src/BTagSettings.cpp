#include "BoostedTTH/BoostedAnalyzer/interface/BTagSettings.hpp"
#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"


//~ using namespace std;

	BTagSettings::BTagSettings(){
		tagger="pfCombinedInclusiveSecondaryVertexV2BJetTags";
		wp=0.800;
		CSVLwp=0.460;
		CSVMwp=0.800;
		CSVTwp=0.935;
			
	}
	
	BTagSettings::~BTagSettings(){}
		
	BTagSettings::BTagSettings(std::string tagger_,double wp_, double CSVLwp_, double CSVMwp_, double CSVTwp_){
		tagger=tagger_;
		wp=wp_;
		CSVLwp=CSVLwp_;
		CSVMwp=CSVMwp_;
		CSVTwp=CSVTwp_;
			
	}
    
    void BTagSettings::DumpStuff(){
		std::cout<<"BTagSetting class values"<<std::endl;
		std::cout<<"taggername "<<tagger<<std::endl;
		std::cout<<"wp "<<wp<<std::endl;
		std::cout<<"CSVLwp "<<CSVLwp<<std::endl;
		std::cout<<"CSVMwp "<<CSVMwp<<std::endl;
		std::cout<<"CSVTwp "<<CSVTwp<<std::endl;
		
		
	}
    
	
