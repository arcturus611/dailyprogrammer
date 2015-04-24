/*
You, the Ogre, will navigate a swamp. If you find a path you will display the solution of all the spaces the ogre will occupy to get to his gold. 
Use a "&" symbol to show the muddy path created by the ogre to reach his gold. If there is no path at all then you will output "No Path"
*/

// Resource used: http://www.eecs.yorku.ca/course_archive/2006-07/W/2011/Notes/BFS_part2.pdf and 
// my own code for Breadth First Search written for Tim Roughgarden's fantastic Algo Design class on coursera. 

// Implementing the maze solver for a gold-seeking ogre (hehe) using breadth-first search. 

	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<ctype.h>
	#include "../Algorithms_Design_And_Analysis/queue.h"
	#define MAX_LINE_LEN 100
	
	struct node{
		char c; 
		int idx; //y+w*x : used for enqueueing 
		int prev; 
		
		int x; 
		int y; 
		int explored; 
	};
	
	struct node** init_maze(int h, int w){
		//malloc for maze_node array
		int num_nodes = h*w;
		int node_idx;

		//Linear array of pointers to nodes representing each location in the maze.
		//We're making it linear because it's easier to then talk about their indices.
		struct node** X = (struct node **)malloc(num_nodes*sizeof(struct node *)); 
		for(int i = 0; i<h; i++){
			for(int j = 0; j<w; j++){
				node_idx = j+i*w; 
				X[node_idx] = (struct node *)malloc(sizeof(struct node));
				X[node_idx]->x = i; 
				X[node_idx]->y = j; 
				X[node_idx]->prev = -1; //invalid prev for init 
				X[node_idx]->explored = 0; //unexplored
			}
		}

		//Read the maze		
		char line[MAX_LINE_LEN];
		char* p; 
		
		FILE* fp = fopen("ogre_in_a_maze.txt", "r"); 
		for(int i = 0; i<h; i++){
			fgets(line, MAX_LINE_LEN, fp);
			p = line;
			while(isspace(*p)) p++; 
			for(int j = 0; j<w; j++){
				node_idx = j+i*w; 
				X[node_idx]->c = *p++;
			}
		}
		fclose(fp); 
		
		return X; 
	}
		
	int is_new_loc_valid(struct node** M, int loc, int h, int w){
		if(loc<0 | loc>(h*w-1)) return 0; 
	
		int tl_x = M[loc]->x;
		int tl_y = M[loc]->y;	
		
		if(tl_x<0 | tl_x>(w-2)) return 0;
		if(tl_y<0 | tl_y>(h-2)) return 0; //not within limits of the swamp
		
		int tl_c = M[loc]->c; 
		int tr_c = M[loc+1]->c;
		int bl_c = M[loc+w]->c; 
		int br_c = M[loc+w+1]->c; 
		if(tl_c=='&' & tr_c=='&' & bl_c=='&' & br_c=='&') return 0; //block under consideration has been visited before
		
		if(tl_c=='O' | tr_c=='O' | bl_c=='O' | br_c=='O') return 0; //cuidado! sink hole!  
		
		return 1;
		
	}	
	
	int has_gold(struct node** M, int loc, int w){
		int tl_c = M[loc]->c; 
		int tr_c = M[loc+1]->c;
		int bl_c = M[loc+w]->c; 
		int br_c = M[loc+w+1]->c; 
		if(tl_c=='$' | tr_c=='$' | bl_c=='$' | br_c=='$') return 1; //yay gold!
		else return 0; 
	}
		
	int ogre_bfs(struct node** M, int start_idx, int h, int w){
		// start node
		struct node* s = M[start_idx];
		int gold_loc = -1; //initialize gold_loc to be invalid
			
		//following Tim Roughgarden's notation
		int queue_front_idx = s->idx;
		int curr_neighbour_idx;
		
		//Mark node s as explored
		s->explored = 1; 
		
		//Initialize queue with node s in it
		create_queue(); 
		enqueue(queue_front_idx); //curr_idx
		
		// extra constant 
		int neighbour_calc_offset[4] = {1, w, -1, -w};
		
		//While queue is not empty, 
		while(!is_queue_empty()){
			//Remove first node v from it, storing the value of node idx
			queue_front_idx = queue_front();
			dequeue(); 
			
			//For all neighbours of this first node:
			for(int neighbour_count = 0; neighbour_count<4; neighbour_count++){
				//Tackle a neighbour
				curr_neighbour_idx = queue_front_idx + neighbour_calc_offset[neighbour_count];
				 
				// if new neighbour_idx is a location ogre can some time move to, then do the following
				if(is_new_loc_valid(M, curr_neighbour_idx, h, w)){ 
					//If not already explored, mark the neighbour as explored
					if(!M[curr_neighbour_idx]->explored){
						M[curr_neighbour_idx]->explored = 1;
						
						//Put neighbour in queue
						enqueue(curr_neighbour_idx);
						
						//Prev node is...
						M[curr_neighbour_idx]->prev = queue_front_idx;
						
						//if present neighbour has gold, that's where we gotta go
						if(has_gold(M, curr_neighbour_idx, w)) return curr_neighbour_idx;
					}
				}
				
			}
		} 

		return gold_loc;
	}

	void print_path_to_gold(struct node** maze, int s, int g, int h, int w){
		if(g<0){
			printf("Boohoo no gold\n");
			return;
		}
		
		printf("\n\n\nWoohoo found gold!\n\n\n");
		int curr_idx = g;
		while(curr_idx!=-1){//do until you reach start
			maze[curr_idx]->c = '&';
			maze[curr_idx+1]->c = '&'; 
			maze[curr_idx+w]->c = '&';
			maze[curr_idx+w+1]->c = '&'; 
			
			curr_idx = maze[curr_idx]->prev; 
		}
		
		for(int i = 0; i<h; i++){
			for(int j = 0; j<w; j++)
				printf("%c ", maze[j+i*w]->c);
			printf("\n"); 
		}
		
		return;
	}	

	int main(int argc, char* argv[]){
		//read maze from text file
		struct node** maze;
		int I, J; 
		I = 10; J = 10;
		maze = init_maze(I, J); 
		for(int i = 0; i<I; i++){
			for(int j = 0; j<J; j++)
				printf("%c ", maze[j+i*J]->c);
			printf("\n");
		}
	
		//init start loc
		int start_idx = 0;
		
		//do bfs
		int gold_loc = ogre_bfs(maze, start_idx, I, J);
		
		//print out the whole path
		print_path_to_gold(maze, start_idx, gold_loc, I, J);
		
		return 0;
	}


