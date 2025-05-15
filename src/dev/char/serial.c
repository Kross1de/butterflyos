#include <dev/char/serial.h>

#define COM1 0x3f8

void serialInit(){
      outb(COM1 + 1,0x00);
      outb(COM1 + 3,0x80);
      outb(COM1 + 0,0x03);
      outb(COM1 + 1,0x00);
      outb(COM1 + 3,0x03);
      outb(COM1 + 2,0xc7);
      outb(COM1 + 4,0x0b);
}

void serial_write_char(char c,void* extra){
      (void)extra;
      while((inb(COM1 + 5)&0x20) == 0);
      outb(COM1,c);
}

char serialReadChar(){
      while((inb(COM1 + 5)&0x01)==0);
      return inb(COM1);
}

void dprintf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vfctprintf(serial_write_char, NULL, format, args);
    va_end(args);

    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}
