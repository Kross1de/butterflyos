#include "printf.h"
struct __attribute__((packed)) idtEntry{
	unsigned short baseLOW;
	unsigned short sel;
	unsigned char always0;
	unsigned char flags;
	unsigned short baseHIGH;
};
struct __attribute__((packed)) idtPTR{
	unsigned short limit;
	unsigned int base;
};
//IDT array
struct idtEntry idt[256];
struct idtPTR idtp;

void setIDTgate(unsigned char num,unsigned long base,unsigned short sel,unsigned char flags){
	idt[num].baseLOW = base & 0xFFFF;
	idt[num].baseHIGH = (base >> 16) & 0xFFFF;
	idt[num].sel = sel;
	idt[num].always0 = 0;
	idt[num].flags=flags;
}

void idtInstall(){
	idtp.limit = (sizeof(struct idtEntry) * 256) - 1;
	idtp.base = (unsigned int)&idt;
	asm volatile("lidt %0" : : "m"(idtp));
	printf("IDT is done!\n");
}

void initInterrupts(){
	setIDTgate(0,(unsigned long)isr0,0x08,0x8E);
	setIDTgate(1,(unsigned long)isr1,0x08,0x8E);
	setIDTgate(32,(unsigned long)isr32,0x08,0x8E);
	setIDTgate(33,(unsigned long)isr33,0x08,0x8E);
	asm volatile("sti");
}

void isr0(){
	printf("Divide-by-zero!\n");
	asm volatile("cli; hlt");
}
void isr1(){
	printf("Debug exception!\n");
	asm volatile("cli; hlt");
}

void isr32(){
	printf("Timer interrupt!\n");
	asm volatile("outb %0, %1" : : "a"((char)0x20), "Nd"((short)0x20));
}

void isr33(){
	printf("Keyboard interrupt!\n");
	asm volatile("outb %0, %1" : : "a"((char)0x20), "Nd"((short)0x20));
}