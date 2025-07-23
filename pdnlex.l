%{
#include <stdio.h>
#include "y.tab.h"
int yylinecount = 0;
%}

%%
[ \t]			;	/* ignore white space */
\n			yylinecount++ ;
\.			return DOT ;
\-			return DASH ;
x			return ECKS ;
[0-9]+			return NUM ;
1\-0			return RESULT ;		/* win */
0\-1			return RESULT ;		/* loss */
1\/2\-1\/2		return RESULT ;		/* draw */
\[			return LBRACK ;
\]			return RBRACK ;
[A-Za-z]+		return HEADERTAG ;
\"[^"]*\"		return HEADERSTR ;
.			return yytext[0] ;
\{[^}]*\}		;
%%

int 
yywrap(void)
{
    return 1 ;
}
