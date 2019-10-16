/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de las rutinas de atencion de interrupciones
*/

#include "defines.h"
#include "idt.h"
#include "isr.h"
#include "tss.h"

#define GDT_CODE_0 14<<3

// P | DPL | 0 D 1 1 0 | 0 0 0
#define IDT_ENTRY_ATTR_KERNEL  0b1000111000000000
#define IDT_ENTRY_ATTR_PEASANT 0b1110111000000000


idt_entry idt[255] = { };

idt_descriptor IDT_DESC = {
    sizeof(idt) - 1,
    (uint32_t) &idt
};

/*
    La siguiente es una macro de EJEMPLO para ayudar a armar entradas de
    interrupciones. Para usar, descomentar y completar CORRECTAMENTE los
    atributos y el registro de segmento. Invocarla desde idt_inicializar() de
    la siguiene manera:

    void idt_inicializar() {
        IDT_ENTRY(0);
        ...
        IDT_ENTRY(19);
        ...
    }
*/


#define IDT_ENTRY(numero, attrVal)                                                                  \
    idt[numero].offset_0_15 = (uint16_t) ((uint32_t)(&_isr ## numero) & (uint32_t) 0xFFFF);         \
    idt[numero].segsel = (uint16_t) GDT_CODE_0;                                                     \
    idt[numero].attr = (uint16_t) attrVal;                                                          \
    idt[numero].offset_16_31 = (uint16_t) ((uint32_t)(&_isr ## numero) >> 16 & (uint32_t) 0xFFFF);


void idt_init() {
    // Excepciones
    IDT_ENTRY( 0, IDT_ENTRY_ATTR_KERNEL)    // Divide-by-zero Error
    IDT_ENTRY( 1, IDT_ENTRY_ATTR_KERNEL)    // Debug   
    IDT_ENTRY( 2, IDT_ENTRY_ATTR_KERNEL)    // Non-maskable Interrupt
    IDT_ENTRY( 3, IDT_ENTRY_ATTR_KERNEL)    // Breakpoint
    IDT_ENTRY( 4, IDT_ENTRY_ATTR_KERNEL)    // Overflow
    IDT_ENTRY( 5, IDT_ENTRY_ATTR_KERNEL)    // Bound Range Exceeded
    IDT_ENTRY( 6, IDT_ENTRY_ATTR_KERNEL)    // Invalid Opcode
    IDT_ENTRY( 7, IDT_ENTRY_ATTR_KERNEL)    // Device Not Available
    IDT_ENTRY( 8, IDT_ENTRY_ATTR_KERNEL)    // Double Fault
    IDT_ENTRY( 9, IDT_ENTRY_ATTR_KERNEL)    // Coprocessor Segment Overrun
    IDT_ENTRY(10, IDT_ENTRY_ATTR_KERNEL)    // Invalid TSS
    IDT_ENTRY(11, IDT_ENTRY_ATTR_KERNEL)    // Segment Not Present
    IDT_ENTRY(12, IDT_ENTRY_ATTR_KERNEL)    // Stack-Segment Fault
    IDT_ENTRY(13, IDT_ENTRY_ATTR_KERNEL)    // General Protection Fault
    IDT_ENTRY(14, IDT_ENTRY_ATTR_KERNEL)    // Page Fault
    IDT_ENTRY(16, IDT_ENTRY_ATTR_KERNEL)    // x87 Floating-Point Exception
    IDT_ENTRY(17, IDT_ENTRY_ATTR_KERNEL)    // Alignment Check
    IDT_ENTRY(18, IDT_ENTRY_ATTR_KERNEL)    // Machine Check
    IDT_ENTRY(19, IDT_ENTRY_ATTR_KERNEL)    // SIMD Floating-Point Exception
    IDT_ENTRY(20, IDT_ENTRY_ATTR_KERNEL)    // Virtualization Exception
    IDT_ENTRY(30, IDT_ENTRY_ATTR_KERNEL)    // Security Exception

    // Nuestro
    IDT_ENTRY(32, IDT_ENTRY_ATTR_KERNEL)    // Clock
    IDT_ENTRY(33, IDT_ENTRY_ATTR_KERNEL)    // Teclado

    IDT_ENTRY(47, IDT_ENTRY_ATTR_PEASANT)    // Syscall
}
