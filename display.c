#include "k_defines.h"
#include "stdarg.h"
#include "i386.h"
#include "display.h"

static int cursor_x, cursor_y;

void k_clear_screen() // clear the entire text screen
{
	unsigned short *vidmem = (unsigned short *) 0xb8000;
	unsigned int i=0;
	while( i<(80*25) )
	{
		vidmem[i] = ' ' + (WHITE_TXT<<8);
		i++;
	}
    cursor_x = 0;
    cursor_y = 0;
}

void k_putch(char ch)
{
    /* Handle a backspace, by moving the cursor back one space */
    if(ch == 0x08)
    {
        if(cursor_x != 0) cursor_x--;
    }
    /* Handles a tab by incrementing the cursor's x, but only
    *  to a point that will make it divisible by 8 */
    else if(ch == 0x09)
    {
        cursor_x = (cursor_x + 8) & ~(8 - 1);
    }
    /* Handles a 'Carriage Return', which simply brings the
    *  cursor back to the margin */
    else if(ch == '\r')
    {
        cursor_x = 0;
    }
    /* We handle our newlines the way DOS and the BIOS do: we
    *  treat it as if a 'CR' was also there, so we bring the
    *  cursor to the margin and we increment the 'y' value */
    else if(ch == '\n')
    {
        cursor_x = 0;
        cursor_y++;
    }
    /* Any character greater than and including a space, is a
    *  printable character. The equation for finding the index
    *  in a linear chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    else if(ch >= ' ')
    {
        unsigned short *vidmem = (unsigned short *) 0xb8000;
        vidmem[ cursor_y * 80 + cursor_x ] = ch | (WHITE_TXT<<8);
        cursor_x++;
    }

    /* If the cursor has reached the edge of the screen's width, we
    *  insert a new line in there */
    if(cursor_x >= 80)
    {
        cursor_x = 0;
        cursor_y++;
    }

    /* Scroll the screen if needed, and finally move the cursor */
    //scroll();
    k_update_cursor();
}

unsigned int k_puts(char *message)
{
    //unsigned int i;
    while (*message != '\0')
    {
        k_putch(*message);
        *message++;
    }
	return(1);
}

static char buf[512];

int printk(const char *fmt, ...)
{
    va_list args;
    int i;
    
    va_start(args, fmt);
    i = vsprintf(buf, fmt, args);
    va_end(args);
    
    k_puts(buf);
    return i;
}

void k_print_int_hex(unsigned int value)
{
    unsigned char i;
    for (i=8; i>0; i--)
    {
        char ch = (value >> ((i-1)*4)) & 0xf;
        if (ch < 10)
            k_putch(ch+'0');
        else
            k_putch(ch-10+'A');
    }
}

/* by DF */
void k_update_cursor()
{
	USHORT	position=(cursor_y*80) + cursor_x;
	// cursor LOW port to vga INDEX register
	outportb(0x3D4, 0x0F);
	outportb(0x3D5, (UCHAR)(position&0xFF));
	// cursor HIGH port to vga INDEX register
	outportb(0x3D4, 0x0E);
	outportb(0x3D5, (UCHAR)((position>>8)&0xFF));
}


