#ifndef GDT_H
#define GDT_H

#define GDT_SIZE 5

#include <stdbool.h>
#include "gdt_entry.h"
#include "gdt_info.h"

void gdt_init();
void gdt_fill_entry(int index, bool executable, uint8_t privilege_level);

#endif