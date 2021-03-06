//r/dailyprogrammer
//challenge 13- intermediate
//create a program that'll take any string and write it out to a file, reversed.
//gcc -std=c99 -g -Wall c13i_reverse_string.c -o c13i_reverse_string

#define _GNU_SOURCE
#include<stdio.h>
#include<string.h>

#define XORSWAP(a, b) if(a^b){a^=b; b^=a; a^=b;} //See the Wikipedia page for a beautiful explanation of xorswap

void reverse_string(char* s){
 int l = strlen(s);
 for(int i=0, j = l-1; i<=j ; i++, j--){
   XORSWAP(s[i], s[j]);
 }
 
 printf("Here is the reversed string: %s\n", s); 
}

int main(int argc, char** argv){
 char* message = strdupa(argv[1]); 
 reverse_string(message); 
 return 0;
}
