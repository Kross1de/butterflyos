void kernel_main(){
	char *videomem = (char *)0xb8000;
	const char *msg = "hello, world";
	//this loop will clear screen
	for(int i=0;i<80*25*2;i+=2){
		videomem[i]=' ';
		videomem[i+1]=0x0a;
	}
	//this loop will print message
	while(*msg){
		*videomem = *msg;
		*(videomem + 1) = 0x0a;
		videomem += 2;
		msg++;
	}

	while(1) {}
}