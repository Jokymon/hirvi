#include "i386.h"

#define PIC1 0x20
#define PIC2 0xA0

#define ICW1 0x11
#define ICW4 0x01

void outportb(unsigned int port,unsigned char value)
{
    asm volatile ("outb %%al,%%dx"::"d" (port), "a" (value));
}

unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    asm volatile ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportl(unsigned int port,unsigned int value)
{
    asm volatile ("outl %%eax,%%dx"::"d" (port), "a" (value));
}

unsigned int inportl (unsigned short _port)
{
    unsigned int rv;
    asm volatile ("inl %1, %0" : "=a" (rv) : "d" (_port));
    return rv;
}

void *memset(void *dest, char val, unsigned int count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

void init_pics(int pic1, int pic2)
{
    /* send ICW1 */
    outportb(PIC1, ICW1);
    outportb(PIC2, ICW1);
    
    /* send ICW2 */
    outportb(PIC1 + 1, pic1);	/* remap */
    outportb(PIC2 + 1, pic2);	/*  pics */
    
    /* send ICW3 */
    outportb(PIC1 + 1, 4);	/* IRQ2 -> connection to slave */
    outportb(PIC2 + 1, 2);
    
    /* send ICW4 */
    outportb(PIC1 + 1, ICW4);
    outportb(PIC2 + 1, ICW4);
    
    /* disable all IRQs */
    outportb(PIC1 + 1, 0xFF);
}

