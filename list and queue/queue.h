#include <malloc.h>

typedef struct queue
{
	int * Pqueue;
	int size;
} queue;

struct queue Qinit();
void Qdel(struct queue queue);
void Qadd(struct queue queue, int item);
int popf(struct queue queue);
int Qlen(struct queue queue);
int firstQ(struct queue queue);

struct queue Qinit()
{
	struct queue queue;
	queue.size = 0;
	queue.Pqueue = (int *)realloc(queue.Pqueue, queue.size);
	return queue;
}

void Qdel(struct queue queue)
{
	free(queue.Pqueue);
}

void Qadd(struct queue queue, int item)
{
	queue.Pqueue = (int *)realloc(queue.Pqueue, queue.size + 1);
	queue.Pqueue[queue.size - 1] = item;
}

int popf(struct queue queue)
{
	int ret = queue.Pqueue[0];
	++queue.Pqueue;
	--queue.size;
	return ret;
}

int Qlen(struct queue queue)
{
	return queue.size;
}

int firstQ(struct queue queue)
{
	return queue.Pqueue[0];
}
