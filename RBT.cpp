#include <iostream>
#include <time.h>
using namespace std;

enum Color
{
	BLACK,
	RED
};
template <class K, class V>
struct RBTNode
{
	typedef RBTNode<K, V> Node;
	Node* _pLeft = nullptr;
	Node* _pRight = nullptr;
	Node* _pParent = nullptr;
	pair<K, V> _kv;
	Color _color = RED;
};


template <class K, class V>
class RBTree
{
public:
	typedef RBTNode<K, V> Node;
	typedef Node* pNode;
	typedef Node* PNode;
	RBTree()
	{
		_header = new Node;
		_header->_pParent = nullptr;
		_header->_pLeft = _header;
		_header->_pRight = _header;

	}

	bool Insert(const pair<K, V>& kv)
	{
		if (_header->_pParent == nullptr)
		{
			pNode root = new Node;
			root->_kv = kv;
			root->_color = BLACK;

			root->_pParent = _header;
			_header->_pParent = root;

			_header->_pLeft = root;
			_header->_pRight = root;

			return true;
		}
		pNode cur = _header->_pParent;
		pNode parent = nullptr;

		while (cur)
		{
			if (kv.first > cur->_kv.first)
			{
				parent = cur;
				cur = cur->_pRight;
			}
			else if (kv.first < cur->_kv.first)
			{
				parent = cur;
				cur = cur->_pLeft;
			}
			else
			{
				return false;
			}
		}

		pNode newNode = new Node;
		newNode->_kv = kv;
		if (kv.first > parent->_kv.first)
		{
			parent->_pRight = newNode;
		}
		else
		{
			parent->_pLeft = newNode;
		}
		newNode->_pParent = parent;

		cur = newNode;
		//调平衡
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
		_header->_pParent->_color = BLACK;
		_header->_pLeft = leftMost();
		_header->_pRight = rightMost();
		return true;
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

	void _Inorder(pNode root)
	{
		if (root)
		{
			_Inorder(root->_pLeft);
			cout << root->_kv.first << "-->" << root->_kv.second << endl;
			_Inorder(root->_pRight);
		}
	}
	void Inorder()
	{
		_Inorder(_header->_pParent);
		return;
	}
	bool IsValidRBTree()//判断红黑树是否正确
	{
		PNode pRoot = _header->_pParent;
		// 空树也是红黑树
		if (nullptr == pRoot)
			return true;
		// 检测根节点是否满足情况
		if (BLACK != pRoot->_color)
		{
			cout << "违反红黑树性质二：根节点必须为黑色" << endl;
			return false;
		}
		// 获取任意一条路径中黑色节点的个数
		size_t blackCount = 0;
		PNode pCur = pRoot;
		while (pCur)
		{
			if (BLACK == pCur->_color)
				blackCount++;
			pCur = pCur->_pLeft;
		}
		// 检测是否满足红黑树的性质，k用来记录路径中黑色节点的个数
		size_t k = 0;
		return _IsValidRBTree(pRoot, k, blackCount);
	}
	bool _IsValidRBTree(PNode pRoot, size_t k, const size_t blackCount)
	{
		//走到null之后，判断k和black是否相等
		if (nullptr == pRoot)
		{
			if (k != blackCount)
			{
				cout << "违反性质四：每条路径中黑色节点的个数必须相同" << endl;
				return false;
			}
			return true;
		}
		// 统计黑色节点的个数
		if (BLACK == pRoot->_color)
			k++;
		// 检测当前节点与其双亲是否都为红色
		PNode pParent = pRoot->_pParent;
		if (pParent && RED == pParent->_color && RED == pRoot->_color)
		{
			cout << "违反性质三：没有连在一起的红色节点" << endl;
			return false;
		}
		return _IsValidRBTree(pRoot->_pLeft, k, blackCount) &&
			_IsValidRBTree(pRoot->_pRight, k, blackCount);
	}
private:
	pNode _header;
};

void testRBTree2()
{
	srand(time(nullptr));
	int n;
	cin >> n;
	RBTree<int, int> rb;
	while (n--)
	{
		int num = rand();
		cout << num << " ";
		rb.Insert(make_pair(num, num));
	}
	cout << "IsValidRBTree: " << rb.IsValidRBTree() << endl;
}


void testRBTree()
{
	RBTree<int, int> rbtree;
	rbtree.Insert(make_pair(0, 0));
	rbtree.Insert(make_pair(10, 0));
	rbtree.Insert(make_pair(2, 0));
	rbtree.Insert(make_pair(8, 0));
	rbtree.Insert(make_pair(9, 0));
	rbtree.Insert(make_pair(4, 0));

	rbtree.Inorder();
	cout << "IsValidRBTree: " << rbtree.IsValidRBTree() << endl;
}

int main()
{
	testRBTree2();

	system("pause");
	return 0;
}