// Huffman Coding
// June 11, 2014

#include <stdio.h>
#include <stdlib.h>

#define NUM_SYMS 27
#define NUM_NODES NUM_SYMS*2-1
#define MAX_FREQ 1.0 //We aren't using this as a check because we aren't bothering checking the accuracy of the double vals in englishLetterWeights[]

double englishLetterWeights[NUM_SYMS] = {.081, .015, .028, .043, .13, .023, .02, .061, .07, .002,
.001, .040, .024, .069, .076, .020, .001, .061, .064, .091,
.028, .01, .024, .002, .02, .0007, .134}; // 27th is for space

char englishLetters[NUM_SYMS] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' '};

/*
double englishLetterWeights[NUM_SYMS] = {850, 395, 388, 366, 355, 305, 295, 278, 255, 200, 148, 145, 144, 75, 61, 51, 46, 42, 35, 29, 17, 10, 8, 2, 1}; 
char englishLetters[NUM_SYMS] = {'e', 'a', 's', 'i', 't', 'n', 'r', 'u', 'l', 'o', 'd', 'c', 'm', 'p', 'v', 'q', 'g', 'f', 'b', 'h', 'j', 'x', 'y', 'z', 'k', 'w'}; 
*/
/*
double englishLetterWeights[NUM_SYMS] = {24, 12, 10, 8, 8}; 
char englishLetters[NUM_SYMS] = {'A', 'B', 'C', 'D', 'E'}; 
*/
typedef struct node{
 int idx;
 char symbol; 
 double freq; 
 struct node *parent; 
 struct node *left, *right;
}Node;

typedef struct idxnode{
 int idx; 
 struct idxnode *next; 
}IdxNode; 

// Swati testing
typedef struct huffcode{
 char symbol; 
 int* symbolCode; 
 int symbolCodeLen;
}HuffCode;

//http://www.geeksforgeeks.org/to-find-smallest-and-second-smallest-element-in-an-array/
void twoSmallest(Node** init, IdxNode* root, double* x, int arr_size)
{
   /* INPUTS: 
     Node** init : address to start of array of Node pointers
     IdxNode* root: address to start of array of IdxNode pointers
     double* x   : address to start of array of ints
     int arr_size: size of array of Node pointers (this increments at each step)
   */
    int i, j, first_idx, second_idx;
    double first, second; 

    first = second = MAX_FREQ;
    first_idx = second_idx = NUM_SYMS; 

    for (j = 0; j < arr_size ; j++)
    {
	i = root->idx;
        root = root->next;  
        /* If current element is smaller than first then update both
          first and second */
        if (init[i]->freq < first)
        {
            second = first;
	    second_idx = first_idx; 

            first = init[i]->freq;
            first_idx = i; 
        }
 
        /* If arr[i] is in between first and second then update second  */
        else if (init[i]->freq < second){
            second = init[i]->freq;
	    second_idx = i; 
	}
    }

    x[0] = first; 
    x[1] = (double)first_idx; 
    x[2] = second; 
    x[3] = (double)second_idx; 

}


void createParent(Node** symAttr, double* x, int newNodeIdx){
/*
 INPUTS:
 Node** symAttr : address to start of array of Node pointers
 int* x         : address to start of array of indices of smallest two freqs in symAttr
 int newNodeIdx : int index for where the new parent should be inserted in symAttr
 
*/
 
 *(symAttr + newNodeIdx) = (Node *)malloc(sizeof(Node));
 int leftChildIdx = (int)x[3]; 
 int rightChildIdx = (int)x[1]; // Making the smallest the right child, because we want the tree freqs to grow bigger as we move up and left.
 (*(symAttr+newNodeIdx))->freq = x[0] + x[2];
 (*(symAttr+newNodeIdx))->idx = 0; // not really requied, we only need indices of the leaves
(*(symAttr+newNodeIdx))->symbol = '0'; 
 (*(symAttr+newNodeIdx))->left = *(symAttr + leftChildIdx); 
 (*(symAttr+newNodeIdx))->right = *(symAttr + rightChildIdx);
 (*(symAttr+leftChildIdx))->parent = (*(symAttr+newNodeIdx)); 
 (*(symAttr+rightChildIdx))->parent = (*(symAttr+newNodeIdx)); 
 (*(symAttr+newNodeIdx))->parent = NULL; 
}

