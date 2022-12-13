#!/usr/bin/env python

import sys
import operator

# 
# plaid.py
#
# a code generator for a simple checkers program
# Written by Mark VandeWettering, using ideas gleaned from 
# many sources as well as early experiments with his never 
# quite working checkers player "Milhouse".

class Illegal(Exception):
    def __init__(self, msg):
	self.msg = msg 
    def __str__(self):
	return repr(msg)
	
def ntoxy(n):
    	if n < 0 or n >= 32:
	    raise Illegal("square %d is out of range" % n)
	y = n // 4 
	x = 2*(3 - n % 4) + (y % 2)
	return (x, y)

def xyton(x, y):
	if x < 0 or x > 7:
	    raise Illegal("xcoord %d is out of range" % x)
	if y < 0 or y > 7:
	    raise Illegal("ycoord %d is out of range" % y)
	if (x + y) % 2 != 0:
	    raise Illegal("coord %dx%d doesn't map to a dark square" % (x,y))
	n = y*4 + 3-(x // 2)
	return n 


def moves(n):
    l = []
    x, y = ntoxy(n)
    for dx, dy in [(-1, 1), (1, 1), (-1, -1), (1, -1)]:
	try:
	    n2 = xyton(x+dx, y+dy)
	    l.append((n, n2))
	except Illegal, msg:
	    continue
    return l 

validmoves = reduce(operator.__add__, map(lambda x : moves(x), range(32)), [])
validmoves.sort()

fwdmoves = filter(lambda x: x[1] > x[0], validmoves)
revmoves = filter(lambda x: x[0] > x[1], validmoves)

def jumps(n):
    l = []
    x, y = ntoxy(n)
    for dx, dy in [(-1, 1), (1, 1), (-1, -1), (1, -1)]:
	try:
	    n2 = xyton(x+dx, y+dy)
	    n3 = xyton(x+2*dx, y+2*dy)
	    l.append((n, n2, n3))
	except Illegal, msg:
	    continue
    return l

validjumps = reduce(operator.__add__, map(lambda x : jumps(x), range(32)), [])
validjumps.sort()

print >> sys.stderr, "%d validjumps" % len(validjumps) 

fwdjumps = filter(lambda x: x[2] > x[0], validjumps)
revjumps = filter(lambda x: x[0] > x[2], validjumps)


# for red, fwdmoves are legal man moves.
# for white, revmoves are legal man moves.
# if you have a king, then you can do either.

def genman(name, f, fwdmoves, kinging):
    print "inline CheckerBoard *\n%smanmove(int c, CheckerBoard *b, CheckerBoard *m)" % name
    print "{"
    print "    switch (c) {"
    for n in range(32):
	print "    case %d:" % n
	for n1, n2 in fwdmoves:
	    if n1 == n:
		if n2 in kinging:
		    print "\tif (UNOCC(%d)) KINGMAN(%s, %d, %d)" % (n2, f, n1, n2)
		else:
		    print "\tif (UNOCC(%d)) MOVEMAN(%s, %d, %d)" % (n2, f, n1, n2)
	print "\tbreak ;"
    print "    }"
    print "    return m ;"
    print "}"

genman("red", "R", fwdmoves, range(28, 32))
genman("white", "W", revmoves, range(0, 4))

def genking(name, f, moves):
    print "inline CheckerBoard *\n%skingmove(int c, CheckerBoard *b, CheckerBoard *m)" % name
    print "{"
    print "    switch (c) {"
    for n in range(32):
	print "    case %d:" % n
	for n1, n2 in moves:
	    if n1 == n:
		print "\tif (UNOCC(%d)) MOVEKING(%s, %d, %d)" % (n2, f, n1, n2)
	print "\tbreak ;"
    print "    }"
    print "    return m ;"
    print "}"


genking("red", "R", validmoves)
genking("white", "W", validmoves)

def genmanresolve(name, f, g, jumps, kinging):
    print "inline CheckerBoard *\n%smanresolve(int c, CheckerBoard *b, CheckerBoard *m)" % name
    print "{"
    print "    CheckerBoard tmp ;"
    print "    CheckerBoard *n = m ; /* remember old value */"
    print "    switch (c) {"
    for n in range(32):
	print "    case %d:" % n
	for n1, n2, n3 in jumps:
	    if n == n1:
	    	if n3 in kinging:
		    print "\tif (UNOCC(%d) && OCC(%s, %d)) FINISHMAN(%s, %s, %s, %d, %d, %d)" % (n3, g, n2, name, f, g, n1, n2, n3) ;
		else:
		    print "\tif (UNOCC(%d) && OCC(%s, %d)) JUMPMAN(%s, %s, %s, %d, %d, %d)" % (n3, g, n2, name, f, g, n1, n2, n3) ;
	print "\tif (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}"
	print "\tbreak ;"
    print "    }"
    print "    return m ;"
    print "}"

def genmanjump(name, f, g, jumps, kinging):
    print "inline CheckerBoard *\n%smanjump(int c, CheckerBoard *b, CheckerBoard *m)" % name
    print "{"
    print "    CheckerBoard tmp ;"
    print "    switch (c) {"
    for n in range(32):
	print "    case %d:" % n
	for n1, n2, n3 in jumps:
	    if n == n1:
	    	if n3 in kinging:
		    print "\tif (UNOCC(%d) && OCC(%s, %d)) FINISHMAN(%s, %s, %s, %d, %d, %d)" % (n3, g, n2, name, f, g, n1, n2, n3) ;
		else:
		    print "\tif (UNOCC(%d) && OCC(%s, %d)) JUMPMAN(%s, %s, %s, %d, %d, %d)" % (n3, g, n2, name, f, g, n1, n2, n3) ;
	print "\tbreak ;"
    print "    }"
    print "    return m ;"
    print "}"

def genkingresolve(name, f, g, jumps):
    print "inline CheckerBoard *\n%skingresolve(int c, CheckerBoard *b, CheckerBoard *m)" % name
    print "{"
    print "    CheckerBoard tmp ;"
    print "    CheckerBoard *n = m ; /* remember old value */"
    print "    switch (c) {"
    for n in range(32):
	print "    case %d:" % n
	for n1, n2, n3 in jumps:
	    if n == n1:
		print "\tif (UNOCC(%d) && OCC(%s, %d)) JUMPKING(%s, %s, %s, %d, %d, %d)" % (n3, g, n2, name, f, g, n1, n2, n3) ;
	print "\tif (m == n) { *m = *b ; m->hash ^= COLORSWAP; m++ ;}"
	print "\tbreak ;"
    print "    }"
    print "    return m ;"
    print "}"

def genkingjump(name, f, g, jumps):
    print "inline CheckerBoard *\n%skingjump(int c, CheckerBoard *b, CheckerBoard *m)" % name
    print "{"
    print "    CheckerBoard tmp ;"
    print "    switch (c) {"
    for n in range(32):
	print "    case %d:" % n
	for n1, n2, n3 in jumps:
	    if n == n1:
		print "\tif (UNOCC(%d) && OCC(%s, %d)) JUMPKING(%s, %s, %s, %d, %d, %d)" % (n3, g, n2, name, f, g, n1, n2, n3) ;
	print "\tbreak ;"
    print "    }"
    print "    return m ;"
    print "}"

genmanresolve("red", "R", "W", fwdjumps, range(28,32)) ;
genmanjump("red", "R", "W", fwdjumps, range(28,32)) ;
genmanresolve("white", "W", "R", revjumps, range(0,4)) ;
genmanjump("white", "W", "R", revjumps, range(0,4)) ;

genkingresolve("red", "R", "W", validjumps) ;
genkingjump("red", "R", "W", validjumps) ;
genkingresolve("white", "W", "R", validjumps) ;
genkingjump("white", "W", "R", validjumps) ;
