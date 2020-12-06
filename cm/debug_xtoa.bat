avr-gcc -Os -Wall -DF_CPU=16000000UL -mmcu=atmega328p -D IORegToMockUart -D DebugXtoa bsl_console.c bsl_COut.c bsl_xtoa.c hal.c bsl_ioreg.c hal_ioreg.c out.c vm.c vmstack.c -o debug_xtoa.o
avr-objcopy -O ihex -j .text -j .data debug_xtoa.o  debug_xtoa.hex
avrdude -c arduino -p atmega328p -b 57600 -P COM8 -D -Uflash:w:debug_xtoa.hex:i
pause