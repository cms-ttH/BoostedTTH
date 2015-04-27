import os
import sys
pattern=''
if len(sys.argv) > 1:
    pattern= sys.argv[1]
from subprocess import call

if not os.path.exists('logs'):
    os.makedirs('logs')

files = [os.path.join(root, name)
                     for root, dirs, files in os.walk('.')
                     for name in files
                     if pattern in name and name.endswith((".sh"))]
for f in files:
#    print f
    call(['qsub', '-cwd', '-S', '/bin/bash','-l', 'os=sld6', '-o', 'logs/$JOB_NAME.o$JOB_ID', '-e', 'logs/$JOB_NAME.e$JOB_ID', '-q', 'default.q', f])
