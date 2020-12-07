# soen442-project

<!--ts-->
   * [soen442-project](#soen442-project)
      * [Commands](#commands)
         * [Task 0](#task-0)
         * [Task 1 &amp; Task 2](#task-1--task-2)
         * [Task 3](#task-3)
         * [Task 4](#task-4)
         * [Task 5](#task-5)
         * [Task 6](#task-6)
         * [Task 7](#task-7)
<!--te-->
## Commands

**Note:** the following commands were written and executed with Windows Command Prompt in mind. They were not tested on a Linux shell and from our experience, some might break on PowerShell.

**Note:** the following commands assume that you are in the root directory of the repository before each step.

### Task 0

Compile aunit:
```bash
gcc aunit.c -o aunit
```

Run aunit:
```bash
./aunit.exe
```

### Task 1 & Task 2

Change directory:
```bash
cd cm
```

Compile cm:
```bash
gcc -DConsoleOutputWithPrintf bsl_console.c bsl_COut.c bsl_xtoa.c admin.c hal.c hal_ioreg.c bsl_ioreg.c out.c vm.c vmstack.c -o cm
```
Copy the created `cm.exe` into /tests/

Copy the created `aunit.exe` from Task 0 into /tests/

Change directory:
```bash
cd ..
cd tests
```

Run the tests:
```bash
run_aunit_tests.bat
```

### Task 3


Change directory:
```bash
cd cm
```

Compile source files and flash to Arduino:

**Note:** your COM port might be different! Substitute the port in the third command with yours before running.

```
avr-gcc -Os -Wall -DF_CPU=16000000UL -mmcu=atmega328p -D IORegToMockUart -D DebugXtoa bsl_console.c bsl_COut.c bsl_xtoa.c hal.c hal_ioreg.c bsl_ioreg.c out.c vm.c vmstack.c -o debug_xtoa.o
avr-objcopy -O ihex -j .text -j .data debug_xtoa.o  debug_xtoa.hex
avrdude -c arduino -p atmega328p -b 57600 -P COM8 -D -Uflash:w:debug_xtoa.hex:i
```

### Task 4

Change directory:
```bash
cd cm
```

Compile source files and flash to Arduino:

**Note:** same as in Task 3, your COM port might be different! Substitute the port in the third command with yours before running.

```
avr-gcc -Os -Wall -DF_CPU=16000000UL -mmcu=atmega328p -D IORegToMockUart -D TestTargetPrecompiled main_arduino.c bsl_console.c bsl_COut.c bsl_xtoa.c hal.c hal_ioreg.c bsl_ioreg.c out.c vm.c vmstack.c -o cm_testArduino_precompiled.o
avr-objcopy -O ihex -j .text -j .data cm_testArduino_precompiled.o  cm_testArduino_precompiled.hex
avrdude -c arduino -p atmega328p -b 57600 -P COM8 -D -Uflash:w:cm_testArduino_precompiled.hex:i
```

### Task 5

Change directory:
```bash
cd cm
```

Compile loader:

**Note:** replace the COM port value with yours.

```
gcc -DTARGET_PORT=\"COM8\" target_loader.c windows_comm.c -o target_loader
```

Compile target source files and flash Arduino:

**Note:** replace the COM port value in the third command with yours.

```
avr-gcc -Os -Wall -DF_CPU=16000000UL -mmcu=atmega328p -D IORegToMockUart main_arduino.c bsl_console.c bsl_COut.c bsl_xtoa.c hal.c hal_ioreg.c bsl_ioreg.c out.c vm.c vmstack.c -o cm_testArduino_loader.o
avr-objcopy -O ihex -j .text -j .data cm_testArduino_loader.o  cm_testArduino_loader.hex
avrdude -c arduino -p atmega328p -b 57600 -P COM8 -D -Uflash:w:cm_testArduino_loader.hex:i
```

Use the host loader to load and run a program onto the arduino:

**Note:** make sure the T01.exe file is copied into the /cm directory.

```
target_loader.exe -send T01.exe
```

### Task 6

Change directory:
```bash
cd cm
```

Test `test_interman0.c` on target:
```bash
# compile with test_interman0.c
avr-gcc -Os -Wall -DF_CPU=16000000UL -mmcu=atmega328p -D IORegToMockUart -DInterruptManagerOn test_interman0.c hal_interman.c bsl_interman.c bsl_console.c bsl_COut.c bsl_xtoa.c hal.c hal_ioreg.c bsl_ioreg.c out.c vm.c vmstack.c -o test_interman0.o
avr-objcopy -O ihex -j .text -j .data test_interman0.o  test_interman0.hex
avrdude -c arduino -p atmega328p -b 57600 -P COM8 -D -Uflash:w:test_interman0.hex:i
```

Test `test_interman1.c` on target:
```bash
# compile with test_interman1.c
avr-gcc -Os -Wall -DF_CPU=16000000UL -mmcu=atmega328p -D IORegToMockUart -DInterruptManagerOn test_interman1.c hal_interman.c bsl_interman.c bsl_console.c bsl_COut.c bsl_xtoa.c hal.c hal_ioreg.c bsl_ioreg.c out.c vm.c vmstack.c -o test_interman1.o
avr-objcopy -O ihex -j .text -j .data test_interman1.o  test_interman1.hex
avrdude -c arduino -p atmega328p -b 57600 -P COM8 -D -Uflash:w:test_interman1.hex:i
```

Test `hal_TestInterman0.c` on target:
```bash
# compile with hal_TestInterman0.c
avr-gcc -Os -Wall -DF_CPU=16000000UL -mmcu=atmega328p -D IORegToMockUart -DInterruptManagerOn hal_TestInterman0.c hal_interman.c bsl_interman.c bsl_console.c bsl_COut.c bsl_xtoa.c hal.c hal_ioreg.c bsl_ioreg.c out.c vm.c vmstack.c -o hal_TestInterman0.o
avr-objcopy -O ihex -j .text -j .data hal_TestInterman0.o  hal_TestInterman0.hex
avrdude -c arduino -p atmega328p -b 57600 -P COM8 -D -Uflash:w:hal_TestInterman0.hex:i
```

### Task 7

Change directory:
```bash
cd cm
```

Test `bsl_TestIOReg0.c` on target:
```bash
avr-gcc -Os -Wall -DF_CPU=16000000UL -mmcu=atmega328p -D IORegToMockUart -D TestTargetIOReg bsl_TestIOReg0.c bsl_console.c bsl_COut.c bsl_xtoa.c hal.c bsl_ioreg.c hal_ioreg.c out.c vm.c vmstack.c -o bsl_TestIOReg0.o
avr-objcopy -O ihex -j .text -j .data bsl_TestIOReg0.o  bsl_TestIOReg0.hex
avrdude -c arduino -p atmega328p -b 57600 -P COM8 -D -Uflash:w:bsl_TestIOReg0.hex:i
```

