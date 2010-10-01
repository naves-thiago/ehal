/** @file */
#ifndef __SPIM_H_
#define __SPIM_H_

#include "types.h"
#include "spim_specific.h"
#include "queue.h"

extern void	spim_init		(u08 id);
extern u32	spim_cfg_freq		(u08 id, u32 f, u32 fcpu);

extern void	spim_xmit		(u08 id, spi_t *buff, u08 size);
extern void	spim_set_callback	(u08 id, void (*fn)(void *buff));

#endif
