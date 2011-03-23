#ifndef PORT_IMPLEMENTATION_H
#define PORT_IMPLEMENTATION_H

#include <io.h>
#include "tinytypes.h"

#define port_mask(p, m, v) do { (p) = ((p) & ~(m)) | ((v) & (m)); } while(0)

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

#endif
