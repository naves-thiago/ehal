/**
 * @file
 * @defgroup uart uart
 * @{
 * @example uartex.c
 */

#ifndef EHAL_UART_H
#define EHAL_UART_H

#ifdef EHAL_GLOBAL
#include "ehal_global.h"
#endif

#include <stdio.h>
#include "tinytypes.h"

/** Possible baud rates. */
enum uart_baud_rate {
	B1200,	B1800,	B2400,	B4800,	B9600,	B19200,	B38400,	B115200,
};

void	*uart_init (int id);
void	*uart_isvalid (int id);

void	uart_setbaud (void *uart, u08 baud);
u32	uart_getbaud (void *uart);

void	uart_setnbits (void *uart, u08 n);
u08	uart_getnbits (void *uart);

void	uart_setstopbits(void *uart, u08 stopbits);
u08	uart_getstopbits (void *uart);

int	uart_write (void *uart, unsigned char *ptr, int sz);
int	uart_read (void *uart, unsigned char *ptr, int sz);
int	uart_putc (void *uart, char c);
int	uart_getc (void *uart);

#endif

/** @} */
