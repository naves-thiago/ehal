#include "queue.h"

bool queue_peaklast (struct queue *q, unsigned char *ret)
{
	if (queue_isempty( q )) return 0;
	*ret = q->buff[((q->s+q->ocupied) & (q->sz-1))];
	return 1;
}
