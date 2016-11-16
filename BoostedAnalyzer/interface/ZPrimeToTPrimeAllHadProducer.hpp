#ifndef BOOSTEDTTH_BOOSTEDANALYZER_ZPRIMETOTPRIMEALLHADPRODUCER_HPP
#define BOOSTEDTTH_BOOSTEDANALYZER_ZPRIMETOTPRIMEALLHADPRODUCER_HPP

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"


#include <vector>
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJet.h"






class ZPrimeToTPrimeAllHad{
   public:
      ZPrimeToTPrimeAllHad();
      ~ZPrimeToTPrimeAllHad();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
      bool IsFilled() const;


      std::vector<reco::GenParticle> GetTopHad() const;
      std::vector<reco::GenParticle> GetTopbarHad() const;
      

      std::vector<reco::GenParticle> GetTPrimeHad() const;
      std::vector<reco::GenParticle> GetTPrimebarHad() const;
      

      




      std::vector<reco::GenParticle> GetZPrimes() const;
      std::vector<reco::GenParticle> GetHiggs() const;
      std::vector<reco::GenParticle> GetZs() const;
      
      std::vector<reco::GenParticle> GetTops_fromZprimes() const;
      std::vector<reco::GenParticle> GetTopbars_fromZprimes() const;
      std::vector<reco::GenParticle> GetTopsandTopbars_fromZprimes() const;
      std::vector<reco::GenParticle> GetTops_fromTprimes() const;
      std::vector<reco::GenParticle> GetTopbars_fromTprimes() const;
      std::vector<reco::GenParticle> GetTopsandTopbars_fromTprimes() const;
      std::vector<reco::GenParticle> GetTops_fromBG() const;
      std::vector<reco::GenParticle> GetTopbars_fromBG() const;
      std::vector<reco::GenParticle> GetTopsandTopbars_fromBG() const;
      
      std::vector<reco::GenParticle> GetTPrimes() const;
      std::vector<reco::GenParticle> GetTPrimebars() const;
      std::vector<reco::GenParticle> GetTPrimesandTPrimebars() const;   
      
      std::vector<reco::GenParticle> GetWplus_fromTops() const;
      std::vector<reco::GenParticle> GetWminus_fromTops() const;
      std::vector<reco::GenParticle> GetW_fromTopsandTopbars() const;
      std::vector<reco::GenParticle> GetWplus_fromTPrimes() const;
      std::vector<reco::GenParticle> GetWminus_fromTPrimes() const;
      std::vector<reco::GenParticle> GetW_fromTPrimesandTPrimebars() const;
      std::vector<reco::GenParticle> GetWplus_fromBG() const;
      std::vector<reco::GenParticle> GetWminus_fromBG() const;
      std::vector<reco::GenParticle> GetWs_fromBG() const;
      
      std::vector<reco::GenParticle> GetBottom_fromTops() const;
      std::vector<reco::GenParticle> GetBottom_fromTopbars() const;
      std::vector<reco::GenParticle> GetBottom_fromTopsandTopbars() const;
      std::vector<reco::GenParticle> GetBottom_fromTPrimes() const;
      std::vector<reco::GenParticle> GetBottom_fromTPrimebars() const;
      std::vector<reco::GenParticle> GetBottom_fromTPrimesandTPrimebars() const;
      std::vector<reco::GenParticle> GetBottoms_fromBG() const;
      std::vector<reco::GenParticle> GetBottombars_fromBG() const;
      std::vector<reco::GenParticle> GetBottomsandBottombars_fromBG() const;
      
      std::vector<reco::GenParticle> GetTopDecayQuarks() const;
      std::vector<reco::GenParticle> GetTopBarDecayQuarks() const;
      std::vector<reco::GenParticle> GetTopDecayBottom() const;
      std::vector<reco::GenParticle> GetTopbarDecayBottom() const;
      std::vector<reco::GenParticle> GetTopandTopbarDecayBottoms() const;

      std::vector<reco::GenParticle> GetTPrimeDecayQuarks() const;
      std::vector<reco::GenParticle> GetTPrimebarDecayQuarks() const;
      std::vector<reco::GenParticle> GetTPrimeDecayBottom() const;
      std::vector<reco::GenParticle> GetTPrimebarDecayBottom() const;
      std::vector<reco::GenParticle> GetTPrimeandTPrimebarDecayBottoms() const;

      
      std::vector<reco::GenParticle> GetW_decay_products_fromTop() const;
      std::vector<reco::GenParticle> GetW_decay_products_fromTopbar() const;
      std::vector<reco::GenParticle> GetW_decay_products_fromTPrime() const;
      std::vector<reco::GenParticle> GetW_decay_products_fromTPrimebar() const;
      std::vector<reco::GenParticle> GetHiggsDecayProducts() const;
      std::vector<reco::GenParticle> GetZDecayProducts() const;


      void fillGenZPrimeTPrimeEvent(const std::vector<reco::GenParticle>& prunedGenParticles/*, int ZPrimeTPrimeID_*/);




 


      
      
