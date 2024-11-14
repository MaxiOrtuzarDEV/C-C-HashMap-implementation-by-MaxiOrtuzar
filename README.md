# Implementación de HashMap en C/C++

## Descripción

Este proyecto implementa una estructura de datos HashMap en C/C++, diseñada para gestionar pares clave-valor utilizando una función hash para un acceso rápido. La estructura soporta métodos básicos de inserción, eliminación, búsqueda y serialización de datos para persistencia en disco.

## Características

- **Inserción de elementos**: Añade un nuevo par clave-valor al HashMap.
- **Eliminación de elementos**: Remueve elementos según su clave.
- **Búsqueda de valores**: Obtiene el valor asociado a una clave específica.
- **Manejo de colisiones**: Utiliza encadenamiento en listas enlazadas para resolver colisiones.
- **Redimensionamiento dinámico**: Amplía la capacidad del HashMap cuando el factor de carga supera el umbral definido.
- **Serialización y deserialización**: Guarda el HashMap en un archivo de texto y permite cargarlo nuevamente.

## Archivos

- **hashmap.h**: Contiene la definición de las estructuras `HASHMAP` y `NODO_HM`, así como las funciones asociadas.
- **main.cpp**: Archivo principal del programa (si se proporciona).
- **CMakeLists.txt**: Archivo de configuración para compilar el proyecto con CMake.

## Compilación

Este proyecto utiliza CMake para gestionar la compilación. Para compilar el programa:

1. Crear un directorio de compilación:
    ```bash
    mkdir build
    cd build
    ```

2. Ejecutar CMake y compilar:
    ```bash
    cmake ..
    make
    ```

3. Ejecutar el programa:
    ```bash
    ./nombre_del_ejecutable
    ```

## Uso

Para usar las funcionalidades del HashMap:

1. Insertar una clave-valor:
   ```cpp
   HASHMAP hashmap;
   hashmap.insertar(100, "ejemplo");
