#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "queue.h"
#include "uart.h"

extern struct queue uart_rx;

static void proc_iddle (void)
{
	cli ();
	set_sleep_mode(SLEEP_MODE_IDLE);
	sleep_enable();
	sei();
	sleep_cpu();
	sleep_disable();
}

int uart_read (void *unused, unsigned char *ptr, int sz)
{
	while (sz){
		if (queue_deq (&uart_rx, ptr)){
			sz--;
			ptr++;
		}
		proc_iddle ();
	}
	return sz;
}
