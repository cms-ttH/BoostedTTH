#include  "BoostedTTH/BoostedAnalyzer/interface/EventInfo.hpp"

EventInfo::  EventInfo() :
    weight(1.),
    evt(-1),
    run(-1),
    sample(-1),
    lumiBlock(-1),
    qScale(-1.),
    alphaQCD(-1.), alphaQED(-1.),
    pthat(-1.),
    scalePDF(-1.),
    x1(-1.), x2(-1.),
    xPDF1(-1.), xPDF2(-1.),
    id1(-99), id2(-99),
    BSx(-99.), BSy(-99.), BSz(-99.),
    //        GoodVertex(false),
    hcalnoiseLoose(false), hcalnoiseTight(false),
    sumNVtx(0), numGenPV(-1), nm1(-1), n0(-1), np1(-1),
    sumTrueNVtx(0), numTruePV(-1), nm1_true(-1), n0_true(-1), np1_true(-1) {};

