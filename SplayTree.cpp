#include "SplayTree.h"
#include <iostream>

void SplayTree::leftRotate(Node* x)
{
	//проверка, что "x" и его правый потомок не нулевые
	if (x == nullptr || x->getRight() == nullptr) 
	{
		return;
	}

	//Сохраняем правого потомка "x"
	Node* y = x->getRight();

	//Переподвешиваем левое поддерерво "y" к правому поддереву "х"
	x->setRight(y->getLeft());
	if (y->getLeft() != nullptr) 
	{
		y->getLeft()->setParent(x);//Обновляем родителя левого поддерева "у"
	}
	//обновляем родителя "y"
	y->setParent(x->getParent());

	if (x->getParent() == nullptr) 
	{
		root = y;
	}
	else if (x == x->getParent()->getRight()) 
	{
		x->getParent()->setRight(y);//"x" был правым ребенком
	}
	else
	{
		x->getParent()->setLeft(y);//"x" был левым ребенком
	}

	//Делает "х" левым ребенком "y"
	y->setLeft(x);
	x->setParent(y);

}

void SplayTree::rightRotate(Node* x)
{
	//Аналогично левому повороту
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
	//node должен быть корнем, идем по всем правым детям(так как в BST правый ребенок больше по значению, чем предок)
	//когда доходим до конца - это и будет максимальный по значению ребенок
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
	//Если дерево пустое создаем корень
	if (root == nullptr)
	{
		root == new Node(key);
		return;
	}

	//Ищем место для вставки как в обычном BST
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
		//Если такой ключ уже есть, мы просто используем splay для него
		else
		{
			splay(current);
			return;
		}
	}
	//Цикл оканчивается тем, что parent - это узел на самом нижнем уровне

	//Создаем новый узел с заданным ключом, в зависимости от значения parent добавляем новый узел на уровень ниже
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

	//Делаем новый узел корнем
	splay(newNode);

}

Node* SplayTree::search(int key)
{
	Node* current = root;
	Node* parent = nullptr;
	
	//Поиск узла (key)
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
			//Нашли узел - делаем splay для него и возвращаем его	
			splay(current);
			return current;
		}
	}

	//узел не найден - делаем splay для последнего посещенного узла
	if (parent != nullptr) 
	{
		splay(parent);
	}

	//узел не найден
	return nullptr;
}

void SplayTree::remove(int key)
{
	//Дерево пустое
	if (root == nullptr)
	{
		return;
	}

	//Поиск узла, splay его
	search(key);

	//Если ключ не найден, ничего не удаляем
	if (root->getKey() != key)
	{
		return;
	}
	
	//Удаляемый узел
	Node* toDelete = root;

	//Объединяем поддеревья(правый и левый дети корня)
	//Нет левого поддерева
	if (root->getLeft() == nullptr)
	{
		//Правое поддерево становится корнем
		root = root->getRight();
		if (root != nullptr)
		{
			root->setParent(nullptr);
		}
	}
	//Нет правого поддерева
	else if (root->getRight() == nullptr)
	{
		//Левое поддерево становится корнем
		root = root->getLeft();
		if (root != nullptr)
		{
			root->setParent(nullptr);
		}
	}
	//Оба поодерева не пустые
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
		//Теперь корень левого дерева с максимальным значением => у него нет правого ребенка и его можно подсоединить к правому

		//Присоединяем правое дерево оно будет удовлетворять BST, так как изначально это было правильно дерево
		maxLeft->setRight(rightTree);
		rightTree->setParent(maxLeft);

		//обновляем корень
		root = maxLeft;
	}

	delete toDelete;
}

void SplayTree::printInOrder(Node* node)
{
	//Базовый случай рекурсии, выход при полном проходе
	if (node == nullptr)
	{
		return;
	}

	//Сначала идем до самого левого нижнего, потом у него не будет левого и правого, 
	//мы вернемся к предыдущему, у него левый уже вызывался => вызывется правый и тд(рекурсивный метод)
	printInOrder(node->getLeft());
	std::cout << node->getKey() << " ";
	printInOrder(node->getRight());
}
