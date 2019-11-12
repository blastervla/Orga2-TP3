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
uint8_t iTareaActual = 0;

f_handler_t *handlers[6];

int sched_isHandler() {
	return iTareaActual % 2 == 0;
}

void sched_init() {
	for (int i = 0; i < 12; ++i) {
		tareas[i] = 0;
	}
}

int16_t sched_nextTask() {
	if (sched_isHandler()) {
		// Estoy ejecutando un handler, este es un estado ilegal!
		// Hay que matar a la tarea dueña del handler (iTareaActual + 1)

		// TODO: Matar a la tarea actual, iTareaActual + 1
	}
	task_inc();
	// Si debería ejecutar un handler y no lo tengo declarado, voy a la task directo:
	if (sched_isHandler() && tareas[iTareaActual] == 0) {
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

uint32_t sched_getTareaActual() {
	// Obtiene el número de tarea actual (agrupando handler y tarea)
	// Nota: la división entera trunca la parte decimal, por lo que
	//		 hace lo que queremos :D
	return iTareaActual / 2;
}

void sched_registerHandler(f_handler_t *handler) {
	// El handler siempre está en el índice anterior a la tarea:
	uint8_t handlerIndex = iTareaActual - 1;
	if (handlers[handlerIndex] != NULL) {
		// Entonces ya estaba setteado el handler!

		// TODO: Matar tarea actual, usar iTareaActual
	} else {
		handlers[handlerIndex] = handler;
	}
}

void sched_mafiallyValidateHandler() {
	if (!sched_isHandler()) {
		// Entonces no es un handler!
		
		// TODO: Matar tarea actual, usar iTareaActual
	} else {
		// Como es un handler, siempre va a estar bien definido
		// hacer esto:
		task_inc();
	}
}