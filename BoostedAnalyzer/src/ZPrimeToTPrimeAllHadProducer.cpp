// -*- C++ -*-
//
// Package:    ZPrimeToTPrimeAllHadProducer/ZPrimeToTPrimeAllHadProducer
// Class:      ZPrimeToTPrimeAllHadProducer
// 
/**\class ZPrimeToTPrimeAllHadProducer ZPrimeToTPrimeAllHadProducer.cc ZPrimeToTPrimeAllHadProducer/ZPrimeToTPrimeAllHadProducer/plugins/ZPrimeToTPrimeAllHadProducer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Simon Kudella
//         Created:  Wed, 17 Aug 2016 09:44:11 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"

#include "BoostedTTH/BoostedAnalyzer/interface/ZPrimeToTPrimeAllHadProducer.hpp"

ZPrimeToTPrimeAllHad::ZPrimeToTPrimeAllHad(){}
ZPrimeToTPrimeAllHad::~ZPrimeToTPrimeAllHad(){}
//






ZPrimeToTPrimeAllHadProducer::ZPrimeToTPrimeAllHadProducer(edm::ConsumesCollector && iC)
{
    customGenJetsToken             = iC.consumes< std::vector<reco::GenJet> >(edm::InputTag("ak4GenJetsCustom","",""));
    prunedGenParticlesToken        = iC.consumes< std::vector<reco::GenParticle> >(edm::InputTag("prunedGenParticles","",""));
}
ZPrimeToTPrimeAllHadProducer::~ZPrimeToTPrimeAllHadProducer(){}


//
// member functions
//

// ------------ method called to produce the data  ------------
ZPrimeToTPrimeAllHad ZPrimeToTPrimeAllHadProducer::Produce(const edm::Event& iEvent, bool doGenHadronMatch, bool returnDummy)
{
//    using namespace edm;
    ZPrimeToTPrimeAllHad zprimetotprimeallhad;
    if(returnDummy) {return zprimetotprimeallhad;     cout<<"obbacht, mein Lieber Herr Gesangsverein, returning Dummy"<<endl;};

    edm::Handle<std::vector<reco::GenParticle> > prunedGenParticles;
    iEvent.getByToken(prunedGenParticlesToken, prunedGenParticles);
//    int ZPrimeTPrimeID_full = *genTtbarId;
//    int ZPrimeTPrimeID = ZPrimeTPrimeID_full%100;
    zprimetotprimeallhad.fillGenZPrimeTPrimeEvent(*prunedGenParticles/*, ZPrimeTPrimeID*/);

    return zprimetotprimeallhad;
 
}




