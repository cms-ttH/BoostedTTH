#include "BoostedTTH/BoostedAnalyzer/interface/TriggerInfo.hpp"
using namespace std;

//the functions which actually match the trigger objects and see if it passes
namespace {
std::vector<const pat::TriggerObjectStandAlone*> getMatchedObjs(const float eta, const float phi, const std::vector<pat::TriggerObjectStandAlone>& trigObjs, const float maxDeltaR = 0.1)
{
    std::vector<const pat::TriggerObjectStandAlone*> matchedObjs;
    const float maxDR2 = maxDeltaR * maxDeltaR;
    for (auto& trigObj : trigObjs) {
        const float dR2 = reco::deltaR2(eta, phi, trigObj.eta(), trigObj.phi());
        if (dR2 < maxDR2)
            matchedObjs.push_back(&trigObj);
    }
    return matchedObjs;
}
}

TriggerInfo::TriggerInfo(std::map<std::string, bool> triggers_, std::map<std::string, int> prescales_)
{
    triggers = triggers_;
    prescales = prescales_;
}

bool TriggerInfo::Exists(std::string triggername) const
{
    if (triggers.find(triggername) == triggers.end()) {
        return false;
    }
    return true;
}

bool TriggerInfo::GetPrescale(std::string triggername) const
{
    if (!Exists(triggername))
        return -1;
    else
        return prescales.at(triggername);
}

bool TriggerInfo::IsTriggered(std::string triggername) const
{
    if (triggername == "any" || triggername == "Any" || triggername == "none" || triggername == "None")
        return true;
    int asterix = triggername.find("*");
    if (asterix == int(std::string::npos)) {
        return Exists(triggername) && triggers.at(triggername);
    } else {
        if (asterix == int(triggername.length() - 1)) {
            triggername.pop_back();
            auto it = triggers.lower_bound(triggername);
            while (it != triggers.end() && it->first.find(triggername) == 0) {
                if (it->second)
                    return true;
                it++;
            }
            return false;
        } else {
            cerr << "* wildcard only allowed at the end" << endl;
            return false;
        }
    }
    return false;
}

bool TriggerInfo::IsAnyTriggered(std::vector<std::string> triggernames) const
{
    for (auto name = triggernames.begin(); name != triggernames.end(); name++) {
        if (IsTriggered(*name))
            return true;
    }
    return false;
}
std::map<std::string, bool> TriggerInfo::GetTriggers() const
{
    return triggers;
}

TriggerInfoProducer::TriggerInfoProducer(const edm::ParameterSet& iConfig,
    edm::ConsumesCollector&& iC)
{
    triggerBitsToken = iC.consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerBits"));
    triggerPrescalesToken = iC.consumes<pat::PackedTriggerPrescales>(iConfig.getParameter<edm::InputTag>("triggerPrescales"));
    era = iConfig.getParameter<std::string>("dataEra");
    if (era.find("2017") != std::string::npos) {
        triggerObjectsToken = iC.consumes<std::vector<pat::TriggerObjectStandAlone>>(iConfig.getParameter<edm::InputTag>("triggerObjects"));
        elesToken_ = iC.consumes<edm::View<pat::Electron>>(edm::InputTag("slimmedElectrons"));
    }
}

void TriggerInfo::Print() const
{
    std::cout << "Triggers:" << endl;
    for (auto f : triggers) {
        std::cout << f.first << " " << f.second << "\n";
    }
}

TriggerInfo TriggerInfoProducer::Produce(const edm::Event& iEvent) const
{
    std::map<std::string, bool> triggers;
    std::map<std::string, int> prescales;
    std::map<std::string, int> triggerFilters;
    edm::Handle<edm::TriggerResults> h_triggerBits;
    edm::Handle<std::vector<pat::TriggerObjectStandAlone>> h_triggerObjects;
    edm::Handle<pat::PackedTriggerPrescales> h_triggerPrescales;
    edm::Handle<edm::View<pat::Electron>> h_eles;
    iEvent.getByToken(triggerBitsToken, h_triggerBits);
    iEvent.getByToken(triggerPrescalesToken, h_triggerPrescales);

    if (h_triggerBits.isValid()) {
        const edm::TriggerNames& names = iEvent.triggerNames(*h_triggerBits);
        for (unsigned int i = 0; i < h_triggerBits->size(); ++i) {
            string name = names.triggerName(i);
            triggers[name] = h_triggerBits->accept(i);
            prescales[name] = h_triggerPrescales->getPrescaleForIndex(i);
        }
        if (era.find("2017") != std::string::npos) {
            iEvent.getByToken(triggerObjectsToken, h_triggerObjects);
            iEvent.getByToken(elesToken_, h_eles);
            // see https://twiki.cern.ch/twiki/bin/view/CMS/Egamma2017DataRecommendations
            //so the filter names are all packed in miniAOD so we need to create a new collection of them which are unpacked
            std::vector<pat::TriggerObjectStandAlone> unpackedTrigObjs;
            for (pat::TriggerObjectStandAlone obj : *h_triggerObjects) {
                // obj.unpackPathNames(names);
                unpackedTrigObjs.push_back(obj);
                unpackedTrigObjs.back().unpackFilterLabels(iEvent, *h_triggerBits);

                // std::cout << "checking eles " << std::endl;
                for (auto& ele : *h_eles) {
                    //the eta/phi of e/gamma trigger objects is the supercluster eta/phi
                    const float eta = ele.superCluster()->eta();
                    const float phi = ele.superCluster()->phi();

                    //now match ALL objects in a cone of DR<0.1
                    //it is important to match all objects as there are different ways to reconstruct the same electron
                    //eg, L1 seeded, unseeded, as a jet etc
                    //and so you want to be sure you get all possible objects
                    std::vector<const pat::TriggerObjectStandAlone*> matchedTrigObjs = getMatchedObjs(eta, phi, unpackedTrigObjs, 0.1);
                    for (const auto trigObj : matchedTrigObjs) {
                        //now just check if it passes the two filters
                        if (trigObj->hasFilterLabel("hltEle32L1DoubleEGWPTightGsfTrackIsoFilter") && trigObj->hasFilterLabel("hltEGL1SingleEGOrFilter")) {
                            // std::cout << " ele " << ele.et() << " " << eta << " " << phi << " passes HLT_Ele32_WPTight_Gsf" << std::endl;
                            triggers["HLT_Ele32_WPTight_Gsf_2017Seeds"] = true;
                        }
                    }
                }
            }
        }
    } else {
        std::cout << "trigger handle is not valid!" << std::endl;
    }

    return TriggerInfo(triggers, prescales);
}
