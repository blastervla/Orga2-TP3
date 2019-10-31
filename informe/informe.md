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
