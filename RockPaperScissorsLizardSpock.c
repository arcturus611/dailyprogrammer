//r/dailyprogrammer
//Challenge 159 (easy)
//rock paper scissors spock lizard

#include<stdio.h>
#include<stdlib.h> //for rand
#include<time.h> //for time
#include<string.h>
#include<ctype.h>

#define MAX_GAMES 5

int player_choice, machine_choice; 
int player_loss_count = 0, player_win_count = 0, tie_count = 0;

char* results_table[25] = {"T", "L", "crushes", "crushes", "L", "covers", "T", "L", "L", "disproves", "L", "cuts", "T", "decapitates", "L", "L", "eats", "L", "T", "poisons", "vaporizes", "L", "smashes", "L", "T"};

char* choices[5]= {"Rock", "Paper", "Scissors", "Lizard", "Spock"}; 

void start_game(){
 printf("\n-----------------------------------------------\n----ROCK---PAPER---SCISSORS---SPOCK---LIZARD---\n-----------------------------------------------\n\n"); 
}

void play_game(){

 do{
 printf("Choose from: Rock (0), Paper (1), Scissors (2), Lizard (3), Spock (4): "); 
 scanf("%d", &player_choice);
 if(player_choice<0 || player_choice>4){
  printf("\nSorry, invalid choice!\n"); 
 }
 }while(player_choice<0 || player_choice>4); 
 
 printf("\nYou chose %s\n", choices[player_choice]); 
 srand(time(NULL)); 
 machine_choice = rand()%5; 
 printf("Machine chose %s\n", choices[machine_choice]); 

}

void who_wins(){
 int result_index = player_choice*5+machine_choice;
 char* result = results_table[result_index]; 

 if(strcmp(result, "L")==0){
  player_loss_count++;
  result_index = machine_choice*5+player_choice; 
  result = results_table[result_index];
  printf("\n%s %s %s\n", choices[machine_choice], result, choices[player_choice]);
  printf("You lose!\n");
 }
 else if (strcmp(result, "T")==0){
  tie_count++;
  printf("\nIt's a tie!\n"); 
 }  
 else{
  player_win_count++;
  printf("\n%s %s %s\n", choices[player_choice], result, choices[machine_choice]);
  printf("You win!\n");  
 }
}

int main(int argc, char** argv){ 
 start_game(); 
 char continue_play; 
 float player_loss_percent, player_win_percent, tie_percent;
 
 for(int count=0; count<MAX_GAMES; count++){
  play_game(); 
  who_wins();
  if (count==MAX_GAMES-1){
   printf("\nDo you wish to continue playing? y/n: ");
   scanf("%*[ \n\t]%c", &continue_play);// http://stackoverflow.com/questions/13542055/in-c-how-to-do-scanf-for-single-char
   if (tolower(continue_play)=='y'){
    count = -1;
   }
  }
 }
 
 int total_count = player_loss_count+player_win_count +tie_count;
 player_loss_percent = 100*((float)player_loss_count/total_count);
 player_win_percent = 100*((float)player_win_count/total_count);
 tie_percent = 100-(player_win_percent+player_loss_percent); 

 printf(" You won %d (%.1f%%) of %d games, lost %d (%.1f%c) and tied %d (%.1f%c)... ", player_win_count, player_win_percent, total_count, player_loss_count, player_loss_percent, '%', tie_count, tie_percent, '%');  

 if(player_win_percent>50)
  printf("Well done, congratulations!\n"); 
 else if (player_win_percent<50)
  printf("Boohoo!\n"); 
 else
  printf("Ah, you just got lucky\n"); 

}
