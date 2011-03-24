#include "queue.h"
#include "cpu.h"

extern struct queue uart_rx;

int uart_read (void *unused, unsigned char *ptr, int sz)
{
	while (sz){
		cpu_sleep (sleep_mode_iddle);
		if (queue_deq (&uart_rx, ptr)){
			sz--;
			ptr++;
		}
	}
	return sz;
}
