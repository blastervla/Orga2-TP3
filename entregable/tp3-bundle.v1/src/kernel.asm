asmsyntax=nasm
; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "print.mac"
%include "seg_print.mac"

%define SCREEN_W 80
%define SCREEN_H 50
%define C_LIGHT_GRAY 0x8
%define C_ALL_LIGHT_GRAY 0x88


%define GDT_C0 14<<3
%define GDT_C3 15<<3
%define GDT_D0 16<<3
%define GDT_D3 17<<3
%define GDT_V0 18<<3

global start
extern GDT_DESC


;; Saltear seccion de datos
jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
start_rm_msg db     'Iniciando kernel en Modo Real'
start_rm_len equ    $ - start_rm_msg

start_pm_msg db     'Iniciando kernel en Modo Protegido'
start_pm_len equ    $ - start_pm_msg
screen_cln_msg db     '   xX Usuario de Windows el que lee Xx    xX Usuario de Windows el que lee Xx   '
screen_cln_len equ    $ - screen_cln_msg

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

;; Punto de entrada del kernel.
BITS 16
start:
    ; Deshabilitar interrupciones
    cli

    ; Cambiar modo de video a 80 X 50
    ; ax = 1003h -> para poder tener 16 colores de background
    mov ax, 1003h
    int 10h ; set mode 03h
    xor bx, bx
    mov ax, 1112h
    int 10h ; load 8x8 font

    ; Imprimir mensaje de bienvenida
    print_text_rm start_rm_msg, start_rm_len, 0x07, 0, 0
    

    ; Habilitar A20
    
    ; Cargar la GDT

    lgdt [GDT_DESC]
    ; Setear el bit PE del registro CR0
    
    ; Saltar a modo protegido
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp (GDT_C0):modo_protegido
modo_protegido:
BITS 32

    ; Establecer selectores de segmentos

    mov eax, GDT_D0
    mov ss, eax

    mov ds, eax
    mov gs, eax
    mov fs, eax

    ; Establecer la base de la pila
    
    mov esp, 0x2B000

    ; Imprimir mensaje de bienvenida
    print_text_pm start_pm_msg, start_pm_len, 0x07, SCREEN_W / 2 - start_rm_len / 2, SCREEN_H / 2


    ; Inicializar pantalla
    ; Screen Size : 80 x 50 
    mov eax, GDT_V0
    mov ds, eax ; Usamos el selector de video

    xchg bx, bx

    call limpiar_pantalla

    mov eax, GDT_D0
    mov ds, eax ; TODO: Checkear por redundancia / utilidad




    ; Inicializar el manejador de memoria
 
    ; Inicializar el directorio de paginas
    
    ; Cargar directorio de paginas

    ; Habilitar paginacion
    
    ; Inicializar tss

    ; Inicializar tss de la tarea Idle

    ; Inicializar el scheduler

    ; Inicializar la IDT
    
    ; Cargar IDT
 
    ; Configurar controlador de interrupciones

    ; Cargar tarea inicial

    ; Habilitar interrupciones

    ; Saltar a la primera tarea: Idle

    ; Ciclar infinitamente (por si algo sale mal...)
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $

limpiar_pantalla:
    push ebp
    mov ebp, esp

    mov ecx, SCREEN_H * 2
    .loop:
        print_text_pm screen_cln_msg, screen_cln_len, C_ALL_LIGHT_GRAY, ecx, 0
        
        dec ecx
        cmp ecx, 0
        jge .loop 

    pop ebp
    ret

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
