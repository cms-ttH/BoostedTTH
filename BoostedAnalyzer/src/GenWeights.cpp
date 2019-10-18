#include "BoostedTTH/BoostedAnalyzer/interface/GenWeights.hpp"
using namespace std;

GenWeights::GenWeights()
{
    LHAPDFinitialized = false;
    initialized       = false;
    // name map for samples containg ps weights
    // see https://twiki.cern.ch/twiki/bin/view/CMS/TopModGen#Event_Generation
    psweightsNameMap[0] = "nominal";
    psweightsNameMap[1] = "nominal_replica";

    // reduced
    psweightsNameMap[2] = "isr_Red_up";
    psweightsNameMap[3] = "fsr_Red_up";
    psweightsNameMap[4] = "isr_Red_down";
    psweightsNameMap[5] = "fsr_Red_down";
    // default
    psweightsNameMap[6] = "isr_Def_up";
    psweightsNameMap[7] = "fsr_Def_up";
    psweightsNameMap[8] = "isr_Def_down";
    psweightsNameMap[9] = "fsr_Def_down";
    // conservative
    psweightsNameMap[10] = "isr_Con_up";
    psweightsNameMap[11] = "fsr_Con_up";
    psweightsNameMap[12] = "isr_Con_down";
    psweightsNameMap[13] = "fsr_Con_down";

    // additional decorrelated weights
    // see
    // https://github.com/cms-sw/cmssw/blob/master/Configuration/Generator/python/PSweightsPythia/PythiaPSweightsSettings_cfi.py
    // and
    // https://indico.cern.ch/event/746817/contributions/3101385/attachments/1702410/2742087/psweights_mseidel.pdf
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

void GenWeights::GetGenWeights(std::map< string, float >& weights, const LHEEventProduct& LHEEvent) const
{
    if (!initialized) {
        // cout << "genweights can not be read" << endl;
        // cout << "get the names for the genweights from the lhe file before you
        // retrieve the weights or your file does not have the lheruninfoproduct" <<
        // endl;
        return;
    }
    // number of generator weights which are stored in the LHEEventProduct
    const uint weightnumber = LHEEvent.weights().size();
    // central lhe weight which is stored
    const double LHE_central_weight = LHEEvent.originalXWGTUP();
    // loop over every generator weight available and add the weight with its
    // corresponding name to the weights map. the name is derived with the
    // generator id and the lhe_weights map which maps the weight id to the
    // corresponding name
    for (uint i = 0; i < weightnumber; i++) {
        const std::string& weight_id = LHEEvent.weights()[i].id;
        if (lhe_weights.find(weight_id) == lhe_weights.end()) continue;
        const std::string& weight_name = lhe_weights.at(weight_id);
        //         cout << weight_id << "   " << weight_name << endl;
        weights[weight_name] = LHEEvent.weights()[i].wgt / LHE_central_weight;
    }
    weights["Weight_LHECentral"] = LHE_central_weight;
}

bool GenWeights::GetLHAPDFWeight(std::map< string, float >& weights, const GenEventInfoProduct& genInfos)
{
    if (!LHAPDFinitialized) { return false; }
    // get the nominal pdf and the nominal gen weight
    const gen::PdfInfo* pdfInfos   = genInfos.pdf();
    const double        gen_weight = genInfos.weight();
    const double        pdfNominal = pdfInfos->xPDF.first * pdfInfos->xPDF.second;

    weights["Weight_GEN_nom"] = gen_weight;

    // Loop over all initialized PDFSets and calculate the weight for a pdf
    // variation
    for (size_t p = 0; p < initializedPDFSets.size(); p++) {
        LHAPDF::PDFSet              PDFSet = initializedPDFSets[p];
        std::vector< LHAPDF::PDF* > PDFs   = initializedPDFs[p];

        std::vector< double > pdfs;
        for (size_t j = 0; j < PDFs.size(); ++j) {
            double xpdf1 = PDFs[j]->xfxQ(pdfInfos->id.first, pdfInfos->x.first, pdfInfos->scalePDF);
            double xpdf2 = PDFs[j]->xfxQ(pdfInfos->id.second, pdfInfos->x.second, pdfInfos->scalePDF);
            pdfs.push_back(xpdf1 * xpdf2);
            if (std::isfinite(1. / pdfNominal)) {
                weights["Weight_LHA_" + initializedPDFNames[p] + std::to_string(PDFs[j]->lhapdfID())] = pdfs[j] / pdfNominal;
            }
        }

        // use the envelope method from lhapdf to calcualte nominal value and
        // uncertanties
        const LHAPDF::PDFUncertainty pdfUnc = PDFSet.uncertainty(pdfs, 68.);

        double weight_up   = 1.0;
        double weight_down = 1.0;
        double weight_nom  = 1.0;
        if (std::isfinite(1. / pdfNominal)) {
            weight_up   = (pdfUnc.central + pdfUnc.errplus) / pdfNominal;
            weight_down = (pdfUnc.central - pdfUnc.errminus) / pdfNominal;
            weight_nom  = pdfUnc.central / pdfNominal;
        }

        // give values and uncertainties for a specific pdf set from an envelope
        // method in lhapdf
        weights["Weight_LHA_" + initializedPDFNames[p] /*+std::to_string(PDFs[0]->lhapdfID())*/ + "_nominal"] = weight_nom;
        weights["Weight_LHA_" + initializedPDFNames[p] /*+std::to_string(PDFs[0]->lhapdfID())*/ + "_up"]      = weight_up;
        weights["Weight_LHA_" + initializedPDFNames[p] /*+std::to_string(PDFs[0]->lhapdfID())*/ + "_down"]    = weight_down;

        for (uint k = 0; k < genInfos.weights().size(); k++) {
            auto index = std::to_string(k);
            // weights["GenWeight_"+index] = genInfos.weights().at(k)/gen_weight;
            weights["GenWeight_" + psweightsNameMap[k]] = genInfos.weights().at(k) / gen_weight;
        }

        // handle internal pdf weights
        /*
        std::vector<double> int_pdf_weights;
        bool next_weight_group = false;
        bool relevant_weight_group = false;
        std::string search_string("_");
        int previous_lhaid = 0;
        for(const auto& internal_pdfs : weights){
          if(internal_pdfs.first.find("Weight_pdf_variation")!=std::string::npos){
            int position = 0;
            for(auto c =
        internal_pdfs.first.end();c!=internal_pdfs.first.begin();c--){
              if(*c==search_string){
                position = std::distance(internal_pdfs.first.begin(),c+1);
                break;
              }
            }
            int lhaid = std::stoi(internal_pdfs.first.substr(position));
            //std::cout << "LHAID by LHA interface " << PDFs[0]->lhapdfID() <<
        std::endl;
            //std::cout << "LHAID parsed " << lhaid << std::endl;
            next_weight_group = abs(lhaid-previous_lhaid)>1;
            if(next_weight_group){
              //std::cout <<
        "--------------------------------------------------------------" <<
        std::endl;
              //std::cout << "next weight group " << next_weight_group << std::endl;
              //std::cout <<
        "--------------------------------------------------------------" <<
        std::endl;
              //std::cout << "pdf weight vector size " << int_pdf_weights.size() <<
        std::endl;
              //std::cout << "lha number of weights " << PDFs.size() << std::endl;
              if(relevant_weight_group and PDFs.size()==int_pdf_weights.size()){
                //std::cout << "dumping information " << relevant_weight_group <<
        std::endl; const LHAPDF::PDFUncertainty int_pdfUnc =
        PDFSet.uncertainty(int_pdf_weights, 68.);
                weights["Weight_LHA_"+std::to_string(PDFs[0]->lhapdfID())+"_nominal"]
        =  int_pdfUnc.central;
                weights["Weight_LHA_"+std::to_string(PDFs[0]->lhapdfID())+"_down"]
        =(int_pdfUnc.central - int_pdfUnc.errminus);
                weights["Weight_LHA_"+std::to_string(PDFs[0]->lhapdfID())+"_up"] =
        (int_pdfUnc.central + int_pdfUnc.errplus);
              }
              int_pdf_weights.clear();
              relevant_weight_group = lhaid==PDFs[0]->lhapdfID();
            }
            int_pdf_weights.push_back(internal_pdfs.second);
            previous_lhaid = lhaid;
          }
        }
        */
        std::vector< double > int_pdf_weights;
        for (size_t i = PDFSet.lhapdfID(); i < (PDFSet.lhapdfID() + PDFSet.size()); i++) {
            if (weights.find("Weight_pdf_variation_" + std::to_string(i)) != weights.end()) {
                int_pdf_weights.push_back(weights["Weight_pdf_variation_" + std::to_string(i)]);
            }
        }
        if (int_pdf_weights.size() == PDFSet.size()) {
            const LHAPDF::PDFUncertainty int_pdfUnc                                 = PDFSet.uncertainty(int_pdf_weights, 68.);
            weights["Weight_LHA_" + std::to_string(PDFSet.lhapdfID()) + "_nominal"] = int_pdfUnc.central;
            weights["Weight_LHA_" + std::to_string(PDFSet.lhapdfID()) + "_down"]    = (int_pdfUnc.central - int_pdfUnc.errminus);
            weights["Weight_LHA_" + std::to_string(PDFSet.lhapdfID()) + "_up"]      = (int_pdfUnc.central + int_pdfUnc.errplus);
        }
    }

    return true;
}

bool GenWeights::initLHAPDF(string name)
{
    // initialize the LHAPDFs
    cout << "Initializing additional PDFs for reweighting:" << endl;
    LHAPDF::PDFSet              PDFSet(name);
    std::vector< LHAPDF::PDF* > PDFs = PDFSet.mkPDFs();

    initializedPDFSets.push_back(PDFSet);
    initializedPDFs.push_back(PDFs);
    initializedPDFNames.push_back(name);

    LHAPDFinitialized = true;

    return true;
}

bool GenWeights::initLHAPDF(vector< string > names)
{
    // initialize the LHAPDFs
    cout << "Initializing additional PDFs for reweighting:" << endl;
    for (const auto& name : names) {
        LHAPDF::PDFSet              PDFSet(name);
        std::vector< LHAPDF::PDF* > PDFs = PDFSet.mkPDFs();

        initializedPDFSets.push_back(PDFSet);
        initializedPDFs.push_back(PDFs);
        initializedPDFNames.push_back(name);
    }

    LHAPDFinitialized = true;
    return true;
}

void GenWeights::GetNamesFromLHE(const LHERunInfoProduct& myLHERunInfoProduct)
{
    // function to get a mapping between the ids of the genweights and their
    // actual name/meaning
    bool    is_pdf_var   = false;
    bool    is_scale_var = false;
    bool    is_hdamp_var = false;
    TString mur          = "";
    TString muf          = "";
    TString pdf_member   = "";
    TString id           = "";
    TString name         = "";
    TString mur_keyword  = "";
    TString muf_keyword  = "";
    TString pdf_keyword  = "";
    double  mur_d        = 0;
    double  muf_d        = 0;
    int     pdf_member_i = 0;
    int     id_i         = 0;

    // loop over lines of LHE header
    for (auto iter = myLHERunInfoProduct.begin(); iter != myLHERunInfoProduct.end(); iter++) {
        TString line = *iter;
        // std::cout << "LHE HEADER:  " << line << std::endl;

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
        line.ReplaceAll("&lt;", "");
        line.ReplaceAll("&gt;", "");
        line.ReplaceAll("dyn-1", "");

        // std::cout << "LHE HEADER edited  :  " << line << std::endl;

        // check if a new weighgroup begins
        if (line.Contains("weightgroup") && line.Contains("combine")) {
            // matrix element weights?
            if (line.Contains("scale")) {
                is_pdf_var   = false;
                is_scale_var = true;
                is_hdamp_var = false;
            }
            // pdf weights?
            else if (line.Contains("lhgrid")) {
                is_pdf_var   = true;
                is_scale_var = false;
                is_hdamp_var = false;
            }
            // pdf weights?
            else if (line.Contains("pdf")) {
                is_pdf_var   = true;
                is_scale_var = false;
                is_hdamp_var = false;
            }
            // hdamp weights?
            else if (line.Contains("hdamp")) {
                is_pdf_var   = false;
                is_scale_var = false;
                is_hdamp_var = true;
            }
            //             else if(line.Contains(
            // anything else?
            else {
                is_pdf_var   = false;
                is_scale_var = false;
                is_hdamp_var = false;
            }
            continue;
        }

        // only use matrix element scale and pdf weights for now
        if (is_hdamp_var) continue;
        if (!is_pdf_var && !is_scale_var) continue;

        // only use lines which have something to do with actual weights
        if (!line.Contains("weightid")) continue;

        // reset some defaults
        mur          = "";
        muf          = "";
        pdf_member   = "";
        id           = "";
        name         = "";
        mur_d        = 0;
        muf_d        = 0;
        pdf_member_i = 0;
        id_i         = 0;
        mur_keyword  = "";
        muf_keyword  = "";
        pdf_keyword  = "";

        // keywords (depend on samples ...)
        if (is_scale_var) {
            if (line.Contains("mur") and line.Contains("muf")) {
                mur_keyword = "mur";
                muf_keyword = "muf";
            }
            else if (line.Contains("renscfact") and line.Contains("facscfact")) {
                mur_keyword = "renscfact";
                muf_keyword = "facscfact";
            }
            else {
                std::cerr << "no known keyword for matrix element scale variations" << std::endl;
                std::cerr << "This should never happen!" << std::endl;
                std::cerr << "Don't trust the generator weights unless this problem is fixed!" << std::endl;
                throw std::exception();
            }
            // get values of mur/muf
            mur_d = GetNumber(line, mur_keyword).Atof();
            muf_d = GetNumber(line, muf_keyword).Atof();
        }
        else if (is_pdf_var) {
            if (line.Contains("pdf")) { pdf_keyword = "pdf"; }
            else {
                std::cerr << "no known keyword for pdf variations" << std::endl;
                std::cerr << "This should never happen!" << std::endl;
                std::cerr << "Don't trust the generator weights unless this problem is fixed!" << std::endl;
                throw std::exception();
            }
            // get ids of pdf variations
            pdf_member_i = GetNumber(line, pdf_keyword).Atoi();
        }

        // get values of weight id
        id_i = GetNumber(line, "weightid").Atoi();

        // fail-safe
        if (((mur_d == 0. or muf_d == 0.) and is_scale_var) or (pdf_member_i == 0 and is_pdf_var) or id_i == 0) {
            std::cerr << "something went wrong with reading the values for the matrix element scale or pdf variation IDs" << std::endl;
            std::cerr << "This should never happen!" << std::endl;
            std::cerr << "Don't trust the generator weights unless this problem is fixed!" << std::endl;
            throw std::exception();
        }

        // ensure a common format
        mur = TString::Format("%.1f", mur_d);
        mur.ReplaceAll(".", "p");
        muf = TString::Format("%.1f", muf_d);
        muf.ReplaceAll(".", "p");
        id         = TString::Format("%i", id_i);
        pdf_member = TString::Format("%i", pdf_member_i);

        // std::cout << "weightid: " << id << std::endl;
        // std::cout << "muf: " << muf << std::endl;
        // std::cout << "mur: " << mur << std::endl;
        // std::cout << "pdfid: " << pdf_member << std::endl;

        // set default names for possible variations
        if (is_scale_var) { name = "Weight_scale_variation_muR_" + mur + "_muF_" + muf; }
        else if (is_pdf_var) {
            name = "Weight_pdf_variation_" + pdf_member;
        }
        else {
            std::cerr << "Problem in GenWeights::GetNamesFromLHE" << std::endl;
            std::cerr << "This should never happen!" << std::endl;
            std::cerr << "Don't trust the generator weights unless this problem is fixed!" << std::endl;
            throw std::exception();
        }

        // put the weight ids and their corresponding names in the map
        lhe_weights[std::string(id)] = name;
    }

    initialized = true;
}

void GenWeights::Clear() { lhe_weights.clear(); }

TString GenWeights::GetNumber(TString line, TString keyword) const
{
    if (line == "" or keyword == "") {
        std::cerr << "Problem in GenWeights::GetNumber" << std::endl;
        std::cerr << "This should never happen!" << std::endl;
        std::cerr << "Don't trust the generator weights unless this problem is fixed!" << std::endl;
        throw std::exception();
    }
    auto split = line.Index(keyword);
    if (split == -1) return "";
    auto index_1 = split;
    for (auto i = split; i < line.Length(); i++) {
        if (std::isdigit(line.Data()[i])) {
            index_1 = i;
            break;
        }
    }
    auto index_2 = index_1;
    for (auto i = index_1; i < line.Length(); i++) {
        if ((not std::isdigit(line.Data()[i])) and (not std::isdigit(line.Data()[i + 1]))) {
            index_2 = i;
            break;
        }
    }
    return line(index_1, index_2 - index_1);
}
