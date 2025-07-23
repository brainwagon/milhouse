#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <strings.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/types.h>
#include <regex.h>
#include <time.h>
#include <sys/time.h>
#include <setjmp.h>
#include <signal.h>
#include <assert.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <ctype.h>
#include <dlfcn.h>

#include <sqlite3.h>

#include "lookupa.h"
#include "lookup8.h"
#include "milhouse.h"

/*
 * $Id: milhouse.c,v 1.105 2010/04/08 19:54:10 markv Exp $
 *         _ _ _
 *   _ __ (_) | |_  ___ _  _ ___ ___
 *  | '  \| | | ' \/ _ \ || (_-</ -_)
 *  |_|_|_|_|_|_||_\___/\_,_/__/\___|
 *
 * A simple Checkers playing program which is used as a platform for
 * learning more about searching game trees.  Part of my list of 
 * "100 interesting programs to write before I die".
 *
 * Written by Mark VandeWettering <brainwagon@gmail.com>
 *   ⛀   ⛀   ⛀   ⛀
 * ⛀   ⛀   ⛀   ⛀
 *   ⛀   ⛀   ⛀   ⛀
 *
 *
 * ⛂   ⛂   ⛂   ⛂
 *   ⛂   ⛂   ⛂   ⛂
 * ⛂   ⛂   ⛂   ⛂
 */

double 
gettimer()
{
    struct timeval tv ;

    gettimeofday(&tv, NULL) ;
    return (double) tv.tv_sec + (double) tv.tv_usec / 1000000.0 ;
}

int
popcount0(BitBoard v)
{
    /* magic method, courtesy of Brian Kernighan 
     * takes time proportional to the number of set bits... 
     * too clever, by half. */
    int c ;
    for (c=0; v; c++) v &= v-1 ;
    return c ;
}

int
popcount(register unsigned int x)
{
    x -= ((x >> 1) & 0x55555555);
    x = (((x >> 2) & 0x33333333) + (x & 0x33333333));
    x = (((x >> 4) + x) & 0x0f0f0f0f);
    x += (x >> 8);
    x += (x >> 16);
    return(x & 0x0000003f);
}

int
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

int
SQ(CheckerBoard *b, int i) 
{
    int idx ;
    static int chars[8] = {'-', /* 000 = blank */
			   'r', /* 001 = red */
			   'w', /* 010 = white */
			   '?', /* 011 = error */
			   '?', /* 100 = error */
			   'R', /* 101 = red king */
			   'W', /* 110 = white king */
			   '?', /* 111 = error */
			} ;
    idx = ((b->R >> i) & 1)
	     |(((b->W) >> i) & 1) << 1
	     |(((b->K) >> i) & 1) << 2 ;
    return chars[idx] ;
}

BitBoard
reversebitboard(BitBoard v)
{
    v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1) ;
    v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2) ;
    v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4) ;
    v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8) ;
    v = ((v >> 16) | (v << 16)) ;
    return v ;
}

int
ReverseBoard(CheckerBoard *b, int color)
{
    BitBoard br, bw, bk ;
    br = reversebitboard(b->R) ;
    bw = reversebitboard(b->W) ;
    bk = reversebitboard(b->K) ;

    b->W = br ;
    b->R = bw ;
    b->K = bk ;
    b->hash = recomputeboardhash(b, 1-color) ;
    return 1-color ;
}

char *
FEN(CheckerBoard *b, int color)
{
    static char buf[80], *bp ;
    char * sep ;
    int i ;

    bp = buf ;

    if (color == COLOR_RED)
	*bp++ = 'B';
    else
	*bp++ = 'W';
    *bp++ = ':' ;
    sep = "" ;
    if (b->W) {
	*bp++ = 'W' ;
	for (i=0; i<32; i++) {
	    if ((b->W&b->K) & (1<<i)) {
		sprintf(bp, "%sK%d", sep, i+1) ;
		sep = "," ;
		while (*bp) bp++ ;
	    } else if (b->W & (1<<i)) {
		sprintf(bp, "%s%d", sep, i+1) ;
		sep = "," ;
		while (*bp) bp++ ;
	    }
	}
    }
    *bp++ = ':' ;
    sep = "" ;
    if (b->R) {
	*bp++ = 'B' ;
	for (i=0; i<32; i++) {
	    if ((b->R&b->K) & (1<<i)) {
		sprintf(bp, "%sK%d", sep, i+1) ;
		sep = "," ;
		while (*bp) bp++ ;
	    } else if (b->R & (1<<i)) {
		sprintf(bp, "%s%d", sep, i+1) ;
		sep = "," ;
		while (*bp) bp++ ;
	    }
	}
    }
    return buf ;
}

/* 
 * A really quick and dirty FEN parser.  It's not very robust, but should
 * do the trick for some easy testing.
 */

int
FENParse(char *str, CheckerBoard *b, int *color)
{
    char *cp ;

    /* uppercase everything */
    for (cp=str; *cp; cp++) {
	if (islower(*cp)) *cp = toupper(*cp) ;
	if (*cp == 'R') *cp = 'B' ;
    }

    /* reset, and try scanning again */
    cp = str ;
    if (*cp == 'B') {
	*color = COLOR_RED ;
	cp++ ;
    } else if (*cp == 'W') {
	*color = COLOR_WHITE ;
	cp++ ;
    } else
	return FALSE ;

    if (*cp != ':')
	return FALSE ;
    cp ++ ;

    /* get a color */
    int which ;
    int n ;
    int isking = FALSE ;

    b->R = 0 ;
    b->W = 0 ;
    b->K = 0 ;

    while (*cp) {
	if (*cp == 'B') 
	    which = COLOR_RED ;
	else if (*cp == 'W')
	    which = COLOR_WHITE ;
	else
	    return FALSE ;
	cp ++ ;

	    while (*cp && *cp != ':') {
		if (*cp == 'K') {
		    isking = TRUE ;
		    cp ++ ;
		} else if (isdigit(*cp)) {
		    n = atoi(cp) ;
		    switch (which) {
		    case COLOR_RED: 
			b->R |= (1<<(n-1)) ;
			break ;
		    case COLOR_WHITE:
			b->W |= (1<<(n-1)) ;
			break ;
		    }
		    if (isking) {
			b->K |= (1<<(n-1)) ;
			isking = FALSE ;
		    }
		    while (isdigit(*cp))
			cp ++ ;
		} else if (*cp == ',') {
		    cp++ ;
		}
	    } 
	    if (*cp == ':')
		cp++ ;
    }
	    
    b->hash = recomputeboardhash(b, *color) ;
    return TRUE ;
}


int usechinook = TRUE ; 
int usehistory = TRUE ; 
int usetransposition = TRUE ; 
int useetc = FALSE ;
int timeflag = TRUE ;
int killflag = FALSE ;
int invertflag = FALSE ;
int color ;
int quiescenceflag = TRUE ;
int timelimit = 0 ;
int repcheck = 1 ;

/* 
 * Simple repetition checker...  As alpha beta gets called, we store the
 * hash of the current position in a table, and if we have repetition
 * checking turned on, and we've seen this position before, score it as a
 * zero. 
 */

ub8 rephash[MAXPLY] ;
int repcnt = 0 ;

void
RepetitionReset()
{
    repcnt = 0 ;
}

void
RepetitionRemember(CheckerBoard *b)
{
    rephash[repcnt++] = b->hash ;
    if (repcnt >= MAXPLY) abort() ;
}

void
RepetitionForget() 
{
    repcnt -- ;
    if (repcnt < 0) abort() ;
}

int
RepetitionCheck(CheckerBoard *b)
{
    int i ;

    for (i=0; i<repcnt; i++) {
	if (b->hash == rephash[i]) return 1 ;
    }
    return 0 ;
}


extern int ChinookLookup(CheckerBoard *, int) ;

typedef struct t_dbinterace {
    char *name ;
    void (*init) (void) ;
    int (*valid) (CheckerBoard *b) ;
    int (*lookup) (CheckerBoard *b, int color) ;
    void (*close) (void) ;
} DBInterface ;

void
CakeInit(void)
{
    extern int db_init(int suggestedMB, char out[256]);
    extern void db_infostring(char *str) ;
    char cakemsg[256] ;
    int np = db_init(512, cakemsg) ;
    printf("... %d piece cake database loaded.\n", np) ;
    {
	int ld = FALSE ;
	char *cp, cakeinfo[1024] ;
	db_infostring(cakeinfo) ;
	for (cp = cakeinfo; *cp; cp++) {
	    if (ld == FALSE)
		printf("... ") ;
	    ld = TRUE ;
	    putchar(*cp) ;
	    if (*cp == '\n')
		ld = FALSE ;
	}
    }
}

void
CakeClose(void)
{
    extern int db_exit(void) ;
    db_exit() ;
}

int 
CakeValid(CheckerBoard *b)
{
    /* presumes an 8 man database */
    if (b->R == 0 || b->W == 0) return FALSE ;
    if (popcount(b->R|b->W) > 8) return FALSE ;
    return TRUE ;
}

int
CakeLookup(CheckerBoard *b, int color)
{
    extern int CakeLookupAdapter(CheckerBoard *b, int color) ;
    return CakeLookupAdapter(b, color) ;
}

DBInterface CakeInterface = {
	"cake", 
	CakeInit,
	CakeValid,
	CakeLookup,
	CakeClose
} ;

void 
ChinookInit(void) 
{ 
    fprintf(stderr, "... initializing chinook database...\n") ;
    extern void DBInit(void) ;
    DBInit() ;
}

int 
ChinookValid(CheckerBoard *b) 
{ 
    if (b->R == 0 || b->W == 0) return 0 ;
    if (popcount(b->R|b->W) > 6) return 0 ;
    return 1 ;
}

int 
ChinookLookup(CheckerBoard *b, int color) 
{ 
    extern int ChinookLookupAdapter(CheckerBoard *b, int color)  ;
    return ChinookLookupAdapter(b, color) ;
}

void 
ChinookClose(void) { 
    fprintf(stderr, "... ending chinook database...\n") ;
}

DBInterface ChinookInterface = {
	"chinook", 
	ChinookInit,
	ChinookValid,
	ChinookLookup,
	ChinookClose
} ;


void NoneInit(void) { } ;
int NoneValid(CheckerBoard *b) { return FALSE ; }
int NoneLookup(CheckerBoard *b, int color) { return DB_UNKNOWN ; }
void NoneClose(void) { }

DBInterface NoneInterface = {
	"none",
	NoneInit,
	NoneValid,
	NoneLookup,
	NoneClose
} ;

DBInterface *db = & ChinookInterface;

void
DatabaseInit(DBInterface *db)
{
	(db->init) () ;
}

int
DatabaseValid(DBInterface *db, CheckerBoard *b)
{
	return (db->valid) (b) ;
}

int
DatabaseLookup(DBInterface *db, CheckerBoard *b, int color)
{
	return (db->lookup) (b, color) ;
}

void
DatabaseClose(DBInterface *db)
{
	(db->close) () ;
}

char *
DatabaseName(DBInterface *db)
{
	return db->name ;
}

void
DumpSmallBoard(CheckerBoard *b, int color, FILE *fp)
{

    int i ;
    static char *fmt[2] = {"\t| %c %c %c %c|\n", "\t|%c %c %c %c |\n"} ;
    int which = 0 ;
    fprintf(fp, "\t   White  \n") ;
    fprintf(fp, "\t+--------+\n") ;
    for (i=28;i>=0;i-=4) {
	fprintf(fp, fmt[which], SQ(b,i+3), SQ(b,i+2), SQ(b,i+1), SQ(b,i)) ;
	which = 1 - which ;
    }
    fprintf(fp, "\t+--------+\n") ;
    fprintf(fp, "\t   Red    \n") ;
    fprintf(fp, "... %s to move\n", color == COLOR_RED ? "Red" : "White") ;
    fprintf(fp, "... FEN: %s\n", FEN(b, color)) ;
    fprintf(fp, "\n") ;
}

static void
DumpSeps(FILE *fp)
{
    int i ;
    fputc('+', fp) ;
    for (i=0; i<8; i++) 
	fprintf(fp, "-------+") ;
    fputc('\n', fp) ;
}

static void
DumpNumbers(int row, int col, FILE *fp) 
{
    if (((row + col) & 1) == 0)
	fprintf(fp, "       |") ;
    else
	fprintf(fp, "     %02d|", (8 * row + col) / 2 + 1) ;
}

