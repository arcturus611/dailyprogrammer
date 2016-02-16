
	#include<stdio.h>
	#include "print_string.h"
	
	void print_string(char* inp){
		char* p = inp;
		while((*p)!='\n'){
			printf("%c", *p);
			p++;
		}
		printf("\n");
		return;
	}
