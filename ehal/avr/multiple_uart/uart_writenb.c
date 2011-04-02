#include <avr/io.h>
#include "queue.h"
#include "uart.h"
#include "cpu.h"
#include "uart_internal.h"

static inline bool tx_is_ready (struct uart_mem_block *u)
{
	return u->ucsra & _BV (UDRE0);
}

int uart_writenb (void *_u, const char *ptr, int sz)
{
	struct uart_dev *u = _u;
	if (sz == 0) return 0;

	for (u->written=0; u->written < sz; u->written++){
		u->tx_tail = (u->tx_tail+1) & (UART_RX_BUFF_SZ-1);
		u->tx_buff[u->tx_tail] = *ptr++;
	}

	if (tx_is_ready (u->u)){
		/* Send the first byte. */
		u->tx_head = (u->tx_head+1) & (UART_RX_BUFF_SZ-1);
		u->u->udr = u->tx_buff[u->tx_head];
	}
	return u->written;
}
