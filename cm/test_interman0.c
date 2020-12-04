/* tintman0.c -- Test #0 - for Interrupt Management - sdi/ri/di/ei
//
// Copyright (C) 1985-2019 by Michel de Champlain
//
*/

#include <stdio.h>
//#include <dos.h>

#include "hal.h" // Hal_Init()
#include "out.h" // All VMOut_Put*

#include "hal_interman.h"

#define __flags() (__emit__(0x9C),__emit__(0x58))

#define IF 0x0200
#define Enabled  "[e]"
#define Disabled "[d]"

u16  Flags() { __flags(); }
//     asm pushf;   // 9C
//     asm pop ax;  // 58
// }

void main(void) {
    u16 saveFlags, flags = Flags();

    Hal_Init();

    VMOut_PutS("Test #0 - Interrupt Manager\n");
    VMOut_PutS("F[e]<DI>F[d]<EI>F[e]<SDI>SF[e]F[d]<RI>F[e]\n");

    VMOut_PutS("F"); // VMOut_PutX((u32)flags);
    VMOut_PutS( (flags&IF) ? Enabled : Disabled);

    VMOut_PutS("<DI>");
    Interrupt_Disable();

    flags = Flags();
    VMOut_PutS("F"); // VMOut_PutX((u32)flags);
    VMOut_PutS( (flags&IF) ? Enabled : Disabled);

    VMOut_PutS("<EI>");
    Interrupt_Enable();

    flags = Flags();
    VMOut_PutS("F"); // VMOut_PutX((u32)flags);
    VMOut_PutS( (flags&IF) ? Enabled : Disabled);

    VMOut_PutS("<SDI>");
    saveFlags = Interrupt_SaveAndDisable();

    flags = Flags();
    VMOut_PutS("SF"); // VMOut_PutX((u32)saveFlags);
    VMOut_PutS( (saveFlags&IF) ? Enabled : Disabled);
    VMOut_PutS("F");  // VMOut_PutX((u32)flags);
    VMOut_PutS( (flags&IF) ? Enabled : Disabled);

    VMOut_PutS("<RI>");
    Interrupt_Restore(saveFlags);

    flags = Flags();
    VMOut_PutS("F"); // VMOut_PutX((u32)flags);
    VMOut_PutS( (flags&IF) ? Enabled : Disabled);
    VMOut_PutN();
}
