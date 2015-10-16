import sys

filename1 = sys.argv[1]

outfileSL=open("KIT_syncHBB/onlySL/SL_"+filename1.split("/",1)[1],"w")
outfileDL=open("KIT_syncHBB/onlyDL/DL_"+filename1.split("/",1)[1],"w")

f1=open(filename1,"r")
list1=list(f1)

th1=list1[0].replace("\n","").split(",")

listlist=[]
for l in list1:
  listlist.append(l.split(","))
#print listlist

print th1

# find isSL and isDL indices
isSLidx=3
isSLidx=4
for i in range(len(th1)):
  if th1[i]=="is_SL":
    isSLidx=i
  if th1[i]=="is_DL":
    isDLidx=i
print isSLidx, isDLidx

outfileSL.write(list1[0])
outfileDL.write(list1[0])

for i in range(len(list1)):
  if (listlist[i][isSLidx]=="1" and listlist[i][isDLidx]=="0" ) or ( listlist[i][isSLidx]=="1.0" and listlist[i][isDLidx]=="0.0" ):
    outfileSL.write(list1[i])
  if (listlist[i][isSLidx]=="0" and listlist[i][isDLidx]=="1" ) or ( listlist[i][isSLidx]=="0.0" and listlist[i][isDLidx]=="1.0" ):
    outfileDL.write(list1[i])

outfileSL.close()
outfileDL.close()














































