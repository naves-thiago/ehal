/* example of a hd44780U low level driver using the port and pin modules.
 * TODO: remove <util/delay.h> & _delay_ms(1) */
#include "ehal/port.h"
#include "ehal/pin.h"
#include "hd44780.h"
#include <util/delay.h>

/* we can do a runtime mapping of the display with this. */
static port_t port = 0;
static port_t mask = 0x0F;
static port_t fdb = 0x00;	/* first data bit */
static struct pin_t rs = {0, 4};
static struct pin_t rw = {0, 5};
static struct pin_t en = {0, 6};

/* standart location. */
void hd44780h_init_hw (void)
{
	port_set_dir (en.port, (1<<en.pin), 0);
	port_set_dir (rs.port, (1<<rs.pin), 0);
	port_set_dir (rw.port, (1<<rw.pin), 0);
	port_set_dir (port, mask << fdb, 0);
}

void delay_1ms (void)
{
	_delay_ms(1);
}

void hd44780h_dir_nibble (unsigned char in)
{
	if (in){
		port_set_dir (port, mask << fdb, mask << fdb);
	}else{
		port_set_dir (port, mask << fdb, 0);
	}
}

void hd44780h_set_nibble (unsigned char data)
{
	port_write (port, mask << fdb, data << fdb);
}

unsigned char hd44780h_get_nibble (void)
{
	port_t read = port_read (port);
	return (read >> fdb) & mask;
}

void hd44780h_en (unsigned char set)
{	
	pin_set_val (en, set);
}

void hd44780h_rs (unsigned char set)
{
	pin_set_val (rs, set);
}

void hd44780h_rw (unsigned char set)
{
	pin_set_val (rw, set);
}
