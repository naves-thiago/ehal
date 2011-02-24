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

/* PORT */
#define PORT_ONCHANGE	/* one of the masked pins has changed */

/* UART */
#define UART_ONNRX	/* rx queue have n bytes */
#define UART_ONNTX	/* tx queue have n bytes */
#define UART_ONCNTRL	/* rx added a control char into queue */
#define UART_ONGOTC	/* rx just added char c into queue */

#endif
