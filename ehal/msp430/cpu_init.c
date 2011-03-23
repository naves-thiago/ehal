#include <io.h>

void cpu_init (void)
{
	WDTCTL = WDTPW + WDTHOLD;	// Stop WDT
}
