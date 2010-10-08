#ifndef __UART_H_
#define __UART_H_

#include "types.h"
#include "queue.h"

enum uart_baud_rate {
	B0,	B50,	B75,	B110,	B134,	B150,	B300,	B600,
	B1200,	B1800,	B2400,	B4800,	B9600,	B19200,	B38400,	B115200,
};

struct uart;

void	uart_init	(u08 id);
u08	uart_validate	(u08 id);

void	uart_set_baud	(u08 id, u08 baud, u32 fcpu);
u32	uart_get_baud	(u08 id, u32 fcpu);
void	uart_set_nbits	(u08 id, u08); /* default of init is 8. */
u08	uart_get_nbits	(u08 id);

void	uart_send	(u08 id, u08 *buff, u08 sz);
void	uart_recv	(u08 id, u08 *buff, u08 sz);

u08	uart_txdone	(u08 id);
u08	uart_rxdone	(u08 id);

#endif
