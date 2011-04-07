#include <avr/io.h>
#include <avr/interrupt.h>
#include "queue.h"
#include "uart.h"
#include "s_uart_internal.h"

/* Must be a power of 2 */
#ifndef TX_BUFF_SZ
#define TX_BUFF_SZ 0x20
#endif

/* Must be a power of 2 */
#ifndef RX_BUFF_SZ
#define RX_BUFF_SZ 0x20
#endif

/* Queue */
char uart_tx_buff[UART_TX_BUFF_SZ];
char uart_rx_buff[UART_RX_BUFF_SZ];

int uart_tx_head;
int uart_tx_tail;

int uart_rx_head;
int uart_rx_tail;

void *uart_init (int id)
{
	if (id >= NUART) return NULL;
	UCSR0C = 3<<UCSZ00;
#ifndef U2X_OFF
	UCSR0A |= (1<<U2X0);
#endif
	UCSR0B = (1<<RXEN0)
		| (1<<TXEN0)
		| (1<<TXCIE0)
		| (1<<RXCIE0);
	calcbaud (9600);

	uart_rx_head = 0;
	uart_rx_tail = 0;

	uart_tx_head = 0;
	uart_tx_tail = 0;

	return (void *)1;
}

ISR (USART_RX_vect)
{
	uart_rx_tail = (uart_rx_tail+1) & (UART_RX_BUFF_SZ-1);
	uart_rx_buff[uart_rx_tail] = UDR0;
}

ISR (USART_TX_vect)
{
	if (uart_tx_head == uart_tx_tail) return;
	uart_tx_head = (uart_tx_head+1) & (UART_RX_BUFF_SZ-1);
	UDR0 = uart_tx_buff[uart_tx_head];
}
