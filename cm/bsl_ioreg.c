#include "bsl_IOReg.h"

void bsl_Init(void)   { 
    LedDirection |= LedBit;
}
void bsl_LED(void) {
    LedRegister &= ~LedBit;
    _delay_ms(1000); // Wait a second.
    LedRegister |= LedBit;
}
