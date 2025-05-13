#!/bin/bash
# mkdir -p binaries/ iso/boot/grub
mkdir -p binaries/ iso/boot/grub

cat > iso/boot/grub/grub.cfg << EOF
set timeout=5
set default=0

menuentry "ButterflyOS" {
    multiboot /boot/kernel.bin
    boot
}
EOF
echo '#include <stdarg.h>' > qq.c
echo '#include <stdint.h>' >> qq.c
echo '#include "source/IDT.h"' >> qq.c
sed -n '/^#define PRINTF_H/,/^#endif/{/^#define PRINTF_H/b; /^#endif/b; p}' source/printf.h >> qq.c
for file in source/*.c; do
    sed '/^#include /d' "$file" >> qq.c
done
nasm -f elf32 source/bootloader.asm -o binaries/bootloader.o
gcc -m32 -ffreestanding -fno-stack-protector -c qq.c -o binaries/qq.o
ld -m elf_i386 -o iso/boot/kernel.bin -T source/linker.ld binaries/bootloader.o binaries/qq.o
grub-mkrescue -o kernel.iso iso/
qemu-system-i386 -cdrom kernel.iso
rm -rf kernel.iso iso/ binaries/ qq.c