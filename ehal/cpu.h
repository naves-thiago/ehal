/** @file
 * @defgroup cpu cpu
 * @{
 */
#ifndef EHAL_CPU
#define EHAL_CPU
/* cpu_specific should contain:
 * (8 bits example)
 *
 * #define	CPU_SIZE	8
 * #define	CPU_TYPE	unsigned char
 * #define	CPU_FREQ	8000000L
 */
#include "tinytypes.h"
#include "cpu_specific.h"

/* TODO complete description */
void	cpu_global_int_en	(void);
void	cpu_global_int_dis	(void);

/** Save the CPU state on the stack, for context switching. */
void	cpu_context_save	(void);
void	cpu_context_load	(void);
void	cpu_set_sp		(void *sp);
void *	cpu_get_sp		(void);

#endif
/** @} */
