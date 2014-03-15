    .file "k_entry.S"
    .code32

    .globl start
    .extern k_main  /* this is in the c file */

.section .text

start:
  /* stop using bootloader GDT, and load new GDT */
  lgdt gdt_ptr

  movw $LINEAR_DATA_SEL, %ax
  movw %ax, %ds
  movw %ax, %es
  movw %ax, %ss
  movw %ax, %fs
  movw %ax, %gs

  /* far jump for loading cs register */
  ljmp $0x18, $new_cs
new_cs:

  call k_main

  hlt /* crash */

/* ******************************************************************** */

.section .data

gdt:
/* NULL descriptor */
	.word 0		// limit 15:0
	.word 0		// base 15:0
	.byte 0		// base 23:16
	.byte 0		// type
	.byte 0		// limit 19:16, flags
	.byte 0		// base 31:24

// unused descriptor
	.word 0
	.word 0
	.byte 0
	.byte 0
	.byte 0
	.byte 0

lin_data_sel:
    .set LINEAR_DATA_SEL, lin_data_sel - gdt
	.word 0xFFFF
	.word 0
	.byte 0
	.byte 0x92		// present, ring 0, data, expand-up, writable
	.byte 0xCF		// page-granular (4 gig limit), 32-bit
	.byte 0

lin_code_sel:
    .set LINEAR_CODE_SEL, lin_code_sel - gdt
	.word 0xFFFF
	.word 0
	.byte 0
	.byte 0x9A		// present,ring 0,code,non-conforming,readable
	.byte 0xCF		// page-granular (4 gig limit), 32-bit
	.byte 0
gdt_end:

gdt_ptr:
	.word gdt_end - gdt - 1
	.long gdt

/* ***************************************************************** */
// ISR assembly functions

.section .text

// In just a few pages in this tutorial, we will add our Interrupt
// Service Routines (ISRs) right here!
    .globl isr0
    .globl isr1
    .globl isr2
    .globl isr3
    .globl isr4
    .globl isr5
    .globl isr6
    .globl isr7
    .globl isr8
    .globl isr9
    .globl isr10
    .globl isr11
    .globl isr12
    .globl isr13
    .globl isr14
    .globl isr15
    .globl isr16
    .globl isr17
    .globl isr18
    .globl isr19
    .globl isr20
    .globl isr21
    .globl isr22
    .globl isr23
    .globl isr24
    .globl isr25
    .globl isr26
    .globl isr27
    .globl isr28
    .globl isr29
    .globl isr30
    .globl isr31

//  0: Divide By Zero Exception
isr0:
    cli
    push $0
    push $0
    jmp isr_common_stub

//  1: Debug Exception
isr1:
    cli
    push $0
    push $1
    jmp isr_common_stub

//  2: Non Maskable Interrupt Exception
isr2:
    cli
    push $0
    push $2
    jmp isr_common_stub

//  3: Int 3 Exception
isr3:
    cli
    push $0
    push $3
    jmp isr_common_stub

//  4: INTO Exception
isr4:
    cli
    push $0
    push $4
    jmp isr_common_stub

//  5: Out of Bounds Exception
isr5:
    cli
    push $0
    push $5
    jmp isr_common_stub

//  6: Invalid Opcode Exception
isr6:
    cli
    push $0
    push $6
    jmp isr_common_stub

//  7: Coprocessor Not Available Exception
isr7:
    cli
    push $0
    push $7
    jmp isr_common_stub

//  8: Double Fault Exception (With Error Code!)
isr8:
    cli
    push $8
    jmp isr_common_stub

//  9: Coprocessor Segment Overrun Exception
isr9:
    cli
    push $0
    push $9
    jmp isr_common_stub

// 10: Bad TSS Exception (With Error Code!)
isr10:
    cli
    push $10
    jmp isr_common_stub

// 11: Segment Not Present Exception (With Error Code!)
isr11:
    cli
    push $11
    jmp isr_common_stub

// 12: Stack Fault Exception (With Error Code!)
isr12:
    cli
    push $12
    jmp isr_common_stub

// 13: General Protection Fault Exception (With Error Code!)
isr13:
    cli
    push $13
    jmp isr_common_stub

// 14: Page Fault Exception (With Error Code!)
isr14:
    cli
    push $14
    jmp isr_common_stub

// 15: Reserved Exception
isr15:
    cli
    push $0
    push $15
    jmp isr_common_stub

