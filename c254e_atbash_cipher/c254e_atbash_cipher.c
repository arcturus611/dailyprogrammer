/* For this challenge you'll be asked to implement the Atbash cipher and encode (or decode) some English language words. If the character is NOT part of the English alphabet (a-z), you can keep the symbol intact.*/

	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<ctype.h>
	
	#include "print_string.h"
	#define MAX_LEN 1000
		
	char* atbash(char* inp){
		char* cipher_input = (char *)malloc(MAX_LEN*sizeof(char));
		char* src = inp;
		char* dest = cipher_input;
		
		while((*src)!='\n'){
			if ((*src) >= 'a' && (*src)<= 'z'){
				*dest = 'a' + 'z' - (*src);
			}
			else if ((*src) >= 'A' && (*src)<= 'Z'){
				*dest = 'A' + 'Z' - (*src);
			}
			else *dest = *src;
			
			src++;
			dest++;
		}
		*dest = '\n';
		
		return cipher_input;
	}

	int main (int argc, char* argv[]){
		char* input = (char *)malloc(MAX_LEN*sizeof(char));
		input = fgets(input, MAX_LEN, stdin);
		char* output = NULL; 
		output = atbash(input);
		
		printf("The given input is: ");
		print_string(input);
		printf("... and the Atbash cipher is: "); 
		print_string(output);
		
		return 0;
	}
