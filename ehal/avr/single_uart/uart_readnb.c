#include "queue.h"
#include "cpu.h"
#include "uart_internal.h"

int uart_readnb (void *unused, unsigned char *ptr, int sz)
{
	int readed=0;
	while (--sz){
		if (uart_rx_head != uart_rx_tail){
			uart_rx_head = (uart_rx_head+1) & (UART_RX_BUFF_SZ-1);
			*ptr = uart_rx_buff[uart_rx_head];
			ptr++;
			readed++;
		}
	}
	return readed;
}
