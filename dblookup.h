// dblookup.h
// all you need.

// include 

// choose which db you want to use

#define PRELOAD // preload (parts) of db in cache? 

#define AUTOLOADSIZE 0

#define DB_BLACK 0
#define DB_WHITE 1


#define SPLITSIZE 8
#define BLOCKNUM4 250
#define BLOCKNUM5 2000
#define BLOCKNUM6 42000
#define BLOCKNUM7 400000
#define BLOCKNUM8 4600000

#define MAXIDX4 100
#define MAXIDX5 500
#define MAXIDX6 1000
#define MAXIDX7 31000
#define MAXIDX8 44000
#define SPLITSIZE 8
#define MAXPIECE 4

#define MINCACHESIZE 65536

//int initdblookup(char str[256]);
#define PRINTF_BUFFER_SIZE      (512)
int db_init(int suggestedMB, char str[PRINTF_BUFFER_SIZE]);
int db_exit(void);
int dblookup(POSITION *p,int cl);
int revert(uint32_t n);
int db_getcachesize(void);
void db_infostring(char *str);
int LSB(uint32_t x);
int MSB(uint32_t x);
