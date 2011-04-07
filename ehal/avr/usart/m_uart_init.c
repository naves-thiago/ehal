#include <avr/io.h>
#include <avr/interrupt.h>
#include "queue.h"
#include "uart.h"
#include "m_uart_internal.h"

struct uart_dev uart_dev[NUART];

struct uart_mem_block *uart_mem_block[NUART] = {
#ifndef USART0_OFF
	(struct uart_mem_block*)0xC0,
#endif
#ifndef USART1_OFF
	(struct uart_mem_block*)0xC8,
#endif
};

static struct uart_dev *uart_dev_init (unsigned int id)
{
	struct uart_dev *d=NULL;
	d = &uart_dev[id];
	d->u = uart_mem_block[id];
	d->readed = 0;
	d->written = 0;
	d->rx_head = 0;
	d->tx_head = 0;
	d->rx_tail = 0;
	d->tx_tail = 0;

	return d;
}

void *uart_init (int id)
{
	struct uart_dev *d;
	if (id >= NUART) return NULL;
	d = uart_dev_init (id);
#ifndef U2X_OFF
	d->u->ucsra = _BV (U2X0);
#endif 
	d->u->ucsrc = 3<<UCSZ00;
	d->u->ucsrb = _BV (RXEN0)
		| _BV (TXEN0)
		| _BV (TXCIE0)
		| _BV (RXCIE0);
	calcbaud (d->u, 9600);
	return d;
}

#ifndef USART0_OFF
ISR (USART0_RX_vect)
{
	uint8_t i = uart_dev[0].rx_tail;
	i = (i+1) & (UART_RX_BUFF_SZ-1);
	uart_dev[0].rx_buff[i] = UDR0;
	uart_dev[0].rx_tail = i;
}

ISR (USART0_TX_vect)
{
	if (uart_dev[0].tx_head == uart_dev[0].tx_tail) return;
	uart_dev[0].tx_head = (uart_dev[0].tx_head+1) & (UART_RX_BUFF_SZ-1);
	UDR0 = uart_dev[0].tx_buff[uart_dev[0].tx_head];
}
#endif

#ifndef USART1_OFF
ISR (USART1_RX_vect)
{
	uint8_t i = uart_dev[1].rx_tail;
	i = (i+1) & (UART_RX_BUFF_SZ-1);
	uart_dev[1].rx_buff[i] = UDR1;
	uart_dev[1].rx_tail = i;
}

ISR (USART1_TX_vect)
{
	if (uart_dev[1].tx_head == uart_dev[1].tx_tail) return;
	uart_dev[1].tx_head = (uart_dev[1].tx_head+1) & (UART_RX_BUFF_SZ-1);
	UDR1 = uart_dev[1].tx_buff[uart_dev[1].tx_head];
}
#endif
