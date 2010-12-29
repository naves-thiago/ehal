#include "queue.h"

void queue_init (struct queue *q,
		unsigned char *buff,
		unsigned char sz )
{
	q->buff = buff;
	q->sz = sz;
	q->s = 0;
	q->ocupied = 0;
}

unsigned char queue_ocupied (struct queue *q)
{
	return q->ocupied;
}

unsigned char queue_isfull (struct queue *q)
{
	return q->ocupied == q->sz;
}

unsigned char queue_isempty (struct queue *q)
{
	return q->ocupied == 0;
}

unsigned char queue_peakfirst (struct queue *q, unsigned char *ret)
{
	if (queue_isempty( q )) return 1;
	*ret = q->buff[ q->s ];
	return 0;
}

unsigned char queue_peaklast (struct queue *q, unsigned char *ret)
{
	if (queue_isempty( q )) return 1;
	*ret = q->buff[ (q->s + q->ocupied-1) % q->sz ];
	return 0;
}

unsigned char queue_enq (struct queue *q, unsigned char data)
{
	if (queue_isfull( q )) return 1;
	q->buff[ (q->s + q->ocupied) % q->sz ] = data;
	q->ocupied++;
	return 0;
}

unsigned char queue_deq (struct queue *q, unsigned char *ret)
{
	if (queue_isempty( q )) return 1;
	*ret = q->buff[ q->s++ ];
	q->ocupied--;
	if (q->s >= q->sz) q->s = 0;
	return 0;
}
