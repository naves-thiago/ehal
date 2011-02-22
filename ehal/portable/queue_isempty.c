#include "queue.h"

bool queue_isempty (struct queue *q)
{
	return q->ocupied == 0;
}
