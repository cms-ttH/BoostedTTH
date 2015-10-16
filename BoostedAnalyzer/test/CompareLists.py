import sys

exludeVariablesInComaparison=["final_discriminant1","final_discriminant1"]

filename1 = sys.argv[1]
filename2 = sys.argv[2]

f1=open(filename1,"r")
list1=list(f1)
f2=open(filename2,"r")
list2=list(f2)

# get table headers
th1=list1[0].replace("\n","").split(",")
th2=list2[0].replace("\n","").split(",")
print th1
print th2
if th1!=th2:
  print "table headers are different"
#  exit(0)
th=th1

nEventsDifferent=0
diffSummary=[]
for t in th:
  diffSummary.append([t,0])
AllDifferences=[]

# prepare lists
shortList1=[]
for i,v in enumerate(list1):
  if i==0:
   continue
  shortList1.append(list1[i].replace("\n","").split(","))
shortList2=[]
for i,v in enumerate(list2):
  if i==0:
   continue
  shortList2.append(list2[i].replace("\n","").split(","))

Events1=[]
Events2=[]
surplusEvents1=[]
surplusEvents2=[]
EventIDs1=[]
EventIDs2=[]
evtIdx1=2
evtIdx2=2
for i in range(len(th1)):
  if th1[i]=="event":
    evtIdx1=i
for i in range(len(th2)):
  if th2[i]=="event":
    evtIdx1=2

print evtIdx1, evtIdx2
# find which list contains which events
for it in shortList1:
  EventIDs1.append(float(it[evtIdx1]))
for it in shortList2:
  EventIDs2.append(float(it[evtIdx2]))

for it in shortList1:
  if float(it[evtIdx1]) in EventIDs1 and float(it[evtIdx1]) in EventIDs2:
    Events1.append([float(v) for v in it])
  else:
    surplusEvents1.append([float(v) for v in it])
for it in shortList2:
  if float(it[evtIdx2]) in EventIDs1 and float(it[evtIdx2]) in EventIDs2:
    Events2.append([float(v) for v in it])
  else:
    surplusEvents2.append([float(v) for v in it])

nEventsTotal1=len(EventIDs1)
nEventsTotal2=len(EventIDs2)
nEventsSurplus1=len(surplusEvents1)
nEventsSurplus2=len(surplusEvents2)
print nEventsTotal1, nEventsTotal2, nEventsSurplus1, nEventsSurplus2


for i in range(min(len(Events1),999999)):
  print Events1[i]
  print Events2[i]
 # if i%1000==0:
  #  print "at event i=",i
  values1=Events1[i]
  values2=Events2[i]
  
  eventID=-1.0
  differences=[]
  for iv in range(len(values1)):
    if iv==evtIdx1:
      eventID=int(values1[iv])
      print iv
    val1=values1[iv]
    val2=values2[iv]
#    different groups different precisions
    strv1=str(val1)
    strv2=str(val2)
    dp1=strv1.find(".")
    dp2=strv2.find(".")
    minDigits=min(len(strv1[dp1+1:]),len(strv2[dp2+1:]))
    rv1=round(val1,minDigits)
    rv2=round(val2,minDigits)
    if rv1!=rv2:
      # different groups different default values
      if (val1==-99.0 and val2==0.0) or (val2==-99.0 and val1==0.0):
        continue
      if th[iv] in exludeVariablesInComaparison:
        continue
      differences.append([th[iv],val1,val2])
  if len(differences)>0:
    nEventsDifferent+=1
    AllDifferences.append(differences)
    print "differences in event ", eventID
    for d in differences:
      print d[0],"\t",d[1],"\t",d[2]
      for ds in diffSummary:
        if d[0]==ds[0]:
          ds[1]+=1

#print summary

print "\n------------------------------------------------------------"
print "\n"
print " following ",nEventsSurplus1," events are only in file1 "
print ",".join(th1)
for ev in surplusEvents1:
  print ",".join(map(str,ev))

print "\n"
print " following ",nEventsSurplus2," events are only in file2 "
print ",".join(th2)
for ev in surplusEvents2:
  print ",".join(map(str,ev))

print "\n-----------------------------------------------------------\n"
print "Summary"
print "file 1 has ", nEventsTotal1, " events in total and ", nEventsSurplus1, "exclusively"
print "file 2 has ", nEventsTotal2, " events in total and ", nEventsSurplus2, "exclusively"

print " Of the ",nEventsTotal1-nEventsSurplus1 , " events in both ", nEventsDifferent, "are different"
print "variable was different in N events"
for ds in diffSummary:
  print ds[0],"\t", ds[1]

corrTable=[]
valTable=[]
longestStringLength=0
for t in th:
  longestStringLength=max(len(t),longestStringLength)
#print longestStringLength
longestStringLength

for i in range(longestStringLength):
  thisLine=[]
  firstString=""
  for k in range(longestStringLength):
    firstString+=" "
  firstString+="|"
  thisLine.append(firstString)
  for t in th:
#    print t
    thisString="  "
    if len(t)>=i+1:
      thisString+=t[i]
    else:
      thisString+=" "
    thisString+="  "
    thisLine.append(thisString)
  corrTable.append(thisLine)




for t in th:
  thisLine=[]
  for tt in th:
    thisLine.append(0)
  valTable.append(thisLine)

for d in AllDifferences:
#  print d
  zippedD=zip(*d)
  thisVars=[]
  for z in zippedD[0]:
    thisVars.append(z.replace("\'",""))
  for i,t in enumerate(th):
    for j, s in enumerate(th):
     # print t, s, thisVars
      if t in thisVars and s in thisVars:
        valTable[i][j]+=1

for i,l in enumerate(valTable):
  firstString=th[i]
  while len(firstString)<longestStringLength:
    firstString+=" "
  firstString+="|"
  thisLine=[firstString]
  for v in l:
    thisString=str(v)
    while len(thisString)<5:
      thisString+=" "
    thisLine.append(thisString)
  corrTable.append(thisLine)

print "\n----------------------------------------------_"
print "correlations"
for l in corrTable:
  print "".join(map(str,l))
  


















