#include "BoostedTTH/TTHReconstruction/interface/ReconstructionMCMatching.hpp"

using namespace std;
ReconstructionMCMatching::ReconstructionMCMatching():maxdr(0.4),setupMC(0)
{}

void ReconstructionMCMatching::Setup(TLorentzVector b_had_, TLorentzVector q1_, TLorentzVector q2_, TLorentzVector b_lep_, TLorentzVector lep_, TLorentzVector nu_, TLorentzVector b1_, TLorentzVector b2_){
  b1=b1_;
  b2=b2_;
  b_had=b_had_;
  q1=q1_;
  q2=q2_;
  b_lep=b_lep_;
  lep=lep_;
  nu=nu_;
  setupMC=2;
}
void ReconstructionMCMatching::Setup(TLorentzVector b_had_, TLorentzVector q1_, TLorentzVector q2_, TLorentzVector b_lep_, TLorentzVector lep_, TLorentzVector nu_){
  b_had=b_had_;
  q1=q1_;
  q2=q2_;
  b_lep=b_lep_;
  lep=lep_;
  nu=nu_;
  setupMC=1;
}


bool ReconstructionMCMatching::MatchH(Interpretation& i){
  if(setupMC<2){
    cerr << "need to setup mc matching (incl Higgs) first!" << endl;
    return false;
  }
  bool matchH=b1.E()>1.&&b2.E()>1.&&i.B1().E()>1.&&i.B2().E()>1.
    && ( (b1.DeltaR(i.B1())<maxdr && b2.DeltaR(i.B2())<maxdr) || (b1.DeltaR(i.B2())<maxdr && b2.DeltaR(i.B1())<maxdr) );
  return matchH;
}
int ReconstructionMCMatching::MatchNH(Interpretation& i){
  if(setupMC<2){
    cerr << "need to setup mc matching (incl Higgs) first!" << endl;
    return false;
  }
  int nQ=0;
  if(b1.E()>1.&&b2.E()>1.&&i.B1().E()>1.&&i.B2().E()>1.){
    if(b1.DeltaR(i.B1())<maxdr || b2.DeltaR(i.B1())<maxdr) nQ++;
    if(b1.DeltaR(i.B2())<maxdr || b2.DeltaR(i.B2())<maxdr) nQ++;
  }
  return nQ;
}
int ReconstructionMCMatching::MatchNWHad(Interpretation& i){
  if(setupMC<1){
    cerr << "need to setup mc matching (incl Higgs) first!" << endl;
    return false;
  }
  int nQ=0;
  if(q1.E()>1.&&q2.E()>1.&&i.Q1().E()>1.&&i.Q2().E()>1.){
    if(q1.DeltaR(i.Q1())<maxdr || q2.DeltaR(i.Q1())<maxdr) nQ++;
    if(q1.DeltaR(i.Q2())<maxdr || q2.DeltaR(i.Q2())<maxdr) nQ++;
  }
  return nQ++;
}


bool ReconstructionMCMatching::MatchWHad(Interpretation& i){
  if(setupMC==0){
    cerr << "need to setup mc matching first!" << endl;
    return false;
  }
  bool matchWhad=q1.E()>1.&&q2.E()>1.&&i.Q1().E()>1.&&i.Q2().E()>1.
		   && 
    ( (q1.DeltaR(i.Q1())<maxdr && q2.DeltaR(i.Q2())<maxdr) || (q1.DeltaR(i.Q2())<maxdr && q2.DeltaR(i.Q1())<maxdr) );
  //  cout << "1 " << q1.DeltaR(i.Q1()) << ", " <<  q2.DeltaR(i.Q2()) << " 2 " << q2.DeltaR(i.Q1()) << ", " <<  q1.DeltaR(i.Q2()) << endl;
  //  cout << "q1 pt " << i.Q1().Pt() << " q2 pt " << i.Q2().Pt()  << " blep pt " << i.BLep().Pt()   << " bhad pt " << i.BHad().Pt() << " nu pz " << i.Nu().Pz() << endl;
  //  if(matchWhad)   cout << "matched" << endl;
  //  else cout << "not matched" << endl;
  return matchWhad;
}
bool ReconstructionMCMatching::MatchBLep(Interpretation& i){
  if(setupMC==0){
    cerr << "need to setup mc matching first!" << endl;
    return false;
  }
  //  cout << "dr blep " << b_lep.DeltaR(i.BLep()) << endl;
  bool matchBlep=b_lep.E()>1.&&i.BLep().E()>1.&&b_lep.DeltaR(i.BLep())<maxdr;
  return matchBlep;
}
bool ReconstructionMCMatching::MatchBHad(Interpretation& i){
  if(setupMC==0){
    cerr << "need to setup mc matching first!" << endl;
    return false;
  }
  bool matchBhad=b_had.E()>1.&&i.BHad().E()>1.&&b_had.DeltaR(i.BHad())<maxdr;  
  //  cout << "dr bhad " << b_had.DeltaR(i.BHad()) << endl;
  return matchBhad;
}

bool ReconstructionMCMatching::MatchTTHallQ(Interpretation& i){
  if(setupMC<2){
    cerr << "need to setup mc matching (incl Higgs) first!" << endl;
    return false;
  }

  bool matchAll = MatchH(i)&&MatchWHad(i)&&MatchBHad(i)&&MatchBLep(i);
  return matchAll;
}

int ReconstructionMCMatching::MatchNTTH(Interpretation& i){
  if(setupMC<2){
    cerr << "need to setup mc matching (incl Higgs) first!" << endl;
    return false;
  }
  int nQ=0;
  nQ+=MatchNH(i);
  nQ+=MatchNWHad(i);
  if(MatchBHad(i)) nQ++;
  if(MatchBLep(i)) nQ++;
  return nQ;
}

int ReconstructionMCMatching::MatchNTTHResonances(Interpretation& i){
  if(setupMC<2){
    cerr << "need to setup mc matching (incl Higgs) first!" << endl;
    return false;
  }
  int nR=0;
  if(MatchH(i)) nR++;
  if(MatchWHad(i)) nR++;
  if(MatchBHad(i)&&MatchWHad(i)) nR++;
  if(MatchBLep(i)) nR++;
  return nR;
}


bool ReconstructionMCMatching::MatchTTallQ(Interpretation& i){
  if(setupMC==0){
    cerr << "need to setup mc matching first!" << endl;
    return false;
  }
  //  cout << "#####" << endl;
  bool matchAll = MatchWHad(i)&&MatchBHad(i)&&MatchBLep(i);
  return matchAll;
}

float ReconstructionMCMatching::SumDrTTH(Interpretation& i){
  if(setupMC<2){
    cerr << "need to setup mc matching (incl Higgs) first!" << endl;
    return false;
  }
  float sumDr=0;
  sumDr+=b_had.DeltaR(i.BHad());
  sumDr+=q1.DeltaR(i.Q1());
  sumDr+=q2.DeltaR(i.Q2());
  sumDr+=b_lep.DeltaR(i.BLep());
  sumDr+=lep.DeltaR(i.Lep());
  sumDr+=nu.DeltaR(i.Nu());
  sumDr+=b1.DeltaR(i.B1());
  sumDr+=b2.DeltaR(i.B1());

  return sumDr;
}

