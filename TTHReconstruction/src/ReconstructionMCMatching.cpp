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
  w_had=q1+q2;
  w_lep=lep+nu;
  top_had=b_had+q1+q2;
  top_lep=b_lep+lep+nu;
  higgs=b1+b2;
  setupMC=2;
}
void ReconstructionMCMatching::Setup(TLorentzVector b_had_, TLorentzVector q1_, TLorentzVector q2_, TLorentzVector b_lep_, TLorentzVector lep_, TLorentzVector nu_){
  b_had=b_had_;
  q1=q1_;
  q2=q2_;
  b_lep=b_lep_;
  lep=lep_;
  nu=nu_;
  w_had=q1+q2;
  w_lep=lep+nu;
  top_had=b_had+q1+q2;
  top_lep=b_lep+lep+nu;
  setupMC=1;
}

int ReconstructionMCMatching::GetState(){
  return setupMC;
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

float ReconstructionMCMatching::DrH(Interpretation& i){
    float dr=999;
    if(higgs.Pt()>0.01 && i.Higgs().Pt()>0.01){
	dr=higgs.DeltaR(i.Higgs());
    }
    return dr;
}
float ReconstructionMCMatching::DrB1(Interpretation& i){
    float dr=999;
    if(b1.Pt()>0.01 && i.B1().Pt()>0.01){
	dr=b1.DeltaR(i.B1());
    }
    return dr;
}
float ReconstructionMCMatching::DrB2(Interpretation& i){
    float dr=999;
    if(b2.Pt()>0.01 && i.B2().Pt()>0.01){
	dr=b2.DeltaR(i.B2());
    }
    return dr;
}
float ReconstructionMCMatching::DrWHad(Interpretation& i){
    float dr=999;
    if(w_had.Pt()>0.01 && i.WHad().Pt()>0.01){
	dr=w_had.DeltaR(i.WHad());
    }
    return dr;
}
float ReconstructionMCMatching::DrQ1(Interpretation& i){
    float dr=999;
    if(q1.Pt()>0.01 && i.Q1().Pt()>0.01){
	dr=q1.DeltaR(i.Q1());
    }
    return dr;
}
float ReconstructionMCMatching::DrQ2(Interpretation& i){
    float dr=999;
    if(q2.Pt()>0.01 && i.Q2().Pt()>0.01){
	dr=q2.DeltaR(i.Q2());
    }
    return dr;
}
float ReconstructionMCMatching::DrWLep(Interpretation& i){
    float dr=999;
    if(w_lep.Pt()>0.01 && i.WLep().Pt()>0.01){
	dr=w_lep.DeltaR(i.WLep());
    }
    return dr;
}
float ReconstructionMCMatching::DrLep(Interpretation& i){
    float dr=999;
    if(lep.Pt()>0.01 && i.Lep().Pt()>0.01){
	dr=lep.DeltaR(i.Lep());
    }
    return dr;
}
float ReconstructionMCMatching::DrNu(Interpretation& i){
    float dr=999;
    if(nu.Pt()>0.01 && i.Nu().Pt()>0.01){
	dr=nu.DeltaR(i.Nu());
    }
    return dr;
}
float ReconstructionMCMatching::DrBLep(Interpretation& i){
    float dr=999;
    if(b_lep.Pt()>0.01 && i.BLep().Pt()>0.01){
	dr=b_lep.DeltaR(i.BLep());
    }
    return dr;
}
float ReconstructionMCMatching::DrBHad(Interpretation& i){
    float dr=999;
    if(b_had.Pt()>0.01 && i.BHad().Pt()>0.01){
	dr=b_had.DeltaR(i.BHad());
    }
    return dr;
}
float ReconstructionMCMatching::DrTopLep(Interpretation& i){
    float dr=999;
    if(top_lep.Pt()>0.01 && i.TopLep().Pt()>0.01){
	dr=top_lep.DeltaR(i.TopLep());
    }
    return dr;
}
float ReconstructionMCMatching::DrTopHad(Interpretation& i){
    float dr=999;
    if(top_had.Pt()>0.01 && i.TopHad().Pt()>0.01){
	dr=top_had.DeltaR(i.TopHad());
    }
    return dr;
}
