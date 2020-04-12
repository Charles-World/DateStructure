#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct heap
{
	int *array;
	int size;
	int capacity;
}Heap;

void AdjustDown(int array[], int size, int root)
{

		int left = 2 * root + 1;
		int right = 2 * root + 2;
		int max;

		if (left >= size)
		{
			return;
		}

		if (right <= size && array[left] >= array[right])
		{
			max = left;
		}
	
		else
		{
			max = right;
		}

		if (array[root] >= array[max])
		{
			return;
		}
		else
		{
			int temp = array[max];
			array[max] = array[root];
			array[root] = temp;
		}

		AdjustDown(array, size, max);
}

void AdjustUp(int array[], int size, int child)
{
	assert(size);

	if (array[child] == array[0])
	{
		return;
	}
	int parent = (child - 1) / 2;

	if (array[parent] >= array[child])
	{
		return;
	}
	else
	{
		int temp = array[child];
		array[child] = array[parent];
		array[parent] = temp;
	}

	AdjustUp(array, size, parent);

}

void CreatHeap(int array, int size)
{
	//for (int i = (size - 2) / 2; i >= 0; i--)
	//{
	//	AdjustDown(array, size, i);
	//}
	for (int i = 0; i < size; i++)
	{
		AdjustUp(array, size, i);
	}
}

void HeapCreatHeap(Heap *heap, int array[],int size)
{
	assert(heap != NULL);
	heap->size = size;
	heap->capacity = 2 * size;
	heap->array = (int*)malloc(sizeof(int) * size);

	for (int i = 0; i < size; i++)
	{
		heap->array[i] = array[i];
	}

	CreatHeap(heap->array, heap->size);  
}

void HeapInsert(Heap *heap, int data)
{
	assert(heap != NULL);
	heap->size++;
	heap->array[heap->size - 1] = data;

	AdjustUp(heap->array, heap->size, heap->size - 1);
}
 
void HeapPop(Heap *heap)
{
	assert(heap != NULL);
	heap->array[0] = heap->array[heap->size - 1];
	heap->size--;

	AdjustDown(heap->array, heap->size, 0);
}

int HeapTop(Heap *heap)
{
	assert(heap != NULL);
	return heap->array[0];
}



int main()
{
	Heap a;
	int array[15] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

	HeapCreatHeap(&a, array, 15);
	/*HeapInsert(&a, 8);
	HeapPop(&a);
	printf("%d", HeapTop(&a));*/
	for (int i = 0; i < 15; i++)
	{
		printf("%d ", a.array[i]);
	}

	system("pause");
	return 0;
}