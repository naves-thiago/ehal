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

int queue_ocupied (struct queue *q)
{
	return q->ocupied;
}

bool queue_isfull (struct queue *q)
{
	return q->ocupied == q->sz;
}

bool queue_isempty (struct queue *q)
{
	return q->ocupied == 0;
}

void queue_flush (struct queue *q)
{
	q->ocupied = 0;
}

bool queue_peakfirst (struct queue *q, unsigned char *ret)
{
	if (queue_isempty (q)) return 0;
	*ret = q->buff[q->s];
	return 1;
}

bool queue_peaklast (struct queue *q, unsigned char *ret)
{
	if (queue_isempty( q )) return 0;
	*ret = q->buff[((q->s+q->ocupied) & (q->sz-1))];
	return 1;
}

bool queue_enq (struct queue *q, unsigned char data)
{
	if (queue_isfull( q )) return 0;
	q->buff[(q->s + q->ocupied) & (q->sz-1)] = data;
	q->ocupied++;
	return 1;
}

bool queue_deq (struct queue *q, unsigned char *ret)
{
	if (queue_isempty( q )) return 0;
	*ret = q->buff[q->s];
	q->s++;
	q->ocupied--;
	if (q->s >= q->sz) q->s = 0;
	return 1;
}
