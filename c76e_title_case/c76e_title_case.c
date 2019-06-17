//compile: gcc -std=c99 -g -Wall c76e_title_case.c -o c76e_title_case

	#include<stdio.h>
	#include<string.h>
	#include<ctype.h>
	#include<stdlib.h>
	#include<stdbool.h>

	enum value_type {TYPE_STRING, TYPE_LIST}; 	
	
	struct cons{
		struct value* value; 
		struct cons* next;
	};

	struct cons* cons(struct value* v, struct cons* n){
		struct cons* cons = malloc(sizeof(struct cons)); 
		cons->value = v; 
		cons->next = n; 
		return cons; 
	}

	struct value{
		enum value_type TYPE;
		union{
			char string[64];
			struct cons* list; 
		};
	};
	
	struct value* read_string(FILE* in){
		struct value* v = malloc(sizeof(struct value)); 
		v->TYPE = TYPE_STRING; 

		int c; 
		char* p = v->string; 

		for(c = fgetc(in);isalpha(c); c = fgetc(in), p++){
			*p = c;
		} 	
		*p = '\0';

		ungetc(c, in); 
 
		return v;
	}

	struct value* read_list(FILE* in){
		struct value* v = malloc(sizeof(struct value));
		v->TYPE = TYPE_LIST; 
 
		struct cons head = {0}, *tail = &head; 
		int c; 

		while(1){
			for (c=fgetc(in); !isalpha(c) && c!=']'; c = fgetc(in)); 
			if (c==']')
				break;
			ungetc(c, in); 
			
			tail->next = cons(read_string(in), NULL); //this ensures you're pointing to NULL next.
			tail = tail->next;		
		}	
		v->list = head.next;	
		return v; 
	}

	struct value* read_input(FILE* in){
		int c; 
		for (c = fgetc(in); !isalpha(c); c = fgetc(in)); 
		ungetc(c, in); 

		return read_list(in); 

	}

	bool is_exception(char* word, struct value* exceptions){
		
		bool result = false; 
	
		for (struct cons* cons = exceptions->list; cons; cons = cons->next){
			struct value* v= cons->value; 
			char* exception_word = v->string; 
		
			if(strcmp(word, exception_word)==0){
				result = true;
				break;
			}
		}

		return result;
		
	}

	void title_case(struct value* sentence, struct value* exceptions){
		// we want the first word to remain untouched
		struct cons* cons = sentence->list;
		struct value* v = cons->value;
		char* word = v-> string;
		word[0] = toupper(word[0]);
		printf("%s ", word);
		cons = cons->next;
		
		for ( ; cons ; cons = cons->next){
			v = cons->value; 
			char* word = v->string; 

			for (int i = 0; word[i]; i++)
				word[i] = tolower(word[i]);

			if(!is_exception(word, exceptions))
				word[0] = toupper(word[0]); 

			printf("%s ", word); 
		}
		printf("\n");	

	}	

	int main(int argc, char* argv[]){
		printf("Welcome to Title Case! Please enter your exceptions within square brackets (each word should be in single quotes and separated from the next by a comma), then enter your desired sentence in square brackets and single quotes\n"); 
		struct value* exceptions = read_input(stdin);
		struct value* sentence = read_input(stdin);
		
		title_case(sentence, exceptions);
		return 0;
	}
