#ifndef SINGLEMUTRIGGERSFS_HPP
#define SINGLEMUTRIGGERSFS_HPP

#include "BoostedTTH/BoostedAnalyzer/interface/InputCollections.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/TriggerScaleFactors.hpp"

class SingleMuTriggerSFs : public TriggerScaleFactors {
   public:
    // constructors
    SingleMuTriggerSFs();
    SingleMuTriggerSFs(std::string name);

    // destructor for cleanup and so on, e.g. close opened files and so on ...
    ~SingleMuTriggerSFs() override;

    // load all necessary files and so on, depends on respective triggers, therefore virtual and should be overwritten
    // by derived class
    void Init(const InputCollections& input) override;

    // calculation of the trigger sfs depends on the triggers, therefore should be implemented in derived class -> virtual function
    std::vector< float > CalculateTriggerSFs(const InputCollections& input) override;

   private:
    TString file      = "";
    TFile*  root_file = nullptr;
    TH2F*   hist      = nullptr;
    float   xmin      = -999.;
    float   xmax      = -999.;
    float   ymin      = -999.;
    float   ymax      = -999.;
    float   pt        = -999.;
    float   eta       = -999.;
};
#endif
