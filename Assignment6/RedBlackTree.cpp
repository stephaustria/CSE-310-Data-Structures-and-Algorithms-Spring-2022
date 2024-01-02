//************************************************************************
// ASU CSE310 Assignment #6 Spring 2022
// Author: Stephen Austria
// ASU ID: 1220159551
// Description: Red black tree implementation. See RedBlackTree.h
//              for the Red Black Tree definition
//************************************************************************

//must include the head file
#include "RedBlackTree.h"

using namespace std;

//*******************************************************************
//constructor
RedBlackTree::RedBlackTree()
{
	//initialize an empty RedBlackTree
	root = NULL;
	this->count = 0;
}

//*******************************************************************
//destructor
RedBlackTree::~RedBlackTree()
{
	//delete all nodes, release memory
	int numOfNodes = count;
	deleteNode(root);
	cout << "The number of nodes deleted: " << numOfNodes << endl;
}

//**************************************************************
//Accessor for the root of the red-black tree
Node* RedBlackTree::getRoot()
{
	//returns the root
	return this->root;
}

//*******************************************************************
//delete the sub-tree rooted at 'node' and return number of nodes deleted
//This should be defined as a recursive function
int RedBlackTree::deleteNode(Node* node)
{
	int c = 0;
	if (node == NULL)
		return 0;
	else
	{
		//will count when a left child or right child is deleted
		c = c + this->deleteNode(node->leftChild);
		c = c + this->deleteNode(node->rightChild);

		//deletes the node
		delete(node);
		//will increment
		c = c + 1;

		return c;
	}
}

//****************************************************************
//This is the general BST insertion operation.
//It does not care about the color of the newly added node.
void RedBlackTree::insertNode(Node* node)
{
	Node* y = new Node;
	Node* x = new Node;

	string key = to_string(node->id) + node->firstName + node->lastName;

	y = NULL;
	//x is the root
	x = root;

	//loop will keep going down until there are no more leaf nodes
	while (x != NULL) {
		y = x;

		//if x is greater than the key, then go down to its left child
		if (compareNodes(x, key) > 0) {
			x = x->leftChild;
		}
		//if x is less than they key, then go down to its right child 
		else {
			x = x->rightChild;
		}
	}
	
	node->parent = y;
	
	if (y == NULL) {
		root = node;
	}
	
	else if (compareNodes(y, key) > 0) {
		y->leftChild = node;
	}
	else {
		y->rightChild = node;
	}
	count++; 
}

//*******************************************************************
//At beginning, each newly added node will always be RED,
//this may violate the red-black tree property #4. fixUp()
//function will restore the property.
void RedBlackTree::fixUp(Node* z)
{
	Node* y = new Node;
	Node* zp = z->parent;

	string red = "RED";
	string black = "BLACK";

	if (zp != NULL) {

		//this loop will go through the cases of a red and black tree.
		while (z->parent->color.compare(red) == 0) {

			//if the parent is not a left child
			if (z->parent != z->parent->parent->leftChild) {

				if (z->parent->parent->leftChild != NULL) {

					//y will be the uncle node
					y = z->parent->parent->leftChild;

					//if uncle and parent are red nodes
					if (y->color.compare(red) == 0) {
						z->parent->color = black;
						y->color = black;
						z->parent->parent->color = red;
						z = z->parent->parent;

					}
					//if uncle is a black node
					else {

						//rotate right
						if (z == z->parent->leftChild) {
							z = zp;
							rightRotate(z);
						}

						//rotate left
						z->parent->color = black;
						z->parent->parent->color = red;
						leftRotate(z->parent->parent);
					}
				}
				else {
					//node is left child of a right child
					if (z == z->parent->leftChild) {
						z = zp;
						rightRotate(z);
					}
					//if node is a right child of a right child
					z->parent->color = black;
					z->parent->parent->color = red;
					leftRotate(z->parent->parent);


				}
			}

			else {


				if (z->parent->parent->rightChild != NULL) {

					y = z->parent->parent->rightChild;
					//if uncle and parent are red

					if (y->color.compare(red) == 0) {

						z->parent->color = black;
						y->color = black;
						z->parent->parent->color = red;
						z = z->parent->parent;

					}
					//if uncle is black
					else {
						//rotate left
						if (z == z->parent->rightChild) {
							z = z->parent;
							leftRotate(z);
						}
						//rotate right
						z->parent->color = black;
						z->parent->parent->color = red;
						rightRotate(z->parent->parent);

					}
				}
				else {
					//if node is a right child of a left child
					if (z == z->parent->rightChild) {
						z = zp;
						leftRotate(z);
					}
					//if node is a left child of a left child
					z->parent->color = black;
					z->parent->parent->color = red;
					rightRotate(z->parent->parent);

				}
			}

			if (z == root) {
				break;
			}
		}
	}
	//the root will always be set to black
	root->color = black;
}

