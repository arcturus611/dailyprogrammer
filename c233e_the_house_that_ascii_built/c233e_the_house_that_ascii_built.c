/* You are to be given an ASCII blueprint of a house, which you will then turn in to glorious reality.
My comment: This is such a lovely problem. Totally easy, but fun. Hard combination that is. 
*/
	#include<stdio.h>
	#include<stdlib.h>
	#include<time.h>
	#include<string.h>
	#define MAX_COLS 50
	#define MAX_NUM_TOWERS 10
	
	#define SINGLE_TOWER_BASE_WIDTH 5
	
	int read_input(char*** arr){
		char n_c[3]; char *pos; 
		int N;
		fgets(n_c, 3, stdin);
		if((pos = strchr(n_c, '\n'))!=NULL) *pos = '\0';
		N = atoi(n_c); // Isn't there a saner way to do this? I just want to read an int, for goodness' sake!
		
		printf("Size of iut is %d\n", N);
		
		*arr = malloc(sizeof(char* )*N); //pointer to N arrays of chars
		for(int i = 0; i<N; i++){
			(*arr)[i] = malloc(sizeof(char)*MAX_COLS);//each element of the array is itself a char array
		}
		
		for(int i=0; i<N; i++){
			fgets((*arr)[i], MAX_COLS, stdin);
			if((pos = strchr((*arr)[i], '\n'))!=NULL) *pos = '\0'; 
		}	
			
		return N;
	}
	
	void test_read_input(int n, char** arr){
		printf("\n Checking if input was read correctly\n");
		for (int i = 0; i<n; i++)
			printf("%d: %s\n", i, arr[i]);	
		
		return;
	}
	
	int init_output(int N, char** inp, char*** out, int* n_o_r, int* n_o_c){
		/*size_t num_inp_cols = sizeof(inp[0])/sizeof(inp[0][0]);
		printf("Num cols is %lu\n", num_inp_cols); */ // Why doesn't this work this way? I just want to be able to count the number of elements in one row of the input matrix. 
		int num_inp_cols = 0;
		while (inp[N-1][num_inp_cols] == '*'){
			num_inp_cols++;
		} //Counting number of elements in last row of input matrix
		printf("Num cols = %d\n", num_inp_cols);
		
		/*I had thought that the max # rows can be determined from the width of the input matrix. This isn't correct. I'll have to read the matrix to get this information*/
		int max_col_height = 0;
		int curr_col_height;
		for(int j = 0; j<num_inp_cols; j++){
			curr_col_height = 0; //initialize this for every column
			for(int i = N-1; i>=0; i--){
				if(inp[i][j]=='*')
					curr_col_height++;
				else break;
			}
			if(curr_col_height>max_col_height) max_col_height = curr_col_height;
		}
		
		*n_o_c = 4*num_inp_cols + 1; //See notebook for calculation
		*n_o_r = 2*num_inp_cols + 2*max_col_height + 1; //See notebook; this is the MAX possible height of the ASCII house for a given width of input
		
		//Allocate space for output matrix
		*out = malloc(sizeof(char* )*(*n_o_r));
		for(int i = 0; i<(*n_o_r); i++)
			(*out)[i] = malloc(sizeof(char)*(*n_o_c)); 
			
		//Initialize it
		for(int i= 0; i<(*n_o_r); i++){
			for(int j = 0; j<(*n_o_c); j++){
				(*out)[i][j] = ' '; //If we don't do this, every element is a null char (I think?) and so the tower appears squished
			}		
		}
			
		return num_inp_cols;
	}

	void create_tower_from_star_chain(int row, int col, int n, char** out, int num_rows, int num_cols){
		int base_len = SINGLE_TOWER_BASE_WIDTH + (n-1)*(SINGLE_TOWER_BASE_WIDTH-1); //According to description
		printf("Base length of output is %d\n", base_len);
		
		/*End points of base*/
		out[row][col] = '+';
		out[row][col+base_len-1] = '+';		
		/*Base segment*/
		if(row==(num_rows-1)){
			for(int i = 1; i<base_len-1; i++){
				printf("~~~~ INDEX 1 = (%d, %d)\n", row, col+i);
				out[row][col+i] = '-';
			}
		}
				
		/*End walls of tower*/
		out[row-1][col] = '|'; //Remember in C rows/cols increase in index going down/right
		out[row-1][col+base_len-1] = '|'; 
		printf("Coord of rihgt wall = %d\n", col+base_len-1);
		
		/*SLoping roof*/
		int roof_height = base_len/2; //height of only the sloping part, including A
		/*Ends of the roof*/
		out[row-2][col] = '+'; 
		out[row-2][col+base_len-1] = '+';
		/*Upslope*/
		for(int i = 1; i<roof_height; i++)
			out[row-2-i][col+i] = '/';
		/*Downslope*/	
		for(int i = 1; i<roof_height; i++)
			out[row-2-i][col+base_len-1-i] = '\\';
		/*The top*/	
		out[row-2-roof_height][col+roof_height] = 'A';
		
		//A window under the top
		out[row-1][col+roof_height] = 'o';
		
		/*In cases where the tall structure is at the very start or the very end, we extend the end walls all the way down*/
		//if((row<(num_rows-1)) && (col==0)){//{
		if(row<(num_rows-1)){
			for(int i = row; i<num_rows-1; i++){
				if(!(out[i][col]=='+' && (out[i-1][col-1]=='\\' || out[i-1][col+1]=='/'))) out[i][col] = '|';
				if(!(out[i][col+base_len-1]=='+' && (out[i-1][col+base_len-2]=='\\' || out[i-1][col+base_len]=='/'))) out[i][col+base_len-1]= '|';
			}
		}
			
		return;
	}
	
        void add_doors_and_windows(char** out, int walls[][2], int num_rows, int num_cols){
     		int get_out_flag = 0; 
     		int num_towers = 0; 
     		int row, col; 
     		int base_len[MAX_NUM_TOWERS];
     		
     		for(int i = 0; i<MAX_NUM_TOWERS; i++){
     			if(get_out_flag) break;
     			col = walls[i][1]; 
     			row = walls[i][0];
     			base_len[i] = walls[i+1][1]-walls[i][1]+1;
     			if(base_len[i]<=1){
     				base_len[i] = num_cols - walls[i][1];
     				get_out_flag = 1;
     			}
     			num_towers++; 
     		}
     		get_out_flag = 0;
     		
     		// randomly generate a door
     		srand(time(0));
     		int door_tower = rand()%num_towers; 
     		
     		//draw this random door
     		int door_abs_pos = walls[door_tower][1] + base_len[door_tower]/2;
     		printf("\n\n\nDOOR IS LOCATED at %d\n\n", door_abs_pos);
     		out[num_rows-2][door_abs_pos] = '|';
     	        out[num_rows-2][door_abs_pos+1] = '|';
     	        
     	        //draw windows
     	        

     	        return;
     			
     	}
	
     	void remove_dangling_walls(char** out, int walls[][2], int num_rows, int num_cols){
     		/*Finally, clean up the dangling inner walls*/ 
		int get_out_flag = 0; //signifies end of tower list in the walls array
		
		for(int OUTERLOOP = 0; OUTERLOOP<MAX_NUM_TOWERS; OUTERLOOP++){
			if(get_out_flag) break;
			int col = walls[OUTERLOOP][1]; 
			int row; 
			int base_len = walls[OUTERLOOP+1][1]-walls[OUTERLOOP][1] + 1;
			if (base_len<=1) {
				base_len = num_cols - walls[OUTERLOOP][1];
				get_out_flag  =1;
			}
			
			
			for( row = num_rows-1; row>=walls[OUTERLOOP][0]; row--){		
				// Different types of clean up: 
				if((col>0) && (row<(num_rows-1))){// && (col+base_len<num_cols)){//clean up only for inner walls
					if(!(((out[row-2][col-1]=='\\') || (out[row-2][col+1]=='/')) && ((out[row][col-1]=='\\') || (out[row][col+1]=='/')))   &&        !(((out[row-2][col-1]=='\\') || (out[row-2][col+1]=='/')) && (out[row+1][col]=='|'))   &&  !(((out[row][col-1]=='\\') || (out[row][col+1]=='/')) && (out[row-1][col]=='|')) &&  !(((out[row-1][col]=='|')  && (out[row+1][col]=='|')))    &&    !(out[row][col]=='+' && ( out[row-1][col-1]=='\\'  ||  out[row-1][col+1]=='/' ))   ){
						printf("Clean up category 1!\nDETAILS: col = %d, row = %d, num_rows = %d\n", col, row, num_rows);
						out[row][col]=' '; 
						
					}
				}
		
				if((col+base_len<num_cols) && (row<num_rows-1)){//clean up only for inner walls
					if(!(((out[row-2][col+base_len-2]=='\\') || (out[row-2][col+base_len]=='/')) && ((out[row][col+base_len-2]=='\\') || (out[row][col+base_len]=='/')))   &&        !(((out[row-2][col + base_len - 2]=='\\') || (out[row-2][col+base_len]=='/')) && (out[row+1][col+base_len-1]=='|'))   &&  !(((out[row][col+base_len-2]=='\\') || (out[row][col+base_len]=='/')) && (out[row-1][col+base_len-1]=='|')) &&  !(((out[row-1][col+base_len-1]=='|')  && (out[row+1][col+base_len-1]=='|')))    &&     !(out[row][col+base_len-1]=='+' && ( out[row-1][col+base_len-2]=='\\'  ||  out[row-1][col+base_len]=='/' )) ){
					
						out[row][col+base_len-1]=' '; 
					}
				}
			}
	
			row = walls[OUTERLOOP][0];
			if (col!=0) {
				if(out[row-3][col-1]=='\\' || out[row-3][col+1]=='/') out[row-2][col] = '+';
			}
		
			if(out[row-3][col+base_len-2]=='\\' || out[row-3][col+base_len]=='/') out[row-2][col+base_len-1] = '+';
		
		}
		
		return;
	}
	
	int identify_star_chain(int inp_row, int inp_col, int inp_wid, char** inp, int* r, int* c, int* l){
	/* The goal of this function is to get a star chain with all parameters required to create a tower out of it. Here (inp_row, inp_col) is the position of the start of the star chain. We return the column of the start of the next chain (as input row is always going to be the bottommost), and we modify the values of the row/col/length to be passed as parameters into the tower creation function. They come in INITIALIZED*/
		
		//NOTE: inp_row, inp_col are in C format (starting with 0 index) so no need to subtract 1 anywhere
		
		//Initializing tower params IN THE CONTEXT OF THE STAR MATRIX. These params will need to be scaled for the tower params
		int tower_offset_from_ground; 
		*c = inp_col*4; //Col coordinate to start building tower in the output 
		int star_chain_len = 1;  
		
		//First get the height of tower
		int j;
		for(j = 0; j<=inp_row; j++){
			if (inp[inp_row-j][inp_col]!='*') 
				break;
		}
		tower_offset_from_ground = j - 1; 
		*r = *r - 2*tower_offset_from_ground; //Row coordinate to start building tower from in the output
		printf("~~ Row coordinate to start building tower in output: %d\n", *r); 
		
		//Walk along the bottom row
		int walk_row = inp_row - tower_offset_from_ground; 
		for(int p = inp_col; p<inp_wid-1; p++){
			printf("Walking along input matrix, p = %d\n", p); 
		//Start at inp_col, everything before that has been taken care of already. Stop at one before last, last case dealt separately
			if(walk_row>0){
				if((inp[walk_row][p+1]=='*') && (inp[walk_row-1][p+1]==' ')) 
					star_chain_len++;
				else break; 
			}else{
				if(inp[walk_row][p+1]=='*')
					star_chain_len++;
				else break;
			}
	
		}	
		
		*l = star_chain_len; 
		
		int new_inp_col = inp_col + star_chain_len; 
		printf("~~~Star Chain Length is %d and new_inp_col is %d\n", *l, new_inp_col); 
		return new_inp_col;
	}
	
	void build_house_from_blueprint(char** inp, int i_rows, int i_cols, char** out, int o_rows, int o_cols, int inner_walls[][2]){
		int inp_col=0;
		int next_inp_col;
		int out_row, out_col, out_len;
		out_row = o_rows-1; 
		int inner_walls_count = 0;
		
		/*Read star matrix and print correspondiing house outline*/
		while(inp_col<i_cols){
			printf("~~~in while loop...\n\n"); 
			printf("Params are: i_rows-1 = %d, inp_col = %d, i_cols =%d\n", i_rows-1, inp_col, i_cols); 
			printf("Outout params are: o_rows = %d\n", o_rows);
			next_inp_col = identify_star_chain(i_rows-1, inp_col, i_cols, inp, &out_row, &out_col, &out_len);
			printf(" I AM HERE!!!!!!!!!!!!!!!!!\n");
			inner_walls[inner_walls_count][0] = out_row;
			inner_walls[inner_walls_count][1] = out_col;
			inner_walls_count++;
			
			printf("Value of next_inp_col is %d\n", next_inp_col);
			printf("Other vals: out_row = %d, out_col = %d, out_len = %d, o_rows = %d, o_cols = %d\n", out_row, out_col, out_len, o_rows, o_cols);
			create_tower_from_star_chain(out_row, out_col, out_len, out, o_rows, o_cols);
			inp_col = next_inp_col;
			out_row = o_rows-1; //Resetting it otherwise towers keep going higher
		}		
		
		
		/*Draw base */
		out[out_row][0] = '+'; 
		out[out_row][o_cols-1] = '+';
		for(int i = 1; i<o_cols-1; i++)
			out[out_row][i] = '-';
		
		return;
	}

	int main(int argc, char* argv[]){
		
		char** blueprint; //declare the input and output matrices
		char** ascii_house;
		
		int num_out_rows, num_out_cols;
			
		int num_inp_rows = read_input(&blueprint);
		
		int num_inp_cols = init_output(num_inp_rows, blueprint, &ascii_house, &num_out_rows, &num_out_cols); 
	
		//create_tower_from_star_chain(num_out_rows-1, 3, 1, ascii_house); 
		int inner_walls[MAX_NUM_TOWERS][2] = {{0}};
			
		printf("CREATED INNER WALLS\n");
		
		build_house_from_blueprint(blueprint, num_inp_rows, num_inp_cols, ascii_house, num_out_rows, num_out_cols, inner_walls);
		
		for(int i = 0; i<10; i++){
			for(int j = 0; j<2; j++){
				printf("%d ", inner_walls[i][j]);
			}
			printf("\n");
		}
		
		remove_dangling_walls(ascii_house, inner_walls, num_out_rows, num_out_cols);
		
		//doors and windows
		add_doors_and_windows(ascii_house, inner_walls, num_out_rows, num_out_cols);
		
		
		for(int i = 0; i<num_out_rows; i++){
			for(int j = 0; j<num_out_cols; j++){
				printf("%c", ascii_house[i][j]);
			}
			printf("\n");
		}
		
			
		return 0;
	}