   private:
//      virtual void beginStream(edm::StreamID) override;
//      virtual void produce(edm::Event&, const edm::EventSetup&) override;
//     virtual void endStream() override;

      std::vector<reco::GenParticle> tops_fromZprime;
      std::vector<reco::GenParticle> topbars_fromZprime;
      std::vector<reco::GenParticle> topsandtopbars_fromZprime;
      std::vector<reco::GenParticle> tops_fromTprime;
      std::vector<reco::GenParticle> topbars_fromTprime;
      std::vector<reco::GenParticle> topsandtopbars_fromTprime;
      std::vector<reco::GenParticle> tops_fromBG;
      std::vector<reco::GenParticle> topbars_fromBG;
      std::vector<reco::GenParticle> topsandtopbars_fromBG;
      
      std::vector<reco::GenParticle> TPrimes;
      std::vector<reco::GenParticle> TPrimebars;
      std::vector<reco::GenParticle> TPrimesandTPrimebars;
    
      std::vector<reco::GenParticle> ZPrimes;
      std::vector<reco::GenParticle> Zs;
      std::vector<reco::GenParticle> Higgs;

      std::vector<reco::GenParticle> wplus_fromTops;
      std::vector<reco::GenParticle> wminus_fromTops;
      std::vector<reco::GenParticle> Wfromtopsandtopbars;
      std::vector<reco::GenParticle> wplus_fromTPrimes;
      std::vector<reco::GenParticle> wminus_fromTPrimes;
      std::vector<reco::GenParticle> WfromTPrimesandTPrimebars;
      std::vector<reco::GenParticle> wplus_fromBG;
      std::vector<reco::GenParticle> wminus_fromBG;
      std::vector<reco::GenParticle> Ws_fromBG;   
      
      std::vector<reco::GenParticle> Bottom_fromTops;
      std::vector<reco::GenParticle> Bottombar_fromTops;
      std::vector<reco::GenParticle> Bottom_fromTopsandTopbars;
      std::vector<reco::GenParticle> Bottom_fromTPrimes;
      std::vector<reco::GenParticle> Bottombar_fromTPrimes;
      std::vector<reco::GenParticle> Bottom_fromTPrimesandTPrimebars;
      std::vector<reco::GenParticle> Bottom_fromBG;
      std::vector<reco::GenParticle> Bottombar_fromBG;
      std::vector<reco::GenParticle> Bottoms_fromBG;      
      
      std::vector<reco::GenParticle> top_decay_quarks;
      std::vector<reco::GenParticle> topbar_decay_quarks;
      std::vector<reco::GenParticle> top_decay_bottom;
      std::vector<reco::GenParticle> topbar_decay_bottom;
      std::vector<reco::GenParticle> topandtopbar_decay_bottoms;

      std::vector<reco::GenParticle> TPrime_decay_quarks;
      std::vector<reco::GenParticle> TPrimebar_decay_quarks;
      std::vector<reco::GenParticle> TPrime_decay_bottom;
      std::vector<reco::GenParticle> TPrimebar_decay_bottom;
      std::vector<reco::GenParticle> TPrimeandTPrimebar_decay_bottoms;



      std::vector<reco::GenParticle> wplus_fromTop_decay_products;
      std::vector<reco::GenParticle> wminus_fromTop_decay_products;
      std::vector<reco::GenParticle> wplus_fromTPrime_decay_products;
      std::vector<reco::GenParticle> wminus_fromTPrime_decay_products;
      std::vector<reco::GenParticle> Higgs_decay_products;
      std::vector<reco::GenParticle> Z_decay_products;
      std::vector<reco::GenParticle> ZPrime_decay_products;

      
      bool topIsHadronic;
      bool topbarIsHadronic;
      bool TPrimeIsHadronic;
      bool TPrimebarIsHadronic;
      bool HiggsIsHadronic;
      bool ZIsHadronic;
      bool AllHad;
      bool isZPrimeTPrime;
      bool isZPrimeTPrimeAllHad;
      bool isZPrimeTPrimeWbAllHad;
      bool isZPrimeTPrimeZtAllHad;
      bool isZPrimeTPrimeHtAllHad;

      bool isFilled;
/*      
      uint N_Top=0;
      uint N_Topbar=0;
      uint N_TPrime=0;
      uint N_TPrimebar=0;
      uint N_ZPrime=0;
*/

};





class ZPrimeToTPrimeAllHadProducer{
   public:
      ZPrimeToTPrimeAllHadProducer(edm::ConsumesCollector && iC);
      ZPrimeToTPrimeAllHad Produce(const edm::Event& iEvent, bool doGenHadronMatch, bool returnDummy);
      ~ZPrimeToTPrimeAllHadProducer();


   private:
  edm::EDGetTokenT< std::vector<reco::GenJet> > customGenJetsToken;  
  edm::EDGetTokenT<std::vector<reco::GenParticle> > prunedGenParticlesToken;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
      
      
      
      
      
      
      
};

#endif