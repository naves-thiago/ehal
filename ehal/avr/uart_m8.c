#include <avr/io.h>
#include <avr/interrupt.h>
#include "queue.h"
#include "uart.h"

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
uint8_t tx_buff[TX_BUFF];
uint8_t rx_buff[RX_BUFF];
struct queue tx, rx;

void *uart_init (int id)
{
	if (!uart_isvalid(id)) return 0;
	UCSRC = 3<<UCSZ0;
#ifndef U2X_ON
	UCSRA |= (1<<U2X);
#endif
	UCSRB = (1<<RXEN)
		| (1<<TXEN)
		| (1<<TXCIE)
		| (1<<RXCIE);
	uart_setbaud (0, B9600);
	queue_init (&tx, tx_buff, TX_BUFF);
	queue_init (&rx, rx_buff, RX_BUFF);
	return (void *)1;
}

void *uart_isvalid (int id)
{
	if (id < 1) return (void *)1;
	return (void *)0;
}

static inline void calcbaud (uint32_t baud)
{
#ifndef U2X_ON
	UBRRH = ((F_CPU/(8UL*baud)) -1) >> 8;
	UBRRL = (F_CPU/(8UL*baud)) -1;
#else
	UBRRH = ((F_CPU/(16UL*baud)) -1) >> 8;
	UBRRL = (F_CPU/(16UL*baud)) -1;
#endif
}

#define ENTRY(_baud) B ## _baud: calcbaud (_baud)
void uart_setbaud (void *unused, u08 baud)
{
	switch(baud){
	case ENTRY(  1200); break;
	case ENTRY(  2400); break;
	case ENTRY(  4800); break;
	case ENTRY(  9600); break;
	case ENTRY( 19200); break;
	case ENTRY( 38400); break;
	case ENTRY(115200); break;
	default: break;
	}
}
#undef ENTRY

ISR (USART_RXC_vect)
{
	queue_enq (&rx, UDR);
}

ISR (USART_TXC_vect)
{
	unsigned char c;
	if (queue_isempty (&tx)) return;
	queue_deq (&tx, &c);
	UDR = c;
}
