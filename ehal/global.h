/* Global configurations
 * + To use them add -DEHAL_GLOBAL to CFLAGS in the Makefile and recompile.
 * + This file is intended to pass configurations to every module.
 * + Every .h from modules shal have in its begining a:
 *
 * #ifdef EHAL_GLOBAL
 * #include "global.h"
 * #endif
 *
 * And The default configurations in the module must be surrounded by:
 *
 * #ifndef CONF_XYZ
 * #define CONF_XYZ default
 * #endif
 *
 * This file can be overwriten by an automatic generator if needed.
 * something like a gui tool in the future.
 *
 */
#ifndef EHAL_GLOBAL_H
#define EHAL_GLOBAL_H

/*******************************************************************************
 * AVR OPTIONS
 ******************************************************************************/
/* Option to turn of the x2 feature of avr uart. */
// #define U2X_OFF

/* Option to turn off an uart */
// #define USART0_OFF
// #define USART1_OFF
// ...


#endif