static void
DumpMen(CheckerBoard *b, int row, int col, FILE *fp) 
{
    if (((row + col) & 1) == 0) 
	fprintf(fp, "       |") ;
    else {
	int idx = 4 * row + col / 2 ;
	if (b->R & (1 << idx))
	    fprintf(fp, "[7;31m[=====][m|") ;
	else if (b->W & (1<<idx))
	    fprintf(fp, "[1;47;30m[     ][m|") ;
	else
	    fprintf(fp, "       |") ;
    }
}

static void
DumpKings(CheckerBoard *b, int row, int col, FILE *fp) 
{
    if (((row + col) & 1) == 0) 
	fprintf(fp, "       |") ;
    else {
	int idx = 4 * row + col / 2 ;
	if ((b->K & b->R) & (1 << idx))
	    fprintf(fp, "[7;31m[=====][m|") ;
	else if ((b->K & b->W) & (1 << idx))
	    fprintf(fp, "[1;47;30m[     ][m|") ;
	else
	    fprintf(fp, "       |") ;
    }
}


void
DumpBoard(CheckerBoard *b, int color, int invert, FILE *fp)
{
    DumpSeps(fp) ;
    int row, col ;
    for (row=0; row<8; row++) {
	fputc('|', fp) ;
	for (col=0; col<8; col++)
	    if (invert)
		DumpNumbers(7-row, 7-col, fp) ;
	    else
		DumpNumbers(row, col, fp) ;
	fputc('\n', fp) ;
	fputc('|', fp) ;
	for (col=0; col<8; col++)
	    if (invert)
		DumpKings(b, 7-row, 7-col, fp) ;
	    else
		DumpKings(b, row, col, fp) ;
	fputc('\n', fp) ;
	fputc('|', fp) ;
	for (col=0; col<8; col++)
	    if (invert)
		DumpMen(b, 7-row, 7-col, fp) ;
	    else
		DumpMen(b, row, col, fp) ;
	fputc('\n', fp) ;
	DumpSeps(fp) ;
    }
    fprintf(fp, "... %s to move\n", color == COLOR_RED ? "Red" : "White") ;
    fprintf(fp, "... FEN: %s\n", FEN(b, color)) ;
}


char *
ComputeMove(CheckerBoard *f, CheckerBoard *t, int color) 
{
    static char buf[1024] ;
    BitBoard p, q ;
    switch (color) {
    case COLOR_RED:
	p = f->R ^ t->R ;
	if (popcount(p) != 2)
	    strcpy(buf, "?-?") ;
	else {
	    q = p & (p - 1) ;
	    p = p ^ q ;
	    if (f->R & q) {
		/* swap p and q, in entirely too clever a way */
		p = p ^ q ;
		q = p ^ q ;
		p = p ^ q ;
	    }
	    sprintf(buf, "%2d%c%-2d", LOG2(p)+1, f->W==t->W?'-':'x', LOG2(q)+1) ;
	}
	break ;
    case COLOR_WHITE:
	p = f->W ^ t->W ;
	if (popcount(p) != 2)
	    strcpy(buf, "?-?") ;
	else {
	    q = p & (p - 1) ;
	    p = p ^ q ;
	    if (f->W & q) {
		/* swap p and q, in entirely too clever a way */
		p = p ^ q ;
		q = p ^ q ;
		p = p ^ q ;
	    }
	    sprintf(buf, "%2d%c%-2d", LOG2(p)+1, f->R==t->R?'-':'x', LOG2(q)+1) ;
	}
	break ;
    default:
	abort() ;
    }
    return buf ;
}

void
DumpMove(CheckerBoard *from, CheckerBoard *to, int color, int move, int eval)
{
    switch (color) {
    case COLOR_RED:
	printf("%3d.\t%s [%d]\n", move+1, ComputeMove(from, to, color), eval) ;
	break ;
    case COLOR_WHITE:
	printf("%3d.\t...\t%s [%d]\n", move+1, ComputeMove(from, to, color), eval) ;
	break ;
    }
    if (color == COLOR_WHITE && ((move + 1) % 10 == 0))
    DumpBoard(to, 1-color, invertflag, stdout) ;
    fflush(stdout) ;
}


FILE * tlog = NULL ;

void
tlog_begin()
{
    tlog = fopen("terse.log", "w") ;
}

void
tlogboard(CheckerBoard *b, int color, int depth)
{
#undef TERSE_LOG
#if defined(TERSE_LOG) 
	if (tlog) fprintf(tlog, "%02d 0x%08x 0x%08x 0x%08x %1d\n", depth, b->R, b->W, b->K, color) ;
#endif /* TERSE_LOG */
}

void
tlog_end()
{
    fclose(tlog) ;
    tlog = NULL ;
}

/*----------------------------------------------------------------------*/
/* Transposition table functions are below...				*/
/* 									*/
/* These functions implement a two tiered cache scheme.   There are two */
/* parallel hash tables.  The tier0 table is updated only if the new    */
/* entry was at a depth lower (closer to the root) than the existing    */
/* entry.   If you can't update the tier0 entry, then you update the    */
/* tier1 entry.  This idea apparently originated with Ken Thompson and  */
/* his work on Belle.   I could do worse than to imitate him. 		*/
/*----------------------------------------------------------------------*/

#define TRANSPOSITION_LOG2SIZE		(20)
#define TRANSPOSITION_SIZE		(1LL<<(TRANSPOSITION_LOG2SIZE))
#define	TRANSPOSITION_MASK		(TRANSPOSITION_SIZE-1LL) 

Transposition tier0[TRANSPOSITION_SIZE] ;
Transposition tier1[TRANSPOSITION_SIZE] ;

static Counter tt_gets ;
static Counter tt_gets0 ;
static Counter tt_gets1 ;

static Counter tt_stores ;
static Counter tt_stores0 ;
static Counter tt_stores1 ;

static Counter tt_stores_beta ;
static Counter tt_stores_alpha ;
static Counter tt_stores_exact ;

static Counter chinookups = 0 ;

static Counter history[32][32] ;		/* for move ordering.. */

void
InitTranspositionTables(void)
{
    memset(tier0, 0, sizeof(tier0)) ;
    memset(tier1, 0, sizeof(tier1)) ;
    tt_gets = tt_stores = tt_stores_beta = tt_stores_alpha = tt_stores_exact = 0 ;
    tt_gets0 = tt_gets1 = tt_stores0 = tt_stores1 = 0 ;
    chinookups = 0 ;

    /* reset all the history information too... */
    memset(history, 0, sizeof(history)) ;
}


Transposition *
GetTranspositionTable(ub8 hash, int depth) 
{
    int slot = (int) (hash & TRANSPOSITION_MASK) ;
    
    tt_gets ++ ;

    if (tier0[slot].hash == hash && depth <= tier0[slot].depth) {
	tt_gets0 ++ ;
	return tier0 + slot ;
    }

    if (tier1[slot].hash == hash && depth <= tier1[slot].depth)  {
	tt_gets1 ++ ;
	return tier1 + slot ;
    }

    return NULL ;
}

void
StoreTranspositionTable(CheckerBoard *b, int color, int depth, CheckerBoard *best, int flags, int value)
{
    ub8 hash = b->hash ;
    int slot = (int) (hash & TRANSPOSITION_MASK) ;
    Transposition *t ;
    BitBoard from, to ;

    assert(color == COLOR_RED || color == COLOR_WHITE) ;
    tt_stores ++ ;
    if (depth >= tier0[slot].depth) {
	tt_stores0 ++ ;
	t = tier0 + slot ;
	/* should I push the contents from tier0 to tier1 ? */
	tier1[slot] = tier0[slot] ;
    } else {
	tt_stores1 ++ ;
	t = tier1 + slot ;
    }

    t->hash = hash ;
    t->flags = flags ;
    t->value = value ;
    t->depth = depth ;
    if (best != NULL) t->best = *best ;

    switch(color) {
    case COLOR_RED:
	from = b->R    & (b->R^best->R) ;
	to   = best->R & (b->R^best->R) ;
	break ;
    case COLOR_WHITE:
    default:
	from = b->W    & (b->W^best->W) ;
	to   = best->W & (b->W^best->W) ;
	break ;
    }

    history[LOG2(from)][LOG2(to)] += (1L<<depth)  ;

    switch(flags) {
    case TRANSPOSITION_BETA:
	tt_stores_beta++ ; break ;
    case TRANSPOSITION_ALPHA:
	tt_stores_alpha++ ; break ;
    case TRANSPOSITION_EXACT:
	tt_stores_exact++ ; break ;
    }

}

void
PrintTranspositionTableTotals()
{

    printf("transposition tables\n") ;
    printf("... %" PRIu64 " gets (%" PRIu64 " tier0 / %" PRIu64 " tier1 / %" PRIu64 " failed)\n", 
		tt_gets,
		tt_gets0,
		tt_gets1,
		tt_gets - tt_gets0 - tt_gets1) ;
    printf("... %" PRIu64 " puts (%" PRIu64 " tier0 / %" PRIu64" tier1) (%" PRIu64" alpha, %" PRIu64", %" PRIu64" beta)\n",
		tt_stores,
		tt_stores0,
		tt_stores1, 
		tt_stores_alpha,
		tt_stores_exact, 
		tt_stores_beta) ;
    printf("... %" PRIu64 " database accesses.\n", chinookups) ;

#if 0
    int i, j ;
    for (i=0; i<32; i++) {
	for (j=0; j<32; j++)
	    printf("%" PRIu64 "  ", history[i][j]) ;
	printf("\n") ;
    }
#endif
}

Counter nodes_searched = 0 ;
Counter nodes_pvhit = 0 ;
Counter nodes_pvmiss = 0 ;
Counter nodes_evaluated = 0 ;
Counter nodes_ordered = 0 ;

Counter nodes_alpha = 0 ;
Counter nodes_beta = 0 ;
Counter nodes_exact = 0 ;

void
InitSearchTotals()
{
    nodes_searched = 0 ;
    nodes_pvhit = 0 ;
    nodes_pvmiss = 0 ;
    nodes_evaluated = 0 ;
    nodes_ordered = 0 ;

    nodes_alpha = 0 ;
    nodes_beta = 0 ;
    nodes_exact = 0 ;
}

void
PrintSearchTotals(int depth)
{
    double bf = exp(log((double) nodes_evaluated) / depth) ;
    printf("... %" PRIu64 " nodes searched, %" PRIu64 " nodes evaluated\n", nodes_searched, nodes_evaluated) ;
    printf("... %" PRIu64 " alpha nodes, %" PRIu64 " pv nodes, %" PRIu64 " beta cutoffs\n", 
		nodes_alpha, nodes_exact, nodes_beta) ;
    printf("... avg branching factor %.2f\n", bf) ;
    printf("... %" PRIu64 " nodes ordered\n", nodes_ordered) ;
    printf("... %" PRIu64 " pv hits, %" PRIu64 " pv misses (%4.2f%%)\n", nodes_pvhit, nodes_pvmiss, 
		100.0 * nodes_pvhit / (nodes_pvhit + nodes_pvmiss)) ;
}



#ifdef USE_TRANSPOSITION_TABLES
Transposition *
FindTransposition(ub8 hash)
{
    int slot = (int) (hash & TRANSPOSITION_MASK) ;
    if (tier0[slot].hash == hash)
	return tier0 + slot ;
    if (tier1[slot].hash == hash)
	return tier1 + slot ;
    return NULL ;
}

char *
ComputeLine(CheckerBoard *b, int color, int depth)
{
    static /* dangerous */ char buffer[4096] ;
    Transposition *t ;
    int i ;

    /* if (depth > 7) depth = 7 ; */

    strcpy(buffer, "") ;
    for (i=0; i<=depth; i++) {
	if (b->W == 0 || b->R == 0) {
	    return buffer ;
	}
	t = FindTransposition(b->hash) ;
	if (t == NULL)
	    break ;
	if (i)
	    strcat(buffer, " ") ;
	strcat(buffer, ComputeMove(b, &(t->best), color)) ;
	b = &(t->best) ;
	color = 1 - color ;
    }
   
    if (i == depth)
	strcat(buffer, " ...") ;
    return buffer ;
}
#endif

/*----------------------------------------------------------------------*/

#define FWD_3 0x00e0e0e0
#define FWD_4 0x0fffffff
#define FWD_5 0x07070707
#define REV_3 0x07070700
#define REV_4 0xfffffff0
#define REV_5 0xe0e0e0e0

