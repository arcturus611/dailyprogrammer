//r/dailyprogrammer
//challenge 13- intermediate
//create a program that'll take any string and write it out to a file, reversed.
//gcc -std=c99 -g -Wall c13i_reverse_string.c -o c13i_reverse_string

#define _GNU_SOURCE
#include<stdio.h>
#include<string.h>

#define XORSWAP(a, b) if(a^b){a^=b; b^=a; a^=b;}

void reverse_string(char* s){
 int l = strlen(s);
 int m = l/2-1;// taking advantage of truncation in int division to get index of where to stop swapping
 for(int idx=0; idx<=m ; idx++){
   XORSWAP(s[idx], s[l-1-idx]);
 }
 
 printf("Here is the reversed string: %s\n", s); 
}

int main(int argc, char** argv){
 char* message = strdupa(argv[1]); 
 reverse_string(message); 
 return 0;
}
