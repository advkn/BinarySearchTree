//Test class for a Binary Search Tree
#include "Tree.h"
#include <array>
using namespace std;

//Takes a presorted array and converts it into a balanced BST.
	Node* BuildBST(int A[], int start, int end) {
		Node* newNode;
		int mid;

		if(start > end) {
			return NULL;
		}

		newNode = new Node();
		if(!newNode) {
			cout << "Memory error";
			return NULL;
		}

		//only one element in array
		if(start == end) {
			newNode->setKey(A[start]);
			newNode->setLeft(NULL);
			newNode->setRight(NULL);
		}
		//recusively find the midpoints of each sub problems(arrays), and build both the left and right trees
		else {
			mid = start + (end - start)/2;
			newNode->setKey(A[mid]);
			newNode->setLeft(BuildBST(A, start, mid-1));
			newNode->setRight(BuildBST(A, mid+1, end));
		}
		return newNode;
	}

	//utility tree print function
	void walk2(Node* node) {
		if(node) {
			cout << node->Key() << " ";
			walk2(node->Left());
			walk2(node->Right());
		}
	}

	//Utility function to print a BST converted to a Circular DLL.
	void walk3(Node* node) {
		Node* temp = node;
		while(node->Left() != temp->Right()) {
			cout << node->Key() << " ";
			node = node->Left();
		}
		cout << node->Key();	//prints the last node
	}



void main() {

	int myArray[] = {1,2,3,4,5,6,9,10,15};

	Tree* myTree = new Tree();

	myTree->addNode(350);
	myTree->addNode(100);
	myTree->addNode(150);
	myTree->addNode(24);
	myTree->addNode(119);
	myTree->addNode(395);
	myTree->addNode(455);
	myTree->addNode(488);
	myTree->addNode(500);

	Node* treeRoot = myTree->Root();
	
	//test findNode function starting at the root node
	cout << "\nFound node: " << myTree->findNode(24, myTree->Root())->Key();
			
	//prints out the entire tree
	cout << "\nWalk the entire tree and print the contents: ";
	myTree->walk(myTree->Root());	

	//test of findMin function
	cout << "\nSmallest node: " << myTree->findMin(myTree->Root())->Key() << endl;;

	//test of findMax function
	cout << "\nLargest node: " << myTree->findMax(myTree->Root())->Key() << endl;
	
	//test of successor function
	cout << "\nSuccessor of " << myTree->Root()->Right()->Key() << " is: " << myTree->successor(395, myTree->Root())->Key();

	//test of addNode in inserting an intermediate node.
	myTree->addNode(433, myTree->Root());
	cout << "\n";
	myTree->walk(myTree->Root());

	//Given two nodes, find the LCA(Least Common Ancestor) of a binary tree.
	Node* testNode1 = myTree->findNode(455, treeRoot);
	Node* testNode2 = myTree->findNode(500, treeRoot);
	cout << "\n\nLCA of Binary Tree: ";
	cout << myTree->FindLCA(myTree->Root(), testNode1, testNode2)->Key();
	
	cout << "\n\nIs a binary tree: ";
	cout << myTree->IsBST(myTree->Root());

	int prev = INT_MIN;
	cout << "\n\nIs a binary tree: ";
	cout << myTree->IsBST2(myTree->Root(), &prev);

	cout << "\n\nPrint out all the elements between a specific range: ";
	myTree->RangePrinter(myTree->Root(), 98, 400);

	cout << "\n\nFind in order succesor of a BST: ";
	cout << myTree->inOrderSucc(treeRoot->Left()->Left())->Key();

	//converts a binary tree to a circular linked list.
	cout << "\n\nBST to circular DLL: ";
	Node* myCircle = myTree->TreeToList(myTree->Root());
	walk3(myCircle);

	cout << "\n\nConvert a SORTED array to a BST: ";
	Node* newTree = BuildBST(myArray, 0, 8);
	walk2(newTree);
	
	

	

	//myTree->Delete(119, treeRoot);
	//myTree->walk(myTree->Root());

	//cout << "\nLargest node: " << myTree->findMax(myTree->Root())->Key() << endl;



	getchar();

}