BitBoard
RedMovers(CheckerBoard *b)
{
    BitBoard U = ~(b->R|b->W) ;
    BitBoard M ;
    M  = (b->R & FWD_4) & (U >> 4) ;
    M |= (b->R & FWD_5) & (U >> 5) ;
    M |= (b->R & FWD_3) & (U >> 3) ;
    BitBoard RK = b->R & b->K ;
    if (RK) {
	M |= (RK & REV_4) & (U << 4) ;
	M |= (RK & REV_5) & (U << 5) ;
	M |= (RK & REV_3) & (U << 3) ;
    }
    return M ;
}

BitBoard
RedAttacked(CheckerBoard *b)
{
    BitBoard U = ~(b->R|b->W) ;
    BitBoard M ;

    M  = (b->R & FWD_4) << 4 ;
    M |= (b->R & FWD_5) << 5 ;
    M |= (b->R & FWD_3) << 3 ;
    BitBoard RK = b->R & b->K ;
    if (RK) {
	M |= (RK & REV_4) >> 4 ;
	M |= (RK & REV_5) >> 5 ;
	M |= (RK & REV_3) >> 3 ;
    }
    return M & U;
}

BitBoard
WhiteMovers(CheckerBoard *b)
{
    BitBoard U = ~(b->R|b->W) ;
    BitBoard M ;
    M  = (b->W & REV_4) & (U << 4) ;
    M |= (b->W & REV_5) & (U << 5) ;
    M |= (b->W & REV_3) & (U << 3) ;
    BitBoard WK = b->W & b->K ;
    if (WK) {
	M |= (WK & FWD_4) & (U >> 4) ;
	M |= (WK & FWD_5) & (U >> 5) ;
	M |= (WK & FWD_3) & (U >> 3) ;
    }
    return M ;
}

BitBoard
WhiteAttacked(CheckerBoard *b)
{
    BitBoard U = ~(b->R|b->W) ;
    BitBoard M ;

    M  = (b->W & REV_4) >> 4 ;
    M |= (b->W & REV_5) >> 5 ;
    M |= (b->W & REV_3) >> 3 ;
    BitBoard WK = b->W & b->K ;
    if (WK) {
	M |= (WK & FWD_4) << 4 ;
	M |= (WK & FWD_5) << 5 ;
	M |= (WK & FWD_3) << 3 ;
    }
    return M & U ;
}

#define JFWD_37 0x00e0e0e0
#define JFWD_47 0x000e0e0e
#define JFWD_49 0x00707070
#define JFWD_59 0x00070707

#define JREV_37 0x07070700
#define JREV_47 0x70707000
#define JREV_49 0x0e0e0e00
#define JREV_59 0xe0e0e000

BitBoard
RedJumpers(CheckerBoard *b)
{
    BitBoard U = ~(b->R|b->W) ;
    BitBoard M ;

    M  = (b->R & JFWD_37) & (b->W >> 3) & (U >> 7) ;
    M |= (b->R & JFWD_47) & (b->W >> 4) & (U >> 7) ;
    M |= (b->R & JFWD_49) & (b->W >> 4) & (U >> 9) ;
    M |= (b->R & JFWD_59) & (b->W >> 5) & (U >> 9) ;

    BitBoard RK = b->R & b->K ;
    if (RK) { 
	M |= (RK & JREV_37) & (b->W << 3) & (U << 7) ;
	M |= (RK & JREV_47) & (b->W << 4) & (U << 7) ;
	M |= (RK & JREV_49) & (b->W << 4) & (U << 9) ;
	M |= (RK & JREV_59) & (b->W << 5) & (U << 9) ;
    }

    return M ;
}

BitBoard
WhiteJumpers(CheckerBoard *b)
{
    BitBoard U = ~(b->R|b->W) ;
    BitBoard M ;

    M  = (b->W & JREV_37) & (b->R << 3) & (U << 7) ;
    M |= (b->W & JREV_47) & (b->R << 4) & (U << 7) ;
    M |= (b->W & JREV_49) & (b->R << 4) & (U << 9) ;
    M |= (b->W & JREV_59) & (b->R << 5) & (U << 9) ;

    BitBoard WK = b->W & b->K ;
    if (WK) { 
	M |= (WK & JFWD_37) & (b->R >> 3) & (U >> 7) ;
	M |= (WK & JFWD_47) & (b->R >> 4) & (U >> 7) ;
	M |= (WK & JFWD_49) & (b->R >> 4) & (U >> 9) ;
	M |= (WK & JFWD_59) & (b->R >> 5) & (U >> 9) ;
    }

    return M ;
}


/* the most naive alpha beta search program that you can get... */
#define 	MAX(a,b)		(((a)>(b))?(a):(b))
#define 	MIN(a,b)		(((a)<(b))?(a):(b))

int
isterminal(CheckerBoard *b, int color)
{
    switch(color) {
    case COLOR_RED:
	return (RedJumpers(b) == 0) && (RedMovers(b) == 0) ;
    case COLOR_WHITE:
	return (WhiteJumpers(b) == 0) && (WhiteMovers(b) == 0) ;
    default:
	return 0 ;
    }
}

int
anycaptures(CheckerBoard *b, int color) 
{
    switch(color) {
    case COLOR_RED:
	return RedJumpers(b) > 0 ;
    case COLOR_WHITE:
	return WhiteJumpers(b) > 0 ;
    default:
	abort() ; /* serious program bug */
    }
}

int
validchinookposition(CheckerBoard *b)
{
    if (b->R == 0 || b->W == 0) return 0 ;
    if (popcount(b->R|b->W) > 8) return 0 ;
#if 0
    if (RedJumpers(b) > 0) return 0 ;
    if (WhiteJumpers(b) > 0) return 0 ;
#endif
    return 1 ;
}

/* Totally rudimentary evaluation function 
 * The evaluation is called with from the view of the side that is about
 * to move.  From that perspective, the side to move should generate positive
 * values if the side is ahead, and negative ones if the side is about to 
 * lose.
 */

#define KING_VAL	(130)
#define MAN_VAL		(100)

#define CENTERMASK 	0x00666600

#define WMOVEMASK		0xf0f0f0f0
#define RMOVEMASK		0x0f0f0f0f
#define DOUBLE_CORNER_MASK	0x88000011	/* double corners */
#define DOUBLE_DIAGONAL_MASK	0x8cc66331	/* on the double diagonal */


static int gdepth ;

int getmoves(CheckerBoard *b, int color, CheckerBoard move[MAXMOVES]);

void
indent(int n)
{
    int i ;
    for (i=0; i<n; i++) putchar(' ') ;
}

int
DatabaseValueNegate(int value)
{
    switch (value) {
    case DB_WIN:
	return DB_LOSS ;
    case DB_LOSS:
	return DB_WIN ;
    case DB_DRAW:
	return value ;
    case DB_UNKNOWN:
	return value ;
    default:
	abort() ;
    }
    /*NOTREACHED*/
    return DB_UNKNOWN ;
}

int
DatabaseValueDepth(CheckerBoard *b, int color, int depth, int wascapturing)
{
    CheckerBoard child[MAXMOVES] ;
    int i, n, value, bestvalue = DB_LOSS ;
    int capturing = FALSE ;

    /* This is a little tricky.  We may need to run a little minimax search 
     * to actually figure out what the value of the given node is, because the
     * Chinook DB doesn't include any information for positions where 
     * _either_ side can make a capture.  This means that we need to do a bit 
     * of search sometime to resolve the position.  
     * 
     * So, here's the deal:
     * If neither side has a capture, then we know what the value of the 
     * node is (we can just use ChinookLookup to find it).
     * If either side has a capture, then we generate all the moves.
     * We then recurse to find the value of each of the subtrees:
     * 
     * If any of the children are DB_LOSS, then we are a DB_WIN.
     * If all of them are DB_WINS, then our position is a DB_LOSS.
     * Otherwise, it's a CHINOOK_DRAW
     */

    /* 
     * We could have been recursing on a capture, in which case 
     * we could have eliminated the other side (or, indeed, been 
     * eliminated).   So, trap that case, and return the appropriate
     * value.
     */
    switch (color) {
    case COLOR_RED:
	if (b->R == 0) return DB_LOSS ;
	if (b->W == 0) return DB_WIN ;
	break ;
    case COLOR_WHITE:
	if (b->W == 0) return DB_LOSS ;
	if (b->R == 0) return DB_WIN ;
	break ;
    }

    BitBoard rj = RedJumpers(b) ;
    BitBoard wj = WhiteJumpers(b) ;

    /* If neither side has a jump, then we can just lookup the 
     * position.   In theory, we can get an DB_UNKNOWN value here,
     * since Cake (in particular) doesn't include all the 8 piece
     * databases, which could be problematic, but in principle, it 
     * means that a previously "won" position may revert to a position
     * where one side has a very strong material advantage, where conventional
     * search is likely to prove fruitful.
     */

    if (rj == 0 && wj == 0) {
	value = DatabaseLookup(db, b, color) ;
	if (value == DB_UNKNOWN) {
		DumpBoard(b, color, invertflag, stdout) ;
		abort() ;
	}
	return value ;
    }

    switch (color) {
    case COLOR_RED:
	capturing = (rj > 0) ;
	break ;
    case COLOR_WHITE:
	capturing = (wj > 0) ;
	break ;
    }

    /* this doesn't seem sufficient! */
    /* Okay, this comment certainly wasn't sufficient, as I came back
     * to examine this code again months later.   The idea is this: the
     * database doesn't store any information for positions where either
     * side might have a jump.  So, as long as either side has a jump, 
     * we continue to recurse.   Except that would allow us to recurse 
     * infinitely.   So, we have to trim those off.
     */
    if (!capturing && !wascapturing)
	return DB_DRAW ;

    /* capturing || wascapturing */
    n = getmoves(b, color, child) ;
    if (n == 0) return DB_LOSS ;

    for (i=0; i<n; i++) {
	value = DatabaseValueNegate(DatabaseValueDepth(child+i, 1-color, depth+1, capturing)) ;
	switch (value) {
	case DB_WIN:
	    return DB_WIN ;
	case DB_LOSS:
	    break ;
	case DB_DRAW:
	    if (bestvalue != DB_UNKNOWN)
	    bestvalue = DB_DRAW ;	/* we'd take it if we could, but */
	    break ;			/* we should keep looking for a win */
	/* If we find an unknown node, we could still resolve the current
	 * position as a WIN, any of the other children are wins.
	 * If we don't find a definite win, it is only safe to list it as 
	 * unknown.
	 */
	case DB_UNKNOWN:		
	    bestvalue = DB_UNKNOWN ;
	    abort() ;
	    break ;
	}
    }
    return bestvalue ;
}

int
DatabaseValue(CheckerBoard *b, int color)
{   
    return DatabaseValueDepth(b, color, 0, TRUE) ;
}

/* Cribbed the idea from cakepp.   The idea is to keep the men from
 * advancing too quick early in the game, and nudge them into advancing
 * later.  It's indexed by the number of men/kings left on the board.
 * Early on, you are penalized for tempo, later on, you are rewarded.
 */
static int TempoMultiplier[25] =
    { 0, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0, -1, -1, -1, -1, -2, -2, -2,
-2, -3, -3, -3, -3 };

/* This table gives a bonus for certain configurations of the back row,
 * which I shamefully also cribbed from a version of Cake.
 */

static int BackRow[32] = { 
	0, 0, 2, 2, 4, 6, 10, 10,
	1, 4, 16, 16, 6, 10, 24, 16,
    	0, 0, 2, 2, 4, 10, 16, 16,
    	1, 4, 16, 16, 6, 10, 24, 16
} ;

