#ifndef UART_INTERNAL_H
#define UART_INTERNAL_H

#ifdef EHAL_GLOBAL
#include "ehal_global.h"
#endif

#include <avr/io.h>
#include "uart.h"
#include "uart_specific.h"

#ifndef UART_TX_BUFF_SZ
#define UART_TX_BUFF_SZ 0x10
#endif

#ifndef UART_RX_BUFF_SZ
#define UART_RX_BUFF_SZ 0x10
#endif

struct uart_mem_block {
	volatile uint8_t ucsra;			/* control */
	volatile uint8_t ucsrb;			/* control */
	volatile uint8_t ucsrc;			/* control */
	volatile uint8_t _pad;
	volatile uint8_t ubrrl;
	volatile uint8_t ubrrh;
	volatile uint8_t udr;			/* data */
};

struct uart_dev {
	struct uart_mem_block *u;
	uint8_t readed;
	uint8_t rx_head;
	uint8_t rx_tail;
	char rx_buff[UART_RX_BUFF_SZ];

	uint8_t written;
	uint8_t tx_head;
	uint8_t tx_tail;
	char tx_buff[UART_TX_BUFF_SZ];
};

static inline void calcbaud (struct uart_mem_block *u, uint32_t baud)
{
#ifndef USX_OFF
	u->ubrrh = ((F_CPU/(8UL*baud)) -1) >> 8;
	u->ubrrl = (F_CPU/(8UL*baud)) -1;
#else
	u->ubrrh = ((F_CPU/(16UL*baud)) -1) >> 8;
	u->ubrrl = (F_CPU/(16UL*baud)) -1;
#endif
}

#endif
