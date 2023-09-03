//Saad Amir 20334372
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"



void tree_insert(Tree_Node** root, char data){
    
    if(*root == NULL){
        
        (*root) = (Tree_Node*)malloc(sizeof(Tree_Node));
        (*root)->data = data;
        (*root)->left = NULL;
        (*root)->right = NULL;   
    }
    else if(data<(*root)->data){
        tree_insert(&(*root)->left,data);
    }
    else{
        tree_insert(&(*root)->right,data);
    }
}

Tree_Node* create_bst (char data[]){

    Tree_Node* root = NULL;
    int i = 0;
    while(data[i] != '\0'){
        tree_insert((&root),data[i]);
        i++;
        
    }
    
    return root;
}

Tree_Node* tree_search(Tree_Node* root, char data){

    if(root == NULL){
      return NULL;  
    }
    else if(data == root->data){
        return root;
    }
    
    else if(data< root->data){
       return tree_search(root->left,data);
    }

    else {
       return tree_search(root->right,data);
    }



}

void tree_print_sorted(Tree_Node* root){
    if(root != NULL){
        tree_print_sorted(root->left);
        printf("%c",root->data);
        tree_print_sorted(root->right);

    }
}

void tree_delete(Tree_Node* root){
    if(root != NULL){
        tree_delete(root->left);
        tree_delete(root->right);
        free(root);
    }
}
