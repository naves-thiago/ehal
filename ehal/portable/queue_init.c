#include "queue.h"

void queue_init (struct queue *q,
		unsigned char *buff,
		int sz )
{
	q->buff = buff;
	q->sz = sz;
	q->s = 0;
	q->ocupied = 0;
}
