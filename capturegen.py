#!/usr/bin/env python

#   31  30  29  28
# 27  26  25  24
#   23  22  21  20
# 19  18  17  16
#   15  14  13  12
# 11  10  09  08
#   07  06  05  04
# 03  02  01  00

fwdmoves =   [ ( 0, 4),( 0, 5),( 1, 5),( 1, 6),( 2, 6),( 2, 7),( 3, 7),
               ( 4, 8),( 5, 8),( 5, 9),( 6, 9),( 6,10),( 7,10),( 7,11),
               ( 8,12),( 8,13),( 9,13),( 9,14),(10,14),(10,15),(11,15),
               (12,16),(13,16),(13,17),(14,17),(14,18),(15,18),(15,19),
               (16,20),(16,21),(17,21),(17,22),(18,22),(18,23),(19,23),
               (20,24),(21,24),(21,25),(22,25),(22,26),(23,26),(23,27),
               (24,28),(24,29),(25,29),(25,30),(26,30),(26,31),(27,31)]

revmoves = [(t, f) for f, t in fwdmoves]
revmoves.sort() ;

fwdjumps = [( 0, 5, 9),( 1, 5, 8),( 1, 6,10),( 2, 6, 9),( 2, 7,11),( 3, 7,10),
            ( 4, 8,13),( 5, 8,12),( 5, 9,14),( 6, 9,13),( 6,10,15),( 7,10,14),
            ( 8,13,17),( 9,13,16),( 9,14,18),(10,14,17),(10,15,19),(11,15,18),
            (12,16,21),(13,16,20),(13,17,22),(14,17,21),(14,18,23),(15,18,22),
            (16,21,25),(17,21,24),(17,22,26),(18,22,25),(18,23,27),(19,23,26),
            (20,24,29),(21,24,28),(21,25,30),(22,25,29),(22,26,31),(23,26,30)]

revjumps = [(t,m,f) for f,m,t in fwdjumps]
revjumps.sort()


def preamble(name):
    print """
int
generate%scaptures(CheckerBoard *b, CheckerBoard child[MAXMOVES], BitBoard m)
{
    CheckerBoard tmp ;
    BitBoard next, c, U = ~(b->W|b->R) ;
    int n = 0 ;

    while(m) {
        next = m & (m - 1) ;
	c = m ^ next ;
	m = next ;

	if ((b->K&c) == 0) {
	    switch(c) {""" % name

def midamble():
    print """
            }
	} else {
	    /* KING */
	    switch(c) {
"""
def postamble():
    print """
    	    }
	}
    }

    return n ;
}
"""

def resolvepreamble(name):
    print """
int
resolve%scaptures(CheckerBoard *b, CheckerBoard child[MAXMOVES], int nbefore, BitBoard m)
{
    CheckerBoard tmp ;
    BitBoard U = ~(b->W|b->R) ;
    int n = nbefore ;

    if ((b->K&m) == 0) {
	switch(m) {""" % name

def resolvemidamble():
    print """
            }
	} else {
	    /* KING */
	    switch(m) {
"""

def resolvepostamble():
    print """
	}
    }
    return 0 ;
}"""


