#include<stdio.h>
#include<stdlib.h>

#define MAX_CONTD_FRAC_SZ 10


void 
print_contd_frac(int a, int b)
{
	int num, den, rem;
	int quo[MAX_CONTD_FRAC_SZ]; 
	num = a;
	den = b;
	rem = 0;
	int iter = 0;
	while(rem!=1){
		quo[iter] = (int) num/den;
		rem = num%den;
		num = den;
		den = rem; 
		iter++;
	}
	quo[iter] = num; // for the last quotient. 
	
	printf("The continued fraction expression is:\n");
	for (int j = 0; j<=iter; j++){
		printf("%d, ", quo[j]);
	}
	printf("\n");
}


int 
main(void)
{
	int num, den;
	printf("We find continued fractions today! \n Enter your numerator and denominator: ");
	scanf("%d %d", &num, &den);
	print_contd_frac(num, den);
}
