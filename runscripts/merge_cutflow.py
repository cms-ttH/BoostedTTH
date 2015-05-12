#!/usr/bin/env python
import sys
first=True
sumlist=[]
yieldlist=[]
outfile = sys.argv[1]
for filename in sys.argv[2:]:
    numbers=[]
    steps=[]
    nevents=[]
    yields=[]
    f = open(filename)
    lines=f.read().splitlines()
    if first:
        nlines=len(lines)
    else:
        if len(lines)!=nlines:
            print 'file', filename,'has wrong number of lines (',len(lines),')'
            break
    for line in lines:        
        linelist=line.split(' : ')
        numbers.append(linelist[0])
        steps.append(linelist[1])
        nevents.append(int(linelist[2]))
        yields.append(float(linelist[3]))
    if first:       
        sumlist=list(nevents)
        yieldlist=list(yields)
        first=False
    else:
        sumlist = [sum(x) for x in zip(sumlist, nevents)]
        yieldlist = [sum(x) for x in zip(yieldlist, yields)]
    f.close()
ff=open(outfile,"w")
for a,b,c,d in zip(numbers,steps,sumlist,yieldlist):
    print str(a)+" : "+str(b)+" : "+str(c)+" : "+str(d)
    ff.write(str(a)+" : "+str(b)+" : "+str(c)+" : "+str(d)+"\n")

ff.close
