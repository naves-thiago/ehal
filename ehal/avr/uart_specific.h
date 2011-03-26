#ifndef UART_SPECIFIC_H
#define UART_SPECIFIC_H

#if defined (ehal_attiny25)	\
	|| (ehal_attiny45)	\
	|| (ehal_attiny85)

#define NUM_UARTS	0
#elif defined (ehal_atmega8)	\
	|| defined (ehal_atmega48)	\
	|| defined (ehal_atmega88)	\
	|| defined (ehal_atmega168)	\
	|| defined (ehal_atmega328)

#define NUM_UARTS	1
/*
#elif	defined (ehal_atmega168p)

#define NUM_UARTS	0
#elif defined (ehal_atmega16)	\
	|| defined (ehal_atmega32)

#define NUM_UARTS	0
#elif defined (ehal_atmega164p)

#define NUM_UARTS	0
#elif defined (ehal_atmega128)

#define NUM_UARTS	0
#else
*/
#error MCU not defined.
#endif

#endif
