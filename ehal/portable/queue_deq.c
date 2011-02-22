#include "queue.h"

bool queue_deq (struct queue *q, unsigned char *ret)
{
	if (queue_isempty( q )) return 0;
	*ret = q->buff[q->s];
	q->s++;
	q->ocupied--;
	if (q->s >= q->sz) q->s = 0;
	return 1;
}
