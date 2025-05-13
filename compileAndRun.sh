#!/bin/bash
mkdir binaries/

echo '#include <stdarg.h>' > qq.c

sed -n '/^#define PRINTF_H/,/^#endif/{/^#define PRINTF_H/b; /^#endif/b; p}' source/printf.h >> qq.c

for file in source/*.c; do
    sed '/^#include /d' "$file" >> qq.c
done

nasm -f elf32 source/bootloader.asm -o binaries/bootloader.o
gcc -m32 -ffreestanding -fno-stack-protector -c qq.c -o binaries/qq.o
ld -m elf_i386 -o kernel.bin -T source/linker.ld binaries/bootloader.o binaries/qq.o
qemu-system-i386 -kernel kernel.bin
rm -rf kernel.bin binaries/