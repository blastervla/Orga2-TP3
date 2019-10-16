; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "print.mac"
%include "colors.mac"

BITS 32

sched_task_offset:     dd 0xFFFF
sched_task_selector:   dw 0xFFFFFFFF

;; PIC
extern pic_finish1

;; Sched
extern sched_nextTask

extern print_dec

global _isr32
global _isr33
global _isr47

;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

%macro ISR 1
global _isr%1

_isr%1:
    ; uint32_t numero, 
    ; uint32_t size, 
    ; uint32_t x, 
    ; uint32_t y, 
    ; uint16_t attr
    push C_BG_WHITE + C_FG_BLACK
    push 25
    push 40
    push  1
    push %1
    call print_dec

    mov eax, %1
    jmp $

%endmacro


;; Rutina de atención de las EXCEPCIONES
;; -------------------------------------------------------------------------- ;;
ISR 0
ISR 1
ISR 2
ISR 3
ISR 4
ISR 5
ISR 6
ISR 7
ISR 8
ISR 9
ISR 10
ISR 11
ISR 12
ISR 13
ISR 14
ISR 16
ISR 17
ISR 18
ISR 19
ISR 20
ISR 30

;; Rutina de atención del RELOJ
;; -------------------------------------------------------------------------- ;;
_isr32:
    call nextClock
    call pic_finish1
    iret

;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;
ISR 33;_isr33:

    ;iret

;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;
ISR 47;_isr47:

    ;iret

;; Funciones Auxiliares
;; -------------------------------------------------------------------------- ;;
isrNumber:           dd 0x00000000
isrClock:            db '|/-\'
nextClock:
        pushad
        inc DWORD [isrNumber]
        mov ebx, [isrNumber]
        cmp ebx, 0x4
        jl .ok
                mov DWORD [isrNumber], 0x0
                mov ebx, 0
        .ok:
                add ebx, isrClock
                print_text_pm ebx, 1, 0x0f, 49, 79
                popad
        ret
