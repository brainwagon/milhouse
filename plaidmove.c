#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

#include "milhouse.h"

#define UNOCC(n)	(~(b->W|b->R)&(1<<n))
#define OCC(f,n)	((b->f)&(1<<n))
#define	COLORSWAP	0x20c879f2166e9ea4LL


#define MOVEMAN(f, n1, n2) \
	{\
		*m = *b ;\
		m->hash ^= COLORSWAP ;\
		m->f ^= ((1<<n1)|(1<<n2)) ;\
		m->hash ^= (Hash[n1].f^Hash[n2].f) ;\
		m++ ;\
	}

#define KINGMAN(f, n1, n2) \
	{\
		*m = *b ;\
		m->hash ^= COLORSWAP ;\
		m->f ^= ((1<<n1)|(1<<n2)) ;\
		m->hash ^= (Hash[n1].f^Hash[n2].f) ;\
		m->K ^= (1<<n2) ;\
		m->hash ^= Hash[n2].K ;\
		m++ ;\
	}

#define MOVEKING(f, n1, n2) \
	{\
		*m = *b ;\
		m->hash ^= COLORSWAP ;\
		m->f ^= ((1<<n1)|(1<<n2)) ;\
		m->hash ^= (Hash[n1].f^Hash[n2].f) ;\
		m->K ^= ((1<<n1)|(1<<n2)) ;\
		m->hash ^= (Hash[n1].K^Hash[n2].K) ;\
		m++ ;\
	}

#define JUMPKING(name, f, g, n1, n2, n3) \
	{\
		tmp = *b ;\
		tmp.f ^= ((1<<n1)|(1<<n3)) ;\
		tmp.K ^= ((1<<n1)|(1<<n3)) ;\
		tmp.hash ^= (Hash[n1].f^Hash[n3].f) ;\
		tmp.hash ^= (Hash[n1].K^Hash[n3].K) ;\
		tmp.g &= ~(1<<n2) ;\
		tmp.hash ^= Hash[n2].g ;\
		if (tmp.K & (1<<n2)) {\
		    tmp.K &= ~(1<<n2) ;\
		    tmp.hash ^= Hash[n2].K ;\
		}\
		m = name##kingresolve(n3, &tmp, m) ;\
	}

#define JUMPMAN(name, f, g, n1, n2, n3) \
	{\
		tmp = *b ;\
		tmp.f ^= ((1<<n1)|(1<<n3)) ;\
		tmp.hash ^= (Hash[n1].f^Hash[n3].f) ;\
		tmp.g &= ~(1<<n2) ;\
		tmp.hash ^= Hash[n2].g ;\
		if (tmp.K & (1<<n2)) {\
		    tmp.K &= ~(1<<n2) ;\
		    tmp.hash ^= Hash[n2].K ;\
		}\
		m = name##manresolve(n3, &tmp, m) ;\
	}

#define FINISHMAN(name, f, g, n1, n2, n3) \
	{\
		*m = *b ; /* n3 is a kinging square */\
		m->f ^= ((1<<n1)|(1<<n3)) ;\
		m->hash ^= COLORSWAP ;\
		m->hash ^= (Hash[n1].f^Hash[n3].f) ;\
		m->K ^= (1<<n3) ;\
		m->hash ^= Hash[n3].K ;\
		m->g &= ~(1<<n2) ;\
		m->hash ^= Hash[n2].g ;\
		if (m->K & (1<<n2)) {\
		    m->K &= ~(1<<n2) ;\
		    m->hash ^= Hash[n2].K ;\
		}\
		m++;\
	}

static int
LOG2(BitBoard b)
{
    int r = 0 ;

    r |= ((b & 0xFFFF0000) != 0) << 4 ;
    r |= ((b & 0xFF00FF00) != 0) << 3 ;
    r |= ((b & 0xF0F0F0F0) != 0) << 2 ;
    r |= ((b & 0xCCCCCCCC) != 0) << 1 ;
    r |= ((b & 0xAAAAAAAA) != 0) << 0 ;
    return r ;
}

/* long long?  That's not good... */

typedef struct t_hashtab {
    uint64_t R, W, K ;
} HashEntry ; 

