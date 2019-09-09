/* @uthor Hitesh Kumar
	roll no 2019201039
	Assignment 2 Question 3
*/

#include<bits/stdc++.h>
using namespace std;

typedef struct _avl {
	int count_nodes;
	int height;
	int data;
	struct _avl* leftPtr;
	struct _avl* rightPtr;
} tree;

int getHeight(tree* root){
	if(root == NULL)
		return 0;
	return root->height;
}
tree* rr(tree* root){
	tree* temp= root->rightPtr;
	root->rightPtr= temp->leftPtr;
	temp->leftPtr= root;
	root->height= std::max(getHeight(root->rightPtr),getHeight(root->leftPtr));
	temp->height= std::max(getHeight(temp->rightPtr),getHeight(temp->leftPtr));
	temp->height+=1;
	root->height+=1;
	return temp;
}

tree* ll(tree* root){
	tree* temp= root->leftPtr;
	root->leftPtr= temp->rightPtr;
	temp->rightPtr= root;
	root->height= std::max(getHeight(root->rightPtr),getHeight(root->leftPtr));
	temp->height= std::max(getHeight(temp->rightPtr),getHeight(temp->leftPtr));
	temp->height+=1;
	root->height+=1;
	return temp;
}

tree* rl(tree* root){
		root->rightPtr=ll(root->rightPtr);
		return rr(root);
}

tree* lr(tree* root){
		root->leftPtr=rr(root->leftPtr);
		return ll(root);
}

bool isEmpty(tree* root){
	if(root->rightPtr == NULL && root->leftPtr == NULL)
		return true;
	return false;
}

int leftCount(tree* root){
	if(root==NULL)
		return 0;
	if(root->leftPtr == NULL)
		return 0;
	return root->leftPtr->count_nodes;
}

int rightCount(tree* root){
	if(root==NULL)
		return 0;
	if(root->rightPtr == NULL)
		return 0;
	return root->rightPtr->count_nodes;
}



int update_height(tree* root){
	if(root == NULL)
		return 0;
	if(root->leftPtr == NULL && root->rightPtr == NULL)
		return 0;
	return std::max(getHeight(root->rightPtr),getHeight(root->leftPtr));
}

tree* getNode(int val){
	tree *newNode= (struct _avl*)malloc(sizeof(struct _avl));
	newNode->rightPtr=NULL;
	newNode->leftPtr=NULL;
	// etiher make nodd node height -1 as discussed in class or
	// height 1
	newNode->height=1;
	newNode->count_nodes=0;
	newNode->data=val;
	return newNode;
}

void print_tree(tree* root){
		if(root==NULL){
            return ;
		}
		print_tree(root->leftPtr);
		int data = root->data;
		std::cout<<data;
		print_tree(root->rightPtr);
}

tree* insertion(tree* root,int val){
	if(root==NULL){
		tree *newNode=getNode(val);
		return newNode;
	}
	if(root->data <= val){//rr
		root->rightPtr=insertion(root->rightPtr,val);
	}else
	if(root->data > val){
		root->leftPtr=insertion(root->leftPtr,val);
	}
	root->height = update_height(root) + 1;

	int bf = getHeight(root->leftPtr) - getHeight(root->rightPtr);
	// +ve left skewd else right

	if(bf>=2){
		if(val>root->leftPtr->data){
			//lr rotaion
			return lr(root);
		}else{
			//ll
			return ll(root);
		}

	}
	if(bf<=-2){
		if(val<root->rightPtr->data){
			//rl
			return rl(root);
		}else{
			//rr
			return rr(root);
		}
	}
	return root;
}

int main(){

	int val;

	tree* avl = NULL;

 	for(int i=0;i<6;i++){
		cin>>val;
		avl= insertion(avl,val);
	}

	print_tree(avl);
	return 0;

}
