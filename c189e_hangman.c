	//r/dailyprogrammer easy HANGMAN
	
	#include<stdlib.h>
	#include<stdio.h>
	#include<string.h>
	#include<stdbool.h>
	#include<time.h>
	
	char* word_list[26] = {"world", "plasma", "today", "snowboard",
    "typhoon", "wasatch", "reunion", "excel", "think", "crazy", "vapor", "texas",
    "street", "mountain", "space", "yellow", "python", "computer", "print", "string", 
    "xylophone", "scrabble", "lumberjack", "doppelganger", "conscientious", "predetermined"};
    
    	char* hangman[8] = {"-----------", "     |     ", "     o     ", "     |     ", "    -|     ", "    -|-    ", "    -|     ", "    -|-    "};
    	
    	void draw_hangman(int n){
    		printf("%s\n%s\n", hangman[0], hangman[1]);
    		
    		switch (n){
    			case 1: printf("%s\n", hangman[2]);
    				break;
    			case 2: printf("%s\n%s\n", hangman[2], hangman[3]);
    				break;
    			case 3: printf("%s\n%s\n", hangman[2], hangman[4]);
    				break;
    			case 4: printf("%s\n%s\n", hangman[2], hangman[5]);
    				break;
    			case 5: printf("%s\n%s\n%s\n", hangman[2], hangman[5], hangman[6]);
    				break;
    			case 6: printf("%s\n%s\n%s\n", hangman[2], hangman[5], hangman[7]);
    				break;
    		}
    		return;
    	}
    
    	void play_hangman(char* str){
    		int num_tries = 6; //head, torso, 2 hands, 2 legs
    		int num_guessed_correct = 0;
    		bool curr_guess;
    		int l = strlen(str);
    		int* mark_guesses = malloc(l*sizeof(int));
		for(int i = 0; i<l; i++)
			mark_guesses[i] = 0;
			
    		char* p;
    		char* k;
    		
    		char guess;
    		for (int i = 0; i<l; i++){
    			printf("_ ");
    		}   		
    		printf("\n~~Guess letter~~\n");
    		
    		while((num_tries>0) && (num_guessed_correct<l)){
    			scanf(" %c", &guess);
    			curr_guess = false;
    			p = str;
    			while(*p){
    				k = strchr(p, guess);
    				if(k){
    					curr_guess = true;
    					num_guessed_correct++; //each correct letter
	    				mark_guesses[k-str] = 1;
	    				p = k+1;
	    			}else
	    				break;
    			}
    			
    			for(int i = 0; i<l; i++){
    				if(mark_guesses[i]){
    					printf("%c ", str[i]);
    				}
    				else printf("_ ");
    			}
    			printf("\n");
    			if(!curr_guess){
    			    	num_tries--;
    				draw_hangman(6 - num_tries);
			}
    		}
    			
    		if(num_guessed_correct<l){
    			printf("Sorry, next time! Word was: %s\n", str);
    		}
    		
    		else printf("You won!\n");
    	}
    
	int main(int argc, char* argv[]){
    		char* word = NULL;
    		srand(time(NULL));
    		word = word_list[rand()%26];
    		
		play_hangman(word);
		return 0;
	}
    
    
