#include "BoostedTTH/BoostedAnalyzer/interface/GenTopEvent.hpp"

GenTopEvent::GenTopEvent (){
  isFilled=false;
}
GenTopEvent::~GenTopEvent(){}

bool GenTopEvent::IsFilled() const{
  return isFilled;
}
void GenTopEvent::Fill(const std::vector<reco::GenParticle>& prunedGenParticles){
  for(auto p=prunedGenParticles.begin(); p!=prunedGenParticles.end(); p++){
    if (abs(p->pdgId())==6){
      bool lastTop=true;
      for(uint i=0;i<p->numberOfDaughters();i++){
	if (abs(p->daughter(i)->pdgId())==6)
	  lastTop=false;
      }
      if(lastTop){
	if(p->pdgId()==6) top=*p;
	if(p->pdgId()==-6) topbar=*p;
	bool setTDecay=false;
	bool setTBarDecay=false;
	for(uint i=0;i<p->numberOfDaughters();i++){
	  if(p->pdgId()==6 && abs(p->daughter(i)->pdgId())<6){
	    if(setTDecay) std::cerr << "GenTopEvent: error 1"<<std::endl;
	    top_decay_quark=*(reco::GenParticle*)p->daughter(i);
	    setTDecay=true;
	  }
	  if(p->pdgId()==-6 && abs(p->daughter(i)->pdgId())<6){
	    if(setTBarDecay) std::cerr << "GenTopEvent: error 1"<<std::endl;
	    topbar_decay_quark=*(reco::GenParticle*)p->daughter(i);
	    setTBarDecay=true;
	  }
	}
      }
    }
  
    if (abs(p->pdgId())==24){
      bool lastW=true;
      for(uint i=0;i<p->numberOfDaughters();i++){
	if (abs(p->daughter(i)->pdgId())==24)
	  lastW=false;
      }
      bool fromT=false;
      const reco::Candidate* mother=&(*p);
      while(mother!=0 && abs(mother->pdgId())==24){
	if (abs(mother->mother()->pdgId())==6){
	  fromT=true;
	  break;
	}
	else mother=mother->mother();
	
      }
      if(lastW&&fromT){
	if(p->pdgId()==24) wplus=*p;
	if(p->pdgId()==-24) wminus=*p;
	for(uint i=0;i<p->numberOfDaughters();i++){
	  if(p->pdgId()==24 && abs(p->daughter(i)->pdgId())<=16){
	    wplus_decay_products.push_back(*(reco::GenParticle*)p->daughter(i));
	  }
	  if(p->pdgId()==-24 && abs(p->daughter(i)->pdgId())<=16){
	    wminus_decay_products.push_back(*(reco::GenParticle*)p->daughter(i));
	  }
	}
      }
    }

    if (abs(p->pdgId())==25){
      bool lastH=true;
      for(uint i=0;i<p->numberOfDaughters();i++){
	if (abs(p->daughter(i)->pdgId())==25)
	  lastH=false;
      }
      if(lastH){
	higgs=*p;
	for(uint i=0;i<p->numberOfDaughters();i++){
	  if(p->pdgId()==25 && abs(p->daughter(i)->pdgId())!=25){
	    higgs_decay_products.push_back(*(reco::GenParticle*)p->daughter(i));
	  }
	}
      }
    }

  }
  if(wminus_decay_products.size()!=2 || wplus_decay_products.size()!=2) std::cerr << "GenTopEvent: error 2"<<std::endl;
  if(top.energy()<1||topbar.energy()<1||wplus.energy()<1||wminus.energy()<1||top_decay_quark.energy()<1||topbar_decay_quark.energy()<1) std::cerr << "GenTopEvent: error 4"<<std::endl;

  int nquarks_from_wplus=0;
  for(auto p=wplus_decay_products.begin(); p!=wplus_decay_products.end();p++){
    if(abs(p->pdgId())<6) nquarks_from_wplus++;
  }
  int nquarks_from_wminus=0;
  for(auto p=wminus_decay_products.begin(); p!=wminus_decay_products.end();p++){
    if(abs(p->pdgId())<6) nquarks_from_wminus++;
  }
  topIsHadronic=nquarks_from_wplus==2;
  topbarIsHadronic=nquarks_from_wminus==2;
  isFilled=true;
}

