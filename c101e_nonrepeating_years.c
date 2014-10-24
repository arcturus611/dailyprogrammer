//r/dailyprogrammer
//challenge 101 (easy)
//non repeating years

// compile: gcc -g -std=c99 -Wall c101e_nonrepeating_years.c -o c101e_nonrepeating_years
// run: ./c101e_nonrepeating_years
//	[start_year, end_year]

	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<ctype.h>
	
	struct in_data{
		char** years; 	
		int num_years;
	};	

	struct in_data create_array(FILE* in){
		char c; char given_years[2][5];
		struct in_data mydata = { {0} }; 

		while(isspace(c = fgetc(in))); //get rid of init whtspaces; out with c = '['
		int i = 0, j = 0;

		while((c= fgetc(in))!=']'){
			if (c==','){
				given_years[i][j] = '\0';
				i++;
				j = 0;
			}
			if((c-'0'>=0) && (c-'0'<=9)){
				given_years[i][j++] = c;
			}
		}
		given_years[i][j] = '\0';
	
		int first_year = atoi(given_years[0]);
		int last_year = atoi(given_years[1]); 
		int num_years = last_year - first_year + 1; 

		char** years = malloc(num_years*sizeof(char*));
		for (int i = 0; i<num_years; i++)
			years[i] = malloc(5*sizeof(char)); 

		strcpy(years[0], given_years[0]); 
		strcpy(years[num_years-1], given_years[1]); 

		for (int i = 1; i <(num_years-1); i++){
			sprintf(years[i], "%d", first_year+i); //http://stackoverflow.com/questions/228005/alternative-to-itoa-for-converting-integer-to-string-c
		}
		
		mydata.years = years; 
		mydata.num_years = num_years;

		return mydata; 
	}

	int q_cmp(const void* a, const void* b){
		return (*((char*)a) - *((char*) b));
	}

	void print_nonrepeating_years(struct in_data y){
		char curr_yr[5];
		int num_nr_yrs = 0;
		printf("The nonrepeating-character years are...\n"); 
		for (int i = 0; i< y.num_years; i++){
			strcpy(curr_yr, y.years[i]); 
			int num_chars = strlen(curr_yr);
			qsort(curr_yr, num_chars, sizeof(char), q_cmp);
			int unq_cnt = 0;
			for (int j = 0; j<num_chars-1; j++){
				if(curr_yr[j]!=curr_yr[j+1])
					unq_cnt++; 	
				else 
					break;
			}		
			if (unq_cnt==num_chars-1){
				printf("%s\n", y.years[i]); 
				num_nr_yrs++; 
			}
		}	
		if(num_nr_yrs==0)
			printf("No non-repeating years :(\n"); 	
		return;
	}

	int main(int argc, char* argv[]){
		struct in_data years = create_array(stdin);
		print_nonrepeating_years(years);
		return 0;
	}

