#include "BoostedTTH/BoostedAnalyzer/interface/MECalculator.hpp"

MECalculator::MECalculator(){
  tthME.initProc("data/param_card.dat");
  ttbbME.initProc("data/param_card.dat");
  tthbbME.initProc("data/param_card.dat");
}


float MECalculator::GetTTHMEsq(const TLorentzVector & top_in, const TLorentzVector & topbar_in, const TLorentzVector & higgs_in){
  const double mtop=173.;
  const double mh=125.;
  TLorentzVector top(top_in.Px(),top_in.Py(),top_in.Pz(),sqrt(mtop*mtop+top_in.P()*top_in.P()));
  TLorentzVector topbar(topbar_in.Px(),topbar_in.Py(),topbar_in.Pz(),sqrt(mtop*mtop+topbar_in.P()*topbar_in.P()));
  TLorentzVector higgs(higgs_in.Px(),higgs_in.Py(),higgs_in.Pz(),sqrt(mh*mh+higgs_in.P()*higgs_in.P()));
  
  double p4_g1[4];
  double p4_g2[4];
  double p4_top[4];
  double p4_topbar[4];
  double p4_h[4];
  
  TLorentzVector tth=top+topbar+higgs;
  double cme = tth.M();
  TLorentzVector g1(0,0,cme/2,cme/2);
  TLorentzVector g2(0,0,-cme/2,cme/2);
  TVector3 boost=tth.BoostVector();
  g1.Boost(boost);
  g2.Boost(boost);
  

  p4_g1[0]=g1.E();
  p4_g1[1]=g1.Px();
  p4_g1[2]=g1.Py();
  p4_g1[3]=g1.Pz();
  p4_g2[0]=g2.E();
  p4_g2[1]=g2.Px();
  p4_g2[2]=g2.Py();
  p4_g2[3]=g2.Pz();
  p4_top[0]=top.E();
  p4_top[1]=top.Px();
  p4_top[2]=top.Py();
  p4_top[3]=top.Pz();
  p4_topbar[0]=topbar.E();
  p4_topbar[1]=topbar.Px();
  p4_topbar[2]=topbar.Py();
  p4_topbar[3]=topbar.Pz();
  p4_h[0]=higgs.E();
  p4_h[1]=higgs.Px();
  p4_h[2]=higgs.Py();
  p4_h[3]=higgs.Pz();

  vector<double*> momenta;
  momenta.push_back(p4_g1);
  momenta.push_back(p4_g2);
  momenta.push_back(p4_top);
  momenta.push_back(p4_topbar);
  momenta.push_back(p4_h);

  tthME.setMomenta(momenta);

  tthME.sigmaKin();

  const double* matrix_elements = tthME.getMatrixElements();

  assert(tthME.nprocesses==1);
  return matrix_elements[0];
}

