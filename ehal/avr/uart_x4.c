#include <avr/io.h>
#include <avr/interrupt.h>
#include "config.h"
#include "uart.h"
#include "queue.h"

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

struct queue tx[UART_NUM];
u08 tx_buff[UART_NUM][0x0F];

struct queue rx[UART_NUM];
u08 rx_buff[UART_NUM][0x0F];

void uart_init (u08 id)
{
	queue_init (&tx[id], tx_buff[id], sizeof (tx_buff[0]));
	queue_init (&rx[id], rx_buff[id], sizeof (rx_buff[0]));

	uart_mem_block[id]->ucsrc = 3<<UCSZ00;
	uart_mem_block[id]->ucsra = (1<<U2X0);
	uart_mem_block[id]->ucsrb = (1<<RXEN0)
		| (1<<TXEN0)
		| (1<<TXCIE0)
		| (1<<RXCIE0);
}

#define ENTRY(_baud, _fcpu) B ## _baud:	\
	uart_mem_block[id]->ubrr = _fcpu/(8UL*_baud) - 1

void uart_setbaud (u08 id, u08 baud, u32 fcpu)
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

/* dummy function. Probably on other 8bits too. */
u32 uart_getbaud (u08 id, u32 fcpu)
{
	return 0;
}

static u08 uart_txready (u08 id)
{
	return queue_empty (&tx[id])
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
		if (queue_enq (&tx[id], ((char *)buff) [i]))
			break;
	return i;
}

u08 uart_read (u08 id, void *buff, u08 sz)
{
	u08 i;
	if (sz == 0) return 0;
	for (i=0; i<sz; i++)
		if (queue_deq (&rx[id], &(((char *)buff) [i])))
			break;
	return i;
}

ISR(USART0_RX_vect)
{
	unsigned char c = uart_mem_block[0]->udr;
	queue_enq (&rx[0], c);
}

ISR(USART0_TX_vect)
{
	unsigned char c;
	if (queue_deq (&tx[0], &c)) return;
	uart_mem_block[0]->udr = c;
}

ISR(USART1_RX_vect)
{
	unsigned char c = uart_mem_block[1]->udr;
	queue_enq (&rx[1], c);
}

ISR(USART1_TX_vect)
{
	unsigned char c;
	if (queue_deq (&tx[1], &c)) return;
	uart_mem_block[1]->udr = c;
}
