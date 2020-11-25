avr-gcc -Os -Wall -DF_CPU=16000000UL -mmcu=atmega328p -D IORegToMockUart mainArduino.c bsl_console.c bsl_COut.c bsl_xtoa.c hal.c ioreg.c out.c vm.c vmstack.c -o cmTestArduino.o
avr-objcopy -O ihex -j .text -j .data cmTestArduino.o  cmTestArduino.hex
avrdude -c arduino -p atmega328p -b 57600 -P COM5 -D -Uflash:w:cmTestArduino.hex:i
pause