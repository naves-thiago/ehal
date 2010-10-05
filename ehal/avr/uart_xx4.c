#include <avr/io.h>
#include "config.h"
#include "uart.h"

#define SET_UBRR(baud, fcpu)	(fcpu/(16*baud
#define UART(n)	(struct uart_mem_block *)&UCSR ## n ## A

struct uart_mem_block {
	volatile u08 ucsra;
	volatile u08 ucsrb;
	volatile u08 ucsrc;
	volatile u08 ubrrl;
	volatile u08 ubrrh;
	volatile u08 udr;
};

struct uart_mem_block *uart_mem_block[] = {
	UART(0),
	UART(1),
};

static struct queue tx[UART_NUM];
static struct queue rx[UART_NUM];

#define ENTRY(baud) B ## baud:	\
	ubrr = fcpu/(8UL*baud) - 1;		\
	uart_mem_block[id]->ubrrl = ubrr >> 8;	\
	uart_mem_block[id]->ubrrh = ubrr

void uart_init (u08 id, u08 baud, u32 fcpu)
{
	u32 ubrr;
	uart_mem_block[id]->ucsra = (1<<U2X0);
	uart_mem_block[id]->ucsrb = (1<<RXEN0) | (1<<TXEN0);
	uart_mem_block[id]->ucsrc = 3<<UCSZ00;

	switch(baud){
	case ENTRY(   300); break;
	case ENTRY(  1200); break;
	case ENTRY(  2400); break;
	case ENTRY(  4800); break;
	default:
	case ENTRY(  9600); break;
	case ENTRY( 19200); break;
	case ENTRY(115200); break;
	}
}

struct queue *uart_gettx (u08 id)
{
	return &tx[id];
}

struct queue *uart_getrx (u08 id)
{
	return &rx[id];
}

