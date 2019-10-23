/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
#include "defines.h"

pte* mmu_createTable(PRIVILEDGE_LEVEL privLvl);

unsigned int nextFreeKernelPage;
unsigned int nextFreeTaskPage;

void mmu_init() {
	nextFreeKernelPage = KERNEL_FREE_PAGE_START;
	nextFreeTaskPage = PEASANT_FREE_PAGE_START;
}

uint32_t mmu_nextFreeKernelPage() {
    unsigned int pagina_libre = nextFreeKernelPage;
    nextFreeKernelPage += PAGE_SIZE;
    return pagina_libre;
}

uint32_t mmu_nextFreeTaskPage() {
    unsigned int pagina_libre = nextFreeTaskPage;
    nextFreeTaskPage += PAGE_SIZE;
    return pagina_libre;
}

typedef struct str_address {
	uint16_t offset:12;
	uint16_t pteIndex:10;
	uint16_t pdeIndex:10;
} address;

address parse_address(uint32_t virtual) {
	address addr;
	addr.offset = virtual;
	addr.pteIndex = PTE_INDEX(virtual);
	addr.pdeIndex = PDE_INDEX(virtual);

	return addr;
}

void mmu_mapPage(uint32_t virtual, uint32_t cr3, uint32_t phy, PRIVILEDGE_LEVEL privLvl) {
	// Descomponemos la dir. virtual
	address addr = parse_address(virtual);
	// Tomamos cr3 entero y no shifteamos porque es múltiplo de 4K 
	// y no usamos los campos bajos para nada (están todos en 0)
	pde* dirEntry = &((pde*) cr3)[addr.pdeIndex];
	if (dirEntry->present == PAGE_NOT_PRESENT) {
		// Si la tabla no está presente, hay que agregarla
		dirEntry->table = ((uint32_t) mmu_createTable(privLvl) >> 12);
		dirEntry->present = PAGE_PRESENT;
	}
	pte* tbl = (pte*) (dirEntry->table << 12);

	// Configuramos el índice de la tabla
	tbl[addr.pteIndex].present = PAGE_PRESENT; 
	tbl[addr.pteIndex].base = (phy >> 12);

	tlbflush();
}

pte* mmu_createTable(PRIVILEDGE_LEVEL privLvl) {
	pte* tbl = (pte*) mmu_nextFreeKernelPage();

	for (int i = 0; i < PAGE_TBL_SIZE; i++) {
		tbl[i].present = PAGE_NOT_PRESENT;
		tbl[i].rw = PAGE_RW;
		tbl[i].us = privLvl;
		tbl[i].pwt = PAGE_PWT;
		tbl[i].pcd = PAGE_PCD;
		tbl[i].acc = PAGE_NOT_ACCESSED;
		tbl[i].drt = PAGE_NOT_DIRTY;
		tbl[i].pat = PAGE_PAT;
		tbl[i].g = PAGE_GLOBAL;
		tbl[i].avl = PAGE_AVL;
	}

	return tbl;
}

uint32_t mmu_unmapPage(uint32_t virtual, uint32_t cr3) {
	// Descomponemos la dir. virtual
	address addr = parse_address(virtual);
	pde* dirEntry = &((pde*) cr3)[addr.pdeIndex];
	if (dirEntry->present == PAGE_NOT_PRESENT) {
		return 0;
	}

	pte* tbl = (pte*) (dirEntry->table << 12);
	// Matamos la entrada de la tabla
	tbl[addr.pteIndex].present = PAGE_NOT_PRESENT;

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

    return (uint32_t) dir;
}

uint32_t mmu_initTaskDir(PLAYER player) {
	// Inicializamos el directorio de paginación
	pde* dir = (pde*) mmu_nextFreeKernelPage();

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

	uint32_t dirCodigo = BASE_PHYS_CODE_ADDR + TASK_CODE_SIZE * player;

	// Copiamos
	uint32_t physCodeDir0 = mmu_nextFreeTaskPage();
	uint32_t physCodeDir1 = mmu_nextFreeTaskPage();

	// Mappeo direcciones del código copiado
	mmu_mapPage(TASK_CODE_ADDR, (uint32_t) dir, physCodeDir0, PRIVILEDGE_LEVEL_TASK);
	mmu_mapPage(TASK_CODE_ADDR + PAGE_SIZE, (uint32_t) dir, physCodeDir1, PRIVILEDGE_LEVEL_TASK);

	// Para copiar código de tarea, vamos a
	uint32_t cr3 = rcr3();

	mmu_mapPage(TEMP_VIRTUAL_ADDR, cr3, physCodeDir0, PRIVILEDGE_LEVEL_TASK);
	mmu_mapPage(TEMP_VIRTUAL_ADDR + PAGE_SIZE, cr3, physCodeDir1, PRIVILEDGE_LEVEL_TASK);

	// --------------

	// Vamos a copiar de a dword.
	// Para ello, nos movemos de a 4 Bytes.
	for (uint32_t i = 0; i < (TASK_CODE_SIZE / 4); i++) {
		uint32_t *dwordSrcActual = (uint32_t *) dirCodigo + (i * 4);
		uint32_t *dwordDstActual = (uint32_t *) TEMP_VIRTUAL_ADDR + (i * 4);

		*dwordDstActual = *dwordSrcActual;
	}

	// --------------

	mmu_unmapPage(TEMP_VIRTUAL_ADDR, cr3);
	mmu_unmapPage(TEMP_VIRTUAL_ADDR + PAGE_SIZE, cr3);

    return (uint32_t) dir;
}
