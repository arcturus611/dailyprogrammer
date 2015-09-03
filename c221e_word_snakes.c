/*Your task today is to take an input word sequence and turn it into a word snake. Here are the rules for the snake:

    It has to start in the top left corner
    Each word has to turn 90 degrees left or right to the previous word
    The snake can't intersect itself

Other than that, you're free to decide how the snake should "snake around"*/
	
	#include<stdio.h>
	#include<stdlib.h>
	#include<ctype.h>
	#define MAX_LEN 1000
	#define MAX_WORDS 100
	
	int down = 0; /*flag to tell whether you are going right or down*/
	
	void print_spaces_so_far(int x){ /*just print x number of spaces*/
		for(int i = 0; i<x; i++)	
			printf(" ");
		return;
	}

	void rightdown_snake_words(char* sentence){
		/*eat up the characters and print */
		char c = *sentence;
		int hor_chars = 0; /*horizontal chars*/
		
		while(c){
			if(!isspace(c)){
				/*We either go down or increment our character count; after both cases, we print the letter*/
				if(down){ 
					printf("\n"); 	
					/* # spaces = -1 + total horizontal characters printed so far*/
					print_spaces_so_far(hor_chars-1); 
				}else hor_chars++;
				printf("%c", c); 
			}else{
				down = !down;
				sentence++; /*as a word's starting letter matches the previous word's last letter*/
			}
			
			sentence++;
			c = *sentence; 	
		}
		
		printf("\n");
		
		return;
	}

	int main(int argc, char* argv[]){
		char* input = (char *)malloc(MAX_LEN*sizeof(char)); 
		input = fgets(input, MAX_LEN, stdin); /*read input in a line of chars*/
		rightdown_snake_words(input);
		return 0;
	}
	