int
DatabaseScore(CheckerBoard *b, int color, int *value)
{
    if (DatabaseValid(db, b)) {
	int val = DatabaseValue(b, color) ;
	int ntotal = popcount(b->W|b->R) ;
	int nRKc = popcount((b->R &  b->K) & CENTERMASK) ;
	int nWKc = popcount((b->W &  b->K) & CENTERMASK) ;
	int nRK = popcount(b->R & b->K) ;
	int nR = popcount(b->R) - nRK ;
	int nWK = popcount(b->W & b->K) ;
	int nW = popcount(b->W) - nWK ;
        int tempo ;

	chinookups ++ ;
	switch (val) {
	case DB_WIN:
		val = 8000 - ntotal * 100 ;
		val += ((color == COLOR_RED) ? nRK : nWK) * 10 ;
		val += ((color == COLOR_RED) ? nRKc : nWKc) * 2 ;
		tempo = 0 ;
		switch (color) {
		case COLOR_RED:
		    if (nR) {
			tempo += 1 * popcount((b->R&~b->K)&0x000000F0) ;
			tempo += 2 * popcount((b->R&~b->K)&0x00000F00) ;
			tempo += 3 * popcount((b->R&~b->K)&0x0000F000) ;
			tempo += 4 * popcount((b->R&~b->K)&0x000F0000) ;
			tempo += 5 * popcount((b->R&~b->K)&0x00F00000) ;
			tempo += 6 * popcount((b->R&~b->K)&0x0F000000) ;
		    }
		    break ;
		case COLOR_WHITE:
		    if (nW) {
			tempo += 6 * popcount((b->W&~b->K)&0x000000F0) ;
			tempo += 5 * popcount((b->W&~b->K)&0x00000F00) ;
			tempo += 4 * popcount((b->W&~b->K)&0x0000F000) ;
			tempo += 3 * popcount((b->W&~b->K)&0x000F0000) ;
			tempo += 2 * popcount((b->W&~b->K)&0x00F00000) ;
			tempo += 1 * popcount((b->W&~b->K)&0x0F000000) ;
		    }
		    break ;
		}
		val += tempo * TempoMultiplier[ntotal] ;
#if 0
		val += (color == COLOR_RED) ? mobility : -mobility ;
#endif
		break ;
	case DB_LOSS:
		val = -8000 + ntotal * 100 ;
		val -= ((color == COLOR_RED) ? nWK : nRK) * 10 ;
		val -= ((color == COLOR_RED) ? nWKc : nRKc) * 2 ;
		tempo = 0 ;
		switch (color) {
		case COLOR_RED:
		    if (nW) {
			tempo -= 1 * popcount((b->W&~b->K)&0x0F000000) ;
			tempo -= 2 * popcount((b->W&~b->K)&0x00F00000) ;
			tempo -= 3 * popcount((b->W&~b->K)&0x000F0000) ;
			tempo -= 4 * popcount((b->W&~b->K)&0x0000F000) ;
			tempo -= 5 * popcount((b->W&~b->K)&0x00000F00) ;
			tempo -= 6 * popcount((b->W&~b->K)&0x000000F0) ;
		    }
		    break ;
		case COLOR_WHITE:
		    if (nR) {
			tempo -= 6 * popcount((b->R&~b->K)&0x0F000000) ;
			tempo -= 5 * popcount((b->R&~b->K)&0x00F00000) ;
			tempo -= 4 * popcount((b->R&~b->K)&0x000F0000) ;
			tempo -= 3 * popcount((b->R&~b->K)&0x0000F000) ;
			tempo -= 2 * popcount((b->R&~b->K)&0x00000F00) ;
			tempo -= 1 * popcount((b->R&~b->K)&0x000000F0) ;
		    }
		    break ;
		}
		val += tempo * TempoMultiplier[ntotal] ;
#if 0
		val += (color == COLOR_RED) ? mobility : -mobility ;
#endif
		break ;
	case DB_DRAW:
		val = 0;
		break ;
	case DB_UNKNOWN:
		return FALSE ;
	}

	*value = val ;
	return TRUE ;
    } else {
	return FALSE ;
    } 
}

char *
DatabaseResolve(CheckerBoard *b, int color)
{
    if (DatabaseValid(db, b)) {
	switch(DatabaseValue(b, color)) {
	case DB_WIN:
	    return color == COLOR_RED ? "[1;32m(DB R WINS)[0m " : "[1;32m(DB W WINS)[0m " ;
	case DB_LOSS:
	    return color == COLOR_RED ? "[1;31m(DB R LOSES)[0m " : "[1;31m(DB W LOSES)[0m " ;
	case DB_DRAW:
	    return "[1;33m(DB DRAW)[0m " ;
	default:
	    return "" ;
	}
    } else
	return "" ;
}

char *
ChinookShortResolve(CheckerBoard *b, int color)
{
    if (DatabaseValid(db, b)) {
	switch (DatabaseLookup(db, b, color)) {
	case DB_WIN:
	    return " W" ;
	case DB_LOSS:
	    return " L" ;
	case DB_DRAW:
	    return " =" ;
	default:
	    return "" ;
	}
    } else
	return "" ;
}



int 
evaluate(CheckerBoard *b, int color, int depth, int alpha, int beta)
{
    int nRK = popcount(b->R & b->K) ;
    int nR = popcount(b->R) - nRK ;
    int nWK = popcount(b->W & b->K) ;
    int nW = popcount(b->W) - nWK ;
    int ntotal = popcount(b->W|b->R) ;
    int rmatval = KING_VAL * nRK + MAN_VAL * nR ;
    int wmatval = KING_VAL * nWK + MAN_VAL * nW ;

    int nRMc = popcount((b->R & ~b->K) & CENTERMASK) ;
    int nRKc = popcount((b->R &  b->K) & CENTERMASK) ;
    int nWMc = popcount((b->W & ~b->K) & CENTERMASK) ;
    int nWKc = popcount((b->W &  b->K) & CENTERMASK) ;

    int val ;

    nodes_evaluated ++ ;

    val = rmatval - wmatval ;
    val += (250 * (rmatval - wmatval)) / (rmatval + wmatval) ;

    /* make sure we identify winning lines with eval. */

    if (wmatval == 0) {
	val = (color == COLOR_WHITE) ? -WIN+gdepth-depth : WIN-gdepth+depth ;
	assert (-WIN <= val && val <= WIN) ;
	return val ;
    }

    if (rmatval == 0) {
	val = (color == COLOR_WHITE) ? WIN-gdepth+depth : -WIN+gdepth-depth ;
	assert (-WIN <= val && val <= WIN) ;
	return val ;
    }

    /* let's try to localize all our access to the database
     * to this part of the evaluation function.
     */
    if (db != NULL && DatabaseValid(db, b)) {
	if (DatabaseScore(b, color, &val))
	    return val ;
    }

    /* tempo?  add bonuses based upon how far back men are */
    int tempo = 0 ;

    /* we could obviously streamline this code */
    tempo += popcount(b->R & ~b->K & 0x0f000000) ;
    tempo += popcount(b->R & ~b->K & 0x0ff00000) ;
    tempo += popcount(b->R & ~b->K & 0x0fff0000) ;
    tempo += popcount(b->R & ~b->K & 0x0ffff000) ;
    tempo += popcount(b->R & ~b->K & 0x0fffff00) ;
    tempo += popcount(b->R & ~b->K & 0x0ffffff0) ;
    tempo += popcount(b->R & ~b->K & 0x0fffffff) ;
    tempo += 8 * popcount(b->R & b->K)  ;

    tempo -= popcount(b->W & ~b->K & 0x000000f0) ;
    tempo -= popcount(b->W & ~b->K & 0x00000ff0) ;
    tempo -= popcount(b->W & ~b->K & 0x0000fff0) ;
    tempo -= popcount(b->W & ~b->K & 0x000ffff0) ;
    tempo -= popcount(b->W & ~b->K & 0x00fffff0) ;
    tempo -= popcount(b->W & ~b->K & 0x0ffffff0) ;
    tempo -= popcount(b->W & ~b->K & 0xfffffff0) ;
    tempo -= 8 * popcount(b->W & b->K)  ;

    /* modify the tempo... */
    tempo *= TempoMultiplier[ntotal] ;

    /* how about giving a bonus for certain configs of the back row? */
    if (nR + nW > 0) {
	int wrev ;
	/* The backrow(s) looks like this...
	 *   31  30  29  28 
	 * 27  26  25  24 
	 *   23  22  21  20
	 * 19  18  17  16 
	 *   15  14  13  12 
	 * 11  10  09  08 
	 *   07  06  05  04 
	 * 03  02  01  00 
         */
	if (b->R & 1<<7)
	    val += BackRow[(b->R & 0x0000000F)+16] ;
	else
	    val += BackRow[(b->R & 0x0000000F)] ;
	wrev = ((b->W >> 31) & 1) 
	     | ((b->W >> 29) & 2)
	     | ((b->W >> 27) & 4)
	     | ((b->W >> 25) & 8) ;
	if (b->W & 1<<24)
	    val -= BackRow[wrev + 16] ;
	else
	    val -= BackRow[wrev] ;
    }

    /* balance (measure of how evenly distributed left to right) the
     * pieces are.   Basically count all the pieces on the leftmost
     * column, diff them with the rightmost.  Similarly second leftmost
     * and second rightmost.  Ditto third and forth.
     *   31  30  29  28 
     * 27  26  25  24 
     *   23  22  21  20
     * 19  18  17  16 
     *   15  14  13  12 
     * 11  10  09  08 
     *   07  06  05  04 
     * 03  02  01  00 
     */
    int rbalance = -3 * popcount(b->R & (1<<4|1<<12|1<<20|1<<28))
	 	   -2 * popcount(b->R & (1<<0|1<<8|1<<16|1<<24))
		   -1 * popcount(b->R & (1<<5|1<<13|1<<21|1<<29))
		   +1 * popcount(b->R & (1<<2|1<<10|1<<18|1<<26))
		   +2 * popcount(b->R & (1<<7|1<<15|1<<23|1<<31))
		   +3 * popcount(b->R & (1<<3|1<<11|1<<19|1<<27)) ;
    int wbalance = -3 * popcount(b->W & (1<<4|1<<12|1<<20|1<<28))
	 	   -2 * popcount(b->W & (1<<0|1<<8|1<<16|1<<24))
		   -1 * popcount(b->W & (1<<5|1<<13|1<<21|1<<29))
		   +1 * popcount(b->W & (1<<2|1<<10|1<<18|1<<26))
		   +2 * popcount(b->W & (1<<7|1<<15|1<<23|1<<31))
		   +3 * popcount(b->W & (1<<3|1<<11|1<<19|1<<27)) ;

    val -= (ABS(wbalance) - ABS(rbalance)) ;

    /* center */
    val += (nRKc - nWKc) * 4 ;
    val += (nRMc - nWMc) * 1 ;

#define EDGE_MASK	0xf818181f
    val -= ((popcount(b->R&b->K&EDGE_MASK)-popcount(b->W&b->K&EDGE_MASK))) * 3 ;
    val -= ((popcount(b->R&EDGE_MASK)-popcount(b->W&EDGE_MASK))) ;

    /* this bonus is to help drive kings out of the double corner
     * when you have an advantage in the endgame.  If you have more
     * pieces, then you penalize positions where the opposing player
     * occupies double corners.
     */

    if (popcount(b->R) > popcount(b->W) && popcount(b->W&b->K) < 3)
	val -= 15 * popcount(b->W&b->K & DOUBLE_CORNER_MASK) ;
    if (popcount(b->W) > popcount(b->R) && popcount(b->R&b->K) < 3)
	val += 15 * popcount(b->R&b->K & DOUBLE_CORNER_MASK) ;

    if ((b->R&~b->K&(1<<0)) && (b->R&~b->K&((1<<4)|(1<<5))))
	val += 3 ;
    if ((b->W&~b->K&(1<<31)) && (b->W&~b->K&((1<<27)|(1<<26))))
	val -= 3 ;

    val += popcount(b->R & DOUBLE_DIAGONAL_MASK) ;
    val -= popcount(b->W & DOUBLE_DIAGONAL_MASK) ;

    /* intact double corner bonus */
    if ((b->R & ~b->K) & (1<<(1-1)))
	if (b->R & ~b->K & ((1<<(5-1)) | (1<<(6-1))))
	    val += 3 ;

    if ((b->W & ~b->K) & (1<<(32-1)))
	if (b->W & ~b->K & ((1<<(28-1)) | (1<<(27-1))))
	    val -= 3 ;

    /* doghole penalties... */
    if ((b->R & (1<<(1-1))) && (b->W & ~b->K & (1<<(5-1))))
	val += 5 ;
    if ((b->R & ~b->K & (1<<(28-1))) && (b->W & (1<<(32-1))))
	val -= 5 ;

    /* cramp! */
    if ((b->R&(1<<19)) && (b->W&(1<<23)))
	val += 5 ;
    if ((b->W&(1<<12)) && (b->R&(1<< 8)))
	val -= 5 ;

    BitBoard ra = RedAttacked(b) ;
    BitBoard wa = WhiteAttacked(b) ;
    int unattacked = popcount(ra & ~wa) ;
    int attacked = popcount(ra & wa) ;
    val += unattacked - attacked ;		/* from red's perspective */
    if (unattacked < 2 && popcount(ra) > 5)
	val -= 8 ;
    if (unattacked == 0)
	val -= 8 ;
    unattacked = popcount(wa & ~ra) ;		/* and from white's */
    val -= unattacked - attacked ;
    if (unattacked < 2 && popcount(wa) > 5)
	val += 8 ;
    if (unattacked == 0)
	val += 8 ;

#if 0
    val += 2 * popcount (b->R & 0x00022400);
    val -= 2 * popcount (b->W & 0x00244000);
#endif

    /* oreo (wtf?) val, cribbed from cake.. */
    if ((b->R&BIT(1)) && (b->R&BIT(2)) && (b->R&BIT(5)))
	val += 5 ;
    if ((b->W&BIT(29)) && (b->W&BIT(30)) && (b->W&BIT(26)))
	val -= 5 ;

    /* developped single corner */
    if (((~b->R)&BIT(0)) && ((~b->R)&BIT(4)))
	val += 5 ;
    if (((~b->W)&BIT(27)) && ((~b->W)&BIT(31)))
	val -= 5 ;

    if (color == COLOR_WHITE)
	val = -val ;

#if 1
    /* handle "the move" */
    if (popcount(b->R) == popcount(b->W)) {
	if (color == COLOR_RED) {
	    int themove = popcount((b->R|b->W)&0xF0F0F0F0) ;
	    if (themove & 1) 
		val += 2 * (24-ntotal) / 6 ;
	    else 
		val -= 2 * (24-ntotal) / 6 ;
	} else {
	    int themove = popcount((b->R|b->W)&0x0F0F0F0F) ;
	    if (themove & 1) 
		val += 2 * (24-ntotal) / 6 ;
	    else 
		val -= 2 * (24-ntotal) / 6 ;
	}
    }
#endif

    /* the side to move always gets a tiny benefit */
    val += 2 ;

    return val ;
}

