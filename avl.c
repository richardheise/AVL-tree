#include<stdio.h>
#include<stdlib.h>
#include"avl.h"

// Function to get a node's height
static int height(t_node *p_node) {

	// checks if node exists, if it doesn't it should return 0
	if (!p_node) return 0;
	return p_node->bf;
}

// Function to get max value between 2 ints
static int max(int a, int b) {
	if (a > b) {
		return a;
	}

	return b;
}

// Function to get the balance of a given node
static int readBalance(t_node *p_node) {

	// Checks if node exists, if so them it applies 
	// the difference between it's sons height
	if (!p_node) return 0;
	return height(p_node->left) - height(p_node->right);
}

t_node *createNode(int key){

	// allocates a node 
	t_node *node;
	node = malloc (sizeof(t_node));

	if(!node){
		perror("error: could not allocate node properly");
		exit(-1);
	}

	// initialize values
	node->left=NULL;
	node->right=NULL;
	node->bf=1;
	node->key=key;

	return node;
}

t_node *insertNode(t_node *p_node, int key){

	// Inserts a node 
	if (!p_node)
		return(createNode(key));

	if (key < p_node->key)
		p_node->left = insertNode(p_node->left, key);
	else if (key > p_node->key)
		p_node->right = insertNode(p_node->right, key);
	else 
		// we don't deal with duplicate key values
		return p_node;


	// recalculate current height
	p_node->bf = 1 + max(height(p_node->left), height(p_node->right));


	// now we test the rotation cases
	int currentBalance = readBalance(p_node);

	if (currentBalance > 1 && key < p_node->left->key) {
		return rightRotation(p_node);
	}

	if (currentBalance < -1 && key > p_node->right->key) {
		return leftRotation(p_node);
	}

	if (currentBalance < -1 && key < p_node->right->key) {
		p_node->right = rightRotation(p_node->right);
		return leftRotation(p_node);
	}

	if (currentBalance > 1 && key > p_node->right->key) {
		p_node->left = leftRotation(p_node->left);
		return rightRotation(p_node);
	}

	return p_node;

}

int sucessor(t_node *p_node){

	t_node *aux=p_node;
	if(aux->left == NULL)
		return aux->key;

	while(aux->left->left != NULL)
		aux=aux->left;

	int key = aux->left->key;
	free(aux->left);
	aux->left=NULL;
	return key;

}

t_node *deleteNode(t_node *p_node, int key){

	if (!p_node)
		return p_node;

	if(p_node->key == key){

		if(p_node->right != NULL)
			p_node->key = sucessor(p_node->right);

		else if (p_node->left == NULL)  {
			p_node = NULL;
		}
		else 
			*p_node = *p_node->left;

	}

	if (p_node == NULL)
		return p_node;
	
	else if(p_node->key > key)
		p_node->left = deleteNode(p_node->left, key);
	else
		p_node->right = deleteNode(p_node->right, key);

	return p_node;

}

void preOrder(t_node *p_node){

	if(!p_node)	
		return;
	printf("%d ", p_node->key);
	preOrder(p_node->left);
	preOrder(p_node->right);
}

void inOrder(t_node *p_node){

	if(!p_node)	
		return;
	inOrder(p_node->left);
	printf("%d ", p_node->key);
	inOrder(p_node->right);

}

void postOrder(t_node *p_node){

	if(!p_node)	
		return;
	postOrder(p_node->left);
	postOrder(p_node->right);
	printf("%d ", p_node->key);

}

t_node *rightRotation(t_node *p_node){

	t_node *aux =  p_node->left;
	t_node *aux2 = p_node->left->right; /*or simply aux->right*/

	p_node->left->right = p_node;
	p_node->left=aux2;

	p_node->bf = 1 + max(height(p_node->left), height(p_node->right));
	aux->bf = 1 + max(height(aux->left), height(aux->right));

	return aux;
}

t_node *leftRotation(t_node *p_node){

	t_node *aux =  p_node->right;
	t_node *aux2 = p_node->right->left; /*or simply aux->left*/

	p_node->right->left = p_node;
	p_node->right = aux2;


	p_node->bf = 1 + max(height(p_node->left), height(p_node->right));
	aux->bf = 1 + max(height(aux->left), height(aux->right));

	return aux;
}
