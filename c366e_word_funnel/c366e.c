#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define MAXLEN 100

bool funnel_test(char* str1, char* str2){
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int misses = 0;
	
	if(len2!=(len1-1)) return 0;
	
	char* p = strchr(str1, *str2);
	char* first_match = p;
	if (p== NULL || (p!= str1 && p!= str1 + 1)) return 0;

	for(;(*p)!='\0' && (*str2)!= '\0'; p++, str2++){
		if((*p)!= *str2){
			if(first_match==str1){
				if (misses == 0){
					misses++;
					str2--;
				}else return 0;
			} else if (first_match== str1+1){
				return 0;
			}
		}
	}
	
	return 1;
}

int main(int argc, char* argv[]){
	char* str1 = malloc(MAXLEN*sizeof(*str1));
	scanf("%s", str1);
	char* str2 = malloc(MAXLEN*sizeof(*str2));
	scanf("%s", str2); 
	printf("The input string is %s\n", str1); 
	printf("The second string is %s\n", str2);
	
	printf(funnel_test(str1, str2)? "Yes, funnel word\n" : "No not a funnel word\n"); 
	
	free(str1);
	free(str2);
	return 0;
}
