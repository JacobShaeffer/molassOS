
#include "tty.h"
#include <stddef.h>
#include <stdint.h>

volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
const int VGA_COLS = 80;
const int VGA_ROWS = 25;

int t_col = 0;
int t_row = 0;
uint8_t t_color = 0x0F;

void terminal_init()
{
    for(int col = 0; col < VGA_COLS; col++)
    {
        for(int row = 0; row < VGA_ROWS; row++)
        {
            const size_t index = (VGA_COLS * row) + col;
            vga_buffer[index] = ((uint16_t)t_color << 8) | ' ';
        }
    }
}

void terminal_putchar(char c)
{
    switch(c)
    {
        case '\n':
        {
            t_col = 0;
            t_row ++;
            break;
        }
        default:
        {
            const size_t index = (VGA_COLS * t_row) + t_col;
            vga_buffer[index] = ((uint16_t)t_color << 8) | c;
            t_col ++;
            break;
        }
    }
       if(t_col >= VGA_COLS)
    {
        t_col = 0;
        t_row ++;
    }
    if(t_row >= VGA_ROWS)
    {
        //TODO: implement scrolling instead of looping overwrite
        t_col = 0;
        t_row = 0;
    }
}

void terminal_print(const char* str)
{
	int i = 0;
	while(str[i] != '\0')
	{
		terminal_putchar(str[i]);
		i ++;
	}
}

void terminal_println(const char* str)
{
	terminal_print(str);
	terminal_putchar("\n");
}