float MECalculator::GetTTHBBMEsq(const TLorentzVector & top_in, const TLorentzVector & topbar_in, const TLorentzVector & b_in, const TLorentzVector & bbar_in){
  const double mtop=173.;
  const double mh=125.;
  TLorentzVector top(top_in.Px(),top_in.Py(),top_in.Pz(),sqrt(mtop*mtop+top_in.P()*top_in.P()));
  TLorentzVector topbar(topbar_in.Px(),topbar_in.Py(),topbar_in.Pz(),sqrt(mtop*mtop+topbar_in.P()*topbar_in.P()));
  // ignore the b-jet masses
  TLorentzVector b_massless(b_in.Px(),b_in.Py(),b_in.Pz(),fabs(b_in.P()));
  TLorentzVector bbar_massless(bbar_in.Px(),bbar_in.Py(),bbar_in.Pz(),fabs(bbar_in.P()));
  // scale b's so that the dijet mass is 125 GeV
  double mh_current=(b_massless+bbar_massless).M();
  b_massless*=(mh/mh_current);
  bbar_massless*=(mh/mh_current);
  TLorentzVector b;
  TLorentzVector bbar;
  // plug in b-quark mass
  b.SetPtEtaPhiM(b_massless.Pt(),b_massless.Eta(),b_massless.Phi(),b_massless.M());
  bbar.SetPtEtaPhiM(bbar_massless.Pt(),bbar_massless.Eta(),bbar_massless.Phi(),bbar_massless.M());
  
  double p4_g1[4];
  double p4_g2[4];
  double p4_top[4];
  double p4_topbar[4];
  double p4_b[4];
  double p4_bbar[4];
  
  TLorentzVector tthbb=top+topbar+b+bbar;
  double cme = tthbb.M();
  TLorentzVector g1(0,0,cme/2,cme/2);
  TLorentzVector g2(0,0,-cme/2,cme/2);
  TVector3 boost=tthbb.BoostVector();
  g1.Boost(boost);
  g2.Boost(boost);
 
  p4_g1[0]=g1.E();
  p4_g1[1]=g1.Px();
  p4_g1[2]=g1.Py();
  p4_g1[3]=g1.Pz();
  p4_g2[0]=g2.E();
  p4_g2[1]=g2.Px();
  p4_g2[2]=g2.Py();
  p4_g2[3]=g2.Pz();
  p4_top[0]=top.E();
  p4_top[1]=top.Px();
  p4_top[2]=top.Py();
  p4_top[3]=top.Pz();
  p4_topbar[0]=topbar.E();
  p4_topbar[1]=topbar.Px();
  p4_topbar[2]=topbar.Py();
  p4_topbar[3]=topbar.Pz();
  p4_b[0]=b.E();
  p4_b[1]=b.Px();
  p4_b[2]=b.Py();
  p4_b[3]=b.Pz();
  p4_bbar[0]=bbar.E();
  p4_bbar[1]=bbar.Px();
  p4_bbar[2]=bbar.Py();
  p4_bbar[3]=bbar.Pz();

  vector<double*> momenta;
  momenta.push_back(p4_g1);
  momenta.push_back(p4_g2);
  momenta.push_back(p4_top);
  momenta.push_back(p4_topbar);
  momenta.push_back(p4_b);
  momenta.push_back(p4_bbar);

  tthbbME.setMomenta(momenta);

  tthbbME.sigmaKin();

  const double* matrix_elements = tthbbME.getMatrixElements();

  assert(tthbbME.nprocesses==1);
  return matrix_elements[0];
}

float MECalculator::GetTTBBMEsq_onshell(const TLorentzVector & top_in, const TLorentzVector & topbar_in, const TLorentzVector & b_in, const TLorentzVector & bbar_in){
  const double mtop=173.;
  const double mh=125.;
  TLorentzVector top(top_in.Px(),top_in.Py(),top_in.Pz(),sqrt(mtop*mtop+top_in.P()*top_in.P()));
  TLorentzVector topbar(topbar_in.Px(),topbar_in.Py(),topbar_in.Pz(),sqrt(mtop*mtop+topbar_in.P()*topbar_in.P()));
  // ignore the b-jet masses
  TLorentzVector b_massless(b_in.Px(),b_in.Py(),b_in.Pz(),fabs(b_in.P()));
  TLorentzVector bbar_massless(bbar_in.Px(),bbar_in.Py(),bbar_in.Pz(),fabs(bbar_in.P()));
  // scale b's so that the dijet mass is 125 GeV
  double mh_current=(b_massless+bbar_massless).M();
  b_massless*=(mh/mh_current);
  bbar_massless*=(mh/mh_current);
  TLorentzVector b;
  TLorentzVector bbar;
  // plug in b-quark mass
  b.SetPtEtaPhiM(b_massless.Pt(),b_massless.Eta(),b_massless.Phi(),b_massless.M());
  bbar.SetPtEtaPhiM(bbar_massless.Pt(),bbar_massless.Eta(),bbar_massless.Phi(),bbar_massless.M());
  
  double p4_g1[4];
  double p4_g2[4];
  double p4_top[4];
  double p4_topbar[4];
  double p4_b[4];
  double p4_bbar[4];
  
  TLorentzVector ttbb=top+topbar+b+bbar;
  double cme = ttbb.M();
  TLorentzVector g1(0,0,cme/2,cme/2);
  TLorentzVector g2(0,0,-cme/2,cme/2);
  TVector3 boost=ttbb.BoostVector();
  g1.Boost(boost);
  g2.Boost(boost);
 
  p4_g1[0]=g1.E();
  p4_g1[1]=g1.Px();
  p4_g1[2]=g1.Py();
  p4_g1[3]=g1.Pz();
  p4_g2[0]=g2.E();
  p4_g2[1]=g2.Px();
  p4_g2[2]=g2.Py();
  p4_g2[3]=g2.Pz();
  p4_top[0]=top.E();
  p4_top[1]=top.Px();
  p4_top[2]=top.Py();
  p4_top[3]=top.Pz();
  p4_topbar[0]=topbar.E();
  p4_topbar[1]=topbar.Px();
  p4_topbar[2]=topbar.Py();
  p4_topbar[3]=topbar.Pz();
  p4_b[0]=b.E();
  p4_b[1]=b.Px();
  p4_b[2]=b.Py();
  p4_b[3]=b.Pz();
  p4_bbar[0]=bbar.E();
  p4_bbar[1]=bbar.Px();
  p4_bbar[2]=bbar.Py();
  p4_bbar[3]=bbar.Pz();

  vector<double*> momenta;
  momenta.push_back(p4_g1);
  momenta.push_back(p4_g2);
  momenta.push_back(p4_top);
  momenta.push_back(p4_topbar);
  momenta.push_back(p4_b);
  momenta.push_back(p4_bbar);

  ttbbME.setMomenta(momenta);

  ttbbME.sigmaKin();

  const double* matrix_elements = ttbbME.getMatrixElements();

  assert(ttbbME.nprocesses==1);
  return matrix_elements[0];
}


