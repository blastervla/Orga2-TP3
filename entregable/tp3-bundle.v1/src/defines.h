/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

    Definiciones globales del sistema.
*/

#ifndef __DEFINES_H__
#define __DEFINES_H__

/* Bool */
/* -------------------------------------------------------------------------- */
#define TRUE                    0x00000001
#define FALSE                   0x00000000
#define ERROR                   1

/* Páginas */
/* -------------------------------------------------------------------------- */
#define KERNEL_PAGE_DIR 		0x0002B000

#define PAG_P                   0x00000001
#define PAG_R                   0x00000000
#define PAG_RW                  0x00000002
#define PAG_S                   0x00000000
#define PAG_US                  0x00000004

#define PAGE_PRESENT 		1
#define PAGE_NOT_PRESENT 	0
#define PAGE_RW 	 		1
#define PAGE_SUPERVISOR 	0
#define PAGE_TASK 			1
#define PAGE_PWT			0
#define PAGE_PCD			0
#define PAGE_NOT_ACCESSED 	0
#define PAGE_IGN 			0
#define PAGE_PS_4K			0
#define PAGE_GLOBAL 		0
#define PAGE_AVL 			0

#define PAGE_NOT_DIRTY		0
#define PAGE_PAT 			0

#define PAGE_DIR_SIZE		1024
#define PAGE_TBL_SIZE		1024
#define PAGE_SIZE 			4 * 1024 // 4K
/* Misc */
/* -------------------------------------------------------------------------- */
#define TASK_CODE_SIZE			2 * PAGE_SIZE

#define PRIVILEDGE_LEVEL uint8_t
#define PRIVILEDGE_LEVEL_SUPERVISOR 0
#define PRIVILEDGE_LEVEL_TASK 1

#define PLAYER uint8_t
#define PLAYER_A_TIPO_1 0
#define PLAYER_A_TIPO_2 1
#define PLAYER_A_TIPO_3 2
#define PLAYER_B_TIPO_1 3
#define PLAYER_B_TIPO_2 4
#define PLAYER_B_TIPO_3 5

/* GDT */
/* -------------------------------------------------------------------------- */

#define GDT_CODE_0 	14
#define GDT_DATA_0 	16
#define GDT_DATA_3 	17
#define GDT_VIDEO 	18

#define GDT_CODE_3 	15
#define GDT_COUNT 33

#define GDT_IDX_NULL_DESC           0
#define GDT_IDX_TSS_INIT			19
#define GDT_IDX_TSS_IDLE			20

#define GDT_IDX_TSS_PA_T1			21
#define GDT_IDX_TSS_PA_T1_H			22
#define GDT_IDX_TSS_PA_T2			23
#define GDT_IDX_TSS_PA_T2_H			24
#define GDT_IDX_TSS_PA_T3			25
#define GDT_IDX_TSS_PA_T3_H			26

#define GDT_IDX_TSS_PB_T1			27
#define GDT_IDX_TSS_PB_T1_H			28
#define GDT_IDX_TSS_PB_T2			29
#define GDT_IDX_TSS_PB_T2_H			30
#define GDT_IDX_TSS_PB_T3			31
#define GDT_IDX_TSS_PB_T3_H			32

#define GDT_OFF_NULL_DESC           (GDT_IDX_NULL_DESC << 3)



/* TSS */
/* -------------------------------------------------------------------------- */
#define TSS_SIZE			512
#define TSS_EFLAGS_INT		0x202

/* Selectores de segmentos */
/* -------------------------------------------------------------------------- */

/* Direcciones de memoria */
/* -------------------------------------------------------------------------- */
#define BOOTSECTOR               0x00001000 /* direccion fisica de comienzo del bootsector (copiado) */
#define KERNEL                   0x00001200 /* direccion fisica de comienzo del kernel */
#define VIDEO                    0x000B8000 /* direccion fisica del buffer de video */

/* Direcciones virtuales de código, pila y datos */
/* -------------------------------------------------------------------------- */
#define TASK_CODE_ADDR			0x08000000 /* direccion virtual del codigo */
#define TEMP_VIRTUAL_ADDR 		0x08004000

/* Direcciones fisicas de codigos */
/* -------------------------------------------------------------------------- */
/* En estas direcciones estan los códigos de todas las tareas. De aqui se
 * copiaran al destino indicado por TASK_<i>_CODE_ADDR.
 */
#define BASE_PHYS_CODE_ADDR		0x10000

/* Direcciones fisicas de directorios y tablas de paginas del KERNEL */
/* -------------------------------------------------------------------------- */
#define KERNEL_PAGE_DIR          0x0002B000
#define KERNEL_PAGE_TABLE_0      0x0002C000
#define KERNEL_STACK_END         KERNEL_PAGE_DIR - 1

/* MMU */
#define KERNEL_FREE_PAGE_START   0x00100000
#define PEASANT_FREE_PAGE_START  0x00400000

#define PDE_INDEX(virtual) (virtual >> 22)
#define PTE_INDEX(virtual) (virtual >> 12)

#endif  /* !__DEFINES_H__ */
