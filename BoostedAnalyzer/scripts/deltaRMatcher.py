import sys
import os
import optparse
import numpy as np
import ROOT

ROOT.gROOT.SetBatch(True)

def draw_hist(hist, plotdir, name, label, dRlabel, ymax):
    canvas = ROOT.TCanvas(name,name, 1024, 768)
    canvas.SetTopMargin(0.07)
    canvas.SetBottomMargin(0.15)
    canvas.SetRightMargin(0.05)
    canvas.SetLeftMargin(0.15)
    canvas.SetTicks(1,1)

    canvas.cd(1)

    hist.Scale(1./hist.Integral())
    sumHist = hist.Clone()
    hist.SetTitle(dRlabel+"  ("+label+")")
    hist.GetXaxis().SetTitle(name)
    hist.GetYaxis().SetTitle("fraction of events")
    hist.GetYaxis().SetRangeUser(0.,ymax)
    hist.SetLineColor(ROOT.kRed)
    hist.SetLineWidth(2)
    #hist.SetFillColor(ROOT.kRed)
    #hist.SetFillStyle(1001)
    
    hist.Draw("HIST")
    hist.SetStats(False)

    # get cumulative sum
    integral = 0
    for iBin in xrange(sumHist.GetNbinsX()):
        integral += sumHist.GetBinContent(iBin+1)
        sumHist.SetBinContent(iBin+1,integral)
    sumHist.SetLineColor(ROOT.kBlack)
    sumHist.SetLineWidth(1)
    sumHist.Draw("SAME HIST")

    legend=ROOT.TLegend(0.70,0.8,0.95,0.9)
    legend.SetBorderSize(0)
    legend.SetLineStyle(0)
    legend.SetTextFont(42)
    legend.SetTextSize(0.03)
    legend.SetFillStyle(0)

    legend.AddEntry(hist, name, "F")
    legend.AddEntry(sumHist, "cumulative sum", "L")
    legend.Draw("SAME")



    canvas.SaveAs(plotdir+"/"+name+".pdf")
    canvas.SaveAs(plotdir+"/"+name+".png")
    canvas.Clear()

class Cut:
    types = ["==",">=","<=","<",">"]
    def __init__(self, cutstring):
        self.cut_type = None
        for t in self.types:
            if t in cutstring:
                self.cut_type = t
                break
        if not self.cut_type: sys.exit("requirement {} invalid".format(cutstring))
        split_string = cutstring.split(self.cut_type)
        self.variable = split_string[0]
        self.requirement = float(split_string[1])
        print("variable {} requires to be {} {}".format(
            self.variable, self.cut_type,self.requirement))

    def getVariable(self):
        return self.variable

    def passesCut(self, value):
        if self.cut_type == "==":
            return value == self.requirement
        if self.cut_type == ">=":
            return value >= self.requirement
        if self.cut_type == "<=":
            return value <= self.requirement
        if self.cut_type == "<":
            return value < self.requirement
        if self.cut_type == ">":
            return value > self.requirement


def get_dPhi(p1, p2):
    dphi = np.abs(p1 - p2)
    if dphi > np.pi:
        dphi = 2.*np.pi - dphi
    return dphi

def get_dEta(e1, e2):
    return np.abs(e1 - e2)

def get_dR(p1, p2, e1, e2):
    dphi = get_dPhi(p1, p2)
    deta = get_dEta(e1, e2)
    dR = np.sqrt( dphi**2 + deta**2 )
    return dR

def parse_groups(args):
    match_groups = []
    variable_list = []

    # loop groups
    for group in args:
        # split conditions
        split_group = group.split("+")
        matches = []

        # loop over match conditions
        for match in split_group:
            split_match = match.split("=")
            if len(split_match) == 2:
                variables = split_match[1]
                name = split_match[0]
            else:
                variables = split_match[0]
                name = ""

            variables = variables.split(",")
            if not len(variables) == 2:
                sys.exit("group {} does not match the required structure.".format(group))
            matches.append([name]+variables)
            variable_list+=variables
        match_groups.append(matches)

    return match_groups, list(set(variable_list))

def check_variables(variable_list, cuts, tree):
    print("checking variables in tree ...")
    for v in variable_list:
        phi = v+"_Phi"
        eta = v+"_Eta"
        print("\tchecking {}".format(v))
        if not hasattr(tree, phi):
            sys.exit("phi variable {} not found".format(phi))
        if not hasattr(tree, eta):
            sys.exit("eta variable {} not found".format(eta))
    for cut in cuts:
        if not hasattr(tree, cut.getVariable()):
            sys.exit("cut variable {} not found".format(cut.getVariable()))

    print("variable check successfull")


