# Makefile output
OUTPUT =
# No output
OUTPUT = >>/dev/null

CP=cp
AVR_INCLUDE_INSTALL=$(which avr-gcc)
AVR_INSTALL_LIB_DIR=$(shell dirname $(shell which avr-gcc))/../avr/lib/

.PHONY: all doc clean avr

all: avr msp430 lpc17xx
install: avr-install msp430-install lpc17xx-install
clean: avr-clean msp430-clean lpc17xx-clean

############################# AVR #######################################
avr:
	make -f Makefile.avr MCU=atmega8 F_CPU=1000000 all $(OUTPUT)
	make -f Makefile.avr MCU=atmega88 F_CPU=1000000 all $(OUTPUT)
	make -f Makefile.avr MCU=atmega324p F_CPU=1000000 all $(OUTPUT)

avr-install:
	make -f Makefile.avr MCU=atmega8 F_CPU=1000000 install $(OUTPUT)
	make -f Makefile.avr MCU=atmega88 F_CPU=1000000 install $(OUTPUT)
	make -f Makefile.avr MCU=atmega324p F_CPU=1000000 install $(OUTPUT)

avr-clean:
	make -f Makefile.avr MCU=atmega8 F_CPU=1000000 clean $(OUTPUT)
	make -f Makefile.avr MCU=atmega88 F_CPU=1000000 clean $(OUTPUT)
	make -f Makefile.avr MCU=atmega324p F_CPU=1000000 clean $(OUTPUT)

############################ MSP430  ####################################
msp430:
	make -f Makefile.msp430 MCU=msp430x2012 all $(OUTPUT)
	make -f Makefile.msp430 MCU=msp430x2013 all $(OUTPUT)

msp430-install:
	make -f Makefile.msp430 MCU=msp430x2012 install $(OUTPUT)
	make -f Makefile.msp430 MCU=msp430x2013 install $(OUTPUT)

msp430-clean:
	make -f Makefile.msp430 MCU=msp430x2012 clean $(OUTPUT)
	make -f Makefile.msp430 MCU=msp430x2013 clean $(OUTPUT)

############################ LPC17XX ####################################
lpc17xx:
	make -f Makefile.lpc17xx MCU=lpc1768 all $(OUTPUT)

lpc17xx-install:
	make -f Makefile.lpc17xx MCU=lpc1768 install $(OUTPUT)

lpc17xx-clean:
	make -f Makefile.lpc17xx MCU=lpc1768 clean $(OUTPUT)

############################ LPC21XX ####################################
# Still unsupported
#
# lpc21xx:
#	@echo
#	@echo building LPC21xx ...
#	make -f Makefile.lpc21xx MCU=lpc2101	$(OUTPUT)
