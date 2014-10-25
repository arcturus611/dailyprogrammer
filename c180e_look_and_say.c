//r/dailyprogrammer
//challenge 180 (easy)
//look and say
// compile: gcc -g -std=c99 -Wall look_and_say.c -o look_and_say 
// run: ./look_and_say string_seed num_iterations 
// for example: ./look_and_say 145 6

	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<math.h>

	char** look_and_say(char* seed, int iter){
		
		int len = strlen(seed); 
		char** seed_output = malloc(iter*sizeof(char*)); //https://www.youtube.com/watch?v=E8Yh4dw6Diw Fantastic explanation on pointer returns from functions. 
		
		for (int i = 0; i<iter; i++){
			
			seed_output[i] = malloc(2*len*sizeof(char)); // don't forget to update len at the end of the loop

			int k = 0; 
			int start_idx = 0; 
			int end_idx = 0; 

			for(int j = 0; j<len; j++){// cover the entire length of input seed
				if (j < len-1){
					if(seed[j]!=seed[j+1]){
						end_idx = j; 
						seed_output[i][k] = '0' + end_idx-start_idx+1; //#chars btwn start & end, incl both
						k++; 
						seed_output[i][k] = seed[j]; //the char itself
						k++; 
						start_idx = j+1;
					}
				}else if (j== (len-1)){
						end_idx = len-1; 
						seed_output[i][k] = '0' + end_idx - start_idx + 1; 
						k++; 
						seed_output[i][k] = seed[j]; 
						k++;							
				}		
			}

			seed_output[i][k] = '\0';							
			seed = seed_output[i]; 
			len = k; 	
  		}

		return seed_output; 

	}

	void print_pattern(char** table, char* seed, int iter){
	
		printf("The table is\n"); 	
		printf("%s\n", seed); 
		for (int i = 0; i <iter; i++){
			printf("%s\n", table[i]); 
		}
		return;
	}

	int main(int arg, char* argv[]){
 		
		char* seed = argv[1]; 
		int iter = atoi(argv[2]); 

		char** seed_output = look_and_say(seed, iter);

		print_pattern(seed_output, seed, iter);

		return 0;
	}
