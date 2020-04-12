#include <iostream>
#include <algorithm>
#include <assert.h>
#include <string>

using namespace std;
template<class T>
class Vector
{
public:
	typedef T* Iterator;
	typedef const T* ConstIterator;
	//�����еĵ�ַ�����������Կ���ͨ����ַ-��ַ���õ��±꣬Ҳ���൱����
	//0X156462 �� 0X1564624,��һ�����׵�ַ���õڶ�����һ���͵õ����Լ����±�
	Iterator Begin()
	{
		return _start;
	}
	Iterator End()
	{
		return _finish - 1;
	}
	ConstIterator CBegin() const
	{
		return _start;
	}
	ConstIterator CEnd() const
	{
		return _finish - 1;
	}
	size_t Size() const
	{
		return _finish - _start;
	}
	size_t Capacity() const
	{
		return _endOfStorage - _start;
	}
	Vector()
		: _start(nullptr)
		, _finish(nullptr)
		, _endOfStorage(nullptr)
	{}
	Vector(int n = 5, const T& value = T())
		: _start(nullptr)
		, _finish(nullptr)
		, _endOfStorage(nullptr)
	{
		Reserve(n);
		while (n--)
		{
			PushBack(value);
		}
	}
	// �������ʹ��Iterator�����������ͻᵼ�³�ʼ���ĵ���������[first,last]ֻ����Vector�ĵ�����
	// ������������������������������[first,last]���������������ĵ��������䡣
	template<class InputIterator>
	Vector(InputIterator first, InputIterator last)
	{
		Reserve(last - first);
		while (first != last)
		{
			PushBack(*first);
			++first;
		}
	}

	Vector(const Vector<T>& v)
		: _start(nullptr)
		, _finish(nullptr)
		, _endOfStorage(nullptr)
	{
		Reserve(v.Capacity());
		Iterator it = Begin();
		ConstIterator vit = v.CBegin();
		while (vit != v.CEnd())
		{
			*it++ = *vit++;
		}
		_finish = _start + v.Size();
		_endOfStorage = _start + v.Capacity();
	}
	Vector<T>& operator= (Vector<T> v)
	{
		Swap(v);
		return *this;
	}
	~Vector()
	{
		delete[] _start;
		_start = _finish = _endOfStorage = nullptr;
	}
	void Reserve(size_t n)
	{
		if (n > Capacity())
		{
			size_t size = Size();
			T* tmp = new T[n];
			if (_start)
			{
				for (size_t i = 0; i < size; ++i)
				{
					tmp[i] = _start[i];
				}
			}
			
			_start = tmp;
			_finish = _start + size;
			_endOfStorage = _start + n;
		}
	}
	void Resize(size_t n, const T& value = T())
	{
		// 1.���nС�ڵ�ǰ��size�������ݸ�����С��n
		if (n <= Size())
		{
			_finish = _start + n;
			return;
		}
		// 2.�ռ䲻��������
		if (n > Capacity())
		{
			Reserve(n);
		}
		// 3.��size����n
		Iterator it = _finish;
		_finish = _start + n;
		while (it != _finish)
		{
			*it = value;
			++it;
		}
	}
	void Swap(Vector<T>& v)
	{
		swap(_start, v._start);
		swap(_finish, v._finish);
		swap(_endOfStorage, v._endOfStorage);
	}
	void PushBack(const T& x)
	{
		Insert(End(), x);
	}
	void PopBack()
	{
		Erase(--End());
	}
	Iterator Insert(Iterator pos, const T& x)
	{

		if (_finish == _endOfStorage)
		{
			size_t newCapacity = Capacity() == 0 ? 1 : Capacity() * 2;
			Reserve(newCapacity);


		}
		Iterator end = _finish - 1;
		while (end > pos)
		{
			*(end + 1) = *end;
			--end;
		}
		*pos = x;
		++_finish;
		return pos;
	}
	// ����ɾ�����ݵ���һ������
	// ������:һ�߱���һ��ɾ���ĵ�����ʧЧ����
	Iterator Erase(Iterator pos)
	{
		// Ų�����ݽ���ɾ��
		Iterator begin = pos + 1;
		while (begin != _finish) {
			*(begin - 1) = *begin;
			++begin;
		}
		--_finish;
		return pos;
	}
	T& operator[](size_t pos)
	{
		return _start[pos];
	}
private:
	Iterator _start; // ָ�����ݿ�Ŀ�ʼ
	Iterator _finish; // ָ����Ч���ݵ�β
	Iterator _endOfStorage; // ָ��洢������β
};

int main()
{
	Vector<int> a(3);
	a.PushBack(4);

	system("pause");
	return 0;
}