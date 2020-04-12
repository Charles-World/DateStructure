#ifndef __SList__h__
#define __SList__h__

#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <assert.h>

typedef struct SListNode
{
	int data;
	struct SListNode *nest;
}SListNode;

typedef struct SList
{
	SListNode *first;
}SList;

void SListInit(SList *list);
SListNode *BuySListNode(int data);
void SListPushFront(SList *list, int data);
void SListDelFront(SList *list);
void SListPushBuck(SList *list, int data);
void SListDelBack(SList *list);
void SListNodePrint(SList *list);
SListNode *SListNodeFind(SList *list, int data);
void SListInsertAfter(SListNode *pos, int data);
void SListEarseAfter(SListNode *pos);
void SListRemove(SList *list, int data);


#endif //__SList__h__