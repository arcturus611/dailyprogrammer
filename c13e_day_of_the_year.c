#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NUM_MONTHS 12

char* month_names[NUM_MONTHS] = {"january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december"}; 
 
int num_days[NUM_MONTHS] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int calc_day(char* month, int date){
	int day = 0; int i, j;	

	for (i = 0; i<NUM_MONTHS; i++){
		if (strcmp(month, month_names[i])==0){
			break;
		}
	}
	
	if (i==NUM_MONTHS){
		printf("Sorry, invalid month\n"); 
		return -1;
	}
	
	for (j = 0; j<i; j++)
		day += num_days[j];
	
	day = day + date;
	
	return day;
}

int main(int argc, char* argv[]){
	char* month = argv[1]; 
	int date = atoi(argv[2]); 

	int day = calc_day(month, date);
	if (day>0)
		printf("Number of the day for %s %d is %d\n", month, date, day);
	 
	 
	return 0;
}
