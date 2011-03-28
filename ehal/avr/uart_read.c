#include "queue.h"
#include "cpu.h"
#include "uart_internal.h"

extern uint8_t uart_rx_buff;
extern uint8_t uart_rx_head;
extern uint8_t uart_rx_tail;

int uart_read (void *unused, unsigned char *ptr, int sz)
{
	while (sz){
		if (sz && (uart_rx_head != uart_rx_tail)){
			sz--;
			ptr++;
		} else {
			cpu_sleep (sleep_mode_iddle);
		}
	}
	return sz;
}
