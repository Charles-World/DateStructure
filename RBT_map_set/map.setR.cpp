#include "testRBT.hpp"
using namespace std;

template <class K, class V>
class Map
{
public:
	struct MapKeyOfValue
	{
		const K& operator () (const pair<K, V>& data)
		{
			return data.first;
		}
	};
	typedef typename RBTree<K, pair<K, V>, MapKeyOfValue>::Iterator Iterator;

	 pair<Iterator, bool> Insert(const pair<K, V>& data)
	{
		return _t.Insert(data);
	}
	Iterator begin()
	{
		return _t.begin();
	}
	Iterator end()
	{
		return _t.end();
	}
	V& operator [] (const K& key)
	{
		return (*(Insert(make_pair(key, V()))).first).second;
	}
private:
	RBTree<K, pair<K, V>, MapKeyOfValue> _t;
};

template <class K>
class Set
{
public:
	struct SetKeyOfValue
	{
		const K& operator () (const K& data)
		{
			return data;
		}
	};
	typedef typename RBTree<K, K, SetKeyOfValue>::Iterator Iterator;
	pair<Iterator, bool>  Insert(const K& key)
	{
		return _t.Insert(key);
	}

	Iterator begin()
	{
		return _t.begin();
	}
	Iterator end()
	{
		return _t.end();
	}

private:
	RBTree<K, K, SetKeyOfValue> _t;
};

void testMapSet()
{
	Map<int, int> m;
	m.Insert(make_pair(0, 0));
	m.Insert(make_pair(5, 5));
	m.Insert(make_pair(9, 9));
	m.Insert(make_pair(1, 1));
	auto it = m.begin();
	while (it != m.end())
	{
		cout << it->first << "--->" << it->second << endl;
		it++;
	}

	/*Set<int> s;
	s.Insert(4);
	s.Insert(5);
	s.Insert(2);
	s.Insert(66);
	s.Insert(43);
	auto it = s.begin();
	while (it != s.end())
	{
		cout << *it << endl;
		it++;
	}*/

}

int main()
{
	testMapSet();
	return 0;
}