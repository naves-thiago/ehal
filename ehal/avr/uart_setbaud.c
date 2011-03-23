#include <avr/io.h>
#include <avr/interrupt.h>
#include "queue.h"
#include "uart.h"
#include "uart_implementation.h"

/* Must be a power of 2 */
#ifndef TX_BUFF
#define TX_BUFF 0x20
#endif

/* Must be a power of 2 */
#ifndef RX_BUFF
#define RX_BUFF 0x20
#endif

#define U2X_OFF

#ifndef U2X_OFF
#define U2X_ON
#endif

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

#define ENTRY(_baud) B ## _baud: calcbaud (_baud)
void uart_setbaud (void *unused, enum uart_baud_rate baud)
{
	switch(baud){
	case ENTRY(  1200); break;
	case ENTRY(  2400); break;
	case ENTRY(  4800); break;
	default: break;
	case ENTRY(  9600); break;
	case ENTRY( 19200); break;
	case ENTRY( 38400); break;
	case ENTRY(115200); break;
	}
}
#undef ENTRY
