## Shared Library ##
gcc -c string_manipulator.c -o string_manipulator.o
ar rcs libstringmanipulator.a string_manipulator.o
gcc test.c -L. -lstringmanipulator -o test1
./test1

## Dynamic Library ##
gcc -fPIC -c -o string_manipulator.o string_manipulator.c
gcc -shared -o libstringmanipulator.so string_manipulator.o
gcc -o test2 test.c -L. -lstringmanipulator
export LD_LIBRARY_PATH=/home/samuel/ALU/linux_wk6_assignment/:$LD_LIBRARY_PATH
./test2

## ELF Files ##
readelf -h libstringmanipulator.so
readelf -h string_manipulator.o
readelf -h test1
readelf -h test2