/* tintman1.c -- Test #1 - Interrupt Management
//
// Copyright (C) 1985-2019 by Michel de Champlain
//
*/

#include <stdio.h>
//#include <dos.h>
#include <int.h>       // int_gen

#include "hal.h"       // Hal_Init()
#include "out.h"       // VMOut_Put*()
#include "hal_interman.h"  // Interrupt_*()

void interrupt Handler() {
    VMOut_PutC('*');
}

void main(void) {
    Hal_Init();

    VMOut_PutS("Test #1 - Interrupt Manager\n");
    VMOut_PutS("[*]\n");

    Interrupt_Disable();
    Interrupt_SetVector(255, (u32)Handler);
    Interrupt_Enable();

    VMOut_PutS("[");

    int_gen(255);

    VMOut_PutS("]\n");
}
