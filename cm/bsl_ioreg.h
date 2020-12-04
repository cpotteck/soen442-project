/* bsl_IOReg.h - IO Register Interface
//
// Copyright (C) 2020 by Michel de Champlain
//
*/

#ifndef __bsl_IOReg_h
#define __bsl_IOReg_h

#define FOSC 16000000    
#define BAUD 9600                
#define MYUBRR FOSC/16/BAUD -1

// #define LedDirection DDRB
// #define LedRegister PORTB
// #define LedBit (1 << 5)
#define PortBDir  0x24L
#define PortBData 0x25L

#include "bsl_stdtype.h"
#include "bsl_stdtype.h"

u32  bsl_IOReg_Read (u32 ioreg);
void bsl_IOReg_Write(u32 ioreg, u32 value);

#endif
