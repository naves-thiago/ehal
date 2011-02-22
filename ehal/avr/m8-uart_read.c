#include <avr/io.h>
#include <avr/interrupt.h>
#include "queue.h"
#include "uart.h"

extern struct queue rx;

int uart_read (void *unused, unsigned char *ptr, int sz)
{
	while (sz){
		if (queue_deq (&rx, ptr)){
			sz--;
			ptr++;
		}
	}
	return sz;
}
