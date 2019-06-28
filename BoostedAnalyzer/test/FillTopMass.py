import ROOT
import sys
from DataFormats.FWLite import Events, Handle
from math import *

ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)

events = Events (sys.argv[1:])

handleJetsAK15  = Handle ("std::vector<pat::Jet>")
handleJetsAK8  = Handle ("std::vector<pat::Jet>")
handleJetsAK4  = Handle ("std::vector<pat::Jet>")
labelJetsAK15 = "selectedUpdatedPatJetsAK15WithPuppiDaughters"
labelJetsAK8 = "selectedUpdatedPatJetsAK8WithPuppiDaughters"
labelJetsAK4 = "selectedPatJetsAK4PFPuppi"

top_mass_ak15_hist = ROOT.TH1D("ak15_softdrop_jet_mass","SoftDrop Jet Mass",100,40,240)
top_mass_ak8_hist = ROOT.TH1D("ak8_softdrop_jet_mass","SoftDrop Jet Mass",100,40,240)

# loop over events
count= 0
for event in events:
    count+=1
    if count%1000==0:
        print count
    #print "----------------------------------------------------------------"
    event.getByLabel (labelJetsAK15, handleJetsAK15)
    event.getByLabel (labelJetsAK8, handleJetsAK8)
    event.getByLabel (labelJetsAK4, handleJetsAK4)
    # get the product
    JetsAK15 = handleJetsAK15.product()
    JetsAK8 = handleJetsAK8.product()
    JetsAK4 = handleJetsAK4.product()

    for jet in JetsAK15:
        if(jet.userFloat("NjettinessAK15Puppi:tau2")==0. or jet.userFloat("NjettinessAK15Puppi:tau3")==0.):
            continue
        if(jet.bDiscriminator('pfMassDecorrelatedDeepBoostedDiscriminatorsJetTags:TvsQCD')>0.8 and 
           jet.pt()>200 and 
           jet.userFloat("NjettinessAK15Puppi:tau3")/jet.userFloat("NjettinessAK15Puppi:tau2")<0.6
           ):
            top_mass_ak15_hist.Fill(jet.userFloat("ak15PFJetsPuppiSoftDropMass"))
    for jet in JetsAK8:
        if(jet.userFloat("NjettinessAK8Puppi:tau2")==0. or jet.userFloat("NjettinessAK8Puppi:tau3")==0.):
            continue
        if(jet.bDiscriminator('pfMassDecorrelatedDeepBoostedDiscriminatorsJetTags:TvsQCD')>0.8 and 
           jet.pt()>200 and 
           jet.userFloat("NjettinessAK8Puppi:tau3")/jet.userFloat("NjettinessAK8Puppi:tau2")<0.6
           ):
            top_mass_ak8_hist.Fill(jet.userFloat("ak8PFJetsPuppiSoftDropMass"))

c=ROOT.TCanvas()
l=ROOT.TLegend(0.3,0.3)
l.AddEntry(top_mass_ak15_hist,"AK15 PFPuppi SoftDrop Jets","l")
l.AddEntry(top_mass_ak8_hist,"AK8 PFPuppi SoftDrop Jets","l")
top_mass_ak15_hist.SetLineColor(ROOT.kRed)
top_mass_ak8_hist.SetLineColor(ROOT.kBlue)
top_mass_ak15_hist.Draw("histe")
top_mass_ak8_hist.Draw("histesame")
l.SetFillStyle(0)
l.SetBorderSize(0)
l.Draw("same")
c.Print("top_mass.pdf")

file = ROOT.TFile("test.root","RECREATE")
file.WriteTObject(top_mass_ak15_hist)
file.WriteTObject(top_mass_ak8_hist)
file.Close()
