#include <stdio.h>
#include "list.h"
#include "queue.h"

/* MAIN: */
int main(int argc, char * argv[])
{
	int i;
	struct list list = Linit();
	struct queue queue = Qinit();
	Ladd(list, 1);
	Ladd(list, 2);
	Ladd(list, 3);
	printf("[");
	for (i = 0; i < list.size; ++i)
	{
		printf("%d, ", list.Plist[i]);
	}
	printf("]\n");
	return 0;
}