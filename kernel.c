#include "k_defines.h"
#include "build_tag.h"
#include "idt.h"
#include "display.h"
#include "kb.h"
#include "pci.h"

unsigned int panic(char *message);

k_main() // like main
{
	k_clear_screen();

	k_puts("Welcome to MoOS version 0.1 (" BUILDTAG ")\n");
    k_puts("\n");
    if (pci_is_available())
    {
	    k_puts(" Detected a PCI bus\n");
    } else
    {
	    k_puts(" No PCI bus detected\n");
    }
    // Try to find PCI devices
    unsigned int i, j, k;
    for (i=0; i<256; i++)
    {
        for (j=0; j<32; j++)
        {
            for (k=0; k<8; k++)
            {
                unsigned int temp = pci_read_dword(i, j, k, 0);
                if ((temp & 0xffff) != 0xffff)
                {
                    printk("PCI device on bus: %u, slot: %u, function: %u VendorId/DeviceId: %x\n", i, j, k, temp);
                }
            }
        }
    }

// NE2000 code

#define NS_DATAPORT		0x10	/* NatSemi-defined port window offset. */
#define NE_DATAPORT		0x10	/* NatSemi-defined port window offset. */
#define NS_RESET		0x1f	/* Issue a read to reset, a write to clear. */

#define E8390_CMD		0x00	/* The command register (for all pages) */
#define E8390_STOP		0x01	/* Stop and reset the chip */
#define E8390_START		0x02	/* Start the chip, clear reset */
#define E8390_RREAD		0x08	/* Remote read */
#define E8390_NODMA		0x20	/* Remote DMA */
#define E8390_PAGE0		0x00	/* Select page chip registers */
#define E8390_PAGE1		0x40	/* using the two high-order bits */
#define E8390_PAGE2		0x80
#define E8390_PAGE3		0xC0	/* Page 3 is invalid on the real 8390. */

#define E8390_RXOFF 0x20		/* EN0_RXCR: Accept no packets */
#define E8390_TXOFF 0x02		/* EN0_TXCR: Transmitter off */

/* Page 0 register offsets. */
#define EN0_CLDALO		0x01	/* Low byte of current local dma addr  RD */
#define EN0_STARTPG		0x01	/* Starting page of ring bfr WR */
#define EN0_CLDAHI		0x02	/* High byte of current local dma addr	RD */
#define EN0_STOPPG		0x02	/* Ending page +1 of ring bfr WR */
#define EN0_BOUNDARY	0x03	/* Boundary page of ring bfr RD WR */
#define EN0_TSR			0x04	/* Transmit status reg RD */
#define EN0_TPSR		0x04	/* Transmit starting page WR */
#define EN0_NCR			0x05	/* Number of collision reg RD */
#define EN0_TCNTLO		0x05	/* Low	byte of tx byte count WR */
#define EN0_FIFO		0x06	/* FIFO RD */
#define EN0_TCNTHI		0x06	/* High byte of tx byte count WR */
#define EN0_ISR			0x07	/* Interrupt status reg RD WR */
#define EN0_CRDALO		0x08	/* low byte of current remote dma address RD */
#define EN0_RSARLO		0x08	/* Remote start address reg 0 */
#define EN0_CRDAHI		0x09	/* high byte, current remote dma address RD */
#define EN0_RSARHI		0x09	/* Remote start address reg 1 */
#define EN0_RCNTLO		0x0a	/* Remote byte count reg WR */
#define EN0_RCNTHI		0x0b	/* Remote byte count reg WR */
#define EN0_RSR			0x0c	/* rx status reg RD */
#define EN0_RXCR		0x0c	/* RX configuration reg WR */
#define EN0_TXCR		0x0d	/* TX configuration reg WR */
#define EN0_COUNTER0	0x0d	/* Rcv alignment error counter RD */
#define EN0_DCFG		0x0e	/* Data configuration reg WR */
#define EN0_COUNTER1	0x0e	/* Rcv CRC error counter RD */
#define EN0_IMR			0x0f	/* Interrupt mask reg WR */
#define EN0_COUNTER2	0x0f	/* Rcv missed frame error counter RD */

	unsigned char SA_prom[32];

	struct {char value, offset; } program_seq[] = {
		{E8390_NODMA+E8390_PAGE0+E8390_STOP, E8390_CMD}, /* Select page 0*/
		{0x48,	EN0_DCFG},		/* Set byte-wide (0x48) access. */
		{0x00,	EN0_RCNTLO},	/* Clear the count regs. */
		{0x00,	EN0_RCNTHI},
		{0x00,	EN0_IMR},		/* Mask completion irq. */
		{0xFF,	EN0_ISR},
		{E8390_RXOFF, EN0_RXCR},		/* 0x20	 Set to monitor */
		{E8390_TXOFF, EN0_TXCR},		/* 0x02	 and loopback mode. */
		{32,			EN0_RCNTLO},
		{0x00,	EN0_RCNTHI},
		{0x00,	EN0_RSARLO},	/* DMA starting at 0x0000. */
		{0x00,	EN0_RSARHI},
		{E8390_RREAD+E8390_START, E8390_CMD},
	};

	int wordlength = 2;

	/* Read the 16 bytes of station address prom, returning 1 for
	   an eight-bit interface and 2 for a 16-bit interface.
	   We must first initialize registers, similar to NS8390_init(eifdev, 0).
	   We can't reliably read the SAPROM address without this.
	   (I learned the hard way!). */
	for (i = 0; i < sizeof(program_seq)/sizeof(program_seq[0]); i++)
		outportb(0x300 + program_seq[i].offset, program_seq[i].value);

	for(i = 0; i < 32 /*sizeof(SA_prom)*/; i+=2) {
		SA_prom[i] = inportb(0x300 + NE_DATAPORT);
		SA_prom[i+1] = inportb(0x300 + NE_DATAPORT);
		if (SA_prom[i] != SA_prom[i+1])
			wordlength = 1;
	}

	printk("Station Address PROM    0:");
	for(i = 0; i < sizeof(SA_prom)/2; i++)
		printk(" %2.2x", SA_prom[i]);
	printk("\nStation Address PROM %#2x:", i);
	for(; i < sizeof(SA_prom); i++)
		printk(" %2.2x", SA_prom[i]);
	printk("\n");

    printk("NE200 wordlength = %u\n", wordlength);

	if (wordlength == 2) {
		/* We must set the 8390 for word mode, AND RESET IT. */
		int tmp;
		outportb(0x300 + EN0_DCFG, 0x49);
		tmp = inportb(0x300 + NS_RESET);
		outportb(0x300 + NS_RESET, tmp);
		/* Un-double the SA_prom values. */
		for (i = 0; i < 16; i++)
			SA_prom[i] = SA_prom[i+i];
	}
    // Check for NE2000 on I/O address 0x300
    printk("MAC of NE2000 @0x300: ");

    outportb(0x300 + E8390_CMD, E8390_NODMA + E8390_PAGE1);
    for (i = 1; i < 6; i++)
        printk("%2X:", inportb(0x300 + i));
    printk("%2X\n");

// End of NE2000 code

    init_pics(0x20, 0x28);

    idt_install();
    isrs_install();
    irq_install();
    keyboard_install();

    asm volatile ("sti");

    for(;;);
}

/* ==============  */

unsigned int panic(char *message) // just a modified version of k_puts
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;
	unsigned int line=0;

	i=(line*80*2);

	while(*message!=0) // 24h
	{
		if(*message==0x2F)
		{
			*message++;
			if(*message==0x6e)
			{
				line++;
				i=(line*80*2);
				*message++;
				if(*message==0)
				{
					return(1);
				};
			};
		};
		vidmem[i]=*message;
		*message++;
		i++;
		vidmem[i]=0x9; // use blue text
		i++;
	};
	return(1);
}