HashEntry Hash[32] = {
    {0x7c3236feeddaee28LL,  0xceed6badd3fc2336LL,  0x4d2ab9895f392da6LL}, 
    {0x81e9f03c12615e01LL,  0x0d3f3f50a73399b6LL,  0x99d5a29582d21fdfLL}, 
    {0xbd1dd6210a702836LL,  0x5921fda57203e332LL,  0x7076ce40bd2e8ac4LL}, 
    {0x5f30e991e3c483fbLL,  0x2bf39dd78f40847fLL,  0xbd90aa2b5be5d8e1LL}, 
    {0xf3f25ab6a1500d9aLL,  0x1e6dcf5c6d1ad5b9LL,  0xa34aac3f167233d3LL}, 
    {0x686ad0f3b25a1893LL,  0x5a7e8d30a9bc1437LL,  0xe86a8db64a5917c6LL}, 
    {0x0f39466eb67061e0LL,  0x274891bf2ccd4f89LL,  0xc5e20d0bb32b0b99LL}, 
    {0xe9602500f680fd9cLL,  0x7af9c86b941f4930LL,  0x5d4c72f6f18f180dLL}, 
    {0x50ff769755237f75LL,  0x6f343b2b54c5c6d0LL,  0x474e0c9b0b3467ebLL}, 
    {0xaae5613904f1d5d2LL,  0xbcb5f7c5c93e5659LL,  0xac585d512743f140LL}, 
    {0x75105328a1274e97LL,  0x2e8bc3ffd4928ab9LL,  0xe741086919d0b29dLL}, 
    {0xf0930cf1b7eaef60LL,  0xbdb7571e8b7de932LL,  0xa0f09495e844f9fbLL}, 
    {0x695720dd7b0a1b89LL,  0xc53039989cc7efafLL,  0x6d3b644197303304LL}, 
    {0x02aeda9b5143807bLL,  0x45922af238cf9ec4LL,  0xc2914fab5dc0227aLL}, 
    {0xb32b7c9cc2e7b199LL,  0xda27f1713d6c490aLL,  0x8dead60e6ac73b81LL}, 
    {0xabe93978a718b507LL,  0xae6f14bd4244ad2fLL,  0xe89daf30a150a8fbLL}, 
    {0x40bfd4ede5b5f1f5LL,  0x51cd84c2885f235aLL,  0xaf611780f72517d2LL}, 
    {0x744c2d161b433441LL,  0x16a3339b8e6b258aLL,  0x9206351739a34e7fLL}, 
    {0xc34d66db78cb55ceLL,  0x064cec84293e5b88LL,  0xfdd365893f4ddf25LL}, 
    {0xcf826bb198ac3dcdLL,  0x64567875fe2b963fLL,  0x52ca16575bc716f6LL}, 
    {0x94a37135f987b45fLL,  0x70153e02204a20acLL,  0xcc8512763618fc85LL}, 
    {0xf6c4b56f8db98cc0LL,  0xf99daa90f251002fLL,  0x002d1eeb2e5c6c04LL}, 
    {0x8e09e8fdb48918bfLL,  0x6bf0a4e058f5106eLL,  0x534330dd5830c82bLL}, 
    {0xe98f0e970aef8b03LL,  0x533722153734e488LL,  0xad3feccde84f7acbLL}, 
    {0x4502a48a72ca07b6LL,  0xef8e51317db9b8d8LL,  0xf9bd4627edbfd42fLL}, 
    {0xcdf4b614e78b9ba3LL,  0xd7c6c1291cf9434cLL,  0x0dfc829fc9bfae47LL}, 
    {0xd8ebbb892586c1d3LL,  0xbab62f894a858636LL,  0xefa5d71d19463f1bLL}, 
    {0xb848e9d01c9e7d69LL,  0x90de57ca11db53aaLL,  0x309b47ed5f78951cLL}, 
    {0x2c0e9d6ea2a55646LL,  0x486509820eb94d8aLL,  0x00034d2e09e2789eLL}, 
    {0x603ca2f6b61b1123LL,  0x06287f423d58ba02LL,  0xdca26d93bee31c90LL}, 
    {0x1845f815060c7a92LL,  0x0f8bb0f4e086a4bfLL,  0xfe893be18d168fd3LL}, 
    {0xb7522d5063d28fc8LL,  0x4605d20affd95ddaLL,  0x3a4ae4b63ede60e4LL}
} ;

/* plaid.c begins here */
#include "plaid.c"
/* plaid.c ends here */
int
generateredmoves(CheckerBoard *b, CheckerBoard *m, BitBoard v)
{
    BitBoard next, c ;
    CheckerBoard *moves = m ;

    while (v) {
	next = v & (v-1) ;
	c = v ^ next ;
	v = next ;
   	
	if (b->R&b->K&c)
		m = redkingmove(LOG2(c), b, m) ;
	else if (b->R&c)
		m = redmanmove(LOG2(c), b, m) ;
    }
    return m-moves ;
}

int
generatewhitemoves(CheckerBoard *b, CheckerBoard *m, BitBoard v)
{
    BitBoard next, c ;
    CheckerBoard *moves = m ;

    while (v) {
	next = v & (v-1) ;
	c = v ^ next ;
	v = next ;
   	
	if (b->W&b->K&c)
		m = whitekingmove(LOG2(c), b, m) ;
	else if (b->W&c)
		m = whitemanmove(LOG2(c), b, m) ;
    }
    return m-moves ;
}

int
generateredcaptures(CheckerBoard *b, CheckerBoard *m, BitBoard v)
{
    BitBoard next, c ;
    CheckerBoard *moves = m ;

    while (v) {
	next = v & (v-1) ;
	c = v ^ next ;
	v = next ;
   	
	if (b->R&b->K&c)
		m = redkingjump(LOG2(c), b, m) ;
	else if (b->R&c)
		m = redmanjump(LOG2(c), b, m) ;
    }
    return m-moves ;
}

int
generatewhitecaptures(CheckerBoard *b, CheckerBoard *m, BitBoard v)
{
    BitBoard next, c ;
    CheckerBoard *moves = m ;

    while (v) {
	next = v & (v-1) ;
	c = v ^ next ;
	v = next ;
   	
	if (b->W&b->K&c)
		m = whitekingjump(LOG2(c), b, m) ;
	else if (b->W&c)
		m = whitemanjump(LOG2(c), b, m) ;
    }
    return m-moves ;
}


ub8
recomputeboardhash(CheckerBoard *b, int color)
{
    unsigned long long h = 0LL ;
    BitBoard m, next, c ;

    m = b->R ;
    while (m) {
	next = m & (m - 1) ;
	c = m ^ next ;
	m = next ;

	h ^= Hash[LOG2(c)].R ;
    }
    m = b->W ;
    while (m) {
	next = m & (m - 1) ;
	c = m ^ next ;
	m = next ;

	h ^= Hash[LOG2(c)].W ;
    }
    m = b->K ;
    while (m) {
	next = m & (m - 1) ;
	c = m ^ next ;
	m = next ;

	h ^= Hash[LOG2(c)].K ;
    }

    if (color == COLOR_RED)
	h ^= COLORSWAP ;

    return h ;
}
