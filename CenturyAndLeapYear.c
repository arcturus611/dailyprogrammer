//r/dailyprogrammer
//challenge 27 (easy)
//Output century of given year, and also if it's a leap year or not

#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv){
 int y = atoi(argv[1]);
 printf("Century: %d, leap year: %s\n", y/100+(y%100?1:0), ((y%4==0)?((y%100==0)?(y%400==0?"yes":"no"):"yes"): "no")); 
 return 0;
}
