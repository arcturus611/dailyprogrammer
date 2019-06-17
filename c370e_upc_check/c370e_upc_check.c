/* 
COMPUTE UPC DIGIT.
*/

#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define MAX_LEN 100

void read_string(FILE* in, char* word){
// inputs: 
// FILE* in = file to read string from
// char* word = pointer to string entered by user

// Function reads the input file and 
// transfers the alphanumeric string
// into the character array "word"
	int c;
	for (c= fgetc(in); isalnum(c); c = fgetc(in), word++)
		*word = c;
	*word = '\0';
	ungetc(c, in);
	return;
}

int upc_check_digit(char* word){
// inputs
// char* word = user's string

// outputs
// int check_dig = UPC check digit computed as per the following alg.

/*

Sum the digits at odd-numbered positions (1st, 3rd, 5th, ..., 11th). If you use 0-based indexing, this is the even-numbered positions (0th, 2nd, 4th, ... 10th).

Multiply the result from step 1 by 3.

Take the sum of digits at even-numbered positions (2nd, 4th, 6th, ..., 10th) in the original number, and add this sum to the result from step 2.

Find the result from step 3 modulo 10 (i.e. the remainder, when divided by 10) and call it M.

If M is 0, then the check digit is 0; otherwise the check digit is 10 - M.

*/
	int checkdig, x, step1 = 0, step2, step3 =0, M;
	char padded_word[12]; // because we are strcpy-ing the word (which has an additional '\0' character)
	char* p = padded_word; // because we can't do padded_word++ (understand why!)
	int num_missing_digs;
	
	size_t len = strlen(word); // okay because word is NULL terminated

	// check for size less than 11
	if (len < 11){
		num_missing_digs = 11 - len;
		for (int i = 0; i < num_missing_digs; i++, p++){
			*p = '0';
		}
	}
	strcpy(p, word); // the p++ in the last loop earlier already took our pointer to the next location
	printf("The user's padded word is %s\n", padded_word);
	
	for (int i = 0; i<11; i+=2){
		x = padded_word[i] - '0';
		step1+= x;
	}
	step2 = 3*step1;
	for (int i = 1; i<11; i+=2){
		x = padded_word[i]-'0';
		step3+= x; 
	}
	step3+= step2; 
	M = step3%10; 
	checkdig = (M==0) ? 0 : 10-M;
	return checkdig;
}

int main(int argc, char* argv[]){
	char inputword[MAX_LEN];
	read_string(stdin, inputword);
	printf("The user's word is %s\n", inputword);
	printf("The UPC check digit is %d\n", upc_check_digit(inputword));
	return 0;
}
