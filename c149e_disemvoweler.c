	//r/dailyprogrammer challenge 149 (easy)
	//disemvoweler
	
	#include<stdio.h>
	#include<ctype.h>
	#include<stdlib.h>
	#include<string.h>
	
	#define MAX_LEN 100
	
	void disemvowel(char* line){
		char* p = line;
		line[strchr(line, '\n') - line] = '\0';
		char* cons_line = malloc(MAX_LEN*sizeof(char)); char* c = cons_line;
		char* vowels_line = malloc(MAX_LEN*sizeof(char)); char* v = vowels_line;
		
		while(*p){
			if(!isspace(*p)){
				if((*p)!='a' && (*p)!='e' && (*p)!='i' && (*p)!='o' && (*p)!='u')
					*c++ = *p;			
				else
					*v++ = *p;
			}
			p++;
		}
		*c = '\0';
		*v = '\0';
		
		printf("The disemboweled string is %s, and the vowels are %s\n", cons_line, vowels_line);
		free(cons_line);
		free(vowels_line);
		
		return;
	}
	
	int main(int argc, char* argv[]){
		char* line = malloc(MAX_LEN*sizeof(char));
		fgets(line, MAX_LEN, stdin);
		
		disemvowel(line);
		
		free(line);
		return 0;
	}
