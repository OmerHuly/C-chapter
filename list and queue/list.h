#include <malloc.h>

typedef struct list
{
	int * Plist;
	int size;
} list;

struct list Linit();
void Ldel(struct list list);
void Ladd(struct list list, int item);
void Lerase(struct list list, int pointer);
int Llen(struct list list);
int pfirst(struct list list);
int plast(struct list list);
int pnext(struct list list, int pointer);
int plast(struct list list, int pointer);
int get(struct list list, int pointer);
int avg(struct list list);

struct list Linit()
{
	struct list list;
	list.size = 0;
	list.Plist = (int *)realloc(list.Plist, list.size);
	return list;
}

void Ldel(struct list list)
{
	free(list.Plist);
}

void Ladd(struct list list, int item)
{
	list.Plist = (int *)realloc(list.Plist, list.size + 1);
	list.Plist[list.size - 1] = item;
}

void Lerase(struct list list, int pointer)
{
	list.Plist[pointer] = list.Plist[pointer + 1];
}

int Llen(struct list list)
{
	return list.size;
}

int pfirst(struct list list)
{
	return 0;
}

int pnext(struct list list, int pointer)
{
	return pointer + 1;
}

int plast(struct list list, int pointer)
{
	return pointer - 1;
}

int get(struct list list, int pointer)
{
	return list.Plist[pointer];
}

int avg(struct list list)
{
	return 0;
}
