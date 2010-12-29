/** @file Queue module of unsigned chars. */
#ifndef EHAL_QUEUE
#define EHAL_QUEUE

struct queue {
	unsigned char *buff;	/**< your buffer goes here. */
	unsigned char sz;	/**< number of elements in buff */
	unsigned char s;	/**< start, index of first element */
	unsigned char ocupied;	/**< number of ocupied bytes */
};

/** set user defined buffer to be the queue buffer. */
void
queue_init	(struct queue *q,
		unsigned char *buff,
		unsigned char sz);

/** returns how many bytes are in the queue. */
unsigned char
queue_ocupied	(struct queue *q);

/** returns non-zero if queue is full */
unsigned char
queue_isfull	(struct queue *q);

/** returns non-zero if queue is empty */
unsigned char
queue_isempty	(struct queue *q);

/** put data in the queue, return zero when success */
unsigned char
queue_enq	(struct queue *q,
		unsigned char data);

/** cp first element in the queue to *ret and remove it from queue */
unsigned char
queue_deq	(struct queue *q,
		unsigned char *ret);

/** same as before but without removing it */
unsigned char
queue_peaklast	(struct queue *q,
		unsigned char *ret);

/** same as before but for the first element */
unsigned char
queue_peakfirst	(struct queue *q,
		unsigned char *ret);

#endif		/* #ifndef __QUEUE_H_ */
