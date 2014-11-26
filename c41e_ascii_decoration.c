	//r/dailyprogrammer (easy) ASCII decoration banner
	
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#define MAX_LEN 100
	
	void print_decoration(char* line, int l){
		for(int i = 0; i<l+5; i++)
			printf("*");
		printf("\n");
		
		printf("*");
		for(int i = 0; i<l+3; i++)
			printf(" ");
		printf("*\n");
		
		printf("* %s *\n", line);
		
		printf("*");
		for(int i = 0; i<l+3; i++)
			printf(" ");
		printf("*\n");

		for(int i = 0; i<l+5; i++)
			printf("*");
		printf("\n");
	}
	
	int main(int argc, char* arv[]){
		char* line = malloc(MAX_LEN*sizeof(char));
		fgets(line, MAX_LEN, stdin);
		int l = strchr(line, '\n') - line; 
		line[strchr(line, '\n')-line] = '\0';
		
		print_decoration(line, l-1);
		return 0;
	}
