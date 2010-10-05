#ifndef __CONFIG_H_
#define __CONFIG_H_

#include <avr/io.h>
#include "types.h"

#if defined (__AVR_ATtiny25__)	\
	|| (__AVR_ATtiny45__)	\
	|| (__AVR_ATtiny85__)
#define PORT_NUM 1
#define UART_NUM 0

#elif defined (__AVR_ATmega8__)	\
	|| (__AVR_ATmega88__)	\
	|| (__AVR_ATmega168__)	\
	|| (__AVR_ATmega328__)
#define PORT_NUM 4
#define UART_NUM 1

#elif defined (__AVR_ATmega16__)\
	|| (__AVR_ATmega32__)
#define PORT_NUM 4
#define UART_NUM 1

#elif defined (__AVR_ATmega164P__)
#define PORT_NUM 4
#define UART_NUM 2

#elif defined (_AVR_IOM128_H_)
#define PORT_NUM 7

#endif

struct spi_mem_block {
	volatile u08 dummy;
};

/* defined in config.c */
extern struct port_mem_block *port_mem_block[];
extern struct uart_mem_block *uart_mem_block[];

#endif	/* __CONFIG_H_ */
