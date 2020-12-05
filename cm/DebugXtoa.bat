avr-gcc -Os -Wall -DF_CPU=16000000UL -mmcu=atmega328p -D IORegToMockUart -D DebugXtoa bsl_console.c bsl_COut.c bsl_xtoa.c hal.c ioreg.c out.c vm.c vmstack.c -o DebugXtoa.o
avr-objcopy -O ihex -j .text -j .data DebugXtoa.o  DebugXtoa.hex
avrdude -c arduino -p atmega328p -b 57600 -P COM8 -D -Uflash:w:DebugXtoa.hex:i
pause