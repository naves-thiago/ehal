#include <avr/io.h>
#include <avr/interrupt.h>
#include "config.h"
#include "uart.h"

struct uart_mem_block {
	volatile u08 ucsra;
	volatile u08 ucsrb;
	volatile u08 ucsrc;
	volatile u08 ubrrl;
	volatile u08 ubrrh;
	volatile u08 udr;
};

#define UART(n)	(struct uart_mem_block *)&UCSR ## n ## A
struct uart_mem_block *uart_mem_block[] = {
	UART(0),
	UART(1),
};

struct uart {
	struct queue tx;
	struct queue rx;
	uart_fn on_txempty;
	uart_fn on_rxfull;
	uart_fn on_foundchar;
};

struct queue tx[2];
struct queue rx[2];

uart_fn on_txempty[2];
uart_fn on_rxfull[2];

void uart_set_on_rxfull (u08 id, uart_fn f)
{
	on_rxfull[id] = f;
}

void uart_init (u08 id)
{
	uart_mem_block[id]->ucsrc = 3<<UCSZ00;
	uart_mem_block[id]->ucsra = (1<<U2X0);
	uart_mem_block[id]->ucsrb = (1<<RXEN0)
		| (1<<TXEN0)
		| (1<<RXCIE0);
}

#define ENTRY(_baud, _fcpu) B ## _baud:		\
	ubrr = _fcpu/(8UL*_baud) - 1;		\
	uart_mem_block[id]->ubrrl = ubrr >> 8;	\
	uart_mem_block[id]->ubrrh = ubrr
void uart_set_baud (u08 id, u08 baud, u32 fcpu)
{
	u32 ubrr;
	switch(baud){
	case ENTRY(   300, fcpu); break;
	case ENTRY(  1200, fcpu); break;
	case ENTRY(  2400, fcpu); break;
	case ENTRY(  4800, fcpu); break;
	default:
	case ENTRY(  9600, fcpu); break;
	case ENTRY( 19200, fcpu); break;
	case ENTRY(115200, fcpu); break;
	}
}
#undef ENTRY

struct queue *uart_gettx (u08 id)
{
	return &tx[id];
}

struct queue *uart_getrx (u08 id)
{
	return &rx[id];
}

void uart_set_rxbuff (u08 id, u08 *buff, u08 sz)
{
	queue_init (uart_getrx (id), buff, sz);
}

void uart_set_txbuff (u08 id, u08 *buff, u08 sz)
{
	queue_init (uart_gettx (id), buff, sz);
}

ISR(USART0_RX_vect)
{
	queue_enq (&rx[0], UDR0);
	if (queue_full (&rx[0]) && on_rxfull[0])
		on_rxfull[0] (&rx[0]);
}

ISR(USART0_TX_vect)
{
	u08 v;
	if (!queue_deq (&tx[0], &v)){
		UDR0 = v;
	}
}

ISR(USART1_RX_vect)
{
	queue_enq (&rx[1], UDR1);
	if (queue_full (&rx[1]) && on_rxfull[1])
		on_rxfull[1] (&rx[1]);
}

ISR(USART1_TX_vect)
{
	u08 v;
	if (!queue_deq (&tx[0], &v)){
		UDR1 = v;
	}
}

void uart_send(u08 id)
{
	u08 v;
	queue_deq (&tx[id], &v);
	uart_mem_block[id]->udr = v;
}
