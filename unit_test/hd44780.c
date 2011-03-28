#include "ehal/port.h"
#include <util/delay.h>
#include "hd44780.h"

#define BUSY_FLAG	(1<<7)

#define DT_PORT	2
#define RS_PORT	1
#define RW_PORT	1
#define EN_PORT	1

#define DT_MASK 0x0F
#define DT_FDB	0x04

#define RS_PIN	(1<<0)
#define RW_PIN	(1<<1)
#define EN_PIN	(1<<2)

static char disp_buff[HD44780_HEIGHT*HD44780_WIDTH];

static void write_nibble (unsigned char c);
static unsigned char read_nibble (void);

static void *port;
static void *rs;
static void *rw;
static void *en;

void hd44780_init (void)
{
	port = port_init (DT_PORT);
	rs = port_init (RS_PORT);
	rw = port_init (RS_PORT);
	en = port_init (RS_PORT);

	port_setdir (port, DT_MASK << DT_FDB, 0);

	port_setdir (rs, RS_PIN, 0);
	port_setdir (rw, RW_PIN, 0);
	port_setdir (en, EN_PIN, 0);

	/* software reset */
	_delay_ms (15);
	write_nibble (0x03);
	_delay_ms (4);
	write_nibble (0x03);
	_delay_ms (1);
	write_nibble (0x03);
	_delay_ms (1);
	/* we're in 8-bits mode, set it to 4-bits */
	write_nibble (0x02);
	/* busy flag can be checked from now on... */
	hd44780_mode (1, 0);
	hd44780_control (1, 1, 0);
	hd44780_fnset (0, 1, 0);
}

void hd44780_write_buff_char (char c)
{
	static int8_t i;
	if (c == '\n' || c == '\r'){
		if (i >= HD44780_WIDTH) i = 0;
		else i = HD44780_WIDTH;
	} else if (c == '\b'){
		disp_buff[i] = ' ';
		i--;
	} else {
		disp_buff[i] = c;
		i++;
	}
	if (i >= HD44780_WIDTH*HD44780_HEIGHT) i=0;
	if (i < 0) i=HD44780_WIDTH*HD44780_HEIGHT-1;
}

void hd44780_write_buff (void)
{
	uint8_t i;

	hd44780_home ();
	for (i=0; i<HD44780_WIDTH; i++){
		hd44780_write_data (disp_buff[i]);
	}
	hd44780_ddram_adr (HD44780_LINE1);
	for (; i<2*HD44780_WIDTH; i++){
		hd44780_write_data (disp_buff[i]);
	}

}

/* rs is normaly 0, and rw is normaly 0, so no need to change here. */
void hd44780_write_data (unsigned char c)
{
	while (hd44780_read_status() & BUSY_FLAG)
		;
	write_nibble(c >> 4);
	write_nibble(c);
}

void hd44780_write_cmd (unsigned char c)
{
	while (hd44780_read_status () & BUSY_FLAG)
		;
	port_write (rs, RS_PIN, 0);
	write_nibble(c >> 4);
	write_nibble(c);
	port_write (rs, RS_PIN, RS_PIN);
}

unsigned char hd44780_read_data (void)
{
	unsigned char readed;
	while (hd44780_read_status() & BUSY_FLAG)
		;
	port_write (rs, RS_PIN, RS_PIN);
	port_write (rw, RW_PIN, 0);

	port_setdir (port, DT_MASK << DT_FDB, DT_MASK << DT_FDB);
	readed = (read_nibble() << 4) | (read_nibble() << 0x0F);

	port_write (rw, RW_PIN, RW_PIN);
	port_write (rs, RS_PIN, RS_PIN);
	port_setdir (port, DT_MASK << DT_FDB, 0);
	return readed;
}

unsigned char hd44780_read_status ()
{
	unsigned char readed;
	port_write (rw, RW_PIN, RW_PIN);
	port_write (rs, RS_PIN, 0);

	port_setdir (port, DT_MASK << DT_FDB, DT_MASK << DT_FDB);
	readed = (read_nibble() << 4) | (read_nibble() << 0x0F);

	port_write (rw, RW_PIN, 0);
	port_write (rs, RS_PIN, RS_PIN);
	port_setdir (port, DT_MASK << DT_FDB, 0);
	return readed;
}

static void write_nibble (unsigned char c)
{
	port_write (en, EN_PIN, EN_PIN);
	port_write (port, DT_MASK << DT_FDB, c << DT_FDB);
	port_write (en, EN_PIN, 0);
}

static unsigned char read_nibble (void)
{
	unsigned char c;
	port_write (en, EN_PIN, EN_PIN);
	c = (port_read (port) >> DT_FDB) & DT_MASK;
	port_write (en, EN_PIN, 0);
	return c;
}
