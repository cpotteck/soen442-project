/* hal_interman.c -- Interrupt Management Interface for Dos16 - Small Model (with Digital Mars C/C++)
//
// Copyright (C) 1985-2019 by Michel de Champlain
//
*/

#include "hal_interman.h"
#include <dos.h>

typedef void (__interrupt __far *Handler)();

#define __cli()  __emit__(0xFA)
#define __sli()  __emit__(0xFB)

#if ____x8086
// End-of-interrupt to 8259 controller
// B0 20    mov  al, 0x20
// E6 20    out  0x20, al
#define __endOfInterrupt() (__emit__(0xB0),__emit__(0x20),__emit__(0xE6),__emit__(0x20))
#define __iret()            __emit__(0xCF)
#endif

#define __saveAndDisable() (__emit__(0x9C),__emit__(0xFA),__emit__(0x58))
#define __restore()        (__emit__(0x55),__emit__(0x89),__emit__(0xE5),__emit__(0xFF),__emit__(0x76),__emit__(0x04),__emit__(0x9D),__emit__(0x5D))

public void  Interrupt_Disable(void) { bsl_cli(); }
public void  Interrupt_Enable(void)  { bsl_sei(); }

public u16   Interrupt_SaveAndDisable(void) { bsl_SaveAndDisable();
/* asm {
        pushf        // 9C Push FLAGS Register onto the Stack
        cli          // FA Clear Interrupt Flag
        pop ax       // 58 Pop from Stack
   }
*/
}

public void  Interrupt_Restore(u16 flags) { bsl_Restore(flags);
/* asm {
        push  bp                // 55
        mov   bp, sp            // 89 E5
        push  word ptr [bp+4]   // FF 76 04
        popf                    // 9D Pop Stack into FLAGS Register
        pop   bp;               // 5D 
    }
*/
}

public void  Interrupt_SetVector(u8 number, u32 handlerAddr) {
    bsl_SetVector(number, (Handler)handlerAddr);
}

public u32   Interrupt_GetVector(u8 number) {
    return (u32)bsl_GetVector(number);
}
