//Node class for a Binary Search Tree impementation
#include <iostream>


class Node {

    int key;
    Node* left;
    Node* right;
	Node* parent;

public:

    Node() { 
		key=-1; 
		left=NULL; 
		right=NULL; 
	}

    void setKey(int aKey) { 
		key = aKey; 
	}

    void setLeft(Node* aLeft) { 
		left = aLeft; 
	}

    void setRight(Node* aRight) { 
		right = aRight; 
	}

	void setParent(Node* aParent) {
		parent = aParent;
	}

    int Key() { 
		return key; 
	}

    Node* Left() { 
		return left; 
	}

    Node* Right() { 
		return right; 
	}

	Node* Parent() {
		return parent;
	}

};