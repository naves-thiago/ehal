/** @file Queue module of unsigned chars. */
#ifndef _QUEUE_H_
#define _QUEUE_H_

struct queue {
	unsigned char *buff;
	unsigned char sz;
	unsigned char s;
	unsigned char ocupied;
};

/** @brief gets a buffer and its size. Works for static and dinamic
 * @arg q - struct queue
 * @arg buff - ptr to buffer
 * @arg sz - sizeof buffer */
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

#endif		/* #ifdef __QUEUE_H_ */
