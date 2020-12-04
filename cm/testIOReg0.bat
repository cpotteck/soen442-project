avr-gcc -Os -Wall -DF_CPU=16000000UL -mmcu=atmega328p bsl_TestIOReg0.c bsl_IOReg.c hal.c hal_Out.c bsl_Uart.c bsl_COut.c bsl_xtoa.c -o bsl_TestIOReg0.o
avr-objcopy -O ihex -j .text -j .data hal_TestIOReg0.o  bsl_TestIOReg0.hex
avrdude -c arduino -p atmega328p -b 57600 -P COM5 -D -Uflash:w:bsl_TestIOReg0.hex:i
pause
