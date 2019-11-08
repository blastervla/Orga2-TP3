/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"
#include "defines.h"

// vector con tareas registradas (12 entradas, )
int16_t tareas[12];
// int tarea actual
int iTareaActual = 0;

void sched_init() {
	for (int i = 0; i < 12; ++i) {
		tareas[i] = 0;
	}
}

int16_t sched_nextTask() {
	task_inc();
	// Si debería ejecutar un handler y no lo tengo declarado, voy a la task directo:
	if (iTareaActual % 2 == 0 && tareas[iTareaActual] == 0) {
		iTareaActual++;
	}

	// Si no hay tarea definida, simplemente ejecuto la idle
	if (tareas[iTareaActual] == 0) {
		return GDT_IDX_TSS_IDLE << 3;
	}
  	return tareas[iTareaActual];
}

void task_inc() {
	iTareaActual++;
	if (iTareaActual == 12) {
		iTareaActual = 0;
	}
}