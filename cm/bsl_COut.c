/* bsl_COut.c - Implementation of a Console for Cm Hardware Abstract Layer for Output Interface. - was _cout.c
//              Everything is private (static). Need to activate DebugXtoa to test all xtoa functions.
//
// Copyright (C) 1999-2020 by Michel de Champlain
//
*/

#include "bsl_OutDesc.h"
#include "bsl_xtoa.h"
#include <stdio.h>


// #include <avr/io.h>
// #include <avr/interrupt.h>

#if ConsoleOutputWithPrintf

static void COut_PutB(bool b)        { printf("%s", b ? "true" : "false"); }
static void COut_PutC(char c)        { printf("%c", c); }
static void COut_PutS(const char* s) { printf("%s", s); }
static void COut_PutI(i32  i)        { printf("%ld", i); }
static void COut_PutU(u32  u)        { printf("%lu", u); }
static void COut_PutX(u32  u)        { printf("%08lX", u); } // To make hex output always aligned to 8 hex digits.
static void COut_PutN(void)          { printf("\n"); }

static IVMOutDesc cout = {
    COut_PutB,
    COut_PutC,
    COut_PutI,
    COut_PutU,
    COut_PutS,
    COut_PutX,
    COut_PutN
};

IOut Out_GetFactory(const char* whichOne) {
    whichOne = 0; // To avoid the warning on the unreferenced formal parameter
    return &cout;
}
#else
#include <avr/io.h>
// Transmit a character to UART.
static void TxChar(char c) {
  while ( !(CtrlStatusRegA & (1 << DataRegEmpty)) );
  DataReg = c;
}

// From '_console.c'
static void Console_Putchar(char c) { TxChar(c); }

static char buf[12];    // Buffer reserved for conversion to ascii characters.
                        // Need to cover max size (12) on a "i32" (sign + 10 chars + null)

static void COut_Init(void) {
  // Set Baud Rate
  BaudRateRegH = 103 >> 8; 
  BaudRateRegL = 103;
}

static void COut_PutC(char c)        { Console_Putchar(c); }
static void COut_PutS(const char* s) { while (*s) Console_Putchar(*s++); }
static void COut_PutB(bool b)        { COut_PutS(b ? "true" : "false"); }
static void COut_PutI(i32  i)        { bsl_itoa(i, buf); COut_PutS(buf); }
static void COut_PutU(u32  u)        { bsl_utoa(u, buf, 0, 10); COut_PutS(buf); }
static void COut_PutX(u32  x)        { bsl_utoa(x, buf, 0, 16); COut_PutS(buf); } // Same behavior as Dos16 VM:
                                                                                     // Hex alpha in upppercase
static void COut_PutN(void)          { Console_Putchar('\n'); }

static IVMOutDesc cout = {
    COut_PutB,
    COut_PutC,
    COut_PutI,
    COut_PutU,
    COut_PutS,
    COut_PutX,
    COut_PutN
};

static bool init = 0;
IOut Out_GetFactory(const char* whichOne) {
    if (!init) {      // To make sure it will be done only once.
        whichOne = 0; // To avoid the warning on the unreferenced formal parameter.
        COut_Init();
        init = true;
    }
    return &cout;
}
#endif






//---------------------------------[ Example of a private unit testing ]--------------

#ifdef DebugXtoa

#include <util/delay.h>

#define MS_DELAY 1000

static void TestCout(void) {
    COut_PutS("Test xtoa\n");
    COut_PutS("123456789ABCDEF\n");

    bsl_itoa(1234, buf);            COut_PutS(buf);
    bsl_utoa(56789, buf, 0, 10);    COut_PutS(buf);
    bsl_utoa(0xABCDEF, buf, 0, 16); COut_PutS(buf);
    COut_PutN();
}

int main (void) {
//    COut_Init();        // Testing a direct call to init (as a first test).
    Out_GetFactory("");   // Testing the factory that hides everything and does a lazy init.

    // Set onboard LED for output. Just to see a blinking feedback from the Nano board.
    DDRB |= (1 << PB5);

    while(1) {
        TestCout();

        PORTB |= _BV(PORTB5);  // Turn the LED on.
        _delay_ms(MS_DELAY);
        PORTB &= ~_BV(PORTB5); // Turn the LED on.
        _delay_ms(MS_DELAY);
    }
}
#endif
