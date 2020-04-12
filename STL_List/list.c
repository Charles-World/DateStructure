#include "SList.h"

void SListInit(SList *list)   //坑B浪费了爸爸十几分钟,测试前一定加上
{
	assert(list != NULL);    
	list->first = NULL;      //初始化
}

SListNode *BuySListNode(int data)    //创建一个节点
{
	SListNode *node = (SListNode*)malloc(sizeof(SListNode));
	assert(node != NULL);
	node->data = data;
	node->nest = NULL;

	return node;
}

void SListPushFront(SList *list, int data)    //头插
{
	assert(list != NULL);
	SListNode *node = BuySListNode(data);    
	node->nest = list->first;                   
	list->first = node;
}

void SListDelFront(SList *list)
{
	assert(list != NULL);
	assert(list->first != NULL);
	SListNode *OldFirst = list->first;
	list->first = list->first->nest;
	free(OldFirst);
}

void SListPushBuck(SList *list, int data)
{
	assert(list != NULL);
	if (list->first == NULL)
	{
		SListPushFront(list, data);
	}
	SListNode *node = BuySListNode(data);
	SListNode *lastone = list->first;
	for (; lastone->nest != NULL; lastone = lastone->nest)
	{
		;
	}

	lastone->nest = node;
}

void SListDelBack(SList *list)
{
	assert(list != NULL);
	assert(list->first != NULL);
	SListNode *cur = list->first;
	for (; cur->nest->nest != NULL; cur = cur->nest)
	{
		;
	}

	free(cur->nest);
	cur->nest = NULL;
}

void SListNodePrint(SList *list)
{
	assert(list != NULL);
	assert(list->first != NULL);
	SListNode *cur = list->first;
	for (; cur != NULL; cur = cur->nest)
	{
		printf("%d--->", cur->data);
	}
	printf("NULL\n");
}

SListNode *SListNodeFind(SList *list, int data)
{
	assert(list != NULL);
	assert(list->first != NULL);
	SListNode *cur = list->first;
	for (; cur != NULL; cur = cur->nest)
	{
		if (cur->data == data)
		{
			return cur;
		}
	}
	return NULL;
}

void SListInsertAfter(SListNode *pos, int data)
{
	assert(pos != NULL);
	SListNode *node = BuySListNode(data);
	node->nest = pos->nest;
	pos->nest = node;
}

void SListEarseAfter(SListNode *pos)
{
	assert(pos != NULL);
	SListNode *nest = pos->nest->nest;
	free(pos->nest);
	pos->nest = nest;
}

void SListRemove(SList *list, int data)
{
	assert(list != NULL);
	assert(list->first != NULL);
	
	SListNode *prev = NULL;
	SListNode *cur = list->first;
	while (cur != NULL && cur->data != data)
	{
		prev = cur;
		cur = cur->nest;
	}

	if (cur == NULL)
	{
		return 0;
	}

	if (prev == NULL)
	{
		SListDelFront(list);
	}
	prev->nest = cur->nest;
	free(cur);
}