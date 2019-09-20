#include "BoostedTTH/BoostedAnalyzer/interface/GenWeights.hpp"
using namespace std;

GenWeights::GenWeights()
{
    LHAPDFinitialized = false;
    initialized = false;
    // name map for samples containg ps weights
    // see https://twiki.cern.ch/twiki/bin/view/CMS/TopModGen#Event_Generation
    psweightsNameMap[0] = "nominal";
    psweightsNameMap[1] = "nominal_replica";

    //reduced
    psweightsNameMap[2] = "isr_Red_up";
    psweightsNameMap[3] = "fsr_Red_up";
    psweightsNameMap[4] = "isr_Red_down";
    psweightsNameMap[5] = "fsr_Red_down";
    //default
    psweightsNameMap[6] = "isr_Def_up";
    psweightsNameMap[7] = "fsr_Def_up";
    psweightsNameMap[8] = "isr_Def_down";
    psweightsNameMap[9] = "fsr_Def_down";
    //conservative
    psweightsNameMap[10] = "isr_Con_up";
    psweightsNameMap[11] = "fsr_Con_up";
    psweightsNameMap[12] = "isr_Con_down";
    psweightsNameMap[13] = "fsr_Con_down";

    //additional decorrelated weights
    //see https://github.com/cms-sw/cmssw/blob/master/Configuration/Generator/python/PSweightsPythia/PythiaPSweightsSettings_cfi.py
    // and https://indico.cern.ch/event/746817/contributions/3101385/attachments/1702410/2742087/psweights_mseidel.pdf
    // 32
    psweightsNameMap[13] = "fsr_G2GG_muR_down";
    psweightsNameMap[14] = "fsr_G2GG_muR_up";
    psweightsNameMap[16] = "fsr_G2QQ_muR_down";
    psweightsNameMap[16] = "fsr_G2QQ_muR_up";
    psweightsNameMap[17] = "fsr_Q2QG_muR_down";
    psweightsNameMap[18] = "fsr_Q2QG_muR_up";
    psweightsNameMap[19] = "fsr_X2XG_muR_down";
    psweightsNameMap[20] = "fsr_X2XG_muR_up";
    psweightsNameMap[21] = "fsr_G2GG_cNS_down";
    psweightsNameMap[22] = "fsr_G2GG_cNS_up";
    psweightsNameMap[23] = "fsr_G2QQ_cNS_down";
    psweightsNameMap[24] = "fsr_G2QQ_cNS_up";
    psweightsNameMap[25] = "fsr_Q2QG_cNS_down";
    psweightsNameMap[26] = "fsr_Q2QG_cNS_up";
    psweightsNameMap[27] = "fsr_X2XG_cNS_down";
    psweightsNameMap[28] = "fsr_X2XG_cNS_up";
    psweightsNameMap[29] = "isr_G2GG_muR_down";
    psweightsNameMap[30] = "isr_G2GG_muR_up";
    psweightsNameMap[31] = "isr_G2QQ_muR_down";
    psweightsNameMap[32] = "isr_G2QQ_muR_up";
    psweightsNameMap[33] = "isr_Q2QG_muR_down";
    psweightsNameMap[34] = "isr_Q2QG_muR_up";
    psweightsNameMap[35] = "isr_X2XG_muR_down";
    psweightsNameMap[36] = "isr_X2XG_muR_up";
    psweightsNameMap[37] = "isr_G2GG_cNS_down";
    psweightsNameMap[38] = "isr_G2GG_cNS_up";
    psweightsNameMap[39] = "isr_G2QQ_cNS_down";
    psweightsNameMap[40] = "isr_G2QQ_cNS_up";
    psweightsNameMap[41] = "isr_Q2QG_cNS_down";
    psweightsNameMap[42] = "isr_Q2QG_cNS_up";
    psweightsNameMap[43] = "isr_X2XG_cNS_down";
    psweightsNameMap[44] = "isr_X2XG_cNS_up";
}

void GenWeights::GetGenWeights(std::map<string, float>& weights,
    const LHEEventProduct& LHEEvent) const
{
    if (!initialized) {
        // cout << "genweights can not be read" << endl;
        // cout << "get the names for the genweights from the lhe file before you retrieve the weights or your file does not have the lheruninfoproduct" << endl;
        return;
    }
    // number of generator weights which are stored in the LHEEventProduct
    const uint weightnumber = LHEEvent.weights().size();
    // central lhe weight which is stored
    const double LHE_central_weight = LHEEvent.originalXWGTUP();
    //loop over every generator weight available and add the weight with its corresponding name to the weights map. the name is derived with the generator id and the lhe_weights map which maps the weight id to the corresponding name
    for (uint i = 0; i < weightnumber; i++) {
        const std::string& weight_id = LHEEvent.weights()[i].id;
        if (lhe_weights.find(weight_id) == lhe_weights.end())
            continue;
        const std::string& weight_name = lhe_weights.at(weight_id);
        // cout << weight_id << "   " << weight_name << endl;
        weights[weight_name] = LHEEvent.weights()[i].wgt / LHE_central_weight;
    }
    weights["Weight_LHECentral"] = LHE_central_weight;
}

