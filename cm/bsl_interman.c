#include <avr/io.h>
#include <avr/interrupt.h>

u16 flags;

public void bsl_cli() { cli();}

public void bsl_sei() { sei();}

public void bsl_SaveAndDisable() {
    flags = SREG;
    bsl_cli();
    return flags;
}

public void bsl_Restore(u16 setFlags) {
    SREG = setFlags;
}

public void bsl_SetVector(u8 number, u32 handlerA) {
    m[number] = handlerA;
}

public u32 bsl_GetVector(u8 number) {
    return m[number];
}