#ifndef UART_SPECIFIC_H
#define UART_SPECIFIC_H

#if defined (ehal_attiny25)	\
	|| (ehal_attiny45)	\
	|| (ehal_attiny85)

#define NUART	0
#elif defined (ehal_atmega8)	\
	|| defined (ehal_atmega48)	\
	|| defined (ehal_atmega88)	\
	|| defined (ehal_atmega168)	\
	|| defined (ehal_atmega328)

#define NUART	1
#endif

#endif
