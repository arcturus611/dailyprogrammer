//r/dailyprogrammer
//Hard (179)
//Modify rogue game
//Added the new features to /u/cooper6581's submission

/* Bonus treasures have different points. They start being visible after differetn wait times. They stay visible for a time inversely proportional to their associated points. As of now, we do not generate new bonus treasures after any expire (a treasure is said to 'expire' when its value-points become zero)*/

#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#include<time.h>
#include<stdbool.h>

#define WIDTH 20

#define MAX_NUM_WALLS 7

#define MAX_TREASURE_COUNT 100 

#define MAX_MOVES 100

#define MAX_BONUS_VALUE 50
#define MIN_BONUS_VALUE 10 //it's a bonus, it has gotta be >1

#define MAX_BONUS_WAIT_TIME 20 // wait time of 1000 seems too long
#define MAX_BONUS_COUNT 5

#define MIN_BONUS_LIFE 20

#define TORCH_RANGE 3

struct Player{
 int x, y; 
 int moves; 
 int score; 
};

struct Bonus{
 int x, y; 
 int wait_time; //time before visibility 
 int value; 
 int life_points; //MIN_BONUS_LIFE + a value inversely proportional to the value (larger value bonus_treasures don't last too long)
};

char world[WIDTH][WIDTH]; 

int min(int x, int y){
 return (x<y? x :y);
}

int max(int x, int y){
 return (x>y?x:y); 
}

void init_game(struct Player* player, struct Bonus* bonus){
 srand(time(NULL)); 

 int x_rand, y_rand;

 //---Draw world
 for(int i = 1; i<WIDTH-1; i++){
  for(int j = 1; j<WIDTH-1; j++){
   world[i][j] = '.';
  }
 }

 for(int i = 0, j = 0; j<WIDTH; j++)
  world[i][j] = '|'; 
 
 for (int j = 0, i= 0; i<WIDTH; i++)
  world[i][j] = '_'; 

 for (int i = WIDTH-1, j= 0; j<WIDTH; j++)
  world[i][j] = '|'; 
 
 for (int i = 0, j = WIDTH-1; i<WIDTH; i++)
  world[i][j] = '-'; 

//end draw world

// Put walls
 int num_walls = 0;
 while(num_walls< MAX_NUM_WALLS){
  x_rand = 1+ rand()%(WIDTH-2);
  y_rand = 1+ rand()%(WIDTH-2); 
  if (world[x_rand][y_rand]== '.'){
   world[x_rand][y_rand] = '*';
   num_walls++; 
  }
 }

// end walls
 
// Put treasures
 int num_treasures = 0; 

 while(num_treasures < MAX_TREASURE_COUNT){
  x_rand = rand()%WIDTH; 
  y_rand = rand()%WIDTH; 
  if(world[x_rand][y_rand]=='.'){
   world[x_rand][y_rand] = '$'; 
   num_treasures++; 
  }
 }
// initialize array of bonus_treasures 
 int num_bonus_treasures = 0; 

 while(num_bonus_treasures < MAX_BONUS_COUNT){
  x_rand = rand()%WIDTH; 
  y_rand = rand()%WIDTH; 
  if (world[x_rand][y_rand] == '.'){
   bonus[num_bonus_treasures].x = x_rand; 
   bonus[num_bonus_treasures].y = y_rand; 
   bonus[num_bonus_treasures].wait_time = rand()%MAX_BONUS_WAIT_TIME + 1; 
   bonus[num_bonus_treasures].value = MIN_BONUS_VALUE + rand()%(MAX_BONUS_VALUE - MIN_BONUS_VALUE + 1); 
   bonus[num_bonus_treasures].life_points = MIN_BONUS_LIFE + 500/bonus[num_bonus_treasures].value; 
   num_bonus_treasures++; 
  }
 }

// initialize player
 x_rand = rand()%WIDTH; 
 y_rand = rand()%WIDTH; 
 player->x = x_rand; 
 player->y = y_rand; 
 player->moves = MAX_MOVES; 
 player->score = 0;
}

