#include "BinarySearchTree.h"
#include <iostream>
#include <windows.h>
using namespace std;

enum class ConsoleColor
{
	BLACK = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = RED | GREEN,
	WHITE = RED | GREEN | BLUE,
};

void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}

void SetCursorColor(ConsoleColor color)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::SetConsoleTextAttribute(output, static_cast<SHORT>(color));
}

void ShowConsoleCursor(bool flag)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	::GetConsoleCursorInfo(output, &cursorInfo);
	cursorInfo.bVisible = flag;
	::SetConsoleCursorInfo(output, &cursorInfo);
}

BinarySearchTree::BinarySearchTree()
{
	_nil = new Node();
	_root = _nil;
}

BinarySearchTree::~BinarySearchTree()
{
	delete _nil;
}

void BinarySearchTree::Print()
{
	::system("cls");
	ShowConsoleCursor(false);
	{ Print(_root, 10, 0); }
}

void BinarySearchTree::Print(Node* node, int x, int y)
{

	if (node == _nil)
		return;

	SetCursorPosition(x, y);
	if (node->color == Color::Red)
		SetCursorColor(ConsoleColor::RED);
	else
		SetCursorColor(ConsoleColor::BLUE);

	cout << "[" << node->key << "]" << endl;
	Print(node->left, x - (5 / (y + 1)), (y + 1));
	Print(node->right, x + (5 / (y + 1)), (y + 1));

	SetCursorColor(ConsoleColor::WHITE);
}

void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node();
	newNode->key = key;

	Node* node = _root;
	Node* parent = _nil;

	while (node != _nil)
	{
		parent = node;
		if (key < node->key)
		{
			node = node->left;
		}
		else
			node = node->right;

	}

	newNode->parent = parent;

	if (parent == _nil)
		_root = newNode;
	else if (key < parent->key)
		parent->left = newNode;
	else
		parent->right = newNode;

	//Red-Black 검사

	newNode->left = _nil;
	newNode->right = _nil;
	newNode->color = Color::Red;

	InsertFixup(newNode);

}

void BinarySearchTree::InsertFixup(Node* node)
{
	while (node->parent->color == Color::Red)
	{
		Node* uncle;
		if (node->parent == node->parent->parent->left)
		{
			uncle = node->parent->parent->right;

			if (uncle->color == Color::Red)
			{
				node->parent->color = Color::Black;
				uncle->color = Color::Black;
				node->parent->parent->color = Color::Red;
				node = node->parent->parent;
			}
			else //uncle == Black
			{
				if (node == node->parent->right) //Triangle
				{
					node = node->parent;
					LeftRotation(node);
				}

				node->parent->color = Color::Black;
				node->parent->parent->color = Color::Red;
				RightRotation(node->parent->parent);

			}
		}
		else
		{
			uncle = node->parent->parent->left;

			if (uncle->color == Color::Red)
			{
				node->parent->color = Color::Black;
				uncle->color = Color::Black;
				node->parent->parent->color = Color::Red;
				node = node->parent->parent;
			}
			else //uncle == Black
			{
				if (node == node->parent->left) //Triangle
				{
					node = node->parent;
					RightRotation(node);
				}

				node->parent->color = Color::Black;
				node->parent->parent->color = Color::Red;
				LeftRotation(node->parent->parent);
				node = node->parent;

			}
		}
	}

	_root->color = Color::Black;
}

void BinarySearchTree::Delete(int key)
{
	Node* node = Search(key);

	Delete(node);
}

void BinarySearchTree::Delete(Node* node)
{
	if (node == _nil)
		return;

	if (node->left == _nil) //오른쪽만 있는 경우, 둘다 없는 경우
	{
		Color color = node->color;
		Node* right = node->right;
		Replace(node, node->right);
		if(color == Color::Black)
			DeleteFixup(right);
	}
	else if (node->right == _nil) // 왼쪽만 있는 경우
	{
		Color color = node->color;
		Node* left = node->left;
		Replace(node, node->left);
		if (color == Color::Black)
			DeleteFixup(left);
	}
	else //둘다 있는 경우
	{
		Node* next = Next(node);
		node->key = next->key;
		Delete(next);
	}
}

void BinarySearchTree::DeleteFixup(Node* node)
{

	Node* x = node;

	while (x != _root && x->color == Color::Black)
	{

		if (x == x->parent->left)
		{
			Node* s = x->parent->right;

			if (s->color == Color::Red)
			{
				x->parent->color = s->color;
				s->color = Color::Black;
				LeftRotation(x->parent);
			}

			if (s->left->color == Color::Black && s->right->color == Color::Black)
			{
				s->color = Color::Red;
				if (x->parent->color == Color::Black)
					x = x->parent;
				else
					x->parent->color = Color::Black;
			}
			else
			{
				if (s->right->color == Color::Black)
				{
					s->left->color = Color::Black;
					s->color = Color::Red;
					RightRotation(s);
					s = s->parent;
				}
				s->color = x->parent->color;
				x->parent->color = Color::Black;
				LeftRotation(x->parent);
				x = _root;
			}
		}
		else
		{
			Node* s = x->parent->left;

			if (s->color == Color::Red)
			{
				x->parent->color = s->color;
				s->color = Color::Black;
				RightRotation(x->parent);
			}

			if (s->left->color == Color::Black && s->right->color == Color::Black)
			{
				s->color = Color::Red;
				if (x->parent->color == Color::Black)
					x = x->parent;
				else
					x->parent->color = Color::Black;
			}
			else
			{
				if (s->left->color == Color::Black)
				{
					s->right->color = Color::Black;
					s->color = Color::Red;
					LeftRotation(s);
					s = s->parent;
				}
				s->color = x->parent->color;
				x->parent->color = Color::Black;
				RightRotation(x->parent);
				x = _root;
			}
		}
	}

	_root->color = Color::Black;

}

void BinarySearchTree::Replace(Node* u, Node* v)
{
	if (u->parent == _nil)
		_root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;

	v->parent = u->parent;

	delete u;
}

void BinarySearchTree::LeftRotation(Node* node)
{
	Node* x = node->right;

	node->right = x->left;

	if (x->left != _nil)
		x->left->parent = node;

	
	x->parent = node->parent;
	if (node->parent == _nil)
		_root = x;
	else if (node == node->parent->left)
		node->parent->left = x;
	else
		node->parent->right = x;

	x->left = node;
	node->parent = x;
	
}

void BinarySearchTree::RightRotation(Node* node)
{
	Node* x = node->left;

	node->left = x->right;

	if (x->right != _nil)
		x->right->parent = node;


	x->parent = node->parent;
	if (node->parent == _nil)
		_root = x;
	else if (node == node->parent->left)
		node->parent->left = x;
	else
		node->parent->right = x;

	x->right = node;
	node->parent = x;
}

Node* BinarySearchTree::Search(int key)
{
	Node* dest = nullptr;
	Node* node = _root;

	while (node != _nil && node->key != key)
	{
		if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}

	dest = node;

	return dest;
}

Node* BinarySearchTree::Min(Node* node)
{
	Node* min = node;
	while (node != _nil)
	{
		min = node;
		node = node->left;
	}
	return min;
}

Node* BinarySearchTree::Max(Node* node)
{
	Node* max = node;
	while (node != _nil)
	{
		max = node;
		node = node->right;
	}
	return max;
}

Node* BinarySearchTree::Next(Node* node)
{
	if (node->right != _nil)
	{
		return Min(node->right);
	}

	Node* parent = node->parent;

	while (parent != _nil && node == parent->right)
	{
		node = parent;
		parent = parent->parent;
	}

	return parent;
}
