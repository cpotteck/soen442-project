/* ioreg.h - IO Register Interface
//
// Copyright (C) 1999-2020 by Michel de Champlain
//
*/

#ifndef __bsl_IOReg_h
#define __bsl_IOReg_h

#include "bsl_stdtype.h"

u8  bsl_IOReg_Read(u8 ioreg);
void bsl_IOReg_Write(u8 ioreg, u8 value);

#endif
