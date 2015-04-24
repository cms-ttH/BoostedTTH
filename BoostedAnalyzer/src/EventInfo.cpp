#include  "BoostedTTH/BoostedAnalyzer/interface/EventInfo.hpp"

EventInfo::  EventInfo(const edm::Event& iEvent_, const edm::Handle<reco::BeamSpot>& beamSpot_, const edm::Handle<HcalNoiseSummary>& hcalNoiseSummary_, const edm::Handle< std::vector<PileupSummaryInfo> >& puSummaryInfo_):
    evt(-1),
    run(-1),
    sample(-1),
    lumiBlock(-1),
    BSx(-99.), BSy(-99.), BSz(-99.),
    //        GoodVertex(false),
    hcalnoiseLoose(false), hcalnoiseTight(false),
    sumNVtx(0), numGenPV(-1), nm1(-1), n0(-1), np1(-1),
    sumTrueNVtx(0), numTruePV(-1), nm1_true(-1), n0_true(-1), np1_true(-1) {};

EventInfo(const edm::Event& iEvent, const edm::Handle<GenEventInfoProduct>& genEvtInfo, const edm::Handle<reco::BeamSpot>& beamSpot, const edm::Handle<HcalNoiseSummary>& hcalNoiseSummary, const edm::Handle< std::vector<PileupSummaryInfo> >& puSummaryInfo){
 
  EventInfo event = EventInfo();
  
  event.evt         = iEvent.id().event();
  event.run         = iEvent.id().run();
  event.sample      = sampleID;
  event.lumiBlock   = iEvent.luminosityBlock();
  
  
  if(genEvtInfo.isValid()){
    std::vector<double> genWeights = genEvtInfo->weights();
    for(size_t i=0;i<genWeights.size();i++){
      event.weight *= genWeights[i];
    }

    event.qScale = genEvtInfo->qScale();
    event.alphaQCD = genEvtInfo->alphaQCD();
    event.alphaQED = genEvtInfo->alphaQED();
    event.pthat = ( genEvtInfo->hasBinningValues() ? (genEvtInfo->binningValues())[0] : 0.0);
    event.scalePDF = genEvtInfo->pdf()->scalePDF;
    event.x1 = genEvtInfo->pdf()->x.first;
    event.x2 = genEvtInfo->pdf()->x.second;
    event.xPDF1 = genEvtInfo->pdf()->xPDF.first;
    event.xPDF2 = genEvtInfo->pdf()->xPDF.second;
    event.id1 = genEvtInfo->pdf()->id.first;
    event.id2 = genEvtInfo->pdf()->id.second;
  }
  
  if(beamSpot.isValid()){
    event.BSx = beamSpot->x0();
    event.BSy = beamSpot->y0();
    event.BSz = beamSpot->z0();
  }
  
 
  if( hcalNoiseSummary.isValid() ){
    event.hcalnoiseLoose = hcalNoiseSummary->passLooseNoiseFilter();
    event.hcalnoiseTight = hcalNoiseSummary->passTightNoiseFilter();
  }
  
  if( puSummaryInfo.isValid() ){
    for(std::vector<PileupSummaryInfo>::const_iterator PVI = puSummaryInfo->begin(); PVI != puSummaryInfo->end(); ++PVI) {

      int BX = PVI->getBunchCrossing();

      event.sumNVtx  += float(PVI->getPU_NumInteractions());
      event.sumTrueNVtx += float(PVI->getTrueNumInteractions());

      if( BX==0 ){
	      event.numGenPV = PVI->getPU_NumInteractions();
	      event.numTruePV = PVI->getTrueNumInteractions();
      }

      if(BX == -1) { 
	      event.nm1 = PVI->getPU_NumInteractions();
	      event.nm1_true = PVI->getTrueNumInteractions();
      }
      else if(BX == 0) { 
	      event.n0 = PVI->getPU_NumInteractions();
	      event.n0_true = PVI->getTrueNumInteractions();
      }
      else if(BX == 1) { 
	      event.np1 = PVI->getPU_NumInteractions();
	      event.np1_true = PVI->getTrueNumInteractions();
      }
    }
  }
  
  return event;
}
