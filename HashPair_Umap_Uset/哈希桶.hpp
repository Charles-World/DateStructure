#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
using namespace std;
//��ϣͰ

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
template <class K, class V, class KeyOfValue, class HashFun> //������ǰ�������ĵ�ԭ�����ʹ���Ҫ�õ���ϣ��
class HashTable;                                             //���ҹ�ϣ��ҲҪ�õ��ʹ�������Ϊ�������Ǵ�������ִ�е�
                                                             //�������Ҫ�õ��±ߵĴ��룬���Ͳ�֪����ʲô������Ҫ��һ��ǰ������
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
		cur = new Node(data);//ֱ�ӽ���ͷ��
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
	//Ҫ�������ݣ�����Ϊԭ������ĳ��Ȳ�������
	//����������ȸı��ˣ�ԭ������������λ�õ�Ҳ�Ͳ�ͬ�ˣ����Ա��������ٸ�һ������
	//Ū�ú󣬾������ݵ�Ǩ���ˣ���ô��
	//��ԭ������ĵ�һ���ǿյĵ�λ�ÿ�ʼ��
	//�Ȱ������ó�������һ���µ�λ�ã��ҵ�λ��
	//��Ϊ����Ҫ��cur�����㣬�ŵ��������һ��λ�ã�����cur��next����ı�
	//��Ϊԭ�������˹�ϣ��ͻ�������¼���ĳ��Ȳ�һ�� �����Բ�һ���ᷢ����ϣ��ͻ
	//��������������nextָ�����Լ�
	//�������ǻ�Ҫ������һ��cur��λ��Ҳ����ԭ��cur��next���Ǹ���㣬����������ǰ�ı���next
	//��Ϊ����Ȱ�cur��next����cur�Ǿ��Ҳ���ԭ����cur�ˣ��Ͳ��ܸı�����������cur��ָ���λ��
	//��Ϊ���Ǳ���ı�������cur��ָ���λ�ã���������Ҫ��ǰ����һ����ԭʼcur��next�Ľڵ�
	void CheckCapacity()
	{
		if (_size == _table.size())
		{
			size_t newC = getPrime(_table.size());
			vector<pNode> newT;
			newT.resize(newC);
			for (size_t i = 0; i < _table.size(); ++i)
			{
				pNode cur = _table[i];//cur��һ���ṹ��ָ��
				while (cur)
				{
					pNode next = cur->_next;

					size_t index = HashIdx(kov(cur->_data), newT.size());
					cur->_next = newT[index];//�����ᶯ��ʡȥ�����½ڵ�Ŀ���
					newT[index] = cur;       //��Ϊ������������ڵ㣬����ֱ�ӿ��԰�����ֵ������
					                         //��Ϊ�Ǹ������������ǿ��԰������ú�ֱ�Ӹ��ǣ�����
					cur = next;              //�Ȳ����˷ѿռ�����ڵ㣬Ҳ�������ź�λ��
				}                            //����൱��һ�����˵Ĺ��̣���Ϊÿ���ڵ㶼�Ƕ����ģ�ֻ��ͨ��һ�����ӹ�ϵ�������໥����
				_table[i] = nullptr;         //���ǲ����������ģ�ֻ����ָ��Ĵ��ڣ������ǿ�������������
			}                                //��������ֻ��Ҫ�����ͷ�����ܰ�˳�����
			_table.swap(newT);               //���Ե�������Ǹ��ƹ�����ֻ������ͷ���������Ǹı�����˳��
		}                                    //����������������پ�����ʱ��ֻ�ǽ����е�����ͷ�ĵ�ַ������ˣ������ǽ��ڵ���ͷ���
	}                                        //�������ǲ��õ��ģ����ǵ������ǴӾ����������ˣ�һ��������Ҳ���ò�����   
                                               
	size_t HashIdx(const K& key, size_t sz) //�����������ַ��������
	{
		HashFun hfun;
		return hfun(key) % sz;
	}
private:
	size_t _size = 0;
	vector<pNode> _table;
};
