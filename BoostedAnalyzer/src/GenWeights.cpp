#include "BoostedTTH/BoostedAnalyzer/interface/GenWeights.hpp"
using namespace std;


GenWeights::GenWeights(){ 
    LHAPDFinitialized = false;
    initialized = false;
}


void GenWeights::GetGenWeights(map<string, float>& weights,
			       const LHEEventProduct& LHEEvent
			       ) const {
    if(!initialized) {
        //cout << "genweights can not be read" << endl;
        //cout << "get the names for the genweights from the lhe file before you retrieve the weights or your file does not have the lheruninfoproduct" << endl;
        return;
    }
    // number of generator weights which are stored in the LHEEventProduct
    const uint weightnumber = LHEEvent.weights().size();
    // central lhe weight which is stored
    const double LHE_central_weight = LHEEvent.originalXWGTUP();
    //loop over every generator weight available and add the weight with its corresponding name to the weights map. the name is derived with the generator id and the lhe_weights map which maps the weight id to the corresponding name
    for (uint i = 0;i < weightnumber; i++) {
        std::string weight_id = LHEEvent.weights()[i].id;
        if(!lhe_weights.count(weight_id) && i>8) continue;
        std::string weight_name;
        if(!lhe_weights.count(weight_id)){
            if (i==0){
            weight_name="scale_variation_muR1p0_muF1p0";
            }
            else if(i==1){
            weight_name="scale_variation_muR1p0_muF2p0";
            }
            else if(i==2){
            weight_name="scale_variation_muR1p0_muF2p0";
            }
            else if(i==3){
            weight_name="scale_variation_muR2p0_muF1p0";
            }
            else if(i==4){
            weight_name="scale_variation_muR2p0_muF2p0";
            }
            else if(i==5){
            weight_name="scale_variation_muR2p0_muF0p5";
            }
            else if(i==6){
            weight_name="scale_variation_muR0p5_muF1p0";
            }
            else if(i==7){
            weight_name="scale_variation_muR0p5_muF2p0";
            }
            else if(i==8){
            weight_name="scale_variation_muR0p5_muF0p5";
            }
            
            else{
                continue;
            }
            
            
        }
        else{
            std::string weight_name = lhe_weights.at(weight_id);
        }
        
        //cout << weight_id << "   " << weight_name << endl;
        weights[weight_name] = LHEEvent.weights()[i].wgt/LHE_central_weight;
    }
    weights["Weight_LHECentral"]=LHE_central_weight;
}


