/** @file Queue module of unsigned chars. */
#ifndef _QUEUE_H_
#define _QUEUE_H_

struct queue {
	/** your buffer goes here. */
	unsigned char *buff;
	/** number of elements in buff */
	unsigned char sz;
	/** start, index of first element */
	unsigned char s;
	/** number of ocupied bytes */
	unsigned char ocupied;
};

/** @brief set user defined buffer to be the queue buffer. */
void
queue_init	(struct queue *q,
		unsigned char *buff,
		unsigned char sz);

/** @brief returns how many bytes are in the queue. */
unsigned char
queue_ocupied	(struct queue *q);

/** @brief returns non-zero if queue is full */
unsigned char
queue_full	(struct queue *q);

/** @brief returns non-zero if queue is empty */
unsigned char
queue_empty	(struct queue *q);

/** @brief put data in the queue, return zero when success */
unsigned char
queue_enq	(struct queue *q,
		unsigned char data);

/** @brief cp first element in the queue to *ret and remove it from queue */
unsigned char
queue_deq	(struct queue *q,
		unsigned char *ret);

/** @brief same as before but without removing it */
unsigned char
queue_peek	(struct queue *q,
		unsigned char *ret);

#endif		/* #ifndef __QUEUE_H_ */
