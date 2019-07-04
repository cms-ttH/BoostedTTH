import sys
import subprocess

crabProjectList = sys.argv[1:]

for icp in crabProjectList:
  bf=open("tmpcrab.txt","w")
  bf.write("empty")
  bf.close()
  if ".log" in icp:
    continue
  print "doing ", icp
  resultfile=open("tmpcrab.txt","w")
  #if "ttH" in icp or "ttbar" in icp:
    #print "skipping icp"
    #continue
  subprocess.call(["crab status "+icp],shell=True, stdout=resultfile)
  resultfile.close()
  
  rf=open("tmpcrab.txt","r")
  rfl = list(rf)
  toResubmit=False
  for rl in rfl:
    if "failed" in rl:
      print rl
      toResubmit=True
  rf.close()
  
  if toResubmit:
    print "resubmitting", icp
    subprocess.call(["crab resubmit "+icp],shell=True)
      #subprocess.call(["crab resubmit "+icp +" --maxmemory=2500 --siteblacklist=T2_US_Florida,T2_US_UCSD,T2_US_Wisconsin,T2_US_Nebraska --sitewhitelist='T2_DE_DESY'"],shell=True)
