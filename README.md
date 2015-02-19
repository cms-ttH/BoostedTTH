BoostedTTH
=======

CMSSW tools for analyzing TTH events with boosted objects

## Installation
Follow These Steps:

    cmsrel CMSSW_7_2_3
    cd CMSSW_7_2_3/src
    cmsenv

    voms-proxy-init --voms cms

    git clone https://github.com/cms-ttH/MiniAOD.git
    git clone https://github.com/cms-ttH/BoostedTTH.git
    
    scram b -j 32
