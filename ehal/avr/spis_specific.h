#ifndef SPIS_SPECIFIC_H
#define SPIS_SPECIFIC_H

#include <avr/io.h>
#include "tinytypes.h"

typedef u08 port_t;

#if defined (attiny25)	\
	|| (attiny45)	\
	|| (attiny85)

#define NSPIS	0
#elif defined (atmega8)	\
	|| defined (atmega48)	\
	|| defined (atmega88)	\
	|| defined (atmega168)	\
	|| defined (atmega328)

#define NSPIS	1
#endif


#endif
