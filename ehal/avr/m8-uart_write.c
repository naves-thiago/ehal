#include <avr/io.h>
#include <avr/interrupt.h>
#include "queue.h"
#include "uart.h"

extern struct queue tx;

int uart_write (void *unused, unsigned char *ptr, int sz)
{
	uint8_t data;
	while (sz-- && queue_enq (&tx, *ptr))
			ptr++;
	if (queue_deq (&tx, &data))
		UDR=data;
	while (!queue_isempty (&tx));
	return sz;
}
