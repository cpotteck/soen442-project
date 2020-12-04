/* hal.h -- Hardware Abstraction Layer interface which decouples (or bridges)
//          the board support (machine dependent) modules to the VM portable code.
//
// Copyright (C) 1985-2020 by Michel de Champlain
//
*/

#ifndef __hal_h
#define __hal_h

#include "bsl_COut.h"
//#include "_stdtype.h"

void Hal_Init(void);
u32 hal_IOReg_Read (u32 ioreg);
void hal_IOReg_Write(u32 ioreg, u32 value);

#endif
