	//r/dailyprogrammer challenge 168 (string index)
	
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<ctype.h>
	
	#define WORD_LEN 25
	#define LINE_LEN 200
	
	typedef struct _word_{
		char str[WORD_LEN];
		struct _word_* next;
	}word;
	
	int get_new_word(FILE* fp, word* curr, int len){
		char* p = curr->str; //we malloc'd curr outside, so this is legal.
		char c;
		
		do{
			c = fgetc(fp); //we're moving the fp forward while doing this.
			if(c==EOF || c=='\n')
				return 0;
		}while(!isalnum(c));
		
		do{
			if(p-curr->str < len-1)
				*p++ = c;
		}while(isalnum(c = fgetc(fp)));
		ungetc(c, fp);
		*p = '\0';
		
		return 1;
	}
	
	word* add_word(word* curr){
		word* temp = malloc(sizeof(word));
		strcpy(temp->str, curr->str);
		temp->next = NULL;
		return temp;
	}

	void index_words(word* head, int n){
		word* curr = head;
		int i = 1;
		
		while(curr!=NULL){
			if(i==n){
				printf("Word %d is %s\n", i, curr->str);
				return;
			}
			i++;
			curr = curr->next;
		}
		printf("Not that many words in the given string!\n");
		return;
	}
	
	void free_words(word* head){
		word* curr = head;
		word* prev = NULL;
		while(curr!=NULL){
			prev = curr;
			curr = curr->next;
			free(prev); 
		}
		return;
	}

	int main(int argc, char* argv[]){
		
		word* head = NULL;
		word* counter = NULL;
		word* last = NULL;
		word* curr = malloc(sizeof(word));
		
		while(get_new_word(stdin, curr, WORD_LEN)){
			if(head==NULL){
				head = add_word(curr); 
			}
			else {
				counter = head;
				while(counter!=NULL){
					last = counter;
					counter = counter->next;
				}
				last->next = add_word(curr); 
			}
		}
		
		int n; 
		scanf("%d", &n);
		index_words(head, n);	
		free_words(head);
		free(curr);
		return 0;
	}
