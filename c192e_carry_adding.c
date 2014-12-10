//r/dailyprogrammer (easy) carry adding
//challenge 192

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_INPUT_LEN 25

typedef struct _number_{
	int num;
	int digits[6];
	struct _number_* next;
}Number;

Number* nStart;
Number* nCarry;

Number* create_new_number(int c){
	Number* nTemp = malloc(sizeof(Number));
	printf("c is = %d\n", c);
	nTemp->num = c; 
	int dig_pos = 0;
	while(c){
		int d = c%10;
		nTemp->digits[dig_pos] = d;
		dig_pos++;
		c /= 10;
	}
	for(int i = 0; i<dig_pos; i++)
		printf("~~Digit %d is %d\n", i, nTemp->digits[i]);
	return nTemp;
}

void read_numbers(void){
	char numbers[MAX_INPUT_LEN]; 
	fgets(numbers, MAX_INPUT_LEN, stdin);
	
	numbers[strchr(numbers, '\n')-numbers] = '\0';
	int len = strlen(numbers);
	
	int curr_idx = 0, prev_idx = 0;
	Number* nCurr;
	
	while(numbers[curr_idx]!='+') curr_idx++;
	
	while(curr_idx<=len){
		if((numbers[curr_idx]!='+') && (numbers[curr_idx]!='\0'))
			curr_idx++;
		else{
			char curr_num[MAX_INPUT_LEN];
			strncpy(curr_num, &numbers[prev_idx], curr_idx-prev_idx);
			
			if(nStart==NULL){
				nStart = create_new_number(atoi(curr_num));	
				nCurr = nStart->next;
			}else{
				nCurr = create_new_number(atoi(curr_num));
				nCurr = nCurr->next;
			}
			
			curr_idx++;
			prev_idx = curr_idx;
		}
	}
	
	/*
	/////
	FILE* fp = stdin;
	
	int c = fgetc(fp) - 48; //zero ascii value is 48
	nStart = create_new_number(c);
	
	Number* nCurr = nStart->next;
	printf("Initialized nStart: %d\n", nStart->num);	
	while(fgetc(fp)!='\n'){
		c = fgetc(fp);
		nCurr = create_new_number(c);
		nCurr = nCurr->next;
	}
	*/

}

int main(int argc, char* argv[]){
	nStart = NULL;
	nCarry = NULL;
	
	read_numbers();
//	display_carry();
}
