/* DO NOT HAND EDIT -- MACHINE GENERATED CODE WITHIN */
#include "milhouse.h"

int
generateredmoves(CheckerBoard *b, CheckerBoard child[MAXMOVES], BitBoard m)
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
	    switch (c) {
            case 0x00000001:
                if (U&(1<<4)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<0)|(1<<4) ;
                }
                if (U&(1<<5)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<0)|(1<<5) ;
                }
                break;
            case 0x00000002:
                if (U&(1<<5)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<1)|(1<<5) ;
                }
                if (U&(1<<6)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<1)|(1<<6) ;
                }
                break;
            case 0x00000004:
                if (U&(1<<6)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<2)|(1<<6) ;
                }
                if (U&(1<<7)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<2)|(1<<7) ;
                }
                break;
            case 0x00000008:
                if (U&(1<<7)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<3)|(1<<7) ;
                }
                break;
            case 0x00000010:
                if (U&(1<<8)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<4)|(1<<8) ;
                }
                break;
            case 0x00000020:
                if (U&(1<<8)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<5)|(1<<8) ;
                }
                if (U&(1<<9)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<5)|(1<<9) ;
                }
                break;
            case 0x00000040:
                if (U&(1<<9)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<6)|(1<<9) ;
                }
                if (U&(1<<10)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<6)|(1<<10) ;
                }
                break;
            case 0x00000080:
                if (U&(1<<10)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<7)|(1<<10) ;
                }
                if (U&(1<<11)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<7)|(1<<11) ;
                }
                break;
            case 0x00000100:
                if (U&(1<<12)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<8)|(1<<12) ;
                }
                if (U&(1<<13)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<8)|(1<<13) ;
                }
                break;
            case 0x00000200:
                if (U&(1<<13)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<9)|(1<<13) ;
                }
                if (U&(1<<14)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<9)|(1<<14) ;
                }
                break;
            case 0x00000400:
                if (U&(1<<14)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<10)|(1<<14) ;
                }
                if (U&(1<<15)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<10)|(1<<15) ;
                }
                break;
            case 0x00000800:
                if (U&(1<<15)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<11)|(1<<15) ;
                }
                break;
            case 0x00001000:
                if (U&(1<<16)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<12)|(1<<16) ;
                }
                break;
            case 0x00002000:
                if (U&(1<<16)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<13)|(1<<16) ;
                }
                if (U&(1<<17)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<13)|(1<<17) ;
                }
                break;
            case 0x00004000:
                if (U&(1<<17)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<14)|(1<<17) ;
                }
                if (U&(1<<18)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<14)|(1<<18) ;
                }
                break;
            case 0x00008000:
                if (U&(1<<18)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<15)|(1<<18) ;
                }
                if (U&(1<<19)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<15)|(1<<19) ;
                }
                break;
            case 0x00010000:
                if (U&(1<<20)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<16)|(1<<20) ;
                }
                if (U&(1<<21)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<16)|(1<<21) ;
                }
                break;
            case 0x00020000:
                if (U&(1<<21)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<17)|(1<<21) ;
                }
                if (U&(1<<22)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<17)|(1<<22) ;
                }
                break;
            case 0x00040000:
                if (U&(1<<22)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<18)|(1<<22) ;
                }
                if (U&(1<<23)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<18)|(1<<23) ;
                }
                break;
            case 0x00080000:
                if (U&(1<<23)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<19)|(1<<23) ;
                }
                break;
            case 0x00100000:
                if (U&(1<<24)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<20)|(1<<24) ;
                }
                break;
            case 0x00200000:
                if (U&(1<<24)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<21)|(1<<24) ;
                }
                if (U&(1<<25)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<21)|(1<<25) ;
                }
                break;
            case 0x00400000:
                if (U&(1<<25)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<22)|(1<<25) ;
                }
                if (U&(1<<26)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<22)|(1<<26) ;
                }
                break;
            case 0x00800000:
                if (U&(1<<26)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<23)|(1<<26) ;
                }
                if (U&(1<<27)) {
                    child[n] = *b ;
                    child[n++].R ^= (1<<23)|(1<<27) ;
                }
                break;
            case 0x01000000:
                if (U&(1<<28)) {
                    child[n] = *b ;
                    child[n].K |= (1<<28) ; /* KING ME */
                    child[n++].R ^= (1<<24)|(1<<28) ;
                }
                if (U&(1<<29)) {
                    child[n] = *b ;
                    child[n].K |= (1<<29) ; /* KING ME */
                    child[n++].R ^= (1<<24)|(1<<29) ;
                }
                break;
            case 0x02000000:
                if (U&(1<<29)) {
                    child[n] = *b ;
                    child[n].K |= (1<<29) ; /* KING ME */
                    child[n++].R ^= (1<<25)|(1<<29) ;
                }
                if (U&(1<<30)) {
                    child[n] = *b ;
                    child[n].K |= (1<<30) ; /* KING ME */
                    child[n++].R ^= (1<<25)|(1<<30) ;
                }
                break;
            case 0x04000000:
                if (U&(1<<30)) {
                    child[n] = *b ;
                    child[n].K |= (1<<30) ; /* KING ME */
                    child[n++].R ^= (1<<26)|(1<<30) ;
                }
                if (U&(1<<31)) {
                    child[n] = *b ;
                    child[n].K |= (1<<31) ; /* KING ME */
                    child[n++].R ^= (1<<26)|(1<<31) ;
                }
                break;
            case 0x08000000:
                if (U&(1<<31)) {
                    child[n] = *b ;
                    child[n].K |= (1<<31) ; /* KING ME */
                    child[n++].R ^= (1<<27)|(1<<31) ;
                }
                break;

	    } 
	} else {
	    /* we are a king */	
	    switch(c) {
            case 0x00000001:
                if (U&(1<<4)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<0)|(1<<4) ;
                    child[n++].K ^= (1<<0)|(1<<4) ;
                }
                if (U&(1<<5)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<0)|(1<<5) ;
                    child[n++].K ^= (1<<0)|(1<<5) ;
                }
                break;
            case 0x00000002:
                if (U&(1<<5)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<1)|(1<<5) ;
                    child[n++].K ^= (1<<1)|(1<<5) ;
                }
                if (U&(1<<6)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<1)|(1<<6) ;
                    child[n++].K ^= (1<<1)|(1<<6) ;
                }
                break;
            case 0x00000004:
                if (U&(1<<6)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<2)|(1<<6) ;
                    child[n++].K ^= (1<<2)|(1<<6) ;
                }
                if (U&(1<<7)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<2)|(1<<7) ;
                    child[n++].K ^= (1<<2)|(1<<7) ;
                }
                break;
            case 0x00000008:
                if (U&(1<<7)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<3)|(1<<7) ;
                    child[n++].K ^= (1<<3)|(1<<7) ;
                }
                break;
            case 0x00000010:
                if (U&(1<<8)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<4)|(1<<8) ;
                    child[n++].K ^= (1<<4)|(1<<8) ;
                }
                if (U&(1<<0)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<4)|(1<<0) ;
                    child[n++].K ^= (1<<4)|(1<<0) ;
                }
                break;
            case 0x00000020:
                if (U&(1<<8)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<5)|(1<<8) ;
                    child[n++].K ^= (1<<5)|(1<<8) ;
                }
                if (U&(1<<9)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<5)|(1<<9) ;
                    child[n++].K ^= (1<<5)|(1<<9) ;
                }
                if (U&(1<<0)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<5)|(1<<0) ;
                    child[n++].K ^= (1<<5)|(1<<0) ;
                }
                if (U&(1<<1)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<5)|(1<<1) ;
                    child[n++].K ^= (1<<5)|(1<<1) ;
                }
                break;
            case 0x00000040:
                if (U&(1<<9)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<6)|(1<<9) ;
                    child[n++].K ^= (1<<6)|(1<<9) ;
                }
                if (U&(1<<10)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<6)|(1<<10) ;
                    child[n++].K ^= (1<<6)|(1<<10) ;
                }
                if (U&(1<<1)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<6)|(1<<1) ;
                    child[n++].K ^= (1<<6)|(1<<1) ;
                }
                if (U&(1<<2)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<6)|(1<<2) ;
                    child[n++].K ^= (1<<6)|(1<<2) ;
                }
                break;
            case 0x00000080:
                if (U&(1<<10)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<7)|(1<<10) ;
                    child[n++].K ^= (1<<7)|(1<<10) ;
                }
                if (U&(1<<11)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<7)|(1<<11) ;
                    child[n++].K ^= (1<<7)|(1<<11) ;
                }
                if (U&(1<<2)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<7)|(1<<2) ;
                    child[n++].K ^= (1<<7)|(1<<2) ;
                }
                if (U&(1<<3)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<7)|(1<<3) ;
                    child[n++].K ^= (1<<7)|(1<<3) ;
                }
                break;
            case 0x00000100:
                if (U&(1<<12)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<8)|(1<<12) ;
                    child[n++].K ^= (1<<8)|(1<<12) ;
                }
                if (U&(1<<13)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<8)|(1<<13) ;
                    child[n++].K ^= (1<<8)|(1<<13) ;
                }
                if (U&(1<<4)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<8)|(1<<4) ;
                    child[n++].K ^= (1<<8)|(1<<4) ;
                }
                if (U&(1<<5)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<8)|(1<<5) ;
                    child[n++].K ^= (1<<8)|(1<<5) ;
                }
                break;
            case 0x00000200:
                if (U&(1<<13)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<9)|(1<<13) ;
                    child[n++].K ^= (1<<9)|(1<<13) ;
                }
                if (U&(1<<14)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<9)|(1<<14) ;
                    child[n++].K ^= (1<<9)|(1<<14) ;
                }
                if (U&(1<<5)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<9)|(1<<5) ;
                    child[n++].K ^= (1<<9)|(1<<5) ;
                }
                if (U&(1<<6)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<9)|(1<<6) ;
                    child[n++].K ^= (1<<9)|(1<<6) ;
                }
                break;
            case 0x00000400:
                if (U&(1<<14)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<10)|(1<<14) ;
                    child[n++].K ^= (1<<10)|(1<<14) ;
                }
                if (U&(1<<15)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<10)|(1<<15) ;
                    child[n++].K ^= (1<<10)|(1<<15) ;
                }
                if (U&(1<<6)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<10)|(1<<6) ;
                    child[n++].K ^= (1<<10)|(1<<6) ;
                }
                if (U&(1<<7)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<10)|(1<<7) ;
                    child[n++].K ^= (1<<10)|(1<<7) ;
                }
                break;
            case 0x00000800:
                if (U&(1<<15)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<11)|(1<<15) ;
                    child[n++].K ^= (1<<11)|(1<<15) ;
                }
                if (U&(1<<7)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<11)|(1<<7) ;
                    child[n++].K ^= (1<<11)|(1<<7) ;
                }
                break;
            case 0x00001000:
                if (U&(1<<16)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<12)|(1<<16) ;
                    child[n++].K ^= (1<<12)|(1<<16) ;
                }
                if (U&(1<<8)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<12)|(1<<8) ;
                    child[n++].K ^= (1<<12)|(1<<8) ;
                }
                break;
            case 0x00002000:
                if (U&(1<<16)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<13)|(1<<16) ;
                    child[n++].K ^= (1<<13)|(1<<16) ;
                }
                if (U&(1<<17)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<13)|(1<<17) ;
                    child[n++].K ^= (1<<13)|(1<<17) ;
                }
                if (U&(1<<8)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<13)|(1<<8) ;
                    child[n++].K ^= (1<<13)|(1<<8) ;
                }
                if (U&(1<<9)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<13)|(1<<9) ;
                    child[n++].K ^= (1<<13)|(1<<9) ;
                }
                break;
            case 0x00004000:
                if (U&(1<<17)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<14)|(1<<17) ;
                    child[n++].K ^= (1<<14)|(1<<17) ;
                }
                if (U&(1<<18)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<14)|(1<<18) ;
                    child[n++].K ^= (1<<14)|(1<<18) ;
                }
                if (U&(1<<9)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<14)|(1<<9) ;
                    child[n++].K ^= (1<<14)|(1<<9) ;
                }
                if (U&(1<<10)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<14)|(1<<10) ;
                    child[n++].K ^= (1<<14)|(1<<10) ;
                }
                break;
            case 0x00008000:
                if (U&(1<<18)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<15)|(1<<18) ;
                    child[n++].K ^= (1<<15)|(1<<18) ;
                }
                if (U&(1<<19)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<15)|(1<<19) ;
                    child[n++].K ^= (1<<15)|(1<<19) ;
                }
                if (U&(1<<10)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<15)|(1<<10) ;
                    child[n++].K ^= (1<<15)|(1<<10) ;
                }
                if (U&(1<<11)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<15)|(1<<11) ;
                    child[n++].K ^= (1<<15)|(1<<11) ;
                }
                break;
            case 0x00010000:
                if (U&(1<<20)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<16)|(1<<20) ;
                    child[n++].K ^= (1<<16)|(1<<20) ;
                }
                if (U&(1<<21)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<16)|(1<<21) ;
                    child[n++].K ^= (1<<16)|(1<<21) ;
                }
                if (U&(1<<12)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<16)|(1<<12) ;
                    child[n++].K ^= (1<<16)|(1<<12) ;
                }
                if (U&(1<<13)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<16)|(1<<13) ;
                    child[n++].K ^= (1<<16)|(1<<13) ;
                }
                break;
            case 0x00020000:
                if (U&(1<<21)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<17)|(1<<21) ;
                    child[n++].K ^= (1<<17)|(1<<21) ;
                }
                if (U&(1<<22)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<17)|(1<<22) ;
                    child[n++].K ^= (1<<17)|(1<<22) ;
                }
                if (U&(1<<13)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<17)|(1<<13) ;
                    child[n++].K ^= (1<<17)|(1<<13) ;
                }
                if (U&(1<<14)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<17)|(1<<14) ;
                    child[n++].K ^= (1<<17)|(1<<14) ;
                }
                break;
            case 0x00040000:
                if (U&(1<<22)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<18)|(1<<22) ;
                    child[n++].K ^= (1<<18)|(1<<22) ;
                }
                if (U&(1<<23)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<18)|(1<<23) ;
                    child[n++].K ^= (1<<18)|(1<<23) ;
                }
                if (U&(1<<14)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<18)|(1<<14) ;
                    child[n++].K ^= (1<<18)|(1<<14) ;
                }
                if (U&(1<<15)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<18)|(1<<15) ;
                    child[n++].K ^= (1<<18)|(1<<15) ;
                }
                break;
            case 0x00080000:
                if (U&(1<<23)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<19)|(1<<23) ;
                    child[n++].K ^= (1<<19)|(1<<23) ;
                }
                if (U&(1<<15)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<19)|(1<<15) ;
                    child[n++].K ^= (1<<19)|(1<<15) ;
                }
                break;
            case 0x00100000:
                if (U&(1<<24)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<20)|(1<<24) ;
                    child[n++].K ^= (1<<20)|(1<<24) ;
                }
                if (U&(1<<16)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<20)|(1<<16) ;
                    child[n++].K ^= (1<<20)|(1<<16) ;
                }
                break;
            case 0x00200000:
                if (U&(1<<24)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<21)|(1<<24) ;
                    child[n++].K ^= (1<<21)|(1<<24) ;
                }
                if (U&(1<<25)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<21)|(1<<25) ;
                    child[n++].K ^= (1<<21)|(1<<25) ;
                }
                if (U&(1<<16)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<21)|(1<<16) ;
                    child[n++].K ^= (1<<21)|(1<<16) ;
                }
                if (U&(1<<17)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<21)|(1<<17) ;
                    child[n++].K ^= (1<<21)|(1<<17) ;
                }
                break;
            case 0x00400000:
                if (U&(1<<25)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<22)|(1<<25) ;
                    child[n++].K ^= (1<<22)|(1<<25) ;
                }
                if (U&(1<<26)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<22)|(1<<26) ;
                    child[n++].K ^= (1<<22)|(1<<26) ;
                }
                if (U&(1<<17)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<22)|(1<<17) ;
                    child[n++].K ^= (1<<22)|(1<<17) ;
                }
                if (U&(1<<18)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<22)|(1<<18) ;
                    child[n++].K ^= (1<<22)|(1<<18) ;
                }
                break;
            case 0x00800000:
                if (U&(1<<26)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<23)|(1<<26) ;
                    child[n++].K ^= (1<<23)|(1<<26) ;
                }
                if (U&(1<<27)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<23)|(1<<27) ;
                    child[n++].K ^= (1<<23)|(1<<27) ;
                }
                if (U&(1<<18)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<23)|(1<<18) ;
                    child[n++].K ^= (1<<23)|(1<<18) ;
                }
                if (U&(1<<19)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<23)|(1<<19) ;
                    child[n++].K ^= (1<<23)|(1<<19) ;
                }
                break;
            case 0x01000000:
                if (U&(1<<28)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<24)|(1<<28) ;
                    child[n++].K ^= (1<<24)|(1<<28) ;
                }
                if (U&(1<<29)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<24)|(1<<29) ;
                    child[n++].K ^= (1<<24)|(1<<29) ;
                }
                if (U&(1<<20)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<24)|(1<<20) ;
                    child[n++].K ^= (1<<24)|(1<<20) ;
                }
                if (U&(1<<21)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<24)|(1<<21) ;
                    child[n++].K ^= (1<<24)|(1<<21) ;
                }
                break;
            case 0x02000000:
                if (U&(1<<29)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<25)|(1<<29) ;
                    child[n++].K ^= (1<<25)|(1<<29) ;
                }
                if (U&(1<<30)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<25)|(1<<30) ;
                    child[n++].K ^= (1<<25)|(1<<30) ;
                }
                if (U&(1<<21)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<25)|(1<<21) ;
                    child[n++].K ^= (1<<25)|(1<<21) ;
                }
                if (U&(1<<22)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<25)|(1<<22) ;
                    child[n++].K ^= (1<<25)|(1<<22) ;
                }
                break;
            case 0x04000000:
                if (U&(1<<30)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<26)|(1<<30) ;
                    child[n++].K ^= (1<<26)|(1<<30) ;
                }
                if (U&(1<<31)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<26)|(1<<31) ;
                    child[n++].K ^= (1<<26)|(1<<31) ;
                }
                if (U&(1<<22)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<26)|(1<<22) ;
                    child[n++].K ^= (1<<26)|(1<<22) ;
                }
                if (U&(1<<23)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<26)|(1<<23) ;
                    child[n++].K ^= (1<<26)|(1<<23) ;
                }
                break;
            case 0x08000000:
                if (U&(1<<31)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<27)|(1<<31) ;
                    child[n++].K ^= (1<<27)|(1<<31) ;
                }
                if (U&(1<<23)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<27)|(1<<23) ;
                    child[n++].K ^= (1<<27)|(1<<23) ;
                }
                break;
            case 0x10000000:
                if (U&(1<<24)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<28)|(1<<24) ;
                    child[n++].K ^= (1<<28)|(1<<24) ;
                }
                break;
            case 0x20000000:
                if (U&(1<<24)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<29)|(1<<24) ;
                    child[n++].K ^= (1<<29)|(1<<24) ;
                }
                if (U&(1<<25)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<29)|(1<<25) ;
                    child[n++].K ^= (1<<29)|(1<<25) ;
                }
                break;
            case 0x40000000:
                if (U&(1<<25)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<30)|(1<<25) ;
                    child[n++].K ^= (1<<30)|(1<<25) ;
                }
                if (U&(1<<26)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<30)|(1<<26) ;
                    child[n++].K ^= (1<<30)|(1<<26) ;
                }
                break;
            case 0x80000000:
                if (U&(1<<26)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<31)|(1<<26) ;
                    child[n++].K ^= (1<<31)|(1<<26) ;
                }
                if (U&(1<<27)) {
                    child[n] = *b ;
                    child[n].R ^= (1<<31)|(1<<27) ;
                    child[n++].K ^= (1<<31)|(1<<27) ;
                }
                break;

	    }
	}
    }
    return n ;
} 

