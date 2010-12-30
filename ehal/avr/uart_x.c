#include <avr/io.h>
#include <avr/interrupt.h>
#include <ctype.h>
#include "cpu.h"
#include "uart.h"
#include "queue.h"

#ifdef EHAL_GLOBAL
#include "global.h"
#endif

#define UART_NUM	1

struct uart {
//	struct rwl rwl;
	struct queue *tx,*rx;
#ifdef UART_ONRX_CB
	void (*rx_cb)(void);
	u08 rx_n;
#endif
#ifdef UART_ONCNTRL_CB
	void (*cntrl_cb)(void);
#endif
#ifdef UART_ONTX_CB
	void (*tx_cb)(void);
	u08 tx_n;
#endif
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
	uart_setbaud (0, B9600);
	sei ();
}

#ifdef UART_ONRX_CB
void uart_onrx_cb (u08 id, void (*rx_cb)(void), u08 n)
{
	uart[0].rx_cb = rx_cb;
	uart[0].rx_n = n;
}
#endif

#ifdef UART_ONCNTRL_CB
void uart_oncntrl_cb (u08 id, void (*cntrl_cb)(void))
{
	uart[0].cntrl_cb = cntrl_cb;
}
#endif

#ifdef UART_ONTX_CB
void uart_ontx_cb (u08 id, void (*tx_cb)(void))
{
	uart[0].tx_cb = tx_cb;
	uart[0].tx_n = n;
}
#endif

void uart_settxqueue (u08 id, struct queue *q)
{
	uart[0].tx = q;
}

struct queue *uart_gettxqueue (u08 id)
{
	return uart[0].tx;
}

void uart_setrxqueue (u08 id, struct queue *q)
{
	uart[0].rx = q;
}

struct queue *uart_getrxqueue (u08 id)
{
	return uart[0].rx;
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
 * optimized to execute only once before the while loop like the
 * one below.
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
	if (!uart_txready (0)) return;
	if (!queue_deq (uart[0].tx, &c))
		UDR = c;
}

ISR(USART_RXC_vect)
{
	unsigned char c = UDR;
	queue_enq (uart[0].rx, c);
#ifdef UART_ONRX_CB
	if (queue_ocupied (uart[0].rx) == uart[0].rx_n && uart[0].rx_cb)
		uart[0].rx_cb();
#endif
#ifdef UART_ONCNTRL_CB
	if (iscntrl (c) && uart[0].cntrl_cb)
		uart[0].cntrl_cb();
#endif
}

ISR(USART_TXC_vect)
{
	unsigned char c;
	if (!queue_deq (uart[0].tx, &c))
		UDR = c;
#ifdef UART_ONTX_CB
	if (queue_ocupied (uart[0].tx) == uart[0].tx_n && uart[0].tx_cb)
		uart[0].tx_cb();
#endif
}
