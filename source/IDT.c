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