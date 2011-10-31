#ifndef _IDT_H
#define _IDT_H

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
void idt_install();

#endif
