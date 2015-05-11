#!/usr/bin/env python
# submits alls *.sh files to cluster
# usage: ./sup.py path/to/scripts [script_pattern]
import os
import sys
pattern=''
path=''
if len(sys.argv) > 1:
    path= sys.argv[1]+'/'
if len(sys.argv) > 2:
    pattern= sys.argv[2]
from subprocess import call

if not os.path.exists('logs'):
    os.makedirs('logs')

files = [os.path.join(root, name)
                     for root, dirs, files in os.walk('./'+path)
                     for name in files
                     if pattern in name and name.endswith((".sh"))]
for f in files:
#    print f
    call(['qsub', '-cwd', '-S', '/bin/bash','-l', 'os=sld6', '-l' ,'h_vmem=2000M', '-l', 's_vmem=2000M' ,'-o', 'logs/$JOB_NAME.o$JOB_ID', '-e', 'logs/$JOB_NAME.e$JOB_ID', '-q', 'default.q', f])
