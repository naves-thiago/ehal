#ifndef SPIS_SPECIFIC_H
#define SPIS_SPECIFIC_H

#include <avr/io.h>
#include "tinytypes.h"

typedef u08 port_t;

#if defined (ehal_attiny25)	\
	|| (ehal_attiny45)	\
	|| (ehal_attiny85)

#define NSPIS	0
#elif defined (ehal_atmega8)	\
	|| defined (ehal_atmega48)	\
	|| defined (ehal_atmega88)	\
	|| defined (ehal_atmega168)	\
	|| defined (ehal_atmega328)

#define NSPIS	1
#endif


#endif
