
#include "hal_ioreg.h"



u8 hal_IOReg_Read(u8 port) {
    return bsl_IOReg_Read(port);
}

void hal_IOReg_Write(u8 port, u8 value) {
    bsl_IOReg_Write(port, value);
}
