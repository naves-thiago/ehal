#include "queue.h"

bool queue_peakfirst (struct queue *q, unsigned char *ret)
{
	if (queue_isempty (q)) return 0;
	*ret = q->buff[q->s];
	return 1;
}
