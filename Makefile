SRC=milhouse.c plaidmove.c lookupa.c puzzle.c lookup8.c chinookdb.c postscript.c dblookup.c acf-openings.c
OBJ=milhouse.o plaidmove.o lookupa.o puzzle.o lookup8.o chinookdb.o postscript.o dblookup.o acf-openings.o
HDR=dblookup.h lookup8.h lookupa.h milhouse.h standard.h acf-openings.h
PYTHONSRC=capturegen.py index.py movegen.py plaid.py
OSRC=pdnparse.y pdnlex.l
CFLAGS=-O6 -Wall -fomit-frame-pointer -DRUNINTERACTIVE\
	-DMILHOUSE -D_GNU_SOURCE \
	-DUSE_TRANSPOSITION_TABLES -DQUIESCENCE 

LIBS=-lreadline -ltermcap -lm -lsqlite3
YFLAGS=-dvg

all: milhouse pdnparse

dist:
	tar cvzf milhouse.tar.gz $(SRC) $(HDR) $(PYTHONSRC) $(OSRC) Makefile

milhouse: $(OBJ)
	$(CC) -o $@ $(CFLAGS) $(OBJ) $(LIBS)

pdnparse:	pdnparse.o pdnlex.o
	$(CC) -o $@ $(CFLAGS) pdnparse.o pdnlex.o $(LIBS)

xxx.c:	plaidmove.c plaid.c
	$(CC) -E $(CFLAGS) plaidmove.c > xxx.c
	indent xxx.c

plaid.c: plaid.py
	python plaid.py > plaid.c

testhash: testhash.o lookup8.o
	$(CC) -o $@ $(CFLAGS) testhash.o lookup8.o

move.c:	movegen.py
	python movegen.py > move.c

capture.c:	capturegen.py
	python capturegen.py > capture.c

dblookup.o: dblookup.h

clean:
	rm $(OBJ)

libbanner.so:	libbanner.c
	gcc -Wall -fPIC -c libbanner.c
	gcc -shared -o libbanner.so libbanner.o

milhouse.o: milhouse.c lookupa.h standard.h milhouse.h Makefile
capture.o: capture.c milhouse.h
lookupa.o: lookupa.c standard.h lookupa.h
move.o: move.c milhouse.h
puzzle.o: puzzle.c milhouse.h
lookup8.o: lookup8.c standard.h
plaidmove.o: plaidmove.c plaid.c
