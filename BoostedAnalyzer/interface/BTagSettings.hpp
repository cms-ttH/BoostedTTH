#ifndef BTAG_SETTINGS_HPP
#define BTAG_SETTINGS_HPP

using namespace std;
#include <string>
#include <DataFormats/PatCandidates/interface/Jet.h>

class BTagSettings {
	  		public:


		//~ bool PassesCSV(const pat::Jet& jet, const char workingPoint='M');

        BTagSettings();
        ~BTagSettings();
		BTagSettings(std::string tagger_,double wp_, double CSVLwp_, double CSVMwp_, double CSVTwp_);

		
		std::string GetTaggerName() const { return tagger; }
		double Getwp() const { return wp; }
		double GetCSVMwp() const { return CSVMwp; }
		double GetCSVLwp() const { return CSVLwp; }
		double GetCSVTwp() const { return CSVTwp; }
		
		void DumpStuff();
		

	
		private:
		
		std::string tagger;
		double wp;
		double CSVLwp;//CSVv2 0.460; 
		double CSVMwp;//CSVv2 0.800;
		double CSVTwp;//CSVv2 0.935;
		
	  };
	  
#endif
	  

