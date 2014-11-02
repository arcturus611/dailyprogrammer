	//r/dailyprogrammer challenge easy 35
	//right triangle print
	
	#include<stdio.h>
	#include<stdlib.h>
	
	void print_line(int num_ints, int max_line_num){
		for(int i = num_ints-1; i>=0; i--)
			printf("%d ", max_line_num-i);
		printf("\n");
		return;
	}
	
	void print_right_triangle(int N){
		int max_line_num = 1; //in the first line, max int is 1
		int inc = 2;
		while(max_line_num<=N){
			max_line_num+=inc;
			inc++;
		}
		inc--;
		max_line_num-=inc;
		inc--;
		
		printf("\n");
		while(max_line_num>=1){
			print_line(inc, max_line_num);
			max_line_num-=inc;
			inc--;
		}
		
		return;
	}
	
	int main(int argc, char* argv[]){
		int N = atoi(argv[1]);
		print_right_triangle(N);
		return 0;
	}	
