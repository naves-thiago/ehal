#ifndef PORT_SPECIFIC_H
#define PORT_SPECIFIC_H

#include <io.h>
#include "tinytypes.h"

/* Mapping of Port with port_ functions index.
 * The letters must be upper case. */
struct port_mem_block {
	volatile u08 in;	/* input */
	volatile u08 out;	/* output */
	volatile u08 dir;	/* direction */
	volatile u08 ifg;	/* interrupt flag */
	volatile u08 ies;	/* edge select */
	volatile u08 ie;	/* interrupt enable */
	volatile u08 sel;	/* selection */
	volatile u08 ren;	/* resistor */
};

typedef u08 port_t;

#if defined (ehal_msp430x2012)
#define NUM_PORTS 2
#endif

#endif
