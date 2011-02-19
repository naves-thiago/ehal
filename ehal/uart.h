/**
 * @file
 * @defgroup uart uart
 * @{
 * @example uartex.c
 */

#ifndef EHAL_UART
#define EHAL_UART

#include <stdio.h>
#include "tinytypes.h"

/** Possible baud rates. */
enum uart_baud_rate {
	B0,	B50,	B75,	B110,	B134,	B150,	B300,	B600,
	B1200,	B1800,	B2400,	B4800,	B9600,	B19200,	B38400,	B115200,
};

void	*uart_init (int id);
void	*uart_get_from_id (int id);

void	uart_setbaud (void *u, u08 baud);
u32	uart_getbaud (void *u);

void	uart_setnbits (void *u, u08 n);
u08	uart_getnbits (void *u);

void	uart_setstopbits(void *u, u08 stopbits);
u08	uart_getstopbits (void *u);

int	uart_putc (void *u, char c);
int	uart_getc (void *u);

#endif

/** @} */
