# Gestion de Cartelera de Cine

Este proyecto es una solución a la tarea 1 correspondiente a la asignatura de Algoritmos y Programación impartida en la Universidad del Bío-Bío. El objetivo del proyecto es desarrollar un sistema para gestionar la cartelera de un cine, permitiendo la administración de películas, lo que incluye agregar y listar películas disponibles.

---

# Implementación

El proyecto está implementado en el lenguaje de programación C, haciendo uso de listas enlazadas para gestionar la información de las películas. Así como funciones para manejar las operaciones de agregar y listar películas.

---

# Estructura del Proyecto

- `src/`: Contiene los archivos fuente en C.
- `include/`: Contiene los archivos de cabecera.
- `bin/`: Contiene los archivos ejecutables generados.

---

# Características del Proyecto

## Interoperabilidad

El proyecto está diseñado para ser compatible con múltiples sistemas operativos, incluyendo Windows, macOS y Linux.

## Facilidad de Uso

La interfaz de línea de comandos es intuitiva y fácil de usar, permitiendo a los usuarios interactuar con el sistema de manera eficiente.

## Validación de Datos

El sistema incluye validaciones para asegurar que los datos ingresados sean correctos y consistentes. Esto incluye verificar que los campos obligatorios estén completos y que los datos cumplan con el formato esperado.
Además, se implementan mecanismos para manejar errores y excepciones, tales como fallos durante la asignación de memoria o la manipulación de archivos.

---

# Cómo Compilar y Ejecutar

Para compilar el proyecto, asegúrate de tener instalado un compilador de C (como GCC). Luego, puedes utilizar el siguiente comando en la terminal desde la raíz del proyecto:

```bash
gcc src/*.c -o bin/programa
```

Para ejecutar el programa, utiliza el siguiente comando:

```bash
./bin/programa
```

# Licencia

Este proyecto fue desarrollado con fines académicos y no posee una licencia específica. Sin embargo, se permite su uso y modificación con fines educativos, siempre que se reconozca la autoría original.
