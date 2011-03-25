#include <avr/io.h>
#include "queue.h"
#include "uart.h"
#include "cpu.h"
#include "uart_implementation.h"

extern struct queue uart_tx;

static inline bool tx_is_iddle (void)
{
	return UCSR0A & _BV (UDRE0);
}

int uart_write (void *unused, char *ptr, int sz)
{
	uint8_t data;
	while (sz && queue_enq (&uart_tx, *ptr)){
			ptr++;
			sz--;
	}

	if (tx_is_iddle () && queue_deq (&uart_tx, &data))
		UDR0=data;

	while (!queue_isempty (&uart_tx) && !tx_is_iddle ()){
		cpu_sleep (sleep_mode_iddle);
	}

	return sz;
}
