// To create a program that finds all anagrams, we are going to create a linked list of linked lists. 
// The structs we are going to be working with here are word and anagram. word will make up the linked list of unique words, but each word element itself will have a linked list of anagrams. 
//edit sept 27: word will have the sorted string. just to make life easier.
//edit oct 11: not freeing mallocated memory! extremely bad practice, gotta add that!

// to compile: gcc -g -Wall -std=c99 c5i_anagram_count.c -o c5i_anagram_count
// to run: have a text file in pwd, named c5i_anagram_count.txt. Put any combination of anagrams, including repetitions of a word. And then do ./c5i_anagram_count. Smile at the output!
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#define MAX_WORD_SIZE 20

typedef struct word{
	char str[MAX_WORD_SIZE];
	struct anagram* anagram_list; 
	struct word* next;
}Word;

typedef struct anagram{
	char str[MAX_WORD_SIZE]; 
	struct anagram* next;
}Anagram;

Word* pStart;

Word* create_new_word(char*, char*);
Anagram* create_new_anagram(char*);
int get_new_word(FILE*, Word*, int); 
void add_word_to_list(Word*);
void print_sets(Word*);
void print_anagrams(Anagram*);
void free_words(Word*);
void free_anagrams(Anagram*);

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

int cmpfnc(const void* a, const void* b){
	return (*(const char *)a)-(*(const char *)b);
} 

void add_word_to_list(Word* pCurr){
	char* curr_str = pCurr->str;
	char curr_str_sorted[MAX_WORD_SIZE];
	strcpy(curr_str_sorted, curr_str);
	qsort(curr_str_sorted, strlen(curr_str_sorted), sizeof(char), cmpfnc);	


	if (pStart==NULL){
		//create pStart
		pStart = create_new_word(curr_str_sorted, curr_str);
		return;
	}
	
	Word* pCounter = pStart; // if pCurr isn't the very first Word in our list, we're gonna count through all the existing ones, to see if we can match it with any of the existing ones in the list
	Word* pLast = NULL;
	while(pCounter != NULL){
		if(strcmp(curr_str_sorted, pCounter->str)==0){
				bool unq = true; 
				Anagram* pCounterAnag = pCounter->anagram_list;
				Anagram* pLastAnag = NULL;
				while(pCounterAnag!=NULL){
					if (strcmp(pCounterAnag->str, curr_str)==0) unq = false; 
					pLastAnag = pCounterAnag;
					pCounterAnag = pCounterAnag->next;
				}
				if (unq == true)
					pLastAnag->next = create_new_anagram(curr_str);
				return;
		}
		pLast = pCounter; 
		pCounter = pCounter->next;
	}

	pLast->next = create_new_word(curr_str_sorted, curr_str);
	return;	
}

Word* create_new_word(char* sorted_str, char* str){
	Word* pNew = NULL; 
	pNew = malloc(sizeof(Word)); 
	strcpy(pNew->str, sorted_str);
	pNew->anagram_list = malloc(sizeof(Anagram));
	strcpy(pNew->anagram_list->str, str);
	pNew->anagram_list->next = NULL; 
	pNew->next = NULL; 
	return pNew;
} 

Anagram* create_new_anagram(char* str){
	Anagram* pAnag = NULL; 
	pAnag = malloc(sizeof(Anagram)); 
	strcpy(pAnag->str, str);
	pAnag->next = NULL; 
	return pAnag;
} 

void print_sets(Word* pInit){
	Word* pCurr = pInit;
	int index = 1;
	while(pCurr!= NULL){
		printf("Set %d of anagrams: ", index++);
		print_anagrams(pCurr->anagram_list);
		printf("\n");
		pCurr = pCurr->next;
	}
	return;
}

void print_anagrams(Anagram* pAnagStart){
	Anagram* pAnagCurr = pAnagStart;
	printf("%s", pAnagCurr->str);
	pAnagCurr = pAnagCurr->next;
	while(pAnagCurr!=NULL){
		printf(", %s", pAnagCurr->str);
		pAnagCurr = pAnagCurr->next;
	}
	return;
}

void free_words(Word* head){
	Word* node = head;
	Word* temp = NULL;
	while(node!= NULL){
		free_anagrams(node->anagram_list);
		temp = node; 
		node = node->next;
		free(temp);
	}
	head = NULL;
	return;
}

void free_anagrams(Anagram* head){
	Anagram* node = head;
	Anagram* temp;
	while(node!= NULL){
		temp = node;
		node = node->next;
		free(temp);		
	}
	head = NULL;
	return;
}

int main(int argc, char* argv[]){
	FILE* fp = fopen("c5i_anagram_count.txt", "r");
	
	pStart = NULL;
	Word* pCurr = malloc(sizeof(Word));

	while(get_new_word(fp, pCurr, MAX_WORD_SIZE)){
		add_word_to_list(pCurr);
	}

	print_sets(pStart);

	free_words(pStart);
	free_words(pCurr);

	fclose(fp);
	return 0;
}

