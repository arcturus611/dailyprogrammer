//r/dailyprogrammer
//challenge 4
//random password generator
//Aug 23

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define NUM_SEEDS 14
#define ALPHABET_SIZE 66

int password_alphabet_seed[NUM_SEEDS] = {43, 1, 45, 1, 48, 10, 61, 1, 65, 26, 95, 1, 97, 26};

char password_alphabet[ALPHABET_SIZE];

void create_password_alphabet(){
 int j, seed, seed_set_size;
 int idx = 0;  

 for (int i = 0; i<NUM_SEEDS; i+=2){
  seed = password_alphabet_seed[i]; 
  seed_set_size = password_alphabet_seed[i+1]; 
  for (j = 0; j<seed_set_size; j++){
   password_alphabet[idx+j] = seed+j; 
  }
  idx = idx+seed_set_size; 
 }
 
 printf("Password alphabet verification:\n"); 
 for (int i= 0; i<idx; i++){
  printf("%c", password_alphabet[i]); 
 }
 printf("\n");
}

#define SWAP(a, b) if(a^b){a^=b; b^=a; a^=b;}

void shuffle(char* s){
 int i, n;
 int len = strlen(s);
 for(i = len-1; i>0; i--){
  n = rand()%(i+1); 
  SWAP(s[i], s[n]); 
 }
}

void generate_passwords(int n, char** passwords){
 
 int len_password, j; 

 for (int i = 0; i<n; i++){
  printf("\n What is the length of your password %d?:", i+1); 
  scanf(" %d", &len_password);
  passwords[i] = malloc(len_password*sizeof(char));

  shuffle(password_alphabet); 

  for(j = 0; j<len_password; j++){
   passwords[i][j] = password_alphabet[rand()%ALPHABET_SIZE]; 
  }
 }

}

int main(int argc, char** argv){
 srand(time(NULL)); 
 create_password_alphabet(); 

 int num_passwords; 
 printf("How many passwords do you want to generate?: "); 
 scanf(" %d", &num_passwords); 
 char** passwords; 
 passwords = malloc(num_passwords*sizeof(char*)); 

 generate_passwords(num_passwords, passwords); 

 for (int i=0; i<num_passwords; i++)
  printf("%s \n", passwords[i]);
 
 return 0; 
}
