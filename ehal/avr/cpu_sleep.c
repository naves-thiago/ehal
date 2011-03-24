#include "cpu.h"
#include <avr/interrupt.h>
#include <avr/sleep.h>

void cpu_sleep (enum sleep_mode sleep)
{
	if (sleep == sleep_mode_iddle){
		cli ();
		set_sleep_mode(SLEEP_MODE_IDLE);
		sleep_enable();
		sei();

		sleep_cpu();
		sleep_disable();
	}
}
