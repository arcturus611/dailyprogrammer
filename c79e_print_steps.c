	//r/dailyprogrammer challenge 79 easy 
	//step count
	
	#include<stdio.h>
	#include<stdlib.h>
	
	void print_steps(float a, float b, int steps){
		float delta = (b-a)/(steps-1);
		
		printf("%.2f, ", a);
		for (int i = 1; i<=steps-2; i++)
			printf("%.2f, ", a + delta*i); 
		printf("%.2f\n", b);
		
		return;
	}
	
	int main(int argc, char* argv[]){
		float a = atof(argv[1]);
		float b = atof(argv[2]);
		int steps = atoi(argv[3]);
		
		print_steps(a, b, steps);
		
		return 0;
	}
