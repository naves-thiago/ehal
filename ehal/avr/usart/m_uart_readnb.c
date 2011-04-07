#include "queue.h"
#include "cpu.h"
#include "m_uart_internal.h"

int uart_readnb (void *_u, char *ptr, int sz)
{
	struct uart_dev *u = _u;
	u->readed=0;
	while (sz--){
		if (u->rx_head != u->rx_tail){
			u->rx_head = (u->rx_head+1) & (UART_RX_BUFF_SZ-1);
			*ptr = u->rx_buff[u->rx_head];
			ptr++;
			u->readed++;
		}
	}
	return u->readed;
}
