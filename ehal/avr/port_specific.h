#ifndef PORT_SPECIFIC_H
#define PORT_SPECIFIC_H

#include <avr/io.h>
#include "tinytypes.h"

typedef u08 port_t;

#if defined (ehal_attiny25)	\
	|| (ehal_attiny45)	\
	|| (ehal_attiny85)

#define NPORT	1
#elif defined (ehal_atmega8)	\
	|| defined (ehal_atmega48)	\
	|| defined (ehal_atmega88)	\
	|| defined (ehal_atmega168)	\
	|| defined (ehal_atmega328)

#define NPORT	3
#elif	defined (ehal_atmega168p)

#define NPORT	3
#elif defined (ehal_atmega16)	\
	|| defined (ehal_atmega32)

#define NPORT	4
#elif defined (ehal_atmega164p)

#define NPORT	4
#elif defined (ehal_atmega128)

#define NPORT	7
#endif


#endif
