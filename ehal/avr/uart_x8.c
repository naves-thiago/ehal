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

volatile u08 *uart_tx;
volatile u08 uart_txsz;

volatile u08 *uart_rx;
volatile u08 uart_rxsz;

void uart_init (u08 id)
{
	uart_mem_block[id]->ucsrc = 3<<UCSZ00;
	uart_mem_block[id]->ucsra = (1<<U2X0);
	uart_mem_block[id]->ucsrb = (1<<RXEN0)
		| (1<<TXEN0)
		| (1<<TXCIE0)
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

u32 uart_get_baud (u08 id, u32 fcpu)
{
	return 0;
}

void uart_send (u08 id, u08 *buff, u08 sz)
{
	uart_tx = buff;
	uart_txsz = sz;
	uart_mem_block[id]->udr = *buff;
}

void uart_recv (u08 id, u08 *buff, u08 sz)
{
	uart_rx = buff;
	uart_rxsz = sz;
}

u08 uart_txdone (u08 id)
{
	return uart_txsz == 0;
}

u08 uart_rxdone (u08 id)
{
	return uart_rxsz == 0;
}

ISR(USART0_RX_vect)
{
	if (!uart_rxdone (0)){
		uart_rxsz--;
		*(uart_rx++) = UDR0;
	}
}

ISR(USART0_TX_vect)
{
	uart_tx++;
	if( uart_txsz-- )
		UDR0 = *uart_tx;
}
