#include "queue.h"

bool queue_enq (struct queue *q, unsigned char data)
{
	if (queue_isfull( q )) return 0;
	q->buff[(q->s + q->ocupied) & (q->sz-1)] = data;
	q->ocupied++;
	return 1;
}
