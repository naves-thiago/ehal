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
 * #define	CPU_TYPE	u08
 *
 * (16 bits example)
 *
 * #define	CPU_SIZE	16
 * #define	CPU_TYPE	u16
 *
 * (32 bits example)
 *
 * #define	CPU_SIZE	32
 * #define	CPU_TYPE	u32
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

#ifndef CPU_TYPE
#define CPU_TYPE <defined at cpu_specific.h>
/** The C type that represents CPU_SIZE */
#error Undefined CPU_TYPE (at cpu_specific.h)
#endif

/** Put the CPU into a init state, configure PLL and remaping the IO pins */
void	cpu_init (void);

/** Global Interrupts Enable. Use it to leave critical areas of code. */
void	cpu_gie	(void);

/** Global Interrupts Disable. Use it to enter critical areas of code. */
void	cpu_gid	(void);

#endif
/** @} */
