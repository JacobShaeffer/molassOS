#include <stddef.h>
#include <stdint.h>
#include "tty.h"
#include "gdt.h"

#if defined(__linux__)
    #error "This code must be compiled with a cross-compiler."
#elif !defined(__i386__)
    #error "This code must be compiled with an x86-elf compiler"
#endif

void kernel_main(const void* multiboot_struct, unsigned int magic)
{
	terminal_init();

	terminal_println("Welcome to molassOS.");

	struct GlobalDescriptorTable gdt;
}
