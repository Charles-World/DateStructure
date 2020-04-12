#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
using namespace std;
//哈希桶

template <class V>
struct HashNode
{
	V _data;
	HashNode<V>* _next;
	HashNode(const V& data)
		:_data(data)
		, _next(nullptr)
	{}
};
template <class K, class V, class KeyOfValue, class HashFun> //这里做前置声明的的原因是送代器要用到哈希表
class HashTable;                                             //并且哈希表也要用到送代器，因为编译器是从上往下执行的
                                                             //如果我们要用到下边的代码，它就不知道是什么，所以要有一个前置声明
template <class K, class V, class KeyOfValue, class HashFun>
struct __HIerator
{
	typedef HashNode<V> Node;
	typedef Node* pNode;
	typedef __HIerator<K, V, KeyOfValue, HashFun> Self;
	typedef HashTable<K, V, KeyOfValue,HashFun> HashT;
	HashT* _ht;
	pNode _node;

	__HIerator(pNode node, HashT* ht)
		:_node(node)
		,_ht(ht)
	{}

	V& operator * ()
	{
		return _node->_data;
	}

	V* operator -> ()
	{
		return &operator*();
	}

	bool operator != (const Self& it)
	{
		return _node != it._node;
	}
	Self& operator ++ ()
	{
		if (_node->_next)
		{
			_node = _node->_next;
		}
		else
		{
			KeyOfValue kov;
			size_t index = _ht->HashIdx(kov(_node->_data), _ht->_table.size());

			++index;
			for (; index < _ht->_table.size(); ++index)
			{
				if (_ht->_table[index])
				{
					_node = _ht->_table[index];
					break;
				}
			}
			if (index == _ht->_table.size())
			{
				_node = nullptr;
			}
		}
		return *this;
	}
};
template <class K, class V, class KeyOfValue, class HashFun>
class HashTable
{
public:
	template <class K, class V, class KeyOfValue, class HashFun>
	friend struct __HIerator;

	typedef HashNode<V> Node;
	typedef Node* pNode;
	KeyOfValue kov;
	typedef __HIerator<K, V, KeyOfValue, HashFun> iterator;
	
	iterator end()
	{
		return iterator(nullptr, this);
	}

	iterator begin()
	{
		for (size_t i = 0; i < _table.size(); ++i)
		{
			if (_table[i])
			{
				return iterator(_table[i], this);
			}
		}
		return iterator(nullptr, this);
	}

	pair<iterator, bool> Insert(const V& data)
	{
		CheckCapacity();
		size_t index = HashIdx(kov(data), _table.size());
		pNode cur = _table[index];

		while (cur)
		{
			if (kov(cur->_data) == kov(data))
			{
				return make_pair(iterator(cur, this), false);
			}
			cur = cur->_next;
		}
		cur = new Node(data);//直接进行头插
		cur->_next = _table[index];
		_table[index] = cur;

		++_size;
		return make_pair(iterator(cur, this), true);
	}
	size_t getPrime(size_t prime)
	{
		const int PRIMECOUNT = 28;
		const size_t primeList[PRIMECOUNT] =
		{
			53ul, 97ul, 193ul, 389ul, 769ul,
			1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
			49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
			1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
			50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};

		for (size_t i = 0; i < PRIMECOUNT; ++i)
		{
			if (primeList[i] > prime)
			{
				return primeList[i];
			}
		}
		return primeList[PRIMECOUNT - 1];
	}
	//要进行扩容，是因为原来数组的长度不够用了
	//但是如果长度改变了，原来数据所处的位置的也就不同了，所以必须重新再搞一个数组
	//弄好后，就是数据的迁移了，怎么找
	//从原来数组的第一个非空的的位置开始找
	//先把数据拿出来计算一下新的位置，找到位置
	//因为我们要将cur这个结点，放到新数组的一个位置，所以cur的next必须改变
	//因为原来发生了哈希冲突，但重新计算的长度不一样 ，所以不一定会发生哈希冲突
	//所以我们让它的next指向它自己
	//但是我们还要计算下一个cur的位置也就是原来cur的next的那个结点，但是我们提前改变了next
	//因为如果先把cur的next给到cur那就找不到原来的cur了，就不能改变新数组里面cur所指向的位置
	//因为我们必须改变新数组cur所指向的位置，所以我们要提前保存一下最原始cur的next的节点
	void CheckCapacity()
	{
		if (_size == _table.size())
		{
			size_t newC = getPrime(_table.size());
			vector<pNode> newT;
			newT.resize(newC);
			for (size_t i = 0; i < _table.size(); ++i)
			{
				pNode cur = _table[i];//cur是一个结构体指针
				while (cur)
				{
					pNode next = cur->_next;

					size_t index = HashIdx(kov(cur->_data), newT.size());
					cur->_next = newT[index];//这样搬动，省去创建新节点的开销
					newT[index] = cur;       //因为本来就有这个节点，所以直接可以把它的值拿来用
					                         //因为是个链表，所以我们可以把它链好后，直接覆盖，这样
					cur = next;              //既不用浪费空间申请节点，也能重新排好位置
				}                            //这就相当于一个搬运的过程，因为每个节点都是独立的，只是通过一层链接关系来进行相互关联
				_table[i] = nullptr;         //它们并不是连续的，只是有指针的存在，让它们看起来是连续的
			}                                //所以我们只需要链表的头，就能按顺序访问
			_table.swap(newT);               //所以到最后我们复制过来的只是链表头，其它都是改变链接顺序
		}                                    //所以最后我们在销毁旧链表时，只是将所有的链表头的地址给清空了，并不是将节点给释放了
	}                                        //所以我们不用担心，我们的数据是从旧链表中来了，一但清空这边也就用不了了   
                                               
	size_t HashIdx(const K& key, size_t sz) //用来处理是字符串的情况
	{
		HashFun hfun;
		return hfun(key) % sz;
	}
private:
	size_t _size = 0;
	vector<pNode> _table;
};
