import math
from ROOT import TFile, TTree, TH1D, TH2D, TCanvas, TStyle, gStyle, TLegend, TUUID, gPad, TProfile




file_name_base = "../test/JECUncValidation_"

variations = [
    "JES",

    "JESAbsoluteStat",
    "JESAbsoluteScale",
    "JESAbsoluteFlavMap",
    "JESAbsoluteMPFBias",
    "JESFragmentation",
    "JESSinglePionECAL",
    "JESSinglePionHCAL",
    "JESFlavorQCD",
    "JESTimeEta",
    "JESTimePt",
    "JESRelativeJEREC1",
    "JESRelativeJEREC2",
    "JESRelativeJERHF",
    "JESRelativePtBB",
    "JESRelativePtEC1",
    "JESRelativePtEC2",
    "JESRelativePtHF",
    "JESRelativeFSR",
    "JESRelativeStatFSR",
    "JESRelativeStatEC",
    "JESRelativeStatHF",
    "JESPileUpDataMC",
    "JESPileUpPtRef",
    "JESPileUpPtBB",
    "JESPileUpPtEC1",
    "JESPileUpPtEC2",
    "JESPileUpPtHF",
    "JESPileUpMuZero",
    "JESPileUpEnvelope",
#    "JESSubTotalPileUp",
#    "JESSubTotalRelative",
#    "JESSubTotalPt",
#    "JESSubTotalScale",
#    "JESSubTotalMC",
#    "JESSubTotalAbsolute",
]



def file_name_nominal():
    return file_name_base+"nominal_Tree.root"

def file_name_dn(label):
    return file_name_base+label+"down_Tree.root"

def file_name_up(label):
    return file_name_base+label+"up_Tree.root"
 

def passes_dR(deltaR):
    if deltaR > 0.3:
        return False
    return True
 

def passes_sel(genJetPt, genJetEta, deltaR):
    if genJetPt < 20:
        return False
    if abs(genJetEta) > 3.0:
        return False
    if not passes_dR(deltaR):
        return False

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


def get_index(bin_edges_low,value):
    n_bins = len(bin_edges_low)
    for i in xrange(n_bins):
        r_i = n_bins-(1+i)
        if value >= bin_edges_low[r_i]:
            return r_i
    return -1


def match(idx,vals1,vals2):
    return abs(vals1[idx]-vals2[idx])/abs(vals1[idx]) < 1E-4


def jetsMismatchExit(iEvt, iJet=None, variation=None):
    print "ERROR: jets do not match"
    print "  in event "+str(iEvt)
    if not iJet == None:
        print "  for jet "+str(iJet)
    else:
        print "  different N(Jets)"
    if not variation == None:
        print "  variation: '"+variation+"'"
    exit(2)


def plot_dpt_hists(h_up,h_dn,label_variation,outname,ymax):
    # create profiles
    h_up_prof = h_up.ProfileX("h_up_prof")
    h_up_prof.GetYaxis().SetTitle(h_up.GetYaxis().GetTitle())
    h_up_prof.SetLineWidth(2)
    h_up_prof.SetLineColor(2)

    h_dn_prof = h_dn.ProfileX("h_dn_prof")
    h_dn_prof.GetYaxis().SetTitle(h_dn.GetYaxis().GetTitle())
    h_dn_prof.SetLineWidth(2)
    h_dn_prof.SetLineColor(4)

    # create frame
    h_frame = h_up_prof.Clone("h_frame")
    for bin in xrange(1,h_frame.GetNbinsX()+1):
        h_frame.SetBinContent(bin,0)
        h_frame.SetBinError(bin,0)
    h_frame.SetTitle(h_up.GetTitle())
    h_frame.SetLineStyle(2)
    h_frame.SetLineWidth(2)
    h_frame.SetLineColor(1)
    h_frame.GetYaxis().SetRangeUser(-ymax,1.3*ymax)

    # plot profiles
    can = TCanvas("can_dpt"+label_variation,"",500,500)
    h_frame.Draw("HIST")
    h_up_prof.Draw("HISTEsame")
    h_dn_prof.Draw("HISTEsame")

    leg = TLegend(0.2,0.79,0.92,0.88)
    leg.SetBorderSize(0)
    leg.SetFillColor(0)
    leg.SetTextFont(42)
    leg.AddEntry(h_up_prof,label_variation+" up","L")
    leg.AddEntry(h_dn_prof,label_variation+" down","L")
    leg.Draw()

    gPad.RedrawAxis()

    can.SaveAs(outname+".pdf")

    # draw the original 2D distributions
    title = h_up.GetTitle()
    can = TCanvas("can2D_dpt"+label_variation,"",500,500)
    can.SetRightMargin(gStyle.GetPadRightMargin()+0.1);

    h_up.SetTitle(label_variation+" UP,  "+title)
    h_up.GetYaxis().SetRangeUser(-ymax,ymax)
    h_up.Draw("colz")    
    can.SaveAs(outname+"_up.pdf")

    h_dn.SetTitle(label_variation+" DOWN,  "+title)
    h_dn.GetYaxis().SetRangeUser(-ymax,ymax)
    h_dn.Draw("colz")    
    can.SaveAs(outname+"_dn.pdf")



