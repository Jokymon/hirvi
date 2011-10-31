@if exist test.bin del test.bin

generate_build_tag.py

"c:\Program Files\nasm\nasm.exe" -f elf k_entry.asm -o k_entry.o
@if %ERRORLEVEL% NEQ 0 goto :FaultyEnd

e:\vm-shared\i386-elf\bin\i386-elf-gcc.exe -nostdinc -fno-builtin -c i386.c -o i386.o
@if %ERRORLEVEL% NEQ 0 goto :FaultyEnd
e:\vm-shared\i386-elf\bin\i386-elf-gcc.exe -nostdinc -fno-builtin -c idt.c -o idt.o
@if %ERRORLEVEL% NEQ 0 goto :FaultyEnd
e:\vm-shared\i386-elf\bin\i386-elf-gcc.exe -nostdinc -fno-builtin -c irq.c -o irq.o
@if %ERRORLEVEL% NEQ 0 goto :FaultyEnd
e:\vm-shared\i386-elf\bin\i386-elf-gcc.exe -nostdinc -fno-builtin -c isrs.c -o isrs.o
@if %ERRORLEVEL% NEQ 0 goto :FaultyEnd
e:\vm-shared\i386-elf\bin\i386-elf-gcc.exe -nostdinc -fno-builtin -c string.c -o string.o
@if %ERRORLEVEL% NEQ 0 goto :FaultyEnd
e:\vm-shared\i386-elf\bin\i386-elf-gcc.exe -nostdinc -fno-builtin -c display.c -o display.o
@if %ERRORLEVEL% NEQ 0 goto :FaultyEnd
e:\vm-shared\i386-elf\bin\i386-elf-gcc.exe -nostdinc -fno-builtin -I. -c vsprintf.c -o vsprintf.o
@if %ERRORLEVEL% NEQ 0 goto :FaultyEnd
e:\vm-shared\i386-elf\bin\i386-elf-gcc.exe -nostdinc -fno-builtin -c kb.c -o kb.o
@if %ERRORLEVEL% NEQ 0 goto :FaultyEnd
e:\vm-shared\i386-elf\bin\i386-elf-gcc.exe -nostdinc -fno-builtin -c pci.c -o pci.o
@if %ERRORLEVEL% NEQ 0 goto :FaultyEnd
e:\vm-shared\i386-elf\bin\i386-elf-gcc.exe -nostdinc -fno-builtin -c kernel.c  -o kernel.o
@if %ERRORLEVEL% NEQ 0 goto :FaultyEnd

e:\vm-shared\i386-elf\bin\i386-elf-ld.exe -Map test.map -T kernel.ld -o test.elf k_entry.o kernel.o string.o vsprintf.o display.o kb.o i386.o idt.o irq.o isrs.o pci.o
@if %ERRORLEVEL% NEQ 0 goto :FaultyEnd

e:\vm-shared\i386-elf\bin\i386-elf-objdump.exe -d test.elf > test.lst

e:\vm-shared\i386-elf\bin\i386-elf-objcopy.exe -I elf32-i386 -O binary test.elf test.bin
@if %ERRORLEVEL% NEQ 0 goto :FaultyEnd

@goto :End

:FaultyEnd
@echo An error occured during compilation!!!

:End
