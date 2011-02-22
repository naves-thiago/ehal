#include <avr/io.h>
#include <avr/interrupt.h>
#include "queue.h"
#include "uart.h"

void *uart_isvalid (int id)
{
	if (id < 1) return (void *)1;
	return (void *)0;
}
