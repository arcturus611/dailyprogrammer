	//r/dailyprogrammer
	//challenge 193, easy acronym expander
	
	#include<stdio.h>
	#include<ctype.h>
	#include<string.h>
	
	#define MAX_LINE_LEN 100
	#define MAX_WORD_LEN 20
	#define NUM_ACRONYMS 10
	
	char* acronyms[NUM_ACRONYMS] = {"lol", "dw", "hf", "gg", "brb", "g2g", "wtf", "wp", "gl", "imo"};
	char* acronyms_expanded[NUM_ACRONYMS] = {"laugh out loud", "don't worry", "have fun", "good game", "be right back", "got to go", "what the fuck", "well played", "good luck", "in my opinion"};
	
	int expand_words(char* word){
		for(int i= 0; i<NUM_ACRONYMS; i++){
			if(strcmp(word, acronyms[i])==0) {
				printf("%s", acronyms_expanded[i]); // if it IS in the acronym list, print the expansion
				return 0;
			}
		}
		return 1;
	}
	
	int get_words_and_expand(char* line){
		char* p = line;
		
		while(1){
			char word[MAX_WORD_LEN];
			char* w = word; //to walk along the letters of the word
		
			while(!isalnum(*p)){ //get rid of all non-wordCharacters
				if(!(*p)){ // if EOL reached (*p = 0), print NEWLINE and quit
					printf("\n");
					return 0;
				}
				printf("%c", *p++); //else print whatever non-wordChar you have (period, comma, exclamation, etc)
			}
		
			do{ //now we are filling the word
				*w++ = *p++;
			}while(isalnum(*p)); //alphanumeric chars needed because of words like g2g.
			*w = '\0';
		
			if(expand_words(word)) printf("%s", word); //if it's NOT in the acronym list, print it out
		}
		
		return 1;
	}	
	
	int main(int argc, char* argv[]){
		char line[MAX_LINE_LEN]; 
		fgets(line, MAX_LINE_LEN, stdin);
		line[strchr(line, '\n') - line] = '\0';
		
		get_words_and_expand(line);

		return 0;
	}