int
generatewhitemoves(CheckerBoard *b, CheckerBoard child[MAXMOVES], BitBoard m)
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
	    switch (c) {
            case 0x00000010:
                if (U&(1<<0)) {
                    child[n] = *b ;
                    child[n].K |= (1<<0) ; /* KING ME */
                    child[n++].W ^= (1<<4)|(1<<0) ;
                }
                break;
            case 0x00000020:
                if (U&(1<<0)) {
                    child[n] = *b ;
                    child[n].K |= (1<<0) ; /* KING ME */
                    child[n++].W ^= (1<<5)|(1<<0) ;
                }
                if (U&(1<<1)) {
                    child[n] = *b ;
                    child[n].K |= (1<<1) ; /* KING ME */
                    child[n++].W ^= (1<<5)|(1<<1) ;
                }
                break;
            case 0x00000040:
                if (U&(1<<1)) {
                    child[n] = *b ;
                    child[n].K |= (1<<1) ; /* KING ME */
                    child[n++].W ^= (1<<6)|(1<<1) ;
                }
                if (U&(1<<2)) {
                    child[n] = *b ;
                    child[n].K |= (1<<2) ; /* KING ME */
                    child[n++].W ^= (1<<6)|(1<<2) ;
                }
                break;
            case 0x00000080:
                if (U&(1<<2)) {
                    child[n] = *b ;
                    child[n].K |= (1<<2) ; /* KING ME */
                    child[n++].W ^= (1<<7)|(1<<2) ;
                }
                if (U&(1<<3)) {
                    child[n] = *b ;
                    child[n].K |= (1<<3) ; /* KING ME */
                    child[n++].W ^= (1<<7)|(1<<3) ;
                }
                break;
            case 0x00000100:
                if (U&(1<<4)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<8)|(1<<4) ;
                }
                if (U&(1<<5)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<8)|(1<<5) ;
                }
                break;
            case 0x00000200:
                if (U&(1<<5)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<9)|(1<<5) ;
                }
                if (U&(1<<6)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<9)|(1<<6) ;
                }
                break;
            case 0x00000400:
                if (U&(1<<6)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<10)|(1<<6) ;
                }
                if (U&(1<<7)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<10)|(1<<7) ;
                }
                break;
            case 0x00000800:
                if (U&(1<<7)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<11)|(1<<7) ;
                }
                break;
            case 0x00001000:
                if (U&(1<<8)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<12)|(1<<8) ;
                }
                break;
            case 0x00002000:
                if (U&(1<<8)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<13)|(1<<8) ;
                }
                if (U&(1<<9)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<13)|(1<<9) ;
                }
                break;
            case 0x00004000:
                if (U&(1<<9)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<14)|(1<<9) ;
                }
                if (U&(1<<10)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<14)|(1<<10) ;
                }
                break;
            case 0x00008000:
                if (U&(1<<10)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<15)|(1<<10) ;
                }
                if (U&(1<<11)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<15)|(1<<11) ;
                }
                break;
            case 0x00010000:
                if (U&(1<<12)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<16)|(1<<12) ;
                }
                if (U&(1<<13)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<16)|(1<<13) ;
                }
                break;
            case 0x00020000:
                if (U&(1<<13)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<17)|(1<<13) ;
                }
                if (U&(1<<14)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<17)|(1<<14) ;
                }
                break;
            case 0x00040000:
                if (U&(1<<14)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<18)|(1<<14) ;
                }
                if (U&(1<<15)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<18)|(1<<15) ;
                }
                break;
            case 0x00080000:
                if (U&(1<<15)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<19)|(1<<15) ;
                }
                break;
            case 0x00100000:
                if (U&(1<<16)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<20)|(1<<16) ;
                }
                break;
            case 0x00200000:
                if (U&(1<<16)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<21)|(1<<16) ;
                }
                if (U&(1<<17)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<21)|(1<<17) ;
                }
                break;
            case 0x00400000:
                if (U&(1<<17)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<22)|(1<<17) ;
                }
                if (U&(1<<18)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<22)|(1<<18) ;
                }
                break;
            case 0x00800000:
                if (U&(1<<18)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<23)|(1<<18) ;
                }
                if (U&(1<<19)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<23)|(1<<19) ;
                }
                break;
            case 0x01000000:
                if (U&(1<<20)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<24)|(1<<20) ;
                }
                if (U&(1<<21)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<24)|(1<<21) ;
                }
                break;
            case 0x02000000:
                if (U&(1<<21)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<25)|(1<<21) ;
                }
                if (U&(1<<22)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<25)|(1<<22) ;
                }
                break;
            case 0x04000000:
                if (U&(1<<22)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<26)|(1<<22) ;
                }
                if (U&(1<<23)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<26)|(1<<23) ;
                }
                break;
            case 0x08000000:
                if (U&(1<<23)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<27)|(1<<23) ;
                }
                break;
            case 0x10000000:
                if (U&(1<<24)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<28)|(1<<24) ;
                }
                break;
            case 0x20000000:
                if (U&(1<<24)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<29)|(1<<24) ;
                }
                if (U&(1<<25)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<29)|(1<<25) ;
                }
                break;
            case 0x40000000:
                if (U&(1<<25)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<30)|(1<<25) ;
                }
                if (U&(1<<26)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<30)|(1<<26) ;
                }
                break;
            case 0x80000000:
                if (U&(1<<26)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<31)|(1<<26) ;
                }
                if (U&(1<<27)) {
                    child[n] = *b ;
                    child[n++].W ^= (1<<31)|(1<<27) ;
                }
                break;

	    } 
	} else {
	    /* we are a king */	
	    switch(c) {
            case 0x00000001:
                if (U&(1<<4)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<0)|(1<<4) ;
                    child[n++].K ^= (1<<0)|(1<<4) ;
                }
                if (U&(1<<5)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<0)|(1<<5) ;
                    child[n++].K ^= (1<<0)|(1<<5) ;
                }
                break;
            case 0x00000002:
                if (U&(1<<5)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<1)|(1<<5) ;
                    child[n++].K ^= (1<<1)|(1<<5) ;
                }
                if (U&(1<<6)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<1)|(1<<6) ;
                    child[n++].K ^= (1<<1)|(1<<6) ;
                }
                break;
            case 0x00000004:
                if (U&(1<<6)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<2)|(1<<6) ;
                    child[n++].K ^= (1<<2)|(1<<6) ;
                }
                if (U&(1<<7)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<2)|(1<<7) ;
                    child[n++].K ^= (1<<2)|(1<<7) ;
                }
                break;
            case 0x00000008:
                if (U&(1<<7)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<3)|(1<<7) ;
                    child[n++].K ^= (1<<3)|(1<<7) ;
                }
                break;
            case 0x00000010:
                if (U&(1<<0)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<4)|(1<<0) ;
                    child[n++].K ^= (1<<4)|(1<<0) ;
                }
                if (U&(1<<8)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<4)|(1<<8) ;
                    child[n++].K ^= (1<<4)|(1<<8) ;
                }
                break;
            case 0x00000020:
                if (U&(1<<0)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<5)|(1<<0) ;
                    child[n++].K ^= (1<<5)|(1<<0) ;
                }
                if (U&(1<<1)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<5)|(1<<1) ;
                    child[n++].K ^= (1<<5)|(1<<1) ;
                }
                if (U&(1<<8)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<5)|(1<<8) ;
                    child[n++].K ^= (1<<5)|(1<<8) ;
                }
                if (U&(1<<9)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<5)|(1<<9) ;
                    child[n++].K ^= (1<<5)|(1<<9) ;
                }
                break;
            case 0x00000040:
                if (U&(1<<1)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<6)|(1<<1) ;
                    child[n++].K ^= (1<<6)|(1<<1) ;
                }
                if (U&(1<<2)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<6)|(1<<2) ;
                    child[n++].K ^= (1<<6)|(1<<2) ;
                }
                if (U&(1<<9)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<6)|(1<<9) ;
                    child[n++].K ^= (1<<6)|(1<<9) ;
                }
                if (U&(1<<10)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<6)|(1<<10) ;
                    child[n++].K ^= (1<<6)|(1<<10) ;
                }
                break;
            case 0x00000080:
                if (U&(1<<2)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<7)|(1<<2) ;
                    child[n++].K ^= (1<<7)|(1<<2) ;
                }
                if (U&(1<<3)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<7)|(1<<3) ;
                    child[n++].K ^= (1<<7)|(1<<3) ;
                }
                if (U&(1<<10)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<7)|(1<<10) ;
                    child[n++].K ^= (1<<7)|(1<<10) ;
                }
                if (U&(1<<11)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<7)|(1<<11) ;
                    child[n++].K ^= (1<<7)|(1<<11) ;
                }
                break;
            case 0x00000100:
                if (U&(1<<4)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<8)|(1<<4) ;
                    child[n++].K ^= (1<<8)|(1<<4) ;
                }
                if (U&(1<<5)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<8)|(1<<5) ;
                    child[n++].K ^= (1<<8)|(1<<5) ;
                }
                if (U&(1<<12)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<8)|(1<<12) ;
                    child[n++].K ^= (1<<8)|(1<<12) ;
                }
                if (U&(1<<13)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<8)|(1<<13) ;
                    child[n++].K ^= (1<<8)|(1<<13) ;
                }
                break;
            case 0x00000200:
                if (U&(1<<5)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<9)|(1<<5) ;
                    child[n++].K ^= (1<<9)|(1<<5) ;
                }
                if (U&(1<<6)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<9)|(1<<6) ;
                    child[n++].K ^= (1<<9)|(1<<6) ;
                }
                if (U&(1<<13)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<9)|(1<<13) ;
                    child[n++].K ^= (1<<9)|(1<<13) ;
                }
                if (U&(1<<14)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<9)|(1<<14) ;
                    child[n++].K ^= (1<<9)|(1<<14) ;
                }
                break;
            case 0x00000400:
                if (U&(1<<6)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<10)|(1<<6) ;
                    child[n++].K ^= (1<<10)|(1<<6) ;
                }
                if (U&(1<<7)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<10)|(1<<7) ;
                    child[n++].K ^= (1<<10)|(1<<7) ;
                }
                if (U&(1<<14)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<10)|(1<<14) ;
                    child[n++].K ^= (1<<10)|(1<<14) ;
                }
                if (U&(1<<15)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<10)|(1<<15) ;
                    child[n++].K ^= (1<<10)|(1<<15) ;
                }
                break;
            case 0x00000800:
                if (U&(1<<7)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<11)|(1<<7) ;
                    child[n++].K ^= (1<<11)|(1<<7) ;
                }
                if (U&(1<<15)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<11)|(1<<15) ;
                    child[n++].K ^= (1<<11)|(1<<15) ;
                }
                break;
            case 0x00001000:
                if (U&(1<<8)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<12)|(1<<8) ;
                    child[n++].K ^= (1<<12)|(1<<8) ;
                }
                if (U&(1<<16)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<12)|(1<<16) ;
                    child[n++].K ^= (1<<12)|(1<<16) ;
                }
                break;
            case 0x00002000:
                if (U&(1<<8)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<13)|(1<<8) ;
                    child[n++].K ^= (1<<13)|(1<<8) ;
                }
                if (U&(1<<9)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<13)|(1<<9) ;
                    child[n++].K ^= (1<<13)|(1<<9) ;
                }
                if (U&(1<<16)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<13)|(1<<16) ;
                    child[n++].K ^= (1<<13)|(1<<16) ;
                }
                if (U&(1<<17)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<13)|(1<<17) ;
                    child[n++].K ^= (1<<13)|(1<<17) ;
                }
                break;
            case 0x00004000:
                if (U&(1<<9)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<14)|(1<<9) ;
                    child[n++].K ^= (1<<14)|(1<<9) ;
                }
                if (U&(1<<10)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<14)|(1<<10) ;
                    child[n++].K ^= (1<<14)|(1<<10) ;
                }
                if (U&(1<<17)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<14)|(1<<17) ;
                    child[n++].K ^= (1<<14)|(1<<17) ;
                }
                if (U&(1<<18)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<14)|(1<<18) ;
                    child[n++].K ^= (1<<14)|(1<<18) ;
                }
                break;
            case 0x00008000:
                if (U&(1<<10)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<15)|(1<<10) ;
                    child[n++].K ^= (1<<15)|(1<<10) ;
                }
                if (U&(1<<11)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<15)|(1<<11) ;
                    child[n++].K ^= (1<<15)|(1<<11) ;
                }
                if (U&(1<<18)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<15)|(1<<18) ;
                    child[n++].K ^= (1<<15)|(1<<18) ;
                }
                if (U&(1<<19)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<15)|(1<<19) ;
                    child[n++].K ^= (1<<15)|(1<<19) ;
                }
                break;
            case 0x00010000:
                if (U&(1<<12)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<16)|(1<<12) ;
                    child[n++].K ^= (1<<16)|(1<<12) ;
                }
                if (U&(1<<13)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<16)|(1<<13) ;
                    child[n++].K ^= (1<<16)|(1<<13) ;
                }
                if (U&(1<<20)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<16)|(1<<20) ;
                    child[n++].K ^= (1<<16)|(1<<20) ;
                }
                if (U&(1<<21)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<16)|(1<<21) ;
                    child[n++].K ^= (1<<16)|(1<<21) ;
                }
                break;
            case 0x00020000:
                if (U&(1<<13)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<17)|(1<<13) ;
                    child[n++].K ^= (1<<17)|(1<<13) ;
                }
                if (U&(1<<14)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<17)|(1<<14) ;
                    child[n++].K ^= (1<<17)|(1<<14) ;
                }
                if (U&(1<<21)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<17)|(1<<21) ;
                    child[n++].K ^= (1<<17)|(1<<21) ;
                }
                if (U&(1<<22)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<17)|(1<<22) ;
                    child[n++].K ^= (1<<17)|(1<<22) ;
                }
                break;
            case 0x00040000:
                if (U&(1<<14)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<18)|(1<<14) ;
                    child[n++].K ^= (1<<18)|(1<<14) ;
                }
                if (U&(1<<15)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<18)|(1<<15) ;
                    child[n++].K ^= (1<<18)|(1<<15) ;
                }
                if (U&(1<<22)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<18)|(1<<22) ;
                    child[n++].K ^= (1<<18)|(1<<22) ;
                }
                if (U&(1<<23)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<18)|(1<<23) ;
                    child[n++].K ^= (1<<18)|(1<<23) ;
                }
                break;
            case 0x00080000:
                if (U&(1<<15)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<19)|(1<<15) ;
                    child[n++].K ^= (1<<19)|(1<<15) ;
                }
                if (U&(1<<23)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<19)|(1<<23) ;
                    child[n++].K ^= (1<<19)|(1<<23) ;
                }
                break;
            case 0x00100000:
                if (U&(1<<16)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<20)|(1<<16) ;
                    child[n++].K ^= (1<<20)|(1<<16) ;
                }
                if (U&(1<<24)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<20)|(1<<24) ;
                    child[n++].K ^= (1<<20)|(1<<24) ;
                }
                break;
            case 0x00200000:
                if (U&(1<<16)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<21)|(1<<16) ;
                    child[n++].K ^= (1<<21)|(1<<16) ;
                }
                if (U&(1<<17)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<21)|(1<<17) ;
                    child[n++].K ^= (1<<21)|(1<<17) ;
                }
                if (U&(1<<24)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<21)|(1<<24) ;
                    child[n++].K ^= (1<<21)|(1<<24) ;
                }
                if (U&(1<<25)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<21)|(1<<25) ;
                    child[n++].K ^= (1<<21)|(1<<25) ;
                }
                break;
            case 0x00400000:
                if (U&(1<<17)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<22)|(1<<17) ;
                    child[n++].K ^= (1<<22)|(1<<17) ;
                }
                if (U&(1<<18)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<22)|(1<<18) ;
                    child[n++].K ^= (1<<22)|(1<<18) ;
                }
                if (U&(1<<25)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<22)|(1<<25) ;
                    child[n++].K ^= (1<<22)|(1<<25) ;
                }
                if (U&(1<<26)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<22)|(1<<26) ;
                    child[n++].K ^= (1<<22)|(1<<26) ;
                }
                break;
            case 0x00800000:
                if (U&(1<<18)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<23)|(1<<18) ;
                    child[n++].K ^= (1<<23)|(1<<18) ;
                }
                if (U&(1<<19)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<23)|(1<<19) ;
                    child[n++].K ^= (1<<23)|(1<<19) ;
                }
                if (U&(1<<26)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<23)|(1<<26) ;
                    child[n++].K ^= (1<<23)|(1<<26) ;
                }
                if (U&(1<<27)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<23)|(1<<27) ;
                    child[n++].K ^= (1<<23)|(1<<27) ;
                }
                break;
            case 0x01000000:
                if (U&(1<<20)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<24)|(1<<20) ;
                    child[n++].K ^= (1<<24)|(1<<20) ;
                }
                if (U&(1<<21)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<24)|(1<<21) ;
                    child[n++].K ^= (1<<24)|(1<<21) ;
                }
                if (U&(1<<28)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<24)|(1<<28) ;
                    child[n++].K ^= (1<<24)|(1<<28) ;
                }
                if (U&(1<<29)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<24)|(1<<29) ;
                    child[n++].K ^= (1<<24)|(1<<29) ;
                }
                break;
            case 0x02000000:
                if (U&(1<<21)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<25)|(1<<21) ;
                    child[n++].K ^= (1<<25)|(1<<21) ;
                }
                if (U&(1<<22)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<25)|(1<<22) ;
                    child[n++].K ^= (1<<25)|(1<<22) ;
                }
                if (U&(1<<29)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<25)|(1<<29) ;
                    child[n++].K ^= (1<<25)|(1<<29) ;
                }
                if (U&(1<<30)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<25)|(1<<30) ;
                    child[n++].K ^= (1<<25)|(1<<30) ;
                }
                break;
            case 0x04000000:
                if (U&(1<<22)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<26)|(1<<22) ;
                    child[n++].K ^= (1<<26)|(1<<22) ;
                }
                if (U&(1<<23)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<26)|(1<<23) ;
                    child[n++].K ^= (1<<26)|(1<<23) ;
                }
                if (U&(1<<30)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<26)|(1<<30) ;
                    child[n++].K ^= (1<<26)|(1<<30) ;
                }
                if (U&(1<<31)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<26)|(1<<31) ;
                    child[n++].K ^= (1<<26)|(1<<31) ;
                }
                break;
            case 0x08000000:
                if (U&(1<<23)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<27)|(1<<23) ;
                    child[n++].K ^= (1<<27)|(1<<23) ;
                }
                if (U&(1<<31)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<27)|(1<<31) ;
                    child[n++].K ^= (1<<27)|(1<<31) ;
                }
                break;
            case 0x10000000:
                if (U&(1<<24)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<28)|(1<<24) ;
                    child[n++].K ^= (1<<28)|(1<<24) ;
                }
                break;
            case 0x20000000:
                if (U&(1<<24)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<29)|(1<<24) ;
                    child[n++].K ^= (1<<29)|(1<<24) ;
                }
                if (U&(1<<25)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<29)|(1<<25) ;
                    child[n++].K ^= (1<<29)|(1<<25) ;
                }
                break;
            case 0x40000000:
                if (U&(1<<25)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<30)|(1<<25) ;
                    child[n++].K ^= (1<<30)|(1<<25) ;
                }
                if (U&(1<<26)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<30)|(1<<26) ;
                    child[n++].K ^= (1<<30)|(1<<26) ;
                }
                break;
            case 0x80000000:
                if (U&(1<<26)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<31)|(1<<26) ;
                    child[n++].K ^= (1<<31)|(1<<26) ;
                }
                if (U&(1<<27)) {
                    child[n] = *b ;
                    child[n].W ^= (1<<31)|(1<<27) ;
                    child[n++].K ^= (1<<31)|(1<<27) ;
                }
                break;

	    }
	}
    }
    return n ;
} 
