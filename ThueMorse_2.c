// ThueMorse- method 2
//r/dailyprogrammer
// Added comment Aug 25- no, this isn't going to work. 
#include<stdio.h>
#include<string.h>

char* bitstr = "01101001"; 

#define SWAP(T, a, b) \
do { T save = (a); (a) = (b); (b) = save; } while (0)
char *strrev(char *s)
{
size_t len = strlen(s);
if (len > 1) {
char *a = s;
char *b = s + len - 1;
for (; a < b; ++a, --b)
SWAP(char, *a, *b);
}
return s;
}


void thueMorse_2(){
 char* revbitstr = (char*)malloc(50*sizeof(char)); 
 int step; //, numBlocks, *tmArr, len, totalLen, blk;
 printf("\n0\n01\n0110\n"); 
 //numBlocks = 1; // double at every step.

 for (step = 3; step<7; step++){
  /*totalLen = numBlocks*8; 
  for (blk = 0; blk<numBlocks; blk++){
   
  }*/ 
  //printf("%s", bitstr); 
  strcpy(bitstr, revbitstr); 
  revbitstr = strrev(bitstr); 
  strcat(bitstr, revbitstr); 
  printf("%s", bitstr); 
 }

}

int main(int argc, char** argv){
 thueMorse_2();
 /*printf("\nNow print an arbitrary nth order sequence\n"); 
 thueMorse_2_n(8);*/
 return 0;
}
