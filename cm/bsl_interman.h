#ifndef bsl__interman_h
#define bsl__interman_hs

#include "bsl_stdtype.h"

#define StatusReg SREG

u16 bsl_Flags(void);
void bsl_cli(void);
void bsl_sei(void);
u16 bsl_SaveAndDisable(void);
void bsl_Restore(u16 setFlags);
void bsl_SetVector(u8 number, u32 handlerA);
u32 bsl_GetVector(u8 number);

#endif