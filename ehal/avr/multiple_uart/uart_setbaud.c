#include <avr/io.h>
#include <avr/interrupt.h>
#include "queue.h"
#include "uart.h"
#include "uart_internal.h"

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

#define ENTRY(_u, _baud) B ## _baud: calcbaud (_u, _baud)
void uart_setbaud (void *u, enum uart_baud_rate baud)
{
	switch(baud){
	case ENTRY( u, 1200); break;
	case ENTRY( u, 2400); break;
	case ENTRY( u, 4800); break;
	default: break;
	case ENTRY( u, 9600); break;
	case ENTRY( u, 19200); break;
	case ENTRY( u, 38400); break;
	case ENTRY( u, 115200); break;
	}
}
#undef ENTRY
