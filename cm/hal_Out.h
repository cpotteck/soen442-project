// hal_ioreg.h -- IO Register Interface

#ifndef __hal_IOReg_h
#define __hal_IOReg_h

#include "bsl_stdtype.h"

void hal_Init(void);
unsigned char hal_Receive();
void hal_Transmit(unsigned char);
u32 hal_IOReg_Read (u32 ioreg);
void hal_IOReg_Write(u32 ioreg, u32 value);

#endif