// 16: Floating Point Exception
isr16:
    cli
    push $0
    push $16
    jmp isr_common_stub

// 17: Alignment Check Exception
isr17:
    cli
    push $0
    push $17
    jmp isr_common_stub

// 18: Machine Check Exception
isr18:
    cli
    push $0
    push $18
    jmp isr_common_stub

// 19: Reserved
isr19:
    cli
    push $0
    push $19
    jmp isr_common_stub

// 20: Reserved
isr20:
    cli
    push $0
    push $20
    jmp isr_common_stub

// 21: Reserved
isr21:
    cli
    push $0
    push $21
    jmp isr_common_stub

// 22: Reserved
isr22:
    cli
    push $0
    push $22
    jmp isr_common_stub

// 23: Reserved
isr23:
    cli
    push $0
    push $23
    jmp isr_common_stub

// 24: Reserved
isr24:
    cli
    push $0
    push $24
    jmp isr_common_stub

// 25: Reserved
isr25:
    cli
    push $0
    push $25
    jmp isr_common_stub

// 26: Reserved
isr26:
    cli
    push $0
    push $26
    jmp isr_common_stub

// 27: Reserved
isr27:
    cli
    push $0
    push $27
    jmp isr_common_stub

// 28: Reserved
isr28:
    cli
    push $0
    push $28
    jmp isr_common_stub

// 29: Reserved
isr29:
    cli
    push $0
    push $29
    jmp isr_common_stub

// 30: Reserved
isr30:
    cli
    push $0
    push $30
    jmp isr_common_stub

// 31: Reserved
isr31:
    cli
    push $0
    push $31
    jmp isr_common_stub


// We call a C function in here. We need to let the assembler know
// that 'fault_handler' exists in another file
    .extern fault_handler

// This is our common ISR stub. It saves the processor state, sets
// up for kernel mode segments, calls the C-level fault handler,
// and finally restores the stack frame.
isr_common_stub:
    pusha
    push %ds
    push %es
    push %fs
    push %gs
    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movl %esp, %eax
    push %eax
    movl $fault_handler, %eax
    call *%eax
    pop %eax
    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa
    add $8, %esp
    iret

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IRQ assembly functions

.globl irq0
.globl irq1
.globl irq2
.globl irq3
.globl irq4
.globl irq5
.globl irq6
.globl irq7
.globl irq8
.globl irq9
.globl irq10
.globl irq11
.globl irq12
.globl irq13
.globl irq14
.globl irq15

// 32: IRQ0
irq0:
    cli
    push $0
    push $32
    jmp irq_common_stub

// 33: IRQ1
irq1:
    cli
    push $0
    push $33
    jmp irq_common_stub

// 34: IRQ2
irq2:
    cli
    push $0
    push $34
    jmp irq_common_stub

// 35: IRQ3
irq3:
    cli
    push $0
    push $35
    jmp irq_common_stub

// 36: IRQ4
irq4:
    cli
    push $0
    push $36
    jmp irq_common_stub

// 37: IRQ5
irq5:
    cli
    push $0
    push $37
    jmp irq_common_stub

// 38: IRQ6
irq6:
    cli
    push $0
    push $38
    jmp irq_common_stub

// 39: IRQ7
irq7:
    cli
    push $0
    push $39
    jmp irq_common_stub

// 40: IRQ8
irq8:
    cli
    push $0
    push $40
    jmp irq_common_stub

// 41: IRQ9
irq9:
    cli
    push $0
    push $41
    jmp irq_common_stub

// 42: IRQ10
irq10:
    cli
    push $0
    push $42
    jmp irq_common_stub

// 43: IRQ11
irq11:
    cli
    push $0
    push $43
    jmp irq_common_stub

// 44: IRQ12
irq12:
    cli
    push $0
    push $44
    jmp irq_common_stub

// 45: IRQ13
irq13:
    cli
    push $0
    push $45
    jmp irq_common_stub

// 46: IRQ14
irq14:
    cli
    push $0
    push $46
    jmp irq_common_stub

// 47: IRQ15
irq15:
    cli
    push $0
    push $47
    jmp irq_common_stub

    .extern irq_handler

irq_common_stub:
    pusha
    push %ds
    push %es
    push %fs
    push %gs

    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movl %esp, %eax

    pushl %eax
    movl $irq_handler, %eax
    call *%eax
    pop %eax

    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa
    add $8, %esp
    iret


