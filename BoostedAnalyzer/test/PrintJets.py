import ROOT
import sys
from DataFormats.FWLite import Events, Handle
from math import *

events = Events (sys.argv[1:])

handleJetsAK15  = Handle ("std::vector<pat::Jet>")
handleJetsAK8  = Handle ("std::vector<pat::Jet>")
labelJetsAK15 = "selectedPatJetsAK15PFPuppi"
labelJetsAK8 = "slimmedJetsPuppi"

# loop over events
count= 0
for event in events:
    print "----------------------------------------------------------------"
    event.getByLabel (labelJetsAK15, handleJetsAK15)
    event.getByLabel (labelJetsAK8, handleJetsAK8)
    # get the product
    JetsAK15 = handleJetsAK15.product()
    JetsAK8 = handleJetsAK8.product()

    for p in JetsAK15:
        print "Trimmed mass: ",p.userFloat("ak15PFJetsPuppiTrimmedMass")
        print "Filtered mass: ",p.userFloat("ak15PFJetsPuppiFilteredMass")
        print "Pruned mass: ",p.userFloat("ak15PFJetsPuppiPrunedMass")
        print "Softdrop mass: ",p.userFloat("ak15PFJetsPuppiSoftDropMass")
        print "HepTopTag mass: ",p.userFloat("hepTopTagPFJetsPuppiMassAK15")
        print "Tau 1: ",p.userFloat("NjettinessAK15Puppi:tau1")
        print "Tau 2: ",p.userFloat("NjettinessAK15Puppi:tau2")
        print "Tau 3: ",p.userFloat("NjettinessAK15Puppi:tau3")
        print "Tau 4: ",p.userFloat("NjettinessAK15Puppi:tau4")
