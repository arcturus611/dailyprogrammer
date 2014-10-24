// compile with:
// gcc -std=c99 -g -Wall -o intermediate -lncurses intermediate.c
 
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
 
#define WIDTH 20
#define HEIGHT 20
 
char level[400] = {
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',
'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',
'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',
'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',
'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',
'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',
'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',
'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',
'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',
'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',
'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',
'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',
'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',
'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',
'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',
'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',
'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',
'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'
};
 
typedef struct _player {
int x;
int y;
int m_points;
int loot;
} Player;
 
void draw(Player *player) {
for (int y = 0; y < WIDTH; y++) {
for (int x = 0; x < WIDTH; x++)
mvaddch(y, x, level[y * WIDTH + x]);
}
mvaddch(player->y, player->x, '@' | A_BOLD);
mvprintw(21,0,"Movement Points: %d Loot: %d",
player->m_points, player->loot);
}
 
void check_hit(Player *old, Player *cur) {
if (level[cur->y * WIDTH + cur->x] == '-' ||
level[cur->y * WIDTH + cur->x] == '|') {
cur->y = old->y;
cur->x = old->x;
} else {
cur->m_points -= 1;
}
if (level[cur->y * WIDTH + cur->x] == '$') {
level[cur->y * WIDTH + cur->x] = '.';
cur->loot++;
}
}
 
void init_game(Player *player) {
srand(time(NULL));
int loot_placed = 0;
while (loot_placed < 100) {
int rand_x = rand() % 20;
int rand_y = rand() % 20;
if (level[rand_y * WIDTH + rand_x] == '.') {
loot_placed++;
level[rand_y * WIDTH + rand_x] = '$';
}
}
int rand_x, rand_y;
do {
rand_x = rand() % 20;
rand_y = rand() % 20;
} while (level[rand_y * WIDTH + rand_x] != '.');
player->x = rand_x;
player->y = rand_y;
player->m_points = 100;
player->loot = 0;
}
 
int do_input(Player *player) {
Player old = *player;
int ch = getch();
switch (ch) {
case 'q':
case 'Q':
return false;
case KEY_LEFT:
player->x -= 1;
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
check_hit(&old, player);
if (player->m_points <= 0)
return false;
return true;
}
 
int main(int argc, char *argv[]) {
Player player;
init_game(&player);
initscr();
noecho();
curs_set(FALSE);
cbreak();
keypad(stdscr, TRUE);
 
int running = TRUE;
draw(&player);
refresh();
while (running) {
if (!do_input(&player))
break;
clear();
draw(&player);
refresh();
}
endwin();
printf("Game Over! Score: %d\n", player.m_points);
return 0;
}
