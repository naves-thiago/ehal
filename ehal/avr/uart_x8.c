#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"

#define UART_NUM 2

struct uart_mem_block {
	volatile u08 ucsra;
	volatile u08 ucsrb;
	volatile u08 ucsrc;
	volatile u08 pad[1];
	volatile u16 ubrr;
	volatile u08 udr;
};

#define UART(n)	(struct uart_mem_block *)&UCSR ## n ## A
volatile struct uart_mem_block *uart_mem_block[] = {
	UART(0),
	UART(1),
};

u08 *uart_tx[UART_NUM];
u08 uart_txsz[UART_NUM];
u08 uart_txcur[UART_NUM];

u08 *uart_rx[UART_NUM];
u08 uart_rxsz[UART_NUM];
u08 uart_rxcur[UART_NUM];
u08 flags;

/* Array of function pointers. One fp for each uart. */
void (*uart_rxdone_cb[UART_NUM])(u08 *buff, u08 sz);
void (*uart_txdone_cb[UART_NUM])(u08 *buff, u08 sz);
void (*uart_foundc_cb[UART_NUM])(u08 *buff, u08 sz);
char uart_foundc_c[UART_NUM];

void uart_open (u08 id)
{
	uart_mem_block[id]->ucsrc = 3<<UCSZ00;
	uart_mem_block[id]->ucsra = (1<<U2X0);
	uart_mem_block[id]->ucsrb = (1<<RXEN0)
		| (1<<TXEN0)
		| (1<<TXCIE0)
		| (1<<RXCIE0);
}

#define ENTRY(_baud, _fcpu) B ## _baud:	\
	uart_mem_block[id]->ubrr = _fcpu/(8UL*_baud) - 1

void uart_set_baud (u08 id, u08 baud, u32 fcpu)
{
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

/* dummy function. */
u32 uart_get_baud (u08 id, u32 fcpu)
{
	return 0;
}

void uart_write (u08 id, void *buff, u08 sz)
{
	uart_tx[id] = buff;
	uart_txsz[id] = sz;
	uart_mem_block[id]->udr = *((u08 *)buff);
}

void uart_read (u08 id, void *buff, u08 sz)
{
	uart_rx[id] = buff;
	uart_rxsz[id] = sz;
	uart_rxcur[id] = 0;
}

void uart_set_foundc_cb (u08 id, void (*uart_fn)(u08 *buff, u08 sz), char c)
{
	uart_foundc_cb[id] = uart_fn;
	uart_foundc_c[id] = c;
}

u08 uart_txdone (u08 id)
{
	return uart_txsz[id] == uart_txcur[id];
}

u08 uart_rxdone (u08 id)
{
	return uart_rxsz[id] == uart_rxcur[id];
}

ISR(USART0_RX_vect)
{
	if (!uart_rxdone (0)){
		uart_rx[0][uart_rxcur[0]] = uart_mem_block[0]->udr;
		uart_rxcur[0]++;
		if ((uart_rx[0][uart_rxcur[0]-1] == uart_foundc_c[0])
			       && uart_foundc_cb[0]){
			uart_foundc_cb[0] (uart_rx[0], uart_rxcur[0]-1);
		}
	}
	else if (uart_rxdone_cb[0]){
		uart_rxdone_cb[0] (uart_rx[0], uart_rxcur[0]);
	}
}

ISR(USART0_TX_vect)
{
	uart_tx[0]++;
	if( uart_txsz[0]-- )
		UDR0 = *uart_tx[0];
}

ISR(USART1_RX_vect)
{
	if (!uart_rxdone (1)){
		uart_rx[1][uart_rxcur[1]] = uart_mem_block[1]->udr;
		uart_rxcur[1]++;
	}
	else if (uart_rxdone_cb[1]) {
		uart_rxdone_cb[1] (uart_rx[1], uart_rxsz[1]);
	}
}

ISR(USART1_TX_vect)
{
	uart_tx[1]++;
	if( uart_txsz[1]-- )
		uart_mem_block[1]->udr = *uart_tx[1];
}
