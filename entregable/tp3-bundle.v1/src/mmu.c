/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
#include "defines.h"


void mmu_init() {
}

uint32_t mmu_nextFreeKernelPage() {
    return 0;
}

void mmu_mapPage(uint32_t virtual, uint32_t cr3, uint32_t phy, uint32_t attrs) {
}

uint32_t mmu_unmapPage(uint32_t virtual, uint32_t cr3) {
    return 0;
}

uint32_t mmu_initKernelDir() {
	// Inicializamos el directorio de paginación
	pde* dir = (pde*) KERNEL_PAGE_DIR;

	for (int i = 0; i < PAGE_DIR_SIZE; i++) {
		dir[i] = (pde) {0};
	}

	dir[0].present = PAGE_PRESENT; 
	dir[0].rw = PAGE_RW;
	dir[0].us = PAGE_SUPERVISOR;
	dir[0].pwt = PAGE_PWT;
	dir[0].pcd = PAGE_PCD;
	dir[0].acc = PAGE_NOT_ACCESSED;
	dir[0].ign = PAGE_IGN;
	dir[0].ps = PAGE_PS_4K;
	dir[0].g = PAGE_GLOBAL;
	dir[0].avl = PAGE_AVL;
	dir[0].table = (KERNEL_PAGE_TABLE_0 >> 12);

	// Inicializamos la tabla de paginación (la única)
	pte* tbl = (pte*) (dir[0].table << 12);

	for (int i = 0; i < PAGE_TBL_SIZE; i++) {
		tbl[i].present = PAGE_PRESENT; 
		tbl[i].rw = PAGE_RW;
		tbl[i].us = PAGE_SUPERVISOR;
		tbl[i].pwt = PAGE_PWT;
		tbl[i].pcd = PAGE_PCD;
		tbl[i].acc = PAGE_NOT_ACCESSED;
		tbl[i].drt = PAGE_NOT_DIRTY;
		tbl[i].pat = PAGE_PAT;
		tbl[i].g = PAGE_GLOBAL;
		tbl[i].avl = PAGE_AVL;
		tbl[i].base = i;
	}

    return 0;
}