float MECalculator::GetTTBBMEsq_offshell(const TLorentzVector & top_in, const TLorentzVector & topbar_in, const TLorentzVector & b_in, const TLorentzVector & bbar_in){
  const double mtop=173.;
  const double mb=4.7;
  TLorentzVector top(top_in.Px(),top_in.Py(),top_in.Pz(),sqrt(mtop*mtop+top_in.P()*top_in.P()));
  TLorentzVector topbar(topbar_in.Px(),topbar_in.Py(),topbar_in.Pz(),sqrt(mtop*mtop+topbar_in.P()*topbar_in.P()));
  
  TLorentzVector b(b_in.Px(),b_in.Py(),b_in.Pz(),sqrt(mb*mb+b_in.P()*b_in.P()));
  TLorentzVector bbar(bbar_in.Px(),bbar_in.Py(),bbar_in.Pz(),sqrt(mb*mb+bbar_in.P()*bbar_in.P()));
  
  double p4_g1[4];
  double p4_g2[4];
  double p4_top[4];
  double p4_topbar[4];
  double p4_b[4];
  double p4_bbar[4];
  
  TLorentzVector ttbb=top+topbar+b+bbar;
  double cme = ttbb.M();
  TLorentzVector g1(0,0,cme/2,cme/2);
  TLorentzVector g2(0,0,-cme/2,cme/2);
  TVector3 boost=ttbb.BoostVector();
  g1.Boost(boost);
  g2.Boost(boost);
 
  p4_g1[0]=g1.E();
  p4_g1[1]=g1.Px();
  p4_g1[2]=g1.Py();
  p4_g1[3]=g1.Pz();
  p4_g2[0]=g2.E();
  p4_g2[1]=g2.Px();
  p4_g2[2]=g2.Py();
  p4_g2[3]=g2.Pz();
  p4_top[0]=top.E();
  p4_top[1]=top.Px();
  p4_top[2]=top.Py();
  p4_top[3]=top.Pz();
  p4_topbar[0]=topbar.E();
  p4_topbar[1]=topbar.Px();
  p4_topbar[2]=topbar.Py();
  p4_topbar[3]=topbar.Pz();
  p4_b[0]=b.E();
  p4_b[1]=b.Px();
  p4_b[2]=b.Py();
  p4_b[3]=b.Pz();
  p4_bbar[0]=bbar.E();
  p4_bbar[1]=bbar.Px();
  p4_bbar[2]=bbar.Py();
  p4_bbar[3]=bbar.Pz();

  vector<double*> momenta;
  momenta.push_back(p4_g1);
  momenta.push_back(p4_g2);
  momenta.push_back(p4_top);
  momenta.push_back(p4_topbar);
  momenta.push_back(p4_b);
  momenta.push_back(p4_bbar);

  ttbbME.setMomenta(momenta);

  ttbbME.sigmaKin();

  const double* matrix_elements = ttbbME.getMatrixElements();

  assert(ttbbME.nprocesses==1);
  return matrix_elements[0];
}