int 
checkevaluate(CheckerBoard *b, int color, int depth, int alpha, int beta)
{
    CheckerBoard tmp ;
    int val1 = evaluate(b, color, depth, alpha, beta) ;
    tmp.R = b->W ;
    tmp.W = b->R ;
    tmp.K = b->K ;
    tmp.hash = recomputeboardhash(&tmp, 1-color) ;
    int val2 = evaluate(&tmp, 1-color, depth, alpha, beta) ;

    if (val1 != -val2) {
	printf("val1 = %d val2 = %d\n", val1, val2) ;
	DumpBoard(b, color, invertflag, stdout) ;
	abort() ;
    }
    return val1 ;
}

/*----------------------------------------------------------------------*/


int
getmoves(CheckerBoard *b, int color, CheckerBoard move[MAXMOVES]) 
{
    int n ;
    switch (color) {
    case COLOR_RED:
	n = generateredcaptures(b, move, RedJumpers(b)) ;
	if (n == 0)
	    n = generateredmoves(b, move, RedMovers(b)) ;
	assert(n <= MAXMOVES) ;
	return n ;
    case COLOR_WHITE:
	n = generatewhitecaptures(b, move, WhiteJumpers(b)) ;
	if (n == 0)
	    n = generatewhitemoves(b, move, WhiteMovers(b)) ;
	assert(n <= MAXMOVES) ;
	return n ;
    default:
	abort() ;
    }
}


void
shuffle(CheckerBoard child[MAXMOVES], int n) 
{
    CheckerBoard tmp ;
    int i, j ;

    for (i=n; i; ) {
	j = lrand48() % i-- ;
	tmp = child[i] ;
	child[i] = child[j] ;
	child[j] = tmp ;
    }
}

void
randommove(CheckerBoard *b, CheckerBoard *nb, int color) 
{
    CheckerBoard child[MAXMOVES] ;
    BitBoard m ;
    int n = 0 ;	

    switch (color) {
    case COLOR_RED:
	m = RedJumpers(b) ;
	if (m)
	    n = generateredcaptures(b, child, m) ;
	else {
	    m = RedMovers(b) ;
	    if (m)
		n = generateredmoves(b, child, m) ;
	    else
		n = 0 ;
	}
	break ;
    case COLOR_WHITE:
	m = WhiteJumpers(b) ;
	if (m)
	    n = generatewhitecaptures(b, child, m) ;
	else {
	    m = WhiteMovers(b) ;
	    if (m)
		n = generatewhitemoves(b, child, m) ;
	    else
		n = 0 ;
	}
	break ;
    }
    if (n == 0) 
	abort() ; /* shouldn't happen */
    n = lrand48() % n ;
    *nb = child[n] ;
}

void
printversion()
{
    fprintf(stderr, "milhouse, a checkers program by Mark VandeWettering.\n") ;
#ifdef USE_TRANSPOSITION_TABLES
    fprintf(stderr, "transposition table enabled.\n") ;
    fprintf(stderr, "... (%d/%d) entries, total size %lu Mb\n",
	(ub4) TRANSPOSITION_SIZE, 
	(ub4) TRANSPOSITION_SIZE, 
	((sizeof(tier0)+sizeof(tier1))/(1024*1024))) ;
#else
    fprintf(stderr, "transposition table disabled\n") ;
#endif /* USE_TRANSPOSITION_TABLES */
#ifdef QUIESCENCE
    fprintf(stderr, "quiescence extension enabled\n") ;
#endif /* QUIESCENCE */
    fprintf(stderr, "%d puzzles in the puzzle library\n", npuzzles()) ;
}

#define MOVE_LIMIT	(200)


/* The principal variation is stored in this array by iterative search. */

time_t	thinkstart ;
int 	thinklimit = 600 ;

jmp_buf	abortsearch, intrsearch ;

void
abortsearchhandler(int dummy) 
{ 
    sigrelse(SIGINT) ;
    signal(SIGINT, abortsearchhandler) ;
    siglongjmp(abortsearch, 1) ;
}

/* ARGSUSED */
void
interrupthandler(int dummy)
{
    siglongjmp(intrsearch, 1) ;
}

void
moveoracle(CheckerBoard *b, int color) 
{
    BitBoard m = b->W|b->R ;
    if (popcount(b->R) != popcount(b->W))
	return ;
    switch(color) {
    case COLOR_RED:
	if (popcount(m&RMOVEMASK)&1)
	    printf("RED has the move.\n") ;
	break ;
    case COLOR_WHITE:
	if (popcount(m&RMOVEMASK)&1)
	    printf("WHITE has the move.\n") ;
	break ;
    }
}

double
computehistscore(CheckerBoard *b0, int color, CheckerBoard *b1)
{
    BitBoard f, t ;
    
    if (tt_stores < 1000)		/* wait until we've accumulated some data */
	return 0.0 ;

    switch(color) {
    case COLOR_RED:
	f = b0->R & (b0->R^b1->R) ;
	t = b1->R & (b0->R^b1->R) ;
	break ;
    case COLOR_WHITE:
    default:
	f = b0->W & (b0->W^b1->W) ;
	t = b1->W & (b0->W^b1->W) ;
	break ;
    }

    return (double) history[LOG2(f)][LOG2(t)] / (double) tt_stores ;
}



/*
 * Quiescence search
 * 
 * If there are no captures possible here for the moving side, then 
 * just go right ahead and evaluate it.  Otherwise, go ahead and play
 * out the jumps using a minimax search of just jumping moves to figure
 * out the final value.
 */

int 
quiescence(CheckerBoard *b, int color, int depth, int alpha, int beta)
{
    int i, n, score = -INF, val ;
    CheckerBoard child[MAXMOVES] ;

    if ((color==COLOR_RED?RedJumpers(b):WhiteJumpers(b)) == 0)
	return evaluate(b, color, depth, alpha, beta) ;

    n = getmoves(b, color, child) ;
    if (n == 0) return -WIN+gdepth-depth ;

    for (i=0; i<n; i++) {
	val = -quiescence(child+i, 1-color, depth, alpha, beta) ;
	if (val > score)
	    score = val ;
    }
    return score ;
}


int
alphabeta(CheckerBoard *b, int color,
	int depth, 
	int alpha, int beta,
	CheckerBoard *best)
{
    CheckerBoard child[MAXMOVES] ;
    CheckerBoard nbest ;
    int i, j, n, value, flags = TRANSPOSITION_ALPHA;

    nodes_searched ++ ;

    if (repcheck && RepetitionCheck(b)) {
	if (0 >= beta) {
		return 0 ;
	}
	if (0 > alpha) {
		alpha = 0 ;
	}
    }

    if (depth == 0) {
	return quiescenceflag ? quiescence(b, color, depth, alpha, beta)
			      : evaluate(b, color, depth, alpha, beta) ;
    }


#if 1
    /* If this code isn't functioning right, then problem #201
     * doesn't work properly.  
     */
    Transposition *t = NULL ;
    if (usetransposition && (t = GetTranspositionTable(b->hash, depth)) != NULL) {
	switch (t->flags) {
	case TRANSPOSITION_EXACT:
	    if (t->value >= beta) {
		return t->value ;		/* beta cutoff */
	    }
	    if (t->value > alpha) {
		alpha = t->value ;		/* we found a good move */
		*best = t->best ;
	    }
	    /* if we fell through, then we didn't learn much. */
	    break ;
	case TRANSPOSITION_BETA:
	    /* If the transposition table is type BETA, then the 
	     * value was the result of a beta cutoff.  We know
 	     * that at least one child will have this score, so
	     * we can adjust alpha up for future searches.
 	     */
	    alpha = MAX2(t->value, alpha) ;
	    if (alpha >= beta) {
		return alpha ;	/* softfail */
	    }
	    break ;
	case TRANSPOSITION_ALPHA:
	    /* The value stored was the result of an "alpha" cutoff.
	     * IOW, all values searched here had a value which were 
	     * <= the score stored in the transposition table.   So,
	     * we could adjust beta down here, and possibly do the
	     * cutoff.
	     */
	    beta = MIN2(t->value, beta) ;
	    if (alpha >= beta) {
		return beta ;	/* softfail */
	    }
	    break ;
	}
    } 
#if 0
    else {
	if (DatabaseScore(b, color, &value)) {
	    return value ;
	}
    }
#endif
#endif

    n = getmoves(b, color, child) ;
    
    if (n == 0) {
	value = -WIN+gdepth-depth ;
	return value ;
    } 

    if (useetc && depth > 4) {
	/* enhanced transposition cutoff...
	 * if any of the moves would cause a beta cutoff, then don't 
	 * bother searching, just do the cutoff and return.
	 * It's important to remember that the child will have range 
	 * of -beta to -alpha.   
	 */
	Transposition *etc ;
	for (i=0; i<n; i++) {
	    etc = GetTranspositionTable(child[i].hash, depth-1) ;
	    if (etc) {
		int val = -etc->value ;
		switch (etc->flags) {
		case TRANSPOSITION_ALPHA:
		    if (val >= beta) {
			return val ;
		    }
		    break ;
		case TRANSPOSITION_EXACT:
		    return val ;
		}
		
	    }
	}
    }

#define USE_HISTORY_HEURISTIC
#ifdef USE_HISTORY_HEURISTIC
    if (usehistory) {
	double histscore[MAXMOVES] ;
	double bestscore = 0 ;
        CheckerBoard tmp ;
	double dtmp ;
        int bestidx ;

	/* first, fill the histscores array */
	for (i=0; i<n; i++)
	    histscore[i] = computehistscore(b, color, child+i) ;
	/* now, sort the children, using the scores... */
	
	for (i=0; i<n; i++) {
	    bestscore = histscore[i];
	    bestidx = i ;
	    for (j=i+1; j<n; j++) {
		if (histscore[j] > bestscore) {
		    bestidx = j ;
		    bestscore = histscore[j] ;
		}
	    }
	    if (bestidx != i) {
		tmp = child[i] ;
		child[i] = child[bestidx] ;
		child[bestidx] = tmp ;
		dtmp = histscore[i] ;
		histscore[i] = histscore[bestidx] ;
		histscore[bestidx] = dtmp ;
	    }
	}
    }
#endif /* USE_HISTORY_HEURISTIC */

#if 1
    if (t) {
	for (i=1; i<n; i++) {
	    if (t->best.hash == child[i].hash) {
		CheckerBoard tmp = child[0] ;
		child[0] = child[i] ;
		child[i] = tmp ;
		nodes_ordered ++ ;
		break ;
	    }
	}
    }
#endif

    /* We'd really like to know how often the first child is 
     * the best of the searched nodes,  So, let's keep track.
     */
 
    int bestscore = -INF ;
    int bestidx = -1; 	/* avoid the uninitialized variable warning */
 
    for (i = 0; i<n; i++) {

	RepetitionRemember(b) ;
	value = -alphabeta(child+i, 1-color, depth-1, 
			   -beta, -MAX(alpha, bestscore), &nbest);
	RepetitionForget() ;

	/* score keeping */
	if (value > bestscore) {
	    bestscore = value ;
	    bestidx = i ;
	}
	if (value >= beta) {
	    nodes_beta ++ ;
	    StoreTranspositionTable(b, color, depth, child+i, 
		TRANSPOSITION_BETA, value) ;
	    return value ;
	} 
	if (value > alpha) {
	    alpha = value ;
	    flags = TRANSPOSITION_EXACT ;
	}
    }
    /* score keeping */
    if (bestidx == 0)
	nodes_pvhit ++ ;
    else
	nodes_pvmiss ++ ;

    *best = child[bestidx] ;
    if (flags == TRANSPOSITION_EXACT)
	nodes_exact ++ ;
    else 
	nodes_alpha ++ ;
    StoreTranspositionTable(b, color, depth, child+bestidx, flags, bestscore) ;
    return bestscore ;
}

