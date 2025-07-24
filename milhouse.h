
/* I probably should shift to using C99 and include
 * stdbool.h to use booleans, but this code is old
 * and probably wouldn't significantly add to either
 * legibility or maintainability.
 */

#ifndef FALSE   
#define FALSE   (0)
#endif /* FALSE */

#ifndef TRUE
#define TRUE    (1)
#endif /* TRUE */

#define COLOR_RED	(0)
#define COLOR_WHITE	(1)

#define 	MAXMOVES	(32)	
#define 	MAXPLY		(100)

typedef unsigned int BitBoard ;

typedef struct t_checkerboard {
	BitBoard R, W, K ;	
        uint64_t hash ;
} CheckerBoard ;

#define TRANSPOSITION_EXACT	(0)
#define TRANSPOSITION_ALPHA	(1)
#define TRANSPOSITION_BETA	(2)

typedef struct t_transposition {
	uint64_t hash ;
	int depth ;
	int flags ;
	int value ;
	CheckerBoard best ;
} Transposition ;

typedef int64_t Counter ;

#define INF	(20000)
#define WIN	(10000)

/* datatypes necessary for tdleaf learning... */

#define NFEATURES	(10)
#define NPHASES		(4)

typedef float Features[NFEATURES] ;
typedef float EvaluationWeights[NPHASES][NFEATURES] ;

/* puzzle.c */
int npuzzles(void);
char *getpuzzle(int idx, CheckerBoard *b, int *m, int *e);

/* plaidmove.c */
int generateredmoves(CheckerBoard *b, CheckerBoard *m, BitBoard v);
int generatewhitemoves(CheckerBoard *b, CheckerBoard *m, BitBoard v);
int generateredcaptures(CheckerBoard *b, CheckerBoard *m, BitBoard v);
int generatewhitecaptures(CheckerBoard *b, CheckerBoard *m, BitBoard v);
uint64_t recomputeboardhash(CheckerBoard *b, int color);

#define MAX2(a,b)	((a)>(b)?(a):(b))
#define MIN2(a,b)	((a)<(b)?(a):(b))
#define ABS(x)		((x)<0?(-x):(x))
#define BIT(x)		(1<<(x))

/* threemove.c */
void verifythreemoves(void);
char *getrandomopening(CheckerBoard *b);

/* postscript.c */
void PostScriptDump(char *fname, CheckerBoard *b);

/* these are the raw chinook DBLookup codes */

#define DB_UNKNOWN 0
#define DB_WIN 1
#define DB_LOSS 2
#define DB_DRAW 3
#define DB_NOT_LOOKED_UP 4

/* Make the two calls compatible... */
#define CHINOOK_TIE     DB_DRAW
#define CHINOOK_WIN     DB_WIN
#define CHINOOK_LOSS    DB_LOSS
#define CHINOOK_UNKNOWN DB_UNKNOWN

/* these are useful for puzzle */
#define RWINS		COLOR_RED
#define WWINS		COLOR_WHITE
#define DRAW		DB_DRAW

#define COLOR(color)	((color==COLOR_RED)?"red":"white") 
