# Proyecto: Analizador Léxico y Sintáctico de Go

Este proyecto implementa un analizador léxico para el lenguaje de programación Go. El analizador es capaz de leer un archivo de código fuente en Go (en este caso `concurrentSum.go`), dividirlo en componentes léxicos (tokens) y
analizar su sintaxis.

## Requisitos

Para compilar y ejecutar este proyecto, asegúrate de tener instalados los siguientes programas:

- **GCC** o cualquier compilador compatible con C.
- **Make** para gestionar la compilación.
- **Linux** o cualquier sistema operativo compatible con herramientas de compilación estándar de C.

## Archivos principales

- **`P1.c`**: Contiene la implementación principal del analizador léxico y sintáctico.
- **`concurrentSum.go`**: Archivo de código fuente en Go que será analizado.
- **`Makefile`**: Archivo para gestionar la compilación del proyecto.

## Compilación

1. Clona este repositorio en tu máquina local.

```bash
git clone <URL_DEL_REPOSITORIO>
cd <nombre_del_repositorio>
```

2. Ejecuta el siguiente comando para compilar el proyecto:

```bash
make
```

Este comando generará el ejecutable `P1` que contiene el programa principal.

## Ejecución

Para ejecutar el programa y analizar el archivo `concurrentSum.go`, simplemente ejecuta:

```bash
./P1 concurrentSum.go
```

El analizador léxico procesará el archivo `concurrentSum.go`, desglosando sus componentes léxicos y realizando el
análisis sintáctico.

## Estructura del Proyecto

```plaintext
.
├── AnalizadorLexico
│   ├── analizadorLexico.h
│   ├── analizadorLexico.l
│   └── lex.yy.c
├── AnalizadorSintactico
│   ├── analizadorSintactico.c
│   └── analizadorSintactico.h
├── concurrentSum.go
├── Error
│   ├── error.c
│   └── error.h
├── HashTable
│   ├── hashTable.c
│   └── hashTable.h
├── main.c
├── makefile
├── README.md
└── TablaSimbolos
    ├── definiciones.h
    ├── tablaSimbolos.c
    └── tablaSimbolos.h
```

## Funcionalidad

1. **Análisis Léxico**: El analizador léxico escanea el código fuente Go y divide el archivo en tokens (por ejemplo,
   identificadores, números, operadores, etc.).
2. **Tabla de Símbolos**: Los tokens identificados se almacenan en una tabla de símbolos para un acceso rápido y
   procesamiento posterior.
3. **Análisis Sintáctico**: Después de analizar los componentes léxicos, el analizador sintáctico imprime por terminal la estructura del código Go según las reglas gramaticales definidas.
4. **Impresión de la tabla de símbolos**: Al comienzo y al finalizar el análisis sintáctico, el programa imprime la tabla de símbolos, mostrando todos los identificadores encontrados en el código fuente junto con su tipo y ubicación en el archivo.