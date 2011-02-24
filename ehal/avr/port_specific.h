#ifndef PORT_SPECIFIC_H
#define PORT_SPECIFIC_H

#include <avr/io.h>
#include "tinytypes.h"

/* Mapping of Port with port_ functions index.
 * The letters must be upper case. */
struct port_mem_block {
	volatile uint8_t read;	/* PINx */
	volatile uint8_t dir;	/* DDRx */
	volatile uint8_t write;	/* PORTx */
};

typedef u08 port_t;

#endif
