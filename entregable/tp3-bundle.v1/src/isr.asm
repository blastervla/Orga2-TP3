; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "print.mac"
%include "colors.mac"
%include "defines.mac"

%define PROCESSING_TICK 6

BITS 32

sched_task_offset:     dd 0
sched_task_selector:   dw 0

current_clock: db 0

;; PIC
extern pic_finish1
extern pic_finish2

;; Sched
extern sched_isHandler
extern sched_nextTask
extern sched_getTareaActual
extern sched_registerHandler
extern sched_killIfNotHandler
extern sched_killIfHandler
extern sched_killCurrent
extern sched_makeItLookLikeAnAccident

;; Game
extern game_tick
extern game_executeFrame
extern game_talk
extern game_getCurrentX
extern game_getCurrentY
extern game_informAction
extern game_kbInput
extern game_showDebugInfo
extern game_isDebugChartOn
extern game_killCurrentBall

extern print_dec

global _isr32
global _isr33
global _isr47

global saltarAIdle

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
    ; push C_BG_WHITE + C_FG_BLACK
    ; push 25
    ; push 40
    ; push  2

    ; Luego del cambio de privilegio, tenemos el error code al tope de la pila
    ; si lo hubo, y sino el EIP. No pusheamos nada porque ya està en la pila
    ;
    ; Pila despues del cambio de privilegio

    pushad

    ; Pila
    ;   EDI
    ;   ESI
    ;   EBP
    ;   ESP
    ;   EBX
    ;   EDX
    ;   ECX
    ;   EAX
    ; priv chg
    ;   Error code
    ;   EIP
    ;   CS
    ;   EFLAGS
    ;   ESP
    ;   SS

    push %1
    ; call print_dec
    call game_killCurrentBall
    call game_showDebugInfo
    call sched_makeItLookLikeAnAccident

    add esp, 4
    popad
    iret

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
    pushad
    call pic_finish1

    ; Si está el modo debug no queremos seguir con la logica del juego.
    call game_isDebugChartOn
    cmp ax, 0
    jne .end

    ; Registrar tick en el juego (para el cálculo de input de usuario)
    call game_tick
    ; Llamar a sched_nextTask y efectivamente cargar la tarea!
    mov cl, [current_clock]
    cmp cl, PROCESSING_TICK
    je .calculateAndIdle

    inc byte [current_clock] ; Incrementamos contador de tarea!

    ; Si la tarea actual es un handler, es porque nunca llamò a inform action,
    ; entonces hay que matarla.
    call sched_killIfHandler

    ; Pedimos el selector tss de la siguiente tarea
    call sched_nextTask

    str bx
    cmp bx, ax
    je .end     ; Si son la misma tarea, no la cambiamos!!!

    ; Salto a la tarea
    mov [sched_task_selector], ax
    jmp far [sched_task_offset]
    jmp .end

.calculateAndIdle:
    mov byte [current_clock], 0
    call game_executeFrame  ; Actualizamos la UI y calculamos todo

    ; Ejecutamos la tarea Idle por el resto del ciclo
    call saltarAIdle

.end:
    call nextClock
    popad
    iret

;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;
_isr33:
    pushad
    call pic_finish1

    ; Item 3. d -------------------------------------------------------------
    ; in al, 0x60
    ; 02 (1), 03 (2), 04 (3), 05 (4), 06 (5), 07 (6), 08 (7), 09 (8), 0a (9), 0b (0)
    ; dec al ; Convertimos a decimal

    ; cmp eax, 10
    ; jg .noPrint

    ; push C_BG_WHITE + C_FG_BLACK
    ; push 0
    ; push 79
    ; push 1
    ; push eax
    ; call print_dec

    ; add esp, 20
;.noPrint:
    ; Item 3. d -------------------------------------------------------------

    xor eax, eax
    in al, 0x60
    push eax
    call game_kbInput
    add esp, 4          ; Limpiamos

    popad
    iret

;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;
_isr47:
    pushad

    cmp eax, SYSCALL_INFORM_ACTION
    je .informAction
    cmp eax, SYSCALL_SET_HANDLER
    je .setHandler
    cmp eax, SYSCALL_WHERE
    je .where
    cmp eax, SYSCALL_TALK
    jne .end

.talk:
    ; Envía al sistema el mensaje almacenado en EBX, máximo 20 chars

    push ebx
    call game_talk
    add esp, 4  ; Limpiamos el parámetro que pasamos antes

    jmp .end

.where:
    ; Retorna los valores x e y correspondientes a la posición 

    ; actual de la pelota en EBX y ECX (respectivamente). X va
    ; entre 1 y 78 (siendo 1 el extremo donde originalmente se
    ; lanzó la pelota). Y va de 1 a 40, 1 siendo la primera 
    ; fila y 40 la última.
    
    ; Le preguntamos a game cuál es la posición actual de la pelota en
    ; cuestión.
    call game_getCurrentX
    mov ebx, eax

    call game_getCurrentY
    mov ecx, eax

    jmp .end

.setHandler:
    ; Registra en el sistema la dirección de memoria del handler
    ; para la tarea actualmente en ejecución.
    ;
    ; ebx = f_handler_t* f

    push ebx
    call sched_registerHandler
    add esp, 4  ; Limpiamos el parámetro que pasamos antes

    jmp .end

.informAction:
    ; Este servicio se utiliza para retornar al sistema luego
    ; de la ejecución de un handler.
    ; ebx = e_action action

    ; 1. Obtenemos iTareaActual de sched.
    ; 2. Reportamos a game la acción que realizó la pelota actual.
    ; 3. Somos losotro´

    ; El servicio debe ser llamado desde un handler
    call sched_killIfNotHandler

    push ebx
    call game_informAction ; game_informAction(action)
    add esp, 4  ; Limpiamos el parámetro que pasamos antes

    call sched_nextTask     ; Pedimos el selector tss de la siguiente tarea

    str bx
    cmp bx, ax
    je .end     ; Si son la misma tarea, no la cambiamos!!!

    ; Salto a la tarea
    mov [sched_task_selector], ax
    jmp far [sched_task_offset]

.end:
    popad
    iret

;; Funciones Auxiliares
;; -------------------------------------------------------------------------- ;;
isrNumber:           dd 0x00000000
isrClock:            db '|/-\'
nextClock:
        inc DWORD [isrNumber]
        mov ebx, [isrNumber]
        cmp ebx, 0x4
        jl .ok
                mov DWORD [isrNumber], 0x0
                mov ebx, 0
        .ok:
                add ebx, isrClock
                print_text_pm ebx, 1, 0x0f, 49, 79
        ret

saltarAIdle:
    str bx
    cmp bx, (GDT_IDX_TSS_IDLE << 3)
    je .end     ; Si ya estamos ejecutando al idle, no la cambiamos!

    jmp (GDT_IDX_TSS_IDLE << 3):0

.end:
    ret