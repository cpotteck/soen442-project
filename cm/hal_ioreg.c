
#include "hal_ioreg.h"



u32 hal_IOReg_Read(u32 port) {
    return bsl_IOReg_Read((u8)port);
}

void hal_IOReg_Write(u32 port, u32 value) {
    bsl_IOReg_Write((u8)port, (u8)value);
}
