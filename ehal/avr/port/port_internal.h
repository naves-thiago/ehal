#ifndef PORT_INTERNAL_H
#define PORT_INTERNAL_H

#include <avr/io.h>
#include "tinytypes.h"
#include "port.h"

#define port_mask(p, m, v) do { p = ((p) & ~(m)) | ((v) & (m)); } while(0)

/* Mapping of Port with port_ functions index.
 * The letters must be upper case. */
struct port_mem_block {
	volatile uint8_t read;	/* PINx */
	volatile uint8_t dir;	/* DDRx */
	volatile uint8_t write;	/* PORTx */
};

#endif