//*****************************************************
//This function print the pre-order traversal of the
//subtree rooted at 'node'.It's a recursive function
void RedBlackTree::preOrderTraversal(Node* node)
{
	if (node == NULL) {
		return;
	}
	else {
		//start at the root
		this->print(node);
		//take all of the left children first
		this->preOrderTraversal(node->leftChild);
		//then take all of the right children
		this->preOrderTraversal(node->rightChild);
	}
}

//**************************************************
//This function print the in-order traversal of the
//subtree rooted at 'node'.It's a recursive function
void RedBlackTree::inOrderTraversal(Node* node)
{
	if (node == NULL) {
		return;
	}
	else {
		//start at left node
		this->inOrderTraversal(node->leftChild);
		//get the node 
		this->print(node);
		//move right one node 
		this->inOrderTraversal(node->rightChild);
	}
}

//**************************************************
//This function print the post-order traversal of the
//subtree rooted at 'node'.It's a recursive function
void RedBlackTree::postOrderTraversal(Node* node)
{
	if (node == NULL) {
		return;
	}
	else {
		//take all the left children
		this->postOrderTraversal(node->leftChild);
		//thentake right children
		this->postOrderTraversal(node->rightChild);
		//print the node
		this->print(node);
	}
}

//**************************************************************
//This function returns a pointer points to the minimum node from
//the current sub-tree rooted at 'node'. It should be designed as
//a recursive function
Node* RedBlackTree::findMinimumNode(Node* node)
{
	if (node == NULL)
	{
		cout << "Tree is empty, no MINIMUM." << endl;
		return node;
	}
	else
	{
		while (node->leftChild != NULL) {
			node = node->leftChild;
		}

		return node;
	}
}

//**************************************************************
//This function returns a pointer points to the maximum node from
//the current sub-tree rooted at 'node'. It should be designed as
//a recursive function
Node* RedBlackTree::findMaximumNode(Node* node)
{
	if (node == NULL)
	{
		cout << "Tree is empty, no MAXIMUM." << endl;
		return node;
	}
	else
	{
		while (node->rightChild != NULL) {
			node = node->rightChild;
		}

		return node;
	}
}

//**************************************************************
//This function search the tree for a given key of a Student
//Note: key is the combination of id, firstName and lastName
//It returns a pointer points to the node if founded; otherwise it returns NULL
Node* RedBlackTree::treeSearch(int id, string firstName, string lastName)
{
	string id1 = to_string(id);
	//student key
	string keyA = id1 + firstName + lastName;
	Node* node = new Node;
	node = root;
	bool f = false;

	
	while (node != NULL) {
		//if node is greater than the key, then go down to the left child
		if (compareNodes(node, keyA) >= 1) {
			node = node->leftChild;
		}
		//if node is less than the key, then go down to the right child
		else if (compareNodes(node, keyA) <= -1) {
			node = node->rightChild;
		}
		//if node and key are equal, break
		else {
			f = true;
			break;
		}
	}
	
	if (f) {
		cout << left;
		cout << setw(8) << id
			<< setw(12) << firstName
			<< setw(12) << lastName
			<< " is FOUND." << endl;
	}
	else {
		cout << left;
		cout << setw(8) << id
			<< setw(12) << firstName
			<< setw(12) << lastName
			<< " is NOT FOUND." << endl;
	}
	return node;
}

//****************************************************
//This function left-rotate the BST rooted at 'node'
void RedBlackTree::leftRotate(Node* x)
{
	if (x == NULL) {
		return;
	}
	else {
		Node* y = x->rightChild;
		//y left child and x right child are equal
		x->rightChild = y->leftChild;

		if (y->leftChild != NULL) {
			y->leftChild->parent = x;
		}

		//positions of x and y are rotated
		y->parent = x->parent;
		if (x->parent == NULL) {
			this->root = y;
		}
		else if (x == x->parent->leftChild) {
			x->parent->leftChild = y;
		}
		else {
			x->parent->rightChild = y;
		}

		y->leftChild = x;
		x->parent = y;
	}
}

//***************************************************
//This function right-rotate the BST rooted at 'node'
void RedBlackTree::rightRotate(Node* y)
{
	if (y == NULL) {
		return;
	}
	else {
		Node* x = y->leftChild;

		//y left child and x right child are equal to each other
		y->leftChild = x->rightChild;
		if (x->rightChild != NULL) {
			x->rightChild->parent = y;
		}

		//positions of x and y are rotated
		x->parent = y->parent;
		if (y->parent == NULL) {
			this->root = x;
		}
		else if (y == y->parent->leftChild) {
			y->parent->leftChild = x;
		}
		else {
			y->parent->rightChild = x;
		}
		x->rightChild = y;
		y->parent = x;
	}
}

//**************************************************************
//This function finds the predecessor of the given 'node'
//it prints the relevant predecessor info. on screen and also
//return a pointer that points to the predecessor
Node* RedBlackTree::findPredecessorNode(Node* node)
{
	Node* y = new Node;
	Node* pred = new Node;

	if (node->leftChild != NULL) {

		//finf max of the left side of the tree
		pred = findMaximumNode(node->leftChild);
	}
	else {
		y = node->parent;

		while (y != NULL && node == y->leftChild) {
			node = y;
			y = y->parent;
		}
		//predecessor = y if max not found 
		pred = y;
	}
	
	if (pred != NULL) {
		cout << left;
		cout << "Its Predecessor is: " << endl;
		print(pred);
	}
	else {
		cout << left;
		cout << "Its Predecessor does NOT EXIST" << endl;
	}
	return pred;
}

