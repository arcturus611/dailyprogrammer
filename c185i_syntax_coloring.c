	//r/dailyprogrammer challenge 185 intermediate
	//print color fonts
	
	#include<stdio.h>
	#include<stdlib.h>
	#include<ncurses.h>
	#define MAX_WORD_LEN 30
	
	int get_new_word(FILE* fp, char* word){
		char* p = word;
		char c;

		do{
			c = fgetc(fp);
			if(c==EOF) return 0;
		}while(isspace(c));
		
!(isalpha(c) || isnum(c) || ispunct(c)));
		do{
			if(p-word<MAX_WORD_LEN)
				*p++ = c;
				c= fgetc(fp);
		}while(isalpha(c) || isnum(c) || );
	
		*p = '\0';
	
		return 1;
	}
	
	void(){
			initscr();
		if(has_colors() == FALSE){
			endwin();
			printf("Your terminal doesn't support color :(!\n");
			exit(1);
		}
		
		start_color();
		init_pair(1, COLOR_CYAN, COLOR_BLACK);
		
		attron(COLOR_PAIR(1));
		printw("This is a print\n");
		attroff(COLOR_PAIR(1));
		
		getch();
		endwin();
	}
	
	int main(int argc, char* argv[]){
		FILE* fp= fopen("syntax_color.txt", "r");
		char word[MAX_WORD_LEN];
		
		while(get_next_word(fp, 
		
		return 0;
	}
