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

#elif defined (ehal_atmega48) \
	|| defined (ehal_atmega88) \
	|| defined (ehal_atmega168) \
	|| defined (ehal_atmega328)
#else
#endif
