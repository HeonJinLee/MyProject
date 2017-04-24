import os

s = os.environ['PATH']
print s

all = os.environ.keys()
all.sort()

for i in all:
    print "%s = %s" % (i,os.environ['i'])
