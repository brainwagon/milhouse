/*
 * $Id: acf-openings.c,v 1.1 2009/12/23 01:05:29 markv Exp $
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <string.h>
#include <regex.h>

#include "milhouse.h"
#include "acf-openings.h"

typedef struct t_opening {
    char *name ;
    char *moves ;
    char *altname ;
    int flags ;
} Opening ;

Opening opening[] = {
	{"ACF 001", "09-13 21-17 05-09", "", DECK_NORMAL},
	{"ACF 002", "09-13 21-17 06-09", "", DECK_NORMAL},
	{"ACF 003", "09-13 21-17 10-14", "", DECK_LOSING},
	{"ACF 004", "09-13 22-17 13-22", "", DECK_NORMAL},
	{"ACF 005", "09-13 22-18 06-09", "", DECK_NORMAL},
	{"ACF 006", "09-13 22-18 10-14", "", DECK_NEW},
	{"ACF 007", "09-13 22-18 10-15", "", DECK_NORMAL},
	{"ACF 008", "09-13 22-18 11-15", "", DECK_NORMAL},
	{"ACF 009", "09-13 22-18 11-16", "", DECK_NEW},
	{"ACF 010", "09-13 22-18 12-16", "", DECK_NORMAL},
	{"ACF 011", "09-13 23-18 05-09", "", DECK_NORMAL},
	{"ACF 012", "09-13 23-18 06-09", "", DECK_NORMAL},
	{"ACF 013", "09-13 23-18 10-14", "", DECK_LOSING},
	{"ACF 014", "09-13 23-18 10-15", "", DECK_NORMAL},
	{"ACF 015", "09-13 23-18 11-15", "", DECK_NORMAL},
	{"ACF 016", "09-13 23-18 11-16", "", DECK_NEW},
	{"ACF 017", "09-13 23-18 12-16", "", DECK_NORMAL},
	{"ACF 018", "09-13 23-19 05-09", "", DECK_NORMAL},
	{"ACF 019", "09-13 23-19 06-09", "", DECK_NORMAL},
	{"ACF 020", "09-13 23-19 10-14", "", DECK_NORMAL},
	{"ACF 021", "09-13 23-19 10-15", "", DECK_NEW},
	{"ACF 022", "09-13 23-19 11-16", "", DECK_NORMAL},
	{"ACF 023", "09-13 24-19 05-09", "", DECK_NORMAL},
	{"ACF 024", "09-13 24-19 06-09", "", DECK_NORMAL},
	{"ACF 025", "09-13 24-19 10-14", "", DECK_NORMAL},
	{"ACF 026", "09-13 24-19 10-15", "", DECK_LOSING},
	{"ACF 027", "09-13 24-19 11-15", "", DECK_NORMAL},
	{"ACF 028", "09-13 24-19 11-16", "", DECK_NORMAL},
	{"ACF 029", "09-13 24-20 05-09", "", DECK_NORMAL},
	{"ACF 030", "09-13 24-20 06-09", "", DECK_NORMAL},
	{"ACF 031", "09-13 24-20 10-14", "", DECK_NORMAL},
	{"ACF 032", "09-13 24-20 10-15", "", DECK_NORMAL},
	{"ACF 033", "09-13 24-20 11-15", "", DECK_NORMAL},
	{"ACF 034", "09-13 24-20 11-16", "", DECK_NEW},
	{"ACF 035", "09-13 24-20 12-16", "", DECK_LOSING},
	{"ACF 036", "09-14 22-17 05-09", "", DECK_NORMAL},
	{"ACF 037", "09-14 22-17 06-09", "", DECK_NORMAL},
	{"ACF 038", "09-14 22-17 11-15", "", DECK_NORMAL},
	{"ACF 039", "09-14 22-17 11-16", "", DECK_NORMAL},
	{"ACF 040", "09-14 22-18 05-09", "", DECK_NORMAL},
	{"ACF 041", "09-14 22-18 10-15", "", DECK_NORMAL},
	{"ACF 042", "09-14 22-18 11-15", "", DECK_NORMAL},
	{"ACF 043", "09-14 22-18 11-16", "", DECK_NORMAL},
	{"ACF 044", "09-14 22-18 12-16", "", DECK_LOSING},
	{"ACF 045", "09-14 22-18 14-17", "", DECK_LOSING},
	{"ACF 046", "09-14 23-18 14-23", "", DECK_NORMAL},
	{"ACF 047", "09-14 23-19 05-09", "", DECK_NORMAL},
	{"ACF 048", "09-14 23-19 10-15", "", DECK_LOSING},
	{"ACF 049", "09-14 23-19 11-16", "", DECK_NORMAL},
	{"ACF 050", "09-14 23-19 14-18", "", DECK_NORMAL},
	{"ACF 051", "09-14 24-19 05-09", "", DECK_NORMAL},
	{"ACF 052", "09-14 24-19 10-15", "", DECK_LOSING},
	{"ACF 053", "09-14 24-19 11-15", "", DECK_NORMAL},
	{"ACF 054", "09-14 24-19 11-16", "", DECK_NORMAL},
	{"ACF 055", "09-14 24-20 05-09", "", DECK_NORMAL},
	{"ACF 056", "09-14 24-20 10-15", "", DECK_NORMAL},
	{"ACF 057", "09-14 24-20 11-15", "", DECK_NORMAL},
	{"ACF 058", "09-14 24-20 11-16", "", DECK_NORMAL},
	{"ACF 059", "10-14 22-17 07-10", "", DECK_NORMAL},
	{"ACF 060", "10-14 22-17 09-13", "", DECK_NEW},
	{"ACF 061", "10-14 22-17 11-15", "", DECK_NEW},
	{"ACF 062", "10-14 22-17 11-16", "", DECK_NEW},
	{"ACF 063", "10-14 22-17 14-18", "", DECK_NORMAL},
	{"ACF 064", "10-14 22-18 06-10", "", DECK_NORMAL},
	{"ACF 065", "10-14 22-18 07-10", "", DECK_NORMAL},
	{"ACF 066", "10-14 22-18 11-15", "", DECK_NORMAL},
	{"ACF 067", "10-14 22-18 11-16", "", DECK_NORMAL},
	{"ACF 068", "10-14 22-18 12-16", "", DECK_NORMAL},
	{"ACF 069", "10-14 23-18 14-23", "", DECK_NORMAL},
	{"ACF 070", "10-14 23-19 06-10", "", DECK_NORMAL},
	{"ACF 071", "10-14 23-19 07-10", "", DECK_NORMAL},
	{"ACF 072", "10-14 23-19 11-15", "", DECK_NORMAL},
	{"ACF 073", "10-14 23-19 11-16", "", DECK_NORMAL},
	{"ACF 074", "10-14 23-19 14-18", "", DECK_NORMAL},
	{"ACF 075", "10-14 24-19 06-10", "", DECK_NORMAL},
	{"ACF 076", "10-14 24-19 07-10", "", DECK_NORMAL},
	{"ACF 077", "10-14 24-19 11-15", "", DECK_LOSING},
	{"ACF 078", "10-14 24-19 11-16", "", DECK_NORMAL},
	{"ACF 079", "10-14 24-19 14-18", "", DECK_NORMAL},
	{"ACF 080", "10-14 24-20 06-10", "", DECK_NORMAL},
	{"ACF 081", "10-14 24-20 07-10", "", DECK_NORMAL},
	{"ACF 082", "10-14 24-20 11-15", "", DECK_NORMAL},
	{"ACF 083", "10-14 24-20 11-16", "", DECK_NORMAL},
	{"ACF 084", "10-14 24-20 14-18", "", DECK_NORMAL},
	{"ACF 085", "10-15 21-17 06-10", "", DECK_NORMAL},
	{"ACF 086", "10-15 21-17 07-10", "", DECK_NORMAL},
	{"ACF 087", "10-15 21-17 09-13", "", DECK_NORMAL},
	{"ACF 088", "10-15 21-17 09-14", "", DECK_LOSING},
	{"ACF 089", "10-15 21-17 11-16", "", DECK_NORMAL},
	{"ACF 090", "10-15 21-17 15-18", "", DECK_NORMAL},
	{"ACF 091", "10-15 22-17 06-10", "", DECK_NORMAL},
	{"ACF 092", "10-15 22-17 07-10", "", DECK_NORMAL},
	{"ACF 093", "10-15 22-17 09-13", "", DECK_NORMAL},
	{"ACF 094", "10-15 22-17 09-14", "", DECK_LOSING},
	{"ACF 095", "10-15 22-17 11-16", "", DECK_NORMAL},
	{"ACF 096", "10-15 22-17 15-19", "", DECK_NORMAL},
	{"ACF 097", "10-15 22-18 15-22", "", DECK_NORMAL},
	{"ACF 098", "10-15 23-18 06-10", "", DECK_NORMAL},
	{"ACF 099", "10-15 23-18 07-10", "", DECK_NORMAL},
	{"ACF 100", "10-15 23-18 09-14", "", DECK_NORMAL},
	{"ACF 101", "10-15 23-18 11-16", "", DECK_NORMAL},
	{"ACF 102", "10-15 23-18 12-16", "", DECK_NORMAL},
	{"ACF 103", "10-15 23-19 06-10", "", DECK_NORMAL},
	{"ACF 104", "10-15 23-19 07-10", "", DECK_NORMAL},
	{"ACF 105", "10-15 23-19 11-16", "", DECK_NEW},
	{"ACF 106", "10-15 24-19 15-24", "", DECK_NORMAL},
	{"ACF 107", "10-15 24-20 06-10", "", DECK_NORMAL},
	{"ACF 108", "10-15 24-20 07-10", "", DECK_NORMAL},
	{"ACF 109", "10-15 24-20 11-16", "", DECK_LOSING},
	{"ACF 110", "10-15 24-20 15-19", "", DECK_NORMAL},
	{"ACF 111", "11-15 21-17 08-11", "", DECK_NORMAL},
	{"ACF 112", "11-15 21-17 09-13", "", DECK_NORMAL},
	{"ACF 113", "11-15 21-17 09-14", "", DECK_NORMAL},
	{"ACF 114", "11-15 21-17 10-14", "", DECK_LOSING},
	{"ACF 115", "11-15 21-17 15-19", "", DECK_NORMAL},
	{"ACF 116", "11-15 22-17 08-11", "", DECK_NORMAL},
	{"ACF 117", "11-15 22-17 09-13", "", DECK_NORMAL},
	{"ACF 118", "11-15 22-17 15-18", "", DECK_NORMAL},
	{"ACF 119", "11-15 22-17 15-19", "", DECK_NORMAL},
	{"ACF 120", "11-15 22-18 15-22", "", DECK_NORMAL},
	{"ACF 121", "11-15 23-18 08-11", "", DECK_NORMAL},
	{"ACF 122", "11-15 23-18 09-14", "", DECK_NORMAL},
	{"ACF 123", "11-15 23-18 10-14", "", DECK_NORMAL},
	{"ACF 124", "11-15 23-18 12-16", "", DECK_NORMAL},
	{"ACF 125", "11-15 23-18 15-19", "", DECK_NORMAL},
	{"ACF 126", "11-15 23-19 08-11", "", DECK_NORMAL},
	{"ACF 127", "11-15 23-19 09-13", "", DECK_NORMAL},
	{"ACF 128", "11-15 23-19 09-14", "", DECK_NORMAL},
	{"ACF 129", "11-15 24-19 15-24", "", DECK_NORMAL},
	{"ACF 130", "11-15 24-20 08-11", "", DECK_NORMAL},
	{"ACF 131", "11-15 24-20 12-16", "", DECK_NORMAL},
	{"ACF 132", "11-15 24-20 15-18", "", DECK_NORMAL},
	{"ACF 133", "11-16 21-17 07-11", "", DECK_NORMAL},
	{"ACF 134", "11-16 21-17 08-11", "", DECK_NORMAL},
	{"ACF 135", "11-16 21-17 09-13", "", DECK_NORMAL},
	{"ACF 136", "11-16 21-17 09-14", "", DECK_NORMAL},
	{"ACF 137", "11-16 21-17 10-14", "", DECK_LOSING},
	{"ACF 138", "11-16 21-17 16-20", "", DECK_NORMAL},
	{"ACF 139", "11-16 22-17 07-11", "", DECK_NORMAL},
	{"ACF 140", "11-16 22-17 08-11", "", DECK_NORMAL},
	{"ACF 141", "11-16 22-17 09-13", "", DECK_NEW},
	{"ACF 142", "11-16 22-17 16-20", "", DECK_NORMAL},
	{"ACF 143", "11-16 22-18 07-11", "", DECK_NORMAL},
	{"ACF 144", "11-16 22-18 08-11", "", DECK_NORMAL},
	{"ACF 145", "11-16 22-18 10-15", "", DECK_LOSING},
	{"ACF 146", "11-16 22-18 16-19", "", DECK_NORMAL},
	{"ACF 147", "11-16 22-18 16-20", "", DECK_NORMAL},
	{"ACF 148", "11-16 23-18 07-11", "", DECK_NORMAL},
	{"ACF 149", "11-16 23-18 08-11", "", DECK_NORMAL},
	{"ACF 150", "11-16 23-18 09-14", "", DECK_NORMAL},
	{"ACF 151", "11-16 23-18 10-14", "", DECK_NORMAL},
	{"ACF 152", "11-16 23-18 16-20", "", DECK_NORMAL},
	{"ACF 153", "11-16 23-19 16-23", "", DECK_NEW},
	{"ACF 154", "11-16 24-19 07-11", "", DECK_NORMAL},
	{"ACF 155", "11-16 24-19 08-11", "", DECK_NORMAL},
	{"ACF 156", "11-16 24-19 10-15", "", DECK_LOSING},
	{"ACF 157", "11-16 24-19 16-20", "", DECK_NORMAL},
	{"ACF 158", "11-16 24-20 07-11", "", DECK_NORMAL},
	{"ACF 159", "11-16 24-20 16-19", "", DECK_NORMAL},
	{"ACF 160", "12-16 21-17 09-13", "", DECK_NORMAL},
	{"ACF 161", "12-16 21-17 09-14", "", DECK_NORMAL},
	{"ACF 162", "12-16 21-17 16-19", "", DECK_NORMAL},
	{"ACF 163", "12-16 21-17 16-20", "", DECK_NORMAL},
	{"ACF 164", "12-16 22-17 16-19", "", DECK_NORMAL},
	{"ACF 165", "12-16 22-17 16-20", "", DECK_NORMAL},
	{"ACF 166", "12-16 22-18 16-19", "", DECK_NORMAL},
	{"ACF 167", "12-16 22-18 16-20", "", DECK_NORMAL},
	{"ACF 168", "12-16 23-18 09-14", "", DECK_LOSING},
	{"ACF 169", "12-16 23-18 16-19", "", DECK_NORMAL},
	{"ACF 170", "12-16 23-18 16-20", "", DECK_NORMAL},
	{"ACF 171", "12-16 23-19 16-23", "", DECK_LOSING},
	{"ACF 172", "12-16 24-19 16-20", "", DECK_NORMAL},
	{"ACF 173", "12-16 24-20 08-12", "", DECK_NORMAL},
	{"ACF 174", "12-16 24-20 10-15", "", DECK_NEW},
} ;

#define NOPENINGS 	(sizeof(opening)/sizeof(opening[0]))

int
myatoi(char *s, int s0, int s1) 
{
    char buf[1024] ;
    strncpy(buf, s+s0, s1-s0) ;
    buf[s1-s0] = '\0' ;
    return atoi(buf) ;
}

int 
getacfopening(CheckerBoard *b, int n, char **moves, char **name, char **altname)
{
    regex_t re ;
    regmatch_t mat[7] ;
    int f, t ;

    if (n < 1 || n > 174)
	return FALSE ;

    n -- ;

    regcomp(&re, "([0-9]+)-([0-9]+) ([0-9]+)-([0-9]+) ([0-9]+)-([0-9]+)", REG_EXTENDED) ;

    if (regexec(&re, opening[n].moves, 7, mat, 0) != 0)
	return FALSE ;

    b->R = 0x00000fff ;
    b->W = 0xfff00000 ;
    f = myatoi(opening[n].moves, mat[1].rm_so, mat[1].rm_eo) ; 
    t = myatoi(opening[n].moves, mat[2].rm_so, mat[2].rm_eo) ; 
    b->R ^= ((1<<(f-1))|(1<<(t-1))) ;
    f = myatoi(opening[n].moves, mat[3].rm_so, mat[3].rm_eo) ; 
    t = myatoi(opening[n].moves, mat[4].rm_so, mat[4].rm_eo) ; 
    b->W ^= ((1<<(f-1))|(1<<(t-1))) ;
    f = myatoi(opening[n].moves, mat[5].rm_so, mat[5].rm_eo) ; 
    t = myatoi(opening[n].moves, mat[6].rm_so, mat[6].rm_eo) ; 
    b->R ^= ((1<<(f-1))|(1<<(t-1))) ;
    b->K = 0 ;

    recomputeboardhash(b, COLOR_WHITE) ;
    if (moves != NULL)
	*moves = opening[n].moves ;
    if (name != NULL)
	*name = opening[n].name ;
    if (altname != NULL)
	*altname = opening[n].altname ;

    return TRUE ;
}

char *
getrandomopening(CheckerBoard *b)
{
    char *m, *r ;
    static char buf[1024] ;

    int n ;
    do {
	n = lrand48() % NOPENINGS ;
    } while (!(opening[n].flags & DECK_TOURNAMENT)) ;

    getacfopening(b, n, &m, &r, NULL) ;
    sprintf(buf, "%s: 1. %s", r, m) ;
    return buf ;
}
