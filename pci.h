#ifndef _PCI_H
#define _PCI_H

int pci_is_available();
unsigned int pci_read_dword(unsigned char bus, unsigned char slot, unsigned char function, unsigned char reg);

#endif
