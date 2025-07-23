#!/usr/bin/env python

# $Id: index.py,v 1.2 2009/05/13 05:54:23 markv Exp $
#

def fact(n):
        total = 1
        while n > 0:
                total *= n 
                n = n - 1 
        return total

def comb(a,b):
        if a >= b:
                return fact(a) / (fact(a-b)*fact(b)) ;
        else:
                return 0

def decompose(idx, n):
        l = []
        id = list(range(32))
        id.reverse()
        for i in id:
                if comb(i, n) <= idx:
                        l = [i] + l
                        idx -= comb(i, n)
                        n = n - 1 
                        if n == 0:
                                break ;
        return l


print((comb(30,1) + comb(31,2) + 1))

for x in range(0,32):
       for y in range(x+1, 32):
               for z in range(y+1, 32):
                       idx = comb(x, 1) + comb(y, 2) + comb(z, 3)
                       print(idx, decompose(idx, 3))
