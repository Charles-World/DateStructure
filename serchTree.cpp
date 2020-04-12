#include <iostream>
using namespace std;

template <class T>
struct BSTNode
{
	BSTNode(const T& val = T())
		:_left(nullptr)
		, _right(nullptr)
		, _data(val)
	{}
	BSTNode<T>* _left;
	BSTNode<T>* _right;
	T _data;
};

template <class T>
class BSTree
{
public:
	typedef BSTNode<T> Node;
	BSTree(Node* root = nullptr)
		:_root(root)
	{}
	STree(const BSTree<T>& bst)
	{
		_root = Copy(bst._root);
	}
	Node* Copy(Node* root)
	{
		if (root)
		{
			Node* newNode = new Node(root->_data);
			newNode->_left = Copy(root->_left);
			newNode->_right = Copy(root->_right);
		}
		else
		{
			return nullptr;
		}
		return newNode;
	}

	BSTree<T>& operator = (const BSTree<T>& bst)
	{
		if (this != &bst)
		{
			if (_root)
			{
				Destory(_root);
			}
			_root = Copy(bst._root);
		}
		return *this;
	}

	void Destory(Node* root)
	{
		if (root)
		{
			Destory(root->_left);
			Destory(root->_right);
			delete root;
			root = nullptr;
		}
		return;
	}

	Node* find(const T& x)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_data == x)
			{
				return cur;
			}
			else if (x > cur->_data)
			{
				cur = cur->_right;
			}
			else
			{
				cur = cur->_left;
			}
		}
		return nullptr;
	}

	bool Insert(const T& x)
	{
		if (_root == nullptr)
		{
			_root = new Node(x)
				;
			return true;
		}
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (cur->_data == x)
			{
				return false;    //搜索树中没有重复节点
			}
			else if (x > cur->_data)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				parent = cur;
				cur = cur->_left;
			}
		}
		cur = new Node(x);
		if (parent->_data > x)
		{
			parent->_left = cur;
		}
		else
			parent->_right = cur;
		return true;
	}

	void Inorder()
	{
		_Inorder(_root);
		cout << endl;
	}

	void _Inorder(Node* root)
	{
		if (root)
		{
			_Inorder(root->_left);
			cout << root->_data << " ";
			_Inorder(root->_right);
		}
	}

	bool Erase(const T& x)
	{
		if (_root == nullptr)
		{
			return false;
		}
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (cur->_data == x)
			{
				break;
			}
			else if (cur->_data > x)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				parent = cur;
				cur = cur->_right;
			}
		}
		if (cur == nullptr)
		{
			return false;
		}
		if (cur->_left == nullptr && cur->_right == nullptr)
		{
			if (cur != _root)
			{
				if (parent->_left == cur)
				{
					parent->_left = nullptr
				}
				else
				{
					parent->_right = nullptr;
				}
			}
			else
			{
				_root = nullptr;
			}
			delete cur;
			cur = nullptr;
		}
		else if (cur->_left == nullptr)
		{
			if (cur != _root)
			{
				if (parent->_left == cur)
				{
					parent->_left = cur->_right;
				}
				else
				{
					parent->_right = cur->_right;
				}
			else
			{
				_root = cur->_right;
			}
			delete cur;
			cur = nullptr;
			}
		}
		else if (cur->_right == nullptr)
		{
			if (cur != _root)
			{
				if (parten->_right == cur)
				{
					parent->_right = cur->_left;
				}
				else
				{
					parent->_left = cur->_left;
				}
			}
			else
			{
				_root = cur->_left;
			}
			delete cur;
			cur = nullptr;
		}
		else
		{
			Node* leftMost = cur->_left;
			parent = cur;
			while (leftMost->_right)
			{
				parent = leftMost;
				leftMost = leftMost->_right;
			}
			cur->_data = leftMost->_data;
			if (parent->_right == leftMost)
			{
				parent->_right = nullptr;
			}
			else
			{
				parent->_left = leftMost->_left;
			}
			delete leftMost;
			leftMost = nullptr;
		}
		return true;
	}

private:
	Node * _root;
};

int main()
{
	BSTree<int> bstree;
	bstree.Insert(0);
	bstree.Insert(5);	
	bstree.Insert(633);
	bstree.Insert(10);
	bstree.Insert(58);
	bstree.Insert(34);
	bstree.Insert(18);
	bstree.Insert(265);
	bstree.Insert(512);
	bstree.Insert(1024);
	bstree.Insert(9);
	bstree.Insert(13);
	bstree.Insert(5);
	bstree.Insert(66);
	bstree.Inorder();

	system("pause");
	return 0;
}