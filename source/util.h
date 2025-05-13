#ifndef UTIL_H
#define UTIL_H
void memset(void *dest,char val,uint32_t count);
struct InterruptRegisters{
	uint32_t cr2;
	uint32_t ds;
	uint32_t edi,esi,ebp,esp,ebx,edx,ecx,eax;
	uint32_t int_no,err_code;
	uint32_t eip,csm,eflags,useresp,ss;
};
#endif