# soen442-project

## Commands

**Note:** the following commands were written and executed with Windows Command Prompt in mind. They were not tested on a Linux shell and from our experience, some might break on PowerShell.

### Task 0

Compile aunit:
```bash
gcc aunit.c -o aunit
```

Run aunit:
```bash
./aunit.exe
```

### Task 1

Compile cm:
```bash
gcc -DConsoleOutputWithPrintf bsl_console.c bsl_COut.c bsl_xtoa.c admin.c hal.c ioreg.c out.c vm.c vmstack.c -o cm
```

Run the tests (assuming the cm executable, aunit, and test files are all under the same directory):
```bash
.\runAunitTests.bat
```

### Task 2

Compile cm:
```bash
gcc -DConsoleOutputWithPrintf bsl_console.c bsl_COut.c bsl_xtoa.c admin.c hal.c ioreg.c out.c vm.c vmstack.c -o cm
```

Run the tests (assuming the cm executable, aunit, and test files are all under the same directory):
```bash
.\runAunitTests.bat
```

### Task 3

Compile source files and flash to Arduino:

**Note:** your COM port might be different! Substitute the port in the third command with yours before running.

```
avr-gcc -Os -Wall -DF_CPU=16000000UL -mmcu=atmega328p -D IORegToMockUart -D DebugXtoa bsl_console.c bsl_COut.c bsl_xtoa.c hal.c ioreg.c out.c vm.c vmstack.c -o debug_xtoa.o
avr-objcopy -O ihex -j .text -j .data debug_xtoa.o  debug_xtoa.hex
avrdude -c arduino -p atmega328p -b 57600 -P COM8 -D -Uflash:w:debug_xtoa.hex:i
```

### Task 4

Compile source files and flash to Arduino:

**Note:** same as in Task 3, your COM port might be different! Substitute the port in the third command with yours before running.

```
avr-gcc -Os -Wall -DF_CPU=16000000UL -mmcu=atmega328p -D IORegToMockUart -D TestTargetPrecompiled main_arduino.c bsl_console.c bsl_COut.c bsl_xtoa.c hal.c ioreg.c out.c vm.c vmstack.c -o cm_testArduino_precompiled.o
avr-objcopy -O ihex -j .text -j .data cm_testArduino_precompiled.o  cm_testArduino_precompiled.hex
avrdude -c arduino -p atmega328p -b 57600 -P COM8 -D -Uflash:w:cm_testArduino_precompiled.hex:i
```

### Task 5

Compile loader:

**Note:** replace the COM port value with yours.

```
gcc -DTARGET_PORT=\"COM3\" target_loader.c windows_comm.c -o target_loader
```

Compile target source files and flash Arduino:

**Note:** replace the COM port value in the third command with yours.

```
avr-gcc -Os -Wall -DF_CPU=16000000UL -mmcu=atmega328p -D IORegToMockUart main_arduino.c bsl_console.c bsl_COut.c bsl_xtoa.c hal.c ioreg.c out.c vm.c vmstack.c -o cm_testArduino_loader.o
avr-objcopy -O ihex -j .text -j .data cm_testArduino_loader.o  cm_testArduino_loader.hex
avrdude -c arduino -p atmega328p -b 57600 -P COM3 -D -Uflash:w:cm_testArduino_loader.hex:i
```

Use the host loader to load and run a program onto the arduino:

```
./target_loader.exe -send T01.exe
```

### Task 6

Test `test_interman0.c`:
```bash
# compile with test_interman0.c
gcc -DConsoleOutputWithPrintf -DInterruptManagerOn .\test_interman0.c .\hal_interman.c ./bsl_interman.c bsl_console.c bsl_COut.c bsl_xtoa.c hal.c ioreg.c out.c vm.c vmstack.c -o test_interman0

# run with test_interman0.c
./test_interman0.exe
```

Test `test_interman1.c`:
```bash
# compile with test_interman1.c
gcc -DConsoleOutputWithPrintf -DInterruptManagerOn .\test_interman1.c .\hal_interman.c ./bsl_interman.c bsl_console.c bsl_COut.c bsl_xtoa.c hal.c ioreg.c out.c vm.c vmstack.c -o test_interman1

# run with test_interman1.c
./test_interman1.exe
```

Test `hal_TestInterman0.c`:
```bash
# compile with hal_TestInterman0.c
gcc -DConsoleOutputWithPrintf -DInterruptManagerOn .\hal_TestInterman0.c .\hal_interman.c ./bsl_interman.c bsl_console.c bsl_COut.c bsl_xtoa.c hal.c ioreg.c out.c vm.c vmstack.c -o hal_TestInterman0

# run with hal_TestInterman0.c
./hal_TestInterman0.exe
```

### Task 7

**TODO**
