/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#ifndef __MMU_H__
#define __MMU_H__

#include "stdint.h"
#include "defines.h"
#include "i386.h"
#include "tss.h"
#include "game.h"


void mmu_init();

uint32_t mmu_nextFreeKernelPage();

void mmu_mapPage(uint32_t virtual, uint32_t cr3, uint32_t phy, uint32_t attrs);

uint32_t mmu_unmapPage(uint32_t virtual, uint32_t cr3);

uint32_t mmu_initKernelDir();

typedef struct str_pde {
	uint8_t present:1; 
	uint8_t rw:1;
	uint8_t us:1;
	uint8_t pwt:1;
	uint8_t	pcd:1;
	uint8_t acc:1;
	uint8_t	ign:1;
	uint8_t	ps:1;
	uint8_t g:1;
	uint8_t avl:3;
	uint32_t table:20;
} __attribute__((__packed__, aligned (4))) pde;

typedef struct str_pte {
	uint8_t present:1; 
	uint8_t rw:1;
	uint8_t us:1;
	uint8_t pwt:1;
	uint8_t	pcd:1;
	uint8_t acc:1;
	uint8_t	drt:1;
	uint8_t	pat:1;
	uint8_t g:1;
	uint8_t avl:3;
	uint32_t base:20;
} __attribute__((__packed__, aligned (4))) pte;

#endif	/* !__MMU_H__ */




