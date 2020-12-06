
#ifndef __hal_IOReg_h
#define __hal_IOReg_h

#include "bsl_ioreg.h"
#include "bsl_stdtype.h"

u8  hal_IOReg_Read(u8 ioreg);
void hal_IOReg_Write(u8 ioreg, u8 value);

#endif
