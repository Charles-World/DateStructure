#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
using namespace std;

class String
{
public:
	typedef char* iterator;
	typedef const char* const_iterator;

	String(const char* str = "")
	{
		assert(str != nullptr);

		_size = strlen(str);
		_str = new char[_size + 1];
		strcpy(_str, str);
		_capacity = _size;
	}

	String(const String& str)
		:_str(nullptr)
		,_size(0)
		,_capacity(0)
	{
		String tmp(str._str);    //通过交换来进行数据的复制
		Swap(tmp);
	}

	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
			_size = 0;
			_capacity = 0;
		}
	}

	void Swap(String& str)
	{
		swap(str._str, _str);
		swap(str._size, _size);
		swap(str._capacity, _capacity);
	}

	String& operator = (String str)   //this指针现在指向，你所要访问的那个类
	{
		Swap(str);                    //str里的内容和this指向的类里的数据进行交换
		return *this;
	}

	char& operator [] (size_t pos)
	{
		assert(pos < _size);
		return _str[pos];
	}

	const char& operator [] (size_t pos)const
	{
		assert(pos < _size);
		return _str[pos];
	}

	iterator begin()
	{
		return _str;
	}

	iterator end()
	{
		return _str + _size;
	}

	const_iterator begin()const
	{
		return _str;
	}

	const_iterator end()const
	{
		return _str + _size;
	}

	char* c_str()
	{
		return _str;
	}

	void Reserve(size_t n)
	{
		if (n > _capacity)
		{
			char* tmp = new char[n + 1];
			strcpy(tmp, _str);
			delete[] _str;
			_str = tmp;
			_capacity = n;
		}
	}

	void Resize(size_t n, char c = '\0')
	{
		if (n > _capacity)
		{
			Reserve(n);
		}

		if (n > _size)
		{
			memset(_str + _size, c, n - _size);
		}

		_size = n;
		_str[_size] = '\0';
	}

	void pushBack(char c)
	{
		if (_size == _capacity)
		{
			size_t newC = _capacity == 0 ? 15 : 2 * _capacity;
			Reserve(newC);
		}

		_str[_size++] = c;
		_str[_size] = '\0';
	}

	void popBack()
	{
		if (_size > 0)
		{
			_str[--_size] = '\0';
		}
	}

	void Erase(size_t pos, size_t len)
	{
		assert(pos < _size);

		if (pos + len >= _size)
		{
			_size = pos;
			_str[_size] = '\0';
		}
		else
		{
			for (size_t i = pos + len; i <= _size; i++)
			{
				_str[pos++] = _str[i];
			}
			_size = pos - 1;
		}
	}

	void Append(const char* str)
	{
		assert(str);

		size_t len = strlen(str);
		if (_size + len >= _capacity)
		{
			Reserve(_size + len);
		}

		/*for (size_t i = 0; i < len; i++)
		{
			_str[_size + i] = str[i];
		}*/
		strcpy(_str + _size, str);

		_size += len;
	}

	void Insert(size_t pos, char* str)
	{
		assert(str);
		assert(pos <= _size);

		if (_capacity <= strlen(str) + _size)
		{
			size_t newcapacity = strlen(str) + _size;
			Reserve(newcapacity);
		}

		size_t end = _size + strlen(str);
		while (end > pos + strlen(str))     //进行向后搬移，将要插入的位置空出来
		{
			_str[end] = _str[end - strlen(str)];
			end--;
		}

		//strcpy(_str + pos, str);
		while (*str)
		{
			_str[pos++] = *str++;
		}
		_size += strlen(str);
		_str[_size] = '\0';
	}

	size_t find(char c)
	{
		for (int i = 0; i < _size; i++)
		{
			if (_str[i] == c)
			{
				return i;
			}

			return -1;
		}
	}

	char* substrpos(char* dest, char* src)  //看dest字符串中是否有src的全部字符，如果有返回src最后一个字符
	{                                       //在dest中的位置
 		char* dst = dest;
		char* sc = src;

		while (*dst)
		{
			if (*dst == *sc)
			{
				char* mathdest = dst + 1;
				char* mathsrc = sc + 1;
				while (*mathsrc && *mathdest)
				{
					if (*mathdest != *mathsrc)
					{
						break;
					}
					mathsrc++;
					mathdest++;
				}

				if (*mathsrc == '\0')
				{
					return dst;
				}
					
			}
			++dst;
		}
		return nullptr;
	}

	size_t find(char* str, size_t pos = 0)
	{
		assert(str);
		char* str2 = str;

		while (*_str)
		{
				while (*_str == *str2)
				{
					if (*_str == '\0' && *str == '\0')
					{
						return 0;
					}
					_str++;
					str2++;
				}
				if (*_str == '\0' && *str2 != '\0')
				{
					return -1;
				}
				if (*str2 == '\0')
				{
					return 0;
				}
			
				str2 = str;
				_str++;
			
		}
		return -1;
	}

	String& operator += (const char c)
	{
		pushBack(c);
		return *this;
	}
	String& operator += (const char* s)
	{
		Append(s);
		return *this;
	}

	String& operator += (const String& s)
	{
		*this += s._str;
		return *this;
	}


private:
	char* _str;
	size_t _size;
	size_t _capacity;
};

String operator + (const string& s1, const String& s2)
{
	String ret(s1.c_str());
	return ret += s2;

}

String operator + (const String& s1, const char* str)
{
	String ret(s1);
	return ret += str;
}

String operator + (const String& s1, char c)
{
	String ret(s1);
	return ret += c;
}

void PrintStringIterator(const String& str)
{
	String::const_iterator sit = str.begin();
	while (sit != str.end())
	{
		cout << *sit++;
	}
	cout << endl;
}

//ostream& operator << (ostream& _count, const String& s)
//{
//	cout << s.c_str << endl;
//}

int main()
{
	String s = "2343168753";
	char a[] = { "436" };
	char* b = a;
	int ret = s.find(b);
	

	system("pause");
	return 0;
}



