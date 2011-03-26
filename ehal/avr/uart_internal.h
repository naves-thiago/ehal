#include <avr/io.h>

#if defined (ehal_atmega8)
#define RXIE0	RXIE
#define RXEN0	RXEN
#define TXEN0	TXEN
#define TXCIE0	TXCIE
#define RXCIE0	RXCIE

#define UBRR0H	UBRRH
#define UBRR0L	UBRRL
#define UCSR0C	UCSRC
#define UCSR0C	UCSRC
#define UCSZ00	UCSZ0
#define UCSR0A	UCSRA
#define UCSR0B	UCSRB
#define UCSR0C	UCSRC
#define U2X0	U2X
#define UDR0	UDR
#define UDRE0	UDRE

#define USART_TX_vect	USART_TXC_vect
#define USART_RX_vect	USART_RXC_vect

static inline void calcbaud (uint32_t baud)
{
#ifndef U2X_ON
	UBRR0H = ((F_CPU/(8UL*baud)) -1) >> 8;
	UBRR0L = (F_CPU/(8UL*baud)) -1;
#else
	UBRR0H = ((F_CPU/(16UL*baud)) -1) >> 8;
	UBRR0L = (F_CPU/(16UL*baud)) -1;
#endif
}

#elif defined (ehal_atmega48) \
	|| defined (ehal_atmega88) \
	|| defined (ehal_atmega168) \
	|| defined (ehal_atmega328)
static inline void calcbaud (uint32_t baud)
{
#ifndef U2X_ON
	UBRR0H = ((F_CPU/(8UL*baud)) -1) >> 8;
	UBRR0L = (F_CPU/(8UL*baud)) -1;
#else
	UBRR0H = ((F_CPU/(16UL*baud)) -1) >> 8;
	UBRR0L = (F_CPU/(16UL*baud)) -1;
#endif
}

#else
#endif

#ifndef TX_BUFF_SZ
#define TX_BUFF_SZ 0x20
#endif

#ifndef RX_BUFF_SZ
#define RX_BUFF_SZ 0x20
#endif
