	//r/dailyprogrammer easy challenge 181, basic equations
	//using pcre. god help me. (oct 18)
	// gcc -std=c99 -g -Wall c181e_basic_equations.c -o c181e_basic_equations -lpcre

	#include "pcre.h"            	/* PCRE lib        NONE  */
	#include <stdio.h>              /* I/O lib         C89   */
	#include <stdlib.h>             /* Standard Lib    C89   */
	#include <string.h>             /* Strings         C89   */

	#define EQ_LEN 20

	char* month_names[12] = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};
	
	typedef struct _date_{
		int year;
		int month;
		int day;
	}Date;

	Date* read_date_input(char* testStrings[]){ 
	  Date* nonstandard_dates = malloc(10*sizeof(Date));
	  
	  pcre *reCompiled;
	  pcre_extra *pcreExtra;
	  int pcreExecRet;
	  int subStrVec[30];
	  const char *pcreErrorStr;
	  int pcreErrorOffset;
	  char *aStrRegex;
	  char **aLineToMatch;
	  const char *psubStrMatchStr;
	  int j;

	  aStrRegex = "([a-zA-Z0-9]{2,4})(\\/?\\-?\\#?\\*?\\s?)(\\d{2})(\\/?\\-?\\#?\\*?\\,?)(\\d{2,4})";  

	  // First, the regex string must be compiled.
	  reCompiled = pcre_compile(aStrRegex, PCRE_EXTENDED, &pcreErrorStr, &pcreErrorOffset, NULL);

	  // pcre_compile returns NULL on error, and sets pcreErrorOffset & pcreErrorStr
	  if(reCompiled == NULL) {
	    printf("ERROR: Could not compile '%s': %s\n", aStrRegex, pcreErrorStr);
	    exit(1);
	  } /* end if */

	  // Optimize the regex
	  pcreExtra = pcre_study(reCompiled, 0, &pcreErrorStr);

	  /* pcre_study() returns NULL for both errors and when it can not optimize the regex.  The last argument is how one checks for errors (it is NULL if everything works, and points to an error string otherwise. */
	  if(pcreErrorStr != NULL) {
	    printf("ERROR: Could not study '%s': %s\n", aStrRegex, pcreErrorStr);
	    exit(1);
	  } /* end if */

	  int line_idx = 0;
	  for(aLineToMatch=testStrings; *aLineToMatch != NULL; aLineToMatch++) {
	    /* Try to find the regex in aLineToMatch, and report results. */
	    pcreExecRet = pcre_exec(reCompiled,
		                    pcreExtra,
		                    *aLineToMatch, 
		                    strlen(*aLineToMatch),  // length of string
		                    0,                      // Start looking at this point
		                    0,                      // OPTIONS
		                    subStrVec,
		                    30);                    // Length of subStrVec

	    // Report what happened in the pcre_exec call..
	    if(pcreExecRet < 0) { // Something bad happened..
	      switch(pcreExecRet) {
	      case PCRE_ERROR_NOMATCH      : printf("String did not match the pattern\n");        break;
	      case PCRE_ERROR_NULL         : printf("Something was null\n");                      break;
	      case PCRE_ERROR_BADOPTION    : printf("A bad option was passed\n");                 break;
	      case PCRE_ERROR_BADMAGIC     : printf("Magic number bad (compiled re corrupt?)\n"); break;
	      case PCRE_ERROR_UNKNOWN_NODE : printf("Something kooky in the compiled re\n");      break;
	      case PCRE_ERROR_NOMEMORY     : printf("Ran out of memory\n");                       break;
	      default                      : printf("Unknown error\n");                           break;
	      } /* end switch */
	    } else {
	    //  printf("Result: We have a match!\n");
		
	      // At this point, rc contains the number of substring matches found...
	      if(pcreExecRet == 0) {
		printf("But too many substrings were found to fit in subStrVec!\n");
		// Set rc to the max number of substring matches possible.
		pcreExecRet = 30 / 3;
	      } /* end if */

	      // PCRE contains a handy function to do the above for you:
	      char* year; char* day; char* month; 
	      int int_month; int int_year; int int_day;
	      //first get the format-
	      j = 2;
 	      pcre_get_substring(*aLineToMatch, subStrVec, pcreExecRet, j, &(psubStrMatchStr));
 	      printf("Our date separater is: %s\n", psubStrMatchStr);

	      if (strcmp(psubStrMatchStr, "/")==0) {
	      	pcre_get_substring(*aLineToMatch, subStrVec, pcreExecRet, 1, &(month));
	      	printf("Month--- %s\n", month);
	      	int_month = atoi(month);
	      	pcre_get_substring(*aLineToMatch, subStrVec, pcreExecRet, 3, &(day));
	        printf("Day--- %s\n", day);
	      	int_day = atoi(day);
	      	pcre_get_substring(*aLineToMatch, subStrVec, pcreExecRet, 5, &(year));
	         printf("Year--- %s\n", year);
	      	int_year = atoi(year);
	      }else if ((strcmp(psubStrMatchStr, "#")==0)) {	       
	      	pcre_get_substring(*aLineToMatch, subStrVec, pcreExecRet, 1, &(month));
	      	printf("Month--- %s\n", month);
	      	int_month = atoi(month);
	      	pcre_get_substring(*aLineToMatch, subStrVec, pcreExecRet, 3, &(year));
	        printf("Day--- %s\n", year);
	      	int_year = atoi(year);
	      	pcre_get_substring(*aLineToMatch, subStrVec, pcreExecRet, 5, &(day));
	         printf("Year--- %s\n", day);
	      	int_day = atoi(day);
	      }else if (strcmp(psubStrMatchStr, "*")==0){
	      	pcre_get_substring(*aLineToMatch, subStrVec, pcreExecRet, 1, &(day));
	      	int_day = atoi(day);
	      	pcre_get_substring(*aLineToMatch, subStrVec, pcreExecRet, 3, &(month));
	      	int_month = atoi(month);
	      	pcre_get_substring(*aLineToMatch, subStrVec, pcreExecRet, 5, &(year));
	      	int_year = atoi(year);
	      }else if (strcmp(psubStrMatchStr, "-")==0){
	      	pcre_get_substring(*aLineToMatch, subStrVec, pcreExecRet, 1, &(year));
	      	int_year = atoi(year);
	      	pcre_get_substring(*aLineToMatch, subStrVec, pcreExecRet, 3, &(month));
	      	int_month = atoi(month);
	      	pcre_get_substring(*aLineToMatch, subStrVec, pcreExecRet, 5, &(day));
	      	int_day = atoi(day);
	      }else if (strcmp(psubStrMatchStr, " ")==0){
	      	pcre_get_substring(*aLineToMatch, subStrVec, pcreExecRet, 1, &(month));
	      	for(int m_idx = 0; m_idx<12; m_idx++){
	      		if(strcmp(month, month_names[m_idx])==0){
	      			int_month = m_idx + 1;
	      			break;
	      		}
	      	}
	      	pcre_get_substring(*aLineToMatch, subStrVec, pcreExecRet, 3, &(day));
	      	int_day = atoi(day);
	      	pcre_get_substring(*aLineToMatch, subStrVec, pcreExecRet, 5, &(year));
	      	int_year = atoi(year);
	      }
	      
	      printf("We have: %d, %d, %d\n", int_year, int_month, int_day);
	      if (int_year>=50 && int_year<=99)
	      	int_year = 1900 + int_year;
	      else if (int_year>=0 && int_year<=49)
	      	int_year = 2000 + int_year;
	      	
	      nonstandard_dates[line_idx].year = int_year;
	      nonstandard_dates[line_idx].month = int_month;
	      nonstandard_dates[line_idx].day = int_day;	
		
	      // Free up the substring
	      pcre_free_substring(psubStrMatchStr);
	    }  /* end if/else */
	    line_idx++;
	      
	  } /* end for */
	  
	  // Free up the regular expression.
	  pcre_free(reCompiled);
	      
	  // Free up the EXTRA PCRE value (may be NULL at this point)
	  if(pcreExtra != NULL)
	    pcre_free(pcreExtra);

	  return nonstandard_dates;

	}
	
	int main(int argc, char *argv[]) {

		char* nonISOdates[] = {"11/06/88", "06#61#17", "jan 03,2015", "23*09*2010", "2014-11-11"};
		
		Date* input_dates = NULL; //malloc(2*sizeof(Date));
	  	input_dates =  read_date_input(nonISOdates); 
	  	
	  	for(int i = 0; i<5; i++)
		        printf("ISO date %d is %04d-%02d-%02d\n", i, input_dates[i].year, input_dates[i].month, input_dates[i].day);
		
	
	  	
	  	return 0;

	} /* end func main */

