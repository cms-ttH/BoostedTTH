// system include files
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

//#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"

#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "TH2F.h"
#include "TFile.h"

class SelectedPhotonProducer : public edm::EDProducer {
   public:
    explicit SelectedPhotonProducer(const edm::ParameterSet&);
    ~SelectedPhotonProducer();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

    enum class PhotonID { None, Veto, Loose, Medium, Tight };

    // Function to sort leptons by pt
    template< typename T >
    T GetSortedByPt(const T&);

   private:
    virtual void               beginJob() override;
    virtual void               produce(edm::Event&, const edm::EventSetup&) override;
    virtual void               endJob() override;
    std::vector< pat::Photon > GetSelectedPhotons(const std::vector< pat::Photon >& inputPhotons, const float iMinPt, const float iMaxEta,
                                                  const PhotonID photonID);
    bool                       isGoodPhoton(const pat::Photon& iPhoton, const float iMinPt, const float iMaxEta, const PhotonID iPhotonID);
    void                       AddPhotonSFs(std::vector< pat::Photon >& inputPhotons, const PhotonID iPhotonID) const;
    std::vector< float >       GetPhotonIDSF(const pat::Photon& iPhoton, const PhotonID iPhotonID) const;
    std::vector< pat::Photon > GetDeltaRCleanedPhotons(const std::vector< pat::Photon >& inputPhotons, const std::vector< pat::Electron >& inputElectrons,
                                                       const float DeltaR) const;
    // ----------member data ---------------------------
    const std::string          era;
    const bool                 isData;
    std::vector< double >      ptMins_;
    std::vector< double >      etaMaxs_;
    std::vector< std::string > collectionNames_;
    std::vector< std::string > ids_;

    // data access tokens
    // pileup density
    edm::EDGetTokenT< double > EDMRhoToken;
    // vertex collection
    edm::EDGetTokenT< reco::VertexCollection > EDMVertexToken;
    // photons
    edm::EDGetTokenT< pat::PhotonCollection > EDMPhotonsToken;
    // electrons
    edm::EDGetTokenT< pat::ElectronCollection > EDMElectronsToken;

    std::vector< PhotonID > photonIDs_;
    // primary vertex
    reco::Vertex vertex;

    // event-specific average pile-up energy density per unit area in the phi-eta
    // plane
    double rho;

    TH2F* PhoID_SF_Loose  = nullptr;
    TH2F* PhoID_SF_Medium = nullptr;
    TH2F* PhoID_SF_Tight  = nullptr;
};
