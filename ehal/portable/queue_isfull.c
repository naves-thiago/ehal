#include "queue.h"

bool queue_isfull (struct queue *q)
{
	return q->ocupied == q->sz;
}
