#include <avr/io.h>
#include "queue.h"
#include "uart.h"
#include "cpu.h"
#include "uart_internal.h"

static inline bool tx_is_ready (void)
{
	return UCSR0A & _BV (UDRE0);
}

int uart_writenb (void *unused, const char *ptr, int sz)
{
	int written;
	if (sz == 0) return 0;

	for (written=0; written < sz; written++){
		uart_tx_tail = (uart_tx_tail+1) & (UART_RX_BUFF_SZ-1);
		uart_tx_buff[uart_tx_tail] = *ptr++;
	}

	if (tx_is_ready ()){
		/* Send the first byte. */
		uart_tx_head = (uart_tx_head+1) & (UART_RX_BUFF_SZ-1);
		UDR0 = uart_tx_buff[uart_tx_head];
	}
	return written;
}
