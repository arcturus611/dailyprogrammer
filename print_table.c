//r/dailyprogrammer
//challenge 69 (easy)
//takes title and items as inputs and prints them out in a nice table/column (if only one title)
//works, but is so ugly, inelegant (code) and very shaky as far as edge cases go! Works only for the correct input format 
// sept 9, 2014

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX_TITLES 5
#define MAX_CHARS_PER_WORD 15
#define MAX_ITEMS_PER_TITLE 5

char titles[MAX_TITLES][MAX_CHARS_PER_WORD]; //= malloc(MAX_TITLES*sizeof(char* ));
char items[MAX_TITLES][MAX_CHARS_PER_WORD*MAX_ITEMS_PER_TITLE]; // = malloc(MAX_TITLES*MAX_ITEMS_PER_TITLE*sizeof(char* )); 

int read_titles(FILE* in){
	char line[MAX_CHARS_PER_WORD*MAX_TITLES]; 
 	if (fgets(line, MAX_CHARS_PER_WORD*MAX_TITLES, in)!= NULL){
		int i = 0; 
  		int title_count = 0; 

		bool inside_list = true; 
		while(line[i]!='\n' && inside_list==true){ //until end of line is reached
			while(line[i]!='\n' && line[i]!='\''){
				i++;
			}
  			i++; 

		       // word starts
			int char_count= 0;
			while(line[i]!='\''){
				titles[title_count][char_count++] = line[i++];
			}
			i++; 

			if (char_count>0){
				titles[title_count][char_count] = '\0';
				title_count++;		
			}
			
			if (line[i]==']'){
				i++;
				inside_list = false; 
			}

		  }
		 return title_count; 
	}
	else
		return 0; 
}	

int read_items(FILE* in){
	char line[MAX_TITLES*MAX_ITEMS_PER_TITLE*MAX_CHARS_PER_WORD]; 

 	if (fgets(line, MAX_TITLES*MAX_ITEMS_PER_TITLE*MAX_CHARS_PER_WORD, in)!= NULL){
		int i = 0; 
		bool inside_list = false; 
		bool inside_items = false; 				
		int item_count = 0; 

		while(line[i]!='\n'){ //until end of line is reached
			while(line[i]!='\n' && line[i]!='['){
				i++;
			}
			inside_list = true; 
  			i++; //previous char was '['
			
			while(inside_list==true){
				while(line[i]!='['){
					i++; 
				}
				i++;//prev char was '[' 
				inside_items = true; 			
	
				while(inside_items == true){
					while(line[i]!='\''){
						i++; 
					}
					i++; //prev char was '\''
				       // word starts
					int char_count= 0;
					while(line[i]!='\''){
						items[item_count][char_count++] = line[i++];
					}
					i++; //prev char was a '\''
	
					if (char_count>0){
						items[item_count][char_count] = '\0';
						item_count++;		
					}

					if (line[i]==']'){
						inside_items = false; 
						i++;
					}
				}	

				if (line[i]==']'){
					inside_list = false; 
					i++;
				}
			} //endwhile start list
		}// endwhile line
		return item_count; 
	}
	else
		return 0; 
}

void print_table(int title_count, int item_count){
	for (int i = 0; i<title_count; i++){
		printf(" %s ", titles[i]); 
	}	
	printf("\n\n\n"); 
	int items_per_title = item_count/title_count; 
	for(int i = 0; i<items_per_title; i++){
		for(int j = 0; j<title_count; j++){
			printf("   %s   ", items[i + j*items_per_title]); 
		}
		printf("\n"); 
	}
	return; 
}

int main(int argc, char* argv[]){
	int title_count = read_titles(stdin); 
	int item_count = read_items(stdin); 
	print_table(title_count, item_count);		
	return 0;
}