def plot_delta_pt(variation):
    # define the pt and eta bins
    eta_bins_low = [0,0.8,1.4]
    pt_bins_low = [20,30,50,100,300]

    # create the histograms per pt, eta bin
    # dpt (in %) vs pt/eta
    hists_dptvspt_up = []
    hists_dptvspt_dn = []
    hists_dptvseta_up = []
    hists_dptvseta_dn = []
    dpt_range =30 # in +/-%
    for i in xrange(len(eta_bins_low)):
        title = ""
        if i == len(eta_bins_low)-1:
            title = "|#eta^{gen}| > %.1f" % (eta_bins_low[i],)
        else:
            title = "%.1f < |#eta^{gen}| < %.1f" % (eta_bins_low[i],eta_bins_low[i+1])
        title += ";p^{gen}_{T} [GeV];#Deltap^{rec}_{T}/p^{rec}_{T,nominal} [%]"
        name = "hist_dptvspt_"+str(i)
        hists_dptvspt_up.append( TH2D(name+"up",title,50,0,500,400,-dpt_range,dpt_range) )
        hists_dptvspt_dn.append( TH2D(name+"dn",title,50,0,500,400,-dpt_range,dpt_range) )

    for i in xrange(len(pt_bins_low)):
        title = ""
        if i == len(pt_bins_low)-1:
            title = "p^{gen}_{T} > %.0f GeV" % (pt_bins_low[i],)
        else:
            title = "%.0f < p^{gen}_{T} < %.0f GeV" % (pt_bins_low[i],pt_bins_low[i+1])
        title += ";|#eta^{gen}|;#Deltap^{rec}_{T}/p^{rec}_{T,nominal} [%]"
        name = "hist_dptvseta_"+str(i)
        hists_dptvseta_up.append( TH2D(name+"up",title,50,0,3,400,-dpt_range,dpt_range) )
        hists_dptvseta_dn.append( TH2D(name+"dn",title,50,0,3,400,-dpt_range,dpt_range) )

    # loop over trees and fill histos
    file_nom = TFile(file_name_nominal(),"READ")
    tree_nom = file_nom.Get("MVATree")
    file_up = TFile(file_name_up(variation),"READ")
    tree_up = file_up.Get("MVATree")
    file_dn = TFile(file_name_dn(variation),"READ")
    tree_dn = file_dn.Get("MVATree")

    for iEvt in xrange(tree_nom.GetEntries()):
        tree_nom.GetEntry(iEvt)
        tree_up.GetEntry(iEvt)
        tree_dn.GetEntry(iEvt)

        # verify same event is being processed
        if tree_up.Evt_ID != tree_nom.Evt_ID or tree_dn.Evt_ID != tree_nom.Evt_ID:
            print "ERROR: non-matching event IDs"
            exit(1)

        # verify gen-jets match in all trees
        if tree_up.N_GenJets != tree_nom.N_GenJets:
            jetsMismatchExit(iEvt)
        if tree_dn.N_GenJets != tree_nom.N_GenJets:
            jetsMismatchExit(iEvt)

        for iJet in xrange(min(6,tree_nom.N_GenJets)):
            # apply gen-jet selection for nominal case
            if not passes_sel(tree_nom.GenJet_Pt[iJet],
                              tree_nom.GenJet_Eta[iJet],
                              tree_nom.GenJet_Jet_DeltaR[iJet]):
                continue

            if not match(iJet,tree_nom.GenJet_Pt,tree_up.GenJet_Pt):
                jetsMismatchExit(iEvt,iJet,variation)
            if not match(iJet,tree_nom.GenJet_Eta,tree_up.GenJet_Eta):
                jetsMismatchExit(iEvt,iJet,variation)
            if not match(iJet,tree_nom.GenJet_Phi,tree_up.GenJet_Phi):
                jetsMismatchExit(iEvt,iJet,variation)

            if not match(iJet,tree_nom.GenJet_Pt,tree_dn.GenJet_Pt):
                jetsMismatchExit(iEvt,iJet,variation)
            if not match(iJet,tree_nom.GenJet_Eta,tree_dn.GenJet_Eta):
                jetsMismatchExit(iEvt,iJet,variation)
            if not match(iJet,tree_nom.GenJet_Phi,tree_dn.GenJet_Phi):
                jetsMismatchExit(iEvt,iJet,variation)

            # check deltaR for varied cases
            if not passes_dR(tree_up.GenJet_Jet_DeltaR[iJet]):
                continue
            if not passes_dR(tree_dn.GenJet_Jet_DeltaR[iJet]):
                continue

            # compute delta pt (in %) of RECO jets
            pt_nom = tree_nom.GenJet_Jet_Pt[iJet]
            pt_up  = tree_up.GenJet_Jet_Pt[iJet]
            pt_dn  = tree_dn.GenJet_Jet_Pt[iJet]
            dpt_up = 100.*(pt_up - pt_nom)/pt_nom
            dpt_dn = -100.*(pt_nom - pt_dn)/pt_nom

            # fill histos, depending on gen-jet (pt,eta)
            eta_bin_idx = get_index(eta_bins_low,abs(tree_nom.GenJet_Eta[iJet]))