void GenTopEvent::Print() const{
  std::cout << "top" << std::endl;
  PrintParticle(GetTop());
  std::cout << "top decay quark" << std::endl;
  PrintParticle(GetTopDecayQuark());
  std::cout << "higgs" << std::endl;
  PrintParticle(GetHiggs());
  std::cout << "higgs decay products" << std::endl;
  PrintParticles(GetHiggsDecayProducts());
  std::cout << "topbar" << std::endl;
  PrintParticle(GetTopBar());
  std::cout << "topbar decay quark" << std::endl;
  PrintParticle(GetTopBarDecayQuark());
  std::cout << "wplus" << std::endl;
  PrintParticle(GetWplus());
  std::cout << "wplus decay products" << std::endl;
  PrintParticles(GetWplusDecayProducts());
  std::cout << "wminus" << std::endl;
  PrintParticle(GetWminus());
  std::cout << "wminus decay products" << std::endl;
  PrintParticles(GetWminusDecayProducts());
  std::cout << "all top hads" << std::endl;
  PrintParticles(GetAllTopHads());
  std::cout << "all W hads" << std::endl;
  PrintParticles(GetAllWhads());
  std::cout << "all tophad bs" << std::endl;
  PrintParticles(GetAllTopHadDecayQuarks());
  std::cout << "all tophad W quarks" << std::endl;
  PrintParticles(GetAllWQuarks());
  std::cout << "all tophad W anti quarks" << std::endl;
  PrintParticles(GetAllWAntiQuarks());
  std::cout << "all top leps" << std::endl;
  PrintParticles(GetAllTopLeps());
  std::cout << "all w leps" << std::endl;
  PrintParticles(GetAllWleps());
  std::cout << "all top lep bs" << std::endl;
  PrintParticles(GetAllTopLepDecayQuarks());
  std::cout << "all leptons" << std::endl;
  PrintParticles(GetAllLeptons());
  std::cout << "all neutrinos" << std::endl;
  PrintParticles(GetAllNeutrinos());
}
void GenTopEvent::PrintParticle(reco::GenParticle p) const{
  std::cout << "pdgId: " << p.pdgId() << ", pt: " << p.pt() << ", eta: " << p.eta() << ", phi: " << p.phi() << std::endl;
}
void GenTopEvent::PrintParticles(std::vector<reco::GenParticle> ps) const{
  for(auto p=ps.begin();p!=ps.end();p++){
    PrintParticle(*p);
  }
}
reco::GenParticle GenTopEvent::GetHiggs() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  return higgs;
}
reco::GenParticle GenTopEvent::GetTop() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  return top;
}
reco::GenParticle GenTopEvent::GetTopBar() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  return topbar;
}
reco::GenParticle GenTopEvent::GetTopHad() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  if(topIsHadronic&&!topbarIsHadronic) return top;
  else if(!topIsHadronic&&topbarIsHadronic) return topbar;
  else{
    std::cerr <<"hadronic/leptonic function called in GenTopEvent, but not a semileptonic event" << std::endl;
    return reco::GenParticle();      
  }
}
reco::GenParticle GenTopEvent::GetTopLep() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  if(topIsHadronic&&!topbarIsHadronic) return topbar;
  else if(!topIsHadronic&&topbarIsHadronic) return top;
  else{
    std::cerr <<"hadronic/leptonic function called in GenTopEvent, but not a semileptonic event" << std::endl;
    return reco::GenParticle();      
  }
}
reco::GenParticle GenTopEvent::GetWplus() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  return wplus;
}
reco::GenParticle GenTopEvent::GetWminus() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  return wminus;
}
reco::GenParticle GenTopEvent::GetWhad() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  if(topIsHadronic&&!topbarIsHadronic) return wplus;
  else if(!topIsHadronic&&topbarIsHadronic) return wminus;
  else{
    std::cerr <<"hadronic/leptonic function called in GenTopEvent, but not a semileptonic event" << std::endl;
    return reco::GenParticle();      
  }
}
reco::GenParticle GenTopEvent::GetWlep() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  if(topIsHadronic&&!topbarIsHadronic) return wminus;
  else if(!topIsHadronic&&topbarIsHadronic) return wplus;
  else{
    std::cerr <<"hadronic/leptonic function called in GenTopEvent, but not a semileptonic event" << std::endl;
    return reco::GenParticle();      
  }
}
std::vector<reco::GenParticle> GenTopEvent::GetWLeptons() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  if(topIsHadronic&&!topbarIsHadronic) return wminus_decay_products;
  else if(!topIsHadronic&&topbarIsHadronic) return wplus_decay_products;
  else{
    std::cerr <<"hadronic/leptonic function called in GenTopEvent, but not a semileptonic event" << std::endl;
    return std::vector<reco::GenParticle>();
  }
}
reco::GenParticle GenTopEvent::GetLepton() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  if(topIsHadronic&&!topbarIsHadronic){
    for(auto p=wminus_decay_products.begin();p!=wminus_decay_products.end();p++){
      if(p->pdgId()==-11||p->pdgId()==-13||p->pdgId()==-15)
	return *p;
    }
    std::cerr <<"no lepton found" <<std::endl;
    return reco::GenParticle();
  }
  else if(!topIsHadronic&&topbarIsHadronic){
    for(auto p=wplus_decay_products.begin();p!=wplus_decay_products.end();p++){
      if(p->pdgId()==11||p->pdgId()==13||p->pdgId()==15)
	return *p;
    }
    std::cerr <<"no lepton found" <<std::endl;
    return reco::GenParticle();
  }
  std::cerr <<"hadronic/leptonic function called in GenTopEvent, but not a semileptonic event" << std::endl;
  return reco::GenParticle();
  
}

