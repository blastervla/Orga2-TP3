/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"
#include "mmu.h"
#include "defines.h"

tss tss_initial;
tss tss_idle = (tss) {
        (uint16_t)  0,  // ptl;
        (uint16_t)  0,  // unused0;
        (uint32_t)  KERNEL_STACK_END,   //   esp0;
        (uint16_t)  GDT_DATA_0 << 3,    // ss0;
        (uint16_t)  0,  // unused1;
        (uint32_t)  0,  //   esp1;
        (uint16_t)  0,  // ss1;
        (uint16_t)  0,  // unused2;
        (uint32_t)  0,  //   esp2;
        (uint16_t)  0,  // ss2;
        (uint16_t)  0,  // unused3;
        (uint32_t)  KERNEL_PAGE_DIR,    //   cr3;
        (uint32_t)  0x1C000,    //   eip;
        (uint32_t)  0x202,    //   eflags;
        (uint32_t)  0,  //   eax;
        (uint32_t)  0,  //   ecx;
        (uint32_t)  0,  //   edx;
        (uint32_t)  0,  //   ebx;
        (uint32_t)  KERNEL_STACK_END, //   esp;
        (uint32_t)  0,  //   ebp;
        (uint32_t)  0,  //   esi;
        (uint32_t)  0,  //   edi;
        (uint16_t)  0,  // es;
        (uint16_t)  0,  // unused4;
        (uint16_t)  GDT_CODE_0 << 3,    // cs;
        (uint16_t)  0,  // unused5;
        (uint16_t)  GDT_DATA_0 << 3,    // ss;
        (uint16_t)  0,  // unused6;
        (uint16_t)  GDT_DATA_0 << 3,    // ds;
        (uint16_t)  0,  // unused7;
        (uint16_t)  0,  // fs;
        (uint16_t)  0,  // unused8;
        (uint16_t)  0,  // gs;
        (uint16_t)  0,  // unused9;
        (uint16_t)  0,  // ldt;
        (uint16_t)  0,  // unused10;
        (uint16_t)  0,  // dtrap;
        (uint16_t)  0,  // iomap;
    };

tss tss_ball_tasks[12];
uint32_t tss_ball_esp0s[12];

tss tss_new_ball (PLAYER player, uint8_t isHandler);

void tss_init() {

/* No falta completar la TSS, sirve para saber
	dónde guardar las TSS's de las tareas y
	luego poder conmutar con otra tarea */

    tss_initial = (tss) { 0 };

    for (int i = 0; i < 12; ++i) {
    	// Sumamos PAGE_SIZE porque estamos definiendo stacks 
    	// (que van de abajo para arriba)
    	tss_ball_esp0s[i] = mmu_nextFreeKernelPage() + PAGE_SIZE;
    }

	tss_ball_tasks[0] = tss_new_ball(PLAYER_A_TIPO_1, 0);
	tss_ball_tasks[1] = tss_new_ball(PLAYER_A_TIPO_1, 1);
	tss_ball_tasks[2] = tss_new_ball(PLAYER_A_TIPO_2, 0);
	tss_ball_tasks[3] = tss_new_ball(PLAYER_A_TIPO_2, 1);
	tss_ball_tasks[4] = tss_new_ball(PLAYER_A_TIPO_3, 0);
	tss_ball_tasks[5] = tss_new_ball(PLAYER_A_TIPO_3, 1);
	tss_ball_tasks[6] = tss_new_ball(PLAYER_B_TIPO_1, 0);
	tss_ball_tasks[7] = tss_new_ball(PLAYER_B_TIPO_1, 1);
	tss_ball_tasks[8] = tss_new_ball(PLAYER_B_TIPO_2, 0);
	tss_ball_tasks[9] = tss_new_ball(PLAYER_B_TIPO_2, 1);
	tss_ball_tasks[10] = tss_new_ball(PLAYER_B_TIPO_3, 0);
	tss_ball_tasks[11] = tss_new_ball(PLAYER_B_TIPO_3, 1);
}

tss tss_new_ball (PLAYER player, uint8_t isHandler) {
	return (tss) {
		(uint16_t)  0,	// ptl;
    	(uint16_t)  0,	// unused0;
    	(uint32_t)  tss_ball_esp0s[player * 2 + (isHandler ? 1 : 0)],	//   esp0;
    	(uint16_t)  GDT_DATA_3 << 3,	// ss0;
    	(uint16_t)  0,	// unused1;
    	(uint32_t)  0,	//   esp1;
    	(uint16_t)  0,	// ss1;
    	(uint16_t)  0,	// unused2;
    	(uint32_t)  0,	//   esp2;
    	(uint16_t)  0,	// ss2;
    	(uint16_t)  0,	// unused3;
    	(uint32_t)  mmu_initTaskDir(player),	//   cr3;
    	(uint32_t)  TASK_CODE_ADDR,	//   eip;
    	(uint32_t)  0,	//   eflags;
    	(uint32_t)  0,	//   eax;
    	(uint32_t)  0,	//   ecx;
    	(uint32_t)  0,	//   edx;
    	(uint32_t)  0,	//   ebx;
    	(uint32_t)  TASK_CODE_ADDR + 7 * 1024,	//   esp;
    	(uint32_t)  0,	//   ebp;
    	(uint32_t)  0,	//   esi;
    	(uint32_t)  0,	//   edi;
    	(uint16_t)  (GDT_DATA_3 << 3) + 3,	// es;
    	(uint16_t)  0,	// unused4;
    	(uint16_t)  (GDT_CODE_3 << 3) + 3,	// cs;
    	(uint16_t)  0,	// unused5;
    	(uint16_t)  (GDT_DATA_3 << 3) + 3,	// ss;
    	(uint16_t)  0,	// unused6;
    	(uint16_t)  (GDT_DATA_3 << 3) + 3,	// ds;
    	(uint16_t)  0,	// unused7;
    	(uint16_t)  (GDT_DATA_3 << 3) + 3,	// fs;
    	(uint16_t)  0,	// unused8;
    	(uint16_t)  (GDT_DATA_3 << 3) + 3,	// gs;
    	(uint16_t)  0,	// unused9;
    	(uint16_t)  0,	// ldt;
    	(uint16_t)  0,	// unused10;
    	(uint16_t)  0,	// dtrap;
    	(uint16_t)  0,	// iomap;
    };
}

void tss_ball_reset(PLAYER player) {
	tss_ball_tasks[player * 2].esp0 = tss_ball_esp0s[player * 2];
	tss_ball_tasks[player * 2].eip = TASK_CODE_ADDR;
	tss_ball_tasks[player * 2].esp = TASK_CODE_ADDR + 7 * 1024;

	tss_ball_tasks[player * 2 + 1].esp0 = tss_ball_esp0s[player * 2 + 1];
	tss_ball_tasks[player * 2 + 1].eip = TASK_CODE_ADDR;
	tss_ball_tasks[player * 2 + 1].esp = TASK_CODE_ADDR + 7 * 1024;
}