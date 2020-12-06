avr-gcc -Os -Wall -DF_CPU=16000000UL -mmcu=atmega328p -D IORegToMockUart -D TestTargetIOReg main_arduino.c bsl_console.c bsl_COut.c bsl_xtoa.c hal.c bsl_ioreg.c hal_ioreg.c out.c vm.c vmstack.c -o cm_testArduino_ioreg.o
avr-objcopy -O ihex -j .text -j .data cm_testArduino_ioreg.o  cm_testArduino_ioreg.hex
avrdude -c arduino -p atmega328p -b 57600 -P COM8 -D -Uflash:w:cm_testArduino_ioreg.hex:i
pause