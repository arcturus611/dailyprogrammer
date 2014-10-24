// Learning binary trees for Huffman Coding. 
// July 8, 2014
// Swati Padmanabhan

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
 int val;
 struct node *left, *right; // When declaring multiple pointers, asterisks only stick to the first one source: http://boredzo.org/pointers/ 
}Node;

void insert(Node **tree, Node *item){
// we pass in a double pointer to the tree because we want to modify *tree. Remember, we pass in a pointer to whatever it is that we wish to modify. 

 if(!(*tree)){ 
    *tree = item; 
    return;
 }

 if(item->val < (*tree)->val)
   insert(&((*tree)->left), item); 
 else 
   insert(&((*tree)->right), item);  

}

void wrong_insert(Node *tree, Node *item){
 //passing in a single pointer, let us see what happns
 if(!tree){
  tree = item; 
  return; 
 }

 if(item->val < tree->val)
  wrong_insert((tree->left), item); 
 else
  wrong_insert((tree->right), item); 
}

void printTree(Node *tree){
 if(tree->left) printTree(tree->left); 
 printf("%d ", tree->val); 
 if(tree->right) printTree(tree->right); 
 printf("\n"); 
}

void main(){
 Node *curr; 
 Node *root; 
 int i; 

 root = NULL; 
 
 for (i = 10; i > 0; i--){
  curr = (Node *)malloc(sizeof(Node));
  curr->val = i; 
  curr->left = curr->right = NULL; 
  insert(&root, curr); 
 // wrong_insert(root, curr); 
 }

// the problem with wrong_insert is, since we only pass in a copy of root to it, root never gets modified and remains NULL forever. So when in printTree we try accessing tree->left, it's a seg fault due to an access violation.
 printTree(root); 
}
