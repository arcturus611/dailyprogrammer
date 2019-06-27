/* 
dailyprogrammer Challenge 223 [Easy]: return "degree" of a garland word (example, garland(onion) = 2; garland(alfalfa) = 4; garland(dog) = 0)
Took WAY longer than anticipated. 
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXLEN 100

int degree(const char* str){
	int deg = 0;
	int index1 = 0;
	char* curr = strchr(str+1, str[index1]);
	
	if (curr!=NULL){	
		while((*curr)!='\0'){
			if ((*curr)==str[index1]){
				deg++;
				index1++;
				curr++;	
			}else{
				deg = 0; 
				index1 = 0;
				curr++; 
				if ((*curr)!='\0'){
					curr = strchr(curr, str[index1]); 
				}else{ 
					return deg;
				}
			}
		}
	}
	
	return deg;
}

int main(int argc, char* argv[]){
	printf("Welcome to Challenge 223[Easy]! Please enter th string to be checked for the garland property!");
	char* str = malloc(sizeof(*str));
	scanf("%s", str);

	printf("The degree of the input word %s is %d\n", str, degree(str));
	return 0;
}