reco::GenParticle GenTopEvent::GetNeutrino() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  if(topIsHadronic&&!topbarIsHadronic){
    for(auto p=wminus_decay_products.begin();p!=wminus_decay_products.end();p++){
      if(abs(p->pdgId())==12||abs(p->pdgId())==14||abs(p->pdgId())==16)
	return *p;
    }
    std::cerr <<"no lepton found" <<std::endl;
    return reco::GenParticle();
  }
  else if(!topIsHadronic&&topbarIsHadronic){
    for(auto p=wplus_decay_products.begin();p!=wplus_decay_products.end();p++){
      if(abs(p->pdgId())==12||abs(p->pdgId())==14||abs(p->pdgId())==16)
	return *p;
    }
    std::cerr <<"no lepton found" <<std::endl;
    return reco::GenParticle();
  }
  std::cerr <<"hadronic/leptonic function called in GenTopEvent, but not a semileptonic event" << std::endl;
  return reco::GenParticle();  
}

std::vector<reco::GenParticle>  GenTopEvent::GetWQuarks() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  if(topIsHadronic&&!topbarIsHadronic) return wplus_decay_products;
  else if(!topIsHadronic&&topbarIsHadronic) return wminus_decay_products;
  else{
    std::cerr <<"hadronic/leptonic function called in GenTopEvent, but not a semileptonic event" << std::endl;
    return std::vector<reco::GenParticle>();
  }
}
std::vector<reco::GenParticle> GenTopEvent::GetHiggsDecayProducts() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  return higgs_decay_products;
}
reco::GenParticle GenTopEvent::GetTopDecayQuark() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  return top_decay_quark;
}
reco::GenParticle GenTopEvent::GetTopBarDecayQuark() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  return topbar_decay_quark;
}
reco::GenParticle GenTopEvent::GetTopHadDecayQuark() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  if(topIsHadronic&&!topbarIsHadronic) return top_decay_quark;
  else if(!topIsHadronic&&topbarIsHadronic) return topbar_decay_quark;
  else{
    std::cerr <<"hadronic/leptonic function called in GenTopEvent, but not a semileptonic event" << std::endl;
    return reco::GenParticle();      
  }
}
reco::GenParticle GenTopEvent::GetTopLepDecayQuark() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  if(topIsHadronic&&!topbarIsHadronic) return topbar_decay_quark;
  else if(!topIsHadronic&&topbarIsHadronic) return top_decay_quark;
  else{
    std::cerr <<"hadronic/leptonic function called in GenTopEvent, but not a semileptonic event" << std::endl;
    return reco::GenParticle();      
  }
}
std::vector<reco::GenParticle> GenTopEvent::GetQuarks() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  std::vector<reco::GenParticle> quarks;
  quarks.push_back(top_decay_quark);
  quarks.push_back(topbar_decay_quark);
  for(auto p=wplus_decay_products.begin();p!=wplus_decay_products.end();p++){
    quarks.push_back(*p);
  }
  for(auto p=wminus_decay_products.begin();p!=wminus_decay_products.end();p++){
    quarks.push_back(*p);
  }
  for(auto p=higgs_decay_products.begin();p!=higgs_decay_products.end();p++){
    quarks.push_back(*p);
  }
  return quarks;
}
std::vector<reco::GenParticle> GenTopEvent::GetWplusDecayProducts() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  return wplus_decay_products;
}
std::vector<reco::GenParticle> GenTopEvent::GetWminusDecayProducts() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  return wminus_decay_products;
}
// always top first, tobar second if both exist
std::vector<reco::GenParticle> GenTopEvent::GetAllTopHads() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  std::vector<reco::GenParticle> tophads;
  if(isFilled&&topIsHadronic) tophads.push_back(top);
  if(isFilled&&topbarIsHadronic) tophads.push_back(topbar);
  return tophads;
}
// always top first, tobar second if both exist
std::vector<reco::GenParticle> GenTopEvent::GetAllTopLeps() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  std::vector<reco::GenParticle> topleps;
  if(isFilled&&!topIsHadronic) topleps.push_back(top);
  if(isFilled&&!topbarIsHadronic) topleps.push_back(topbar);
  return topleps;
}
// always top first, tobar second if both exist
std::vector<reco::GenParticle> GenTopEvent::GetAllTopHadDecayQuarks() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  std::vector<reco::GenParticle> quarks;
  if(isFilled&&topIsHadronic) quarks.push_back(top_decay_quark);
  if(isFilled&&topbarIsHadronic) quarks.push_back(topbar_decay_quark);
  return quarks;
}
// always top first, tobar second if both exist
std::vector<reco::GenParticle> GenTopEvent::GetAllTopLepDecayQuarks() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  std::vector<reco::GenParticle> quarks;
  if(isFilled&&!topIsHadronic) quarks.push_back(top_decay_quark);
  if(isFilled&&!topbarIsHadronic) quarks.push_back(topbar_decay_quark);
  return quarks;
}
// always top first, tobar second if both exist
std::vector<reco::GenParticle> GenTopEvent::GetAllWhads() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  std::vector<reco::GenParticle> ws;
  if(isFilled&&topIsHadronic) ws.push_back(wplus);
  if(isFilled&&topbarIsHadronic) ws.push_back(wminus);
  return ws;
}
// always top first, tobar second if both exist
std::vector<reco::GenParticle> GenTopEvent::GetAllWleps() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  std::vector<reco::GenParticle> ws;
  if(isFilled&&!topIsHadronic) ws.push_back(wplus);
  if(isFilled&&!topbarIsHadronic) ws.push_back(wminus);
  return ws;
}
// always top first, tobar second if both exist
std::vector<reco::GenParticle> GenTopEvent::GetAllLeptons() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  std::vector<reco::GenParticle> leptons;
  for(auto p=wplus_decay_products.begin();isFilled&& p!=wplus_decay_products.end();p++){
    if(abs(p->pdgId())==11||abs(p->pdgId())==13||abs(p->pdgId())==15) leptons.push_back(*p);
  }
  for(auto p=wminus_decay_products.begin();isFilled&& p!=wminus_decay_products.end();p++){
    if(abs(p->pdgId())==11||abs(p->pdgId())==13||abs(p->pdgId())==15) leptons.push_back(*p);
  }
  return leptons;
}
// always top first, tobar second if both exist
std::vector<reco::GenParticle> GenTopEvent::GetAllNeutrinos() const{
  std::vector<reco::GenParticle> neutrinos;
  for(auto p=wplus_decay_products.begin(); isFilled&&p!=wplus_decay_products.end();p++){
    if(abs(p->pdgId())==12||abs(p->pdgId())==14||abs(p->pdgId())==16) neutrinos.push_back(*p);
  }
  for(auto p=wminus_decay_products.begin(); isFilled&&p!=wminus_decay_products.end();p++){
    if(abs(p->pdgId())==12||abs(p->pdgId())==14||abs(p->pdgId())==16) neutrinos.push_back(*p);
  }
  return neutrinos;
}
// always top first, tobar second if both exist
std::vector<reco::GenParticle> GenTopEvent::GetAllWQuarks() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  std::vector<reco::GenParticle> quarks;
  for(auto p=wplus_decay_products.begin();isFilled&& p!=wplus_decay_products.end();p++){
    if(p->pdgId()>0&&p->pdgId()<6) quarks.push_back(*p);
  }
  for(auto p=wminus_decay_products.begin();isFilled&& p!=wminus_decay_products.end();p++){
    if(p->pdgId()>0&&p->pdgId()<6) quarks.push_back(*p);
  }
  return quarks;
}
// always top first, tobar second if both exist
std::vector<reco::GenParticle> GenTopEvent::GetAllWAntiQuarks() const{
  if(!isFilled) std::cerr << "Trying to access GenTopEvent but it is not filled" << std::endl;
  std::vector<reco::GenParticle> quarks;
  for(auto p=wplus_decay_products.begin();isFilled&& p!=wplus_decay_products.end();p++){
    if(p->pdgId()<0&&p->pdgId()>-6) quarks.push_back(*p);
  }
  for(auto p=wminus_decay_products.begin();isFilled&& p!=wminus_decay_products.end();p++){
    if(p->pdgId()<0&&p->pdgId()>-6) quarks.push_back(*p);
  }
  return quarks;
}

