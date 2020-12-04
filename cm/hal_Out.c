/* ioreg.c -- I/O Register Interface for Windows
//
// Copyright (C) 1985-2020 by Michel de Champlain
//
*/

#include "hal_ioreg.h"
#include "bsl_IOReg.h"           
#include <avr/io.h>

#ifndef IORegToMockUart
#include <dos.h>
#endif

// Software internal counters and values
static u32 _nReads;
static u32 _nWrites;

void hal_Init(){
    PortBDir |= PortBData;
}

unsigned char hal_Receive(){
    /* Wait for data to be received */
    while (!(UCSR0A & (1<<RXC0)));
    /* Get and return received data from buffer */
    return UDR0;
}

void hal_Transmit(unsigned char data)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1<<UDRE0)));
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

/*------------------------------------------------------------------------------------------------------------
 * IOReg_Read is a generic read function to get a value from a device register.
 * The parameter 'ioreg' is 32-bit wide allowing to pass 8-bit, 16-bit, 24-bit, or 32-bit device addresses.
 * The return value is also 32-bit wide allowing to get  8-bit, 16-bit, 24-bit, or 32-bit values.
 *
 * In the case of Windows: ioreg is u16 (unsigned) and return value is u8 (unsigned char)
 *-----------------------------------------------------------------------------------------------------------*/
u32 IOReg_Read(u32 port) {
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
void IOReg_Write(u32 port, u32 value) {
    port |= value;
    ++_nWrites;
}
