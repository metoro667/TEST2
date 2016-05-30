#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _cell{
  int tag;
  union{
    struct{struct _cell *car,*cdr;} cons;
    int num;
    struct{char *name;struct _cell *value;} symbol;
   }data;
};

typedef struct _cell cell;
typedef cell *ptr;

#define HASHSIZE 8   //必ず,2^n

