section .multiboot
align 4
dd 0x1badb002 ;magic number
dd 0x00 ;flags
dd - (0x1badb002 + 0x00)  ;checksum

section .text
global start
start:
	extern kernel_main
	call kernel_main
	cli
	hlt