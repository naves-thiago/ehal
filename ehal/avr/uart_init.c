#include <avr/io.h>
#include <avr/interrupt.h>
#include "queue.h"
#include "uart.h"
#include "uart_implementation.h"

/* Must be a power of 2 */
#ifndef TX_BUFF_SZ
#define TX_BUFF_SZ 0x20
#endif

/* Must be a power of 2 */
#ifndef RX_BUFF_SZ
#define RX_BUFF_SZ 0x20
#endif

/* Queue */
static uint8_t tx_buff[TX_BUFF_SZ];
static uint8_t rx_buff[RX_BUFF_SZ];
struct queue uart_tx, uart_rx;

void *uart_init (int id)
{
	if (id >= NUM_UARTS) return NULL;
	UCSR0C = 3<<UCSZ00;
#ifndef U2X_OFF
	UCSR0A |= (1<<U2X0);
#endif
	UCSR0B = (1<<RXEN0)
		| (1<<TXEN0)
		| (1<<TXCIE0)
		| (1<<RXCIE0);
	uart_setbaud (0, B9600);
	queue_init (&uart_tx, tx_buff, TX_BUFF_SZ);
	queue_init (&uart_rx, rx_buff, RX_BUFF_SZ);
	return (void *)1;
}

ISR (USART_RX_vect)
{
	queue_enq (&uart_rx, UDR0);
}

ISR (USART_TX_vect)
{
	unsigned char c;
	if (queue_isempty (&uart_tx)) return;
	queue_deq (&uart_tx, &c);
	UDR0 = c;
}
