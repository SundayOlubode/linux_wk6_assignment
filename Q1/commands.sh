## Static Library ##
gcc -c string_manipulator.c -o string_manipulator.o
ar rcs libstringmanipulator.a string_manipulator.o
gcc test.c -L. -lstringmanipulator -o test1
echo "Executing test1 with static library"
./test1

echo -e "\n"

## Dynamic Library ##
gcc -fPIC -c -o string_manipulator.o string_manipulator.c
gcc -shared -o libstringmanipulator.so string_manipulator.o
gcc -o test2 test.c -L. -lstringmanipulator
export LD_LIBRARY_PATH=$(pwd):$LD_LIBRARY_PATH
echo "Executing test2 with dynamic library"
./test2

echo -e "\n"

## ELF Files ##
echo "ELF Files are: libstringmanipulator.so, string_manipulator.o, test1, test2"
readelf -h libstringmanipulator.so
readelf -h string_manipulator.o
readelf -h test1
readelf -h test2

## Clean Up ##
rm libstringmanipulator.a libstringmanipulator.so string_manipulator.o test1 test2