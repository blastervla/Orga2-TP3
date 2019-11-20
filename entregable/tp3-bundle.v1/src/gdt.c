/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de la tabla de descriptores globales
*/

#include "gdt.h"
#include "tss.h"

#define ADDR(variable) (uint32_t) &variable

gdt_entry gdt[GDT_COUNT] = {
    /* Descriptor nulo*/
    /* Offset = 0x00 */
    [GDT_IDX_NULL_DESC] = (gdt_entry) {
        (uint16_t)    0x0000,         /* limit[0:15]  */
        (uint16_t)    0x0000,         /* base[0:15]   */
        (uint8_t)     0x00,           /* base[23:16]  */
        (uint8_t)     0x00,           /* type         */
        (uint8_t)     0x00,           /* s            */
        (uint8_t)     0x00,           /* dpl          */
        (uint8_t)     0x00,           /* p            */
        (uint8_t)     0x00,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x00,           /* db           */
        (uint8_t)     0x00,           /* g            */
        (uint8_t)     0x00,           /* base[31:24]  */
    },

    // ======= CODIGO LVL 0 =======
    [14] = (gdt_entry) {
        (uint16_t)    0xa2FF,         /* limit[0:15] a2FF = 163 MB / 4 KB */
        (uint16_t)    0x0000,         /* base[0:15]   */
        (uint8_t)     0x00,           /* base[23:16]  */
        (uint8_t)     0x08,           /* type        8 es execute only */
        (uint8_t)     0x01,           /* s            */
        (uint8_t)     0x00,           /* dpl          */
        (uint8_t)     0x01,           /* p            */
        (uint8_t)     0x00,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x01,           /* db           */
        (uint8_t)     0x01,           /* g            */
        (uint8_t)     0x00,           /* base[31:24]  */
    },

    // ======= CODIGO LVL 3 =======
    [15] = (gdt_entry) {
        (uint16_t)    0xa2FF,         /* limit[0:15] a2FF = 163 MB / 4 KB */
        (uint16_t)    0x0000,         /* base[0:15]   */
        (uint8_t)     0x00,           /* base[23:16]  */
        (uint8_t)     0x08,           /* type         */
        (uint8_t)     0x01,           /* s            */
        (uint8_t)     0x03,           /* dpl          */
        (uint8_t)     0x01,           /* p            */
        (uint8_t)     0x00,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x01,           /* db           */
        (uint8_t)     0x01,           /* g            */
        (uint8_t)     0x00,           /* base[31:24]  */
    },

    // ======= DATOS LVL 0 =======
    [16] = (gdt_entry) {
        (uint16_t)    0xa2FF,         /* limit[0:15] a2FF = 163 MB / 4 KB */
        (uint16_t)    0x0000,         /* base[0:15]   */
        (uint8_t)     0x00,           /* base[23:16]  */
        (uint8_t)     0x02,           /* type         2 es read/write */
        (uint8_t)     0x01,           /* s            */
        (uint8_t)     0x00,           /* dpl          */
        (uint8_t)     0x01,           /* p            */
        (uint8_t)     0x00,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x01,           /* db           */
        (uint8_t)     0x01,           /* g            */
        (uint8_t)     0x00,           /* base[31:24]  */
    },

    // ======= DATOS LVL 3 =======
    [17] = (gdt_entry) {
        (uint16_t)    0xa2FF,         /* limit[0:15] a2FF = 163 MB / 4 KB */
        (uint16_t)    0x0000,         /* base[0:15]   */
        (uint8_t)     0x00,           /* base[23:16]  */
        (uint8_t)     0x02,           /* type         */
        (uint8_t)     0x01,           /* s            */
        (uint8_t)     0x03,           /* dpl          */
        (uint8_t)     0x01,           /* p            */
        (uint8_t)     0x00,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x01,           /* db           */
        (uint8_t)     0x01,           /* g            */
        (uint8_t)     0x00,           /* base[31:24]  */
    },

    // ======= PANTALLA =======
    // Es de 80x50
    // Arranca en 0x000B8000
    [18] = (gdt_entry) {
        (uint16_t)    7999,           /* limit[0:15] a2FF = 163 MB / 4 KB */
        (uint16_t)    0x8000,         /* base[0:15]   */
        (uint8_t)     0x0B,           /* base[23:16]  */
        (uint8_t)     0x02,           /* type         */
        (uint8_t)     0x01,           /* s            */
        (uint8_t)     0x00,           /* dpl          */
        (uint8_t)     0x01,           /* p            */
        (uint8_t)     0x00,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x01,           /* db           */
        (uint8_t)     0x00,           /* g            */
        (uint8_t)     0x00,           /* base[31:24]  */
    },
};

