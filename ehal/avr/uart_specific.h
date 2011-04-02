#ifndef UART_SPECIFIC_H
#define UART_SPECIFIC_H

#if defined (attiny25)	\
	|| (attiny45)	\
	|| (attiny85)

#define NUART	0
#elif defined (atmega8)	\
	|| defined (atmega48)	\
	|| defined (atmega88)	\
	|| defined (atmega168)	\
	|| defined (atmega328)

#define NUART	1
#elif defined (atmega324p)	\
	|| defined (atmega164p)
#define NUART	2
#endif

#endif