void insertNode(IdxNode* curr, int newIdx){

 while(curr->next!=NULL){
  curr = curr->next; 
 }

 curr->next = (IdxNode *)malloc(sizeof(IdxNode)); 
 curr->next->idx = newIdx; 
 curr->next->next = NULL; 

}

// https://www.cs.bu.edu/teaching/c/linked-list/delete/
IdxNode *deleteSpecificNode(IdxNode *currP, int value)
{
  /* See if we are at end of list. */
  if (currP == NULL)
    return NULL;

  /*
   * Check to see if current node is one
   * to be deleted.
   */
  if (currP->idx == value) {
    IdxNode *tempNextP;

    /* Save the next pointer in the node. */
    tempNextP = currP->next;

    /* Deallocate the node. */
    free(currP);

    /*
     * Return the NEW pointer to where we
     * were called from.  I.e., the pointer
     * the previous call will use to "skip
     * over" the removed node.
     */
    return tempNextP;
  }

  /*
   * Check the rest of the list, fixing the next
   * pointer in case the next node is the one
   * removed.
   */
  currP->next = deleteSpecificNode(currP->next, value);


  /*
   * Return the pointer to where we were called
   * from.  Since we did not remove this node it
   * will be the same.
   */
  return currP;
}

/* EXPLANATION: 
The arguments to the comparison function are pointers to (const) elements of the array. If the elements of the array are themselves pointers to Node elements, then the arguments to the comparison function will be pointers to pointers to const Node, i.e., const Node **. Of course, the function signature requires the arguments to be of type const void *, so you need to cast the arguments to type const Node ** before you dereference them.
*/
// OTHER REFERENCES:
//http://support.microsoft.com/kb/73853
//http://stackoverflow.com/questions/3489139/how-to-qsort-an-array-of-pointers-to-char-in-c
int cmpfunc(const void* a, const void* b){
	const Node* p1 = *(const Node**)a; 
	const Node* p2 = *(const Node**)b; 
	int d = -(p1->freq - p2->freq); // reverse required for descending order
	return d;
}

void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);
    printf("\n");
}

int isLeaf(Node* curr){
 return (!(curr->left) && !(curr->right)); 
}


