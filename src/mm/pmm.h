#pragma once

#include <types.h>
#include <kernel.h>

#define PAGE_SIZE 4096
#define divCeiling(x,y)(x+(y-1))/y
#define alignUp(x,y)divCeiling(x,y)*y
#define alignDown(x,y)(x/y)*y
#define higherHalf(ptr) ((void*)((u64)ptr)+hhdm_offset)
#define physical(ptr) ((void*)((u64)ptr)-hhdm_offset)

void pmm_init();