std::vector<math::XYZTLorentzVector> GenTopEvent::GetAllTopHadVecs() const{
  return GetLVs(GetAllTopHads());
}
std::vector<math::XYZTLorentzVector> GenTopEvent::GetAllTopLepVecs() const{
  return GetLVs(GetAllTopLeps());
}
std::vector<math::XYZTLorentzVector> GenTopEvent::GetAllTopHadDecayQuarkVecs() const{
  return GetLVs(GetAllTopHadDecayQuarks());
}
std::vector<math::XYZTLorentzVector> GenTopEvent::GetAllTopLepDecayQuarkVecs() const{
  return GetLVs(GetAllTopLepDecayQuarks());
}
std::vector<math::XYZTLorentzVector> GenTopEvent::GetAllWhadVecs() const{
  return GetLVs(GetAllWhads());
}
std::vector<math::XYZTLorentzVector> GenTopEvent::GetAllWlepVecs() const{
  return GetLVs(GetAllWleps());
}
std::vector<math::XYZTLorentzVector> GenTopEvent::GetAllLeptonVecs() const{
  return GetLVs(GetAllLeptons());
}
std::vector<math::XYZTLorentzVector> GenTopEvent::GetAllNeutrinoVecs() const{
  return GetLVs(GetAllNeutrinos());
}
std::vector<math::XYZTLorentzVector> GenTopEvent::GetAllWQuarkVecs() const{
  return GetLVs(GetAllWQuarks());
}
std::vector<math::XYZTLorentzVector> GenTopEvent::GetAllWAntiQuarkVecs() const{
  return GetLVs(GetAllWAntiQuarks());
}

