#ifndef __sequ__h__
#define __sequ__h__
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct SequenceList
{
	int *array;
	int size;
	int capacity;
}SequenceList;
SequenceList *sl;

void SeqListInit(SequenceList *sl, size_t capacity);
void SequenceListDestroy(SequenceList *sl);
void SequenceListInsertBack(SequenceList *sl, int Data);
void SequenceListInsertFront(SequenceList *sl, int Data);
void SequenceListDelBack(SequenceList *sl);
void SequenceListDelFront(SequenceList *sl);
void SequenceListPrint(SequenceList *sl);
void CheckCapacity(SequenceList *sl);

#endif //__sequ__h__
