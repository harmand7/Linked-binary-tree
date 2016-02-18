#include "bintree.h"
#include <algorithm>    // std::max //used for get height.

//Harman Dhunna
//------------------------- Constructor ---------------------------------
//Default. 
//Takes in no parameters, just sets the root to NULL so it can initiate the
//tree.
//------------------------- Constructor ---------------------------------

BinTree::BinTree()
{
	root = NULL;
}

/*
-------------------------Copy Constructor -----------------------------------
Sets root NULL to all for initiation of the object without having loss 
pointers
Deep copy. Uses the assignment operator.
-----------------------------------------------------------------------------
*/

BinTree::BinTree(const BinTree &copy)
{
	this->root = NULL;
	*this = copy;
}
/*
------------------------- Destructor ---------------------------------------
Completes whips the Tree of any data
Deletes any connecting node that go along with it.
-----------------------------------------------------------------------------
*/

BinTree::~BinTree()
{
	this->makeEmpty();
}

/*
------------------------- isEmpty -------------------------------------------
Returns if the head/root node is NULL. If the root is NULL then all of the
following data is NULL and therefore the tree is empty

-----------------------------------------------------------------------------
*/


bool BinTree::isEmpty() const
{
	return (root == NULL);
}

/*
-------------------------makeEmpty -----------------------------------
Calls a recursive Function that empties the tree
-----------------------------------------------------------------------------
*/

void BinTree::makeEmpty()
//post order
{
	if (root != NULL)
	{
		recursiveMakeEmpty(root);
	}
}

/*
-------------------------recursiveMakeEmpty ---------------------------------
This post order recursiveve
keeps going till it reaches null then goes right
then deletes right 
deletes left
then deletes root
returns true if there was something to delete
-----------------------------------------------------------------------------
*/


bool BinTree::recursiveMakeEmpty(Node *&current)
{
	if (current != NULL)
	{
		recursiveMakeEmpty(current->left);
		recursiveMakeEmpty(current->right);

		if (current->data != NULL)
		{
		//	delete current->data;
			current->data = NULL;
		}
		//delete current->data;
		delete current;
		current = NULL;
		
		return true;
	}
	return false;
}

/*
-------------------------operator= ---------------------------------
Calls helper function
before doing so calls empty to clear out the tree
-----------------------------------------------------------------------------
*/

BinTree& BinTree::operator=(const BinTree &copy)
{
	if (*this == copy)
	{
		return *this;
	}
	this->makeEmpty();
	recursiveAssignment(copy.root);
	return *this;
}
/*
-------------------------recursiveAssignmenr ---------------------------------
This is pre order
first the root data gets assigned then the left then the right
goes till it reaches the null node then comes back to the previous layer to
insert the data.
-----------------------------------------------------------------------------
*/


void BinTree::recursiveAssignment(Node* curr )
{
	if (curr != NULL)
	{
		this->insert(curr->data);
		recursiveAssignment(curr->left);
		recursiveAssignment(curr->right);
	}
}

/*
------------------------- operator==  --------------------------------------
calls helper function
-----------------------------------------------------------------------------
*/

bool BinTree::operator==(const BinTree &val) const
{
	return isEqual(this->root, val.root);
}

/*
------------------------- isEquals and operator!= ------------------------
checks if the initial nodes are either equal or null
then checks if one is null and the other is not
this allows for two cases of inequality to be crossed out
then it is boolean algebra with the two return statements


operator !=
negations of operator==
-----------------------------------------------------------------------------
*/


bool BinTree::isEqual(Node *thisPtr, Node* thatPtr) const
{
	if (thisPtr == NULL && thatPtr == NULL)
	{
		return true;
	}
	else if (thisPtr == NULL || thatPtr == NULL)
	{
		return false;
	}
	else if ((*thisPtr->data == *thatPtr->data) && (thisPtr->left == NULL&& thatPtr->left==NULL) && (thisPtr->right == NULL &&thatPtr->right == NULL))
	{
		return true;
	}
	else
	{
		return ((*thisPtr->data == *thatPtr->data) && isEqual(thisPtr->left, thatPtr->left) && isEqual(thisPtr->right,thatPtr->right));
	}
	return false;
}
bool BinTree::operator!=(const BinTree &val) const
{
	return !(*this == val) ;
}

/*
------------------------- Insert   ---------------------------------
calls helper function
-----------------------------------------------------------------------------
*/

bool BinTree::insert(NodeData *ptr)
{
	return recursiveInsert(ptr, root);
}

/*
------------------------- Recursive Insert Helper ---------------------------
if the first node passed in is null then create the new Node for data 
allocation. This becomes the base case

if not then evaluate the value of the data in comparssion with the node's 
data

then pick which side to go

reach the two possible base case
1. node is not a duplicate and is NULL be added to the list return true
2. node is a duplicate and return false;
-----------------------------------------------------------------------------
*/

bool BinTree::recursiveInsert(NodeData * val, Node*&curr)
{
	if (curr == NULL)
	{
		curr = new Node();
		curr->data = val;
		curr->left = curr->right = NULL;
		return true;
	}
	else if (*val > *curr->data)
	{
		return recursiveInsert(val, curr->right);
	}
	else if (*val < *curr->data)
	{
		return recursiveInsert(val, curr->left);
	}
	else // Duplication: return false;
	{
		return false;
	}
}

/*
------------------------- Retrieve   ----------------------------------------
calls helper function after few checks of weather the address is null or
if the root == null
-----------------------------------------------------------------------------
*/

