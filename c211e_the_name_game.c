/*
implement a computer program that can play Ms. Ellis' Name Game. You will recieve a name for input, and output the rhyme for that name. 
*/

	#include<stdio.h>
	#include<stdlib.h>
	#include<ctype.h>
	#include<string.h>
	#define MAX_LEN 50
	
	char* spl_inits[4] = {"-", " B", " F", " M"};
	
	void get_name_minus_start(char* s2, char* s){ //dest, src
		char s0 = tolower(s[0]);
		
		if((s0 == 'a') | (s0=='e') | (s0 =='i') | (s0 == 'o') | (s0 == 'u')){
			s2[0] = s0;
			strcpy(s2+1, s+1);  
		}else{ 
			strcpy(s2, s+1); 
		}
		
		return;
	}
	
	void sing_the_name_song(char* s2, char* s, char* flags){
	
		int p1 = flags[0]-48; 
		int p2 = flags[1]-48; 
		int p3 = flags[2]-48; 
		
		printf("\n\n*~*~*~*~*~*~*~\n\n\n");
		printf("%s, %s bo%s%s,\n", s, s, spl_inits[p1], s2); 
		printf("Bonana fanna fo%s%s,\n", spl_inits[p2], s2); 
		printf("Fee fy mo%s%s,\n", spl_inits[p3], s2); 
		printf("%s!\n", s);  
		printf("\n\n*~*~*~*~*~*~*~\n");
		
		return;
	}
	
	void process_given_str(char* s2, char* s, char* flags){//dest, src
		int l = strlen(s);
		if(l<2){
			printf("ERROR: Name must be at least 2 characters long!\n");
			return;
		}
		
		if(isalpha(s[0])){
			char X = tolower(s[0]); 
			if (X=='b') flags[0] = '0'; 
			if (X=='f') flags[1] = '0'; 
			if (X=='m') flags[2] = '0'; 
		}	
		
		for(int i = 1; i<l; i++){
			if(s[i]=='!'){
				s[i] = '\0';
				break;
			}
			
			if(isalpha(s[i])){
				s[i] = tolower(s[i]);
			}	
		}
		
		get_name_minus_start(s2, s);
		
		return;
	}
	
	int main(int argc, char* argv[]){
		char name[MAX_LEN];
		char name_tail[MAX_LEN];
		char flags[3] = "123";
		
		printf("Enter the name you want to rhyme!\n");
		fgets(name, MAX_LEN, stdin);
	
		process_given_str(name_tail, name, flags);	
	
		sing_the_name_song(name_tail, name, flags);
		
		return 0;
	}
