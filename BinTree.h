#pragma once
using namespace std;
#include "nodedata.h"


//Harman Dhunna
class BinTree 
{				// you add class/method comments and assumptions

	friend ostream& operator<<(std::ostream &out, const BinTree &val);	// prints the tree
public:
	BinTree();								// constructor
	BinTree(const BinTree &copy);			// copy constructor
	~BinTree();								// destructor, calls makeEmpty	

	int getHeight(const NodeData &)const;	//gets the height of the tree
	void bstreeToArray(NodeData*val[]);		//takes the tree and stores it in an array 
	void arrayToBSTree(NodeData *val[]);	//takes the array and made it into balanced array

	bool isEmpty() const;					//true if tree is empty, otherwise false
	void makeEmpty();						//make the tree empty so isEmpty returns true
	BinTree& operator=(const BinTree &);	//Assignment operator. Assigns the rhs to lhs 
	bool operator==(const BinTree &ref) const;	//equals operator; deep check
	bool operator!=(const BinTree &ref) const;	//not equals
	bool insert(NodeData*ptr);				//insert NodeData ptr into the tree
	bool retrieve(const NodeData &, NodeData*&) const;	//retrieves the data, also checks if its in the tree
	void displaySideways() const;	// provided below, displays the tree sideways

private:	//Private helper function
	struct Node {
		NodeData* data = NULL;			// pointer to data object
		Node* left = NULL;				// left subtree pointer
		Node* right = NULL;				// right subtree pointer
	};
	Node* root;			// root of the tree

	bool recursiveInsert(NodeData* ptrVal, Node* &val);		//recessively inserts a val 
	void recursiveAssignment(Node*);						// utility functions
	void inorderHelper(std::ostream& out, Node* retVal) const;	//output helper
	void sideways(Node* ptr, int val) const;				// provided below, helper for displaySideways()
	bool recursiveMakeEmpty(Node* &root);					// recursively empties the tree
	bool retrieveRecussive(const NodeData &find, NodeData*& gotIT, Node *ptr) const;	//retrieve helper
	int preOrderNodeRetrieve(const NodeData &find, Node* ptr) const;	//Pre-order helper to get the data
	int recGetHeight(Node*ptr) const;	//gets the height for the tree
	int fillArrayRecursive(Node *ptr, NodeData* val[]);	//bstreetoArray helper
	int getArraySize(NodeData* arr[]);		//gets the size of the array
	void fillTree(NodeData* arr[], int low, int high);	//array fills the tree helper
	bool isEqual(Node *, Node*) const;		//helper for the operator==
};