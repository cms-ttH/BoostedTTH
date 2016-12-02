from ROOT import TFile, TTree, TH1D, TCanvas, TStyle, gStyle, TLegend, TUUID, gPad




file_name_base = "../test/testJEC_"

variations = [
    "JES",
    "JESAbsoluteScale"
]



def file_name_nominal():
    return file_name_base+"nominal_Tree.root"

def file_name_dn(label):
    return file_name_base+label+"down_Tree.root"

def file_name_up(label):
    return file_name_base+label+"up_Tree.root"
 

def passes_sel(genJetPt, genJetEta, deltaR):
    if genJetPt < 20:        return False
    if abs(genJetEta) > 3.0: return False
    if deltaR > 0.3:         return False

    return True


def get_jets_histogram(file_name, var, nbins, xmin, xmax, apply_selection):
    uid = TUUID()
    hist = TH1D("h_"+var+"_"+uid.AsString(),";"+var+";N(jets)",nbins,xmin,xmax)
    
    file = TFile(file_name,"READ")
    tree = file.Get("MVATree")
    for event in tree:
        genJetPts   = event.GenJet_Pt
        genJetEtas  = event.GenJet_Eta
        deltaRs     = event.GenJet_Jet_DeltaR
        nGenJets    = event.N_GenJets
        plottedVars = getattr(event,var)

        for i,val in enumerate(plottedVars):
            if i < nGenJets:
                if apply_selection and (i > 6 or not passes_sel(genJetPts[i],genJetEtas[i],deltaRs[i])):
                    continue
                hist.Fill(val)

    file.Close()
    
    hist.SetLineWidth(2)

    return hist


def compare(var, xtitle, varied, nbins, xmin, xmax, apply_selection):
    hist_nm = get_jets_histogram(file_name_nominal(),var,nbins,xmin,xmax,apply_selection)
    hist_up = get_jets_histogram(file_name_up(varied),var,nbins,xmin,xmax,apply_selection)
    hist_dn = get_jets_histogram(file_name_dn(varied),var,nbins,xmin,xmax,apply_selection)

    hist_nm.SetLineColor(1)
    hist_up.SetLineColor(2)
    hist_dn.SetLineColor(4)

    y_max = hist_nm.GetBinContent(hist_nm.GetMaximumBin())
    hist_nm.GetYaxis().SetRangeUser(0,1.5*y_max)
    hist_nm.GetXaxis().SetTitle(xtitle)

    can = TCanvas(var+"_"+varied,"",500,500)
    hist_nm.Draw("HIST")
    hist_up.Draw("HISTsame")
    hist_dn.Draw("HISTsame")
    hist_nm.Draw("HISTsame")

    leg = TLegend(0.2,0.72,0.92,0.88)
    leg.SetBorderSize(0)
    leg.SetFillColor(0)
    leg.SetTextFont(42)
    leg.AddEntry(hist_nm,"nominal JEC","L")
    leg.AddEntry(hist_up,varied+" up","L")
    leg.AddEntry(hist_dn,varied+" down","L")
    leg.Draw()

    gPad.RedrawAxis()

    can.SaveAs(can.GetName()+".pdf")


    hist_nm.GetYaxis().SetRangeUser(9E-1,500*y_max)
    hist_nm.Draw("HIST")
    hist_up.Draw("HISTsame")
    hist_dn.Draw("HISTsame")
    hist_nm.Draw("HISTsame")
    leg.Draw()
    can.SetLogy()
    can.SaveAs(can.GetName()+"_log.pdf")



def set_style():
    gStyle.SetErrorX(0);

    #  For the canvas
    gStyle.SetCanvasBorderMode(0);
    gStyle.SetCanvasColor(10);
    gStyle.SetCanvasDefH(800); #Height of canvas
    gStyle.SetCanvasDefW(800); #Width of canvas
    gStyle.SetCanvasDefX(0);   #Position on screen
    gStyle.SetCanvasDefY(0);

    #  For the frame
    gStyle.SetFrameBorderMode(0);
    gStyle.SetFrameBorderSize(10);
    gStyle.SetFrameFillColor(1);
    gStyle.SetFrameFillStyle(0);
    gStyle.SetFrameLineColor(1);
    gStyle.SetFrameLineStyle(0);
    gStyle.SetFrameLineWidth(2);
    gStyle.SetLineWidth(2);
    
    #  For the Pad
    gStyle.SetPadBorderMode(0);
    gStyle.SetPadColor(10);
    gStyle.SetPadGridX(False);
    gStyle.SetPadGridY(False);
    gStyle.SetGridColor(0);
    gStyle.SetGridStyle(3);
    gStyle.SetGridWidth(1);
  
    #  Margins
    gStyle.SetPadTopMargin(0.08);
    gStyle.SetPadBottomMargin(0.15);
    gStyle.SetPadLeftMargin(0.18);
    gStyle.SetPadRightMargin(0.05);
    
    #  For the histo:
    gStyle.SetHistLineColor(1);
    gStyle.SetHistLineStyle(0);
    gStyle.SetHistLineWidth(2);
    gStyle.SetMarkerSize(1.2);
    gStyle.SetEndErrorSize(4);
    gStyle.SetHatchesLineWidth(1);
    
    #  For the statistics box:
    gStyle.SetOptStat(0);
    
    #  For the axis
    gStyle.SetAxisColor(1,"XYZ");
    gStyle.SetTickLength(0.03,"XYZ");
    gStyle.SetNdivisions(510,"XYZ");
    gStyle.SetPadTickX(1);
    gStyle.SetPadTickY(1);
    gStyle.SetStripDecimals(False);
    
    #  For the axis labels and titles
    gStyle.SetTitleColor(1,"XYZ");
    gStyle.SetLabelColor(1,"XYZ");
    gStyle.SetLabelFont(42,"XYZ");
    gStyle.SetLabelOffset(0.007,"XYZ");
    gStyle.SetLabelSize(0.04,"XYZ");
    gStyle.SetTitleFont(42,"XYZ");
    gStyle.SetTitleSize(0.047,"XYZ");
    gStyle.SetTitleXOffset(1.5);
    gStyle.SetTitleYOffset(1.9);

    #  For the legend
    gStyle.SetLegendBorderSize(0);



set_style()

for variation in variations:
    apply_selection = True
    compare("GenJet_Pt","p_{T}^{gen} [GeV]",variation,100,0,200,apply_selection)
    compare("GenJet_Eta","#eta^{gen}",variation,100,-5,5,apply_selection)
    compare("GenJet_Jet_Pt","p_{T}^{rec} [GeV]",variation,100,0,200,apply_selection)
    compare("GenJet_Jet_Eta","#eta^{rec}",variation,100,-5,5,apply_selection)
