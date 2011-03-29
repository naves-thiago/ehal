#ifndef UART_INTERNAL_H
#define UART_INTERNAL_H

#ifdef EHAL_GLOBAL
#include "ehal_global.h"
#endif

#include <avr/io.h>

/* Atmega8 implementation is the same as 48, 88, 168, 328, just need the
 * redefinition of the register names. */
#if defined (ehal_atmega8)
#define RXIE0	RXIE
#define RXEN0	RXEN
#define TXEN0	TXEN
#define TXCIE0	TXCIE
#define RXCIE0	RXCIE

#define UBRR0H	UBRRH
#define UBRR0L	UBRRL
#define UCSR0C	UCSRC
#define UCSR0C	UCSRC
#define UCSZ00	UCSZ0
#define UCSR0A	UCSRA
#define UCSR0B	UCSRB
#define UCSR0C	UCSRC
#define U2X0	U2X
#define UDR0	UDR
#define UDRE0	UDRE

#define USART_TX_vect	USART_TXC_vect
#define USART_RX_vect	USART_RXC_vect
#endif

#if defined (ehal_atmega8) \
	|| defined (ehal_atmega48) \
	|| defined (ehal_atmega88) \
	|| defined (ehal_atmega168) \
	|| defined (ehal_atmega328)
static inline void calcbaud (uint32_t baud)
{
#ifndef U2X_ON
	UBRR0H = ((F_CPU/(8UL*baud)) -1) >> 8;
	UBRR0L = (F_CPU/(8UL*baud)) -1;
#else
	UBRR0H = ((F_CPU/(16UL*baud)) -1) >> 8;
	UBRR0L = (F_CPU/(16UL*baud)) -1;
#endif
}
#endif

#ifndef UART_TX_BUFF_SZ
#define UART_TX_BUFF_SZ 0x20
#endif

#ifndef UART_RX_BUFF_SZ
#define UART_RX_BUFF_SZ 0x20
#endif

extern char uart_tx_buff[UART_TX_BUFF_SZ];
extern int uart_tx_head;
extern int uart_tx_tail;

extern char uart_rx_buff[UART_RX_BUFF_SZ];
extern int uart_rx_head;
extern int uart_rx_tail;

#endif
