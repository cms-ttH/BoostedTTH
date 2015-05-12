#!/usr/bin/env python
# creates scripts to run cmssw on naf cluster
# usage: ./get_filenames.py /folder/containing/rootfiles filepattern_without_wildcards name [number_of_jobs XS sum_pos_minus_neg_events sampleID]
import os
import sys
import stat   
path= sys.argv[1]
pattern= sys.argv[2]
samplename= sys.argv[3]
njobs=9999999
xs="1"
mcevents="1000000"
sampleID="1"
if len(sys.argv) > 4:
    njobs=int(sys.argv[4])
if len(sys.argv) > 5:
    xs=sys.argv[5]
if len(sys.argv) > 6:
    mcevents=sys.argv[6]
if len(sys.argv) > 7:
    sampleID=sys.argv[7]

outpath='/nfs/dust/cms/user/hmildner/trees/'
scriptpath='/nfs/dust/cms/user/hmildner/CMSSW_7_2_3/src/BoostedTTH/runscripts/scripts'
cmsswcfgpath='/nfs/dust/cms/user/hmildner/CMSSW_7_2_3/src/BoostedTTH/BoostedAnalyzer/test/boostedAnalysis_nosel_cfg.py'
cmsswpath='/nfs/dust/cms/user/hmildner/CMSSW_7_2_3/'

print 'path',path
print 'samplename',samplename
print 'njobs',njobs
print 'sampleID',sampleID
print 'xs',xs
print 'mcevents',mcevents
print 'outpath',outpath
print 'scriptpath',scriptpath
print 'cmsswcfgpath',cmsswcfgpath
print 'cmsswpath',cmsswpath

if not os.path.exists(scriptpath):
    os.makedirs(scriptpath)


script="""#!/bin/bash
export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch
source $VO_CMS_SW_DIR/cmsset_default.sh
"""
script+='cd '+cmsswpath+'/src\neval `scram runtime -sh`\n'

files = [os.path.join(root, name)
                     for root, dirs, files in os.walk(path)
                     for name in files
                     if pattern in name and name.endswith((".root"))]
njobs=min(len(files),njobs)
for ijob in range(njobs):
    # job ijob
    filename=scriptpath+'/'+samplename+'_'+str(ijob)+'.sh'
    f=open(filename,'w')
    f.write(script)
    jobfilelist=[]
    for i in range(ijob*len(files)/njobs,(ijob+1)*len(files)/njobs):
        jobfilelist.append('file:'+files[i])
    f.write('export FILENAMES="'+' '.join(jobfilelist)+'"\n')
    f.write('export OUTFILENAME="'+outpath+'/'+samplename+'_'+str(ijob)+'"\n')
    f.write('export XS="'+xs+'"\n')
    f.write('export MCEVENTS="'+mcevents+'"\n')
    f.write('export SAMPLEID="'+sampleID+'"\n')
    f.write('cmsRun '+cmsswcfgpath+'\n')
    st = os.stat(filename)
    os.chmod(filename, st.st_mode | stat.S_IEXEC)


