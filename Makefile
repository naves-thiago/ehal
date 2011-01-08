# No output
# OUTPUT = >>/dev/null
# Makefile output
OUTPUT =

CP=cp
AVR_INCLUDE_INSTALL=$(which avr-gcc)
AVR_INSTALL_LIB_DIR=$(shell dirname $(shell which avr-gcc))/../avr/lib/

.PHONY: all doc clean avr

all: avr lpc21xx
	@echo
	@echo done!

clean: avr-clean

############################# AVR #######################################

avr:
	@echo
	@echo building AVRs ...
	# tiny
	make -f Makefile.avr ARCH=avr MCU=attiny25		$(OUTPUT)
	# mega
	make -f Makefile.avr ARCH=avr MCU=atmega164p		$(OUTPUT)
	make -f Makefile.avr ARCH=avr MCU=atmega88		$(OUTPUT)
	make -f Makefile.avr ARCH=avr MCU=atmega168		$(OUTPUT)
	make -f Makefile.avr ARCH=avr MCU=atmega128		$(OUTPUT)
	make -f Makefile.avr ARCH=avr MCU=atmega8		$(OUTPUT)

avr-clean:
	make -f Makefile.avr ARCH=avr MCU=atmega88 clean	$(OUTPUT)
	make -f Makefile.avr ARCH=avr MCU=atmega128 clean	$(OUTPUT)
	make -f Makefile.avr ARCH=avr MCU=attiny25 clean	$(OUTPUT)
	make -f Makefile.avr ARCH=avr MCU=atmega8 clean		$(OUTPUT)

############################ LPC21XX ####################################
# Still unsupported
#
# lpc21xx:
#	@echo
#	@echo building LPC21xx ...
#	make -f Makefile.lpc21xx ARCH=lpc21xx MCU=lpc2101	$(OUTPUT)