#            print ">>> "+variation+" "+str(iEvt)+" "+str(iJet)+" >>>>>>>>"
#            print "  ptGen  = "+str(tree_nom.GenJet_Pt[iJet])
#            print "  etaGen = "+str(abs(tree_nom.GenJet_Eta[iJet]))
#            print "  etabin = "+str(eta_bin_idx)
#            print "  ptNom  = "+str(pt_nom)
#            print "  ptUp   = "+str(pt_up)
#            print "  dptup  = "+str(dpt_up)
#            print "  dptdn  = "+str(dpt_dn)
#
            if not eta_bin_idx < 0:
                hists_dptvspt_up[eta_bin_idx].Fill(tree_nom.GenJet_Pt[iJet],dpt_up)
                hists_dptvspt_dn[eta_bin_idx].Fill(tree_nom.GenJet_Pt[iJet],dpt_dn)

            pt_bin_idx = get_index(pt_bins_low,tree_nom.GenJet_Pt[iJet])
            if not pt_bin_idx < 0:
                hists_dptvseta_up[pt_bin_idx].Fill(abs(tree_nom.GenJet_Eta[iJet]),dpt_up)
                hists_dptvseta_dn[pt_bin_idx].Fill(abs(tree_nom.GenJet_Eta[iJet]),dpt_dn)


    # plot dptvspt histograms in bins of eta
    for bin in xrange(len(eta_bins_low)):
        outname = "DeltaPt_"+variation+"_vsPt_EtaBin"+str(bin)
        plot_dpt_hists(hists_dptvspt_up[bin],
                       hists_dptvspt_dn[bin],
                       variation,
                       outname,
                       ymax=5)

    # plot dptvseta histograms in bins of pt
    for bin in xrange(len(pt_bins_low)):
        outname = "DeltaPt_"+variation+"_vsEta_PtBin"+str(bin)
        plot_dpt_hists(hists_dptvseta_up[bin],
                       hists_dptvseta_dn[bin],
                       variation,
                       outname,
                       ymax=5)



