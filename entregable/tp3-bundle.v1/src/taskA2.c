/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "syscall.h" 

void handler(void);

void task() {
    char* message = "Hable mas fuerte";
    syscall_talk(message);
    syscall_setHandler(handler);

    // Descomentar para que la tarea muera, y se pueda ver la pantalla de debug
    // char* p = (char*) 0; *p = 0; 

    while(1) { __asm __volatile("mov $2, %%eax":::"eax"); }
}

void handler() {
    syscall_informAction(Up);
}
