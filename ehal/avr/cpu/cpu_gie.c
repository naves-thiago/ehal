#include <avr/io.h>
#include <avr/interrupt.h>

void cpu_gie (void)
{
	sei ();
}
