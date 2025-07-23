#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "milhouse.h"

char *postscript_hdr =
	"%%!PS\n"
	"\n"
	"<< /PageSize [450 450] >> setpagedevice\n"
	"\n"
	"25 25 translate\n"
	"(draughts.ttf) findfont 50 scalefont setfont\n" ;

char *postscript_ftr =
	"0 1 7 {\n"
	"   50 mul 0 exch moveto\n"
	"   show\n"
	"} for\n"
	"\n"
	"/Helvetica-Bold findfont 8 scalefont setfont\n"
	"\n"
	"/S { dup stringwidth 8 sub exch neg exch rmoveto -2 -2 rmoveto show } def\n"
	"\n"
	" 50  50 moveto ( 4) S\n"
	"150  50 moveto ( 3) S\n"
	"250  50 moveto ( 2) S\n"
	"350  50 moveto ( 1) S\n"
	"100 100 moveto ( 8) S\n"
	"200 100 moveto ( 7) S\n"
	"300 100 moveto ( 6) S\n"
	"400 100 moveto ( 5) S\n"
	" 50 150 moveto (12) S\n"
	"150 150 moveto (11) S\n"
	"250 150 moveto (10) S\n"
	"350 150 moveto ( 9) S\n"
	"100 200 moveto (16) S\n"
	"200 200 moveto (15) S\n"
	"300 200 moveto (14) S\n"
	"400 200 moveto (13) S\n"
	" 50 250 moveto (20) S\n"
	"150 250 moveto (19) S\n"
	"250 250 moveto (18) S\n"
	"350 250 moveto (17) S\n"
	"100 300 moveto (24) S\n"
	"200 300 moveto (23) S\n"
	"300 300 moveto (22) S\n"
	"400 300 moveto (21) S\n"
	" 50 350 moveto (28) S\n"
	"150 350 moveto (27) S\n"
	"250 350 moveto (26) S\n"
	"350 350 moveto (25) S\n"
	"100 400 moveto (32) S\n"
	"200 400 moveto (31) S\n"
	"300 400 moveto (30) S\n"
	"400 400 moveto (29) S\n"
	"\n"
	"newpath 0 0 400 400 rectstroke\n"
	"newpath -10 -10 420 420 rectstroke\n"
	"\n"
	"showpage\n"
	"quit\n" ;

void
PostScriptDump(char *fname, CheckerBoard *b)
{
    FILE *fp = fopen("board.ps", "w") ;
    int row, col, m, idx ;

    if (fp == NULL) {
	perror(fname) ;
	return ;
    }

    fwrite(postscript_hdr, 1, strlen(postscript_hdr), fp) ;

    for (row=8; row>0; ) {
	row -- ;
	fprintf(fp, "(") ;
	for (col=8; col>0; ) {
	    col-- ;
	    idx = row * 8 + col ;
	    if ((row + col) & 1) {
		m = 1<<(idx / 2) ;
		if (b->R & m)
		    fputc(b->K & m ? 'a' : 'e', fp) ;
		else if (b->W & m)
		    fputc(b->K & m ? 'c' : 'f', fp) ;
		else
		    fputc('i', fp) ;
	    } else {
		fputc(' ', fp) ;
	    }
	}
	fprintf(fp, ")") ;
    }
    fwrite(postscript_ftr, 1, strlen(postscript_ftr), fp) ;
    fclose(fp) ;

    /* if you have ghostscript, you can convert it directly to a png file. */
    {
	char cmd[1024] ;
        int rc ;

	sprintf(cmd, "gs -dBATCH -q -dNOPAUSE -sDEVICE=ppmraw -r300 -sOutputFile=board.ppm board.ps") ;
	printf("executing \"%s\"...", cmd) ;
	rc = system(cmd) ;
        printf("rc=%d\n", rc) ;
	sprintf(cmd, "pnmscale -width 1024 board.ppm | pnmtopng > board.png") ;
	printf("executing \"%s\"...", cmd) ;
	rc = system(cmd) ;
        printf("rc=%d\n", rc) ;
    }
}
