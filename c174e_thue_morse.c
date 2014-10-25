// r/DailyProgrammer
// Thue-Morse sequence

#include<stdio.h>
#include<math.h>

void thueMorse(){

int tm[100], lastP, nextP, step, n, len, currP, i; 
char tmP[100]; 

tm[0] = 0; 
tmP[0] = tm[0]+'0';
printf("\n%c\n", tmP[0]); 
tm[1] = 1; 
tmP[1] = tm[1]+'0';
lastP= 1;
currP=lastP+1; 

for (len = 0; len<=lastP; len++){
 printf("%c", tmP[len]); 
}
printf("\n");

for (step=2; step<=6; step++){
 nextP = currP*2;
 for (len = currP; len<nextP; len++){
  if(len%2){
   n = (int)((len-1)/2);
   tm[len] = 1-tm[n]; 
  }
  else{
   n = (int)(len/2);
   tm[len] = tm[n]; 
  }
 tmP[len] = tm[len]+'0';
 }

for (i = 0; i<nextP; i++)
 printf("%c", tmP[i]); 

 currP = nextP; 
 lastP = currP-1;

 printf("\n");
}

}


int main(int argc, char** argv){

thueMorse(); 

return 0;

}

/*
3-- 69
4-- 6996
5-- 69969669
6-- 6996966996696996



*/
