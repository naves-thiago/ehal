# Makefile output
OUTPUT =
# No output
OUTPUT = >>/dev/null

CP=cp
AVR_INCLUDE_INSTALL=$(which avr-gcc)
AVR_INSTALL_LIB_DIR=$(shell dirname $(shell which avr-gcc))/../avr/lib/

.PHONY: all doc clean avr

all: avr msp430
	@echo
	@echo done!

install: avr-install msp430-install

clean: avr-clean msp430-clean

############################# AVR #######################################
avr-depend:
	make -f Makefile.avr ARCH=avr MCU=atmega8 makedepend
avr:
	@echo
	@echo building AVRs ...
	# tiny
#	make -f Makefile.avr ARCH=avr MCU=attiny25	all	$(OUTPUT)
	# mega
	make -f Makefile.avr ARCH=avr MCU=atmega8 F_CPU=1000000 all $(OUTPUT)
	make -f Makefile.avr ARCH=avr MCU=atmega8 F_CPU=8000000 all $(OUTPUT)
	make -f Makefile.avr ARCH=avr MCU=atmega88 F_CPU=1000000 all $(OUTPUT)
	make -f Makefile.avr ARCH=avr MCU=atmega88 F_CPU=8000000 all $(OUTPUT)
#	make -f Makefile.avr ARCH=avr MCU=atmega164p	all	$(OUTPUT)
#	make -f Makefile.avr ARCH=avr MCU=atmega88	all	$(OUTPUT)
#	make -f Makefile.avr ARCH=avr MCU=atmega168	all	$(OUTPUT)
#	make -f Makefile.avr ARCH=avr MCU=atmega128	all	$(OUTPUT)
avr-install:
	@echo
	@echo installing AVRs ...
	make -f Makefile.avr ARCH=avr MCU=atmega8 F_CPU=1000000 install $(OUTPUT)
	make -f Makefile.avr ARCH=avr MCU=atmega8 F_CPU=8000000 install $(OUTPUT)
	make -f Makefile.avr ARCH=avr MCU=atmega88 F_CPU=1000000 install $(OUTPUT)
	make -f Makefile.avr ARCH=avr MCU=atmega88 F_CPU=8000000 install $(OUTPUT)
#	make -f Makefile.avr ARCH=avr MCU=atmega164p	install	$(OUTPUT)
#	make -f Makefile.avr ARCH=avr MCU=atmega88	install	$(OUTPUT)
#	make -f Makefile.avr ARCH=avr MCU=atmega168	install	$(OUTPUT)
#	make -f Makefile.avr ARCH=avr MCU=atmega128	install	$(OUTPUT)
	
avr-clean:
	@echo
	@echo cleaning AVRs ...
	make -f Makefile.avr ARCH=avr MCU=atmega8 F_CPU=1000000 clean $(OUTPUT)
	make -f Makefile.avr ARCH=avr MCU=atmega8 F_CPU=8000000 clean $(OUTPUT)
	make -f Makefile.avr ARCH=avr MCU=atmega88 F_CPU=1000000 clean $(OUTPUT)
	make -f Makefile.avr ARCH=avr MCU=atmega88 F_CPU=8000000 clean $(OUTPUT)
#	make -f Makefile.avr ARCH=avr MCU=attiny25	clean	$(OUTPUT)
#	make -f Makefile.avr ARCH=avr MCU=atmega164p	clean	$(OUTPUT)
#	make -f Makefile.avr ARCH=avr MCU=atmega88	clean	$(OUTPUT)
#	make -f Makefile.avr ARCH=avr MCU=atmega168	clean	$(OUTPUT)
#	make -f Makefile.avr ARCH=avr MCU=atmega128	clean	$(OUTPUT)

############################ MSP430  ####################################
msp430:
	make -f Makefile.msp430 MCU=msp430x2012 ARCH=msp430 all $(OUTPUT)

msp430-install:
	make -f Makefile.msp430 MCU=msp430x2012 ARCH=msp430 install $(OUTPUT)

msp430-clean:
	make -f Makefile.msp430 MCU=msp430x2012 ARCH=msp430 clean $(OUTPUT)

############################ LPC21XX ####################################
# Still unsupported
#
# lpc21xx:
#	@echo
#	@echo building LPC21xx ...
#	make -f Makefile.lpc21xx ARCH=lpc21xx MCU=lpc2101	$(OUTPUT)
