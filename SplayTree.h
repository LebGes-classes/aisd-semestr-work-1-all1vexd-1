	#pragma once
	#include "Node.h"
	class SplayTree
	{
	private:
		Node* root;

		void leftRotate(Node* x);
		void rightRotate(Node* x);
		void splay(Node* x);
		Node* findMax(Node* node);

	public:
		SplayTree() : root(nullptr) {}

		void insert(int key);
		Node* search(int key);
		void remove(int key);
		void printInOrder(Node* node);
	
		Node* getRoot() { return root; }
	};

