#ifndef IDT_H
#define IDT_H
void setIDTgate(unsigned char num,unsigned long base,unsigned short sel,unsigned char flags);
void idtInstall();
void initInterrupts();
void isr0();
void isr1();
void isr32();
void isr33();
#endif