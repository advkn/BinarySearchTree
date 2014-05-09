//Binary Search Tree class  -- The main class that faciliates the creation, deletion and traversal of nodes in a binary tree.

#include <iostream>
#include <list>
using namespace std;
#include "TreeNode.h"


class Tree {

	Node* root;
public:


	//deafult ctor
	Tree() {
		 root = NULL;
	}

	//destructor
	~Tree() {
		 freeNode(root);
	}

	//return the root node
	Node* Root() {
		return root;
	}

	/*Function accepts a node as a parameter
	and returns the data stored in it.
	*/
	

	// Free the node
	void freeNode(Node* leaf)
	{
		if ( leaf != NULL )
		{
		   freeNode(leaf->Left());
		   freeNode(leaf->Right());
		   free(leaf);
		}
	}

	// Add a node to a 0 height tree
	void addNode(int key) {
		 //If no previous existing elements, add node as root node
		 if ( root == NULL ) {
			cout << "add root node ... " << key << endl;
			Node* n = new Node();
			n->setKey(key);
			root = n;
		 }
		 //defer control to the overloaded addNode() method
		 else {
			cout << "add other node ... " << key << endl;
			addNode(key, root);
		 }
	}

	//Overloaded addNode which determines where to add a node based on the location of previously inserted nodes. It is a recursive funtion.
	void addNode(int key, Node* leaf) {
		if(key <= leaf->Key()) {
			if(leaf->Left() != NULL) {
				addNode(key, leaf->Left());
			}
			else {
				Node *n = new Node();
				n->setKey(key);
				n->setParent(leaf);
				leaf->setLeft(n);
			}
		}
		else {
			if(leaf->Right() != NULL) {
				addNode(key, leaf->Right());
			}
			else {
				Node *n = new Node();
				n->setKey(key);
				n->setParent(leaf);
				leaf->setRight(n);
			}
		}
	}

	//Find a node
	Node* findNode(int key, Node* node) {

		if(node == NULL) {
			return NULL;
		}
		else if(node->Key() == key) {
			return node;
		}
		else if(key < node->Key()) {
			findNode(key, node->Left());
		}
		else if(key > node->Key()) {
			findNode(key, node->Right());
		}
		else {
			return NULL;
		}

	}


	//Print the tree
	void walk(Node* node) {
		if(node) {
			cout << node->Key() << " ";
			walk(node->Left());
			walk(node->Right());
		}
	}

	//Find the minimum node in the tree by traversing the left side of the tree recursively.
	Node* findMin(Node* node) {
		if(node->Key() == NULL) {
			return NULL;
		}
		else if(node->Left()) {
			findMin(node->Left());
		}
		else {
			return node;
		}
	}

	//Find the maximum node by traversing the right side of the tree recursively
	Node* findMax(Node* node) {
		if(node->Key() == NULL) {
			return NULL;
		}
		else if(node->Right()) {
			findMax(node->Right());
		}
		else {
			return node;
		}
	}
	
	//Find the successor to a Node
	Node* successor(int key, Node* node) {
		Node* thisKey = findNode(key, node);
		if(thisKey) {
			return findMax(thisKey->Right());
		}
	}

	//Find the predecessor to a Node
	Node* predecessor(int key, Node* node) {
		Node* thisKey = findNode(key, node);
		if(thisKey) {
			return findMax(thisKey->Left());
		}
	}

	//Find the LCA(Least Common Ancestor) of the binary tree, given two nodes
	Node* FindLCA(Node* root, Node* node2, Node* node3) {
		while(root != NULL) {

			if((node2->Key() < root->Key() && node3->Key() > root->Key()) ||
				node2->Key() > root->Key() && node3->Key() < root->Key()) {
					return root;
			}

			if(node2->Key() < root->Key()) {
				root = root->Left();
			}
			else {
				root = root->Right();
			}
		}
	}


	//Check if a binary tree is a BST.
	int IsBST(Node* root) {
		if(root == NULL) {
			return 1;
		}
		//false if the max of the left is > root
		if(root->Left() != NULL && findMax(root->Left())->Key() > root->Key()) {
			return 0;
		}

		//false if the min of right is <= root
		if(root->Right() != NULL && findMin(root->Right())->Key() < root->Key()) {
			return 0;
		}

		//false if recursively, the left or right is not a BST
		if(!IsBST(root->Left()) || !IsBST(root->Right())) {
			return 0;
		}

		return 1;
	}

