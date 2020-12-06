/* _out.h - Interface for Cm VM Output Interface
//
// Copyright (C) 1999-2020 by Michel de Champlain
//
*/

#ifndef __CmVM_Out_h
#define __CmVM_Out_h

#include "bsl_stdtype.h"

#define CtrlStatusRegA  UCSR0A
#define DataRegEmpty    UDRE0
#define DataReg         UDR0
#define BaudRateRegH    UBRR0H
#define BaudRateRegL    UBRR0L

#ifdef BAUD
#define UBRR F_CPU/16/BAUD-1
#else
#define UBRR F_CPU/16/9600-1 // Default baud rate to 9600
#endif

        struct IVMOutDesc;
typedef struct IVMOutDesc* IOut;

IOut Out_GetFactory(const char* whichOne);

#endif
