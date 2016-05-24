#include "BoostedTTH/BoostedAnalyzer/interface/GenWeights.hpp"
using namespace std;


GenWeights::GenWeights(){ 
    GeneratorSet = false;
    errweightvalue = -1000;
}


void GenWeights::GetGenWeights(map<string, float>& weights,
			       const LHEEventProduct& LHEEvent,
			       bool& dogenweights ) const {
  bool doreweighting = dogenweights;
  if(GeneratorSet){
    if(doreweighting){
      int weightnumber = LHEEvent.weights().size();
      //Fix for Problem with ttHnobb Sample
      if (weightnumber <= 98 ){ doreweighting = false; }
      else {
	for (int i = 0; (i < weightnumber && i < GeneratorWeights ); i++) {
	  weights[weightnames.at(i)] = LHEEvent.weights()[i].wgt;
	}
      }
    }
    //Default process:
    if(!doreweighting){
      for(int i = 0; i < GeneratorWeights; i++){
	weights[weightnames.at(i)] = errweightvalue;
      }
    }
  }
}

bool GenWeights::SetGenerator(const Generator::Generator usedGenerator){
  if(usedGenerator != Generator::notSpecified){
    weightnames = GetWeightNames(usedGenerator);
    GeneratorWeights = weightnames.size();
    GeneratorSet = true;
    return true;
  }
  else {
    return false;
  }
}


map<int, string> GenWeights::GetWeightNames(const Generator::Generator usedGenerator) const{
  map<int, string> names;
  names[0] = "Weight_muRnmuFn";
  names[1] = "Weight_muRnmuFup";
  names[2] = "Weight_muRnmuFdown";
  names[3] = "Weight_muRupmuFn";
  names[4] = "Weight_muRupmuFup";
  names[5] = "Weight_muRupmuFdown";
  names[6] = "Weight_muRdownmuFn";
  names[7] = "Weight_muRdownmuFup";
  names[8] = "Weight_muRdownmuFdown";
  if(usedGenerator == Generator::POWHEG){
    //NNPDF
    int set = 260001;
    for(int i=0; i<100; i++){
      names[9+i] = "Weight_NNPDFid"+std::to_string(set+i);
    }
    names[109] = "Weight_NNPDFasdown265000";
    names[110] = "Weight_NNPDFasup266000";
    //CT10
    set = 11000;
    for(int i=0; i<53; i++){
      names[i+111] = "Weight_CT10id"+std::to_string(set+i);
    }
    names[164] = "Weight_CT10asdown11067";
    names[165] = "Weight_CT10asup11069";
    //MMHT2014
    set = 25200;
    for(int i=0; i<=50; i++){
      names[i+166] = "Weight_MMHT2014"+std::to_string(set+i);
    } 
    set = 25260;
    for(int i=0; i<=4;i++){
      names[i+217] = "Weight_MMHT2014"+std::to_string(set+i);
    }
    for(int i=0; i<28;i++){
      names[222+i] = "Weight_hdampvar"+std::to_string(i);
    }
  }
  else if (usedGenerator == Generator::aMC) {
    int set = 292201;
    for (int i=0; i<=101; i++){
      names[9+i] = "Weight_NNPDFnf5"+std::to_string(set+i);
    }
  }
  else if (usedGenerator == Generator::MadGraph) {
    int set = 263000;
    for(int i=0; i<= 100; i++){
      names[9+i] = "Weight_NNPDF30Lo"+std::to_string(set+i);
    }
    set = 263400;
    for(int i=0; i<=100; i++){
      names[110+i] = "Weight_NNPDF30Lonf4"+std::to_string(set+i);
    }
    names[211] = "Weight_NNPDF30Lo262000";
    set = 247000;
    for(int i=0; i<=100; i++) {
      names[212+i] = "Weight_NNPDF23Loqed"+std::to_string(set+i);
    }
    names[313] = "Weight_NNPDF23Loqed246800";
    names[314] = "Weight_CTEQ6l110042";
    set = 25000;
    for(int i=0;i<=50;i++) {
      names[315+i] = "Weight_MMHT2014Lo"+std::to_string(set+i);
    }
    names[366] = "Weight_MMHT2014Lo25060";
    names[367] = "Weight_MMHT2014Lo25061";
    names[368] = "Weight_MMHT2014Lo25062";
    set = 60800;
    for(int i=0;i<=20;i++){
      names[369+i] = "Weight_HERPDF15Lo"+std::to_string(set+i);
    }
    names[390] = "Weight_NNPDF30NLO260000";
    names[391] = "Weight_NNPDF30NLO230000";
    set = 11000;
    for(int i=0;i<=52;i++){
      names[392+i] = "Weight_CT10"+std::to_string(set+i);
    }
    names[445] = "Weight_MMHT2015nlo25100";
  }
  
  return names;
}
