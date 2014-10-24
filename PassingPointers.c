// Passing pointers as arguments to a function

#include<stdio.h>

int min_max(double * min , double * max , int size , double a[]){                                                                       
int
i;                                                                                                                                

printf("Inside min_max, before anything: Values: \n%lg\t%lg\n Addresses: %p\t%p\n", *min, *max, min, max);                                                                                                   

min = &a[0];                                                                                                                          
max = &a[0];                                                                                                                          

printf("After initializing to &a[0], addresses are: %p\t%p\n", min, max); 

for (i = 1 ; i < size ; i++) {                                                                                                        
 if (a[i] > *max)                                                                                                                    
  max = &a[i];                                                                                                                      
 else if (a[i] < *min)                                                                                                               
  min = &a[i];                                                                                                                      
 }                                                                                                                                     
 printf("Inside min_max, after everything: Values: \n%lg\t%lg\n, Addresses: %p\t%p\n", *min, *max, min, max);                                                                                                   
 return 0;                                                                                                                             
}

int correct_min_max(double** min, double** max, int size, double a[]){
 printf("Inside correct fn\n");
 *min = &a[0]; 
 *max = &a[0]; 
 
 for (int i = 0; i<size; i++){
  if(**min>a[i]){ 
   *min = &a[i]; 
  }
  if(**max<a[i]){
   *max = &a[i];
  }
 
 } 

 return 0; 
}

void main(){
int m = 0;
double *min = &m, *max = &m; 
printf("Before min_max: Values are: %lg \t %lg\n and addresses are: %p\t %p\n", *min, *max, min, max);
double a[10] = {1, 2, 4, 5, 6, 2, 7, 8, 12, -9};
min_max(min, max, 10, a); 
printf("Outside min_max: Values: %lg\t %lg\n and addresses: %p\t%p\n", *min, *max, min, max); 
printf("Entering correct_min_max\n");
correct_min_max(&min, &max, 10, a); 
printf("Outside correct_min_max: Values: %g\t%lg \n", *min, *max); 
}

