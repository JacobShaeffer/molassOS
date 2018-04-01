#ifndef __TTY_H
#define __TTY_H

#include <stddef.h>

void terminal_init(void);
void terminal_putchar(char c);
void terminal_print(const char* str);
void terminal_println(const char* str);

#endif