bool GenWeights::GetLHAPDFWeight( map<string, float>& weights,
				  const GenEventInfoProduct& genInfos ) {

  if(!LHAPDFinitialized){
    return false;
  }
  // get the nominal pdf and the nominal gen weight
  const gen::PdfInfo* pdfInfos = genInfos.pdf();
  const double gen_weight = genInfos.weight();
  double pdfNominal = pdfInfos->xPDF.first * pdfInfos->xPDF.second;
  
  if (pdfNominal==0){
//     LHAPDF::PDFSet PDFSet = initializedPDFSets[2];
    std::vector<LHAPDF::PDF*> PDFs = initializedPDFs[2];
    double xpdf1 = PDFs[0]->xfxQ(pdfInfos->id.first, pdfInfos->x.first, pdfInfos->scalePDF);
    double xpdf2 = PDFs[0]->xfxQ(pdfInfos->id.second, pdfInfos->x.second, pdfInfos->scalePDF);
//     std::cout<<"xpdf1 "<<xpdf1<<" id "<<pdfInfos->id.first<<" x "<<pdfInfos->x.first<<" scale "<<pdfInfos->scalePDF<<std::endl;
//     std::cout<<"xpdf2 "<<xpdf2<<" id "<<pdfInfos->id.second<<" x "<<pdfInfos->x.second<<" scale "<<pdfInfos->scalePDF<<std::endl;
//     pdfs.push_back(xpdf1 * xpdf2);    
    pdfNominal=xpdf1 * xpdf2;
  }
  
//   std::cout<<"pdfNominal "<<pdfNominal<<std::endl;
  weights["Weight_GEN_nom"]=gen_weight;

  //Loop over all initialized PDFSets and calculate the weight for a pdf variation
  for( size_t p = 0; p < initializedPDFSets.size(); p++ ) {

    LHAPDF::PDFSet PDFSet = initializedPDFSets[p];
    std::vector<LHAPDF::PDF*> PDFs = initializedPDFs[p];

    std::vector<double> pdfs;
    for (size_t j = 0; j < PDFs.size(); ++j) {
      double xpdf1 = PDFs[j]->xfxQ(pdfInfos->id.first, pdfInfos->x.first, pdfInfos->scalePDF);
      double xpdf2 = PDFs[j]->xfxQ(pdfInfos->id.second, pdfInfos->x.second, pdfInfos->scalePDF);
//       std::cout<<"xpdf1 "<<xpdf1<<" id "<<pdfInfos->id.first<<" x "<<pdfInfos->x.first<<" scale "<<pdfInfos->scalePDF<<std::endl;
//       std::cout<<"xpdf2 "<<xpdf2<<" id "<<pdfInfos->id.second<<" x "<<pdfInfos->x.second<<" scale "<<pdfInfos->scalePDF<<std::endl;
      pdfs.push_back(xpdf1 * xpdf2);
      if (std::isfinite(1./pdfNominal)) {
            weights["Weight_LHA_"+initializedPDFNames[p]+std::to_string(PDFs[j]->lhapdfID())] =  pdfs[j] / pdfNominal;
      }
    }

    // use the envelope method from lhapdf to calcualte nominal value and uncertanties
    const LHAPDF::PDFUncertainty pdfUnc = PDFSet.uncertainty(pdfs, 68.);
    
    double weight_up = 1.0;
    double weight_down = 1.0;
    double weight_nom = 1.0;
    if (std::isfinite(1./pdfNominal)) {
      weight_up = (pdfUnc.central + pdfUnc.errplus) / pdfNominal;
      weight_down = (pdfUnc.central - pdfUnc.errminus) / pdfNominal;
      weight_nom = pdfUnc.central / pdfNominal;
    }
    
    // give values and uncertainties for a specific pdf set from an envelope method in lhapdf
    weights["Weight_LHA_"+initializedPDFNames[p]/*+std::to_string(PDFs[0]->lhapdfID())*/+"_nominal"] =  weight_nom;
    weights["Weight_LHA_"+initializedPDFNames[p]/*+std::to_string(PDFs[0]->lhapdfID())*/+"_up"] = weight_up;
    weights["Weight_LHA_"+initializedPDFNames[p]/*+std::to_string(PDFs[0]->lhapdfID())*/+"_down"] = weight_down;
    
  }

  return true;

}

