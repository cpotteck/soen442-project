avr-gcc -Os -Wall -DF_CPU=16000000UL -mmcu=atmega328p -D IORegToMockUart mainArduino.c bsl_console.c bsl_COut.c bsl_xtoa.c hal.c ioreg.c out.c vm.c vmstack.c -o cmTestArduinoLoader.o
avr-objcopy -O ihex -j .text -j .data cmTestArduinoLoader.o  cmTestArduinoLoader.hex
avrdude -c arduino -p atmega328p -b 57600 -P COM8 -D -Uflash:w:cmTestArduinoLoader.hex:i
pause