//r/dailyprogrammer
//challenge 84 (easy)
//8/1/2012
//text adventure :-) Started Sept 10, 2014. Hope this gets big! 
// I'd also like to attempt the Sept 10 intermediate game challenge after this. 

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include<ctype.h>

#define MAX_X_COORD 100
#define MAX_Y_COORD 100
#define NUM_STATES 4
#define NUM_VERBS 8

char* str_lower(char* p){
	char* s = p; 
	for (; *p; p++) *p = tolower(*p); 
	return s; 
}

char state_of_mind[NUM_STATES][15] = {"sleepy", "cranky", "ask", "happy"}; 
//char state_of_mind[NUM_STATES][15] = {"sleepy", "hungry", "thirsty", "cranky", "happy", "sad", "confused", "confident", "angry", "friendly", "ask"};
char verb_type[NUM_VERBS][10]= {"look", "walk", "eat", "drink", "scratch", "roar", "bow", "stretch"};

struct person {
 int x, y; 
 char state[15]; 
};

struct person Snowy = {0, 0, {0}}; 
struct person Tiger = {0, 0, {0}}; 
struct person Wellington = {0, 0, {0}}; 
struct person treasure = {0, 0, {0}}; 
void describe_state(){// struct person* Snowy, struct person* Tiger, struct person* Wellington, struct person* treasure
	printf("You, Snowy, are currently located at %d, %d, and you are feeling %s\n", Snowy.x, Snowy.y, Snowy.state); 

	printf("The cat, Tiger, is currently located at %d, %d, and it is feeling %s \n", Tiger.x, Tiger.y, Tiger.state); 	

	printf("The ghost, Wellington, is currently located at %d, %d\n", Wellington.x, Wellington.y); 

	printf("The treasure is currently located at %d, %d\n", treasure.x, treasure.y); 	
}


void ask_act(){
	char ask_about[15];
	printf("\nWhat do you want to know? \n"); 
	scanf("%s", ask_about); 

	if (strcmp(str_lower(ask_about), "position")==0 || strcmp(ask_about, "state")==0)
		describe_state();
	else
		printf("Sorry, I don't know about %s\n", ask_about); 
	return; 
}

void cranky_act(){
	char x; 
	printf("You are feeling cranky, eh? Hungry? y/n: "); 
	scanf(" %c", &x); 
	if (x=='y'){
		printf("Aww, let us get you something\n"); 
		printf("...\n...\nYou just had a delicious meal\n"); 
		strcpy(Snowy.state, "happy"); 
	}
	else
		printf("Well, go get some sleep,then\n"); 
	return; 
}
	
void sleepy_act(){
	char x;
	printf("Do you want to sleep? y/n: ");
	scanf(" %c", &x); //http://stackoverflow.com/questions/13542055/in-c-how-to-do-scanf-for-single-char
	if (x=='y')
		printf("Good night!\n"); 
	else
		printf("Oh well.\n"); 
	return; 
}

void walk_act(){
	char news[10];
	printf("You must specify a direction");
	scanf(" %s", news); 
	if(strcmp(news, "north")==0 || strcmp(news, "n")==0)
		Snowy.y++; 
	else if (strcmp(news, "south")==0 || strcmp(news, "s")==0)
		Snowy.y--; 
	else if (strcmp(news, "east")==0 || strcmp(news, "e")==0)
		Snowy.x++; 
	else if (strcmp(news, "west")==0 || strcmp(news, "w")==0)
		Snowy.x--; 
	else
		printf(" Sorry, can only move north/south/east/west\n");
	return;
}
	

//idea from /u/skeeto's submission for challenge 178 (easy)
const struct table{
 const char* name; 
 void (*act)(); 
}ACTIONS[] = {
 {"sleepy", sleepy_act}, 
 {"cranky", cranky_act}, 
 {"ask", ask_act}, 
 {"walk", walk_act}
};

double dist_between(struct person* a, struct person* b){
	double dist; 
	dist = sqrt((double)(pow(a->x - b->x, 2) + pow(a->y - b->y, 2)));
	return dist; 
}

void set_up_adventure(){// struct person* Snowy, struct person* Tiger, struct person* Wellington, struct person* treasure
	//clear; //not possible in C?

	printf("\n It is dark and dank, and you're an american spy in a creaky old house in Russia. You are not sure where things are, so you stumble around, trying to find your way to the documents you've been asked to get your hands on. \n"); 
	srand(time(NULL)); 

	Snowy.x = rand()%MAX_X_COORD;  
	Snowy.y = rand()%MAX_Y_COORD; 
	strcpy(Snowy.state, state_of_mind[rand()%NUM_STATES]); 

	Tiger.x = rand()%MAX_X_COORD; 
	Tiger.y = rand()%MAX_Y_COORD; 
	strcpy(Tiger.state, state_of_mind[rand()%NUM_STATES]); 

	Wellington.x = rand()%MAX_X_COORD; 
	Wellington.y = rand()%MAX_Y_COORD; 

	treasure.x = rand()%MAX_X_COORD; 
	treasure.y = rand()%MAX_Y_COORD; 
}


void command_exec(char* command){
 	
	for (int i = 0; i<sizeof(ACTIONS)/sizeof(ACTIONS[0]); i++){
		if(strcmp(command, ACTIONS[i].name)==0){
			ACTIONS[i].act(command); 
		}
	}
}



void begin_exploring(){
	char command[15]; 

	while(1){
		printf(">: "); 
		scanf("%s", command); 
		if (strcmp(command, "quit")==0)
			break; 
		else{
			command_exec(command); 
		}

	}
}

int main(int argc, char* argv[]){
	set_up_adventure();
	describe_state(); 
	begin_exploring(); 
	return 0; 
}