//**************************************************************
//This function finds the successor of the given 'node'
//it prints the relevant successor info. on screen and also return
//a pointer that points to the successor node
Node* RedBlackTree::findSuccessorNode(Node* node)
{
	Node* y = new Node;
	Node* succ = new Node;
	
	if (node->rightChild != NULL) {
		//find min on the left side of the tree
		succ = findMinimumNode(node->rightChild);
	}
	else {
		y = node->parent;

		while (y != NULL && node == y->rightChild) {
			node = y;
			y = y->parent;
		}
		//successor = y, if min not found
		succ = y;
	}
	
	if (succ != NULL) {
		cout << left;
		cout << "Its Successor is: " << endl;
		print(succ);
	}
	else {
		cout << "Its Successor does NOT EXIST" << endl;
	}
	return succ;
}

//****************************************************************
//This function find the minimum node of the entire red-black tree
//It print out the minimum node info. on screen if tree is not empty
//or print 'Tree is empty' message on screen.
void RedBlackTree::treeMinimum()
{
	if (root == NULL) {
		cout << "Tree is empty. No Minimum." << endl;
		return;
	}
	else {
		cout << "The MINIMUM is:" << endl;
		//print min
		this->print(this->findMinimumNode(this->root));

	}
}

//**************************************************************
//This function find the maximum node of the entire red-black tree
//It print out the maximum node info. on screen if tree is not empty
//or print 'Tree is empty' message on screen.
void RedBlackTree::treeMaximum()
{
	if (root == NULL) {
		cout << "Tree is empty. No Maximum." << endl;
		return;
	}
	else {
		cout << "The MAXIMUM is:" << endl;
		//print max
		this->print(this->findMaximumNode(this->root));

	}
}

//****************************************************************************
//This function print out the pre-order traversal of the entire red-black tree
void RedBlackTree::treePreorder()
{
	this->preOrderTraversal(this->root);
}

//***************************************************************************
//This function print out the in-order traversal of the entire red-black tree
void RedBlackTree::treeInorder()
{
	this->inOrderTraversal(this->root);
}

//*****************************************************************************
//This function print out the post-order traversal of the entire red-black tree
void RedBlackTree::treePostorder()
{
	this->postOrderTraversal(this->root);
}

//******************************************************************
//Given a Student key, this function first check whether the
//student is inside the tree or not, if it is inside, it will print
//its predecessor info. on screen, if not, it print an error message
void RedBlackTree::treePredecessor(int id, string firstName, string lastName)
{
	if (root == NULL)
		cout << "Tree is empty. No Predecessor." << endl;
	else
	{
		this->findPredecessorNode(this->treeSearch(id, firstName, lastName));

	}
}

//******************************************************************
//Given a Student key, this function first check whether the
//student is inside the tree or not, if it is inside, it will print
//its successor info. on screen, if not, it print an error message
void RedBlackTree::treeSucessor(int id, string firstName, string lastName)
{
	if (root == NULL)
		cout << "Tree is empty. No Successor." << endl;
	else
	{
		this->findSuccessorNode(this->treeSearch(id, firstName, lastName));
	}
}

//**************************************************************
//This function create a node from the given info., then insert
//the node inside the red-black tree. Note: at beginning, the newly
//added node should always be 'RED'
void RedBlackTree::treeInsert(int id, string firstName, string lastName, double gpa)
{
	Node* myNode = new Node;
	myNode->id = id;
	myNode->firstName = firstName;
	myNode->lastName = lastName;
	myNode->gpa = gpa;
	myNode->color = "RED";
	//left child and right child are null
	myNode->leftChild = NULL;
	myNode->rightChild = NULL;
	myNode->parent = NULL;
	//calls insert node to create a binary search tree
	this->insertNode(myNode);
	//calls fix up to turn the BST into a red black tree
	this->fixUp(myNode);
}

//******************************************************************
//Given a 'node', this function prints all the node information on screen
void RedBlackTree::print(Node* node)
{
	cout << left;
	cout << setw(8) << node->id
		<< setw(12) << node->firstName
		<< setw(12) << node->lastName
		<< setw(10) << fixed << setprecision(2) << node->gpa;
	cout << right << setw(7) << node->color << endl;
}

//**************************************************************
//Given a Node 'node1', this function compares it with another
//node's key.
//key is a string combination of it + firstName + lastName
//It returns a negative number if in alphabetical order, key2 is
//in front of 'node1'; otherwise it returns a positive number
int RedBlackTree::compareNodes(Node* node1, string key2)
{
	int id1 = node1->id;
	string id = to_string(id1);
	string keyA = id + node1->firstName + node1->lastName;

	//comapring the keys
	return keyA.compare(key2);
}
