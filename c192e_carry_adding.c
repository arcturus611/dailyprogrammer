	//r/dailyprogrammer (easy) carry adding
	//challenge 192

	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#define MAX_INPUT_LEN 25
	#define MAX_DIGITS 10

	typedef struct _number_{
		int num;
		int digits[MAX_DIGITS];
		struct _number_* next;
	}Number;

	Number* nStart;
	Number* nCarry;
	Number* nSum;

	Number* create_new_number(int c){
		Number* nTemp = malloc(sizeof(Number));
		nTemp->num = c; 
		int dig_pos = 0;
		while(c){
			int d = c%10;
			nTemp->digits[dig_pos] = d;
			dig_pos++;
			c /= 10;
		}
	
		return nTemp;
	}

	void read_numbers(void){

		char numbers[MAX_INPUT_LEN]; 
		fgets(numbers, MAX_INPUT_LEN, stdin);
	
		numbers[strchr(numbers, '\n')-numbers] = '\0';
		int len = strlen(numbers);
	
		int curr_idx = 0, prev_idx = 0;
		Number* nCurr = NULL;
		Number* nLast = NULL;
	
		while(numbers[curr_idx]!='+') curr_idx++;
	
		while(curr_idx<=len){
			if((numbers[curr_idx]!='+') && (curr_idx!=len))
				curr_idx++;
			else{
				char curr_num[MAX_INPUT_LEN] = {'0'};
				strncpy(curr_num, &numbers[prev_idx], curr_idx-prev_idx);
			
				if(nStart==NULL){
					nStart = create_new_number(atoi(curr_num));	
					nCurr = nStart;
				}else{
					nLast = nCurr;
					nLast->next = create_new_number(atoi(curr_num));
					nCurr = nCurr->next;
				}
			
				curr_idx++;
				prev_idx = curr_idx;
			}
		}
	
		return;
	}

	void calculate_carry(void){
		Number* nCurr = malloc(sizeof(Number));
		int carry = 0;
	
		for(int i = 0; i<MAX_DIGITS; i++){ //because you only add digits 0 to MAX_DIGITS-1 for carry
			nCurr = nStart;
			int sum = 0;
		
			while(nCurr){
				sum+=(nCurr->digits[i]);
				nCurr = nCurr->next;
			}
			sum+=carry;

			carry = sum/10;
		
			if(i<MAX_DIGITS-1){
				nCarry->digits[i+1] = carry;
			}
			
			sum%=10;
			nSum->digits[i] = sum;
		}

		return;
	}

	void display_carry_addition(void){
		Number* nCurr = nStart;
		int i;
	
		while(nCurr){	
			for(i = MAX_DIGITS-1; i>=0; i--){
				if(nCurr->digits[i]!=0)
					break;
				else
					printf(" ");
			}
			for(int j = i ; j>=0; j--)
				printf("%c", nCurr->digits[j]+48); //digit to char
			printf("\n");
			nCurr = nCurr->next;
		}
		printf("----------\n");
	
		for(i = MAX_DIGITS-1; i>=0; i--){
			if(nSum->digits[i]!=0)
				break;
			else
				printf(" ");
		}
		for(int j = i ; j>=0; j--)
			printf("%c", nSum->digits[j]+48); //digit to char
		printf("\n");
	
		printf("----------\n");
		for(i = MAX_DIGITS-1; i>=0; i--){
			if(nCarry->digits[i]!=0)
				break;
			else
				printf(" ");
		}
		for(int j = i ; j>=0; j--)
			printf("%c", nCarry->digits[j]+48); //digit to char
		printf("\n");
		return;		
	}

	int main(int argc, char* argv[]){
		nStart = NULL;
		nCarry = malloc(sizeof(Number));
		nSum = malloc(sizeof(Number));
		
		read_numbers();
		calculate_carry();
		display_carry_addition();
		return 1;
	}