class CaptureGenerator:
    def __init__(self, name, myfield, hisfield, fwd, rev, kinging):
	self.name = name
	self.myfield = myfield
	self.hisfield = hisfield 
	self.fwd = fwd
	self.rev = rev 
	self.kinging = kinging
    def generatecapture(self):
	mjumps = {}
	for (f,m,t) in self.fwd:
	    mjumps[f] = mjumps.get(f, []) + [(m, t)]
	kjumps = {}
	for (f,m,t) in self.fwd:
	    kjumps[f] = kjumps.get(f, []) + [(m, t)]
	for (f,m,t) in self.rev:
	    kjumps[f] = kjumps.get(f, []) + [(m, t)]
	preamble(self.name)

	mkeys = mjumps.keys()
	mkeys.sort()
	for f in mkeys:
	     print "            case 0x%08x:" % (1<<f)
	     for m, t in mjumps[f]:
		 print "                if ((U&(1<<%d))&&(b->%s&(1<<%d))) {" % (t, self.hisfield, m)
	  	 print "                    tmp = *b ;"
		 print "		    tmp.%s &= ~(1<<%d) ;" % (self.hisfield, m)
		 print "		    tmp.K &= ~(1<<%d) ;" % m
		 print "                    tmp.%s ^= ((1<<%d)|(1<<%d)) ;" % (self.myfield, f, t)
		 if (t in self.kinging):
			print "                    tmp.K |= (1<<%d);" % t ;
			print "                    child[n++] = tmp ;"
		 else:
			print "                    n = resolve%scaptures(&tmp, child, n, 1<<%d) ;" % (self.name, t)
		 print "                }"
	     print "                break ;"
	midamble()

	kkeys = kjumps.keys()
	kkeys.sort()

	for f in kkeys:
	     print "            case 0x%08x:" % (1<<f)
	     for m, t in kjumps[f]:
		 print "                if ((U&(1<<%d))&&(b->%s&(1<<%d))) {" % (t, self.hisfield, m)
	  	 print "                    tmp = *b ;"
		 print "		    tmp.%s &= ~(1<<%d) ;" % (self.hisfield, m)
		 print "		    tmp.K &= ~(1<<%d) ;" % m
		 print "                    tmp.%s ^= ((1<<%d)|(1<<%d)) ;" % (self.myfield, f, t)
		 print "                    tmp.K ^= ((1<<%d)|(1<<%d)) ;" % (f, t) 
		 print "                    n = resolve%scaptures(&tmp, child, n, 1<<%d) ;" % (self.name, t)
		 print "                }"
	     print "                break ;"
	postamble()
    def generateresolve(self):
	mjumps = {}
	for (f,m,t) in self.fwd:
	    mjumps[f] = mjumps.get(f, []) + [(m, t)]
	kjumps = {}
	for (f,m,t) in self.fwd:
	    kjumps[f] = kjumps.get(f, []) + [(m, t)]
	for (f,m,t) in self.rev:
	    kjumps[f] = kjumps.get(f, []) + [(m, t)]
	resolvepreamble(self.name)

	mkeys = mjumps.keys()
	mkeys.sort()
	for f in mkeys:
	     print "            case 0x%08x:" % (1<<f)
	     for m, t in mjumps[f]:
		 print "                if ((U&(1<<%d))&&(b->%s&(1<<%d))) {" % (t, self.hisfield, m)
	  	 print "                    tmp = *b ;"
		 print "		    tmp.%s &= ~(1<<%d) ;" % (self.hisfield, m)
		 print "		    tmp.K &= ~(1<<%d) ;" % m
		 print "                    tmp.%s ^= ((1<<%d)|(1<<%d)) ;" % (self.myfield, f, t)
		 if (t in self.kinging):
			print "                    tmp.K |= (1<<%d);" % t ;
			print "                    child[n++] = tmp ;"
		 else:
			print "                    n = resolve%scaptures(&tmp, child, n, 1<<%d) ;" % (self.name, t)
		 print "                }"
	     print "                if (n == nbefore) {"
	     print "                    child[n++] = *b ;"
	     print "                }"
	     print "                return n ;"
	print "      default: child[n++] = *b ; return n;"
	resolvemidamble()

	kkeys = kjumps.keys()
	kkeys.sort()

	for f in kkeys:
	     print "            case 0x%08x:" % (1<<f)
	     for m, t in kjumps[f]:
		 print "                if ((U&(1<<%d))&&(b->%s&(1<<%d))) {" % (t, self.hisfield, m)
	  	 print "                    tmp = *b ;"
		 print "		    tmp.%s &= ~(1<<%d) ;" % (self.hisfield, m)
		 print "		    tmp.K &= ~(1<<%d) ;" % m
		 print "                    tmp.%s ^= ((1<<%d)|(1<<%d)) ;" % (self.myfield, f, t)
		 print "                    tmp.K ^= ((1<<%d)|(1<<%d)) ;" % (f, t) 
		 print "                    n = resolve%scaptures(&tmp, child, n, 1<<%d) ;" % (self.name, t)
		 print "                }"
	     print "                if (n == nbefore) {"
	     print "                    child[n++] = *b ;"
	     print "                }"
	     print "                return n ;"
	resolvepostamble()

print '''#include "milhouse.h"'''
c = CaptureGenerator("red", "R", "W", fwdjumps, revjumps, range(28, 32))
c.generateresolve()
c.generatecapture()
c = CaptureGenerator("white", "W", "R", revjumps, fwdjumps, range(4))
c.generateresolve()
c.generatecapture()
