#!/cvmfs/cms.cern.ch/slc6_amd64_gcc481/cms/cmssw/CMSSW_7_2_3/external/slc6_amd64_gcc481/bin/python

import ROOT

fileDir = "/nfs/dust/cms/user/shwillia/BoostedTrees/Spring15/TopTagging/"

trueFileDir = fileDir+"MC_Powheg_TTbar_Tree.root"
falseFileDir = fileDir+"MC_Powheg_TTbar_Tree.root"

trueDef = "(TopJet_Top_Pt>0)&&((TopJet_Dr_GenB>=0&&TopJet_Dr_GenB<1.5)&&(TopJet_Dr_GenQ1>=0&&TopJet_Dr_GenQ1<1.5)&&(TopJet_Dr_GenQ2>=0&&TopJet_Dr_GenQ2<1.5))"
falseDef = "(TopJet_Top_Pt>0)&&(((TopJet_Dr_GenB>=0&&TopJet_Dr_GenB>1.5)||(TopJet_Dr_GenQ1>=0&&TopJet_Dr_GenQ1>1.5)||(TopJet_Dr_GenQ2>=0&&TopJet_Dr_GenQ2>1.5))&&(TopJet_Dr_GenTopHad>=0&&TopJet_Dr_GenTopHad>2.0))"

trueFile = ROOT.TFile(trueFileDir)
falseFile = ROOT.TFile(falseFileDir)

trueTree = trueFile.Get("MVATree")
falseTree = falseFile.Get("MVATree")

variableNames = [ ("TopJet_Top_M","TopJet_Top_M",100,0.,300.),
                  ("TopJet_MRatio_23_Top","TopJet_M23/TopJet_Top_M",80,0.,1.),
                  ("TopJet_Atan_1213","atan(TopJet_M12/TopJet_M13)",80,0.,2.),
                  ("TopJet_MRatio_W_Top","TopJet_MRatio_W_Top",80,0.,1.),
                  ("TopJet_Atan_BW1W2","atan(TopJet_BW1_M/TopJet_BW2_M)",80,0.,2.),
                  ("TopJet_MRatio_Wbtag_Top","TopJet_MRatio_Wbtag_Top",80,0.,1.),
                  ("TopJet_Atan_BW1W2btag","atan(TopJet_BW1btag_M/TopJet_BW2btag_M)",80,0.,2.)
                ]

outFile = ROOT.TFile("toplikelihoodtaggerhistos.root","RECREATE")

for name,var,bins,xmin,xmax in variableNames:
  
  trueHist = ROOT.TH1F(name+"_True",name+"_True",bins,xmin,xmax)
  falseHist = ROOT.TH1F(name+"_False",name+"_False",bins,xmin,xmax)
  
  trueTree.Draw(var+">>"+name+"_True",trueDef)
  falseTree.Draw(var+">>"+name+"_False",falseDef)

  trueHist.Scale(1/trueHist.Integral())
  falseHist.Scale(1/falseHist.Integral())
  
  trueHist.Write()
  falseHist.Write()

outFile.Close()

trueFile.Close()
falseFile.Close()
