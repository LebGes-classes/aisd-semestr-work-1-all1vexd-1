#pragma once
class Node
{
private:
	int key;
	Node* left;
	Node* right;
	Node* parent;

public:
	Node(int k) : key(k), left(nullptr), right(nullptr), parent(nullptr) {}

	int getKey() const { return key; }
	Node* getLeft() const { return left; }
	Node* getRight() const { return right; }
	Node* getParent() const { return parent; }
	Node* getGrangParent() const { return parent->getParent(); }

	void setLeft(Node* node) { left = node; }
	void setRight(Node* node) { right= node; }
	void setParent(Node* node) { parent = node; }

};

