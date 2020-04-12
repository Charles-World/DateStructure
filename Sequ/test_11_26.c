#include "sequ.h"

int main()
{
	SequenceList sl;

	SeqListInit(&sl, 10);
	SequenceListInsertBack(&sl, 1);
	SequenceListInsertBack(&sl, 5);
	SequenceListInsertBack(&sl, 9);
	SequenceListPrint(&sl);
	SequenceListInsertFront(&sl, 3);
	SequenceListInsertFront(&sl, 8);
	SequenceListInsertFront(&sl, 6);
	SequenceListPrint(&sl);
	SequenceListDelBack(&sl);
	SequenceListPrint(&sl);
	SequenceListDelFront(&sl);
	SequenceListPrint(&sl);
	SequenceListDestroy(&sl);
	SequenceListPrint(&sl);

	system("pause");
	return 0;
}