bool GenWeights::initLHAPDF(string name){
  // initialize the LHAPDFs
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
  // initialize the LHAPDFs
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

void GenWeights::GetNamesFromLHE(const LHERunInfoProduct& myLHERunInfoProduct) {
    // function to get a mapping between the ids of the genweights and their actual name/meaning
    bool is_pdf_var=false;
    bool is_scale_var=false;
    bool is_hdamp_var=false;
    TString mur = "";
    TString muf = "";
    double mur_d = 0;
    double muf_d = 0;
    TString name_string = "";
    int split=0;
    for (auto iter=myLHERunInfoProduct.begin(); iter!=myLHERunInfoProduct.end(); iter++) {
        TString line = *iter;
        
        std::cout<<"michaels suggestion: "<<line<<std::endl;
        // first remove some characters which complicate everything
        line.ToLower();
        line.ReplaceAll("\n","");
        line.ReplaceAll(" ","");
        line.ReplaceAll("<","");
        line.ReplaceAll(">","");
        line.ReplaceAll("/","");
        line.ReplaceAll('"',"");
        line.ReplaceAll("=","");
        line.ReplaceAll("+","");
        // check if this line has anything to do with generator weights
        if(!line.Contains("weight")) continue;
        // check if a new weighgroup begins
        if(line.Contains("weightgroupcombine")) {
            // pdf weights?
            if(line.Contains("pdf")) {
                is_pdf_var=true;
                is_scale_var=false;
                is_hdamp_var=false;
            }
            // pdf weights?
            else if(line.Contains("lhgrid")) {
                is_pdf_var=true;
                is_scale_var=false;
                is_hdamp_var=false;
            }
            // matrix element weights?
            else if(line.Contains("scale")){
                is_pdf_var=false;
                is_scale_var=true;
                is_hdamp_var=false;
            }
            // hdamp weights?
            else if(line.Contains("hdamp")) {
                is_pdf_var=false;
                is_scale_var=false;
                is_hdamp_var=true;
            }
            // anything else?
            else {
                is_pdf_var=false;
                is_scale_var=false;
                is_hdamp_var=false;
            }
            // remove name/type string from the actual name of the weightgroup
            split=0;
            if(line.Contains("name")) split=line.Index("name");
            if(line.Contains("type")) split=line.Index("type");
            line.Remove(0,split+4);
            // use the name of the weightgroup for the following weights 
            name_string = line;
            // some names have .lhgrid string in their name->remove
            name_string.ReplaceAll(".lhgrid","");
            name_string.ReplaceAll("centralscalevariation","scale_variation");
            //cout << "blablabla " << split << "       " << pdf_string << endl;
            continue;
        }
        // only use matrix element scale and pdf weights for now
        if(is_hdamp_var) continue;
        if(!is_pdf_var&&!is_scale_var) continue;
        // only use lines which have something to do with actual weights
        if(!line.Contains("weightid")) continue;
        
        //cout << line << endl;
        // remove substrings to extract the weightids
        line.ReplaceAll("weight","");
        line.ReplaceAll("id","");
        
        split=0;
        if(line.Contains("pdfset")) split=line.Index("pdfset");
        if(line.Contains("member")) split=line.Index("member");                
        if(line.Contains("mur")) {
            //cout << "-----------------------------------" << endl;
            //cout << line << endl;
            split=line.Index("hdamp");
            line.ReplaceAll(line(split,line.Length()),"");
            //cout << line << endl;
            split=line.Index("muf");
            muf = line(split,line.Length());
            line.ReplaceAll(muf,"");
            muf.ReplaceAll("muf","");
            //cout << line << endl;
            split=line.Index("mur");
            mur = line(split,line.Length());
            line.ReplaceAll(mur,"");
            mur.ReplaceAll("mur","");
            //cout << line << endl;
            //std::string mur_ = mur.Data();
            //std::string muf_ = muf.Data();
            mur_d = mur.Atof();
            muf_d = muf.Atof();
            mur = TString::Format("%.1f",mur_d);
            muf = TString::Format("%.1f",muf_d);
            mur.ReplaceAll(".","p");
            muf.ReplaceAll(".","p");
            std::cout<<mur<<std::endl;
            std::cout<<muf<<std::endl;
        }
        // get the id of the weight
        TString id=TString(line,split);
        line.ReplaceAll(TString(id),"");
        // some more string acrobatics to get a nice identifier string for the weights
        if(is_pdf_var) {
            line.ReplaceAll("pdfset","Weight_"+name_string+"_");
            line.ReplaceAll("member","Weight_"+name_string+"_");
        }
        if(is_scale_var) line="Weight_"+name_string+"_muR"+mur+"_muF"+muf;
        //cout << line << "   " << id << endl;
        // add the unique weightid and the corresponding name to a map to use later when reading the weights from the events
        lhe_weights[std::string(id)]=line;
        
        }
        
        initialized = true;
        
}

void GenWeights::Clear() {
    lhe_weights.clear();
}




