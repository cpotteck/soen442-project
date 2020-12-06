avr-gcc -Os -Wall -DF_CPU=16000000UL -mmcu=atmega328p -D IORegToMockUart main_arduino.c bsl_console.c bsl_COut.c bsl_xtoa.c hal.c ioreg.c out.c vm.c vmstack.c -o cm_testArduino_loader.o
avr-objcopy -O ihex -j .text -j .data cm_testArduino_loader.o  cm_testArduino_loader.hex
avrdude -c arduino -p atmega328p -b 57600 -P COM8 -D -Uflash:w:cm_testArduino_loader.hex:i
pause