void ZPrimeToTPrimeAllHad::fillGenZPrimeTPrimeEvent(const std::vector<reco::GenParticle>& prunedGenParticles/*, int ZPrimeTPrimeID_*/){
//    ZPrimeTPrimeID=ZPrimeTPrimeID_;
    bool foundT=false;
    bool foundTbar=false;
    bool foundTPrime=false;
    bool foundTPrimebar=false;
    bool foundW=false;
    bool foundZPrime=false;
    bool foundZ=false;
    bool foundHiggs=false;
    bool foundB=false;
    bool foundBbar=false;


    
    for(auto p=prunedGenParticles.begin(); p!=prunedGenParticles.end(); p++){                       //loop over all gen particles
//        cout<<p->pdgId()<<endl;
        if (abs(p->pdgId())==6){
            if(p->pdgId()==6) foundT=true;
            if(p->pdgId()==-6) foundTbar=true;
            bool lastTop=true;
            for(uint i=0;i<p->numberOfDaughters();i++){
                if (abs(p->daughter(i)->pdgId())==6)
                lastTop=false;
            }
            bool fromZprime=false;
            bool fromTPrime=false;
            bool fromBG=false;
            const reco::Candidate* mother=&(*p);
            while(mother!=0 && abs(mother->pdgId())==6){                                           //check where W comes from 9000010
                if ((abs(mother->mother()->pdgId())==9900113) || (abs(mother->mother()->pdgId())==9000010)){
                    fromZprime=true;
                    break;
                }
                if ((abs(mother->mother()->pdgId())==8000001) || (abs(mother->mother()->pdgId())==9000001) || (abs(mother->mother()->pdgId())==9000003)){
                    fromTPrime=true;
                    break;
                }
                if (abs(mother->mother()->pdgId())!=6 && (abs(mother->mother()->pdgId())!=8000001 || abs(mother->mother()->pdgId())!=9000001 || abs(mother->mother()->pdgId())!=9000003) && ((abs(mother->mother()->pdgId())!=9900113) || (abs(mother->mother()->pdgId())!=9000010))){
                    fromBG=true;
                    break;
                }
                else mother=mother->mother();
	
            }
            
            if(lastTop){
                if(fromZprime){
                    if(p->pdgId()==6) tops_fromZprime.push_back(*p);
                    if(p->pdgId()==-6) topbars_fromZprime.push_back(*p);
                topsandtopbars_fromZprime.push_back(*p);
                }
                if(fromTPrime){
                    if(p->pdgId()==6) tops_fromTprime.push_back(*p);
                    if(p->pdgId()==-6) topbars_fromTprime.push_back(*p);
                topsandtopbars_fromTprime.push_back(*p);
                }
                if(fromBG){
                    if(p->pdgId()==6) tops_fromBG.push_back(*p);
                    if(p->pdgId()==-6) topbars_fromBG.push_back(*p);
                topsandtopbars_fromBG.push_back(*p);
                }
                bool setTDecay=false;
                bool setTBarDecay=false;
                for(uint i=0;i<p->numberOfDaughters();i++){
                    if(p->pdgId()==6 && abs(p->daughter(i)->pdgId())<6){
                        if(setTDecay) std::cerr << "ZPrimeToTPrimeAllHad: error 1"<<std::endl;
                        top_decay_quarks.push_back(*(reco::GenParticle*)p->daughter(i));
                        setTDecay=true;
                        if(p->daughter(i)->pdgId()==5) top_decay_bottom.push_back(*(reco::GenParticle*)p->daughter(i));

                    }
                    if(p->pdgId()==-6 && abs(p->daughter(i)->pdgId())<6){
                        if(setTBarDecay) std::cerr << "ZPrimeToTPrimeAllHad: error 1"<<std::endl;
                        topbar_decay_quarks.push_back(*(reco::GenParticle*)p->daughter(i));
                        setTBarDecay=true;
                        if(p->daughter(i)->pdgId()==-5) topbar_decay_bottom.push_back(*(reco::GenParticle*)p->daughter(i));

                    }
                    if(abs(p->daughter(i)->pdgId())==5) topandtopbar_decay_bottoms.push_back(*(reco::GenParticle*)p->daughter(i));
                }

            }
        }
/*       
        const reco::Candidate* mother=&(*p);
        while(mother!=0 && abs(mother->pdgId())==6){                                           //check where W comes from
                if (abs(mother->mother()->pdgId())!=6){
                break;
                }
                else mother=mother->mother();
	
        }
        cout<<"foundTop "<<foundT<<" from "<<mother->mother()->pdgId()<<" with status: "<<mother->mother()->status()<<endl;
        cout<<"foundTopbar "<<foundTbar<<" from "<<mother->mother()->pdgId()<<" with status: "<<mother->mother()->status()<<endl;    
        
        
*/
        if ((abs(p->pdgId())==8000001) || (abs(p->pdgId())==9000001) || (abs(p->pdgId())==9000003)){                                                                    //check if gen particle is TPrime/TPrimebar 9000001
            if((p->pdgId()==8000001) || (p->pdgId()==9000001) || (p->pdgId()==9000003)) foundTPrime=true;
            if((p->pdgId()==-8000001) || (p->pdgId()==-9000001) || (p->pdgId()==-9000003)) foundTPrimebar=true;
            bool lastTPrime=true;
            for(uint i=0;i<p->numberOfDaughters();i++){
                if ((abs(p->daughter(i)->pdgId())==8000001) || (abs(p->daughter(i)->pdgId())==9000001) || (abs(p->daughter(i)->pdgId())==9000003))
                lastTPrime=false;
            }                                                                                       //check if last TPrime -> decaying
            if(lastTPrime){
                if((p->pdgId()==8000001) || (p->pdgId()==9000001) || (p->pdgId()==9000003)) TPrimes.push_back(*p);
                if((p->pdgId()==-8000001) || (p->pdgId()==-9000001) || (p->pdgId()==-9000003)) TPrimebars.push_back(*p);
                TPrimesandTPrimebars.push_back(*p);
                bool setTPrimeDecay=false;
                bool setTPrimeBarDecay=false;

                for(uint i=0;i<p->numberOfDaughters();i++){
                    if((p->pdgId()==8000001 || p->pdgId()==9000001 || (p->pdgId()==9000003)) && abs(p->daughter(i)->pdgId())<7){
                        if(setTPrimeDecay) std::cerr << "GenTPrimeEvent: error 1"<<std::endl;
                        TPrime_decay_quarks.push_back(*(reco::GenParticle*)p->daughter(i));
                        if (p->daughter(i)->pdgId()==5) TPrime_decay_bottom.push_back(*(reco::GenParticle*)p->daughter(i));

                        setTPrimeDecay=true;
                    }
                    if((p->pdgId()==-8000001 || p->pdgId()==-9000001 || (p->pdgId()==-9000003)) && abs(p->daughter(i)->pdgId())<7){
                        if(setTPrimeBarDecay) std::cerr << "GenTPrimeEvent: error -1"<<std::endl;
                        TPrimebar_decay_quarks.push_back(*(reco::GenParticle*)p->daughter(i));
                        if (p->daughter(i)->pdgId()==-5) TPrimebar_decay_bottom.push_back(*(reco::GenParticle*)p->daughter(i));
                        setTPrimeBarDecay=true;
                    }
                    if(abs(p->daughter(i)->pdgId())==5) TPrimeandTPrimebar_decay_bottoms.push_back(*(reco::GenParticle*)p->daughter(i));
                }
            }
/*            const reco::Candidate* mother=&(*p);
            while(mother!=0 && abs(mother->pdgId())==8000001){                                           //check where W comes from
                if (abs(mother->mother()->pdgId())!=8000001){
                break;
                }
                else mother=mother->mother();
	
            }
            
        cout<<"foundTPrime "<<foundTPrime<<" from "<<mother->mother()->pdgId()<<" with status: "<<mother->mother()->status()<<endl;
        cout<<"foundTPrimebar "<<foundTPrimebar<<" from "<<mother->mother()->pdgId()<<" with status: "<<mother->mother()->status()<<endl;
*/      
        }

        if (abs(p->pdgId())==24){                                                                   //check if gen particle is W
            foundW=true;
            bool lastW=true;
            for(uint i=0;i<p->numberOfDaughters();i++){
                if (abs(p->daughter(i)->pdgId())==24)
                    lastW=false;
            }
            bool fromTop=false;
            bool fromTPrime=false;
            bool fromBG=false;
            const reco::Candidate* mother=&(*p);
            while(mother!=0 && abs(mother->pdgId())==24){                                           //check where W comes from
                if (abs(mother->mother()->pdgId())==6){
                    fromTop=true;
                    break;
                }
                if ((abs(mother->mother()->pdgId())==8000001) || (abs(mother->mother()->pdgId())==9000001) || (abs(mother->mother()->pdgId())==9000003)){
                    fromTPrime=true;
                    break;
                }
                if (abs(mother->mother()->pdgId())!=24 && (abs(mother->mother()->pdgId())!=8000001 || abs(mother->mother()->pdgId())!=9000001 || abs(mother->mother()->pdgId())!=9000003) && abs(mother->mother()->pdgId())!=6){
                    fromBG=true;
                    break;
                }
                else mother=mother->mother();
	
            }
                                                                                                    //check if last W  -> decaying
            if(lastW&&fromTop){
                if(p->pdgId()==24) wplus_fromTops.push_back(*p);
                if(p->pdgId()==-24) wminus_fromTops.push_back(*p);
                Wfromtopsandtopbars.push_back(*p);
                for(uint i=0;i<p->numberOfDaughters();i++){
                    if(p->pdgId()==24 && abs(p->daughter(i)->pdgId())<=16){
                        wplus_fromTop_decay_products.push_back(*(reco::GenParticle*)p->daughter(i));
                    }
                    if(p->pdgId()==-24 && abs(p->daughter(i)->pdgId())<=16){
                        wminus_fromTop_decay_products.push_back(*(reco::GenParticle*)p->daughter(i));
                    }
                }
            }
            if(lastW&&fromTPrime){
                if(p->pdgId()==24) wplus_fromTPrimes.push_back(*p);
                if(p->pdgId()==-24) wminus_fromTPrimes.push_back(*p);
                WfromTPrimesandTPrimebars.push_back(*p);
                for(uint i=0;i<p->numberOfDaughters();i++){
                    if(p->pdgId()==24 && abs(p->daughter(i)->pdgId())<=16){
                        wplus_fromTPrime_decay_products.push_back(*(reco::GenParticle*)p->daughter(i));
                    }
                    if(p->pdgId()==-24 && abs(p->daughter(i)->pdgId())<=16){
                        wminus_fromTPrime_decay_products.push_back(*(reco::GenParticle*)p->daughter(i));
                    }
                }
            }
           if(lastW&&fromBG){
                if(p->pdgId()==24) wplus_fromBG.push_back(*p);
                if(p->pdgId()==-24) wminus_fromBG.push_back(*p);
                Ws_fromBG.push_back(*p);
                for(uint i=0;i<p->numberOfDaughters();i++){
                    if(p->pdgId()==24 && abs(p->daughter(i)->pdgId())<=16){
                        wplus_fromBG_decay_products.push_back(*(reco::GenParticle*)p->daughter(i));
                    }
                    if(p->pdgId()==-24 && abs(p->daughter(i)->pdgId())<=16){
                        wminus_fromBG_decay_products.push_back(*(reco::GenParticle*)p->daughter(i));
                    }
                }
               
           }
/*
            while(mother!=0 && abs(mother->pdgId())==24){                                           //check where W comes from
                    if (abs(mother->mother()->pdgId())!=24){
                    break;
                    }
                    else mother=mother->mother();
	
            }
            cout<<"foundW "<<foundW<<" from "<<mother->mother()->pdgId()<<" with status: "<<mother->mother()->status()<<endl;
*/
        }
        
        
        if (abs(p->pdgId())==5){                                                                   //check if gen particle is b
            foundB=true;
            bool lastBottom=true;
            for(uint i=0;i<p->numberOfDaughters();i++){
                if (abs(p->daughter(i)->pdgId())==5)
                    lastBottom=false;
            }
            bool fromTop=false;
            bool fromTPrime=false;
            bool fromBG=false;
            const reco::Candidate* mother=&(*p);
            while(mother!=0 && abs(mother->pdgId())==5){                                           //check where b comes from
                if (abs(mother->mother()->pdgId())==6){
                    fromTop=true;
                    break;
                }
                if ((abs(mother->mother()->pdgId())==8000001) || (abs(mother->mother()->pdgId())==9000001) || (abs(mother->mother()->pdgId())==9000003)){
                    fromTPrime=true;
                    break;
                }
                if (abs(mother->mother()->pdgId())!=5 && abs(mother->mother()->pdgId())!=6 && (abs(mother->mother()->pdgId())!=8000001 || abs(mother->mother()->pdgId())!=9000001 || abs(mother->mother()->pdgId())!=9000003)){
                    fromBG=true;
                    break;
                }
                else mother=mother->mother();
	
            }
            if(lastBottom&&fromTop){
                if(p->pdgId()==5) Bottom_fromTops.push_back(*p);
                if(p->pdgId()==-5) Bottombar_fromTops.push_back(*p);
                Bottom_fromTopsandTopbars.push_back(*p);
            }
            if(lastBottom&&fromTPrime){
                if(p->pdgId()==5) Bottom_fromTPrimes.push_back(*p);
                if(p->pdgId()==-5) Bottombar_fromTPrimes.push_back(*p);
                Bottom_fromTPrimesandTPrimebars.push_back(*p);
            }
            if(lastBottom&&fromBG){
                if(p->pdgId()==5) Bottom_fromBG.push_back(*p);
                if(p->pdgId()==-5) Bottombar_fromBG.push_back(*p);
                Bottoms_fromBG.push_back(*p);
            }
        }
        
        
        
        if ((abs(p->pdgId())==9900113) || (abs(p->pdgId())==9000010) ){                                                                    //check if gen particle is ZPrime
            foundZPrime=true;
            bool lastZPrime=true;
            for(uint i=0;i<p->numberOfDaughters();i++){
                if ((abs(p->daughter(i)->pdgId())==9900113) || (abs(p->daughter(i)->pdgId())==9000010))
                lastZPrime=false;
            }                                                                                       //check if last ZPrime -> decaying
            if(lastZPrime){
                ZPrimes.push_back(*p);
                for(uint i=0;i<p->numberOfDaughters();i++){
                    if((abs(p->daughter(i)->pdgId())!=9900113) || (abs(p->daughter(i)->pdgId())!=9000010)){
                        ZPrime_decay_products.push_back(*(reco::GenParticle*)p->daughter(i));
                    }
                }
            }
//        cout<<"foundZPrime "<<foundZPrime<<endl;

        }
        
        
        if (abs(p->pdgId())==23){                                                                    //check if gen particle is Z
            if(p->pdgId()==23) foundZ=true;
            bool lastZ=true;
            for(uint i=0;i<p->numberOfDaughters();i++){
                if (p->daughter(i)->pdgId()==23)
                lastZ=false;
            }                                                                                       //check if last ZPrime -> decaying
            if(lastZ){
                Zs.push_back(*p);
                for(uint i=0;i<p->numberOfDaughters();i++){
                    if(abs(p->daughter(i)->pdgId())<=23){
                        Z_decay_products.push_back(*(reco::GenParticle*)p->daughter(i));
                    }
                }
            }
        }
        if (abs(p->pdgId())==25){                                                                    //check if gen particle is Higgs
            if(p->pdgId()==25) foundHiggs=true;
            bool lastHiggs=true;
            for(uint i=0;i<p->numberOfDaughters();i++){
                if (p->daughter(i)->pdgId()==25)
                lastHiggs=false;
            }                                                                                       //check if last Higgs -> decaying
            if(lastHiggs){
                Higgs.push_back(*p);
                for(uint i=0;i<p->numberOfDaughters();i++){
                    if(abs(p->daughter(i)->pdgId())<=16){
                        Higgs_decay_products.push_back(*(reco::GenParticle*)p->daughter(i));
                    }
                }
            }
        }
        
        
    }
    
    if(wminus_fromTop_decay_products.size()!=2 || wplus_fromTop_decay_products.size()!=2 || wminus_fromTPrime_decay_products.size()!=2 || wplus_fromTPrime_decay_products.size()!=2 || ZPrime_decay_products.size()!=2 || Z_decay_products.size()!=2 || Higgs_decay_products.size()!=2) {
        //std::cerr << "ZPrimeToTPrimeAllHad: error 2"<<std::endl;
        while(wminus_fromTop_decay_products.size()<2){
            wminus_fromTop_decay_products.push_back(reco::GenParticle());
        }
        while(wplus_fromTop_decay_products.size()<2){
            wplus_fromTop_decay_products.push_back(reco::GenParticle());
        }
        while(wminus_fromTPrime_decay_products.size()<2){
            wminus_fromTPrime_decay_products.push_back(reco::GenParticle());
        }
        while(wplus_fromTPrime_decay_products.size()<2){
            wplus_fromTPrime_decay_products.push_back(reco::GenParticle());
        }
        while(ZPrime_decay_products.size()<2){
            ZPrime_decay_products.push_back(reco::GenParticle());
        }
        while(Z_decay_products.size()<2){
            Z_decay_products.push_back(reco::GenParticle());
        }
        while(Higgs_decay_products.size()<2){
            Higgs_decay_products.push_back(reco::GenParticle());
        }
    }
//    if(top.energy()<1||topbar.energy()<1||wplus_fromTop.energy()<1||wminus_fromTop.energy()<1||wplus_fromTPrime.energy()<1||wminus_fromTPrime.energy()<1||top_decay_quark.energy()<1||topbar_decay_quark.energy()<1){ std::cerr << "ZPrimeToTPrimeAllHad: error 4"<<std::endl;}

    int nquarks_from_wplus_fromTop=0;
    for(auto p=wplus_fromTop_decay_products.begin(); p!=wplus_fromTop_decay_products.end();p++){
        if(abs(p->pdgId())<6) nquarks_from_wplus_fromTop++;
    }
    int nquarks_from_wminus_fromTop=0;
    for(auto p=wminus_fromTop_decay_products.begin(); p!=wminus_fromTop_decay_products.end();p++){
        if(abs(p->pdgId())<6) nquarks_from_wminus_fromTop++;
    }
    int nquarks_from_wplus_fromTPrime=0;
    for(auto p=wplus_fromTPrime_decay_products.begin(); p!=wplus_fromTPrime_decay_products.end();p++){
        if(abs(p->pdgId())<6) nquarks_from_wplus_fromTop++;
    }
    int nquarks_from_wminus_fromTPrime=0;
    for(auto p=wminus_fromTPrime_decay_products.begin(); p!=wminus_fromTPrime_decay_products.end();p++){
        if(abs(p->pdgId())<6) nquarks_from_wminus_fromTop++;
    }
    int nquarks_from_ZPrime=0;
    for(auto p=ZPrime_decay_products.begin(); p!=ZPrime_decay_products.end();p++){
        if(abs(p->pdgId())<6) nquarks_from_ZPrime++;
    }
    int nquarks_from_Z=0;
    for(auto p=Z_decay_products.begin(); p!=Z_decay_products.end();p++){
        if(abs(p->pdgId())<6) nquarks_from_Z++;
    }
    int nquarks_from_Higgs=0;
    for(auto p=Higgs_decay_products.begin(); p!=Higgs_decay_products.end();p++){
        if(abs(p->pdgId())<6) nquarks_from_Higgs++;
    }
       
    
    
    
    topIsHadronic=nquarks_from_wplus_fromTop==2;
    topbarIsHadronic=nquarks_from_wminus_fromTop==2;
    TPrimeIsHadronic=nquarks_from_wplus_fromTPrime==2;
    TPrimebarIsHadronic=nquarks_from_wminus_fromTPrime==2;
    HiggsIsHadronic=nquarks_from_Higgs==2;
    ZIsHadronic=nquarks_from_Z==2;
    
    AllHad=((topIsHadronic&&TPrimebarIsHadronic)||(topbarIsHadronic&&TPrimeIsHadronic)||(topIsHadronic&&topbarIsHadronic&&ZIsHadronic)||(topIsHadronic&&topbarIsHadronic&&HiggsIsHadronic));

    
    isZPrimeTPrime=((foundTPrime&&foundZPrime)||(foundTPrimebar&&foundZPrime));//((foundTbar&&foundB&&foundW)||(foundT&&foundBbar&&foundW)||(foundTbar&&foundHiggs&&foundT)||(foundT&&foundTbar&&foundHiggs));
    isZPrimeTPrimeAllHad=(isZPrimeTPrime&&AllHad);
    isZPrimeTPrimeWbAllHad=(isZPrimeTPrimeAllHad&&foundW&&(foundB||foundBbar));
    isZPrimeTPrimeZtAllHad=(isZPrimeTPrimeAllHad&&foundZ&&foundT&&foundTbar);
    isZPrimeTPrimeHtAllHad=(isZPrimeTPrimeAllHad&&foundHiggs&&foundT&&foundTbar);

//     if (tops_fromZprime.size()>0){
//         std::cout<<"WOW pointer? ProdZprime"<<tops_fromZprime.at(0)<<std::endl;
//         std::cout<<"daughter"<<tops_fromZprime[0].daughter(0)<<std::endl;
//     }
//     if (tops_fromTprime.size()>0){
//         std::cout<<"WOW pointer ProdTprime? "<<tops_fromTprime.at(0)<<std::endl;
//         std::cout<<"daughter"<<tops_fromTprime[0].daughter(0)<<std::endl;
//     }
//     if (tops_fromBG.size()>0){
//         std::cout<<"WOW pointer ProdBKG? "<<tops_fromBG.at(0)<<std::endl;
//         std::cout<<"daughter"<<tops_fromBG[0].daughter(0)<<std::endl;
//     }    
    isFilled=true;
    
    
}

