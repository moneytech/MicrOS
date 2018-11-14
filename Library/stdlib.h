#ifndef STDLIB_H
#define STDLIB_H

#include <stdint.h>
#include "string.h"

void sleep(uint32_t ms);
int32_t atoi(const char* string);
char* itoa(int input, char* buffer, int base);

#endif