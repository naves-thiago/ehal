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
 * #define	CPU_TYPE	unsigned char
 */

#ifdef EHAL_GLOBAL
#include "ehal_global.h"
#endif

#include "tinytypes.h"
#include "cpu_specific.h"

/** Put the CPU into a init state, configure PLL and remaping the IO pins */
void	cpu_init (void);

/** Global Interrupts Enable. Use it to leave critical areas of code. */
void	cpu_gie	(void);

/** Global Interrupts Disable. Use it to enter critical areas of code. */
void	cpu_gid	(void);

#endif
/** @} */
