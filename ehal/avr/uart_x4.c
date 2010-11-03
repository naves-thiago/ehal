#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "queue.h"

#define UART(n)	(struct uart_mem_block *)&UCSR ## n ## A
#define UART_NUM (sizeof(uart_mem_block)/sizeof(uart_mem_block[0]))

struct uart {
//	struct rwl rwl;
	struct queue tx,rx;
};

struct uart_mem_block {
	volatile u08 ucsra;
	volatile u08 ucsrb;
	volatile u08 ucsrc;
	volatile u08 pad[1];
	volatile u16 ubrr;
	volatile u08 udr;
};

volatile struct uart_mem_block *uart_mem_block[] = {
	UART(0),
	UART(1),
};

struct uart uart[UART_NUM];


u08 uart_isvalid (u08 id)
{
	return id < UART_NUM;
}

void uart_init (u08 id)
{
	uart_mem_block[id]->ucsrc = 3<<UCSZ00;
	uart_mem_block[id]->ucsra = (1<<U2X0);
	uart_mem_block[id]->ucsrb = (1<<RXEN0)
		| (1<<TXEN0)
		| (1<<TXCIE0)
		| (1<<RXCIE0);
	uart_setbaud (id, B9600);
}

void uart_inittx (u08 id, u08 *buff, u08 sz)
{
	queue_init (&uart[id].tx, buff, sz);
}

void uart_initrx (u08 id, u08 *buff, u08 sz)
{
	queue_init (&uart[id].rx, buff, sz);
}

#define ENTRY(_baud, _fcpu) B ## _baud:	\
	uart_mem_block[id]->ubrr = _fcpu/(8UL*_baud) - 1
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
	return FCPU/(( uart_mem_block[id]->ubrr+1 )*8);
}

u08 uart_txready (u08 id)
{
	return queue_empty (&uart[id].tx)
	       	&& (uart_mem_block[id]->ucsra & (1<<UDRE0));
}

u08 uart_write (u08 id, void *buff, u08 sz)
{
	u08 i;
	if (sz == 0) return 0;
	if (uart_txready (id)) {
		uart_mem_block[id]->udr = *((u08 *)buff);
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

ISR(USART0_RX_vect)
{
	unsigned char c = uart_mem_block[0]->udr;
	queue_enq (&uart[0].rx, c);
}

ISR(USART0_TX_vect)
{
	unsigned char c;
	if (queue_deq (&uart[0].tx, &c)) return;
	uart_mem_block[0]->udr = c;
}

ISR(USART1_RX_vect)
{
	unsigned char c = uart_mem_block[1]->udr;
	queue_enq (&uart[1].rx, c);
}

ISR(USART1_TX_vect)
{
	unsigned char c;
	if (queue_deq (&uart[1].tx, &c)) return;
	uart_mem_block[1]->udr = c;
}
