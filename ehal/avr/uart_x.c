#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "queue.h"

#define UART_NUM 1

struct uart {
//	struct rwl rwl;
	struct queue tx,rx;
};

struct uart uart[UART_NUM];


u08 uart_isvalid (u08 id)
{
	return id < UART_NUM;
}

void uart_init (u08 id)
{
	UCSRC = 3<<UCSZ0;
	UCSRA = (1<<U2X);
	UCSRB = (1<<RXEN)
		| (1<<TXEN)
		| (1<<TXCIE)
		| (1<<RXCIE);
	uart_setbaud (id, B9600);
	sei ();
}

void uart_inittx (u08 id, u08 *buff, u08 sz)
{
	queue_init (&uart[id].tx, buff, sz);
}

void uart_initrx (u08 id, u08 *buff, u08 sz)
{
	queue_init (&uart[id].rx, buff, sz);
}

#define ENTRY(_baud, _fcpu) B ## _baud:		\
	UBRRH = (_fcpu/(8UL*_baud) - 1) >> 8;	\
	UBRRL = (_fcpu/(8UL*_baud) - 1);

void uart_setbaud (u08 id, u08 baud)
{
	switch(baud){
	case ENTRY(   300, FCPU); break;
	case ENTRY(  1200, FCPU); break;
	case ENTRY(  2400, FCPU); break;
	case ENTRY(  4800, FCPU); break;
	default:
	case ENTRY(  9600, FCPU); break;
	case ENTRY( 19200, FCPU); break;
	case ENTRY(115200, FCPU); break;
	}
}
#undef ENTRY

u32 uart_getbaud (u08 id)
{
	return FCPU/(( UBRRL + (UBRRH << 8) + 1 )*8);
}

u08 uart_txready (u08 id)
{
	return queue_empty (&uart[id].tx)
	       	&& (UCSRA & (1<<UDRE));
}

u08 uart_write (u08 id, void *buff, u08 sz)
{
	u08 i;
	if (sz == 0) return 0;
	if (uart_txready (id)) {
		UDR = *((u08 *)buff);
		buff++;
		sz--;
	}
	for (i=0; i<sz; i++)
		if (queue_enq (&uart[id].tx, ((char *)buff) [i]))
			break;
	return i;
}

u08 uart_read (u08 id, void *buff, u08 sz)
{
	u08 i;
	if (sz == 0) return 0;
	for (i=0; i<sz; i++)
		if (queue_deq (&uart[id].rx, &((u08 *)buff) [i]))
			break;
	return i;
}

ISR(USART_RXC_vect)
{
	unsigned char c = UDR;
	queue_enq (&uart[0].rx, c);
}

ISR(USART_TXC_vect)
{
	unsigned char c;
	if (queue_deq (&uart[0].tx, &c)) return;
	UDR = c;
}