math::XYZTLorentzVector GenTopEvent::GetHiggsVec() const{
  return GetLV(GetHiggs());
}
math::XYZTLorentzVector GenTopEvent::GetTopVec() const{
  return GetLV(GetTop());
}
math::XYZTLorentzVector GenTopEvent::GetTopBarVec() const{
  return GetLV(GetTopBar());
}
math::XYZTLorentzVector GenTopEvent::GetTopHadVec() const{
  return GetLV(GetTopHad());
}
math::XYZTLorentzVector GenTopEvent::GetTopLepVec() const{
  return GetLV(GetTopLep());
}
math::XYZTLorentzVector GenTopEvent::GetWplusVec() const{
  return GetLV(GetWplus());
}
math::XYZTLorentzVector GenTopEvent::GetWminusVec() const{
  return GetLV(GetWminus());
}
math::XYZTLorentzVector GenTopEvent::GetWhadVec() const{
  return GetLV(GetWhad());
}
math::XYZTLorentzVector GenTopEvent::GetWlepVec() const{
  return GetLV(GetWlep());
}
math::XYZTLorentzVector GenTopEvent::GetLeptonVec() const{
  return GetLV(GetLepton());
}
math::XYZTLorentzVector GenTopEvent::GetNeutrinoVec() const{
  return GetLV(GetNeutrino());
}
std::vector<math::XYZTLorentzVector> GenTopEvent::GetQuarkVecs() const{
  return GetLVs(GetQuarks());
}
std::vector<math::XYZTLorentzVector> GenTopEvent::GetHiggsDecayProductVecs() const{
  return GetLVs(GetHiggsDecayProducts());
}
math::XYZTLorentzVector GenTopEvent::GetTopDecayQuarkVec() const{
  return GetLV(GetTopDecayQuark());
}
math::XYZTLorentzVector GenTopEvent::GetTopBarDecayQuarkVec() const{
  return GetLV(GetTopBarDecayQuark());
}
math::XYZTLorentzVector GenTopEvent::GetTopHadDecayQuarkVec() const{
  return GetLV(GetTopHadDecayQuark());
}
math::XYZTLorentzVector GenTopEvent::GetTopLepDecayQuarkVec() const{
  return GetLV(GetTopLepDecayQuark());
}
std::vector<math::XYZTLorentzVector> GenTopEvent::GetWLeptonsVecs() const{
  return GetLVs(GetWLeptons());
}
std::vector<math::XYZTLorentzVector> GenTopEvent::GetWQuarksVecs() const{
  return GetLVs(GetWQuarks());
}
std::vector<math::XYZTLorentzVector> GenTopEvent::GetWplusDecayProductsVecs() const{
  return GetLVs(GetWplusDecayProducts());
}
std::vector<math::XYZTLorentzVector> GenTopEvent::GetWminusDecayProductsVecs() const{
  return GetLVs(GetWminusDecayProducts());
}


bool GenTopEvent::IsAllHadron() const{
  return topIsHadronic&&topbarIsHadronic;
}
bool GenTopEvent::IsDiLepton() const{
  return !topIsHadronic&&!topbarIsHadronic;
}
bool GenTopEvent::IsSemiLepton() const{
  return (topIsHadronic&&!topbarIsHadronic)||(!topIsHadronic&&topbarIsHadronic);
}
math::XYZTLorentzVector GenTopEvent::GetLV(const reco::GenParticle& p) const{
  return math::XYZTLorentzVector(p.px(),p.py(),p.pz(),p.energy());
}

std::vector<math::XYZTLorentzVector> GenTopEvent::GetLVs(const std::vector<reco::GenParticle>& ps) const{
  std::vector<math::XYZTLorentzVector> vecs;
  for(auto p=ps.begin();p!=ps.end();p++){
    vecs.push_back(GetLV(*p));
  }
  return vecs;
}

