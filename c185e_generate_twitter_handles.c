	//r/dailyprogrammer easy challenge 185
	//generating twitter handles
	//gcc -std=c99 -g -Wall c185e_generate_twitter_handles.c -o c185_generate_twitter_handles

	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<ctype.h>

	#define MAX_WORD_LEN 30

	int get_new_word(FILE* fp, char* word){
		char* p = word;
		char c;
	
		do{
			c = fgetc(fp);
			if(c==EOF) return 0;
		}while(!isalpha(c));
	
		do{
			if(p-word<MAX_WORD_LEN)
				*p++ = tolower(c);
		}while(isalpha(c= fgetc(fp)));
	
		*p = '\0';
	
		return 1;
	}

	void generate_twitter_handles(char* word){
		int l = strlen(word);
		char* p = word;
		char* pos = NULL;
		int last_match_pos;
	
		while(p-word<l){
			pos = strstr(p, "at");
			if(pos==NULL) break;
			else{
				last_match_pos = pos-p;
				for(int i = 0; i<last_match_pos; i++)
					printf("%c", p[i]);
				printf("@");
				p = p + last_match_pos + 2;
			}
		}
	
		if(p!=word){
			printf("%s: %s\n", p, word);
		}
	
		return;
	}

	int main(int argc, char* argv[]){
		FILE* fp = fopen("twitter_handles.txt", "r");
		char word[MAX_WORD_LEN];
	
		while(get_new_word(fp, word)){
			generate_twitter_handles(word);
		}
	
		fclose(fp);
		return 0;
	}
