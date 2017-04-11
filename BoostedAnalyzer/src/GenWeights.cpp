#include "BoostedTTH/BoostedAnalyzer/interface/GenWeights.hpp"
using namespace std;


GenWeights::GenWeights(){ 
    GeneratorSet = false;
    errweightvalue = -1000;

    LHAPDFinitialized = false;
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
	  //cout << "added generator weight " << weightnames.at(i) << endl;
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

bool GenWeights::GetLHAPDFWeight( map<string, float>& weights,
				  const GenEventInfoProduct& genInfos ) {

  
  if(!LHAPDFinitialized){
    return false;
  }
  
  auto pdfInfos = genInfos.pdf();
  double pdfNominal = pdfInfos->xPDF.first * pdfInfos->xPDF.second;

  //Loop over all initialized PDFSets
  for( size_t p = 0; p < initializedPDFSets.size(); p++ ) {

    LHAPDF::PDFSet PDFSet = initializedPDFSets[p];
    std::vector<LHAPDF::PDF*> PDFs = initializedPDFs[p];

    std::vector<double> pdfs;
    for (size_t j = 0; j < PDFs.size(); ++j) {
      double xpdf1 = PDFs[j]->xfxQ(pdfInfos->id.first, pdfInfos->x.first, pdfInfos->scalePDF);
      double xpdf2 = PDFs[j]->xfxQ(pdfInfos->id.second, pdfInfos->x.second, pdfInfos->scalePDF);
      pdfs.push_back(xpdf1 * xpdf2);

      weights["Weight_"+initializedPDFNames[p]+std::to_string(PDFs[j]->lhapdfID())] =  pdfs[j] / pdfNominal;
      
    }

  

    const LHAPDF::PDFUncertainty pdfUnc = PDFSet.uncertainty(pdfs, 68.);
    
    double weight_up = 1.0;
    double weight_down = 1.0;
    double weight_nom = 1.0;
    if (std::isfinite(1./pdfNominal)) {
      weight_up = (pdfUnc.central + pdfUnc.errplus) / pdfNominal;
      weight_down = (pdfUnc.central - pdfUnc.errminus) / pdfNominal;
      weight_nom = pdfUnc.central / pdfNominal;
    }
    

    weights["Weight_"+initializedPDFNames[p]/*+std::to_string(PDFs[0]->lhapdfID())*/+"_nominal"] =  weight_nom;
    weights["Weight_"+initializedPDFNames[p]/*+std::to_string(PDFs[0]->lhapdfID())*/+"_up"] = weight_up;
    weights["Weight_"+initializedPDFNames[p]/*+std::to_string(PDFs[0]->lhapdfID())*/+"_down"] = weight_down;
  
  }


  

  return true;

}

bool GenWeights::initLHAPDF(string name){

  cout << "Initializing additional PDFs for reweighting:" << endl;
  LHAPDF::PDFSet PDFSet(name);
  std::vector<LHAPDF::PDF*> PDFs = PDFSet.mkPDFs();
  
  initializedPDFSets.push_back(PDFSet);
  initializedPDFs.push_back(PDFs);
  initializedPDFNames.push_back(name);

  LHAPDFinitialized = true;

  return true;


}


bool GenWeights::initLHAPDF(vector<string> names){


  //++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // NOT YET TESTED 
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
  cout << "Initializing additional PDFs for reweighting:" << endl;
  for( auto name: names ){

    LHAPDF::PDFSet PDFSet(name);
    std::vector<LHAPDF::PDF*> PDFs = PDFSet.mkPDFs();
    
    initializedPDFSets.push_back(PDFSet);
    initializedPDFs.push_back(PDFs);
    initializedPDFNames.push_back(name);

  }

  LHAPDFinitialized = true;
  return true;

}


map<int, string> GenWeights::GetWeightNames(const Generator::Generator usedGenerator) const{
  map<int, string> names;
  names[0] = "Weight_muRnmuFun";
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
  return names;
}


