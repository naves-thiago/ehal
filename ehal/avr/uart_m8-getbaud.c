#include <avr/io.h>
#include <avr/interrupt.h>
#include "queue.h"
#include "uart.h"

u32 uart_getbaud (void *unused)
{
	return F_CPU/((UBRRL+(UBRRH << 8)+1)*8);
}
