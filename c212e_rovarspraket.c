/*
Rövarspråket is not very complicated: you take an ordinary sentence and replace the consonants with the consonant doubled and with an "o" in between. So the consonant "b" is replaced by "bob", "r" is replaced with "ror", "s" is replaced with "sos", and so on. Vowels are left intact. It's made for Swedish, but it works just as well in English.

Your task today is to write a program that can encode a string of text into Rövarspråket. 
*/

	#include<stdio.h>
	#include<stdlib.h>
	#include<ctype.h>
	#include<string.h>
	#define MAX_LEN 100
	
	char vowels[] = "AEIOUYÅÄÖaeiouyåäö";
	
	void rovarspraket(char* sentence){
		
		while(*sentence){
			
			printf("%c", *sentence);
			if(isalnum(*sentence) && !strchr(vowels, *sentence)){//&&: logical AND
				printf("o%c", tolower(*sentence));
			}
			
			sentence++;
		}
		printf("\n");	
		return;
	}	
	
	int main(int argc, char* argv[]){
		char* input = (char *)malloc(MAX_LEN);
		input = fgets(input, MAX_LEN, stdin);
		rovarspraket(input);
		return 0;
	}
