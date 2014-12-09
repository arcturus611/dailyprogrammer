// to compile: gcc -g -Wall -std=c99 c191e_word_counting.c -o c191e_word_counting.bin
// to run: have a text file in pwd, named c191e_word_counting.txt. 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX_WORD_SIZE 20

typedef struct word{
	char str[MAX_WORD_SIZE];
	int num_occurences; 
	struct word* next;
}Word;

Word* pStart;

Word* create_new_word(char*);
int get_new_word(FILE*, Word*, int); 
void update_list(Word*);
void print_sets(Word*);
void free_words(Word*);

int get_new_word(FILE* fp, Word* pCurr, int len){
	char* p = pCurr->str; 
	char c; 
	
	do{
		c = fgetc(fp); 
		if(c==EOF)
			return 0;
	}while(!isalpha(c));
	
	do{
		if(p-pCurr->str<len-1) 
			*p++ = tolower(c);
	}while(isalpha(c = fgetc(fp)));
	
	*p = '\0';

	return 1;
}

Word* create_new_word(char* str){
	Word* pNew = NULL; 
	pNew = malloc(sizeof(Word)); 
	strcpy(pNew->str, str);
	pNew->num_occurences = 1;
	pNew->next = NULL; 
	return pNew;
}

void update_list(Word* pCurr){
	char* curr_str = pCurr->str;

	if (pStart==NULL){
		//create pStart
		pStart = create_new_word(curr_str);
		return;
	}
	
	Word* pCounter = pStart; // if pCurr isn't the very first Word in our list, we'll count through all the existing ones 
	Word* pLast = NULL;
	while(pCounter != NULL){
		if(strcmp(curr_str, pCounter->str)==0){ //if this word already existed in the list
			pCounter->num_occurences++;
			return;
		}else{
			pLast = pCounter; 
			pCounter = pCounter->next;
		}
	}

	pLast->next = create_new_word(curr_str);
	return;	
}

void print_word_occurences(Word* pInit){
	Word* pCurr = pInit;
	int index = 1;
	while(pCurr!= NULL){
		printf("%s: %d\n", pCurr->str, pCurr->num_occurences);
		pCurr = pCurr->next;
	}
	return;
}

void free_words(Word* head){
	Word* node = head;
	Word* temp = NULL;
	while(node!= NULL){
		temp = node; 
		node = node->next;
		free(temp);
	}
	head = NULL;
	return;
}

int main(int argc, char* argv[]){
	FILE* fp = fopen("c191e_word_counting.txt", "r");
	
	pStart = NULL;
	Word* pCurr = malloc(sizeof(Word));

	while(get_new_word(fp, pCurr, MAX_WORD_SIZE)){
		update_list(pCurr);
	}

	print_word_occurences(pStart);

	free_words(pStart);
	free_words(pCurr);

	fclose(fp);
	return 0;
}

