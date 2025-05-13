#include "printf.h"
void kernel_main();
void kernel_main(){
	char *videomem = (char *)0xb8000;
	const char *msg = "hello, world";
	//this loop will clear screen
	for(int i=0;i<80*25*2;i+=2){
		videomem[i]=' ';
		videomem[i+1]=0x0a;
	}
	printf("Message: %s, Number: %d, Hex: %x, Char: %c\n", msg, 42, 0x2a, 'A');

	while(1) {}
}