int
negascout(CheckerBoard *b, int color,
	int depth, 
	int alpha, int beta,
	CheckerBoard *best)
{
    int i, value ;
    int localalpha, localbeta ;
    int nmoves ;
    CheckerBoard nbest, child[MAXMOVES] ;
    int flags = TRANSPOSITION_ALPHA;

    if (depth == 0) {
	value = evaluate(b, color, depth, alpha, beta) ;
	return value ;
    }

    nmoves = getmoves(b, color, child) ;

    if (nmoves == 0) {
	value = -WIN+gdepth-depth ;
	return value ;
    }

    localbeta = alpha ;
    for (i = 0; i<nmoves; i++) {
	localalpha = -negascout(child+i, 1-color, depth-1, -localbeta, -alpha, &nbest);
	if (localalpha > alpha) {
		flags = TRANSPOSITION_EXACT ;
		*best = child[i] ;
		alpha = localalpha ;
	}
	if (alpha >= beta) {
	    StoreTranspositionTable(b, color, depth, child+i, TRANSPOSITION_BETA, alpha) ;
	    return alpha ;		/* beta cutoff */
	}
	if (alpha >= localbeta) {
	    /* we failed high, we need to research using the original window... */
	    alpha = -negascout(child+i, 1-color, depth-1, -beta, -alpha, &nbest);
	    if (alpha >= beta) {
		    StoreTranspositionTable(b, color, depth, child+i, TRANSPOSITION_BETA, alpha) ;
		    return alpha ;	/* another beta cutoff */
	    }
	}
	localbeta = alpha + 1 ;
    }
    StoreTranspositionTable(b, color, depth, best, flags, alpha) ;
    return alpha ;
}

int 
deepen(CheckerBoard *b, int color,
	int depth,
	CheckerBoard *best, int verbose, int analyze)
{
    int i ;
    /* We need to define eval as "volatile", so that it's value 
     * doesn't get accidently rolled back during a longjmp(), as 
     * is allowed by the ANSI C spec.
     */
    int eval = 0 ;	
    CheckerBoard nbest ;
    int mineval = -INF, maxeval = INF ;
    double stime, etime ;
    CheckerBoard child[MAXMOVES] ;

    /* if there is a forced move, there really isn't any reason 
     * that you should bother wasting time doing a search, you 
     * won't choose a different move, after all...
     */
    if (!analyze) {
	int n = getmoves(b, color, child) ;
	if (n == 1) {
	    *best = child[0] ;
	    return eval ; 		/* phony value, but we don't care. */
	}
    }

    if (sigsetjmp(abortsearch, 1) != 0) {
	signal(SIGINT, SIG_IGN) ;
	signal(SIGALRM, SIG_IGN) ;
	return eval;
    } else {
	signal(SIGINT, abortsearchhandler) ;
	if (timelimit) {
	    signal(SIGALRM, abortsearchhandler) ;
	    alarm(timelimit) ;
	}
    }

    InitSearchTotals() ;
    stime = gettimer() ;
    InitTranspositionTables() ;
    for (i=1; i<=depth; i+=2) {
	RepetitionReset() ;
	gdepth = i ;
	if (eval <= -WIN+MAXPLY || eval >= WIN-MAXPLY) break ;
	eval = alphabeta(b, color, i, mineval, maxeval, &nbest) ;
	if (eval <= mineval) {
	    if (verbose) printf("... researching after failing low (%d)\n", eval) ;
	    eval = alphabeta(b, color, i, -INF, eval, &nbest) ;
	} else if (eval >= maxeval) {
	    if (verbose) printf("... researching after failing high (%d)\n", eval) ;
	    eval = alphabeta(b, color, i, eval, INF, &nbest) ;
	}
	etime = gettimer() ;
	mineval = eval - 10 ;
	maxeval = eval + 10 ;
	if (verbose) {
	    /* print this in a tidy way */
	    char *cp = ComputeLine(b, color, i-1) ;
	    unsigned int newline = TRUE ;
	    printf("    %+4d : [%d] %.2fs", i, eval, etime-stime) ;
	    int cc = 0 ;
	    while (*cp) {
		if (newline) {
		    printf("\n         : ") ;
		    newline = FALSE ;
		    while (*cp && isspace(*cp))
			cp++ ;
		}
		if (*cp == 0) break ;
		putchar(*cp) ;
		cc ++ ;
		if (isspace(*cp++) && cc > 50) {
			newline = TRUE ;
			cc = 0 ;
		}
	    }
	    printf("\n") ;
	}
	*best = nbest ;
    }

	signal(SIGINT, SIG_IGN) ;
	signal(SIGALRM, SIG_IGN) ;

    return eval ;
}

/* traditional minimax
 * this isn't actually all that useful, because alpha-beta should search
 * fewer nodes and produce the same result.  There are situations however
 * where I suspect that isn't happening, which could indicate bugs with 
 * the cutoffs that are done in alpha-beta.  I put this in for later testing.
 */
int
minimax(CheckerBoard *b, int color, int depth, int maxdepth, CheckerBoard *best)
{
    int max = -INF ;
    CheckerBoard child[MAXMOVES], nbest[MAXPLY] ;
    int i, j, n, score ;

    if (depth == maxdepth) return evaluate(b, color, depth, -INF, INF) ;
    n = getmoves(b, color, child) ;
    if (n == 0) return -WIN + depth ;
    
    for (i=0; i<n; i++) {
	score = -minimax(child+i, 1-color, depth+1, maxdepth, nbest) ;
	if (score > max) {
	    max = score ;
	    best[depth] = child[i] ;
	    for (j=depth+1; j<maxdepth; j++)
		best[j] = nbest[j] ;
	}
    }
    return max ;
}

#ifdef RUNTESTHASH
int
main(int argc, char *argv[])
{
    CheckerBoard b, child[MAXMOVES] ;
    BitBoard m ;
    int i, j, n, color ;
    ub8 h1, h2, h3 ;
    int failures = 0 ;

    for (i=0; i<1000000; i++) {
	b.R = (ub4) lrand48() ;
	b.W = (ub4) lrand48() ;
	m = b.R & b.W ;
	b.R ^= m ;
	b.W ^= m ;
	b.K = lrand48() & (b.R|b.W) ;
	color = lrand48() % 2 ;
	b.hash = recomputeboardhash(&b, color) ;

	n = getmoves(&b, color, child) ;
	for (j=0; j<n; j++) {
	    if (child[j].hash != recomputeboardhash(child+j, 1-color)) {
#if 1
	/* too noisy */
	switch(color) {
	case COLOR_RED:
		if (RedJumpers(&b))
			printf("RED CAN JUMP\n") ;
		else if (RedMovers(&b)) 
			printf("RED CAN MOVE\n") ;
		break ;
	case COLOR_WHITE:
		if (WhiteJumpers(&b))
			printf("WHITE CAN JUMP\n") ;
		else if (WhiteMovers(&b)) 
			printf("WHITE CAN MOVE\n") ;
		break ;
	}
#endif

	    	h1 = child[j].hash ;
		h2 = recomputeboardhash(child+j, 1-color) ;
		h3 = h1 ^ h2 ;
		printf("%llx %llx %llx\n", h1, h2, h3) ;
		DumpBoard(&b, color, invertflag, stdout) ;
		DumpBoard(child+j, 1-color, invertflag, stdout) ;
		failures ++ ;
	    }
	}
    }
    if (failures == 0)
	    fprintf(stderr, "ALL TESTS PASSED\n") ;
    else 
	    fprintf(stderr, "%d failures in %d attempts\n", failures, i) ;
    return 0 ;
}
#endif /* RUNTESTHASH */

#ifdef RUNINTERACTIVE

#define MAX_ARGS	(20)

int 
split(char *cmd, char *cmdargv[])
{
    int c = 0;
    int skipblanks = TRUE ;

    while (*cmd) {
	if (skipblanks) {
	    if (isspace(*cmd)) 
		cmd++ ;
	    else {
		cmdargv[c++] = cmd++ ;
		skipblanks = FALSE ;
	    }
	} else {
	    if (isspace(*cmd)) {
		*cmd++ = '\0' ;
		skipblanks = TRUE ;
	    } else {
		cmd ++ ;
	    }
	}
    }
    return c ;
}

void
perftcount(CheckerBoard *board, int color, size_t *total, int depth)
{
    CheckerBoard moves[MAXMOVES] ;
    int i, n ;

    n = getmoves(board, color, moves) ;
    if (depth == 1) {
	*total += n ;
	return ;
    }
    color = 1 - color ;
    for (i=0; i<n; i++)
	perftcount(moves+i, color, total, depth-1) ;
}

void
perft(int depth)
{
    CheckerBoard board ;
    int color, winner ;
    size_t total = 0 ;
    char * name ;
    double t0, t1 ;

    name = getpuzzle(0, &board, &color, &winner) ;
    (void) name ;                                       /* we aren't going to use name... */
    t0 = gettimer() ;
    perftcount(&board, color, &total, depth) ;
    t1 = gettimer() ;
    printf("depth %d positions %lu (%.3lf seconds, %lu KN/s)\n", 
	depth, total, t1-t0, (size_t) ((double) total / (1000*(t1-t0)))) ;
}

/*----------------------------------------------------------------------*/
typedef struct t_booktree {
    CheckerBoard board ;
    int color ;
    int depth ;
    int score ;
    int hscore ;
    struct t_booktree *brother ;
    struct t_booktree *child ;
} BookTreeNode ;

BookTreeNode *
MakeBookTreeNode(CheckerBoard *b)
{
    BookTreeNode *t = (BookTreeNode *) malloc(sizeof(BookTreeNode)) ;
    t->board = *b ;
    t->brother = NULL ;
    t->child = NULL ;
    t->score = t->hscore = 0 ;
    return t ;
}

BookTreeNode *
BookTreeNodeSelect(BookTreeNode *node)
{
    BookTreeNode *c ;
    while (node->child != NULL) {
        int cnt, pick ;
	c = node->child ;
	for (cnt=0; c != NULL; cnt++) 
	    c = c->brother ;
	pick = lrand48() % cnt ;
	c = node->child ;
	for (cnt=0, c=node->child; cnt < pick; cnt++) 
	    c = c->brother ;
	node = c ;
    }
    return node ;
}

void
DumpBookTree(BookTreeNode *node, FILE *fp)
{
#if 1
    DumpSmallBoard(&(node->board), 
		node->depth&1?COLOR_WHITE:COLOR_RED, 
		fp) ;
#else
    fprintf(fp, "HASH: 0x%016" PRIx64 "\n", node->board.hash) ;
#endif

    if (node->child)
	DumpBookTree(node->child, fp) ;
    if (node->brother) 
	DumpBookTree(node->brother, fp) ;
}


void
insertbooktree(BookTreeNode *node, sqlite3 *db)
{
    char ibuf[4096] ;
    char *err ;

    sprintf(ibuf, "insert into opening (key1, key2, depth, color, FEN)"
	          " values(%u, %u, %d, %d, '%s')\n",
		  (uint32_t)(node->board.hash>>32), 
		  (uint32_t)(node->board.hash&0xffffffff), 
			  node->depth, node->color, FEN(&(node->board), node->color)) ;
    fputs(ibuf, stdout) ;

    sqlite3_exec(db, ibuf, NULL, NULL, &err) ;

    if (node->child)
	insertbooktree(node->child, db) ;
    if (node->brother)
	insertbooktree(node->brother, db) ;
}

