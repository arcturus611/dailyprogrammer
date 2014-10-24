	//r/dailyprogrammer
	//challenge 182 easy: Columnify text

	#include<stdio.h>
	#include<stdlib.h>
	#include<math.h>

	#define MAX_ROWS 1024

	typedef struct col_info_{
		int num_cols;
		int col_width;
		int space_width;
		int num_rows;
		int num_chars; 
		char* single_col_data; 
	}ColumnInfo;

	ColumnInfo* prep_col_info(FILE* fp){
		ColumnInfo* text_col_info = malloc(sizeof(ColumnInfo));
		scanf("%d %d %d", &(text_col_info->num_cols), &(text_col_info->col_width), &(text_col_info->space_width));

		text_col_info->single_col_data = calloc(MAX_ROWS, text_col_info->col_width);
		int num_chars = 0; char* p = text_col_info->single_col_data;
		while(1){
			int c = fgetc(fp);
			if (c =='\n') c = ' ';
			if(c == EOF) break;
			*p = c;
			num_chars++;
			p++;
		}
		text_col_info->num_chars = num_chars;
		text_col_info->num_rows = ceil((float)num_chars/((text_col_info->num_cols)*(text_col_info->col_width)));

		return text_col_info;
	}

	void columnify(ColumnInfo* text_col_info, FILE* fp){
		int height = text_col_info->num_rows;
		int width = text_col_info->col_width;
		int space_width = text_col_info->space_width;
		int num_chars_per_col = height*width;
		int total_chars = text_col_info->num_chars;
		int num_chars_in_line;
		char* p_start = text_col_info->single_col_data;
		char* p;

		for (int row = 0; row<height; row++){
			for(int col = 0; col<text_col_info->num_cols; col++){
				if (row*width + col*num_chars_per_col>=total_chars) 
					break;
				else if (row*width + col*num_chars_per_col<=total_chars-width){
					num_chars_in_line = width;
				}
				else if ((row*width + col*num_chars_per_col>total_chars-width) && (row*width + col*num_chars_per_col<total_chars)){
					num_chars_in_line = total_chars- (row*width + col*num_chars_per_col);
				}
				p = p_start + row*width + col*num_chars_per_col;
				for(int my_char = 0; my_char<num_chars_in_line; my_char++)
					printf("%c", *p++);
				for(int my_space = 0; my_space<space_width; my_space++)
					printf(" ");
			}
			printf("\n");
		}
	}

	int main(int argc, char* argv[]){

		FILE* fp;
		fp = fopen("columnify_input.txt", "r");
		ColumnInfo* ptext_col_info;
		ptext_col_info = prep_col_info(fp);

		columnify(ptext_col_info, fp);
		return 0;
	}
