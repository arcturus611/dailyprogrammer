	//r/dailyprogrammer challenge 109 (easy)
	//digits check
	
	#include<stdio.h>
	#include<ctype.h>
	
	void digits_check(char* s){
		
		while(*s){
			if(!isdigit(*s++)){
				printf("False\n");
				return;
			}
		}
		
		printf("True\n");
		return;
	
	}
	
	int main(int argc, char* argv[]){
		char* str = argv[1];
		digits_check(str);
		return 0;
	}