void
bookgen()
{
    BookTreeNode *root, *node = NULL, *tail, *leaf ;
    int tmp1, tmp2, i, j, n ;
    CheckerBoard moves[MAXMOVES] ;
	
    /* create the start value */
    root = (BookTreeNode *) malloc(sizeof(BookTreeNode)) ;
    getpuzzle(0, &(root->board), &tmp1, &tmp2) ;
    root->depth = 0 ;
    root->color = COLOR_RED ;
    root->brother = NULL ;
    root->child = NULL ;

    srand48(1010) ;
    for (i=0; i<200; ) {
	leaf = BookTreeNodeSelect(root) ;
	n = getmoves(&(leaf->board), 
		     leaf->depth&1?COLOR_WHITE:COLOR_RED, 
		     moves) ;
	tail = NULL ;
	for (j=n-1; j>=0; j--) {
	    node = MakeBookTreeNode(moves+j) ;
	    node->brother = tail ;
	    node->child = NULL ;
	    node->depth = leaf->depth + 1 ;
	    node->color = (leaf->depth&1)?COLOR_WHITE:COLOR_RED ;
	    tail = node ;
	}
	leaf->child = node ;
	if ((++i % 100) == 0)
	    printf("... %d nodes expanded\r", i) ;
    }
    printf("\n") ;

#if 0
    printf("... dumping a bunch of nodes.\n") ;
    fp = fopen("book.dump", "w") ;
    DumpBookTree(root, fp) ;
    fclose(fp) ;
    printf("... done.\n") ;
#endif

    /* okay, now traverse the tree and store it into an 
     * sqlite3 database...
     */
    sqlite3 *db ;
    int rc = sqlite3_open("milhouse.db", &db) ;

    if (rc != SQLITE_OK) {
	/* an error occurred. */
	fprintf(stderr, "an error occurred!\n") ;
    } else {
	insertbooktree(root, db) ;
    }
    sqlite3_close(db) ;
}
/*----------------------------------------------------------------------*/


