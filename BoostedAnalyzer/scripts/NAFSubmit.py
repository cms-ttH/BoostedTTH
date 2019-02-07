#!/usr/bin/env python

import sys
import os
import glob
import numpy as np
import subprocess 
import stat
import re
import time
import optparse


def submitToBatch(workdir, list_of_shells, memory_, disk_, runtime_, use_proxy, proxy_dir_, name_ ):
    ''' submit the list of shell script to the NAF batch system '''

    if name_!="":
        name_ = name_+"_"
    
    # write array script for submission
    arrayScript = writeArrayScript(workdir, list_of_shells, name_)

    # write submit script for submission
    submitScript = writeSubmitScript(workdir, arrayScript, len(list_of_shells), memory_, disk_, runtime_, use_proxy, proxy_dir_, name_)
        
    # submit the whole thing
    jobID = condorSubmit( submitScript )
    return [jobID]

def writeArrayScript(workdir, files, name_):
    path = workdir+"/"+name_+"arraySubmit.sh"

    code = """
#!/bin/bash
subtasklist=(
%(tasks)s
)
thescript=${subtasklist[$SGE_TASK_ID]}
echo "${thescript}"
echo "$SGE_TASK_ID"
. $thescript
    """ % ({"tasks":"\n".join(files)})

    with open(path, "w") as f:
        f.write(code)

    st = os.stat(path)
    os.chmod(path, st.st_mode | stat.S_IEXEC)
    
    print("wrote array script "+str(path))
    return path


def writeSubmitScript(workdir, arrayScript, nScripts, memory_, disk_, runtime_, use_proxy, proxy_dir_, name_):
    path = workdir+"/"+name_+"submitScript.sub"
    logdir = workdir+"/logs"
    if not os.path.exists(logdir):
        os.makedirs(logdir)

    code = """
universe = vanilla
executable = /bin/zsh
arguments = {arg}
error  = {dir}/{name}submitScript.$(Cluster)_$(ProcId).err
log    = {dir}/{name}submitScript.$(Cluster)_$(ProcId).log
output = {dir}/{name}submitScript.$(Cluster)_$(ProcId).out
run_as_owner = true
RequestMemory = {memory}
RequestDisk = {disk}
+RequestRuntime = {runtime}
""".format(
        arg = arrayScript,
        dir = logdir,
        memory = memory_,
        disk = disk_,
        runtime = runtime_,
        name = name_)
    if use_proxy:
        code+="""
environment = X509_USER_PROXY={proxy_dir}
getenv = True
use_x509userproxy = True
x509userproxy = {proxy_dir}""".format(proxy_dir = proxy_dir_)
    code+="""
Queue Environment From ("""
    for taskID in range(nScripts):
        code += "\"SGE_TASK_ID="+str(taskID+1)+"\"\n"
    code += ")"

    with open(path, "w") as f:
        f.write(code)

    print("wrote submit script "+str(path))
    return path

def condorSubmit(submitPath):
    submitCommand = "condor_submit -terse -name bird-htc-sched12.desy.de " + submitPath
    print("submitting:")
    print(submitCommand)
    tries = 0
    jobID = None
    while not jobID:
        process = subprocess.Popen(submitCommand.split(), stdout = subprocess.PIPE, stderr = subprocess.STDOUT, stdin = subprocess.PIPE)
        process.wait()
        output = process.communicate()
        try:
            jobID = int(output[0].split(".")[0])
        except:
            print("something went wrong with calling the condir_submit command, submission of jobs was not successful")
            print("DEBUG:")
            print(output)
            tries += 1
            jobID = None
            time.sleep(60)
        if tries>10:
            print("job submission was not successful after ten tries - exiting without JOBID")
            sys.exit(-1)
    return jobID




