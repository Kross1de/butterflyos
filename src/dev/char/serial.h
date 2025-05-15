#pragma once

#include <types.h>
#include <lib/printf.h>
#include <sys/io.h>

void serialInit();
void dprintf(const char* fmt,...);
char serialReadChar();
