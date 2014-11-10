	//r/dailyprogrammer challenge 142 (easy)
	//falling sand simulation
	
	#include<stdlib.h>
	#include<stdio.h>
	#include<string.h>
	
	void read_sim_envt(int n, char env[n][n]){
		char* line = malloc(n*sizeof(char));
		char* p = NULL;
		
		for (int i= 0; i<n; i++){
			fgets(line, n+2, stdin);
			p = strchr(line, '\n');
			line[p-line] = '\0';
			strcpy(env[i], line);
		}
		
		free(line);
		return;
	}
	
	void sim_falling_sand(int n, char env[n][n]){
		int rock_bottom;
		
		for(int c = 0; c<n; c++){
			rock_bottom = n-1;
			for(int r = n-1; r>=0; r--){
				switch(env[r][c]){
					case '#':
						rock_bottom = r-1;
						break;
					case '.':
						env[r][c] = ' ';
						env[rock_bottom][c] = '.';
						rock_bottom--;
						break;					
				}
			}
		}
		
		return;
	}
	
	void print_sim(int n, char env[n][n]){
		for(int i = 0; i<n; i++){
			for(int j = 0; j<n; j++)
				printf("%c ", env[i][j]);
			printf("\n");
		}
		return;
	}
	
	int main(int argc, char* argv[]){
		int n = atoi(argv[1]);
		
		char env[n][n];
		read_sim_envt(n, env);
		
		printf("\n~~Before simulation~~\n");
		print_sim(n, env);
		
		sim_falling_sand(n, env);
		
		printf("\n~~After simulation~~\n");
		print_sim(n, env);
		
		return 0;
	}
	
	
