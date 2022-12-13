#include <stdio.h>
#include <sys/types.h>

#include "standard.h"
#include "lookup8.h"

typedef struct {
	u_int32_t x, y, z ;
} T ;

T p = { 0x04000001, 0x00200000, 0x04200001 } ;
T q = { 0x04000000, 0x00200000, 0x04200000 } ;

int
main()
{
     ub8 h1 = hash((ub1 *) & p, sizeof(p), (ub8) 0) ;
     ub8 h2 = hash((ub1 *) & q, sizeof(q), (ub8) 1) ;

     printf("%08lx%08lx\n", (ub4) h1, (ub4) (h1 >> 32)) ;
     printf("%08lx%08lx\n", (ub4) h2, (ub4) (h2 >> 32)) ;
     return 0 ;
}
