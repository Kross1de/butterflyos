#!/bin/bash
mkdir binaries/
nasm -f elf32 source/bootloader.asm -o binaries/bootloader.o
gcc -m32 -ffreestanding -c source/kernel.c -o binaries/kernel.o
ld -m elf_i386 -o kernel.bin -T source/linker.ld binaries/bootloader.o binaries/kernel.o
qemu-system-i386 -kernel kernel.bin
rm -rf kernel.bin binaries/