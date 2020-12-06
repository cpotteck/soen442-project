/* ioreg.h - IO Register Interface
//
// Copyright (C) 1999-2020 by Michel de Champlain
//
*/

#ifndef __bsl_IOReg_h
#define __bsl_IOReg_h

#include "bsl_stdtype.h"

u32  bsl_IOReg_Read(u32 ioreg);
void bsl_IOReg_Write(u32 ioreg, u32 value);

#endif
