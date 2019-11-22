/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "syscall.h" 

void handler(void);

void task() {
    char* message = "Tarea B1";
    syscall_talk(message);
    syscall_setHandler(handler);

    // Descomentar para que la tarea muera, y se pueda ver la pantalla de debug
    //char* p = (char*) 0xFFFFFFFF; *p = 0; 

    while(1) { __asm __volatile("mov $4, %%eax":::"eax"); }
}

void handler() {
    syscall_informAction(Center);
}
