/**
 * @file
 * @defgroup spis spis
 * @{
 * @example spis.c
 */

#ifndef EHAL_SPIS_H
#define EHAL_SPIS_H

#ifdef EHAL_GLOBAL
#include "ehal_global.h"
#endif

#include <stdio.h>
#include "spis_specific.h"
#include "tinytypes.h"

#ifndef NSPI
/** Maximum number of spiss. */
#define NSPI <defined in spis_specific.h>
#error Undefined number of spiss
#endif

#ifndef NSPI
/** Number of spiss present on platform */
#define NSPI <defined in spis_specific.h>
#error undefined NSPI
#endif

/** Initializes and returns a hdl from an id.
 * Puts the spis into the default state.
 *
 * @param id - index of spis from 0 to @ref NSPI.
 * @return spis handler.
 ******************************************************************************/
void	*spis_init (int id);

/** write an array into the spis.
 * @param id - index of spis from 0 to @ref NSPI.
 * @param ptr - Pointer with data.
 * @param sz - number of bytes to write.
 * @return Actual number of written bytes.
 ******************************************************************************/
int	spis_write (void *id, char *ptr, int sz);

/** Reads sz bytes into ptr.
 * @param id - index of spis from 0 to @ref NSPI.
 * @param ptr - Buffer to write data.
 * @param sz - number of bytes to read.
 * @return Number successfuly readed.
 ******************************************************************************/
int	spis_read (void *id, char *ptr, int sz);

#endif

/** @} */
