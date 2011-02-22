#include <avr/io.h>
#include <avr/interrupt.h>
#include "queue.h"
#include "uart.h"

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
	UBRRH = ((F_CPU/(8UL*baud)) -1) >> 8;
	UBRRL = (F_CPU/(8UL*baud)) -1;
#else
	UBRRH = ((F_CPU/(16UL*baud)) -1) >> 8;
	UBRRL = (F_CPU/(16UL*baud)) -1;
#endif
}

#define ENTRY(_baud) B ## _baud: calcbaud (_baud)
void uart_setbaud (void *unused, u08 baud)
{
	switch(baud){
	case ENTRY(  1200); break;
	case ENTRY(  2400); break;
	case ENTRY(  4800); break;
	case ENTRY(  9600); break;
	case ENTRY( 19200); break;
	case ENTRY( 38400); break;
	case ENTRY(115200); break;
	default: break;
	}
}
#undef ENTRY
