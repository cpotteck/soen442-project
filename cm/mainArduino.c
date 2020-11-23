

#include "hal.h"
#include "out.h"
#include "vm.h"
#include <util/delay.h>

void main(void) {
    Hal_Init();

    // Test pre-compiled program
    VMOut_PutS("Test pre-compiled program:\n");
    VMOut_PutS("1\n");
    u8 mem[] = { 0x91, 0xFF, 0x82, 0x00 };
    VM_Init(mem);
    VM_execute(mem);

    // Test UART
    /*
    while(true) {
      VMOut_PutS("Test Out:<2\n");
      VMOut_PutS("Bools: [true|false|true|true]\n");
      VMOut_PutS("Ints:  [-1|-2147483648|2147483647|4294967295|FFFFFFFF]\n");

      VMOut_PutS("Bools: [");
      VMOut_PutB(-1); VMOut_PutC('|');
      VMOut_PutB(0);  VMOut_PutC('|');
      VMOut_PutB(1);  VMOut_PutC('|');
      VMOut_PutB(2);  VMOut_PutS("]\n");

      VMOut_PutS("Ints:  [");
      VMOut_PutI(0xFFFFFFFFL); VMOut_PutC('|');
      VMOut_PutI(0x80000000L); VMOut_PutC('|');
      VMOut_PutI(0x7FFFFFFFL); VMOut_PutC('|');
      VMOut_PutU(0xFFFFFFFFL); VMOut_PutC('|');
      VMOut_PutX(0xFFFFFFFFL);
      VMOut_PutS("]\n");
      _delay_ms(5000);
    }*/
}