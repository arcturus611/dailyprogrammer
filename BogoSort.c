// r/dailyprogrammer
// challenge 175- easy
// bogosort
//gcc -std=c99 -g BogoSort.c -o BogoSort_mint

#define _GNU_SOURCE
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdint.h>
#include<ctype.h>
#include<stdlib.h>

#define SWAP(a, b) if(a^b){a^=b; b^=a; a^=b;}

void shuffle(char* s){
 int i, n;
 int len = strlen(s);
 for(i = len-1; i>0; i--){
  n = rand()%(i+1); 
  SWAP(s[i], s[n]); 
 }
}

bool issorted(char* s){
 for(const char* p = s; p[1]; p++){
  if (toupper(p[0])>=toupper(p[1]))
   return false;
 }
 return true;
}

uint64_t bogo_sort(char* s){
 uint64_t count; 
 for (count = 0; !issorted(s); count++){
  shuffle(s); 
 }
 return count; 
}

int main(int argc, char** argv){
 char* message = strdupa(argc>1 ? argv[1] : "Sample string"); 
 int count = bogo_sort(message); 
 printf("Number of iterations: %d, sorted string: %s\n", count, message); 
 return 0;
}
