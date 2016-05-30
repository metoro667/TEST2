//2015.05.25
//read S-expression
// sread0525.c
// sread(FILE *fp) の作成
//分割コンパイル

#include "rdlisp.h"

extern ptr  cons(ptr x,ptr y);
extern ptr intern(char *p);
extern ptr  makeint(int n);
extern ptr nil;

#define ILLEGAL 0
#define ALPHA 1
#define NUM   2
#define MACRO 3  //まだ使わない
#define SPACE 4
#define RIGHTP 5
#define LEFTP  6
#define DOT    7

int readtable[128]={0};

//  mainから初期化で呼ぶ
void init_readtable(void){
  int i;
  for(i='a';i<='z';i++)
     readtable[i]=ALPHA;
  for(i='A';i<='Z';i++)
     readtable[i]=ALPHA;
  for(i='0';i<='9';i++)
     readtable[i]=NUM;
   readtable['(']=LEFTP;
   readtable[')']=RIGHTP;
   readtable['.']=DOT;
   readtable[' ']=SPACE;
   readtable['\n']=SPACE;
   readtable['\t']=SPACE;
   readtable['+']=ALPHA;
   readtable['-']=ALPHA;
   readtable['*']=ALPHA;
   readtable['/']=ALPHA;
}

char tokenstr[256];

static ptr sread_list(FILE *fp);  //プロトタイプ宣言

ptr symbol_token(int loc,FILE *fp){
int c,x;
  while(1){
    c=fgetc(fp);
    x=readtable[c];
    if(x==ALPHA||x==NUM){
     tokenstr[loc++]=c;
    }
   else
    break;
 }
   ungetc(c,fp);
   tokenstr[loc]='\0';
  return intern(tokenstr);  
}

ptr integer_token(int c,FILE *fp){   //c==+,- or 0-9
  int loc=0,x,sig=1,n=0,num=0;
  tokenstr[loc++]=c;
  if(c=='-') sig=-1;
  else if(c!='+'){
     num=1; // integer start
      n=c-'0';  // to integer!
    }
  else
    ;    //+  do nothing
  while(1){
    c=fgetc(fp);
    x=readtable[c];
    if(x==NUM){
       n=n*10+c-'0';   //integer の計算
      tokenstr[loc++]=c;  //symbolの可能性があるので必要
     }
   else if(x==ALPHA){
      tokenstr[loc++]=c;
      return symbol_token(loc,fp);  //これはsymbolだった 2xとか
     }
   else
     break;
  }
   ungetc(c,fp);
   if((num==0)&&(loc==1)){
      tokenstr[loc]='\0';
      return intern(tokenstr);   //+  or -  symbol!
    }
   n*=sig;
   return makeint(n);
 }
  

ptr sread(FILE *fp){
  int loc=0,c,x;
 while(1){
  c=fgetc(fp);
  x=readtable[c];
  switch(x){
     case ALPHA:
            tokenstr[loc++]=c;
          if(c=='+'||c=='-')
           return integer_token(c,fp);
          else
            return symbol_token(loc,fp);
     case NUM:
           return integer_token(c,fp);
     case SPACE: break;   //無視して、次の文字へ
     case LEFTP:
                return sread_list(fp);
     case RIGHTP:
                return (ptr)RIGHTP;
     case DOT:
                return (ptr)DOT;
     default: printf("sread:%c  illegal char\n",c);
              exit(1);
   }
 }
}
//  sread_listは、sread以外からはCALLしない。
static ptr sread_list(FILE *fp){
   ptr x,y;
    x=sread(fp);
    if(x==(ptr)RIGHTP) return nil;
    if(x==(ptr)DOT){
       x=sread(fp);
       y=sread(fp); //  )のはず
       if(y==(ptr)RIGHTP) return x;
       printf("illegal dot  . obj1 obj2 \n");
       exit(1);
    }
    return cons(x,sread_list(fp));
}

