	//r/dailyprogrammer challenge 139 (easy) pangrams
	//Solutions posted by others are amazing, especially the ones using bit-shift and comparing with 0x3ffff... Good trick.
	
	#include<stdio.h>
	#include<stdlib.h>
	#include<ctype.h>
	#include<stdbool.h>
	#include<string.h>
	
	#define ALPHABET_SIZE 26
	#define LINE_LEN 100
	int alpha_hist[26] = {0};
	
	void reset_alpha_hist(void){
		for(int i = 0; i<ALPHABET_SIZE; i++){
			alpha_hist[i] = 0;
		}
		return;
	}	
	
	void print_is_pangram(){
		bool is_pangram = true;
		for(int i= 0; i<ALPHABET_SIZE; i++){
			printf("%c: %d, ", 'a'+i, alpha_hist[i]);
			if(!alpha_hist[i]) is_pangram = false;
		}	
		
		if(is_pangram) printf("TRUE\n");
		else printf("FALSE\n");
		
		return;
	}
	
	void is_pangram(int n, char** lines){
		char* p; 
		
		lines = malloc(n*sizeof(char*));
		
		for(int i= 0; i<n; i++){
			lines[i] = malloc(LINE_LEN*sizeof(char));
			
			fgets(lines[i], LINE_LEN, stdin);
			lines[i][strchr(lines[i], '\n')-lines[i]] = '\0';
			
			p = lines[i];
			while((*p)!='\n' && (*p)!=0){
				if(isalpha(*p))	alpha_hist[tolower(*p)-'a']++;
				p++;
			}
			print_is_pangram();
			reset_alpha_hist();
		}
	
		//QUESTION: When I write this code to free memory outside this function, in main, I get a seg fault. Does that mean memory malloc'd inside a function isn't accessible outside of it if the pointer to that memory isn't returned? The variables 'lines' was passed into this function, and malloc'd some memory; when we get out of the fn, why can't main still access the data in that memory? It was, after all, in the heap, not stack,right?	
		for(int i = 0; i<n; i++){
			free(lines[i]);
		}	
		free(lines);
		
		return;
	}
	
	int main(int argc, char* argv[]){
		int n = atoi(argv[1]); //number of lines input
		
		char** lines = NULL;
		is_pangram(n, lines);
	
		return 0;
	}
