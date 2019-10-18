## Ejercicio 3 - Interrupciones
-
## Ejercicio 4 - Paginación
- Calculamos las direcciones de forma tal que la paginación sea Identity
  mappin'.
- Definimos como dirección del directorio de tablas, la posición física especificada por el enunciado.
- Declaramos un struct para los entries de ambas tablas para llenarlos de forma más cómoda y declarativa.
- Las entradas de estas tablas están alineadas a 4 bytes.
- Así mísmo, inicializamos una sola tabla de página, que contiene 1024 página.
- Pusimos en el registro de control _cr3_ la dirección del único directorio de paginas, dejando en 0 el resto de los atributos ya que estos no son utilizados.
- Habilitamos paginación poniendo en 1 el bit 31 del registro de control _cr0_.
- Imprimimos las libretas de los integrantes del grupo.
