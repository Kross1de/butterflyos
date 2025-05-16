#pragma once

#include <types.h>

#define PAGE_SIZE 4096
#define divCeiling(x,y)(x+(y-1))/y
#define alignUp(x,y)divCeiling(x,y)*y
#define alignDown(x,y)(x/y)*y

void pmm_init();