void update_bonus(struct Bonus* bonus){
 for (int i = 0; i<MAX_BONUS_COUNT; i++){ 
  if(bonus[i].wait_time>0) 
   bonus[i].wait_time--; 
  else if (bonus[i].life_points>0){
   world[bonus[i].x][bonus[i].y] = 'B'; 
   bonus[i].life_points--; 
  }
  else if (bonus[i].life_points==0)
   world[bonus[i].x][bonus[i].y] = '*';
 }
}

void draw(struct Player* player, struct Bonus* bonus){
 mvaddch(player->y, player->x, '@'); 

 for (int i = -TORCH_RANGE; i<=TORCH_RANGE; i++){
  for (int j = -TORCH_RANGE; j<=TORCH_RANGE; j++){
    if (abs(i)+abs(j)<=TORCH_RANGE){
     int boundary_x = min(max(player->x + i, 0), WIDTH-1); 
     int boundary_y = min(max(player->y + j, 0), WIDTH-1);
     if (!(i==0 && j==0)){
      mvaddch(boundary_y, boundary_x, world[boundary_x][boundary_y]);
     }
    }

  }
 }

 mvprintw(WIDTH + 1,0,"Movement Points: %d, Bonus life points left: %d, %d, %d, %d, %d. Score: %d out of a maximum score of %d", player->moves, bonus[0].life_points, bonus[1].life_points, bonus[2].life_points, bonus[3].life_points, bonus[4].life_points, player->score, MAX_TREASURE_COUNT + bonus[0].value + bonus[1].value + bonus[2].value + bonus[3].value + bonus[4].value);
 
 mvprintw(WIDTH + 3, 0, "B: Bonus treasure with unknown value and limited unknown life");
 mvprintw(WIDTH + 4, 0, "*: You lose movement points with zero increase in score"); 
}

void check_hit(struct Player* old, struct Player* curr, struct Bonus* bonus){
 if (curr->x < WIDTH-1 && curr->x >0 && curr->y>0 && curr->y< WIDTH-1){
  curr->moves--; 
  if(world[curr->x][curr->y]=='*'){
   curr->x = old->x; 
   curr->y = old->y; 
  } 
 }
 else{
  curr->x = old->x; 
  curr->y = old->y; 
 } 

 if (world[curr->x][curr->y] == '$') {
  world[curr->x][curr->y] = '.';
  curr->score++;
 }

 for(int i = 0; i<MAX_BONUS_COUNT; i++){
  if (world[curr->x][curr->y] == 'B' && curr->x == bonus[i].x && curr->y == bonus[i].y){
   curr->score = curr->score + bonus[i].value; 
   bonus[i].life_points = 0; 
   world[curr->x][curr->y] = '.';
  } 
 }
  
}

int do_input(struct Player* player, struct Bonus* bonus){
 struct Player old = *player; 
 int ch = getch(); 
 switch(ch){
  case 'q':
  case 'Q': 
   return false;
  case KEY_LEFT: 
   (player->x)--;
   break;
  case KEY_RIGHT:
   player->x += 1;
   break;
  case KEY_UP:
   player->y -= 1;
   break;
  case KEY_DOWN:
   player->y += 1;
   break;
 }

 check_hit(&old, player, bonus); 
 if (player->moves<=0)
  return false;
 return true; 
}

int main(int argc, char* argv[]){
 struct Player player; 
 struct Bonus bonus[MAX_BONUS_COUNT]; 
 init_game(&player, bonus); 

 initscr();
 noecho();
 curs_set(FALSE);
 cbreak();
 keypad(stdscr, TRUE);

 draw(&player, bonus); 
 refresh(); 

 bool running = true; 
 while(running){
  update_bonus(bonus); 
  if(!do_input(&player, bonus)) 
   break;
  clear(); 
  refresh(); 
  draw(&player, bonus);
 }
 
 endwin(); 
 printf("Game over! Score is : %d out of a maximum score of %d\n", player.score, MAX_TREASURE_COUNT + bonus[0].value + bonus[1].value + bonus[2].value + bonus[3].value + bonus[4].value);
 if ((float)player.score/(MAX_TREASURE_COUNT + bonus[0].value + bonus[1].value + bonus[2].value + bonus[3].value + bonus[4].value)<0.5)
   printf("You need more practice!\n"); 
 else
   printf("Well done!\n"); 
 
 return 0;
}
