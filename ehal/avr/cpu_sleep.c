#include "cpu.h"
#include <avr/interrupt.h>
#include <avr/sleep.h>

static void cpu_iddle (void)
{
	cli ();
	set_sleep_mode(SLEEP_MODE_IDLE);
	sleep_enable();
	sei();

	sleep_cpu();
	sleep_disable();
}
