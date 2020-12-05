#include "bsl_interman.h"

#if ConsoleOutputWithPrintf

u16 flags = 0x00;
u32 interruptVectors[256];

u16 bsl_Flags() { return flags; }

void bsl_cli() { flags = 0x00;}

void bsl_sei() {flags = 0x80;}

u16 bsl_SaveAndDisable() {
    u16 savedFlags = flags;
    bsl_cli();
    return savedFlags;
}

void bsl_Restore(u16 setFlags) {
    flags = setFlags;
}

void bsl_SetVector(u8 number, u32 handlerA) {
    interruptVectors[number] = handlerA;
}

u32 bsl_GetVector(u8 number) {
    return interruptVectors[number];
}
#else

#include <avr/io.h>
#include <avr/interrupt.h>

u16 flags;
u32 interruptVectors[256];

u16 bsl_Flags() { 
    flags = SREG;
    return flags; 
}

void bsl_cli() { cli();}

void bsl_sei() { sei();}

u16 bsl_SaveAndDisable() {
    flags = SREG;
    bsl_cli();
    return flags;
}

void bsl_Restore(u16 setFlags) {
    SREG = setFlags;
}

void bsl_SetVector(u8 number, u32 handlerA) {
    interruptVectors[number] = handlerA;
}

u32 bsl_GetVector(u8 number) {
    return interruptVectors[number];
}

#endif