#include "¹şÏ£Í°.hpp"
//Ä£°åÌØ»¯

template <class K>
struct HFun
{
	const K& operator () (const K& key)
	{
		return key;
	}
};

template <>
struct HFun<string>
{
	size_t operator () (const string& str)
	{
			size_t hash = 0;
			for (const auto& e : str)
			{
				hash = hash * 131 + e;
			}
			return hash;
	}
};


template <class K, class V,class HashFun = HFun<K>>
class UnorderedMap
{
	struct MapKeyOfValue
	{
		const K& operator () (const pair<K, V>& data)
		{
			return data.first;
		}
	};
public:
	typedef typename HashTable<K, pair<K, V>, MapKeyOfValue, HashFun>::iterator iterator;
	V& operator [] (const K& key)
	{
		pair<iterator, bool> ret = _ht.Insert(make_pair(key, V()));
		return ret.first->second;
	}

	pair<iterator, bool> Insert(const pair<K, V>& data)
	{
		return _ht.Insert(data);
	}
	iterator begin()
	{
		return _ht.begin();
	}
	iterator end()
	{
		return _ht.end();
	}
private:
	HashTable<K, pair<K, V>, MapKeyOfValue, HashFun> _ht;
};

void TestUnordered()
{
	//UnorderedMap<int, int> Umap;
	//srand(time(nullptr));
	//int n;
	//cin >> n;
	//for (size_t i = 0; i < n; i++)
	//{
	//	Umap.Insert(make_pair(rand() % 50, i));
	//}

	//Umap[100] = 100;
	//Umap[200] = 200;
	//Umap[300] = 300;

	//UnorderedMap<int, int>::iterator uit = Umap.begin();
	//while (uit != Umap.end())
	//{
	//	cout << uit->first << "--->" << uit->second << endl;
	//	++uit;
	//}
	UnorderedMap<string, string> uMap;
	uMap.Insert(make_pair("123", "123"));
	uMap.Insert(make_pair("12", "123"));
	uMap.Insert(make_pair("13", "123"));
	uMap.Insert(make_pair("3", "123"));
	uMap.Insert(make_pair("133", "123"));
	uMap.Insert(make_pair("153", "123"));
	UnorderedMap<string, string>::iterator uit = uMap.begin();
	while (uit != uMap.end())
	{
		cout << uit->first << "--->" << uit->second << endl;
		++uit;
	}
	
}

template <class K, class HashFun = HFun<K>>
class UnorderedSet
{
	struct SetKeyOfValue
	{
		const K& operator () (const K& data)
		{
			return data;
		}
	};
public:
	typedef typename HashTable<K, K, SetKeyOfValue, HashFun >::iterator iterator;
	pair<iterator, bool> Insert(const K& data)
	{
		return _ht.Insert(data);
	}
	iterator begin()
	{
		return _ht.begin();
	}
	iterator end()
	{
		return _ht.end();
	}

private:
	HashTable<K, K, SetKeyOfValue, HashFun> _ht;
};

void testSet()
{
	UnorderedSet<string> uMap;
	srand(time(nullptr));
	//int n;
	//cin >> n;
	//for (size_t i = 0; i < n; i++)
	//{
	//	uSet.Insert(rand() % 50));
	//}
	uMap.Insert("123");
	uMap.Insert("12");
	uMap.Insert("13");
	uMap.Insert("3");
	uMap.Insert("133");
	uMap.Insert("153");
	UnorderedSet<string>::iterator sit = uMap.begin();
	while (sit != uMap.end())
	{
		cout << *sit << endl;
		++sit;
	}


}

int main()
{
	//TestUnordered();
	testSet();
	return 0;
}
