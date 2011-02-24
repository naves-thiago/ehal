/** @file Queue module of unsigned chars. */
#ifndef EHAL_QUEUE_H
#define EHAL_QUEUE_H

#ifdef EHAL_GLOBAL
#include "ehal_global.h"
#endif

#include <stdbool.h>
#include <stdint.h>

struct queue {
	unsigned char *buff;	/**< your buffer goes here. */
	uint8_t sz;	/**< number of elements in buff */
	uint8_t s;	/**< start, index of first element */
	uint8_t ocupied;	/**< number of ocupied bytes */
};

/** set user defined buffer to be the queue buffer. */
void queue_init	(struct queue *q,
		unsigned char *buff,
		int sz);

/** returns how many bytes are in the queue. */
int queue_ocupied	(struct queue *q);

/** returns non-zero if queue is full */
bool queue_isfull	(struct queue *q);

/** returns non-zero if queue is empty */
bool queue_isempty	(struct queue *q);

/** put data in the queue, return true for success */
bool queue_enq	(struct queue *q, unsigned char data);

/** cp first element in the queue to *ret and remove it from queue */
bool queue_deq	(struct queue *q, unsigned char *ret);

void queue_flush	(struct queue *q);

/** same as before but without removing it */
bool queue_peaklast	(struct queue *q, unsigned char *ret);

/** same as before but for the first element */
bool queue_peakfirst	(struct queue *q, unsigned char *ret);

#endif		/* #ifndef __QUEUE_H_ */