def match_events(tree, match_groups, cuts, options):
    number_matched_events = 0
    number_total_events = 0
    
    # generate some histograms to fill deltaR values
    if options.plot:
        hist_dict = {}
        for group in match_groups:
            for match in group:
                name = match[0]
                if not name in hist_dict:
                    hist = ROOT.TH1F(name, name, 40, 0., 4.)
                    hist_dict[name] = hist


    # event loop
    for i in xrange(tree.GetEntries()):
        tree.GetEntry(i)
        passesCuts = True
        for cut in cuts:
            if not cut.passesCut( tree.GetLeaf(cut.getVariable()).GetValue() ):
                passesCuts = False   
        if not passesCuts: continue

        if options.verbose>1:
            print("-"*20)
            print("analyzing event {}".format(i))
        number_total_events += 1

        # iterate over all groups to be matched
        all_groups_matched = True
        one_match = False
        tmp_hist_dict = {}
        for group in match_groups:
            # iterate over all neccesary matches in group
            dRs = []
            for match in group:
                name = match[0]
                phi1 = tree.GetLeaf(match[1]+"_Phi").GetValue()
                eta1 = tree.GetLeaf(match[1]+"_Eta").GetValue()
                phi2 = tree.GetLeaf(match[2]+"_Phi").GetValue()
                eta2 = tree.GetLeaf(match[2]+"_Eta").GetValue()
                # get deltaR
                dR = get_dR(phi1, phi2, eta1, eta2)
                if options.plot:
                    if not name in tmp_hist_dict:
                        tmp_hist_dict[name] = dR
                    elif tmp_hist_dict[name] >= dR:
                        tmp_hist_dict[name] = dR
                dRs.append(dR)
            if options.verbose>2:
                print(group)
                print(dRs)
            
            # check if all dRs in group match the dR requirement
            all_matched = True
            for dr in dRs:
                if not dr <= options.radius:
                    all_matched = False
                    all_groups_matched = False
            
            if all_matched: 
                if options.verbose>2: print("this group matched all dRs")
                one_match = True
            if options.verbose>2: print("\n")
            
        if options.plot:
            for key in tmp_hist_dict:
                hist_dict[key].Fill(tmp_hist_dict[key])

        if options.matchAll:
            if all_groups_matched:
                if options.verbose>2: print("all groups matched all dRs")
                number_matched_events += 1
        else:
            if one_match:
                number_matched_events += 1

    print("################################")
    match_percentage = float(number_matched_events)/float(number_total_events)*100
    print("matched {}/{} events".format(number_matched_events,number_total_events))
    print("\t= {}%".format(match_percentage))
    print("################################")

    dRlabel = "matched {:.2f}% with \\deltaR\\leq {:.1f}".format(match_percentage, options.radius)
    if options.plot:
        if not os.path.exists(options.plotdir):
            os.makedirs(options.plotdir)
        for key in hist_dict:
            draw_hist(hist_dict[key], options.plotdir, key, options.label, dRlabel, options.ymax)


if __name__ == "__main__":

    # option parser
    usage = "\n\n"+"="*100+"\n"
    usage+= "python deltaRMatcher.py -i /path/to/input/file.root -r 0.4 nameA=var1,var2+nameB=var3,var4 nameC=var5,var6\n\n"
    usage+= "additional arguments determine the matching structure\n"
    usage+= "two objects/variables to be deltaR matched are separated by ','\n"
    usage+= "groups that have to be matched at the same time are appended with '+'\n"
    usage+= "if multiple arguments are given, matches are evaluated if one of these groups is matched\n"
    usage+= "if all groups should be matched at the same time, use the option '--all'\n\n"
    usage+= "the variable names given as arguements are prefixes to the eta and phi variables in the root tree\n"
    usage+= "make sure the variables of strucutre 'var_Eta' and 'var_Phi' exist in your tree\n\n"
    usage+= "="*100

    parser = optparse.OptionParser(usage=usage)
    parser.add_option("-i","--input",dest="inputFile",default="../test/testrun_nominal_Tree.root",
        help = "input root file. default is 'testrun_nominal_Tree.root' in test directory")
    parser.add_option("-p","--plot",dest="plot",default=False,action="store_true",
        help = "generate deltaR plots with names specifed in args")
    parser.add_option("-r","--deltaR",dest="radius",default=0.4,type=float,
        help = "matching radius")
    parser.add_option("-c","--category",dest="cat",default="N_Jets>=6",
        help = "requirements on some variables, e.g. N_Jets>=6,N_BTagsM>=4")
    parser.add_option("--all",dest="matchAll",default=False,action="store_true",
        help = "match all argument groups.")
    parser.add_option("-v",dest="verbose",default=1,type=int,
        help = "verbose output")
    parser.add_option("-l","--label",dest="label",default="\\geq 6 Jets",
        help = "label for plots")    
    parser.add_option("-o","--plotDir",dest="plotdir",default="plots",
        help = "directory for plots")
    parser.add_option("-y","--ymax",dest="ymax",default=0.4,type=float,
        help = "max value for y axis of plots")

    (options, args) = parser.parse_args()

    # collect groups
    if len(args) == 0:
        print("no matching groups were specified -- using default")
        args = ['dR_HiggsB1=Reco_Higgs_BJet1,GenHiggs_B1+dR_HiggsB2=Reco_Higgs_BJet2,GenHiggs_B2', 'dR_HiggsB1=Reco_Higgs_BJet1,GenHiggs_B2+dR_HiggsB2=Reco_Higgs_BJet2,GenHiggs_B1']

    # print all groups to be matched
    print("matching groups:")
    print("\n".join(args))

    # parse groups
    match_groups, variable_list = parse_groups(args)

    # generate conditional cuts
    cuts = []
    for cut in options.cat.split(","):
        cuts.append(Cut(cut))

    # load root file
    f = ROOT.TFile(options.inputFile)
    tree = f.Get("MVATree")

    # check if all variables exist
    check_variables(variable_list, cuts, tree)

    # match stuff
    match_events(tree, match_groups, cuts, options)
