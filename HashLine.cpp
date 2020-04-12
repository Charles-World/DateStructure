#include <iostream>
#include <vector>
using namespace std;
//闭散列,线性探测，不能解决哈希冲突

enum STATE { EMPTY, EXIST, DELETE };

template <class K, class V>
struct HashNode
{
	pair<K, V> _kv;
	STATE _state = EMPTY;
};

template<class K, class V>
class HashTable
{
public:
	typedef HashNode<K, V> Node;
	typedef Node* pNode;
	HashTable(size_t N = 1)
	{
		_table.resize(N);
		_size = 0;
	}
	bool Insert(const pair<K, V>& kv)
	{
		CheckCapacity();

		size_t index = kv.first % _table.size();
		while (_table[index]._state == EXIST)
		{
			if (_table[index]._kv.first == kv.first)//不允许有重复元素
			{
				return false;
			}
			++index;
			if (index == _table.size())
			{
				index = 0;
			}
		}
		_table[index]._kv = kv;
		_table[index]._state = EXIST;
		++_size;
		return true;
	}

	void CheckCapacity()
	{
		if (_size * 10 / _table.size() >= 7)//负载因子
		{
			vector<Node> newT;
			size_t newC = _table.size() == 0 ? 1 : 2 * _table.size();
			//_table.resize(newC);
			newT.resize(newC);
			//HashTable<K, V> newHt(newC);
			for (size_t i  = 0; i < _table.size(); i++)
			{
				if (_table[i]._state == EXIST)
				{
					size_t index = _table[i]._kv.first % newT.size();
					newT[index]._kv = _table[i]._kv;
					newT[index]._state = EXIST;
				}
			}
			_table.swap(newT);
		}
	}

	pNode Find(const K& key)
	{
		size_t index = key % _table.size();
		while (_table[index]._state != EMPTY)
		{
			if (_table[index]._state == EXIST && _table[index]._kv.first == key)
			{
				return &_table[index];
			}
			++index;
			if (index == _table.size())
			{
				index = 0;
			}
		}
		return nullptr;
	}

	bool Erase(const K& key)
	{
		pNode ret = Find(key);
		if (ret)
		{
			ret->_state = DELETE;
			--_size;
			return true;
		}
		return false;
	}
private:
	vector<Node> _table;
	size_t _size;
};

void test()
{
	HashTable<int, int> ht;
	ht.Insert(make_pair(0, 0));
	ht.Insert(make_pair(3, 3));
	ht.Insert(make_pair(5, 5));
	ht.Insert(make_pair(6, 6));
	ht.Insert(make_pair(8, 8));

	int key;
	cin >> key;
	HashTable<int, int>::pNode ret = ht.Find(key);
	if (ret)
	{
		cout << ret->_kv.first << "--->" << ret->_kv.second << endl;
	}
	else
	{
		cout << " Not Find" << endl;
	}

	if (ht.Erase(3))
	{
		cout << "删除成功" << endl;
	}
	else
	{
		cout << "删除失败" << endl;
	}
}
int main()
{
	test();

	system("pause");
	return 0;
}