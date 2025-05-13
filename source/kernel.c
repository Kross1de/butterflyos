#include <stdarg.h>

void kernel_main();
void printf(const char *format, ...);
static void printChar(char *videomem, char c, char attr);
static void printString(char *videomem, const char *str, char attr);
static void printInt(char *videomem, int num, int base,  char attr);
static char *itoa(int value, char *str, int base);
static int strlen(const char *str);

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

void printf(const char *format, ...){
	char *videomem = (char *)0xb8000;
	va_list args;
	va_start(args,format);
	char attr = 0x0a;
	
	while(*format){
		if(*format!='%'){
			if(*format=='\n'){
				videomem += (80-((videomem-(char *)0xb8000)/2)%80)*2;
			}else{
				printChar(videomem,*format,attr);
				videomem+=2;
			}
			format++;
			continue;
		}
		format++;	//skip '%'
		
		switch(*format){
			case 's':{
				const char *str=va_arg(args, const char *);
				printString(videomem,str,attr);
				videomem += strlen(str)*2;
				break;
			}
			case 'c':{
				char c = (char)va_arg(args,int);
				printChar(videomem,c,attr);
				videomem+=2;
				break;
			}
			case 'd':{
				int num=va_arg(args,int);
				printInt(videomem,num,10,attr);
				char buf[12];
				itoa(num,buf,10);
				videomem += strlen(buf)*2;
				break;
			}
			case 'x':{
				int num=va_arg(args,int);
				printInt(videomem,num,16,attr);
				char buf[12];
				itoa(num,buf,10);
				videomem += strlen(buf)*2;
				break;
			}
			default:
				printChar(videomem,'%',attr);
				videomem+=2;
				printChar(videomem,*format,attr);
				videomem+=2;
				break;
		}
		format++;
	}
	va_end(args);
}

static void printChar(char *videomem,char c,char attr){
	*videomem = c;
	*(videomem+1)=attr;
}

static void printString(char *videomem,const char *str,char attr){
	while(*str){
		printChar(videomem,*str,attr);
		videomem+=2;
		str++;
	}
}

static void printInt(char *videomem,int num,int base,char attr){
	char buf[32];
	itoa(num,buf,base);
	printString(videomem,buf,attr);
}

static char *itoa(int value,char *str,int base){
	char *ptr = str;
	char *digits="0123456789abcdef";
	int isNeg=0;
	
	if(value<0&&base==10){
		isNeg=1;
		value=-value;
	}
	
	do{
		*ptr++=digits[value%base];
		value/=base;
	}while(value);
	
	if(isNeg){
		*ptr++='-';
	}
	*ptr='\0';
	//reverse the string
	char *start=str;
	char *end=ptr-1;
	while(start<end){
		char temp = *start;
		*start++ = *end;
		*end-- = temp;
	}
	
	return str;
}

static int strlen(const char *str){
	int len = 0;
	while(*str++) len++;
	return len;
}