//http://www.geeksforgeeks.org/greedy-algorithms-set-3-huffman-coding/
void printCodes(Node* root, int arr[], int top)
{
    // Assign 0 to left edge and recur
    if (root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
 
    // Assign 1 to right edge and recur
    if (root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
 
    // If this is a leaf node, then it contains one of the input
    // characters, print the character and its code from arr[]
    if (isLeaf(root))
    {
        printf("%c: ", root->symbol);
        printArr(arr, top);
    }
}


void generateCodes(Node* root, HuffCode** codeArr, int arr[], int top)
{
    int j; 
    // Assign 0 to left edge and recur
    if (root->left)
    {
        arr[top] = 0;
        generateCodes(root->left, codeArr, arr, top + 1);
    }
 
    // Assign 1 to right edge and recur
    if (root->right)
    {
        arr[top] = 1;
        generateCodes(root->right, codeArr, arr, top + 1);
    }
 
    // If this is a leaf node, then it contains one of the input
    // characters, print the character and its code from arr[]
    if (isLeaf(root))
    {
       // printf("%c: ", root->symbol);
       // printArr(arr, top);
        (*(codeArr+(root->idx)))->symbol = root->symbol; 
 	// convert the int arr into a string
	(*(codeArr+(root->idx)))->symbolCodeLen = top; 
	(*(codeArr+(root->idx)))->symbolCode = (int*)malloc(top*sizeof(int)); 
 	for (j = 0; j<top; j++){
	(*(codeArr+(root->idx)))->symbolCode[j] = arr[j]; 
	}
    }
}


void buildHuffmanTree(HuffCode** englishCodes, Node** symAttr){
	//Node* symAttr[NUM_NODES]; // see http://unixwiz.net/techtips/reading-cdecl.html
	IdxNode *root = (IdxNode *)malloc(sizeof(IdxNode));
        root->idx = 0; 
	root->next = 0; 



	double smallestFreqs[4];
	int i; 

	for (i = 0; i<NUM_SYMS; i++){
		symAttr[i] = (Node*)malloc(sizeof(Node)); // since each element is a pointer
		symAttr[i]->symbol = englishLetters[i];
		symAttr[i]->idx = i;  
		symAttr[i]->freq = englishLetterWeights[i]; 
		symAttr[i]->left = NULL; 
		symAttr[i]->right = NULL;
		symAttr[i]->parent = NULL;  
	}
	
	for (i = 1; i<NUM_SYMS; i++){
		insertNode(root, i); 
	}
	
	for (i = NUM_SYMS; i<NUM_NODES; i++){
		twoSmallest(symAttr, root, smallestFreqs, NUM_NODES-i+1); // only from structs corresponding to indices in Linked List. 
		createParent(symAttr, smallestFreqs, i); 
		//modifyLinkedList(); //delete indices of smallest freqs, add index of new parent	
		insertNode(root, i); 
		root = deleteSpecificNode(root, (int)smallestFreqs[1]); 
		root = deleteSpecificNode(root, (int)smallestFreqs[3]); 
	}	

	int codeArray[NUM_NODES]; 
//        printCodes(symAttr[NUM_NODES-1], codeArray, 0); 
	generateCodes(symAttr[NUM_NODES-1], englishCodes, codeArray, 0);
 
}

void decode(Node* t){
	FILE* f_o, *f_i; 
	f_o = fopen("huffman_decoding.txt", "w"); 
	Node* n = t; 
 	f_i = fopen("huffman_encoding.txt", "r"); 
	int c = 100; 
	
	do{
	c = (char)fgetc(f_i);
	 if(c == '0')
	   n = n->left; 
	else
	   n = n->right;
	
 	if ((n->symbol)!='0'){
	  fputc(n->symbol, f_o); 
	  n = t; 
	}
	}while(!feof(f_i));

	fclose(f_o); 
	fclose(f_i); 
}

int main(){
/*
     int i = 0; 
     for(i = 0; i<NUM_SYMS; i++){
	englishLetterWeights[i] = englishLetterWeights[i]/4857; 
     }
*/
	// create array of codewords. length of array = NUM_SYMS
	Node* symAttr[NUM_NODES]; 
	HuffCode* englishCodes[NUM_SYMS]; 
 	int i, j; 
        for (i = 0; i<NUM_SYMS; i++){
	   englishCodes[i] = (HuffCode*)malloc(sizeof(HuffCode));
           englishCodes[i]->symbol = englishLetters[i]; 
	//   englishCodes[i]->symbolCode = (int*)malloc(sizeof(int)); 
	}

	buildHuffmanTree(englishCodes, symAttr); 
	printf("\n Printing the codes...\n");
	for (i = 0; i<NUM_SYMS; i++){
	 printf("%c: ", (*(englishCodes+i))->symbol);
         for (j=0; j<(*(englishCodes+i))->symbolCodeLen; j++)
	  printf("%d", ((*(englishCodes+i))->symbolCode)[j]);
	printf("\n");  
 	}

	// parse a piece of text and replace its letters with code
	FILE* input_file_ptr; 
 	FILE* output_file_ptr;
	int c, cc, ii; 
	input_file_ptr = fopen("huffman_input.txt", "r"); 
	output_file_ptr = fopen("huffman_encoding.txt", "w"); 

	if (!input_file_ptr || !output_file_ptr)
	  return 0; 
	
	do{
	  c = fgetc(input_file_ptr);
 	
	  if (c==' ')
	   cc = 26; 
	  else
	   cc = c-'a'; 
  
	  if(cc<0)
	   break; 
	  
	  printf("\n %d", cc); 
	  for (ii = 0; ii<englishCodes[cc]->symbolCodeLen; ii++){
	   fputc(englishCodes[cc]->symbolCode[ii] + '0', output_file_ptr);  
	  }
	} while(c!= EOF); 

	fclose(input_file_ptr); 
	fclose(output_file_ptr); 

	decode(symAttr[NUM_NODES-1]);

	printf("\n\n"); 
	return 0; 
}

