#include "bstdb.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

typedef struct node{
	char* name;
	int id;
	int word_count;
	struct node* left;
	struct node* right;


}node;

node* root;
int comps;
int searches;
int book_count;

//Could put this is the init function
int middle = 5000000;
int i = 0;
double step = 1;
int were_equal = 0;



int id_gen();
node* tree_search(node* root, int id);
void destroy(node* root);
int height(node* root);
int max(int a, int b);
int check_balance(node* root);


int bstdb_init ( void ){
	comps = 0;
	searches = 0;
	root = NULL;
	book_count = 0;
	return 1;
}


int
bstdb_add ( char *name, int word_count ) {
	
	int new_id = id_gen();

	node* new_node = (node*)malloc(sizeof(node));
	new_node->id = new_id;
	new_node->word_count = word_count;
	new_node->name = name;

	new_node->left = NULL;
	new_node->right = NULL;
	
	if(root == NULL){
		root = new_node;
		book_count++;
		return (root->id);
	}
    else{
		
	node* current = root;
	node* previous = root;

	while(current != NULL){

		previous = current;

		if(new_node->id > current->id){
			current = current->right;
		}
		else if(new_node->id < current->id){
			current = current->left;
		}
		else if(new_node->id == current->id){
			were_equal++;
			if(i%2 == 0){new_node->id++;}
			else{new_node->id--;}
			//im very sure this case is impossible
			//3 nested elses can probably make this cleaner later
		}
	}

	if(new_node->id > previous->id){
		previous->right = new_node;
		book_count++;
		return(new_node->id);
	}
	else if(new_node->id < previous->id){
		previous->left = new_node;
		book_count++;
		return(new_node->id);
		
	}
	else{return -1;}

	}
	
}




int
bstdb_get_word_count ( int doc_id ) {
	
	searches++;
	node* p = (node*)malloc(sizeof(node));
	p = tree_search(root,doc_id);
	if(p != NULL){
		return(p->word_count);
	}
	// If the required node is not found, this function should return -1
	else{return -1;}
	
}

char*
bstdb_get_name ( int doc_id ) {
	
	searches++;
	node* p = (node*)malloc(sizeof(node));
	p = tree_search(root,doc_id);
	if(p != NULL){
		return(p->name);
	}
	// If the required node is not found, this function should return NULL or 0
	else{return NULL;}
}

void
bstdb_stat ( void ) {
	
	printf("STAT");

	printf("\nnumber of nodes created: " );

	printf("%i",book_count);
	printf("\nIs tree balanced: ");
	if(check_balance(root) == 1){
		printf(" N ");
	}
	else{
		printf(" Y ");
	}
	
	printf("\nDuplicate ids created: %i",were_equal);
	

	printf("\nAvg comparisons per search  -> %lf",(double)comps/searches);
	printf("\n(For reference, Log2(100,000) is approximately 16.6\n");

}

void
bstdb_quit ( void ) {

	destroy(root);
}





int id_gen(){
	double x;
	//generate ideal id keys level by level from left to right in the bst

	if((0.5*step*middle + i*step*middle)<2*middle){
		x = (0.5*step*middle + i*step*middle);
		i++;
	}
	else{
		step = step*0.5;
		x = 0.5*step*middle;
		i = 1;
	}

	return floor(x);

}

node* tree_search(node* root, int id){

    
    if(id == root->id){
		comps++;
        return root;
    }
    
    else if(id< root->id && root->left !=NULL){
		comps++;
        return tree_search(root->left,id);
    }

    else if(id> root->id && root->right != NULL){
		comps++;
        return tree_search(root->right,id);
    }

	else{return NULL;}

	
}

void destroy(node* root){
	//recursion sure is neat
	if(root != NULL){
		destroy(root->left);
		destroy(root->right);
		free(root);
	}
}



int height(node* root){

    if (root == NULL){
        return 0;}
    
    return 1 + max(height(root->left), height(root->right));
}

int max(int a, int b){
	if(a >= b){
		return a;
	}
	else{return b;}
}




int check_balance(node* root){
    
    int leftside;
    int rightside;
 
    
    if (root == NULL){
        return 1;}
 
    leftside = height(root->left);
    rightside = height(root->right);
 
    if (abs(leftside - rightside) <= 1){
        return 1;}
 
    else{return 0;}

}

