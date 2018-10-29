import csv
import os
import shutil
import sys
from subprocess import call

csvfile=open(sys.argv[1],'r') 
reader = csv.DictReader(csvfile, delimiter=',')

def repl(old,new,filename):
    cmd=" ".join(["sed","-i","'s|"+old+"|"+new+"|g'",filename])
    call(cmd,shell=True)

def get_list_of_systematics(filename):
    systs=[]
    with open(filename,"r") as f:
        systs=f.readlines()
    systs=[s.rstrip('\n') for s in systs]
    systs=[s.rstrip('\t') for s in systs]
    good_systs=[s for s in systs if not (s.startswith("#") or len(s)==0)]
    if len(good_systs) != len(set(good_systs)):
        print "ERROR specifying list of systematics: DUPLICATE ENTRIES"
        sys.exit()
    if not "nominal" in good_systs:
        #print "WARNING: no 'nominal' variation specified...adding it"
        good_systs.insert(0,"nominal")

    #print "Systematic variations:"
    #for syst in good_systs:
        #print "  '"+syst+"'"

    return good_systs

def split_for_systematic_variations(variations,nvariations):
    #print variations
    syst_str = ""
    systs = []
    k=0
    for i in range(len(variations)):
        if(k==nvariations):
            systs.append(syst_str)
            syst_str = ""
            k=0
        if(k==0):
            syst_str = syst_str+variations[i]
        else:
            syst_str = syst_str+","+variations[i]
        k+=1
    if(i==(len(variations)-1) and k!=nvariations):
        systs.append(syst_str)
    return systs

for row in reader:
    variation_list = get_list_of_systematics("systematicVariations.txt")
    #print variation_list
    variations_list = split_for_systematic_variations(variation_list,100)
    src='template_slimmed_ntuples_cfg.py'
    if row['isData']=='True':
        variations_list = ['nominal']
    datasets=row['dataset'].split(",")
    for variations,l in zip(variations_list,range(len(variations_list))):
        print "looking at systematic sources ",variations
        for dataset,i in zip(datasets,range(len(datasets))):
            print "looking at dataset ",dataset
            out='configs_slimmed_ntuples/'+row['name']+'_'+str(i)+"_"+str(l)+'_crab.py'
            filenames = []
            for filename in variations.split(","):
                if filename=="nominal":
                    filenames.append("ntuples_"+filename+"_Tree.root")
                else: 
                    filenames.append("ntuples_"+filename+"up"+"_Tree.root")
                    filenames.append("ntuples_"+filename+"down"+"_Tree.root")
            shutil.copy(src,out)
            repl('THEREQUESTNAME',row['name']+"_"+str(i)+"_"+str(l),out)
            repl('THEINPUTDATASET',dataset,out)
            repl('DATAERA',row['run'],out)
            repl('GLOBALTAG',row['globalTag'],out)
            repl('ISDATA',row['isData'],out)
            #repl('GENERATORNAME',row['generator'],out)
            #repl('WEIGHT',row['weight'],out)
            repl('SYSTEMATICVARIATIONS',variations,out)
            #repl('OUTPUTFILES',str(filenames).replace("'",'"'),out)
