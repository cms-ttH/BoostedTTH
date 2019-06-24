import ROOT
import sys
from DataFormats.FWLite import Events, Handle
from math import *

events = Events (sys.argv[1:])

handleJetsAK15  = Handle ("std::vector<pat::Jet>")
handleJetsAK8  = Handle ("std::vector<pat::Jet>")
handleJetsAK4  = Handle ("std::vector<pat::Jet>")
labelJetsAK15 = "selectedUpdatedPatJetsAK15WithPuppiDaughters"
labelJetsAK8 = "selectedUpdatedPatJetsAK8WithPuppiDaughters"
labelJetsAK4 = "selectedPatJetsAK4PFPuppi"
# loop over events
count= 0
for event in events:
    print "----------------------------------------------------------------"
    event.getByLabel (labelJetsAK15, handleJetsAK15)
    event.getByLabel (labelJetsAK8, handleJetsAK8)
    event.getByLabel (labelJetsAK4, handleJetsAK4)
    # get the product
    JetsAK15 = handleJetsAK15.product()
    JetsAK8 = handleJetsAK8.product()
    JetsAK4 = handleJetsAK4.product()

    for jet in JetsAK15:
        print "AK15 jet pt: ",jet.pt()
        print "AK15 jet eta: ",jet.eta()
        #print "AK15 prob Tbqq: ", jet.bDiscriminator('pfMassDecorrelatedDeepBoostedJetTags:probTbqq')
        #print "AK15 prob Tbcq: ", jet.bDiscriminator('pfMassDecorrelatedDeepBoostedJetTags:probTbcq')
        #print "AK15 prob Tbq: ", jet.bDiscriminator('pfMassDecorrelatedDeepBoostedJetTags:probTbq')
        #print "AK15 prob Tbc: ", jet.bDiscriminator('pfMassDecorrelatedDeepBoostedJetTags:probTbc')
        top_prob = jet.bDiscriminator('pfMassDecorrelatedDeepBoostedJetTags:probTbqq')+jet.bDiscriminator('pfMassDecorrelatedDeepBoostedJetTags:probTbcq')+jet.bDiscriminator('pfMassDecorrelatedDeepBoostedJetTags:probTbq')+jet.bDiscriminator('pfMassDecorrelatedDeepBoostedJetTags:probTbc')
        qcd_prob = jet.bDiscriminator('pfMassDecorrelatedDeepBoostedJetTags:probQCDbb')+jet.bDiscriminator('pfMassDecorrelatedDeepBoostedJetTags:probQCDcc')+jet.bDiscriminator('pfMassDecorrelatedDeepBoostedJetTags:probQCDb')+jet.bDiscriminator('pfMassDecorrelatedDeepBoostedJetTags:probQCDc')+jet.bDiscriminator('pfMassDecorrelatedDeepBoostedJetTags:probQCDothers')
        #print top_prob
        #print qcd_prob
        if(top_prob+qcd_prob>0.):
            print "AK15 TvsQCD 1: ", top_prob/(top_prob+qcd_prob)
            print "AK15 TvsQCD 2: ", jet.bDiscriminator('pfMassDecorrelatedDeepBoostedDiscriminatorsJetTags:TvsQCD')
        #print "Trimmed mass: ",p.userFloat("ak15PFJetsPuppiTrimmedMass")
        #print "Filtered mass: ",p.userFloat("ak15PFJetsPuppiFilteredMass")
        #print "Pruned mass: ",p.userFloat("ak15PFJetsPuppiPrunedMass")
        print "Softdrop mass: ",jet.userFloat("ak15PFJetsPuppiSoftDropMass")
        #print "HepTopTag mass: ",p.userFloat("hepTopTagPFJetsPuppiMassAK15")
        #print "Tau 1: ",p.userFloat("NjettinessAK15Puppi:tau1")
        #print "Tau 2: ",p.userFloat("NjettinessAK15Puppi:tau2")
        #print "Tau 3: ",p.userFloat("NjettinessAK15Puppi:tau3")
        #print "Tau 4: ",p.userFloat("NjettinessAK15Puppi:tau4")
    for jet in JetsAK8:
        print "AK8 jet pt: ",jet.pt()
        print "AK8 jet eta: ",jet.eta()
        #print "AK8 prob Tbqq: ", jet.bDiscriminator('pfMassDecorrelatedDeepBoostedJetTags:probTbqq')
        #print "AK8 prob Tbcq: ", jet.bDiscriminator('pfMassDecorrelatedDeepBoostedJetTags:probTbcq')
        #print "AK8 prob Tbq: ", jet.bDiscriminator('pfMassDecorrelatedDeepBoostedJetTags:probTbq')
        #print "AK8 prob Tbc: ", jet.bDiscriminator('pfMassDecorrelatedDeepBoostedJetTags:probTbc')
        top_prob = jet.bDiscriminator('pfMassDecorrelatedDeepBoostedJetTags:probTbqq')+jet.bDiscriminator('pfMassDecorrelatedDeepBoostedJetTags:probTbcq')+jet.bDiscriminator('pfMassDecorrelatedDeepBoostedJetTags:probTbq')+jet.bDiscriminator('pfMassDecorrelatedDeepBoostedJetTags:probTbc')
        qcd_prob = jet.bDiscriminator('pfMassDecorrelatedDeepBoostedJetTags:probQCDbb')+jet.bDiscriminator('pfMassDecorrelatedDeepBoostedJetTags:probQCDcc')+jet.bDiscriminator('pfMassDecorrelatedDeepBoostedJetTags:probQCDb')+jet.bDiscriminator('pfMassDecorrelatedDeepBoostedJetTags:probQCDc')+jet.bDiscriminator('pfMassDecorrelatedDeepBoostedJetTags:probQCDothers')
        #print top_prob
        #print qcd_prob
        if(top_prob+qcd_prob>0.):
            print "AK8 TvsQCD 1: ", top_prob/(top_prob+qcd_prob)
            print "AK8 TvsQCD 2: ", jet.bDiscriminator('pfMassDecorrelatedDeepBoostedDiscriminatorsJetTags:TvsQCD')
    #for jet in JetsAK4:
        #print "DeepJet prob b: ",jet.bDiscriminator("pfDeepFlavourJetTags:probb")
        #print "AK4 jet pt: ",jet.pt()
        #print "AK4 jet eta: ",jet.eta()
