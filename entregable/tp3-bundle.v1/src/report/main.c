#include "stdint.h"

typedef struct str_tss {
    uint16_t  ptl;
    uint16_t  unused0;
    uint32_t    esp0;
    uint16_t  ss0;
    uint16_t  unused1;
    uint32_t    esp1;
    uint16_t  ss1;
    uint16_t  unused2;
    uint32_t    esp2;
    uint16_t  ss2;
    uint16_t  unused3;
    uint32_t    cr3;
    uint32_t    eip;
    uint32_t    eflags;
    uint32_t    eax;
    uint32_t    ecx;
    uint32_t    edx;
    uint32_t    ebx;
    uint32_t    esp;
    uint32_t    ebp;
    uint32_t    esi;
    uint32_t    edi;
    uint16_t  es;
    uint16_t  unused4;
    uint16_t  cs;
    uint16_t  unused5;
    uint16_t  ss;
    uint16_t  unused6;
    uint16_t  ds;
    uint16_t  unused7;
    uint16_t  fs;
    uint16_t  unused8;
    uint16_t  gs;
    uint16_t  unused9;
    uint16_t  ldt;
    uint16_t  unused10;
    uint16_t  dtrap;
    uint16_t  iomap;
} __attribute__((__packed__, aligned (8))) tss;

tss tss_idle;

int main() {
	tss_idle = (tss) {
		(uint16_t)  0,	// ptl;
    	(uint16_t)  0,	// unused0;
    	(uint32_t)  0x0002B000 - 1,	//   esp0;
    	(uint16_t)  16 << 3,	// ss0;
    	(uint16_t)  0,	// unused1;
    	(uint32_t)  0,	//   esp1;
    	(uint16_t)  0,	// ss1;
    	(uint16_t)  0,	// unused2;
    	(uint32_t)  0,	//   esp2;
    	(uint16_t)  0,	// ss2;
    	(uint16_t)  0,	// unused3;
    	(uint32_t)  0x0002B000,	//   cr3;
    	(uint32_t)  0x1C000,	//   eip;
    	(uint32_t)  0,	//   eflags;
    	(uint32_t)  0,	//   eax;
    	(uint32_t)  0,	//   ecx;
    	(uint32_t)  0,	//   edx;
    	(uint32_t)  0,	//   ebx;
    	(uint32_t)  0x0002B000 - 1, //   esp;
    	(uint32_t)  0,	//   ebp;
    	(uint32_t)  0,	//   esi;
    	(uint32_t)  0,	//   edi;
    	(uint16_t)  0,	// es;
    	(uint16_t)  0,	// unused4;
    	(uint16_t)  14 << 3,	// cs;
    	(uint16_t)  0,	// unused5;
    	(uint16_t)  16 << 3,	// ss;
    	(uint16_t)  0,	// unused6;
    	(uint16_t)  16 << 3,	// ds;
    	(uint16_t)  0,	// unused7;
    	(uint16_t)  0,	// fs;
    	(uint16_t)  0,	// unused8;
    	(uint16_t)  0,	// gs;
    	(uint16_t)  0,	// unused9;
    	(uint16_t)  0,	// ldt;
    	(uint16_t)  0,	// unused10;
    	(uint16_t)  0,	// dtrap;
    	(uint16_t)  0,	// iomap;
    };
	return 0;
}
