#ifndef PORT_SPECIFIC_H
#define PORT_SPECIFIC_H

#include <avr/io.h>
#include "tinytypes.h"

typedef u08 port_t;

#if defined (ehal_attiny25)	\
	|| (ehal_attiny45)	\
	|| (ehal_attiny85)
#define NUM_PORTS	1
#elif defined (ehal_atmega8)	\
	|| defined (ehal_atmega48)	\
	|| defined (ehal_atmega88)	\
	|| defined (ehal_atmega168)	\
	|| defined (ehal_atmega328)
#define NUM_PORTS	3
#elif	defined (ehal_atmega168p)
#define NUM_PORTS	3
#elif defined (ehal_atmega16)	\
	|| defined (ehal_atmega32)
#define NUM_PORTS	4
#elif defined (ehal_atmega164p)
#define NUM_PORTS	4
#elif defined (ehal_atmega128)
#define NUM_PORTS	7
#else
#error MCU not defined in ehal/avr/port_init.c
#endif


#endif
