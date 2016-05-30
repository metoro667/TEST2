#include "rdlisp.h"

extern void init_readtable(void);
extern ptr sread(FILE *fp);

//これは、sread.cで定義されているので変更に注意
#define RIGHTP 5

//#define HASHSIZE 8

//#define nil  NULL   //これでも良い。
cell NIL;
ptr nil;
ptr free_list;
// プロトタイプ宣言

ptr  add_free_cell(int n);

ptr  car(ptr p){
    return p->data.cons.car  ;
}
ptr  cdr(ptr p){
    return p->data.cons.cdr  ;
}
ptr  cons(ptr x,ptr y){
  ptr p;
   //p=malloc(sizeof(cell));
   p=free_list;
   if(p==nil){
      p=add_free_cell(1000);
   }
   free_list=cdr(p);
   p->data.cons.car=x ;
   p->data.cons.cdr=y  ;
   p->tag=0;  //0はcons
  return p;
}
ptr  makeint(int n){
  ptr p;
   p=cons(nil,nil);
   p->data.num=n ;
   p->tag=1  ;//1は整数データ
  return p;
}
ptr  makesymbol(char *name){
  ptr p;
  char *s;
   p=cons(nil,nil);
  //  mallocに変更してある。
   s=malloc(strlen(name)+1);
   strcpy(s,name);
   p->data.symbol.name=s;
   p->tag=2  ;//2はシンボル
  return p;
}
ptr find_symbol(ptr hlist,char *name){
  ptr s;
  while(hlist!=nil){
    s=car(hlist);
    if(strcmp(s->data.symbol.name,name)==0){
       return s;
    }
   hlist=cdr(hlist);
  }
  return nil;
}

ptr print_cons (ptr p); //プロトタイプ宣言

ptr print_dot(ptr p){
  if(p==nil){
    printf("()");
     return nil;
  }  
  switch(p->tag){
     case 0:  //リストのprint
          putchar('(');
          print_dot(car(p));
          printf(" . ");
          print_dot(cdr(p));
          putchar(')');
         break;
     case 1:  //int
          printf("%d",p->data.num);
          break;
     case 2:  //symbol
          printf("%s",p->data.symbol.name);
         break;
     default:
          printf("Abnormal data! Fatal!\n");
          exit(1);
   }
   return nil;
}


ptr print(ptr p){
  if(p==nil){
    printf("()");
     return nil;
  }   
  switch(p->tag){
     case 0:  //リストのprint
          putchar('(');
          print_cons(p);
         break;
     case 1:  //int
          printf("%d",p->data.num);
          break;
     case 2:  //symbol
          printf("%s",p->data.symbol.name);
         break;
     default:
          printf("Abnormal data! Fatal!\n");
          exit(1);
   }
   return nil;
}   

ptr print_cons(ptr p){  //  p is cons
  ptr next;
          print(car(p));
          next=cdr(p);
          if(next==nil)
             putchar(')');
          else if(next->tag==0){ //list が続く
            putchar(' ');
             print_cons(next);
            }
          else{  //非真性リスト
            printf(" . ");
            print(next);
            putchar(')');
         }
     return nil;
}
//free_list

 ptr  add_free_cell(int n){
     ptr  p,f=free_list;
     p= malloc(n*sizeof(cell));
   while(n>0){
        p->data.cons.cdr =f;
        p->tag=0;   //cons
        f=p;
        p++;
        n--;
      }
    free_list=f;
    return f;
 }
ptr hashtable[HASHSIZE];
int hashmask;

int hash(char *p) {
    int h=0,c;
    while((c=*p++)!=0)  {       
       h+=(h<<1);   // h=3*h
      h+=c;
     }
   return  h&hashmask;
} 
ptr intern(char *name){
  int h;
  ptr p,hlist;
  h=hash(name);
  hlist=hashtable[h];
  p=find_symbol(hlist,name);
 if(p==nil){
     p=makesymbol(name);
     hashtable[h]=cons(p,hlist);
   }
 return p;
}
void print_hash(){
  int i;
   for(i=0;i<HASHSIZE;i++){
   printf("%d: ",i);
   print(hashtable[i]);
   putchar('\n');
  }
} 
void sys_init(){
  int i;
   nil=&NIL;
   free_list=nil;
   add_free_cell(1000);

   init_readtable();

   hashmask=HASHSIZE-1;
   for(i=0;i<HASHSIZE;i++){
    hashtable[i]=nil;
  }
}

int main(){
  ptr s,q,bye;
  int ex = 0;
   sys_init();
   q=intern("quit");
   bye=intern("bye");
  while(1){
   printf("rdlisp> ");
   s=sread(stdin);
  if(s==(ptr)RIGHTP){
     printf("Error Illegal right par )\n");
     exit(1);
  }
  print(s);
  putchar('\n');

  if(s==nil){
		  printf("nil!\n");  //  quit!
  }
    else{
        switch(s->tag){
            case 0: //リストのprint
                printf("List!\n");
				if(car(s)==bye&&cdr(s)==nil) ex = 1;
				break;
			case 1: //int
				printf("int!\n");
				break;
			case 2: //Symbol
				printf("Symbol!\n");
				break;
			defaul:
				printf("Abnormal data! Fatal!\n");
				exit(1);
        }
    }


  if(s == bye) break;
  if(ex == 1) break;
  }
  print_hash();
  return 0;
}

