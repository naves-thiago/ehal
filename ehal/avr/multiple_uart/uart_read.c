#include "queue.h"
#include "cpu.h"
#include "uart_internal.h"

int uart_read (void *unused, unsigned char *ptr, int sz)
{
	int readed=0;
	while (readed < sz){
		if (uart_rx_head != uart_rx_tail){
			uart_rx_head = (uart_rx_head+1) & (UART_RX_BUFF_SZ-1);
			*ptr = uart_rx_buff[uart_rx_head];
			ptr++;
			readed++;
		} else {
			cpu_sleep (sleep_mode_iddle);
		}
	}
	return sz;
}
