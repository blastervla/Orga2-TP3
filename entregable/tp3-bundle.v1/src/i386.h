/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  rutinas comunes para lectura y escritura de registros desde C
*/

#ifndef __i386_H__
#define __i386_H__

#include "stdint.h"

#define LS_INLINE static __inline __attribute__((always_inline))

LS_INLINE uint32_t reax(void);
LS_INLINE uint32_t rebx(void);
LS_INLINE uint32_t recx(void);
LS_INLINE uint32_t redx(void);
LS_INLINE uint32_t resi(void);
LS_INLINE uint32_t redi(void);
LS_INLINE uint32_t rebp(void);
LS_INLINE uint32_t resp(void);
LS_INLINE uint32_t reip(void);

LS_INLINE uint32_t rcs(void);
LS_INLINE uint32_t rds(void);
LS_INLINE uint32_t res(void);
LS_INLINE uint32_t rfs(void);
LS_INLINE uint32_t rgs(void);
LS_INLINE uint32_t rss(void);
LS_INLINE uint32_t reflags(void);

LS_INLINE void lcr0(uint32_t val);
LS_INLINE uint32_t rcr0(void);
LS_INLINE void lcr1(uint32_t val);
LS_INLINE uint32_t rcr1(void);
LS_INLINE void lcr2(uint32_t val);
LS_INLINE uint32_t rcr2(void);
LS_INLINE void lcr3(uint32_t val);
LS_INLINE uint32_t rcr3(void);
LS_INLINE void lcr4(uint32_t val);
LS_INLINE uint32_t rcr4(void);
LS_INLINE void tlbflush(void);
LS_INLINE void ltr(uint16_t sel);
LS_INLINE uint16_t rtr(void);
LS_INLINE void hlt(void);
LS_INLINE void breakpoint(void);

/*
 * Implementaciones
 */

LS_INLINE void lcr0(uint32_t val) {
    __asm __volatile("movl %0,%%cr0" : : "r" (val));
}

LS_INLINE uint32_t rcr0(void) {
    uint32_t val;
    __asm __volatile("movl %%cr0,%0" : "=r" (val));
    return val;
}

LS_INLINE void lcr1(uint32_t val) {
    __asm __volatile("movl %0,%%cr1" : : "r" (val));
}

LS_INLINE uint32_t rcr1(void) {
    uint32_t val;
    __asm __volatile("movl %%cr1,%0" : "=r" (val));
    return val;
}

LS_INLINE void lcr2(uint32_t val) {
    __asm __volatile("movl %0,%%cr2" : : "r" (val));
}

LS_INLINE uint32_t rcr2(void) {
    uint32_t val;
    __asm __volatile("movl %%cr2,%0" : "=r" (val));
    return val;
}

LS_INLINE void lcr3(uint32_t val) {
    __asm __volatile("movl %0,%%cr3" : : "r" (val));
}

LS_INLINE uint32_t rcr3(void) {
    uint32_t val;
    __asm __volatile("movl %%cr3,%0" : "=r" (val));
    return val;
}

LS_INLINE void lcr4(uint32_t val) {
    __asm __volatile("movl %0,%%cr4" : : "r" (val));
}

LS_INLINE uint32_t rcr4(void) {
    uint32_t cr4;
    __asm __volatile("movl %%cr4,%0" : "=r" (cr4));
    return cr4;
}

 LS_INLINE void tlbflush(void) {
    uint32_t cr3;
    __asm __volatile("movl %%cr3,%0" : "=r" (cr3));
     __asm __volatile("movl %0,%%cr3" : : "r" (cr3));
}

LS_INLINE void ltr(uint16_t sel) {
    __asm __volatile("ltr %0" : : "r" (sel));
}

LS_INLINE uint16_t rtr(void) {
    uint16_t sel;
    __asm __volatile("str %0" : "=r" (sel) : );
    return sel;
}

LS_INLINE void hlt(void) {
    __asm __volatile("hlt" : : );
}

LS_INLINE void breakpoint(void) {
    __asm __volatile("xchg %%bx, %%bx" : :);
}

LS_INLINE uint32_t reax(void) {
    uint32_t val;
    __asm __volatile("movl %%eax,%0" : "=r" (val));
    return val;
}
LS_INLINE uint32_t rebx(void) {
    uint32_t val;
    __asm __volatile("movl %%ebx,%0" : "=r" (val));
    return val;
}
LS_INLINE uint32_t recx(void) {
    uint32_t val;
    __asm __volatile("movl %%ecx,%0" : "=r" (val));
    return val;
}
LS_INLINE uint32_t redx(void) {
    uint32_t val;
    __asm __volatile("movl %%edx,%0" : "=r" (val));
    return val;
}
LS_INLINE uint32_t resi(void) {
    uint32_t val;
    __asm __volatile("movl %%esi,%0" : "=r" (val));
    return val;
}
LS_INLINE uint32_t redi(void) {
    uint32_t val;
    __asm __volatile("movl %%edi,%0" : "=r" (val));
    return val;
}
LS_INLINE uint32_t rebp(void) {
    uint32_t val;
    __asm __volatile("movl %%ebp,%0" : "=r" (val));
    return val;
}
LS_INLINE uint32_t resp(void) {
    uint32_t val;
    __asm __volatile("movl %%esp,%0" : "=r" (val));
    return val;
}
LS_INLINE uint32_t reip(void) {
    uint32_t val;
    __asm __volatile("movl %%eip,%0" : "=r" (val));
    return val;
}
LS_INLINE uint32_t rcs(void) {
    uint32_t val;
    __asm __volatile("movl %%cs,%0" : "=r" (val));
    return val;
}
LS_INLINE uint32_t rds(void) {
    uint32_t val;
    __asm __volatile("movl %%ds,%0" : "=r" (val));
    return val;
}
LS_INLINE uint32_t res(void) {
    uint32_t val;
    __asm __volatile("movl %%es,%0" : "=r" (val));
    return val;
}
LS_INLINE uint32_t rfs(void) {
    uint32_t val;
    __asm __volatile("movl %%fs,%0" : "=r" (val));
    return val;
}
LS_INLINE uint32_t rgs(void) {
    uint32_t val;
    __asm __volatile("movl %%gs,%0" : "=r" (val));
    return val;
}
LS_INLINE uint32_t rss(void) {
    uint32_t val;
    __asm __volatile("movl %%ss,%0" : "=r" (val));
    return val;
}
LS_INLINE uint32_t reflags(void) {
    uint32_t val;
    __asm __volatile("pushf" : : );
    __asm __volatile("pop %0" : "=r" (val));
    return val;
}

#endif  /* !__i386_H__ */
