#ifndef PORT_SPECIFIC_H
#define PORT_SPECIFIC_H

#include <avr/io.h>
#include "tinytypes.h"

typedef u08 port_t;

#if defined (attiny25)	\
	|| (attiny45)	\
	|| (attiny85)

#define NPORT	1
#elif defined (atmega8)	\
	|| defined (atmega48)	\
	|| defined (atmega88)	\
	|| defined (atmega168)	\
	|| defined (atmega328)

#define NPORT	3
#elif	defined (atmega168p)

#define NPORT	3
#elif defined (atmega16)	\
	|| defined (atmega32)

#define NPORT	4
#elif defined (atmega164p)

#define NPORT	4
#elif defined (atmega128)

#define NPORT	7
#endif


#endif
