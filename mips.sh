#!/bin/bash
make clean
make bin/c_compiler
if [[ -z "$1" ]]; then
    COMPILER=bin/c_compiler
else
    COMPILER=$1
fi

mkdir -p working

for DRIVER in compiler_tests/array/*_driver.c ; do
    NAME=$(basename $DRIVER _driver.c)
    TESTCODE=compiler_tests/array/$NAME.c

    >&2 echo "Test case $NAME"

    # Compile driver with normal GCC
    bin/c_compiler -S ${NAME}.c -o ${NAME}.s
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Couldn't compile driver program using GCC."
        continue
    fi

    # Compile test function with compiler under test to assembly
    mips-linux-gnu-gcc -mfp32 -o ${NAME}.o -c ${NAME}.s
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Compiler returned error message."
        continue
    fi

    # Link driver object and assembly into executable
    mips-linux-gnu-gcc -mfp32 -static -o ${NAME} ${NAME}.o ${NAME}_driver.c
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Linker returned error message."
        continue
    fi

    # Run the actual executable
    qemu-mips ${NAME}
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Testcase returned $?, but expected 0."
    else
	echo "pass"
    fi
done
