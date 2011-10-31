#ifndef _DISPLAY_H
#define _DISPLAY_H

#define WHITE_TXT 0x7
#define BLUE_TXT 0x09

void k_clear_screen();
void k_putch(char ch);
unsigned int k_puts(char *message);
void k_update_cursor();

#endif
