	//r/dailyprogrammer easy challenge 18
	//telephone keypad
	//gcc -g -std=c99 -Wall c18e_telephone_keypad.c -o c18e_telephone_keypad
	//./c18e_telephone_keypad
	//1-800-COMCAST
	
	#include<stdio.h>
	#include<ctype.h>
	
	int keys[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};
	
	void telephone_keypad(FILE* fp){
	
		char c = fgetc(fp);
		
		do{
			printf("%c", c);
			c= fgetc(fp);
		}while(!isalpha(c));
		
		do{
			int i = tolower(c) - 'a';
			printf("%d", keys[i]);
			c = fgetc(fp);
		}while(isalpha(c));
		
		printf("\n");
		
		return;
	}
	
	int main(int argc, char* argv[]){
		telephone_keypad(stdin);
		return 0;
	}