bool BinTree::retrieve(const NodeData & find, NodeData*& gotIT) const
{
	if (&find == NULL)
	{
		return false;
	}
	if (root == NULL)
	{
		return false;
	}
	return retrieveRecussive(find, gotIT, root);
}

/*
------------------------- retrieveRrecursive --------------------------------
if the node passed in NULL then it is in the tree; base case
After that it is similar to insert as it checks the value of the find(target)
against the node's data.
-----------------------------------------------------------------------------
*/

bool BinTree::retrieveRecussive(const NodeData &find, NodeData*& gotIT, Node *ptr) const
{
	if (ptr == NULL)
	{
		gotIT = NULL;
		return false;
	}
	else if (*ptr->data == find)
	{
		gotIT = ptr->data;
		return true;
	}
	else if (*ptr->data < find)
	{
		return retrieveRecussive(find, gotIT, ptr->right);
	}
	else
	{
		return retrieveRecussive(find, gotIT, ptr->left);
	}
}


/*
-------------------------Get Height--------------------------------

calls recursive helper function

-----------------------------------------------------------------------------
*/

int BinTree::getHeight(const NodeData &find)const
{
	return preOrderNodeRetrieve(find, root);
}

/*
---------------------preOrderNodeRetrieve  ----------------------------------

similar to the retrieve it searchs the tree, except it does not compare and
returns when the value is found 

once the data is found it calls another recursive helper function to obtain
its height 
-----------------------------------------------------------------------------
*/

int BinTree::preOrderNodeRetrieve(const NodeData& find, Node* ptr) const
{
	if (ptr == NULL)
	{
		return 0;
	}
	else if (*ptr->data == find)
	{
		return recGetHeight(ptr);
	}
	else
	{
		int left = preOrderNodeRetrieve(find, ptr->left);
		int right = preOrderNodeRetrieve(find, ptr->right);
		return max(left, right);
	}
}

/*
-------------------------recGetHeight---------------------------------------
recursive goes troughs the parents Node in order to find the height
for each layer of recursion it adds one. But each time it returns from the 
recursion it finds the max value
-----------------------------------------------------------------------------
*/
int BinTree::recGetHeight(Node*ptr) const
{
	if (ptr == NULL)
	{
		return 0;
	}
	else
	{
		return 1 + max(recGetHeight(ptr->left),recGetHeight(ptr->right));
	}
}

/*
-------------------------bstreeToArray---------------------------------------

calls recursive helper function
then empties the tree with the help of makeEmpty
-----------------------------------------------------------------------------
*/

void BinTree::bstreeToArray(NodeData*val[] )
{
	
	//in order
	//left root right
	//store the value
	fillArrayRecursive(root, val);
	this->makeEmpty();

}

/*
-------------------------fillArrayRecursive ---------------------------------
As long as the node is not null it adds the value accordingly to the array
It is in order.
First the left child, then the parent, then the right child
Deep copy of ptr for the NodeData

The int returned is used to set the index of the inserting of the NodeData*
-----------------------------------------------------------------------------
*/


int BinTree::fillArrayRecursive(Node *ptr, NodeData* val[])
{
	//How to move the pointer of the NodeData to pointers in the array
	if (ptr != NULL)
	{
		int left = fillArrayRecursive(ptr->left, val);
		NodeData* temp = ptr->data;
		ptr->data = NULL;
		val[left] = temp;
		temp = NULL;
		int right=fillArrayRecursive(ptr->right, val+left+1);
		return left + right + 1;
	}
	return 0;
}

/*
-------------------------ArrayToBstree---------------------------------------
Makes the tree empty
then gets the size of the array
Calls a helper function
-----------------------------------------------------------------------------
*/

void BinTree::arrayToBSTree(NodeData *val[] )
{
	this->makeEmpty();
	//uses the getArraySize() function to get the size.
	int indexSize = getArraySize(val);
	//Helper Function
	fillTree(val,0,indexSize-1);
}

/*
------------------------- FillTree-------------------------------------------
finds the midpoint index and the inserts that first into the tree
then the splits the recursion into half the size of the arr allowing it work
like a quick sort
-----------------------------------------------------------------------------
*/

void BinTree::fillTree(NodeData* arr[], int start, int end)
{
	if (start > end)
	{
		return;
	}
	else
	{
		int mid = (end + start) / 2;
		//NodeData copyPtr(*arr[mid]);
		NodeData *ptr = arr[mid];
		arr[mid] = NULL;
		this->insert(ptr);
		fillTree(arr, start, mid - 1);
		fillTree(arr, mid + 1, end);
	}
}

/*
------------------------- getArraySize --------------------------------------
A while loop to get the size of the array.
-----------------------------------------------------------------------------
*/

int BinTree::getArraySize(NodeData* arr[])
{
	int i = 0;
	while (arr[i] != NULL)
	{
		i++;
	}
	return i;
}

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const
{
	sideways(root, 0);
}
//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "  ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}

/*
-------------------------Operator<<  ---------------------------------------

calls recursive helper function and sends the out ostream with it

-----------------------------------------------------------------------------
*/

ostream& operator<<(std::ostream &out, const BinTree &val)
{
	val.inorderHelper(out, val.root);
	out << endl;
	return out;
}

/*
------------------------- inorderHelper -------------------------------------
If not null then go left child then it will reach null and add the value of
the parent data to out stream, then go right and add the data from there in
in order traversal. 
-----------------------------------------------------------------------------
*/

void BinTree::inorderHelper(std::ostream& out, Node* ptr) const
{
	if (ptr != NULL)
	{
		inorderHelper(out, ptr->left);
		out << *ptr->data << "  ";
		inorderHelper(out, ptr->right);
	}
}
