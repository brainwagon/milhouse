%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char *yytext ;
extern int yylex(void) ;
extern int yyerror(char *) ;

int ngames = 0 ;
int jumps[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ;
int wins = 0, losses = 0, draws = 0 ;
int moves = 0 ;

%}

%union {
	int i ;
}

%type <i> capture

%token NUM LBRACK RBRACK HEADERTAG HEADERSTR DOT DASH
%token RESULT ECKS

%%
file: 	gamelist {
	    printf("%d single jumps.\n", jumps[1]) ;
	    printf("%d double jumps.\n", jumps[2]) ;
	    printf("%d triple jumps.\n", jumps[3]) ;
	    printf("%d quadruple jumps.\n", jumps[4]) ;
	    printf("%d wins.\n", wins) ;
	    printf("%d losses.\n", losses) ;
	    printf("%d draws.\n", draws) ;
	    printf("%d total moves.\n", moves) ;
	} ;
gamelist: gamelist game {
		ngames ++ ;
	} 
	| ;

game: headerlist turns result ;

headerlist: headerlist header
	| ;

header: LBRACK HEADERTAG HEADERSTR RBRACK ;

result: RESULT {
	if (strcmp(yytext, "1-0") == 0)
		wins ++ ;
	else if (strcmp(yytext, "0-1") == 0)
		losses ++ ;
	else if (strcmp(yytext, "1/2-1/2") == 0)
		draws ++ ;
	} 
	| {
		fprintf(stderr, "malformed game missing result\n");
	  } ;

turns: turnlist endofturnlist ;

turnlist: turnlist turn | ;

endofturnlist: halfturn | ;

turn: movenumber ply ply {
		moves += 2 ;
	} ;

halfturn: movenumber ply {
		moves ++ ;
	} ;

movenumber: NUM DOT ;

ply: move | capture {
	jumps[$1]++ ;
	}

move: NUM DASH NUM ;

capture: capture ECKS NUM  {
		$$ = $1 + 1 ;
	}
	| NUM {
		$$ = 0 ;
	} ;

%%
int
yyerror(char *str)
{
    extern int yylinecount ;
    fprintf(stderr, "syntax error at line %d: %s\n", yylinecount, str) ;
    exit(-1) ;
    return 0 ;
}

int
main(int argc, char *argv[])
{
    extern FILE *yyin ;
    extern int yyparse(void) ;
    FILE *fp = NULL ;

    if (argc == 2) {
	fp = fopen(argv[1], "r") ;
	if (fp == NULL) {
	    perror(argv[1]) ;
	    exit(1) ;
	} else {
	    yyin = fp ;
	}
    } else {
	yyin = stdin ;
    }
    if (yyparse() == 1) {
        /* we got an error */
        fprintf(stderr, "invalid pdn input file.\n") ;
        exit(1);
    }
    fprintf(stderr, "%d games read.\n", ngames) ;
    if (fp)
	fclose(fp) ;
    return 0 ;
}
