#include <stdio.h>
#include "func.h"
#include "dialog.h"
#include <stdlib.h>

int main()
{
	Tree *tree = NULL;
	int rc;
	const char *msgs[] = { "0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show", "5. File", "6. Bypass", "7. Time", "8. MyFunc" };
	const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
	const int(*fptr[])(Tree **) = { NULL, Dadd, Dfind, Ddelete, Dshow, Dfile, Dbypass, Dtime, DMyFunc };
	int is;
	while (rc = dialog(msgs, NMsgs))
		if (is = fptr[rc](&tree))
			break;
	printf("That's all. Bye!\n");
	import(tree);
	delTree(&tree);
	system("dot g.dot -Tpng -og.png");
	return 0;
}

