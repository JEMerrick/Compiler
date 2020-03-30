#!/bin/bash
if [[ "$1" != "" ]] ; then
    compiler="$1"
else
    compiler="bin/c_compiler"
fi
have_compiler=0
if [[ ! -f bin/c_compiler ]] ; then
    >&2 echo "Warning : cannot find compiler at path ${compiler}. Only checking C reference against python reference."
    have_compiler=1
fi
input_dir="compiler_tests"
working="working"
mkdir -p ${working}
testsTotal=0
testsPassed=0
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\e[93m'
NC='\033[0m'
echo "Passing tests:" > passingTests.txt
echo "Failing tests:" > failingTests.txt
for SUBDIR in ${input_dir}/* ; do
    for DRIVER in ${SUBDIR}/*_driver.c ; do
        base=$(basename $DRIVER _driver.c)
        TESTCODE=${input_dir}/$NAME
        DIR=$(dirname "${DRIVER}")
        if [[ ${have_compiler} -eq 0 ]] ; then
            #run the compiler on the test program:
            #bin/c_compiler -S test_program.c -o test_program.s
            echo "Compiling test program"
            $compiler -S ${DIR}/${base}.c -o ${working}/${base}.s
            #use gcc to assemble the generated assembly
            #mips-linux-gnu-gcc -mfp32 -o test_program.o -c test_program.s
            echo "Assembling into object"
            mips-linux-gnu-gcc -mfp32 -o ${working}/${base}.o -c ${working}/${base}.s
            echo "Linking object with driver"
            #use gcc to link the generated object with the driver file to produce an executable
            #mips-linux-gnu-gcc -mfp32 -static -o test_program test_program.o test_program_driver.c
            mips-linux-gnu-gcc -mfp32 -static -o ${working}/$base ${working}/${base}.o $DRIVER
            #use qemu to simulate the executable on mips
            #qemu-mips test_program
            echo "Simulating executable on MIPS"
            qemu-mips ${working}/${base}
            EXIT_CODE=$?
        fi
        #should produce exit code 0
        testsTotal=$((${testsTotal}+1))
        if [[ ${have_compiler} -ne 0 ]] ; then
            echo -e "${YELLOW}$base, Fail, No C compiler/translator${NC}"
        elif [[ ${EXIT_CODE} -ne 0 ]] ; then
            echo -e "${RED}$base, Fail, Expected 0, got ${EXIT_CODE}${NC}"
            echo "$base" >> failingTests.txt
        else
            echo -e "${GREEN}$base, Pass${NC}"
            echo "$base" >> passingTests.txt
            testsPassed=$((${testsPassed}+1))
        fi
    done
done
echo -e "Passed ${testsPassed} out of ${testsTotal} tests.\n"

# #!/bin/bash
# make clean
# make bin/c_compiler
# if [[ -z "$1" ]]; then
#     COMPILER=bin/c_compiler
# else
#     COMPILER=$1
# fi
#
# mkdir -p working
#
# for DRIVER in compiler_tests/local_var/*_driver.c ; do
#     NAME=$(basename $DRIVER _driver.c)
#     TESTCODE=compiler_tests/local_var/$NAME.c
#
#     >&2 echo "Test case $NAME"
#
#     # Compile driver with normal GCC
#     mips-linux-gnu-gcc -c $DRIVER -o working/${NAME}_driver.o 2> working/${NAME}_driver.compile.stderr
#     if [[ $? -ne 0 ]]; then
#         >&2 echo "ERROR : Couldn't compile driver program using GCC."
#         continue
#     fi
#
#     # Compile test function with compiler under test to assembly
#     cat $TESTCODE | $COMPILER > working/$NAME.s  2> working/${NAME}.compile.stderr
#     if [[ $? -ne 0 ]]; then
#         >&2 echo "ERROR : Compiler returned error message."
#         continue
#     fi
#
#     # Link driver object and assembly into executable
#     mips-linux-gnu-gcc -static working/${NAME}.s working/${NAME}_driver.o -o working/${NAME}.elf 2> working/${NAME}.link.stderr
#     if [[ $? -ne 0 ]]; then
#         >&2 echo "ERROR : Linker returned error message."
#         continue
#     fi
#
#     # Run the actual executable
#     qemu-mips working/${NAME}.elf
#     if [[ $? -ne 0 ]]; then
#         >&2 echo "ERROR : Testcase returned $?, but expected 0."
#     else
# 	echo "pass"
#     fi
# done
