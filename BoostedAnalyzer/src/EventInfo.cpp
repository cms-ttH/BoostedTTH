#include "BoostedTTH/BoostedAnalyzer/interface/EventInfo.hpp"

EventInfo::EventInfo(const edm::Event& iEvent, const edm::Handle< reco::BeamSpot >& beamSpot, const edm::Handle< HcalNoiseSummary >& hcalNoiseSummary,
                     const edm::Handle< std::vector< PileupSummaryInfo > >& puSummaryInfo, bool firstVertexIsGood_, float rho_) :
    firstVertexIsGood(firstVertexIsGood_),
    rho(rho_)
{
    evt = iEvent.id().event();

    run       = iEvent.id().run();
    lumiBlock = iEvent.luminosityBlock();

    BSx = beamSpot->x0();
    BSy = beamSpot->y0();
    BSz = beamSpot->z0();

    if (hcalNoiseSummary.isValid()) {
        hcalnoiseLoose = hcalNoiseSummary->passLooseNoiseFilter();
        hcalnoiseTight = hcalNoiseSummary->passTightNoiseFilter();
    }

    if (puSummaryInfo.isValid()) {
        for (std::vector< PileupSummaryInfo >::const_iterator PVI = puSummaryInfo->begin(); PVI != puSummaryInfo->end(); ++PVI) {
            int BX = PVI->getBunchCrossing();

            sumNVtx += float(PVI->getPU_NumInteractions());
            sumTrueNVtx += float(PVI->getTrueNumInteractions());

            if (BX == 0) {
                numGenPV  = PVI->getPU_NumInteractions();
                numTruePV = PVI->getTrueNumInteractions();
            }

            if (BX == -1) {
                nm1      = PVI->getPU_NumInteractions();
                nm1_true = PVI->getTrueNumInteractions();
            }
            else if (BX == 0) {
                n0      = PVI->getPU_NumInteractions();
                n0_true = PVI->getTrueNumInteractions();
            }
            else if (BX == 1) {
                np1      = PVI->getPU_NumInteractions();
                np1_true = PVI->getTrueNumInteractions();
            }
        }
    }
}