bool ZPrimeToTPrimeAllHad::IsFilled() const{
  return isFilled;
}



std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetTops_fromZprimes() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return tops_fromZprime;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetTopbars_fromZprimes() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return topbars_fromZprime;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetTopsandTopbars_fromZprimes() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return topsandtopbars_fromZprime;
}

std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetTops_fromTprimes() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return tops_fromTprime;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetTopbars_fromTprimes() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return topbars_fromTprime;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetTopsandTopbars_fromTprimes() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return topsandtopbars_fromTprime;
}

std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetTops_fromBG() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return tops_fromBG;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetTopbars_fromBG() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return topbars_fromBG;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetTopsandTopbars_fromBG() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return topsandtopbars_fromBG;
}

std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetTPrimes() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return TPrimes;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetTPrimebars() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return TPrimebars;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetTPrimesandTPrimebars() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return TPrimesandTPrimebars;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetZPrimes() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return ZPrimes;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetHiggs() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return Higgs;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetZs() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return Zs;
}


std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetWplus_fromTops() const{
    assert(isFilled);
      if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return wplus_fromTops;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetWminus_fromTops() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return wminus_fromTops;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetW_fromTopsandTopbars() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return Wfromtopsandtopbars;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetWplus_fromTPrimes() const{
    assert(isFilled);
      if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return wplus_fromTPrimes;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetWminus_fromTPrimes() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return wminus_fromTPrimes;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetW_fromTPrimesandTPrimebars() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return WfromTPrimesandTPrimebars;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetWplus_fromBG() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return wplus_fromBG;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetWminus_fromBG() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return wminus_fromBG;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetWs_fromBG() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return Ws_fromBG;
}


std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetBottom_fromTops() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return Bottom_fromTops;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetBottom_fromTopbars() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return Bottombar_fromTops;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetBottom_fromTopsandTopbars() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return Bottom_fromTopsandTopbars;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetBottom_fromTPrimes() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return Bottom_fromTPrimes;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetBottom_fromTPrimebars() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return Bottombar_fromTPrimes;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetBottom_fromTPrimesandTPrimebars() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return Bottom_fromTPrimesandTPrimebars;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetBottoms_fromBG() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return Bottoms_fromBG;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetBottombars_fromBG() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return Bottoms_fromBG;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetBottomsandBottombars_fromBG() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return Bottoms_fromBG;
}


