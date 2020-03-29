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
    TCODE=compiler_tests/array/$NAME.c

    >&2 echo "Test case $NAME"

    # Compile driver with normal GCC
    mips-linux-gnu-gcc -c $DRIVER -o working/${NAME}_driver.o 2> working/${NAME}_driver.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Couldn't compile driver program using GCC."
        continue
    fi

    # Compile test function with compiler under test to assembly
    cat $TCODE | $COMPILER > working/$NAME.s  2> working/${NAME}.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Compiler returned error message."
        continue
    fi

    # Link driver object and assembly into executable
    mips-linux-gnu-gcc -static working/${NAME}.s working/${NAME}_driver.o -o working/${NAME}.elf 2> working/${NAME}.link.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Linker returned error message."
        continue
    fi

    # Run the actual executable
    qemu-mips working/${NAME}.elf
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Testcase returned $?, but expected 0."
    else
	echo "pass"
    fi
done

for DRIVER in compiler_tests/control_flow/*_driver.c ; do
    NAME=$(basename $DRIVER _driver.c)
    TCODE=compiler_tests/control_flow/$NAME.c

    >&2 echo "Test case $NAME"

    # Compile driver with normal GCC
    mips-linux-gnu-gcc -c $DRIVER -o working/${NAME}_driver.o 2> working/${NAME}_driver.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Couldn't compile driver program using GCC."
        continue
    fi

    # Compile test function with compiler under test to assembly
    cat $TCODE | $COMPILER > working/$NAME.s  2> working/${NAME}.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Compiler returned error message."
        continue
    fi

    # Link driver object and assembly into executable
    mips-linux-gnu-gcc -static working/${NAME}.s working/${NAME}_driver.o -o working/${NAME}.elf 2> working/${NAME}.link.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Linker returned error message."
        continue
    fi

    # Run the actual executable
    qemu-mips working/${NAME}.elf
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Testcase returned $?, but expected 0."
    else
	echo "pass"
    fi
done

for DRIVER in compiler_tests/default/*_driver.c ; do
    NAME=$(basename $DRIVER _driver.c)
    TCODE=compiler_tests/default/$NAME.c

    >&2 echo "Test case $NAME"

    # Compile driver with normal GCC
    mips-linux-gnu-gcc -c $DRIVER -o working/${NAME}_driver.o 2> working/${NAME}_driver.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Couldn't compile driver program using GCC."
        continue
    fi

    # Compile test function with compiler under test to assembly
    cat $TCODE | $COMPILER > working/$NAME.s  2> working/${NAME}.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Compiler returned error message."
        continue
    fi

    # Link driver object and assembly into executable
    mips-linux-gnu-gcc -static working/${NAME}.s working/${NAME}_driver.o -o working/${NAME}.elf 2> working/${NAME}.link.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Linker returned error message."
        continue
    fi

    # Run the actual executable
    qemu-mips working/${NAME}.elf
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Testcase returned $?, but expected 0."
    else
	echo "pass"
    fi
done

for DRIVER in compiler_tests/float/*_driver.c ; do
    NAME=$(basename $DRIVER _driver.c)
    TCODE=compiler_tests/float/$NAME.c

    >&2 echo "Test case $NAME"

    # Compile driver with normal GCC
    mips-linux-gnu-gcc -c $DRIVER -o working/${NAME}_driver.o 2> working/${NAME}_driver.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Couldn't compile driver program using GCC."
        continue
    fi

    # Compile test function with compiler under test to assembly
    cat $TCODE | $COMPILER > working/$NAME.s  2> working/${NAME}.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Compiler returned error message."
        continue
    fi

    # Link driver object and assembly into executable
    mips-linux-gnu-gcc -static working/${NAME}.s working/${NAME}_driver.o -o working/${NAME}.elf 2> working/${NAME}.link.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Linker returned error message."
        continue
    fi

    # Run the actual executable
    qemu-mips working/${NAME}.elf
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Testcase returned $?, but expected 0."
    else
	echo "pass"
    fi
done

for DRIVER in compiler_tests/functions/*_driver.c ; do
    NAME=$(basename $DRIVER _driver.c)
    TCODE=compiler_tests/functions/$NAME.c

    >&2 echo "Test case $NAME"

    # Compile driver with normal GCC
    mips-linux-gnu-gcc -c $DRIVER -o working/${NAME}_driver.o 2> working/${NAME}_driver.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Couldn't compile driver program using GCC."
        continue
    fi

    # Compile test function with compiler under test to assembly
    cat $TCODE | $COMPILER > working/$NAME.s  2> working/${NAME}.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Compiler returned error message."
        continue
    fi

    # Link driver object and assembly into executable
    mips-linux-gnu-gcc -static working/${NAME}.s working/${NAME}_driver.o -o working/${NAME}.elf 2> working/${NAME}.link.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Linker returned error message."
        continue
    fi

    # Run the actual executable
    qemu-mips working/${NAME}.elf
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Testcase returned $?, but expected 0."
    else
	echo "pass"
    fi
done

for DRIVER in compiler_tests/integer/*_driver.c ; do
    NAME=$(basename $DRIVER _driver.c)
    TCODE=compiler_tests/integer/$NAME.c

    >&2 echo "Test case $NAME"

    # Compile driver with normal GCC
    mips-linux-gnu-gcc -c $DRIVER -o working/${NAME}_driver.o 2> working/${NAME}_driver.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Couldn't compile driver program using GCC."
        continue
    fi

    # Compile test function with compiler under test to assembly
    cat $TCODE | $COMPILER > working/$NAME.s  2> working/${NAME}.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Compiler returned error message."
        continue
    fi

    # Link driver object and assembly into executable
    mips-linux-gnu-gcc -static working/${NAME}.s working/${NAME}_driver.o -o working/${NAME}.elf 2> working/${NAME}.link.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Linker returned error message."
        continue
    fi

    # Run the actual executable
    qemu-mips working/${NAME}.elf
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Testcase returned $?, but expected 0."
    else
	echo "pass"
    fi
done

for DRIVER in compiler_tests/local_var/*_driver.c ; do
    NAME=$(basename $DRIVER _driver.c)
    TCODE=compiler_tests/local_var/$NAME.c

    >&2 echo "Test case $NAME"

    # Compile driver with normal GCC
    mips-linux-gnu-gcc -c $DRIVER -o working/${NAME}_driver.o 2> working/${NAME}_driver.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Couldn't compile driver program using GCC."
        continue
    fi

    # Compile test function with compiler under test to assembly
    cat $TCODE | $COMPILER > working/$NAME.s  2> working/${NAME}.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Compiler returned error message."
        continue
    fi

    # Link driver object and assembly into executable
    mips-linux-gnu-gcc -static working/${NAME}.s working/${NAME}_driver.o -o working/${NAME}.elf 2> working/${NAME}.link.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Linker returned error message."
        continue
    fi

    # Run the actual executable
    qemu-mips working/${NAME}.elf
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Testcase returned $?, but expected 0."
    else
	echo "pass"
    fi
done

for DRIVER in compiler_tests/misc/*_driver.c ; do
    NAME=$(basename $DRIVER _driver.c)
    TCODE=compiler_tests/misc/$NAME.c

    >&2 echo "Test case $NAME"

    # Compile driver with normal GCC
    mips-linux-gnu-gcc -c $DRIVER -o working/${NAME}_driver.o 2> working/${NAME}_driver.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Couldn't compile driver program using GCC."
        continue
    fi

    # Compile test function with compiler under test to assembly
    cat $TCODE | $COMPILER > working/$NAME.s  2> working/${NAME}.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Compiler returned error message."
        continue
    fi

    # Link driver object and assembly into executable
    mips-linux-gnu-gcc -static working/${NAME}.s working/${NAME}_driver.o -o working/${NAME}.elf 2> working/${NAME}.link.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Linker returned error message."
        continue
    fi

    # Run the actual executable
    qemu-mips working/${NAME}.elf
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Testcase returned $?, but expected 0."
    else
	echo "pass"
    fi
done

for DRIVER in compiler_tests/pointer/*_driver.c ; do
    NAME=$(basename $DRIVER _driver.c)
    TCODE=compiler_tests/pointer/$NAME.c

    >&2 echo "Test case $NAME"

    # Compile driver with normal GCC
    mips-linux-gnu-gcc -c $DRIVER -o working/${NAME}_driver.o 2> working/${NAME}_driver.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Couldn't compile driver program using GCC."
        continue
    fi

    # Compile test function with compiler under test to assembly
    cat $TCODE | $COMPILER > working/$NAME.s  2> working/${NAME}.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Compiler returned error message."
        continue
    fi

    # Link driver object and assembly into executable
    mips-linux-gnu-gcc -static working/${NAME}.s working/${NAME}_driver.o -o working/${NAME}.elf 2> working/${NAME}.link.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Linker returned error message."
        continue
    fi

    # Run the actual executable
    qemu-mips working/${NAME}.elf
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Testcase returned $?, but expected 0."
    else
	echo "pass"
    fi
done

for DRIVER in compiler_tests/programs/*_driver.c ; do
    NAME=$(basename $DRIVER _driver.c)
    TCODE=compiler_tests/programs/$NAME.c

    >&2 echo "Test case $NAME"

    # Compile driver with normal GCC
    mips-linux-gnu-gcc -c $DRIVER -o working/${NAME}_driver.o 2> working/${NAME}_driver.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Couldn't compile driver program using GCC."
        continue
    fi

    # Compile test function with compiler under test to assembly
    cat $TCODE | $COMPILER > working/$NAME.s  2> working/${NAME}.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Compiler returned error message."
        continue
    fi

    # Link driver object and assembly into executable
    mips-linux-gnu-gcc -static working/${NAME}.s working/${NAME}_driver.o -o working/${NAME}.elf 2> working/${NAME}.link.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Linker returned error message."
        continue
    fi

    # Run the actual executable
    qemu-mips working/${NAME}.elf
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Testcase returned $?, but expected 0."
    else
	echo "pass"
    fi
done

for DRIVER in compiler_tests/strings/*_driver.c ; do
    NAME=$(basename $DRIVER _driver.c)
    TCODE=compiler_tests/strings/$NAME.c

    >&2 echo "Test case $NAME"

    # Compile driver with normal GCC
    mips-linux-gnu-gcc -c $DRIVER -o working/${NAME}_driver.o 2> working/${NAME}_driver.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Couldn't compile driver program using GCC."
        continue
    fi

    # Compile test function with compiler under test to assembly
    cat $TCODE | $COMPILER > working/$NAME.s  2> working/${NAME}.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Compiler returned error message."
        continue
    fi

    # Link driver object and assembly into executable
    mips-linux-gnu-gcc -static working/${NAME}.s working/${NAME}_driver.o -o working/${NAME}.elf 2> working/${NAME}.link.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Linker returned error message."
        continue
    fi

    # Run the actual executable
    qemu-mips working/${NAME}.elf
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Testcase returned $?, but expected 0."
    else
	echo "pass"
    fi
done

for DRIVER in compiler_tests/struct/*_driver.c ; do
    NAME=$(basename $DRIVER _driver.c)
    TCODE=compiler_tests/struct/$NAME.c

    >&2 echo "Test case $NAME"

    # Compile driver with normal GCC
    mips-linux-gnu-gcc -c $DRIVER -o working/${NAME}_driver.o 2> working/${NAME}_driver.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Couldn't compile driver program using GCC."
        continue
    fi

    # Compile test function with compiler under test to assembly
    cat $TCODE | $COMPILER > working/$NAME.s  2> working/${NAME}.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Compiler returned error message."
        continue
    fi

    # Link driver object and assembly into executable
    mips-linux-gnu-gcc -static working/${NAME}.s working/${NAME}_driver.o -o working/${NAME}.elf 2> working/${NAME}.link.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Linker returned error message."
        continue
    fi

    # Run the actual executable
    qemu-mips working/${NAME}.elf
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Testcase returned $?, but expected 0."
    else
	echo "pass"
    fi
done

for DRIVER in compiler_tests/type/*_driver.c ; do
    NAME=$(basename $DRIVER _driver.c)
    TCODE=compiler_tests/type/$NAME.c

    >&2 echo "Test case $NAME"

    # Compile driver with normal GCC
    mips-linux-gnu-gcc -c $DRIVER -o working/${NAME}_driver.o 2> working/${NAME}_driver.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Couldn't compile driver program using GCC."
        continue
    fi

    # Compile test function with compiler under test to assembly
    cat $TCODE | $COMPILER > working/$NAME.s  2> working/${NAME}.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Compiler returned error message."
        continue
    fi

    # Link driver object and assembly into executable
    mips-linux-gnu-gcc -static working/${NAME}.s working/${NAME}_driver.o -o working/${NAME}.elf 2> working/${NAME}.link.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Linker returned error message."
        continue
    fi

    # Run the actual executable
    qemu-mips working/${NAME}.elf
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Testcase returned $?, but expected 0."
    else
	echo "pass"
    fi
done
