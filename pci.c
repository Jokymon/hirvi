#include "pci.h"
#include "i386.h"

#define CONFIG_DATA 0xcfc
#define CONFIG_ADDRESS 0xcf8

int pci_is_available()
{
    unsigned int temp;
    temp = inportl(CONFIG_DATA);
    return (temp==0xffffffff);
}

unsigned int pci_read_dword(unsigned char bus, unsigned char slot, unsigned char function, unsigned char reg)
{
    unsigned int address = 0x80000000; // start with ECD Bit = bit 31 set

    address |= ((unsigned int)bus << 16);
    address |= ((unsigned int)(slot & 0x1f) << 11);
    address |= ((unsigned int)(function & 0x7) << 11);
    address |= ((unsigned int)(reg & 0x3f) << 2);

    outportl(CONFIG_ADDRESS, address);
    return inportl(CONFIG_DATA);
}
