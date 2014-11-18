	//r/dailyprogrammer mini challenge
	//count letters in a string
	
	//see skeeto's solution, it's really clever.
	//you use the fact that you are doing a character-wise analysis here, and use getchar instead of fgets() or something like that.
	#include<stdio.h>
	#include<stdlib.h>
	#include<ctype.h>
	
	#define MAX_LEN 1000
	
	int* count_letters(char* str){
		int* count = malloc(26*sizeof(int));
		
		for(int i = 0; i < 26; i++)
			count[i] = 0;
			
		char* p = str;
		while(*p){
			if(isalpha(*p)){
				count[tolower(*p)-'a']++;
			}	
			p++;
		}
		
		return count;
	}
	
	void print_letter_count(int* I){
		for(int i = 0; i<26; i++){
			if(I[i]!=0)
				printf("%c:%d ", 'a'+i, I[i]);
		}
		printf("\n");
		return;
	}
	
	int main(int argc, char* argv[]){
		char line[MAX_LEN] = "Hello World!";
		
		int* letter_count = NULL;		
		letter_count = count_letters(line);
		
		print_letter_count(letter_count);
		
		return 0;
	}
