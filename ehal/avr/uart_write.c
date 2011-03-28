#include <avr/io.h>
#include "queue.h"
#include "uart.h"
#include "cpu.h"
#include "uart_internal.h"

extern char uart_tx_buff[TX_BUFF_SZ];
extern uint8_t uart_tx_head;
extern uint8_t uart_tx_tail;

static inline bool tx_is_iddle (void)
{
	return UCSR0A & _BV (UDRE0);
}

int uart_write (void *unused, char *ptr, int sz)
{
	if (sz == 0) return 0;

	while (sz && uart_tx_head != uart_tx_tail){
		uart_tx_tail = (uart_tx_tail+1) & (RX_BUFF_SZ-1);
		uart_tx_buff[uart_tx_tail] = *ptr;
		ptr++;
		sz--;
	}

	/* Send the first byte. */
	uart_tx_tail = (uart_tx_tail+1) & (RX_BUFF_SZ-1);
	UDR0 = uart_tx_buff[uart_tx_tail];

	while (uart_tx_head != uart_tx_tail){
		cpu_sleep (sleep_mode_iddle);
	}

	return sz;
}
