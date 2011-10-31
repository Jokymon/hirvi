#ifndef _I386_H
#define _I386_H

/* This defines what the stack looks like after an ISR was running */
struct regs
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;    
};

//-----------------------------------------------------------------------

void *memset(void *dest, char val, unsigned int count);

void outportb(unsigned int port,unsigned char value);  // Output a byte to a port
unsigned char inportb (unsigned short _port);
void outportl(unsigned int port,unsigned int value);  // Output a dword to a port
unsigned int inportl (unsigned short _port);

void init_pics(int pic1, int pic2);

#endif