	//Check if BST using inorder traversal. Improved complexity from the previous IsBST() funciton
	/*The idea behind this is that, inorder traversal of a BST produces a sorted list.  Therefore, while traversing
	the BST inoder, at each node, check the condition that each node's value should be GREATER than the value of
	the previously visited node.  Also, the value prev needs to be initialized with a minimum int value(INT_MIN)
	before being used, and passed into the function as a reference.*/
	int IsBST2(Node* root, int* prev) {
		if(root) {
			return 1;
		}
		//left subtree
		if(!IsBST2(root->Left(), prev)) {
			return 0;
		}
		//check if current node value is less than previous node value
		if(root->Key() < *prev) {
			return 0;
		}
		*prev = root->Key();		//make current node, previous node
		return IsBST2(root->Right(), prev);		//right subtree

	}


	//Print all the elements between the ranges K1 and K2
	void RangePrinter(Node* root, int K1, int K2) {
		if(root == NULL) {
			return;
		}
		if(root->Key() >= K1) {
			RangePrinter(root->Left(), K1, K2);
		}
		if(root->Key() >= K1 && root->Key() <= K2) {
			cout << root->Key() << " ";
		}
		if(root->Key() <= K2) {
			RangePrinter(root->Right(), K1, K2);
		}
	}

	//Append function for converting a BST to a Circular DLL
	Node* Append(Node* a, Node* b) {
		Node *aList, *bList;

		if(a == NULL) {
			return b;
		}
		if(b == NULL) {
			return a;
		}
		aList = a->Left();		//assign the respective subtree
		bList = b->Left();		//assign the respective subtree

		//the following left and right settings make the list completely circular.
		b->setLeft(aList);
		bList->setRight(a);
		a->setLeft(bList);

		return a;
	}

	Node* TreeToList(Node* root) {
		Node *aList, *bList;
		if(root == NULL) {
			return NULL;
		}

		aList = TreeToList(root->Left());
		bList = TreeToList(root->Right());
		root->setLeft(root);
		root->setRight(root);
		aList = Append(aList, root);
		aList = Append(aList, bList);

		return aList;
	}

	Node* kthSmallestInBST(Node* root, int k, int count) {
		if(!root) {
			return NULL;
		}

		Node* left = kthSmallestInBST(root->Left(), k, count);
		if(left) {
			return left;
		}
		if(++count == k) {
			return root;
		}

		return kthSmallestInBST(root->Right(), k, count);
	}

	//Find the 'next' node (i.e. inorder successor) of a given node in a BST
	Node* inOrderSucc(Node* n) {
		if(n == NULL) {
			return NULL;
		}

		/*Found right children -> return the left most node of the right subtree.*/
		if(n->Parent() == NULL || n->Right() != NULL) {
			return leftMostNode(n->Right());
		}
		else {
			Node* q = n;
			Node* x = q->Parent();

			/*Go up until we are on the left instead of the right*/
			while(x != NULL && x->Left() != q) {
				q = x;
				x = x->Parent();
			}
			return x;
		}
	}

	/*Return the left most node in a BST*/
	Node* leftMostNode(Node* n) {
		if(n == NULL) {
			return NULL;
		}
		while(n->Left() != NULL) {
			n = n->Left();
		}
		
		return n;
	}


	//NOT COMPLETE. gives an Access error
	/* Delete a node
	 (1) If leaf just delete.
	 (2) If only one child delete this node and replace with the child.
	 (3) If 2 children. Find the predecessor (or successor).
	 Delete the predecessor (or successor). Replace the node to be deleted with the predecessor (or successor).
	 */
	Node* Delete(int key, Node* node) {
		Node* temp;

		
		if(node == NULL) {
			return NULL;
		}
		//recursively traverse left subtree until node is found
		else if(key < node->Key()) {
			Delete(key, node->Left());
		}
		//recursively traverse right subtree until node is found
		else if(key > node->Key()) {
			Delete(key, node->Right());
		}
		//found element
		else {
			//the node to be deleted has both left and right children
			if(node->Left() && node->Right()) {
				//replace that node with the largest node in the subtree
				temp = findMax(node->Left());
				node->setKey(temp->Key());
				node->setLeft(Delete(node->Key(), node->Left()));
			}
			else if(node->Right()) {
				//replace that node with the largest node in the subtree
				temp = node->Right();
				node->Parent()->setRight(temp);
				//node->setRight(Delete(node->Key(), node->Right()));
				delete node;
			}
			else if(node->Left()) {
				//replace that node with the largest node in the subtree
				temp = findMax(node->Left());
				node->setKey(temp->Key());
				node->setLeft(Delete(node->Key(), node->Left()));
			}
			//one child
			else {
				temp = node;
				if(temp->Key() == key) {
					if(temp->Parent()->Left()->Key() == key) {
						temp->Parent()->setLeft(NULL);
					}
					if(temp->Parent()->Right()->Key() == key) {
						temp->Parent()->setRight(NULL);
					}
				}
				/*else if(node->Right() == NULL) {
					node = node->Left();
					//node->Parent()->setLeft(NULL);
				}*/
				delete node;
			}
		}
		//return node;

	}

};