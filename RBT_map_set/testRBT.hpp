#pragma once

#include <iostream>
#include <time.h>
using namespace std;

enum Color
{
	BLACK,
	RED
};
template <class T>
struct RBTNode
{
	typedef RBTNode<T> Node;
	Node* _pLeft = nullptr;
	Node* _pRight = nullptr;
	Node* _pParent = nullptr;
	T _data;
	Color _color = RED;
};
template <class T>

struct __TreeIterator
{
	typedef RBTNode<T> Node;
	typedef Node* pNode;
	typedef __TreeIterator<T> Self;
	Node* _node;

	__TreeIterator(Node* node)
		:_node(node)
	{}

	
	T& operator * ()
	{
		return _node->_data;
	}
	T* operator -> ()
	{
		return &(operator*());
	}
	bool operator != (const Self& it)
	{
		return _node != it._node;
	}

	Self& operator ++ () //要找到父亲节点的孩子不是它的右孩子
	{
		if (_node->_pRight)
		{
			_node = _node->_pRight;
			while (_node->_pLeft)
			{
				_node = _node->_pLeft;
			}
		}
		else
		{
			pNode parent = _node->_pParent;
				while (_node == parent->_pRight)
				{
					_node = parent;
					parent = parent->_pParent;
				}
				if (_node->_pRight != parent)
				{
					_node = parent;
				}
		}
		return *this;
	}
     Self operator ++ (int)
	{
		Self tmp(*this);
		++(*this);
		return tmp;
	}
	Self& operator -- ()
	{
		if (_node->_pLeft)
		{
			_node = _node->_pLeft;
			while (_node->_pRight)
			{
				_node = _node->_pRight;
			}
		}
		else
		{
			pNode parent = _node->_pParent;

				while (_node = parent->_pLeft)
				{
					_node = parent;
					parent = parent->_pParent;
				}
				if (parent->_pLeft != parent)
				{
					_node = parent;
				}
		}
		return *this;
	}

	Self operator -- (int)
	{
		Self tmp(*this);
		--(*this);
		return tmp;
	}
};


template <class K, class V, class KeyOfValue>
class RBTree
{
public:
	typedef RBTNode<V> Node;
	typedef __TreeIterator<V> Iterator;
	typedef Node* pNode;
	typedef Node* PNode;
	RBTree()
	{
		_header = new Node;
		_header->_pParent = nullptr;
		_header->_pLeft = _header;
		_header->_pRight = _header;
	}

	Iterator begin()
	{
		return Iterator(_header->_pLeft);
	}
	Iterator end()
	{
		return Iterator(_header);
	}
	Iterator rbegin()
	{
		return Iterator(_header->_right);
	}
	Iterator rend()
	{
		return Iterator(_header);
	}
	pair<Iterator, bool> Insert(const V& data)
	{
		if (_header->_pParent == nullptr)
		{
			pNode root = new Node;
			root->_data = data;
			root->_color = BLACK;

			root->_pParent = _header;
			_header->_pParent = root;

			_header->_pLeft = root;
			_header->_pRight = root;

			return make_pair(Iterator(root), true);
		}
		KeyOfValue keyofvalue;
		pNode cur = _header->_pParent;
		pNode parent = nullptr;

		while (cur)
		{
			if (keyofvalue(data) > keyofvalue(cur->_data))
			{
				parent = cur;
				cur = cur->_pRight;
			}
			else if (keyofvalue(data) < keyofvalue(cur->_data))
			{
				parent = cur;
				cur = cur->_pLeft;
			}
			else
			{
				return make_pair(Iterator(cur), false);
			}
		}

		pNode newNode = new Node;
		newNode->_data = data;
		if (keyofvalue(data) > keyofvalue(parent->_data))
		{
			parent->_pRight = newNode;
		}
		else
		{
			parent->_pLeft = newNode;
		}
		newNode->_pParent = parent;

		cur = newNode;
		while (cur != _header->_pParent && cur->_pParent->_color == RED)
		{
			pNode parent = cur->_pParent;
			pNode gParent = parent->_pParent;
			if (gParent->_pLeft == parent)
			{
				pNode uncle = gParent->_pRight;
				if (uncle && uncle->_color == RED)
				{
					parent->_color = uncle->_color = BLACK;
					gParent->_color = RED;
					cur = gParent;
				}
				else
				{
					if (cur == parent->_pRight)
					{
						RotateL(parent);
						swap(parent, cur);
					}
					RotateR(gParent);
					parent->_color = BLACK;
					gParent->_color = RED;
					break;
				}
			}
			else
			{
				if (gParent->_pRight == parent)
				{
					pNode uncle = gParent->_pLeft;
					if (uncle && uncle->_color == RED)
					{
						parent->_color = uncle->_color = BLACK;
						gParent->_color = RED;
						cur = gParent;
					}
					else
					{
						if (cur == parent->_pLeft)
						{
							RotateR(parent);
							swap(parent, cur);
						}
						RotateL(gParent);
						parent->_color = BLACK;
						gParent->_color = RED;
						break;
					}
				}

			}
		}
		_header->_pParent->_color == BLACK;
		_header->_pLeft = leftMost();
		_header->_pRight = rightMost();
		return make_pair(Iterator(newNode), true);
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_pLeft;
		Node* subLR = subL->_pRight;
		//单向连接subL,parent,subLR
		subL->_pRight = parent;
		parent->_pLeft = subLR;
		//向上连接subLR
		if (subLR)
		{
			subLR->_pParent = parent;
		}
		//subL, parent->parent双向连接
		if (parent != _header->_pParent)
		{
			Node* gParent = parent->_pParent;
			if (gParent->_pLeft == parent)
			{
				gParent->_pLeft = subL;
			}
			else
			{
				gParent->_pRight = subL;
			}
			subL->_pParent = gParent;
		}
		else
		{
			subL->_pParent = _header;
			_header->_pParent = subL;
		}
		//向上连接parent,subL
		parent->_pParent = subL;
	}


	void RotateL(Node* parent)
	{
		Node* subR = parent->_pRight;
		Node* subRL = subR->_pLeft;

		subR->_pLeft = parent;
		parent->_pRight = subRL;

		if (subRL)
		{
			subRL->_pParent = parent;
		}
		if (parent != _header->_pParent)
		{
			Node* gParent = parent->_pParent;
			if (gParent->_pLeft == parent)
			{
				gParent->_pLeft = subR;
			}
			else
			{
				gParent->_pRight = subR;
			}
			subR->_pParent = gParent;
		}
		else
		{
			subR->_pParent = _header;
			_header->_pParent = subR;
		}
		parent->_pParent = subR;
	}
	pNode leftMost()
	{
		pNode cur = _header->_pParent;
		while (cur && cur->_pLeft)
		{
			cur = cur->_pLeft;
		}
		return cur;
	}
	pNode rightMost()
	{
		pNode cur = _header->_pParent;
		while (cur && cur->_pRight)
		{
			cur = cur->_pRight;
		}
		return cur;
	}

private:
	pNode _header;
};


