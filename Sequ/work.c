#include "sequ.h"

void SeqListInit(SequenceList *sl, size_t capacity)
{
	assert(sl != NULL);
	sl->size = 0;
	sl->capacity = capacity;
	sl->array = (SequenceList*)malloc(capacity * sizeof(SequenceList));
}

void SequenceListDestroy(SequenceList *sl)
{
	memset(sl->array, NULL, (sl->capacity * sizeof(SequenceList)));
	sl->size = 0;
	sl->capacity = 0;
}

void SequenceListInsertBack(SequenceList *sl, int Data)
{
	assert(sl != NULL);
	CheckCapacity(sl);
	sl->array[sl->size] = Data;
	sl->size++;
}

void SequenceListInsertFront(SequenceList *sl, int Data)
{
	assert(sl != NULL);

	for (int i = (sl->size) - 1; i >= 0; i--)
	{
		sl->array[i + 1] = sl->array[i];
	}
	sl->array[0] = Data;
	sl->size++;
}

void SequenceListDelBack(SequenceList *sl)
{
	assert(sl != NULL);
	sl->size--;
}

void SequenceListDelFront(SequenceList *sl)
{
	assert(sl != NULL);
	  
	for (int i = 1; i < sl->size; i++)
	{
		sl->array[i - 1] = sl->array[i];
	}
	sl->size--;
}

void SequenceListPrint(SequenceList *sl)
{
	for (int i = 0; i < sl->size; i++)
	{
		printf("%d", sl->array[i]);
	}
	printf("\n");
}

void CheckCapacity(SequenceList *sl)
{
	assert(sl != NULL);

	if (sl->size == sl->capacity)
	{
		sl->capacity *= 2;
		sl->array = (SequenceList*)malloc(sl->capacity * sizeof(SequenceList));
	}
}