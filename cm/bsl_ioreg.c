#include "bsl_IOReg.h"
#include "hal.h"

u32  bsl_IOReg_Read (u32 ioreg){
    hal_IOReg_Read(ioreg);
}
void bsl_IOReg_Write(u32 ioreg, u32 value){
    hal_IOReg_Write(ioreg, value);
}

// void bsl_Init(void)   { 
//     LedDirection |= LedBit;
// }
// void bsl_LED(void) {
//     LedRegister |= LedBit;
// }
