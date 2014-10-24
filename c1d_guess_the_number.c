	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<time.h>

	#define INIT_FIRST 1
	#define INIT_LAST 100


	int guess_the_number(int first, int last){
	    int range = last-first + 1;
	    int guess = first + rand()%range;
	    char user_resp;
	    
	    printf("My guess is %d.", guess); 
	    printf("Please respond with L, H, or E: ");
	    scanf(" %c", &user_resp); 
	    
	    switch(user_resp){
		case 'L':
		    return guess_the_number(guess+1, last); 
		case 'H':
		    return guess_the_number(first, guess-1);
		case 'E':
		    return guess;
		default:
		    printf("Not a valid response\n");
		    return -1; 
	    }
		    
	}

	int main(int argc, char* argv[])
	{   
	   srand(time(NULL)); 
	   printf("The final guess is: %d\n", guess_the_number(INIT_FIRST, INIT_LAST));
	   return 0;
	}


