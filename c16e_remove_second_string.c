	//r/dailyprogrammer challenge 16 easy
	//remove string characters
	//gcc -g -std=c99 -Wall c16e_remove_second_string.c -o c16e_remove_second_string
	//To run: ./c16e_remove_second_string String1 String2
	// Note: the solution by /u/defrost is excellent in understanding the use of several pointers for the same address. 
	
	#include<stdio.h>
	#include<string.h>
	
	void remove_second_string(char* s1, char* s2){
		char c;
		int l1 = strlen(s1);
		
		for (int i = 0; i<l1; i++){
			c = s1[i];
			if(strchr(s2, c)==0) printf("%c", c);
		}
		
		printf("\n");
		
		return;
	}
	
	int main(int argc, char* argv[]){
		char* str1 = argv[1]; //note you can't initialize as char str1[] = argv[1]
		char* str2 = argv[2]; 
	
		remove_second_string(str1, str2);
		
		return 0;
	}