bool GenWeights::GetLHAPDFWeight(std::map<string, float>& weights,
    const GenEventInfoProduct& genInfos)
{

    if (!LHAPDFinitialized) {
        return false;
    }
    // get the nominal pdf and the nominal gen weight
    const gen::PdfInfo* pdfInfos = genInfos.pdf();
    const double gen_weight = genInfos.weight();
    const double pdfNominal = pdfInfos->xPDF.first * pdfInfos->xPDF.second;

    weights["Weight_GEN_nom"] = gen_weight;

    //Loop over all initialized PDFSets and calculate the weight for a pdf variation
    for (size_t p = 0; p < initializedPDFSets.size(); p++) {

        LHAPDF::PDFSet PDFSet = initializedPDFSets[p];
        std::vector<LHAPDF::PDF*> PDFs = initializedPDFs[p];

        std::vector<double> pdfs;
        for (size_t j = 0; j < PDFs.size(); ++j) {
            double xpdf1 = PDFs[j]->xfxQ(pdfInfos->id.first, pdfInfos->x.first, pdfInfos->scalePDF);
            double xpdf2 = PDFs[j]->xfxQ(pdfInfos->id.second, pdfInfos->x.second, pdfInfos->scalePDF);
            pdfs.push_back(xpdf1 * xpdf2);
            if (std::isfinite(1. / pdfNominal)) {
                weights["Weight_LHA_" + initializedPDFNames[p] + std::to_string(PDFs[j]->lhapdfID())] = pdfs[j] / pdfNominal;
            }
        }

        // use the envelope method from lhapdf to calcualte nominal value and uncertanties
        const LHAPDF::PDFUncertainty pdfUnc = PDFSet.uncertainty(pdfs, 68.);

        double weight_up = 1.0;
        double weight_down = 1.0;
        double weight_nom = 1.0;
        if (std::isfinite(1. / pdfNominal)) {
            weight_up = (pdfUnc.central + pdfUnc.errplus) / pdfNominal;
            weight_down = (pdfUnc.central - pdfUnc.errminus) / pdfNominal;
            weight_nom = pdfUnc.central / pdfNominal;
        }

        // give values and uncertainties for a specific pdf set from an envelope method in lhapdf
        weights["Weight_LHA_" + initializedPDFNames[p] /*+std::to_string(PDFs[0]->lhapdfID())*/ + "_nominal"] = weight_nom;
        weights["Weight_LHA_" + initializedPDFNames[p] /*+std::to_string(PDFs[0]->lhapdfID())*/ + "_up"] = weight_up;
        weights["Weight_LHA_" + initializedPDFNames[p] /*+std::to_string(PDFs[0]->lhapdfID())*/ + "_down"] = weight_down;

        for (uint k = 0; k < genInfos.weights().size(); k++) {
            auto index = std::to_string(k);
            // weights["GenWeight_"+index] = genInfos.weights().at(k)/gen_weight;
            weights["GenWeight_" + psweightsNameMap[k]] = genInfos.weights().at(k) / gen_weight;
        }

        //handle internal pdf weights
        /*
    std::vector<double> int_pdf_weights;
    bool next_weight_group = false;
    bool relevant_weight_group = false;
    std::string search_string("_");
    int previous_lhaid = 0;
    for(const auto& internal_pdfs : weights){
      if(internal_pdfs.first.find("Weight_pdf_variation")!=std::string::npos){
        int position = 0;
        for(auto c = internal_pdfs.first.end();c!=internal_pdfs.first.begin();c--){
          if(*c==search_string){
            position = std::distance(internal_pdfs.first.begin(),c+1);
            break;
          }
        }
        int lhaid = std::stoi(internal_pdfs.first.substr(position));
        //std::cout << "LHAID by LHA interface " << PDFs[0]->lhapdfID() << std::endl;
        //std::cout << "LHAID parsed " << lhaid << std::endl;
        next_weight_group = abs(lhaid-previous_lhaid)>1;
        if(next_weight_group){
          //std::cout << "--------------------------------------------------------------" << std::endl;
          //std::cout << "next weight group " << next_weight_group << std::endl;
          //std::cout << "--------------------------------------------------------------" << std::endl;
          //std::cout << "pdf weight vector size " << int_pdf_weights.size() << std::endl;
          //std::cout << "lha number of weights " << PDFs.size() << std::endl;
          if(relevant_weight_group and PDFs.size()==int_pdf_weights.size()){
            //std::cout << "dumping information " << relevant_weight_group << std::endl;
            const LHAPDF::PDFUncertainty int_pdfUnc = PDFSet.uncertainty(int_pdf_weights, 68.);
            weights["Weight_LHA_"+std::to_string(PDFs[0]->lhapdfID())+"_nominal"] =  int_pdfUnc.central;
            weights["Weight_LHA_"+std::to_string(PDFs[0]->lhapdfID())+"_down"] =(int_pdfUnc.central - int_pdfUnc.errminus);
            weights["Weight_LHA_"+std::to_string(PDFs[0]->lhapdfID())+"_up"] = (int_pdfUnc.central + int_pdfUnc.errplus);
          }
          int_pdf_weights.clear();
          relevant_weight_group = lhaid==PDFs[0]->lhapdfID();
        }
        int_pdf_weights.push_back(internal_pdfs.second);
        previous_lhaid = lhaid;
      }
    }
    */
        std::vector<double> int_pdf_weights;
        for (size_t i = PDFSet.lhapdfID(); i < (PDFSet.lhapdfID() + PDFSet.size()); i++) {
            if (weights.find("Weight_pdf_variation_" + std::to_string(i)) != weights.end()) {
                int_pdf_weights.push_back(weights["Weight_pdf_variation_" + std::to_string(i)]);
            }
        }
        if (int_pdf_weights.size() == PDFSet.size()) {
            const LHAPDF::PDFUncertainty int_pdfUnc = PDFSet.uncertainty(int_pdf_weights, 68.);
            weights["Weight_LHA_" + std::to_string(PDFSet.lhapdfID()) + "_nominal"] = int_pdfUnc.central;
            weights["Weight_LHA_" + std::to_string(PDFSet.lhapdfID()) + "_down"] = (int_pdfUnc.central - int_pdfUnc.errminus);
            weights["Weight_LHA_" + std::to_string(PDFSet.lhapdfID()) + "_up"] = (int_pdfUnc.central + int_pdfUnc.errplus);
        }
    }

    return true;
}

