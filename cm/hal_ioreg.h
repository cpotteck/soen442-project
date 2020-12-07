
#ifndef __hal_IOReg_h
#define __hal_IOReg_h

#include "bsl_ioreg.h"
#include "bsl_stdtype.h"

u32  hal_IOReg_Read(u32 ioreg);
void hal_IOReg_Write(u32 ioreg, u32 value);

#endif
