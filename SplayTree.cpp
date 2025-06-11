#include "SplayTree.h"
#include <iostream>

void SplayTree::leftRotate(Node* x)
{
	//��������, ��� "x" � ��� ������ ������� �� �������
	if (x == nullptr || x->getRight() == nullptr) 
	{
		return;
	}

	//��������� ������� ������� "x"
	Node* y = x->getRight();

	//��������������� ����� ���������� "y" � ������� ��������� "�"
	x->setRight(y->getLeft());
	if (y->getLeft() != nullptr) 
	{
		y->getLeft()->setParent(x);//��������� �������� ������ ��������� "�"
	}
	//��������� �������� "y"
	y->setParent(x->getParent());

	if (x->getParent() == nullptr) 
	{
		root = y;
	}
	else if (x == x->getParent()->getRight()) 
	{
		x->getParent()->setRight(y);//"x" ��� ������ ��������
	}
	else
	{
		x->getParent()->setLeft(y);//"x" ��� ����� ��������
	}

	//������ "�" ����� �������� "y"
	y->setLeft(x);
	x->setParent(y);

}

void SplayTree::rightRotate(Node* x)
{
	//���������� ������ ��������
	if (x == nullptr || x->getLeft() == nullptr) 
	{
		return;
	}

	Node* y = x->getLeft();

	x->setLeft(y->getRight());
	if (y->getRight() != nullptr) 
	{
		y->getRight()->setParent(x);

	}
	y->setParent(x->getParent());

	if (x->getParent() == nullptr) 
	{
		root = y;
	}
	else if (x == x->getParent()->getRight()) 
	{
		x->getParent()->setRight(y);
	}
	else
	{
		x->getParent()->setLeft(y);
	}
	y->setRight(x);
	x->setParent(y);
}

void SplayTree::splay(Node* x)
{
	while (x->getParent() != nullptr) {
		if (x == x->getParent()->getLeft())
		{
			if (x->getGrangParent() == nullptr)
			{
				rightRotate(x->getParent());
			}
			else if (x->getParent() == x->getGrangParent()->getLeft())
			{
				rightRotate(x->getGrangParent());
				rightRotate(x->getParent());
			}
			else if (x->getParent() == x->getGrangParent()->getRight())
			{
				rightRotate(x->getParent());
				leftRotate(x->getParent());
			}
		}
		else if (x == x->getParent()->getRight())
		{
			if (x->getGrangParent() == nullptr)
			{
				leftRotate(x->getParent());
			}
			else if (x->getParent() == x->getGrangParent()->getRight())
			{
				leftRotate(x->getGrangParent());
				leftRotate(x->getParent());
			}
			else if (x->getParent() == x->getGrangParent()->getLeft())
			{
				leftRotate(x->getParent());
				rightRotate(x->getParent());
			}
		}
	}
}

Node* SplayTree::findMax(Node* node)
{
	//node ������ ���� ������, ���� �� ���� ������ �����(��� ��� � BST ������ ������� ������ �� ��������, ��� ������)
	//����� ������� �� ����� - ��� � ����� ������������ �� �������� �������
	if (node == nullptr) 
	{
		return nullptr;
	}
	
	while (node->getRight() != nullptr)
	{
		node = node->getRight();
	}

	return node;
}

void SplayTree::insert(int key)
{
	//���� ������ ������ ������� ������
	if (root == nullptr)
	{
		root == new Node(key);
		return;
	}

	//���� ����� ��� ������� ��� � ������� BST
	Node* current = root;
	Node* parent = nullptr;

	while (current != nullptr)
	{
		parent = current;
		if (key < current->getKey())
		{
			current = current->getLeft();
		}
		else if (key > current->getKey())
		{
			current = current->getRight();
		}
		//���� ����� ���� ��� ����, �� ������ ���������� splay ��� ����
		else
		{
			splay(current);
			return;
		}
	}
	//���� ������������ ���, ��� parent - ��� ���� �� ����� ������ ������

	//������� ����� ���� � �������� ������, � ����������� �� �������� parent ��������� ����� ���� �� ������� ����
	Node* newNode = new Node(key);
	newNode->setParent(parent);
	if (parent->getKey() < key) 
	{
		parent->setRight(newNode);
	}
	else
	{
		parent->setLeft(newNode);
	}

	//������ ����� ���� ������
	splay(newNode);

}

Node* SplayTree::search(int key)
{
	Node* current = root;
	Node* parent = nullptr;
	
	//����� ���� (key)
	while (current != nullptr)
	{
		parent = current;
		if (current->getKey() > key)
		{
			current = current->getLeft();
		}
		else if (current->getKey() < key)
		{
			current = current->getRight();
		}
		else
		{
			//����� ���� - ������ splay ��� ���� � ���������� ���	
			splay(current);
			return current;
		}
	}

	//���� �� ������ - ������ splay ��� ���������� ����������� ����
	if (parent != nullptr) 
	{
		splay(parent);
	}

	//���� �� ������
	return nullptr;
}

void SplayTree::remove(int key)
{
	//������ ������
	if (root == nullptr)
	{
		return;
	}

	//����� ����, splay ���
	search(key);

	//���� ���� �� ������, ������ �� �������
	if (root->getKey() != key)
	{
		return;
	}
	
	//��������� ����
	Node* toDelete = root;

	//���������� ����������(������ � ����� ���� �����)
	//��� ������ ���������
	if (root->getLeft() == nullptr)
	{
		//������ ��������� ���������� ������
		root = root->getRight();
		if (root != nullptr)
		{
			root->setParent(nullptr);
		}
	}
	//��� ������� ���������
	else if (root->getRight() == nullptr)
	{
		//����� ��������� ���������� ������
		root = root->getLeft();
		if (root != nullptr)
		{
			root->setParent(nullptr);
		}
	}
	//��� ��������� �� ������
	else
	{
		Node* leftTree = root->getLeft();
		Node* rightTree = root->getRight();

		leftTree->setParent(nullptr);
		rightTree->setParent(nullptr);
		
		Node* maxLeft = leftTree;
		while (maxLeft->getRight() != nullptr)
		{
			maxLeft = maxLeft->getRight();
		}
		splay(maxLeft);
		//������ ������ ������ ������ � ������������ ��������� => � ���� ��� ������� ������� � ��� ����� ������������ � �������

		//������������ ������ ������ ��� ����� ������������� BST, ��� ��� ���������� ��� ���� ��������� ������
		maxLeft->setRight(rightTree);
		rightTree->setParent(maxLeft);

		//��������� ������
		root = maxLeft;
	}

	delete toDelete;
}

void SplayTree::printInOrder(Node* node)
{
	//������� ������ ��������, ����� ��� ������ �������
	if (node == nullptr)
	{
		return;
	}

	//������� ���� �� ������ ������ �������, ����� � ���� �� ����� ������ � �������, 
	//�� �������� � �����������, � ���� ����� ��� ��������� => ��������� ������ � ��(����������� �����)
	printInOrder(node->getLeft());
	std::cout << node->getKey() << " ";
	printInOrder(node->getRight());
}
