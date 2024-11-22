# Run in Assembly
echo "Running calculator in Assembly"
nasm -f elf32 calculator.asm -o calculator.o
ld -m elf_i386 calculator.o -o asm_calculator
./asm_calculator

echo -e "\n"

# Run in C
echo "Running calculator in C"
gcc -o c_calculator calculator.c
./c_calculator

# The assembly version will consume less memory compared to the C version, 
# due to the lack of dependencies on external libraries and the fine-grained control over hardware resources.






