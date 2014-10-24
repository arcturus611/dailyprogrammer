#include<stdio.h>
#include<string.h>

void separate_duplicates(char* inp){
	int orig_len = strlen(inp);
	int j;char temp; 
	int len_first_arr = orig_len;

	for(int i = 1; i<len_first_arr; i++){
		if(inp[i]==inp[i-1]){
			temp = inp[i];
			for (j = i; j<orig_len-1; j++){
				inp[j] = inp[j+1];
			}
			inp[orig_len-1] = temp;
			len_first_arr--; 
			i--; // because you want to make sure that the next char is not a duplicate (by checking for it too)
		}
	}

	printf("String 1: "); 
	for (int i = 0; i<len_first_arr; i++)
		printf("%c", inp[i]); 

	printf("\n"); 
	printf("String 2: "); 
	for (int i = 0; i <orig_len-len_first_arr; i++)
		printf("%c", inp[i+len_first_arr]); 

	printf("\n"); 

}

int main(int argc, char* argv[]){
	separate_duplicates(argv[1]);
	return 0;
}
