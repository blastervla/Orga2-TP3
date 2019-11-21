/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#ifndef __GAME_H__
#define __GAME_H__

#include "stdint.h"
#include "defines.h"
#include "screen.h"
#include "mmu.h"
#include "sched.h"

typedef enum e_action {
    Up = 1,
    Center = 2,
    Down = 3,
} e_action_t;

void game_init();
void game_tick();
void game_executeFrame();

void game_talk(const char *msg);

uint32_t game_getCurrentX();
uint32_t game_getCurrentY();

void game_informAction(e_action_t action);

void game_kbInput(uint32_t input);
void game_showDebugInfo(
        uint32_t exception,  
        uint32_t pa_edi,
        uint32_t pa_esi,
        uint32_t pa_ebp,
        uint32_t pa_esp,
        uint32_t pa_ebx,
        uint32_t pa_edx,
        uint32_t pa_ecx,
        uint32_t pa_eax,   
        uint32_t pchg_error_code,
        uint32_t pchg_eip,
        uint16_t pchg_cs,
        uint32_t pchg_eflags,
        uint32_t pchg_esp,
        uint16_t pchg_ss);

#endif  /* !__GAME_H__ */
