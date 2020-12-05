/* hal.c -- Hardware Abstraction Layer implementation
//
// Copyright (C) 1985-2020 by Michel de Champlain
//
*/

#include "hal.h"
#include "hal_Out.h"

#ifndef IORegToMockUart
//#include <dos.h>
#endif

// Software internal counters and values
static u32 _nReads;
static u32 _nWrites;

void hal_Init(void) {
    VMOut_Init(Out_GetFactory("")); // "" to save space, later should be "console".

    #ifdef FullVersion
        Add other init subsystems here.
    #endif
}

/*------------------------------------------------------------------------------------------------------------
 * IOReg_Read is a generic read function to get a value from a device register.
 * The parameter 'ioreg' is 32-bit wide allowing to pass 8-bit, 16-bit, 24-bit, or 32-bit device addresses.
 * The return value is also 32-bit wide allowing to get  8-bit, 16-bit, 24-bit, or 32-bit values.
 *
 * In the case of Windows: ioreg is u16 (unsigned) and return value is u8 (unsigned char)
 *-----------------------------------------------------------------------------------------------------------*/
u32 hal_IOReg_Read(u32 port) {
    
    ++_nReads;
    return (u32)((_nReads << 8) | (_nWrites << 4) | (port & 0xFFUL));
}

/*------------------------------------------------------------------------------------------------------------
 * IOReg_Write is a generic write function to set a value to a device register.
 * The parameter 'ioreg' is 32-bit wide allowing to pass 8-bit, 16-bit, 24-bit, or 32-bit device addresses.
 * The parameter 'value' is 32-bit wide allowing to set  8-bit, 16-bit, 24-bit, or 32-bit values.
 *
 * In the case of Dos16: ioreg is u16 (unsigned) and value is u8 (unsigned char)
 *-----------------------------------------------------------------------------------------------------------*/
void hal_IOReg_Write(u32 port, u32 value) {
    ++_nWrites;
}


