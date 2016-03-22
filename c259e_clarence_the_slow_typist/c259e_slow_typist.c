	/* Your task is to write a program that calculates the distance Clarence must move his finger to type in arbitrary IP addresses. */
	/* For compiling: gcc -std=c99 -g -o c259e_slow_typist.bin c259e_slow_typist.c -lm */
	/* Don't forget to link math lib in the end!*/
	
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<math.h>
	#define MAX_LEN_IP 15
	
	char keys[] = {"123456789.0"};
	
	int* get_coords(char c, int* coords){
		
		int p = strchr(keys, c) - keys;
		
		/* Because of how the keypad is built, we can get coordinates easily like this */
		*coords = p/3;
		*(coords + 1) = p%3;
		
		return coords; 
	}
	
	float euc_dist(int* p1, int* p2){
	
		/* Note that sqrt returns double, if you don't use float, you get truncated value */
		float d = sqrt(	 pow(p1[0] - p2[0], 2) + pow(p1[1] - p2[1], 2)	);
		
		return d;
	}
	
	float calc_dist(char* str){
		char* prev = str; 
		char* curr = str + 1; 
		float d = 0;
		
		/* If you don't malloc here, segmentation fault. 
		Want to be able to do this by prev_coords[2] and curr_coords[2]
		since malloc seems silly to use here */
		int* prev_coords = (int *)malloc(2*sizeof(int));
		int* curr_coords = (int* )malloc(2*sizeof(int));
		
		/* Note that the last char is NULL, not RETURN since fgets 
		stops at RETURN without taking it */
		while( (*curr)!= '\0' ){
			prev_coords = get_coords(*prev, prev_coords);
			curr_coords = get_coords(*curr, curr_coords); 		
			
			d = d + euc_dist( prev_coords, curr_coords );
			
			prev++;
			curr++;
		}
		
		
		return d;
	}
	
	int main (int argc, char* argv[]){
			
		char* ip_add = (char *)malloc( MAX_LEN_IP*sizeof(char) );
		ip_add = fgets( ip_add, MAX_LEN_IP, stdin );
		
		float total_dist = calc_dist(ip_add);
			
		printf("Clarence moves %.2f cm\n", total_dist);
			
		return 0;
	}
