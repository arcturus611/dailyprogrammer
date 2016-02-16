/* For this challenge you'll be asked to implement the Atbash cipher and encode (or decode) some English language words. If the character is NOT part of the English alphabet (a-z), you can keep the symbol intact.*/

	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<ctype.h>
	#define MAX_LEN 1000
	#define LC_A 97
	#define LC_Z 122
	#define UC_A 65
	#define UC_Z 90
	
//	char* atbash(char* inp){
	void atbash(char* inp){
		int l = strlen(inp);
		char* cipher_input = (char *)malloc(l*sizeof(char));
		for (int i = 0; i<l; i++){
			if (inp[i] >= LC_A && inp[i]<=LC_Z){
				cipher_input[i] = LC_A + LC_Z - inp[i];
			}
			else if (inp[i] >= UC_A && inp[i]<= UC_Z){
				cipher_input[i] = UC_A + UC_Z - inp[i];
			}
			else cipher_input[i] = inp[i];
			
			printf("%c", cipher_input[i]); 
		}
		
		//return 0;
		//return cipher_input; 
	}

	int main (int argc, char* argv[]){
		char* input = (char *)malloc(MAX_LEN*sizeof(char));
		input = fgets(input, MAX_LEN, stdin);
		
		atbash(input);
		//cipher = atbash(input);
		
	//	print_string(cipher);
		
		return 0;
	}
