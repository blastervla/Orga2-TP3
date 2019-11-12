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
void game_executeFrame();

void game_talk(const char *msg);

void game_getCurrentX();
void game_getCurrentY();

void game_reportAction(e_action_t action);

#endif  /* !__GAME_H__ */