std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetTopDecayBottom() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return top_decay_bottom;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetTopbarDecayBottom() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return topbar_decay_bottom;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetTopandTopbarDecayBottoms() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return topandtopbar_decay_bottoms;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetTPrimeDecayBottom() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return TPrime_decay_bottom;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetTPrimebarDecayBottom() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return TPrimebar_decay_bottom;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetTPrimeandTPrimebarDecayBottoms() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return TPrimeandTPrimebar_decay_bottoms;
}




std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetTopDecayQuarks() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return top_decay_quarks;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetTopBarDecayQuarks() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return topbar_decay_quarks;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetTPrimeDecayQuarks() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return TPrime_decay_quarks;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetTPrimebarDecayQuarks() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return TPrimebar_decay_quarks;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetHiggsDecayProducts() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return Higgs_decay_products;
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetZDecayProducts() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  return Z_decay_products;
}





std::vector<reco::GenParticle>  ZPrimeToTPrimeAllHad::GetW_decay_products_fromTop() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  if(topIsHadronic) return wplus_fromTop_decay_products;
  else{
    std::cerr <<"hadronic/leptonic function called in ZPrimeToTPrimeAllHad, but not a semileptonic event" << std::endl;
    return std::vector<reco::GenParticle>();
  }
}
std::vector<reco::GenParticle>  ZPrimeToTPrimeAllHad::GetW_decay_products_fromTopbar() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  if(topbarIsHadronic) return wminus_fromTop_decay_products;
  else{
    std::cerr <<"hadronic/leptonic function called in ZPrimeToTPrimeAllHad, but not a semileptonic event" << std::endl;
    return std::vector<reco::GenParticle>();
  }
}
std::vector<reco::GenParticle>  ZPrimeToTPrimeAllHad::GetW_decay_products_fromTPrime() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  if(TPrimeIsHadronic) return wplus_fromTPrime_decay_products;
  else{
    std::cerr <<"hadronic/leptonic function called in ZPrimeToTPrimeAllHad, but not a semileptonic event" << std::endl;
    return std::vector<reco::GenParticle>();
  }
}
std::vector<reco::GenParticle>  ZPrimeToTPrimeAllHad::GetW_decay_products_fromTPrimebar() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  if(TPrimebarIsHadronic) return wminus_fromTPrime_decay_products;
  else{
    std::cerr <<"hadronic/leptonic function called in ZPrimeToTPrimeAllHad, but not a semileptonic event" << std::endl;
    return std::vector<reco::GenParticle>();
  }
}
std::vector<reco::GenParticle>  ZPrimeToTPrimeAllHad::GetWplus_decay_products_fromBG() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  if(TPrimebarIsHadronic) return wminus_fromBG_decay_products;
  else{
    std::cerr <<"hadronic/leptonic function called in ZPrimeToTPrimeAllHad, but not a semileptonic event" << std::endl;
    return std::vector<reco::GenParticle>();
  }
}
std::vector<reco::GenParticle>  ZPrimeToTPrimeAllHad::GetWminus_decay_products_fromBG() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  if(TPrimebarIsHadronic) return wminus_fromBG_decay_products;
  else{
    std::cerr <<"hadronic/leptonic function called in ZPrimeToTPrimeAllHad, but not a semileptonic event" << std::endl;
    return std::vector<reco::GenParticle>();
  }
}
/*
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetTPrimeHad() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  if(topIsHadronic) return TPrimes;
  else{
    std::cerr <<"hadronic function called in ZPrimeToTPrimeAllHad, but something fucked up" << std::endl;
    return std::vector<reco::GenParticle>();      
  }
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetTPrimebarHad() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  if(topbarIsHadronic) return TPrimebars;
  else{
    std::cerr <<"hadronic function called in ZPrimeToTPrimeAllHad, but something fucked up" << std::endl;
    return std::vector<reco::GenParticle>();      
  }
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetTopHad() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  if(topIsHadronic) return tops;
  else{
    std::cerr <<"hadronic function called in ZPrimeToTPrimeAllHad, but something fucked up" << std::endl;
    return std::vector<reco::GenParticle>();      
  }
}
std::vector<reco::GenParticle> ZPrimeToTPrimeAllHad::GetTopbarHad() const{
    assert(isFilled);
  if(!isFilled) std::cerr << "Trying to access ZPrimeToTPrimeAllHad but it is not filled" << std::endl;
  if(topbarIsHadronic) return topbars;
  else{
    std::cerr <<"hadronic function called in ZPrimeToTPrimeAllHad, but something fucked up" << std::endl;
    return std::vector<reco::GenParticle>();      
  }
}
*/

/*ZPrimeToTPrimeAllHadProducer::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
ZPrimeToTPrimeAllHadProducer::endStream() {
}
*/
// ------------ method called when starting to processes a run  ------------
/*
void
ZPrimeToTPrimeAllHadProducer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
ZPrimeToTPrimeAllHadProducer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
ZPrimeToTPrimeAllHadProducer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
ZPrimeToTPrimeAllHadProducer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
/* 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
ZPrimeToTPrimeAllHadProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(ZPrimeToTPrimeAllHadProducer);
*/
