##############################
# Author: Hu Yugui <yugui.hu@hotmail.com>
# Project for Breshless DC motor
##############################
include ../Makefile.common

SRC_OBJ = startup.o main.o fsmc_sram.o ili9320_api.o ili9320.o \
	lcd_init.o xprintf.o console.o toolbox.o

src: version $(SRC_OBJ)

version:
	@echo "/* Auto generate, don't modify it */" > version.h
	@echo \#define COMPILER \"`$(CC) -v 2>&1 | tail -n 1`\" >> version.h
	@echo \#define COMPILE_BY \"`whoami`\" >> version.h
	@echo \#define COMPILE_HOST \"`hostname`\" >> version.h

$(SRC_OBJ): %.o: %.c
	$(CC) -c $(CFLAGS) $<

.PHONY: clean

clean:
	rm -f $(SRC_OBJ) version.h
