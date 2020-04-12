#include <iostream>
#include <vector>
using namespace std;
class bitSet
{
public:
	bitSet(size_t range)
	{
		_bits.resize((range >> 5) + 1);
	}

	void Set(size_t N)
	{
		size_t index = N >> 5;
		size_t bitNum = N % 32;
		_bits[index] |= (1 << bitNum);
	}
	void Reset(size_t N)
	{
		size_t index = N >> 5;
		size_t bitNum = N % 32;
		_bits[index] &= (~(1 << bitNum));
	}
	bool Test(size_t N)
	{
		size_t index = N >> 5;
		size_t bitNum = N % 32;
		return (_bits[index] >> bitNum) & 1;
	}
private:
	vector<int> _bits;
};

void testBitSet()
{
	bitSet bs(1001);
	bs.Set(5);
	bs.Set(63);
	bool ret = bs.Test(33);
	if (ret)
	{
		cout << "它在" << endl;
	}
	else
	{
		cout << "它不在" << endl;
	}
}
//k = (m / range) * ln2
//m = k / ln2 * range 
//k / 0.7 * range
struct HashFun1
{
	size_t operator () (const string& s)
	{
		size_t hash = 0;
		for (const auto& e : s)
		{
			hash = hash * 131 + e;
		}
		return hash;
	}
};
struct HashFun2
{
	size_t operator () (const string& s)
	{
		size_t hash = 0;
		for (const auto& e : s)
		{
			hash = hash * 65599 + e;
		}
		return hash;
	}
};

struct HashFun3
{
	size_t operator () (const string& s)
	{
		size_t hash = 0;
		for (const auto& e : s)
		{
			hash = hash * 3781 + e;
		}
		return hash;
	}
};

template <class T, class HashFun1, class HashFun2, class HashFun3>
class BloomFilter
{
public:
	BloomFilter(size_t range)
		:_bitset(5 * range)
		,_bitCount(5 * range)
	{}

	void Set(const T& data)
	{
		size_t index1 = HashFun1()(data) % _bitCount;
		size_t index2 = HashFun2()(data) % _bitCount;
		size_t index3 = HashFun3()(data) % _bitCount;
		_bitset.Set(index1);
		_bitset.Set(index2);
		_bitset.Set(index3);
	}

	bool Test(const T& data)
	{
		size_t index1 = HashFun1()(data) % _bitCount;
		if (!_bitset.Test(index1))
		{
			return false;
		}
		size_t index2 = HashFun2()(data) % _bitCount;
		if (!_bitset.Test(index2))
		{
			return false;
		}
		size_t index3 = HashFun3()(data) % _bitCount;
		if (!_bitset.Test(index3))
		{
			return false;
		}
		return true;
	}
private:
	bitSet _bitset;
	size_t _bitCount;
};

int main()
{
	//testBitSet();
	BloomFilter<string, HashFun1, HashFun2, HashFun3> bf(10);
	bf.Set("https://www.google.com/search?sxsrf=ACYBGNRGx4dQYtS12uHZAIz");
	bf.Set("https://www.google.com/search?sxsrf=ACYBGNRGx4");
	bf.Set("arch?sxsrf=ACYBGNRGx4d");

	bool ret = bf.Test("https://www.google.com/earch?sxsrf=ACYBGNRGx4");
	if (ret)
	{
		cout << "存在" << endl;
	}
	else
	{
		cout << "不存在" << endl;
	}

	system("pause");
	return 0;
}