bool GenWeights::initLHAPDF(string name)
{
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

bool GenWeights::initLHAPDF(vector<string> names)
{
    // initialize the LHAPDFs
    cout << "Initializing additional PDFs for reweighting:" << endl;
    for (const auto& name : names) {

        LHAPDF::PDFSet PDFSet(name);
        std::vector<LHAPDF::PDF*> PDFs = PDFSet.mkPDFs();

        initializedPDFSets.push_back(PDFSet);
        initializedPDFs.push_back(PDFs);
        initializedPDFNames.push_back(name);
    }

    LHAPDFinitialized = true;
    return true;
}

void GenWeights::GetNamesFromLHE(const LHERunInfoProduct& myLHERunInfoProduct)
{
    // function to get a mapping between the ids of the genweights and their actual name/meaning
    bool is_pdf_var = false;
    bool is_scale_var = false;
    bool is_hdamp_var = false;
    bool is_cfcv_var = false;
    bool special_shit = false;

    TString mur = "";
    TString muf = "";
    double mur_d = 0;
    double muf_d = 0;
    TString name_string = "";
    int split = 0;
    for (auto iter = myLHERunInfoProduct.begin(); iter != myLHERunInfoProduct.end(); iter++) {
        TString line = *iter;
        // std::cout<<line<<std::endl;
        // first remove some characters which complicate everything
        line.ToLower();
        line.ReplaceAll("\n", "");
        line.ReplaceAll(" ", "");
        line.ReplaceAll("<", "");
        line.ReplaceAll(">", "");
        line.ReplaceAll("/", "");
        line.ReplaceAll('"', "");
        line.ReplaceAll("=", "");
        line.ReplaceAll("+", "");
        // check if this line has anything to do with generator weights
        if (!line.Contains("weight"))
            continue;
        // check if a new weighgroup begins
        // std::cout << line << std::endl;
        TString lineAsPrinted = line;
        if (line.Contains("weightgroupcombine") || line.Contains("weightgroupnamemg_reweighting")) {
            // std::cout << line << std::endl;
            // pdf weights?
            if (line.Contains("pdf")) {
                is_pdf_var = true;
                is_scale_var = false;
                is_hdamp_var = false;
                is_cfcv_var = false;
            }
            // pdf weights?
            else if (line.Contains("lhgrid")) {
                is_pdf_var = true;
                is_scale_var = false;
                is_hdamp_var = false;
                is_cfcv_var = false;
            }
            // matrix element weights?
            else if (line.Contains("scale")) {
                is_pdf_var = false;
                is_scale_var = true;
                is_hdamp_var = false;
                is_cfcv_var = false;
            }
            // hdamp weights?
            else if (line.Contains("hdamp")) {
                is_pdf_var = false;
                is_scale_var = false;
                is_hdamp_var = true;
                is_cfcv_var = false;
            }
            // cfcv weights?
            else if (line.Contains("mg_reweighting")) {
                is_pdf_var = false;
                is_scale_var = false;
                is_hdamp_var = false;
                is_cfcv_var = true;
                // else if(line.Contains(
                // anything else?
            } else {
                is_pdf_var = false;
                is_scale_var = false;
                is_hdamp_var = false;
                is_cfcv_var = false;
            }

            // remove name/type string from the actual name of the weightgroup
            split = 0;
            if (line.Contains("name"))
                split = line.Index("name");
            if (line.Contains("type"))
                split = line.Index("type");
            line.Remove(0, split + 4);
            // use the name of the weightgroup for the following weights
            name_string = line;
            // some names have .lhgrid string in their name->remove
            name_string.ReplaceAll(".lhgrid", "");
            name_string.ReplaceAll("centralscalevariation", "scale_variation");
            name_string.ReplaceAll("pdf_variation1", "pdf_variation");
            name_string.ReplaceAll("pdf_variation2", "pdf_variation");
            continue;
        }

        if (is_hdamp_var)
            continue;
        if (!is_pdf_var && !is_scale_var && !is_cfcv_var)
            continue;
        // only use lines which have something to do with actual weights
        // if (!line.Contains("weightid") )
        if (!(line.Contains("weightid")
                or (line.Contains("weight") and line.Contains("nnpdf31"))
                or (line.Contains("weightmuf") and line.Contains("pdf306000")) // hacks for TH Samples
                or (line.Contains("weightmuf") and line.Contains("pdf320900"))))
            continue;

        // remove substrings to extract the weightids

        line.ReplaceAll("weight", "");
        if (!(line.Contains("mur") and line.Contains("muf") and is_pdf_var))
            line.ReplaceAll("id", "");

        split = 0;
        if (line.Contains("pdf"))
            split = line.Index("lhapdf");
        if (line.Contains("lhapdf"))
            split = line.Index("lhapdf");
        if (line.Contains("pdfset"))
            split = line.Index("pdfset");
        if (line.Contains("member"))
            split = line.Index("member");
        if (line.Contains("setparam"))
            split = line.Index("setparam");
        if (line.Contains("renscfact")) {
            //cout << "-----------------------------------" << endl;
            //cout << line << endl;
            split = line.Index("hdamp");
            line.ReplaceAll(line(split, line.Length()), "");
            //             cout << line << endl;
            split = line.Index("facscfact");
            muf = line(split, line.Length());
            line.ReplaceAll(muf, "");
            muf.ReplaceAll("facscfact", "");
            //             cout << line << endl;
            split = line.Index("renscfact");
            mur = line(split, line.Length());
            line.ReplaceAll(mur, "");
            mur.ReplaceAll("renscfact", "");
            //             cout << line << endl;
            //             std::string mur_ = mur.Data();
            //             std::string muf_ = muf.Data();
            mur_d = mur.Atof();
            //             cout << mur_d << " "<< mur <<" "<< TString::Format("%.1f",mur_d)<<endl;
            muf_d = muf.Atof();
            mur = TString::Format("%.1f", mur_d);
            mur.ReplaceAll(".", "p");
            muf = TString::Format("%.1f", muf_d);
            muf.ReplaceAll(".", "p");
            split = line.Index("lhapdf");
            line.ReplaceAll(line(split, line.Length()), "");
        }

        int idIndex = 0;
        TString id = TString(line);
        // cout <<"IM HERE " << line << std::endl;
        if (line.Contains("mur") and line.Contains("muf") and is_pdf_var) {
            // cout << "DEBUUUUG" << endl;
            // cout << line << endl;
            int pdfIndex = line.Index("pdf");
            name_string = line(pdfIndex + 3, line.Length());
            pdfIndex = name_string.Index("pdf");
            if (!(pdfIndex == -1))
                name_string = name_string(0, name_string.Index("id"));
            split = line.Index("mur");
            line.ReplaceAll(line(line.Index("member"), line.Length()), "");
            line.ReplaceAll("muf1mur1pdf", "");
            idIndex = line.Index("id");
            split = -1;
            special_shit = true;
        } else if (line.Contains("mur") and line.Contains("muf") and is_scale_var) {
            special_shit = true;

            // cout << "-----------------------------------" << endl;
            // cout << line << endl;
            //if(line.Contains("dyn-1")) line.ReplaceAll("dyn-1","");
            split = line.Index("hdamp");
            line.ReplaceAll(line(split, line.Length()), "");
            line.ReplaceAll("dyn-1", "");
            // line.ReplaceAll("pdf30600", "");
            int pdfIndex = line.Index("pdf");
            TString muRmuFString = line(pdfIndex + 9, line.Length());
            // cout << muRmuFString << endl;

            split = muRmuFString.Index("muf") + 3;
            id = muRmuFString(0, 1);
            // cout << "id hack: " << id << std::endl;
            muf = muRmuFString(split, muRmuFString.Length());
            muRmuFString.ReplaceAll(muf, "");
            muRmuFString.ReplaceAll("muf", "");
            muf.ReplaceAll("muf", "");
            // cout << muf << endl;
            // cout << muRmuFString << endl;

            muRmuFString = line(pdfIndex + 10, line.Length());
            split = muRmuFString.Index("mur");
            mur = muRmuFString(split, muRmuFString.Length());
            muRmuFString.ReplaceAll(mur, "");
            muRmuFString.ReplaceAll("mur", "");
            mur.ReplaceAll("mur", "");
            // cout << muRmuFString << endl;

            std::string mur_ = mur.Data();
            std::string muf_ = muf.Data();
            mur_d = mur.Atof();
            // cout << mur_d << " "<< mur <<" "<< TString::Format("%.1f",mur_d)<<endl;
            muf_d = muf.Atof();
            mur = TString::Format("%.1f", mur_d);
            mur.ReplaceAll(".", "p");
            muf = TString::Format("%.1f", muf_d);
            muf.ReplaceAll(".", "p");
            // cout << "mur: " << mur << "    muf: " << muf << endl;
            split = line.Index("lhapdf");
            line.ReplaceAll(line(split, line.Length()), "");
            // cout << line << std::endl;

            name_string = "scale_variation";
        } else if (is_cfcv_var) {
            special_shit = false;
            // cout << "HANDLE it now!" << endl;
            // cout << line << endl;
            split = line.Index("set");
            line = line(0, split);
            // cout << line << endl;
            id = line;
            split = -1;
        }

        // get the id of the weight
        if (special_shit and not is_scale_var) {
            id = TString(line(idIndex + 2, line.Length()));
            line.ReplaceAll(TString(id), "");
            // line.ReplaceAll("id", "");
            line = line(id.Length(),line.Length());
        } else {
            line.ReplaceAll("id", "");
            // line = line(id.Length(),line.Length());
            if (split != -1)
                id = TString(line(0, split));
            if (line.Contains("lhapdf"))
                line = TString(line(line.Index("lhapdf"), line.Length()));
        }

        // some more string acrobatics to get a nice identifier string for the weights
        if (is_pdf_var and special_shit) {
            line = "Weight_pdf_variation_" + name_string;
        } else if (is_pdf_var) {
            line.ReplaceAll("lhapdf", "Weight_" + name_string + "_");
            line.ReplaceAll("pdfset", "Weight_" + name_string + "_");
            line.ReplaceAll("member", "Weight_" + name_string + "_");
        }
        if (is_scale_var)
            line = "Weight_" + name_string + "_muR_" + mur + "_muF_" + muf;
        //         cout << lineAsPrinted<<" " <<line << "   " << id << endl;
        if (is_cfcv_var)
            line = "Weight_" + line;

        // hack to exclude all pdf variations not belonging to NNPDF31_nnlo_hessian_pdfas pdfset. They have lhaids 306000-306102
        if (line.Contains("pdf_variation") && !(line.Contains("_306") || line.Contains("_320")))
            continue;
        if (line == "")
            continue;
        // add the unique weightid and the corresponding name to a map to use later when reading the weights from the events
        // std::cout << "id: " << id << " line: " << line << std::endl;
        lhe_weights[std::string(id)] = line;
    }

    initialized = true;
}

void GenWeights::Clear()
{
    lhe_weights.clear();
}
