#include <cpu/GDT.h>
#include <dev/char/serial.h>

gdtTable gdt = {
      {
            //null segment
            0x0000000000000000,
            //16bit
            0x00009a000000ffff,
            0x000093000000ffff,
            //32bit
            0x00cf9a000000ffff,
            0x00cf93000000ffff,
            //64bit 
            0x00af9b000000ffff,
            0x00af93000000ffff,
            //64bit user mode
            0x00affb000000ffff,
            0x00aff3000000ffff
      }
};

gdtr gdt_descriptor;

void gdtInstall(){
      gdt_descriptor = (gdtr) {
            .size = (sizeof(u64) * 9) - 1,
                  .offset = (u64)&gdt 
      };

      asm volatile ("lgdt %0" :: "m"(gdt) : "memory");
      dprintf("GDT: GDT initialized!\n");
}
