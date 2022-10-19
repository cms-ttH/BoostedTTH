// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/ConfigurationDescriptions.h"
#include "FWCore/ParameterSet/interface/ParameterSetDescription.h"

#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "SimDataFormats/JetMatching/interface/JetFlavourInfo.h"
#include "SimDataFormats/JetMatching/interface/JetFlavourInfoMatching.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "CommonTools/Utils/interface/StringCutObjectSelector.h"
#include "CommonTools/Utils/interface/StringObjectFunction.h"

class GenHFJetMatcher : public edm::stream::EDProducer<> {
   public:
    explicit GenHFJetMatcher(const edm::ParameterSet& iConfig) :
        src_(consumes< std::vector< reco::GenJet > >(iConfig.getParameter< edm::InputTag >("src"))),
        cut_(iConfig.getParameter< std::string >("cut"), true),
        deltaR_(iConfig.getParameter< double >("deltaR")),
        jetFlavourInfosToken_(consumes< reco::JetFlavourInfoMatchingCollection >(iConfig.getParameter< edm::InputTag >("jetFlavourInfos")))
    {
        produces< std::vector< pat::Jet > >("GenBJets");
        produces< std::vector< pat::Jet > >("GenCJets");
    }

    ~GenHFJetMatcher() override{};

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions)
    {
        edm::ParameterSetDescription desc;
        desc.add< edm::InputTag >("src")->setComment("input genJet collection");
        desc.add< edm::InputTag >("jetFlavourInfos")->setComment("input flavour info collection");
        desc.add< std::string >("cut")->setComment("cut on input genJet collection");
        desc.add< double >("deltaR")->setComment("deltaR to match genjets");
    }

   private:
    void produce(edm::Event&, edm::EventSetup const&) override;

    edm::EDGetTokenT< std::vector< reco::GenJet > >            src_;
    const StringCutObjectSelector< reco::GenJet >              cut_;
    const double                                               deltaR_;
    edm::EDGetTokenT< reco::JetFlavourInfoMatchingCollection > jetFlavourInfosToken_;
};

// ------------ method called to produce the data  ------------
void GenHFJetMatcher::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    edm::Handle< reco::GenJetCollection > jets;
    iEvent.getByToken(src_, jets);

    edm::Handle< reco::JetFlavourInfoMatchingCollection > jetFlavourInfos;
    iEvent.getByToken(jetFlavourInfosToken_, jetFlavourInfos);

    std::vector< pat::Jet > GenBJets;
    std::vector< pat::Jet > GenCJets;

    for (const reco::GenJet& jet : *jets) {
        if (!cut_(jet)) continue;
        for (const reco::JetFlavourInfoMatching& jetFlavourInfoMatching : *jetFlavourInfos) {
            if (deltaR(jet.p4(), jetFlavourInfoMatching.first->p4()) < deltaR_) {
                int hadronflavour = jetFlavourInfoMatching.second.getHadronFlavour();
                if (hadronflavour == 5)
                    GenBJets.push_back(jet);
                else if (hadronflavour == 4)
                    GenCJets.push_back(jet);
                //std::cout << "Number of GenBJets: " << GenBJets.size() << std::endl;
                //std::cout << "Number of GenCJets: " << GenCJets.size() << std::endl;
                break;
            }
        }
    }
    std::unique_ptr< std::vector< pat::Jet > > GenBJetsPtr = std::make_unique< std::vector< pat::Jet > >(GenBJets);
    std::unique_ptr< std::vector< pat::Jet > > GenCJetsPtr = std::make_unique< std::vector< pat::Jet > >(GenCJets);
    iEvent.put(std::move(GenBJetsPtr), "GenBJets");
    iEvent.put(std::move(GenCJetsPtr), "GenCJets");
}

#include "FWCore/Framework/interface/MakerMacros.h"
//define this as a plug-in
DEFINE_FWK_MODULE(GenHFJetMatcher);
