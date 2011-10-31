Playground for developing an operating system that should be based on Python as
much as possible. The inspiration are systems like JNode.

The build process was split into two stages, first building an ELF file and
then converting this to a BIN file using objcopy. This is due to an issue when
doing it directly as discussed here:
http://forum.osdev.org/viewtopic.php?f=1&t=22547, a OSDev forum entry called
"Strange 'undefined reference to ...' linker error".

Many of the basic sources for this kernel are copied from Bran's Kernel
Development Tutorial on this URL: http://www.osdever.net/bkerndev/Docs/

The currently used hard disk image can be converted into a VDI file that is
bootable by Sun VirtualBox using the following command:

C:\Users\Silvan Wegmann\.VirtualBox\Machines\MyOs>"c:\Program Files\sun\VirtualBox\VBoxManage.exe" convertfromraw -format VDI c50m.img c50m.vdi

The vsprintf implementation was copied from LittleOS.
The strlen implementation was copied from http://en.wikipedia.org/wiki/Strlen

TODO: Describe how to create a bootable hard disk using only windows tools

Paging
======
http://wiki.osdev.org/Setting_Up_Paging
http://www.jamesmolloy.co.uk/tutorial_html/6.-Paging.html

Interrupts & Exceptions handling
================================

http://wiki.osdev.org/I_Cant_Get_Interrupts_Working
http://www.osdever.net/tutorials/view/interrupts-exceptions-and-idts-part-3-idts

Programming the NE2000
======================

http://wiki.osdev.org/Ne2000
http://www.national.com/opf/DP/DP8390D.html#Documents
http://www.osdever.net/documents/WritingDriversForTheDP8390.pdf?the_id=56

Info on PCI programming
=======================

http://wiki.osdev.org/PCI
http://www.waste.org/~winkles/hardware/pci.htm

Additional links
================

http://www.osdever.net/papers/index
http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html
http://www.brackeen.com/vga/
