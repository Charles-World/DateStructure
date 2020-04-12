#define _CRT_SECURE_NO_WARNIGS 1

#include <stdio.h>
#include <assert.h>

typedef struct DListNode
{
	int data;
	struct DListNode *next;
	struct DListNode *prev;
}DListNode;

typedef struct DList
{
	DListNode *head;
}DList;

DListNode *BuyNode(int data)
{
	DListNode *node = (DListNode*)malloc(sizeof(DListNode));
	assert(node != NULL);

	node->data = data;
	node->next = NULL;
	node->prev = NULL;

	return node;
}

void DListInit(DList *list)
{
	assert(list != NULL);
	DListNode *head = BuyNode(0);
	head->next = head;
	head->prev = head;
	list->head = head;
}

void DLNPushFront(DList *list, int data)   
{
	assert(list != NULL);
	DListNode *node = BuyNode(data);
	node->prev = list->head;
	node->next = list->head->next;
	list->head->next->prev = node;    //这句必须在前否则会造成传址失误
	list->head->next = node;
}

void DLNPushBack(DList *list, int data)
{
	assert(list != NULL);
	DListNode *node = BuyNode(data);
	node->next = list->head;
	node->prev = list->head->prev;
	list->head->prev->next = node;      //这句必须在前否则会造成传址失误
	list->head->prev = node;
}

void DLNPopFront(DList *list)
{
	assert(list != NULL);
	assert(list->head->next != list->head);
	DListNode *old = list->head->next;              //记得创建old不能直接freelist->head->next
	list->head->next->next->prev = list->head;  //这里也要注意顺序
	list->head->next = list->head->next->next;
	free(old);
}

void DLNPopBack(DList *list)
{
	assert(list != NULL);
	assert(list->head->next != list->head);
	DListNode *old = list->head->prev;            //记得创建old不能直接freelist->head->next
	list->head->prev->prev->next = list->head;
	list->head->prev = list->head->prev->prev;//这里也要注意顺序
	free(old);
}

void DLNInsert(DListNode *pos, int data)
{
	assert(pos != NULL);
	DListNode *node = BuyNode(data);
	node->next = pos;
	node->prev = pos->prev;
	pos->prev->next = node;
	pos->prev = node;
}

void DLNPrint(DList *list)
{
	assert(list != NULL);
	for (DListNode *cur = list->head->next; cur != list->head; cur = cur->next)
	{
		printf("%d--->", cur->data);
	}
	printf("\n");
}

void DLNErase(DListNode *pos)
{
	assert(pos != NULL);
	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;
	free(pos);
}

DListNode *DLNFind(DList *list, int data)
{
	assert(list != NULL);
	DListNode *cur;
	for (cur = list->head->next; cur != list->head; cur = cur->next)
	{
		if (cur->data == data)
		{
			return cur;
		}
	}
	return NULL;
}
void DLNClear(DList *list)
{
	assert(list != NULL);
	for (DListNode * cur = list->head->next; cur != list->head; cur = cur->next)
	{
		free(cur);
	}
	list->head->next = list->head;
	list->head->prev = list->head;
}

void DLNDestory(DList *list)
{
	assert(list != NULL);
	DLNClear(list);
	free(list->head);
	list->head = NULL;
}
int main()
{
	DList list;
	DListNode pos;
	DListInit(&list);
	DLNPushFront(&list, 5);
	DLNPushFront(&list, 6);
	DLNPushFront(&list, 7);
	DLNPrint(&list);
	DLNPushBack(&list, 8);
	DLNPushBack(&list, 9);
	DLNPushBack(&list, 10);
	DLNPrint(&list);
	DLNPopFront(&list);
	DLNPrint(&list);
	DLNPopBack(&list);
	DLNPrint(&list);
	DLNInsert(DLNFind(&list, 5), 15);
	DLNPrint(&list);
	DLNErase(DLNFind(&list, 5));
	DLNPrint(&list);

	system("pause");
	return 0;
}