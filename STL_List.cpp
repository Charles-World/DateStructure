#include <iostream>
#include <assert.h>
using namespace std;

template <typename T>
struct ListNode
{
	ListNode(const T& val = T())//T()表示创建一个匿名变量，然后初始化为0
		:_data(val)
		, _next(nullptr)
		, _prev(nullptr)
	{}

	T _data;
	ListNode<T>* _next;
	ListNode<T>* _prev;
};

template <class T, class Ref, class Ptr>
struct ListIterator
{
	typedef ListIterator<T, Ref, Ptr> Self;
	ListNode<T>* _node;

	ListIterator(ListNode<T>* node)
		:_node(node)
	{}

	Ref operator * ()
	{
		return _node->_data;
	}

	Ptr operator -> ()
	{
		return &(_node->_data);
	}

	Self& operator ++ ()
	{
		_node = _node->_next;
		return *this;
	}

	Self operator ++ (int)
	{
		Self tmp(*this);
		_node = _node->_next;
		return tmp;
	}

	bool operator != (const Self& lit)
	{
		return _node != lit._node;
	} 

	bool operator == (const Self& lit)
	{
		return _node == lit._node;
	}
};

template <typename T>
class List
{
public:
	typedef ListNode<T> Node;
	typedef ListIterator<T, T&, T*> iterator;
    typedef ListIterator<T, const T&, const T*> const_iterator;
	typedef Node* pNode;    
	//const送代器和非const的实现，因为const的和非const的送代器很像
	//如果写两份代码，会感觉代码冗余，所以多加了两个模板参数类型来自动
	//以const和非const做一个区分，然后const送代器的出现是因为不想让你通过
	//送代器来修改表中的内容，就是这么简单，使用它你的操作只能是查看，这样安全了很多
	List()
	{
		_head = new Node;
		_head->_next = _head;
		_head->_prev = _head;
	}

	~List()
	{
		if (_head)
		{
			pNode curNode = _head->_next;
			while (curNode != _head)
			{
				pNode next = curNode->_next;
				delete curNode;
				curNode = next;
			}

			delete _head;
			_head = nullptr;
		}
	}

	void PushBack(const T& val)
	{
		pNode newNode = new Node(val);
		pNode prev = _head->_prev;
		prev->_next = newNode;
		newNode->_prev = prev;
		newNode->_next = _head;
		_head->_prev = newNode;
		
	}

	iterator begin()
	{
		return iterator(_head->_next);
	}

	iterator end()
	{
		return iterator(_head);
	}

	const_iterator begin() const
	{
		return const_iterator(_head->_next);
	}

	const_iterator end() const
	{
		return const_iterator(_head);
	}

	iterator Erase(iterator pos)
	{
		if (pos != end())
		{
			pNode cur = pos._node;
			pNode prev = cur->_prev;
			pNode next = cur->_next;

			delete cur;
			cur = nullptr;

			prev->_next = next;
			next->_prev = prev;

		    pos = iterator(next);
		}
		return pos;
	}

	void clear()
	{
		assert(_head);
		pNode hea = _head->_next;

		while (_hea != _head)
		{
			_head->_next = _hea->_next;
			delete _hea;
			_hea = _head->_next;
		}

		_head->_next = _head;
		_head->_prev= _head;
	}

	void popBack()
	{
		pNode _hea = _head->_prev;

		_head->_prev = _hea->_next;
		_hea->_next = _head;
		delete _hea;
	}

	void popFront()
	{
		pNode _hea = _head->_next;

		_head->_next = _hea->_next;
		_hea->_next->_prev = _head;
		delete  _hea;
	}

	void Insert(iterator pos, const T& val)
	{
		pNode node = new Node(val);
		pNode cur = pos._node;
		pNode prev = cur->_prev;

		prev->_next = node;
		node->_prev = prev;

		cur->_prev = node;
		node->_next = cur;
	}

	size_t size() const//const修饰的*this不是this,表明这个成员对象不能被修改
	{
		size_t sz = 0;
		for (const auto& e : *this)//基于范围的for，它相当于
		{
			++sz;
		}

		return sz;
	}

	bool Empty()
	{
		return _head->_next == _head;
	}

	List(const List<T>& lst) //list的拷贝构造，深拷贝
	{
		_head = new pNode;    //必须要有一个头节点，因为list是双向链表
		_head->_next = _head;
		_head->_prev = _head;
		/*list<T> tmp(lst.begin(), lst.end());
		return Swap(this);*/
		List<T> tmp;
		auto b = lst.begin();
		while (b != lst.end())
		{
			PushBack(*b);
		}
	}

	List<T>& operator = (const List<T> lst)
	{
		_head->_data = lst->_head->_data;
		_head->_next = lst->_head->_next;
		_head->_prev = lst->_head->_prev;
		return this;
	}

private:
	pNode _head;
};

template<class T>
void print(ListIterator<T, T&, T*> iterator)
{
	while (*iterator)
	{
		cout << "data:" << *iterator << endl;
		iterator++;
	}
}



int main()
{
	List<int> lst;
	lst.PushBack(1);
	lst.PushBack(2);
	lst.PushBack(3);
	//auto e = lst.begin();
	//print(e);
	int a = lst.size();
	cout << "lst.size():" << a << endl;

	system("pause");
	return 0;
}