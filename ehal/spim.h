/** @file */
#ifndef __SPIM_H_
#define __SPIM_H_

#include "types.h"
#include "spim_specific.h"
#include "queue.h"

extern void	spim_init		(u08 id);
extern u08	spim_cfg_freq		(u08 id, u32 f);
extern u08	spim_cfg_cpufreq	(u08 id, u32 f);

extern void	spimi_xmit		(u08 id, spi_t *buff, u08 size);
extern void	spimi_set_callback	(u08 id, void (*fn)(void *buff));

/* methods form queue itself. they will operate on the spim->queue */

#endif
