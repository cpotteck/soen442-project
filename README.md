# soen442-project

## Commands

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
