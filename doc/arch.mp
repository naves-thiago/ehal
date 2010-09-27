input metauml;

Class.types("types")
(	"+ u08 : unsigned char",
	"+ u16 : unsigned short int",
	"+ u32 : unsigned long int",
	"+ u64 : unsigned long long",
	"+ s08 : signed char",
	"+ u16 : signed short int",
	"+ u32 : signed long int",
	"+ u64 : signed long long",
)
();

beginfig(1);
drawObjects(types);
endfig;

Class.port("port") ()
(	"+ init (id : u08) : void",
	"+ write (id : u08, mask : pio_t, val : pio_t) : void",
	"+ pullup (id : u08, mask : pio_t, val : pio_t) : void",
	"+ read (id : u08) : pio_t",
	"+ set_dir (id : u08, mask : pio_t, val : pio_t) : void",
	"+ get_dir (id : u08) : pio_t",
	"+ validate (id : u08) : bool",
);

Class.pin("pin")
()
(	"+ make_pin (port : u08, pin : u08) : pin_t",
	"+ set_high (id : pin_t) : void",
	"+ set_low (id : pin_t) : void",
	"+ set_in (id : pin_t) : void",
	"+ set_out (id : pio_t) : void",
	"+ set_pullup (id : pin_t) : void",
	"+ set_pullup_off (id : pio_t) : void",
	"+ validate (id : pin_t) : bool",
);

beginfig(2);
leftToRight(45)(port, pin);
drawObjects(port, pin);
endfig;

Class.spim("spim") ()
(	"+ init (id : u08, cpol : u08, cpha : u08) : u08",
	"+ conf_freq (id : u08, freq : u32, cpufreq : u32) : u32",
	"+ xmit (id : u08, value : spi_t) : spi_t",
	"+ validate (id : u08) : bool",
);

Class.spimi("spimi") ()
(	"+ init (id : u08, cpol : u08, cpha : u08) : u08",
	"+ conf_freq (id : u08, freq : u32, cpufreq : u32) : u32",
	"+ validate (id : u08) : bool",
);

Class.twim("twim")()
(	"+ init (id : u08)",
	"+ conf_freq (id : u08, freq : u32, cpufreq : u32) : u32",
	"+ validate (id : u08) : bool",
);

Class.queue("queue")
(	"- *ptr : u08",
	"- sz : u08",
)
(	"+ init (*q : queue, *buff : u08, sz : u08) : enum_queue",
	"+ ocupied (*q : queue) : u08",
	"+ queue_full (*q : queue)",
	"+ queue_empty (*q : queue)",
	"+ queue_peek (*q : queue)",
	"+ queue_enq (*q : queue)",
	"+ queue_deq (*q : queue)",
	"+ queue_full (*q : queue) : queue_enum",
);

Class.usart("usart")
(	"+ tx : queue",
	"+ rx : queue",
)
(	"+ init (id : u08) : u08",
	"+ set_freq (id : u08, freq : u32, cpufreq : u32) : u32",
	"+ send (id : u08, v : u08) : void",
	"+ recv (id : u08, v : u08) : void",
	"+ validate (id : u08) : u08",
);

beginfig(3);
topToBottom(45)(usart, queue);
drawObjects(usart, queue);
clink(aggregationUni) (queue, usart);
endfig;

end
