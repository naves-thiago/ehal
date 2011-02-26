#include <avr/io.h>
#include <avr/interrupt.h>
#include "queue.h"
#include "uart.h"

extern struct queue uart_tx;

int uart_write (void *unused, unsigned char *ptr, int sz)
{
	uint8_t data;
	while (sz-- && queue_enq (&uart_tx, *ptr))
			ptr++;
	if (queue_deq (&uart_tx, &data))
		UDR=data;
	while (!queue_isempty (&uart_tx));
	return sz;
}
