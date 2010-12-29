#include <avr/io.h>
#include <avr/interrupt.h>
#include "cpu.h"
#include "uart.h"
#include "queue.h"

#define UART_NUM	1

struct uart {
//	struct rwl rwl;
	struct queue *tx,*rx;
};

static struct uart uart[UART_NUM];


u08 uart_isvalid (u08 id)
{
	return id < UART_NUM;
}

void uart_init (u08 id)
{
	UCSRC = 3<<UCSZ0;
	UCSRA |= (1<<U2X);
	UCSRB = (1<<RXEN)
		| (1<<TXEN)
		| (1<<TXCIE)
		| (1<<RXCIE);
	uart_setbaud (id, B9600);
	sei ();
}

void uart_settxqueue (u08 id, struct queue *q)
{
	uart[id].tx = q;
}

struct queue *uart_gettxqueue (u08 id)
{
	return uart[id].tx;
}

void uart_setrxqueue (u08 id, struct queue *q)
{
	uart[id].rx = q;
}

struct queue *uart_getrxqueue (u08 id)
{
	return uart[id].rx;
}

#define ENTRY(_baud, _fcpu) B ## _baud:		\
	UBRRH = (_fcpu/(8UL*_baud) - 1) >> 8;	\
	UBRRL = (_fcpu/(8UL*_baud) - 1);
void uart_setbaud (u08 id, u08 baud)
{
	switch(baud){
	case ENTRY(   300, CPU_FREQ); break;
	case ENTRY(  1200, CPU_FREQ); break;
	case ENTRY(  2400, CPU_FREQ); break;
	case ENTRY(  4800, CPU_FREQ); break;
	default:
	case ENTRY(  9600, CPU_FREQ); break;
	case ENTRY( 19200, CPU_FREQ); break;
	case ENTRY(115200, CPU_FREQ); break;
	}
}
#undef ENTRY

u32 uart_getbaud (u08 id)
{
	return CPU_FREQ/((UBRRL+(UBRRH << 8)+1)*8);
}

u08 uart_txready (u08 id)
{
	return UCSRA & _BV(UDRE);
}

/* The noinline attribute prevents a bug where uart_transmit is
 * optimized to executed only once before the while loop.
 *
 * while (1){
 *	uart_transmit (0);
 * }
 *
 */
void uart_transmit (u08 id) __attribute__((noinline));
void uart_transmit (u08 id)
{
	unsigned char c;
	if (!uart_txready (id)) return;
	if (!queue_deq (uart[0].tx, &c))
		UDR = c;
}

ISR(USART_RXC_vect)
{
	unsigned char c = UDR;
	queue_enq (uart[0].rx, c);
}

ISR(USART_TXC_vect)
{
	unsigned char c;
	if (!queue_deq (uart[0].tx, &c))
		UDR = c;
}
