#include "SList.h"

int main()
{
	SList list;
	SListNode *cur;
	SListInit(&list);
	SListPushFront(&list, 1);
	SListPushFront(&list, 3);
	SListPushFront(&list, 2);
	SListNodePrint(&list);
	SListPushBuck(&list, 4);
	SListPushBuck(&list, 6);
	SListPushBuck(&list, 8);
	SListNodePrint(&list);
	/*SListDelFront(&list);
	SListDelFront(&list);
	SListNodePrint(&list);
	SListDelBack(&list);
	SListDelBack(&list);
	SListNodePrint(&list);*/
	cur = SListNodeFind(&list, 3);
	SListInsertAfter(cur, 9);
	SListNodePrint(&list);
	SListEarseAfter(cur);
	SListNodePrint(&list);
	SListRemove(&list, 6);
	SListNodePrint(&list);




	system("pause");
	return 0;
}