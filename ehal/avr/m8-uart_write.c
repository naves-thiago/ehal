#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include "queue.h"
#include "uart.h"

extern struct queue uart_tx;

static inline bool tx_is_iddle (void)
{
	return UCSRA & _BV (UDRE);
}

int uart_write (void *unused, unsigned char *ptr, int sz)
{
	uint8_t data;
	while (sz-- && queue_enq (&uart_tx, *ptr))
			ptr++;

	if (tx_is_iddle () && queue_deq (&uart_tx, &data))
		UDR=data;
	/* TODO: Sleep the CPU here. */
	while (!queue_isempty (&uart_tx) && !tx_is_iddle ());

	return sz;
}
