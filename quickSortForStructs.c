/* Compile options needed: none
 *
 * This example program uses the C run-time library function qsort()
 * to sort an array of structures.
 */ 

#include <stdio.h>
#include <stdlib.h>

typedef int (*compfn)(const void*, const void*);

struct animal { int  number;
                char name[15];
              };

struct animal array[10]  = { {  1, "Anaconda"    },
                             {  5, "Elephant"    },
                             {  8, "Hummingbird" },
                             {  4, "Dalmatian"   },
                             {  3, "Canary"      },
                             {  9, "Llama"       },
                             {  2, "Buffalo"     },
                             {  6, "Flatfish"    },
                             { 10, "Zebra"       },
                             {  7, "Giraffe"     }  };

void printarray(void);
int  compare(struct animal *, struct animal *);

void main(void)
{
   printf("List before sorting:\n");
   printarray();

   qsort(&array,              // Beginning address of array
   10,                                 // Number of elements in array
   sizeof(struct animal),              // Size of each element
   (compfn)compare );                  // Pointer to compare function

   printf("\nList after sorting:\n");
   printarray();
}

int compare(struct animal *elem1, struct animal *elem2)
{
   if ( elem1->number < elem2->number)
      return -1;

   else if (elem1->number > elem2->number)
      return 1;

   else
      return 0;
}

void printarray(void)
{
   int i;

   for (i = 0; i < 10; i++)
      printf("%d:  Number %d is a %s\n",
               i+1, array[i].number, array[i].name);
}

