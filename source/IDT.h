#ifndef IDT_H
#define IDT_H
void setIDTgate(unsigned char num,unsigned long base,unsigned short sel,unsigned char flags);
void idtInstall();
#endif