def monitorJobStatus(jobIDs = None):
    allfinished = False
    errorcount = 0
    print("checking job status in condor_q ...")

    command = ["condor_q", "-name", "bird-htc-sched12.desy.de"]
    if jobIDs:
        command += jobIDs
        command = [str(c) for c in command]
    command.append("-totals")

    while not allfinished:
        time.sleep(30)
        
        a = subprocess.Popen(command, stdout=subprocess.PIPE,stderr=subprocess.STDOUT,stdin=subprocess.PIPE)
        a.wait()
        qstat = a.communicate()[0]

        nrunning = -1
        queryline = [line for line in qstat.split("\n") if "Total for query" in line] 
        if len(queryline) == 1:
            jobsRunning = int(re.findall(r'\ [0-9]+\ running', queryline[0])[0][1:-8])
            jobsIdle = int(re.findall(r'\ [0-9]+\ idle', queryline[0])[0][1:-5])
            jobsHeld = int(re.findall(r'\ [0-9]+\ held', queryline[0])[0][1:-5])

            nrunning = jobsRunning + jobsIdle + jobsHeld

            print("{:4d} running | {:4d} idling | {:4d} held |\t total: {:4d}".format(jobsRunning, jobsIdle, jobsHeld, nrunning))

            errorcount = 0
            if nrunning == 0:
                print("waiting on no more jobs - exiting loop")
                allfinished=True
        else:
            errorcount += 1
            # sometimes condor_q is not reachable - if this happens a lot something is probably wrong
        
            print("line does not match query")
            if errorcount == 30:
                print("something is off - condor_q has not worked for 15 minutes ...")
                print("exiting condor_q (jobs are probably still in queue")
                sys.exit()


    print("all jobs are finished - exiting monitorJobStatus")
    return




if __name__ == "__main__":
    parser = optparse.OptionParser(usage="%prog [options] files")
    parser.add_option("-f","--folder", dest = "folder", default = None, metavar = "FOLDER",
        help = "Specify relative path to a folder from which all files are to be submitted.")
    
    parser.add_option("-p","--pattern", dest = "pattern", default = None, metavar = "'PATTERN'",
        help = "Specify a pattern to match files in FOLDER, e.g. '_test'.")

    parser.add_option("-m","--monitorStatus", action = "store_true", dest = "monitorStatus", default = False, metavar = "MONITORSTATUS",
        help = "Monitor the job status after submission with 'condor_q' until all jobs are done.")

    parser.add_option("-o","--outputdir", dest = "outputdir", default = os.path.dirname(os.path.realpath(__file__)), metavar = "OUTPUTDIR",
        help = "Path to output directory for log files and submit scripts (relative or absolute).")
    
    parser.add_option("-M","--memory",type="string",default="2000",dest="memory",metavar = "MEMORY",
        help = "Amount of memory in MB which is requested for the machines")
    
    parser.add_option("-d","--disk",type="string",default="2000",dest="disk",metavar = "DISK",
        help = "Amount of disk space in MB which is requested for the machines")
    
    parser.add_option("-r","--runtime",type="string",default="180",dest="runtime",metavar = "RUNTIME",
        help = "Amount of runtime in minutes which is requested for the machines")
    
    parser.add_option("-u","--useproxy",action="store_true",default=False,dest="useproxy",metavar = "USEPROXY",
        help = "Use voms proxy")
    
    parser.add_option("-v","--vomsproxy",type="string",default="",dest="vomsproxy",metavar = "VOMSPROXY",
        help = "Path to the VOMS proxy file")
    
    parser.add_option("-n","--name",type="string",default="",dest="name",metavar = "NAME",
        help = "Name for this submit job")

    (opts, args) = parser.parse_args()

    if opts.useproxy and not opts.vomsproxy:
        parser.error('If flag to use proxy is set, a path to the proxy file has to be provided')
    
    # get files to submit
    if opts.folder:
        filepath = opts.folder+"/*.sh"
        submit_files = glob.glob(filepath)
    else:
        submit_files = [f for f in args if f.endswith(".sh")]


    # check for naming pattern
    if opts.pattern:
        print(opts.pattern)
        submit_files = [f for f in submit_files if opts.pattern in f]

    # print list of files to submit
    print("-"*40)
    print("number of files to submit: {}".format(len(submit_files)))
    for f in submit_files: print("    {}".format(f))
    print("-"*40)

    
    # setup workdir
    workdir = opts.outputdir+"/"
    if not os.path.exists(workdir):
        os.makedirs(workdir)
    print("output directory for logfiles, etc: {}".format(workdir))


    # submit to batch
    jobIDs = submitToBatch(workdir, submit_files, opts.memory, str(int(opts.disk)*1000), str(int(opts.runtime)*60), opts.useproxy, opts.vomsproxy, opts.name)
    print("submitted jobs with IDs: {}".format(jobIDs))
    
    # monitor job status
    if opts.monitorStatus:
        monitorJobStatus(jobIDs)

    print("done.")