gdt_descriptor GDT_DESC = {
    sizeof(gdt) - 1,
    (uint32_t) &gdt
};

void gdt_init() {
    // ======= TSS Tarea Inicial =========
    gdt[GDT_IDX_TSS_INIT] = (gdt_entry) {
        (uint16_t)    TSS_SIZE - 1,   /* limit[0:15]  */
        (uint16_t)    ADDR(tss_initial),  /* base[0:15]   */
        (uint8_t)     (ADDR(tss_initial) >> 16),           /* base[23:16]  */
        (uint8_t)     0x09,           /* type         */
        (uint8_t)     0x00,           /* s            */
        (uint8_t)     0x00,           /* dpl          */
        (uint8_t)     0x01,           /* p            */
        (uint8_t)     0x00,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x01,           /* db           */
        (uint8_t)     0x00,           /* g            */
        (uint8_t)     (ADDR(tss_initial) >> 24),           /* base[31:24]  */
    };

    // ======= TSS Tarea Idle =========
    gdt[GDT_IDX_TSS_IDLE] = (gdt_entry) {
        (uint16_t)    TSS_SIZE - 1,   /* limit[0:15]  */
        (uint16_t)    ADDR(tss_idle),  /* base[0:15]   */
        (uint8_t)     (ADDR(tss_idle) >> 16),           /* base[23:16]  */
        (uint8_t)     0x09,           /* type         */
        (uint8_t)     0x00,           /* s            */
        (uint8_t)     0x00,           /* dpl          */
        (uint8_t)     0x01,           /* p            */
        (uint8_t)     0x00,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x01,           /* db           */
        (uint8_t)     0x00,           /* g            */
        (uint8_t)     (ADDR(tss_idle) >> 24),           /* base[31:24]  */
    };

    gdt[GDT_IDX_TSS_PA_T1] = (gdt_entry) {
        (uint16_t)    TSS_SIZE - 1,   /* limit[0:15]  */
        (uint16_t)    ADDR(tss_ball_tasks[0]), /* base[0:15]   */
        (uint8_t)     (ADDR(tss_ball_tasks[0]) >> 16),           /* base[23:16]  */
        (uint8_t)     0x09,           /* type         */
        (uint8_t)     0x00,           /* s            */
        (uint8_t)     0x00,           /* dpl          */
        (uint8_t)     0x01,           /* p            */
        (uint8_t)     0x00,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x01,           /* db           */
        (uint8_t)     0x00,           /* g            */
        (uint8_t)     (ADDR(tss_ball_tasks[0]) >> 24),           /* base[31:24]  */
    };

    gdt[GDT_IDX_TSS_PA_T1_H] = (gdt_entry) {
        (uint16_t)    TSS_SIZE - 1,           /* limit[0:15]  */
        (uint16_t)    ADDR(tss_ball_tasks[1]),         /* base[0:15]   */
        (uint8_t)     (ADDR(tss_ball_tasks[1]) >> 16),           /* base[23:16]  */
        (uint8_t)     0x09,           /* type         */
        (uint8_t)     0x00,           /* s            */
        (uint8_t)     0x00,           /* dpl          */
        (uint8_t)     0x01,           /* p            */
        (uint8_t)     0x00,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x01,           /* db           */
        (uint8_t)     0x00,           /* g            */
        (uint8_t)     (ADDR(tss_ball_tasks[1]) >> 24),           /* base[31:24]  */
    };

    gdt[GDT_IDX_TSS_PA_T2] = (gdt_entry) {
        (uint16_t)    TSS_SIZE - 1,   /* limit[0:15]  */
        (uint16_t)    ADDR(tss_ball_tasks[2]),  /* base[0:15]   */
        (uint8_t)     (ADDR(tss_ball_tasks[2]) >> 16),           /* base[23:16]  */
        (uint8_t)     0x09,           /* type         */
        (uint8_t)     0x00,           /* s            */
        (uint8_t)     0x00,           /* dpl          */
        (uint8_t)     0x01,           /* p            */
        (uint8_t)     0x00,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x01,           /* db           */
        (uint8_t)     0x00,           /* g            */
        (uint8_t)     (ADDR(tss_ball_tasks[2]) >> 24),           /* base[31:24]  */
    };

    gdt[GDT_IDX_TSS_PA_T2_H] = (gdt_entry) {
        (uint16_t)    TSS_SIZE - 1,   /* limit[0:15]  */
        (uint16_t)    ADDR(tss_ball_tasks[3]),         /* base[0:15]   */
        (uint8_t)     (ADDR(tss_ball_tasks[3]) >> 16),           /* base[23:16]  */
        (uint8_t)     0x09,           /* type         */
        (uint8_t)     0x00,           /* s            */
        (uint8_t)     0x00,           /* dpl          */
        (uint8_t)     0x01,           /* p            */
        (uint8_t)     0x00,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x01,           /* db           */
        (uint8_t)     0x00,           /* g            */
        (uint8_t)     (ADDR(tss_ball_tasks[3]) >> 24),           /* base[31:24]  */
    };

    gdt[GDT_IDX_TSS_PA_T3] = (gdt_entry) {
        (uint16_t)    TSS_SIZE - 1,   /* limit[0:15]  */
        (uint16_t)    ADDR(tss_ball_tasks[4]),  /* base[0:15]   */
        (uint8_t)     (ADDR(tss_ball_tasks[4]) >> 16),           /* base[23:16]  */
        (uint8_t)     0x09,           /* type         */
        (uint8_t)     0x00,           /* s            */
        (uint8_t)     0x00,           /* dpl          */
        (uint8_t)     0x01,           /* p            */
        (uint8_t)     0x00,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x01,           /* db           */
        (uint8_t)     0x00,           /* g            */
        (uint8_t)     (ADDR(tss_ball_tasks[4]) >> 24),           /* base[31:24]  */
    };

    gdt[GDT_IDX_TSS_PA_T3_H] = (gdt_entry) {
        (uint16_t)    TSS_SIZE - 1,           /* limit[0:15]  */
        (uint16_t)    ADDR(tss_ball_tasks[5]),         /* base[0:15]   */
        (uint8_t)     (ADDR(tss_ball_tasks[5]) >> 16),           /* base[23:16]  */
        (uint8_t)     0x09,           /* type         */
        (uint8_t)     0x00,           /* s            */
        (uint8_t)     0x00,           /* dpl          */
        (uint8_t)     0x01,           /* p            */
        (uint8_t)     0x00,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x01,           /* db           */
        (uint8_t)     0x00,           /* g            */
        (uint8_t)     (ADDR(tss_ball_tasks[5]) >> 24),           /* base[31:24]  */
    };

    gdt[GDT_IDX_TSS_PB_T1] = (gdt_entry) {
        (uint16_t)    TSS_SIZE - 1,   /* limit[0:15]  */
        (uint16_t)    ADDR(tss_ball_tasks[6]),  /* base[0:15]   */
        (uint8_t)     (ADDR(tss_ball_tasks[6]) >> 16),           /* base[23:16]  */
        (uint8_t)     0x09,           /* type         */
        (uint8_t)     0x00,           /* s            */
        (uint8_t)     0x00,           /* dpl          */
        (uint8_t)     0x01,           /* p            */
        (uint8_t)     0x00,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x01,           /* db           */
        (uint8_t)     0x00,           /* g            */
        (uint8_t)     (ADDR(tss_ball_tasks[6]) >> 24),           /* base[31:24]  */
    };

    gdt[GDT_IDX_TSS_PB_T1_H] = (gdt_entry) {
        (uint16_t)    TSS_SIZE - 1,           /* limit[0:15]  */
        (uint16_t)    ADDR(tss_ball_tasks[7]),         /* base[0:15]   */
        (uint8_t)     (ADDR(tss_ball_tasks[7]) >> 16),           /* base[23:16]  */
        (uint8_t)     0x09,           /* type         */
        (uint8_t)     0x00,           /* s            */
        (uint8_t)     0x00,           /* dpl          */
        (uint8_t)     0x01,           /* p            */
        (uint8_t)     0x00,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x01,           /* db           */
        (uint8_t)     0x00,           /* g            */
        (uint8_t)     (ADDR(tss_ball_tasks[7]) >> 24),           /* base[31:24]  */
    };

    gdt[GDT_IDX_TSS_PB_T2] = (gdt_entry) {
        (uint16_t)    TSS_SIZE - 1,   /* limit[0:15]  */
        (uint16_t)    ADDR(tss_ball_tasks[8]),  /* base[0:15]   */
        (uint8_t)     (ADDR(tss_ball_tasks[8]) >> 16),           /* base[23:16]  */
        (uint8_t)     0x09,           /* type         */
        (uint8_t)     0x00,           /* s            */
        (uint8_t)     0x00,           /* dpl          */
        (uint8_t)     0x01,           /* p            */
        (uint8_t)     0x00,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x01,           /* db           */
        (uint8_t)     0x00,           /* g            */
        (uint8_t)     (ADDR(tss_ball_tasks[8]) >> 24),           /* base[31:24]  */
    };

    gdt[GDT_IDX_TSS_PB_T2_H] = (gdt_entry) {
        (uint16_t)    TSS_SIZE - 1,   /* limit[0:15]  */
        (uint16_t)    ADDR(tss_ball_tasks[9]),         /* base[0:15]   */
        (uint8_t)     (ADDR(tss_ball_tasks[9]) >> 16),           /* base[23:16]  */
        (uint8_t)     0x09,           /* type         */
        (uint8_t)     0x00,           /* s            */
        (uint8_t)     0x00,           /* dpl          */
        (uint8_t)     0x01,           /* p            */
        (uint8_t)     0x00,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x01,           /* db           */
        (uint8_t)     0x00,           /* g            */
        (uint8_t)     (ADDR(tss_ball_tasks[9]) >> 24),           /* base[31:24]  */
    };

    gdt[GDT_IDX_TSS_PB_T3] = (gdt_entry) {
        (uint16_t)    TSS_SIZE - 1,   /* limit[0:15]  */
        (uint16_t)    ADDR(tss_ball_tasks[10]),  /* base[0:15]   */
        (uint8_t)     (ADDR(tss_ball_tasks[10]) >> 16),           /* base[23:16]  */
        (uint8_t)     0x09,           /* type         */
        (uint8_t)     0x00,           /* s            */
        (uint8_t)     0x00,           /* dpl          */
        (uint8_t)     0x01,           /* p            */
        (uint8_t)     0x00,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x01,           /* db           */
        (uint8_t)     0x00,           /* g            */
        (uint8_t)     (ADDR(tss_ball_tasks[10]) >> 24),           /* base[31:24]  */
    };

    gdt[GDT_IDX_TSS_PB_T3_H] = (gdt_entry) {
        (uint16_t)    TSS_SIZE - 1,           /* limit[0:15]  */
        (uint16_t)    ADDR(tss_ball_tasks[11]),         /* base[0:15]   */
        (uint8_t)     (ADDR(tss_ball_tasks[11]) >> 16),           /* base[23:16]  */
        (uint8_t)     0x09,           /* type         */
        (uint8_t)     0x00,           /* s            */
        (uint8_t)     0x00,           /* dpl          */
        (uint8_t)     0x01,           /* p            */
        (uint8_t)     0x00,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x01,           /* db           */
        (uint8_t)     0x00,           /* g            */
        (uint8_t)     (ADDR(tss_ball_tasks[11]) >> 24),           /* base[31:24]  */
    };
}