int 
main(int argc, char *argv[])
{
    double stime = 0., etime = 0. ;
    int i ;
    char *cmd ;
    int cmdargc ;
    char *cmdargv[20] ;
    char *name ;
    int depth ;
    int color, winner ;
    CheckerBoard board, move, moves[MAXMOVES] ;
    int n ;
    char prompt[80] ;
    char histname[80] ;
    char *progname ;

    if ((progname = strrchr(argv[0], '/')) != NULL)
	progname ++ ;
    else
	progname = argv[0] ;

    if (strcmp(progname, "milhouse-evaluate") == 0) {
        CheckerBoard tmpb, tmpmove ;
        int tmpcolor ;
	depth = atoi(argv[2]) ;
	timelimit = atoi(argv[3]) ;
	if (FENParse(argv[1], &tmpb, &tmpcolor)) {
	    /* deepen */
	    int score = 
	    printf("POSITION: %s\n", argv[1]) ;
	    printf("HASH: 0x%016" PRIX64 "\n", tmpb.hash) ;
	    score = deepen(&tmpb, tmpcolor, depth, &tmpmove, FALSE, FALSE) ;
	    printf("MOVE: %s\n", ComputeMove(&tmpb, &tmpmove, tmpcolor)) ;
	    printf("SCORE: %d\n", score) ;
	} else {
	    printf("couldn't parse FEN position, exiting.\n") ;
	    exit(-1) ;
	}
	exit(0) ;
    }

    printversion() ; 
    srand48(getpid()) ;
    InitTranspositionTables() ;
    sprintf(histname, "%s/.milhist", getenv("HOME")) ;
    fprintf(stderr, "history filename is %s\n", histname) ;

    using_history() ;		/* we are gonna use history */
    stifle_history(500) ;	/* but only remember the last 500 commands. */

    /* open the ~/.milhist file and read history... */
    if (read_history(histname) == 0) {
	fprintf(stderr, "reading history from %s\n", histname) ;
    } else {
	fprintf(stderr, "no previous history found.\n") ;
    }

    DatabaseInit(db) ;

    /* ignore ^C, we'll trap it later. */
    signal(SIGINT, SIG_IGN) ;

    n = 1 ;
    depth = 15 ;
    name = getpuzzle(0, &board, &color, &winner) ;

    for (;;) {
	strcpy(prompt, "") ;
	strcat(prompt, DatabaseResolve(&board, color)) ;
	strcat(prompt, "milhouse: ") ;
	cmd = readline(prompt) ;
	if (cmd == NULL) 
	    break ;
	if (*cmd)
	    add_history(cmd) ;
	cmdargc = split(cmd, cmdargv) ;
	if (cmdargc > 0) {
	    if (strcmp(cmdargv[0], "depth") == 0) {
		if (cmdargc == 2)
		    depth = MIN2(atoi(cmdargv[1]), MAXPLY) ;
		fprintf(stderr, "search depth is %d\n", depth) ;
	    } else if (strcmp(cmdargv[0], "eval") == 0) {
		printf("board evaluates to %d.\n", evaluate(&board, color, 0, -INF, INF)) ;
	    } else if (strcmp(cmdargv[0], "time") == 0) {
		timeflag = !timeflag ;
		printf("search routines will %sbe timed.\n", 
			timeflag ? "" : "not ") ;
	    } else if (strcmp(cmdargv[0], "puzzle") == 0) {
		name = getpuzzle(atoi(cmdargv[1]), &board, &color, &winner) ;
		n = 1 ;
		printf("... Loaded puzzle %d: %s.\n", atoi(cmdargv[1]), name) ;
		switch (color) {
		case COLOR_RED:
		    printf("... Red to move and ") ;
		    break ;
		case COLOR_WHITE:
		    printf("... White to move and ") ;
		    break ;
		}
		switch (winner) {
		case COLOR_RED:
		case COLOR_WHITE:
		    if (color == winner)
			printf("win.\n") ;
		    else
			printf("lose.\n") ;
		    break ;
		default:
		    printf("draw.\n") ;
		    break ;
		}
		DumpBoard(&board, color, invertflag, stdout) ;
	    } else if (strcmp(cmdargv[0], "makepuzzle") == 0) {
		printf("\t{{0x%08x, 0x%08x, 0x%08x}, %s, DRAW, \"comment\"},\n",
			board.R, board.W, board.K, 
			color == COLOR_RED ? "COLOR_RED" : "COLOR_WHITE") ;
	    } else if (strcmp(cmdargv[0], "catalog") == 0) {
		FILE *pager ;
		pager = popen("/bin/more", "w") ;
		CheckerBoard puzzle ;
		char *puzzle_name ;
		int puzzle_mover, puzzle_end ;
		regex_t re ;
		int trymatch = 0 ;

		if (cmdargc == 2) {
			/* we have a regular expression! */
		    if (regcomp(&re, cmdargv[1], REG_EXTENDED|REG_ICASE|REG_NOSUB) != 0)
			printf("couldn't compile the regular expression.") ;
		    trymatch = 1 ;
		}
	
		for (i=0; i<npuzzles(); i++) {
		    puzzle_name = getpuzzle(i, &puzzle, &puzzle_mover, &puzzle_end) ;
		    if (trymatch == 0 || regexec(&re, puzzle_name, (size_t) 0, NULL, 0) == 0)
			fprintf(pager, "%3d : %s\n", i, puzzle_name) ;
		}
		pclose(pager) ;
		if (trymatch) regfree(&re) ;
	    } else if (strcmp(cmdargv[0], "print") == 0) {
		printf("Puzzle %s loaded.\n", name) ;
		DumpBoard(&board, color, invertflag, stdout) ;
	    } else if (strcmp(cmdargv[0], "flip") == 0) {
		invertflag = !invertflag ;
		printf("... board display is %s\n", invertflag?"flipped":"normal") ;
	    } else if (strcmp(cmdargv[0], "fen") == 0) {
		CheckerBoard tmpb ;
		int tmpcolor ;
		if (FENParse(cmdargv[1], &tmpb, &tmpcolor)) {
		    board = tmpb ;
		    color = tmpcolor ;
		    DumpBoard(&board, color, invertflag, stdout) ;
		} else {
		    printf("couldn't parse FEN position.\n") ;
		}
	    } else if (strcmp(cmdargv[0], "ps") == 0) {
		PostScriptDump("board.ps", &board) ;
	    } else if (strcmp(cmdargv[0], "color") == 0) {
		if (cmdargc == 2) {
		    if (strcasecmp("red", cmdargv[1]) == 0)
			color = COLOR_RED ;
		    else if (strcasecmp("black", cmdargv[1]) == 0)
			color = COLOR_RED ;
		    else if (strcasecmp("white", cmdargv[1]) == 0)
			color = COLOR_WHITE ;
		}
		printf("Color is set to %s.\n", (color==COLOR_RED)?"red":"white") ;
	    } else if (strcmp(cmdargv[0], "timelimit") == 0) {
		if (cmdargc == 2) 
		    timelimit = atoi(cmdargv[1]) ;
		if (timelimit == 0)
		    printf("time limit is disabled.\n") ;
		else
		    printf("time limit is set to %d seconds.\n", timelimit) ;
	    } else if (strcmp(cmdargv[0], "minimax") == 0) {
		printf("final score = %d\n", minimax(&board, color, 0, depth, &move)) ;
		printf("\t%d. %s%s\n", n, color==COLOR_RED? "": "... ", ComputeMove(&board, &move, color)) ;
		DumpBoard(&move, 1-color, invertflag, stdout) ;
	    } else if (strcmp(cmdargv[0], "go") == 0 || strcmp(cmdargv[0], "id") == 0) {
		if (board.R == 0 || board.W == 0)
		    printf("game is over.\n") ;
		else {
		    if (timeflag) stime = gettimer() ;
		    printf("final score = %d\n", deepen(&board, color, depth, &move, TRUE, FALSE)) ;
		    if (timeflag) {
			etime = gettimer() ;
			printf("%.3f seconds elapsed.\n", etime-stime) ;
		    }
		    PrintSearchTotals(depth) ;
		    PrintTranspositionTableTotals() ;
		    if (strcmp(cmdargv[0], "go") == 0) {
			printf("... LOG: %s\n", ComputeMove(&board, &move, color)) ;
			printf("\t%d. %s%s\n", n, color==COLOR_RED? "": "... ", ComputeMove(&board, &move, color)) ;
			board = move ;
			color = 1 - color ;
			DumpBoard(&board, color, invertflag, stdout) ;
		    }
		}
	    } else if (strcmp(cmdargv[0], "negascout") == 0) {
		if (timeflag) stime = gettimer() ;
		gdepth = depth ;
		printf("final score = %d\n", negascout(&board, color, depth, 5000, INF, &move)) ;
		if (timeflag) {
		    etime = gettimer() ;
		    printf("%.3f seconds elapsed.\n", etime-stime) ;
		}
	    } else if (strcmp(cmdargv[0], "playout") == 0) {
		if (sigsetjmp(abortsearch, 1) != 0) {
		    signal(SIGINT, SIG_IGN) ;
		    printf("aborted playout.\n") ;
		    continue ;
		} else {
		    signal(SIGINT, abortsearchhandler) ;
		}
		n = 1 ;
		if (color == COLOR_WHITE)
		    printf("    %2d.              ", n) ;
	        while (n <= 10 && !isterminal(&board, color)) {
		    int s ;
		    s = deepen(&board, color, depth, &move, FALSE, FALSE) ;
		    switch (color) {
		    case COLOR_RED:
			printf("    %2d. %5s {%5d%s}", n, ComputeMove(&board, &move, color), 
				s, ChinookShortResolve(&board, color)) ;
			break ;
		    case COLOR_WHITE:
			printf(" %5s {%5d%s}\n", ComputeMove(&board, &move, color), 
				s, ChinookShortResolve(&board, color)) ;
			break ;
		    }
		    fflush(stdout) ;
		    board = move ;
		    color = 1 - color ;
		    if (color == COLOR_RED) n++ ;
		}
		if (color == COLOR_WHITE)
		    printf("\n") ;
		DumpBoard(&board, color, invertflag, stdout) ;
		signal(SIGINT, SIG_IGN) ;
	    } else if (strcmp(cmdargv[0], "annotate") == 0 ||
		       strcmp(cmdargv[0], "analyze") == 0) {
		if (sigsetjmp(abortsearch, 1) != 0) {
		    signal(SIGINT, SIG_IGN) ;
		    printf("analysis aborted.\n") ;
		    continue ;
		} else {
		    signal(SIGINT, abortsearchhandler) ;
		}
		n = 1 ;
		printf("analyzing board position...\n") ;
		n = getmoves(&board, color, moves) ;
		for (i=0; i<n; i++) {
		    int score = -deepen(moves+i, 1-color, depth, &move, FALSE, TRUE) ;
		    printf("\t%+6d : %s %s\n",
			score,
			ComputeMove(&board, moves+i, color),
			ComputeLine(moves+i, 1-color, depth)) ;
		}
		signal(SIGINT, SIG_IGN) ;
	    } else if (strcmp(cmdargv[0], "flip") == 0) {
		color = 1 - color ;
		printf("%s moves next.\n", color == COLOR_RED?"red":"white") ;
	    } else if (strcmp(cmdargv[0], "save") == 0) {
		FILE *fp ;
		if (cmdargc != 2) {
		    printf("usage: save filename\n") ;
		} else {
		    if ((fp = fopen(cmdargv[1], "wb")) == NULL) {
			perror(cmdargv[1]) ;
		    } else {
			fwrite(&color, sizeof(color), 1, fp) ;
			fwrite(&board, sizeof(board), 1, fp) ;
			printf("board saved to %s\n", cmdargv[1]) ;
			fclose(fp) ;
		    }
		}
	    } else if (strcmp(cmdargv[0], "restore") == 0) {
		FILE *fp ;
		if (cmdargc != 2) {
		    printf("usage: restore filename\n") ;
		    break ;
		} else {
		    if ((fp = fopen(cmdargv[1], "rb")) == NULL) {
			perror(cmdargv[1]) ;
		    } else {
                        int rc ;
			rc = fread(&color, sizeof(color), 1, fp) ;
                        (void) rc ;
			rc = fread(&board, sizeof(board), 1, fp) ;
                        (void) rc ;
			printf("board restore from %s\n", cmdargv[1]) ;
			DumpBoard(&board, color, invertflag, stdout) ;
			fclose(fp) ;
		    }
		}
	    } else if (strcmp(cmdargv[0], "three") == 0) {
		name = getrandomopening(&board) ;
		color = COLOR_WHITE ;
		DumpBoard(&board, color, invertflag, stdout) ;
		printf("... opening %s\n", name) ;
	    } else if (strcmp(cmdargv[0], "selfplay") == 0) {
		int s ;
		name = getrandomopening(&board) ;
		color = COLOR_WHITE ;
		printf("... Opening %s\n", name) ;
		n = 2 ;
		printf("    %2d. %5s        ", n, "...") ;
		while (!isterminal(&board, color) && (n <= 100)) {
		    InitTranspositionTables() ;
		    s = deepen(&board, color, depth-2*(color == COLOR_RED), &move, FALSE, FALSE) ;
		    switch (color) {
		    case COLOR_RED:
			printf("    %2d. %5s {%5d}", n, ComputeMove(&board, &move, color), s) ;
			break ;
		    case COLOR_WHITE:
			printf(" %5s {%5d}\n", ComputeMove(&board, &move, color), s) ;
			break ;
		    }
		    fflush(stdout) ;
		    board = move ;
		    color = 1 - color ;
		    if (color == COLOR_RED)
			n++ ;
		}
		printf("\n") ;
		DumpBoard(&board, color, invertflag, stdout) ;
	    } else if (strcmp(cmdargv[0], "killflag") == 0) {
		killflag = !killflag ;
		printf("killer heuristic is %s.\n", killflag?"enabled":"disabled") ;
	    } else if (strcmp(cmdargv[0], "history") == 0) {
		usehistory = !usehistory ;
		printf("history heuristic is %s.\n", usehistory?"enabled":"disabled") ;
	    } else if (strcmp(cmdargv[0], "quiescence") == 0 || strcmp(cmdargv[0], "q") == 0) {
		quiescenceflag = !quiescenceflag ;
		printf("quiescence is %s.\n", quiescenceflag?"enabled":"disabled") ;
	    } else if (strcmp(cmdargv[0], "chinook") == 0) {
		usechinook = !usechinook ;
		printf("chinook is %s.\n", usechinook?"enabled":"disabled") ;
	    } else if (strcmp(cmdargv[0], "etc") == 0) {
		useetc = !useetc ;
		printf("enhanced transposition cutoffs are %s.\n", useetc?"enabled":"disabled") ;
	    } else if (strcmp(cmdargv[0], "transposition") == 0 || strcmp(cmdargv[0], "t") == 0) {
		usetransposition = !usetransposition ;
		printf("transposition lookups are %s.\n", usetransposition?"enabled":"disabled") ;
	    } else if (strcmp(cmdargv[0], "evaluate") == 0 || strcmp(cmdargv[0], "e") == 0) {
		printf("evaluation function score = %d\n", 
			quiescenceflag ? quiescence(&board, color, depth, -INF, INF) 
				       : evaluate(&board, color, depth, -INF, INF)) ; 
		if (DatabaseValid(db, &board))
		    printf("database value = %d\n", DatabaseValue(&board, color)) ;
		else
		    printf("couldn't lookup the database value.\n") ;
	    } else if (strcmp(cmdargv[0], "database") == 0) {
		/* select either "chinook", "cake", or "none" */
		if (cmdargc == 1) 
		    printf("database is currently set to %s.\n", DatabaseName(db)) ;
		else if (cmdargc != 2)
		    printf("usage: database chinook|cake|none\n") ;
		else {
		    if (strcmp(cmdargv[1], "none") == 0) {
			DatabaseClose(db) ;
			db = & NoneInterface ;
			DatabaseInit(db) ;
		    } else if (strcmp(cmdargv[1], "chinook") == 0) {
			DatabaseClose(db) ;
		 	db = & ChinookInterface ;
			DatabaseInit(db) ;
		    } else if (strcmp(cmdargv[1], "cake") == 0) {
			DatabaseClose(db) ;
			db = & CakeInterface ;
			DatabaseInit(db) ;
		    } else {
			printf("usage: database chinook|cake|none\n") ;
			printf("       database %s is unknown.\n", cmdargv[1]) ;
		    }
		}
	    } else if (strcmp(cmdargv[0], "captures") == 0) {
		if (anycaptures(&board, color))
		    printf("There are captures for the moving side.\n") ;
		if (RedJumpers(&board) > 0)
		    printf("There are captures for the red side.\n") ;
		if (WhiteJumpers(&board) > 0)
		    printf("There are captures for the white side.\n") ;
	    } else if (strcmp(cmdargv[0], "db") == 0) {
		/* lookup the current position in current database */
		if (!DatabaseValid(db, &board)) {
		    printf("position isn't valid for the database.\n") ;
		} else {
		    switch (DatabaseValue(&board, color)) {
		    case DB_UNKNOWN:
			printf("position isn't in the database.\n") ;
			break ;
		    case DB_WIN:
			printf("position is a win for %s.\n", COLOR(color)) ;
			break ;
		    case DB_LOSS:
			printf("position is a loss for %s.\n", COLOR(color)) ;
			break ;
		    case DB_DRAW:
			printf("position is a draw for %s.\n", COLOR(color)) ;
			break ;
		    }
		}
	    } else if (strcmp(cmdargv[0], "gem") == 0) {
		int puzzle ;
		for (puzzle=214; puzzle <= 375; puzzle++) {
		    name = getpuzzle(puzzle, &board, &color, &winner) ;
		    switch (DatabaseValue(&board, color)) {
		    case DB_WIN:
			printf("%d : %s is a win for %s\n", 
				puzzle, name, color == COLOR_RED?"red":"white") ;
			break ;
		    case DB_LOSS:
			printf("%d : %s is a loss for %s\n", 
				puzzle, name, color == COLOR_RED?"red":"white") ;
			break ;
		    case DB_DRAW:
			printf("%d : %s is a draw for %s\n", 
				puzzle, name, color == COLOR_RED?"red":"white") ;
			break ;
		    }
		}
	    } else if (strcmp(cmdargv[0], "gould") == 0) {
		int puzzle ;
		for (puzzle=885; puzzle <= 1977; puzzle++) {
		    name = getpuzzle(puzzle, &board, &color, &winner) ;
		    switch (DatabaseValue(&board, color)) {
		    case DB_UNKNOWN:
			break ;
		    case DB_WIN:
			switch(color) {
			case COLOR_RED:
			    if (winner != COLOR_RED) {
				printf("%d : %s is actually a win for red\n", 
					puzzle, name) ;
			    }
			    break ;
			case COLOR_WHITE:
			    if (winner != COLOR_WHITE) {
				printf("%d : %s is actually a win for white\n", 
					puzzle, name) ;
			    }
			    break ;
			}
			break ;
		    case DB_LOSS:
			switch(color) {
			case COLOR_RED:
			    if (winner != COLOR_WHITE) {
				printf("%d : %s is actually a loss for red\n", 
					puzzle, name) ;
			    }
			    break ;
			case COLOR_WHITE:
			    if (winner != COLOR_RED) {
				printf("%d : %s is actually a loss for white\n", 
					puzzle, name) ;
			    }
			    break ;
			}
			break ;
		    case DB_DRAW:
			if (winner != DB_DRAW) {
			    printf("%d : %s is actually a draw\n", puzzle, name) ;
			}
			break ;
		    }
		}
	    } else if (strcmp(cmdargv[0], "perft") == 0) {
		int d ;
		printf("running perft performance/accuracy test.\n") ;
		for (d = 1; d < 13; d++)
			perft(d) ;
	    } else if (strcmp(cmdargv[0], "r") == 0) {
		repcheck = !repcheck ;
		printf("draw by repetition checking is %s\n",
			repcheck ? "enabled" : "disabled") ;
	    } else if (strcmp(cmdargv[0], "m") == 0) {
		char *movenumbuf ;
		int movenum ;
		n = getmoves(&board, color, moves) ;
		printf("%s moves:", color == COLOR_RED ? "red" : "white" ) ;
		for (i=0; i<n; i++)
		    printf(" (%d) %s", i+1, ComputeMove(&board, moves+i, color)) ;
		printf("\n") ;
		for (;;) {
		    movenumbuf = readline("which move? ") ;
		    if (strcmp("", movenumbuf) == 0) {
			/* empty string, just exit */
			free((void *) movenumbuf) ;
			break ;
		    }
		    movenum = atoi(movenumbuf) ;
		    if (movenum >= 1 && movenum <= n) {
			printf("... LOG: %s\n", ComputeMove(&board, moves+movenum-1, color)) ;
			board = moves[movenum-1] ;
			color = 1 - color ;
			break;
		    } else {
			printf("%s wasn't a valid move number.", movenumbuf) ;
		    }
		    free((void *) movenumbuf) ;
		}
	    } else if (strcmp(cmdargv[0], "bookgen") == 0) {
		/* try to generate a book, maybe. */
		bookgen() ;
	    } else {
		fprintf(stderr, "unknown command: %s\n", cmdargv[0]) ;
	    } 
	}
	/* free up storage */
        free((void *) cmd) ;
    }

    if (write_history(histname) == 0) {
	fprintf(stderr, "Wrote history to %s\n", histname) ;
    } else {
	fprintf(stderr, "ERROR: couldn't write history to %s\n", histname) ;
    }
    return 0 ;
}
#endif /* RUNINTERACTIVE */

#ifdef GENTHREE
void
genthree(CheckerBoard *b, int color, char *s, int depth)
{
    CheckerBoard move[MAXMOVES] ;
    char buf[1024] ;
    int i, n ;

    if (depth == 0) {
	/* dump it */
	printf("{{%0#10" PRIx32", %0#10" PRIx32", %#" PRIx32", %0#18" PRIx64"}, \"%s\"},\n",
		b->R, b->W, b->K, b->hash, s) ;
    } else {
	n = getmoves(b, color, move) ;
	for (i=0; i<n; i++) {
	   strcpy(buf, s) ;
	   if (depth != 3)
	       strcat(buf, " ") ;
	   strcat(buf, ComputeMove(b, move+i, color)) ;
	   genthree(move+i, 1-color, buf, depth-1) ;
	}
    }
}

main()
{
    CheckerBoard board ;
    int color, winner ;

    getpuzzle(0, &board, &color, &winner) ;
    genthree(&board, color, "", 3) ;
    verifythreemoves() ;
    return 0 ;

#endif
