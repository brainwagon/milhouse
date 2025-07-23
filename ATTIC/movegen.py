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

########################################################################

class MoveGenerator:
    def __init__(self, name, field, fwd, rev, kinging):
        self.name = name
        self.field = field
        self.fwd = fwd
        self.rev = rev 
        self.kinging = kinging
    def generate(self):
        fmoves = {}
        for f, t in self.fwd:
                fmoves[f] = fmoves.get(f, []) + [t]

        kmoves = {}

        for f, t in self.fwd:
                kmoves[f] = kmoves.get(f, []) + [t]
        for f, t in self.rev:
                kmoves[f] = kmoves.get(f, []) + [t]

########################################################################


        print("""
int
generate%smoves(CheckerBoard *b, CheckerBoard child[MAXMOVES], BitBoard m)
{
    BitBoard next, c ;
    BitBoard U = ~ (b->R|b->W) ;
    int n = 0 ;

    while (m) {
        next = m & (m - 1) ;
        c = m ^ next ;
        m = next ;
        
        if ((b->K & c) == 0) {
            /* we are just a normal man */
            switch (c) {""" % self.name)

        fkeys = list(fmoves.keys())
        fkeys.sort()

        for k in fkeys:
            print("            case 0x%08x:" % (1<<k))
            for t in fmoves[k]:
                print("                if (U&(1<<%d)) {" % t)
                print("                    child[n] = *b ;")
                if (t in self.kinging):
                        print("                    child[n].K |= (1<<%d) ; /* KING ME */" % t)
                print("                    child[n++].%s ^= (1<<%d)|(1<<%d) ;" % (self.field, k, t))
                print("                }")
            print("                break;")
                

        ########################################################################

        print("""
            } 
        } else {
            /* we are a king */ 
            switch(c) {""")
        ########################################################################

        kkeys = list(kmoves.keys()) 
        kkeys.sort()

        for k in kkeys:
            print("            case 0x%08x:" % (1<<k))
            for t in kmoves[k]:
                print("                if (U&(1<<%d)) {" % t)
                print("                    child[n] = *b ;")
                print("                    child[n].%s ^= (1<<%d)|(1<<%d) ;" % (self.field, k, t))
                print("                    child[n++].K ^= (1<<%d)|(1<<%d) ;" % (k, t))
                print("                }")
            print("                break;")
                
        print("""
            }
        }
    }
    return n ;
} """)

print("""/* DO NOT HAND EDIT -- MACHINE GENERATED CODE WITHIN */""")
print('''#include "milhouse.h"''')

m = MoveGenerator("red", "R", fwdmoves, revmoves, list(range(28,32)))
m.generate()
m = MoveGenerator("white", "W", revmoves, fwdmoves, list(range(4)))
m.generate()
