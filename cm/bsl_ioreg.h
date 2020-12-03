#include <stdint.h>                

#ifndef __bsl_ioreg_h
#define __bsl_ioreg_h

#define FOSC 16000000    
#define BAUD 9600                
#define MYUBRR FOSC/16/BAUD -1

#define LedDirection DDRB
#define LedRegister PORTB
#define LedBit (1 << 5)

void bsl_Init();
void bsl_PutC(char c);
void bsl_PutI(int  i);
void bsl_PutU(int  u);
void bsl_PutX(int  x);


#endif // __bsl_IOReg_h
