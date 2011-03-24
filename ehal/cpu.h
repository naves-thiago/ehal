/** @file
 * @defgroup cpu cpu
 * @{
 */
#ifndef EHAL_CPU_H
#define EHAL_CPU_H
/* cpu_specific should contain:
 * (8 bits example)
 *
 * #define	CPU_SIZE	8
 * typedef uint8_t	cpu_t;
 *
 * (16 bits example)
 *
 * #define	CPU_SIZE	16
 * typedef uint16_t	cpu_t;
 *
 * (32 bits example)
 *
 * #define	CPU_SIZE	32
 * typedef uint32_t	cpu_t;
 */

#ifdef EHAL_GLOBAL
#include "ehal_global.h"
#endif

#include "tinytypes.h"
#include "cpu_specific.h"

#ifndef CPU_SIZE
#define CPU_SIZE <defined at cpu_specific.h>
/** Number of bits of the processor word. */
#error Undefined CPU_SIZE (at cpu_specific.h)
#endif

enum sleep_mode { sleep_mode_none, sleep_mode_iddle };

/** Put the CPU into a init state, configure PLL and remaping the IO pins */
void	cpu_init (void);

/** Global Interrupts Enable. Use it to leave critical areas of code. */
void	cpu_gie	(void);

/** Global Interrupts Disable. Use it to enter critical areas of code. */
void	cpu_gid	(void);

void	cpu_sleep (enum sleep_mode);

#endif
/** @} */
