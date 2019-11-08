## Ejercicios 2 y 3

#### idt.c
- Agregamos un par de defines para los atributos de las entradas de la IDT de 
  Kernel y de Tarea (un define para cada una).
- Creamos una macro `IDT_ENTRY` para ayudarnos a armar la IDT. Esta macro toma
  dos parámetros, `numero` y `attrVal`, y configura la entrada de número 
  `numero` de manera adecuada, utilizando los atributos `attrVal` para la 
  entrada.
- En `idt_init` configuramos las entradas de las excepciones implementadas por 
  Intel y de las interrupciones de Clock, Teclado y Syscall (32, 33 y 47, 
  respectivamente). Configuramos todas como de nivel Kernel, salvo la Syscall (
  pues su propósito es poder ser utilizada por la tarea).

#### isr.asm
- Implementamos la subrutina `_isr%1` para que imprima el número de excepción 
  que la llamó por pantalla.
- Utilizamos la macro `ISR 1` para implementar las rutinas de atención de todas
  las excepciones implementadas por Intel.
- Escribimos la rutina de atención del Clock para que printee la animación de
  reloj provista por la cátedra en la esquina inferior derecha de la pantalla.
- Implementamos la rutina de atención del Teclado para que, en caso de que el
  "make code" de la tecla presionada corresponda a algún dígito decimal, imprima
  en pantalla el dígito presiondo en la esquina superior derecha.
- Escribimos la rutina de atención de la Syscall para que reemplaze el valor de
  eax por el número 0x42.

#### isr.h
- Declaramos en isr.h todas las rutinas de atención de interrupción / ejecución.

#### kernel.asm
- Llamamos a `idt_init` para inicializar la IDT y luego cargamos el IDTR con la
  instrucción `lidt`.
- Resetteamos el PIC y lo habilitamos.
- Habilitamos interrupciones.
- Probamos que las excepciones se impriman en pantalla dividiendo por cero.

## Ejercicio 4
Este ejercicio trata de la MMU.

#### defines.h
- Agregamos defines de utilidad para sumar descriptividad a los descriptores 
  (valga la redundancia, y para que Ezequiel no nos pegue)

#### kernel.asm
- Llamamos a `mmu_initKernelDir`
- Habilitamos paginación (poniendo el bit 31) de CR0 en 1.
- Agregamos una subrutina `print_group` que se encarga de imprimir en pantalla
  las libretas universitarias de los integrantes del equipo.

#### mmu.h
- Agregamos las definiciones de los structs para las PDE's y PTE's

#### mmu.c
- Completamos `mmu_initKernelDir`, que se encarga de:
    - Inicializar el Page Directory del Kernel llenándolo de ceros.
    - Escribir la primera entrada del Directory, configurándola para acceso de
      supervisor.
    - Configuramos todas las entradas de la primera (y al menos por ahora única)
      tabla del Kernel, de manera tal que tengamos identity mapping para las
      direcciones 0x00000000 a 0x003FFFFF.

## Ejercicio 5
Este ejercicio trata de la MMU también.

#### defines.h
- Continuamos agregando defines de utilidad para sumar descriptividad a los 
  descriptores

#### kernel.asm
- Inicializamos la MMU llamando a `mmu_init`.
- A modo de prueba, llamamos a `init_taskDir` para configurar paginación para
  el jugador A tipo 1, y pisamos `CR3` con la dirección al directorio 
  correspondiente.

#### mmu.h
- Agregamos defines para utilizar como tipo enumerado para los niveles de 
  privilegios.
- Incluimos defines para los tipos de jugadores, cuyo valor será utilizado como
  índice para obtener la posición en la cual comienza el código para dicha
  tarea.
- Reemplazamos el parámetro `attrs` de la función `mmu_mapPage` por el nivel de
  privilegio de la tarea.

#### mmu.c
Definimos variables globales para saber cuál es la siguiente página libre para
el kernel y la tarea.

Además, creamos la estructura auxiliar `address`, que usaremos para parsear las
direcciones virtuales y obtener sus componentes.
Implementamos las funciones:

- `mmu_init`: Inicializa las variables globales descriptas previamente
- `mmu_nextFreeKernelPage` y `mmu_nextFreeTaskPage`: Incrementan los punteros
  definidos como variables globales (cada uno tiene uno que utiliza
  exclusivamente) y devuelven la siguiente página libre.
- `mmu_mapPage`:
    - Descomponemos la dirección virtual haciendo uso de la estructura auxiliar
      mencionada.
    - Luego utilizamos el cr3 (completo, pues los campos bajos no se utilizan)
      y el índice obtenido de la dirección lineal para obtener la PDE (Page
      Directory Entry).
    - Si la tabla referenciada en la PDE no existe, la creamos con el 
      privilegio correspondiente.
    - Finalmente, obtenemos la PTE referenciada, la ponemos presente y le 
      configuramos la base shifteando la dirección física provista.
    - Flusheamos (invalida la TLB)
- `mmu_createTable`: Se encarga de crear una tabla nueva desde 0, llenando
  todas las PTEs de la misma y configurándolas como "No presentes".
- `mmu_unmapPage`: Si el entry del directorio no está presente, no hace nada.
  Si lo está, simplemente obtiene la PTE adecuada y la configura como "No 
  presente".
- `mmu_initTaskDir`:
    - Pide una página nueva del kernel para almacenar el Page Directory de la
      tarea. Configura cada PDE con 0s.
    - Hace identity mapping con los primeros 4K de la memoria, para poder tener
      referenciado el Kernel. Esto es para poder resolver las excepciones que
      surjan durante la ejecución de la tarea y poder accionar desde el Kernel.
    - Obtenemos la dirección física del código de la tarea pedida, y se piden
      dos nuevas páginas, puesto que el código de cada tarea puede ocupar dos
      páginas (por el enunciado).
    - Mappeamos temporalmente las direcciones físicas donde queremos copiar el
      código en una dirección no utilizada.
    - Copiamos el código en las dos páginas pedidas.
    - Limpiamos los mappings temporales y devolvemos la dirección del nuevo 
      directorio de páginas.

## Ejercicio 6

#### defines.h
- Declaramos nuevas constantes para el uso en la GDT.

#### tss.c
Decidimos definir todas las tss's ahora, haciendo futurología (Facu Linari nos
dijo que en Ingeniería I nos van a enseñar a no hacer esto, pero todavía no la
cursamos :P)
- Implementamos `tss_init` para que inicialice todas las tss's de nuestro 
  sistema (la de la tarea inicial, idle y de las pelotas con sus respectivos
  handlers).
- Decidimos guardarnos las tss's de las tareas y los handlers en un array para
  poder recorrerlo más fácilmente luego.
- Creamos un método `tss_new_ball` que recibe por parámetro el número de jugador
  (A|B + tipo) y si es handler o no, y se encarga de devolver una tss 
  inicializada de manera adecuada.
- Creamos el método `tss_ball_reset`, que se encarga de reconfigurar el tss de
  una de las tareas de pelotas previo a su ejecución (en particular por el stack
  y un par de cosas más). Usaremos este método siempre que queramos lanzar una
  nueva pelota o una tarea handler.


#### gdt.c
- Escribimos las gdt entries de todas las TSS que necesitaremos. Estas son 6 
  para las tareas y otras 6 para sus respectivos handlers, una más para la tarea
  inicial y una última para la tarea _idle_. Para 
- Colocamos el bit busy de la gdt entry de la tarea inicial en 1... [VER!]