def plot_closure_test(variations):
    for dir in ["up","dn"]:
        # difference of total JEC variation and sum of sources
        h_dpt = TH2D("h_dpt_"+dir,"JEC closure "+dir,50,0,500,51,-50,50)
        h_dpt.GetXaxis().SetTitle("p^{gen}_{T} [GeV]")
        h_dpt.GetYaxis().SetTitle("#left(#sum#Deltap^{rec}_{T,i} - #Deltap^{rec}_{T}#right) / #Deltap^{rec}_{T}  [%]")

        # tree with nominal JEC
        file_nom = TFile(file_name_nominal(),"READ")
        tree_nom = file_nom.Get("MVATree")

        # tree with total JEC variation
        if dir == "up":
            file_tot = TFile(file_name_up("JES"),"READ")
        else: 
            file_tot = TFile(file_name_dn("JES"),"READ")
        tree_tot = file_tot.Get("MVATree")

        # trees with JEC var sources
        files_var = []
        trees_var = []
        for var in variations:
            if var == "JES":    # this is the total variation
                continue
            if dir == "up":
                files_var.append( TFile(file_name_up(var),"READ") )
            else: 
                files_var.append( TFile(file_name_dn(var),"READ") )
            trees_var.append( files_var[-1].Get("MVATree") )

        # loop over events and get variations
        for iEvt in xrange(100):#tree_nom.GetEntries()):
            tree_nom.GetEntry(iEvt)
            tree_tot.GetEntry(iEvt)
            for tree in trees_var:
                tree.GetEntry(iEvt)

            # verify the same event is being processed
            if tree_nom.Evt_ID != tree_tot.Evt_ID:
                print "ERROR: non-matching event IDs"
                exit(1)
            for tree in trees_var:
                if tree_nom.Evt_ID != tree.Evt_ID:
                    print "ERROR: non-matching event IDs"
                    exit(1)

            # verify N(gen-jets) match in all trees
            if tree_nom.N_GenJets != tree_tot.N_GenJets:
                jetsMismatchExit(iEvt)
            for tree in trees_var:
                if tree_nom.N_GenJets != tree.N_GenJets:
                    jetsMismatchExit(iEvt)


            # consider leading 6 jets in the event
            for iJet in xrange(min(6,tree_nom.N_GenJets)):
                # apply gen-jet selection for nominal case
                if not passes_sel(tree_nom.GenJet_Pt[iJet],
                                  tree_nom.GenJet_Eta[iJet],
                                  tree_nom.GenJet_Jet_DeltaR[iJet]):
                    continue

                # verify gen-jets match in all trees
                if not match(iJet,tree_nom.GenJet_Pt,tree_tot.GenJet_Pt):
                    jetsMismatchExit(iEvt,iJet)
                if not match(iJet,tree_nom.GenJet_Eta,tree_tot.GenJet_Eta):
                    jetsMismatchExit(iEvt,iJet)
                if not match(iJet,tree_nom.GenJet_Phi,tree_tot.GenJet_Phi):
                    jetsMismatchExit(iEvt,iJet)

                for tree in trees_var:
                    if not match(iJet,tree_nom.GenJet_Pt,tree.GenJet_Pt):
                        jetsMismatchExit(iEvt,iJet)
                    if not match(iJet,tree_nom.GenJet_Eta,tree.GenJet_Eta):
                        jetsMismatchExit(iEvt,iJet)
                    if not match(iJet,tree_nom.GenJet_Phi,tree.GenJet_Phi):
                        jetsMismatchExit(iEvt,iJet) 


                # compute delta pt of RECO jets
                pt_nom = tree_nom.GenJet_Jet_Pt[iJet]

                # dpt for tot variation
                pt_tot = tree_tot.GenJet_Jet_Pt[iJet]
                dpt_tot = (pt_tot - pt_nom)/pt_nom
                if dir == "dn":
                    dpt_tot *= -1.

                # dpt for sum of all sources
                dpt_var_sum = 0.
                for tree in trees_var:
                    dpt = tree.GenJet_Jet_Pt[iJet] - tree_nom.GenJet_Jet_Pt[iJet]
                    if dir == "dn":
                        dpt *= -1.
                    dpt_var_sum += dpt*dpt
                dpt_var_sum = math.sqrt(dpt_var_sum)

                dpt_tot = tree_tot.GenJet_Jet_Pt[iJet] - tree_nom.GenJet_Jet_Pt[iJet]
                if dir == "dn":
                    dpt_tot *= -1.

                rel_diff = 100.*(dpt_var_sum - dpt_tot)/dpt_tot

                # fill histos
                h_dpt.Fill(tree_nom.GenJet_Pt[iJet],rel_diff)


        # plot histo
        can = TCanvas("can2D_closure_"+dir,"",500,500)
        can.SetRightMargin(gStyle.GetPadRightMargin()+0.1);
        can.SetLeftMargin(gStyle.GetPadLeftMargin()+0.05);
        h_dpt.Draw("colz")    
        can.SaveAs("JEC_closure_"+dir+".pdf")

        file_nom.Close()
        file_tot.Close()
        for file in files_var:
            file.Close()
        



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

plot_closure_test(variations)

#for variation in variations:
#    apply_selection = True
#    compare("GenJet_Pt","p_{T}^{gen} [GeV]",variation,100,0,200,apply_selection)
#    compare("GenJet_Eta","#eta^{gen}",variation,100,-5,5,apply_selection)
#    compare("GenJet_Jet_Pt","p_{T}^{rec} [GeV]",variation,100,0,200,apply_selection)
#    compare("GenJet_Jet_Eta","#eta^{rec}",variation,100,-5,5,apply_selection)
#    plot_delta_pt(variation)
#
