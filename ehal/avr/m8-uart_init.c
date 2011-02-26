#include <avr/io.h>
#include <avr/interrupt.h>
#include "queue.h"
#include "uart.h"
#include "uart_specific.h"

/* Must be a power of 2 */
#ifndef TX_BUFF
#define TX_BUFF 0x20
#endif

/* Must be a power of 2 */
#ifndef RX_BUFF
#define RX_BUFF 0x20
#endif

#define U2X_OFF

#ifndef U2X_OFF
#define U2X_ON
#endif

/* Queue */
static uint8_t tx_buff[TX_BUFF];
static uint8_t rx_buff[RX_BUFF];
struct queue uart_tx, uart_rx;

void *uart_init (int id)
{
	if (id >= UART_NUM) return NULL;
	UCSRC = 3<<UCSZ0;
#ifndef U2X_ON
	UCSRA |= (1<<U2X);
#endif
	UCSRB = (1<<RXEN)
		| (1<<TXEN)
		| (1<<TXCIE)
		| (1<<RXCIE);
	uart_setbaud (0, B9600);
	queue_init (&uart_tx, tx_buff, TX_BUFF);
	queue_init (&uart_rx, rx_buff, RX_BUFF);
	return (void *)1;
}

ISR (USART_RXC_vect)
{
	queue_enq (&uart_rx, UDR);
}

ISR (USART_TXC_vect)
{
	unsigned char c;
	if (queue_isempty (&uart_tx)) return;
	queue_deq (&uart_tx, &c);
	UDR = c;
}
