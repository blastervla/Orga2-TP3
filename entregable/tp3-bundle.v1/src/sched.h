/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCHED_H__
#define __SCHED_H__

#include "stdint.h"
#include "screen.h"
#include "tss.h"

typedef void (*f_handler_t)();

int sched_isHandler();

void sched_init();

int16_t sched_nextTask();

void sched_newBall(PLAYER ballType);
void sched_registerHandler(f_handler_t* handler);

uint32_t sched_getTareaActual();

// Checkea que la tarea actualmente en ejecución es un handler,
// si no lo es, la mata ◉ _ ◉
void sched_killIfNotHandler();
void sched_killIfHandler();

// Mata a la tarea actual junto con su handler.
// Pre: La tarea actual es una pelota.
void sched_makeItLookLikeAnAccident();

void sched_killBall(int iBall);
void sched_killCurrent();

#endif	/* !__SCHED_H__ */
