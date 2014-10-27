	//r/dailyprogrammer c144easy nut bolts
	//gcc -g -Wall -std=c99 c144e_nut_bolts.c -o c144e_nut_bolts
	//./c144e_nut_bolts N
	
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<stdbool.h>
	#include<ctype.h>
	
	#define MAX_WORD_LEN 50
	#define MAX_LINE_LEN 60
	
	typedef struct item_info_{
		char name[MAX_WORD_LEN];
		int old_price, new_price;
	}item_info;
	
	void read_item_info(item_info* info, int n){
		char line[MAX_LINE_LEN];
		
		for (int i = 0; i<2*n; i++){
			bool is_repeated = false;
			if (fgets(line, MAX_LINE_LEN, stdin)== NULL) 
				printf("error\n");
			else{
				char* p = line; int j;
				
				line[strchr(line, '\n')-line] = '\0';
				
				while(!isspace(*p)) p++; //assuming line begins with alphabetical char
				*p = '\0'; //insert null in place of space.
				p++;
				
				while(isspace(*p)) p++;
				
				
				for (j = 0; (j<n) & (j<i); j++){
					if(strstr((info+j)->name, line)){
						(info+j)->new_price = atoi(p);
						is_repeated = true;
						break;
					}
				}
				if(j==n) j--;
				if (!is_repeated){
					strcpy((info+j)->name, line);
					(info+j)->old_price = atoi(p);
				}
				
			}
		}
		
		return;
	}
	
	void print_item_change_info(item_info* info, int n){
		for (int i= 0; i<n; i++){
			int delta_price = (info+i)->new_price - (info+i)->old_price;
			if (delta_price)
				printf("Change in price of %s is %d\n", (info+i)->name, delta_price);
		}
		return;
	}
	
	int main(int argc,  char* argv[]){
		int N = atoi(argv[1]);
		
		item_info* info_list = malloc(N*sizeof(item_info));
		
		read_item_info(info_list, N);
		
		print_item_change_info(info_list, N);
		
		return 0;
	}
