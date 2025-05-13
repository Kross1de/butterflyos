#ifndef PORT_H
#define PORT_H
unsigned char inportb(unsigned short port){
	unsigned char ret;
	asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
	return ret;
}
void outportb(unsigned short port,unsigned char value){
	asm volatile("outb %0, %1" : : "a"(value),"d"(port));
}
#endif